#*******************************************************************************
#
#  FILENAME: VisionCommon.inc
#
#  Copyright (c) 2013, Teledyne LeCroy - All Rights Reserved
#
#  DESCRIPTION
#    This file contains common functions that are used in USB3 Vision decoder files.
#
#  REVISION HISTORY
#    13MAR13 First created -ag-
#
#*******************************************************************************

%include "CATCScriptAPI.inc"      
%include "USBCommon.inc"          #include useful decoder functions


set DECODE_ABORTED_OFFSET = 0;
set DECODE_ABORTED_FLAG = 0;

set VisionPrefix = 
[
    [0x00000000, "Unknown"],
    [0x43563355, "U3VC"],
    [0x45563355, "U3VE"]
];


set VisionPrefixFunc = 
[
    [0x00000000, "UNKNOWN_VISION_CHANNEL"],
    [0x43563355, "VISION_CONTROL_CHANNEL"],
    [0x45563355, "VISION_EVENTS_CHANNEL"]
];

set VisionControlEventFields = Map(
[
    ["Prefix",          0,  4,  0xFFFFFFFF,  "Prefix", "0x%08x",    null,            0,  "This Prefix does not match the USB3 Vision control or Events channel prefix"],
    ["ControlPrefix",   0,  4,  0xFFFFFFFF,  "Prefix", "%s",        VisionPrefix,    0,  "This Prefix contains the ASCII string “U3VC” (0x43563355) standing for USB3 Vision Control"],
    ["EventsPrefix",    0,  4,  0xFFFFFFFF,  "Prefix", "%s",        VisionPrefix,    0,  "This Prefix contains the ASCII string “U3VE” (0x45563355) standing for USB3 Vision Events"]    
] );


DecodeVisionControlEvents(offset)
{
    DECODE_ABORTED_OFFSET = 0;
    DECODE_ABORTED_FLAG = 0;

    out.Decoded = offset;    
    
    # Check signature of USB3 Vision
    _result = GetFieldData("Prefix", offset, VisionControlEventFields);   
           
    _row = Find( VisionPrefixFunc, _result[1] );    
    
    return Call( _row[1], [offset] );    
}

UNKNOWN_VISION_CHANNEL(offset)
{
    FieldColor = RGB(0, 0, 0);
    AddCaptionCell(" Vision "," Unknown ","USB3 Vision Unknown Channel", _MONOCOLOR );       
    FieldColor = RGB(250, 58, 31);

    AddField("Prefix", offset, VisionControlEventFields);  
    
    out.Decoded += 4;
    
    return 0;
}

VISION_CONTROL_CHANNEL(offset)
{
    FieldColor = RGB(24, 153, 248);        
    AddCaptionCell(" Vision "," Control ","USB3 Vision Device Control", _MONOCOLOR );
    FieldColor = RGB(133, 201, 252);

    AddField("ControlPrefix", offset, VisionControlEventFields);  
    AddSeparator();           
    
    out.Decoded += 4;
    
    return 1;
}

VISION_EVENTS_CHANNEL(offset)
{
    FieldColor = RGB(206, 77, 234);        
    AddCaptionCell(" Vision "," Events","USB3 Vision Device Events", _MONOCOLOR );
    FieldColor = RGB(234, 177, 245);
  
    AddField("EventsPrefix", offset, VisionControlEventFields);  
    AddSeparator();           

    out.Decoded += 4;
    
    return 1;
}

##########################################################################
#                       General Utility Functions
##########################################################################
AddDataPayloadField(FieldId, offset, len, FieldsArray)
{
    _row = Find(FieldsArray, FieldId);

    offset = _row[1] + offset;
   
    if( DECODE_ABORTED_FLAG && offset >= DECODE_ABORTED_OFFSET )
        return 0;
    
    if( offset + len > in.DataLength )
    {        
        AddCell("NOT ENOUGH DATA","", "", WarningColor, _MONOFIELD);
        len = in.DataLength - offset;
    }

    GetNBits(in.Data, offset * 8, 0);

    SetFieldOffsetLen(offset * 8, len * 8);
    ShowDataBlockReOrder(len);                
    
    return 1;
}

AddDataPayloadFieldForRest(offset)
{
    GetNBits(in.Data, offset * 8, 0);

    len = in.DataLength - offset;
    SetFieldOffsetLen(offset * 8, len * 8);
    ShowDataBlock(len);                
}

AddField(FieldId, offset, FieldsArray)
{    
    # Set to 1 if field is added successfully.
    ReturnValues[0] = 0; 
    # Field value if field is added successfully.
    ReturnValues[1] = 0;
           
    _row = Find(FieldsArray, FieldId);           
             
    offset          = _row[1] + offset;
    len             = _row[2];
    mask            = _row[3];
    name            = _row[4];
    valueformat     = _row[5];
    valuearray      = _row[6];
    isvaluebitmap   = _row[7];
    tooltip         = _row[8];        
    value           = 0;

    
    if( DECODE_ABORTED_FLAG && offset >= DECODE_ABORTED_OFFSET )
    {
        return ReturnValues;
    }
    
    if( offset + len > in.DataLength ) 
    {
        DECODE_ABORTED_FLAG = 1;             
        DECODE_ABORTED_OFFSET = offset;

        AddCell("DECODE ABORTED", "NOT ENOUGH DATA", "", WarningColor, _ERROR); 
        AddSeparator(); 
   
        return ReturnValues;
    }
 
    if(len == 1)
    {
        value = GetDataByte(offset);
        value &= mask;
    }
    else if(len == 2)
    {        
        value = GetDataWord(offset);
        value &= mask;
    }
    else if(len == 3)        
    {
        value = GetDataLong(offset);
        value &= 0x00FFFFFF;
        value &= mask;
    }    
    else if(len == 4)        
    {
        value = GetDataLong(offset);
        value &= mask;            
    }
    else
    {        
		value = GetDataByteArray(offset, len);
        value = GetArrayHexStringEx(value, 1);
    }
        
    ReturnValues[0] = 1;        
    ReturnValues[1] = value;
    
    if(valuearray != null)
    {        
        if( isvaluebitmap == 1 )
        {   
            strvalues = "";
            for( i = 0; i < len * 8; i++ )
            {                
                maskedvalue = value & (1 << i);
                if( maskedvalue )
                {
                    if( strvalues != "" )
                        strvalues += ", ";
                
                    _names = Find(valuearray, maskedvalue);
                    if(_names != null)
                        strvalues += Format( valueformat, _names[1] );    
                    else 
                        strvalues += Format( valueformat, Format("0x%04x", maskedvalue) );    
                }
            }

            value = strvalues;
        }
        else
        {
            _names = Find(valuearray, value);            
            if(_names != null)
                value = _names[1];
            else 
                value = Format("0x%x", value);
        }

    }
    
    AddPayLoadCell(name, Format(valueformat, value), tooltip);
    
    return ReturnValues;
}

GetFieldData(FieldId, offset, FieldsArray)
{
    # Set to 1 if field is added successfully.
    ReturnValues[0] = 0; 
    # Field value if field is added successfully.
    ReturnValues[1] = 0;
           
    _row = Find(FieldsArray, FieldId);           
             
    offset          = _row[1] + offset;
    len             = _row[2];
    mask            = _row[3];
    valueformat     = _row[5];    
    value           = 0;

    
    if( DECODE_ABORTED_FLAG && offset >= DECODE_ABORTED_OFFSET )
    {
        return ReturnValues;
    }
    
    if( offset + len > in.DataLength ) 
    {
        DECODE_ABORTED_FLAG = 1;             
        DECODE_ABORTED_OFFSET = offset;

        AddCell("DECODE ABORTED", "NOT ENOUGH DATA", "", WarningColor, _ERROR); 
        AddSeparator(); 
   
        return ReturnValues;
    }

    if(len == 1)
    {
        value = GetDataByte(offset);
        value &= mask;
    }
    else if(len == 2)
    {        
        value = GetDataWord(offset);
        value &= mask;
    }
    else if(len == 3)        
    {
        value = GetDataLong(offset);
        value &= 0x00FFFFFF;
        value &= mask;
    }    
    else if(len == 4)        
    {
        value = GetDataLong(offset);
        value &= mask;            
    }
    else
    {
        value = GetDataByteArray(offset, len);
        if(valueformat)
            value = GetArrayHexStringEx(value, 0); # Returns LSB-MSB byte stream
    }

    ReturnValues[0] = 1;        
    ReturnValues[1] = value;
    
    return ReturnValues;
}
 
 
GetAsciiString( value, byte_len )
{
    ret_value = "";

    for( i = 0; i < byte_len; i++ )
    {
        digit = value & 0xFF;
        ret_value += Format("%c", digit);                   
        value = value >> 8;        
    }
    
    return ret_value;
}
 

####################################################################################
#                       USBTracer specific caption cell                            #
####################################################################################

AddSpecCaptionCell(caption, text, tooltip, FieldColor, addparam, addparam1, addparam2 )
{   
    AddCell(caption, text, tooltip, FieldColor, _USBBULK_HEADER, addparam, addparam1, addparam2 );        
    return 1;        
}
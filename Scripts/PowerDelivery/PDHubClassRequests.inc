#S******************************************************************************
#*
#*  FILENAME: StandardRequestsForPD.dec
#*
#*  Copyright (C) 2015 Teledyn LeCroy
#*
#*  DESCRIPTION
#*    This is the request file for PDHUB device requests.
#*
#*  REVISION HISTORY
#*            File Created -mm
#*******************************************************************************

%include "PDCommon.inc"
%include "PDObjectDecodings.inc"

set DECODE_ABORTED_FLAG = 0;
set DECODE_ABORTED_OFFSET = 0;

set PDPortChangeMaskIntModeTable =
[
    [0,  "Reserved",                         null, "Reserved and shall not be used."],
    [1,  "External supply",                  null, "External supply. The Supply field shall indicate the current status of the supply."],
    [2,  "Port operation mode",              null, "Port operation mode. The Port Operation Mode field shall indicated the current operational mode of the Port."],
    [3,  "Supported Provider Capabilities",  null, "Supported Provider Capabilities. The SPM shall get the updated Power Data Objects from by retrieving the BOS Descriptor from the PDUSB Hub."],
    [4,  "Negotiated power level",           null, "Negotiated power level. The Request Data Object field shall indicate the power level that the Port partner wants to operate at."],
    [5,  "New power direction",              null, "New power direction. This field shall indicate the Port partner wants to perform a Power Role Swap."],
    [6,  "PD Reset Complete",                null, "PD Reset Complete. This field shall indicate that a PD Hard Reset or a Cable Reset has completed."],        
    [7,  "Insertion Detect",                 null, "Insertion Detect. The Insertion Detect field shall indicate the current status of whether a cable is plugged into this Port."],
    [8,  "PD Capable Cable",                 null, "PD Capable Cable. The PD Capable Cable field shall indicate the current status of whether a PD Capable Cable is plugged into this Port."],
    [9,  "Request Rejected",                 null, "Request Rejected. This field shall indicate one of two conditions:\n\t\t * The PDUSB Hub received a request to change the power level (Negotiated power level (Bit 4) bit in this field shall be set) that was rejected.\n\t\t * The PDUSB Hub received a request to perform a Power Role Swap (New power direction bit (Bit 5) in this field shall be set) that was rejected."],
    [10, "Reserved",                         null, "Reserved and shall be set to zero."],
    [11, "Hybrid Mode Request",              null, "Hybrid Mode Request."],
    [12, "Power Role Swap Completed",        null, "Power Role Swap Completed. This shall indicate that the hub completes a Power Role Swap requested by the SPM.\nThe SPM can determin if the Swap request was successful or unsuccessful based on the PD Direction bit."],
    [13, "VDM Received",                     null, "VDM Received. The SPM shall use the Get VDMs command (see section 9.4.8) to get further details on this notification."],
    [14, "Reserved",                         null, "Reserved and shall be set to zero."],
    [15, "Error",                            null, "Error. This field shall indicate that an unknown error has occurred on the Port."]
];

set PDPortChangeMaskNonIntModeTable =
[
    [0,  "Reserved",                        null, "Reserved and shall not be used."],
    [1,  "External supply",                 null, "External supply. The Supply field shall indicate the current status of the supply."],
    [2,  "Port operation mode",             null, "Port operation mode. The Port Operation Mode field shall indicated the current operational mode of the Port."],
    [3,  "Supported Provider Capabilities", null, "Supported Provider Capabilities. The SPM shall get the updated Power Data Objects from by retrieving the BOS Descriptor from the PDUSB Hub."],
    [4,  "Negotiated power level",          null, "Negotiated power level. The Request Data Object field shall indicate the newly negotiated power level."],
    [5,  "New power direction",             null, "New power direction. This field shall indicate that the power direction has changed."],
    [6,  "PD Reset Complete",               null, "PD Reset Complete. This field shall indicate that a PD Hard Reset or a Cable Reset has completed."],        
    [7,  "Insertion Detect",                null, "Insertion Detect. The Insertion Detect field shall indicate the current status of whether a cable is plugged into this Port."],
    [8,  "PD Capable Cable",                null, "PD Capable Cable. The PD Capable Cable field shall indicate the current status of whether a PD Capable Cable is plugged into this Port."],
    [9,  "Request Rejected",                null, "Request Rejected. This field shall indicate one of two conditions:\n\t\t * The PDUSB Hub received a request to change the power level (Negotiated power level (Bit 4) bit in this field shall be set) that was rejected.\n\t\t * The PDUSB Hub received a request to perform a Power Role Swap (New power direction bit (Bit 5) in this field shall be set) that was rejected."],
    [10, "Reserved",                        null, "Reserved and shall be set to zero."],
    [11, "Hybrid Mode Request",             null, "Hybrid Mode Request."],
    [12, "Power Role Swap Completed",       null, "Power Role Swap Completed. This shall indicate that the hub completes a Power Role Swap requested by the SPM.\nThe SPM can determin if the Swap request was successful or unsuccessful based on the PD Direction bit."],
    [13, "VDM Received",                    null, "VDM Received. The SPM shall use the Get VDMs command (see section 9.4.8) to get further details on this notification."],
    [14, "Reserved",                        null, "Reserved and shall be set to zero."],
    [15, "Error",                           null, "Error. This field shall indicate that an unknown error has occurred on the Port."]
];

set PDExternalSupplyTable = [
    [ 0,  "No",      null,  "No External Supply Presents"  ],
    [ 1,  "Yes",     null,  "External Supply Presents"     ]
];

set PDPortOprModeTable = [
    [ 8, "Undefined",         null,  ""],
    [ 0, "No Consumer",       null,  ""],
    [ 1, "Legacy",            null,  ""],
    [ 2, "BC",                null,  ""],
    [ 3, "PD",                null,  ""],
    [ 4, "Type-C Current",    null,  ""]
];

set PDInsertionDetectTable = [
    [ 0, "Not Detected", null, "Cable Insertion Not Detected" ],
    [ 1, "Detected",     null, "Cable Insertion Detected"     ]
];

set PDCapableCableTable = [
    [ 0, "Not Detected", null, "PD Capable Cable Not Detected" ],
    [ 1, "Detected",     null, "PD Capable Cable Detected"     ]
];

set PDDirectionTable = [
    [ 0, "Consumer",    null, "Port is operating as a Consumer" ],
    [ 1, "Provider",    null, "Port is operating as a Provider" ]
];

set PD_Status_Fields = Map(
[
    ["PortStMaskIntMode",    0,  16,   0xFFFF,     "PD Port Change Bits",  "%s",   PDPortChangeMaskIntModeTable,    1, "Port Status Change"],
    ["PortStMaskNotIntMode", 0,  16,   0xFFFF,     "PD Port Change Bits",  "%s",   PDPortChangeMaskNonIntModeTable, 1, "Port Status Change"],
    ["ExtSupply",           16,  1,    0x1,        "Ext Supp",             "%s",   PDExternalSupplyTable,           0, "External Supply"],
    ["PortOprMode",         17,  3,    0x7,        "Port Opr Mode",        "%s",   PDPortOprModeTable,              0, "Current port operation mode"],
    ["InsertionDetect",     20,  1,    0x1,        "Cable Insertion",      "%s",   PDInsertionDetectTable,          0, "The field indicates the current status of whether a cable is plugged into this Port or not."],
    ["PDCapableCable",      21,  1,    0x1,        "PD Capable Cable",     "%s",   PDCapableCableTable,             0, "The field indicates the current status of whether a PD Capable cable is plugged into this Port or not."],
    ["PortRole",            22,  1,    0x1,        "Port Role",            "%s",   PDDirectionTable,                0, "The field indicates whether the Port is operating as a Consumer or Provider."],
    ["Reserved",            23,  9,    0x1FF,      "Reserved",         "0x%03X",   null,                            0, "Reserved. Shall be set to zero."]
] );

AddPDStatusField(FieldId, offset)
{
    if( DECODE_ABORTED_FLAG )
        return 0;
    _row = Find(PD_Status_Fields, FieldId);

    offset          = _row[1] + offset;
    len             = _row[2];
    mask            = _row[3];
    name            = _row[4];
    valueformat     = _row[5];
    valuearray      = _row[6];
    isvaluebitmap   = _row[7];
    tooltip         = _row[8];        
    value           = 0;
    raw_value       = 0;

    if( offset + len > in.DataLength * 8 )
    {
        DECODE_ABORTED_FLAG = 1;
        DECODE_ABORTED_OFFSET = offset;

        AddSeparator();
        AddCell("DECODE ABORTED", "NOT ENOUGH DATA", "", WarningColor, _ERROR); 
        AddSeparator();
        return 0;
    }
    
    value = GetNBits(in.Data, offset, len);
    value &= mask;
    raw_value = value;
    
    if(valuearray != null)
    {
        if( isvaluebitmap == 1 )
        {
            tooltip += Format(": 0x%X", raw_value);
            tooltip = ToBitDecode(valuearray, value, "", tooltip);
            value = ToBitString(value, len);
        }
        else
        {
            _names = Find(valuearray, value);
            if(_names != null)
                value = _names[1];
            else
                value = Format("0x%X", value);

            if( sizeof(_names) > 3 )
            {
                if( _names[3] )
                    tooltip = _names[3];
            }
        }
    }
    
    tooltip += Format("\n\n%s: ", name);
    tooltip += Format("0x%X", raw_value);
    
    AddPayLoadCell(name, Format(valueformat, value), tooltip);
    
    return 1;
}
PD_GET_STATUS()
{
    out.Decoded = 16;
    DECODE_ABORTED_FLAG = 0;
    
    if ( bReqType == 0xA3 )
    {
        if (wValue != 1)
            AddWValueCell(wValue, FormatEx(_err_Illegal_Value, "wValue", wValue, 0 ) );  
        else
            AddWValueCell(wValue, "Correct Value of 1" );
        
        if (wLength != 8)
            AddWLengthCell( FormatEx(_err_Illegal_Value, "wLength", wLength, 8 ) , 1 );  
        else
            AddWLengthCell( "Correct Value of 8", 0 );
        
        offset = 64;
        CurrentFldInit();
        FieldColor = 0xABCDEF;
        
        intrusive_mode = GetNBits(in.Data, offset + 11, 1);
        
        if( intrusive_mode )
            AddPDStatusField( "PortStMaskIntMode",    offset );
        else
            AddPDStatusField( "PortStMaskNotIntMode", offset );

        AddPDStatusField( "ExtSupply",        offset );
        AddPDStatusField( "PortOprMode",      offset );
        AddPDStatusField( "InsertionDetect",  offset );
        AddPDStatusField( "PDCapableCable",   offset );
        AddPDStatusField( "PortRole",         offset );
        AddPDStatusField( "Reserved",         offset );
        
        AddSeparator();
        
        if( !DECODE_ABORTED_FLAG )
        {
            req_data_offset = 12;
            DecodeRequestDataObject( req_data_offset, intrusive_mode );
        }
    }
    else
    {
        AddPayLoadCell("Invalid bReqType value",   Format("0x%02X", bReqType),   "Expected 0xA3 only",  ErrorColor); 
    }
}

PD_GET_STATUS_text()
{}

PD_DecodeClearPortPDFeature()
{
    mask = GetDataWord( 8 );
    Tooltip = ToBitDecode(PDPortChangeMaskTable, mask, "", "Clear Change Mask\n");
    MaskText = ToBitString(mask, 16);
    AddPayLoadCell( "Mask", MaskText, Tooltip ); 
}

PD_GET_PARTNER_PDO()
{
    if ( bReqType == 0xA3 )
    {
        out.Decoded = 8 + wLength;
        
        if ( wValue == 0 )
            AddWValueCell("Consumer PDOs", Format("wValue = 0x%04X\n\nConsumer PDOs", wValue), 0 );
        else if ( wValue == 1 )
            AddWValueCell("Provider PDOs", Format("wValue = 0x%04X\n\nProvider PDOs", wValue), 0 );
        else
            AddWValueCell("", Format("wValue = 0x%04X\nError: only legal value are 0 and 1", wValue ) , 1 );

        AddWIndexCell( Format("For Port # %i", wIndex), "Hub Port Number for this Request" );
        
        if ( wLength % 4 == 0 )
            AddWLengthCell( Format("%d data objects", wLength / 4), 0 );
        else
            AddWLengthCell( "Invalid data length. Expected multiples of 4" , 1 );
        
        if ( wLength / 4 > 0 )
        {
            curr_offset = 8;
            if( wValue == 1 )
                DecodeSrcCapDataObjects( curr_offset );
            else
                DecodeSinkCapDataObjects( curr_offset );
        }
    }
    else
    {
        AddPayLoadCell("Invalid bReqType value",   Format("0x%02X", bReqType),   "Expected 0xA3 only",  ErrorColor);
    }    
}

PD_GET_PARTNER_PDO_text()
{}

PD_SET_PDO()
{
    if ( bReqType == 0x23 )
    {
        out.Decoded = 8 + wLength;
        
        if ( wValue == 0 )
            AddWValueCell("", "Correct Value of 0", 0 );
        else
            AddWValueCell("", FormatEx(_err_Illegal_Value, "wValue", wValue, 0 ) , 1 );

        AddWIndexCell( Format("For Port # %i", wIndex), "Hub Port Number for this Request" );
        
        if ( wLength % 4 == 0 )
            AddWLengthCell( Format("%d data objects", wLength / 4), 0 );
        else
            AddWLengthCell( "Invalid data length. Expected multiples of 4" , 1 );
        
        if ( wLength / 4 > 0 )
        {
            curr_offset = 8;
            DecodeSrcCapDataObjects( curr_offset );
        }
    }
    else
    {
        AddPayLoadCell("Invalid bReqType value",   Format("0x%02X", bReqType),   "Expected 0x23 only",  ErrorColor);
    }
}
PD_SET_PDO_text()
{}

PD_GET_VDM()
{
    if ( bReqType == 0xA3 )
    {
        out.Decoded = 8 + wLength;
        
        if ( wValue == 0 )
            AddWValueCell("", "Correct Value of 0", 0 );
        else
            AddWValueCell("", FormatEx(_err_Illegal_Value, "wValue", wValue, 0 ) , 1 );

        AddWIndexCell( Format("For Port # %i", wIndex), "Hub Port Number for this Request" );
        
        if ( wLength == 0 )
            AddWLengthCell( "No data object", 0 );
        else if ( wLength % 4 == 0 )
            AddWLengthCell( Format("%d data objects", wLength / 4), 0 );
        else
            AddWLengthCell( "Invalid data length. Expected multiples of 4" , 1 );
        
        if ( wLength / 4 > 0 )
        {
            curr_offset = 8;            
            DecodeVDMDataObjects( curr_offset );
        }
    }
    else
    {
        AddPayLoadCell("Invalid bReqType value",   Format("0x%02X", bReqType),   "Expected 0xA3 only",  ErrorColor);
    }
}
PD_GET_VDM_text()
{}

PD_SEND_VDM()
{
        if ( bReqType == 0x23 )
    {
        out.Decoded = 8 + wLength;
        
        if ( wValue == 0 )
            AddWValueCell("SOP", "VDM send to Port Partner", 0 );
        else if ( wValue == 1 )
            AddWValueCell("SOP'", "VDM send to Cable's SOP Prime entity", 0 );
        else if ( wValue == 2 )
            AddWValueCell("SOP''", "VDM send to Cable's SOP Double Prime entity", 0 );
        else
            AddWValueCell("", FormatEx(_err_Illegal_Value, "wValue", wValue, 0 ) , 1 );

        AddWIndexCell( Format("For Port # %i", wIndex), "Hub Port Number for this Request" );
        
        if ( wLength == 0 )
            AddWLengthCell( "No data object", 1 );
        else if ( wLength % 4 == 0 )
            AddWLengthCell( Format("%d data objects", wLength / 4), 0 );
        else
            AddWLengthCell( "Invalid data length. Expected multiples of 4" , 1 );
        
        if ( wLength / 4 > 0 )
        {
            curr_offset = 8;            
            DecodeVDMDataObjects( curr_offset, obj_cnt );
        }
    }
    else
    {
        AddPayLoadCell("Invalid bReqType value",   Format("0x%02X", bReqType),   "Expected 0x23 only",  ErrorColor);
    }
}
PD_SEND_VDM_text()
{}

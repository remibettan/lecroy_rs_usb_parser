#*******************************************************************************
#
#  FILENAME: HIDCommon.inc
#
#  Copyright (c) 2016, Teledyne LeCroy - All Rights Reserved
#
#  DESCRIPTION
#    This file contains common functions that are used in HID decoder files.
#
#  FILE HISTORY:
#         June 2016 Created - SM
#         Dec  2016 Edited  - FJ
#
#*******************************************************************************

%include "CATCScriptAPI.inc"      
%include "USBCommon.inc"          #include useful decoder functions

set DECODE_ABORTED_OFFSET = 0;
set DECODE_ABORTED_FLAG = 0;

set HIDCaptionColor            = RGB(119, 87, 65);
set HIDCellColor               = RGB(216, 158, 119);

AddHIDField(offset, len, bit_offset, bit_len, name, tooltip, cellcolor, is_array_field, usage_page)
{
    # Set to 1 if field is added successfully.
    ReturnValues[0] = 0; 
    # Field value if field is added successfully.
    ReturnValues[1] = 0;
    value_format = "";
   
    if( DECODE_ABORTED_FLAG && offset >= DECODE_ABORTED_OFFSET )
    {
        return ReturnValues;
    }
    
    byte_offset_for_decoding =  offset + len + (bit_len/8);    
    if(bit_len % 8 != 0)
        byte_offset_for_decoding++;
    
    if( byte_offset_for_decoding  > in.DataLength )
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
        value_format = "0x%02X";
    }
    else if(len == 2)
    {        
        value = GetDataWord(offset);
        value_format = "0x%04X";
    }
    else if(len == 3)        
    {
        value = GetData3Bytes(offset);
        value_format = "0x%06X";
    }    
    else if(len == 4)        
    {
        value = GetDataLong(offset);        
        value_format = "0x%08X";
    }
    else if(bit_len > 0)
    {           
        if(bit_len == 1)
        {            
            value_format = "%d";
            byte_value = GetDataByte(offset);        
            value = (byte_value >> bit_offset) & (0x01);            
        }
        else
        {
            hex_digit_count = bit_len / 4;
            if(bit_len % 4)
                hex_digit_count ++;        
            value_format = "0x%0" + hex_digit_count + "X";
                                                
            value = 0;
            last_bit_len_in_byte = 0;            
            while(bit_len > 0)
            {                
                bit_len_in_byte = bit_len;
                if((bit_len + bit_offset) > 8)            
                    bit_len_in_byte = 8 - bit_offset;
                byte_value = GetDataByte(offset);        
                value =  (((byte_value >> bit_offset) & MakeBitMask(bit_len_in_byte)) << last_bit_len_in_byte) | value;                                
                
                bit_len = bit_len - bit_len_in_byte;
                last_bit_len_in_byte = bit_len_in_byte;
                bit_offset = 0;
                offset++;
            }
        }
    }
    else
    {        
		value = GetDataByteArray(offset, len);
        value = GetArrayHexStringEx(value, 1);
        value_format = "%s";
    }
        
    ReturnValues[0] = 1;        
    ReturnValues[1] = value;
        
	SetCellColor(cellcolor);
    
    if(usage_page && is_array_field)#This helps to show value interpretation in Usage page instead of raw value, like ASCII codes in keyboard
    {        
        _row = Find(HIDUsageTable, UsagePageId);
        ReportData = value;
        value_usage_decr = Call (_row[2]);
        tooltip = tooltip + ": " + value_usage_decr + "\nValue: " + Format(value_format, value);
        AddPayLoadCell(name, value_usage_decr, tooltip);
    }
	else
    {    
        AddPayLoadCell(name, Format(value_format, value), tooltip);
    }
    
    return ReturnValues;
}

MakeBitMask(len)
{
    mask = 0;
    for(i=0; i < len; i++)
        mask = (mask << 1) | 1;
    return mask;
}
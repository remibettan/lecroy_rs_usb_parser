#*******************************************************************************
#*
#*  FILENAME: TypeC_Common.inc
#*
#*  Copyright (C) 2016 Teledyn LeCroy
#*
#*  DESCRIPTION
#*    Common Functions for TypeC Bridge device decodings.
#*******************************************************************************

#####################################################################################################
# Common Functions
#####################################################################################################
set DECODE_ABORTED_FLAG = 0;
set Last_TypeC_PPM_Command = 0; #A communication way for Requests and Notifications to help Notification decoding on command specifics


################################################################
## Colors:
const BRIDGE_CAPABILITY_COLOR               = [175, 215, 197];
const SEND_PD_DATA_COLOR                    = [56, 146, 146];
const GET_PD_DATA_COLOR                     = [26, 100, 248];
const BB_NOTIFICATION_COLOR                 = [222, 89, 180];
const PPM_RESERVED_COLOR                    = [0, 0, 0];
const PPM_PPM_RESET_COLOR                   = [198, 1, 109];
const PPM_CANCEL_COLOR                      = [174, 25, 76];
const PPM_CONNECTOR_RESET_COLOR             = [192, 7, 191];
const PPM_ACK_PCR_PAN_COLOR                 = [161, 189, 120];
const PPM_SET_NOTIFICATION_ENABLE_COLOR     = [222, 51, 74];
const PPM_GET_CAPABILITY_COLOR              = [184, 249, 100];
const PPM_GET_CONNECTOR_CAPABILITY_COLOR    = [154, 246, 36];
const PPM_GET_CONNECTOR_STATUS_COLOR        = [121, 116, 214];
const PPM_GET_ERROR_STATUS_COLOR            = [155, 0, 0];
const PPM_NOTIFICATION_COLOR                = [87, 231, 239];
const PD_NOTIFICATION_COLOR                 = [111, 199, 199];
################################################################

#####################################################################################################
# FieldsArray contains a list of these values in each row:
#   * Field ID            : Field unique Id 
#   * Offset              : Field offset in bits
#   * Size                : Field size in bits
#   * Mask 	              : Field mask that can be used for masking some bits of value
#   * Field Name          : Field name that is shown in packet viewer
#   * Value Format        : This format is used in Format() method to convert field's value to string
#   * Value Substitute    : This array can define substitute for each field value. for example when we want to show meaningful name for numeric values
#   * Is Value Bitmap     : Specifies if value is a bitmap or not. 
#   * Tooltip             : Field tooltip that is shown in packet viewer
#####################################################################################################

MakeBitMask(len)
{
    mask = 0;
    for(i=0; i < len; i++)
        mask = (mask << 1) | 1;
    return mask;
}

AddTypeCField(FieldId, offset, FieldsArray, NameFormatExtra)
{
    if( DECODE_ABORTED_FLAG )
        return 0;
        
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
    
    if( offset + len > in.DataLength * 8 )
    {
        DECODE_ABORTED_FLAG = 1;

        AddSeparator();
        AddCell("DECODE ABORTED", "NOT ENOUGH DATA", "", WarningColor, _ERROR); 
        AddSeparator();
        return 0;
    }	
	
	byte_offset = offset / 8;
	bit_offset = offset % 8;
	bit_len = len;
	if(bit_len == 1)
	{            
		value_format = "%d";
		byte_value = GetDataByte(byte_offset);        
		value = (byte_value >> bit_offset) & (0x01);            
		
		tooltip += Format("\n\n%s: ", name);
		tooltip += Format(value_format, value);
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
			byte_value = GetDataByte(byte_offset);        
			value =  (((byte_value >> bit_offset) & MakeBitMask(bit_len_in_byte)) << last_bit_len_in_byte) | value;                                
			
			bit_len = bit_len - bit_len_in_byte;
			last_bit_len_in_byte = bit_len_in_byte;
			bit_offset = 0;
			byte_offset++;
		}
		
		if(valuearray != null)
		{
			if( isvaluebitmap == 1 )
			{
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
			value_format = "%s";			
		}
		else
		{
			if(valueformat == "%d")
				value_format = valueformat;
			
			tooltip += Format("\n\n%s: ", name);
			tooltip += Format(value_format, value);
		}
	}	
		
	SetCellColor(FieldColor);
	#Todo: we have problem showing bitmap values in HTML view, for now just show in cells in view
	#SetFieldOffsetLen(offset + len, len);			
    #AddPayLoadCell(name, Format(value_format, value), tooltip);  
	AddCell(name, Format(value_format, value), tooltip, FieldColor);  
    
    return 1;
}

## Return Field value from in.Data
GetTypeCFieldValue( FieldId, FieldsArray, data_offset )
{
    _row = Find(FieldsArray, FieldId);
    val = GetNBits(in.Data, data_offset + _row[1], _row[2]);
    return val;
}

#####################################################################################################
# FieldsArray contains a list of these values in each row:
#   * value         : value that matches this
#   * Text          : Text to use in the cell
#   * Tooltip       : Tooltip to use in the cell
#####################################################################################################
AddSelectCell(caption, value, FieldsArray)
{
    _row = Find(FieldsArray, value);

    text = _row[1];
    tooltip = _row[2];

    AddPayLoadCell(caption, text, tooltip, FieldColor);
}

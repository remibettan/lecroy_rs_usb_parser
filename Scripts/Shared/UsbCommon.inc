#
#  Copyright (c) 2003, Computer Access Technology Corp. - All Rights Reserved
#
#  UsbCommon.inc
#
#  common USB commands/events definitions
#

%include "UsbTabularCellId.inc"

#Reserved Variable Names
#define SD_DECODE_TYPE                  "UsbDecodeType"
#define SD_REQUEST_TYPE                 "UsbReqType"
#define SD_ENDPOINT_TYPE                "UsbEndpType"
#define SD_ENDPOINT_DIR                 "UsbEndpDir"
#define SD_MAX_PACKET_SIZE              "UsbMaxPktSize"
#define SD_MAX_TRANSFER_SIZE            "UsbMaxXferSize"
#define SD_MAX_TRANSFER_DECODE_SIZE     "UsbMaxXferDecodeSize"
#define SD_CLASS_CODE                   "UsbClassCode"
#define SD_SUB_CLASS                    "UsbSubClass"
#define SD_PROTOCOL                     "UsbProtocol"
#define SD_VENDOR_ID                    "UsbVendorId"
#define SD_PRODUCT_ID                   "UsbProductId"
#define SD_ENDPOINT_ID                  "UsbEndpId"
#define SD_IGNORE_SETUP_DATA            "UsbIgnoreSetupData"
#define SD_BYTES_ARE_LSB_TO_MSB         "UsbLsbToMsb"
#define SD_NUMBER_OF_DESCRIPTORS        "UsbNumDesc"
#define SD_REQUEST_STRING               "UsbReqStr"
#define SD_DESCRIPTOR_TOOLTIP_STRING    "UsbDescTooltipStr"
#define SD_DATA_DECODE_STRING           "UsbDataDecodeStr"
#define SD_DECODER_HEADER_TYPE          "UsbDecHdrType"
#define SD_DECODER_HEADER_LENGTH        "UsbDecHdrLen"
#define SD_DECODER_EXTRA_INFO_BYTE_POS  "UsbDecExtraInfoBytePos"
#define SD_SCRIPT_DECODER_TYPE          "UsbScriptDecodeType"
#define SD_SPEC_VERSION                 "UsbSpecVersion"
#define SD_UAS_PIPE_ID                  "UsbUASPipeId"

#Reserved Parameter Values
#define SD_DECODE_TYPE_REQUEST          "Request"
#define SD_DECODE_TYPE_ENDPOINT         "Endpoint"

#define SD_REQUEST_TYPE_CLASS           "Class"
#define SD_REQUEST_TYPE_VENDOR          "Vendor"

#define SD_ENDPOINT_TYPE_BULK           "Bulk"
#define SD_ENDPOINT_TYPE_INTERRUPT      "Interrupt"

#define SD_ENDPOINT_DIR_IN              "In"
#define SD_ENDPOINT_DIR_OUT             "Out"


# UsbXferCompleteClue definitions.   (For Bulk endpoints)
# These are used to help the online software do it's initial determination
# of how transfers are made up of transactions.  The default rule is:
# 1. Bulk Transfers end when a 0 or < Max packet length transaction is seen
# 2. Bulk Transfers end if there is a Max Packet Size transaction followed by empty frames
#
# These do not always work!
# So these "Clues" are provided to help.
# This is a bitmask:
#define SD_CLUE_XFER_EMPTY_FRAMES_ALLOWED      1 // Transfer not necessarily over when empty frame seen
#define SD_CLUE_XFER_ENDS_ON_NULL_OR_PARTIAL   2 // All transfers end with NULL or Partial block
#define SD_CLUE_XFER_ENDS_WHEN_OTHER_PIPE_SEEN 4 // If you see activity on the other direction pipe, end xfer
#define SD_CLUE_OTHER_XFER_ENDS_WHEN_THIS_SEEN 8 // If you see activity on this pipe, end xfer on other direction pipe
#
# Just provide a value obtained by "OR"ing them.
# Currently, the value of 1 is used in PTP decoding, 4 is used in Mass Storage SCSI Bulk Out,
# and 8 is used in Mass Storage SCSI Bulk In


# Byte offsets in in.DecodeParams
#define SD_DECODER_HEADER_TYPE_OPCODE_BYTE_0     0
#define SD_DECODER_HEADER_TYPE_OPCODE_BYTE_1     1
#define SD_DECODER_BRANCH_SPEED_BYTE             2


# This variable defines that the script which includes this file
# belongs to the USB script decoding family.
set ScriptFamily = "USB";

#These colors are maintained from the application so they will match
#the ones used by the older decoder script mechanism, and for requests
#which do not have a decoder script of any kind
extern bRequestColor;
extern wValueColor;
extern wIndexColor;
extern wLengthColor;
extern wDescriptorColor;

extern BranchSpeed;

#Flag to decide on speed mode, it should be replaced by a dynamic variable
const Low_Speed_Mode = 2;
const Full_Speed_Mode = 1;
const High_Speed_Mode = 0;
const Super_Speed_Mode = 4;
const Super_Speed_Plus_Mode = 5;
const SSIC_HS_Mode = 6;
const Undefined_Speed_Mode = 3;

set tempSpeedFlag = Undefined_Speed_Mode; #will be read in through the in.DecodeParams context



const REQ_DATA_OFFSET = 8 * 8; # Offset in bits of the Data after request.

set DecodeReqList = null;

set LittleEndian = 1;

set UsbReqStr = "";

set UsbDescTooltipStr = "";
# If  DescriptorTooltipTextString  above includes all of the decode, you dont have to
# bother with this next variable at all.  However, if the tooltip just contains
# the first portion of the decode, you should put the FULL decode in the following string
set UsbDataDecodeStr = "";

set UsbNumDesc = 0;
set DataByteHeaderOffset = 0;

const FIELD_WIDTH = 21;
set BuildString = "";

# 0 = \n,  1 = \r\n
set NewLineMode = 0;

set EmptyPrefixStr = "      |                     |        |";


set EntryBaseOffset    = 0;
set EntryFieldGroupLen = 0;
set EntryFieldOffset   = 0;
set EntryFieldLen      = 0;
set EntryFieldName     = "";
set EntryFieldStrVal   = "";
set EntryFieldDesc     = "";

set CurrentByteOffset = 0;


#
# WUSB PHY Rate bitmap table
#

set PHYRateBitmapTable =
[
   [ 0, "53.3 Mbs"  ],
   [ 1, "80 Mbs"    ],
   [ 2, "106.7 Mbs" ],
   [ 3, "160 Mbs"   ],
   [ 4, "200 Mbs"   ],
   [ 5, "320 Mbs"   ],
   [ 6, "400 Mbs"   ],
   [ 7, "480 Mbs"   ]
];




DescriptorDataInit()
{
    UsbDescTooltipStr = "";
    UsbDataDecodeStr = "";
    UsbReqStr = "";
    UsbNumDesc = 0;
}


ToBitDecode_old( table, value, prefix_string )
{
    str = "";
    i = 0;
    bit_val = 0;
    table_val = 0;
    while( table[i][0] != null )
    {
        table_val = (table[i][0]);
        bit_val = (value >> table_val) & 0x1;
#        Trace("Val:", value, " i:", i, " table_i:", (table[i][0]), " table_val:", table_val, " bit_val:", bit_val, "\n");
				str += NewLine();
        str += prefix_string;
        str += Format("Bit %2d: ", table[i][0]);
        str += Format("%s ",       table[i][1]);
        str += Format("%d",      bit_val);
        i = i + 1;
    }
#   Trace("ToBitDecode:", str, "\n");
    return str;
}

ToBitDecode_old_ex( table, value, prefix_string, title )
{
    str = "";
    i = 0;
    bit_val = 0;
    table_val = 0;
    while( table[i][0] != null )
    {
        table_val = (table[i][0]);
        bit_val = (value >> table_val) & 0x1;
#        Trace("Val:", value, " i:", i, " table_i:", (table[i][0]), " table_val:", table_val, " bit_val:", bit_val, "\n");

		str += "&nbsp;&nbsp;<b>";

        str += prefix_string;
        str += Format("Bit %2d: ", table[i][0]);
        str += "</b>";
        str += Format("%s = ",       table[i][1]);
        str += "<b>";
        str += Format("%d",      bit_val);
        str += "</b><br>";
        i = i + 1;
    }

    if( title != "" )
        title = "&nbsp;&nbsp" + title + "<br>";

    if( str != "" )
        str = "<html><br>" + title + "<br>" + str +  "</html>";

#   Trace("ToBitDecode:", str, "\n");
    return str;
}

##################################################
#        Request cell functions                  #
##################################################

set bReqType = 0;     #Declaring global variables
set bRequest = 0;
set wValue   = 0;
set wIndex   = 0;
set wLength  = 0;


AddReqTypeCell()
{
    SetFieldOffsetLen( 8, 8 );
    FieldColor = bReqTypeColor;
    AddPayLoadCell("bReqType",Format("0x%04X",bReqType),Format("bitmap with decimal value of %d",bReqType) + "\n\nCharacteristics of Request:\n   D7      Data xfer direction\n\t   0 = Host to Device\n\t   1=Device to host\n\n   D6..5   Type\n\t   0 = Standard\n\t   1 = Class\n\t   2 = Vendor\n\t   3 = Reserved\n\n   D4..0   Recipient\n\t   0 = Device\n\t   1 = Interface\n\t   2 = Endpoint\n\t   3 = Other\n\t   4..31 = Reserved\n");
}


AddGenReqTypeCell()
{
    SetFieldOffsetLen( 8, 8 );
    AddPayLoadCell( caption , text, tooltip, addparam, addparam1 );
}


AddRequestCell( req_text )
{
    SetFieldOffsetLen( 16, 8 );
    FieldColor = bRequestColor;
    AddPayLoadCell("bRequest", req_text, Format("bRequest HexVal: 0x%02X", bRequest), FieldColor, [_TABULARCELL, CELL_REQUEST, "TEXT"]);
}


AddGenWValueCell( caption , text, tooltip, addparam, addparam1 )
{
   SetFieldOffsetLen( 32, 16 );
   AddPayLoadCell( caption , text, tooltip, addparam, addparam1, [_TABULARCELL, CELL_WVALUE, "TEXT_CAPTION"] );
}


AddWValueCell( val_text, tooltip,isError )
{
    SetFieldOffsetLen( 32, 16 );


    if( val_text == null || val_text == "" )
        val_text = Format( "0x%04X", wValue );



    if (isError != 1)
       {
          AddPayLoadCell( "wValue", val_text, tooltip, FieldColor, [_TABULARCELL, CELL_WVALUE, "TEXT_CAPTION"]  );
       }
    else
       {
       	   SetCellColor(ERROR_COLOR);
           AddCell("wValue*",val_text, tooltip,wValueColor,_ERROR, [_TABULARCELL, CELL_WVALUE, "TEXT_CAPTION"]);
           if( in.PrepareFldsForDlg )
               PrepareFieldForDlg("wValue*" , val_text,"<font Color = \"ORANGE\">" +  tooltip+"</font>", addparam, VS[COLLAPSED] );
           RestoreCellColor();
       }

}

AddGenWIndexCell( caption , text, tooltip, addparam, addparam1 )
{
   SetFieldOffsetLen( 48, 16 );
   AddPayLoadCell( caption , text, tooltip, addparam, addparam1 );
}



AddWIndexCell( idx_text, tooltip,isError )
{
    SetFieldOffsetLen( 48, 16 );

    if( idx_text == null || idx_text == "" )
        idx_text = Format( "0x%04X", wIndex );


    if (isError != 1)
       {
          AddPayLoadCell("wIndex", idx_text, tooltip);
       }
    else
       {
       	   SetCellColor(ERROR_COLOR);
           AddCell("wIndex*",idx_text, tooltip,wIndexColor,_ERROR);
           if( in.PrepareFldsForDlg )
               PrepareFieldForDlg("wIndex*" , idx_text,"<font Color = \"ORANGE\">" +  tooltip+"</font>", addparam, VS[COLLAPSED] );
           RestoreCellColor();
       }

}


AddWLengthCell( tooltip,isError )
{
    SetFieldOffsetLen( 64, 16 );

    if (isError != 1)
       {
          FieldColor = wLengthColor;
          AddPayLoadCell("wLength", Format( "%u", wLength ), tooltip );
       }
    else
       {
       	   SetCellColor(ERROR_COLOR);
           AddCell("wLength*",Format( "%u", wLength ), tooltip,wLengthColor,_ERROR);
           if( in.PrepareFldsForDlg )
               PrepareFieldForDlg("wLength*" , idx_text,"<font Color = \"ORANGE\">" +  tooltip+"</font>", addparam, VS[COLLAPSED] );
           RestoreCellColor();
       }


}


AddIllegalTypeCell( req_txt )
{
    if( !req_txt )
        req_txt = ""; # guarantees that we have a string

    FieldColor = ERROR_COLOR;
    SetFieldOffsetLen( 8, 8 );

    AddErrorMonoCell(req_txt, _err_IllegalTypeCell_Data, FormatEx(_err_IllegalTypeCell_ToolTip, bReqType, req_txt));
}




SetRequestDataOffset()
{
    SetFieldOffsetLen( 64, 0 );
}


##########################################################################
#              Common Descriptor decoding function                       #
##########################################################################

do_descriptor()
{
    valuecell_error = 0;
    descriptor_index =  wValue & 0xFF;
    descriptor_type  = (wValue >> 8) & 0xFF;

    _row_dt = FindDescriptorEntry( descriptor_type );


    dt_str = Format("Descriptor type 0x%02X", descriptor_type);
    di = "";

    index_str = Format ("0x%04X", wIndex);

    di = Format(", Index %d", descriptor_index);

    if( _row_dt[0] != 0xFF )
    {
        dt_str = _row_dt[1] + " type";

        if( _row_dt[3] != null ) # we have some string to add.
           dt_str += _row_dt[3];
    }

    if (descriptor_type)
    {
        if (descriptor_type == 0x03)
        {
            # This is a STRING descriptor.  In this case, the wIndex has the Language ID
            index_str = Format ("Language ID 0x%04X", wIndex);

            if (descriptor_index  == 0)
            {
                # special case for descriptor index zero: it requests a list of supported Language IDs

                dt_str = dt_str + ", LANGID codes requested";
                # valuecell_error = 1;

            }
            else
            {
                dt_str = dt_str + di;
            }
        }
        else if (descriptor_type == 0x02)
        {
            dt_str = dt_str + di;
        }
    }
    else
    {
         dt_str = dt_str + di;
    }


    if( _row_dt[0] != 0xFF )
    {
     AddWValueCell( dt_str,"Type of Descriptor " ,valuecell_error );
    }
    else
    {
     AddWValueCell( dt_str,_err_NotMatchingDescriptor,1  );
    }

    AddWIndexCell( index_str, "index info" );

    #--------------------- Descriptors ----------------------------
    SaveOffset();
    FieldColor = wDescriptorColor;
    InitText();
	#AddLineOfText("From do_descriptor()");
    DescriptorCellString = "N/A";
    UsbDescTooltipStr = DoStandardDescriptors(descriptor_type, 1);

    SetFieldOffsetLen( B_offset, GetBitOffset() - B_offset );

    # Use simple AddCell() function here because we don't want to send this cell
    # information to dialog view.
    # All the discriptors information for dialog view is provided
    # by DoStandardDescriptors() function.
    AddCell("Descriptors", DescriptorCellString, "");
}




#
# Let's not use the new ToBitDecode function until we replace the old Decode request dialog.
#

ToBitDecode( table, value, prefix_string, title )
{
    str = "<HTML>";

    if( title != null )
       str += "<b>" + title + "</b>";

    str += "<table cellspacing=0 cellpadding=1 border=1>";
    bit_val = 0;
    table_val = 0;

    str += "<tr><td><b>Bit</b></td><td><b>Name</b></td><td><b>Value</b></td></tr>";

    for( i = 0; table[i][0] != null; i++ )
    {
        str += "<tr>";

        table_val = ( table[i][0] );
        bit_val = (value >> table_val) & 0x1;

        str += FormatEx( "<td><font color=#0000FF>%sBit %2d</font></td>", prefix_string, table[i][0] );

        str += Format( "<td>%s</td>", table[i][1] );
        str += Format( "<td align=center>%d</td>", bit_val );

        str += "</tr>";
    }

    str += "</table></HTML>";

    return str;
}



ToBitString(value, number_of_bits)
{
    strTemp = "";
    for (i=0; i<number_of_bits;i++)
    {
        if (((value >> ((number_of_bits-1) - i)) & 0x1) == 1)
        {
            strTemp += "1";
        }
        else
        {
            strTemp += "0";
        }
    }
#    Trace("ToBitString:", value, "\n");
#    Trace("ToBitString:", value, str, "\n");
    return strTemp;
}


NewLine()
{
    if( in.PrepareFldsForDlg )
        return "<br>";


    if (NewLineMode == 0)
        return "\n";
    else
        return "\r\n";
}


AddDataHeader(decoder_name, length)
{
    if( in.PrepareFldsForDlg )
    {
        EntryBaseOffset += EntryFieldGroupLen;
        EntryFieldGroupLen  = 0;

        AddCaptionToDlg( decoder_name );
        return 0;
    }

    AddDataStageTitle(length);
    AddDash();
    AddDecoderTitle(decoder_name);
    AddBlankLine();
    AddColumnTitles();
    AddFieldBreak();
}

AddShortDataHeader(decoder_name)
{
    if( in.PrepareFldsForDlg )
    {
        EntryBaseOffset += EntryFieldGroupLen;
        EntryFieldGroupLen  = 0;

        AddCaptionToDlg( decoder_name );
        return 0;
    }


    AddBlankLine();
    AddDecoderTitle(decoder_name);
    AddBlankLine();
    AddColumnTitles();
    AddFieldBreak();
}


AddDataStageTitle(length)
{
    if( in.PrepareFldsForDlg )
        return 0;

    str = "";
    str = Format("  Data Stage (%d bytes) :", length);
    BuildString += str;
    BuildString += NewLine();
}


AddDash()
{
    if( in.PrepareFldsForDlg )
        return 0;

    BuildString += "------------------------------------";
    BuildString += NewLine();
}

AddLineOfText(text)
{
    if( in.PrepareFldsForDlg )
        return 0;

    BuildString += text;
    BuildString += NewLine();
}

AddDecoderTitle(decoder_name)
{
    if( in.PrepareFldsForDlg )
        return 0;

    BuildString += "   ";
    BuildString += decoder_name;
    BuildString += NewLine();
}

AddBlankLine()
{
    if( in.PrepareFldsForDlg )
        return 0;

    BuildString += NewLine();
}

AddFieldBreak()
{
    if( in.PrepareFldsForDlg )
    {
        AddViewFieldEntry( EntryFieldName, EntryFieldLen, EntryFieldOffset, EntryFieldStrVal,
               EntryFieldDesc, 1, FieldColor );

         return 0;
    }

    BuildString += "------|---------------------|--------|---------------------";
    BuildString += NewLine();
}

AddColumnTitles()
{
    if( in.PrepareFldsForDlg )
        return 0;

    BuildString += "Offset|        Field        | Value  |  Description";
    BuildString += NewLine();
}



AddEntry( offset, field_name, value, value_format, description, description_to_follow, decimal_format, custom_text )
{
    if( in.PrepareFldsForDlg )
    {
        if( field_name == "STRING" )
            field_name = " STRING ";

        EntryFieldOffset = EntryBaseOffset + offset *  8;
        EntryFieldLen    = value_format * 4; # value format contains the number of nibbles(4 bits) in the field.
        EntryFieldName   = field_name;

        if( custom_text )
        {
            EntryFieldStrVal = custom_text;
        }
        else
        {
            if( decimal_format )
                EntryFieldStrVal = Format( "%d", value );
            else
                EntryFieldStrVal = FormatHexVal(value, value_format);
        }

        EntryFieldDesc   = description;

        EntryFieldGroupLen += EntryFieldLen;
        return 0;
    }

    if (offset >= 0)
    {
        temp_str = Format(" %4d |", offset);
    }
    else
    {
        temp_str =        "     |";
    }
    BuildString += temp_str;

    if (field_name == "")
    {
        temp_str =        "                     |";
    }
    else
    {
        temp_str = "";
        str_length = sizeof(field_name);
        total_blanks = FIELD_WIDTH - str_length;
        blanks_before = total_blanks/2;
        extra_blank = total_blanks%2;
        blanks_after = blanks_before + extra_blank;
        j = 0;
        for (j=0; j<blanks_before; j++)
        {
            temp_str += " ";
        }

        temp_str += field_name;

        for (j=0; j<blanks_after; j++)
        {
            temp_str += " ";
        }
        temp_str += "|";
    }
    BuildString += temp_str;

    if( custom_text )
        temp_str = custom_text;
    else
    {
        if( decimal_format )
            temp_str = Format( "%d", value );
        else
            temp_str = FormatHexVal(value, value_format);
    }

    temp_str = temp_str +"|";

    BuildString += temp_str;

    if ( description_to_follow == 0)
    {
        BuildString += description;
        BuildString += NewLine();
    }

}

AddStringEntry( offset, len, field_name, value, description, description_to_follow)
{
    if( in.PrepareFldsForDlg )
    {
        if( field_name == "STRING" )
            field_name = " STRING ";

        EntryFieldOffset = EntryBaseOffset + offset * 8;
        EntryFieldLen    = len;
        EntryFieldName   = field_name;
        EntryFieldStrVal = value;
        EntryFieldDesc   = description;

        EntryFieldGroupLen += EntryFieldLen;
        return 0;
    }


    if (offset >= 0)
    {
        temp_str = Format(" %4d |", offset);
    }
    else
    {
        temp_str =        "     |";
    }
    BuildString += temp_str;

    if (field_name == "")
    {
        temp_str =        "                     |";
    }
    else
    {
        temp_str = "";
        str_length = sizeof(field_name);
        total_blanks = FIELD_WIDTH - str_length;
        blanks_before = total_blanks/2;
        extra_blank = total_blanks%2;
        blanks_after = blanks_before + extra_blank;
        j = 0;
        for (j=0; j<blanks_before; j++)
        {
            temp_str += " ";
        }

        temp_str += field_name;

        for (j=0; j<blanks_after; j++)
        {
            temp_str += " ";
        }
        temp_str += "|";
    }
    BuildString += temp_str;
    temp_str = "";
    str_length = sizeof(value);
    total_blanks = 8 - str_length;
    blanks_before = total_blanks/2;
    extra_blank = total_blanks%2;
    blanks_after = blanks_before + extra_blank;
    j = 0;
    for (j=0; j<blanks_before; j++)
    {
        temp_str += " ";
    }

    temp_str += value;

    for (j=0; j<blanks_after; j++)
    {
        temp_str += " ";
    }
    temp_str = temp_str + "|";

    BuildString += temp_str;

    if ( description_to_follow == 0)
    {
        BuildString += description;
        BuildString += NewLine();
    }

}

######################################################################
#            Some shortcut functions for adding "entries"            #
######################################################################

AddByteEntry( name, description, param, param1, reserved )
{
    val = GetDataByte( Base + CurrentByteOffset );

    if( param == null )
        param = 0;

    if( param1 == null )
        param1 = 0;

    if( reserved && val )
        description = "<font COLOR=#FF0000>!!! WARNING !!! " + description + "</font>";


    AddEntry( CurrentByteOffset, name, val, 2, description, param, param1 );
    AddFieldBreak();

    IncCurrByteOffset( 1 );
}


AddWordEntry( name, description, param, param1, reserved )
{
    val  = GetDataWord( Base + CurrentByteOffset );

    if( param == null )
        param = 0;

    if( param1 == null )
        param1 = 0;

    if( reserved && val )
        description = "<font COLOR=#FF0000>!!! WARNING !!! " + description + "</font>";


    AddEntry( CurrentByteOffset, name, val, 4, description, param, param1 );
    AddFieldBreak();

    IncCurrByteOffset( 2 );
}

Add2BytesEntry( name, description, param, param1, reserved )
{
		val = GetNBits(in.Data,((Base+CurrentByteOffset+DataByteHeaderOffset)*8), 16);
    SetFieldOffsetLen(((Base+CurrentByteOffset)*8) + 16, 16);

    if( param == null )
        param = 0;

    if( param1 == null )
        param1 = 0;

    if( reserved && val )
        description = "<font COLOR=#FF0000>!!! WARNING !!! " + description + "</font>";


    AddEntry( CurrentByteOffset, name, val, 4, description, param, param1 );
    AddFieldBreak();

    IncCurrByteOffset( 2 );
}

Add3BytesEntry( name, description, param, param1, reserved )
{
    val  = GetData3Bytes ( Base + CurrentByteOffset );

    if( param == null )
        param = 0;

    if( param1 == null )
        param1 = 0;

    if( reserved && val )
        description = "<font COLOR=#FF0000>!!! WARNING !!! " + description + "</font>";

    AddEntry( CurrentByteOffset, name, val, 6, description, param, param1 );
    AddFieldBreak();

    IncCurrByteOffset( 3 );
}

AddDwordEntry( name, description, param, param1, reserved )
{
    val  = GetDataLong ( Base + CurrentByteOffset );

    if( param == null )
        param = 0;

    if( param1 == null )
        param1 = 0;

    if( reserved && val )
        description = "<font COLOR=#FF0000>!!! WARNING !!! " + description + "</font>";

    AddEntry( CurrentByteOffset, name, val, 8, description, param, param1 );
    AddFieldBreak();

    IncCurrByteOffset( 4 );
}


IncCurrByteOffset( len )
{
    CurrentByteOffset += len;
    out.Decoded       += len;
}

############################################################################################


AddDescriptionOnly(description_part)
{
    if( in.PrepareFldsForDlg )
    {
        EntryFieldDesc += " " + description_part;
        return 0;
    }

    BuildString += EmptyPrefixStr;
    BuildString += description_part;
    BuildString += NewLine();
}

AddDescriptorSizeString(value)
{
    if( in.PrepareFldsForDlg )
    {
        EntryFieldDesc += Format( "Descriptor size is %d bytes", value );
        return 0;
    }

    temp_str = "Descriptor size";
    BuildString += temp_str;
    BuildString += NewLine();
    temp_str = Format("is %d bytes", value);
    AddDescriptionOnly( temp_str );
}

GetDescriptorTypeString(str)
{
    temp_str = "";
    temp_str = Format("%s Descriptor Type", str);
    return temp_str;
}

FormatHexVal(value, number_of_nibbles)
{
    hex_str = "";
    select
    {
        number_of_nibbles == 0: hex_str =        "        ";
        number_of_nibbles == 1: hex_str = Format("    0x%01X ", value);
        number_of_nibbles == 2: hex_str = Format("   0x%02X ", value);
        number_of_nibbles == 3: hex_str = Format("  0x%03X ", value);
        number_of_nibbles == 4: hex_str = Format(" 0x%04X ", value);
        number_of_nibbles == 5: hex_str = Format("0x%05X ", value);
        number_of_nibbles == 6: hex_str = Format("0x%06X", value);
        number_of_nibbles == 7: hex_str = Format(" %07X", value);
        number_of_nibbles == 8: hex_str = Format("%08X", value);
        default               : hex_str = Format("?<format error in script> 0x%08X ", value);
    };
    return hex_str;
}



DecodeRequestToTextCommon(request_table)
{
    DataByteHeaderOffset = 0;
    bReqType = GetDataByte(0);
    bRequest = GetDataByte(1);
    wValue   = GetDataWord(2);
    wIndex   = GetDataWord(4);
    wLength  = GetDataWord(6);

    st_bRequest = "";
    st_Direction = "";
    st_Recipient = "";
    st_RequestData = "";
    st_Type = "";
    st_wIndex = "";
    st_wLength = "";
    st_wValue = "";

    i = 0;
    st = "";
    DataSt = "";

    for( i=0; i<8; i++ )
    {
        st = Format( "%02X ", GetDataByte(i));
        st_RequestData = st_RequestData + st;
    }

    if (bReqType >> 7)
    {
        st_Direction = "Device-to-host";
    }
    else
    {
        st_Direction = "Host-to-device";
    }

    type = (bReqType >> 5) & 0x03;
    select
    {
        type == 0 : st_Type = "Standard";
        type == 1 : st_Type = "Class";
        type == 2 : st_Type = "Vendor";
        type == 3 : st_Type = "Reserved";
    };

    recipient = (bReqType) & 0x07;
    select
    {
        recipient == 0 : st_Recipient = "Device";
        recipient == 1 : st_Recipient = "Interface";
        recipient == 2 : st_Recipient = "Endpoint";
        recipient == 3 : st_Recipient = "Other";
        recipient == 4 : st_Recipient = "Port";
        recipient == 5 : st_Recipient = "RPipe";
        default        : st_Recipient = Format ("Reserved:0x%X", recipient);
    };

    _row = Find(request_table, bRequest);
    st_bRequest =     _row[1];


    st_wValue = Decode_wValue();
    if ((st_wValue == "") || (st_wValue == null))
    {
        st_wValue = Format ("0x%04X", wValue);
    }

    st_wIndex = Decode_wIndex();
    if ((st_wIndex == "") || (st_wIndex == null))
    {
        st_wIndex = Format ("0x%04X", wIndex);
    }

    st_wLength = Decode_wLength();
    if ((st_wLength == "") || (st_wLength == null))
    {
        st_wLength = Format ("0x%04X", wLength);
    }

    if( in.PrepareFldsForDlg )
    {
       DecodeReqList = [st_RequestData, st_Direction, st_Type, st_Recipient, st_bRequest, st_wValue, st_wIndex, st_wLength ];
       return BuildString;
    }


    BuildString = "Setup Data:  ";
    BuildString += st_RequestData;
    BuildString += NewLine();
    AddDash();
    BuildString += " Direction:  ";
    BuildString += st_Direction;
    BuildString += NewLine();
    BuildString += "      Type:  ";
    BuildString += st_Type;
    BuildString += NewLine();
    BuildString += " Recipient:  ";
    BuildString += st_Recipient;
    BuildString += NewLine();
    AddDash();
    BuildString += "  bRequest:  ";
    BuildString += st_bRequest;
    BuildString += NewLine();
    BuildString += NewLine();
    BuildString += "    wValue:  ";
    BuildString += st_wValue;
    BuildString += NewLine();
    BuildString += NewLine();
    BuildString += "    wIndex:  ";
    BuildString += st_wIndex;
    BuildString += NewLine();
    BuildString += NewLine();
    BuildString += "   wLength:  ";
    BuildString += st_wLength;

    return BuildString;
}

GetDataByte(index)
{

    val = GetNBits(in.Data, ((index+DataByteHeaderOffset)*8), 8);
    SetFieldOffsetLen((index*8) + 8, 8);
    return val;
}

GetDataWord(index)
{
	val = GetNBits(in.Data,((index+DataByteHeaderOffset)*8), 16);
    if (LittleEndian == 1)
    {
        val2 = ((val & 0xFF00) >> 8)  |
              ((val & 0x00FF) << 8);
    }
    else
    {
        val2 = val;
    }
    SetFieldOffsetLen((index*8) + 16, 16);
    return val2;
}

GetData3Bytes(index)
{
	val = GetNBits(in.Data,((index+DataByteHeaderOffset)*8), 24);
    if (LittleEndian == 1)
    {
        val2 = ((val & 0xFF0000) >> 16) |
        				  (val & 0x00FF00)        |
                 ((val & 0x0000FF) << 16);
    }
    else
    {
        val2 = val;
    }
    SetFieldOffsetLen((index*8) + 24, 24);
    return val2;
}

GetDataLong(index)
{
    if (LittleEndian == 1)
    {
	    val = GetNBits(in.Data, ((index+DataByteHeaderOffset)*8), 32);
	    val2 =
	    ((val >> 24) & 0xFF) |
	    ((val >> 8)  & 0xFF00) |
	    ((val << 8)  & 0xFF0000) |
	    ((val << 24) & 0xFF000000 );
    }
    else
    {
	    val2 = GetNBits(in.Data, ((index+DataByteHeaderOffset)*8), 32);
	}
    SetFieldOffsetLen((index*8) + 32, 32);
    #Trace (" index:", index, " val:", val, " val1:", val1, " val2:", val2, "\n");
    return val2;
}

GetDataByteArray(index, len)
{
	val = GetNBits(in.Data, (index+DataByteHeaderOffset)*8, len * 8);			
	SetFieldOffsetLen((index*8) + len *8, len *8);
	#Trace (" index:", index, " val:", val, "\n");
	return val;
}

GetArrayHexString( arrayvalues )
{
    value = "";    
    for( i = 0; i < sizeof( arrayvalues ); i++ )
    {
        value += Format("%02x",arrayvalues[i]);    
    }
                    
    return value;
}

GetArrayASCIIString( arrayvalues )
{
    value = "";    
    for( i = 0; i < sizeof( arrayvalues ); i++ )
    {
        value += Format("%c",arrayvalues[i]);    
    }
                    
    return value;
}

GetDecoderHeaderByte(index)
{
     return GetNBits(in.DecodeParams, (index    * 8), 8);
}

InitText()
{
    BuildString = "";
}

GetFinalText()
{
    return BuildString;
}

AddStringToText(str)
{
    BuildString+= str;
}


NextNBitsReOrder()
{
    val = NextNBits(8);
    return ( NibbleReOrder[val & 0xF] << 4) |
           ( NibbleReOrder[(val & 0xF0) >> 4]);
}

NextNBitsReOrderList(len)
{

    for (x=0; x < len; x++)
    {
        orig_val = NextNBits(8);
        val[x] = ( NibbleReOrder[orig_val & 0xF] << 4) |
                 ( NibbleReOrder[(orig_val & 0xF0) >> 4]);
    }

    return val;
}



DataBlockReOrder( len )
{
  select
  {
    len == 0 :  ;
    len == 1 :  AddDataCell( [ NextNBitsReOrder()] );
    len == 2 :  AddDataCell( [ NextNBitsReOrder(), NextNBitsReOrder()] );
    len == 3 :  AddDataCell( [ NextNBitsReOrder(), NextNBitsReOrder(), NextNBitsReOrder()] );
    len == 4 :  AddDataCell( [ NextNBitsReOrder(), NextNBitsReOrder(), NextNBitsReOrder(), NextNBitsReOrder()] );
    default  :  AddDataCell(   NextNBitsReOrderList(len) );
  };
#  if (len > 0) AddDataCell( NextNBitsReOrderList(len) );
}


/*
ShowDataBlockReOrder( len )
{
  DataBlockReOrder( len );
  out.Decoded = out.Decoded + len;
}
*/



###########################################################
#  This function is intended for presentation DataBlock   #
#  len - length of DataBlock,                             #
#                                                         #
#  no_cell - define that no Cells will be drawn.          #
#            (useful for View Settings)                   #
#                                                         #
#  show_in_collapsed - define that datablock is shown     #
#                      in collapsed state                 #
###########################################################

ShowDataBlockReOrder( len, no_cells, show_in_collapsed )
{
   # no need to do anything if len = 0 or len < 0
   if( !len )    return 0;
   if( len < 0 ) return 0;

  if( in.PrepareFldsForDlg )
  {
        lenbits = len * 8;
        BitCurrentFieldOffset = BitCurrentFieldOffset + lenbits;
        BitCurrentFieldLength = lenbits;


        str = Format("%d bytes", len);
        PrepareFieldForDlg( "DATA_BLOCK", str,
        "Data Block containing " + str, !no_cells, show_in_collapsed );

        NextNBitsReOrder( lenbits );
  }
  else
  {
        if( !no_cells )
            DataBlockReOrder( len );
        else
            NextNBitsReOrder( 8 * len );
  }

  out.Decoded += len;
}


###########################################################
# Show DataBlock using information about showing in       #
# collapsed or in expanded states contained in            #
# view_setting.                                           ##
###########################################################

ShowReDataBlockVS( len, view_setting )
{
     if( view_setting == null ) view_setting = VS;
     ShowDataBlockReOrder( len, !ShowItem( view_setting ), view_setting[COLLAPSED] );
}

CreateHTMLSpace(space_count)
{
    space = "";
    for(counter = 0 ; counter < space_count ; counter += 1)
        space += "&nbsp";
    
    return space;
}




CopyToOutDataReOrder( len )
{
  select
  {
    len == 0 :  ;
    len == 1 :  out.Data = [ NextNBitsReOrder() ];
    len == 2 :  out.Data = [ NextNBitsReOrder(), NextNBitsReOrder()];
    len == 3 :  out.Data = [ NextNBitsReOrder(), NextNBitsReOrder(), NextNBitsReOrder()];
    len == 4 :  out.Data = [ NextNBitsReOrder(), NextNBitsReOrder(), NextNBitsReOrder(), NextNBitsReOrder()];
    default  :  out.Data =   NextNBitsReOrderList(len);
  };
}

CopyAddToOutDataReOrder( len )
{
  select
  {
    len == 0 :  ;
    len == 1 :  out.Data += [ NextNBitsReOrder() ];
    len == 2 :  out.Data += [ NextNBitsReOrder(), NextNBitsReOrder()];
    len == 3 :  out.Data += [ NextNBitsReOrder(), NextNBitsReOrder(), NextNBitsReOrder()];
    len == 4 :  out.Data += [ NextNBitsReOrder(), NextNBitsReOrder(), NextNBitsReOrder(), NextNBitsReOrder()];
    default  :  out.Data +=   NextNBitsReOrderList(len);
  };
}

ReOrderByte(val)
{
    return ( NibbleReOrder[val & 0xF] << 4) |
           ( NibbleReOrder[(val & 0xF0) >> 4]);
}
set NibbleReOrder = [0, 0x8, 0x4, 0xC, 0x2, 0xA, 0x6, 0xE, 0x1, 0x9, 0x5, 0xD, 0x3, 0xB, 0x7, 0xF];


DoDefaultDecode()
{
    str = OutputType + Format (" decoder was not able to decode this item.");
    AddCell("bRequest", Format("0x%02X", bRequest), str, bRequestColor);
    AddCell("bReqType", Format("0x%02X", bReqType), str,  bRequestColor);
    AddCell("wValue",   Format("0x%04X", wValue),   str,  wValueColor);
    AddCell("wIndex",   Format("%d", wIndex),   str,  wIndexColor);
    AddCell("wLength",  Format("%d", wLength),  str,  wLengthColor);
}


#AddDecodedTextHeader()
#{
#    AddCaptionToDlg(OutputType, "", "");
#    AddCaptionToDlg("", "", "");
#    AddCaptionToDlg("Offset      Field          HexVal  Decoded", "", "");
#}

ObtainString(start_offset, length)
{
    done = 0;
    str = "";
    offset = 8;
    index = 0;
    val = 0;
    while ((done == 0) && (index < length))
    {
        val = GetDataByte(start_offset + index);
        if (val != 0)
        {
            str += Format("%c", val);
            index++;
        }
        else
        {
            done = 1;
        }
    }
    SetFieldOffsetLen((start_offset+length)*8, 8);
    return str;
}

ObtainUnicodeString(start_offset, length)
{
    done = 0;
    str = "";
    offset = 8;
    index = 0;
    val = 0;
    while ((done == 0) && (index < length))
    {
        val = GetDataByte(start_offset + index);
        if (val != null)
        {
            str += Format("%c", val);
            index++;
        }
        else
        {
            done = 1;
        }
    }
    SetFieldOffsetLen((start_offset+length)*8, 8);
    return str;
}

SetBranchSpeed()
{
    BranchSpeed = GetNBits( in.DecodeParams, 2*8, 8 );  # SD_DECODER_BRANCH_SPEED_BYTE = 2
}

InitType2Decoder()
{
    DataByteHeaderOffset = 0;
    out.Decoded = 0;

    FieldColor = SRP_DataColor;

    Global_BitField_offset = 0;

    BitCurrentFieldOffset  = 0;
    BitCurrentFieldLength  = 0;

    SetBranchSpeed();
    GetNBits( in.Data, 0, 0 );
}

EndOfRequest()
{
    AddCaptionToDlg("$@", "", "");
}

Get8BytesData()
{
    IncFieldOffset(64);
    val =  Format("0x%08X", NextNBits(32));
    val += Format("%08X" , NextNBits(32));
    return val;
}

Get16BytesData()
{
    IncFieldOffset(128);
    giid =  Format("0x%08X", NextNBits(32));
    giid += Format("%08X" , NextNBits(32));
    giid += Format("%08X" , NextNBits(32));
    giid += Format("%08X"  , NextNBits(32));
    return giid;
}

AddExtraBytesPayloadCell(diffBytes)
{

    if (diffBytes > 0)
    {
        str = "0x";
        for(i = 0; i < diffBytes; i++)
            str += Format("%02X", NextNBits(8));
        IncFieldOffset( diffBytes * 8);
        AddPayLoadCell("Undecoded Bytes", str, Format("%d extra Bytes that can not be decoded", diffBytes), _ERROR);
    }
}

ShowUndecodedBytes( len )
{
     vs = Resolve( Prefix + "_Undecoded_Bytes" );

     ShowDataBlockVS( len, vs );

}

NextDataWord_()
{
    val = NextNBits_(16);
    if (LittleEndian == 1)
    {
        result = ((val & 0xFF00) >> 8)  |
              ((val & 0x00FF) << 8);
    }
    else
    {
        result = val;
    }
    return result;
}

NextDataDWord_()
{
    val = NextNBits_(32);
    if (LittleEndian == 1)
    {

         result =
            ((val >> 24) & 0xFF) |
	    ((val >> 8)  & 0xFF00) |
	    ((val << 8)  & 0xFF0000) |
	    ((val << 24) & 0xFF000000 );
    }
    else
    {
         result = val;
    }

    return result;
}

NextData3Bytes_()
{
	val = NextNBits_(24);
    if (LittleEndian == 1)
    {
        result = ((val & 0xFF0000) >> 16) |
        				  (val & 0x00FF00)        |
                 ((val & 0x0000FF) << 16);
    }
    else
    {
        result = val;
    }
    return result;
}

AddNoEnoughDataCell()
{
    AddErrorMonoCell("Error", "Not enough data", "Not enough data to decode");
}

ObtainUnicodeNextString( length )
{
    done = 0;
    str = "";
    index = 0;
    val = 0;



    while ((done == 0) && (index < (length * 2)))
    {
        val = NextNBits(8);

        if (val != null)
        {
            str += Format("%c", val);
            index++;
        }
        else
        {
            done = 1;
        }
    }

    IncFieldOffset( length * 16 );
    return str;
}

Get8BytesValue()
{
    IncFieldOffset(64);
    if (LittleEndian == 1)
    {
        val = "";
        for (i = 0; i < 8; i++)
            val = Format("%02X", NextNBits(8)) + val;
        val = "0x" + val;
    }
    else
    {
        val =  Format("0x%08X", NextNBits(32));
        val += Format("%08X" , NextNBits(32));
    }
    return val;
}

Get16BytesValue()
{
    IncFieldOffset(128);
    if (LittleEndian == 1)
    {
        val = "";
        for (i = 0; i < 16; i++)
            val = Format("%02X", NextNBits(8)) + val;
        val = "0x" + val;
    }
    else
    {
        val =  Format("0x%08X", NextNBits(32));
        val += Format("%08X" , NextNBits(32));
        val += Format("%08X" , NextNBits(32));
        val += Format("%08X"  , NextNBits(32));
    }
    return val;
}


StartTable(title)
{
    str = "<HTML>";
	  if( title != null )
        str += "<b>" + title + "</b>";

    str += "<table cellspacing=0 cellpadding=1 border=1>";

    str += "<tr><td><b>Bit</b></td><td><b>Name</b></td><td><b>Value</b></td></tr>";

    return str;
}

AddTableRow(str, row_title, stIndex, EdIndex, row_desc)
{
    str += "<tr>";

	str += FormatEx( "<td><font color=#0000FF>Bit %d-%d</font></td>", stIndex, EdIndex );

    str += Format( "<td>%s</td>", row_title );

    str += Format( "<td>%s</td>", row_desc );
	
    str += "</tr>";

    return str;
}

ToBitDecodeByIndex( str, table, stIndex, EdIndex, value, prefix_string )
{
    bit_val = 0;
    table_val = 0;


    for( i = stIndex; table[i][0] != null && i<= EdIndex; i++ )
    {
        str += "<tr>";

        table_val = ( table[i][0] );
        bit_val = (value >> table_val) & 0x1;

        str += FormatEx( "<td><font color=#0000FF>%sBit %2d</font></td>", prefix_string, table[i][0] );

        str += Format( "<td>%s</td>", table[i][1] );
        str += Format( "<td align=center>%d</td>", bit_val );

        str += "</tr>";
    }

    return str;
}

ToBitsDecode( str, table, Index, IndexLength, value, prefix_string )
{

    bit_val = 0;
    table_val = 0;


    str += "<tr>";

        table_val = ( table[Index][0] );
        bit_val = (value >> table_val);

        str += FormatEx( "<td><font color=#0000FF>%s</font></td>", prefix_string );

        str += Format( "<td>%s</td>", table[Index][1] );
        str2 = ToBitString(bit_val,IndexLength);

        str += Format( "<td align=center>%s</td>", str2 );

    str += "</tr>";

    return str;
}

ToBitsDecodeStringValue( str, table, Index, IndexLength, value, prefix_string, value_string_table )
{

    bit_val = 0;
    table_val = 0;


    str += "<tr>";

        table_val = ( table[Index][0] );
        bit_val = (value >> table_val);

        str += FormatEx( "<td><font color=#0000FF>%s</font></td>", prefix_string );

        str += Format( "<td>%s</td>", table[Index][1] );

        total_value = (0x7FFFFFFF >> (31 - IndexLength)) & bit_val;
        
        str2 = Format( "%s", value_string_table[total_value][1] );
        str += Format( "<td align=center>%s</td>", str2 );

    str += "</tr>";

    return str;
}


EndTable(str)
{
	   str += "</table></HTML>";
	   return str ;
}

GetArrayHexStringEx( arrayvalues, is_digit )
{
    value = "";    
    
    if(is_digit)
    {
        value = "0x";
        for( i = sizeof( arrayvalues ); i >= 0 ; i-- )
        {
            value += Format("%02x",arrayvalues[i]);    
        }    
    }
    else
    {
        for( i = 0; i < sizeof( arrayvalues ); i++ )
        {
            value += Format("%02x",arrayvalues[i]);    
        }
    }                    
    
    return value;
}

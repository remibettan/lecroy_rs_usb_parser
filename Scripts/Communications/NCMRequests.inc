#*******************************************************************************
#  Copyright (c) 2013, LeCroy - All Rights Reserved
#
#  Network Control Model request decoder
#
#*******************************************************************************

#------------------------------------------------------------------------------------------
# type,     type name                                                    |
#------------------------------------------------------------------------------------------
set NCMRequestTypeTable = Map(
[   
	[0x80,      "GET_NTB_PARAMETERS"        ],
    [0x81,      "GET_NET_ADDRESS"           ],
    [0x82,      "SET_NET_ADDRESS"           ],
    [0x83,      "GET_NTB_FORMAT"            ],
    [0x84,      "SET_NTB_FORMAT"            ],
    [0x85,      "GET_NTB_INPUT_SIZE"        ],
    [0x86,      "SET_NTB_INPUT_SIZE"        ],
    [0x87,      "GET_MAX_DATAGRAM_SIZE"     ],
    [0x88,      "SET_MAX_DATAGRAM_SIZE"     ],
    [0x89,      "GET_CRC_MODE"              ],
    [0x8A,      "SET_CRC_MODE"              ]
] );


#*******************************************************************************
# GET_NTB_PARAMETERS :
#                 This request retrieves the parameters that describe NTBs for each direction.
#                 In response to this request, the function shall return these elements
#
# bmRequestType :
# bmRequestType : 0xA1
# bRequest      : 0x80
# wValue        : 0x0000
# wIndex        : Interface
# wLength       : Amount of data in bytes associated with this recipient
# Data          : NTB Parameter Structure
#*******************************************************************************
# start GET_NTB_PARAMETERS
GET_NTB_PARAMETERS()
{
    if (bRequest == 0x80)
    {
		# Just to force save current cell color. Below cells have own their colors.
		SetCellColor(0);
		
        wValue   = GetDataWord(2); # Now that Endian is set...
        wIndex   = GetDataWord(4);
        wLength  = GetDataWord(6);

        val_text =  Format("0x%04X", wValue);
        val_text_Tooltip =  Format("wValue HexVal: 0x%04X", wValue);
        AddWValueCell (val_text, val_text_Tooltip);

        wIndex_text =  Format("0x%04X", wIndex);
        wIndex_text_Tooltip =  Format("wIndex HexVal: 0x%04X", wIndex);
        AddWIndexCell (wIndex_text, wIndex_text_Tooltip);

        wLength_text =  Format("wLength HexVal: 0x%04X", wLength);
        wLength_text_Tooltip =  Format("wLength HexVal: 0x%04X", wLength);
        AddWLengthCell(wLength_text, wLength_text_Tooltip);

        GetNBits( in.Data, 0, 0 );

		RestoreCellColor();
		
        NTB_Parameter_Structure_ToolTip = NTB_Parameter_Structure();
        AddPayLoadCell("NTB_Parameter",   "Parameters",
                        NTB_Parameter_Structure_ToolTip, FieldColor);

        out.Decoded = in.DataLength;
    }
}
# end GET_NTB_PARAMETERS

#*******************************************************************************
# GET_NET_ADDRESS :
#                 This request returns the function’s current EUI-48 station address.
#
# bmRequestType : 0xA1
# bRequest      : 0x81
# wValue        : 0x0000
# wIndex        : Interface
# wLength       : Amount of data in bytes associated with this recipient
# Data          : The EUI-48 current address, in net-work byte order
#*******************************************************************************
# start GET_NET_ADDRESS
GET_NET_ADDRESS()
{
    if (bRequest == 0x81)
    {
		# Just to force save current cell color. Below cells have own their colors.
		SetCellColor(0);

        wValue   = GetDataWord(2); # Now that Endian is set...
        wIndex   = GetDataWord(4);
        wLength  = GetDataWord(6);

        val_text =  Format("0x%04X", wValue);
        val_text_Tooltip =  Format("wValue HexVal: 0x%04X", wValue);
        AddWValueCell (val_text, val_text_Tooltip);

        wIndex_text =  Format("0x%04X", wIndex);
        wIndex_text_Tooltip =  Format("wIndex HexVal: 0x%04X", wIndex);
        AddWIndexCell (wIndex_text, wIndex_text_Tooltip);

        wLength_text =  Format("wLength HexVal: 0x%04X", wLength);
        wLength_text_Tooltip =  Format("wLength HexVal: 0x%04X", wLength);
        AddWLengthCell(wLength_text, wLength_text_Tooltip);

        GetNBits( in.Data, 0, 0 );
        dummy = NextNBits(6*8);
        Len = NextNBits(8);
        dummy = NextNBits(8);
        i = 0;
        st = "";
        while (i < Len)
        {
            F1 = NextNBits(8);
            st += FormatEx("%02X", F1);
            st += " ";
            i += 1;
        }

        Current_Address_ToolTip = st;

		RestoreCellColor();
		
        AddPayLoadCell("Current_Address",  st,
            Format ("Current Net Address is = %s", Current_Address_ToolTip), FieldColor);
        out.Decoded = in.DataLength;
    }
}
# end GET_NET_ADDRESS

#*******************************************************************************
# SET_NET_ADDRESS :
#                 This request sets the function’s current EUI-48 station address.
#
# bmRequestType : 0x21
# bRequest      : 0x82
# wValue        : 0x0000
# wIndex        : Interface
# wLength       : Amount of data in bytes associated with this recipient
# Data          : The EUI-48 address, in network byte order
#*******************************************************************************
# start SET_NET_ADDRESS
SET_NET_ADDRESS()
{
    if (bRequest == 0x82)
    {
		# Just to force save current cell color. Below cells have own their colors.
		SetCellColor(0);
	
        wValue   = GetDataWord(2); # Now that Endian is set...
        wIndex   = GetDataWord(4);
        wLength  = GetDataWord(6);

        val_text =  Format("0x%04X", wValue);
        val_text_Tooltip =  Format("wValue HexVal: 0x%04X", wValue);
        AddWValueCell (val_text, val_text_Tooltip);

        wIndex_text =  Format("0x%04X", wIndex);
        wIndex_text_Tooltip =  Format("wIndex HexVal: 0x%04X", wIndex);
        AddWIndexCell (wIndex_text, wIndex_text_Tooltip);

        wLength_text =  Format("wLength HexVal: 0x%04X", wLength);
        wLength_text_Tooltip =  Format("wLength HexVal: 0x%04X", wLength);
        AddWLengthCell(wLength_text, wLength_text_Tooltip);

        GetNBits( in.Data, 0, 0 );
        dummy = NextNBits(6*8);
        Len = NextNBits(8);
        dummy = NextNBits(8);
        i = 0;
        st = "";
        while (i < Len)
        {
            F1 = NextNBits(8);
            st += FormatEx("%02X", F1);
            st += " ";
            i += 1;
        }

        Net_Address = st;

		RestoreCellColor();
		
        AddPayLoadCell("Net_Address",  st,
            Format ("Set Net Address to = %s", Net_Address), FieldColor);

        out.Decoded = in.DataLength;
    }
}
# end SET_NET_ADDRESS


#*******************************************************************************
# GET_NTB_FORMAT :
#                 This request returns the NTB data format currently being used by the function.
#
# bmRequestType : 0xA1
# bRequest      : 0x83
# wValue        : 0x0000
# wIndex        : Interface
# wLength       : Amount of data in bytes associated with this recipient
# Data          : The NTB format code (2 bytes, little-endian), as defined under wValue in SetNtbFormat
#*******************************************************************************
# start GET_NTB_FORMAT
GET_NTB_FORMAT()
{
    if (bRequest == 0x83)
    {
		# Just to force save current cell color. Below cells have own their colors.
		SetCellColor(0);
	
        wValue   = GetDataWord(2); # Now that Endian is set...
        wIndex   = GetDataWord(4);
        wLength  = GetDataWord(6);

        val_text =  Format("0x%04X", wValue);
        val_text_Tooltip =  Format("wValue HexVal: 0x%04X", wValue);
        AddWValueCell (val_text, val_text_Tooltip);

        wIndex_text =  Format("0x%04X", wIndex);
        wIndex_text_Tooltip =  Format("wIndex HexVal: 0x%04X", wIndex);
        AddWIndexCell (wIndex_text, wIndex_text_Tooltip);

        wLength_text =  Format("wLength HexVal: 0x%04X", wLength);
        wLength_text_Tooltip =  Format("wLength HexVal: 0x%04X", wLength);
        AddWLengthCell(wLength_text, wLength_text_Tooltip);

        GetNBits( in.Data, 0, 0 );
        dummy = NextNBits(6*8);
        Len = NextNBits(8);
        dummy = NextNBits(8);

        NTB_Format_Code = NextNBits(Len*8);

		RestoreCellColor();
		
        AddPayLoadCell("NTB_Format_Code",   Format("0x%X", NTB_Format_Code),
            Format ("NTB Format Code is = 0x%X", NTB_Format_Code), FieldColor);
        out.Decoded = in.DataLength;
    }
}
# end GET_NTB_FORMAT

#*******************************************************************************
# SET_NTB_FORMAT :
#                 This request selects the format of NTB to be used for NTBs transmitted from the function to the host.
#
# bmRequestType : 0x21
# bRequest      : 0x84
# wValue        : 0x0000/0x0001
# wIndex        : Interface
# wLength       : Amount of data in bytes associated with this recipient
# Data          : None
#*******************************************************************************
# start SET_NTB_FORMAT
SET_NTB_FORMAT()
{
    if (bRequest == 0x84)
    {
        wValue   = GetDataWord(2); # Now that Endian is set...
        wIndex   = GetDataWord(4);
        wLength  = GetDataWord(6);

        val_text =  Format("0x%04X", wValue);
        val_text_Tooltip =  Format("wValue HexVal: 0x%04X", wValue);
        AddWValueCell (val_text, val_text_Tooltip);

        wIndex_text =  Format("0x%04X", wIndex);
        wIndex_text_Tooltip =  Format("wIndex HexVal: 0x%04X", wIndex);
        AddWIndexCell (wIndex_text, wIndex_text_Tooltip);

        wLength_text =  Format("wLength HexVal: 0x%04X", wLength);
        wLength_text_Tooltip =  Format("wLength HexVal: 0x%04X", wLength);
        AddWLengthCell(wLength_text, wLength_text_Tooltip);

        out.Decoded = in.DataLength;
    }
}
# end SET_NTB_FORMAT

#*******************************************************************************
# GET_NTB_INPUT_SIZE :
#                 This request returns NTB input size currently being used by the function.
#
# bmRequestType : 0xA1
# bRequest      : 0x85
# wValue        : 0x0000
# wIndex        : Interface
# wLength       : Amount of data in bytes associated with this recipient
# Data          : The NTB input size, as defined in SetNtbInputSize
#*******************************************************************************
# start GET_NTB_INPUT_SIZE
GET_NTB_INPUT_SIZE()
{
    if (bRequest == 0x85)
    {
		# Just to force save current cell color. Below cells have own their colors.
		SetCellColor(0);
	
        wValue   = GetDataWord(2); # Now that Endian is set...
        wIndex   = GetDataWord(4);
        wLength  = GetDataWord(6);

        val_text =  Format("0x%04X", wValue);
        val_text_Tooltip =  Format("wValue HexVal: 0x%04X", wValue);
        AddWValueCell (val_text, val_text_Tooltip);

        wIndex_text =  Format("0x%04X", wIndex);
        wIndex_text_Tooltip =  Format("wIndex HexVal: 0x%04X", wIndex);
        AddWIndexCell (wIndex_text, wIndex_text_Tooltip);

        wLength_text =  Format("wLength HexVal: 0x%04X", wLength);
        wLength_text_Tooltip =  Format("wLength HexVal: 0x%04X", wLength);
        AddWLengthCell(wLength_text, wLength_text_Tooltip);

        GetNBits( in.Data, 0, 0 );
        dummy = NextNBits(6*8);
        Len = NextNBits(8);
        dummy = NextNBits(8);
        Ntb_Input_Size = NextNBits(Len*8);

		RestoreCellColor();
		
        AddPayLoadCell("Ntb_Input_Size",   Format("0x%X", Ntb_Input_Size),
            Format ("Ntb Input Size is = 0x%X", Ntb_Input_Size), FieldColor);
        out.Decoded = in.DataLength;
    }
}
# end GET_NTB_INPUT_SIZE

#*******************************************************************************
# SET_NTB_INPUT_SIZE :
#                 This request selects the maximum size of NTB that the device is permitted to send to the host.
#
# bmRequestType : 0x21
# bRequest      : 0x86
# wValue        : 0x0000
# wIndex        : Interface
# wLength       : Amount of data in bytes associated with this recipient
# Data          : Maximum NTB size, in bytes, in little-endian order
#*******************************************************************************
# start SET_NTB_INPUT_SIZE
SET_NTB_INPUT_SIZE()
{
    if (bRequest == 0x86)
    {
		# Just to force save current cell color. Below cells have own their colors.
		SetCellColor(0);
	
        wValue   = GetDataWord(2); # Now that Endian is set...
        wIndex   = GetDataWord(4);
        wLength  = GetDataWord(6);

        val_text =  Format("0x%04X", wValue);
        val_text_Tooltip =  Format("wValue HexVal: 0x%04X", wValue);
        AddWValueCell (val_text, val_text_Tooltip);

        wIndex_text =  Format("0x%04X", wIndex);
        wIndex_text_Tooltip =  Format("wIndex HexVal: 0x%04X", wIndex);
        AddWIndexCell (wIndex_text, wIndex_text_Tooltip);

        wLength_text =  Format("wLength HexVal: 0x%04X", wLength);
        wLength_text_Tooltip =  Format("wLength HexVal: 0x%04X", wLength);
        AddWLengthCell(wLength_text, wLength_text_Tooltip);

        GetNBits( in.Data, 0, 0 );
        dummy = NextNBits(6*8);
        Len = NextNBits(8);
        dummy = NextNBits(8);
        Maximum_NTB_Size = NextNBits(Len*8);

		RestoreCellColor();
		
        AddPayLoadCell("Maximum_NTB_Size ",   Format("0x%04X", Maximum_NTB_Size),
            Format ("Set Maximum NTB Size to = 0x%04X", Maximum_NTB_Size), FieldColor);

        out.Decoded = in.DataLength;
    }
}
# end SET_NTB_INPUT_SIZE

#*******************************************************************************
# GET_MAX_DATAGRAM_SIZE :
#                 This request returns the currently effective maximum datagram size that the function has in effect.
#
# bmRequestType : 0xA1
# bRequest      : 0x87
# wValue        : 0x0000
# wIndex        : Interface
# wLength       : Amount of data in bytes associated with this recipient
# Data          : The current maximum datagram size, in little endian order (2 bytes).
#*******************************************************************************
# start GET_MAX_DATAGRAM_SIZE
GET_MAX_DATAGRAM_SIZE()
{
    if (bRequest == 0x87)
    {
		# Just to force save current cell color. Below cells have own their colors.
		SetCellColor(0);
	
        wValue   = GetDataWord(2); # Now that Endian is set...
        wIndex   = GetDataWord(4);
        wLength  = GetDataWord(6);

        val_text =  Format("0x%04X", wValue);
        val_text_Tooltip =  Format("wValue HexVal: 0x%04X", wValue);
        AddWValueCell (val_text, val_text_Tooltip);

        wIndex_text =  Format("0x%04X", wIndex);
        wIndex_text_Tooltip =  Format("wIndex HexVal: 0x%04X", wIndex);
        AddWIndexCell (wIndex_text, wIndex_text_Tooltip);

        wLength_text =  Format("wLength HexVal: 0x%04X", wLength);
        wLength_text_Tooltip =  Format("wLength HexVal: 0x%04X", wLength);
        AddWLengthCell(wLength_text, wLength_text_Tooltip);

        GetNBits( in.Data, 0, 0 );
        dummy = NextNBits(6*8);
        Len = NextNBits(8);
        dummy = NextNBits(8);
        Max_Datagram_Size = NextNBits(Len*8);

		RestoreCellColor();		
		
        AddPayLoadCell("Max_Datagram_Size",   Format("0x%X", Max_Datagram_Size),
            Format ("Max Datagram Size is = 0x%X", Max_Datagram_Size), FieldColor);
        out.Decoded = in.DataLength;
    }
}
# end GET_MAX_DATAGRAM_SIZE

#*******************************************************************************
# SET_MAX_DATAGRAM_SIZE :
#                 This request selects the maximum datagram size that either host or function will send in an NTB.
#
# bmRequestType : 0x21
# bRequest      : 0x88
# wValue        : 0x0000
# wIndex        : Interface
# wLength       : Amount of data in bytes associated with this recipient
# Data          : Maximum datagram size, in bytes, in little-endian order
#*******************************************************************************
# start SET_MAX_DATAGRAM_SIZE
SET_MAX_DATAGRAM_SIZE()
{
    if (bRequest == 0x88)
    {
		# Just to force save current cell color. Below cells have own their colors.
		SetCellColor(0);
	
        wValue   = GetDataWord(2); # Now that Endian is set...
        wIndex   = GetDataWord(4);
        wLength  = GetDataWord(6);

        val_text =  Format("0x%04X", wValue);
        val_text_Tooltip =  Format("wValue HexVal: 0x%04X", wValue);
        AddWValueCell (val_text, val_text_Tooltip);

        wIndex_text =  Format("0x%04X", wIndex);
        wIndex_text_Tooltip =  Format("wIndex HexVal: 0x%04X", wIndex);
        AddWIndexCell (wIndex_text, wIndex_text_Tooltip);

        wLength_text =  Format("wLength HexVal: 0x%04X", wLength);
        wLength_text_Tooltip =  Format("wLength HexVal: 0x%04X", wLength);
        AddWLengthCell(wLength_text, wLength_text_Tooltip);

        GetNBits( in.Data, 0, 0 );
        dummy = NextNBits(6*8);
        Len = NextNBits(8);
        dummy = NextNBits(8);
        Max_Datagram_Size = NextNBits(Len*8);

		RestoreCellColor();
		
        AddPayLoadCell("Max_Datagram_Size ",   Format("0x%02X", Max_Datagram_Size),
            Format ("Set Max Datagram Size to = 0x%02X", Max_Datagram_Size), FieldColor);

        out.Decoded = in.DataLength;
    }
}
# end SET_MAX_DATAGRAM_SIZE

#*******************************************************************************
# GET_CRC_MODE :
#                 This request returns the currently selected CRC mode for NTBs formatted by the function.
#
# bmRequestType : 0xA1
# bRequest      : 0x89
# wValue        : 0x0000
# wIndex        : Interface
# wLength       : Amount of data in bytes associated with this recipient
# Data          : The current CRC mode, in little en-dian order (2 bytes).
#*******************************************************************************
# start GET_CRC_MODE
GET_CRC_MODE()
{
    if (bRequest == 0x89)
    {
		# Just to force save current cell color. Below cells have own their colors.
		SetCellColor(0);
	
        wValue   = GetDataWord(2); # Now that Endian is set...
        wIndex   = GetDataWord(4);
        wLength  = GetDataWord(6);

        val_text =  Format("0x%04X", wValue);
        val_text_Tooltip =  Format("wValue HexVal: 0x%04X", wValue);
        AddWValueCell (val_text, val_text_Tooltip);

        wIndex_text =  Format("0x%04X", wIndex);
        wIndex_text_Tooltip =  Format("wIndex HexVal: 0x%04X", wIndex);
        AddWIndexCell (wIndex_text, wIndex_text_Tooltip);

        wLength_text =  Format("wLength HexVal: 0x%04X", wLength);
        wLength_text_Tooltip =  Format("wLength HexVal: 0x%04X", wLength);
        AddWLengthCell(wLength_text, wLength_text_Tooltip);

        GetNBits( in.Data, 0, 0 );
        dummy = NextNBits(6*8);
        Len = NextNBits(8);
        dummy = NextNBits(8);
        Crc_Mode = NextNBits(Len*8);

		RestoreCellColor();
		
        AddPayLoadCell("Crc_Mode",   Format("0x%X", Crc_Mode),
            Format ("Crc Mode is = 0x%X", Crc_Mode), FieldColor);
        out.Decoded = in.DataLength;
    }
}
# end GET_CRC_MODE

#*******************************************************************************
# SET_CRC_MODE :
#                 This request controls whether the function will append CRCs to
#                 datagrams when formatting NTBs to be sent to the host.
# bmRequestType : 0x21
# bRequest      : 0x8A
# wValue        : 0x0000/0x0001
# wIndex        : Interface
# wLength       : Amount of data in bytes associated with this recipient
# Data          : None
#*******************************************************************************
# start SET_CRC_MODE
SET_CRC_MODE()
{
    if (bRequest == 0x8A)
    {
        wValue   = GetDataWord(2); # Now that Endian is set...
        wIndex   = GetDataWord(4);
        wLength  = GetDataWord(6);

        val_text =  Format("0x%04X", wValue);
        val_text_Tooltip =  Format("wValue HexVal: 0x%04X", wValue);
        AddWValueCell (val_text, val_text_Tooltip);

        wIndex_text =  Format("0x%04X", wIndex);
        wIndex_text_Tooltip =  Format("wIndex HexVal: 0x%04X", wIndex);
        AddWIndexCell (wIndex_text, wIndex_text_Tooltip);

        wLength_text =  Format("wLength HexVal: 0x%04X", wLength);
        wLength_text_Tooltip =  Format("wLength HexVal: 0x%04X", wLength);
        AddWLengthCell(wLength_text, wLength_text_Tooltip);

        out.Decoded = in.DataLength;
    }
}
# end SET_CRC_MODE

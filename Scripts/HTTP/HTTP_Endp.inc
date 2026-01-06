
#
#  HTTP Class Out Endpoint Decoder
#

%include "HTTP_Common.inc"
%include "CATCScriptAPI.inc"
%include "UsbCommon.inc"



# Please see "View Settings" commnet in "CataLyst_Common.inc"
#					[collapsed, expanded]
const HTTP_Type		= [1, 1];

#-----------------------------------------------------------------------------

const Tabular_Def_Table = Map( 
[   
    #-----------------------------------------------------------------------------------------------------
    #       id                  ,      colId                          , 		containerCellId
    #-----------------------------------------------------------------------------------------------------
    [ CELL_HTTP_PROTOCOL        , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE    , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ CELL_HTTP_VERSION         , TABULAR_SCRIPT_COLUMN_ID_NONE       , TABULAR_SCRIPT_CONTAINER_CELL_ID_MISC ]

] );

ProcessData_HTTP()
{
    InitType2Decoder();
    Prefix =  "HTTP";

    length = in.DataLength;
    if (length < 4)
        return (0);


    # BitCurrentFieldOffset must be zero
	#AddPayLoadCell("BitCurrentFieldOffset", Format("0x%02X", BitCurrentFieldOffset), "For Debug", _ERROR);

    # signature = GetDataLong(0);
    # if (signature == HTTP_SIGNATURE )
        return HTTP_PayloadWrapper(length);
    # else
    #     return 0;
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# UDP Header
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set UDP_HeaderFields =
[
	#	FieldName				, Length,	Tooltip,	FieldDecodeTable, tabular info

	["Ethernet II"				, 0		], # <-- Header Field
	["Destination MAC Address"	, 48	],
	["Source MAC Address"		, 48	],
	["Type"						, 16	],

	["Internet Protocol (IP)"	, 0		], # <-- Header Field
	["VersionIHL"				, 8		, null , null, [_TABULARCELL, CELL_HTTP_VERSION, "TEXT_CAPTION" ]],
	["TOS"						, 8		, "Type of Service" ],
	["Total Length"				, 16	],
	["Identification"			, 16	],
	["Flags"					, 24	],
	["Fragment Offset"			, 104	],
	["TTL"						, 8		, "Time to Live" ],
	["Protocol"					, 8		, "This field specifies the next encapsulated protocol.", null, [_TABULARCELL, CELL_HTTP_PROTOCOL, "TEXT_CAPTION" ] ],
	["Header checksum"			, 16	],
	["Source IP Adddress"		, 32	],
	["Destination IP Address"	, 32	]
];



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ARP Header
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set ARP_HeaderFields =
[
	#	FieldName				, Length,	Tooltip,	FieldDecodeTable

	["Ethernet II"				, 0		], # <-- Header Field
	["Destination MAC Address"	, 48	],
	["Source MAC Address"		, 48	],
	["Type"						, 16	]
];



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# HTTP Header
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set HTTP_HeaderFields =
[
	#	FieldName				, Length,	Tooltip,	FieldDecodeTable

	["Ethernet II"				, 0		], # <-- Header Field
	["Destination MAC Address"	, 48	],
	["Source MAC Address"		, 48	],
	["Type"						, 16	],

	["Internet Protocol (IP)"	, 0		], # <-- Header Field
	["VersionIHL"				, 8		],
	["TOS"						, 8		, "Type of Service" ],
	["Total Length"				, 16	],
	["Identification"			, 16	],
	["Flags"					, 24	],
	["Fragment Offset"			, 104	],
	["TTL"						, 8		, "Time to Live" ],
	["Protocol"					, 8		, "This field specifies the next encapsulated protocol." ],
	["Header checksum"			, 16	],
	["Source IP Adddress"		, 32	],
	["Destination IP Address"	, 32	],

	["Transmission Control Protocol (TCP)", 0		], # <-- Header Field
	["Source Port"				, 16	],
	["Destination Port"			, 16	],
	["Sequence Number"			, 32	],
	["Acknowledgment Number"	, 32	],
	["DataOffset"				, 8		],
	["ECNControlBits"			, 8		],
	["Window"					, 16	],
	["Checksum"					, 16	]

];



HTTP_PayloadWrapper(length)
{

    AddDecSeparator();
    FieldColor = HTTP_CaptionColor;
    
    Trace("111111111111111111", "\n");
    AddCaptionCell("       HTTP     ", "Transmission Control Protocol", "This data payload represents a HTTP Payload.");

    FieldColor = HTTP_PayLoadColor;

	AddDecodedTextHeader();
	# AddDecSeparator();
	AddStringToDlg("Wrapped HTTP Payload", "", "");

	ShowArrowFields(UDP_HeaderFields);

    out.Decoded = in.DataLength;
}



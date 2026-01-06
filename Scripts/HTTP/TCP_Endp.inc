
#
#  TCP Class Endpoint Decoder
#

%include "HTTP_Common.inc"
%include "CATCScriptAPI.inc"
%include "UsbCommon.inc"


set TCP_SIGNATURE = 0x43425355;	# OK: 0x43425355
const TCP_CaptionColor   = 0x008080FF;
const TCP_PayloadColor  = 0x00009100; 

# Please see "View Settings" commnet in "CataLyst_Common.inc"
#					[collapsed, expanded]
const TCP_Sequence_Number	= [1, 1];

#-----------------------------------------------------------------------------

const Tabular_Def_Table = Map( 
[   
    #-----------------------------------------------------------------------------------------------------
    #       id                  ,      colId                          , 		containerCellId
    #-----------------------------------------------------------------------------------------------------
    [ CELL_TCP_SEQUENCE_NUMBER  , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE    , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ CELL_TCP_SORT_PORT        , TABULAR_SCRIPT_COLUMN_ID_NONE       , TABULAR_SCRIPT_CONTAINER_CELL_ID_MISC ]

] );


#~~~~ Parsing entry point ~~~~
ProcessData_TCP()
{
    InitType2Decoder();
    Prefix =  "TCP";   

    length = in.DataLength;
    if (length < 4)
        return (0); 
   
   
    # BitCurrentFieldOffset must be zero
	#AddPayLoadCell("BitCurrentFieldOffset", Format("0x%02X", BitCurrentFieldOffset), "For Debug", _ERROR);
   
    # signature = GetDataLong(0);
    # if (signature == TCP_SIGNATURE )
        return TCP_PayloadWrapper(length);
    # else
    #     return 0;
}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# TCP Header
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set TCP_HeaderFields =
[
	#	FieldName			, Length,	Tooltip,	FieldDecodeTable    , tabular info
	["Source Port"			, 16	, nuul, null, [_TABULARCELL, CELL_TCP_SORT_PORT, "TEXT_CAPTION" ] ],
	["Destination Port"		, 16	],
	["Sequence Number"		, 32    , null, null, [_TABULARCELL, CELL_TCP_SEQUENCE_NUMBER, "TEXT_CAPTION" ]	],
	["Acknowledgment Number", 32	],
	["Data Offset"			, 4		],
	["reserved"				, 4		],
	["ECN"					, 2		, "Explicit Congestion Notification"],
	["Control Bits"			, 6		],
	["Window"				, 16	],
	["Checksum"				, 16	],
	["Urgent Pointer"		, 16	]
];



TCP_PayloadWrapper(length)
{
       
    AddDecSeparator();
    FieldColor = TCP_CaptionColor;
    AddCaptionCell("       TCP     ", "Transmission Control Protocol", "This data payload represents a TCP Payload."); 
	 
    FieldColor = TCP_PayloadColor;
    
    AddDecodedTextHeader();
    # AddDecSeparator();
    AddStringToDlg("Wrapped TCP Payload", "", "");

	ShowArrowFields(TCP_HeaderFields);

    out.Decoded = in.DataLength;
}



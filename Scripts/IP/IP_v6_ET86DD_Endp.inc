
#
#  Internet Protocol v6 Class Out Endpoint
#

%include "IP_Common.inc"
%include "CATCScriptAPI.inc"
%include "UsbCommon.inc"


# Please see "View Settings" commnet in "CataLyst_Common.inc"
#					[collapsed, expanded]
const IP_Version		= [1, 1];

#-----------------------------------------------------------------------------

const Tabular_Def_Table = Map( 
[   
    #-----------------------------------------------------------------------------------------------------
    #       id                  ,      colId                          , 		containerCellId
    #-----------------------------------------------------------------------------------------------------
    [ CELL_IP_PROTOCOL          , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE    , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ CELL_IP_VERSION           , TABULAR_SCRIPT_COLUMN_ID_NONE       , TABULAR_SCRIPT_CONTAINER_CELL_ID_MISC ]

] );


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# IP Header
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set IPv6_HeaderFields =
[
	#	FieldName			, Length,	Tooltip,	FieldDecodeTable  , tabular info 
	["Version"				, 4     , null     , null                 , [_TABULARCELL, CELL_IP_VERSION, "TEXT_CAPTION" ]],
	["TrafficClass"			, 8		, "Internet traffic priority delivery value."],
	["FlowLabel"			, 20	],
	["Payload Length"		, 16	],
	["Next Header"			, 8		, "Specifies the next encapsulated protocol."],
	["Hop Limit"			, 8		],
	["Source address"		, 128	],
	["Destination address"	, 128	]
];


InternetProtocolPayloadWrapper()
{
    AddDecSeparator();
    FieldColor = IP_CaptionColor;
    AddCaptionCell("Internet Protocol", "IPv6_ET86DD", "This data payload represents a Internet Protocol Payload.");

	ShowArrowFields(IPv6_HeaderFields);

    out.Decoded = in.DataLength;
}

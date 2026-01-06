
#
#  ATAPI SSC2 (SCSI Stream Commands - 2) Class Out Endpoint
#


%include "CATCScriptAPI.inc"
%include "UsbCommon.inc"
%include "ATAPI_Common.inc"


# Please see "View Settings" commnet in "CataLyst_Common.inc"
#					[collapsed, expanded]
# const ATAPI_###filed_name###		= [1, 1];

#-----------------------------------------------------------------------------


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x19: SSC2- Erase (6)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set SSC2_Erase6Fields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "ERASE (6)"],
	["LONG"				, 1 ],
	["IMMED"			, 1 ],
	["Reserved"			, 6 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x1B: SSC2- Load Unload
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set SSC2_LoadUnloadFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "LOAD UNLOAD"],
	["IMMED"			, 1 ],
	["Reserved"			, 7 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["LOAD"				, 1 ],
	["RETEN"			, 1 ],
	["EOT"				, 1 ],
	["HOLD"				, 1 ],
	["Reserved"			, 4 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x2B: SSC2- Locate (10)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set SSC2_Locate10Fields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "LOCATE (10)"],
	["IMMED"			, 1 ],
	["CP"				, 1 ],
	["BT"				, 1 ],
	["Reserved"			, 5 ],
	["Reserved"			, 8 ],
	["LOGICAL OBJECT IDENTIFIER", 32 ],
	["Reserved"			, 8 ],
	["PARTITION"		, 8 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x08: SSC2- Read (6)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set SSC2_Read6Fields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "READ (6)"],
	["FIXED"			, 1 ],
	["SILI"				, 1 ],
	["Reserved"			, 6 ],
	["TRANSFER LENGTH"	, 24],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x05: SSC2- Read Block Limits
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set SSC2_ReadBlockLimitsFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "READ BLOCK LIMITS"],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x34: SSC2- Read Position
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set SSC2_ReadPositionFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "READ POSITION"],
	["SERVICE ACTION"	, 5 ],
	["Reserved"			, 3 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["ALLOCATION LENGTH", 16],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x44: SSC2- Report Density Support
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set SSC2_ReportDensitySupportFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "REPORT DENSITY SUPPORT"],
	["MEDIA"			, 1 ],
	["Reserved"			, 7 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["ALLOCATION LENGTH", 16],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x02: SSC2- Request Block Address
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set SSC2_RequestBlockAddressFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "REQUEST BLOCK ADDRESS"],
	["Reserved"			, 24],
	["ALLOCATION LENGTH", 8 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x01: SSC2- Rewind
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set SSC2_RewindFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "REWIND"],
	["IMMED"			, 1 ],
	["Reserved"			, 7 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x0C: SSC2- Seek Block
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set SSC2_SeekBlockFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "SEEK BLOCK"],
	["IMMED"			, 1 ],
	["Reserved"			, 7 ],
	["Logical Block Address", 24 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x11: SSC2- Space (6)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set SSC2_Space6Fields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "SPACE (6)"],
	["CODE"				, 4 ],
	["Reserved"			, 4 ],
	["COUNT"			, 24 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x13: SSC2- Verify (6)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set SSC2_Verify6Fields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "VERIFY (6)"],
	["FIXED"			, 1 ],
	["BYTCMP"			, 1 ],
	["IMMED"			, 1 ],
	["Reserved"			, 5 ],
	["VERIFICATION LENGTH", 24 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x0A: SSC2- Write (6)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set SSC2_Write6Fields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "WRITE (6)"],
	["FIXED"			, 1 ],
	["Reserved"			, 7 ],
	["TRANSFER LENGTH"	, 24],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x10: SSC2- Write Filemarks (6)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set SSC2_WriteFilemarks6Fields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "WRITE FILEMARKS (6)"],
	["IMMED"			, 1 ],
	["WSMK"				, 1 ],
	["Reserved"			, 6 ],
	["TRANSFER LENGTH"	, 24],
	["Control"			, 8 ]
];


# #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# # 0x: SSC2-
# #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# set SSC2_Fields =
# [
# 	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
# 	["Operation Code"	, 8, ""],
# 	["Reserved"			, 8 ],
# 	["Reserved"			, 8 ],
# 	["Reserved"			, 8 ],
# 	["Reserved"			, 8 ],
# 	["Reserved"			, 8 ],
# 	["Reserved"			, 8 ],
# 	["Reserved"			, 8 ],
# 	["Reserved"			, 8 ],
# 	["Reserved"			, 8 ],
# 	["Reserved"			, 8 ],
# 	["Reserved"			, 8 ],
# 	["Reserved"			, 8 ],
# 	["Control"			, 8 ]
# ];



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# SSC2 Command Table
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set ATAPI_SSC2_CommandsTable =
[
	[0xFF, NULL								],
	[0x19, SSC2_Erase6Fields				],
	[0x1B, SSC2_LoadUnloadFields			],
	[0x2B, SSC2_Locate10Fields				],
	[0x08, SSC2_Read6Fields					],
	[0x05, SSC2_ReadBlockLimitsFields		],
	[0x34, SSC2_ReadPositionFields			],
	[0x44, SSC2_ReportDensitySupportFields	],
	[0x02, SSC2_RequestBlockAddressFields	],
	[0x01, SSC2_RewindFields				],
	[0x0C, SSC2_SeekBlockFields				],
	[0x11, SSC2_Space6Fields				],
	[0x13, SSC2_Verify6Fields				],
	[0x0A, SSC2_Write6Fields				],
	[0x10, SSC2_WriteFilemarks6Fields		]
];



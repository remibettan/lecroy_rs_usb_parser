
#
#  ATAPI SPC3 (SCSI Primary Commands - 3) Class Out Endpoint
#


%include "CATCScriptAPI.inc"
%include "UsbCommon.inc"
%include "ATAPI_Common.inc"


# Please see "View Settings" commnet in "CataLyst_Common.inc"
#					[collapsed, expanded]
# const ATAPI_###filed_name###		= [1, 1];

#-----------------------------------------------------------------------------


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x12: SPC3- Inquiry
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set SPC3_InquiryFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "INQUIRY"],
	["EVPD"				, 1 ],
	["CMDDT"			, 1 ],
	["Reserved"			, 6 ],
	["PAGE OR OPERATION CODE", 8 ],
	["ALLOCATION LENGTH", 16],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x4C: SPC3- Log Select
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set SPC3_LogSelectFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "LOG SELECT"],
	["SP"				, 1 ],
	["PCR"				, 1 ],
	["Reserved"			, 6 ],
	["Reserved"			, 6 ],
	["PC"				, 2 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Parameter List Length", 16 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x4D: SPC3- Log Sense
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set SPC3_LogSenseFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "LOG SENSE"],
	["SP"				, 1 ],
	["PPC"				, 1 ],
	["Reserved"			, 6 ],
	["Page Code"		, 6 ],
	["PC"				, 2 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Parameter Pointer", 16],
	["Allocation Length", 16],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x15: SPC3- Mode Select (6)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set SPC3_ModeSelect6Fields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "MODE SELECT(6)"],
	["SP"				, 1 ],
	["Reserved"			, 3 ],
	["PF"				, 1 ],
	["Reserved"			, 3 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Parameter List Length", 8 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x55: SPC3- Mode Select (10)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set SPC3_ModeSelect10Fields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "MODE SELECT (10)"],
	["SP"				, 1 ],
	["Reserved"			, 3 ],
	["PF"				, 1 ],
	["Reserved"			, 3 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Parameter List Length", 16 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x1A: SPC3- Mode Sense (6)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set SPC3_ModeSense6Fields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "MODE SENSE (6)"],
	["Reserved"			, 3 ],
	["DBD"				, 1 ],
	["Reserved"			, 4 ],
	["Page Code"		, 6 ],
	["PC"				, 2 ],
	["Subpage Code"		, 8 ],
	["Allocation Length", 8 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x55: SPC3- Mode Sense (10)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set SPC3_ModeSense10Fields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "MODE SENSE (10)"],
	["SP"				, 1 ],
	["Reserved"			, 3 ],
	["PF"				, 1 ],
	["Reserved"			, 3 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Parameter List Length", 8 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x1E: SPC3- Prevent Allow Medium Removal
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set SPC3_PreventAllowMediumRemovalFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "PREVENT ALLOW MEDIUM REMOVAL"],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["PREVENT"			, 2 ],
	["Reserved"			, 6 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x3C: SPC3- ReadBuffer
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set SPC3_ReadBufferFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "READ BUFFER"],
	["MODE"				, 5 ],
	["Reserved"			, 3 ],
	["Buffer ID"		, 8 ],
	["Buffer Offset"	, 24],
	["Allocation Length", 24],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x1C: SPC3- Receive Diagnostic Results
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set SPC3_ReceiveDiagnosticResultsFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "RECEIVE DIAGNOSTIC RESULTS"],
	["Reserved"			, 1 ],
	["PCV"				, 7 ],
	["PAGE CODE"		, 8 ],
	["ALLOCATION LENGTH", 16],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x17: SPC3- Release Unit (6)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set SPC3_ReleaseUnit6Fields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "Release Unit (6)"],
	["Obsolete"			, 1 ],
	["Third Party Device ID", 3 ],
	["3RdPty"			, 1 ],
	["Reserved"			, 3 ],
	["Obsolete"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x57: SPC3- Release Unit (10)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set SPC3_ReleaseUnit10Fields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "Release Unit (10)"],
	["Obsolete"			, 1 ],
	["LongID"			, 1 ],
	["Reserved"			, 2 ],
	["3RdPty"			, 1 ],
	["Reserved"			, 3 ],
	["Obsolete"			, 8 ],
	["Third Party Device ID", 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Parameter List Length", 16 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x03: SPC3- Request Sense
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set SPC3_RequestSenseFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "Request Sense"],
	["DESC"				, 1 ],
	["Reserved"			, 7 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["ALLOCATION LENGTH", 8 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x16: SPC3- Reserve (Unit) (6)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set SPC3_ReserveUnit6Fields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "RESERVE (UNIT) (6)"],
	["Obsolete"			, 1 ],
	["Third Party Device ID", 3 ],
	["3RdPty"			, 1 ],
	["Reserved"			, 3 ],
	["Obsolete"			, 8 ],
	["Obsolete"			, 16],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x56: SPC3- Reserve (Unit) (10)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set SPC3_ReserveUnit10Fields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "RESERVE (UNIT) (10)"],
	["Obsolete"			, 1 ],
	["LongID"			, 1 ],
	["Reserved"			, 2 ],
	["3RdPty"			, 1 ],
	["Reserved"			, 3 ],
	["Obsolete"			, 8 ],
	["Third Party Device ID", 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Parameter List Length", 16 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x1D: SPC3- Send Diagnostic
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set SPC3_SendDiagnosticFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "SEND DIAGNOSTIC"],
	["UnitOffL"			, 1 ],
	["DevOffL"			, 1 ],
	["SelfTest"			, 1 ],
	["Reserved"			, 1 ],
	["PF"				, 1 ],
	["SELF-TEST CODE"	, 3 ],
	["Reserved"			, 8 ],
	["Parameter List Length", 16 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x00: SPC3- Test Unit Ready
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set SPC3_TestUnitReadyFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "TEST UNIT READY"],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x3B: SPC3- Write Buffer
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set SPC3_WriteBufferFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "WRITE BUFFER"],
	["Mode"				, 5 ],
	["Reserved"			, 3 ],
	["Buffer ID"		, 8 ],
	["Buffer Offset"	, 24],
	["Parameter List Length", 24 ],
	["Control"			, 8 ]
];


# #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# # 0x: SPC3-
# #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# set SPC3_Fields =
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
# SPC3 Command Table
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set ATAPI_SPC3_CommandsTable =
[
	[0xFF, NULL									],
	[0x00, SPC3_TestUnitReadyFields				], # OK: 0x00
	[0x12, SPC3_InquiryFields					],
	[0x4C, SPC3_LogSelectFields					],
	[0x4D, SPC3_LogSenseFields					],
	[0x15, SPC3_ModeSelect6Fields				],
	[0x55, SPC3_ModeSelect10Fields				],
	[0x1A, SPC3_ModeSense6Fields				],
	[0x55, SPC3_ModeSense10Fields				],
	[0x1E, SPC3_PreventAllowMediumRemovalFields	],
	[0x3C, SPC3_ReadBufferFields				],
	[0x1C, SPC3_ReceiveDiagnosticResultsFields	],
	[0x17, SPC3_ReleaseUnit6Fields				],
	[0x57, SPC3_ReleaseUnit10Fields				],
	[0x03, SPC3_RequestSenseFields				],
	[0x16, SPC3_ReserveUnit6Fields				],
	[0x56, SPC3_ReserveUnit10Fields				],
	[0x1D, SPC3_SendDiagnosticFields			],
	[0x3B, SPC3_WriteBufferFields				]
];



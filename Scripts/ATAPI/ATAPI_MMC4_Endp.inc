
#
#  ATAPI MMC4 (MultiMedia Commands 4) Class Out Endpoint
#

%include "CATCScriptAPI.inc"
%include "UsbCommon.inc"
%include "ATAPI_Common.inc"


# Please see "View Settings" commnet in "CataLyst_Common.inc"
#					[collapsed, expanded]
# const ATAPI_###filed_name###		= [1, 1];

#-----------------------------------------------------------------------------


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x00: MMC4- Test Unit Ready
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_TestUnitReadyFields =
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
# 0x5B: MMC4- Close Track-Session
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_CloseTrackSessionFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "CLOSE TRACK/SESSION"],
	["IMMED"			, 1 ],
	["Reserved"			, 7 ],
	["Close Function"	, 3 ],
	["Reserved"			, 5 ],
	["Reserved"			, 8 ],
	["Track Number"		,16 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x04: MMC4- Format Unit
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_FormatUnitFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "FORMAT UNIT"],
	["Format Code"		, 3 ],
	["CmpList"			, 1 ],
	["FmtData"			, 1 ],
	["Reserved"			, 3 ],
	["Reserved"			, 8 ],
	["Interleave Value"	,16 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0xA1: MMC4- Blank
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_BlankFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "BLANK"],
	["Blanking Type"	, 3 ],
	["Reserved"			, 1 ],
	["IMMED"			, 1 ],
	["Reserved"			, 3 ],
	["Start Address/Track Number",24 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x46: MMC4- Get Configuration
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_GetConfigurationFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "GET CONFIGURATION"],
	["RT"				, 2 ],
	["Reserved"			, 6 ],
	["Starting Feature Number", 16 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Allocation Length", 16],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x4A: MMC4- Get Event Status Notification
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_GetEventStatusNotificationFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "GET EVENT STATUS NOTIFICATION"],
	["Polled"			, 1 ],
	["Reserved"			, 7 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Notification Class Request", 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Allocation Length", 16],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x12: MMC4- Inquiry
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_InquiryFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "INQUIRY"],
	["EVPD"				, 1 ],
	["CmdDt"			, 1 ],
	["Reserved"			, 6 ],
	["Page or Operation Code", 8 ],
	["Reserved"			, 8 ],
	["Allocation Length", 8 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0xBD: MMC4- Mechanism Status
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_MechanismStatusFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "MECHANISM STATUS"],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Allocation Length", 16],
	["Reserved"			, 8 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x55: MMC4- Mode Select (10)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_ModeSelect10Fields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "MODE SELECT (10)"],
	["SP"				, 1 ],
	["Reserved"			, 3 ],
	["PF = 1"			, 1 ],
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
# 0x5A: MMC4- Mode Sense (10)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_ModeSense10Fields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "MODE SENSE (10)"],
	["Reserved"			, 3 ],
	["DBD"				, 1 ],
	["LLBAA"			, 1 ],
	["Reserved"			, 3 ],
	["Page Code"		, 6 ],
	["PC"				, 2 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Allocation Length", 16],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x4B: MMC4- Pause/Resume
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_PauseResumeFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "PAUSE/RESUME"],
	["Reserved"			, 5 ],
	["Reserved"			, 3 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Resume"			, 1 ],
	["Reserved"			, 7 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x45: MMC4- Play Audio (10)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_PlayAudio10Fields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "PLAY AUDIO (10)"],
	["RelADR"			, 1 ],
	["Reserved"			, 7 ],
	["Starting Logical Block Address", 32 ],
	["Reserved"			, 8 ],
	["Play Length"		, 16],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x47: MMC4- Play Audio MSF
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_PlayAudioMSFFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "PLAY AUDIO MSF"],
	["Reserved"			, 5 ],
	["Reserved"			, 3 ],
	["Reserved"			, 8 ],
	["Starting M Field"	, 8 ],
	["Starting S Field"	, 8 ],
	["Starting F Field"	, 8 ],
	["Starting M Field"	, 8 ],
	["Starting S Field"	, 8 ],
	["Starting F Field"	, 8 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x1E: MMC4- Prevent Allow Medium Removal
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_PreventAllowMediumRemovalFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "PREVENT ALLOW MEDIUM REMOVAL"],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Prevent"			, 1 ],
	["Persistent"		, 1 ],
	["Reserved"			, 6 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x28: MMC4- Read (10)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_Read10Fields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "READ (10)"],
	["RelAdr"			, 1 ],
	["Reserved"			, 2 ],
	["FUA"				, 1 ],
	["DPO"				, 1 ],
	["Reserved"			, 3 ],
	["Logical Block Address", 32 ],
	["Reserved"			, 8 ],
	["Transfer Length"	, 16],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0xA8: MMC4- Read (12)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_Read12Fields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "READ (12)"],
	["RELADR"			, 1 ],
	["Reserved"			, 2 ],
	["FUA"				, 1 ],
	["DPO"				, 1 ],
	["Reserved"			, 3 ],
	["Logical Block Address", 32 ],
	["Transfer Length"	, 32],
	["Reserved"			, 7 ],
	["Streaming"		, 1 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x5C: MMC4- Read Buffer Capacity
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_ReadBufferCapacityFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "READ BUFFER CAPACITY"],
	["BLOCK"			, 1 ],
	["Reserved"			, 4 ],
	["Reserved"			, 3 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Allocation Length", 16],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x3C: MMC4- Read Buffer
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_ReadBufferFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "READ BUFFER"],
	["Mode"				, 5 ],
	["Reserved"			, 3 ],
	["Buffer ID"		, 8 ],
	["Buffer Offset"	, 24],
	["Allocation Length", 24],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x25: MMC4- Read Capacity
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_ReadCapacityFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "READ CAPACITY"],
	["RelAdr=0"			, 1 ],
	["Reserved"			, 7 ],
	["Logical Block Address=0000 0000h", 32 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["PMI=0"			, 1 ],
	["Reserved"			, 7 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0xB9: MMC4- Read CD MSF
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_ReadCDMSFFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "READ CD MSF"],
	["Reserved"			, 1 ],
	["DAP"				, 1 ],
	["Expected Sector Type", 3 ],
	["Reserved"			, 3 ],
	["Reserved"			, 8 ],
	["Starting M Field"	, 8 ],
	["Starting S Field"	, 8 ],
	["Starting F Field"	, 8 ],
	["Starting M Field"	, 8 ],
	["Starting S Field"	, 8 ],
	["Starting F Field"	, 8 ],
	["Reserved"			, 1 ],
	["C2 Errors"		, 2 ],
	["EDC & ECC"		, 1 ],
	["User Data"		, 1 ],
	["Header Codes"		, 2 ],
	["SYNC"				, 1 ],
	["Sub-channel Selection Bits", 3 ],
	["Reserved"			, 5 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0xBE: MMC4- Read CD
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_ReadCDFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "READ CD"],
	["RelAdr"			, 1 ],
	["DAP"				, 1 ],
	["Expected Sector Type", 3 ],
	["Reserved"			, 3 ],
	["Starting Logical Block Address", 32 ],
	["Transfer Length"	, 24 ],
	["Reserved"			, 1 ],
	["C2 Error Information", 2 ],
	["EDC & ECC"		, 1 ],
	["User Data"		, 1 ],
	["Header Codes"		, 2 ],
	["SYNC"				, 1 ],
	["Sub-channel Selection Bits", 3 ],
	["Reserved"			, 5 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x51: MMC4- Read Disc Information
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_ReadDiscInformationFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "READ DISC INFORMATION"],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Allocation Length", 16],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0xAD: MMC4- Read DVD Structure
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_ReadDVDStructureFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "READ DVD STRUCTURE"],
	["Reserved"			, 8 ],
	["Address"			, 32],
	["Layer Number"		, 8 ],
	["Format"			, 8 ],
	["Allocation Length", 16],
	["Reserved"			, 6 ],
	["AGID"				, 2 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x23: MMC4- Read Format Capacities
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_ReadFormatCapacitiesFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "READ FORMAT CAPACITIES"],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Allocation Length", 16],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x42: MMC4- Read Sub-Channel
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_ReadSubChannelFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "READ SUB-CHANNEL"],
	["Reserved"			, 1 ],
	["TIME"				, 1 ],
	["Reserved"			, 6 ],
	["Reserved"			, 6 ],
	["SUBQ"				, 1 ],
	["Reserved"			, 1 ],
	["Sub-channel Parameter List", 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Track Number (Hex)",8 ],
	["Allocation Length", 16],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x43: MMC4- Read TOC/PMA/ATIP
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_ReadTOC_PMA_ATIPFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "READ TOC/PMA/ATIP"],
	["Reserved"			, 1 ],
	["TIME"				, 1 ],
	["Reserved"			, 6 ],
	["Format"			, 4 ],
	["Reserved"			, 4 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Track/Session Number", 8 ],
	["Allocation Length", 16],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x52: MMC4- Read Track Information
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_ReadTrackInformationFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "READ TRACK INFORMATION"],
	["Address/Number Type", 2 ],
	["Reserved"			, 6 ],
	["Logical Block Address/Track/Session Number", 32 ],
	["Reserved"			, 8 ],
	["Allocation Length", 8 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x58: MMC4- Repair Track
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_RepairTrackFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "REPAIR TRACK"],
	["IMMED"			, 1 ],
	["Reserved"			, 7 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Track Number"		, 16],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0xA4: MMC4- Report Key
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_ReportKeyFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "REPORT KEY"],
	["Reserved"			, 5 ],
	["Reserved"			, 3 ],
	["Reserved/Logical Block Address", 32 ],
	["Reserved"			, 8 ],
	["Key Class"		, 8 ],
	["Allocation Length", 16],
	["KEY Format"		, 6 ],
	["AGID"				, 2 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x03: MMC4- Request Sense
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_RequestSenseFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "REQUEST SENSE"],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Allocation Length", 8 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x53: MMC4- Reserve Track
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_ReserveTrackFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "Reserve Track"],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reservation Size"	, 32],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0xBA: MMC4- Scan
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_ScanFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "SCAN"],
	["RelAdr"			, 1 ],
	["Reserved"			, 3 ],
	["Direction"		, 1 ],
	["Reserved"			, 3 ],
	["Scan Starting Address", 32 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 6 ],
	["Type"				, 2 ],
	["Reserved"			, 8 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x2B: MMC4- Seek (10)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_Seek10Fields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "SEEK (10)"],
	["Reserved"			, 8 ],
	["Logical Block Address", 32 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0xBF: MMC4- Send DVD structure
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_SendDVDStructureFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "SEND DVD STRUCTURE"],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Format"			, 8 ],
	["Parameter List Length", 16 ],
	["Reserved"			, 8 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x5D: MMC4- Send Cue sheet
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_SendCueSheetFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "SEND CUE SHEET"],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Cue Sheet Size"	, 24],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0xA3: MMC4- Send Key
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_SendKeyFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "SEND KEY"],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Key Class"		, 8 ],
	["Parameter List Length", 16 ],
	["Key Format"		, 6 ],
	["AGID"				, 2 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x54: MMC4- Send OPC information
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_SendOpcInformationFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "SEND OPC INFORMATION"],
	["DoOpc"			, 1 ],
	["Reserved"			, 7 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Parameter List Length", 16 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0xBB: MMC4- Set CD Speed
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_SetCDSpeedFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "SET CD SPEED"],
	["Rotational Control", 2 ],
	["Reserved"			, 6 ],
	["Logical Unit Read Speed (Kbytes/sec)", 16 ],
	["Logical Unit Write Speed (Kbytes/sec)", 16 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0xA7: MMC4- Set Read Ahead
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_SetReadAheadFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "SET READ AHEAD"],
	["Reserved"			, 8 ],
	["Trigger Logical Block Address", 32 ],
	["Read Ahead Logical Block Address", 32 ],
	["Reserved"			, 8 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0xB6: MMC4- Set Streaming
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_SetStreamingFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "SET STREAMING"],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Parameter List Length", 16 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x1B: MMC4- Start Stop Unit
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_StartStopUnitFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "START STOP UNIT"],
	["IMMED"			, 1 ],
	["Reserved"			, 7 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Start"			, 1 ],
	["LoEj"				, 1 ],
	["Reserved"			, 2 ],
	["Power Conditions"	, 4 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x4E: MMC4- Stop Play/Scan
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_StopPlayScanFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "STOP PLAY/SCAN"],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Reserved"			, 8 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x35: MMC4- Synchronize Cache
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_SynchronizeCacheFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "SYNCHRONIZE CACHE"],
	["RelAdr"			, 1 ],
	["IMMED"			, 1 ],
	["Reserved"			, 6 ],
	["Logical Block Address", 32 ],
	["Reserved"			, 8 ],
	["Number of Blocks"	, 16],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x2F: MMC4- Verify (10)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_Verify10Fields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "VERIFY (10)"],
	["RelAdr"			, 1 ],
	["BytChk"			, 1 ],
	["Reserved"			, 2 ],
	["DPO"				, 1 ],
	["Reserved"			, 3 ],
	["Logical Block Address", 32 ],
	["Reserved"			, 7 ],
	["G3tout"			, 1 ],
	["Number of Blocks"	, 16],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x2A: MMC4- Write (10)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_Write10Fields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "WRITE (10)"],
	["RelAdr"			, 1 ],
	["Reserved"			, 2 ],
	["FUA"				, 1 ],
	["DPO"				, 1 ],
	["Reserved"			, 3 ],
	["Logical Block Address", 32 ],
	["Reserved"			, 8 ],
	["Transfer Length"	, 16],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0xAA: MMC4- Write (12)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_Write12Fields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "WRITE (12)"],
	["Reserved"			, 3 ],
	["FUA"				, 1 ],
	["Reserved"			, 4 ],
	["Logical Block Address", 32 ],
	["Transfer Length"	, 32 ],
	["Reserved"			, 7 ],
	["Streaming"		, 1 ],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x2E: MMC4- Write And Verify (10)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_WriteAndVerify10Fields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "WRITE AND VERIFY (10)"],
	["Reserved"			, 8 ],
	["Starting Logical Block Address", 32 ],
	["Reserved"			, 8 ],
	["Transfer Length"	, 16],
	["Control"			, 8 ]
];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 0x3B: MMC4- Write Buffer
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set MMC4_WriteBufferFields =
[
	#	FieldName		, Length,	Tooltip,	FieldDecodeTable
	["Operation Code"	, 8, "WRITE BUFFER"],
	["Mode"				, 3 ],
	["Reserved"			, 5 ],
	["Buffer ID"		, 8 ],
	["Buffer Offset"	, 24 ],
	["Parameter List Length", 24 ],
	["Control"			, 8 ]
];


# #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# # 0x: MMC4-
# #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# set MMC4_Fields =
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
# MMC4 Command Table
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set ATAPI_MMC4_CommandsTable =
[
	[0xFF, NULL										],
	[0x00, MMC4_TestUnitReadyFields					], # OK: 0x00
	[0xA1, MMC4_BlankFields							],
	[0x5B, MMC4_CloseTrackSessionFields				],
	[0x04, MMC4_FormatUnitFields					],
	[0x46, MMC4_GetConfigurationFields				],
	[0x4A, MMC4_GetEventStatusNotificationFields	],
	[0x12, MMC4_InquiryFields						],
	[0xBD, MMC4_MechanismStatusFields				],
	[0x55, MMC4_ModeSelect10Fields					],
	[0x5A, MMC4_ModeSense10Fields					],
	[0x4B, MMC4_PauseResumeFields					],
	[0x45, MMC4_PlayAudio10Fields					],
	[0x47, MMC4_PlayAudioMSFFields					],
	[0x1E, MMC4_PreventAllowMediumRemovalFields		],
	[0x28, MMC4_Read10Fields						],
	[0xA8, MMC4_Read12Fields						],
	[0x5C, MMC4_ReadBufferCapacityFields			],
	[0x3C, MMC4_ReadBufferFields					],
	[0x25, MMC4_ReadCapacityFields					],
	[0xB9, MMC4_ReadCDMSFFields						],
	[0xBE, MMC4_ReadCDFields						],
	[0x51, MMC4_ReadDiscInformationFields			],
	[0xAD, MMC4_ReadDVDStructureFields				],
	[0x23, MMC4_ReadFormatCapacitiesFields			],
	[0x42, MMC4_ReadSubChannelFields				],
	[0x43, MMC4_ReadTOC_PMA_ATIPFields				],
	[0x52, MMC4_ReadTrackInformationFields			],
	[0x58, MMC4_RepairTrackFields					],
	[0xA4, MMC4_ReportKeyFields						],
	[0x03, MMC4_RequestSenseFields					],
	[0x53, MMC4_ReserveTrackFields					],
	[0xBA, MMC4_ScanFields							],
	[0x2B, MMC4_Seek10Fields						],
	[0xBF, MMC4_SendDVDStructureFields				],
	[0x5D, MMC4_SendCueSheetFields					],
	[0xA3, MMC4_SendKeyFields						],
	[0x54, MMC4_SendOpcInformationFields			],
	[0xBB, MMC4_SetCDSpeedFields					],
	[0xA7, MMC4_SetReadAheadFields					],
	[0xB6, MMC4_SetStreamingFields					],
	[0x1B, MMC4_StartStopUnitFields					],
	[0x4E, MMC4_StopPlayScanFields					],
	[0x35, MMC4_SynchronizeCacheFields				],
	[0x2F, MMC4_Verify10Fields						],
	[0x2A, MMC4_Write10Fields						],
	[0xAA, MMC4_Write12Fields						],
	[0x2E, MMC4_WriteAndVerify10Fields				],
	[0x3B, MMC4_WriteBufferFields					]  # OK: 0x3B
];



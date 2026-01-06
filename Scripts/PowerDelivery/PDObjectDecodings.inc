#S******************************************************************************
#*
#*  FILENAME: PDObjectDecodings.inc
#*
#*  Copyright (C) 2015 Teledyn LeCroy
#*
#*  DESCRIPTION
#*    Decoding of Power Delivery Data Objects
#*
#*  REVISION HISTORY
#*            File Created -mm
#*******************************************************************************

%include "Standard\\Companies.inc"

set DECODE_ABORTED_FLAG = 0;
set DECODE_ABORTED_OFFSET = 0;

const PD_CURRENT_FACTOR = 10;
const PD_VOLTAGE_FACTOR = 50;
const PD_POWER_FACTOR   = 250;
const OBJ_BIT_COUNT     = 32;

const FIRST_SVID_CMD    = 16;
const LAST_SVID_CMD     = 31;
const PD_SID            = 0xFF00;

# Value, "Text", Color, Tooltip
set PD_Cap_SupplyTypeTable = [
    [ 0, "Fixed",     null, "Fixed Supply"], 
    [ 1, "Battery",   null, "Battery Supply"], 
    [ 2, "Variable",  null, "Variable Supply"], 
    [ 3, "Undefined", null, "Reserved/Invalid Value"]
];

set PD_Cap_PeakCurrentTable = [
    [  0x0,  "100%",   null,  "Peak current equals Operating Current"], 
    [  0x1,  "110%",   null,  "Overload Capabilities:\n\
1. Peak current equals 150% OC for 1ms @ 5% duty cycle (low current equals 97% OC for 19ms)\n\
2. Peak current equals 125% OC for 2ms @ 10% duty cycle (low current equals 97% OC for 18ms)\n\
3. Peak current equals 110% OC for 10ms @ 50% duty cycle (low current equals 90% OC for 10ms)"], 
    [  0x2,  "125%",   null,  "Overload Capabilities:\n\
1. Peak current equals 200% OC for 1ms @ 5% duty cycle (low current equals 95% OC for 19ms)\n\
2. Peak current equals 150% OC for 2ms @ 10% duty cycle (low current equals 94% OC for 18ms)\n\
3. Peak current equals 125% OC for 10ms @ 50% duty cycle (low current equals 75% OC for 10ms)"], 
    [  0x3,  "150%",   null,  "Overload Capabilities:\n\
1. Peak current equals 200% OC for 1ms @ 5% duty cycle (low current equals 95% OC for 19ms)\n\
2. Peak current equals 175% OC for 2ms @ 10% duty cycle (low current equals 92% OC for 18ms)\n\
3. Peak current equals 150% OC for 10ms @ 50% duty cycle (low current equals 50% OC for 10ms)"]
];

set PD_VDM_TypeTable = [
    [  0,  "Unstructured",   null,  "Unstructured VDM"], 
    [  1,  "Structured",     null,  "Structured VDM"  ]
];

set PD_VDM_CmdTable = [
    [  0,  "Rsvd0",             null,           "Reserd, shall not be used"  ],
    [  1,  "Discover ID",       [203,39,0],     ""                           ],
    [  2,  "Discover SVIDs",    [110,72,17],    ""                           ],
    [  3,  "Discover Modes",    [112,30,120],   ""                           ],
    [  4,  "Enter Mode",        [244,42,111],   ""                           ],
    [  5,  "Exit Mode",         [72,5,126],     ""                           ],
    [  6,  "Attention",         [247,75,187],   ""                           ],
    [  7,  "Rsvd7",             null,           "Reserd, shall not be used"  ],
    [  8,  "Rsvd8",             null,           "Reserd, shall not be used"  ],
    [  9,  "Rsvd9",             null,           "Reserd, shall not be used"  ],
    [ 10,  "Rsvd10",            null,           "Reserd, shall not be used"  ],
    [ 11,  "Rsvd11",            null,           "Reserd, shall not be used"  ],
    [ 12,  "Rsvd12",            null,           "Reserd, shall not be used"  ],
    [ 13,  "Rsvd13",            null,           "Reserd, shall not be used"  ],
    [ 14,  "Rsvd14",            null,           "Reserd, shall not be used"  ],
    [ 15,  "Rsvd15",            null,           "Reserd, shall not be used"  ],
    [ 16,  "SVID Cmd (0x10)",   [52, 72, 94],   "SVID Specific Command"      ],
    [ 17,  "SVID Cmd (0x11)",   [52, 72, 94],   "SVID Specific Command"      ],
    [ 18,  "SVID Cmd (0x12)",   [52, 72, 94],   "SVID Specific Command"      ],
    [ 19,  "SVID Cmd (0x13)",   [52, 72, 94],   "SVID Specific Command"      ],
    [ 20,  "SVID Cmd (0x14)",   [52, 72, 94],   "SVID Specific Command"      ],
    [ 21,  "SVID Cmd (0x15)",   [52, 72, 94],   "SVID Specific Command"      ],
    [ 22,  "SVID Cmd (0x16)",   [52, 72, 94],   "SVID Specific Command"      ],
    [ 23,  "SVID Cmd (0x17)",   [52, 72, 94],   "SVID Specific Command"      ],
    [ 24,  "SVID Cmd (0x18)",   [52, 72, 94],   "SVID Specific Command"      ],
    [ 25,  "SVID Cmd (0x19)",   [52, 72, 94],   "SVID Specific Command"      ],
    [ 26,  "SVID Cmd (0x1A)",   [52, 72, 94],   "SVID Specific Command"      ],
    [ 27,  "SVID Cmd (0x1B)",   [52, 72, 94],   "SVID Specific Command"      ],
    [ 28,  "SVID Cmd (0x1C)",   [52, 72, 94],   "SVID Specific Command"      ],
    [ 29,  "SVID Cmd (0x1D)",   [52, 72, 94],   "SVID Specific Command"      ],
    [ 30,  "SVID Cmd (0x1E)",   [52, 72, 94],   "SVID Specific Command"      ],
    [ 31,  "SVID Cmd (0x1F)",   [52, 72, 94],   "SVID Specific Command"      ],
    [ 32,  "SVID Cmd (0x20)",   [52, 72, 94],   "SVID Specific Command"      ]
];

set PD_VDM_CmdTypeTable = [
    [  0,  "Init",      null,  "Initiator"      ],
    [  1,  "RespAck",   null,  "Response ACK"   ], 
    [  2,  "RespNak",   null,  "Response NAK"   ], 
    [  3,  "RespBusy",  null,  "Response BUSY"  ]
];

set PD_VDM_VerTable = [
    [  0,  "Ver 1.0",     null,  "Version 1.0"      ],
    [  1,  "Undefined 1", null,  "Reserved Value"   ], 
    [  2,  "Undefined 2", null,  "Reserved Value"   ], 
    [  3,  "Undefined 3", null,  "Reserved Value"   ]
];

set PD_VDM_ProdTypeTable = [
    [  0,  "Undefined",             null, "" ],
    [  1,  "Hub",                   null, "" ], 
    [  2,  "Peripheral",            null, "" ], 
    [  3,  "Passive Cable",         null, "" ],
    [  4,  "Active Cable",          null, "" ],
    [  5,  "Alternate Mode Adapter",null, "" ],
    [  6,  "Rsvd",                  null, "" ],
    [  7,  "Rsvd",                  null, "" ]    
];

set PD_VDM_Cbl_SS_SuppTable = [
    [  0,  "2.0",       null, "USB 2.0 only" ],
    [  1,  "3.1 G1",    null, "USB 3.1 Gen1" ], 
    [  2,  "3.1 G1/G2", null, "USB 3.1 Gen1 and Gen2" ], 
    [  3,  "Rsvd",      null, "Reserved, shall not be used" ],
    [  4,  "Rsvd",      null, "Reserved, shall not be used" ],
    [  5,  "Rsvd",      null, "Reserved, shall not be used" ],
    [  6,  "Rsvd",      null, "Reserved, shall not be used" ],
    [  7,  "Rsvd",      null, "Reserved, shall not be used" ]    
];

set PD_VDM_Cbl_VBusCurrTable = [
    [  0,  "None",  null, "VBus not through cable" ],
    [  1,  "3A",    null, "3A" ], 
    [  2,  "5A",    null, "5A" ], 
    [  3,  "Rsvd",  null, "Reserved, shall not be used" ]  
];

set PD_VDM_Cbl_TermTypeTable = [
    [  0,  "Passive, No VConn",     null, "Both ends Passive, VCONN not required" ],
    [  1,  "Passive, VConn",        null, "Both ends Passive, VCONN required" ], 
    [  2,  "Passive/Active VConn",  null, "One end Active, one end Passive, VCONN required" ], 
    [  3,  "Active VConn",          null, "Both ends Active, VCONN required" ]  
];

set PD_VDM_Cbl_LatencyTable = [
    [  0,  "Rsvd (0)",              null, "" ],
    [  1,  "<10ns (~1m)",           null, "" ], 
    [  2,  "10ns to 20ns (~2m)",    null, "" ], 
    [  3,  "20ns to 30ns (~3m)",    null, "" ], 
    [  4,  "30ns to 40ns (~4m)",    null, "" ], 
    [  5,  "40ns to 50ns (~5m)",    null, "" ], 
    [  6,  "50ns to 60ns (~6m)",    null, "" ], 
    [  7,  "60ns to 70ns (~7m)",    null, "" ], 
    [  8,  "1000ns (~100m)",        null, "" ], 
    [  9,  "2000ns (~200m)",        null, "" ],
    [ 10,  "3000ns (~300m)",        null, "" ], 
    [ 11,  "Rsvd (11)",             null, "" ], 
    [ 12,  "Rsvd (12)",             null, "" ],
    [ 13,  "Rsvd (13)",             null, "" ], 
    [ 14,  "Rsvd (14)",             null, "" ], 
    [ 15,  "Rsvd (15)",             null, "" ]
];

set PD_VDM_Cbl_TypCToPlgTable = [
    [  0,  "Plug",      null, "" ],
    [  1,  "Receptacle",null, "" ]
];

set PD_VDM_Cbl_TypCToTable = [
    [  0,  "Type-A",  null, "" ],
    [  1,  "Type-B",  null, "" ], 
    [  2,  "Type-C",  null, "" ], 
    [  3,  "Captive", null, "" ]
];

set PD_VDM_SSXX_DirTable = [
    [  0,  "Fixed",         null, "" ],
    [  1,  "Configurable",  null, "" ]
];

set PD_VDM_Ama_SS_SuppTable = [
    [  0,  "2.0",       null, "USB 2.0 only" ],
    [  1,  "3.1 G1",    null, "USB 3.1 Gen1 and USB 2.0" ], 
    [  2,  "3.1 G1/G2", null, "USB 3.1 Gen1 and Gen2 and USB 2.0" ], 
    [  3,  "2.0 BB",    null, "USB 2.0 billboard only" ],
    [  4,  "Rsvd",      null, "Reserved, shall not be used" ],
    [  5,  "Rsvd",      null, "Reserved, shall not be used" ],
    [  6,  "Rsvd",      null, "Reserved, shall not be used" ],
    [  7,  "Rsvd",      null, "Reserved, shall not be used" ]    
];

set PD_VDM_Ama_VCONN_PowTable = [
    [  0,  "1 W",   null, "" ],
    [  1,  "1.5 W", null, "" ], 
    [  2,  "2 W",   null, "" ], 
    [  3,  "3 W",   null, "" ],
    [  4,  "4 W",   null, "" ],
    [  5,  "5 W",   null, "" ],
    [  6,  "6 W",   null, "" ],
    [  7,  "Rsvd",  null, "" ]    
];

#####################################################################################################
# PD fields information are kept in these maps.
# Each row consist of below attribute for each field :
# Field ID            : Field unique Id 
# Offset              : Field offset in bits
# Size                : Field size in bits
# Mask 	              : Field mask that can be used for masking some bits of value
# Field Name          : Field name that is shown in packet viewer
# Value Format        : This format is used in Format() method to convert field's value to string
# Value Substitute    : This array can define substitute for each field value. for example when we want to show meaningful name for numeric values
# Is Value Bitmap     : Specifies if value is a bitmap or not. 
# Tooltip             : Field tooltip that is shown in packet viewer
#####################################################################################################
set PD_Request_Fields = Map(
[
    ["MaxOpCurPow",      0,  10, 0x3FF,  "MaxOprCur | Pow", "%d mA |",     null,  0, "Maximum Operating Current (Fixed or Variable PDO) | Power (Battery PDO)", " %d mW"],
    ["MinOpCurPow",      0,  10, 0x3FF,  "MinOprCur | Pow", "%d mA |",     null,  0, "Minimum Operating Current (Fixed or Variable PDO) | Power (Battery PDO)", " %d mW"],
    ["OperCurPow",      10,  10, 0x3FF,  "OperCur | Pow",   "%d mA |",     null,  0, "Operating Current (Fixed or Variable PDO) | Power (Battery PDO)",         " %d mW"],
    ["Rsvd1",           20,   4, 0xF,    "Reserved 1",      "0x%X",        null,  0, "Reserved and shall be zero"],
    ["NoUSBSuspend",    24,   1, 0x1,    "No USB Suspend",  "%d",          null,  0, "No USB Suspend"],
    ["USBComCap",       25,   1, 0x1,    "USB Com Cap",     "%d",          null,  0, "USB Communication Capable"],
    ["CapMismatch",     26,   1, 0x1,    "Cap Mismatch",    "%d",          null,  0, "Capability Mismatch"],
    ["GiveBackFlag",    27,   1, 0x1,    "Give Back Flag",  "%d",          null,  0, "Give Back Flag"],
    ["ObjPos",          28,   3, 0x7,    "Obj Pos",         "%d",          null,  0, "Object position"],
    ["Rsvd2",           30,   1, 0x1,    "Reserved 2",      "0x%X",        null,  0, "Reserved and shall be zero"]
] );

set PD_Capabilities_Fields = Map(
[
    ["MaxCurr",      0,  10,    0x3FF,  "Max Curr",     "%d mA",  null,                     0, "Maximum Current"],
    ["Vol",         10,  10,    0x3FF,  "Vol",          "%d mV",  null,                     0, "Voltage"],
    ["PeakCur",     20,   2,    0x3,    "Peak Curr",    "%s",     PD_Cap_PeakCurrentTable,  0, "Peak Current"],
    ["Rsvd",        22,   3,    0x7,    "Reserved",     "0x%X",   null,                     0, "Reserved and shall be zero"],
    ["SnkRsvd",     20,   5,    0x1F,   "Reserved",     "0x%X",   null,                     0, "Reserved and shall be zero"],
    ["DRSwap",      25,   1,    0x1,    "DR Swap",      "%d",     null,                     0, "Data Role Swap Support"],
    ["UsbComCap",   26,   1,    0x1,    "Usb Com Cap",  "%d",     null,                     0, "USB Communications Capable"],
    ["ExtPow",      27,   1,    0x1,    "Ext Pow",      "%d",     null,                     0, "Externally Powered"],
    ["SuspSupp",    28,   1,    0x1,    "Usb Suspend",  "%d",     null,                     0, "USB Suspend Supported"],
    ["HighCap",     28,   1,    0x1,    "Higher Cap",   "%d",     null,                     0, "Higher Capability"],
    ["DualRole",    29,   1,    0x1,    "Dual Role",    "%d",     null,                     0, "Dual-Role Power (Power Role Swap Support)"],    
    ["SupType",     30,   2,    0x3,    "SupplyType",   "%s",     PD_Cap_SupplyTypeTable,   0, "Supply Type"],
    ["MaxVol",      20,  10,    0x3FF,  "Max Vol",      "%d mV",  null,                     0, "Maximum Voltage"],
    ["MinVol",      10,  10,    0x3FF,  "Min Vol",      "%d mV",  null,                     0, "Minimum Voltage"],
    ["MaxPow",       0,  10,    0x3FF,  "Max Pow",      "%d mW",  null,                     0, "Maximum Allowable Power"],
    ["OperCurr",     0,  10,    0x3FF,  "Oper Curr",    "%d mA",  null,                     0, "Operational Current"],
    ["OperPow",      0,  10,    0x3FF,  "Oper Pow",     "%d mW",  null,                     0, "Operational Power"],
    
    ["UndefCapData", 0,  30, 0x3FFFFFFF,"Undef Data",   "0x%04X", null,                     0, "Supply type is a reserved value, this data is undefined."]
] );

set PD_VDM_Fields = Map(
[
# VDM Header
    ["VDMType",         15,   1,    0x1,    "VDM Type",         "%s",     PD_VDM_TypeTable,         0, "VDM Type"],
    ["HdrVID",          16,  16,    0xFFFF, "Vendor ID",        "%s",     CompaniesTable,           0, "Vendor ID"],
    ["HdrUnstruct",      0,  15,    0x7FFF, "Unstructured",     "0x%04X", null,                     0, "Content of this field is defined by the vendor"],
    ["HdrUnstruct2",     0,  32, 0xFFFFFFFF,"Unstructured",     "0x%08X", null,                     0, "Content of this field is defined by the vendor"],
    ["HdrCmd",           0,   5,    0x1F,   "Cmd",              "%s",     PD_VDM_CmdTable,          0, "Command"],
    ["HdrRsvd1",         5,   1,    0x1,    "Rsvd1",            "0x%X",   null,                     0, "Reserved"],
    ["HdrCmdType",       6,   2,    0x3,    "Cmd Type",         "%s",     PD_VDM_CmdTypeTable,      0, "Command Type"],
    ["HdrObjPos",        8,   3,    0x7,    "Obj Pos",          "%d",     null,                     0, "Object Position"],
    ["HdrRsvd2",        11,   2,    0x3,    "Rsvd2",            "0x%X",   null,                     0, "Reserved"],
    ["HdrVDMVer",       13,   2,    0x3,    "VDM Ver",          "%s",     PD_VDM_VerTable,          0, "Structured VDM Version"],
    ["VDMUndefinedObj",  0,  32, 0xFFFFFFFF,"Undefined",        "0x%08X", null,                     0, "Content of this field is undefined"],
    
#ID Header
    ["IdHdrSVID",        0,  16,    0xFFFF, "Vendor ID",        "%s",     CompaniesTable,           0, "USB Vendor ID"],
    ["IdHdrRsvd",       16,  10,    0x3FF,  "Rsvd",             "0x%X",   null,                     0, "Reserved"],
    ["IdHdrModal",      26,   1,    0x1,    "Modal Opr",        "%d",     null,                     0, "Modal Operation"],
    ["IdHdrProdType",   27,   3,    0x7,    "Prod Type",        "%s",     PD_VDM_ProdTypeTable,     0, "Product Type"],
    ["IdHdrUsbDevice",  30,   1,    0x1,    "Device Cap",       "%d",     null,                     0, "Data Capable as USB Device"],
    ["IdHdrUsbHost",    31,   1,    0x1,    "Host Cap",         "%d",     null,                     0, "Data Capable as USB Host"],
    
#CertState
    ["CertStatTID",      0,  20,    0xFFFFF,"Test ID",          "0x%X",   null,                     0, "Test ID"],
    ["CertStatRsvd",    20,  12,    0xFFF,  "Reserved",         "0x%03X", null,                     0, "Reserved"],
    
#Product VDO
    ["ProdVdoBcdDev",    0,  16,    0xFFFF, "bcd Device",       "%d",     null,                     0, "bcdDevice"],
    ["ProdVdoPID",      16,  16,    0xFFFF, "Product ID",       "0x%04X", null,                     0, "Product ID"],
    
#Cable VDO
    ["CblVdoSSSupp",     0,   3,    0x7,    "Usb SS",           "%s",     PD_VDM_Cbl_SS_SuppTable,  0, "USB Superspeed Signaling Support"],
    ["CblVdoSopDpSupp",  3,   1,    0x1,    "SOP'' Con",        "%d",     null,                     0, "SOP'' Controller Present?"],
    ["CblVdoVBusCbl",    4,   1,    0x1,    "VBUS Cable",       "%d",     null,                     0, "VBus Through Cable"],
    ["CblVdoVBusCurrCap",5,   2,    0x3,    "VBUS Curr Cap",    "%s",     PD_VDM_Cbl_VBusCurrTable, 0,"VBus Current Handling Capability"],
    ["CblVdoSSRX2",      7,   1,    0x1,    "SS RX2",           "%d",     PD_VDM_SSXX_DirTable,     0, "SSRX2 Directionality Support"],
    ["CblVdoSSRX1",      8,   1,    0x1,    "SS RX1",           "%d",     PD_VDM_SSXX_DirTable,     0, "SSRX1 Directionality Support"],
    ["CblVdoSSTX2",      9,   1,    0x1,    "SS TX2",           "%d",     PD_VDM_SSXX_DirTable,     0, "SSTX2 Directionality Support"],
    ["CblVdoSSTX1",     10,   1,    0x1,    "SS TX1",           "%d",     PD_VDM_SSXX_DirTable,     0, "SSTX1 Directionality Support"],
    ["CblVdoTermType",  11,   2,    0x3,    "Cable Term",       "%s",     PD_VDM_Cbl_TermTypeTable, 0, "Cable Termination Type"],
    ["CblVdoCblLatency",13,   4,    0xF,    "Cable Latency",    "%s",     PD_VDM_Cbl_LatencyTable,  0, "Cable Latency"],
    ["CblVdoTypeCToPlg",17,   1,    0x1,    "Type-C to Plg",    "%s",     PD_VDM_Cbl_TypCToPlgTable,0, "Type-C to Plug/Receptacle"],
    ["CblVdoTypeCTo",   18,   2,    0x3,    "Type-C to",        "%s",     PD_VDM_Cbl_TypCToTable,   0, "Type-C to Type-A/B/C"],
    ["CblVdoRsvd",      20,   4,    0xF,    "Rsvd",             "0x%X",   null,                     0, "Reserved"],
    ["CblAmaVdoFWVer",  24,   4,    0xF,    "FW Ver",           "%d",     null,                     0, "Firmware Version"],
    ["CblAmaVdoHWVer",  28,   4,    0xF,    "HW Ver",           "%d",     null,                     0, "HW Version"],
    
#AMA VDO
    ["AmaVdoSSSupp",     0,   3,    0x7,    "USB SS",           "%s",     PD_VDM_Ama_SS_SuppTable,  0, "USB Superspeed Signaling Support"],
    ["AmaVdoVBusReq",    3,   1,    0x1,    "VBus Req",         "%d",     null,                     0, "VBus Required"],
    ["AmaVdoVConnReq",   4,   1,    0x1,    "VConn Req",        "%d",     null,                     0, "VConn Required"],
    ["AmaVdoVConnPow",   5,   3,    0x7,    "VConn Pow",        "%s",     PD_VDM_Ama_VCONN_PowTable,0, "VConn Power"],
    ["AmaVdoSSRX2",      8,   1,    0x1,    "SS RX2",           "%d",     PD_VDM_SSXX_DirTable,     0, "SSRX2 Directionality Support"],
    ["AmaVdoSSRX1",      9,   1,    0x1,    "SS RX1",           "%d",     PD_VDM_SSXX_DirTable,     0, "SSRX1 Directionality Support"],
    ["AmaVdoSSTX2",     10,   1,    0x1,    "SS TX2",           "%d",     PD_VDM_SSXX_DirTable,     0, "SSTX2 Directionality Support"],
    ["AmaVdoSSTX1",     11,   1,    0x1,    "SS TX1",           "%d",     PD_VDM_SSXX_DirTable,     0, "SSTX1 Directionality Support"],
    ["AmaVdoRsvd",      12,  12,    0xFFF,  "Rsvd",             "0x%03X", null,                     0, "Reserved"],

#SVIDs
    ["SVID1",            0,  16,    0xFFFF, "SVID %d",          "%s",     CompaniesTable,           0, "USB Vendor ID"],
    ["SVID2",           16,  16,    0xFFFF, "SVID %d",          "%s",     CompaniesTable,           0, "USB Vendor ID"],
    
#Modes
    ["Mode",             0,  32, 0xFFFFFFFF, "Mode %d",         "0x%08X", null,                     0, ""]
] );


#####################################################################################################
# PD Source Cap and Sink Cap decodings
#####################################################################################################
DecodeRequestDataObject( offset, is_intrusive_mode )
{
    DECODE_ABORTED_FLAG = 0;
    DECODE_ABORTED_OFFSET = 0;
    
    FieldColor = [26, 100, 248];
    bit_offset = offset * 8;
    giveback_flag = GetPDFieldValue("GiveBackFlag", PD_Request_Fields, bit_offset);
    
    AddSeparator();
    
    request_tooltip = "";
    if( is_intrusive_mode )
        request_tooltip = "Power level that the Port partner wants to operate at";
    else
        request_tooltip = "Currently negotiated power level";
    AddCell("Request", "", request_tooltip, FieldColor, _MONOFIELD);
    
    if( giveback_flag )
        AddPDReqSpecialField( "MinOpCurPow", bit_offset, PD_CURRENT_FACTOR, PD_POWER_FACTOR );
    else
        AddPDReqSpecialField( "MaxOpCurPow", bit_offset, PD_CURRENT_FACTOR, PD_POWER_FACTOR );
        
    AddPDReqSpecialField    ( "OperCurPow",  bit_offset, PD_CURRENT_FACTOR, PD_POWER_FACTOR );
    
    AddPDRequestField( "Rsvd1",         bit_offset );
    AddPDRequestField( "NoUSBSuspend",  bit_offset );
    AddPDRequestField( "USBComCap",     bit_offset );
    AddPDRequestField( "CapMismatch",   bit_offset );
    AddPDRequestField( "GiveBackFlag",  bit_offset ); 
    AddPDRequestField( "ObjPos",        bit_offset );
    AddPDRequestField( "Rsvd2",         bit_offset ); 
}

AddPDRequestField(FieldId, offset)
{
    return AddField(FieldId, offset, PD_Request_Fields);
}

AddPDReqSpecialField(FieldId, offset, multiply_by1, multiply_by2)
{
    return AddSpecialField(FieldId, offset, PD_Request_Fields, multiply_by1, multiply_by2);
}


#####################################################################################################
# PD Source Cap and Sink Cap decodings
#####################################################################################################
DecodeSrcCapDataObjects( offset )
{
    DECODE_ABORTED_FLAG = 0;
    DECODE_ABORTED_OFFSET = 0;
    obj_cnt = wLength / 4;
    
    FieldColor = [184, 249, 100];
    bit_offset = offset * 8;
    
    AddSeparator();
    AddCell("Src Cap", "", "Source Capabilities", FieldColor, _MONOFIELD);
    
    for( obj = 0; obj < obj_cnt; obj++ )
    {
        AddSeparator();
        AddPDCapField( "SupType", bit_offset );
        
        sup_type = GetPDFieldValue( "SupType", PD_Capabilities_Fields, bit_offset );
        
        if( sup_type == 0 )         # FIXED Capability
        {
            AddPDCapSpecialField( "MaxCurr",    bit_offset, PD_CURRENT_FACTOR );
            AddPDCapSpecialField( "Vol",        bit_offset, PD_VOLTAGE_FACTOR );
            AddPDCapField       ( "PeakCur",    bit_offset );
            AddPDCapField       ( "Rsvd",       bit_offset );
            AddPDCapField       ( "DRSwap",     bit_offset );
            AddPDCapField       ( "UsbComCap",  bit_offset );
            AddPDCapField       ( "ExtPow",     bit_offset );
            AddPDCapField       ( "SuspSupp",   bit_offset );
            AddPDCapField       ( "DualRole",   bit_offset );
        }                         
        else if( sup_type == 1 )    # BATTERY Capability
        {
            AddPDCapSpecialField( "MaxPow", bit_offset, PD_POWER_FACTOR   );
            AddPDCapSpecialField( "MinVol", bit_offset, PD_VOLTAGE_FACTOR );
            AddPDCapSpecialField( "MaxVol", bit_offset, PD_VOLTAGE_FACTOR );
            
        }
        else if( sup_type == 2 )    # VARIABLE Capability
        {
            AddPDCapSpecialField( "MaxCurr", bit_offset, PD_CURRENT_FACTOR );
            AddPDCapSpecialField( "MinVol",  bit_offset, PD_VOLTAGE_FACTOR );
            AddPDCapSpecialField( "MaxVol",  bit_offset, PD_VOLTAGE_FACTOR );
        }
        else                        # UNDEFINED Capability
        {
            AddPDCapField ( "UndefCapData",   bit_offset );
        }
        
        bit_offset += OBJ_BIT_COUNT;
    }
    ForceFullDescriptions();
}

DecodeSinkCapDataObjects( offset )
{
    DECODE_ABORTED_FLAG = 0;
    DECODE_ABORTED_OFFSET = 0;
    obj_cnt = wLength / 4;
    
    FieldColor = [110, 141, 58];
    bit_offset = offset * 8;
    
    AddSeparator();
    AddCell("Sink Cap", "", "Sink Capabilities", FieldColor, _MONOFIELD);
    
    for( obj = 0; obj < obj_cnt; obj++ )
    {
        AddSeparator();
        AddPDCapField( "SupType", bit_offset );        
        sup_type = GetPDFieldValue( "SupType", PD_Capabilities_Fields, bit_offset );
            
        if( sup_type == 0 )         # FIXED Capability
        {
            AddPDCapSpecialField( "OperCurr",   bit_offset, PD_CURRENT_FACTOR );
            AddPDCapSpecialField( "Vol",        bit_offset, PD_VOLTAGE_FACTOR );
            AddPDCapField       ( "SnkRsvd",    bit_offset );
            AddPDCapField       ( "DRSwap",     bit_offset );
            AddPDCapField       ( "UsbComCap",  bit_offset );
            AddPDCapField       ( "ExtPow",     bit_offset );
            AddPDCapField       ( "HighCap",    bit_offset );
            AddPDCapField       ( "DualRole",   bit_offset );
        }                         
        else if( sup_type == 1 )    # BATTERY Capability
        {
            AddPDCapSpecialField( "OperPow", bit_offset, PD_POWER_FACTOR   );
            AddPDCapSpecialField( "MinVol",  bit_offset, PD_VOLTAGE_FACTOR );
            AddPDCapSpecialField( "MaxVol",  bit_offset, PD_VOLTAGE_FACTOR );
            
        }
        else if( sup_type == 2 )    # VARIABLE Capability
        {
            AddPDCapSpecialField( "OperCurr", bit_offset, PD_CURRENT_FACTOR );
            AddPDCapSpecialField( "MinVol",   bit_offset, PD_VOLTAGE_FACTOR );
            AddPDCapSpecialField( "MaxVol",   bit_offset, PD_VOLTAGE_FACTOR );
        }
        else                        # UNDEFINED Capability
        {
            AddPDCapField ( "UndefCapData",   bit_offset );
        }
        bit_offset += OBJ_BIT_COUNT;
    }
    
}

AddPDCapField(FieldId, offset)
{
    return AddField(FieldId, offset, PD_Capabilities_Fields);
}
AddPDCapSpecialField(FieldId, offset, multiply_by)
{
    return AddSpecialField(FieldId, offset, PD_Capabilities_Fields, multiply_by);
}


#####################################################################################################
# PD Vendor Defined Data Object decodings
#####################################################################################################
DecodeVDMDataObjects( data_offset )
{
    DECODE_ABORTED_FLAG = 0;
    DECODE_ABORTED_OFFSET = 0;
    
    FieldColor = [238, 172, 92];
    bit_offset = data_offset * 8;
    obj_cnt = wLength / 4;
    
    vdm_type = GetPDFieldValue( "VDMType", PD_VDM_Fields, bit_offset );
    
    AddSeparator();
    ################## VDM Header #####################
    if ( vdm_type )    # Structured #
    {
        AddPDVdmField ( "HdrCmd",     bit_offset );
        AddPDVdmField ( "HdrRsvd1",   bit_offset );
        AddPDVdmField ( "HdrCmdType", bit_offset );
        AddPDVdmField ( "HdrObjPos",  bit_offset );
        AddPDVdmField ( "HdrRsvd2",   bit_offset );
        AddPDVdmField ( "HdrVDMVer",  bit_offset );
        AddPDVdmField ( "VDMType",    bit_offset );
        AddPDVdmField ( "HdrVID",     bit_offset );

        DecodeVDMStructuredDataObjects( data_offset, obj_cnt );
    }
    else              # Unstructured #
    {
        AddPDVdmField ( "HdrUnstruct", bit_offset );
        AddPDVdmField ( "VDMType",     bit_offset );
        AddPDVdmField ( "HdrVID",      bit_offset );
        
        DecodeVDMUnstructuredDataObjects( data_offset, obj_cnt );
    }    
}

DecodeVDMStructuredDataObjects( data_offset, obj_cnt )
{
    bit_offset = data_offset * 8;
    id_header_bit_offset = bit_offset + OBJ_BIT_COUNT;
    cmd        = GetPDFieldValue( "HdrCmd",         PD_VDM_Fields, bit_offset );
    cmd_type   = GetPDFieldValue( "HdrCmdType",     PD_VDM_Fields, bit_offset );
    vendor_id  = GetPDFieldValue( "HdrVID",         PD_VDM_Fields, bit_offset );
    prod_type  = GetPDFieldValue( "IdHdrProdType",  PD_VDM_Fields, id_header_bit_offset );
    
    cmd_row    = Find( PD_VDM_CmdTable, cmd );
    FieldColor = cmd_row[2];
    
    for( obj = 1; obj < obj_cnt; obj++ )
    {
        bit_offset += OBJ_BIT_COUNT;
        AddSeparator();
        
        if ( vendor_id != PD_SID )
        {
            DecodeVDMSvidSpecificDataObject( vendor_id, cmd, cmd_type, obj, bit_offset );
        }
        else
        {
            if ( cmd_type != 0 )  ## RESPONDER
            {
                if ( cmd == 1 )         # DiscoverIdentity
                {
                    if ( obj == 1 )         DecodeVDMIDHeaderObject  ( bit_offset );
                    else if ( obj == 2 )    DecodeVDMCertStateObject ( bit_offset );
                    else if ( obj == 3 )    DecodeVDMProductVDObject ( bit_offset );
                    else
                    {
                        if ( prod_type == 3 || prod_type == 4 )
                            DecodeVDMCableVDObject( bit_offset );
                        else if ( prod_type == 5 )
                            DecodeVDMAlternateModeObject( bit_offset );
                        else
                            DecodeVDMUndefinedDataObject( bit_offset );
                    }
                }
                else if ( cmd == 2 )    # DiscoverSVIDs
                {
                    DecodeVDMSVIDsObject( obj, bit_offset );
                }
                else if ( cmd == 3 )    # DiscoverModes
                {
                    DecodeVDMModeObject( obj, bit_offset );
                }
                else
                {
                    DecodeVDMUndefinedDataObject( bit_offset );
                }
            }
            else                  ## INITIATOR
            {
                AddPDVdmField ( "HdrUnstruct2", bit_offset );
            }
        }
    }
}

DecodeVDMIDHeaderObject( bit_offset )
{
    AddPDVdmField ( "IdHdrSVID",      bit_offset );
    AddPDVdmField ( "IdHdrRsvd",      bit_offset );
    AddPDVdmField ( "IdHdrModal",     bit_offset );
    AddPDVdmField ( "IdHdrProdType",  bit_offset );
    AddPDVdmField ( "IdHdrUsbDevice", bit_offset );
    AddPDVdmField ( "IdHdrUsbHost",   bit_offset );
}

DecodeVDMCertStateObject( bit_offset )
{
    AddPDVdmField ( "CertStatTID",    bit_offset );
    AddPDVdmField ( "CertStatRsvd",   bit_offset );    
}

DecodeVDMProductVDObject( bit_offset )
{
    AddPDVdmField ( "ProdVdoBcdDev",  bit_offset );
    AddPDVdmField ( "ProdVdoPID",     bit_offset );
}

DecodeVDMCableVDObject( bit_offset )
{
    AddPDVdmField ( "CblVdoSSSupp",      bit_offset );
    AddPDVdmField ( "CblVdoSopDpSupp",   bit_offset );
    AddPDVdmField ( "CblVdoVBusCbl",     bit_offset );
    AddPDVdmField ( "CblVdoVBusCurrCap", bit_offset );
    AddPDVdmField ( "CblVdoSSRX2",       bit_offset );
    AddPDVdmField ( "CblVdoSSRX1",       bit_offset );
    AddPDVdmField ( "CblVdoSSTX2",       bit_offset );
    AddPDVdmField ( "CblVdoSSTX1",       bit_offset );
    AddPDVdmField ( "CblVdoTermType",    bit_offset );
    AddPDVdmField ( "CblVdoCblLatency",  bit_offset );
    AddPDVdmField ( "CblVdoTypeCToPlg",  bit_offset );
    AddPDVdmField ( "CblVdoTypeCTo",     bit_offset );
    AddPDVdmField ( "CblVdoRsvd",        bit_offset );
    AddPDVdmField ( "CblAmaVdoFWVer",    bit_offset );
    AddPDVdmField ( "CblAmaVdoHWVer",    bit_offset );
}

DecodeVDMAlternateModeObject( bit_offset )
{
    AddPDVdmField ( "AmaVdoSSSupp",     bit_offset );
    AddPDVdmField ( "AmaVdoVBusReq",    bit_offset );
    AddPDVdmField ( "AmaVdoVConnReq",   bit_offset );
    AddPDVdmField ( "AmaVdoVConnPow",   bit_offset );
    AddPDVdmField ( "AmaVdoSSRX2",      bit_offset );
    AddPDVdmField ( "AmaVdoSSRX1",      bit_offset );
    AddPDVdmField ( "AmaVdoSSTX2",      bit_offset );
    AddPDVdmField ( "AmaVdoSSTX1",      bit_offset );
    AddPDVdmField ( "AmaVdoRsvd",       bit_offset );
    AddPDVdmField ( "CblAmaVdoFWVer",   bit_offset );
    AddPDVdmField ( "CblAmaVdoHWVer",   bit_offset );
}

DecodeVDMSVIDsObject( obj, bit_offset )
{
    AddPDVdmNumberedField ( "SVID1", obj * 2,     bit_offset );
    AddPDVdmNumberedField ( "SVID2", obj * 2 + 1, bit_offset );
}

DecodeVDMModeObject( obj, bit_offset )
{
    AddPDVdmNumberedField ( "Mode", obj,  bit_offset );
}

DecodeVDMUndefinedDataObject( bit_offset )
{
    AddPDVdmField ( "VDMUndefinedObj", bit_offset );
}

DecodeVDMUnstructuredDataObjects( data_offset, obj_cnt )
{
    bit_offset = data_offset * 8;    
    
    for( obj = 1; obj < obj_cnt; obj++ )
    {
        AddSeparator();
        bit_offset += OBJ_BIT_COUNT;
        DecodeVDMUnstructDataObject( bit_offset );
    }
}

DecodeVDMUnstructDataObject( bit_offset )
{
    AddPDVdmField ( "HdrUnstruct2", bit_offset );
}

AddPDVdmField(FieldId, offset)
{
    return AddField(FieldId, offset, PD_VDM_Fields);
}

AddPDVdmNumberedField ( FieldId, num, offset )
{
    return AddField(FieldId, offset, PD_VDM_Fields, num);
}

#####################################################################################
# DisplayPort Decoding Functions 
#####################################################################################
set DisplayPortCommandsTable =
[   #CommandID  #CommandFunction(cmd, cmd_type, obj, bit_offset) returns 1 in case of success, and 0 when the data can't be decoded here
    [0,         null                            ],
    [3,         "DisplayPortDiscoverModes"      ],
    [6,         "DisplayPortAttention"          ],
    [16,        "DisplayPortStatusUpdate"       ],
    [17,        "DisplayPortConfigure"          ]
];

DisplayPortDiscoverModes( cmd, cmd_type, obj, bit_offset )
{
    if ( cmd == 3 && cmd_type != 0 ) # Discover Modes Response
    {
        #FIXME
    }
    
    return 0;
}

DisplayPortAttention( cmd, cmd_type, obj, bit_offset )
{
    if ( cmd == 6 && cmd_type == 0 ) # Attention Init
    {
        #FIXME
    }
    
    return 0;
}

DisplayPortStatusUpdate( cmd, cmd_type, obj, bit_offset )
{
    #FIXME
    return 0;
}

DisplayPortConfigure( cmd, cmd_type, obj, bit_offset )
{
    #FIXME
    return 0;
}

###########################################################################################
# SVID Specific decodings
###########################################################################################
set Supported_SVIDs_Table = 
[   #SVID       #Name              #CommandsTable: table format is: [cmd, "function"]
    [0x0,       "UnsupportedSVID" , null                        ],
    [0xFF01,    "DisplayPort"     , DisplayPortCommandsTable    ]
    
    #Add more SVIDs Here
];

DecodeVDMSvidSpecificDataObject( vendor_id, cmd, cmd_type, obj, bit_offset )
{
    row = Find(Supported_SVIDs_Table, vendor_id);
    if( row[0] == 0 || row[2] == null ) #Not supported
    {
        if( cmd == 3 && cmd_type != 0 ) #Discover Modes
        {
            DecodeVDMModeObject( obj, bit_offset );
        }
        else
        {
            DecodeVDMUnstructDataObject( bit_offset );
        }
    }
    else
    {
        functions_table = row[2];
        func_row = Find( functions_table, cmd );
        decoded = 0;#1: decoded, #0: not decoded
        if( func_row[1] != null )
        {
            #CommandFunction(cmd, cmd_type, obj, bit_offset) returns 1 in case of success, and 0 when the data can't be decoded.
            decoded = Call( func_row[1], [cmd, cmd_type, obj, bit_offset] );
        }
        
        if( decoded == 0 )
        {
            DecodeVDMUndefinedDataObject( bit_offset );
        }
    }
}

#####################################################################################################
# Common Functions
#####################################################################################################
AddField(FieldId, offset, FieldsArray, NameFormatExtra)
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
    raw_value       = 0;

    if( offset + len > in.DataLength * 8 )
    {
        DECODE_ABORTED_FLAG = 1;
        DECODE_ABORTED_OFFSET = offset;

        AddSeparator();
        AddCell("DECODE ABORTED", "NOT ENOUGH DATA", "", WarningColor, _ERROR); 
        AddSeparator();
        return 0;
    }
    
    value = GetNBits(in.Data, offset, len);
    value &= mask;
    raw_value = value;
    
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
    }
    
    tooltip += Format("\n\n%s: ", name);
    tooltip += Format("0x%X", raw_value);
    
    if( NameFormatExtra != null )
        name = Format( name, NameFormatExtra );
        
    AddPayLoadCell(name, Format(valueformat, value), tooltip);
    
    return 1;
}

## Return Field value from in.Data
GetPDFieldValue( FieldId, FieldsArray, data_offset )
{
    _row = Find(FieldsArray, FieldId);
    val = GetNBits(in.Data, data_offset + _row[1], _row[2]);
    return val;
}

AddSpecialField(FieldId, offset, FieldsArray, multiply_by1, multiply_by2)
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
    _2ndvalueformat = null;
    
    if( sizeof( _row ) > 9 )
        _2ndvalueformat = _row[9];

    if( offset + len > in.DataLength * 8 )
    {
        DECODE_ABORTED_FLAG = 1;
        DECODE_ABORTED_OFFSET = offset;

        AddSeparator();
        AddCell("DECODE ABORTED", "NOT ENOUGH DATA", "", WarningColor, _ERROR); 
        AddSeparator();
        return 0;
    }
    
    value = GetNBits(in.Data, offset, len);
    value &= mask;
    value1 = value * multiply_by1;
    
    value2 = null;
    if( multiply_by2 != null )
        value2 = value * multiply_by2;
    
    cell_text = Format(valueformat, value1);
    
    if ( value2 != null && _2ndvalueformat )
        cell_text += Format(_2ndvalueformat, value2);
    
    tooltip += Format("\n\n%s: ", name);
    tooltip += Format("0x%X",     value);
    
    AddPayLoadCell(name, cell_text, tooltip);
    
    return 1;
}

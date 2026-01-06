#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  hci_common.inc
#
#  common HCI commands/events definitions
#


const HCIconnhandleColor = 0x876304;


Next16Bits()
{
  data = NextNBits(8);
  data = (NextNBits(8) << 8) + data;
  return data;
}


Next24Bits()
{
  data = NextNBits(8);
  data = (NextNBits(8) << 8) + data;
  data = (NextNBits(8) << 16) + data;
  return data;
}

Next32Bits()
{
  data = NextNBits(8);
  data = (NextNBits(8) << 8) + data;
  data = (NextNBits(8) << 16) + data;
  data = (NextNBits(8) << 24) + data;
  return data;
}



set HciErrorCodes = 
[
  [0xffff, "???"                   , "Unknown HCI Error code."                          ],
  [0x00 , "Success"                , "Success"                                          ],
  [0x01 , "Unknown HCI Cmd"        , "Unknown HCI Command"                              ],
  [0x02 , "No Connection"          , "Unknown Connection Identifier"                    ],
  [0x03 , "Hardware Failure"       , "Hardware Failure"                                 ],
  [0x04 , "Page Timeout"           , "Page Timeout"                                     ],
  [0x05 , "Auth. Failure"          , "Authentication Failure"                           ],
  [0x06 , "PIN Missing"            , "PIN Missing"                                      ],
  [0x07 , "Memory Full"            , "Memory Capacity Exceeded"                         ],
  [0x08 , "Timeout"                , "Connection Timeout"                               ],
  [0x09 , "Max Connections"        , "Connection Limit Exceeded"                        ],
  [0x0A , "Max SCO"                , "Synchronous Connection Limit To A Device Exceeded"],
  [0x0B , "ACL exists"             , "ACL Connection Already Exists"                    ],
  [0x0C , "Disallowed"             , "Command Disallowed"                               ],
  [0x0D , "limited resources"      , "Connection Rejected due to Limited Resources"     ],
  [0x0E , "security reasons"       , "Connection Rejected Due To Security Reasons"      ],
  [0x0F , "Unacceptable BDADDR"    , "Connection Rejected due to Unacceptable BD_ADDR"  ],
  [0x10 , "Host Timeout"           , "Connection Accept Timeout Exceeded"               ],
  [0x11 , "Unsupported"            , "Unsupported Feature or Parameter Value"           ],
  [0x12 , "Invalid parameters"     , "Invalid HCI Command Parameters"                   ],
  [0x13 , "Remote Terminated"      , "Remote User Terminated Connection"                ],
  [0x14 , "Low Resources"          , "Remote Device Terminated Connection due to Low Resources"  ],
  [0x15 , "Power Off"              , "Remote Device Terminated Connection due to Power Off"      ],
  [0x16 , "LocalTerminated"        , "Connection Terminated By Local Host"              ],
  [0x17 , "Repeated Attempts"      , "Repeated Attempts"                                ],
  [0x18 , "Pairing Not Allowed"    , "Pairing Not Allowed"                              ],
  [0x19 , "Unknown LMP"            , "Unknown LMP PDU"                                  ],
  [0x1A , "Unsupported Feature"    , "Unsupported Remote Feature"                       ],
  [0x1B , "Rejected"               , "SCO Offset Rejected"                              ],
  [0x1C , "Rejected"               , "SCO Interval Rejected"                            ],
  [0x1D , "Rejected"               , "SCO Air Mode Rejected"                            ],
  [0x1E , "Invalid Parameters"     , "Invalid LMP Parameters"                           ],
  [0x1F , "Error"                  , "Unspecified Error"                                ],
  [0x20 , "Unsupported"            , "Unsupported LMP Parameter Value"                  ],
  [0x21 , "Not Allowed"            , "Role Change Not Allowed"                          ],
  [0x22 , "LMP Resp Tout"          , "LMP Response Timeout"                             ],
  [0x23 , "LMP Collision"          , "LMP Error Transaction Collision"                  ],
  [0x24 , "LMP Not Allowed"        , "LMP PDU Not Allowed"                              ],
  [0x25 , "Not Acceptable"         , "Encryption Mode Not Acceptable"                   ],
  [0x26 , "Unit Key Used"          , "Link Key Can Not be Changed"                      ],
  [0x27 , "Not Supported"          , "Requested QoS Is Not Supported"                   ],
  [0x28 , "Instant Passed"         , "Instant Passed"                                   ],
  [0x29 , "Not Supported"          , "Pairing With Unit Key Not Supported"              ],
  [0x2A , "Tra Collision"          , "Different Transaction Collision"                  ],
  [0x2B , "Reserved"               , "Reserved"                                         ],
  [0x2C , "QoS Parameter"          , "QoS Unacceptable Parameter"                       ],
  [0x2D , "QoS Rejected"           , "QoS Rejected"                                     ],
  [0x2E , "Channel Classification" , "Channel Classification Not Supported"             ],
  [0x2F , "Insufficient Security"  , "Insufficient Security"                            ],
  [0x30 , "Out Of Mandatory Range" , "Parameter Out Of Mandatory Range"                 ],
  [0x31 , "Reserved"               , "Reserved"                                         ],
  [0x32 , "Role Switch Pending"    , "Role Switch Pending"                              ],
  [0x33 , "Reserved"               , "Reserved"                                         ],
  [0x34 , "Reserved Slot"          , "Reserved Slot Violation"                          ],
  [0x35 , "Switch Failed"          , "Role Switch Failed"                               ]
];


ShowBD_ADDR(color)
{
    str = Format( "%02X", NextNBits(8) );
    str = Format( "%02X", NextNBits(8) ) + str;
    str = Format( "%02X", NextNBits(8) ) + str;
    str = Format( "%02X", NextNBits(8) ) + str;
    str = Format( "%02X", NextNBits(8) ) + str;
    str = Format( "%02X", NextNBits(8) ) + str;
     
    AddCell ("BD_ADDR", str, "", color);
}

set Page_Scan_Repetition_ModeTable =
[
  [0xFF , "Reserved" ], 
  [0x00 , "R0"       ],
  [0x01 , "R1"       ],
  [0x02 , "R2"       ]
];

ShowPage_Scan_Repetition_Mode(color)
{
    data = NextNBits(8);
    _row = Find(Page_Scan_Repetition_ModeTable, data);
    AddCell("Page_Scan_Repetition_Mode", _row[1], Format("0x%02X - ", data) + _row[1], color);
}



set Page_Scan_Period_ModeTable = 
[
  [ 0xFF , "Reserved." ],
  [ 0x00 , "P0"        ],
  [ 0x01 , "P1"        ],
  [ 0x02 , "P2"        ]
];

ShowPage_Scan_Period_Mode(color)
{
    data = NextNBits(8);
    _row = Find(Page_Scan_Period_ModeTable, data);
    AddCell("Page_Scan_Period_Mode",  _row[1], Format("0x%02X - ", data) + _row[1], color);
}

set Page_Scan_ModeTable = 
[
  [0xFF , "Reserved." , "Reserved."                       ],
  [0x00 , "Mandatory" , "Mandatory Page Scan Mode."       ],
  [0x01 , "Mode I"    , "Optional Page Scan Mode I."      ],
  [0x02 , "Mode II"   , "Optional Page Scan Mode II."     ],
  [0x03 , "Mode III"  , "Optional Page Scan Mode III."    ]
];

ShowPage_Scan_Mode(color)
{
    data = NextNBits(8);
    _row = Find(Page_Scan_ModeTable, data);
    AddCell("Page_Scan_Mode", _row[1], Format("0x%02X - ", data) + _row[2], color);
}

ShowClass_of_Device(color)
{
    AddCell ("Class_of_Device", Format("0x%06X", Next24Bits()), "Class of Device for the device.", color);
}

ShowConnection_Handle()
{
    str = Format( "%02X", NextNBits(8) );
    str = Format( "0x%01X", NextNBits(8) ) + str;

    AddCell("Connection_Handle", str, "Connection Handle.\nRange: 0x000-0xEFF (0xF00 - 0xFFF Reserved for future use)", HCIconnhandleColor);
}

set Encryption_ModeTable = 
[
  [ 0xFF , "Reserved."                                                 ],
  [ 0x00 , "Encryption not required.."                                 ],
  [ 0x01 , "Encryption required for all connections."                  ]

 # 1.1 spec
 #  [ 0x01 , "Encryption only for point-to-point packets."               ],
 #  [ 0x02 , "Encryption for both point-to-point and broadcast packets." ]
];

ShowEncryption_Mode(color)
{
    data = NextNBits(8);
    _row = Find(Encryption_ModeTable, data);
    AddCell("Encryption_Mode",  Format("0x%02X", data), _row[1], color);
}

ShowName(color)
{
  name = "";
  char = NextNBits(8);

  while (char != 0)
  {
    name = name + Format( "%c", char);
    char = NextNBits(8);
  }
  AddCell ("Name",  name, "A UTF-8 encoded User-Friendly Descriptive Name for the device.", color);
}

ShowLink_Key(color)
{
    data = NextNBits(32);
    str = Format("0x%08X", data);
    data = NextNBits(32);
    str = str + Format("%08X", data);
    data = NextNBits(32);
    str = str + Format("%08X", data);
    data = NextNBits(32);
    str = str + Format("%08X", data);
    AddCell ("Link_Key", str, "Link Key for the associated BD_ADDR.", color);
}

set PacketTypeTable_ALL =
[
  [0x0001 , "Reserved for future use."  ],
  [0x0002 , "Reserved for future use."  ],
  [0x0004 , "Reserved for future use."  ],
  [0x0008 , "DM1"                       ],
  [0x0010 , "DH1"                       ],
  [0x0020 , "HV1"                       ],
  [0x0040 , "HV2"                       ],
  [0x0080 , "HV3"                       ],
  [0x0100 , "Reserved for future use."  ],
  [0x0200 , "Reserved for future use."  ],
  [0x0400 , "DM3"                       ],
  [0x0800 , "DH3"                       ],
  [0x1000 , "Reserved for future use."  ],
  [0x2000 , "Reserved for future use."  ],
  [0x4000 , "DM5"                       ],
  [0x8000 , "DH5"                       ]
];

set PacketTypeTable_ACL =
[
  [0x0001 , "Reserved for future use."  ],
  [0x0002 , "no 2-DH1"                  ],
  [0x0004 , "no 3-DH1"                  ],
  [0x0008 , "DM1"                       ],
  [0x0010 , "DH1"                       ],
  [0x0020 , "Reserved for future use."  ],
  [0x0040 , "Reserved for future use."  ],
  [0x0080 , "Reserved for future use."  ],
  [0x0100 , "no 2-DH3"                  ],
  [0x0200 , "no 3-DH3"                  ],
  [0x0400 , "DM3"                       ],
  [0x0800 , "DH3"                       ],
  [0x1000 , "no 2-DH5"                  ],
  [0x2000 , "no 3-DH5"                  ],
  [0x4000 , "DM5"                       ],
  [0x8000 , "DH5"                       ]
];

set PacketTypeTable_SCO =
[
  [0x0001 , "Reserved for future use."  ],
  [0x0002 , "Reserved for future use."  ],
  [0x0004 , "Reserved for future use."  ],
  [0x0008 , "Reserved for future use."  ],
  [0x0010 , "Reserved for future use."  ],
  [0x0020 , "HV1"                       ],
  [0x0040 , "HV2"                       ],
  [0x0080 , "HV3"                       ],
  [0x0100 , "Reserved for future use."  ],
  [0x0200 , "Reserved for future use."  ],
  [0x0400 , "Reserved for future use."  ],
  [0x0800 , "Reserved for future use."  ],
  [0x1000 , "Reserved for future use."  ],
  [0x2000 , "Reserved for future use."  ],
  [0x4000 , "Reserved for future use."  ],
  [0x8000 , "Reserved for future use."  ]
];

set PacketTypeTable_eSCO =
[
  [0x0001 , "HV1"                       ],
  [0x0002 , "HV2"                       ],
  [0x0004 , "HV3"                       ],
  [0x0008 , "EV3"                       ],
  [0x0010 , "EV4"                       ],
  [0x0020 , "EV5"                       ],
  [0x0040 , "no 2-EV3"                  ],
  [0x0080 , "no 3-EV3"                  ],
  [0x0100 , "no 2-EV5"                  ],
  [0x0200 , "no 3-EV5"                  ],
  [0x0400 , "Reserved for future use."  ],
  [0x0800 , "Reserved for future use."  ],
  [0x1000 , "Reserved for future use."  ],
  [0x2000 , "Reserved for future use."  ],
  [0x4000 , "Reserved for future use."  ],
  [0x8000 , "Reserved for future use."  ]
];


ShowPacket_Type(color, table)
{
    data = Next16Bits();

    tooltip = "<HTML>Packet types:<TABLE CELLPADDING=2>";
    for (i = 0; i < sizeof(table); i++)
    {
      tooltip = tooltip + Format("<TR><TD>bit %d</TD>", i) +
        select { data & table[i][0] : "<TD>1</TD>";
                 default            : "<TD>0</TD>"; } + "<TD>" + table[i][1] + "</TD></TR>";
 
    }
    tooltip += "</TABLE></HTML>";


    AddCell("Packet_Type", Format("0x%04X", data), tooltip, color );
}

set Link_Policy_SettingsTable = 
[
  [0x0001 , "Enable Master Slave Switch."   ],
  [0x0002 , "Enable Hold Mode."             ],
  [0x0004 , "Enable Sniff Mode."            ],
  [0x0008 , "Enable Park Mode."             ]
];

ShowLink_Policy_Settings(color)
{
    data = Next16Bits();
    if (data == 0)
      AddCell("Link_Policy_Settings", Format("0x%04X", data), "0x0000  - Disable All LM Modes. Default.", color);
    else
    {

        for (i = 0; i < sizeof(Link_Policy_SettingsTable); i++)
        {
          tooltip = tooltip + 
            select { data & Link_Policy_SettingsTable[i][0] : "\nyes - ";
                     default : "\nno  - "; } + Link_Policy_SettingsTable[i][1];
            
        }
        tooltip = "<HTML>Link_Policy_Settings<TABLE CELLPADDING=2>";
        for (i = 0; i < sizeof(Link_Policy_SettingsTable); i++)
        {
          tooltip = tooltip + Format("<TR><TD>bit %d</TD>", i)
            + select { data & Link_Policy_SettingsTable[i][0] : "<TD>1</TD>";
                     default                                : "<TD>0</TD>"; } 
            + "<TD>" + Link_Policy_SettingsTable[i][1] + "</TD></TR>";
 
        }
        tooltip = tooltip + Format("<TR><TD>bit %d-32</TD>", i) 
          + Format("<TD>0x%X</TD><TD>reserved</TD></TR>", data >> i); 
        
        tooltip += "</TABLE></HTML>";
        AddCell("Link_Policy_Settings", Format("0x%04X", data), tooltip, color);
    }
}


set PIN_TypeTable = 
[
  [ 0xff , "unknown"  ],
  [ 0x00 , "Variable" ],
  [ 0x01 , "Fixed"    ]
];

ShowPIN_Type(color)
{
    data = NextNBits(8);
    _row = Find(PIN_TypeTable, data);
    AddCell("PIN_Type",  _row[1], Format("0x%02X - ", data) + _row[1], color);
}

set Scan_EnableTable = 
[
  [ 0xFF , "Reserved"                                   ],
  [ 0x00 , "No Scans enabled. Default."                 ],
  [ 0x01 , "Inquiry Scan enabled.\nPage Scan disabled." ],
  [ 0x02 , "Inquiry Scan disabled.\nPage Scan enabled." ],
  [ 0x03 , "Inquiry Scan enabled.\nPage Scan enabled."  ]
];

ShowScan_Enable(color)
{
    data = NextNBits(8);
    _row = Find(Scan_EnableTable, data);
    AddCell("Scan_Enable",  Format("0x%02X", data), _row[1], color);
}

ShowPage_Scan_Interval(color)
{
    data = Next16Bits();
    AddCell("Page_Scan_Interval", Format("%d slots",  data),
            "The Page_Scan_Interval configuration parameter defines the amount of time between consecutive page scans.\nRange: 0x0012 - 0x1000\nTime = N * 0.625 msec\nRange: 11.25 msec - 2560 msec",
             color,
             select {((data > 0x1000) || (data < 0x0012)): _ERROR; } );
}

ShowPage_Scan_Window(color)
{
    data = Next16Bits();
    AddCell("Page_Scan_Window", Format("%d slots",  data),
            "The Page_Scan_Window configuration parameter defines the amount of time for the duration of the page scan.\nRange: 0x0011 - 0x1000\nTime = N * 0.625 msec\nRange: 10.625 msec - 2560 msec",
             color,
             select {((data > 0x1000) || (data < 0x0011)): _ERROR; } );
}

ShowInquiry_Scan_Interval(color)
{
    data = Next16Bits();
    AddCell("Inquiry_Scan_Interval", Format("%d slots",  data),
            "The Inquiry_Scan_Interval configuration parameter defines the amount of time between consecutive inquiry scans.\nRange: 0x0012 - 0x1000\nTime = N * 0.625 msec\nRange: 11.25 msec - 2560 msec",
             color,
             select {((data > 0x1000) || (data < 0x0012)): _ERROR; } );
}

ShowInquiry_Scan_Window(color)
{
    data = Next16Bits();
    AddCell("Inquiry_Scan_Window", Format("%d slots",  data),
            "The Inquiry_Scan_Window configuration parameter defines the amount of time for the duration of the inquiry scan.\nRange: 0x0012 - 0x1000\nTime = N * 0.625 msec\nRange: 10.625 msec - 2560 msec",
             color,
             select {((data > 0x1000) || (data < 0x0011)): _ERROR; } );
}

set Authentication_EnableTable =
[
  [ 0xFF , "Reserved"                                     ],
  [ 0x00 , "Authentication not required."                 ],
  [ 0x01 , "Authentication required for all connections." ]
];

ShowAuthentication_Enable(color)
{
    data = NextNBits(8);
    _row = Find(Authentication_EnableTable, data);
    AddCell("Authentication_Enable",  Format("0x%02X", data), _row[1], color);
}


ShowVoice_Setting(color)
{
    data = Next16Bits();

    tooltip = "<HTML>Voce Settings:<TABLE CELLPADDING=2>"
      + "<TR><TD><B>bits</B></TD><TD><B>value</B></TD><TD><B>parameter</B></TD><TD><B>value description</B></TD></TR>"
      + "<TR><TD>bit 0-1</TD>" 
      + Format("<TD>0x%X</TD>", data & 0x003)
      + "<TD>Air Coding Format</TD><TD>" 
      + select {
          (data & 0x003) == 0x000 : "CVSD";
          (data & 0x003) == 0x001 : "u-Law";
          (data & 0x003) == 0x002 : "A-Law";
          (data & 0x003) == 0x003 : "Transparent Data";
      }
      + "</TD></TR>"
 
      + "<TR><TD>bit 2-4</TD>" 
      + Format("<TD>%d</TD>",  (data & 0x01C) >> 2)
      + "<TD>Linear_PCM_Bit_Pos</TD><TD># bit positions that MSB of sample is away\n"
      + "from starting at MSB (only for Liner PCM)"
      + "</TD></TR>"

      + "<TR><TD>bit 5</TD>" 
      + select {
          (data & 0x020) == 0x000 : "<TD>0</TD><TD>Input Sample Size</TD><TD>8 bit (only for Liner PCM)";
          (data & 0x020) == 0x020 : "<TD>1</TD><TD>Input Sample Size</TD><TD>16 bit (only for Liner PCM)";
      }
      + "</TD></TR>"

      + "<TR><TD>bit 6-7</TD>" 
      + Format("<TD>0x%X</TD>", (data >> 6) & 0x003)
      + "<TD>Input Data Format</TD><TD>" 
      + select {
          (data & 0x0C0) == 0x000 : "1's complement";
          (data & 0x0C0) == 0x040 : "2's complement";
          (data & 0x0C0) == 0x080 : "Sign-Magnitude";
          (data & 0x0C0) == 0x0C0 : "Unsigned";
      }
      +"</TD></TR>"

      + "<TR><TD>bit 8-9</TD>" 
      + Format("<TD>0x%X</TD>", (data >> 8) & 0x003)
      + "<TD>Input Coding</TD><TD>" 
      + select {
          (data & 0x300) == 0x000 : "Linear";
          (data & 0x300) == 0x100 : "u-Law Input Coding";
          (data & 0x300) == 0x200 : "A-Law Input Coding";
          (data & 0x300) == 0x300 : "Reserved for Future Use";
      }
      + "</TD></TR>"

      + Format("<TR><TD>bit 10-15</TD><TD>0x%X</TD><TD>reserved</TD><TD></TD></TR>", data >> 10)

      + "</TABLE></HTML>";

    AddCell("Voice_Setting", Format("0x%04X", data), tooltip, color);
}




BitValue(data, mask)
{
  return select
  {
    data & mask : "<TD>1</TD>";
    default     : "<TD>0</TD>";
  };
}

ShowLmpFeatures(color)
{
        ToolTip = "<HTML><TABLE CELLPADDING=0><TR><TD>";

    data = NextNBits(8);
    text = Format(" %02X", data);

        ToolTip += "<TABLE CELLPADDING=2>"
          + "<TR><TD><B>byte 0</B></TD>"
          + Format("<TD></TD><TD><B>0x%02X</B></TD></TR>", data)
                                
          + "<TR><TD>bit 0 (0)</TD>" + BitValue(data, 0x01) + "<TD ALIGN=LEFT>3-slot packets</TD></TR>"
          + "<TR><TD>bit 1 (1)</TD>" + BitValue(data, 0x02) + "<TD ALIGN=LEFT>5-slot packets</TD></TR>"
          + "<TR><TD>bit 2 (2)</TD>" + BitValue(data, 0x04) + "<TD ALIGN=LEFT>Encryption</TD></TR>"
          + "<TR><TD>bit 3 (3)</TD>" + BitValue(data, 0x08) + "<TD ALIGN=LEFT>Slot offset</TD></TR>"
          + "<TR><TD>bit 4 (4)</TD>" + BitValue(data, 0x10) + "<TD ALIGN=LEFT>Timing accuracy</TD></TR>"
          + "<TR><TD>bit 5 (5)</TD>" + BitValue(data, 0x20) + "<TD ALIGN=LEFT>Role switch</TD></TR>"
          + "<TR><TD>bit 6 (6)</TD>" + BitValue(data, 0x40) + "<TD ALIGN=LEFT>Hold mode</TD></TR>"
          + "<TR><TD>bit 7 (7)</TD>" + BitValue(data, 0x80) + "<TD ALIGN=LEFT>Sniff mode</TD></TR>";

    data = NextNBits(8);
    text += Format(" %02X", data);

        ToolTip += "<TR><TD><B>byte 1</B></TD>"
          + Format("<TD></TD><TD><B>0x%02X</B></TD></TR>", data)
                                
          + "<TR><TD>bit 0 (8)</TD>" + BitValue(data, 0x01) + "<TD ALIGN=LEFT>Park state</TD></TR>"
          + "<TR><TD>bit 1 (9)</TD>" + BitValue(data, 0x02) + "<TD ALIGN=LEFT>Power control requests</TD></TR>"
          + "<TR><TD>bit 2 (10)</TD>" + BitValue(data, 0x04) + "<TD ALIGN=LEFT>Channel quality driven data rate</TD></TR>"
          + "<TR><TD>bit 3 (11)</TD>" + BitValue(data, 0x08) + "<TD ALIGN=LEFT>SCO link</TD></TR>"
          + "<TR><TD>bit 4 (12)</TD>" + BitValue(data, 0x10) + "<TD ALIGN=LEFT>HV2 packets</TD></TR>"
          + "<TR><TD>bit 5 (13)</TD>" + BitValue(data, 0x20) + "<TD ALIGN=LEFT>HV3 packets</TD></TR>"
          + "<TR><TD>bit 6 (14)</TD>" + BitValue(data, 0x40) + "<TD ALIGN=LEFT>u-law log synchronous data</TD></TR>"
          + "<TR><TD>bit 7 (15)</TD>" + BitValue(data, 0x80) + "<TD ALIGN=LEFT>A-law log synchronous data</TD></TR>";
        
    data = NextNBits(8);
    text += Format(" %02X", data);

        ToolTip += "<TR><TD><B>byte 2</B></TD>"
          + Format("<TD></TD><TD><B>0x%02X</B></TD></TR>", data)
                                
          + "<TR><TD>bit 0 (16)</TD>" + BitValue(data, 0x01) + "<TD ALIGN=LEFT>CVSD synchronous data</TD></TR>"
          + "<TR><TD>bit 1 (17)</TD>" + BitValue(data, 0x02) + "<TD ALIGN=LEFT>Paging parameter negotiation</TD></TR>"
          + "<TR><TD>bit 2 (18)</TD>" + BitValue(data, 0x04) + "<TD ALIGN=LEFT>Power control</TD></TR>"
          + "<TR><TD>bit 3 (19)</TD>" + BitValue(data, 0x08) + "<TD ALIGN=LEFT>Transparent synchronous data</TD></TR>"
          + "<TR><TD>bit 4 - 6</TD>"
          + Format("<TD>%d</TD><TD>flow control lag</TD></TR>", (data >> 4) & 0x7)
          + "<TR><TD>bit 7 (23)</TD>" + BitValue(data, 0x80) + "<TD ALIGN=LEFT>Broadcast encryption</TD></TR>"

          + "</TABLE></TD>"

          + "<TD>"
          + "<TABLE CELLPADDING=2>";

    data = NextNBits(8);
    text += Format(" %02X", data);

        ToolTip += "<TR><TD><B>byte 3</B></TD>"
          + Format("<TD></TD><TD><B>0x%02X</B></TD></TR>", data)
                                
          + "<TR><TD>bit 0 (24)</TD>" + BitValue(data, 0x01) + "<TD ALIGN=LEFT>Scatter mode</TD></TR>"
#          + "<TR><TD>bit 1 (25)</TD>" + BitValue(data, 0x02) + "<TD ALIGN=LEFT>reserved</TD></TR>"
#          + "<TR><TD>bit 2 (26)</TD>" + BitValue(data, 0x04) + "<TD ALIGN=LEFT>reserved</TD></TR>"
          + "<TR><TD>bit 3 (27)</TD>" + BitValue(data, 0x08) + "<TD ALIGN=LEFT>Enhanced inquiry scan</TD></TR>"
          + "<TR><TD>bit 4 (28)</TD>" + BitValue(data, 0x10) + "<TD ALIGN=LEFT>Interlaced inquiry scan</TD></TR>"
          + "<TR><TD>bit 5 (29)</TD>" + BitValue(data, 0x20) + "<TD ALIGN=LEFT>Interlaced page scan</TD></TR>"
          + "<TR><TD>bit 6 (30)</TD>" + BitValue(data, 0x40) + "<TD ALIGN=LEFT>RSSI with inquiry results</TD></TR>"
          + "<TR><TD>bit 7 (31)</TD>" + BitValue(data, 0x80) + "<TD ALIGN=LEFT>Extended SCO link (EV3 packets)</TD></TR>";

    data = NextNBits(8);
    text += Format(" %02X", data);

        ToolTip += "<TR><TD><B>byte 4</B></TD>"
          + Format("<TD></TD><TD><B>0x%02X</B></TD></TR>", data)
                                
          + "<TR><TD>bit 0 (32)</TD>" + BitValue(data, 0x01) + "<TD ALIGN=LEFT>EV4 packets</TD></TR>"
          + "<TR><TD>bit 1 (33)</TD>" + BitValue(data, 0x02) + "<TD ALIGN=LEFT>EV5 packets</TD></TR>"
          + "<TR><TD>bit 2 (34)</TD>" + BitValue(data, 0x04) + "<TD ALIGN=LEFT>Absence masks</TD></TR>"
          + "<TR><TD>bit 3 (35)</TD>" + BitValue(data, 0x08) + "<TD ALIGN=LEFT>AFH capable slave</TD></TR>"
          + "<TR><TD>bit 4 (36)</TD>" + BitValue(data, 0x10) + "<TD ALIGN=LEFT>AFH classification slave</TD></TR>"
          + "<TR><TD>bit 5 (37)</TD>" + BitValue(data, 0x20) + "<TD ALIGN=LEFT>Alias authentication</TD></TR>"
          + "<TR><TD>bit 6 (38)</TD>" + BitValue(data, 0x40) + "<TD ALIGN=LEFT>Anonymity mode</TD></TR>";
#          + "<TR><TD>bit 7 (39)</TD>" + BitValue(data, 0x80) + "<TD ALIGN=LEFT>reserved</TD></TR>"


    data = NextNBits(8);
    text += Format(" %02X", data);

        ToolTip += "<TR><TD><B>byte 5</B></TD>"
         + Format("<TD></TD><TD><B>0x%02X</B></TD></TR>", data)

#         + "<TR><TD> </TD><TD></TD><TD></TD></TR>"; 

#          + "<TR><TD>bit 0 (40)</TD>" + BitValue(data, 0x01) + "<TD ALIGN=LEFT>reserved</TD></TR>"
#          + "<TR><TD>bit 1 (41)</TD>" + BitValue(data, 0x02) + "<TD ALIGN=LEFT>reserved</TD></TR>"
#          + "<TR><TD>bit 2 (42)</TD>" + BitValue(data, 0x04) + "<TD ALIGN=LEFT>reserved</TD></TR>"
          + "<TR><TD>bit 3 (43)</TD>" + BitValue(data, 0x08) + "<TD ALIGN=LEFT>AFH capable master</TD></TR>"
          + "<TR><TD>bit 4 (44)</TD>" + BitValue(data, 0x10) + "<TD ALIGN=LEFT>AFH classification master</TD></TR>";
#          + "<TR><TD>bit 5 (45)</TD>" + BitValue(data, 0x20) + "<TD ALIGN=LEFT>reserved</TD></TR>"
#          + "<TR><TD>bit 6 (46)</TD>" + BitValue(data, 0x40) + "<TD ALIGN=LEFT>reserved</TD></TR>"
#          + "<TR><TD>bit 7 (47)</TD>" + BitValue(data, 0x80) + "<TD ALIGN=LEFT>reserved</TD></TR>";
        
    data = NextNBits(8);
    text += Format(" %02X", data);

        ToolTip += "<TR><TD><B>byte 6</B></TD>"
         + Format("<TD></TD><TD><B>0x%02X</B></TD></TR>", data);

#         + "<TR><TD> </TD><TD></TD><TD></TD></TR>"; 

#          + "<TR><TD>bit 0 (48)</TD>" + BitValue(data, 0x01) + "<TD ALIGN=LEFT>reserved</TD></TR>"
#          + "<TR><TD>bit 1 (49)</TD>" + BitValue(data, 0x02) + "<TD ALIGN=LEFT>reserved</TD></TR>"
#          + "<TR><TD>bit 2 (50)</TD>" + BitValue(data, 0x04) + "<TD ALIGN=LEFT>reserved</TD></TR>"
#          + "<TR><TD>bit 3 (51)</TD>" + BitValue(data, 0x08) + "<TD ALIGN=LEFT>reserved</TD></TR>"
#          + "<TR><TD>bit 4 (52)</TD>" + BitValue(data, 0x10) + "<TD ALIGN=LEFT>reserved</TD></TR>"
#          + "<TR><TD>bit 5 (53)</TD>" + BitValue(data, 0x20) + "<TD ALIGN=LEFT>reserved</TD></TR>"
#          + "<TR><TD>bit 6 (54)</TD>" + BitValue(data, 0x40) + "<TD ALIGN=LEFT>reserved</TD></TR>"
#          + "<TR><TD>bit 7 (55)</TD>" + BitValue(data, 0x80) + "<TD ALIGN=LEFT>reserved</TD></TR>";

    data = NextNBits(8);
    text += Format(" %02X ", data);

        ToolTip += "<TR><TD><B>byte 7</B></TD>"
          + Format("<TD></TD><TD><B>0x%02X</B></TD></TR>", data)

#          + "<TR><TD> </TD><TD></TD><TD></TD></TR>"

#          + "<TR><TD>bit 0 (56)</TD>" + BitValue(data, 0x01) + "<TD ALIGN=LEFT>reserved</TD></TR>"
#          + "<TR><TD>bit 1 (57)</TD>" + BitValue(data, 0x02) + "<TD ALIGN=LEFT>reserved</TD></TR>"
#          + "<TR><TD>bit 2 (58)</TD>" + BitValue(data, 0x04) + "<TD ALIGN=LEFT>reserved</TD></TR>"
#          + "<TR><TD>bit 3 (59)</TD>" + BitValue(data, 0x08) + "<TD ALIGN=LEFT>reserved</TD></TR>"
#          + "<TR><TD>bit 4 (60)</TD>" + BitValue(data, 0x10) + "<TD ALIGN=LEFT>reserved</TD></TR>"
#          + "<TR><TD>bit 5 (61)</TD>" + BitValue(data, 0x20) + "<TD ALIGN=LEFT>reserved</TD></TR>"
#          + "<TR><TD>bit 6 (62)</TD>" + BitValue(data, 0x40) + "<TD ALIGN=LEFT>reserved</TD></TR>"
          + "<TR><TD>bit 7 (63)</TD>" + BitValue(data, 0x80) + "<TD ALIGN=LEFT>Extended features</TD></TR>"

          + "</TABLE></TD></TR></TABLE></HTML>";

    AddCell("LMP_Features", text, ToolTip, color);
}

ShowFlush_Timeout(color)
{
  data = Next16Bits();
  if ( data )
    AddCell ("Flush_Timeout", Format("%d slots", data), 
             "Flush Timeout = N * 0.625 msec\nRange: 0x0001 - 0x07FF", 
             HCIcommandColor,
             select {(data > 0x07ff): _ERROR; } );
  else
    AddCell ("Flush_Timeout", "0", "No Automatic Flush. Default.", color);
}

ShowNum_Broadcast_Retran(color)
{
    AddCell("Num_Broadcast_Retran", Format("%d", NextNBits(8)), "Number of Broadcast Retransmissions", color);
}




set Hold_Mode_ActivityTable = 
[
  [ 0xFF , "Reserved for Future Use."       ],
  [ 0x00 , "Maintain current Power State."  ],
  [ 0x01 , "Suspend Page Scan."             ],
  [ 0x02 , "Suspend Inquiry Scan."          ],
  [ 0x04 , "Suspend Periodic Inquiries."    ]
];

ShowHold_Mode_Activity(color)
{
    data = NextNBits(8);
    _row = Find(Hold_Mode_ActivityTable, data);
    AddCell("Hold_Mode_Activity",  Format("0x%02X", data), _row[1], color);
}

set SCO_Flow_Control_EnableTable = 
[
  [ 0xff , "unknown value"   ],
  [ 0x00 , "SCO Flow Control is disabled.\nNo Number of Completed Packets events will be sent from the Host Controller for SCO Connection Handles." ],
  [ 0x01 , "SCO Flow Control is enabled.\nNumber of Completed Packets events will be sent from the Host Controller for SCO Connection Handles."     ]
];

ShowSCO_Flow_Control_Enable(color)
{
    data = NextNBits(8);
    _row = Find(SCO_Flow_Control_EnableTable, data);
    AddCell("SCO_Flow_Control_Enable",  Format("0x%02X", data), _row[1], color);
}

ShowLink_Supervision_Timeout(color)
{
    data = Next16Bits();
    if ( data )
      AddCell ("Link_Supervision_Timeout", Format("%d slots", data), 
               "Link_Supervision_Timeout = N * 0.625 msec (1 Baseband slot)\nRange for N: 0x0001 - 0xFFFF\nTime Range: 0.625ms - 40.9 sec\nDefault: N = 0x7D00\nLink_Supervision_Timeout = 20 sec", 
               color );
    else
      AddCell ("Link_Supervision_Timeout", "0", "No Link_Supervision_Timeout.", color);
}

set Loopback_ModeTable = 
[
  [ 0xFF , "Reserved for Future Use."   ],
  [ 0x00 , "No Loopback mode enabled."  ],
  [ 0x01 , "Enable Local Loopback."     ],
  [ 0x02 , "Enable Remote Loopback."    ]
];

ShowLoopback_Mode(color)
{
    data = NextNBits(8);
    _row = Find(Loopback_ModeTable, data);
    AddCell("Loopback_Mode",  Format("0x%02X", data), _row[1], color);
}

ShowCatcKeySize(color)
{
    data = NextNBits(8);
    AddCell("Key_Size", Format("%d", data), "", color, 
       select { ((data < 1) || (data > 16)) : _ERROR; } 
    );
}

ShowCatcKeyType(color)
{
    data = NextNBits(8);
    select {
      data == 0: AddCell("Key_Type", "Combination",  "0x00 : Combination key", color);
      data == 1: AddCell("Key_Type", "Unit",         "0x01 : Unit key", color);
      default:   AddCell("Key_Type", "Unknown",      Format("0x%02X - unknown", data), color, _ERROR);
    };
}


set LmpTestScenarioTable = [
 [ 0xFFF, "Reserved" ],
 [ 0x00 , "Pause Test Mode" ],
 [ 0x01 , "Transmitter test - 0 pattern" ],
 [ 0x02 , "Transmitter test - 1 pattern"  ],
 [ 0x03 , "Transmitter test - 1010 pattern" ],
 [ 0x04 , "Pseudorandom bit sequence" ],
 [ 0x05 , "Closed Loop Back - ACL packets" ],
 [ 0x06 , "Closed Loop Back - SCO packets" ],
 [ 0x07 , "ACL Packets without whitening" ],
 [ 0x08 , "SCO Packets without whitening" ],
 [ 0x09 , "Transmitter test - 1111 0000 pattern" ],
 [ 0xFF , "Exit Test Mode" ]
];

ShowLmpTestScenario(color)
{
    data = NextNBits(8);
    _row = Find(LmpTestScenarioTable, data);
    AddCell("TestScenario",  Format("0x%02X", data), _row[1], color);
}



set LmpHoppingModeTable = [
 [ 0xFF , "Reserved"        ],
 [ 0x00 , "Tx/Rx on a single frequency" ],
 [ 0x01 , "Europe/USA"      ],
 [ 0x03 , "France"          ],
 [ 0x05 , "Reduced hopping" ]
];

ShowLmpHoppingMode(color)
{
    data = NextNBits(8);
    _row = Find(LmpHoppingModeTable, data);
    AddCell("HoppingMode",  Format("0x%02X", data), _row[1], color);
}


ShowTxFreq(color)
{
    AddCell("TxFreq",  Format("0x%02X", NextNBits(8)), "", color);
}

ShowRxFreq(color)
{
    AddCell("RxFreq",  Format("0x%02X", NextNBits(8)), "", color);
}

ShowPowerControlMode(color)
{
    data = NextNBits(8);
    AddCell("PowerControlMode", data , select { 
       data == 0: "Fixed Tx output power"; 
       data == 1: "Adaptive power control"; 
         default: "unknown"; }, color);
}

ShowPollPeriod(color)
{
    AddCell("PollPeriod",  NextNBits(8), "", color);
}

set LmpPacketType = [
 [ 0xFF , "Reserved" ],
 [ 0x01 , "POLL" ],
 [ 0x00 , "NULL" ],
 [ 0x03 , "DM1"  ],
 [ 0x05 , "HV1"  ],
 [ 0x06 , "HV2"  ],
 [ 0x07 , "HV3"  ],
 [ 0x08 , "DV"   ],
 [ 0x04 , "DH1"  ],
 [ 0x0A , "DM3"  ],
 [ 0x0B , "DH3"  ],
 [ 0x0E , "DM5"  ],
 [ 0x0F , "DH5"  ],
 [ 0x09 , "AUX1" ]
];

ShowPacketType(color)
{
    data = NextNBits(8);
    _row = Find(LmpPacketType, data);
    AddCell("PacketType", _row[1],  Format("0x%02X", data), color);
}

ShowToken_Rate(color)
{
    data_lo = Next16Bits();
    data_hi = Next16Bits();
    text = Format("0x%04X", data_hi) + Format("%04X", data_lo);
    if (data_hi & 0x8000)
      tooltip = "Token Rate in bytes per second.";
    else 
      tooltip = Format( "%d - Token Rate in bytes per second.", data_hi << 16 | data_lo);

    AddCell("Token_Rate", text, tooltip,  color);
}

ShowPeak_Bandwidth(color)
{
    data_lo = Next16Bits();
    data_hi = Next16Bits();
    text = Format("0x%04X", data_hi) + Format("%04X", data_lo);
    if (data_hi & 0x8000)
      tooltip = "Peak Bandwidth in bytes per second.";
    else 
      tooltip = Format( "%d - Peak Bandwidth in bytes per second.", data_hi << 16 | data_lo);
   
    AddCell("Peak_Bandwidth", text, tooltip,  color);
}

ShowLatency(color)
{
    data_lo = Next16Bits();
    data_hi = Next16Bits();
    text = Format("0x%04X", data_hi) + Format("%04X", data_lo);
    if (data_hi & 0x8000)
      tooltip = "Latency in microseconds.";
    else 
      tooltip = Format( "%d - Latency in microseconds.", data_hi << 16 | data_lo);

    AddCell("Latency", text, tooltip,  color);
}

ShowDelay_Variation(color)
{
    data_lo = Next16Bits();
    data_hi = Next16Bits();
    text = Format("0x%04X", data_hi) + Format("%04X", data_lo);
    if (data_hi & 0x8000)
      tooltip = "Delay Variation in microseconds.";
    else 
      tooltip = Format( "%d - Delay Variation in microseconds.", data_hi << 16 | data_lo);

    AddCell("Delay_Variation", text, tooltip,  color);
}

ShowCatcDataPath(color)
{
    data = NextNBits(8);
    select {
      data== 0:
      {
         AddCell("Data_Path", "PCM", "0 - PCM CODEC is used to send and receive voice data for the current SCO connection.", color);
      }
      data == 1:
      {
         AddCell("Data_Path", "HCI", "1 - voice data is sent according to the Data_Pattern parameter.\nThe received voice data is routed to the PCM CODEC.", color);
      }
      default:
      {
         AddCell("Data_Path", "???", Format("0x%02X - unknown meaning", data), color);
      }
    };
}

ShowTciTxJitter(color)
{
    data = NextNBits(8);

    jitter_05_text = "us";
    if (data & 0x40)
    {
      if ( (data & 0x80) == 0 )
      {
        jitter_05_text = ".5us";
        data =  data ^ 0x40;
      }
    }
    else
    {
      if (data & 0x80)
      {
        jitter_05_text = ".5us";
        data =  data | 0x40;
      }
    }

    if (data & 0x80)
      data = 0xFFFFFF00 | data;
    AddCell("TxJitter", Format("%d", data) + jitter_05_text, "", color);
}

ShowCatcParkMode(color)
{
    data = NextNBits(8);
    select {
      data == 0: AddCell("ParkMode", "PM_ADDR", "0 - parking by PM_ADDR",  color);
      data == 1: AddCell("ParkMode", "BD_ADDR", "1 - parking by BD_ADDR",  color);
      default:   AddCell("ParkMode", Format("0x%02X", data), "reserved value",  color, _ERROR);
    };
}

ShowMaxSlot(color)
{
    AddCell("MaxSlot", Format("%d", NextNBits(8)), "Maximal number of slots", color);
}


ShowFlags(color)
{
    AddCell("Flags", Format("0x%02X", NextNBits(8)),"Reserved for Future Use.", color);
}

ShowFlow_direction(color)
{
    data = NextBits(8);
    select {
      data == 0 : AddCell("Flow_direction", "Outgoing", "0 - Outgoing Flow i.e. traffic send over the ACL connection",  color);
      data == 1 : AddCell("Flow_direction", "Incoming", "1 - Incoming Flow i.e. traffic received over the ACL connection",  color);
      default   : AddCell("Flow_direction", Format("0x%02X", data) , "Reserved value.",  color);
    };
}

ShowToken_Bucket_Size(color)
{
    AddCell("Token Bucket Size", Format("0x%08X", Next32Bits()), "Token Bucket Size in bytes", color);
}

ShowPage(color)
{
    page = NextNBits(8);
    AddCell("Page",  Format("%d", page), "", color);
}

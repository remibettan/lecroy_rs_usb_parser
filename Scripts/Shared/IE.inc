###############################################################################
#                                                                             #  
#  FILENAME: IE.inc                                                           #
#                                                                             #
#  Copyright (C) 2005 LeCroy Corporation PSG Group ( CATC )                   #
#                                                                             #
#  DESCRIPTION                                                                #
#    This Information Element definition file is supplied by LeCroy.          #
#    This file defines Wireless USB Channel Information Elements.             #
#                                                                             #
#    Version Information:                                                     #
#    01/13/2006  Initial Created JZ  Created according to WUSB Spec 1.0       # 
###############################################################################

%include "IE_Colors.inc"

 
##//ViewSettings
#############################################################################
#                               View Settings                               #
#############################################################################
#
#    In this section user can set up which fields are to be shown and 
#    which are to be hidden in expanded and collapsed states.
#    Zero-value everywhere means that fields will not be shown,
#    otherwise means opposite.
#


# ----------------------- All Field View Settings ---------------------------
#   These settings have priority above separate field View Settings in
#   expanded state ONLY.
#   In order separate field View Settings to work properly
#   BOTH All Field View Settings should be set to 0.
#
#   Due to the fact that ViewAll-setting and HideAll-setting are 
#   exceptive proDecodedBytess - ViewAll has been set a higher priority.
#
#
#  Prefix =  "IE";
# ---------------------------------------------------------------------------

const IE_ViewAll              = 0;
const IE_HideAll              = 0;
# ---------------------------------------------------------------------------


# -----------------------  Separate Field View Settings ---------------------
# The FIRST value in list-variables defines if the field is to be shown or
# hidden in COLLAPSED state. 
# 0 - means the field is to be shown.
# 1 - means the field is to be hidden.
# 
# The SECOND value in list-variables defines if the field is to be shown or
# hidden in EXPANDED state. 
# 0 - means the field is to be shown.
# 1 - means the field is to be hidden.
#
# i.e.  const IE_Field = [0, 1]; - means that field 'Field' will be hidden
# in collapsed state and will be shown in expanded state. 
#


#                   [collapsed, expanded]   
const IE_Length           = [0, 1];
const IE_IE_Id             = [1, 1];
const IE_Undecoded_Bytes   = [0, 1];

set WUSBChannelIEIdentifiersTable =
[
    [0x00, "Reserved_IE"           , IE_Reserved_IE_Color           ],
    [0x80, "WCTA_IE"               , IE_WCTA_IE_Color               ],
    [0x81, "WCONNECTACK_IE"        , IE_WCONNECTACK_IE_Color        ],
    [0x82, "WHOSTINFO_IE"          , IE_WHOSTINFO_IE_Color          ],
    [0x83, "WCHCHANGEANNOUNCE_IE"  , IE_WCHCHANGEANNOUNCE_IE_Color  ],
    [0x84, "WDEV_DISCONNECT_IE"    , IE_WDEV_DISCONNECT_IE_Color    ],
    [0x85, "WHOST_DISCONNECT_IE"   , IE_WHOST_DISCONNECT_IE_Color   ],
    [0x86, "WRELEASE_CHANNEL_IE"   , IE_WRELEASE_CHANNEL_IE_Color   ],
    [0x87, "WWORK_IE"              , IE_WWORK_IE_Color              ],
    [0x88, "WCHANNEL_STOP_IE"      , IE_WCHANNEL_STOP_IE_Color      ],
    [0x89, "WDEV_KEEPALIVE_IE"     , IE_WDEV_KEEPALIVE_IE_Color     ],
    [0x8A, "WISOCH_DISCARD_IE"     , IE_WISOCH_DISCARD_IE_Color     ],
    [0x8B, "WRESETDEVICE_IE"       , IE_WRESETDEVICE_IE_Color       ],
    [0x8C, "WXMIT_PACKET_ADJUST_IE", IE_WXMIT_PACKET_ADJUST_IE_Color]
];

set BASE = 0;
set DecodedBytes = 0;
set lastIE = null;
set bLength = 0;
set IEId = 0;
set IEColor = 0xD5A7C9;
set lengthStr = "wLength";
set MaxBytes = 0;

#####################################################################
#    This function will decode the incoming data stream             #
#    according to the WUSB spec 1.0 Chapter 7.5.                    #
#                                                                   #
#    Return : total number of bytes this function is processed      #
#####################################################################

ShowIE()
{    
    UnitDecoderInit("IE"); 
    #we first need to make sure wLength do not exceed the length of the payload
    MaxBytes = in.DataLength - GetBitOffset() / 8;
    if (wLength <= MaxBytes)
    {
        MaxBytes = wLength;
        lengthStr = "wLength";
    }
    else
    {
        err_tooltip = Format("wLength %d is longer than the data payload length", wLength);
        err_tooltip += Format(" %d \nSo data payload length will be used to replace wLength", MaxBytes);
        AddPLCellMonoNoDlg("wLength",Format("%d",wLength), AddErrorTooltip(), _ERROR);
        lengthStr = "Payload Length";
    }

    DecodedBytes = 0;
    lastIE = null;
    while (DecodedBytes < MaxBytes)
    {
        if (lastIE == "WHOSTINFO_IE")
        {
            err_tooltip = "WHOSTINFOR IE must be the last IE in an MMC";
            AddPLCellMonoNoDlg("Ordering","Error",AddErrorTooltip(), _ERROR);
        }
        AddDecSeparator();
        bLength = NextNBits_(8);
        
        if (bLength >1 && MaxBytes > DecodedBytes + 1)
        {
            IEId = PeekNBits(8);
	        row  = Find(WUSBChannelIEIdentifiersTable, IEId);
	        FieldColor = row[2];
	        
	        if( in.PrepareFldsForDlg )
                AddCaptionToDlg("IE", row[1], "", null, VS[COLLAPSED]);
        }
        else
        {
            FieldColor = ERROR_COLOR;
        }
        
        if ( bLength <= 0)
        {
            err_tooltip = "Illegal bLength value, nothing will be decoded!";
            AddPayLoadCell("Length", Format("%d", bLength), AddErrorTooltip(), _ERROR);
            ShowUndecodedBytes ( MaxBytes - DecodedBytes);
            bLength = MaxBytes;
            DecodedBytes = MaxBytes;
        }
        else if (bLength <= (MaxBytes - DecodedBytes)) #Normal
        {
            AddPayLoadCell("Length", Format("%d", bLength), "Length of the IE");
            bLength += DecodedBytes;
            DecodedBytes ++;
        }
        else # bLength > (MaxBytes - DecodedBytes)
        {
            err_tooltip = "The bLength value exceed the actual length of the data payload!\n";
            err_tooltip += Format("The actual length %d will be used as the length of the request\n", MaxBytes - DecodedBytes);
            AddPayLoadCell("Length", Format("%d", wLength), AddErrorTooltip(), _ERROR);
            bLength = MaxBytes;
            DecodedBytes ++;
        }
        
        if (DecodedBytes < bLength)
        {
            IEId = NextNBits_(8);
            DecodedBytes ++;
            row  = Find(WUSBChannelIEIdentifiersTable, IEId);
            AddPayLoadCell("IE Id", row[1], Format("IE type 0x%02X : ",IEId) + row[1]);
            Call( row[1] );
            lastIE = row[1];
        }
    }
    return DecodedBytes;
}

##################################################################
#                  Unknow IE Defination                          #
##################################################################
Reserved_IE()
{
    if (DecodedBytes < bLength)
    {
        ShowUndecodedBytes(bLength - DecodedBytes);
        DecodedBytes = bLength;
    }
  
}




##################################################################
#                  WCONNECTACK_IE Defination                     #
##################################################################
#                   [collapsed, expanded]   
const IE_CDID             = [0, 1];
const IE_Device_Addr      = [0, 1];
WCONNECTACK_IE()
{
    ConnectAckID = 0;
    while ( bLength > DecodedBytes ) # max limit for connection ack?
    {        
        AddPLCellMonoNoDlg("ConnectAck ID",Format("%d", ConnectAckID), Format("ConnectAct Bloc number %d", connectAckID));
        
        if ( bLength > DecodedBytes + 16 )
        {
            AddPayLoadCell("CDID", Get16BytesData() , "Connection Device ID");
            DecodedBytes += 16;
        }
        else if ( bLength > DecodedBytes )
        {
            AddExtraBytesPayloadCell (bLength - DecodedBytes);
            DecodedBytes = bLength;
        }
        
        if (bLength > DecodedBytes + 1)
        {
            bDeviceAddress = NextNBits_(8);
            AddPayLoadCell("Addr", Format("%d", bDeviceAddress), "A new device address for the associating device");
            DecodedBytes ++;
        }
        if (bLength > DecodedBytes + 1)
        {
            PLReservedCheck(8);
            DecodedBytes ++;
        }
        ConnectAckID ++;
    }
}
        

##################################################################
#                  WHOSTINFO_IE Defination                       #
##################################################################
#                                     [collapsed, expanded]   
const IE_Connection_Availability            = [0, 1];
const IE_P2P_DRD_Capable                    = [0, 1];
const IE_MAC_Strm_Indx                      = [0, 1];
const IE_CHID                               = [0, 1];

set ConnectionAvailabilityTable =
[
    [0x0, "Reconnect Only", "Host is available only for reconnect notifications"               ],
    [0x1, "Limited"       , "Host is only available for connections and reconnections"         ],
    [0x2, "Reserved"      , "Reserved"                                                         ],
    [0x3, "ALL"           , "Host is open for connect, reconnect and new connect notifications"]
];


WHOSTINFO_IE()
{    
    if (bLength > DecodedBytes + 2)
    {
        ConnectionAvailability = NextNBits_(2);
        row = Find(ConnectionAvailabilityTable, ConnectionAvailability);
        AddPayLoadCell("Connection Availability", row[1], row[2]);
        
        Capable = NextNBits_(1);
        if (Capable)
            tooltip = "The host is Peer to Peer DRD capable";
        else
            tooltip = "The host is not Peer to Peer DRD capable";
        AddPayLoadCell("P2P DRD Capable", Format("0x%X", Capable), tooltip);
        
        StreamIndex = NextNBits_(3);
        AddPayLoadCell("MAC Strm Indx", Format("0x%X", StreamIndex), "MAC Layer Stream Index");
        
        PLReservedCheck(10);
        DecodedBytes += 2;
    }
    else if (bLength > DecodedBytes )
    {
        AddExtraBytesPayloadCell (bLength - DecodedBytes);
        DecodedBytes = bLength;
    }
    
    if ( bLength >= DecodedBytes + 16 )
    {
        AddPayLoadCell("CHID", Get16BytesData() , "Connection Host ID");
        DecodedBytes += 16;
    }
    else if ( bLength > DecodedBytes )
    {
        AddExtraBytesPayloadCell (bLength - DecodedBytes);
        DecodedBytes = bLength;
    }
    if (bLength > DecodedBytes)
    {
        ShowUndecodedBytes(bLength - DecodedBytes);
        DecodedBytes = bLength;
    }
}


##################################################################
#              WCHCHANGEANNOUNCE_IE Defination                   #
##################################################################
#                                     [collapsed, expanded]   
const IE_Chnl_Num                           = [0, 1];
const IE_Switch_Time                        = [0, 1];

ChannelTimeDecoding()
{
    val = NextNBits_(24);
    if (LittleEndian == 1)
    {
        ReceptionTime = ((val & 0xFF0000) >> 16)  |
               (val & 0x00FF00)          |
               ((val & 0x0000FF) << 16);
    }
    else
    {
        ReceptionTime = val;
    }
    return Format ("0x%05X:%02X", ReceptionTime>> 7, ReceptionTime & 0x7F);
}


WCHCHANGEANNOUNCE_IE()
{
    if (bLength > DecodedBytes)
    {
        bNewPHYChannelNumber = NextNBits_(8);
        AddPayLoadCell("Chnl Num", Format("0x%02X", bNewPHYChannelNumber), "The PHY channel number where the host is moving the WUSB cluster");
        DecodedBytes ++;
    }
    
    if (bLength >= DecodedBytes + 3)
    {
        SwitchTime = ChannelTimeDecoding();
        AddPayLoadCell("Switch Time", SwitchTime, "The time at which the WUSB channel will switch");
        DecodedBytes += 3;
    }
    else if (bLength > DecodedByets)
    {
        AddExtraBytesPayloadCell (bLength - DecodedBytes);
        DecodedBytes = bLength;
    }
    if (bLength > DecodedBytes)
    {
        ShowUndecodedBytes(bLength - DecodedBytes);
        DecodedBytes = bLength;
    }    
}


##################################################################
#               WDEV_DISCONNECT_IE Defination                    #
##################################################################
#                                     [collapsed, expanded]   
const IE_Addr                               = [0, 1];

WDEV_DISCONNECT_IE ()
{
    index = 0;
    for ( ;DecodedBytes < bLength && index < 128; DecodedBytes++)
    {
        bDeviceAddress = NextNBits_(8);
        AddPayLoadCell("Addr", Format("%d", bDeviceAddress), Format("Device Address %d",index));
        index ++;
    }
    if (bLength > DecodedBytes)
    {
        ShowUndecodedBytes(bLength - DecodedBytes);
        DecodedBytes = bLength;
    }
    
}
##################################################################
#               WHOST_DISCONNECT_IE Defination                   #
##################################################################
WHOST_DISCONNECT_IE ()
{
    if (bLength > DecodedBytes)
    {
        ShowUndecodedBytes(bLength - DecodedBytes);
        DecodedBytes = bLength;
    }   
}             
        
##################################################################
#               WRELEASE_CHANNEL_IE Defination                   #
##################################################################
#                                     [collapsed, expanded]   
const IE_Start                                    = [0, 1];
const IE_Duration                                 = [0, 1];
const IE_UDRB                                     = [0, 1];


WRELEASE_CHANNEL_IE ()
{
    index = 0;
    while (bLength > DecodedBytes)
    {
        AddSeparator();
        AddPLCellMonoNoDlg("UDRB #", Format("%d",index), "UDRB index");
        if (bLength > DecodedBytes + 2)
        {
            wStart = NextDataWord_();
            AddPayLoadCell("Start", Format("0x%04X",wStart), "WUSB channel time at which the addressed\ndevice must transmit a UDR control packet");
            DecodedBytes += 2;
        }
        else if (bLength > DecodedBytes)
        {
            AddExtraBytesPayloadCell (bLength - DecodedBytes);
            DecodedBytes = bLength;
        }
        
        if (bLength >= DecodedBytes + 2)
        {
            wDurationValue = NextDataWord_();
            AddPayLoadCell("Duration", Format("0x%04X",wDurationValue), "This is a timestamp proviede by the host");
            DecodedBytes += 2;
        }
        else if (bLength > DecodedBytes)
        {
            AddExtraBytesPayloadCell (bLength - DecodedBytes);
            DecodedBytes = bLength;
        }
        
        if (bLength > DecodedBytes)
        {
            bDeviceAddress = NextNBits_(8);
            AddPayLoadCell("Addr", Format("%d", bDeviceAddress), "Device address of a device that should transmit\nthe UDR packet at start time");
            DecodedBytes ++;
        }
        
        if (bLength > DecodedBytes)
        {
            PLReservedCheck(8);
            DecodedBytes ++;
        }
        index ++;
    }
        
}         
    
##################################################################
#                       WWORK_IE Defination                      #
##################################################################
#                                     [collapsed, expanded]   
const IE_Wrk_Png                            = [0, 1];

WWORK_IE ()
{
    index = 0;
    for ( ;DecodedBytes < bLength && index < 128; DecodedBytes++)
    {
        AddSeparator();
        bDeviceAddress = NextNBits_(7);
        AddPayLoadCell("Addr", Format("%d", bDeviceAddress), Format("Device Address %d", index));
        WorkPending = NextNBits_(1);
        if (WorkPending)
        {
            text = "Yes";
            tooltip = "There is work pending for the device";
        }
        else
        {
            tooltip = "There are NO work pending for the device";
            text = "No";
        }
        AddPayLoadCell("Wrk Png", text, tooltip);
        index ++;
    }
    if (DecodedBytes < bLength)
    {
        ShowUndecodedBytes(bLength - DecodedBytes);
        DecodedBytes = bLength;
    }
}

##################################################################
#                   WCHANNEL_STOP_IE Defination                  #
##################################################################
#                                     [collapsed, expanded]   
const IE_Remote_Wakeup                      = [0, 1];
const IE_Stop_Time                          = [0, 1];

WCHANNEL_STOP_IE()
{
    if (bLength > DecodedBytes)
    {
        RemoteWakeup = NextNBits_(1);
        if (RemoteWakeup)
            tooltip = "The host will be \"polling\" for Remote Wakeup";
        else
            tooltip = "The host will not be \"polling\" for Remote Wakeup"; 
        AddPayLoadCell("Remote Wakeup", Format("0x%X", RemoteWakeup), tooltip);
        PLReservedCheck(7);
        DecodedBytes ++;
    }
    
    if (bLength >= DecodedBytes + 3)
    {
        StopTime = ChannelTimeDecoding();
        AddPayLoadCell("Stop Time", StopTime, "The time at which the Wireless USB channel will stop");
        DecodedBytes += 3;
    }
    else if (bLength > DecodedByets)
    {
        AddExtraBytesPayloadCell (bLength - DecodedBytes);
        DecodedBytes = bLength;
    }
    if (DecodedBytes < bLength)
    {
        ShowUndecodedBytes(bLength - DecodedBytes);
        DecodedBytes = bLength;
    }
}

##################################################################
#               WDEV_KEEPALIVE_IE Defination                     #
##################################################################


WDEV_KEEPALIVE_IE ()
{
    index = 0;
    for ( ;DecodedBytes < bLength && index < 128; DecodedBytes++)
    {
        bDeviceAddress = NextNBits_(8);
        AddPayLoadCell("Addr", Format("%d", bDeviceAddress), Format("Device Address %d", index));
        index ++;
    }
    if (DecodedBytes < bLength)
    {
        ShowUndecodedBytes(bLength - DecodedBytes);
        DecodedBytes = bLength;
    }
    
}

##################################################################
#                   WISOCH_DISCARD_IE Defination                 #
##################################################################
#                                     [collapsed, expanded]   
const IE_Discard_ID                         = [0, 1];
const IE_USB_Endp                           = [0, 1];
const IE_Rcv_Wnd_Pos                        = [0, 1];
const IE_Num_Discard_Pkts                   = [0, 1];
const IE_Num_Discard_Segs                   = [0, 1];
const IE_Dev_Rcv_Wnd                        = [0, 1];

WISOCH_DISCARD_IE()
{
    # WISOCH_DISCRAD_IE has to be the first IE
    if (lastIE != null && lastIE != "WISOCH_DISCRAD_IE")
    {
        err_tooltip = "WISOCH_DISCRAD_IE need to be the first IE in an MMC";
        AddPLCellMonoNoDlg("Ordering","Error",AddErrorTooltip(), _ERROR);
    }
    if (bLength > DecodedBytes)
    {
        bDiscardID = NextNBits_(8);
        AddPayLoadCell("Discard ID", Format("0x%02X", bDiscardID), "An ID number of the discard IE");
        DecodedBytes ++;
    }
    
    if (bLength > DecodedBytes)
    {
        bDeviceAddress = NextNBits_(8);
        AddPayLoadCell("Addr", Format("%d", bDiscardID), "Device Address");
        DecodedBytes ++;
    }
    
    if (bLength > DecodedBytes)
    {
        USBEP = NextNBits_(4);
        AddPayLoadCell("USB Endp", Format("0x%X", USBEP), "USB Endpoint Number");
        PLReservedCheck(4);
        DecodedBytes ++;
    }

    if (bLength > DecodedBytes)
    {
        bFRWP = NextNBits_(8);
        AddPayLoadCell("Rcv Wnd Pos", Format("0x%02X", bFRWP), "The sequence number of the first position\nin the bmDeviceReceiveWindow field");
        DecodedBytes ++;
    }
    
    if (bLength >= DecodedBytes + 2)
    {
        wNumDP = NextDataWord_();
        AddPayLoadCell("Num Discard Pkts", Format("0x%04X",wNumDP), "The number of discarded packets");
        DecodedBytes += 2;
    }
    else if (bLength > DecodedByets)
    {
        AddExtraBytesPayloadCell (bLength - DecodedBytes);
        DecodedBytes = bLength;
    }
    
    if (bLength >= DecodedBytes + 2)
    {
        wNumDS = NextDataWord_();
        AddPayLoadCell("Num Discard Segs", Format("0x%04X",wNumDS), "The number of discarded isochronous segments");
        DecodedBytes += 2;
    }
    else if (bLength > DecodedByets)
    {
        AddExtraBytesPayloadCell (bLength - DecodedBytes);
        DecodedBytes = bLength;
    }

    if (bLength >= DecodedBytes + 4)
    {
        bmDRW = NextDataDWord_();
        AddPayLoadCell("Dev Rcv Wnd", Format("0x%08X",bmDRW), "Bitmap indicating the sequence numbers that the host\nexpects to be active in the device receive window");
        DecodedBytes += 4;
    }
    else if (bLength > DecodedByets)
    {
        AddExtraBytesPayloadCell (bLength - DecodedBytes);
        DecodedBytes = bLength;
    }
    
    if (DecodedBytes < bLength)
    {
        ShowUndecodedBytes(bLength - DecodedBytes);
        DecodedBytes = bLength;
    }
}

##################################################################
#                  WRESETDEVICE_IE Defination                    #
##################################################################
WRESETDEVICE_IE()
{
    index = 0;
    while ( bLength > DecodedBytes)
    {        
        if ( bLength >= DecodedBytes + 16 )
        {
            AddPayLoadCell("CDID", Get16BytesData() , Format("Connection Device %d ID", index));
            DecodedBytes += 16;
        }
        else if ( bLength > DecodedBytes )
        {
            AddExtraBytesPayloadCell (bLength - DecodedBytes);
            DecodedBytes = bLength;
        }
        index ++;
    }
}
  
##################################################################
#               WXMIT_PACKET_ADJUST_IE Defination                #
##################################################################
#                                     [collapsed, expanded]   
const IE_Trans_Adj                          = [0, 1];


WXMIT_PACKET_ADJUST_IE()
{
    if (bLength > DecodedBytes)
    {
        bTransmitAdjustment = NextNBits_(8);
        AddPayLoadCell("Trans Adj", Format("%d 탎", bTransmitAdjustment), "Number of additional microseconds\n(above 64K) that a DBD should include\nin the repeat interval when doing\ndirected packet transmission");
        DecodedBytes ++;
    }
    
    if (bLength > DecodedBytes)
    {
        PLReservedCheck(8);
        DecodedBytes ++;
    }
    if (DecodedBytes < bLength)
    {
        ShowUndecodedBytes(bLength - DecodedBytes);
        DecodedBytes = bLength;
    }
}  
  
##################################################################
#                       WCTA_IE Defination                       #
##################################################################
#                                     [collapsed, expanded]   
const IE_Setup_Flag                         = [0, 1];
const IE_CTA_Type                           = [1, 1];
const IE_Dir                                = [0, 1];
const IE_Device_ID                          = [0, 1];
const IE_TX_Pkt_Size                        = [0, 1];
const IE_Ctrl_Stat_Flg                      = [0, 1];
const IE_PHY_TX_Rate                        = [0, 1];
const IE_Trans_Power                        = [0, 1];
const IE_Trans_Burst_Size                   = [0, 1];
const IE_Preamble_Policy                    = [0, 1];
const IE_bvDINAck                           = [0, 1];
const IE_Num_Slots                          = [0, 1];



set CTATypeTable =
[
    [0x3, "ReservedCTA", IE_ReservedCTA_Color],
    [0x0, "WDRCTA"     , IE_WDRCTA_Color     ],
    [0x1, "WDTCTA"     , IE_WDTCTA_Color     ],
    [0x2, "WDNTSCTA"   , IE_WDNTSCTA_Color   ]
];

set PHY_TXRateTable =
[
    [0xFF, "Reserved"  ],
    [0x00, "53.3 Mb/s" ],
    [0x01, "80 Mb/s"   ],
    [0x02, "106.7 Mb/s"],
    [0x03, "160 Mb/s"  ],
    [0x04, "200 Mb/s"  ],
    [0x05, "320 Mb/s"  ],
    [0x06, "400 Mb/s"  ],
    [0x07, "480 Mb/s"  ]
];
    
set PreamblePolicyTable =
[
    [0xF, "Unknown"],
    [0x0, "Use only standard preambles"],
    [0x1, "Every 2nd packet"],
    [0x2, "Every 4th packet"],
    [0x3, "Every 8th packet"]
];


WCTA_IE()
{
    if (lastIE != null && lastIE != "WISOCH_DISCRAD_IE" && lastIE != "WCTA_IE")
    {
        err_tooltip = "WCTA_IE need to be the first or following the WISOCH_DISCRAD_IE in an MMC\nLast IE is ";
        err_tooltip += lastIE;
        AddPLCellMonoNoDlg("Ordering","Error",AddErrorTooltip(), _ERROR);
    }
    while (bLength > DecodedBytes)
    {
        
        AddSeparator();
        bmAttributes = PeekNBits(8);
        CTAType = bmAttributes & 0x03;
        row = Find(CTATypeTable, CTAType);
        FieldColor = row[2];
        Call(row[1]);
    }
}   

ReservedCTA()
{
    bmAttributes = PeekNBits(8);
    CTAType = bmAttributes & 0x03;
    AddPLCellMonoNoDlg("CTA Type", "Reserved", Format("CTA Type 0x%X : Reserved", CTAType));
    ShowUndecodedBytes(bLength - DecodedBytes);
    DecodedBytes = bLength;
}


WDRCTA()
{
    USBEP = NextNBits_(4);
    AddPayLoadCell("USB Endp", Format("0x%X", USBEP), "USB Endpoint Number");
    PLReservedCheck(1);
    SetupFlag = NextNBits_(1);
    AddPayLoadCell("Setup Flag", Format("0x%X", SetupFlag), "Setup Flag");
    CTAType = NextNBits_(2);
    row = Find(CTATypeTable, CTAType);
    AddPayLoadCell("CTA Type", row[1], Format("CTA Type 0x%X :", CTAType) + row[1]);
    DecodedBytes ++;
    
    if (bLength >= DecodedBytes + 2)
    {
        wStart = NextDataWord_();
        AddPayLoadCell("Start", Format("%d 탎", bStart) , "The value is measured from the beginning of the\npreamble of the MMC packet where this WxCTA\n Block is transmitted");
        DecodedBytes +=2;
    }
    else if ( bLength > DecodedBytes )
    {
        AddExtraBytesPayloadCell (bLength - DecodedBytes);
        DecodedBytes = bLength;
    }
    
    if (bLength > DecodedBytes)
    {
        bDeviceID = NextNBits_(8);
        AddPayLoadCell("Device ID", Format("0x%02X", bDeviceID), "Device Address of the Wireless USB device");
        DecodedBytes ++;
    }
}

WDTCTA()
{
    USBEP = NextNBits_(4);
    AddPayLoadCell("USB Endp", Format("0x%X", USBEP), "USB Endpoint Number");
    Direction = NextNBits_(1);
    if (Direction)
        str = "IN";
    else
        str = "OUT";
    AddPayLoadCell("Dir", str, "Which device endpoint number should transmit during the time slot");
    SetupFlag = NextNBits_(1);
    AddPayLoadCell("Setup Flag", Format("0x%X", SetupFlag), "Setup Flag");
    CTAType = NextNBits_(2);
    row = Find(CTATypeTable, CTAType);
    AddPayLoadCell("CTA Type", row[1], Format("CTA Type 0x%X :", CTAType) + row[1]);
    DecodedBytes ++;
    
    if (bLength >= DecodedBytes + 2)
    {
        wStart = NextDataWord_();
        AddPayLoadCell("Start", Format("%d 탎", bStart) , "The value is measured from the beginning of the\npreamble of the MMC packet where this WxCTA\n Block is transmitted");
        DecodedBytes +=2;
    }
    else if ( bLength > DecodedBytes )
    {
        AddExtraBytesPayloadCell (bLength - DecodedBytes);
        DecodedBytes = bLength;
    }
    
    if (bLength > DecodedBytes)
    {
        bDeviceID = NextNBits_(8);
        AddPayLoadCell("Device ID", Format("0x%02X", bDeviceID), "Device Address of the Wireless USB device");
        DecodedBytes ++;
    }
    
    if (bLength >= DecodedBytes + 4)
    {
        TXPacketSize = NextNBits_(15);
        AddPayLoadCell("TX Pkt Size", Format("0x%04X", TXPacketSize) , "The Max size of the data payloads a device must\nuse for packet transmissions during the data phase");
        
        ControlStatusflg = NextNBits_(1);
	AddPayLoadCell("Ctrl Stat Flg", Format("0x%X", ControlStatusflg) , "The associated protocol time slot is for a status stage handshake if 1");
	
        PHY_TXRate = NextNBits_(5);
        row = Find(PHY_TXRateTable, PHY_TXRate);
        AddPayLoadCell("PHY TX Rate", row[1] , Format("The PHY_TX rate 0x%02X :", PHY_TXRate) + row[1]);
        
        TransmitPower = NextNBits_(3);
        AddPayLoadCell("Trans Power", Format("0x%X", TransmitPower) , "This value selects the transmit power level\nthe device must use to tranmit data packets\nduring the data phase protocol time slot");
        
        TransBurstSize = NextNBits_(5);
        AddPayLoadCell("Trans Burst Size", Format("0x%02X", TransBurstSize) , "This field is used by the host to modify the\nconfigured burst size for the currenttransaction");
        
        
        PreamblePolicy = NextNBits_(3);
        row = Find(PreamblePolicyTable,PreamblePolicy);
        AddPayLoadCell("Preamble Policy", row[1] , Format("The value is 0x%X :", PreamblePolicy) + row[1]);

        DecodedBytes +=4;
    }
    else if ( bLength > DecodedBytes )
    {
        AddExtraBytesPayloadCell (bLength - DecodedBytes);
        DecodedBytes = bLength;
    }

    if (bLength >= DecodedBytes + 4)
    {
        bvDINAck = NextDataDWord_();
        AddPayLoadCell("bvDINAck", Format("0x%08X", bvDINAck) , "Data burst acknowledgement bit vector");
        DecodedBytes +=4;
    }
    else if ( bLength > DecodedBytes )
    {
        AddExtraBytesPayloadCell (bLength - DecodedBytes);
        DecodedBytes = bLength;
    }
}


WDNTSCTA()
{
    PLReservedCheck(6);
    CTAType = NextNBits_(2);
    row = Find(CTATypeTable, CTAType);
    AddPayLoadCell("CTA Type", row[1], Format("CTA Type 0x%X :", CTAType) + row[1]);
    DecodedBytes ++;
    
    if (bLength >= DecodedBytes + 2)
    {
        wStart = NextDataWord_();
        AddPayLoadCell("Start", Format("%d 탎", bStart) , "The value is measured from the beginning of the\npreamble of the MMC packet where this WxCTA\n Block is transmitted");
        DecodedBytes +=2;
    }
    else if ( bLength > DecodedBytes )
    {
        AddExtraBytesPayloadCell (bLength - DecodedBytes);
        DecodedBytes = bLength;
    }
    
    if (bLength > DecodedBytes)
    {
        bNumslots = NextNBits_(8);
        AddPayLoadCell("Num Slots", Format("0x%02X", bNumslots), "The raw number of notification message time slots available in the DNTS");
        DecodedBytes ++;
    }
}
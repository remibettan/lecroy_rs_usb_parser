#******************************************************************************
#
#  FILENAME: CommunicationDescriptors.inc
#
#  Copyright (C) 2006 LeCroy Corporation
#
#  DESCRIPTION
#    This descriptor definition file is supplied by LeCroy.
#    This file defines standard USB Communication descriptors.
#    File version is 1.0.
#
#    03/13/2007  Updated for Wireless Mobile Communication Devices Specification
#                Version 1.0. Also replaced all tabs w/ spaces and added
#                appropriate indentation for decode file. Also fixed some typos 
#                (AddEntry function called instead of AddByteEntry, etc.) - RK
#   
#******************************************************************************
set CommunicationDescriptorTypeTable =
[
      [ 0xFF, Illegal],
      [ 0x24, "COMM_CS_INTERFACE"],
      [ 0x25, "COMM_CS_ENDPOINT"]
];

set bLength = 0;
set DescriptorSubTypeTable =
[
      [ 0xFF, "RESERVED",                               "Reserved"],
      [ 0x00, "HEADER_FUNCTIONAL",                      "Header Functional Descriptor"],
      [ 0x01, "CALL_MANAGEMENT_FUNCTIONAL",             "Call Management Functional Descriptor"],
      [ 0x02, "ABSTRACT_CONTROL_MANAGEMENT_FUNCTIONAL", "Abstract Control Management Functional Descriptor"],
      [ 0x03, "DIRECT_LINE_MANAGEMENT_FUNCTIONAL",      "Direct Line Management Functional Descriptor"],
      [ 0x04, "TELEPHONE_RINGER_FUNCTIONAL",            "Telephone Ringer Functional Descriptor"],
      [ 0x05, "REPORTING_CAPABILITIES_FUNCTIONAL",      "Telephone Call and Line State Reporting Capabilities Functional Descriptor"],
      [ 0x06, "UNION_FUNCTIONAL",                       "Union Functional Descriptor"],
      [ 0x07, "COUNTRY_SELECTION_FUNCTIONAL",           "Country Selection Functional Descriptor"],
      [ 0x08, "TELEPHONE_OPERATIONAL_MODES_FUNCTIONAL", "Telephone Operational Modes Functional Descriptor"],
      [ 0x09, "USB_TERMINAL_FUNCTIONAL",                "USB Terminal Functional Descriptor"],
      [ 0x0A, "NETWORK_CHANNEL_TERMINAL",               "Network Channel Terminal Descriptor"],
      [ 0x0B, "PROTOCOL_UNIT_FUNCTIONAL",               "Protocol Unit Functional Descriptor"],
      [ 0x0C, "EXTENSION_UNIT_FUNCTIONAL",              "Extension Unit Functional Descriptor"],
      [ 0x0D, "NULTI_CHANNEL_MANAGEMENT_FUNCTIONAL",    "Multi-Channel management Functional Descriptor"],
      [ 0x0E, "CAPI_CONTROL_MANAGEMENT_FUNCTIONAL",     "CAPI Control Management Functional Descriptor"],
      [ 0x0F, "ETHERNET_NETWORKING_FUNCTIONAL",         "Ethernet Networking Functional Descriptor"],
      [ 0x10, "ATM_NETWORKING_FUNCTIONAL",              "ATM Networking Functional Descriptor"],
      [ 0x11, "WIRELESS_HANDSET_CONTROL_FUNCTIONAL",    "Wireless Handset Control Model Functional Descriptor"],
      [ 0x12, "MDLM_FUNCTIONAL",                        "Mobile Direct Line Model Functional Descriptor"],
      [ 0x13, "MDLM_DETAIL_FUNCTIONAL",                 "MDLM Detail Functional Descriptor"],
      [ 0x14, "DEVICE_MANAGEMENT_FUNCTIONAL",           "Device Management Model Functional Descriptor"],
      [ 0x15, "OBEX_FUNCTIONAL",                        "OBEX Functional Descriptor"],
      [ 0x16, "COMMAND_SET_FUNCTIONAL",                 "Command Set Functional Descriptor"],
      [ 0x17, "COMMAND_SET_DETAIL_FUNCTIONAL",          "Command Set Detail Functional Descriptor"],
      [ 0x18, "TELEPHONE_CONTROL_MODEL_FUNCTIONAL",     "Telephone Control Model Functional Descriptor"],
      #Add For NCM and CDC support
      [ 0x19, "OBEX_SERVICE_IDENTIFIER_FUNCTIONAL",     "OBEX Service Identifier Functional Descriptor"],      
      [ 0x1A, "NCM_FUNCTIONAL",                         "NCM Functional Descriptor"],
	  [ 0x1B, "MBIM_FUNCTIONAL",						"Mobile Broadband Interface Model Functional Descriptor "]
];
      

TryCommunicationDescriptors(bDescriptorType)
{
    Trace("00000000000000000000:", "", "\n");
    
    _row = Find (CommunicationDescriptorTypeTable, bDescriptorType);
    CurrentByteOffset = 0;
    if (_row[0] == 0xFF) 
        return 0;
    Call (_row[1]);
    return 1;   
}

COMM_CS_INTERFACE()
{
    totalLength = bLength;
    AddShortDataHeader(FormatEx ("%s Descriptor  (%d bytes)", "Communication Class Specific INTERFACE", totalLength ));
    
    counter = 300; # in the case of dead loop, we don't want to halt user if something is wrong
                   # Upped Counter from 100 to 300 because MDLM Semantic Model can define upto 256 different 
                   # kinds of MDLM Detail Functional Descriptors...
    
    if (bLength > in.DataLength - Base ) #Checking there is enough data
    {
        AddStringToDlg("Not enough data for this descriptor",FormatEx("Length required %d bytes, Actual Length %d bytes", bLength, in.DataLength - Base), OutputUnknownData(in.DataLength - Base, 0));
        return 0;
    }
                   
    while( totalLength > CurrentByteOffset && counter > 0 )
    {
        if (CurrentByteOffset + 1 > bLength) return 1;
        AddByteEntry("bLength....", "Size of the descriptor, in bytes");
        if (CurrentByteOffset + 1 > bLength) return 1;
        AddByteEntry( "bDescriptorType", GetDescriptorTypeString("CS_INTERFACE"), 0);
        
        if (CurrentByteOffset + 1 > bLength) return 1;
        bDescriptorSubType = GetDataByte(Base + CurrentByteOffset);
        _row_vid_if = Find (DescriptorSubTypeTable, bDescriptorSubType);
        AddEntry( CurrentByteOffset, "bDescriptorSubType", bDescriptorSubType, 2, Format ("%s  Subtype", _row_vid_if[2]), 0);
        AddFieldBreak();
        IncCurrByteOffset( 1 );
        if (_row_vid_if[0] != 0xFF) 
        {
            Call (_row_vid_if[1]); 
        }
        counter ++;
    }
    return 1;           
}

CS_ENDPOINT_sub()
{
    return 0; # no endpoint descriptor
}


HEADER_FUNCTIONAL()
{
    if (CurrentByteOffset + 2 > bLength) return 1;
    bcdCDC = GetDataWord( Base + CurrentByteOffset ); 
    AddEntry( CurrentByteOffset, "bcdCDC", bcdCDC, 4, "USB Class Definitions for Communications " , 0);
    AddDescriptionOnly( "the Communication specification" );
    AddDescriptionOnly( FormatEx( "version %X.%02X", (bcdCDC & 0xFF00)>> 8, bcdCDC & 0xFF) );

    AddFieldBreak();
    IncCurrByteOffset( 2 );
}


set CallManagementCapabilitiesBitTable = 
[
    [0, "Whether device handle call management itself"],
    [1, "Whether device can send/receive call management information over a Data Class Interface"]
];

CALL_MANAGEMENT_FUNCTIONAL()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bmCapabilities", ToBitDecode_old(CallManagementCapabilitiesBitTable, val), 0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bDataInterface", "Interface number of data class interface optionally used for call management", 0);
}

set AbstractControlCapabilitiesBitTable =
[
    [ 0, "Whether device supports the request combination of Set_Comm_Feature, Clear_Comm_Feature, and Get_Comm_Feature"],
    [ 1, "Whether device supports the request combination of Set_Line_Coding, Set_Control_Line_State, Get_Line_Coding, and the notification Serial_State"],
    [ 2, "Whether device supports the request Send_Break"],
    [ 3, "Whether device supports the notification Network_Connection"],
    [ 4, "RESERVED"],
    [ 5, "RESERVED"],
    [ 6, "RESERVED"],
    [ 7, "RESERVED"]            
];

ABSTRACT_CONTROL_MANAGEMENT_FUNCTIONAL()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bmCapabilities", ToBitDecode_old(AbstractControlCapabilitiesBitTable, val), 0);
}

set DirectLineCapabilitiesBitTable =
[
    [0, "Whether device supports the request combination of Pulse_Setup, Send_Pulse, and Set_Pulse_Time"],
    [1, "Whether device supports the request combination of Set_Aux_Line_State, Ring_Aux_Jack, and notification Aux_Jack_Hook_State"],
    [2, "Whether device requires extra Pulse_Setup request during pulse dialing sequence to disengage holding circuit"]
];

DIRECT_LINE_MANAGEMENT_FUNCTIONAL()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bmCapabilities", ToBitDecode_old(DirectLineCapabilitiesBitTable, val), 0);

}



TELEPHONE_RINGER_FUNCTIONAL()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    bRingerVolSteps = GetDataByte(Base + CurrentByteOffset);
    if (bRingerVolSteps == 0)
        AddEntry( CurrentByteOffset, "bRingerVolSteps", bRingerVolSteps, 2, "256 discrete volume steps", 0);
    else
        AddEntry( CurrentByteOffset, "bRingerVolSteps", bRingerVolSteps, 2, Format("%d discrete volume steps",bRingerVolSteps) , 0);
    AddFieldBreak();
    IncCurrByteOffset( 1 );  
    
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNumRingerPatterns","Number of ringer patterns supported", 0);
}


set TelephoneOperationalModesCapabilitiesBitTable =
[
    [0, "Whether support Simple Mode"],
    [1, "Whether support Standalone Mode"],
    [2, "Whether support Computer Centric Mode"]
];

TELEPHONE_OPERATIONAL_MODES_FUNCTIONAL()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bmCapabilities", ToBitDecode_old(TelephoneOperationalModesCapabilitiesBitTable, val));
}

set ReportingCapabilitiesBitTable =
[
    [0, "Whether device reports interrupted dialtone in addition to normal dialtone"],
    [1, "Whether device reports ringback, busy, and fast busy states"],
    [2, "Whether device reports caller ID information."],
    [3, "Whether device reports incoming distinctive ringing patterns"],
    [4, "Whether device can report DTMF digits input remotely over the telephone line"],
    [5, "Whether device supports line state change notification"]
];

REPORTING_CAPABILITIES_FUNCTIONAL()  
{
    if (CurrentByteOffset + 4 > bLength) return 1;
    bmCapabilities = GetNBits(in.Data, ((Base + CurrentByteOffset + DataByteHeaderOffset)*8), 32);
    SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 32, 32);
    toolTip = ToBitDecode_old(ReportingCapabilitiesBitTable, bmCapabilities);
    AddEntry( CurrentByteOffset, "bmCapabilities", bmCapabilities, 8, toolTip, 0);
    AddFieldBreak();
    IncCurrByteOffset( 4 );
}

##################### Add For NCM and CDC support ###################
NCM_FUNCTIONAL()
{
    if (CurrentByteOffset + 2 > bLength) return 1;
    bcdNcmVersion = GetDataWord( Base + CurrentByteOffset ); 
    AddEntry( CurrentByteOffset, "bcdNcmVersion", bcdNcmVersion, 4, "Release number of this specification in BCD" , 0);
    AddFieldBreak();
    IncCurrByteOffset( 2 );
    
    D0Str = "Function can process SetEthenetPacket-Filter requests.";             
    D1Str = "Function can process GetNetAddress and SetNetAddress requests.";
    D2Str = "Function can process SendEncapsulated-Command and GetEncapsulatedResponse requests.";
    D3Str = "Function can process SetMaxDatagram-Size and GetMaxDatagramSize requests";
    D4Str = "Function can process SetCrcMode and GetCrcMode requests";
    D7_D5Str = "Reserved (zero)";
    
    BuildSt = Format ("D0: " + D0Str + " %d", ((bmNetworkCapabilities >> 0) & 0x01)) + "," + 
              Format ("D1: " + D1Str + " %d", ((bmNetworkCapabilities >> 1) & 0x01)) + "," +
              Format ("D2: " + D2Str + " %d", ((bmNetworkCapabilities >> 2) & 0x01)) + "," +
              Format ("D3: " + D3Str + " %d", ((bmNetworkCapabilities >> 3) & 0x01)) + "," +
              Format ("D4: " + D4Str + " %d", ((bmNetworkCapabilities >> 4) & 0x01)) + "," +
              Format ("D7-5: " + D7_D5Str , 0);
        
    if (CurrentByteOffset + 1 > bLength) return 1;
    bmNetworkCapabilities = GetDataByte( Base + CurrentByteOffset ); 
    AddByteEntry( "bmNetworkCapabilities",BuildSt, 0);    
    #AddFieldBreak();
    #IncCurrByteOffset( 1 );    
}

OBEX_SERVICE_IDENTIFIER_FUNCTIONAL()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    bmOBEXRole = GetDataByte( Base + CurrentByteOffset ); 
    AddByteEntry("bmOBEXRole", bmOBEXRole, 0);
    #AddFieldBreak();
    #IncCurrByteOffset( 1 );
    
    
    if (CurrentByteOffset + 16 > bLength) return 1;
    bOBEXServiceUUID = GetNBits(in.Data, ((Base + CurrentByteOffset + DataByteHeaderOffset)*8), 16*8);
    SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 16*8, 16*8);
    toolTip = "A 16 byte UUID value used to indicate the particular OBEX service associated with this function";
    AddEntry( entry, "bOBEXServiceUUID", bOBEXServiceUUID, 32, toolTip, 0);
    AddFieldBreak();
    IncCurrByteOffset( 16 );    
    
    
    if (CurrentByteOffset + 2 > bLength) return 1;
    wOBEXServiceVersion = GetDataWord( Base + CurrentByteOffset ); 
    AddEntry( CurrentByteOffset, "wOBEXServiceVersion", wOBEXServiceVersion, 
              4, "A 16 bit value indicating the version of the OBEX service associated with this function" , 0);
    AddFieldBreak();
    IncCurrByteOffset( 2 );

}
##################### End of new changes for NCM and CDC support ###################

UNION_FUNCTIONAL()
{
	if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bControlInterface","The interface number of the Communications or Data Class interface", 0);
	
	for (i = 0; i < bLength - 3; i++)
    {
        if (CurrentByteOffset + 1 > bLength) return 1;
         AddByteEntry(Format("bSubordinateInterface%d",i), "Interface number of subordinate interface in the Union", 0);
    }
	
}

COUNTRY_SELECTION_FUNCTIONAL()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iCountryCodeRelData","Index of string giving the release data for the implemented ISO 3166 Country Codes", 0);
    
    for (i = 0; i < (bLength - 3) / 2; i++)
    {
        if (CurrentByteOffset + 2 > bLength) return 1;
        AddWordEntry(Format("wCountryCode%d",i), "Country code in hex", 0);
    }
}  

USB_TERMINAL_FUNCTIONAL()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bEntilyId", "Uniquely ID the Terminal", 0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddButeEntry("bInInterfaceNo","The input interface number of the associated USB interface", 0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bOutInterfaceNo","The output interface number of the associated USB interface", 0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry( "bmOptions","Bitmaps:" + NewLine()+ Format ("D0:  Is Wrapper Used        %d", ((bmOptions >> 0) & 0x01))+ 
                                                      NewLine() + 
                                                      Format ("D1 - D7: Reserved           %d", (bmOptions >> 1)), 0);

    for (i = 0; i < bLength - 6; i++)
    {
        if (CurrentByteOffset + 2 > bLength) return 1;
        AddWordEntry( Format("bChildId%d",i), "ID of lower Terminal or Unit to which this Terminal is connected", 0);
    }
}

NETWORK_CHANNEL_TERMINAL()
{
    if (CurrentByteOffset + 1 > bLength) return 1;  
    AddByteEntry("bEntilyId","Uniquely ID the Terminal", 0);
    if (CurrentByteOffset + 1 > bLength) return 1;  
    AddByteEntry("iName","Index of string descriptor", 0);
    if (CurrentByteOffset + 1 > bLength) return 1;  
    AddByteEntry("bChannelIndex", "The channel index of the associated network channel according to indexing rules below", 0);
    if (CurrentByteOffset + 1 > bLength) return 1;  
    bPhysicalInterface = GetDataByte(Base + CurrentByteOffset);    
    if (bPhysicalInterface == 0)
        text = "None";
    else if (bPhysicalInterface == 1)
        text = "ISDN";
    else if (bPhysicalInterface <= 200)
        text = "Reserved";
    else
        text = "Vendor specific";
    AddEntry( CurrentByteOffset, "bPhysicalInterface", text, 0);
    AddFieldBreak();
    IncCurrByteOffset( 1 );
}

PROTOCOL_UNIT_FUNCTIONAL()
{
    if (CurrentByteOffset + 1 > bLength) return 1;  
    AddByteEntry("bEntilyId","Uniquely ID the Terminal", 0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    bProtocol = GetDataByte(Base + CurrentByteOffset);
    _row = Find(DI_ProtocolTable, bprotocol);
    AddEntry(entry, "bProtocol", bProtocol, 2, _row[1], 0);
    AddFieldBreak();
    IncCurrByteOffset( 1 );
    for (i = 0; i < bLength - 4; i++)
    {
        if (CurrentByteOffset + 2 > bLength) return 1;
        AddByteEntry(Format("bChildId%d",i),"ID of lower Terminal or Unit to which this Terminal is connected", 0);
    }
}
  
EXTENSION_UNIT_FUNCTIONAL()
{
    if (CurrentByteOffset + 1 > bLength) return 1;  
    AddByteEntry("bEntilyId","Uniquely ID the Terminal", 0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bExtensionCode","Vendor specific code identifying the Extension Unit", 0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iName","Index of string descriptor", 0);
  
    for (i = 0; i < bLength - 5; i++)
    {
        if (CurrentByteOffset + 1 > bLength) return 1;
        AddByteEntry(Format("bChildId%d",i),"ID of lower Terminal or Unit to which this Terminal is connected", 0);
    }
}

set MultiChannelCapabilitiesBitTable =
[
    [0, "Whether device stores Unit parameters in non-volatile memory"],
    [1, "Whether device supports the request Clear_Unit_Parameter"],
    [2, "Whether device supports the request Set_Unit_Parameter"]
];

NULTI_CHANNEL_MANAGEMENT_FUNCTIONAL()
{
    if (CurrentByteOffset + 1 > bLength) return 1;  ;
    AddByteEntry("bmCapabilities",ToBitDecode_old(MultiChannelCapabilitiesBitTable, val));
}  

set CAPIControlCapabilitiesBitTable =
[
    [0, "Whether device is an Intelligent CAPI device"]
];

CAPI_CONTROL_MANAGEMENT_FUNCTIONAL()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bmCapabilities",ToBitDecode_old(CAPIControlCapabilitiesBitTable, val));
}
set EthernetNEtworkingStatisticsBitTable =
[
    [0,  "XMIT_OK"],
    [1,  "RVC_OK"],
    [2,  "XMIT_ERROR"],
    [3,  "RCV_ERROR"],
    [4,  "RCV_NO_BUFFER"],
    [5,  "DIRECTED_BYTES_XMIT"],
    [6,  "DIRECTED_FRAMES_XMIT"],
    [7,  "MULTICAST_BYTES_XMIT"],
    [8,  "MULTICAST_FRAMES_XMIT"],
    [9,  "BROADCAST_BYTES_XMIT"],
    [10,  "BROADCAST_FRAMES_XMIT"],
    [11,  "DIRECTED_BYTES_RCV"],
    [12,  "DIRECTED_FRAMES_RCV"],
    [13,  "MULTICAST_BYTES_RCV"],
    [14,  "MULTICAST_FRAMES_RCV"],
    [15,  "BROADCAST_BYTES_RCV"],
    [16,  "BROADCAST_FRAMES_RCV"],
    [17,  "RCV_CRC_ERROR"],
    [18,  "TRANSMIT_QUEUE_LENGTH"],
    [19,  "RCV_ERROR_ALIGNMENT"],
    [20,  "XMIT_ONE_COLLISION"],
    [21,  "XMIT_MORE_COLLISIONS"],
    [22,  "XMIT_DEFERRED"],
    [23,  "XMIT_MAX_COLLISIONS"],
    [24,  "RCV_OVERRUN"],
    [25,  "XMIT_UNDERRUN"],
    [26,  "XMIT_HEARTBEAT_FAILURE"],
    [27,  "XMIT_TIMES_CRS_LOST"],
    [28,  "XMIT_LATE_COLLISIONS"]
];

ETHERNET_NETWORKING_FUNCTIONAL()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iMACAddress","Index of string descriptor", 0);
    if (CurrentByteOffset + 4 > bLength) return 1;
    bmEthernetStatistics = GetNBits(in.Data, ((Base + CurrentByteOffset + DataByteHeaderOffset)*8), 32);
    SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 32, 32);
    toolTip = ToBitDecode_old(EthernetNEtworkingStatisticsBitTable, bmEthernetStatistics);
    AddEntry( entry, "bmEthernetStatistics", bmEthernetStatistics, 8, toolTip, 0);
    AddFieldBreak();
    IncCurrByteOffset( 4 );    

    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wMaxSegmentSize","The Maximum segment size that the Ethernet device is capable of supporting", 0);

    if (CurrentByteOffset + 2 > bLength) return 1;
    Add2BytesEntry("wNumberMCFilters", "Multicast filters bitmap", 0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNumberPowerFilters", "Contains the number of pattern filters that are available for causing wake-up of the host", 0);
}

set ATMNetworkingCapabilitiesBitTable =
[
    [1, "Type 1 -- Concatenated ATM cells"],
    [2, "Type 2 -- ATM header template + concatenated ATM cell payloads"],
    [3, "Type 3 -- AAL5 SDU"]
];

set ATMNetworkingStatisticsBitTable = 
[
    [0, "Device counts downstream cells received (DS_CELLS_RECEIVED)"],
    [1, "Device counts upstream cells sent (US_CELLS_SENT)"],
    [2, "Device counts cells with HEC error detected and corrected (DS_CELLS_HEC_ERROR_CORRECTED)"],
    [3, "Device counts downstream cells received on a per VC basis (VC_DS_CELLS_ RECEIVED)"],
    [4, "Device counts upstream cells sent on a per VC basis (VC_US_CELLS_ SENT)"]
];
  
ATM_NETWORKING_FUNCTIONAL()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iEndSystemIdentifier","Index of string descriptor", 0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bmDataCapabilities","The ATM data types bitmap:" + ToBitDecode_old(ATMNetworkingCapabilitiesBitTable,val), 0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bmATMDeviceStatistics","Optional Statistics Bitmap:" + ToBitDecode_old(ATMNetworkingStatisticsBitTable, val), 0);
    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wType2MaxSegmentSize","The maximum segment size that the Type 2 device is capable of supporting", 0);
    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wType3MaxSegmentSize","The maximum segment size that the Type 3 device is capable of supporting", 0);
    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wMaxVC","The maximum number of simultaneous virtual circuits the device is capable of supporting (Type 3 only)", 0);
}  

WIRELESS_HANDSET_CONTROL_FUNCTIONAL()
{
    if (CurrentByteOffset + 2 > bLength) return 1;
    bcdVersion = GetDataWord( Base + CurrentByteOffset ); 
    AddEntry( CurrentByteOffset, "bcdVersion", bcdVersion, 4, "WHCM Communication device compliant to " , 0);
    AddDescriptionOnly( "the Wireless Mobile Communication Devices specification " );
    AddDescriptionOnly( FormatEx( "version %X.%02X", (bcdVersion & 0xFF00)>> 8, bcdVersion & 0xFF) );
    AddFieldBreak();
    IncCurrByteOffset( 2 );
}

MDLM_FUNCTIONAL()
{
    if (CurrentByteOffset + 2 > bLength) return 1;
    bcdVersion = GetDataWord( Base + CurrentByteOffset ); 
    AddEntry( CurrentByteOffset, "bcdVersion", bcdVersion, 4, "MDLM Communication device compliant to " , 0);
    AddDescriptionOnly( "the Wireless Mobile Communication Devices specification " );
    AddDescriptionOnly( FormatEx( "version %X.%02X", (bcdVersion & 0xFF00)>> 8, bcdVersion & 0xFF) );
    AddFieldBreak();
    IncCurrByteOffset( 2 );
    
    if (CurrentByteOffset + 16 > bLength) return 1;
    bGUID_16 = "0x: ";
    for ( ctr = 0; ctr < 16; ctr++)
    {
        tmpval = GetDataByte( Base + CurrentByteOffset + ctr );
        bGUID_16 += Format("%02X ", tmpval);
    }
    AddEntry( CurrentByteOffset, "bGUID[16]", bGUID_16, 32, "Uniquely identifies the detailed transport protocol (and therefore the host drivers) provided by this MDLM interface. The GUID is given in wire-order, as defined in [LEACH1998].", 0);
    AddFieldBreak();
    IncCurrByteOffset( 16 );
}

MDLM_DETAIL_FUNCTIONAL()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bGuidDescriptorType","Discriminator,interpreted according to the semantic model specified by the GUID in the MDLM Functional Descriptor", 0);
    
    bDetailDataLength = bLength - 4;
    
    if (CurrentByteOffset + bDetailDataLength > bLength) return 1;
    bDetailData_n = "0x: ";
    for ( ctr = 0; ctr < bDetailDataLength; ctr++)
    {
        tmpval = GetDataByte( Base + CurrentByteOffset + ctr );
        bDetailData_n += Format("%02X ", tmpval);
    }
    AddEntry( CurrentByteOffset, "bDetailData[n]", bDetailData_n, bDetailDataLength*2, "Information associated with this GUID and discriminator, according to the semantic model specified by the GUID in the MDLM Functional Descriptor. " + Format("[ n = %d ]",bDetailDataLength), 0);
    AddFieldBreak();
    IncCurrByteOffset( bDetailDataLength );
}  
    
DEVICE_MANAGEMENT_FUNCTIONAL()
{
    if (CurrentByteOffset + 2 > bLength) return 1;
    bcdVersion = GetDataWord( Base + CurrentByteOffset ); 
    AddEntry( CurrentByteOffset, "bcdVersion", bcdVersion, 4, "Device Management Communication device compliant to " , 0);
    AddDescriptionOnly( "the Wireless Mobile Communication Devices specification " );
    AddDescriptionOnly( FormatEx( "version %X.%02X", (bcdVersion & 0xFF00)>> 8, bcdVersion & 0xFF) );
    AddFieldBreak();
    IncCurrByteOffset( 2 );
    
    if (CurrentByteOffset + 2 > bLength) return 1;
    wMaxCommand = GetDataWord( Base + CurrentByteOffset );
    AddEntry( CurrentByteOffset, "wMaxCommand", wMaxCommand, 4, "The buffer size allocated in the device for data sent from the host using SEND_ENCAPSULATED_COMMAND. This shall be at least 256 decimal (0x0100)." , 0);
    AddFieldBreak();
    IncCurrByteOffset( 2 );    
}

OBEX_FUNCTIONAL()
{
    if (CurrentByteOffset + 2 > bLength) return 1;
    bcdVersion = GetDataWord( Base + CurrentByteOffset ); 
    AddEntry( CurrentByteOffset, "bcdVersion", bcdVersion, 4, "OBEX Communication device compliant to " , 0);
    AddDescriptionOnly( "the Wireless Mobile Communication Devices specification " );
    AddDescriptionOnly( FormatEx( "version %X.%02X", (bcdVersion & 0xFF00)>> 8, bcdVersion & 0xFF) );
    AddFieldBreak();
    IncCurrByteOffset( 2 );
}  

COMMAND_SET_FUNCTIONAL()
{
    if (CurrentByteOffset + 2 > bLength) return 1;
    bcdVersion = GetDataWord( Base + CurrentByteOffset ); 
    AddEntry( CurrentByteOffset, "bcdVersion", bcdVersion, 4, "Command Set Communication device compliant to " , 0);
    AddDescriptionOnly( "the Wireless Mobile Communication Devices specification " );
    AddDescriptionOnly( FormatEx( "version %X.%02X", (bcdVersion & 0xFF00)>> 8, bcdVersion & 0xFF) );
    AddFieldBreak();
    IncCurrByteOffset( 2 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iCommandSet","Index of string that describes this command set.", 0, 1, 0);
     
    if (CurrentByteOffset + 16 > bLength) return 1;
    bGUID_16 = "0x: ";
    for ( ctr = 0; ctr < 16; ctr++)
    {
        tmpval = GetDataByte( Base + CurrentByteOffset + ctr );
        bGUID_16 += Format("%02X ", tmpval);
    }
    AddEntry( CurrentByteOffset, "bGUID[16]", bGUID_16, 32, "Uniquely identifies the command set to be used when communicating with this interface. The GUID is given in wire-order, as defined in [LEACH1998].", 0);
    AddFieldBreak();
    IncCurrByteOffset( 16 );
}

COMMAND_SET_DETAIL_FUNCTIONAL()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bGuidDescriptorType","Discriminator,interpreted according to the command set model specified by the GUID in the Command Set Functional Descriptor", 0);
    
    bDetailDataLength = bLength - 4;
    
    if (CurrentByteOffset + bDetailDataLength > bLength) return 1;
    bDetailData_n = "0x: ";
    for ( ctr = 0; ctr < bDetailDataLength; ctr++)
    {
        tmpval = GetDataByte( Base + CurrentByteOffset + ctr );
        bDetailData_n += Format("%02X ", tmpval);
    }
    AddEntry( CurrentByteOffset, "bDetailData[n]", bDetailData_n, bDetailDataLength*2, "Information associated with this GUID and discriminator, according to the command set model specified by the GUID in the Command Set Functional Descriptor. " + Format("[ n = %d ]",bDetailDataLength), 0);
    AddFieldBreak();
    IncCurrByteOffset( bDetailDataLength );
}

TELEPHONE_CONTROL_MODEL_FUNCTIONAL()
{
    if (CurrentByteOffset + 2 > bLength) return 1;
    bcdVersion = GetDataWord( Base + CurrentByteOffset ); 
    AddEntry( CurrentByteOffset, "bcdVersion", bcdVersion, 4, "Telephone Control Model Communication device compliant to " , 0);
    AddDescriptionOnly( "the Wireless Mobile Communication Devices specification " );
    AddDescriptionOnly( FormatEx( "version %X.%02X", (bcdVersion & 0xFF00)>> 8, bcdVersion & 0xFF) );
    AddFieldBreak();
    IncCurrByteOffset( 2 );
    
    if (CurrentByteOffset + 2 > bLength) return 1;
    wMaxCommand = GetDataWord( Base + CurrentByteOffset );
    AddEntry( CurrentByteOffset, "wMaxCommand", wMaxCommand, 4, "Describes the maximum number of characters that can be transported in a single SEND_ENCAPSULATED_COMMAND. This shall be at least 256 decimal (0x0100)." , 0);
    AddFieldBreak();
    IncCurrByteOffset( 2 );  
}

MBIM_FUNCTIONAL()
{
	if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("bcdMBIMVersion","Release number of this specification in BCD", 0);
	
	if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wMaxControlMessage","Maximum segment size in bytes a function", 0);
	
	if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNumberFilters","Contains the number of PacketFilter that are available in total for all SessionIds ", 0);
	
	if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bMaxFilterSize","The Maximum size of the PacketFilters in bytes", 0);
	
	if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wMaxSegmentSize","The Maximum segment size in bytes that the function is capable of supporting", 0);
	
	if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bmNetworkCapabilities","Specifies the capabilities of this function ", 0);	
	
}

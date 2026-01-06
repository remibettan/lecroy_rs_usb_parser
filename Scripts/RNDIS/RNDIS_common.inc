#
#  Copyright (c) 2005-7, CATC/LeCroy - All Rights Reserved
#
#  RNDIS_Common.inc
#
#  RNDISDisplay Decoder base in RNDIS V1.1 spec
#
#  FILE HISTORY:
#        2007 Created - mgd 
#     3/16/07 Updated for Dialogue View & Eliminated Tabs - RK
#

# Parsing entry point
#

%include "RNDIS_OID.inc"

# start DecodeNDIS

set OIDFlag = 0;
set DECODE_ABORTED_FLAG = 0;
set DECODE_ABORTED_OFFSET = 0;
set DatLen = 0;

const Tabular_Def_Table = Map( 
[   
    #-----------------------------------------------------------------------------------------------------
    #       id            ,      colId                          , 		containerCellId
    #-----------------------------------------------------------------------------------------------------
    [ CELL_REQUEST        , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE   , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ CELL_RNDIS_MSG_TYPE , TABULAR_SCRIPT_COLUMN_ID_NONE      , TABULAR_SCRIPT_CONTAINER_CELL_ID_MISC ]
] );


set NDIS_MessageTypeTable = [
    [  0x00000000,  "UNKNOWN CODE",                     RGB(255,000,000),  "Unknown code"], 
    [  0x00000001,  "REMOTE_NDIS_PACKET_MSG",			RGB(182,202,255),  "The host and device use this to send network data to one another"],
    [  0x00000002,  "REMOTE_NDIS_INITIALIZE_MSG",       RGB(200,220,100),  "Initialize the device."],
    [  0x00000003,  "REMOTE_NDIS_HALT_MSG",             RGB(200,220,100),  "Halt the device.  This is the only host control\nmessage that doesn’t get a response."],
    [  0x00000004,  "REMOTE_NDIS_QUERY_MSG",            RGB(100,220,200),  "Send a ‘query’ OID."],
    [  0x00000005,  "REMOTE_NDIS_SET_MSG",              RGB(100,120,100),  "Send a ‘set’ OID."],
    [  0x00000006,  "REMOTE_NDIS_RESET_MSG",            RGB(200,120,200),  "Perform a soft reset on the device."],
    [  0x00000007,  "REMOTE_NDIS_INDICATE_STATUS_MSG",  RGB(150,220,150),  "Indicates 802.3 link state or undefined message error."],
    [  0x00000008,  "REMOTE_NDIS_KEEPALIVE_MSG",        RGB(120,240,120),  "During idle periods, sent every few seconds to\ncheck that the device is still responsive (may\noptionally also be sent by the device)."],
    [  0x80000002,  "REMOTE_NDIS_INITIALIZE_CMPLT",     RGB(220,240,120),  "Device response to initialization request."],
    [  0x80000004,  "REMOTE_NDIS_QUERY_CMPLT",          RGB(120,240,220),  "Device response to ‘query’ OID request."],
    [  0x80000005,  "REMOTE_NDIS_SET_CMPLT",            RGB(120,140,120),  "Device response to ‘set’ OID request."],
    [  0x80000006,  "REMOTE_NDIS_RESET_CMPLT",          RGB(120,140,220),  "Device responses to reset request."],
    [  0x80000008,  "REMOTE_NDIS_KEEPALIVE_CMPLT",      RGB(140,255,140),  "Device response to keep alive message."]
];

#####################################################################################################
# Common MBIM fields information are kept in this map.
# Each row consist of below attribute for each field :
# Field ID            : Field unique Id 
# Offset              : Field offset in byte
# Size                : Field size in byte
# Mask 	              : Field mask that can be used for masking some bits or bytes of value
# Field Name          : Field name that is shown in packet viewer
# Value Format        : This format is used in Format() method to convert field's value to string
# Value Substitute    : This array can define substitute for each field value. for example when we want to show meaningful name for numeric values
# Is Value Bitmap     : Specifies if value is a bitmap or not. 
# Tooltip             : Field tooltip that is shown in packet viewer
#####################################################################################################
set RNDIS_Request_Fields = Map(
[
    ["MsgType",         0,  4, 0xFFFFFFFF,  "MsgType",          "%s",       NDIS_MessageTypeTable,  0, "Identifies the type of the RNDIS message and MUST be set to 0x00000001"],
    ["MsgLen",          4,  4, 0xFFFFFFFF,  "MsgLen",           "%d",       null,                   0, "The total length of this RNDIS message including the header, payload, and padding."],
    ["Dof",             8,  4, 0xFFFFFFFF,  "Dof",              "0x%08x",   null,                   0, "Specifies the offset, in bytes, from the start of the DataOffset field of this message to the start of the data.\nThis MUST be an integer multiple of 4"],
    ["DataLen",         12, 4, 0xFFFFFFFF,  "DataLen",          "%d",       null,                   0, "Specifies the number of bytes in the payload of this message."],
    ["OOBDof",          16, 4, 0xFFFFFFFF,  "OOBDof",           "0x%08x",   null,                   0, "Specifies the offset, in bytes, of the first out-of-band data record from the start of the DataOffset field in this message.\nMUST be an integer multiple of 4 when out-of-band data is present or set to 0 otherwise.\nWhen there are multiple out-of-band data records, each subsequent record MUST immediately follow the previous out-of-band data record."],
    ["OOBDataLen",      20, 4, 0xFFFFFFFF,  "OOBDataLen",       "%d",       null,                   0, "Specifies, in bytes, the total length of the out-of-band data."],            
    ["OOBDataNum",      24, 4, 0xFFFFFFFF,  "OOBDataNum",       "%d",       null,                   0, "Specifies the number of out-of-band records in this message."],                   
    ["PPIDof",          28, 4, 0xFFFFFFFF,  "PPIDof",           "0x%08x",   null,                   0, "Specifies the offset, in bytes, of the start of per-packet-info data record from the start of the DataOffset field in this message.\nMUST be an integer multiple of 4 when per-packet-info data record is present or MUST be set to 0 otherwise.\nWhen there are multiple per-packet-info data records, each subsequent record MUST immediately follow the previous record."],
    ["PPIDataLen",      32, 4, 0xFFFFFFFF,  "PPIDataLen",       "%d",       null,                   0, "Specifies, in bytes, the total length of per-packet-information contained in this message."],              
    ["Vch",             36, 4, 0xFFFFFFFF,  "Vch",              "0x%08x",   null,                   0, "Reserved for connection-oriented devices. Set to 0"],                
    ["Rsvd",            40, 4, 0xFFFFFFFF,  "Rsvd",             "0x%08x",   null,                   0, "Reserved. Set to zero."],                
    ["Payload",         8,  4, 0xFFFFFFFF,  "Payload",          "%s",       null,                   0, "Network data contained in this message."],                    
    
    ["OOBSize",         0,  4, 0xFFFFFFFF,  "Size",             "%d",       null,                   0, "Length, in bytes, of this header and appended out-of-band data and padding.\nThis value MUST be an integer multiple of 4."],                    
    ["OOBType",         4,  4, 0xFFFFFFFF,  "Type",             "%d",       null,                   0, "MUST be as per host operating system specification."],                    
    ["ClassInfoOffset", 8,  4, 0xFFFFFFFF,  "ClassInfoOffset",  "0x%08x",   null,                   0, "The byte offset from the beginning of this out-of-band data record to the beginning of out-of-band data."],                    
    ["OOBData",         0,  4, 0xFFFFFFFF,   "OOBData",         "%s",       null,                   0, "The out-of-band data."],
    
    ["PPISize",         0,  4, 0xFFFFFFFF,  "Size",             "%d",       null,                   0, "Length, in bytes, of this header plus PerPacketData plus any padding necessary.\nMUST be an integer multiple of 4."],                    
    ["PPIType",         4,  4, 0xFFFFFFFF,  "Type",             "%d",       null,                   0, "Must be as per the host operating system specification."],                    
    ["PPIOffset",       8,  4, 0xFFFFFFFF,  "PPIOffset",        "0x%08x",   null,                   0, "The byte offset from the beginning of this per-packet-info record to the beginning of PerPacketData."],                    
    ["PPIData",         0,  4, 0xFFFFFFFF,  "PPIData",          "%s",       null,                   0, "The per-packet- data."]     
] );

######################################

DecodeNDIS()
{
    DECODE_ABORTED_FLAG = 0;
    DatLen = in.DataLength - 8;
    #messageType= NextNBits(8) +( NextNBits(8) * 256)+( NextNBits(8) * 256*256)+( NextNBits(8) * 256*256*256);
    if(DatLen > 3)  
    {
        messageType= NextDataDWord_();
                      
        msgTypeRow = Find(NDIS_MessageTypeTable, messageType);
        AddShortDataHeader(msgTypeRow[1]);
        
        SetCellColor(msgTypeRow[2]);
        AddCaptionCell(msgTypeRow[1], "", "NDIS MsgTyp\n" + "Message Type = " + Format("0x%08X",messageType) + "\n(" + msgTypeRow[3] + ")\n\n          Double Click to Expand          ", _MONOCOLOR, _MONOFIELD);       
        DatLen -= 4;
    }
    else
    {
        AddCell("NOT ENOUGH DATA","DECODE ABORTED",FormatEx("!!! WARNING !!! *** ERROR *** Not enough data!\n Expected 4+ bytes, Found only %d...\n NO NDIS to Decode", DatLength), WarningColor, _ERROR);
        AddShortDataHeader("<font color=RED>NOT ENOUGH DATA! DECODE ABORTED!!!</font>");
    }

    #messageLength= NextNBits(8) +( NextNBits(8) * 256)+( NextNBits(8) * 256*256)+( NextNBits(8) * 256*256*256);
    if(DatLen > 3)
    {
        DatLen -= 4;
        messageLength= NextDataDWord_();
        if(messageLength != in.DataLength - 8)
        {
            SetCellColor(WarningColor);
            AddPayLoadCell("MsgLen",messageLength ,Format("!!! WARNING !!!\nData Discrepancy of %d bytes (Message Length - Actual Data in PayLoad)\n\nMessage Length =",(messageLength-in.DataLength-8)) + Format("0x%04X",messageLength) + "\nSpecifies the total length of this Remote NDIS message in bytes.",_ERROR);
            RestoreCellColor();
        }
        else if(SimpleShowItem())
            AddPayLoadCell("MsgLen",messageLength ,"Message Length =" + Format("0x%08X",messageLength) + "\nSpecifies the total length of this Remote NDIS message in bytes.");
    }
    else
    {
        AbortDecodeNEData(4,DatLen,MsgLen);
        return 0;
    }
 
    #if(SimpleShowItem())
        Call(msgTypeRow[1]);
    
    if(DECODE_ABORTED_FLAG)
        out.Decoded = in.DataLength - 8 - DatLen;
    
    if( OIDFlag && !DECODE_ABORTED_FLAG && (bRequest != 0x0000) && ((in.DataLength - 8 -out.Decoded)%4 == 0))
    {
      AddSeparator();
      AddCaptionCell("OID_SUPPORTED_LIST",Format("%d OIDs",(in.DataLength-8-out.Decoded)/4),"NOTE: Extra data in the payload is being decoded as\n a Supported OID List because the script variable\n 'OIDFlag' has been set to 1. Set to 0 to stop this\n decoding. This function is meant to allow for the\n verififcation of the list(s), it is not meant to be\n the default!\n\n Variable is located at the top of the RNDIS Decode\n file 'RNDIS_common.inc'");
      while(( in.DataLength - 8 - out.Decoded) > 3)
      {
        GetOID();
      }
    }    
    
    AddSeparator();
}

################################# Tabe 3-2
REMOTE_NDIS_INITIALIZE_MSG() 
{
    GetRequestID();
    GetMajorVersion() ;
    GetMinorVersion() ;
    GetMaxTransferSize();
    out.Decoded=24;
}

################################# Tabe 3-3
set NDIS_deviceFlagsTable = [
    [0x00000000,  "unknown in 1.1spec"],
    [0x00000001,  "RNDIS_DF_CONNECTIONLESS"],
    [0x00000002,  "RNDIS_DF_CONNECTION_ORIENTED"]
];

set NDIS_MediumTable = [
    [0x00000000,  "RNDIS_MEDIUM_802_3"]
];


################################# Tabe 3-4
REMOTE_NDIS_INITIALIZE_CMPLT() 
{
    GetRequestID();
    GetStatus() ;
    GetMajorVersion() ;
    GetMinorVersion() ;

    if(DatLen > 7)
    {
        if(SimpleShowItem())
        {
            dFlags = Next4BytesNumeric();
            devFlag= Find(NDIS_deviceFlagsTable, dFlags);
            SetCellColor(RGB(240,220,20));
            AddPayLoadCell("DeviceFlags",devFlag[1],"DeviceFlags =" + Format("0x%08X",dFlags) + "\nSpecifies the device type as either\nconnectionless or connection oriented. This\nvalue can be one of the following: RNDIS_DF_CONNECTIONLESS = 0x00000001, RNDIS_DF_CONNECTION_ORIENTED = 0x00000002");
            RestoreCellColor();
  
            mDium= Next4BytesNumeric();
            meDium=Find(NDIS_MediumTable, mDium);
            SetCellColor(RGB(230,180,10));
            AddPayLoadCell("Medium",meDium[1],"Medium =" + Format("0x%08X",mDium) + "\nSpecifies the medium supported by the device.");
            RestoreCellColor();
        }
    }
    else
    {
        AbortDecodeNEData(8,DatLen,"DeviceFlags & Medium");
        return 0;
    }
  
    if(SimpleShowItem())
    {  
        Display4Byte("MxPktPtx","MaxPacketsPerTransfer","Specifies the maximum number of\nconcatenated REMOTE_NDIS_PACKET_MSGs that the\ndevice can handle in a single transfer to it. This\nvalue should be at least 1");

        Display4Byte("MxTfrSz","MaxTransferSize","Specifies the maximum size, in bytes, of any\nsingle bus data transfer that the device expects\nto receive from the host.");

        Display4Byte("PackAlgnF","PacketAlignmentFactor","Specifies the byte alignment the device expects\nfor each Remote NDIS message that is part of\na multi-message transfer to it. This value is\nspecified as an exponent of 2. For example,\nthis value is set to 3 to indicate 8-byte alignment.");
        ## todo at a check for non zero in the next 2
        Display4Byte("AFLoff","AFListOffset","Reserved for connection-oriented devices. Set value to 0.");
        Display4Byte("AFLsz","AFListSize","Reserved for connection-oriented devices. Set value to 0.");
    }

    out.Decoded = 52;
}

#################################
REMOTE_NDIS_HALT_MSG() 
{
    GetRequestID();
}



#################################

REMOTE_NDIS_QUERY_MSG() 
{
    GetRequestID();
    GetOID();
    GetInformationBufferLength();
    GetInformationBufferOffset();
    
    if(SimpleShowItem())
        Display4Byte("DvHand","DeviceVcHandle","Reserved for connection-oriented devices. Set to 0.");
        
    out.Decoded=28;
}
#################################

REMOTE_NDIS_QUERY_CMPLT()
{
    GetRequestID();
    GetStatus();
    GetInformationBufferLength();
    GetInformationBufferOffset();
    out.Decoded=24;
}

#################################
REMOTE_NDIS_SET_MSG() 
{
    GetRequestID();
    GetOID();
    GetInformationBufferLength();
    GetInformationBufferOffset();
    
    if(SimpleShowItem())
        Display4Byte("DvHand","DeviceVcHandle","Reserved for connection-oriented devices. Set to 0.");
        
    out.Decoded=28;
}

#################################
REMOTE_NDIS_SET_CMPLT() 
{
    GetRequestID();
    GetStatus();
 
    out.Decoded=16;
# The previous code replaces the following code as per a customer fix; Akira Fukumoto  of Siemens.  Bug 5713
#    GetRequestID();
#    GetOID();
#    GetInformationBufferLength();
#    GetInformationBufferOffset();
#    out.Decoded=16;
}

#################################
REMOTE_NDIS_RESET_MSG() 
{
  if(SimpleShowItem())
      Display4Byte("rsVd","Reserved","Reserved in 1.1 spec. Set to 0.");
      
  out.Decoded=12;
}

#################################
REMOTE_NDIS_RESET_CMPLT() 
{
    GetRequestID();
    GetStatus();
    Display4Byte("AddrRst","AddressingReset","Indicates if addressing information (multicast\naddress list, packet filter) has been lost during\nthe concluded reset operation. If the device\nneeds the host to resend addressing\ninformation, it sets this field to 1; otherwise it\nsets this field to 0.");
    out.Decoded=20;
}

#################################
REMOTE_NDIS_INDICATE_STATUS_MSG() 
{
    GetStatus();
    if(SimpleShowItem())
    {
        Display4Byte("SBufLen","StatusBufferLength","Specifies the length of the status data in bytes.");
        Display4Byte("SBufOff","SStatusBufferOffset","Specifies the byte offset from the beginning of\nthe Status field at which the\nRndis_Diagnostic_Info status data for the\ndevice indication is located.");
        Display4Byte("DiagSt","DiagStatus","Contains additional status about the error itself\n(e.g. RNDIS_STATUS_NOT_SUPPORTED)");
        Display4Byte("ErrOfs","ErrorOffseth","Specifies the 0-based byte offset within the\noffending message at which the error was detected.");
    }
    out.Decoded=20;
}

#################################
REMOTE_NDIS_KEEPALIVE_MSG() 
{
    GetRequestID();
    out.Decoded=12;
}

#################################
REMOTE_NDIS_KEEPALIVE_CMPLT() 
{
    GetRequestID();
    GetStatus();
    out.Decoded=16;
}

#################################

GetRequestID() 
{
    requestID= Next4BytesNumeric();
    if(SimpleShowItem())
        AddPayLoadCell("requestID",requestID ,"requestID =" + Format("0x%08X",requestID) + "\nSpecifies the Remote NDIS message id value.\nThis value is used to match host sent\nmessages with device responses.  ");
}

GetStatus() 
{
    status= Next4BytesNumeric();
    status_string = "";
    if(SimpleShowItem())
    {
        status_string = select {
            status == 0x00000000 : "Success";
            status == 0xC0000001 : "Unspecified error";
            status == 0xC0010015 : "Invalid data error";
            status == 0xC00000BB : "Unsupported request error";
            status == 0x4001000B : "Device is connected to a network medium";
            status == 0x4001000C : "Device is disconnected from the medium";
            default : "";
       };
        AddPayLoadCell("Status", status , "Status =" + Format("0x%08X", status) + Format("\nDescription: %s", status_string) + "\nSpecifies RNDIS_STATUS_SUCCESS if the device initialized\nsuccessfully, otherwise it specifies an error code \nindicating the failure.\n\nSee section 2.9 of the RNDIS Spec for more details.",RGB(99,99,200));
    }
}

GetMajorVersion() 
{
    MajorVersion= Next4BytesNumeric();
    if(SimpleShowItem())
        AddPayLoadCell("MajorVersion",MajorVersion ,"MajorVersion =" + Format("0x%08X",MajorVersion) + "\n RNDIS_MAJOR_VERSION\nTogether with MinorVersion, specifies the\nhighest Remote NDIS protocol version\nsupported by the device.",RGB(99,99,200));
}

GetMinorVersion() 
{
    MinorVersion= Next4BytesNumeric();
    if(SimpleShowItem())
        AddPayLoadCell("MinorVersion",MinorVersion ,"MinorVersion =" + Format("0x%08X",MinorVersion) + "\nRNDIS_MINOR_VERSION\nTogether with MajorVersion, specifies the\nhighest Remote NDIS protocol version\nsupported by the device.");
}

######################################
# OID's

GetOID() 
{
    
    OID = Next4BytesNumeric(); #NextDataDWord_();
    oid_func = (OID&0xFF);

    oid_mand_opt = ((OID>>8)&0xFF);
    OIDMandOpt = Find(OID_Byte2_Table,oid_mand_opt);
    
    oid_opt_stats = ((OID>>16)&0xFF);
    OIDOptStat = Find(OID_Byte3_Table,oid_opt_stats);

    oid_class = ((OID>>24)&0xFF);
    OIDClass = Find(OID_Byte4_Table,oid_class);

    OIDRow = Find(NDIS_OID_Table, OID);
    
    tttxt ="";
    if(OIDRow[1] == "UNKNOWN")
    {
        SetCellColor(WarningColor);
        tttxt = "\n  Check psgsupport@teledynelecroy.com for update if OID is Valid.";
    }
    else
        SetCellColor(RGB(220,200,20));
    
    if(SimpleShowItem())
        AddPayLoadCell("OID ", /*Format("0x%08X : ",OID) +*/ OIDRow[1] ,"OID  =" + Format(" 0x%08X : ",OID) + OIDRow[1] + "\n " + OIDRow[2] + tttxt + "\n\nSpecifies the NDIS OID that identifies\nthe parameter being set." +
        "\nByte 4 - OID Class: " + Format("0x%02X ",oid_class) + OIDClass[1] + "\nByte 3 -  Function: "  + Format("0x%02X ",oid_opt_stats) + OIDOptStat[1] + "\nByte 2 -  Function: " + Format("0x%02X ",oid_mand_opt) + OIDMandOpt[1]);
    else
        AddCell( OIDRow[1],"","OID  =" + Format(" 0x%08X : ",OID) + OIDRow[1] + "\n " + OIDRow[2] + tttxt + "\n\nSpecifies the NDIS OID that identifies\nthe parameter being set." + "\nByte 4 - OID Class: " + Format("0x%02X ",oid_class) + OIDClass[1] + "\nByte 3 -  Function: "  + Format("0x%02X ",oid_opt_stats) + OIDOptStat[1] + "\nByte 2 -  Function: " + Format("0x%02X ",oid_mand_opt) + OIDMandOpt[1] + "\n\n                    Double Click to Expand                    ",FieldColor,_MONOFIELD);
    RestoreCellColor();
}

######################################

GetMaxTransferSize() 
{
    val = Next4BytesNumeric();
    if(SimpleShowItem())
        Display4Byte_MOD(val,"MxTxSize","MaxTransferSize","Specifies the maximum size, in bytes, of any\nsingle bus data transfer that the host expects to\nreceive from the device. Typically, each bus\ndata transfer accommodates a single Remote\nNDIS message. However, the device may\nbundle several Remote NDIS data packets into\na single transfer.");
}

GetInformationBufferLength() 
{
    val = Next4BytesNumeric();
    if(SimpleShowItem())
        Display4Byte_MOD(val,"InfBLen","InformationBufferLength","Specifies in bytes the length of the input data for\nthe query. Set to 0 when there is no OID input buffer.");
}

GetInformationBufferOffset() 
{
    val = Next4BytesNumeric();
    if(SimpleShowItem())
        Display4Byte_MOD(val,"InfBOff","InformationBufferOffset","Specifies the byte offset from the beginning of\nthe RequestId field at which input data for the\nquery is located. Set to 0 if there is no OID input buffer.");
}

Decode_RNDIS_Packet_MSG(bSize) 
{
    DECODE_ABORTED_FLAG = 0;
    DECODE_ABORTED_OFFSET = 0;
    MsgOffset = 0;
    MsgCount = 0; 
    
    msgTypeRow = Find(NDIS_MessageTypeTable, 0x00000001);
    SetCellColor(msgTypeRow[2]);
    while( MsgOffset < in.DataLength && !DECODE_ABORTED_FLAG )
    {
        MsgCount++;
        
        AddSeparator();
        AddCaptionCell(Format("MSG #%d", MsgCount),"","", _MONOCOLOR, _MONOFIELD);
        AddSeparator();    
           
        RetVal = AddRNDISField( "MsgType", MsgOffset);
        if( RetVal[0] == 1 && RetVal[1] != 0x00000001 )
        {
            SetCellColor(WarningColor);
            AddPayLoadCell( "MessageType","Invalid RNDIS Message Type",Format("!!! WARNING !!! *** ERROR ***\nFor an RNDIS 1.1 Packet Message the first four bytes of the PayLoad should = 0x1\n Found: 0x%08X\n\nTherefore this is not RNDIS 1.1 format data, try another decoder", RetVal[1] ), _ERROR );
            RestoreCellColor();
            
            return 0;
        }
   
        RetVal = AddRNDISField( "MsgLen", MsgOffset);
        MessageLen = RetVal[1];        
        
        RetVal = AddRNDISField( "Dof", MsgOffset);
        DataOffset = RetVal[1];        
        
        RetVal = AddRNDISField( "DataLen",   MsgOffset);
        DataLength = RetVal[1];        
               
        AddRNDISDataPayloadField("Payload", MsgOffset + DataOffset, DataLength);
        
        
        SetCellColor(RGB(124, 138, 173));
        AddSeparator();
        AddCaptionCell("OOB","OOB","OOB", _MONOCOLOR, _MONOFIELD);
        
        RetVal = AddRNDISField( "OOBDof", MsgOffset);
        DataOffset = RetVal[1];        
 
        RetVal = AddRNDISField( "OOBDataLen", MsgOffset);
        TotalDataLength = RetVal[1];                            
        
        RetVal = AddRNDISField( "OOBDataNum", MsgOffset);
        DataNum = RetVal[1];        

        OOBOffset = MsgOffset + DataOffset + 8;
       
        if( SimpleShowItem() )
            AddOOBData(OOBOffset, DataNum, TotalDataLength);
        
             
        SetCellColor(RGB(88, 97, 122));
        AddSeparator();
        AddCaptionCell("PPI","PPI","PPI", _MONOCOLOR, _MONOFIELD);      
        
        RetVal = AddRNDISField( "PPIDof", MsgOffset); 
        DataOffset = RetVal[1];        
        
        RetVal = AddRNDISField( "PPIDataLen", MsgOffset);
        TotalDataLength = RetVal[1];                            
        
        PPIOffset = MsgOffset + DataOffset + 8;
        
        if( SimpleShowItem() )
            AddPPIData(PPIOffset, TotalDataLength);
        
      
        AddSeparator();
        AddRNDISField( "Vch",   MsgOffset);
        AddRNDISField( "Rsvd",  MsgOffset);
    
    
        MsgOffset += MessageLen;       
    }
    
    # For probable data block
    AddSeparator(); 
    
    out.Decoded = MsgOffset;
    
}

AddOOBData(OOBOffset, DataNum, TotalDataLength)
{
    for( i = 1; i <= DataNum; i++ )
    {    
        AddSeparator();
        AddCaptionCell(Format("Data #%d", i ), "", "OOB Data", _MONOCOLOR, _MONOFIELD);      

        RetVal = AddRNDISField( "OOBSize", OOBOffset );
        if( !RetVal[0] )
            return 0; 
        DataSize = RetVal[1];
       
        RetVal = AddRNDISField( "OOBType", OOBOffset );
        if( !RetVal[0] )
            return 0; 
                
        RetVal = AddRNDISField( "ClassInfoOffset",   OOBOffset );           
        if( !RetVal[0] )
            return 0; 

        DataOffset = RetVal[1];
    
        if( DataSize <= 0 || DataOffset <= 0 || DataOffset >= TotalDataLength )
        {
            AddCell("DECODE ABORTED", "INVALID SIZE OR OFFSET", "", WarningColor, _ERROR);            
            return 0;
        }
    
        AddRNDISDataPayloadField( "OOBData", OOBOffset + DataOffset, DataSize - DataOffset ); 
        
        OOBOffset += DataSize;
    }
}

AddPPIData(PPIOffset, TotalDataLength)
{
    PPICount = 0;
    PPIEndOffset = PPIOffset + TotalDataLength;

    while( PPIOffset < PPIEndOffset )
    {
        PPICount++;
        
        AddSeparator();
        AddCaptionCell(Format("Data #%d", PPICount ), "", "OOB Data", _MONOCOLOR, _MONOFIELD);      
  
        RetVal = AddRNDISField( "PPISize", PPIOffset);
        if( !RetVal[0] )
            return 0;         
        DataSize = RetVal[1];

        RetVal = AddRNDISField( "PPIType", PPIOffset);
        if( !RetVal[0] )
            return 0; 
        
        RetVal = AddRNDISField( "PPIOffset", PPIOffset);      
        if( !RetVal[0] )
            return 0;         
        DataOffset = RetVal[1];

        if( DataSize <= 0 || DataOffset <= 0 || DataOffset >= TotalDataLength )
        {
            AddCell("DECODE ABORTED", "INVALID SIZE OR OFFSET", "", WarningColor, _ERROR);            
            return 0;
        }
        
        AddRNDISDataPayloadField( "PPIData", PPIOffset + DataOffset, DataSize - DataOffset );

        PPIOffset += DataSize;
    }
}

# End DecodeNDIS

####################################
## utils
######################################

DisplayDataBlockByteN(fName, PayloadSize) 
{
    #val = NextNBits(8) +( NextNBits(8) * 256)+( NextNBits(8) * 256*256)+( NextNBits(8) * 256*256*256);
    if(!DECODE_ABORTED_FLAG)
    {
        if(DatLen >= PayloadSize)
        {
            ShowDataBlock(PayloadSize);            
           
            out.Decoded = out.Decoded + PayloadSize;
            DatLen -= PayloadSize;
        }
        else
            AbortDecodeNEData(PayloadSize, DatLen, fName);
    }
}

Display4ByteN(fName, fName1,ttdesc) 
{
    #val = NextNBits(8) +( NextNBits(8) * 256)+( NextNBits(8) * 256*256)+( NextNBits(8) * 256*256*256);
    if(!DECODE_ABORTED_FLAG)
    {
        if(DatLen > 3)
        {
            val = NextDataDWord_();
            SetCellColor(RGB(190,100,200));
            AddPayLoadCell(fName ,val  , fName1 +  " = " + Format("0x%04X\n",val) + ttdesc);
            RestoreCellColor();
            out.Decoded = out.Decoded +4;
            DatLen -= 4;
            return val;
        }
        else
            AbortDecodeNEData(4,DatLen,fName1);
    }
}


Display4Byte(fName, fName1,ttdesc) 
{
    val = Next4BytesNumeric();
    if(!DECODE_ABORTED_FLAG)
        AddPayLoadCell(fName ,val  , fName1 +  " = " + Format("0x%04X\n",val) + ttdesc);
}

Display4Byte_MOD(val,fName, fName1,ttdesc) 
{
    if(!DECODE_ABORTED_FLAG)
        AddPayLoadCell(fName ,val  , fName1 +  " = " + Format("0x%04X\n",val) + ttdesc);
}

Next4BytesNumeric() 
{ 
    #val = NextNBits(8) +( NextNBits(8) * 256)+( NextNBits(8) * 256*256)+( NextNBits(8) * 256*256*256);
    if(!DECODE_ABORTED_FLAG)
    {
        if(DatLen > 3)
        {
            val = NextDataDWord_();
            out.Decoded = out.Decoded +4;
            DatLen -= 4;
            return val;
        }
        else
            AbortDecodeNEData(4,DatLen);
    }   
}

AbortDecodeNEData(DatSize,DatLength,field)
{
    if(field == null)
      field = "the next expected field";
    AddCell("NOT ENOUGH DATA","DECODE ABORTED",FormatEx("!!! WARNING !!! *** ERROR *** Not enough data!\n Expected %d bytes, Found only %d...\n While Decoding %s", DatSize, DatLength, field), WarningColor, _ERROR);
    AddShortDataHeader("<font color=RED>NOT ENOUGH DATA! DECODE ABORTED!!!</font>");
    DECODE_ABORTED_FLAG = 1;
    out.Decoded = in.DataLength - 8 - DatLen;
}

####################################################################################
#                                   Utility functions                              #
####################################################################################

GetRNDISFieldOffset(FieldId)
{
    _row = Find(RNDIS_Request_Fields, FieldId);
    
    return _row[1];
}

AddDataPayloadFieldForRemain(offset)
{
    GetNBits(in.Data, offset * 8, 0);

    len = in.DataLength - 8;
    SetFieldOffsetLen(offset * 8, len * 8);
    ShowDataBlockReOrder(len);                
}

AddRNDISDataPayloadField(FieldId, offset, len)
{         
    _row = Find(RNDIS_Request_Fields, FieldId);

    offset = _row[1] + offset;
   
    if( DECODE_ABORTED_FLAG && offset >= DECODE_ABORTED_OFFSET )
        return 0;
    
    if( offset + len > in.DataLength )
    {        
        AddCell("NOT ENOUGH DATA","", "", WarningColor, _MONOFIELD);
        len = in.DataLength - offset;
    }

    GetNBits(in.Data, offset * 8, 0);

    SetFieldOffsetLen(offset * 8, len * 8);
    ShowDataBlockReOrder(len);                
    
    return 1;
}

AddRNDISDataPayloadFieldForRemain(FieldId, offset)
{
        _row = Find(RNDIS_Request_Fields, FieldId);
    
        offset = _row[1] + offset;
    
        len = in.DataLength - offset;
    
        if( offset + len > in.DataLength ) return 0;

        GetNBits(in.Data, offset * 8, 0);

        SetFieldOffsetLen(offset * 8, len * 8);
        ShowDataBlockReOrder(len);                
        
        return 1;
}

AddRNDISField(FieldId, offset)
{
    RetVal[0] = 0;
    RetVal[1] = 0;
    
    FieldOff = GetRNDISFieldOffset(FieldId);     

    if( !DECODE_ABORTED_FLAG || (offset + FieldOff) < DECODE_ABORTED_OFFSET )
    {
        RetVal = AddField(FieldId, offset, RNDIS_Request_Fields);
        if( !RetVal[0] )
        {
            DECODE_ABORTED_FLAG = 1;             
            DECODE_ABORTED_OFFSET = offset + FieldOff;

            AddCell("DECODE ABORTED", "NOT ENOUGH DATA", "", WarningColor, _ERROR); 
            AddSeparator();
        }        
    }
    
    return RetVal;
}

AddField(FieldId, offset, FieldsArray)
{    
        # Set to 1 if field is added successfully.
        ReturnValues[0] = 0; 
        # Field value if field is added successfully.
        ReturnValues[1] = 0;
        
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

        if( offset + len > in.DataLength ) return ReturnValues;
        
        if(len == 1)
        {
            value = GetDataByte(offset);
            value &= mask;
        }
        else if(len == 2)
        {        
            value = GetDataWord(offset);
            value &= mask;
        }
        else if(len == 3)        
        {
            value = GetDataLong(offset);
            value &= 0x00FFFFFF;
            value &= mask;
        }    
        else if(len == 4)        
        {
            value = GetDataLong(offset);
            value &= mask;
        }
        else
        {
			value = GetDataByteArray(offset, len);
            value = GetArrayHexString(value);
        }
            
        ReturnValues[0] = 1;        
        ReturnValues[1] = value;

        if(valuearray != null)
        {        
            if( isvaluebitmap == 1 )
            {
                strvalues = "";
                for( i = 0; i < len * 8; i++ )
                {                
                    maskedvalue = value & (1 << i);
                    if( maskedvalue )
                    {
                        if( strvalues != "" )
                            strvalues += ", ";
                    
                        _names = Find(valuearray, maskedvalue);
                        if(_names != null)
                            strvalues += Format( valueformat, _names[1] );    
                        else 
                            strvalues += Format( valueformat, Format("0x%04x", maskedvalue) );    
                    }
                }
    
                value = strvalues;
            }
            else
            {
                _names = Find(valuearray, value);            
                if(_names != null)
                    value = _names[1];
                else 
                    value = Format("0x%x", value);
            }

        }
            
        AddPayLoadCell(name, Format(valueformat, value), tooltip);
        
        return ReturnValues;
}


####################################################################################
#                       USBTracer specific caption cell                            #
####################################################################################

AddSpecCaptionCell(caption, text, tooltip, FieldColor, addparam, addparam1, addparam2 )
{   
    AddCell(caption, text, tooltip, FieldColor, _USBBULK_HEADER, addparam, addparam1, addparam2 );        
    return 1;        
}
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  WA_Descriptors.inc
#
#  Wire Adapter Descriptor decoders
#





const RESERVED = 1;


set HostWADescriptorTable =
[
# descr_type, name        , decoding function
    [ 0xFF, "Illegal"     , null         , null  ],
    [ 0x21, "WIRE_ADAPTER", "WAClass_sub", null  ],
    [ 0x22, "HostRPIPE"   , "HostRPipe_sub"  , null  ],
    [ 0x23, "RADIO_CONTROL","RADIO_CONTROL_sub", null]   
];

set DeviceWADescriptorTable =
[
# descr_type, name        , decoding function
    [ 0xFF, "Illegal"     , null         , null  ],
    [ 0x21, "WIRE_ADAPTER", "WAClass_sub", null  ],
    [ 0x22, "DeviceRPIPE" , "DeviceRPipe_sub"  , null  ],
    [ 0x23, "RADIO_CONTROL","RADIO_CONTROL_sub", null]   
];

TryWA_Descriptors(bDescriptorType)
{
   _row_vid = Find (HostWADescriptorTable, bDescriptorType);
   
   bLengh = 0;
   CurrentByteOffset = 0; 

   if (_row_vid[0] == 0xFF) 
       return 0;
   Call (_row_vid[1]);
   return 1;   
}



DecodeWADescriptor()
{
   # let's set the class-specific table 
   # ClassDescriptorTable = DWADescriptorTable;
   
   Base = 8;
   CurrentByteOffset = 0; 
   
   do_descriptor(); # this function is defined in UsbCommon.inc
}



#################################################################
#           Wire Adapter descriptor decoding functions
#################################################################



WIRE_ADAPTER()
{
    DescriptorCellString = "WIRE ADAPTER Descriptor";
     
    AddDataHeader( "WIRE ADAPTER Descriptor", in.DataLength - 8 );
    WAClass_sub();
    return GetFinalText();  
}


HostRPIPE()
{
    DescriptorCellString = "RPIPE Descriptor";
    
    AddDataHeader( "RPIPE Descriptor", in.DataLength - 8 );
    HostRPipe_sub();
    return GetFinalText();    
}

DeviceRPIPE()
{
    DescriptorCellString = "RPIPE Descriptor";
    
    AddDataHeader( "RPIPE Descriptor", in.DataLength - 8 );
    DeviceRPipe_sub();
    return GetFinalText();    
}




WAClass_sub()
{
    #
    # bLength
    #
    bLength = AddLengthEntry();
    if( CurrentByteOffset > MaxDataBytes ) return "";
    
    #
    # bDescriptorType
    #
    AddByteEntry( "bDescriptorType", GetDescriptorTypeString("WIRE ADAPTER") );
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #
    # bcdWAVersion
    #
    AddWordEntry( "bcdWAVersion", "WA Class Release Number in Binary-Coded Decimal." );
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #
    # bNumPorts
    #
    AddByteEntry( "bNumPorts", "The number of ports supported by this Wire Adapter.", 0, 1 );
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    #
    # bmAttributes
    #
    AddWAClassAttributeEntry();
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #
    # wNumRPipes
    #
    AddWordEntry( "wNumRPipes", "The number of RPipes supported by this Wire Adapter.", 0, 1 );
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #
    # wRPipeMaxBlock
    #
    AddWordEntry( "wRPipeMaxBlock", "The maximum number of buffer blocks assignable to all RPipes.", 0, 1 );
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #
    # bRPipeBlockSize
    #
    AddRPipeBlockSizeEntry();
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    
    #
    # bPwrOn2PwrGood
    #
    AddPwrOn2PwrGoodEntry();
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #
    # bNumMMCIEs
    #
    AddByteEntry( "bNumMMCIEs", "bNumMMCIEs field", 0, 1 );
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #
    # DeviceRemovable
    #
    
   # for( i = 0; CurrentByteOffset < MaxDataBytes; i++ )
   for( i = 0; CurrentByteOffset < bLength; i++ )
        AddDevRemovableEntry( i );
    
}

DeviceRPipe_sub()
{       
    #
    # bLength
    #
    AddLengthEntry();
    if( CurrentByteOffset > MaxDataBytes ) return "";
    
    #
    # bDescriptorType
    #
    AddByteEntry( "bDescriptorType", GetDescriptorTypeString("RPIPE") );
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #
    # wRPipeIndex
    #
    AddWordEntry( "wRPipeIndex", "Number of the RPipe.", 0, 1 );
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #
    # wRequests
    #
    AddWordEntry( "wRequests", "The number of concurrent requests that can be assigned to this RPipe.", 0, 1 );
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #
    # wBlocks
    #
    AddWordEntry( "wBlocks", "The number of buffer blocks assigned to this RPipe.", 0, 1 );
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #
    # wMaxPacketSize
    #
    AddWordEntry( "wMaxPacketSize", "Maximum packet size that this RPipe will use.", 0, 1 );
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    #
    # bHSHubAddress
    #
    AddByteEntry( "bHSHubAddress", "The address of the attached device’s parent high speed hub." );
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #
    # bHSHubPort
    #
    AddByteEntry( "bHSHubPort", "Device index where the device information buffer is present." );
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #
    # bSpeed
    #    
    AddSpeedEntry();
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #
    # bDeviceAddress
    #
    AddByteEntry( "bDeviceAddress", "Address to be used with attached device.", 0, 1 );
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    #
    # bEndpointAddress
    #
    AddEndpointEntry();
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #
    # bDataSequence
    #
    AddByteEntry( "bDataSequence", "Current data sequence.", 0, 1 );
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #
    # dwCurrentWindow
    #
    AddDwordEntry( "dwCurrentWindow", "Reserved and must be set to zero.", 0, 0, RESERVED );
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #AddCell( "CurrentByteOffset", Format("%d", CurrentByteOffset) );
    #AddCell( "MaxDataBytes", Format("%d", MaxDataBytes) );
    
    #
    # bMaxDataSequence
    #
    AddByteEntry( "bMaxDataSequence", "Reserved and must be set to zero.", 0, 0, RESERVED );
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
        
    #
    # bInterval
    #
    AddByteEntry( "bInterval", "Polling interval to be used by this RPipe.", 0, 1 );
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #
    # bOverTheAirInterval
    #
    AddByteEntry( "bOverTheAirInterval", "the interval at which the upstream wireless endpoint is polled.", 0, 1 );
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    #
    # bmAttribute
    #
    AddRPipeAttributeEntry();
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #
    # bmCharacteristics
    #
    AddCharacteristicsEntry();
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    
    #
    # bmRetryOptions
    #
    AddByteEntry( "bmRetryOptions", "The maximum number of times a transaction must be retried." );
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #
    # wNumTransactionErrors
    #
    AddWordEntry( "wNumTransactionErrors", "wNumTransactionErrors field.", 0, 1 ); 
        
}

HostRPipe_sub()
{       
    #
    # bLength
    #
    AddLengthEntry();
    if( CurrentByteOffset > MaxDataBytes ) return "";
    
    #
    # bDescriptorType
    #
    AddByteEntry( "bDescriptorType", GetDescriptorTypeString("RPIPE") );
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #
    # wRPipeIndex
    #
    AddWordEntry( "wRPipeIndex", "Number of the RPipe.", 0, 1 );
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #
    # wRequests
    #
    AddWordEntry( "wRequests", "The number of concurrent requests that can be assigned to this RPipe.", 0, 1 );
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #
    # wBlocks
    #
    AddWordEntry( "wBlocks", "The number of buffer blocks assigned to this RPipe.", 0, 1 );
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #
    # wMaxPacketSize
    #
    AddWordEntry( "wMaxPacketSize", "Maximum packet size that this RPipe will use.", 0, 1 );
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    #
    # bHSHubAddress
    #
    AddByteEntry( "bHSHubAddress", "Reserved and must be set to zero." , 0, 0, RESERVED );
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #
    # bHSHubPort
    #
    AddByteEntry( "bHSHubPort", "Device index where the device information buffer is present." );
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #
    # bSpeed
    #    
    AddSpeedEntry();
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #
    # bDeviceAddress
    #
    AddByteEntry( "bDeviceAddress", "Address to be used with attached device.", 0, 1 );
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    #
    # bEndpointAddress
    #
    AddEndpointEntry();
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #
    # bDataSequence
    #
    AddByteEntry( "bDataSequence", "Current data sequence.", 0, 1 );
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #
    # dwCurrentWindow
    #
    AddDwordEntry( "dwCurrentWindow", "Current window used for data sequence management and burst transfer.");
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #AddCell( "CurrentByteOffset", Format("%d", CurrentByteOffset) );
    #AddCell( "MaxDataBytes", Format("%d", MaxDataBytes) );
    
    #
    # bMaxDataSequence
    #
    AddByteEntry( "bMaxDataSequence", "Maximum sequence number that the endpoint supports.");
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
        
    #
    # bInterval
    #
    AddByteEntry( "bInterval", "Polling interval to be used by this RPipe.", 0, 1 );
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #
    # bOverTheAirInterval
    #
    AddByteEntry( "bOverTheAirInterval", "the interval at which the upstream wireless endpoint is polled.", 0, 1 );
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    #
    # bmAttribute
    #
    AddRPipeAttributeEntry();
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #
    # bmCharacteristics
    #
    AddCharacteristicsEntry();
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    
    #
    # bmRetryOptions
    #
    AddByteEntry( "bmRetryOptions", "The maximum number of times a transaction must be retried." );
    if( CurrentByteOffset >= MaxDataBytes ) return "";
    
    
    #
    # wNumTransactionErrors
    #
    AddWordEntry( "wNumTransactionErrors", "wNumTransactionErrors field.", 0, 1 ); 
        
}


RADIO_CONTROL()
{    
    DescriptorCellString = "RADIO_CONTROL Descriptor";
    Base = 8;
    AddDataHeader("RADIO_CONTROL Descriptor", in.DataLength-8);
    RADIO_CONTROL_sub();
    return GetFinalText();
}

RADIO_CONTROL_sub()
{

    base = Base;
    bLength             = GetDataByte(base);    
    bDescriptorType     = GetDataByte(base+1);    
    bcdRCIVersion       = GetDataWord(base+2);
    
    AddEntry( 0, "bLength", bLength, 2, "", 1);
    AddDescriptorSizeString(bLength);
    AddFieldBreak();
    
    AddEntry( 1, "bDescriptorType", bDescriptorType, 2, GetDescriptorTypeString("RADIO_CONTROL"), 0);
    AddFieldBreak();
    
    AddEntry( 2, "bcdRCIVersion", bcdRCIVersion, 4, "Radio Control Interface Version number in Binary-Coded Decimal.", 0);
    AddFieldBreak();
   
}



#################################################################
#              Add .. Entry helpers                             #
#################################################################


AddLengthEntry()
{
   val = GetDataByte( Base + CurrentByteOffset );
   
   AddEntry( CurrentByteOffset, "bLength", val, 2, "", 1, 1 );
   AddDescriptorSizeString(val);
   AddFieldBreak();
   
   IncCurrByteOffset( 1 );
return val;
}



AddSpeedEntry()
{
    val = GetDataByte( Base + CurrentByteOffset );
    
    rate_str = GetPhyRateDesc( val );
    description = "The speed of device to be targeted by RPipe.";
    
    AddEntry( CurrentByteOffset, "bSpeed", val, 2, description, 0, 0, rate_str );
    AddFieldBreak();
    
    IncCurrByteOffset( 1 );
}



AddEndpointEntry()
{
    val = GetDataByte( Base + CurrentByteOffset );
    
    endp = val & 0xF;
    dir  = val & 0x80;
    
    str = Format( "%d ", endp );
    
    if( dir ) str += "IN";
    else      str += "OUT";
    
    description = "Endpoint Address to be used with this RPipe.";
    
    AddEntry( CurrentByteOffset, "bEndpointAddress", val, 2, description, 0, 0, str );
    AddFieldBreak();
    
    IncCurrByteOffset( 1 );
}



AddRPipeAttributeEntry()
{
    val = GetDataByte( Base + CurrentByteOffset ); 
    
    transfer_type = val & 0x3;  # bits 1:0
    endp = ( val & 0x3C ) >> 2; # bits 5:2
    
    select
    {
        transfer_type == 0b00 : str = "CTRL";   
        transfer_type == 0b01 : str = "ISOCH" + Format( ", ENDP:%d", endp );
        transfer_type == 0b10 : str = "BULK";
        transfer_type == 0b11 : str = "INRPT";
    };
    
    
    AddEntry( CurrentByteOffset, "bmAttribute", val, 2, "bmAttribute field.", 0, 0, str );
    AddFieldBreak();
    
    IncCurrByteOffset( 1 );
}



AddCharacteristicsEntry()
{
    val = GetDataByte( Base + CurrentByteOffset );    
    bit_set = 0;
    
    str = "";
    
    # bit 0
    if( val & 0b0001 ) 
    { 
        str += "CTRL";
        bit_set = 1; 
    }
    
    #bit 1
    if( val & 0b0010 )
    { 
        if( bit_set ) str += ",ISOCH";
        else          str += "ISOCH"; 
        bit_set = 1;        
    }
    
    #bit 2
    if( val & 0b0100 )
    { 
        if( bit_set ) str += ",BULK";
        else          str += "BULK"; 
        bit_set = 1;
    }
    
    
    #bit 3
    if( val & 0b1000 )
    { 
        if( bit_set ) str += ",INRPT";
        else          str += "INRPT"; 
        bit_set = 1;                
    }   
    
    if( !bit_set )
        str = "NONE";
    
    
    AddEntry( CurrentByteOffset, "bmCharacteristics", val, 2, "Transfer types supported on this RPipe.", 0, 0, str );
    AddFieldBreak();
    
    IncCurrByteOffset( 1 );
}






GetPhyRateDesc( rate )
{
    str = select 
    {
        rate == 0b00000 : "53.3 Mbs";
        rate == 0b00001 : "80 Mbs";
        rate == 0b00010 : "106.7 Mbs";
        rate == 0b00011 : "160 Mbs";
        rate == 0b00100 : "200 Mbs";
        rate == 0b00101 : "320 Mbs";
        rate == 0b00110 : "400 Mbs";
        rate == 0b00110 : "480 Mbs";
        
        default         : Format("Unknown(%d)", rate);
    };
    
    
    return str;    
}


AddWAClassAttributeEntry()
{
   val = GetDataByte( Base + CurrentByteOffset );
   
   str = GetBinaryString( val, 8 );   
   
   
   AddEntry( CurrentByteOffset, "bmAttributes", val, 2, "bmAttributes field", 0, 0, str );   
   AddFieldBreak();
   
   IncCurrByteOffset( 1 );
}


AddRPipeBlockSizeEntry()
{
   val = GetDataByte( Base + CurrentByteOffset );
   
   if( val )
   {
        block_size = 0x1 << ( val - 1 );   
        str = Format( "%d bytes", block_size );
   }
   else
        str = "0 bytes";
    
   
   AddEntry( CurrentByteOffset, "bRPipeBlockSize", val, 2, "The size of an RPipe buffer block.", 0, 0, str );   
   AddFieldBreak();
   
   IncCurrByteOffset( 1 );
}


AddPwrOn2PwrGoodEntry()
{
   val = GetDataByte( Base + CurrentByteOffset ) * 2;   
   
   str = Format( "%d ms", val );    
   
   AddEntry( CurrentByteOffset, "bPwrOn2PwrGood", val, 2, "Time from the power-on until power is good on that port.", 0, 0, str );   
   AddFieldBreak();
   
   IncCurrByteOffset( 1 );    
}



AddDevRemovableEntry( byte_num )
{
   val = GetDataByte( Base + CurrentByteOffset );
   
   str = GetBinaryString( val, 8 );   
   
   AddEntry( CurrentByteOffset, Format("DeviceRemovable(%d)", byte_num ), val, 2, Format( "DeviceRemovable, byte: %d", byte_num ), 0, 0, str );   
   AddFieldBreak();
   
   IncCurrByteOffset( 1 );
}

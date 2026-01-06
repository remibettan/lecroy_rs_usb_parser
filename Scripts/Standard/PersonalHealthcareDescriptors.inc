#******************************************************************************
#
#  FILENAME: PersonalHealthcareDescriptors.inc
#
#  Copyright (C) 2008 LeCroy Corporation
#
#  DESCRIPTION
#    This descriptor definition file is supplied by LeCroy.
#    This file defines standard USB Personal Healthcare Descriptors.
#    File version is 1.0.
#       Based on Personal Healthcare Devices Revision 1.0 released November 8, 2007
#
#  REVISION HISTORY
#    03/01/2008  Created - RK and JC
#
#******************************************************************************

set PersonalHealthcareDescriptorTypeTable =        #Table for Personal Healthcare Device Class specific Descriptor Type
[
    [ 0xFF, "UNKNOWN" ],
    [ 0x20, "PHDC_CLASSFUNCTION_DESCRIPTOR", "PHDC CLASS FUNCTION" ],
    [ 0x21, "PHDC_QOS_DESCRIPTOR", "PHDC QOS" ],
    [ 0x22, "PHDC_METADATA_DESCRIPTOR", "PHDC METADATA" ],
    [ 0x30, "PHDC_11073PHD_FUNCTION_DESCRIPTOR", "PHDC 11073 PHD FUNCTION EXTENSION" ]
];

TryPersonalHealthcareDescriptors(bDescriptorType)  #If (Personal Healthcare Device Class specific descriptor) decode; else return 0
{
    CurrentByteOffset = 0;                                                     #Global variable from UsbCommon.inc
    PHDC_row = Find (PersonalHealthcareDescriptorTypeTable, bDescriptorType);    #Find specific descriptor

    if (PHDC_row[0] == 0xFF)
        return 0;
	
    AddShortDataHeader( PHDC_row[2] + FormatEx( " Descriptor (%d bytes)", bLength ) );

    dataLength = bLength;                   #Length of Data from encapsulating call: bLength is defined in StandardDescriptors.inc
                                            #via other .inc files; this file is included in StandardDescriptors.inc

    if (dataLength > in.DataLength - Base ) #Checking if there is enough data
    {
      AddStringToDlg("Not enough data for this descriptor",FormatEx("Expected Length %d bytes, Actual Length %d bytes", dataLength, in.DataLength - Base), OutputUnknownData(in.DataLength - Base, 0));
      return 0;
    }

    Call (PHDC_row[1]);
    return 1;
}

PHDC_CLASSFUNCTION_DESCRIPTOR()
{
    base = Base;
    bLength         = GetDataByte(base);
    bDescriptorType = GetDataByte(base+1);
    bPHDCDataCode   = GetDataByte(base+2);
    bmCapability    = GetDataByte(base+3);

    AddEntry( 0, "bLength", bLength, 2, "Descriptor size, in bytes (including this field)", 0, 1);
    AddDescriptorSizeString(bLength);
    AddFieldBreak();

    AddEntry( 1, "bDescriptorType", bDescriptorType, 2, "PHDC_CLASSFUNCTION_DESCRIPTOR Type", 0);
    AddFieldBreak();

    if ( bPHDCDataCode & 0x01 )
        str_PHDCDataCode = "Data/Messaging Format Code:<br> &nbsp&nbsp&nbsp&nbsp&nbsp&nbsp0x01 - vendor defined standard";
    else if ( bPHDCDataCode & 0x02 )
        str_PHDCDataCode = "Data/Messaging Format Code:<br> &nbsp&nbsp&nbsp&nbsp&nbsp&nbsp0x02 - ISO/IEEE 11073-20601 Optimized Exchange Protocol";
    else
        str_PHDCDataCode = "Unsupported Data/Messaging Format Code. The descriptor is invalid.";

    AddEntry( 2, "bPHDCDataCode", bPHDCDataCode, 2,  str_PHDCDataCode , 0);
    AddFieldBreak();

    if ( bmCapability & 0x01)
        str_bmCapbility = "The Meta-Data Message Preamble feature defined.";
    else
        str_bmCapbility = "The Meta-Data Message Preamble feature not defined.";

    if( bmCapability & 0xFE)
        str_bmCapbility += "<br><font color=\"ORANGE\">&nbsp&nbsp!!! WARNING !!!\n&nbsp&nbspBits 7..1 are reserved and must be set to 0 !</font>";

    AddEntry( 3, "bmCapability", bmCapability, 2, str_bmCapbility , 0);
    AddFieldBreak();
}

PHDC_QOS_DESCRIPTOR()
{
    base = Base;
    bLength              = GetDataByte(base);
    bDescriptorType      = GetDataByte(base+1);
    bQoSEncodingVersion  = GetDataByte(base+2);
    bmLatencyReliability = GetDataByte(base+3);

    AddEntry( 0, "bLength", bLength, 2, "Descriptor size, in bytes (including this field)", 0, 1);
    AddDescriptorSizeString(bLength);
    AddFieldBreak();

    AddEntry( 1, "bDescriptorType", bDescriptorType, 2, "PHDC_QOS_DESCRIPTOR Type", 0);
    AddFieldBreak();

    AddEntry( 2, "bQoSEncodingVersion", bQoSEncodingVersion, 2, "0x01 = version 1 QoS information encoding", 0);
    AddFieldBreak();

    if(bQoSEncodingVersion == 1)
    {
        str_bmLatencyRelibility = "If bQoSEncodingVersion = 0x01, then this bitmap refers to the latency/reliability<br> &nbsp&nbspbin for the QoS data. <br>&nbsp&nbspBitmap:";
        if( (bmLatencyReliability & 0x40 ) || ( bmLatencyReliability & 0x80 ) )
            str_bmLatencyRelibility += "<br>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp Bit 6-7: reserved and set to 0.";
        if( bmLatencyReliability & 0x20 )
            str_bmLatencyRelibility += "<br>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp Bit 5: Very High. Best Latency, reliability bin.";
        if( bmLatencyReliability & 0x10 )
            str_bmLatencyRelibility += "<br>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp Bit 4: High. Best Latency, reliability bin.";
        if( bmLatencyReliability & 0x08 )
            str_bmLatencyRelibility += "<br>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp Bit 3: Medium. Best Latency, reliability bin.";
        if( bmLatencyReliability & 0x04 )
            str_bmLatencyRelibility += "<br>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp Bit 2: Medium. Better Latency, reliability bin.";
        if( bmLatencyReliability & 0x02 )
            str_bmLatencyRelibility += "<br>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp Bit 1: Medium. Good Latency, reliability bin.";
        if( bmLatencyReliability & 0x01 )
            str_bmLatencyRelibility += "<br>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp Bit 0: Low. Good latency, reliability bin.";
    }
    else
         str_bmLatencyRelibility = "If bQoSEncodingVersion = 0x01, then this bitmap refers to the latency/reliability<br> &nbsp&nbspbin for the QoS data. <br>&nbsp&nbspBitmap:<br>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp Undefined Bitmap";

    AddEntry( 3, "bmLatencyReliability", bmLatencyReliability, 2, str_bmLatencyRelibility , 0);
    AddFieldBreak();
}

PHDC_METADATA_DESCRIPTOR()
{
    base = Base;
    bLength         = GetDataByte(base);
    bDescriptorType = GetDataByte(base+1);
    bOpaqueData     = "0x";
    index = 0;
    val = 0;
    while (index < (bLength-2))
    {
        val = GetDataByte((base+2) + index);
        bOpaqueData += Format("%02X", val);
        index++;
    }

    SetFieldOffsetLen(((base+2)+(bLength-2))*8, 8);

    AddEntry( 0, "bLength", bLength, 2, "Descriptor size, in bytes (including this field)", 0, 1);
    AddDescriptorSizeString(bLength);
    AddFieldBreak();

    AddEntry( 1, "bDescriptorType", bDescriptorType, 2, "PHDC_METADATA_DESCRIPTOR Type", 0);
    AddFieldBreak();

    AddEntry( 2, "bOpaqueData", bOpaqueData, ((bLength-2)*2), "Opaque meta-data", 0, 0, bOpaqueData );
    AddFieldBreak();
}

PHDC_11073PHD_FUNCTION_DESCRIPTOR()
{
    base = Base;
    bLength             = GetDataByte(base);
    bDescriptorType     = GetDataByte(base+1);
    bReserved           = GetDataByte(base+2);
    bNumDevSpecs        = GetDataByte(base+3);
    bDevSpecializations = "0x";
    index = 0;
    val = 0;
    while (index < (bLength-4))
    {
        val = GetDataByte((base+4) + index);
        bDevSpecializations += Format("%02X", val);
        index++;
    }

    SetFieldOffsetLen(((base+4)+(bLength-4))*8, 8);

    AddEntry( 0, "bLength", bLength, 2, "Descriptor size, in bytes (including this field)", 0, 1);
    AddDescriptorSizeString(bLength);
    AddFieldBreak();

    AddEntry( 1, "bDescriptorType", bDescriptorType, 2, "PHDC_11073PHD_FUNCTION_DESCRIPTOR Type", 0);
    AddFieldBreak();

    str_bReserved = "Reserved for future use.";
    if ( !(bReserved & 0x00) )
        str_bReserved += " WARNING: Must be zero.<br>";

    AddEntry( 2, "bReserved", bReserved, 2,  str_bReserved , 0);
    AddFieldBreak();

    AddEntry( 3, "bNumDevSpecs", bNumDevSpecs, 2,  "Number of wDevSpecializations" , 0, 1);
    AddFieldBreak();

    TestNumDev = (bLength - 4) % 2;
    if (TestNumDev != 0)
        AddEntry( 4, "bDevSpecializations", bDevSpecializations, ((bLength-4)*2), "<font color=\"ORANGE\">!!! WARNING !!! \n&nbsp&nbspbNumDevSpecs is invalid</font>", 0, 0, bDevSpecializations );
    else
        AddEntry( 4, "bDevSpecializations", bDevSpecializations, ((bLength-4)*2), "list from Communication Infrastructure", 0, 0, bDevSpecializations );

    AddFieldBreak();
}

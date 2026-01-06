#******************************************************************************
#
#  FILENAME: ContentSecurityDescriptors.inc
#
#  Copyright (C) 2008 LeCroy Corporation
#
#  DESCRIPTION
#    This descriptor definition file is supplied by LeCroy.
#    This file defines standard USB Content Security descriptors.
#    File version is 1.0.
#       Based on Content Security Devices Revision 1.0 released August 2000
#
#  REVISION HISTORY
#    03/01/2008 Created. - RK and JC
#
#******************************************************************************

set ContentSecurityDescriptorTypeTable =        #Table for Content Security Device Class specific Descriptor Type
[
    [ 0xFF, "UNKNOWN" ],
    [ 0x21, "CS_GENERAL_DESCRIPTOR" , "CS GENERAL" ],
    [ 0x22, "CHANNEL_DESCRIPTOR"    , "CHANNEL" ],
    [ 0x23, "CSM_DESCRIPTOR"        , "CONTENT SECURITY METHOD" ],
    [ 0x24, "CSMV_DESCRIPTOR"       , "CONTENT SECURITY METHOD VARIANT" ]
];

TryContentSecurityDescriptors(bDescriptorType)  #If (Content Security Device Class specific descriptor) decode; else return 0
{
    CurrentByteOffset = 0;                                                  #Global variable from UsbCommon.inc
    CS_row = Find (ContentSecurityDescriptorTypeTable, bDescriptorType);    #Find specific descriptor

    if (CS_row[0] == 0xFF)
    {
        if ((bDescriptorType >= 0x25) && (bDescriptorType <= 0x3F))
        {
            AddShortDataHeader("Reserved for future extension");
            return 0;
        }
        else
            return 0;
    }

    AddShortDataHeader( CS_row[2] + FormatEx( " Descriptor (%d bytes)", bDescriptorType, bLength ) );

    base = Base;

    dataLength = bLength;                   #Length of Data from encapsulating call: bLength is defined in StandardDescriptors.inc
                                            #via other .inc files; this file is included in StandardDescriptors.inc

    if (dataLength > in.DataLength - Base ) #Checking there is enough data
    {
        AddStringToDlg( "Not enough data for this descriptor", FormatEx( "Length required %d bytes, Actual Length %d bytes", dataLength, in.DataLength - Base ), OutputUnknownData( in.DataLength - Base, 0 ) );
        return 0;
    }

    bLength         = GetDataByte(base);
    bDescriptorType = GetDataByte(base+1);

    AddEntry( 0, "bLength", bLength, 2, "Descriptor size, in bytes (including this field)", 0, 1 );
    AddDescriptorSizeString(bLength);
    AddFieldBreak();

    AddEntry( 1, "bDescriptorType", bDescriptorType, 2, CS_row[1] + " Type", 0 );
    AddFieldBreak();

    Call(CS_row[1]);
    return 1;
}

CS_GENERAL_DESCRIPTOR()
{
    bcdVersion = GetDataWord(base+2);
    AddEntry( 2, "bcdVersion", bcdVersion, 4,  "Content Security Interface Version number in Binary-Coded Decimal (i.e. version 2.10 is 0x0210)." , 0 );
    AddFieldBreak();
}

CHANNEL_DESCRIPTOR()
{
    base = Base;
    length_counter = 2;
    method_index_counter = 0;

    bChannelID            = GetDataByte(base+length_counter++);
    bmAttributes          = GetDataByte(base+length_counter++);
    bRecipient            = GetDataByte(base+length_counter++);
    bRecipientAlt         = GetDataByte(base+length_counter++);
    bRecipientLogicalUnit = GetDataByte(base+length_counter++);

    AddEntry( 2, "bChannelID", bChannelID, 2, "The Channel Number must be a zero-based value that is unique across the device.", 0 );
    AddFieldBreak();

    str_bmAttributes = "";
    str_bmAttributes = "D7..D5:  Reserved and set to zero. \n&nbsp&nbspD4..D0: Recipient Type\n";

    if( bmAttributes == 0 )
        str_bmAttributes = "&nbsp&nbsp&nbsp&nbspRecipient Type is Not Used";
    else if( bmAttributes == 1 )
        str_bmAttributes = "&nbsp&nbsp&nbsp&nbspRecipient Type is Interface.";
    else if( bmAttributes == 2 )
        str_bmAttributes = "&nbsp&nbsp&nbsp&nbspRecipient Type is Endpoint.";
    else if( bmAttributes >= 3 && bmAttributes <= 31 )
        str_bmAttributes = "&nbsp&nbsp&nbsp&nbspRecipient Type is Reserved.";

    AddEntry( 3, "bmAttributes", bmAttributes, 2, str_bmAttributes , 0 );
    AddFieldBreak();

    str_bRecipient = "Identifier of the target recipient.";

    if( bmAttributes == 1 )
        str_bRecipient += "<br>The Recipient type field of bmAttributes = 1, thus the value in the bRecipient field is the bInterfaceNumber.";
    else if( bmAttributes == 2 )
    {
        str_bRecipient += "<br>The Recipient type field of bmAttributes = 2, thus the value in the bRecipient field is an enpoint address, where:";
        str_bRecipient += "<BR>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp D7: Direction";
        str_bRecipient += "<BR>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp 0 = OUT";
        str_bRecipient += "<BR>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp 1 = IN";
        str_bRecipient += "<BR>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp D6...D4: Reserved and set to zero";
        str_bRecipient += "<BR>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp D3...D0: Endpoint number";
    }

    AddEntry( 4, "bRecipient", bRecipient, 2, str_bRecipient , 0 );
    AddFieldBreak();

    if( bmAttributes == 1 )
        str_bRecipientAlt = "bRecipientAlt is the alternate setting for the interface to which this channel applies.";
    else
        str_bRecipientAlt = "bRecipientAlt should be set to 0 since bmAttributes is not equal to 1.";

    AddEntry( 5, "bRecipientAlt", bRecipientAlt, 2, str_bRecipientAlt , 0 );
    AddFieldBreak();

    str_bRecipientLogicalUnit = "The definition of a LU is dependent upon the interface being protected.";

    if ( bmAttributes == 1 )
        str_bRecipientLogicalUnit += " <BR>&nbsp&nbspbRecipientLogicalUnit is the logical unit within the protected interface to which this channel applies.";
    else
        str_bRecipientLogicalUnit += " <BR>&nbsp&nbspSince bmAttributes is not set to the interface, then bRecipientLogicalUnit should be set to 0.";

    AddEntry( 6, "bRecipientLogicalUnit", bRecipientLogicalUnit, 2, str_bRecipientLogicalUnit , 0 );
    AddFieldBreak();

    str_bMethod  = "Index of a class-specific CSM descriptor that describes one of the Content Security Methods offered";
    str_bMethod += " <BR>&nbsp&nbspby the device, must be a one-based value that is unipue accross the device.  The value of 0(zero)";
    str_bMethod += " <BR>&nbsp&nbspis reserved and must not be used in this field.";

    str_bMethodVariant  = "Zero-based value that points to a CSM Variant descriptor.";
    str_bMethodVariant += " <BR>&nbsp&nbspIf there is no CSM Variant descriptor then it has the value of zero.";

    for( ; ( (length_counter + 2) <= bLength ) ; )
    {
        bMethod[method_index_counter] = GetDataByte(base+length_counter);
        str_bMethod_extra = str_bMethod;

        if( bMethod[method_index_counter] == 1 )
            str_bMethod_extra += Format(" <BR>&nbsp&nbspbbMethod[%d] - Basic Authentication Protocol", method_index_counter);
        else if( bMethod[method_index_counter] == 2 )
            str_bMethod_extra += Format(" <BR>&nbsp&nbspbbMethod[%d] - USB Digital Transmission Content Protection Implementation", method_index_counter);
        else if( bMethod[method_index_counter] == 3 )
            str_bMethod_extra += Format(" <BR>&nbsp&nbspbbMethod[%d] - Open Copy Protection System", method_index_counter);
        else if( bMethod[method_index_counter] == 4 )
            str_bMethod_extra += Format(" <BR>&nbsp&nbspbbMethod[%d] - Elliptic Curve Content Protection Protocol", method_index_counter);

        AddEntry( length_counter, Format( "bMethod[%d]", bMethod[method_index_counter], 2, str_bMethod_extra , 0 ) );
        AddFieldBreak();
        length_counter++;

        bMethodVariant[method_index_counter] = GetDataByte(base+length_counter);
        AddEntry( length_counter, Format( "bMethodVariant[%d]", bMethodVariant[method_index_counter], 2, str_bMethodVariant , 0 ) );
        AddFieldBreak();
        length_counter++;

        method_index_counter++;
    }

    if( ( bLength % 2 ) == 1 )
    {
        undecoded = GetDataByte(base+length_counter);
        AddEntry( length_counter, "Undecoded", undecoded, 2, "Undecoded byte" , 0 );
    }
}

CSM_DESCRIPTOR()
{
    base = Base;

    bMethodID       = GetDataByte(base+2);
    iCSMDescriptor  = GetDataByte(base+3);
    bcdVersion      = GetDataWord(base+4);

    str_bMethodID = "Index of a class-specific CSM descriptor that describes one of the Content Security Methods offered by the device, must be a one-based value that is unique across the device. The value of 0 (zero) is reserved and must not be used in this field.";

    if( bMethodID == 1 )
        str_bMethodID += Format( "<br>&nbsp&nbspbbMethod[%d] - Basic Authentication Protocol", method_index_counter );
    else if( bMethodID == 2 )
        str_bMethodID += Format( "<br>&nbsp&nbspbbMethod[%d] - USB Digital Transmission Content Protection Implementation", method_index_counter );
    else if( bMethodID == 3 )
        str_bMethodID += Format( "<br>&nbsp&nbspbbMethod[%d] - Open Copy Protection System", method_index_counter );
    else if( bMethodID == 4 )
        str_bMethodID += Format( "<br>&nbsp&nbspbbMethod[%d] - Elliptic Curve Content Protection Protocol", method_index_counter );

    AddEntry( 2, "bMethodID", bMethodID, 2, str_bMethodID , 0 );
    AddFieldBreak();

    AddEntry( 3, "iCSMDescriptor", iCSMDescriptor, 2, "Index of string descriptor that describes the Content Security Method", 0 );
    AddFieldBreak();

    AddEntry( 4, "bcdVersion", bcdVersion, 4,  "Content Security Interface Version number in Binary-Coded Decimal(i.e. version 2.10 is 0x0210)." , 0 );
    AddFieldBreak();

    CSMData = "0x";
    index = 0;
    val = 0;

    while( index < ( bLength-6 ) )
    {
        val = GetDataByte((base+6) + index);
        CSMData += Format( "%02X", val );
        index++;
    }

    SetFieldOffsetLen( ( ( base+6 ) + ( bLength-6 ) )*8, 8*(bLength-6) );

    AddEntry( 6, "CSMData", CSMData, ((bLength-6)*2), "Optional field(s) that provides device-specific implementation details for the CSM identified by the bMethodID field.", 0, 0, CSMData );
    AddFieldBreak();
}

CSMV_DESCRIPTOR()
{
    base     = Base;

    CSMVData = "0x";
    index    = 0;
    val      = 0;

    while (index < (bLength-2))
    {
        val = GetDataByte((base+2) + index);
        CSMVData += Format( "%02X", val );
        index++;
    }

    SetFieldOffsetLen( ( ( base+2 ) + ( bLength-2 ) )*8, 8 );

    AddEntry( 2, "CSMVData", CSMVData, ( (bLength-2) * 2 ), "Optional field(s) that provides device-specific implementation details for the CSM Variant.", 0, 0, CSMVData );
    AddFieldBreak();
}
#******************************************************************************
#
#  FILENAME: PersonalHealthcareDescriptors.inc
#
#  Copyright (C) 2016 Teledyne LeCroy Corporation
#
#  DESCRIPTION
#    This descriptor definition file is supplied by Teledyne LeCroy.
#    This file defines standard USB Type-C Bridge Descriptors.
#
#******************************************************************************

%include "..\TypeC\TypeC_Common.inc"

set TypeC_BridgeDescriptorTypeTable = [
    [ 0xFF, "UNKNOWN"                                                                             ],
    [ 0x21, "BRIDGE_CAPABILITY", "TypeC_Bridge_BRIDGE_CAPABILITY", "Bridge Capability descriptor" ]
];

TryTypeCBridgeDescriptors(bDescriptorType)
{
    _row = Find (TypeC_BridgeDescriptorTypeTable, bDescriptorType);    #Find specific descriptor

    if (_row[0] == 0xFF)
        return 0;
	
    AddShortDataHeader( _row[3] + FormatEx( " Descriptor (%d bytes)", bLength ) );

    dataLength = bLength;                   #Length of Data from encapsulating call: bLength is defined in StandardDescriptors.inc
                                            #via other .inc files; this file is included in StandardDescriptors.inc

    if (dataLength > in.DataLength - Base ) #Checking if there is enough data
    {
      AddStringToDlg("Not enough data for this descriptor",FormatEx("Expected Length %d bytes, Actual Length %d bytes", dataLength, in.DataLength - Base), OutputUnknownData(in.DataLength - Base, 0));
      return 0;
    }

    Call ( _row[2] );
    
    return 1;
}

set BridgeCapAttribuites_BitTable =
[
    [ 0, "Support PPM functionality"],
    [ 1, "Support PAM functionality"],
    [ 2, "Support PFUM functionality"],
    [ 3, "Support Billboard functionality"],
    [ 4, "Reserved and shall be set to zero"],
    [ 5, "Reserved and shall be set to zero"],
    [ 6, "Reserved and shall be set to zero"],
    [ 7, "Reserved and shall be set to zero"]
];

set BridgeCapability_Fields = [
    ["bcdVersion",      16, 16, 0xFFFF, "bcdVersion",      "0x%X", null,                          0, "Version of the USB Type-C Bridge Specification that the USB Type-C Bridge is compliant to and shall be set to 0100h."],
    ["bmConnectorMask", 32, 16, 0xFFFF, "bmConnectorMask", "%s",   null,                          1, "This field indicates which of the Connector on the Device Container the USB Type-C Bridge can communicate with. The maximum number of Connectors a USB Type-C Bridge can support is limited to fifteen. If a bit is set to one, then the USB Type-C Bridge shall be able communicate with that Connector."],
    ["bmAttributes",    48,  8, 0xFF,   "bmAttributes",    "%s",   BridgeCapAttribuites_BitTable, 1, "Attributes"]
];

TypeC_Bridge_BRIDGE_CAPABILITY()
{
    DECODE_ABORTED_FLAG = 0;
    data_bit_offset = Base * 8;
    FieldColor = BRIDGE_CAPABILITY_COLOR;
    for( i = 0; BridgeCapability_Fields[i][0] != null; i++ )
    {
        AddTypeCField( BridgeCapability_Fields[i][0], data_bit_offset, BridgeCapability_Fields );
    }
}

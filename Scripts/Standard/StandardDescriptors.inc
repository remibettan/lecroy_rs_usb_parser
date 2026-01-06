#******************************************************************************
#
#  FILENAME: StandardDescriptors.inc
#
#  Copyright (C) 2004 Computer Access Technology Corporation
#
#  DESCRIPTION
#    This descriptor definition file is supplied by CATC.
#    This file defines standard USB descriptors.
#    File version is 1.1.
#
#    09/24/2001  Added  DEVICE_QUALIFIER and OTHER_SPEED_CONFIGURATION
#    10/01/2001  Added  OTG
#    05/11/2004  Added  INTERFACE_ASSOCIATION and Video and Miscellaneous classes
#    05/20/2004  Converted to Script Decoding Language
#    06/13/2005  Add Wireless USB descriptors (0x0C through 0x11)
#    12/28/2006  Added CBAF Interface (0x03) to Miscellaneous Device SubClass Table
#    01/03/2007  Modified DescriptorTypeTable (Removed 0x21,0x22,0x23 - Hid_Specific)
#                The removed types are now in table Hid_Descriptors in Hid\Hid_descr.inc
#    01/04/2007  Added Smart Card Class (0x0B), SC_ProtocolTable, and TrySmartCard_Descriptor
#                call and included function definition include file SmartCardDescriptors.inc
#    03/13/2007  Added CDC Wireless Protocols and replaced all tabs in file w/ spaces as
#                well as added appropriate indentation for this file.  - RK
#    03/28/2007  Corrected Endpoint Descriptor decoding to show transfer type. - RK
#    04/03/2007  Added 0xFE Application Specific Class to Device Class Table. Also added
#                an implementation for SubClass Specific Protocol Codes. Example is in
#                function INTERFACE_sub for App-specific class. - RK
#    07/09/2007  Added table DesciptorTypeTableEx and function FindDescriptorEntryEx(). This
#                is to resolve HID Descriptors (change made on 01/03/2007 had other
#                ramifications). HID Descriptors work outside of Configuration, so they are
#                checked w/ FindDescriptorEntry() & Config w/ FindDescriptorEntryEx(). - RK
#    03/15/2008  Added 0x0F Personal Healtchare and 0x0D Content Security Classes and their
#                respective TryDescriptor functions in doSharedConfig(). - RK and JC
#    10JUN08 Updated according to USB 3.0 ver0.85 
#    05JUL08 Added error handling  
#    01SEP08 Updated according to USB 3.0 ver0.9  
#    09Sep11 Jake updated OTG descriptor to 2.00 format
#    15DEC16 Adding Audio 3.0
#			 Adding Interface Association Descriptor's Subclass function to the DeviceClassTable, because some Classes like Audio 2.0 and 3.0
#			 have different interpretation of Subclass code in Interface Association Descriptor(function subclass) and Interface descriptor(interface subclass).
#******************************************************************************

%include "companies.inc"
%include "..\Shared\VideoTables.inc"
%include "..\Shared\ErrorHandlingMessages.inc"
%include "DFU_descr.inc"
%include "TypeCBridgeDescriptors.inc"
%include "AudioDescriptors.inc"

#Descriptor Type Table w/ HID Specific Types since HID Devices have no "Configuration"
set DescriptorTypeTable =
[
   [ 0xFF, "Illegal"                    ,"Illegal_sub"                   ],
   [ 0x01, "DEVICE"                     ,"DEVICE_sub"                    ],
   [ 0x02, "CONFIGURATION"              ,"CONFIGURATION_sub"             ],
   [ 0x03, "STRING"                     ,"STRING_sub"                    ],
   [ 0x04, "INTERFACE"                  ,"INTERFACE_sub"                 ],
   [ 0x05, "ENDPOINT"                   ,"ENDPOINT_sub"                  ],
   [ 0x06, "DEVICE_QUALIFIER"           ,"DEVICE_QUALIFIER_sub"          ],
   [ 0x07, "OTHER_SPEED_CONFIGURATION"  ,"OTHER_SPEED_CONFIGURATION_sub" ],
   [ 0x08, "INTERFACE_POWER"            ,"INTERFACE_POWER_sub"           ],
   [ 0x09, "OTG"                        ,"OTG_sub"                       ],
   [ 0x0B, "INTERFACE_ASSOCIATION"      ,"INTERFACE_ASSOCIATION_sub"     ],
   [ 0x0C, "SECURITY"                   ,"SECURITY_sub"                  ],
   [ 0x0D, "KEY"                        ,"KEY_sub"                       ],
   [ 0x0E, "ENCRYPTION_TYPE"            ,"ENCRYPTION_TYPE_sub"           ],
   [ 0x0F, "BOS"                        ,"BOS_sub"                       ],
   [ 0x10, "DEVICE_CAPABILITY"          ,"DEVICE_CAPABILITY_sub"         ],
   [ 0x11, "WIRELESS_ENDPOINT_COMPANION","WIRELESS_ENDPOINT_COMPANION_sub"],
   [ 0x21, "HID_DESCRIPTOR"             ,"Hid_class_sub"                 ],   #HID-Specific
   [ 0x22, "REPORT_DESCRIPTOR"          ,"Hid_Report_sub"                ],   #HID-Specific
   [ 0x23, "PHYSICAL_DESCRIPTOR"        ,"Hid_Physical_sub"              ],   #HID-Specific
   [ 0x30, "SUPERSPEED_USB_ENDPOINT_COMPANION", "SUPERSPEED_USB_ENDPOINT_COMPANION_sub"],
   [ 0x31, "SUPERSPEEDPLUS_ISOCHRONOUS_ENDPOINT_COMPANION", "SUPERSPEEDPLUS_ISOCHRONOUS_ENDPOINT_COMPANION_sub"]
];

set DescriptorTypeTableForUSB3 =
[
   [ 0xFF, "Illegal"                    ,"Illegal_sub"                   ],
   [ 0x01, "DEVICE"                     ,"DEVICE_sub"                    ],
   [ 0x02, "CONFIGURATION"              ,"CONFIGURATION_sub"             ],
   [ 0x03, "STRING"                     ,"STRING_sub"                    ],
   [ 0x04, "INTERFACE"                  ,"INTERFACE_sub"                 ],
   [ 0x05, "ENDPOINT"                   ,"DecodeEndpointForUSB3"         ],
   [ 0x06, "Reserved"           ,""          ],
   [ 0x07, "Reserved"  ,"" ],
   [ 0x08, "INTERFACE_POWER"            ,"INTERFACE_POWER_sub"           ],
   [ 0x09, "OTG"                        ,"OTG_sub"                       ],
   [ 0x0A, "Debug" ,""], 
   [ 0x0B, "INTERFACE_ASSOCIATION"      ,"INTERFACE_ASSOCIATION_sub"     ],
   [ 0x0C, "SECURITY"                   ,"SECURITY_sub"                  ],
   [ 0x0D, "KEY"                        ,"KEY_sub"                       ],
   [ 0x0E, "ENCRYPTION_TYPE"            ,"ENCRYPTION_TYPE_sub"           ],
   [ 0x0F, "BOS"                        ,"BOS_sub"                       ],
   [ 0x10, "DEVICE_CAPABILITY"          ,"DEVICE_CAPABILITY_sub"         ],
   [ 0x11, "WIRELESS_ENDPOINT_COMPANION","WIRELESS_ENDPOINT_COMPANION_sub"],
   [ 0x21, "HID_DESCRIPTOR"             ,"Hid_class_sub"                 ],   #HID-Specific
   [ 0x22, "REPORT_DESCRIPTOR"          ,"Hid_Report_sub"                ],   #HID-Specific
   [ 0x23, "PHYSICAL_DESCRIPTOR"        ,"Hid_Physical_sub"              ],   #HID-Specific
   [ 0x30, "SUPERSPEED_USB_ENDPOINT_COMPANION", "SUPERSPEED_USB_ENDPOINT_COMPANION_sub"],
   [ 0x31, "SUPERSPEEDPLUS_ISOCHRONOUS_ENDPOINT_COMPANION", "SUPERSPEEDPLUS_ISOCHRONOUS_ENDPOINT_COMPANION_sub"]
];

#Descriptor Type Table without HID Specific Types (used beyond standard checking)
set DescriptorTypeTableEx =
[
   [ 0xFF, "Illegal"                    ,"Illegal_sub"                   ],
   [ 0x01, "DEVICE"                     ,"DEVICE_sub"                    ],
   [ 0x02, "CONFIGURATION"              ,"CONFIGURATION_sub"             ],
   [ 0x03, "STRING"                     ,"STRING_sub"                    ],
   [ 0x04, "INTERFACE"                  ,"INTERFACE_sub"                 ],
   [ 0x05, "ENDPOINT"                   ,"ENDPOINT_sub"                  ],
   [ 0x06, "DEVICE_QUALIFIER"           ,"DEVICE_QUALIFIER_sub"          ],
   [ 0x07, "OTHER_SPEED_CONFIGURATION"  ,"OTHER_SPEED_CONFIGURATION_sub" ],
   [ 0x08, "INTERFACE_POWER"            ,"INTERFACE_POWER_sub"           ],
   [ 0x09, "OTG"                        ,"OTG_sub"                       ],
   [ 0x0B, "INTERFACE_ASSOCIATION"      ,"INTERFACE_ASSOCIATION_sub"     ],
   [ 0x0C, "SECURITY"                   ,"SECURITY_sub"                  ],
   [ 0x0D, "KEY"                        ,"KEY_sub"                       ],
   [ 0x0E, "ENCRYPTION_TYPE"            ,"ENCRYPTION_TYPE_sub"           ],
   [ 0x0F, "BOS"                        ,"BOS_sub"                       ],
   [ 0x10, "DEVICE_CAPABILITY"          ,"DEVICE_CAPABILITY_sub"         ],
   [ 0x11, "WIRELESS_ENDPOINT_COMPANION","WIRELESS_ENDPOINT_COMPANION_sub"],
   [ 0x30, "SUPERSPEED_USB_ENDPOINT_COMPANION", "SUPERSPEED_USB_ENDPOINT_COMPANION_sub"],
   [ 0x31, "SUPERSPEEDPLUS_ISOCHRONOUS_ENDPOINT_COMPANION", "SUPERSPEEDPLUS_ISOCHRONOUS_ENDPOINT_COMPANION_sub"]
];
set DescriptorTypeTableExForUSB3 =
[
   [ 0xFF, "Illegal"                    ,"Illegal_sub"                   ],
   [ 0x01, "DEVICE"                     ,"DEVICE_sub"                    ],
   [ 0x02, "CONFIGURATION"              ,"CONFIGURATION_sub"             ],
   [ 0x03, "STRING"                     ,"STRING_sub"                    ],
   [ 0x04, "INTERFACE"                  ,"INTERFACE_sub"                 ],
   [ 0x05, "ENDPOINT"                   ,"DecodeEndpointForUSB3"         ],
   [ 0x06, "Reserved"           ,""          ],
   [ 0x07, "Reserved"  ,"" ],
   [ 0x08, "INTERFACE_POWER"            ,"INTERFACE_POWER_sub"           ],
   [ 0x09, "OTG"                        ,"OTG_sub"                       ],
   [ 0x0A, "Debug" ,""], 
   [ 0x0B, "INTERFACE_ASSOCIATION"      ,"INTERFACE_ASSOCIATION_sub"     ],
   [ 0x0C, "SECURITY"                   ,"SECURITY_sub"                  ],
   [ 0x0D, "KEY"                        ,"KEY_sub"                       ],
   [ 0x0E, "ENCRYPTION_TYPE"            ,"ENCRYPTION_TYPE_sub"           ],
   [ 0x0F, "BOS"                        ,"BOS_sub"                       ],
   [ 0x10, "DEVICE_CAPABILITY"          ,"DEVICE_CAPABILITY_sub"         ],
   [ 0x11, "WIRELESS_ENDPOINT_COMPANION","WIRELESS_ENDPOINT_COMPANION_sub"],
   [ 0x21, "HID_DESCRIPTOR"             ,"Hid_class_sub"                 ],   #HID-Specific
   [ 0x22, "REPORT_DESCRIPTOR"          ,"Hid_Report_sub"                ],   #HID-Specific
   [ 0x23, "PHYSICAL_DESCRIPTOR"        ,"Hid_Physical_sub"              ],   #HID-Specific
   [ 0x30, "SUPERSPEED_USB_ENDPOINT_COMPANION", "SUPERSPEED_USB_ENDPOINT_COMPANION_sub"],
   [ 0x31, "SUPERSPEEDPLUS_ISOCHRONOUS_ENDPOINT_COMPANION", "SUPERSPEEDPLUS_ISOCHRONOUS_ENDPOINT_COMPANION_sub"]
];

#Device Capability Type Codes(This type codes place in bDevCapabilityType field of Device Capability Descriptor)
#Device Capability Descriptors return by device as subordinate descriptors of BOS descriptor.

const DCT_WIRELESS_USB                  = 0x01;
const DCT_USB_20_EXTENSION              = 0x02;
const DCT_SUPERSPEED_USB                = 0x03;
const DCT_CONTAINER_ID                  = 0x04;
const DCT_PLATFORM                      = 0x05;
const DCT_POWER_DELIVERY_CAPABILITY     = 0x06;
const DCT_BATTERY_INFO_CAPABILITY       = 0x07;
const DCT_PD_CONSUMER_PORT_CAPABILITY   = 0x08;
const DCT_PD_PROVIDER_PORT_CAPABILITY   = 0x09;
const DCT_SUPERSPEED_PLUS               = 0x0A;
const DCT_PRECISION_TIME_MEASUREMENT    = 0x0B;
const DCT_Wireless_USB_Ext              = 0x0C;
const DCT_BILLBOARD_CAPABILITY          = 0x0D;





set DescriptorCellString = "";
set IsTooltip = 0;
set countx = 0;
set Base = 0;
set MaxDataBytes = 0;
set MostRecentInterfaceSubClass = 0;
set MostRecentClass = 0;
set MostRecentSubClass = 0;
set MostRecentProtocol = 0;
set MostRecentEndpointType = 0;

set ClassDescriptorTable     = null;

set MaxNumberOfDescriptorsWeShouldDecode = 300;

FindDescriptorEntry( descriptor_type )
{
    _row_sd = null;

    if( ClassDescriptorTable )
        _row_sd = Find( ClassDescriptorTable, descriptor_type );

    if( _row_sd == null )
     {
      if ( tempSpeedFlag == Super_Speed_Mode )
        _row_sd = Find( DescriptorTypeTableForUSB3, descriptor_type );  # will determine which request is being used (USB 3)
      else
        _row_sd = Find( DescriptorTypeTable, descriptor_type );  # will determine which request is being used
      }  

    return  _row_sd;
}

# This is a copy of FindDescriptorEntry() except it searches the DescriptorTypeTableEx
FindDescriptorEntryEx( descriptor_type )
{
    _row_sd = null;
    if( ClassDescriptorTable )
        _row_sd = Find( ClassDescriptorTable, descriptor_type );

    if( _row_sd == null )
      {
         if ( tempSpeedFlag == Super_Speed_Mode )
            _row_sd = Find( DescriptorTypeTableExForUSB3, descriptor_type );  # will determine which request is being used
         else 
            _row_sd = Find( DescriptorTypeTableEx, descriptor_type );  # will determine which request is being used
      }
    return  _row_sd;
}

DoStandardDescriptors( descriptor_type, is_tooltip )
{
    InitText();

    if( in.DataLength == 8 ) bad_data = 1;
    else                     bad_data = 0;
  

    if( in.PrepareFldsForDlg )
    {
        IsTooltip = 0;

        Global_BitField_offset = REQ_DATA_OFFSET;
        CurrentFldInit();

        EntryBaseOffset    = 0;
        EntryFieldGroupLen = 0;
    }
    else
    {
        IsTooltip = is_tooltip;
    }

    _row_sd = FindDescriptorEntry( descriptor_type );

    if( bad_data )
    {
        AddErrorMonoCell(_err_NotEnoughData_Header, Format( _err_NotEnoughData_Data, in.DataLength-8 ),_err_NotEnoughData_ToolTip);   

#       if( in.PrepareFldsForDlg )
#       {
#
#         AddStringToDlg( "Not enough data to decode descriptor(s).", "", "", _ERROR );
#         AddErrorMonoCell("Not enough data", Format( "Data stage : %d bytes", in.DataLength-8 )," Not enough data to decode descriptor(s)."); 
#            return null;
#        }
#        else
#        {
#            str = "";
#         
#
#            if( _row_sd[0] != 0xFF )
#            {
#                DescriptorCellString = _row_sd[1] + " Descriptor";
#
#                str  = Format( "Data stage : %d bytes", in.DataLength );
#                str += "\n--------------------------------------------\n";
#                str += DescriptorCellString + "\n\n";
#
#            }
#
#            return str + "Not enough data to decode descriptor(s).";
#        }
    }


    MaxDataBytes = in.DataLength - 8;

    if( _row_sd[0] != 0xFF )
    {


        standard_desc_string = Call (_row_sd[1]);
        return standard_desc_string;
    }
    else
    {
        return _err_NotMatchingDescriptor;
    }
}

set CI_SubClassTable =
[
      [ 0xFF, "Illegal" ],
      [ 0x01, "Direct Line Control Model"],
      [ 0x02, "Abstract Control Model"],
      [ 0x03, "Telephone Control Model"],
      [ 0x04, "Multi-Channel Control Model"],
      [ 0x05, "CAPI Control Model"],
      [ 0x06, "Ethernet Networking Control Model"],
      [ 0x07, "ATM Networking Control Model"],
      [ 0x08, "Wireless Handset Control Model"],
      [ 0x09, "Device Management Model"],
      [ 0x0A, "Mobile Direct Line Model"],
      [ 0x0B, "OBEX Model"],
	  [ 0x0C,"Ethernet Emulation Model"],
	  [ 0x0D, "Network Control Model"],
	  [ 0x0E, "Mobile Broadband Interface Model"]
	  
];

set CI_ProtocolTable =
[
      [ 0xDD, "Reserved"],
      [ 0x00, "No class specific protocol required"],
      [ 0x01, "Common AT commands"],
      [ 0x02, "AT Commands defined by [PCCA101]"],
      [ 0x03, "AT Commands defined by [PCCA101] + [PCCA101-O]"],
      [ 0x04, "AT Commands defined by [GSM07.07]"],
      [ 0x05, "AT Commands defined by [3GPP27.007]"],
      [ 0x06, "AT Commands defined by [C-S0017-0]"],
      [ 0xFE, "External Protocol: Commands defined by Command Set functional descriptor"],
      [ 0xFF, "Vendor-Specific"]
];

set MS_SubClassTable =
[
      [ 0xFF, "Illegal" ],
      [ 0x01, "RBC" ],
      [ 0x02, "ATAPI"],
      [ 0x03, "QIC-157" ],
      [ 0x04, "UFI"],
      [ 0x05, "SFF-8070i"  ],
      [ 0x06, "SCSI Transparent"  ]
];

set MS_ProtocolTable =
[
      [ 0xFF, "Illegal" ],
      [ 0x00, "CBI w/ CmdComplt" ],
      [ 0x01, "CBI, no Cmd Cmplt"],
      [ 0x50, "Bulk-Only" ],
      [ 0x62, "UASP" ]
];

set MD_SubClassTable =
[
      [ 0xFF, "Illegal" ],
      [ 0x02, "Common Class"],
      [ 0x03, "CBAF Interface"],
      [ 0x05, "USB3 Vision"]
];

set MD_ProtocolTable =
[
      [ 0xFF, "Illegal" ],
      [ 0x01, "Interface Association Descriptor"],
      [ 0x02, "Wire Adapter Multifunction Peripheral"]
];

set DI_ProtocolTable =
[
      [ 0x01, "Reserved"],
      [ 0x00, "No class specific protocol required"],
      [ 0x30, "Physical interface protocol for ISDN BRI"],
      [ 0x31, "HDLC"],
      [ 0x32, "Transparent"],
      [ 0x50, "Management protocol for Q.921 data link protocol"],
      [ 0x51, "Data link protocol for Q.931"],
      [ 0x52, "TEI-multiplexor for Q.921 data link protocol"],
      [ 0x90, "Data compression procedures"],
      [ 0x91, "Euro-ISDN protocol control"],
      [ 0x92, "V.24 rate adaptation to ISDN"],
      [ 0x93, "CAPI commands"],
      [ 0xFD, "Host based driver"],
      [ 0xFE, "The protocol(s) are described using a Ptrocol Unit Functional Descriptors on Communication Class Interface"],
      [ 0xFF, "Vendor-specific"]
];
set WA_SubClassTable =
[
    [0xFF, "Illegal"],
    [0x01, "RF Controller"],
    [0x02, "Wireless USB Adapter"]
];

set WA_ProtocolTable = # this protocol table does not apply if sublclass == 0x1 (RF Controler)
[
    [0xFF, "Illegal"],
    [0x01, "Host Wire Adapter Control/Data Streaming interface"],
    [0x02, "Device Wire Adapter Control/Data Streaming interface/UWB Radio Control Interface Programming Interface"],
    [0x03, "Device Wire Adapter Isochronous Streaming Interface"]
];

set HID_SubClassTable =
[
    [0x02, "Reserved"               ],
    [0x00, "No SubClass"            ],
    [0x01, "Boot Interface Subclass"]
];

set BILLBOARD_SubClassTable =
[
    [0xFF, "Reserved"               ],
    [0x00, "Billboard Subclass"     ]
];

set BILLBOARD_ProtocolTable =
[
    [0xFF, "Illegal"],
    [0x00, "Billboard Protocol"]
];

set HID_ProtocolTable =
[
    [0x03, "Reserved"   ],
    [0x00, "None"       ],
    [0x01, "Keyboard"   ],
    [0x02, "Mouse"      ]
];

set Printer_ProtocolTable =
[
    [0x00, "Unknown"        ],
    [0x01, "Unidirectional" ],
    [0x02, "bi-directional" ],
    [0x03, "1284.4"         ]
];

set Printer_SubClassTable =
[
    [0x00, "Unknown"    ],
    [0x01, "Printers"   ]
];

set SC_ProtocolTable =
[
    [ 0xFF, "Illegal" ],
    [ 0x00, "<b>CCID:</b> CCID Protocol <b>ICCD:</b> Bulk transfers optional interrupt-IN"],
    [ 0x01, "<b>CCID:</b> Illegal (must be 00h) <b>ICCD:</b> Version A, Control transfers (no interrupt-IN)"],
    [ 0x02, "<b>CCID:</b> Illegal (must be 00h) <b>ICCD:</b> Version B, Control transfers (optional interrupt-IN)"]
];

set APP_SubClassTable =
[
    [ 0xFF, "Illegal" ],
    [ 0x01, "Device Firmware Upgrade" ],
    [ 0x02, "IrDA Bridge Device" ],
    [ 0x03, "USB Test and Measurement Device"]
];

# Sub-Class specific protocol table, handled in INTERFACE_sub()
set APP_ProtocolTable =
[
    [ 0xFF, "Unknown" ]
];

set AD_ProtocolTable =
[
    [IP_VERSION_01_00, "IP_VERSION_01_00"],
    [IP_VERSION_02_00, "IP_VERSION_02_00"],
    [IP_VERSION_03_00, "IP_VERSION_03_00"]
];

#DeviceClassTable fields:
#  ClassCode | Class Symbol | Class Description | Interface Subclass Table | Interface Association Subclass function | Protocol Table.
set DeviceClassTable =
[
      [ 0xFF, "Illegal"             ,   null, null, null ],
      [ 0x01, "DC_AUDIO"            ,   "Audio Interface" , AudioInterfaceSubclassCodesTable, "AD_FUNCTION_SUBCLASS_sub", AD_ProtocolTable],
      [ 0x02, "DC_COMMUNICATION"    ,   "Communication Device/Interface", CI_SubClassTable, null, CI_ProtocolTable],
      [ 0x03, "DC_HID"              ,   "HID", HID_SubClassTable, null, HID_ProtocolTable ],
      [ 0x06, "DC_STILL_IMAGE"      ,   "Still Image", null, null, null ],
      [ 0x07, "DC_PRINTER"          ,   "Printer", Printer_SubClassTable, null, Printer_ProtocolTable ],
      [ 0x08, "DC_MS"               ,   "Mass Storage", MS_SubClassTable, null, MS_ProtocolTable ],
      [ 0x09, "DC_HUB"              ,   "HUB", null, null, null ],
      [ 0x0A, "DC_DATA_INTERFACE"   ,   "Data Interface", null, null, DI_ProtocolTable],
      [ 0x0B, "DC_SMART_CARD"       ,   "Smart Card", null, null, SC_ProtocolTable],
      [ 0x0D, "DC_CONTENT_SECURITY" ,   "Content Security", null, null, null ],
      [ 0x0E, "DC_VIDEO"            ,   "Video", VideoSubclassCodeTable, null, VideoInterfaceProtocolCodeTable ],
      [ 0x0F, "DC_PERSONAL_HEALTHCARE", "Personal Healthcare", null, null, null ],
      [ 0xE0, "DC_WIRELESS_CONTROLLER", "Wireless Controller", WA_SubClassTable, null, WA_ProtocolTable ],
      [ 0x11, "DC_BILLBOARD"        ,   "Billboard", BILLBOARD_SubClassTable, null, BILLBOARD_ProtocolTable ],
      [ 0xEF, "DC_MISC"             ,   "Miscellaneous Device", MD_SubClassTable, null, MD_ProtocolTable ],
      [ 0xFE, "DC_APP_SPECIFIC"     ,   "Application Specific", APP_SubClassTable, null, APP_ProtocolTable ],
      [ 0x12, "DC_TYPE_C_BRIDGE"    ,   "Type-C Bridge", null, null, null ]
];

Illegal()
{
    DescriptorCellString = "Illegal Descriptor";
    Base = 8;
    AddDataHeader("Illegal Descriptor", in.DataLength-8);
    Illegal_sub();
    return GetFinalText();
}
Illegal_sub()
{
   AddLineOfText( Format(" Unrecognized bDescriptorType = 0x%X", bDescriptorType ));

}

#******************************************************************************
# DEVICE Descriptor definitions
#******************************************************************************
DEVICE()
{
    DescriptorCellString = "DEVICE Descriptor";
    Base = 8;
    AddDataHeader("DEVICE Descriptor", in.DataLength-8);
    DEVICE_sub();
    return GetFinalText();
}


DEVICE_sub()
{
    base = Base;

    bLength             = GetDataByte(base);
    bDescriptorType     = GetDataByte(base+1);
    bcdUSB              = GetDataWord(base+2);
    bDeviceClass        = GetDataByte(base+4);
    bDeviceSubClass     = GetDataByte(base+5);
    bDeviceProtocol     = GetDataByte(base+6);
    bMaxPacketSize0     = GetDataByte(base+7);
    idVendor            = GetDataWord(base+8);
    idProduct           = GetDataWord(base+10);
    bcdDevice           = GetDataWord(base+12);
    iManufacturer       = GetDataByte(base+14);
    iProduct            = GetDataByte(base+15);
    iSerialNumber       = GetDataByte(base+16);
    bNumConfigurations  = GetDataByte(base+17);

    base -=8;

    AddEntry( 0, "bLength", bLength, 2, "", 1 );
    AddDescriptorSizeString(bLength);
    AddFieldBreak();

    if (MaxDataBytes <= 1) return "";
    AddEntry( 1, "bDescriptorType", bDescriptorType, 2, GetDescriptorTypeString("DEVICE"), 0);
    AddFieldBreak();

    doDeviceSharedStuff(bcdUSB, bDeviceClass, bDeviceSubClass, bDeviceProtocol, bMaxPacketSize0, bDescriptorType);    
    
    if (MaxDataBytes <= 8) return "";
    _row_cmp = Find(CompaniesTable, idVendor);
    if (_row_cmp[0] == 0xFF)
    {
        AddEntry( 8, "idVendor", idVendor, 4, Format ( "Vendor ID is %d", idVendor), 0);
    }
    else
    {
        AddEntry( 8, "idVendor", idVendor, 4, Format ( "Vendor ID is %d:", idVendor), 0);
        AddDescriptionOnly( _row_cmp[1]);
    }
    AddFieldBreak();


    if (MaxDataBytes <= 10) return "";
    AddEntry( 10, "idProduct", idProduct, 4, Format ("Product ID is %d", idProduct) , 0);
    AddFieldBreak();

    if (MaxDataBytes <= 12) return "";
    AddEntry( 12, "bcdDevice", bcdDevice, 4, "The device release", 0);
    AddDescriptionOnly(FormatEx ("number is %X.%02X",
        ((bcdDevice >> 8) & 0xFF), (bcdDevice & 0xFF)));
    AddFieldBreak();

    if (MaxDataBytes <= 14) return "";
    if (iManufacturer == 0)
    {
        AddEntry( 14, "iManufacturer", iManufacturer, 2, "The device doesn't have", 0);
        AddDescriptionOnly("the string descriptor");
        AddDescriptionOnly("describing the manufacturer");
    }
    else
    {
        AddEntry( 14, "iManufacturer", iManufacturer, 2, "The manufacturer" , 0);
        AddDescriptionOnly("string descriptor");
        AddDescriptionOnly(Format ("index is %d", iManufacturer ));
    }
    AddFieldBreak();

    if (MaxDataBytes <= 15) return "";
    if (iProduct == 0)
    {
        AddEntry( 15, "iProduct", iProduct, 2, "The device doesn't have", 0);
        AddDescriptionOnly("the string descriptor");
        AddDescriptionOnly("describing the product");
    }
    else
    {
        AddEntry( 15, "iProduct", iProduct, 2, "The product" , 0);
        AddDescriptionOnly("string descriptor");
        AddDescriptionOnly(Format ("index is %d", iProduct ));
    }
    AddFieldBreak();


    if (MaxDataBytes <= 16) return "";
    if (iSerialNumber == 0)
    {
        AddEntry( 16, "iSerialNumber", iSerialNumber, 2, "The device doesn't have", 0);
        AddDescriptionOnly("the string descriptor");
        AddDescriptionOnly("describing the serial number");
    }
    else
    {
        AddEntry( 16, "iSerialNumber", iSerialNumber, 2, "The serial number" , 0);
        AddDescriptionOnly("string descriptor");
        AddDescriptionOnly(Format ("index is %d", iSerialNumber ));
    }
    AddFieldBreak();

    if (MaxDataBytes <= 17) return "";
    AddEntry( 17, "bNumConfigurations", bNumConfigurations, 2, Format ("The device has %d", bNumConfigurations) , 0);
    AddDescriptionOnly("possible configurations");
    AddFieldBreak();

    Base += bLength;
    out.Decoded += bLength;

}

doDeviceSharedStuff(bcdUSB, bDeviceClass, bDeviceSubClass, bDeviceProtocol, bMaxPacketSize0, bDescriptorType)
{
    AddEntry( 2, "bcdUSB", bcdUSB, 4, "USB Specification " , 0);    
    AddDescriptionOnly( FormatEx( "version %X.%02X", (bcdUSB & 0xFF00)>> 8, bcdUSB & 0xFF) );
    
    #==========================================================
    # set the global variable for deciding on the USB specification with which the device is compliant    
    if (bDescriptorType == 0x01) #DEVICE Descriptor
    { 
    	  if ((bcdUSB == 0x300) || (bcdUSB == 0x310) )  # Added SSP  SS+  Gen II Gen 2 USB 3.1 SuperSpeed Plus  SuperSpeed+ 10Gbps  so we can find it if we search
        		gDeviceCompliantSpec = USB3_Spec; 
        else
            gDeviceCompliantSpec = USB2_Spec; 
    }
    #==========================================================       	
        	
    if (gDeviceCompliantSpec == USB3_Spec || gDeviceCompliantSpec == UNKNOWN_VALUE)
    {    	
    	  DecodeDevicebcdUSBForUSB3(bcdUSB, bDescriptorType);
    }
    
    AddFieldBreak();
    subclass_done = 0;
    protocol_done = 0;

    _row_d = Find(DeviceClassTable, bDeviceClass);
    MostRecentClass = bDeviceClass;
    MostRecentSubClass = bDeviceSubClass;
    MostRecentProtocol = bDeviceProtocol;

    #AddLineOfText( FormatEx ("DEVICE MostRecentClass =%d %d", MostRecentClass, bDeviceClass ));
    if (bDeviceClass == 0)
    {
        AddEntry( 4, "bDeviceClass", bDeviceClass, 2, "Each interface" , 0);
        AddDescriptionOnly( "specifies its own" );
        AddDescriptionOnly( "class information" );
    }
    else if (bDeviceClass == 0xFF)
    {
        AddEntry( 4, "bDeviceClass", bDeviceClass, 2, "The device Class" , 0);
        AddDescriptionOnly( "is vendor-specific" );
    }
    else if (_row_d[0] != 0xFF)
    {
        AddEntry( 4, "bDeviceClass", bDeviceClass, 2, "The device" , 0);
        AddDescriptionOnly( "belongs to the" );
        AddDescriptionOnly( FormatEx ("%s Class", _row_d[2]) );
        if (_row_d[3] != null)
        {
            _row_sc = Find(_row_d[3], bDeviceSubClass);

            AddFieldBreak();
            if (_row_sc[0] != 0xFF)
            {
                AddEntry( 5, "bDeviceSubClass", bDeviceSubClass, 2, "The device" , 0);
                AddDescriptionOnly( "belongs to the" );
                AddDescriptionOnly( FormatEx ("%s Subclass", _row_sc[1]) );
            }
            else
            {
                AddEntry( 5, "bDeviceSubClass", bDeviceSubClass, 2, "Subclass" , 0);
                AddDescriptionOnly( FormatEx ("0x%02X not defined", bDeviceSubClass) );
            }
            subclass_done = 1;

        }
        if (_row_d[5] != null)
        {
            AddFieldBreak();

            # Adding Special Cases here for Device Classes with SubClass Specific
            # Protocol Codes. Should be an if-else statement (see INTERFACE_sub
            # for examples)
            # BEGIN Exceptions here:


            # END Exceptions
            #else
                _row_p = Find(_row_d[5], bDeviceProtocol);

            if (_row_p[0] != 0xFF)
            {
                AddEntry( 6, "bDeviceProtocol", bDeviceProtocol, 2, "The device uses the" , 0);
                AddDescriptionOnly( FormatEx ("%s Protocol", _row_p[1]) );
            }
            else
            {
                AddEntry( 6, "bDeviceProtocol", bDeviceProtocol, 2, "Protocol" , 0);
                AddDescriptionOnly( FormatEx ("0x%02X not defined", bDeviceProtocol) );
            }
            protocol_done = 1;
        }
    }
    else
    {
        AddEntry( 4, "bDeviceClass", bDeviceClass, 2, "Unknown Class" , 0);
    }

    if (subclass_done == 0)
    {
        AddFieldBreak();
        if (bDeviceSubClass == 0)
        {
            AddEntry( 5, "bDeviceSubClass", bDeviceSubClass, 2, "Each interface" , 0);
            AddDescriptionOnly( "specifies its own");
            AddDescriptionOnly( "Subclass information");
        }
        else if (bDeviceSubClass == 0xFF)
        {
            AddEntry( 5, "bDeviceSubClass", bDeviceSubClass, 2, "The device Subclass" , 0);
            AddDescriptionOnly("is vendor-specific");
        }
        else
        {
            AddEntry( 5, "bDeviceSubClass", bDeviceSubClass, 2, Format ("Subclass code = %d", bDeviceSubClass) , 0);
        }
    }

    if (protocol_done == 0)
    {
        AddFieldBreak();
        if (bDeviceProtocol == 0)
        {
            AddEntry( 6, "bDeviceProtocol", bDeviceProtocol, 2, "No protocols" , 0);
            AddDescriptionOnly( "the device basis");
        }
        else if (bDeviceSubClass == 0xFF)
        {
            AddEntry( 6, "bDeviceProtocol", bDeviceProtocol, 2, "The device Protocol" , 0);
            AddDescriptionOnly("is vendor-specific");
        }
        else
        {
            AddEntry( 6, "bDeviceProtocol", bDeviceProtocol, 2, Format ("Protocol code = %d", bDeviceProtocol) , 0);
        }
    }
    AddFieldBreak();

    if (gDeviceCompliantSpec == USB3_Spec || gDeviceCompliantSpec == UNKNOWN_VALUE || tempSpeedFlag == Super_Speed_Mode)
    {
       DecodeDeviceMaxPacketSizeForUSB3(bMaxPacketSize0, bDescriptorType);
    }
    else
    {
       if ( bMaxPacketSize0 == 8 || bMaxPacketSize0 == 16 || bMaxPacketSize0 == 32 || bMaxPacketSize0 == 64)
       {
           AddEntry( 7, "bMaxPacketSize0", bMaxPacketSize0, 2, "Maximum packet size for" , 0);
           AddDescriptionOnly( Format ("endpoint zero is %d", bMaxPacketSize0));
       }
       else
       {
           AddEntry( 7, "bMaxPacketSize0", bMaxPacketSize0, 2, " The Maximum packet size" , 0);
           AddDescriptionOnly( Format ("%d for endpoint zero is invalid!", bMaxPacketSize0));
           AddDescriptionOnly( "(Only 8,16,32,or 64 are valid)" );
       }
    }
    
    AddFieldBreak();
 }

set CurrentOffset = 0;
set ConfigString = "";

#******************************************************************************
# CONFIGURATION Descriptor definitions
#******************************************************************************
CONFIGURATION()
{
    ConfigString = "CONFIGURATION";

    doSharedConfig();
}


doSharedConfig()
{
    DescriptorCellString = Format ("%s Descriptor", ConfigString);
    curr_offset = 8;
    bLength            = GetDataByte(curr_offset);
    bDescriptorType    = GetDataByte(curr_offset+1);
    wTotalLength       = GetDataWord(curr_offset+2);
    descriptor_count = 0;

    if (IsTooltip)
    {
        if (in.DataLength > (bLength+8))
        {
            AddLineOfText("RIGHT CLICK ON DESCRIPTORS FIELD TO SHOW ALL DESCRIPTORS DECODED!!");
        }
        Base = 8;
        AddDataHeader(DescriptorCellString, in.DataLength-8);
        CONFIGURATION_sub();

        more_left = MaxNumberOfDescriptorsWeShouldDecode; # max num descriptors we will decode in 1 config statement

        while (more_left > 0)
        {
            descriptor_count = descriptor_count + 1;
            curr_offset += (bLength & 0xFF);            #DescriptorCellString = FormatEx ("%d %d %d %d", descriptor_count, curr_offset, bLength, in.DataLength);

            if (curr_offset >= in.DataLength)
            {
                more_left = 0;
            }
            else
            {
                bLength = GetDataByte(curr_offset);
                more_left = more_left - 1;
            }
        }

        if ( descriptor_count > 1)
        {
            DescriptorCellString = Format ("%d Descriptors", descriptor_count);            #DescriptorCellString = FormatEx ("%d %d %d", descriptor_count, curr_offset, in.DataLength);
        }
    }
    else
    {
        AddDataStageTitle(in.DataLength-8);
        AddDash();

        more_left = MaxNumberOfDescriptorsWeShouldDecode; # max num descriptors we will decode in 1 config statement
        curr_offset = 8;

        descriptor_count = 0;

        while (more_left)
        {
            descriptor_count++;

            AddBlankLine();
            _row_dtt2 = FindDescriptorEntryEx( bDescriptorType );

            #AddLineOfText( FormatEx ("count=%d  bDescriptorType=%d row=0x%X", descriptor_count,  bDescriptorType, _row_dtt2 ));
            Base = curr_offset;
            if (_row_dtt2[0] != 0xFF)
            {
                AddShortDataHeader(FormatEx ("%s Descriptor  (%d bytes)", _row_dtt2[1], bLength ));
                Call (_row_dtt2[2]);
                if(bDescriptorType == 0x21)#Hid_class_sub
                     Base += bLength;
			
            }
            else
            {
                #AddLineOfText( FormatEx ("count=%d  bDescriptorType=%d MostRecentClass =%d", descriptor_count,  bDescriptorType, MostRecentClass ));

                if ( MostRecentClass == 0xEF) # Miscellaneous
                {
                    # Defined sub class code and protocol for USB3 Vision.
                    if( MostRecentSubClass == 0x05 &&  MostRecentProtocol == 0x00 ) 
                        result = TryUsb3VisionDescriptors(bDescriptorType);
                    else
                        result = 0;                    
                }
                else if ( MostRecentClass == 0x0E) # DC_VIDEO
                {
                    result = TryVideoDescriptors(bDescriptorType);
                }
                else if ( MostRecentClass == 0xE0 ) # wireless stuff.
                {               
                    # USB-IF refers this ClassCode, SubClassCode and Protocol to RNDIS that is over CDC
                    if( MostRecentSubClass == 0x01 &&  MostRecentProtocol == 0x03 ) 
                        result = TryCommunicationDescriptors(bDescriptorType);
                    else
                        result = TryWA_Descriptors(bDescriptorType);
                }
                else if ( MostRecentClass == 0x02 ) # communication stuff
                {
                    result = TryCommunicationDescriptors(bDescriptorType);
                }
                else if ( MostRecentClass == 0x01 ) # audio stuff
                {
                    result = TryAudioDescriptors(bDescriptorType);
                }
                else if ( MostRecentClass == 0x03 ) # Hid stuff.
                {
                    result = TryHid_Descriptors (bDescriptorType);
                }
                else if ( MostRecentClass == 0x0B ) # Smart Card stuff
                {
                    result = TrySmartCardDescriptors(bDescriptorType);
                }
                else if ( MostRecentClass == 0x0D ) # Content Security stuff
                {
                    result = TryContentSecurityDescriptors(bDescriptorType);
                }
                else if ( MostRecentClass == 0x0F ) # Personal Healthcare stuff
                {
                    result = TryPersonalHealthcareDescriptors(bDescriptorType);
                }
                else if ( MostRecentClass == 0x08 ) # mass storage
                {
                    result = TryMassStorageDescriptors(bDescriptorType);
                }
				else if ( MostRecentClass == 0xFE && MostRecentSubClass = 0x01) # DFU
                {
                    result = TryDFU_Descriptors (bDescriptorType);
                }
                else if ( MostRecentClass == 0x12 ) #Type-C Bridge
                {
                    result = TryTypeCBridgeDescriptors(bDescriptorType);
                }
                else
                {
                    result = 0;
                }

                #AddLineOfText( FormatEx ("count=%d  bDescriptorType=%d", descriptor_count,  bDescriptorType ));
                if (result == 0)
                {
                    if( in.PrepareFldsForDlg )
                    {
                        EntryBaseOffset += EntryFieldGroupLen;

                        AddStringToDlg( "Unknown Descriptor Type", FormatEx( "0x%02X   (%d bytes)", bDescriptorType, bLength), OutputUnknownData(bLength, 0) );
                        EntryFieldGroupLen = bLength * 8;
                    }
                    else
                    {
                        AddDash();
                        AddLineOfText( FormatEx("Unknown Descriptor Type: 0x%02X   (%d bytes)", bDescriptorType, bLength));
                        OutputUnknownData(bLength, 0);
                        AddDash();
                        #AddBlankLine();
                    }
                }

              	# Shouldn't really rely on bLength.  All the "Try" subroutines should be modified
              	# to make decoded length available.  Once all the above "Try" subroutines have been
                # fixed, we can remove this line.
              	Base += bLength;
                
            }

            # subroutines should modify Base to data offset at which they finished.
            curr_offset = Base;

            # DK
            #if( EntryFieldGroupLen < ( bLength * 8 ) )
              EntryFieldGroupLen = bLength * 8;


            #AddLineOfText( FormatEx ("2 bLength=%d  curr_offset=%d  in.DataLength=%d", bLength, curr_offset, in.DataLength ));
            # Minus 2 because we need at least 2 bytes to read the next bLength and bDescriptorType
            if (curr_offset >= (in.DataLength-2))
            {
                more_left = 0;
                
                if ( curr_offset < in.DataLength )
                {
                	  extra_len = in.DataLength - curr_offset;
                	  # output extra bytes
                	  AddStringToDlg( "Undecoded Data", FormatEx( "(%d bytes)", extra_len), OutputUnknownData(extra_len, 0) );
                }
            }
            else
            {
                 bLength            = GetDataByte(curr_offset);
                 bDescriptorType    = GetDataByte(curr_offset+1);
                 #AddLineOfText( FormatEx ("3 bLength=%d  curr_offset=%d", bLength, curr_offset ));
                 more_left--;
            }
        }
    }

    return GetFinalText();
}

CONFIGURATION_sub()
{
    base = Base;

    bLength             = GetDataByte(base);
    bDescriptorType     = GetDataByte(base+1);
    wTotalLength        = GetDataWord(base+2);
    bNumInterfaces      = GetDataByte(base+4);
    bConfigurationValue = GetDataByte(base+5);
    iConfiguration      = GetDataByte(base+6);
    bmAttributes        = GetDataByte(base+7);
    MaxPower            = GetDataByte(base+8);


    AddEntry( 0, "bLength", bLength, 2, "", 1);
    AddDescriptorSizeString(bLength);
    AddFieldBreak();

    AddEntry( 1, "bDescriptorType", bDescriptorType, 2, GetDescriptorTypeString(ConfigString), 0);
    AddFieldBreak();

    AddEntry( 2, "wTotalLength", wTotalLength, 4, "The total length of data", 0);
    AddDescriptionOnly(Format ("for this configuration is %d.", wTotalLength));
    AddDescriptionOnly("This includes the combined length");
    AddDescriptionOnly("of all the descriptors returned");
    if (wTotalLength != bLength)
      AddDescriptionOnly("\n Warning : The Value of wTotalLength is not equal to real length");
  
   
    AddFieldBreak();

    AddEntry( 4, "bNumInterfaces", bNumInterfaces, 2, "This configuration supports", 0);
    AddDescriptionOnly(Format ("%i interfaces", bNumInterfaces));
    AddFieldBreak();

    AddEntry( 5, "bConfigurationValue", bConfigurationValue, 2, Format ("The value %d should be used", bConfigurationValue), 0);
    AddDescriptionOnly("to select this configuration");
    AddFieldBreak();

    if (iConfiguration == 0)
    {
        AddEntry( 6, "iConfiguration", iConfiguration, 2, "The device doesn't have", 0);
        AddDescriptionOnly("the string descriptor");
        AddDescriptionOnly("describing this configuration");
    }
    else
    {
        AddEntry( 6, "iConfiguration", iConfiguration, 2, "The configuration" , 0);
        AddDescriptionOnly("string descriptor");
        AddDescriptionOnly(Format ("index is %d", iConfiguration ));
    }
    AddFieldBreak();

    AddEntry( 7, "bmAttributes", bmAttributes, 2, "Configuration characteristics :", 0);
    AddDescriptionOnly(Format ("Bit 7: Reserved (set to one) %1X", ((bmAttributes & 0x80) >> 7)));
    AddDescriptionOnly(Format ("Bit 6: Self-powered          %1X", ((bmAttributes & 0x40) >> 6)));
    AddDescriptionOnly(Format ("Bit 5: Remote Wakeup         %1X", ((bmAttributes & 0x20) >> 5)));
    AddFieldBreak();

    AddEntry( 8, "bMaxPower", MaxPower, 2, "Maximum power consumption", 0);
    AddDescriptionOnly("of the device in this");
    if (gDeviceCompliantSpec == USB3_Spec || gDeviceCompliantSpec == UNKNOWN_VALUE)
    {
        DecodeMaxPowerForUSB3(MaxPower, bDescriptorType);
    }
    else
        AddDescriptionOnly(Format ("configuration is %d mA", MaxPower*2));
    AddFieldBreak();
    
    Base += bLength;
}



#******************************************************************************
# STRING Descriptor definitions
#******************************************************************************
STRING()
{
    Base = 8;
    AddDataHeader("STRING Descriptor", in.DataLength-8);
    STRING_sub();
    return GetFinalText();}

STRING_sub()
{
    base = Base;

    bLength          = GetDataByte(base);
    bDescriptorType  = GetDataByte(base+1);

    if (wIndex == 0)
    {
        AddEntry( 0, "bLength", bLength, 2, "", 1);
        AddDescriptorSizeString(bLength);
        AddFieldBreak();

        AddEntry( 1, "bDescriptorType", bDescriptorType, 2, "STRING Descriptor Type", 0);
        AddFieldBreak();

        n = 2;
        length_to_decode = in.DataLength-base;
        while (n < length_to_decode )
        {
            wLangId = GetDataWord(base + n);
            AddEntry( n, Format("wLANGID[%d]", n/2 - 1), wLangId, 4, Format ("Language Id: %d", wLangId), 0);
            AddFieldBreak();

            n += 2;
        }
        DescriptorCellString = "Lang Supported";
        
        Base += n;
    }
    else
    {
        AddEntry( 0, "bLength", bLength, 2, "Unicode String Length is", 0);
        AddDescriptionOnly(FormatEx("%d bytes (%d chars)", bLength , (bLength-2)/2));
        AddFieldBreak();

        AddEntry( 1, "bDescriptorType", bDescriptorType, 2, "STRING Descriptor Type", 0);
        AddFieldBreak();

        #if we want to show the raw bytes, do it here.

        length_to_decode = in.DataLength-(base+2);
        DescriptorCellString = ObtainUnicodeString(base+2, length_to_decode);
        AddEntry( 2, "STRING", "", 2, "String:" + DescriptorCellString, 0);
        AddFieldBreak();
        
        Base += 2 + length_to_decode;
    }
}

#******************************************************************************
# INTERFACE Descriptor definitions
#******************************************************************************
INTERFACE()
{
    temp_str = ("Illegal usage: GET_DESCRIPTOR  INTERFACE type");
    temp_str = temp_str + NewLine();
    temp_str = temp_str + "Must be obtained through GET_DESCRIPTOR  CONFIGURATION type";
    return (temp_str);
}
INTERFACE_sub()
{
    base = Base;
    bLength             = GetDataByte(base);
    bDescriptorType     = GetDataByte(base+1);
    bInterfaceNumber    = GetDataByte(base+2);
    bAlternateSetting   = GetDataByte(base+3);
    bNumEndpoints       = GetDataByte(base+4);
    bInterfaceClass     = GetDataByte(base+5);
    bInterfaceSubClass  = GetDataByte(base+6);
    bInterfaceProtocol  = GetDataByte(base+7);
    iInterface          = GetDataByte(base+8);



    AddEntry( 0, "bLength", bLength, 2, "", 1);
    AddDescriptorSizeString(bLength);
    AddFieldBreak();

    AddEntry( 1, "bDescriptorType", bDescriptorType, 2, GetDescriptorTypeString("INTERFACE"), 0);
    AddFieldBreak();

    AddEntry( 2, "bInterfaceNumber", bInterfaceNumber, 2, "The number of this", 0);
    AddDescriptionOnly(Format ("interface is %d.", bInterfaceNumber));
    AddFieldBreak();

    AddEntry( 3, "bAlternateSetting", bAlternateSetting, 2, "The value used to select", 0);
    AddDescriptionOnly("the alternate setting for");
    AddDescriptionOnly(Format ("this interface is %d", bAlternateSetting));
    AddFieldBreak();

    AddEntry( 4, "bNumEndpoints", bNumEndpoints, 2, "The number of endpoints used", 0);
    AddDescriptionOnly(Format ("by this interface is %d", bNumEndpoints));
    AddDescriptionOnly("(excluding endpoint zero)");
    AddFieldBreak();

    subclass_done = 0;
    protocol_done = 0;

    _row_d = Find(DeviceClassTable, bInterfaceClass);
    MostRecentClass = bInterfaceClass;
    MostRecentSubClass = bInterfaceSubClass;
    MostRecentProtocol = bInterfaceProtocol;
    
    #AddLineOfText( FormatEx ("INTERFACE MostRecentClass =%d %d", MostRecentClass, bInterfaceClass ));
    if (bInterfaceClass == 0)
	
    {
        AddEntry( 5, "bInterfaceClass", bInterfaceClass, 2, "This value is reserved" , 0);
        AddDescriptionOnly( "for future standardization" );
    }
    else if (bInterfaceClass == 0xFF)
    {
        AddEntry( 5, "bInterfaceClass", bInterfaceClass, 2, "The interface class" , 0);
        AddDescriptionOnly( "is vendor-specific" );
    }
    else if (_row_d[0] != 0xFF)
    {
        AddEntry( 5, "bInterfaceClass", bInterfaceClass, 2, "The interface" , 0);
        AddDescriptionOnly( "implements the" );
        AddDescriptionOnly( FormatEx ("%s class", _row_d[2]) );
        if (_row_d[3] != null)
        {
            _row_sc = Find(_row_d[3], bInterfaceSubClass);

            AddFieldBreak();
            if (_row_sc[0] != 0xFF)
            {
                AddEntry( 6, "bInterfaceSubClass", bInterfaceSubClass, 2, "The interface" , 0);
                AddDescriptionOnly( "implements the" );
                AddDescriptionOnly( FormatEx ("%s Subclass", _row_sc[1]) );
            }
            else
            {
                AddEntry( 6, "bInterfaceSubClass", bInterfaceSubClass, 2, "SubClass" , 0);
                AddDescriptionOnly( FormatEx ("0x%02X not defined", bInterfaceSubClass) );
            }
            subclass_done = 1;

        }
        if (_row_d[5] != null)
        {
            AddFieldBreak();

            # Adding Special Cases here for Device Classes with SubClass Specific
            # Protocol Codes.
            # BEGIN Exceptions here:

            # Application Specific Class
            if(_row_d[0] == 0xFE)
            {
                ProtCode = bInterfaceProtocol;
                SC_Code  = bInterfaceSubClass;
                select
                {
                    SC_Code == 0x01 :    _row_p = select{
                                                            ProtCode == 0x01 : [ 0x01, "Runtime" ];
                                                            ProtCode == 0x02 : [ 0x02, "DFU Mode" ];
                                                            default          : [ 0xFF, "Illegal" ];
                                                        };
                    SC_Code == 0x02 :    _row_p = select{
                                                            ProtCode == 0x00 : [ 0x00, "Only supported" ];
                                                            default          : [ 0xFF, "Illegal" ];
                                                        };
                    SC_Code == 0x03 :    _row_p = select{
                                                            ProtCode == 0x00 : [ 0x00, "USBTMC Interface" ];
                                                            ProtCode == 0x01 : [ 0x01, "USBTMC USB488 Interface" ];
                                                            ProtCode <= 127  : [ ProtCode, "RESERVED" ];
                                                            default          : [ 0xFF, "Illegal" ];
                                                        };
                    default         :    _row_p = [0xFF, "Illegal"];
                };
            }
            # Miscellaneous Specific Class
            else if(_row_d[0] == 0xEF) 
            {
                ProtCode = bInterfaceProtocol;
                SC_Code  = bInterfaceSubClass;
            
                # USB3 Vision
                if( SC_Code == 0x5 ) 
                {
                    _row_p = select{
                                    ProtCode == 0x00 : [ 0x00, "Device Control" ];
                                    ProtCode == 0x01 : [ 0x01, "Device Events" ];
                                    ProtCode == 0x02 : [ 0x02, "Device Streaming" ];
                                    default          : [ 0xFF, "Illegal" ];
                                   };                
                }
                else              
                {
                    _row_p = Find(_row_d[5], ProtCode);
                }
            }

            # END Exceptions
            else
                _row_p = Find(_row_d[5], bInterfaceProtocol);

            if (_row_p[0] != 0xFF)
            {
                AddEntry( 7, "bInterfaceProtocol", bInterfaceProtocol, 2, "The interface uses" , 0);
                AddDescriptionOnly( FormatEx ("the %s Protocol", _row_p[1]) );
            }
            else
            {
                AddEntry( 7, "bInterfaceProtocol", bInterfaceProtocol, 2, "Protocol" , 0);
                AddDescriptionOnly( FormatEx ("0x%02X not defined", bInterfaceProtocol) );
            }
            protocol_done = 1;
        }
    }
    else
    {
        AddEntry( 5, "bInterfaceClass", bInterfaceClass, 2, "Unknown class" , 0);
    }

    if (subclass_done == 0)
    {
        AddFieldBreak();
        if (bInterfaceSubClass == 0xFF)
        {
            AddEntry( 6, "bInterfaceSubClass", bInterfaceSubClass, 2, "The interface Subclass" , 0);
            AddDescriptionOnly("is vendor-specific");
        }
        else
        {
            AddEntry( 6, "bInterfaceSubClass", bInterfaceSubClass, 2, Format ("The Subclass code is %d", bInterfaceSubClass) , 0);
        }
    }

    MostRecentInterfaceSubClass = bInterfaceSubClass;

    if (protocol_done == 0)
    {
        AddFieldBreak();
        if (bInterfaceProtocol == 0)
        {
            AddEntry( 7, "bInterfaceProtocol", bInterfaceProtocol, 2, "The interface doesn't use" , 0);
            AddDescriptionOnly( "any class-specific protocols");
        }
        else if (bInterfaceProtocol == 0xFF)
        {
            AddEntry( 7, "bInterfaceProtocol", bInterfaceProtocol, 2, "The interface protocol" , 0);
            AddDescriptionOnly("is vendor-specific");
        }
        else
        {
            AddEntry( 7, "bInterfaceProtocol", bInterfaceProtocol, 2, Format ("The Protocol code is %d", bInterfaceProtocol) , 0);
        }
    }

    AddFieldBreak();


    if (iInterface == 0)
    {
        AddEntry( 8, "iInterface", iInterface, 2, "The device doesn't have", 0);
        AddDescriptionOnly("a string descriptor");
        AddDescriptionOnly("describing this iInterface");
    }
    else
    {
        AddEntry( 8, "iInterface", iInterface, 2, "The interface string" , 0);
        AddDescriptionOnly(Format ("descriptor index is %d", iInterface ));
    }
    AddFieldBreak();
    
    Base += bLength;
}

set bIntervalTable =
[
    [1,1],
    [2,2],
    [3,4],
    [4,8],
    [5,16],
    [6,32],
    [7,64],
    [8,128],
    [9,256],
    [10,512],
    [11,1024],
    [12,2046],
    [13,4096],
    [14,8192],
    [15,16384],
    [16,32768]
];
#******************************************************************************
# ENDPOINT Descriptor definitions
#******************************************************************************
ENDPOINT()
{
    temp_str = ("Illegal usage: GET_DESCRIPTOR  ENDPOINT type");
    temp_str = temp_str + NewLine();
    temp_str = temp_str + "Must be obtained through GET_DESCRIPTOR  CONFIGURATION type";
    return (temp_str);
}

ENDPOINT_sub()
{
    base = Base;
    bLength             = GetDataByte(base);
    bDescriptorType     = GetDataByte(base+1);
    bEndpointAddress    = GetDataByte(base+2);
    bmAttributes        = GetDataByte(base+3);
    wMaxPacketSize      = GetDataWord(base+4);
    bInterval           = GetDataByte(base+6);


    AddEntry( 0, "bLength", bLength, 2, "", 1);
    AddDescriptorSizeString(bLength);
    AddFieldBreak();

    AddEntry( 1, "bDescriptorType", bDescriptorType, 2, GetDescriptorTypeString("ENDPOINT"), 0);
    AddFieldBreak();

    direction = 1;
    if (bEndpointAddress & 0x70)
    {
        AddEntry( 2, "bEndpointAddress", bEndpointAddress, 2, "Invalid endpoint number", 0);
        AddDescriptionOnly("(reserved bits are set to one)!");
    }
    else if (bEndpointAddress & 0x80)
    {
        AddEntry( 2, "bEndpointAddress", bEndpointAddress, 2, "This is an IN endpoint", 0);
        AddDescriptionOnly(Format ("with endpoint number %d", bEndpointAddress & 0x0F));
    }
    else
    {
        AddEntry( 2, "bEndpointAddress", bEndpointAddress, 2, "This is an OUT endpoint", 0);
        AddDescriptionOnly(Format ("with endpoint number %d", bEndpointAddress & 0x0F));
        direction = 0;
    }
    AddFieldBreak();


  AddEntry( 3, "bmAttributes", bmAttributes, 2, "Types -", 0);

  if ((bmAttributes & 0x3) == 0)
  {
        trans = "CONTROL";
        MostRecentEndpointType = 0;
    AddDescriptionOnly(Format ("<br>&nbsp&nbsp&nbsp&nbspTransfer : %s", trans));
    if (bmAttributes & 0xFC)
    {
        AddDescriptionOnly("<br>&nbsp&nbsp&nbsp&nbspError: Reserved not 0");
    }
  }
  else if ((bmAttributes & 0x3) == 1)
  {
      trans = "ISOCHRONOUS";
      MostRecentEndpointType = 1;
      if ((bmAttributes & 0xC) == 0)
          sync = "No";
      else if ((bmAttributes & 0xC) == 0x4)
          sync = "Async";
      else if ((bmAttributes & 0xC) == 8)
          sync = "Adaptive";
      else
          sync = "Sync";

      if ((bmAttributes & 0x30) == 0)
          usage = "Data EP";
      else if ((bmAttributes & 0x30) == 0x10)
          usage = "Feedback EP";
      else if ((bmAttributes & 0x30) == 0x20)
          usage = "Implicit Feedback EP";
      else
          usage = "RESERVED";

      AddDescriptionOnly(Format ("<br>&nbsp&nbsp&nbsp&nbspTransfer: %s", trans));
      AddDescriptionOnly(Format ("<br>&nbsp&nbsp&nbsp&nbspSync:     %s", sync));
      AddDescriptionOnly(Format ("<br>&nbsp&nbsp&nbsp&nbspUsage:    %s", usage));
      if (bmAttributes & 0xC0)
      {
          AddDescriptionOnly("<br>&nbsp&nbsp&nbsp&nbspError: Reserved not 0");
      }
  }
  else if ((bmAttributes & 0x3) == 2)
  {
      trans = "BULK";
      MostRecentEndpointType = 2;
      if (bmAttributes & 0x80)
          adjust = "Yes";
      else
          adjust = "No";

      AddDescriptionOnly(Format ("<br>&nbsp&nbsp&nbsp&nbspTransfer: %s", trans));
      AddDescriptionOnly(Format ("<br>&nbsp&nbsp&nbsp&nbspPkt Size Adjust: %s", adjust));
      if (bmAttributes & 0x7C)
      {
          AddDescriptionOnly("<br>&nbsp&nbsp&nbsp&nbspError: Reserved not 0");
      }
  }
  else
  {
      trans = "INTERRUPT";
      MostRecentEndpointType = 3;
      if (bmAttributes & 0x04)
        low_power = "Yes";
      else
        low_power = "No";

      AddDescriptionOnly(Format ("<br>&nbsp&nbsp&nbsp&nbspTransfer: %s", trans));
      AddDescriptionOnly(Format ("<br>&nbsp&nbsp&nbsp&nbspLow Power: %s", low_power));

      if (bmAttributes & 0x80)
          adjust = "Yes";
      else
          adjust = "No";

      AddDescriptionOnly(Format ("<br>&nbsp&nbsp&nbsp&nbspPkt Size Adjust: %s", adjust));
      if (bmAttributes & 0x78)
      {
          AddDescriptionOnly("<br>&nbsp&nbsp&nbsp&nbspError: Reserved not 0");
      }
  }
    AddFieldBreak();

    AddEntry( 4, "wMaxPacketSize", wMaxPacketSize, 4, "Maximum packet size for" , 0);
    AddDescriptionOnly( Format ("this endpoint is %d Bytes.", (wMaxPacketSize & 0x7FF)));
    AddDescriptionOnly( Format ("If Hi-Speed, %d additional", ((wMaxPacketSize >> 11) & 0x3)));
    AddDescriptionOnly("transactions per frame");
    AddFieldBreak();

    AddEntry( 6, "bInterval", bInterval, 2, "The polling interval value is", 0);
    AddDescriptionOnly(Format ("every %d Frames.", bInterval));
    if (direction == 1)
    {
        if ((bInterval > 0) && (bInterval < 17))
        {
            _row_bi = Find(bIntervalTable, bInterval);
            AddDescriptionOnly(Format ("If Hi-Speed, every %d uFrames", _row_bi[1]));
        }
        else
        {
            AddDescriptionOnly("Undefined for Hi-Speed");
        }
    }
    else
    {
        AddDescriptionOnly(Format ("If Hi-Speed, %d uFrames/NAK", bInterval));
    }
    AddFieldBreak();
              
    if (bLength == 9) # Audio extensions to Standard Endpoint Descriptor
    {
        bRefresh           = GetDataByte(base+7);
        bSynchAddress      = GetDataByte(base+8);
        AddEntry( 7, "bRefresh", bRefresh, 2, "Refresh Rate  2**n ms", 0);
        AddDescriptionOnly(Format ("where n = %d", bRefresh ));
        AddFieldBreak();
        AddEntry( 8, "bSynchAddress", bSynchAddress, 2, "Synchronization Endpoint", 0);
        AddDescriptionOnly(Format ("(if used) is endpoint %d", bSynchAddress ));
      
        AddFieldBreak();         
    }
	
	Base += bLength;
}



#******************************************************************************
# DEVICE_QUALIFIER Descriptor definitions
#******************************************************************************
DEVICE_QUALIFIER()
{
    DescriptorCellString = "DEVICE_QUALIFIER Descriptor";
    Base = 8;
    AddDataHeader("DEVICE_QUALIFIER Descriptor", in.DataLength-8);
    DEVICE_QUALIFIER_sub();
    return GetFinalText();}

DEVICE_QUALIFIER_sub()
{
    base = Base;

    bLength             = GetDataByte(base);
    bDescriptorType     = GetDataByte(base+1);
    bcdUSB              = GetDataWord(base+2);
    bDeviceClass        = GetDataByte(base+4);
    bDeviceSubClass     = GetDataByte(base+5);
    bDeviceProtocol     = GetDataByte(base+6);
    bMaxPacketSize0     = GetDataByte(base+7);
    bNumConfigurations  = GetDataByte(base+8);
    bReserved           = GetDataByte(base+9);

    AddEntry( 0, "bLength", bLength, 2, "", 1);
    AddDescriptorSizeString(bLength);
    AddFieldBreak();

    AddEntry( 1, "bDescriptorType", bDescriptorType, 2, GetDescriptorTypeString("DEVICE_QUALIFIER"), 0);
    AddFieldBreak();
    
    doDeviceSharedStuff(bcdUSB, bDeviceClass, bDeviceSubClass, bDeviceProtocol, bMaxPacketSize0, bDescriptorType);
    
    AddEntry( 8, "bNumConfigurations", bNumConfigurations, 2, Format ("The device has %d possible", bNumConfigurations) , 0);
    AddDescriptionOnly("other-speed configurations");
    AddFieldBreak();

    if (bReserved == 0)
        AddEntry( 9, "Reserved", bReserved, 2, "Reserved for future use", 0);
    else
        AddEntry( 9, "Reserved", bReserved, 2, "Error! this bit has to be zero", 0);
    AddFieldBreak();
    
    Base += bLength;
}



#******************************************************************************
# OTHER_SPEED_CONFIGURATION Descriptor definitions
#******************************************************************************
OTHER_SPEED_CONFIGURATION()
{
    ConfigString = "OTHER_SPEED_CONFIGURATION";

    doSharedConfig();
}

OTHER_SPEED_CONFIGURATION_sub()
{
     # call the one used by normal CONFIGURATION
     CONFIGURATION_sub();

}

#******************************************************************************
# OTG Descriptor definitions
#******************************************************************************
OTG()
{
    temp_str = ("Illegal usage: GET_DESCRIPTOR  OTG type");
    temp_str = temp_str + NewLine();
    temp_str = temp_str + "Must be obtained through GET_DESCRIPTOR  CONFIGURATION type";
}

OTG_sub()
{
    base = Base;
    bLength             = GetDataByte(base);
    bDescriptorType     = GetDataByte(base+1);
    bmAttributes        = GetDataByte(base+2);
    bcdOTG              = GetDataWord(base+3);

    AddEntry( 0, "bLength", bLength, 2, "", 1);
    AddDescriptorSizeString(bLength);
    AddFieldBreak();

    AddEntry( 1, "bDescriptorType", bDescriptorType, 2, GetDescriptorTypeString("OTG"), 0);
    AddFieldBreak();

    AddEntry( 2, "bmAttributes", bmAttributes, 2, "OTG Device Characteristics", 0);
    AddDescriptionOnly(Format ("SRP Support : %d",  (bmAttributes & 0x01) ));
    AddDescriptionOnly(Format ("HNP Support : %d", ((bmAttributes & 0x02) >> 1) ));
    AddDescriptionOnly(Format ("ADP Support : %d", ((bmAttributes & 0x04) >> 2) ));
    AddFieldBreak();

    AddEntry( 3, "bcdOTG", bcdOTG, 4, "OTG Specification " , 0);    
    AddDescriptionOnly( FormatEx( "version %X.%02X", (bcdOTG & 0xFF00)>> 8, bcdOTG & 0xFF) );

    Base += bLength;
}

#******************************************************************************
# INTERFACE_ASSOCIATION  Descriptor definitions
#******************************************************************************
INTERFACE_ASSOCIATION()
{
    temp_str = ("Illegal usage: GET_DESCRIPTOR  INTERFACE_ASSOCIATION type");
    temp_str = temp_str + NewLine();
    temp_str = temp_str + "Must be obtained through GET_DESCRIPTOR  CONFIGURATION type";
}

INTERFACE_ASSOCIATION_sub()
{
    base = Base;

    bLength            = GetDataByte(base);
    bDescriptorType    = GetDataByte(base+1);
    bFirstInterface    = GetDataByte(base+2);
    bInterfaceCount    = GetDataByte(base+3);
    bFunctionClass     = GetDataByte(base+4);
    bFunctionSubClass  = GetDataByte(base+5);
    bFunctionProtocol  = GetDataByte(base+6);
    iFunction          = GetDataByte(base+7);

    AddEntry( 0, "bLength", bLength, 2, "", 1);
    AddDescriptorSizeString(bLength);
    AddFieldBreak();

    AddEntry( 1, "bDescriptorType", bDescriptorType, 2, GetDescriptorTypeString("INTERFACE_ASSOCIATION"), 0);
    AddFieldBreak();

    AddEntry( 2, "bFirstInterface", bFirstInterface, 2, "The first interface" , 0);
    AddDescriptionOnly("number associated with");
    AddDescriptionOnly( Format ("this function is %d", bFirstInterface));
    AddFieldBreak();

    AddEntry( 3, "bInterfaceCount", bInterfaceCount, 2, "The number of contiguous" , 0);
    AddDescriptionOnly("interfaces associated with");
    AddDescriptionOnly( Format ("this function is %d", bInterfaceCount));
    AddFieldBreak();

    subclass_done = 0;
    protocol_done = 0;

    _row_d = Find(DeviceClassTable, bFunctionClass);
    MostRecentClass = bFunctionClass;
    MostRecentSubClass = bFunctionSubClass;
    MostRecentProtocol = bFunctionProtocol;
    
    #AddLineOfText( FormatEx ("FUNCTION MostRecentClass =%d %d", MostRecentClass, bFunctionClass ));
    if (bFunctionClass == 0)
    {
        AddEntry( 4, "bFunctionClass", bFunctionClass, 2, "VALUE NOT ALLOWED!" , 0);
    }
    else if (bFunctionClass == 0xFF)
    {
        AddEntry( 4, "bFunctionClass", bFunctionClass, 2, "The Function Class" , 0);
        AddDescriptionOnly( "is vendor-specific" );
    }
    else if (_row_d[0] != 0xFF)
    {
        AddEntry( 4, "bFunctionClass", bFunctionClass, 2, "The function" , 0);
        AddDescriptionOnly( "belongs to the" );
        AddDescriptionOnly( FormatEx ("%s Class", _row_d[2]) );
		
		_subclass_desc = "";
		
		# If Interface Association Descriptor specific function defined for extracting of subclass
		if (_row_d[4] != null)
		{
			_subclass_desc = Call(_row_d[4], [bFunctionSubClass, bFunctionProtocol]);
		}
        else if (_row_d[3] != null)
        {
            _row_sc = Find(_row_d[3], bFunctionSubClass);

            if (_row_sc[0] != 0xFF)
            {
				_subclass_desc = _row_sc[1];
            }
        }
		
		if ((_row_d[4] != null) || (_row_d[3] != null))
		{
			AddFieldBreak();
			
            if (_subclass_desc)
            {
                AddEntry( 5, "bFunctionSubClass", bFunctionSubClass, 2, "The function" , 0);
                AddDescriptionOnly( "belongs to the" );
                AddDescriptionOnly( FormatEx ("%s Subclass", _subclass_desc) );
            }
            else
            {
               AddEntry( 5, "bFunctionSubClass", bFunctionSubClass, 2, "Subclass" , 0);
                AddDescriptionOnly( FormatEx ("0x%02X not defined", bFunctionSubClass) );
            }
            subclass_done = 1;
		}
		
        if (_row_d[5] != null)
        {
            AddFieldBreak();
            _row_p = Find(_row_d[5], bFunctionProtocol);

            if (_row_p[0] != 0xFF)
            {
                AddEntry( 6, "bFunctionProtocol", bFunctionProtocol, 2, "The function uses the" , 0);
                AddDescriptionOnly( FormatEx ("%s Protocol", _row_p[1]) );
            }
            else
            {
                AddEntry( 6, "bFunctionProtocol", bFunctionProtocol, 2, "Protocol" , 0);
                AddDescriptionOnly( FormatEx ("0x%02X not defined", bFunctionProtocol) );
            }
            protocol_done = 1;
        }

    }
    else
    {
        AddEntry( 4, "bFunctionClass", bFunctionClass, 2, "Unknown Class" , 0);
    }

    if (subclass_done == 0)
    {
        AddFieldBreak();
        if (bFunctionSubClass == 0xFF)
        {
            AddEntry( 5, "bFunctionSubClass", bFunctionSubClass, 2, "The function Subclass" , 0);
            AddDescriptionOnly("is vendor-specific");
        }
        else
        {
            AddEntry( 5, "bFunctionSubClass", bFunctionSubClass, 2, Format ("Subclass code = %d", bFunctionSubClass) , 0);
        }
    }

    if (protocol_done == 0)
    {
        AddFieldBreak();
        if (bFunctionProtocol == 0xFF)
        {
            AddEntry( 6, "bFunctionProtocol", bFunctionProtocol, 2, "The function Protocol" , 0);
            AddDescriptionOnly("is vendor-specific");
        }
        else
        {
            AddEntry( 6, "bFunctionProtocol", bFunctionProtocol, 2, Format ("Protocol code = %d", bFunctionProtocol) , 0);
        }
    }

    AddFieldBreak();

    AddEntry( 7, "iFunction", iFunction, 2, "The Function" , 0);
    AddDescriptionOnly("string descriptor");
    AddDescriptionOnly(Format ("index is %d", iFunction ));
    AddFieldBreak();
    
    Base += bLength;
}






#******************************************************************************
# SECURITY Descriptor definitions
#******************************************************************************
SECURITY()
{

    DescriptorCellString = "SECURITY Descriptor";

    curr_offset = 8;
    bLength            = GetDataByte(curr_offset);
    bDescriptorType    = GetDataByte(curr_offset+1);
    wTotalLength       = GetDataWord(curr_offset+2);
    bNumEncryptionTypes= GetDataByte(curr_offset+4);

    descriptor_count = 0;

    if (IsTooltip)
    {
        if (in.DataLength > (bLength+8))
        {
            AddLineOfText("RIGHT CLICK ON DESCRIPTORS FIELD TO SHOW ALL DESCRIPTORS DECODED!!");
        }
        Base = 8;
        AddDataHeader(DescriptorCellString, in.DataLength-8);
        SECURITY_sub();

        more_left = MaxNumberOfDescriptorsWeShouldDecode; # max num descriptors we will decode in 1 config statement



        while (more_left > 0)
        {
            descriptor_count = descriptor_count + 1;
            curr_offset += (bLength & 0xFF);            #DescriptorCellString = FormatEx ("%d %d %d %d", descriptor_count, curr_offset, bLength, in.DataLength);

            if (curr_offset >= in.DataLength)
            {
                more_left = 0;
            }
            else
            {
                bLength = GetDataByte(curr_offset);
                more_left = more_left - 1;
            }
        }

        if ( descriptor_count > 1)
        {
            DescriptorCellString = Format ("%d Descriptors", descriptor_count);            #DescriptorCellString = FormatEx ("%d %d %d", descriptor_count, curr_offset, in.DataLength);
        }
    }
    else
    {
        AddDataStageTitle(in.DataLength-8);
        AddDash();

        more_left = MaxNumberOfDescriptorsWeShouldDecode; # max num descriptors we will decode in 1 config statement
        curr_offset = 8;

        descriptor_count = 0;

        while (more_left)
        {
            descriptor_count++;
            AddBlankLine();

            _row_dtt2 = FindDescriptorEntryEx( bDescriptorType );

            #AddLineOfText( FormatEx ("count=%d  bDescriptorType=%d row=0x%X", descriptor_count,  bDescriptorType, _row_dtt2 ));
            Base = curr_offset;
            if (_row_dtt2[0] != 0xFF)
            {
                AddShortDataHeader(FormatEx ("%s Descriptor  (%d bytes)", _row_dtt2[1], bLength ));
                Call (_row_dtt2[2]);
            }
            else
            {
                #AddLineOfText( FormatEx ("count=%d  bDescriptorType=%d MostRecentClass =%d", descriptor_count,  bDescriptorType, MostRecentClass ));
              # if ( MostRecentClass == 0x0E) # DC_VIDEO
              # {
              #      result = TryVideoDescriptors(bDescriptorType);
              # }
                #else if ( MostRecentClass == 0xYourClassValue ) # add additional class-specific descriptor decodes here
                #{
                #    result = YourDescriptorDecoderName(bDescriptorType);
                #}
              # else
                {
                    result = 0;
                }

                #AddLineOfText( FormatEx ("count=%d  bDescriptorType=%d", descriptor_count,  bDescriptorType ));
                if (result == 0)
                {
                    AddDash();
                    AddLineOfText( FormatEx("Unknown Descriptor Type: 0x%02X   (%d bytes)", bDescriptorType, bLength));
                    OutputUnknownData(bLength, 0);
                    AddDash();
                    #AddBlankLine();
                }

            }


            curr_offset = curr_offset + bLength;
            #AddLineOfText( FormatEx ("2 bLength=%d  curr_offset=%d  in.DataLength=%d", bLength, curr_offset, in.DataLength ));
            if (curr_offset >= in.DataLength)
            {
                more_left = 0;
            }
            else
            {
                 bLength            = GetDataByte(curr_offset);
                 bDescriptorType    = GetDataByte(curr_offset+1);
                 #AddLineOfText( FormatEx ("3 bLength=%d  curr_offset=%d", bLength, curr_offset ));
                 more_left--;
            }
        }
    }

    return GetFinalText();
}

SECURITY_sub()
{
    base = Base;

    bLength             = GetDataByte(base);
    bDescriptorType     = GetDataByte(base+1);
    wTotalLength        = GetDataWord(base+2);
    bNumEncryptionTypes = GetDataByte(base+4);


    AddEntry( 0, "bLength", bLength, 2, "", 1);
    AddDescriptorSizeString(bLength);
    AddFieldBreak();

    AddEntry( 1, "bDescriptorType", bDescriptorType, 2, GetDescriptorTypeString("SECURITY"), 0);
    AddFieldBreak();

    AddEntry( 2, "wTotalLength", wTotalLength, 4, "The total length of data", 0);
    AddDescriptionOnly(Format ("for this Security Descriptor is %d.", wTotalLength));
    AddDescriptionOnly("This includes the combined length");
    AddDescriptionOnly("of all the descriptors returned");
    AddFieldBreak();

    AddEntry( 4, "bNumEncryptionTypes", bNumEncryptionTypes, 2, "This configuration supports", 0);
    AddDescriptionOnly(Format ("%i Encryption Types", bNumEncryptionTypes));
    AddFieldBreak();

    Base += bLength;
}




set EncryptionTypeTable =
[
      [ 0xFF, "Illegal Value" ],
      [ 0x00, "UNSECURE: No Encryption" ],
      [ 0x01, "WIRED: Virtual Encrypt"],
      [ 0x02, "CCM_1: AES-128 in CCM Mode" ],
      [ 0x03, "RSA_1: RSA-3072 w/ SHA-256 hash" ]
];

#******************************************************************************
# ENCRYPTION_TYPE Descriptor definitions
#******************************************************************************
ENCRYPTION_TYPE()
{
    temp_str = ("Illegal usage: GET_DESCRIPTOR  ENCRYPTION_TYPE type");
    temp_str = temp_str + NewLine();
    temp_str = temp_str + "Must be obtained through GET_DESCRIPTOR  SECURITY type";
}

ENCRYPTION_TYPE_sub()
{
    base = Base;
    bLength             = GetDataByte(base);
    bDescriptorType     = GetDataByte(base+1);
    bEncryptionType     = GetDataByte(base+2);
    bEncryptionValue    = GetDataByte(base+3);
    bAuthKeyIndex       = GetDataByte(base+4);

    AddEntry( 0, "bLength", bLength, 2, "", 1);
    AddDescriptorSizeString(bLength);
    AddFieldBreak();

    AddEntry( 1, "bDescriptorType", bDescriptorType, 2, GetDescriptorTypeString("ENCRYPTION"), 0);
    AddFieldBreak();

    _row_e = Find(EncryptionTypeTable, bEncryptionType);
    if (_row_e[0] != 0xFF)
    {
        AddEntry( 2, "bEncryptionType", bEncryptionType, 2, FormatEx ("%s", _row_e[1]) , 0);
    }
    else
    {
        AddEntry( 2, "bEncryptionType", bEncryptionType, 2, Format ("Illegal Type : %d",  bEncryptionType) , 0);
    }
    AddFieldBreak();

    AddEntry( 3, "bEncryptionValue", bEncryptionValue, 2, "Val for Set Encryption", 0);
    AddDescriptionOnly(Format("Value is %d", bEncryptionValue));
    AddFieldBreak();

    AddEntry( 4, "bAuthKeyIndex", bAuthKeyIndex, 2, "Non-zero if this type", 0);
    AddDescriptionOnly("can be used for New connect");
    AddDescriptionOnly("Authentication.  Value");
    AddDescriptionOnly("specifies Key Index to");
    AddDescriptionOnly("use for Authentication.");
    AddDescriptionOnly(Format("Value is %d", bAuthKeyIndex));
    AddFieldBreak();

    Base += bLength;
}


#******************************************************************************
# KEY Descriptor definitions
#******************************************************************************
KEY()
{
    temp_str = ("Illegal usage: GET_DESCRIPTOR  KEY type");
    temp_str = temp_str + NewLine();
    temp_str = temp_str + "Must be obtained through GET_DESCRIPTOR  SECURITY type";
}

KEY_sub()
{
    base = Base;
    bLength             = GetDataByte(base);
    bDescriptorType     = GetDataByte(base+1);
    tTKID               = GetDataByte(base+2) + ((GetDataByte(base+3))<< 8) + ((GetDataByte(base+4)) << 16);
    bReserved           = GetDataWord(base+5);

    bmAttributes        = GetDataWord(base+6+i);

    AddEntry( 0, "bLength", bLength, 2, "", 1);
    AddDescriptorSizeString(bLength);
    AddFieldBreak();

    AddEntry( 1, "bDescriptorType", bDescriptorType, 2, GetDescriptorTypeString("KEY"), 0);
    AddFieldBreak();

    AddEntry( 2, "tTKID", tTKID, 3, FormatEx("0x%06X", tTKID) , 0);
    AddFieldBreak();

    AddEntry( 3, "bReserved", bReserved, 2, "" , 0);
    AddFieldBreak();

    bytes_left = in.DataLength - base - 6;
    i = 0;

    while (bytes_left > 0)
    {
        AddEntry( 4+i, "Key Data", GetDataWord(base+6+i), 2, "" , 0); 
        AddFieldBreak();
        bytes_left--;
        i++;
    }

    Base += bLength;
}







#******************************************************************************
# BOS Descriptor definitions
#******************************************************************************
BOS()
{

    DescriptorCellString = "BOS Descriptor";

    curr_offset = 8;
    bLength            = GetDataByte(curr_offset);
    bDescriptorType    = GetDataByte(curr_offset+1);
    wTotalLength       = GetDataWord(curr_offset+2);
    bNumDeviceCaps     = GetDataByte(curr_offset+4);

    descriptor_count = 0;

    if (IsTooltip)
    {
        if (wTotalLength > (bLength+8))
        {
            AddLineOfText("RIGHT CLICK ON DESCRIPTORS FIELD TO SHOW ALL DESCRIPTORS DECODED!!");
        }
        Base = 8;
        AddDataHeader(DescriptorCellString, in.DataLength-8);
        BOS_sub();

        more_left = MaxNumberOfDescriptorsWeShouldDecode; # max num descriptors we will decode in 1 config statement



        while (more_left > 0)
        {
            descriptor_count = descriptor_count + 1;
            curr_offset += (bLength & 0xFF);            #DescriptorCellString = FormatEx ("%d %d %d %d", descriptor_count, curr_offset, bLength, in.DataLength);

            if (curr_offset >= in.DataLength)
            {
                more_left = 0;
            }
            else
            {
                bLength = GetDataByte(curr_offset);
                more_left = more_left - 1;
            }
        }

        if ( descriptor_count > 1)
        {
            DescriptorCellString = Format ("%d Descriptors", descriptor_count);            #DescriptorCellString = FormatEx ("%d %d %d", descriptor_count, curr_offset, in.DataLength);
        }
    }
    else
    {
        AddDataStageTitle(in.DataLength-8);
        AddDash();

        more_left = MaxNumberOfDescriptorsWeShouldDecode; # max num descriptors we will decode in 1 config statement
        curr_offset = 8;

        descriptor_count = 0;

        while (more_left)
        {
            descriptor_count++;
            AddBlankLine();

            _row_dtt2 = FindDescriptorEntryEx( bDescriptorType );

            #AddLineOfText( FormatEx ("count=%d  bDescriptorType=%d row=0x%X", descriptor_count,  bDescriptorType, _row_dtt2 ));
            Base = curr_offset;
            if (_row_dtt2[0] != 0xFF)
            {
                AddShortDataHeader(FormatEx ("%s Descriptor  (%d bytes)", _row_dtt2[1], bLength ));
                Call (_row_dtt2[2]);
            }
            else
            {
                #AddLineOfText( FormatEx ("count=%d  bDescriptorType=%d MostRecentClass =%d", descriptor_count,  bDescriptorType, MostRecentClass ));
              # if ( MostRecentClass == 0x0E) # DC_VIDEO
              # {
              #      result = TryVideoDescriptors(bDescriptorType);
              # }
                #else if ( MostRecentClass == 0xYourClassValue ) # add additional class-specific descriptor decodes here
                #{
                #    result = YourDescriptorDecoderName(bDescriptorType);
                #}
              # else
                {
                    result = 0;
                }

                #AddLineOfText( FormatEx ("count=%d  bDescriptorType=%d", descriptor_count,  bDescriptorType ));
                if (result == 0)
                {
                    AddDash();
                    AddLineOfText( FormatEx("Unknown Descriptor Type: 0x%02X   (%d bytes)", bDescriptorType, bLength));
                    if ( ( in.DataLength - Base ) > 0 )
                    {
                        OutputUnknownData(in.DataLength - Base, 0);
                    }
                    AddDash();
                    #AddBlankLine();
                }

                Base = in.DataLength;
            }


            # subroutines should modify Base to data offset at which they finished.
            curr_offset = Base;
            
            #AddLineOfText( FormatEx ("2 bLength=%d  curr_offset=%d  in.DataLength=%d", bLength, curr_offset, in.DataLength ));
            # Minus 2 because we need at least 2 bytes to read the next bLength and bDescriptorType
            if (curr_offset >= (in.DataLength-2))
            {
                more_left = 0;
                
                if ( curr_offset < in.DataLength )
                {
                	  extra_len = in.DataLength - curr_offset;
                	  # output extra bytes
                	  AddStringToDlg( "Undecoded Data", FormatEx( "(%d bytes)", extra_len), OutputUnknownData(extra_len, 0) );
                }
            }
            else
            {
                 bLength            = GetDataByte(curr_offset);
                 bDescriptorType    = GetDataByte(curr_offset+1);
                 #AddLineOfText( FormatEx ("3 bLength=%d  curr_offset=%d", bLength, curr_offset ));
                 more_left--;
            }
        }
    }

    return GetFinalText();
}

BOS_sub()
{
    base = Base;

    bLength             = GetDataByte(base);
    bDescriptorType     = GetDataByte(base+1);
    wTotalLength        = GetDataWord(base+2);
    bNumDeviceCaps      = GetDataByte(base+4);


    AddEntry( 0, "bLength", bLength, 2, "", 1);
    AddDescriptorSizeString(bLength);
    AddFieldBreak();

    AddEntry( 1, "bDescriptorType", bDescriptorType, 2, GetDescriptorTypeString("BOS"), 0);
    AddFieldBreak();

    AddEntry( 2, "wTotalLength", wTotalLength, 4, "The total length of data", 0);
    AddDescriptionOnly(Format ("for this Binary Device Object is %d.", wTotalLength));
    AddDescriptionOnly("This includes the combined length");
    AddDescriptionOnly("of all the descriptors returned");
    AddFieldBreak();

    AddEntry( 4, "bNumDeviceCaps", bNumDeviceCaps, 2, "This configuration supports", 0);
    AddDescriptionOnly(Format ("%i Device Capability descriptors", bNumDeviceCaps));
    AddFieldBreak();

    Base += 5;
}

####################################################################################################
#  USB Billboard Device Rev 1.0 Table 6-3 Billboard Capability Descriptor (inside BOS descriptor)  #
####################################################################################################
DecodeBillboardDeviceCapability(bDevCapabiltyType)
{
    base = Base;
    
    AddEntry( 2, "bDevCapabiltyType", bDevCapabiltyType, 2, "BILLBOARD_CAPABILITY", 0);
    AddFieldBreak();
    
    ##############
    
    iAddtionalInfoURL = GetDataByte(base+3);
    AddEntry( 3, "iAddtionalInfoURL", iAddtionalInfoURL, 2, "Index of string descriptor for additional info URL is: ", 0);
    AddDescriptionOnly(iAddtionalInfoURL);
    AddFieldBreak();
    
    ###############    
    
    bNumberOfAlternateModes = GetDataByte(base+4);
    AddEntry( 4, "bNumberOfAlternateModes", bNumberOfAlternateModes, 2, "Number of Alternate modes supported:" , 0);    
    AddDescriptionOnly(bNumberOfAlternateModes);
    AddFieldBreak();
    
    ###############
    
    bPreferredAlternateMode= GetDataByte(base+5);
    AddEntry( 5, "bPreferredAlternateMode", bPreferredAlternateMode, 2, "Index of the preferred Alternate mode:", 0);
    AddDescriptionOnly(bPreferredAlternateMode);        
    AddFieldBreak();
    
    ###############
    
    ForceFullDescriptions();
    
    VCONN_Power = GetDataWord(base+6);
    
    #Bits 2..0
    bit_0_2 = VCONN_Power & 0x7;
    
    if     (bit_0_2 == 0)
        power = "1W";
    else if(bit_0_2 == 1)
        power = "1.5W";
    else if(bit_0_2 == 2)
        power = "2W";
    else if(bit_0_2 == 3)
        power = "3W";
    else if(bit_0_2 == 4)
        power = "4W";
    else if(bit_0_2 == 5)
        power = "5W";
    else if(bit_0_2 == 6)
        power = "6W";
    else
        power = "undefined";
        
        
    if(VCONN_Power & 0x8000)
    {
        description = "Adapter dose not require any V_CONN Power";
    }
    else
    {
        description = Format("V_CONN Power needed by adapter for full functionality: %s", power);
    }
    
    AddEntry( 6, "VCONN Power", VCONN_Power, 4, description, 0);
    AddFieldBreak();
    
    ###############
    
    bm_configured_offset = base + 8;
    alternate_state_index_start = 0;
    
    #For simplicity of showing data we separate bmConfigured(32 Bytes) field to word(2 Bytes) units and each unit contains state of 4 alternate modes.
    #Each 2 bits use for each alternate mode's state.
    for( word_counter = 0 ; word_counter < 16 ; word_counter += 1)
    {
        bm_configured_n = GetDataWord(bm_configured_offset + (word_counter * 2));
        
        alternate_state_index = (word_counter * 8);
        
        bm_configured_field_name  = Format("bmConfigured[%03d to ", alternate_state_index);
        bm_configured_field_name += Format("%03d]", alternate_state_index + 7);
        
        AddEntry( 8 + (word_counter * 2) , bm_configured_field_name, bm_configured_n, 4, "Alternate modes:", 0);
        
        if(alternate_state_index <= (bNumberOfAlternateModes - 1))
        {
            for(bit_pair_counter = 0 ; bit_pair_counter < 8 ; bit_pair_counter += 1)
            {
                alternate_mode_index = alternate_state_index + bit_pair_counter;
                
                bm_configured_n_state  = Format("<br>&nbsp&nbsp&nbsp&nbspbmConfigured[%03d]=", alternate_mode_index);
                
                if(alternate_mode_index <= (bNumberOfAlternateModes - 1))
                {
                    bm_configured = (bm_configured_n >> (bit_pair_counter * 2));
                    bm_configured = (bm_configured & 0x03);
                    bm_configured_n_state += Format("%d : ", bm_configured);
                    
                    if(bm_configured == 0)
                        state_desc = "Unspecified Error";
                    else if(bm_configured == 1)
                        state_desc = "Not attempted";
                    else if(bm_configured == 2)
                        state_desc = "Attempted but unsuccessful";
                    else if(bm_configured == 3)
                        state_desc = "Successful";
                }
                else
                {
                    state_desc = "Undefined Alternate Mode";
                }
                
                bm_configured_n_state += Format("%s", state_desc);
                
                AddDescriptionOnly(bm_configured_n_state);
            }
        }
        else
        {
            AddDescriptionOnly("Undefined Alternate Mode");
        }
        
        AddFieldBreak();
    }

    ###############

    bReserved = GetDataLong(base+40);
    AddEntry( 40, "bReserved", bReserved, 8, "Reserved for future use, shall be set to zero", 0);
    AddFieldBreak();    
    
    ###############
 
    offset_in_struct = 44;
    
    #Extract wSVID[n], bAlternateMode[0] and iAlternateModeString[0] for each alternate mode
    for( alternate_mode_counter = 0 ; alternate_mode_counter < bNumberOfAlternateModes ; alternate_mode_counter += 1)
    {
        offset = offset_in_struct + (alternate_mode_counter * 4);
        
        wSVID_n = GetDataWord(base + offset);
        AddEntry(offset , Format("wSVID[%03d]", alternate_mode_counter), wSVID_n, 4, "Standard or Vendor ID:", 0);
        AddDescriptionOnly(Format("0x%04X", wSVID_n));
        AddFieldBreak();
        
        bAlternateMode = GetDataByte(base + offset + 2);
        AddEntry( offset + 2, Format("bAlternateMode[%03d]", alternate_mode_counter), bAlternateMode, 2, "Index of the Alternate mode:", 0);
        AddDescriptionOnly(Format("%d", bAlternateMode));
        AddFieldBreak();
        
        iAlternateModeString = GetDataByte(base + offset + 3);
        AddEntry( offset + 3, Format("iAlternateModeString[%03d]", alternate_mode_counter), iAlternateModeString, 2, "Index of string descriptor:", 0);
        AddDescriptionOnly(Format("%d", iAlternateModeString));
        AddFieldBreak();
    }
    
    DontForceFullDescriptions();
    
    ###############
}



#******************************************************************************
# DEVICE_CAPABILITY Descriptor definitions
#******************************************************************************
DEVICE_CAPABILITY()
{
    temp_str = ("Illegal usage: GET_DESCRIPTOR  DEVICE_CAPABILITY type");
    temp_str = temp_str + NewLine();
    temp_str = temp_str + "Must be obtained through GET_DESCRIPTOR  BOS type";
}

DEVICE_CAPABILITY_sub()
{
    base = Base;
    bLength             = GetDataByte(base);
    bDescriptorType     = GetDataByte(base+1);
    bDevCapabiltyType   = GetDataByte(base+2);

    AddEntry( 0, "bLength", bLength, 2, "", 1);
    AddDescriptorSizeString(bLength);
    AddFieldBreak();

    AddEntry( 1, "bDescriptorType", bDescriptorType, 2, GetDescriptorTypeString("DEVICE_CAPABILITY"), 0);
    AddFieldBreak();
    
    if (bDevCapabiltyType == DCT_WIRELESS_USB)
    {
        # Wireless_USB type
        AddEntry( 2, "bDevCapabiltyType", bDevCapabiltyType, 2, "WIRELESS_USB", 0);
        AddFieldBreak();

        bmAttributes = GetDataByte(base+3);

        if (bmAttributes & 0x2)
            p2p = "Yes ";
        else
            p2p = "No";

        if      (((bmAttributes & 0xC) >> 2) == 1)
            beacon = "Self";
        else if (((bmAttributes & 0xC) >> 2) == 2)
            beacon = "Directed";
        else if (((bmAttributes & 0xC) >> 2) == 3)
            beacon = "No";
        else
            beacon = "Error!";


        AddEntry( 3, "bmAttributes", bmAttributes, 2, "Attributes -", 0);
        AddDescriptionOnly(Format ("P2P-DRD : %s", p2p));
        AddDescriptionOnly(Format ("Beacon  : %s", beacon));
        if (bmAttributes & 0xF1)
            AddDescriptionOnly("Error: Reserved not 0");
        AddFieldBreak();

        wPhyRates = GetDataWord(base+4);

        AddEntry( 4, "wPhyRates", wPhyRates, 4, "Phy Rates Supported -", 0);
        phyRates = "";
        if (wPhyRates  & 0x1)  phyRates = "53.3 ";
        if (wPhyRates  & 0x2)  phyRates = phyRates + "80 ";
        if (wPhyRates  & 0x4)  phyRates = phyRates + "106.7 ";
        if (wPhyRates  & 0x8)  phyRates = phyRates + "160 ";
        AddDescriptionOnly(phyRates);

        phyRates = "";
        if (wPhyRates  & 0x10)  phyRates = "200 ";
        if (wPhyRates  & 0x20)  phyRates = phyRates + "320 ";
        if (wPhyRates  & 0x40)  phyRates = phyRates + "400 ";
        if (wPhyRates  & 0x80)  phyRates = phyRates + "480 ";
        AddDescriptionOnly(phyRates);
        if (wPhyRates & 0xFF00)
        AddDescriptionOnly("Error: Reserved not 0");
        AddFieldBreak();


        bmTFITXPowerInfo = GetDataByte(base+6);

        AddEntry( 6, "bmTFITXPowerInfo", bmTFITXPowerInfo, 2, "TFI PowerInfo -", 0);
        AddDescriptionOnly(FormatEx("Power Level Steps: %d", bmTFITXPowerInfo & 0xF));
        int_part = ((bmTFITXPowerInfo >> 4) + 4)/4;
        dec_part = ((bmTFITXPowerInfo >> 4)%4)*25;
        AddDescriptionOnly(FormatEx("Step Size (db): %d.%d", int_part, dec_part));
        AddFieldBreak();


        bmFFITXPowerInfo = GetDataByte(base+7);

        AddEntry( 7, "bmFFITXPowerInfo", bmFFITXPowerInfo, 2, "FFI PowerInfo -", 0);
        AddDescriptionOnly(FormatEx("Power Level Steps: %d", bmFFITXPowerInfo & 0xF));
        int_part = ((bmFFITXPowerInfo >> 4) + 4)/4;
        dec_part = ((bmFFITXPowerInfo >> 4)%4)*25;
        AddDescriptionOnly(FormatEx("Step Size (db): %d.%d", int_part, dec_part));
        AddFieldBreak();


        bmBandGroup = GetDataWord(base+8);

        AddEntry( 8, "bmBandGroup", bmBandGroup, 4, "Band Groups Supported -", 0);
        bandGroup = "";
        if (bmBandGroup  &   1)  bandGroup = "1 ";
        if (bmBandGroup  &   2)  bandGroup = bandGroup + "2";
        if (bmBandGroup  &   4)  bandGroup = bandGroup + "3";
        if (bmBandGroup  &   8)  bandGroup = bandGroup + "4";
        if (bmBandGroup  &0x10)  bandGroup = bandGroup + "5";
        AddDescriptionOnly(bandGroup);

        if (bmBandGroup & 0xFFE0)
            AddDescriptionOnly("Error: Reserved not 0");
        AddFieldBreak();



        bReserved = GetDataByte(base+10);

        AddEntry( 10, "bReserved", bReserved, 2, "", 0);
        if (bReserved)
        {
            AddDescriptionOnly("Error: Reserved not 0");
        }
        AddFieldBreak();
                
        Base += 11;

    }
    
    else if (bDevCapabiltyType == DCT_USB_20_EXTENSION)
    {
        # USB 2.0 EXTENSION type
        AddEntry( 2, "bDevCapabiltyType", bDevCapabiltyType, 2, "USB 2.0 EXTENSION", 0);
        AddFieldBreak();

        bmAttributes = GetDataLong(base+3);
        
        new_lpm_support = FALSE;
            
        if (bmAttributes & 0x00000004)
        {
            if (bmAttributes & 0x00000002)
            {
                lpm = "LPM: BESL & Alt HIRD supt";
                if (bmAttributes & 0x00000008)
                {
                    baseline_besl_valid = Format ("- Base BESL : %d", (bmAttributes  >> 8) &0xF);
                    lpm = lpm + baseline_besl_valid;
                }    
                if (bmAttributes & 0x00000010)
                {
                    deep_besl_valid = Format ("- Deep BESL : %d", (bmAttributes  >> 12) &0xF);
                    lpm = lpm + baseline_besl_valid;
                }
            }
            else
            {
                lpm = "Error: bit 2 cannot be set if bit 1 is 0";
            }
        }
        else
        {
            if (bmAttributes & 0x00000002)
            {
                lpm = "LPM: Pre 7//2007-errata support";
            }
            else
            {
                lpm = "No LPM support";
            }
        }
            
        AddEntry( 3, "bmAttributes", bmAttributes, 8, "Attributes:<br>", 0);
        AddDescriptionOnly(Format ("&nbsp&nbspLink Power Management : %s", lpm));
        
        if (bmAttributes & 0xFFFF00E1)
        {
            AddDescriptionOnly("<br>-- Error: Reserved bits not 0 --");            
        }
        AddFieldBreak();
        
        
        Base += bLength; # Assume it was self-correct
        
    }
    else if (bDevCapabiltyType == DCT_SUPERSPEED_USB)
    {
    	 DecodeSuperSpeedUSBDeviceCapability(bDevCapabiltyType);
		    
         Base += bLength; # Assume it was self-correct
    }
    else if (bDevCapabiltyType == DCT_CONTAINER_ID)
    {
    	 DecodeContainerIdDeviceCapability(bDevCapabiltyType, bLength);
		    
         Base += bLength; # Assume it was self-correct
    }
    else if (bDevCapabiltyType == DCT_PLATFORM)
    {
    	 DecodePlatformDeviceCapability(bDevCapabiltyType, bLength);
		    
         Base += bLength; # Assume it was self-correct
    }
    else if (bDevCapabiltyType == DCT_POWER_DELIVERY_CAPABILITY)
    {
    	 DecodePDDeviceCapability(bDevCapabiltyType, bLength);
		    
         Base += bLength; # Assume it was self-correct
    }
    else if (bDevCapabiltyType == DCT_BATTERY_INFO_CAPABILITY)
    {
    	 DecodePDBatteryInfoDeviceCapability(bDevCapabiltyType, bLength);
		    
         Base += bLength; # Assume it was self-correct
    }
    else if (bDevCapabiltyType == DCT_PD_CONSUMER_PORT_CAPABILITY)
    {
    	 DecodePDConsumerPortDeviceCapability(bDevCapabiltyType, bLength);
		    
         Base += bLength; # Assume it was self-correct
    }
    else if (bDevCapabiltyType == DCT_PD_PROVIDER_PORT_CAPABILITY)
    {
    	 DecodePDProviderPortDeviceCapability(bDevCapabiltyType, bLength);
		    
         Base += bLength; # Assume it was self-correct
    }
    else if (bDevCapabiltyType == DCT_SUPERSPEED_PLUS)
    {
    	 DecodeUSBSSPDeviceCapability(bDevCapabiltyType, bLength);
		    
         Base += bLength; # Assume it was self-correct
    }
    else if (bDevCapabiltyType == DCT_BILLBOARD_CAPABILITY)
    {
    	 DecodeBillboardDeviceCapability(bDevCapabiltyType);
		    
         Base += bLength; # Assume it was self-correct
    }
}

#******************************************************************************
# WIRELESS_ENDPOINT_COMPANION Descriptor definitions
#******************************************************************************
WIRELESS_ENDPOINT_COMPANION()
{
    temp_str = ("Illegal usage: GET_DESCRIPTOR  WIRELESS_ENDPOINT_COMPANION type");
    temp_str = temp_str + NewLine();
    temp_str = temp_str + "Must be obtained through GET_DESCRIPTOR  CONFIG type";
}

WIRELESS_ENDPOINT_COMPANION_sub()
{
    base = Base;
    bLength              = GetDataByte(base);
    bDescriptorType      = GetDataByte(base+1);
    bMaxBurst            = GetDataByte(base+2);
    bMaxSequence         = GetDataByte(base+3);
    wMaxStreamDelay      = GetDataWord(base+4);
    wOverTheAirPacketSize= GetDataWord(base+6);
    bOverTheAirInterval  = GetDataByte(base+8);
    bmCompAttributes     = GetDataByte(base+9);

    AddEntry( 0, "bLength", bLength, 2, "", 1);
    AddDescriptorSizeString(bLength);
    AddFieldBreak();

    AddEntry( 1, "bDescriptorType", bDescriptorType, 2, GetDescriptorTypeString("WIRELESS_ENDPOINT_COMPANION"), 0);
    AddFieldBreak();

    AddEntry( 2, "bMaxBurst", bMaxBurst, 2, "Max Send/Recv", 0);
    AddDescriptionOnly(Format(" Burst Rate is %d", bMaxBurst));
    if ((bMaxBurst == 0) || (bMaxBurst > 16))
    {
        AddDescriptionOnly("Error: Must be between");
        AddDescriptionOnly("1 and 16, inclusive");
    }
    AddFieldBreak();

    AddEntry( 3, "bMaxSequence", bMaxSequence, 2, "Max Sequence Number", 0);
    AddDescriptionOnly(Format("is %d", bMaxSequence));
    if ((bMaxSequence < 2) || (bMaxSequence > 32))
    {
        AddDescriptionOnly("Error: Must be between");
        AddDescriptionOnly("2 and 32, inclusive");
    }
    AddFieldBreak();

    AddEntry( 4, "wMaxStreamDelay", wMaxStreamDelay, 4, "Max number of 128uS", 0);
    AddDescriptionOnly("delay increments");
    AddDescriptionOnly(Format("supported is %d", wMaxStreamDelay));
    AddFieldBreak();

    AddEntry( 6, "wOverTheAirPacketSize", wOverTheAirPacketSize, 4, "Max isoch packet", 0);
    AddDescriptionOnly(Format("size is %d", wOverTheAirPacketSize));
    AddFieldBreak();

   AddEntry( 8 , "bOverTheAirInterval", bOverTheAirInterval, 2, "Isoch Polling ", 0);
   AddDescriptionOnly("Interval Exponent");
   AddDescriptionOnly(Format("value is %d", bOverTheAirInterval));
   AddDescriptionOnly("Number of 128 uSec intervals");
   AddDescriptionOnly("is calculated by");
   AddDescriptionOnly("2^^(bOverTheAirInterval-1)");

    AddFieldBreak();

   AddEntry( 9 , "bmCompAttributes", bmCompAttributes, 2, "Attributes of the endpoint companion descriptor", 0 );
   AddFieldBreak();
   
  Base += 10;
}



OutputUnknownData(bLength, start_offset)
{
    jj = start_offset;
    while( jj < bLength)
    {
        byte_value = GetDataByte(Base+jj);
        byte_str += Format ("%02X ",byte_value);
        if (((jj+1) == bLength) || ((jj%16) == 15))
        {
            AddLineOfText(byte_str);
            total_byte_str += byte_str;
            byte_str = "";
        }
        jj++;
    }

    return total_byte_str;
}



#TryVideoDescriptors(bDescriptorType) {}




%include "VideoDescriptors.inc"
%include "CommunicationDescriptors.inc"
%include "SmartCardDescriptors.inc"
%include "PersonalHealthcareDescriptors.inc"
%include "ContentSecurityDescriptors.inc"
%include "MassStorageDescriptors.inc"
%include "Usb3VisionDescriptors.inc"



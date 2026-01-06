#S******************************************************************************
#*
#*  FILENAME: StandardRequests.dec
#*
#*  Copyright (C) 2008 Elecomp Corporation
#*
#*  DESCRIPTION
#*    This is the request file for standard USB 3.0 device requests.
#*
#*  REVISION HISTORY
#*            File Created
#*    5/15/2014: SET_SEL decoding updated -TJ
#*    6/11/2014: bMaxBurst description updated -TJ
#*    2/4/2015: SUPERSPEEDPLUS_ISOCHRONOUS_ENDPOINT_COMPANION added. Needs testing. -TJ
#*
#*******************************************************************************

%include "PowerDelivery\\PDStandardRequests.inc"
%include "Ds5UvcDefines.inc"

############################################################
# USB 3.0      Table 9-6 Standard Feature Selectors        #
############################################################
set USB3DeviceFeatureSelectorTable =
[
    [0xFFFF, "UNDEFINED"           ],  #default value
    [0x0001, "DEVICE_REMOTE_WAKEUP"],
    [0x0002, "TEST_MODE"           ],
    [0x0030, "U1_ENABLE"           ],                                                                       
    [0x0031, "U2_ENABLE"           ], 
    [0x0032, "LTM_ENABLE"          ]  
];

###########################################################
# USB 3.0  Table 9-6 Standard Feature Selectors           #
###########################################################
set InterfaceFeatureSelectorTable =
[
    [0xFFFF, "UNDEFINED"       ],
    [0x0000, "FUNCTION_SUSPEND"]
];

############################################################
# USB 3.0  Figure 9-4 Returned by GetStatus() to a device  #
############################################################
set USB3DeviceStatusBitmapTable =
[
   [ 0, "Self Powered"    ],
   [ 1, "Remote Wakeup(Must Be Zero)"   ],
   [ 2, "U1 Enable"       ],
   [ 3, "U2 Enable"       ],
   [ 4, "LTM Enable"      ]
];

############################################################
# USB 3.0  Figure 9-5 Returned by GetStatus() to a device  #
############################################################
set InterfaceStatusBitmapTable =
[
   [ 0, "Function Remote Wake Capable"  ],
   [ 1, "Function Remote Wakeup"        ]
];

############################################################
# USB 3.0  Table 9-8 Suspend Options                       #
############################################################
set SuspendOptionBitmapTable =
[
   [ 0, "Operation State (0: Normal, 1: Low power suspend)" ],
   [ 1, "Function Remote Wakeup Enablity(0 : Disable,1 : Enable)"]
];
################################################################
# USB 3.0  Table 9-5 Descriptor Type                           #
# WUSB 1.0 Table 7-25 WUSB Standard Extension Descriptor Type  #
################################################################

set DescriptorTypeTableForUSB3 =
[
   [ 0xFF, "Illegal" ],
   [ 0x01, "DEVICE type" ],
   [ 0x02, "CONFIG type" ],
   [ 0x03, "STRING type" ],
   [ 0x04, "INTERFACE type (ERROR! Should only be part of GetDescriptor(Config))" ],
   [ 0x05, "ENDPOINT type (ERROR! Should only be part of GetDescriptor(Config))" ],
   [ 0x06, "Reserved" ],
   [ 0x07, "Reserved" ],
   [ 0x08, "INTERFACE_POWER type (ERROR! Should only be part of GetDescriptor(Config))" ],
   [ 0x09, "OTG type (ERROR! Should only be part of GetDescriptor(Config))" ],
   [ 0x0A, "Debug" ], 
   [ 0x0B, "INTERFACE_ASSOCIATION type (ERROR! Should only be part of GetDescriptor(Config))" ],
   [ 0x0C, "SECURITY"       ],
   [ 0x0D, "KEY"            ],
   [ 0x0E, "ENCRYPTION type"],
   [ 0x0F, "BOS"            ],
   [ 0x10, "DEVICE CAPABILITY"],
   [ 0x11, "WIRELESS_ENDPOINT_COMPANION"],
   [ 0x30, "SUPERSPEED_USB_ENDPOINT_COMPANION"],
   [ 0x31, "SUPERSPEEDPLUS_ISOCHRONOUS_ENDPOINT_COMPANION"]
  # [ 0x22, "HID type" ],
  # [ 0x23, "RADIO CONTROL type"]
];
############################################################
# USB 3.0  Figure 9-14 Device capablity Speed Support  #
############################################################
set USB3DeviceCapabilitySpeedSupportBitmapTable =
[
   [ 0, "Low Speed Supprot"    ],
   [ 1, "Full Speed Supprot"   ],
   [ 2, "High Speed Supprot"   ],
   [ 3, "5Gb/s Speed Supprot"  ]
];


##########################################################################
#  USB 3.0 Table 9-7 Test Mode Selectors                                 #
##########################################################################
GetUSB3TestModeSelectorTooltip(value)
{
   if (value >= 0x00 && value <= 0x05)
        return "Reserved";
   else if (value == 0x06)
        return "COMPLIANCE_MODE";
    else if (value == 0x07)
        return "LOOPBACK_MODE";
    else if (value >= 0x08 && value <= 0x3E )
        return "Reserved for standard test selectors";
    else if (value >= 0x3F && value <= 0xBF)
        return "Reserved";
    else if (value >= 0xC0 && value <= 0xFF)
        return "Reserved for vendor-specific test modes";
    else
        return "Invalid";
}


#***********************************************************************************
#  GET_LINK_ERROR_COUNT :
#
# bRequestType      :0x80
# bRequest          :0x32
# wValue            :Zero
# wIndex            :Zero
# wLength           :Two
# Data              :Number of Link Errors
#***********************************************************************************
GET_LINK_ERR_COUNT()
{
    out.Decoded = 8;
    if (bReqType == 0x80)
    {
        AddWValueCell("", "Should set to 0");
        AddWIndexCell("", "Should set to 0");        
        AddWLengthCell("Length of the payload, should set to 2");

        if (in.DataLength >= 10)
        {
            value  = GetDataWord(8);
            FieldColor = wDataColor;            
            AddPayLoadCell("Number of Link Errors", Format ("%d" , value), Format ("Number of link errors = 0x%02X" , value));
            out.Decoded += 2;
        }
        else
            AddErrorMonoCell("Error", "Not enough data", "Not enough data to decode current request");
    }
    else
    {
        AddIllegalTypeCell( "GET LINK ERR COUNT" );
    }
}

#*******************************************************************************
# GET_STATUS (for an interface): This request returns the status for the specified interface
# bReqType                     : 0x81 
# bRequest                     : 0x00
# wValue                       : 0x0000
# wIndex                       : Interface
# wLength                      : 2
# Data                         : Interface Status
#*******************************************************************************
DecodeGetStatusForInterface()
{
         if (wValue != 0)
            AddWValueCell("", FormatEx(_err_Illegal_Value,"wValue",wValue,0 ) ,1 );  
         else
            AddWValueCell("", "Correct Value of 0",0 ); 

         AddWIndexCell("" , "Interface index" );

        
         if (wLength != 2)
            AddWLengthCell( FormatEx(_err_Illegal_Value,"wLength",wLength,2 ) ,1 );  
         else
            AddWLengthCell( "Correct Value of 2",0 );           
 
 
     out.Decoded = 8;
     if (in.DataLength - 8 >=2)
     {
           value = GetDataWord(8);
           FieldColor = wDataColor;           
           FormatValue= Format("Interface # %d Status", wIndex);
           
           toolTip = ToBitDecode( InterfaceStatusBitmapTable, value, "" );
           AddPayLoadCell(FormatValue, Format("0x%04X",value), toolTip);
               
           out.Decoded += 2;
      }
       
      if (out.Decoded < 10)
          AddErrorMonoCell("Error", "Not enough data", "Not enough data to decode current request");        
}

#*******************************************************************************
# CLEAR_FEATURE : This request is used to clear or disable a specific feature
# bReqType : 0x00/01/02
# bRequest      : 0x01
# wValue        : Feature Selector
# wIndex        : Zero/Interface/Endpoint
# wLength       : 0x00
# Data          : None
#*******************************************************************************
DoClearFeatureForUSB3()
{
     if (bReqType == 0x00)
        DecodeClearFeatureForUSB3Device();
    else if (bReqType == 0x01)
        DecodeClearFeatureForInterface();
    else if (bReqType == 0x02)
        DecodeClearFeatureForEndpoint();
    else
    {
        AddIllegalTypeCell( "SET FEATURE" );
    }
    out.Decoded = 8;   
}
DecodeClearFeatureForUSB3Device()
{

        row = Find(USB3DeviceFeatureSelectorTable, wValue);
        AddWValueCell(row[1], FormatEx("wValue = 0x%04X\n\n",wValue) + row[1]);

        
        if (wIndex != 0)
            AddWIndexCell("", FormatEx(_err_Illegal_Value,"wIndex",wIndex,0 ) ,1 );  
         else
            AddWIndexCell("", "Correct Value of 0",0 ); 
        
        
         if (wLength != 0)
            AddWLengthCell( FormatEx(_err_Illegal_Value,"wLength",wLength,0 ) ,1 );  
         else
            AddWLengthCell( "Correct Value of 0",0 );   
        
 }
DecodeClearFeatureForInterface()
{
          FieldColor = ERROR_COLOR;
        FormatValue=Format("Clear Interface # %d Feature", wIndex);
        AddGenWValueCell( FormatValue, Format ("0x%04X", wValue) , "Error: Interface CLEAR_FEATURE not defined!");
        
        if (wLength != 0)
            AddWLengthCell( FormatEx(_err_Illegal_Value,"wLength",wLength,2 ) ,1 );  
        else
            AddWLengthCell( "Correct Value of 0",0 );   
}

DecodeClearFeatureForEndpoint()
{
        FieldColor = wDataColor;
        if (wIndex & 0x80)
        {
            FormatValue=Format("Clear Endpoint # %d IN Feature", wIndex & 0xF);
        }
        else
        {
            FormatValue=Format("Clear Endpoint # %d OUT Feature", wIndex & 0x0F );
        }
        if (wValue == 0)
        {
            AddGenWValueCell( "wValue" , "ENDPOINT_HALT" , "value = 0");
			endpointString = Find(CameraEndpointsMap, wIndex);
			AddPayLoadCell(" EndPoint ", endpointString[1], "Endpoint to clear halt");
        }
        else
        {
            FieldColor = ERROR_COLOR;
            AddGenWValueCell( "wValue", Format ("Undefined: 0x&04X", wValue) , "Error.  Only legal value is 0." );
        }
		
#        if (wLength != 0)
#            AddWLengthCell( FormatEx(_err_Illegal_Value,"wLength",wLength,2 ) ,1 );  
#        else
#            AddWLengthCell( "Correct Value of 0",0 );  
}
#*******************************************************************************
# SET_FEATURE   : This request is used to set or enable a specific feature
# bReqType      : 0x00/0x01/0x02
# bRequest      : 0x03
# wValue        : Feature Selector / Suspend Option
# wIndex        : Zero/Interface/Endpoint
# wLength       : 0x00
# Data          : None
#*******************************************************************************
DoSetFeatureForUSB3()
{
	if (bReqType == 0x00)
        DecodeSetFeatureForUSB3Device();
    else if (bReqType == 0x01)
        DecodeSetFeatureForInterface();
    else if (bReqType == 0x02)
        DecodeSetFeatureForEndpoint();
    else
    {
        AddIllegalTypeCell( "SET FEATURE" );
    }
    out.Decoded = 8;    
}


DecodeSetFeatureForUSB3Device()
{
    ##############################################
    #               Device                       #
    ##############################################
        row = Find(USB3DeviceFeatureSelectorTable, wValue);
        AddWValueCell(row[1], FormatEx("wValue = 0x%04X\n\n",wValue) + row[1]);
    
    if (row[1] == "TEST_MODE" )
    {
        TestModeSelector = GetDataByte(4);        
        TestModeText = GetUSB3TestModeSelectorTooltip(TestModeSelector);
        FieldColor = wDataColor;
        SetFieldOffsetLen( 40, 8 );
        AddPayLoadCell("Test Mode", TestModeText, Format("Test Mode Selector: 0x%02X", TestModeSelector));
        if (wLength != 0)
            AddWLengthCell( FormatEx(_err_Illegal_Value,"wLength",wLength,2 ) ,1 );  
         else
            AddWLengthCell( "Correct Value of 0",0 );         
    }
    else
    {
        if (wIndex != 0)
            AddWIndexCell("", FormatEx(_err_Illegal_Value,"wIndex",wIndex,0 ) ,1 );  
         else
            AddWIndexCell("", "Correct Value of 0",0 ); 
        
        
         if (wLength != 0)
            AddWLengthCell( FormatEx(_err_Illegal_Value,"wLength",wLength,2 ) ,1 );  
         else
            AddWLengthCell( "Correct Value of 0",0 );   

    }      
}

DecodeSetFeatureForInterface()
{
    ##############################################
    #               Interface                    #
    ##############################################
        row = Find(InterfaceFeatureSelectorTable, wValue);
        AddWValueCell(row[1], FormatEx("wValue = 0x%04X\n\n",wValue) + row[1]);
    
    if (row[1] == "FUNCTION_SUSPEND" )
    {        
        value = GetDataByte(4);      # get the wIndex lower byte  
        toolTip = "First Interface that is part of the Function Suspend" ;        
        FieldColor = wDataColor;
        SetFieldOffsetLen( 40, 8 );
		
		if (Ds5SkuType == 0)	# PSR/ASR/AWG
		{
			interfaceNameString = Find(CurrentInterfacesMapPSR, value);  # will determine interface name
		}
		else if ((Ds5SkuType == 5) || (Ds5SkuType == 6))	# S585 D585
		{
			interfaceNameString = Find(CurrentInterfacesMapS585, value);  # will determine interface name
		}
		else
		{
			interfaceNameString = Find(CurrentInterfacesMapAWGT, value);  # will determine interface name
		}
        #AddPayLoadCell("Interface", Format("0x%02X",value), toolTip);
		AddPayLoadCell("Interface", interfaceNameString[1], toolTip);
 
		AddSeparator(); 

		FieldColor = 0x5000;
        value = GetDataByte(5);      # get the wIndex upper byte  
		
		if (value & 0x01)
		{
			operationStateString = "Low Power Suspend";
		}
		else
		{
			operationStateString = "Normal Mode";
		}
		AddPayLoadCell("Operation State", operationStateString, Format("operation state: wIndex high byte, bit[0] = %d", value & 0x01));

		if (value & 0x02)
		{
			wakeUpString = "Enabled";
		}
		else
		{
			wakeUpString = "Disabled";
		}
		AddPayLoadCell("Remote Wakeup", wakeUpString, Format("Remote Wakeup: wIndex high byte, bit[1] = %d", value & 0x02));
		
        #toolTip = ToBitDecode( SuspendOptionBitmapTable, value, "" );        
        #FieldColor = wDataColor;
        #SetFieldOffsetLen( 48, 8 );
        #AddPayLoadCell("Suspend Option", Format("0x%02X",value), toolTip);
              
#        if (wLength != 0)
#            AddWLengthCell( FormatEx(_err_Illegal_Value,"wLength",wLength,2 ) ,1 );  
#        else
#            AddWLengthCell( "Correct Value of 0",0 );       
    }    
}

DecodeSetFeatureForEndpoint()
{
      ##############################################
    #              Endpoint                      #
    ##############################################
	
    if (wIndex & 0x80)
    {
        FormatValue=Format("Set Endpoint # %d IN Feature", wIndex & 0xF);
    }
    else
    {
        FormatValue=Format("Set Endpoint # %d OUT Feature", wIndex & 0x0F );
    }
    if (wValue == 0)
    {
        AddGenWValueCell(FormatValue, "ENDPOINT_HALT" , "ENDPOINT_HALT, value = 0");
		endpointString = Find(CameraEndpointsMap, wIndex);
		AddPayLoadCell(" EndPoint ", endpointString[1], "Endpoint to set halt");

    }
    else
    {
        FieldColor = ERROR_COLOR;
        AddGenWValueCell(FormatValue, Format ("Undefined: 0x%04X", wValue) , "Error.  Only legal value is 0!" );
    }
	 
#    if (wLength != 0)
#       AddWLengthCell( FormatEx(_err_Illegal_Value,"wLength",wLength,0 ) ,1 );  
#    else
#       AddWLengthCell( "Correct Value of 0",0 );   
}

#***********************************************************************************
#  SET_ISOCH_DELAY :
#
# bRequestType      :0x00
# bRequest          :0x31
# wValue            :Delay in ns
# wIndex            :Zero
# wLength           :Zero
# Data              :None
#***********************************************************************************
SET_ISOCH_DELAY()
{
    out.Decoded = 8;
    if (bReqType == 0x00)
    {
        AddWValueCell(Format("Delay in ns: 0x%04X", wValue), Format("Delay in ns: 0x%04X", wValue));
        AddWIndexCell("", "Should set to 0");
        AddWLengthCell("Should set to 0");      
    }
    else
    {
        AddIllegalTypeCell( "SET ISOCH DELAY" );
    }
}

#***********************************************************************************
#  SET_SEL :
#
# bRequestType      :0x00
# bRequest          :0x30
# wValue            :Zero
# wIndex            :Zero
# wLength           :Six
# Data              :Exit Latency Values
#***********************************************************************************
SET_SEL()
{
    out.Decoded = 14;
    if (bReqType == 0x00)
    {
        AddWValueCell( wValue, Format( "wValue = 0x%04X", wValue ) );
     #   AddWIndexCell("", "Should set to 0");
     #   AddWLengthCell("Should set to 6");      
        if (wIndex != 0)
           AddWIndexCell("", FormatEx(_err_Illegal_Value,"wIndex",wIndex,0 ) ,1 );  
        else
           AddWIndexCell("", "Correct Value of 0",0 ); 
           
        if (wLength != 6)
           AddWLengthCell( FormatEx(_err_Illegal_Value,"wLength",wLength,6 ) ,1 );  
        else
           AddWLengthCell( "Correct Value of 6",0 );
        
        Global_BitField_offset = 64;
        CurrentFldInit();
        curr_offset = 8;
        
        U1SEL = GetDataByte(curr_offset);
        U1PEL = GetDataByte(curr_offset + 1);
        U2SEL = GetDataWord(curr_offset + 2);
        U2PEL = GetDataWord(curr_offset + 4);
        
        AddDataHeader( FormatEx( "Exit Latency Values  (%d bytes)", wLength ) );     
        FieldColor = wDataColor;        
        
        SetFieldOffsetLen( 8, 8 );
        AddBlockPLCell( "U1SEL", U1SEL, Format( "0x%02X", U1SEL ) + ", Time in us for U1 System Exit Latency" );
        SetFieldOffsetLen( 16, 8 );
        AddBlockPLCell( "U1PEL", U1PEL, Format( "0x%02X", U1PEL ) + ", Time in us for U1 Device to Host Exit Latency" );
        SetFieldOffsetLen( 32, 16 );
        AddBlockPLCell( "U2SEL", U2SEL, Format( "0x%04X", U2SEL ) + ", Time in us for U2 System Exit Latency" );
        SetFieldOffsetLen( 48, 16 );
        AddBlockPLCell( "U2PEL", U2PEL, Format( "0x%04X", U2PEL ) + ", Time in us for U2 Device to Host Exit Latency" );
        
    }
    else
    {
        AddIllegalTypeCell( "SET ISOCH DELAY" );
    }
}

#========================================================================================#
#                      USB 3.0 Descriptor Decoding                                       #
#========================================================================================#

#*************************************************************************
#  bcdUSB field in DEVICE and DEVICE_QUALIFIER Descriptors  
#*************************************************************************
DecodeDevicebcdUSBForUSB3(bcdUSB, bDescriptorType)
{
      if (bDescriptorType == 0x06 ) #DEVICE_QUALIFIER
      {
          if (gDeviceCompliantSpec == USB3_Spec)
          {
             if (tempSpeedFlag == Super_Speed_Mode && bcdUSB != 0x210)
                 AddDescriptionOnly( "is invalid! (Only 0x210 is valid when operating in SuperSpeed mode)" );
             else if ((tempSpeedFlag == High_Speed_Mode) && (bcdUSB != 0x300) && (bcdUSB != 0x310))
                 AddDescriptionOnly( "is invalid! (Only 0x300 or 0x310 is valid when operating in High-Speed mode)" );
          }
          else if (gDeviceCompliantSpec == UNKNOWN_VALUE)
          {
             AddDescriptionOnly( "<br>&nbsp&nbsp(If the device is a USB3.0/3.1 compliant device,");
             AddDescriptionOnly("0x300 or 0x310 is the only valid value when it is operating in High-Speed mode" );
             AddDescriptionOnly("and 0x210 when operating in SuperSpeed mode)" );
          }
      }
}

#*************************************************************************
#  MaxPacketSize field in DEVICE and DEVICE_QUALIFIER Descriptors
#*************************************************************************
DecodeDeviceMaxPacketSizeForUSB3(bMaxPacketSize0, bDescriptorType)
{     
      if ((gDeviceCompliantSpec == USB3_Spec) ||(tempSpeedFlag == Super_Speed_Mode))
      {

        if (bDescriptorType == 0x01 ) #DEVICE
          {
            AddEntry( 7, "bMaxPacketSize0", bMaxPacketSize0, 2,Format( "Maximum packet size for enpoint zero is 2 ^ %d",bMaxPacketSize0) , 0);
              if (tempSpeedFlag == Super_Speed_Mode)
              {
                  if (bMaxPacketSize0 == 0x09)
                      AddDescriptionOnly( Format ("for endpoint zero is %d(512 byte for SuperSpeed mode) ", bMaxPacketSize0));
                  else
                  {
                      AddDescriptionOnly( Format ("<br>&nbsp&nbsp&nbsp %d for endpoint zero is invalid!", bMaxPacketSize0));
                      AddDescriptionOnly( "(Only 0x09 is valid when operating in SuperSpeed mode)" );
                  }
              }
              else
              {
                  if (bMaxPacketSize0 == 0x40)
                     AddDescriptionOnly( Format ("for endpoint zero is %d", bMaxPacketSize0));
                  else
                  {
                     AddDescriptionOnly( Format ("<br>&nbsp&nbsp&nbsp %d for endpoint zero is invalid!", bMaxPacketSize0));
                     AddDescriptionOnly( "(Only 64 is valid when operating in High-Speed mode)" );
                  }         
              }
          }
          else if (bDescriptorType == 0x06 ) #DEVICE_QUALIFIER
          {
                AddEntry( 7, "bMaxPacketSize0", bMaxPacketSize0, 2, "Maximum packet size" , 0);
              if (tempSpeedFlag == Super_Speed_Mode)
              {
                  if (bMaxPacketSize0 == 0x09)
                      AddDescriptionOnly( Format ("<br>&nbsp&nbsp&nbsp for endpoint zero is %d", bMaxPacketSize0));
                  else
                  {
                      AddDescriptionOnly( Format ("<br>&nbsp&nbsp&nbsp %d for endpoint zero is invalid!", bMaxPacketSize0));
                      AddDescriptionOnly( "(Only 0x09 is valid when operating in SuperSpeed mode)" );
                  }
              }
              else
              {
                  if (bMaxPacketSize0 == 0x40)
                      AddDescriptionOnly( Format ("for endpoint zero is %d", bMaxPacketSize0));
                  else
                  {
                      AddDescriptionOnly( Format ("%d for endpoint zero is invalid!", bMaxPacketSize0));
                      AddDescriptionOnly( "(Only 0x40 is valid when operating in High-Speed mode)" );
                  }         
              }
          }
      }
      else if (gDeviceCompliantSpec == UNKNOWN_VALUE)
      {
          AddEntry( 7, "bMaxPacketSize0", bMaxPacketSize0, 2, "Maximum packet size" , 0);
          AddDescriptionOnly("<br>&nbsp&nbsp(If the device is a USB3.0 compliant device,");
          AddDescriptionOnly("0x09 is the only valid value when operating in SuperSpeed mode");
          AddDescriptionOnly("and 0x40 when operating in High-Speed mode)");
      }
}

#***********************************************************************************
#  MaxPower field in CONFIGURATION and OTHER_SPEED_CONFIGURATION Descriptors
#***********************************************************************************
DecodeMaxPowerForUSB3(MaxPower, bDescriptorType)
{
      if (gDeviceCompliantSpec == USB3_Spec)
      {
        if (bDescriptorType == 0x02) #CONFIGURATION
        {
            if (tempSpeedFlag == Super_Speed_Mode)
                AddDescriptionOnly(Format ("configuration is %d mA", MaxPower*8));
            else if (tempSpeedFlag == High_Speed_Mode)
                AddDescriptionOnly(Format ("configuration is %d mA", MaxPower*2));
        }
        else #bDescriptorType == OTHER_SPEED_CONFIGURATION, 0x07
        {
            if (tempSpeedFlag == Super_Speed_Mode)
                AddDescriptionOnly(Format ("configuration is %d mA", MaxPower*2));
            else if (tempSpeedFlag == High_Speed_Mode)
                AddDescriptionOnly(Format ("configuration is %d mA", MaxPower*8));
        }
    }
    else if (gDeviceCompliantSpec == UNKNOWN_VALUE)
      {
          AddDescriptionOnly(Format ("configuration is %d mA", MaxPower));
          AddDescriptionOnly("expressed in 2-mA units when the device is operating in High-Speed mode");
          AddDescriptionOnly("and in 8-mA units when operating in SuperSpeed mode");
      }
}

############################################################################################
#  USB3.0 Table 9-13 SuperSpeed USB Device Capability Descriptor (inside BOS descriptor)   #
############################################################################################
DecodeSuperSpeedUSBDeviceCapability(bDevCapabiltyType)
{     
     #  SuperSpeed USB type
   base = Base;
    AddEntry( 2, "bDevCapabiltyType", bDevCapabiltyType, 2, "SUPERSPEED_USB", 0);
    AddFieldBreak();
##############
    bmAttributes = GetDataByte(base+3);
    if (bmAttributes & 0x2)
       ltm = "Yes";
    else
       ltm = "No";
        
    AddEntry( 3, "bmAttributes", bmAttributes, 2, "Attributes:<br>", 0);
    AddDescriptionOnly(Format ("&nbsp&nbspLatency Tolerance Messages : %s", ltm));
        
    if (bmAttributes & 0xFD)
       AddDescriptionOnly("<br>-- Error: Reserved bits not 0 --");
    AddFieldBreak();
   ###############    
    wSpeedsSupported = GetDataWord(base+4);
    if (wSpeedsSupported & 0x1)
          speed = "Yes";
    else      
        speed = "No";
       
    AddEntry( 4, "wSpeedsSupported", wSpeedsSupported, 4, "Supported Speeds:<br>" , 0);    
    #tbl = ToBitDecode( USB3DeviceCapabilitySpeedSupportBitmapTable, wSpeedsSupported,"");
    supportSpeeds = "";
    if (wSpeedsSupported & 0x0001)
        supportSpeeds += " |Low Speed|";
    if (wSpeedsSupported & 0x0002)
        supportSpeeds += " |Full Speed|";
    if (wSpeedsSupported & 0x0004)
        supportSpeeds += " |High Speed|";
    if (wSpeedsSupported & 0x0008)
        supportSpeeds += " |5 Gbs|";                
    
    AddDescriptionOnly(supportSpeeds );
    if (wSpeedsSupported & 0xFFF0)
        AddDescriptionOnly("<br>-- Error: Reserved bits not 0 --");
    AddFieldBreak();
  ###############   
   bFunctionalitySupport= GetDataByte(base+6);
    
    AddEntry( 6, "bFunctionalitySupport", bFunctionalitySupport, 2, "The lowest suppoted speed with full functionality", 0);
    AddDescriptionOnly(bFunctionalitySupport);        
    AddFieldBreak();
     ###############        

    bU1DevExitLat = GetDataByte(base+7);
    bU1DevExitLatStr = GetU1DeviceExitLatencyMeaning(bU1DevExitLat);
    AddEntry( 7, "bU1DevExitLat", bU1DevExitLat, 2, "U1 Device Exit Latency:", 0);
    AddDescriptionOnly(bU1DevExitLatStr);        
    AddFieldBreak();
     ###############        
    wU2DevExitLat = GetDataWord(base+8);
    wU2DevExitLatStr = GetU2DeviceExitLatencyMeaning(wU2DevExitLat);
    AddEntry( 8, "wU2DevExitLat", wU2DevExitLat, 4, "U2 Device Exit Latency:", 0);
    AddDescriptionOnly(wU2DevExitLatStr);        
    AddFieldBreak();
}

############################################################################################
#  USB3.0 Table 9-14 Container ID Device Capability Descriptor (inside BOS descriptor)   #
############################################################################################
DecodeContainerIdDeviceCapability(bDevCapabiltyType, bLength)
{
    base = Base;
    AddEntry( 2, "bDevCapabiltyType", bDevCapabiltyType, 2, "CONTAINER_ID", 0);
    AddFieldBreak();

    ###############       
    bReserved = GetDataByte(base+3);        
    AddEntry( 3, "bReserved", bReserved, 2, "Reserved", 0);
    AddFieldBreak();
    
    ###############   
    if(bLength == 20)
    {
      IDGuid = Get16BytesValue(base+4);        
      AddEntry( 4, "UUID", IDGuid, 32, "Number unique to a device instance that is used to uniquely identify", 0);        
      AddDescriptionOnly(" the device instance across all modes of operation");        
      AddFieldBreak();
    }  
    else
    {
        AddEntry( 4, "UUID", 0, 0, "Wrong UUID length, ", 0); 
        AddDescriptionOnly(" UUID must be 128 bits long.");        
        AddFieldBreak();
    }
}

############################################################################################
#  USB3.0 Table 9-18 Platform Descriptor (inside BOS descriptor)                           #
############################################################################################
DecodePlatformDeviceCapability(bDevCapabiltyType, bLength)
{
    base = Base;
    AddEntry( 2, "bDevCapabiltyType", bDevCapabiltyType, 2, "PLATFORM", 0);
    AddFieldBreak();

    ############### 
    
    bReserved = GetDataByte(base+3);        
    AddEntry( 3, "bReserved", bReserved, 2, "Reserved", 0);
    AddFieldBreak();
    
    ###############
    
    if(bLength >= 20)
    {
      IDGuid = Get16BytesValue(base+4);        
      AddEntry( 4, "UUID", IDGuid, 32, "128-bit number that uniquely identifies a platform specific capability of the device", 0);               
      AddFieldBreak();
    }  
    else
    {
        AddEntry( 4, "UUID", 0, 0, "Wrong UUID length, ", 0); 
        AddDescriptionOnly(" UUID must be 128 bits long.");        
        AddFieldBreak();
    }
    
    ###############
    
    if(bLength >= 20)
    {
        CapabilityDataLenght = bLength - 20;
        CapabilityData = GetDataByteArray(base+20, CapabilityDataLenght);
        nibbles_count = (CapabilityDataLenght * 2);
        
        AddEntry( 20, "CapabilityData", CapabilityData, nibbles_count, "variable-length field containing data associated with the platform specific capability", 0);
        AddFieldBreak();
    }
}

########################################################################
#  USB3.0 Table 9-19 SuperSpeedPlus Descriptor (inside BOS descriptor) #
########################################################################
DecodeUSBSSPDeviceCapability(bDevCapabiltyType, bLength)
{   
    base = Base;
    AddEntry( 2, "bDevCapabiltyType", bDevCapabiltyType, 2, "SUPERSPEED_PLUS", 0);
    AddFieldBreak();

    ############### 
    
    bReserved = GetDataByte(base+3);        
    AddEntry( 3, "bReserved", bReserved, 2, "Reserved", 0);
    AddFieldBreak();
    
    ###############
    ForceFullDescriptions();
    
    bmAttributes = GetDataLong(base+4);        
    AddEntry( 4, "bmAttributes", bmAttributes, 8, "Bitmap encoding of supported SuperSpeedPlus features:<br>", 0);
    AddDescriptionOnly("&nbsp&nbspBit&nbsp&nbsp&nbsp&nbspValue" + CreateHTMLSpace(12) + "Description<br>");
    
    SSAC = (bmAttributes & 0x0000001F); #bit_0_4
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "4:0" + CreateHTMLSpace(4) + "%02d" + CreateHTMLSpace(17) + "Sublink Speed Attribute Count (SSAC)<br>", SSAC));
    
    bit_5_8 = ((bmAttributes >> 5) & 0x0000000F);
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "8:5" + CreateHTMLSpace(4) + "%02d" + CreateHTMLSpace(17) + "Sublink Speed ID Count (SSIC)<br>", bit_5_8));
    
    bit_9_31 = ((bmAttributes >> 9) & 0x007FFFFF);
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "31:9" + CreateHTMLSpace(2) + "0x%08X" + CreateHTMLSpace(4) + "Reserved", bit_9_31));
    
    AddFieldBreak();
    
    ###############
    
    wFunctionalitySupport = GetDataWord(base+8);        
    AddEntry( 8, "wFunctionalitySupport", wFunctionalitySupport, 4, "The device shall support full functionality at all reported<br>", 0);
    AddDescriptionOnly(CreateHTMLSpace(2) + "bandwidths at or above the minimum bandwidth described via this field<br>");
    AddDescriptionOnly(CreateHTMLSpace(2) + "Bit" + CreateHTMLSpace(4) + "Value" + CreateHTMLSpace(12) + "Description<br>");
    
    bit_0_3 = (wFunctionalitySupport & 0x0000000F);
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "3:0" + CreateHTMLSpace(6) + "%02d" + CreateHTMLSpace(17) + "Sublink Speed Attribute ID (SSID)<br>", bit_0_3));
    
    bit_4_7 = ((wFunctionalitySupport >> 4) & 0x0000000F);
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "7:4" + CreateHTMLSpace(6) +  "%02d" + CreateHTMLSpace(17) + "Reserved. Shall be set to zero<br>", bit_4_7));
    
    bit_8_11 = ((wFunctionalitySupport >> 8) & 0x0000000F);
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "11:8" + CreateHTMLSpace(4) + "%02d" + CreateHTMLSpace(17) + "Min Rx Lane Count<br>", bit_8_11));
    
    bit_12_15 = ((wFunctionalitySupport >> 12) & 0x0000000F);
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "15:12" + CreateHTMLSpace(2) +"%02d" + CreateHTMLSpace(17) + "Min Tx Lane Count", bit_12_15));
    
    AddFieldBreak();
    
    ###############
    
    wReserved = GetDataWord(base+9);        
    AddEntry( 9, "wReserved", wReserved, 4, "Reserved. Shall be set to zero.", 0);
    AddFieldBreak();
    
    ###############
    
    for(ssa_index = 0 ; ssa_index < SSAC+1 ; ssa_index += 1)
    {
        ssa_offset = 12 + (ssa_index * 4);
        
        bmSublinkSpeedAttr_n = GetDataLong(base + ssa_offset);        
        AddEntry( ssa_offset, Format("bmSublinkSpeedAttr[%d]", ssa_index), bmSublinkSpeedAttr_n, 8, "Bitmap encoding of a Sublink characteristics:<br>", 0);
        
        AddDescriptionOnly("&nbsp&nbspBit&nbsp&nbsp&nbsp&nbspValue" + CreateHTMLSpace(12) + "Description<br>");
        
        bit_0_3 = (bmSublinkSpeedAttr_n & 0x0000000F);
        AddDescriptionOnly(Format(CreateHTMLSpace(2) + "3:0" + CreateHTMLSpace(4) + "%02d" + CreateHTMLSpace(17) + "Sublink Speed Attribute ID (SSID)<br>", bit_0_3));
        
        bit_4_5 = ((bmSublinkSpeedAttr_n >> 4) & 0x00000003);
        AddDescriptionOnly(Format(CreateHTMLSpace(2) + "5:4" + CreateHTMLSpace(4) + "%02d" + CreateHTMLSpace(17) + "Lane Speed Exponent (LSE)<br>", bit_4_5));
        
        bit_6   = ((bmSublinkSpeedAttr_n >> 6) & 0x00000001);
        if(bit_6)
            desc = "Asymmetric";
        else
            desc = "Symmetric";
        AddDescriptionOnly(Format(CreateHTMLSpace(2) + "6" + CreateHTMLSpace(8) + "%d" + CreateHTMLSpace(17) + "Sublink Type: " + desc + "<br>", bit_6));
        
        bit_7   = ((bmSublinkSpeedAttr_n >> 7) & 0x00000001);
        if(bit_7)
            desc = "Sublink operates in Transmit mode";
        else
            desc = "Sublink operates in Receive mode";
        AddDescriptionOnly(Format(CreateHTMLSpace(2) + "7" + CreateHTMLSpace(8) + "%d" + CreateHTMLSpace(17) + "Sublink Type: " + desc + "<br>", bit_7));
        
        bit_8_13 = ((bmSublinkSpeedAttr_n >> 8) & 0x0000003F);
        AddDescriptionOnly(Format(CreateHTMLSpace(2) + "13:8" + CreateHTMLSpace(4) + "0x%X" + CreateHTMLSpace(13) + "Reserved<br>", bit_8_13));
        
        bit_14_15 = ((bmSublinkSpeedAttr_n >> 14) & 0x00000003);
        if(bit_14_15 == 0)
            desc = "SuperSpeed";
        else if(bit_14_15 == 1)
            desc = "SuperSpeedPlus";
        else
            desc = "Reserved";
        AddDescriptionOnly(Format(CreateHTMLSpace(2) + "15:14" + CreateHTMLSpace(3) + "%d" + CreateHTMLSpace(16) + "Link Protocol: " + desc + "<br>", bit_14_15));
        
        bit_16_31 = ((bmSublinkSpeedAttr_n >> 16) & 0x0000FFFF);
        AddDescriptionOnly(Format(CreateHTMLSpace(2) + "31:16" + CreateHTMLSpace(3) + "0x%04X" + CreateHTMLSpace(6) + "Lane Speed Mantissa (LSM)<br>", bit_16_31));
        
        AddFieldBreak();
    }
    
    DontForceFullDescriptions();
    
    ###############
}

################################################################################################
#  USBPD_R2_0 V1.0 Table 9-2 USB Power Delivery Capability Descriptor  (inside BOS descriptor) #
################################################################################################
DecodePDDeviceCapability(bDevCapabiltyType, bLength)
{
    base = Base;
    AddEntry( 2, "bDevCapabiltyType", bDevCapabiltyType, 2, "POWER_DELIVERY_CAPABILITY", 0);
    AddFieldBreak();

    ############### 
    
    bReserved = GetDataByte(base+3);        
    AddEntry( 3, "bReserved", bReserved, 2, "Shall be set to zero", 0);
    AddFieldBreak();
    
    ###############
    ForceFullDescriptions();
    
    bmAttributes = GetDataLong(base+4);
    AddEntry( 4, "bmAttributes", bmAttributes, 8, "Bitmap encoding of supported device level features:<br>", 0);
    AddDescriptionOnly("&nbsp&nbspBit&nbsp&nbsp&nbsp&nbspValue&nbsp&nbsp&nbspDescription<br>");
    
    bit_0 = (bmAttributes & 0x00000001);
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "0" + CreateHTMLSpace(7) + "%d" + CreateHTMLSpace(9) + "Reserved. Shall be set to zero<br>", bit_0));
    
    bit_1 = ((bmAttributes >> 1) & 0x00000001);
    if(bit_1)
        desc = "Device supports Battery Charging";
    else
        desc = "Battery Charging not supported";
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "1" + CreateHTMLSpace(7) + "%d" + CreateHTMLSpace(9) + desc + "<br>", bit_1));
    
    bit_2 = ((bmAttributes >> 2) & 0x00000001);
    if(bit_2)
        desc = "Device supports the USB Power Delivery";
    else
        desc = "USB Power Delivery not supported";
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "2" + CreateHTMLSpace(7) + "%d" + CreateHTMLSpace(9) + desc + "<br>", bit_2));
    
    bit_3 = ((bmAttributes >> 3) & 0x00000001);
    if(bit_3)
        desc = "Device is Provider(capable of providing power)";
    else
        desc = "Device is not Provider";
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "3" + CreateHTMLSpace(7) + "%d" + CreateHTMLSpace(9) + desc + "<br>", bit_3));
    
    bit_4 = ((bmAttributes >> 4) & 0x00000001);
    if(bit_4)
        desc = "Device is Consumer(consumer of power)";
    else
        desc = "Device is not Consumer";
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "4" + CreateHTMLSpace(7) + "%d" + CreateHTMLSpace(9) + desc + "<br>", bit_4));
    
    bit_5 = ((bmAttributes >> 5) & 0x00000001);
    if(bit_5)
        desc = "Device supports the feature CHARGING_POLICY";
    else
        desc = "CHARGING_POLICY feature not supported";
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "5" + CreateHTMLSpace(7) + "%d" + CreateHTMLSpace(9) + desc + "<br>", bit_5));
    
    bit_6 = ((bmAttributes >> 6) & 0x00000001);
    if(bit_6)
        desc = "Device supports USB Type-C Current";
    else
        desc = "USB Type-C Current not supported";
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "6" + CreateHTMLSpace(7) + "%d" + CreateHTMLSpace(9) + desc + "<br>", bit_6));
    
    bit_7 = ((bmAttributes >> 7) & 0x00000001);
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "7" + CreateHTMLSpace(7) + "%d" + CreateHTMLSpace(9) + "Reserved. Shall be set to zero<br>", bit_7));
    

    #*******************15:8  bmPowerSource    
    AddDescriptionOnly("<br>" + CreateHTMLSpace(2) + "15:8" + CreateHTMLSpace(9) + "&nbsp&nbsp&nbsp&nbsp" + "bmPowerSource(Supported power sources):<br>");
    
    bit_8  = ((bmAttributes >> 8) & 0x00000001);
    if(bit_8)
        desc = "Device supports AC Supply power source";
    else
        desc = "AC Supply power source not supported";
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "8" + CreateHTMLSpace(7) + "%d" + CreateHTMLSpace(9) + desc + "<br>", bit_8));
    
    bit_9  = ((bmAttributes >> 9) & 0x00000001);
    if(bit_9)
        desc = "Device supports Battery power source";
    else
        desc = "Battery power source not supported";
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "9" + CreateHTMLSpace(7) + "%d" + CreateHTMLSpace(9) + desc + "<br>", bit_9));
    
    bit_10  = ((bmAttributes >> 10) & 0x00000001);
    if(bit_10)
        desc = "Device supports Other power source";
    else
        desc = "Other power source not supported";
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "10" + CreateHTMLSpace(5) + "%d" + CreateHTMLSpace(9) + desc + "<br>", bit_10));
    
    bit_11_13  = ((bmAttributes >> 11) & 0x00000007);
    desc = Format("&nbsp&nbsp&nbspNumBatteries(%d)", bit_11_13);
    AddDescriptionOnly(CreateHTMLSpace(2) + "13:11" + CreateHTMLSpace(9) + desc + "<br>");
    
    bit_14  = ((bmAttributes >> 14) & 0x00000001);
    if(bit_14)
        desc = "Device Uses VBUS as power source";
    else
        desc = "VBUS not used as power source";
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "14" + CreateHTMLSpace(5) + "%d" + CreateHTMLSpace(9) + desc + "<br>", bit_14));
    
    bit_15 = ((bmAttributes >> 15) & 0x00000001);
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "15" + CreateHTMLSpace(5) + "%d" + CreateHTMLSpace(9) + "Reserved. Shall be set to zero<br><br>", bit_15));
    #*******************
    
    bit_16_31  = ((bmAttributes >> 16) & 0x0000FFFF);
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "31:16" + CreateHTMLSpace(2) + "%04X" + CreateHTMLSpace(2) + "Reserved. Shall be set to zero<br>", bit_16_31));
    
    AddFieldBreak();
    ###############
    
    bmProviderPorts  = GetDataWord(base+8);
    AddEntry( 8, "bmProviderPorts", bmProviderPorts, 4, "Bit zero refers to the UFP of the device.<br>", 0);
    AddDescriptionOnly(CreateHTMLSpace(2) + "Bits one through fifteen are only valid for hubs and refers to the downstream ports of the hub:<br>");
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "0x%04X" + "<br>", bmProviderPorts));
    
    AddFieldBreak();
    ###############
    
    bmConsumerPorts  = GetDataWord(base+10);
    AddEntry( 10, "bmConsumerPorts", bmConsumerPorts, 4, "Bit zero refers to the UFP of the device.<br>", 0);
    AddDescriptionOnly(CreateHTMLSpace(2) + "Bits one through fifteen are only valid for hubs and refers to the downstream ports of the hub:<br>");
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "0x%04X" + "<br>", bmConsumerPorts));
    
    AddFieldBreak();
    ###############
    
    bcdBCVersion  = GetDataWord(base+12);
    AddEntry( 12, "bcdBCVersion", bcdBCVersion, 4, "Battery Charging Specification Release Number:", 0);
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "0x%04X" + "<br>", bcdBCVersion));
    
    AddFieldBreak();
    ###############
    
    bcdPDVersion  = GetDataWord(base+14);
    AddEntry( 14, "bcdPDVersion", bcdPDVersion, 4, "USB Power Delivery Specification Release Number:", 0);
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "0x%04X" + "<br>", bcdPDVersion));
    
    AddFieldBreak();
    ###############
    
    bcdUSBTypeCVersion  = GetDataWord(base+16);
    AddEntry( 16, "bcdUSBTypeCVersion", bcdUSBTypeCVersion, 4, "USB Type-C Specification Release Number:", 0);
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "0x%04X" + "<br>", bcdUSBTypeCVersion));
    
    AddFieldBreak();
    
    DontForceFullDescriptions();
    ###############
}

##########################################################################################
#  USBPD_R2_0 V1.0 Table 9-3 Battery Info Capability Descriptor  (inside BOS descriptor) #
##########################################################################################
DecodePDBatteryInfoDeviceCapability(bDevCapabiltyType, bLength)
{
    base = Base;
    AddEntry( 2, "bDevCapabiltyType", bDevCapabiltyType, 2, "BATTERY_INFO_CAPABILITY", 0);
    AddFieldBreak();

    ############### 
    
    iBattery = GetDataByte(base+3);        
    AddEntry( 3, "iBattery", iBattery, 2, "Index of string descriptor contain the user friendly name:", 0);
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "%d", iBattery));
    AddFieldBreak();
    
    ###############
    
    iSerial = GetDataByte(base+4);        
    AddEntry( 4, "iSerial", iSerial, 2, "Index of string descriptor contain the Serial Number String:", 0);
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "%d", iSerial));
    AddFieldBreak();
    
    ###############
    
    iManufacturer = GetDataByte(base+5);        
    AddEntry( 5, "iManufacturer", iManufacturer, 2, "Index of string descriptor contain the name of the Manufacturer:", 0);
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "%d", iManufacturer));
    AddFieldBreak();
    
    ###############
    
    bBatteryId  = GetDataByte(base+6);        
    AddEntry( 6, "bBatteryId ", bBatteryId , 2, "Value shall be used to uniquely identify this battery in status messages:", 0);
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "%d", bBatteryId ));
    AddFieldBreak();
    
    ###############
    
    bReserved  = GetDataByte(base+7);        
    AddEntry( 7, "bReserved ", bReserved , 2, "Reserved and shall be set to zero", 0);
    AddFieldBreak();
    
    ###############
    
    dwChargedThreshold  = GetDataLong(base+8);        
    AddEntry( 8, "dwChargedThreshold ", dwChargedThreshold , 8, "Battery Charge value above which this battery is considered to be fully charged:", 0);
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "%u(mWh)", dwChargedThreshold ));
    AddFieldBreak();
    
    ###############
    
    dwWeakThreshold  = GetDataLong(base+12);        
    AddEntry( 12, "dwWeakThreshold ", dwWeakThreshold , 8, "Minimum charge level of this battery such<br>&nbsp&nbspthat above this threshold, a device can be assured of being able to power up successfully:", 0);
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "%u(mWh)", dwWeakThreshold ));
    AddFieldBreak();
    
    ###############
    
    dwBatteryDesignCapacity  = GetDataLong(base+16);        
    AddEntry( 16, "dwBatteryDesignCapacity ", dwBatteryDesignCapacity , 8, "Contain the design capacity of the battery:", 0);
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "%u(mWh)", dwBatteryDesignCapacity ));
    AddFieldBreak();
    
    ###############
    
    dwBatteryLastFullchargeCapacity  = GetDataLong(base+20);        
    AddEntry( 20, "dwBatteryLastFullchargeCapacity ", dwBatteryLastFullchargeCapacity , 8, "Contain the maximum capacity of the battery when fully charged:", 0);
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "%u(mWh)", dwBatteryLastFullchargeCapacity ));
    AddFieldBreak();
    
    ###############
}

##########################################################################################
#  USBPD_R2_0 V1.0 Table 9-4  PD Consumer Port Descriptor        (inside BOS descriptor) #
##########################################################################################
DecodePDConsumerPortDeviceCapability(bDevCapabiltyType, bLength)
{
    base = Base;
    AddEntry( 2, "bDevCapabiltyType", bDevCapabiltyType, 2, "PD_CONSUMER_PORT_CAPABILITY", 0);
    AddFieldBreak();

    ############### 
    
    bReserved  = GetDataByte(base+3);        
    AddEntry( 3, "bReserved ", bReserved , 2, "Reserved and shall be set to zero", 0);
    AddFieldBreak();
    
    ###############
    ForceFullDescriptions();
    
    bmCapabilities = GetDataWord(base+4);        
    AddEntry( 4, "bmCapabilities", bmCapabilities, 4, "Capability: indicate the specification the Consumer Port will operate under:<br>", 0);
    AddDescriptionOnly("&nbsp&nbspBit&nbsp&nbsp&nbsp&nbspValue&nbsp&nbsp&nbspDescription<br>");
    
    
    bit_0 = (bmCapabilities & 0x00000001);
    if(bit_0)
        desc = "Battery Charging supported";
    else
        desc = "Battery Charging not supported";
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "0" + CreateHTMLSpace(7) + "%d" + CreateHTMLSpace(9) + desc + "<br>", bit_0));
    
    bit_1 = ((bmCapabilities >> 1) & 0x00000001);
    if(bit_1)
        desc = "USB Power Delivery supported";
    else
        desc = "USB Power Delivery not supported";
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "1" + CreateHTMLSpace(7) + "%d" + CreateHTMLSpace(9) + desc + "<br>", bit_1));
    
    bit_2 = ((bmCapabilities >> 2) & 0x00000001);
    if(bit_2)
        desc = "USB Type-C Current supported";
    else
        desc = "USB Type-C Current not supported";
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "2" + CreateHTMLSpace(7) + "%d" + CreateHTMLSpace(9) + desc + "<br>", bit_2));
    
    bit_3_15 = ((bmCapabilities >> 3) & 0x00001FFF);
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "15:3" + CreateHTMLSpace(2) + "0x%X" + CreateHTMLSpace(6) + desc, bit_3_15));
    
    AddFieldBreak();
    
    ###############
    
    wMinVoltage  = GetDataWord(base+6);        
    AddEntry( 6, "wMinVoltage ", wMinVoltage , 4, "Minimum voltage in 50mV units that this Consumer is capable of operating at:", 0);
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "%u :" + CreateHTMLSpace(2), wMinVoltage ));
    AddDescriptionOnly(Format("%u(mV)", wMinVoltage * 50 ));
    AddFieldBreak();
    
    ###############
    
    wMaxVoltage  = GetDataWord(base+8);        
    AddEntry( 8, "wMaxVoltage ", wMaxVoltage , 4, "Maximum voltage in 50mV units that this Consumer is capable of operating at:", 0);
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "%u :" + CreateHTMLSpace(2), wMaxVoltage ));
    AddDescriptionOnly(Format("%u(mV)", wMaxVoltage * 50 ));
    AddFieldBreak();
    
    ###############
    
    wReserved  = GetDataWord(base+10);        
    AddEntry( 10, "wReserved ", wReserved , 4, "Reserved and shall be set to zero", 0);
    AddFieldBreak();
    
    ###############
    
    dwMaxOperatingPower  = GetDataLong(base+12);        
    AddEntry( 12, "dwMaxOperatingPower ", dwMaxOperatingPower , 8, "Maximum power in 10mW units this Consumer can draw when it is in a steady state mode:", 0);
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "%u :" + CreateHTMLSpace(2), dwMaxOperatingPower ));
    AddDescriptionOnly(Format("%u(mW)", dwMaxOperatingPower * 10 ));
    AddFieldBreak();
    
    ###############
    
    dwMaxPeakPower  = GetDataLong(base+16);        
    AddEntry( 16, "dwMaxPeakPower ", dwMaxPeakPower , 8, "Maximum power in 10mW units this Consumer can draw for a short duration of time before it falls back into a steady state:", 0);
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "%u :" + CreateHTMLSpace(2), dwMaxPeakPower ));
    AddDescriptionOnly(Format("%u(mW)", dwMaxPeakPower * 10 ));
    AddFieldBreak();
    
    ###############
    
    dwMaxPeakPowerTime  = GetDataLong(base+20);        
    AddEntry( 20, "dwMaxPeakPowerTime ", dwMaxPeakPowerTime , 8, "Time in 100ms units that this Consumer can draw peak current:", 0);
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "%u :" + CreateHTMLSpace(2), dwMaxPeakPowerTime ));
    AddDescriptionOnly(Format("%u(ms)", dwMaxPeakPowerTime * 100 ));
    AddDescriptionOnly("<br>" + CreateHTMLSpace(2) + "A device shall set this field to 0xFFFF if this value is unknown.");
    AddFieldBreak();
    
    DontForceFullDescriptions();
    ###############
}

##########################################################################################
#  USBPD_R2_0 V1.0 Table 9-5  PD Provider Port Descriptor        (inside BOS descriptor) #
##########################################################################################
DecodePDProviderPortDeviceCapability(bDevCapabiltyType, bLength)
{
    base = Base;
    AddEntry( 2, "bDevCapabiltyType", bDevCapabiltyType, 2, "PD_PROVIDER_PORT_CAPABILITY", 0);
    AddFieldBreak();

    ############### 
    
    bReserved  = GetDataByte(base+3);        
    AddEntry( 3, "bReserved ", bReserved , 2, "Reserved and shall be set to zero", 0);
    AddFieldBreak();
    
    ###############
    ForceFullDescriptions();
    
    bmCapabilities = GetDataWord(base+4);        
    AddEntry( 4, "bmCapabilities", bmCapabilities, 4, "Capability: indicate the specification the Provider Port will operate under:<br>", 0);
    AddDescriptionOnly("&nbsp&nbspBit&nbsp&nbsp&nbsp&nbspValue&nbsp&nbsp&nbspDescription<br>");
    
    
    bit_0 = (bmCapabilities & 0x00000001);
    if(bit_0)
        desc = "Battery Charging supported";
    else
        desc = "Battery Charging not supported";
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "0" + CreateHTMLSpace(7) + "%d" + CreateHTMLSpace(9) + desc + "<br>", bit_0));
    
    bit_1 = ((bmCapabilities >> 1) & 0x00000001);
    if(bit_1)
        desc = "USB Power Delivery supported";
    else
        desc = "USB Power Delivery not supported";
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "1" + CreateHTMLSpace(7) + "%d" + CreateHTMLSpace(9) + desc + "<br>", bit_1));
    
    bit_2 = ((bmCapabilities >> 2) & 0x00000001);
    if(bit_2)
        desc = "USB Type-C Current supported";
    else
        desc = "USB Type-C Current not supported";
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "2" + CreateHTMLSpace(7) + "%d" + CreateHTMLSpace(9) + desc + "<br>", bit_2));
    
    bit_3_15 = ((bmCapabilities >> 3) & 0x00001FFF);
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "15:3" + CreateHTMLSpace(2) + "0x%X" + CreateHTMLSpace(6) + desc, bit_3_15));
    
    AddFieldBreak();
    
    ###############
    
    bNumOfPDObjects  = GetDataByte(base+6);
    AddEntry( 6, "bNumOfPDObjects ", bNumOfPDObjects , 2, "Number of Power Data Objects:", 0);
    AddDescriptionOnly(Format(CreateHTMLSpace(2) + "%u" + CreateHTMLSpace(2), bNumOfPDObjects ));
    AddFieldBreak();
    
    ###############
    
    bReserved  = GetDataByte(base+7);        
    AddEntry( 7, "bReserved ", bReserved , 2, "Reserved and shall be set to zero", 0);
    AddFieldBreak();
    
    ###############
    
    for(data_object_index = 0 ; data_object_index < bNumOfPDObjects ; data_object_index += 1)
    {
        data_object_offset = 8 + (data_object_index * 4);
        
        wPowerDataObject_n  = GetDataLong(base + data_object_offset);        
        AddEntry( data_object_offset, Format("wPowerDataObject%d ", data_object_index + 1), wPowerDataObject_n , 8, "Power Data Object supported by this Provider Port:", 0);
        AddDescriptionOnly(Format(CreateHTMLSpace(2) + "0x%08X" + CreateHTMLSpace(2), wPowerDataObject_n ));
        AddFieldBreak();
    }
    
    DontForceFullDescriptions();
    
    ###############
    
}

#***********************************************************************************
# USB3.0 Table 9-15 Meaning of the bU1DevExitLat field
#***********************************************************************************
GetU1DeviceExitLatencyMeaning(value)
{
      if (value == 0)
         return "Zero";
      else if (value <= 0xA)
         return Format("Less than %d microseconds", value);
      else if (value >= 0xB && value <= 0xFF)
         return "Reserved";   
}

#***********************************************************************************
# USB3.0 Table 9-15 Meaning of the bU2DevExitLat field
#***********************************************************************************
GetU2DeviceExitLatencyMeaning(value)
{
      if (value == 0)
         return "Zero";
      else if (value <= 0x07FF)
         return Format("Less than %d microseconds", value);
      else if (value >= 0x0800 && value <= 0xFFFF)
         return "Reserved";   
}

#***********************************************************************************
# USB3.0 Table 9-15 Meaning of the bHubHdrDecLat field
#***********************************************************************************
GetHubHeaderDecodeLatencyMeaning(value)
{
      if (value == 0)
         return "Much less than 0.1 microseconds";
      else if (value >= 0x1 && value <= 0x04)     
         return Format("0.%d microseconds", value);
      else 
         return "Reserved";
}

#******************************************************************************
# SUPERSPEED_USB_ENDPOINT_COMPANION Descriptor definitions
#******************************************************************************
SUPERSPEED_USB_ENDPOINT_COMPANION()
{
    temp_str = ("Illegal usage: GET_DESCRIPTOR  SUPERSPEED_USB_ENDPOINT_COMPANION type");
    temp_str = temp_str + NewLine();
    temp_str = temp_str + "Must be obtained through GET_DESCRIPTOR  CONFIG type";
}

SUPERSPEED_USB_ENDPOINT_COMPANION_sub()
{
    base = Base;

    bLength             = GetDataByte(base);
    bDescriptorType     = GetDataByte(base+1);
    bMaxBurst           = GetDataByte(base+2);
    bmAttributes        = GetDataByte(base+3);
    wBytesPerInterval   = GetDataWord(base+4);
    
    Base += bLength;
    
    AddEntry( 0, "bLength", bLength, 2, "", 1);
    AddDescriptorSizeString(bLength);
    AddFieldBreak();

    AddEntry( 1, "bDescriptorType", bDescriptorType, 2, GetDescriptorTypeString("SUPERSPEED_USB_ENDPOINT_COMPANION"), 0);
    AddFieldBreak();
    
    ##############
    if (MostRecentEndpointType != 0) 
     { 
      AddEntry( 2, "bMaxBurst", bMaxBurst, 2, Format ("The endpoint can send or receive maximum of %d packets as a part of burst", bMaxBurst+1) , 0);
      AddDescriptionOnly("Maximum packet of a burst");
     }
    else
       {
      AddEntry( 2, "bMaxBurst", bMaxBurst, 2,"<font Color = \"ORANGE\">"+ "For endpoints of type control this shall be set to 0 "+"</font>", 0);    
      AddDescriptionOnly( ".");
         }   
        if ((bMaxBurst < 0) || (bMaxBurst > 15))
    {
        AddDescriptionOnly("Error: Must be between");
        AddDescriptionOnly("0 and 15, inclusive");
    }
    AddFieldBreak();
    ########
    
    if (MostRecentEndpointType == 2) #Bulk
    {
      maxStreams = bmAttributes & 0x0F;
      AddEntry( 3, "bmAttributes", bmAttributes, 2, Format ("The endpoint supports the  maximum of 2^%d streams", maxStreams) , 0);
      if ( bmAttributes & 0xF0)
        AddDescriptionOnly( "<font COLOR=#FF0000>!!! WARNING !!! " + "Reserved bits shal be set to zero(Bits 5 : 7)" + "</font>");
      AddFieldBreak();
    }
    if ((MostRecentEndpointType == 3) || (MostRecentEndpointType == 0)) #Interupt or control 
    {
      AddEntry( 3, "bmAttributes", bmAttributes, 2, "Reserved if the endpoint is control or interupt" , 0);
      
      if (bmAttributes > 0)
        AddDescriptionOnly( "<font COLOR=#FF0000>!!! WARNING !!! " + "Reserved bits shal be set to zero" + "</font>");
      AddFieldBreak();
    }
    
    if (MostRecentEndpointType == 1) #Isochron
    {
      mult = bmAttributes & 0x03;
      AddEntry( 3, "bmAttributes", bmAttributes, 2, Format ("The endpoint supports the  maximum of %d burst within a service interval/n", mult) , 0);
      if ( mult > 2)
        AddDescriptionOnly( "<font COLOR=#FF0000>!!! WARNING !!! " + "Mult maximum value is 2 /n" + "</font>");

      if ( bmAttributes & 0xFC)
        AddDescriptionOnly( "<font COLOR=#FF0000>!!! WARNING !!! " + "Reserved bits shal be set to zero(Bits 2 : 7)" + "</font>");
      AddFieldBreak();
    }
    
    if (MostRecentEndpointType != 1)
      AddEntry( 4, "wBytesPerInterval", wBytesPerInterval, 4, Format ("Total Number of bytes this endpoint will transfer every service interval is : %d bytes/n", wBytesPerInterval) , 0);
    else
      AddEntry( 4, "wBytesPerInterval", wBytesPerInterval, 4, "Use to reserve the bus item in the schedule" , 0);
    AddFieldBreak();    

}
DecodeEndpointForUSB3()
{
    base = Base;
    bLength             = GetDataByte(base);
    bDescriptorType     = GetDataByte(base+1);
    bEndpointAddress    = GetDataByte(base+2);
    bmAttributes        = GetDataByte(base+3);
    wMaxPacketSize      = GetDataWord(base+4);
    bInterval           = GetDataByte(base+6);

    Base += bLength;

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
        AddDescriptionOnly("<br>&nbsp&nbsp&nbsp&nbspError: Reserved Shall be Set to Zero");
    }
  }
  else if ((bmAttributes & 0x3) == 1)
  {
      trans = "ISOCHRONOUS";
      MostRecentEndpointType = 1;
      if ((bmAttributes & 0xC) == 0)
          sync = "No Synchronization";
      else if ((bmAttributes & 0xC) == 0x4)
          sync = "Asynchronous";
      else if ((bmAttributes & 0xC) == 8)
          sync = "Adaptive";
      else
          sync = "Synchronous";


      if ((bmAttributes & 0x30) == 0)
          usage = "Data endpoint ";
      else if ((bmAttributes & 0x30) == 0x10)
          usage = "Feedback endpoint";
      else if ((bmAttributes & 0x30) == 0x20)
          usage = "Implicit Feedback Data endpoint";
      else
          usage = "Reserved";

      AddDescriptionOnly(Format ("<br>&nbsp&nbsp&nbsp&nbspTransfer  :%s", trans));
      AddDescriptionOnly(Format ("<br>&nbsp&nbsp&nbsp&nbspSync Type :%s", sync));
      AddDescriptionOnly(Format ("<br>&nbsp&nbsp&nbsp&nbspUsage Type:%s", usage));
      if (bmAttributes & 0xC0)
      {
          AddDescriptionOnly("<br>&nbsp&nbsp&nbsp&nbspError: Reserved Shall be Set to Zero");
      }
  }
  else if ((bmAttributes & 0x3) == 2) 
  {
      trans = "BULK";
      MostRecentEndpointType = 2;

#      if (bmAttributes & 0x80)
#          adjust = "Yes";
#      else
#          adjust = "No";


     #AddDescriptionOnly(Format ("<br>&nbsp&nbsp&nbsp&nbspPkt Size Adjust: %s", adjust));
      AddDescriptionOnly(Format ("<br>&nbsp&nbsp&nbsp&nbspTransfer : %s", trans));
      if (bmAttributes & 0xFC)
       {
        AddDescriptionOnly(Format( "<br>&nbsp&nbsp&nbsp&nbspError: Reserved Shall be Set to Zero(0x%04X)",bmAttributes & 0xFC));
       }
  }
  else
  {
      trans = "INTERRUPT";
      MostRecentEndpointType = 3;

      if ((bmAttributes & 0x30) == 0)
          usage = "Periodic";
      else if ((bmAttributes & 0x30) == 0x10)
          usage = "Notification ";
      else if ((bmAttributes & 0x30) == 0x20)
          usage = "Reserved";
      else
          usage = "Reserved";

      AddDescriptionOnly(Format ("<br>&nbsp&nbsp&nbsp&nbspTransfer  :%s", trans));
        if ((bmAttributes & 0xC) != 0)
         {
            AddDescriptionOnly(Format( "<br>&nbsp&nbsp&nbsp&nbspError: Reserved Shall be Set to Zero(0x%04X)",bmAttributes & 0xC));
         }
        AddDescriptionOnly(Format ("<br>&nbsp&nbsp&nbsp&nbspUsage Type:%s", usage));
  }
    AddFieldBreak();

    AddEntry( 4, "wMaxPacketSize", wMaxPacketSize, 4, "Maximum packet size for" , 0);
    AddDescriptionOnly( Format ("this endpoint is %d Bytes.", wMaxPacketSize));
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
    
}






/*
SUPERSPEED_USB_ENDPOINT_COMPANION_sub()
{
    
    
    base = Base;
    bmEndpointType       = GetDataByte(base - 4);
    base = Base;
    bDescriptorType      = GetDataByte(base+1);
    bMaxBurst            = GetDataByte(base+2);
    bmAttributes         = GetDataByte(base+3);
    
    
    AddEntry( 0, "bLength", bLength, 2, "", 1);
    AddDescriptorSizeString(bLength);
    AddFieldBreak();

    AddEntry( 1, "bDescriptorType", bDescriptorType, 2, GetDescriptorTypeString("SUPERSPEED_USB_ENDPOINT_COMPANION"), 0);
    AddFieldBreak();

    if (bmEndpointType != 0)     
      {
        AddEntry( 2, "bMaxBurst", bMaxBurst, 2,"Maximum number of packets in a burst for ", 0);    
        AddDescriptionOnly( Format ("this endpoint is %d.", bMaxBurst+1));
          }
        else
          {
        AddEntry( 2, "bMaxBurst", bMaxBurst, 2,"<font Color = \"ORANGE\">"+ "For endpoints of type control this shall be set to 0 "+"</font>", 0);    
        AddDescriptionOnly( ".");
          }   
        
        if ((bMaxBurst < 0) || (bMaxBurst > 15))
    {
        AddDescriptionOnly("Error: Must be between");
        AddDescriptionOnly("0 and 15, inclusive");
    }
    AddFieldBreak();

    AddEntry( 3, "bmAttributes", bmAttributes, 2, "Attributes:", 0); 
    if (MostRecentEndpointType == 1) #Isochronous Endpoint
    {
          Mult = bmAttributes & 0x03;
                AddDescriptionOnly( Format ("<br>&nbsp&nbsp&nbsp&nbspMult: %d", Mult));
                
                if (bmAttributes & 0xFC)
        {
            AddDescriptionOnly("<br>&nbsp&nbsp&nbsp&nbspError: Reserved not 0!");
        }
    }   
    else if (MostRecentEndpointType == 2) #Bulk Endpoint
    {
         MaxTasks = (bmAttributes & 0x7C) >> 2;
         AddDescriptionOnly("<br>&nbsp&nbsp&nbsp&nbspMaxTasks: ");
         if (MaxTasks == 0)
             AddDescriptionOnly("no tasks is defined for this Endpoint");
         else
            AddDescriptionOnly( Format ("2 raised to the power of %d", MaxTasks));
             
         if (MaxTasks < 0 || MaxTasks > 16)
         {
               AddDescriptionOnly( "&nbsp&nbsp&nbspError:  Must be between");
               AddDescriptionOnly( "0 and 16, inclusive");
         }
         
         if (bmAttributes & 0x83)
       {
          AddDescriptionOnly("<br>&nbsp&nbsp&nbsp&nbspError: Reserved not 0!");
       }
    }
    else
    {
          AddDescriptionOnly("None");
          if (bmAttributes != 0)
              AddDescriptionOnly( "&nbsp&nbsp&nbspError:  Must be zero!");
    }
    AddFieldBreak();    
}
*/


#******************************************************************************
# SUPERSPEEDPLUS_ISOCHRONOUS_ENDPOINT_COMPANION Descriptor definitions
#******************************************************************************
SUPERSPEEDPLUS_ISOCHRONOUS_ENDPOINT_COMPANION_sub()
{
    base = Base;

    bLength             = GetDataByte(base);
    bDescriptorType     = GetDataByte(base+1);
    wReserved           = GetDataWord(base+3);
    dwBytesPerInterval  = GetDataLong(base+4);
    
    Base += bLength;
    
    AddEntry( 0, "bLength", bLength, 2, "", 1);
    AddDescriptorSizeString(bLength);
    AddFieldBreak();

    AddEntry( 1, "bDescriptorType", bDescriptorType, 2, GetDescriptorTypeString("SUPERSPEEDPLUS_ISOCHRONOUS_ENDPOINT_COMPANION"), 0);
    AddFieldBreak();
	
	AddEntry( 2, "wReserved", wReserved, 4, GetDescriptorTypeString("Reserved. Shall be set to zero."), 0);
    AddFieldBreak();
	
	AddEntry( 3, "dwBytesPerInterval", dwBytesPerInterval, 8, GetDescriptorTypeString("The total number of bytes this endpoint will transfer every service interval (SI)."), 0);
    AddFieldBreak();
    
}

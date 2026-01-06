#******************************************************************************
#
#  FILENAME: SmartCardDescriptors.inc
#
#  Copyright (C) 2006 LeCroy Corporation
#
#  DESCRIPTION
#    This descriptor definition file is supplied by LeCroy.
#    This file defines standard USB Smart Card descriptors.
#    File version is 1.0.
#       Based on CCID Revision 1.1 & ICCD Revision 1.0 (both released April 22nd, 2005)
#
#******************************************************************************

set SmartCardDescriptorTypeTable =        #Table for Smart Card Class specific Descriptor Type
[
    [ 0xFF, "UNKNOWN" ],
    [ 0x21, "SmartCard_CS_DEVICE"]        #CS = Class Specific
];

TrySmartCardDescriptors(bDescriptorType)  #If (Smart Card Class specific descriptor) decode; else return 0
{
  CurrentByteOffset = 0;                                            #Global variable from UsbCommon.inc
  SC_row = Find (SmartCardDescriptorTypeTable, bDescriptorType);    #Find specific descriptor
  #AddShortDataHeader(FormatEx ("%s Descriptor  (%X type)", _row[1], bDescriptorType ));    
  if (SC_row[0] == 0xFF) 
    return 0;
    
  Call (SC_row[1]);
  return 1;   
}

SmartCard_CS_DEVICE()
{
  CCID_descrip = "";
  ICCD_descrip = "";
  dataLength = bLength;                   #Length of Data from encapsulating call: bLength is defined in StandardDescriptors.inc 
                                          #via other .inc files; this file is included in StandardDescriptors.inc
                                          
  AddShortDataHeader(FormatEx ("%s Descriptor (%d bytes)", "SMART CARD CLASS SPECIFIC DEVICE", dataLength ));
  if (dataLength > in.DataLength - Base ) #Checking there is enough data
  {
    AddStringToDlg("Not enough data for this descriptor",FormatEx("Length required %d bytes, Actual Length %d bytes", dataLength, in.DataLength - Base), OutputUnknownData(in.DataLength - Base, 0));
    return 0;
  }
#BEGIN Decode of bLength    
  bLength_val = GetDataByte( Base + CurrentByteOffset );
  bLength_descrip = "Size of this descriptor, in bytes. 54 bytes long.";
  if(bLength_val != 0x36)
  {
    bLength_descrip = Format("<font COLOR=#FF0000>!!! WARNING !!! Size of this descriptor, is %d bytes. Should be 54 bytes long.</font>",bLength_val);
  }
  AddEntry(CurrentByteOffset, "bLength", bLength_val, 2, bLength_descrip , 0,1);
  AddFieldBreak();
  IncCurrByteOffset( 1 );
#END Decode of bLength  
      
  if (CurrentByteOffset + 1 > dataLength)  #Another data check
    return 1;
  AddByteEntry("bDescriptorType", GetDescriptorTypeString("Class Specific DEVICE"));

  if (CurrentByteOffset + 2 > dataLength)  #Another data check
    return 1;
  AddWordEntry("bcdCCID","Integrated Circuit(s) Cards Interface Devices (CCID) Specification Release Number in Binary-Coded decimal (i.e., 2.10 is 0210h).");
  
  if (CurrentByteOffset + 1 > dataLength)  #Another data check
    return 1;
  AddByteEntry("bMaxSlotIndex","<b>CCID:</b> The index of the highest available slot on this device. All slots are consecutive starting at 00h. i.e. 0Fh = 16 slots on this device numbered 00h to 0Fh. <br>&nbsp&nbsp<b>ICCD:</b> Index of the highest available slot. A USB-ICC is regarded as a single slot CCID.");
  
  if (CurrentByteOffset + 1 > dataLength)  #Another data check
    return 1;
#BEGIN Decode of bVoltageSupport    
  bVoltageSupport_val = GetDataByte( Base + CurrentByteOffset );
  if(bVoltageSupport_val == 0x01)
    CCID_descrip = "<b>CCID:</b> 5.0V <br>&nbsp&nbsp<b>ICCD:</b> 5.0V";
  else if (bVoltageSupport_val != 0)
  {
    CCID_descrip = "<b>CCID:</b> ";
    if(bVoltageSupport_val&0x04)
      CCID_descrip += "1.8V, ";
    if(bVoltageSupport_val&0x02)
      CCID_descrip += "3.0V, ";
    if(bVoltageSupport_val&0x01)
      CCID_descrip += "5.0V";
    CCID_descrip += "<br>&nbsp&nbsp<b>ICCD:</b> Should be 5.0V, not relevant, but fixed to 01h for legacy reason.";
  }
  else
    CCID_descrip = "<b>CCID:</b> !WARNING, NO Supported Voltages Indicated...! <br>&nbsp&nbsp<b>ICCD:</b> Should be 5.0V, not relevant, but fixed to 01h for legacy reason.";
    
  AddEntry(CurrentByteOffset,"bVoltageSupport",bVoltageSupport_val,2,CCID_descrip,0,0);
  AddFieldBreak();
  IncCurrByteOffset(1);
#END Decode of bVoltageSupport
  
  if (CurrentByteOffset + 4 > dataLength)  #Another data check
    return 1;
#BEGIN Decode of dwProtocol  
  dwProtocols_val = GetDataLong ( Base + CurrentByteOffset );
  
  tempx = (dwProtocols_val&0xFFFF0000);
  if(tempx != 0)
    CCID_descrip = "<b>CCID:</b> RRRR -Upper Word- is Reserved for Future Use!!! Must be zero.";
  else
    CCID_descrip = "<b>CCID:</b> RRRR -Upper Word- is Reserved for Future Use";
  
  tempx = (dwProtocols_val&0xFFFF);
  if(tempx == 1)
    CCID_descrip += "<br>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbspPPPP -Lower Word- Protocol T = 0";
  else if(tempx == 2)
    CCID_descrip += "<br>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbspPPPP -Lower Word- Protocol T = 1";
  else if(tempx == 3)
    CCID_descrip += "<br>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbspPPPP -Lower Word- Protocol T = 0 or 1";  
  else
    CCID_descrip += "<br>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbspPPPP -Lower Word- Protocol Unknown";
  
  if(dwProtocols_val == 0x00000001)
    ICCD_descrip = "<br>&nbsp&nbsp<b>ICCD:</b> Protocol T = 0 (Character-oriented asynchronous half duplex transmission protocol)";
  else if(dwProtocols_val == 0x00000002)
    ICCD_descrip = "<br>&nbsp&nbsp<b>ICCD:</b> Protocol T = 1 (Block-oriented asynchronous half duplex transmission protocol)";
  else
    ICCD_descrip = "<br>&nbsp&nbsp<b>ICCD:</b> Protocol Unknown (Can only support T = 0 [0x00000001] or T = 1 [0x00000002])";

  dwProtocols_descrip = CCID_descrip + ICCD_descrip;  
  AddEntry(CurrentByteOffset,"dwProtocols",dwProtocols_val,8,dwProtocols_descrip,0,0);
  AddFieldBreak();
  IncCurrByteOffset( 4 );  
#END Decode of dwProtocol

  if (CurrentByteOffset + 4 > dataLength)  #Another data check
    return 1;
#BEGIN Decode of dwDefaultClock  
  dwDefaultClock_val = GetDataLong ( Base + CurrentByteOffset );
  if(dwDefaultClock_val != 0x00000DFC)
    CCID_descrip = FormatEx("<b>CCID:</b> %uKHz <br>&nbsp&nbsp<b>ICCD:</b>  %uKHz --> Should be 3.58MHz, not relevant, just fixed for legacy reason.",dwDefaultClock_val,dwDefaultClock_val);
  else
    CCID_descrip = "<b>CCID:</b> 3.58MHz <br>&nbsp&nbsp<b>ICCD:</b> 3.58MHz";
    
  AddEntry(CurrentByteOffset,"dwDefaultClock",dwDefaultClock_val,8,CCID_descrip,0,1);
  AddFieldBreak();
  IncCurrByteOffset( 4 );
#END Decode of dwDefaultClock    
    
  if (CurrentByteOffset + 4 > dataLength)  #Another data check
    return 1;
#BEGIN Decode of dwMaximumClock  
  dwMaximumClock_val = GetDataLong ( Base + CurrentByteOffset );
  if(dwMaximumClock_val != 0x00000DFC)
    CCID_descrip = FormatEx("<b>CCID:</b> %uKHz <br>&nbsp&nbsp<b>ICCD:</b>  %uKHz --> Should be 3.58MHz, not relevant, just fixed for legacy reason.",dwMaximumClock_val,dwMaximumClock_val);
  else
    CCID_descrip = "<b>CCID:</b> 3.58MHz <br>&nbsp&nbsp<b>ICCD:</b> 3.58MHz";
    
  AddEntry(CurrentByteOffset,"dwMaximumClock",dwMaximumClock_val,8,CCID_descrip,0,1);
  AddFieldBreak();
  IncCurrByteOffset( 4 );    
#END Decode of dwMaximumClock  
  
  if (CurrentByteOffset + 1 > dataLength)  #Another data check
    return 1;
#BEGIN Decode of bNumClockSupported  
  bNumClockSupported_val = GetDataByte( Base + CurrentByteOffset );
  if(bNumClockSupported_val != 0x00)
     CCID_descrip = Format("<b>CCID:</b> %u clock frequencies supported. <br>&nbsp&nbsp<b>ICCD:</b> Should only be the Default Clock (dwDefaultClock), not relevant, fixed for legacy reason.",bNumClockSupported_val);
  else
  {
    tempx = (dwMaximumClock_val - dwDefaultClock_val + 1);
    if(tempx ==1)
      CCID_descrip = Format("<b>CCID:</b> One clock frequency supported (Default Clock). <br>&nbsp&nbsp<b>ICCD:</b> One clock frequency supported, the Default Clock.");
    else
      CCID_descrip = FormatEx("<b>CCID:</b> %u clock frequencies supported (dwMaximumClock - dwDefaultClock + 1) <br>&nbsp&nbsp<b>ICCD:</b> %u clock frequencies supported. Should only be the Default Clock, not relevant, fixed for legacy reason.",tempx,tempx);
  }
   
  AddEntry(CurrentByteOffset,"bNumClockSupported",bNumClockSupported_val,2,CCID_descrip,0,1);
  AddFieldBreak();
  IncCurrByteOffset(1);
#END Decode of bNumClockSupported

  if (CurrentByteOffset + 4 > dataLength)  #Another data check
    return 1;
#BEGIN Decode of dwDataRate
  dwDataRate_val = GetDataLong( Base + CurrentByteOffset );
  
  if(dwDataRate_val != 0x00002580)
    CCID_descrip = FormatEx("<b>CCID:</b> %ubps (Default Data Rate) <br>&nbsp&nbsp<b>ICCD:</b> %ubps --> Should be 9600bps, not relevant, fixed for legacy reason.",dwDataRate_val,dwDataRate_val);
  else
    CCID_descrip = "<b>CCID:</b> 9600bps (Default Data Rate) <br>&nbsp&nbsp<b>ICCD:</b> 9600bps";      
  AddEntry(CurrentByteOffset,"dwDataRate",dwDataRate_val,8,CCID_descrip,0,1);
  AddFieldBreak();
  IncCurrByteOffset(4);
#END Decode of dwDataRate

  if (CurrentByteOffset + 4 > dataLength)  #Another data check
    return 1;
#BEGIN Decode of dwMaxDataRate
  dwMaxDataRate_val = GetDataLong( Base + CurrentByteOffset );
  
  if(dwMaxDataRate_val != 0x00002580)
    CCID_descrip = FormatEx("<b>CCID:</b> %ubps (Default Data Rate) <br>&nbsp&nbsp<b>ICCD:</b> %ubps --> Should be 9600bps, not relevant, fixed for legacy reason.",dwMaxDataRate_val,dwMaxDataRate_val);
  else
    CCID_descrip = "<b>CCID:</b> 9600bps <br>&nbsp&nbsp<b>ICCD:</b> 9600bps";
  AddEntry(CurrentByteOffset,"dwMaxDataRate",dwMaxDataRate_val,8,CCID_descrip,0,1);
  AddFieldBreak();
  IncCurrByteOffset(4);
#END Decode of dwMaxDataRate
  
  if (CurrentByteOffset + 1 > dataLength)  #Another data check
    return 1;
#BEGIN Decode of   bNumDataRatesSupported
  bNumDataRatesSupported_val = GetDataByte( Base + CurrentByteOffset );
  
  if(bNumDataRatesSupported_val != 0x00)
    CCID_descrip = FormatEx("<b>CCID:</b> %u data rates supported. <br>&nbsp&nbsp<b>ICCD:</b> Should only be the Default Data Rate, not relevant, fixed for legacy reason.",bNumDataRatesSupported_val);
  else
  {
    tempx = (dwMaxDataRate_val - dwDataRate_val + 1);
    if(tempx != 1)
      CCID_descrip = FormatEx("<b>CCID:</b> %u data rates supported. (dwMaxDataRate - dwDataRate + 1)<br>&nbsp&nbsp<b>ICCD:</b> %u data rates supported. --> Should only be the default data rate, not relevant, fixed for legacy reason.",tempx,tempx);
    else
      CCID_descrip = "<b>CCID:</b> One data rate supported (Default Data Rate) <br>&nbsp&nbsp<b>ICCD:</b> One data rate, the Default Data Rate";
  }
  AddEntry(CurrentByteOffset,"bNumDataRatesSupported",bNumDataRatesSupported_val,2,CCID_descrip,0,1);
  AddFieldBreak();
  IncCurrByteOffset(1);
#END Decode of bNumDataRatesSupported
  
  if (CurrentByteOffset + 4 > dataLength)  #Another data check
    return 1;
    
  AddDwordEntry("dwMaxIFSD","<b>CCID:</b> Maximum IFSD supported by CCID for protocol T=1. <br>&nbsp&nbsp<b>ICCD:</b> Maximum IFSD supported by the USB-ICC for protocol T=1, the value should be 000000FEh. For T=0 any value may be given.");

  if (CurrentByteOffset + 4 > dataLength)  #Another data check
    return 1;
#BEGIN Decode of dwSynchProtocols
  dwSynchProtocols_val = GetDataLong(Base + CurrentByteOffset);

  tempx = (dwSynchProtocols_val&0xFFFF0000);
  if(tempx != 0)
    CCID_descrip = "<b>CCID:</b> RRRR -Upper Word- is Reserved for Future Use!!! Must be zero.";
  else
    CCID_descrip = "<b>CCID:</b> RRRR -Upper Word- is Reserved for Future Use";
  
  tempx = (dwSynchProtocols_val&0xFFFF);
  if(tempx == 1)
    CCID_descrip += "<br>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbspPPPP -Lower Word- Supports 2-wire Protocol";
  else if(tempx == 2)
    CCID_descrip += "<br>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbspPPPP -Lower Word- Supports 3-wire Protocol";
  else if(tempx == 4)
    CCID_descrip += "<br>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbspPPPP -Lower Word- Supports I2C Protocol";  
  else
    CCID_descrip += "<br>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbspPPPP -Lower Word- Protocol Unknown";

  if(dwSynchProtocols_val != 0)
    CCID_descrip +="<br>&nbsp&nbsp<b>ICCD:</b> Should be ISO7816-3, not relevant, fixed for legacy reason.";
  else
    CCID_descrip +="<br>&nbsp&nbsp<b>ICCD:</b> ISO7816-3";

  AddEntry(CurrentByteOffset,"dwSynchProtocols",dwSynchProtocols_val,8,CCID_descrip,0,0);
  AddFieldBreak();
  IncCurrByteOffset(4);
#END Decode of dwSynchProtocols
  
  if (CurrentByteOffset + 4 > dataLength)  #Another data check
    return 1;
#BEGIN Decode of dwMechanical  
  dwMechanical_val = GetDataLong( Base + CurrentByteOffset);
  
  CCID_descrip = "";
  tempx = 0;
  if (dwMechanical_val == 0)
    CCID_descrip = "<b>CCID:</b> No special characteristics <br>&nbsp&nbsp<b>ICCD:</b> No special characteristics";
  else if((dwMechanical_val&0xF)!=0)
  {
    CCID_descrip = "<b>CCID:</b> <u>Mechanisms Supported</u> - ";
    if((dwMechanical_val%2) == 1)
      CCID_descrip += Format("%d.) <i>Card accept</i> ",++tempx);
    if(dwMechanical_val&0x00000002)
      CCID_descrip += Format("%d.) <i>Card ejection</i> (not part of spec) ",++tempx);
    if(dwMechanical_val&0x00000004)
      CCID_descrip += Format("%d.) <i>Card capture</i> (not part of spec) ",++tempx);
    if(dwMechanical_val&0x00000008)
      CCID_descrip += Format("%d.) <i>Card lock/unlock</i> ",++tempx);
    CCID_descrip += "<br>&nbsp&nbsp<b>ICCD:</b> Should be 'No special characteristic', not relevant, fixed for legacy reason.";  }
  else
    CCID_descrip = "<b>CCID:</b> UNKNOWN <br>&nbsp&nbsp<b>ICCD:</b> UNKNOWN";
  AddEntry(CurrentByteOffset,"dwMechanical",dwMechanical_val,8,CCID_descrip,0,0);  
  AddFieldBreak();
  IncCurrByteOffset(4);
#END Decode of dwMechanical
  
  if (CurrentByteOffset + 4 > dataLength)  #Another data check
    return 1;
#BEGIN Decode of dwFeatures
  dwFeatures_val = GetDataLong ( Base + CurrentByteOffset);
  
  ICCD_descrip = "";
  CCID_descrip = "";
  tempx = 0;
  temp_descrip = "";
  temp2_descrip = "";
  
  LExchange = 0;
  upperflag = 0;
  lowerflag = 0;
  APDUflag  = 0;
  
  if (dwFeatures_val == 0)
    CCID_descrip = "<b>CCID:</b>USBWakeup(<i>OFF</i>) XLevel(<i>Character</i>) Features(<i>No special characteristics</i>) <br>&nbsp&nbsp<b>ICCD:</b> XLevel(<i>Character</i>) LowerWord(<i>UNKNOWN --> should be 0840h.</i>)";
  else
  {
    tempx2 = ((dwFeatures_val >> 16)&0xFFFF);
    if(tempx2 == 0)
    {
      CCID_descrip = "<b>CCID:</b> USBWakeup(<i>OFF</i>) XLevel(<i>Character</i>) ";
      ICCD_descrip = "<br>&nbsp&nbsp<b>ICCD:</b> XLevel(<i>Character</i>) ";  
    }
    else
    {
      if(tempx2&0x0001) #Checking if First bit in lower byte of upper word is SET
      {
        LExchange = 1;    #First bit in lower byte of upper word
        upperflag = 1;
      }
      if(tempx2&0x0002) #Checking if Second bit in lower byte of upper word is SET
      {
        if(!upperflag)
        {
          LExchange = 2;  #2nd bit in lower byte of upper word is only SET
          upperflag = 1;
        }
        else
          LExchange = 0;  #No Mutually Exlusive Bit set in lower byte of upper word
      }
      if(tempx2&0x0004) #Checking if Third bit in lower byte of upper word is SET
      {
        if(!upperflag)
        {
          LExchange = 3;  #Third bit in lower byte of upper word
          upperflag = 1;
        }
        else
          LExchange = 0;  #No Mutually Exlusive Bit set in lower byte of upper word
      }  
      if(tempx2&0x0008) #Checking if Fourth bit in lower byte of upper word is SET
        LExchange = 0;  #"Reserved/Unspecified" Bit set in lower byte of upper word    
      
      if(tempx2&0x0010)
        CCID_descrip = "<b>CCID:</b> USBWakeup(<i>ON</i>) ";
      else
        CCID_descrip = "<b>CCID:</b> USBWakeup(<i>OFF</i>) ";
      
      CCID_descrip += select{
        LExchange == 0 : "XLevel(<i>Character</i>) ";
        LExchange == 1 : "XLevel(<i>TPDU</i>) ";
        LExchange == 2 : "XLevel(<i>Short APDU</i>) ";
        LExchange == 3 : "XLevel(<i>Short and Extended APDU</i>) ";
      };
  
      if(!(tempx2>0x0F))  #Already checked lower nibble (bits 0-4) of upper word, checking for higher bits set
        ICCD_descrip = select{
          LExchange == 2 : "<br>&nbsp&nbsp<b>ICCD:</b> XLevel(<i>Short APDU</i>) ";
          LExchange == 3 : "<br>&nbsp&nbsp<b>ICCD:</b> XLevel(<i>Short and Extended APDU</i>) ";
          default        : "<br>&nbsp&nbsp<b>ICCD:</b> XLevel(<i>UNKNOWN</i>) ";
        };
      else
        ICCD_descrip = "<br>&nbsp&nbsp<b>ICCD:</b> XLevel(<i>UNKNOWN</i>) ";
    }
    
    tempx2 = (dwFeatures_val&0xFFFF);
    if((LExchange == 2)|(LExchange == 3))
      APDUflag = 1;
      
    if(tempx2 == 0x0840)
    {
      if(APDUflag)
        CCID_descrip += "Features(<i>AutoParamNegotiate</i> WARNING - AutoParamCfg Not Set for APDU) ";
      else
        CCID_descrip += "Features(<i>AutoParamNegotiate</i>) ";
      ICCD_descrip += "LowerWord(<i>0840h (valid USB-ICC requests from host)</i>)";
    }
    else
    {
      ICCD_descrip += "LowerWord(<i>UNKNOWN --> should be 0840h.</i>)";
      if(tempx2!= 0)
        CCID_descrip += "Features(<i>";
      else
        CCID_descrip += "Features(<i>No special characteristics";
        
      if(tempx2&0x0002)
        CCID_descrip += "AutoParamCfg, ";
      else if(APDUflag)
        CCID_descrip += " !WARNING - AutoParamCfg NOT SET for APDU! ";
        
      if(tempx2&0x0004)
        CCID_descrip += "AutoActivateICC, ";      
      
      if(tempx2&0x0008)
        CCID_descrip += "AutoICCVoltSel, ";
        
      if(tempx2&0x0010)
        CCID_descrip += "AutoICCClkFreq, ";
      
      if(tempx2&0x0020)
        CCID_descrip += "AutoBaudRate, ";
      
      if(tempx2&0x0040)
      {
        if(!(tempx2&0x0080))
          CCID_descrip += "AutoParamNegotiate, ";    
        else
          CCID_descrip += " !WARNING Both AutoParamNegotiate & AutoPPS Set (mutually exclusive)! ";
        
        lowerflag = 1;
      }
      
      if((tempx2&0x0080)&&(!lowerflag))
        CCID_descrip += "<i>AutoPPS</i>, ";
      else if(APDUflag&&(!lowerflag))
        CCID_descrip += " !WARNING - AutoParamNegotiate or AutoPPS Not Set for APDU! ";
      
      if(tempx2&0x0100)
        CCID_descrip += "CCIDSetICCClkStop, ";
      
      if(tempx2&0x0200)
        CCID_descrip += "NonZeroNADValue, ";
        
      if(tempx2&0x0400)
        CCID_descrip += "AutoIFSDExchng, ";
    }
    CCID_descrip += "</i>)" + ICCD_descrip;
  }    
      AddEntry(CurrentByteOffset,"dwFeatures",dwFeatures_val,8,CCID_descrip,0,0);
      AddFieldBreak();
      IncCurrByteOffset(4);
#END Decode of dwFeatures

  if (CurrentByteOffset + 4 > dataLength)  #Another data check
    return 1;
#BEGIN Decode of dwMaxCCIDMessageLength
#  dwMaxCCIDMessageLength_val = GetDataLong( Base + CurrentByteOffset );
  
  AddDwordEntry("dwMaxCCIDMessageLength","<b>CCID:</b> For Extended APDU Level - Value range [ 271 - 65554 ], otherwise Minimum Value should be wMaxPacketSize of the Bulk-OUT endpoint. <br>&nbsp&nbsp<b>ICCD:</b> Bulk Transfers: Value range [ 271 - 65554 ]; Control Transfers: Value range [ 261 - 65544 ]",0,1);
  
  if (CurrentByteOffset + 1 > dataLength)  #Another data check
    return 1;
#BEGIN Decode of bClassGetResponse
  bClassGetResponse_val = GetDataByte( Base + CurrentByteOffset);
  if(bClassGetResponse_val == 0xFF)
    CCID_descrip = "<b>CCID:</b> The CCID echoes the class of the APDU. <br>&nbsp&nbsp<b>ICCD:</b> Echoes the class of the APDU.";
  else
    CCID_descrip = "<b>CCID:</b> Significant only for CCID that offer an extended APDU exchange level. Indicates the default class value used by the CCID for a Get Response command with transportation using an APDU by T=0 protocol. <br>&nbsp&nbsp<b>ICCD:</b> WARNING - Value not FFh --> should echo APDU class.";    
  AddEntry(CurrentByteOffset,"bClassGetResponse",bClassGetResponse_val,2,CCID_descrip,0,0);
  AddFieldBreak();
  IncCurrByteOffset(1);
#END Decode of bClassGetResponse

  if (CurrentByteOffset + 1 > dataLength)  #Another data check
    return 1;
#BEGIN Decode of bClassEnvelope
  bClassEnvelope_val = GetDataByte( Base + CurrentByteOffset);
  if(bClassEnvelope_val == 0xFF)
    CCID_descrip = "<b>CCID:</b> The CCID echoes the class of the APDU. <br>&nbsp&nbsp<b>ICCD:</b> Echoes the class of the APDU.";
  else
    CCID_descrip = "<b>CCID:</b> Significant only for CCID that offer an extended APDU exchange level. Indicates the default class value used by the CCID for a Envelope command with transportation using an APDU by T=0 protocol. <br>&nbsp&nbsp<b>ICCD:</b> WARNING - Value not FFh --> should echo APDU class.";    
  AddEntry(CurrentByteOffset,"bClassEnvelope",bClassEnvelope_val,2,CCID_descrip,0,0);
  AddFieldBreak();
  IncCurrByteOffset(1);
#END Decode of bClassEnvelope    
    
  if (CurrentByteOffset + 2 > dataLength)  #Another data check
    return 1;  
#BEGIN Decode of wLcdLayout
  wLcdLayout_val = GetDataWord( Base + CurrentByteOffset );
  if(wLcdLayout_val == 0)
    CCID_descrip = "<b>CCID:</b> No LCD <br>&nbsp&nbsp<b>ICCD:</b> No LCD";
  else
    CCID_descrip = FormatEx("<b>CCID:</b> %d lines (upperbyte);  %d characters per line (lowerbyte) <br>&nbsp&nbsp<b>ICCD:</b> Should be 0000h (No LCD), not relevant, fixed for legacy reason.",((wLcdLayout_val>>8)&0xFF),(wLcdLayout_val&0xFF));
      
  AddEntry(CurrentByteOffset,"wLcdLayout",wLcdLayout_val,4,CCID_descrip,0,0);
  AddFieldBreak();
  IncCurrByteOffset(2);
#END Decode of wLcdLayout

  if (CurrentByteOffset + 1 > dataLength)  #Another data check
    return 1;
#BEGIN Decode of bPinSupport
  bPinSupport_val = GetDataByte( Base + CurrentByteOffset );
  if(bPinSupport_val == 0)
    CCID_descrip = "<b>CCID:</b> No PIN pad <br>&nbsp&nbsp<b>ICCD:</b> No PIN pad";
  else
  {
    CCID_descrip = "<b>CCID: </b><u>Supported</u>- ";
    if(bPinSupport_val&0x01)
      CCID_descrip += "PIN Verification; ";
    if(bPinSupport_val&0x02)
      CCID_descrip += "PIN Modification ";
      
    CCID_descrip += "<br>&nbsp&nbsp<b>ICCD:</b> Should be 'No PIN pad' (00h), not relevant, fixed for legacy reason.";
  }  
  AddEntry(CurrentByteOffset,"bPinSupport",bPinSupport_val,2,CCID_descrip,0,0);
  AddFieldBreak();
  IncCurrByteOffset(1);
#END Decode of bPinSupport  
  if (CurrentByteOffset + 1 > dataLength)  #Another data check
    return 1;
#BEGIN Decode of bMaxCCIDBusySlots
  bMaxCCIDBusySlots_val = GetDataByte( Base + CurrentByteOffset);
  if(bMaxCCIDBusySlots_val != 1)
    CCID_descrip = "<b>CCID:</b> Maximum number of slots which can be simultaneously busy. <br>&nbsp&nbsp<b>ICCD:</b> WARNING - Should be One Slot (01h), the USB-ICC is regarded as a single slot CCID.";
  else
    CCID_descrip = "<b>CCID:</b> Maximum number of slots which can be simultaneously busy. <br>&nbsp&nbsp<b>ICCD:</b> One slot is busy, the USB-ICC is regarded as a single slot CCID.";
  AddEntry(CurrentByteOffset,"bMaxCCIDBusySlots",bMaxCCIDBusySlots_val,2,CCID_descrip,0,1);
  AddFieldBreak();
  IncCurrByteOffset(1);
#END Decode of bMaxCCIDBusySlots  
}
      
      
      
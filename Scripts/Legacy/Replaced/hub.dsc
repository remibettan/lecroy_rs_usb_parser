*******************************************************************************
*
*  FILENAME: hub.dsc
*
*  Copyright (C) 1999 Computer Access Technology Corporation
*
*  DESCRIPTION
*    This descriptor definition file is supplied by CATC.
*    This file defines the HUB descriptor.
*    File version is 1.0.
*
*******************************************************************************

DescriptorName=HUB
DescriptorType=0x29
ClassCode=0x09

AllOffsets={
 2=bNbrPorts
 3=wHubCharacteristics
 5=bPwrOn2PwrGood
 6=bHubContrCurrent
 7=DeviceRemovable
 8=PortPwrCtrlMask
}

Offset(2)={
  FormatValue=The hub has %d downstream ports
}

Offset(3)={
  Size=2
  WordValue={
    0x0000=Ganged Power Switching, Not a compound device, Global Over-current protection
    0x0001=Individual Power Switching, Not a compound device, Global Over-current protection
    0x0002=No Power Switching, Not a compound device, Global Over-current protection
    0x0003=No Power Switching, Not a compound device, Global Over-current protection
    0x0004=Ganged Power Switching, Compound device, Global Over-current protection
    0x0005=Individual Power Switching, Compound device, Global Over-current protection
    0x0006=No Power Switching, Compound device, Global Over-current protection
    0x0007=No Power Switching, Compound device, Global Over-current protection
    0x0008=Ganged Power Switching, Not a compound device, Individual Over-current protection
    0x0009=Individual Power Switching, Not a compound device, Individual Over-current protection
    0x000A=No Power Switching, Not a compound device, Individual Over-current protection
    0x000B=No Power Switching, Not a compound device, Individual Over-current protection
    0x000C=Ganged Power Switching, Compound device, Individual Over-current protection
    0x000D=Individual Power Switching, Compound device, Individual Over-current protection
    0x000E=No Power Switching, Compound device, Individual Over-current protection
    0x000F=No Power Switching, Compound device, Individual Over-current protection
    0x0010=Ganged Power Switching, Not a compound device, No Over-current protection
    0x0011=Individual Power Switching, Not a compound device, No Over-current protection
    0x0012=No Power Switching, Not a compound device, No Over-current protection
    0x0013=No Power Switching, Not a compound device, No Over-current protection
    0x0014=Ganged Power Switching, Compound device, No Over-current protection
    0x0015=Individual Power Switching, Compound device, No Over-current protection
    0x0016=No Power Switching, Compound device, No Over-current protection
    0x0017=No Power Switching, Compound device, No Over-current protection
    0x0018=Ganged Power Switching, Not a compound device, No Over-current protection
    0x0019=Individual Power Switching, Not a compound device, No Over-current protection
    0x001A=No Power Switching, Not a compound device, No Over-current protection
    0x001B=No Power Switching, Not a compound device, No Over-current protection
    0x001C=Ganged Power Switching, Compound device, No Over-current protection
    0x001D=Individual Power Switching, Compound device, No Over-current protection
    0x001E=No Power Switching, Compound device, No Over-current protection
    0x001F=No Power Switching, Compound device, No Over-current protection
  }
}

Offset(5)={
   Units=2  
   FormatValue=The time from the start of the power-on sequence on a port until the power is good is %d ms   
}

Offset(6)={
  FormatValue=Maximum current required by Hub Controller electronics is %d mA
}

Offset(7)={
  Name=Device Removable
  Bitmap={
    1=Port 1, Device removable
    2=Port 2, Device removable
    3=Port 3, Device removable
    4=Port 4, Device removable
    5=Port 5, Device removable
    6=Port 6, Device removable
    7=Port 7, Device removable
  }
}

Offset(8)={
   WordValue={
       0xFF=All bits are set to one for 1.0 compatibility
   }
   FormatValue=Non-reserved value 0x%02X
}
#******************************************************************************
#
#  FILENAME: Usb3VisionDescriptors.inc
#
#  Copyright (C) 2013 Teledyne LeCroy Corporation
#
#  DESCRIPTION
#    This descriptor definition file is supplied by Teledyne LeCroy.
#    This file defines standard USB3 Vision Descriptors.
#    File version is 1.0.
#       Based on USB3 Vision Revision 1.02
#
#
#******************************************************************************

set Usb3VisionDescriptorTypeTable =         
[
    [ 0xFF, "UNKNOWN" ],
    [ 0x24, "VISION_DEVICE_INFO", "DEVICE INFO" ]
];


#If (Usb3 vision Class specific descriptor) decode; else return 0
TryUsb3VisionDescriptors(bDescriptorType)  
{
    CurrentByteOffset = 0;                                              #Global variable from UsbCommon.inc
    vision_row = Find (Usb3VisionDescriptorTypeTable, bDescriptorType);    #Find specific descriptor

    if (vision_row[0] == 0xFF)
        return 0;
  
    expectedLen = 20;
    dataLength = bLength;                   
                                                
    if (dataLength != expectedLen ) 
    {
        AddShortDataHeader( FormatEx ( "%s Descriptor (%d bytes) - Expected Length is %d bytes", vision_row[2], bLength, expectedLen ) );        
    }
    else
    {
        AddShortDataHeader(FormatEx ("%s Descriptor (%d bytes)", vision_row[2], bLength ));    
    }

    Call (vision_row[1]);
    
    return 1;
}

VISION_DEVICE_INFO() 
{   
    base = Base;
    ProcessedLen = 0;
    
    if( ProcessedLen >= bLength )
        return 0;
        
    bLength = GetDataByte(base); 
    AddEntry( 0, "bLength", bLength, 2, "", 0, 1);
    AddDescriptorSizeString(bLength);
    AddFieldBreak();
    ProcessedLen += 1;

    if( ProcessedLen >= bLength )
        return 0;    
        
    bDescriptorType = GetDataByte(base+1); 
    AddEntry( 1, "bDescriptorType", bDescriptorType, 2, "Device Info Descriptor", 0);
    AddFieldBreak();  
    ProcessedLen += 1;

    if( ProcessedLen >= bLength )
        return 0;       
        
    bDescriptorSubType  = GetDataByte(base+2); 
    AddEntry( 2, "bDescriptorSubType", bDescriptorSubType, 2, "U3V_CAMERAINFO", 0);
    AddFieldBreak();  
    ProcessedLen += 1;    
    
    if( ProcessedLen >= bLength )
        return 0;        
        
    bGenCPVersion = GetDataLong(base+3);
    AddEntry( 3, "bGenCPVersion", bGenCPVersion, 8, "GenCP version. Must be identical to the value in the bootstrap register GenCP Version.", 0);
    AddFieldBreak();
    ProcessedLen += 4;
        
    if( ProcessedLen >= bLength )
        return 0;            
        
    bU3VVersion = GetDataLong(base+7);
    AddEntry( 7, "bU3VVersion", bU3VVersion, 8, "USB3 Vision version. Must be identical to the value in the bootstrap register U3V Version.", 0);
    AddFieldBreak(); 
    ProcessedLen += 4;
    
    if( ProcessedLen >= bLength )
        return 0;       
        
    iDeviceGUID = GetDataByte(base+11);
    AddEntry( 11, "iDeviceGUID", iDeviceGUID, 2, "Index to USB3 Vision GUID string.", 0);
    AddFieldBreak();  
    ProcessedLen += 1;
    
    if( ProcessedLen >= bLength )
        return 0;        
        
    iVendorName = GetDataByte(base+12);
    AddEntry( 12, "iVendorName", iVendorName, 2, "Index to Vendor Name string. Must be identical to the string in the bootstrap register Manufacturer Name.", 0);
    AddFieldBreak();  
    ProcessedLen += 1;
    
    if( ProcessedLen >= bLength )
        return 0;        
        
    iModelName = GetDataByte(base+13);
    AddEntry( 13, "iModelName", iModelName, 2, "Index to Model Name string. Must be identical to the string in the bootstrap register Model Name.", 0);
    AddFieldBreak();  
    ProcessedLen += 1;
    
    if( ProcessedLen >= bLength )
        return 0;        
        
    iFamilyName = GetDataByte(base+14);
    AddEntry( 14, "iFamilyName", iFamilyName, 2, "Index to Family Name string. Must be identical to the string in the bootstrap register Family Name. May be zero.", 0);
    AddFieldBreak();
    ProcessedLen += 1;    
    
    if( ProcessedLen >= bLength )
        return 0;        
        
    iDeviceVersion = GetDataByte(base+15);
    AddEntry( 15, "iDeviceVersion", iDeviceVersion, 2, "Index to Device Version string. Must be identical to the string in the bootstrap register Device Version.", 0);
    AddFieldBreak();  
    ProcessedLen += 1;
    
    if( ProcessedLen >= bLength )
        return 0;        
        
    iManufactureInfo = GetDataByte(base+16);
    AddEntry( 16, "iManufactureInfo", iManufactureInfo, 2, "Index to Manufacturer Info string. Must be identical to the string in the bootstrap register Manufacturer Info.", 0);
    AddFieldBreak();  
    ProcessedLen += 1;    
    
    if( ProcessedLen >= bLength )
        return 0;        
        
    iSerialNumber = GetDataByte(base+17);
    AddEntry( 17, "iSerialNumber", iSerialNumber, 2, "Index to Serial Number string. Must be identical to the string in the bootstrap register Serial Number.", 0);
    AddFieldBreak();
    ProcessedLen += 1;    
    
    if( ProcessedLen >= bLength )
        return 0;        
        
    iUserDefinedName = GetDataByte(base+18);
    AddEntry( 18, "iUserDefinedName", iUserDefinedName, 2, "Index to User Defined Name string. Must be identical to the string in the bootstrap register User Defined Name. May be zero.", 0);
    AddFieldBreak();  
    ProcessedLen += 1;    
      
    if( ProcessedLen >= bLength )
        return 0;          
        
    # Bit 0: Full sepped, Bit 1: High Speed, Bit 2 : SUper Speed, Bit 3-8: Reserved    
    bmSpeedSupport = GetDataByte(base+19); 
    AddEntry( 19, "bmSpeedSupport", bmSpeedSupport, 2, "Bit 0: Full Speed, Bit 1: High Speed, Bit 2 : Super Speed, Bit 3-7: Reserved", 0);
    AddFieldBreak();  
    ProcessedLen += 1;    
 
}


#
#  Copyright (c) 2002- 2006, LeCroy Corp. PSG  - All Rights Reserved
#
#  PTPStillImageDeviceInfoDataset.inc
#
#  This file contains functional decoding related to the Device Information Dataset
#  


DeviceInfoDataset()
{  
    AddDecSeparator();
    isEnoughData = 1;  
    FieldColor = StandardVersionColor;
    if (in.DataLength > out.Decoded + 2)
    {
        StandardVersion = NextDataWord_();
        AddPayLoadCell("StandardVersion", StandardVersion, "Highest version of the standard that the device can support", FieldColor, [_TABULARCELL, CELL_STILL_IMAGE_STANDARD_VERSION, "TEXT_CAPTION"]);
        
        out.Decoded += 2;
    }
    else
        isEnoughData = 0;    

    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 4)
    {
        VendorExtensionID = NextDataDWord_();
        FieldColor = VendorExtensionColor;
        result = Find (MicrosoftVendorExtensionID, VendorExtensionID);
        AddPayLoadCell("VendExtID", result[1], Format("Vendor Extension ID = 0x%08X", VendorExtensionID));
        out.Decoded += 4;
    }
    else
        isEnoughData = 0;    

    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 2)
    {
        VendorExtensionVersion = NextDataWord_();
        FieldColor = VendorExtensionVersionColor;
        AddSimplePLCell("VendExtVersion", VendorExtensionVersion, Format("VendorExtensionVersion: Vendor-specific version number of extensions that are supported\nVendorExtensionVersion HexVal: 0x%04X", VendorExtensionVersion));
        out.Decoded += 2;
    }
    else
        isEnoughData = 0;    

    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 1)
    {
        VendorExtensionDescNumChars = NextNBits_(8);  # gets the number of characters that are in the vendorextensiondesc string
    	out.Decoded ++;
    }
    else
        isEnoughData = 0;    

    if (isEnoughData == 1 && in.DataLength >= out.Decoded + VendorExtensionDescNumChars * 2)
    {
        if (VendorExtensionDescNumChars > 0)
        {
            VendorExtesionDesc = ObtainUnicodeStringPTP(VendorExtensionDescNumChars);
            out.Decoded += VendorExtensionDescNumChars * 2;
            FieldColor = VendorExtensionDescColor;
            AddLimitedSimplePLCell("VendExtDesc", VendorExtesionDesc, Format("VendorExtensionDesc: String used to hold a description of the VendorExtensionID, length = %d",VendorExtensionDescNumChars));
	    }
    }
    else
        isEnoughData = 0;
              
    if(isEnoughData == 1 && !IsExpanded())   # if not expanded
    {
        AddLimitedCell("Vendor","Info",Format("VendorExtension information which includes:\n VendorExtensionID: 0x%04X(hexidecimal)",VendorExtensionID) + Format("\n VendorExtensionVersion: 0x%04X(hexidecimal)",VendorExtensionVersion) + Format("\n VendorExtensionDesc: %s", VendorExtesionDesc),VendorExtensionColor);
    }
    AddSeparator();
    
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 2)
    {
        FunctionalMode = NextDataWord_();    
        # uses the hex value of FunctionalMode to determine the string name of it
        result = Find (PTPFunctionalModeTable, FunctionalMode);
        if(result[0] == 0xFFFF && (FunctionalMode & 0x8000))
        {
        	  if (FunctinMode & 0x4000)
        	      result[1] = "MTP-defined";
        	  else
        	      result[1] = "MTP vendor extension";
        }
        FieldColor = FuncModeColor;
        AddLimitedPayLoadCell("FuncMode", result[1], Format("FunctionalMode: 0x%04X\nControls whether the device is in an alternate mode \n that provides a different set of capabilities",FunctinMode));	    
        out.Decoded += 2;
    }
    else
        isEnoughData = 0;    

    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 4)
    {
        FieldColor = OpsSupportedColor;
        OperationsSupportednumElements = NextDataDWord_();
        AddLimitedSimplePLCell("OpsSuppCount", OperationsSupportednumElements, "Number of operations that are supported by the device in decimal");
        out.Decoded += 4;
    }
    else
        isEnoughData = 0;    

    if (isEnoughData == 1 && in.DataLength >= out.Decoded + OperationsSupportednumElements * 2)
    {
        Ops = "";
        for(i = 0; i < OperationsSupportednumElements; i++) 
        {
  	        a = NextDataWord_();
  	        out.Decoded += 2;
  	        opsSupp ++;
	        _supOperations = Find(PTPOperationCodeTable, a);
	        statement = " ...Check the expanded version of this field to see rest of operations supported.";
	        if(_supOperations[0] == 0xFFFF && (a >> 15) == 0b1)
	        {
	            if (((a >> 11) & 0b00001) == 0b00001)
	                _supOperations[1] = "MTP-defined";
	            else
	        	    _supOperations[1] = Format("Vendor (0x%04X)", a); #"Vendor Extensions";
	        }
            FieldColor = OpsSupportedColor;
 	        AddLimitedSimplePLCell("OpsSupported", _supOperations[1], Format("Operation code value = 0x%04X",a));
 	        
 	        # for the tooltip
 	        if(opsSupp < 25)
 	        {
	            Ops += Format(" %s\n",_supOperations[1]);
	        }
	        else if(opsSupp == 25)
	        {
	            Ops += Format("%s",statement);
	        }
 	    }
        if (!IsExpanded())
        {
            AddLimitedCell("Operations","Supported",Format("List of operations that are supported: \n%s",Ops), OpsSupportedColor); 
        }
    }
    else
        isEnoughData = 0;
	AddSeparator();


    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 4)
    {
        FieldColor = EventsSupportedColor;   
        EventsSupportednumElements = NextDataDWord_();
        AddLimitedSimplePLCell("EventsSupp", EventsSupportednumElements,"Number of events that are currently generated by the device in decimal");
        out.Decoded += 4;
    }
    else
        isEnoughData = 0;    

    if (isEnoughData == 1 && in.DataLength >= out.Decoded + EventsSupportednumElements * 2)
    {
        Events = "";
        for(i = 0; i < EventsSupportednumElements; i++) 
        {
  	        a = NextDataWord_();
  	        out.Decoded += 2;
  	        eventcounter ++;
	        _supEventSupport = Find(PTPEventCodeTable, a);
	        eventstatement = "...Check the expanded version of this field to see rest of events supported.";
	        if(_supEventSupport[0] == 0xFFFF && (a >> 15) == 0b1)
	        {
	            if (((a >> 11) & 0b00001) == 0b00001)
	                _supEventSupport[1] = "MTP-defined";
	            else
	        	    _supEventSupport[1] = Format("Vendor (0x%04X)", a); #"Vendor Extensions";
	        }
            FieldColor = EventsSupportedColor;
 	        AddLimitedSimplePLCell("EventsSupp", _supEventSupport[1], Format("Event code value = 0x%04X",a));
 	        
 	        # for the tooltip
 	        if(eventcounter < 25)
 	        {
	            Events += Format(" %s\n",_supEventSupport[1]);
	        }
	        else if(eventcounter == 25)
	        {
	            Events += Format("%s",eventstatement);
	        }
 	    }
        if (!IsExpanded())
        {
            AddLimitedCell("Events","Supported",Format("List of events that are currently generated by the device: \n%s",Events), EventsSupportedColor);
        }
    }
    else
        isEnoughData = 0;
	AddSeparator();
	
    
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 4)
    {
        FieldColor = DPSColor;
        DSPnumElements = NextDataDWord_();
        AddLimitedSimplePLCell("DPSSupp", DSPnumElements,"Number of device properties supported by device in decimal");
        out.Decoded += 4;
    }
    else
        isEnoughData = 0;    

    if (isEnoughData == 1 && in.DataLength >= out.Decoded + DSPnumElements * 2)
    {
        DSPs = "";
        for(i = 0; i < DSPnumElements; i++) 
        {
  	        a = NextDataWord_();
  	        out.Decoded += 2;
  	        dpscounter ++;
	        _supDSP = Find(PTPDevicePropCodesTable, a);
	        dpsstatement = "...Check the expanded version of this field to see rest of the device properties supported.";
	        if(_supDSP[0] == 0xFFFF && (a >> 15) == 0b1)
	        {
	            if (((a >> 10) & 0b000001) == 0b000001)
	                _supDSP[1] = "MTP-defined";
	            else
	        	    _supDSP[1] = Format("Vendor (0x%04X)", a); #"Vendor Extensions";
	        }
            FieldColor = DPSColor;
 	        AddLimitedSimplePLCell("DPS", _supDSP[1] , Format("DevicePropertiesSupported: 0x%04X",a));
 	        
 	        # for the tooltip
 	        if(dpscounter < 25)
 	        {
	            DSPs += Format(" %s\n",_supDSP[1]);
	        }
	        else if(dpscounter == 25)
	        {
	            DSPs += Format("%s",dpsstatement);
	        }
 	    }
        if (!IsExpanded())
        {
            AddLimitedCell("DPS","Supported",Format("List of device properties supported by device: \n%s",DSPs),DPSColor);
        }
    }
    else
        isEnoughData = 0;
	AddSeparator();


    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 4)
    {
        FieldColor = CaptureFormatsColor;
        CapturenumElements = NextDataDWord_();
        AddLimitedSimplePLCell("CaptureSupp",CapturenumElements,"Number of capture formats that can be created by device in decimal");
        out.Decoded += 4;
    }
    else
        isEnoughData = 0;    

    if (isEnoughData == 1 && in.DataLength >= out.Decoded + CapturenumElements * 2)
    {
        Captures = "";
        for(i = 0; i < CapturenumElements; i++) 
        {
  	        a = NextDataWord_();
  	        out.Decoded += 2;
  	        capturecounter ++;
	        _supCapture = Find(PTPObjectFormatCodesTable, a);
	        capturestatement = "...Check the expanded version of this field to see rest of the capture formats supported.";    
	        if(_supCapture[0] == 0xFFFF && (a >> 15) == 0b1)
	        {
	            if (((a >> 11) & 0b00001) == 0b00001)
	                _supCapture[1] = "MTP-defined";
	            else
	        	    _supCapture[1] = "Vendor Extensions";
	        }
            FieldColor = CaptureFormatsColor;
 	        AddLimitedSimplePLCell("CaptureFormats", _supCapture[1], Format("CaptureFormat code = 0x%04X",a));
 	        
 	        # for the tooltip
 	        if(capturecounter < 25)
 	        {
	            Captures += Format(" %s\n",_supCapture[1]);
	        }
	        else if(capturecounter == 25)
	        {
	            Captures += Format("%s",capturestatement);
	        }
 	    }
        if (!IsExpanded())
        {
            AddLimitedCell("Capture","Formats",Format("List of data formats that the device can create: \n%s",Captures),CaptureFormatsColor);
        }
    }
    else
        isEnoughData = 0;
	AddSeparator();


    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 4)
    {
        FieldColor = ImageFormatsColor;
        ImagenumElements = NextDataDWord_();
        AddLimitedSimplePLCell("ImageSupp",ImagenumElements,"Number of image formats that are supported by the device in decimal");
        out.Decoded += 4;
    }
    else
        isEnoughData = 0;    

    if (isEnoughData == 1 && in.DataLength >= out.Decoded + ImagenumElements * 2)
    {
        Images = "";
        for(i = 0; i < ImagenumElements; i++) 
        {
  	        a = NextDataWord_();
  	        out.Decoded += 2;
  	        imagecounter ++;
	        _supImage = Find(PTPObjectFormatCodesTable, a);
	        imagestatement = "...Check the expanded version of this field to see rest of the image formats supported.";    
	        if(_supImage[0] == 0xFFFF && (a >> 15) == 0b1)
	        {
	            if (((a >> 11) & 0b00001) == 0b00001)
	                _supImage[1] = "MTP-defined";
	            else
	        	    _supImage[1] = "Vendor Extensions";
	        }
            FieldColor = ImageFormatsColor;
 	        AddLimitedSimplePLCell("ImageFormats", _supImage[1], Format("ImageFormat code = 0x%04X",a));
 	        
 	        # for the tooltip
 	        if(imagecounter < 25)
 	        {
	            Images += Format(" %s\n",_supImage[1]);
	        }
	        else if(imagecounter == 25)
	        {
	            Images += Format("%s",imagestatement);
	        }
 	    }
        if (!IsExpanded())
        {
            AddLimitedCell("Image","Formats",Format("List of image formats that the device supports \n(order is from highest preference to lowest preference): \n%s",Images),ImageFormatsColor);
        }
    }
    else
        isEnoughData = 0;
	AddSeparator();

    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 1)
    {
        ManufacturernumChars = NextNBits_(8);
        out.Decoded ++;
    }
    else
        isEnoughData = 0;    

    if (isEnoughData == 1 && in.DataLength >= out.Decoded + ManufacturernumChars * 2)
    {
        if (ManufacturernumChars > 0)
        {   
	        FieldColor = ManufacturerColor;    
            Manufacturer = ObtainUnicodeStringPTP(ManufacturernumChars);
            out.Decoded += ManufacturernumChars * 2;
            AddLimitedPayLoadCell("Manufacturer", Manufacturer, Format("Manufacturer name, length = %d", ManufacturernumChars));
        }
    }
    else
        isEnoughData = 0;    

    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 1)
    {
	    ModelnumChars = NextNBits_(8);
	    out.Decoded ++;
    }
    else
        isEnoughData = 0;    

    if (isEnoughData == 1 && in.DataLength >= out.Decoded + ModelnumChars * 2)
    {
        if (ModelnumChars > 0)
        {   
            Model = ObtainUnicodeStringPTP(ModelnumChars);
            out.Decoded += ModelnumChars * 2;
            FieldColor = ModelColor;
            AddLimitedPayLoadCell("Model", Model, Format("Model name, length = %d", ModelnumChars));
        }
    }
    else
        isEnoughData = 0;  

    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 1)
    {
	    DeviceVersionnumChars = NextNBits_(8);
	    out.Decoded ++;
    }
    else
        isEnoughData = 0;    

    if (isEnoughData == 1 && in.DataLength >= out.Decoded + DeviceVersionnumChars * 2)
    {
        if (DeviceVersionnumChars > 0)
        {   
            DevVer = ObtainUnicodeStringPTP( DeviceVersionnumChars );
            out.Decoded += DeviceVersionnumChars * 2;
            FieldColor = DeviceVersionColor;
            AddLimitedPayLoadCell("DevVer", DevVer, Format("Device Version, length = %d", DeviceVersionnumChars));
        }
    }
    else
        isEnoughData = 0; 

    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 1)
    {
	    SerialNumnumChars = NextNBits_(8);
	    out.Decoded ++;
    }
    else
        isEnoughData = 0;    

    if (isEnoughData == 1 && in.DataLength >= out.Decoded + SerialNumnumChars * 2)
    {
        if (SerialNumnumChars > 0)
        {   
            SerialNumber = ObtainUnicodeStringPTP(SerialNumnumChars);
            out.Decoded += SerialNumnumChars * 2;
            FieldColor = SerialNumberColor;
            AddLimitedPayLoadCell("SerialNumber", SerialNumber, Format("Serial Number, length = %d", SerialNumnumChars));
        }
    }
    else
        isEnoughData = 0; 

    return isEnoughData;
}



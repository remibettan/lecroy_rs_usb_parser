#******************************************************************************
#
#  FILENAME: VideoDescriptors.inc
#
#  Copyright (C) 2004 Computer Access Technology Corporation
#
#  DESCRIPTION
#    This descriptor definition file is supplied by CATC.
#    This file defines standard USB Video descriptors.
#    File version is 1.0.
#
#
#******************************************************************************

set VC_Version =0;

TryVideoDescriptors(bDescriptorType)
{
   _row_vid = Find (VideoClassSpecificDescriptorTypesTable, bDescriptorType);
   
   if (_row_vid[0] == 0xFF) 
       return 0;
       
   Call (_row_vid[1]);
   return 1;   
}

CS_UNDEFINED()
{
    return 0; 
}

CS_DEVICE()
{
    return 0; 
}


CS_CONFIGURATION()
{
    return 0; 
}


CS_STRING()
{
    return 0; 
}


CS_INTERFACE()
{
    base = Base;

    bLength            = GetDataByte(base);    
    bDescriptorType    = GetDataByte(base+1);    
    bDescriptorSubType = GetDataByte(base+2);
    AddShortDataHeader(FormatEx ("%s Descriptor  (%d bytes)", "CS_INTERFACE", bLength ));
       
    AddEntry( 0, "bLength", bLength, 2, "", 1);
    AddDescriptorSizeString(bLength);
    AddFieldBreak();
    
    AddEntry( 1, "bDescriptorType", bDescriptorType, 2, GetDescriptorTypeString("CS_INTERFACE"), 0);
    AddFieldBreak();
    
    # We need to use the most recent interface subtype to see which type (streaming, control, etc)
    # we are looking for
   
    if(VC_Version == 0x0100)	#Checking VC Version to call appropriate table
       _row_vid_if = Find (VideoClassSpecificVSInterfaceDescriptorSubtypesTable, bDescriptorSubType);
    else if(VC_Version == 0x150)
		_row_vid_if = Find (VideoClassSpecificVSInterfaceDescriptorSubtypesTable_V1_5, bDescriptorSubType);
	else 
		_row_vid_if = Find (VideoClassSpecificVSInterfaceDescriptorSubtypesTable_V1_1, bDescriptorSubType);
		
    if (MostRecentInterfaceSubClass == 1)
    {
        _row_vid_if = Find (VideoClassSpecificVCInterfaceDescriptorSubtypesTable, bDescriptorSubType);
    }
    
   
    if (_row_vid_if[0] == 0xFF) 
    {
        AddEntry( 2, "bDescriptorSubType", bDescriptorSubType, 2, "SubType unknown", 0);
        AddFieldBreak();
        return 0;
    }
   
    AddEntry( 2, "bDescriptorSubType1", bDescriptorSubType, 2, Format ("%s descriptor subtype", _row_vid_if[1]), 0);
    AddFieldBreak();
    
    
    decoded_it = Call (_row_vid_if[1]); 
    
    if ((decoded_it == 0) && (bLength > 3))
    {
        FinishUndecodedData(bLength, 3);
        /*
        loop_count_down = bLength - 3;
        loop_index = 0;
        while (loop_count_down > 0)
        {
           byteval       = GetDataByte(base+3+loop_index);
           AddEntry( 3+loop_index, "<Additional Data>", byteval, 2, Format ("Value = %d", byteval) , 0); 
    AddBlankLine();
           loop_count_down--;
           loop_index++;
        }
        */
    }
    return 1;  
         
}


CS_ENDPOINT()
{
    base = Base;

    bLength            = GetDataByte(base);    
    bDescriptorType    = GetDataByte(base+1);    
    bDescriptorSubType = GetDataByte(base+2);
    
    AddShortDataHeader(FormatEx ("%s Descriptor  (%d bytes)", "CS_INTERFACE", bLength ));
       
    AddEntry( 0, "bLength", bLength, 2, "", 1);
    AddDescriptorSizeString(bLength);
    AddFieldBreak();
    
    AddEntry( 1, "bDescriptorType", bDescriptorType, 2, GetDescriptorTypeString("CS_INTERFACE"), 0);
    AddFieldBreak();
    
    _row_vid_ep = Find (VideoClassSpecificEndpointDescriptorSubtypesTable, bDescriptorSubType);
    if (_row_vid_ep[0] == 0xFF) 
    {
        AddEntry( 2, "bDescriptorSubType", bDescriptorSubType, 2, "SubType unknown", 0);
        AddFieldBreak();
       return 0;
    }
   
    AddEntry( 2, "bDescriptorSubType", bDescriptorSubType, 2, Format ("%s descriptor subtype", _row_vid_ep[1]), 0);
    AddFieldBreak();
    
    decoded_it = Call (_row_vid_ep[1]); 
    return 1;  
}

EP_UNDEFINED()
{
    return 0;
}

EP_GENERAL()
{
    return 0;
}

EP_ENDPOINT()
{
    return 0;
}

EP_INTERRUPT()
{
    base = Base;
    wMaxTransferSize   = GetDataWord(base+3);          
    AddEntry( 3, "wMaxTransferSize", wMaxTransferSize, 4, "The maximum interrupt", 0);
    AddDescriptionOnly( "structure size this" );
    AddDescriptionOnly( "endpoint is capable" );
    AddDescriptionOnly( FormatEx( "of sending is %d", wMaxTransferSize) );
    AddFieldBreak();
    return 1;
}





VC_DESCRIPTOR_UNDEFINED()
{
    return 0; # did not decoded it
}


VC_HEADER()
{
    base = Base;
	
	bcdVDC              = GetDataWord(base+3);
	wTotalLength        = GetDataWord(base+5);
	dwClockFrequency    = GetDataLong(base+7);    
	bInCollection       = GetDataByte(base+11);

	VC_Version = bcdVDC;
	
	if(VC_Version == 0x0100)
		AddEntry( 3, "bcdVDC", bcdVDC, 4, "Video Device Class" , 0);
	else
		AddEntry( 3, "bcdUVC", bcdVDC, 4, "Video Device Class" , 0);

	AddDescriptionOnly( "Specification" );
	AddDescriptionOnly( FormatEx( "release %d.%1d%1d", (bcdVDC & 0xFF00)>> 8, (bcdVDC >> 4) & 0xF, bcdVDC & 0xF ) );			
	AddFieldBreak();
	
	AddEntry( 5, "wTotalLength", wTotalLength, 4, "The total bytes of data for", 0); 
    AddDescriptionOnly("the Class Specific VideoControl");
    AddDescriptionOnly(Format ("interface descriptor is %d", wTotalLength));
    AddDescriptionOnly("This includes the combined length");
    AddDescriptionOnly("of this header and all Unit");
    AddDescriptionOnly("and Terminal descriptors");
    AddFieldBreak();
    
    AddEntry( 7, "dwClockFrequency", dwClockFrequency, 8, "The device clock frequency", 0); 
    AddDescriptionOnly(Format ("is %d Hz.  Specifies the unit used", dwClockFrequency));
    AddDescriptionOnly("for time info fields in the ");
    AddDescriptionOnly("Video Sample Headers in the");
    AddDescriptionOnly("data stream");
    AddFieldBreak();
    
    AddEntry( 11, "bInCollection", bInCollection, 2, "The number of VideoStreaming", 0); 
    AddDescriptionOnly("interfaces in the Video");
    AddDescriptionOnly("Interface Collection to which");
    AddDescriptionOnly("this VideoConrol interface");
    AddDescriptionOnly(Format("belongs is : %d", bInCollection));
    AddFieldBreak();
    
    loop_count_down = bInCollection;
    loop_index = 0;
    while (loop_count_down > 0)
    {
       baInterfaceNr       = GetDataByte(base+12+loop_index);
       AddEntry( 12+loop_index, Format ( "baInterfaceNr(%d)", (loop_index+1)), baInterfaceNr, 2, "VideoStreaming interface", 0); 
       AddDescriptionOnly(Format ("number %d in the collection", baInterfaceNr));
       AddFieldBreak();
       loop_count_down--;
       loop_index++;
    }
    
    return 1; #decoded it
}

VC_INPUT_TERMINAL()
{
    base = Base;

    bTerminalID     = GetDataByte(base+3);
    wTerminalType   = GetDataWord(base+4);
    bAssocTerminal  = GetDataByte(base+6);    
    iTerminal       = GetDataByte(base+7);
    
    AddEntry( 3, "bTerminalID", bTerminalID, 2, "Unique Terminal" , 0);
    AddDescriptionOnly(  FormatEx( "Identifier is %d", bTerminalID ));
    AddFieldBreak();
    
    
    _row_vid_it = Find (USBTerminalTypes, wTerminalType);
   
    if (_row_vid_it[0] == 0xFF) 
    {
        _row_vid_it = Find (InputTerminalTypes, wTerminalType);
    }
    if (_row_vid_it[0] == 0xFF) 
    {
        _row_vid_it = Find (OutputTerminalTypes, wTerminalType);
    }
    if (_row_vid_it[0] == 0xFF) 
    {
        _row_vid_it = Find (ExternalTerminalTypesTable, wTerminalType);
    }
     
    if (_row_vid_it[0] == 0xFF) 
    {
        AddEntry( 4, "wTerminalType", wTerminalType, 4, Format("wTerminalType %d unknown", wTerminalType ), 0);
    }
    else
    {
        AddEntry( 4, "wTerminalType", wTerminalType, 4, "The Terminal Type is", 0);
        AddDescriptionOnly ( Format("%s", _row_vid_it[1])) ;
    }
    
    AddFieldBreak();
    
 
    AddEntry( 6, "bAssocTerminal", bAssocTerminal, 2, "This Input Terminal is", 0); 
    AddDescriptionOnly("associated with Output");
    AddDescriptionOnly(Format ("Terminal ID %d.", bAssocTerminal));
    AddFieldBreak();
    
       
    AddEntry( 7, "iTerminal", iTerminal, 2, "The index of the", 0); 
    AddDescriptionOnly("Input Terminal string");
    AddDescriptionOnly(Format ("descriptor is %d", iTerminal));    
    AddFieldBreak();
    
    successful_decode = 0;
    if (_row_vid_it[0] != 0xFF)
    { 
        successful_decode = Call (_row_vid_it[1]);
    }
    
    if ((successful_decode == 0) && (bLength > 8))
    {
        #AddLineOfText(Format ("Remaining Undecoded %d Bytes:", bLength-8));
        FinishUndecodedData(bLength, 8);
        /*
        loop_count_down = bLength - 8;
        loop_index = 0;
        while (loop_count_down > 0)
        {
           byteval       = GetDataByte(base+8+loop_index);
           AddEntry( 8+loop_index, "<Additional Data>", byteval, 2, Format ("Value = %d", byteval) , 0); 
           AddFieldBreak();
           loop_count_down--;
           loop_index++;
        }
        */
    }
    
    return 1; #decoded it
}

    
    
TT_VENDOR_SPECIFIC()
{
    return 0; # cant decode it
}

TT_STREAMING()
{ 
    return 0; # cant decoded it YET
}



ITT_VENDOR_SPECIFIC()
{
    return 0; # cant decode it
}

ITT_CAMERA()
{
    base = Base;

    wObjectiveFocalLengthMin = GetDataWord(base+8);
    wObjectiveFocalLengthMax = GetDataWord(base+10);
    wOcularFocalLength       = GetDataWord(base+12);
    bControlSize             = GetDataByte(base+14);
     
    if (wObjectiveFocalLengthMin == 0)
    {
        AddEntry( 8, "wObjectiveFocalLenMin", wObjectiveFocalLengthMin, 4, "Optical Zoom Not Supported", 0); 
    }
    else
    {
        AddEntry( 8, "wObjectiveFocalLenMin", wObjectiveFocalLengthMin, 4, "The value of Lmin", 0); 
        AddDescriptionOnly(Format ("is %d.", wObjectiveFocalLengthMin));
    }
    AddFieldBreak();

    if (wObjectiveFocalLengthMax == 0)
    {
        AddEntry( 10, "wObjectiveFocalLenMax", wObjectiveFocalLengthMax, 4, "Optical Zoom Not Supported", 0); 
    }
    else
    {
        AddEntry( 10, "wObjectiveFocalLenMax", wObjectiveFocalLengthMax, 4, "The value of Lmax", 0); 
        AddDescriptionOnly(Format ("is %d.", wObjectiveFocalLengthMax));
    }
    AddFieldBreak();

    if (wOcularFocalLength == 0)
    {
        AddEntry( 12, "wOcularFocalLength", wOcularFocalLength, 4, "Optical Zoom Not Supported", 0); 
    }
    else
    {
        AddEntry( 12, "wOcularFocalLength", wOcularFocalLength, 4, "The value of Locular", 0); 
        AddDescriptionOnly(Format ("is %d", wOcularFocalLength));
    }
    AddFieldBreak();
    
    AddEntry( 14, "bControlSize", bControlSize, 2, "The number of ", 0); 
    AddDescriptionOnly(Format ("bmControl bytes is %d.", bControlSize));
    AddFieldBreak();
    
    if (bControlSize > 0)
    {
        bmControls               = GetDataByte(base+15);
        AddEntry( 15, "bmControls 0", bmControls, 2, "Control Bitmap: ", 0); 
        AddDescriptionOnly(Format ("<br>D0:  Scanning Mode            %d", ((bmControls >> 0) & 0x01)));
        AddDescriptionOnly(Format ("<br>D1:  Auto-Exposure Mode       %d", ((bmControls >> 1) & 0x01)));
        AddDescriptionOnly(Format ("<br>D2:  Auto-Exposure Priority   %d", ((bmControls >> 2) & 0x01)));
        AddDescriptionOnly(Format ("<br>D3:  Exposure Time (Absolute) %d", ((bmControls >> 3) & 0x01)));
        AddDescriptionOnly(Format ("<br>D4:  Exposure Time (Relative) %d", ((bmControls >> 4) & 0x01)));
        AddDescriptionOnly(Format ("<br>D5:  Focus (Absolute)         %d", ((bmControls >> 5) & 0x01)));
        AddDescriptionOnly(Format ("<br>D6:  Focus (Relative)         %d", ((bmControls >> 6) & 0x01)));
        AddDescriptionOnly(Format ("<br>D7:  Iris (Absolute)          %d", ((bmControls >> 7) & 0x01)));
        AddFieldBreak();
    }
    
    if (bControlSize > 1)
    {
        bmControls               = GetDataByte(base+16);
        AddEntry( 16, "bmControls 1", bmControls, 2, "Control Bitmap: ", 0); 
        AddDescriptionOnly(Format ("<br>D8:  Iris (Relative)          %d", ((bmControls >> 0) & 0x01)));
        AddDescriptionOnly(Format ("<br>D9:  Zoom (Absolute)          %d", ((bmControls >> 1) & 0x01)));
        AddDescriptionOnly(Format ("<br>D10: Zoom (Relative)          %d", ((bmControls >> 2) & 0x01)));
        AddDescriptionOnly(Format ("<br>D11: PanTilt (Absolute)       %d", ((bmControls >> 3) & 0x01)));
        AddDescriptionOnly(Format ("<br>D12: PanTilt (Relative)       %d", ((bmControls >> 4) & 0x01)));
        AddDescriptionOnly(Format ("<br>D13: Roll (Absolute)          %d", ((bmControls >> 5) & 0x01)));
        AddDescriptionOnly(Format ("<br>D14: Roll (Relative)          %d", ((bmControls >> 6) & 0x01)));
        AddDescriptionOnly(Format ("<br>D15: Reserved                 %d", ((bmControls >> 7) & 0x01)));
        AddFieldBreak();
    }
    
    if (bControlSize > 2)
    {
        bmControls               = GetDataByte(base+17);
        AddEntry( 17, "bmControls 2", bmControls, 2, "Control Bitmap: ", 0); 
        AddDescriptionOnly(Format ("<br>D16: Reserved                 %d", ((bmControls >> 0) & 0x01)));
        AddDescriptionOnly(Format ("<br>D17: Focus, Auto              %d", ((bmControls >> 1) & 0x01)));
        AddDescriptionOnly(Format ("<br>D18: Privacy                  %d", ((bmControls >> 2) & 0x01)));
        #add mere here...
        AddFieldBreak();
    }
    
    if (bControlSize > 3)
    {
        bmControls               = GetDataByte(base+18);
        AddEntry( 18, "bmControls 3", bmControls, 2, "Unable to decode", 0); 
        AddFieldBreak();
    }
    
    if (bControlSize > 4)
    {
        bmControls               = GetDataByte(base+19);
        AddEntry( 19, "bmControls 4", bmControls, 2, "Unable to decode", 0); 
        AddFieldBreak();
    }
    return 1;
}

ITT_MEDIA_TRANSPORT_INPUT()
{
    return 0;
}

EXTERNAL_VENDOR_SPECIFIC()
{
    return 0; # cant decode it
}

COMPOSITE_CONNECTOR()
{
    return 0;
}

SVIDEO_CONNECTOR()
{
    return 0;
}

COMPONENT_CONNECTOR()
{
    return 0;
}

VC_OUTPUT_TERMINAL()
{
    base = Base;

    bTerminalID     = GetDataByte(base+3);
    wTerminalType   = GetDataWord(base+4);
    bAssocTerminal  = GetDataByte(base+6);    
    iTerminal       = GetDataByte(base+7);
    
    AddEntry( 3, "bTerminalID", bTerminalID, 2, "Unique Terminal" , 0);
    AddDescriptionOnly(  FormatEx( "Identifier is %d", bTerminalID ));
    AddFieldBreak();
    
    
    _row_vid_ot = Find (USBTerminalTypes, wTerminalType);
   
    if (_row_vid_ot[0] == 0xFF) 
    {
         _row_vid_ot = Find (InputTerminalTypes, wTerminalType);
    }
    if (_row_vid_ot[0] == 0xFF) 
    {
         _row_vid_ot = Find (OutputTerminalTypes, wTerminalType);
    }
    if (_row_vid_ot == 0xFF) 
    {
         _row_vid_ot= Find (ExternalTerminalTypesTable, wTerminalType);
    } 
    if (_row_vid_ot[0] == 0xFF) 
    {
        AddEntry( 4, "wTerminalType", wTerminalType, 4, Format("wTerminalType %d unknown", wTerminalType ), 0);
    }
    else
    {
        AddEntry( 4, "wTerminalType", wTerminalType, 4, "The Terminal Type is", 0);
        AddDescriptionOnly ( Format("%s", _row_vid_ot[1])) ;
    }
    
    AddFieldBreak();
    
 
    AddEntry( 6, "bAssocTerminal", bAssocTerminal, 2, "This Output Terminal is", 0); 
    AddDescriptionOnly("associated with Input");
    AddDescriptionOnly(Format ("Terminal ID %d", bAssocTerminal));
    AddFieldBreak();
    
    AddEntry( 7, "bSourceID", bSourceID, 2, "The ID of the Unit or", 0); 
    AddDescriptionOnly("Terminal to which this Terminal");
    AddDescriptionOnly(Format ("is Connected is %d", bSourceID));  
    AddFieldBreak();
    
    AddEntry( 8, "iTerminal", iTerminal, 2, "The index of the", 0); 
    AddDescriptionOnly("Input Terminal string");
    AddDescriptionOnly(Format ("descriptor is %d", iTerminal));    
    AddFieldBreak();
           
    successful_decode = 0;
    if (_row_vid_ot[0] != 0xFF)
    { 
        successful_decode = Call (_row_vid_ot[1]);
    }
    
    if ((successful_decode == 0) && (bLength > 9))
    {
        FinishUndecodedData(bLength, 9);
        /*
        loop_count_down = bLength - 9;
        loop_index = 0;
        while (loop_count_down > 0)
        {
           byteval       = GetDataByte(base+9+loop_index);
           AddEntry( 9+loop_index, "<Additional Data>", byteval, 2, Format ("Value = %d", byteval) , 0); 
           AddFieldBreak();    
           loop_count_down--;
           loop_index++;
        }
        */
    }
    
    return 1; #decoded it

}


OTT_VENDOR_SPECIFIC()
{
    return 0; # cant decode it
}

OTT_DISPLAY()
{
    return 0;
}

OTT_MEDIA_TRANSPORT_OUTPUT()
{
    return 0;
}


VC_SELECTOR_UNIT()
{
    base = Base;

    bUnitID          = GetDataByte(base+3);
    bNrInPins        = GetDataByte(base+4);
    
    AddEntry( 3, "bUnitID", bUnitID, 2, "Unique Unit Number" , 0);
    AddDescriptionOnly( "within the Video" );
    AddDescriptionOnly( Format( "Function is %d", bUnitID) );
    AddFieldBreak();
         
    AddEntry( 4, "bNrInPins", bNrInPins, 2, "The number of Input Pins", 0); 
    AddDescriptionOnly(Format("of this Unit is %d", bNrInPins));
    AddFieldBreak();
    
    loop_count_down = bNrInPins;
    loop_index = 0;
    while (loop_count_down > 0)
    {
       baSourceID       = GetDataByte(base+5+loop_index);
       AddEntry( 5+loop_index, Format ( "baSourceID(%d)", (loop_index+1)), baSourceID, 2, "ID of the Unit or", 0); 
       AddDescriptionOnly("Terminal to which the first");
       AddDescriptionOnly("Input Pin of this Selector");
       AddDescriptionOnly(Format ("Unit is Connected: %d", baSourceID));
       AddFieldBreak();
       loop_count_down--;
       loop_index++;
    }
    
    AddEntry( 5+loop_index, "iSelector", iSelector, 2, "The index of the", 0); 
    AddDescriptionOnly("Selector Unit string");
    AddDescriptionOnly(Format ("descriptor is %d", iSelector));    
    AddFieldBreak();
    
    return 1; #decoded it
  
}


VC_PROCESSING_UNIT()
{
    base = Base;

    bUnitID        = GetDataByte(base+3);
    bSourceID      = GetDataByte(base+4);
    wMaxMultiplier = GetDataWord(base+5);
    bControlSize   = GetDataByte(base+7);
    
    AddEntry( 3, "bUnitID", bUnitID, 2, "Unique Unit Number" , 0);
    AddDescriptionOnly( "within the Video" );
    AddDescriptionOnly( Format( "Function is %d", bUnitID) );
    AddFieldBreak();
     
    if (wMaxMultiplier == 0)
    {
        AddEntry( 5, "wMaxMultiplier", wMaxMultiplier, 4, "Optical Zoom Not Supported", 0); 
    }
    else
    {
        AddEntry( 5, "wMaxMultiplier", wMaxMultiplier, 4, "The value of Lmin", 0); 
        AddDescriptionOnly(Format ("is %d.", wMaxMultiplier));
    }
    AddFieldBreak();

    
    AddEntry( 7, "bControlSize", bControlSize, 2, "The number of ", 0); 
    AddDescriptionOnly(Format ("bmControl bytes is %d.", bControlSize));
    AddFieldBreak();
    
    if (bControlSize > 0)
    {
        bmControls               = GetDataByte(base+8);
        AddEntry( 8, "bmControls 0", bmControls, 2, "Control Bitmap: ", 0); 
        AddDescriptionOnly(Format ("<br>D0:  Brightness           %d", ((bmControls >> 0) & 0x01)));
        AddDescriptionOnly(Format ("<br>D1:  Contrast             %d", ((bmControls >> 1) & 0x01)));
        AddDescriptionOnly(Format ("<br>D2:  Hue                  %d", ((bmControls >> 2) & 0x01)));
        AddDescriptionOnly(Format ("<br>D3:  Saturation           %d", ((bmControls >> 3) & 0x01)));
        AddDescriptionOnly(Format ("<br>D4:  Sharpness            %d", ((bmControls >> 4) & 0x01)));
        AddDescriptionOnly(Format ("<br>D5:  Gamma                %d", ((bmControls >> 5) & 0x01)));
        AddDescriptionOnly(Format ("<br>D6:  White Bal Temp       %d", ((bmControls >> 6) & 0x01)));
        AddDescriptionOnly(Format ("<br>D7:  White Bal Component  %d", ((bmControls >> 7) & 0x01)));
        AddFieldBreak();
    }
    if (bControlSize > 1)
    {
        bmControls               = GetDataByte(base+9);
        AddEntry( 9, "bmControls 1", bmControls, 2, "Control Bitmap: ", 0); 
        AddDescriptionOnly(Format ("<br>D8:  Backlight Comp       %d", ((bmControls >> 0) & 0x01)));
        AddDescriptionOnly(Format ("<br>D9:  Gain                 %d", ((bmControls >> 1) & 0x01)));
        AddDescriptionOnly(Format ("<br>D10: Power Line Freq      %d", ((bmControls >> 2) & 0x01)));
        AddDescriptionOnly(Format ("<br>D11: Hue, Auto            %d", ((bmControls >> 3) & 0x01)));
        AddDescriptionOnly(Format ("<br>D12: Whte Bal Temp, Auto  %d", ((bmControls >> 4) & 0x01)));
        AddDescriptionOnly(Format ("<br>D13: Wht Bal Cmpnt, Auto  %d", ((bmControls >> 5) & 0x01)));
        AddDescriptionOnly(Format ("<br>D14: Digital Mult         %d", ((bmControls >> 6) & 0x01)));
        AddDescriptionOnly(Format ("<br>D15: Digital Mult Limit   %d", ((bmControls >> 7) & 0x01)));
        AddFieldBreak();
    }
    
    if(VC_Version == 0x0100){   #Checking if VC Ver. is 1.0, else it's the current new spec (v1.10), handle appropriatlely
    	if (bControlSize > 2)
    	{
        bmControls               = GetDataByte(base+10);
        AddEntry( 11, "bmControls 2", bmControls, 2, "Unable to decode", 0); 
        AddFieldBreak();
    	}
    }
    else{
      if (bControlSize > 2)
  	  {
        bmControls               = GetDataByte(base+10);
        AddEntry( 10, "bmControls 2", bmControls, 2, "Control Bitmap: ", 0);
        AddDescriptionOnly(Format ("<br>D16: Analog Vid Std       %d", ((bmControls >> 0) & 0x01)));
        AddDescriptionOnly(Format ("<br>D17: Analog Vid Lock Stat %d", ((bmControls >> 1) & 0x01))); 
        AddDescriptionOnly("D18+: Should be reserved    ");
        AddFieldBreak();
    	}
    }
    if (bControlSize > 3)
    {
        bmControls               = GetDataByte(base+11);
        AddEntry( 11, "bmControls 3", bmControls, 2, "Unable to decode", 0); 
        AddFieldBreak();
    }
    
    AddEntry( 8+bControlSize, "iProcessing", iProcessing, 2, "The index of the", 0); 
    AddDescriptionOnly("Processing Unit string");
    AddDescriptionOnly(Format ("descriptor is %d", iProcessing));
    AddFieldBreak();
    
    return 1; #decoded it   
}


VC_EXTENSION_UNIT()
{
    base = Base;

    bUnitID            = GetDataByte(base+3);
LittleEndian = 0;
    guidExtensionCode1 = GetDataLong(base+4);
    guidExtensionCode2 = GetDataLong(base+8);
    guidExtensionCode3 = GetDataLong(base+12);
    guidExtensionCode4 = GetDataLong(base+16);
LittleEndian = 1;
    bNumControls       = GetDataByte(base+20);
    bNrInPins          = GetDataByte(base+21);
    
    AddEntry( 3, "bUnitID", bUnitID, 2, "Unique Unit Number" , 0);
    AddDescriptionOnly( "within the Video" );
    AddDescriptionOnly( Format( "Function is - %d", bUnitID) );
    AddFieldBreak();
#mgd
         guidExtensionCodeS=FormatEx("%04X-%04X-%04X-%04X",guidExtensionCode1, guidExtensionCode2, guidExtensionCode3, guidExtensionCode4);
    AddEntry( 4, "guidExtensionCode", guidExtensionCode1, 8, "Vendor-Specific code identifying the Extension Unit\n" + guidExtensionCodeS, 0,0,guidExtensionCodeS); 
    #AddEntry( 8, "guidExtensionCode2", guidExtensionCode2, 8, "", 0); 
    #AddEntry( 12, "guidExtensionCode3", guidExtensionCode3, 8, "", 0); 
    #AddEntry( 16, "guidExtensionCode4", guidExtensionCode4, 8, "", 0); 
    AddFieldBreak();
    
    AddEntry( 20, "bNumControls", bNumControls, 2, "The number of controls in", 0); 
    AddDescriptionOnly(Format("this Extension Unit is %d", bNumControls));
    AddFieldBreak();
    
    AddEntry( 21, "bNrInPins", bNrInPins, 2, "The number of Input Pins", 0); 
    AddDescriptionOnly(Format("of this Unit is %d", bNrInPins));
    AddFieldBreak();
    
    loop_count_down = bNrInPins;
    loop_index = 0;
    while (loop_count_down > 0)
    {
       baSourceID       = GetDataByte(base+22+loop_index);
       AddEntry( 22+loop_index, Format ( "baSourceID(%d)", (loop_index+1)), baSourceID, 2, "ID of the Unit or", 0); 
       AddDescriptionOnly("Terminal to which the first");
       AddDescriptionOnly("Input Pin of this Extensionm");
       AddDescriptionOnly(Format ("Unit is Connected: %d", baSourceID));
       AddFieldBreak();
       loop_count_down--;
       loop_index++;
    }

    
    bControlSize       = GetDataByte(base+22+loop_index);
    AddEntry( 22+loop_index, "bControlSize", bControlSize, 2, "The number of ", 0); 
    AddDescriptionOnly(Format ("bmControls bytes is %d.", bControlSize));
    AddFieldBreak();
    
    if (bControlSize > 0)
    {
        bmControls               = GetDataByte(base+23+loop_index);
        AddEntry( 23+loop_index, "bmControls 0", bmControls, 2, "Bitmap of supported controls", 0); 
        AddFieldBreak();
    }
    
    if (bControlSize > 1)
    {
        bmControls               = GetDataByte(base+24+loop_index);
        AddEntry( 24+loop_index, "bmControls 1", bmControls, 2, "Unable to decode", 0); 
        AddFieldBreak();
    }
    
    
    if (bControlSize > 2)
    {
        bmControls               = GetDataByte(base+25+loop_index);
        AddEntry( 25+loop_index, "bmControls 2", bmControls, 2, "Unable to decode", 0); 
        AddFieldBreak();
    }
    
    if (bControlSize > 3)
    {
        bmControls               = GetDataByte(base+26+loop_index);
        AddEntry( 26+loop_index, "bmControls 3", bmControls, 2, "Unable to decode", 0); 
        AddFieldBreak();
    }
    
    iExtension       = GetDataByte(base+23+loop_index+bControlSize);
    AddEntry( 23+loop_index+bControlSize, "iExtension", iExtension, 2, "The index of the", 0); 
    AddDescriptionOnly("Extension Unit string");
    AddDescriptionOnly(Format ("descriptor is %d", iExtension));
    AddFieldBreak();
    
    return 1; #decoded it
}

VC_ENCODING_UNITVC_ENCODING_UNIT()
{
    base = Base;

    bUnitID                = GetDataByte(base+3);
    bSourceID              = GetDataByte(base+4);
    iEncoding              = GetDataByte(base+5);
    bControlSize           = GetDataByte(base+6);
    bmControls             = GetData3Bytes(base+7);
    bmControlsRuntime      = GetData3Bytes(base+10);
	
	AddEntry( 3, "bUnitID", bUnitID, 2, "A non-zero constant that uniquely identifies the Unit within the video function", 0); 
    AddFieldBreak();
	
	AddEntry( 4, "bSourceID", bSourceID, 2, "ID of the Unit or Terminal to which this Unit is connected", 0); 
    AddFieldBreak();

	AddEntry( 5, "iEncoding", iEncoding, 2, "Index of a string descriptor that describes this encoding unit", 0); 
    AddFieldBreak();	
	
	AddEntry( 6, "bControlSize", bControlSize, 2, "Size, in bytes, of the bmControls and bmControlsRuntime fields: The value must be 3", 0); 
    AddFieldBreak();
	
    AddEntry( 7, "bmControls", bmControls, 8, "A bit set to 1 indicates that the specified control is supported for initialization", 0);#?2
    AddDescriptionOnly(Format("<br>D0: Select Layer %d"                                        ,((bmControls >> 0) & 0x01)));
    AddDescriptionOnly(Format("<br>D1: Profile and Toolset %d"                                 ,((bmControls >> 1) & 0x01)));
    AddDescriptionOnly(Format("<br>D2: Video Resolution %d"                                    ,((bmControls >> 2) & 0x01)));
    AddDescriptionOnly(Format("<br>D3: Minimum Frame Interval %d"                              ,((bmControls >> 3) & 0x01)));
    AddDescriptionOnly(Format("<br>D4: Slice Mode %d"                                          ,((bmControls >> 4) & 0x01)));
    AddDescriptionOnly(Format("<br>D5: Rate Control Mode %d"                                   ,((bmControls >> 5) & 0x01)));
	AddDescriptionOnly(Format("<br>D6: Average Bit Rate %d"                                    ,((bmControls >> 6) & 0x01)));
	AddDescriptionOnly(Format("<br>D7: CPB Size %d"                                            ,((bmControls >> 7) & 0x01)));
	AddDescriptionOnly(Format("<br>D8: Peak Bit Rate %d"                                       ,((bmControls >> 8) & 0x01)));
	AddDescriptionOnly(Format("<br>D9: Quantization Parameter %d"                              ,((bmControls >> 9) & 0x01)));
	AddDescriptionOnly(Format("<br>D10: Synchronization and Long-Term Reference Frame %d"      ,((bmControls >> 10) & 0x01)));
	AddDescriptionOnly(Format("<br>D11: Long-Term Buffer %d"                                   ,((bmControls >> 11) & 0x01)));
	AddDescriptionOnly(Format("<br>D12: Picture Long-Term Reference %d"                        ,((bmControls >> 12) & 0x01)));
	AddDescriptionOnly(Format("<br>D13: LTR Validation %d"                                     ,((bmControls >> 13) & 0x01)));
	AddDescriptionOnly(Format("<br>D14: Level IDC %d"                                          ,((bmControls >> 14) & 0x01)));
	AddDescriptionOnly(Format("<br>D15: SEI Message %d"                                        ,((bmControls >> 15) & 0x01)));
	AddDescriptionOnly(Format("<br>D16: QP Range %d"                                           ,((bmControls >> 16) & 0x01)));
	AddDescriptionOnly(Format("<br>D17: Priority ID %d"                                        ,((bmControls >> 17) & 0x01)));
	AddDescriptionOnly(Format("<br>D18: Start or Stop Layer/View %d"                           ,((bmControls >> 18) & 0x01)));
	AddDescriptionOnly(Format("<br>D19: Error Resiliency %d"                                   ,((bmControls >> 19) & 0x01)));
	AddDescriptionOnly(Format("<br>D23..D20: Reserved; set to zero %d"                         ,((bmControls >> 20) & 0x0F)));
    AddFieldBreak();	
	
	AddEntry( 10, "bmControlsRuntime", bmControlsRuntime, 8, "A bit set to 1 indicates that the mentioned control is supported during runtime", 0);
    AddDescriptionOnly(Format("<br>D0: Select Layer %d"                                        ,((bmControlsRuntime >> 0) & 0x01)));
    AddDescriptionOnly(Format("<br>D1: Profile and Toolset %d"                                 ,((bmControlsRuntime >> 1) & 0x01)));
    AddDescriptionOnly(Format("<br>D2: Video Resolution %d"                                    ,((bmControlsRuntime >> 2) & 0x01)));
    AddDescriptionOnly(Format("<br>D3: Minimum Frame Interval %d"                              ,((bmControlsRuntime >> 3) & 0x01)));
    AddDescriptionOnly(Format("<br>D4: Slice Mode %d"                                          ,((bmControlsRuntime >> 4) & 0x01)));
    AddDescriptionOnly(Format("<br>D5: Rate Control Mode %d"                                   ,((bmControlsRuntime >> 5) & 0x01)));
	AddDescriptionOnly(Format("<br>D6: Average Bit Rate %d"                                    ,((bmControlsRuntime >> 6) & 0x01)));
	AddDescriptionOnly(Format("<br>D7: CPB Size %d"                                            ,((bmControlsRuntime >> 7) & 0x01)));
	AddDescriptionOnly(Format("<br>D8: Peak Bit Rate %d"                                       ,((bmControlsRuntime >> 8) & 0x01)));
	AddDescriptionOnly(Format("<br>D9: Quantization Parameter %d"                              ,((bmControlsRuntime >> 9) & 0x01)));
	AddDescriptionOnly(Format("<br>D10: Synchronization and Long-Term Reference Frame %d"      ,((bmControlsRuntime >> 10) & 0x01)));
	AddDescriptionOnly(Format("<br>D11: Long-Term Buffer %d"                                   ,((bmControlsRuntime >> 11) & 0x01)));
	AddDescriptionOnly(Format("<br>D12: Picture Long-Term Reference %d"                        ,((bmControlsRuntime >> 12) & 0x01)));
	AddDescriptionOnly(Format("<br>D13: LTRValidation %d"                                      ,((bmControlsRuntime >> 13) & 0x01)));
	AddDescriptionOnly(Format("<br>D14: Level IDC %d"                                          ,((bmControlsRuntime >> 14) & 0x01)));
	AddDescriptionOnly(Format("<br>D15: SEI Message %d"                                        ,((bmControlsRuntime >> 15) & 0x01)));
	AddDescriptionOnly(Format("<br>D16: QP Range %d"                                           ,((bmControlsRuntime >> 16) & 0x01)));
	AddDescriptionOnly(Format("<br>D17: Priority ID %d"                                        ,((bmControlsRuntime >> 17) & 0x01)));
	AddDescriptionOnly(Format("<br>D18: Start or Stop Layer/View %d"                           ,((bmControlsRuntime >> 18) & 0x01)));
	AddDescriptionOnly(Format("<br>D19: Error Resiliency %d"                                   ,((bmControlsRuntime >> 19) & 0x01)));
	AddDescriptionOnly(Format("<br>D23..D20: Reserved; set to zero %d"                         ,((bmControlsRuntime >> 20) & 0x0F)));
    AddFieldBreak();	
}

				
VS_UNDEFINED()
{
    return 0; #decoded it
}


VS_INPUT_HEADER()
{
    base = Base;

    bNumFormats         = GetDataByte(base+3);
    wTotalLength        = GetDataWord(base+4);
    bEndpointAddress    = GetDataByte(base+6);
    bmInfo              = GetDataByte(base+7);
    bTerminalLink       = GetDataByte(base+8);
    bStillCaptureMethod = GetDataByte(base+9);
    bTriggerSupport     = GetDataByte(base+10);
    bTriggerUsage       = GetDataByte(base+11);
    bControlSize        = GetDataByte(base+12);    
         
    AddEntry( 3, "bNumFormats", bNumFormats, 2, "Number of video payload", 0); 
    AddDescriptionOnly( "format descriptors following" );
    AddDescriptionOnly( "for this interface (excluding" );
    AddDescriptionOnly( Format( "video frame descriptors) is %d", bNumFormats) );
    AddFieldBreak();

    AddEntry( 4, "wTotalLength", wTotalLength, 4, "Total number of bytes returned" , 0);
    AddDescriptionOnly(                         "for the class-specific" );
    AddDescriptionOnly(                         "VideoStreaming interface" );
    AddDescriptionOnly(                         "descriptors including this");
    AddDescriptionOnly( Format( " header descriptor is %d", bNumFormats) );
    AddFieldBreak();
    
    if (bEndpointAddress & 0x80)
    {
        AddEntry( 6, "bEndpointAddress", bEndpointAddress, 2, Format("Endpoint %d IN", bEndpointAddress & 0xF) , 0);
    }
    else
    {
        AddEntry( 6, "bEndpointAddress", bEndpointAddress, 2, Format("Endpoint %d OUT", bEndpointAddress & 0xF), 0);
    }
    AddFieldBreak();
         
    AddEntry( 7, "bmInfo", bmInfo, 2, "Video Streaming", 0); 
    AddDescriptionOnly("interface Capabilities:");
    AddDescriptionOnly("the video endpoint of ");
    AddDescriptionOnly("this interface is");
    AddDescriptionOnly(Format("connected is %d", bmInfo));
    AddFieldBreak();
    
    AddEntry( 8, "bTerminalLink", bTerminalLink, 2, "The terminal ID of the", 0); 
    AddDescriptionOnly("Output Terminal to which");
    AddDescriptionOnly("the video endpoint of ");
    AddDescriptionOnly("this interface is");
    AddDescriptionOnly(Format("connected is %d", bTerminalLink));
    AddFieldBreak();
    
    if (bStillCaptureMethod)
    {
        AddEntry( 9, "bStillCaptureMethod", bStillCaptureMethod, 2, "Still image capture", 0); 
        AddDescriptionOnly(Format("method is Method %d", bStillCaptureMethod));
    }
    else
    {
        AddEntry( 9, "bStillCaptureMethod", bStillCaptureMethod, 2, "NO Still image capture", 0); 
    }    
    AddFieldBreak();
    
    if (bTriggerSupport)
    {
        AddEntry( 10, "bTriggerSupport", bTriggerSupport, 2, "Trigger Supported", 0); 
    }
    else
    {
        AddEntry( 10, "bTriggerSupport", bTriggerSupport, 2, "Trigger NOT Supported", 0); 
    }    
    AddFieldBreak();
        
    AddEntry( 11, "bTriggerUsage", bTriggerUsage, 2, "SW action upon trigger:", 0); 
    if (bTriggerUsage)
    {
        AddDescriptionOnly("1: General Purpose Button Event");
    }
    else
    {
        AddDescriptionOnly("0: Initiate still image capture");
    }
    AddFieldBreak();
    
    AddEntry( 12, "bControlSize", bControlSize, 2, "The number of ", 0); 
    AddDescriptionOnly(Format ("bmControl bytes is %d.", bControlSize));
    AddFieldBreak();
    
        
    loop_count_down = bNumFormats;
    loop_index = 0;
    while (loop_count_down > 0)
    {
        inner_loop_count_down = bControlSize;
        inner_loop_index = 0;
        
        while (inner_loop_count_down > 0)
        {
            
            bmControls               = GetDataByte(base+13+(loop_index*bControlSize)+inner_loop_index);
            if (inner_loop_index == 0)
            {
                AddEntry( 13+(loop_index*bControlSize)+inner_loop_index, FormatEx ("Fmt%d bmControls(%d)",loop_index+1, inner_loop_index+1 ), bmControls, 2, "Control Bitmap: ", 0); 
                AddDescriptionOnly(Format ("<br>D0:  Key frame rate          %d", ((bmControls >> 0) & 0x01)));
                AddDescriptionOnly(Format ("<br>D1:  P frame rate            %d", ((bmControls >> 1) & 0x01)));
                AddDescriptionOnly(Format ("<br>D2:  Compression quality     %d", ((bmControls >> 2) & 0x01)));
                AddDescriptionOnly(Format ("<br>D3:  Compression window size %d", ((bmControls >> 3) & 0x01)));
                AddDescriptionOnly(Format ("<br>D4:  Generate Key Frame      %d", ((bmControls >> 4) & 0x01)));
                AddDescriptionOnly(Format ("<br>D5:  Update Frame Segment    %d", ((bmControls >> 5) & 0x01)));
            }
            else
            {
                AddEntry( 13+(loop_index*bControlSize)+inner_loop_index, FormatEx ("Fmt%d bmControls(%d)",loop_index+1, inner_loop_index+1 ), bmControls, 2, "Not decodable", 0); 
            }
            AddFieldBreak();
            inner_loop_count_down--;
            inner_loop_index++;
        }
        loop_count_down--;
        loop_index++;
    }
    return 1; #decoded it
}
    
VS_OUTPUT_HEADER()
{
    base = Base;

    bNumFormats      = GetDataByte(base+3);
    wTotalLength     = GetDataWord(base+4);
    bEndpointAddress = GetDataByte(base+6);
    bTerminalLink    = GetDataByte(base+7);    
    
         
    AddEntry( 3, "bNumFormats", bNumFormats, 2, "Number of video payload", 0); 
    AddDescriptionOnly( "format descriptors following" );
    AddDescriptionOnly( "for this interface (excluding" );
    AddDescriptionOnly( Format( "video frame descriptors) is %d", bNumFormats) );
    AddFieldBreak();

    AddEntry( 4, "wTotalLength", wTotalLength, 4, "Total number of bytes returned" , 0);
    AddDescriptionOnly(                         "for the class-specific" );
    AddDescriptionOnly(                         "VideoStreaming interface" );
    AddDescriptionOnly(                         "descriptors including this");
    AddDescriptionOnly( Format( " header descriptor is %d", bNumFormats) );
    AddFieldBreak();
    
    if (bEndpointAddress & 0x80)
    {
        AddEntry( 6, "bEndpointAddress", bEndpointAddress, 2, Format("Endpoint %d IN", bEndpointAddress & 0xF) , 0);
    }
    else
    {
        AddEntry( 6, "bEndpointAddress", bEndpointAddress, 2, Format("Endpoint %d OUT", bEndpointAddress & 0xF), 0);
    }
    AddFieldBreak();
         
    AddEntry( 7, "bTerminalLink", bTerminalLink, 2, "The terminal ID of the", 0); 
    AddDescriptionOnly("Input Terminal to which");
    AddDescriptionOnly("the video endpoint of ");
    AddDescriptionOnly("this interface is");
    AddDescriptionOnly(Format("connected is %d", bTerminalLink));
    AddFieldBreak();
    
    return 1; # decoded it
}

VS_STILL_IMAGE_FRAME()
{
    base = Base;

    bEndpointAddress      = GetDataByte(base+3);
    bNumImageSizePatterns = GetDataByte(base+4);
    
    if (bEndpointAddress & 0x80)
    {
        AddEntry( 3, "bEndpointAddress", bEndpointAddress, 2, Format("Endpoint %d IN", bEndpointAddress & 0xF) , 0);
    }
    else
    {
        AddEntry( 3, "bEndpointAddress", bEndpointAddress, 2, Format("Endpoint %d OUT", bEndpointAddress & 0xF), 0);
    }
    AddFieldBreak();
          
    
    AddEntry( 4, "bNumImageSizePatterns", bNumImageSizePatterns, 2, "The number of Image", 0); 
    AddDescriptionOnly(Format ("Size patterns is %d.", bNumImageSizePatterns));
    AddFieldBreak();
    
        
    loop_count_down = bNumImageSizePatterns;
    loop_index = 0;
    while (loop_count_down > 0)
    {
       wWidth       = GetDataWord(base+5+(loop_index*4));
       AddEntry( 5+(loop_index*4), Format ( "wWidth(%d)", (loop_index+1)), wWidth, 2, "Width of the Still Image", 0); 
       AddDescriptionOnly(FormatEx ("In pattern %d is %d", loop_index+1, wWidth));
       AddFieldBreak();
       wHight       = GetDataWord(base+7+(loop_index*4));
       AddEntry( 7+(loop_index*4), Format ( "wHight(%d)", (loop_index+1)), wHight, 2, "Height of the Still Image", 0); 
       AddDescriptionOnly(FormatEx ("In pattern %d is %d", loop_index+1, wHight));
       AddFieldBreak();
       loop_count_down--;
       loop_index++;
    }
    new_offset = 5+(loop_index*4);    
    AddEntry( new_offset, "bNumCompressionPatterns", bNumCompressionPatterns, 2, "The number of Compression", 0); 
    AddDescriptionOnly(Format ("pattern of this format is %d.", bNumCompressionPatterns));
    AddFieldBreak();
    
    loop_count_down = bNumCompressionPatterns;
    loop_index = 0;
    while (loop_count_down > 0)
    {
       bCompression       = GetDataWord(base+new_offset+loop_index);
       AddEntry( new_offset+loop_index, Format ( "bCompression(%d)", (loop_index+1)), bCompression, 2, Format("Compression val: %d", bCompression), 0); 
       AddFieldBreak();
       loop_count_down--;
       loop_index++;
    }
    return 1; #decoded it
}



VS_FORMAT_UNCOMPRESSED()
{
    base = Base;

    bFormatIndex          = GetDataByte(base+3);
    bNumFrameDescriptors  = GetDataByte(base+4);
LittleEndian = 0;    
    guidFormat1           = GetDataLong(base+5);
    guidFormat2           = GetDataLong(base+9);
    guidFormat3           = GetDataLong(base+13);
    guidFormat4           = GetDataLong(base+17);
LittleEndian = 1;
  
    bBitsPerPixel         = GetDataByte(base+21);
    bDefaultFrameIndex    = GetDataByte(base+22);
    bAspectRatioX         = GetDataByte(base+23);
    bAspectRatioY         = GetDataByte(base+24);
    bmInterlaceFlags      = GetDataByte(base+25);
    bCopyProtect          = GetDataByte(base+26); 

    AddEntry( 3, "bFormatIndex", bFormatIndex, 2, "Index of this format descriptor", 0); 
    AddFieldBreak();
 
    AddEntry( 4, "bNumFrameDescriptors", bNumFrameDescriptors, 2, "Number of frame descriptors following that correspond to this format", 0); 
    AddFieldBreak();

    guidFormatS = FormatEx("%04X-%04X-%04X-%04X",guidFormat1, guidFormat2, guidFormat3, guidFormat4);
    AddEntry( 5, "guidFormat", guidFormat1, 8, "Globally Unique Identifier used to identify stream-encoding format\n" + guidFormatS, 0, 0, guidFormatS); 
    AddFieldBreak();

    AddEntry( 21, "bBitsPerPixel", bBitsPerPixel, 2, "Number of bits per pixel used to specify color in the decoded video frame", 0); 
   
   AddFieldBreak();

    AddEntry( 22, "bDefaultFrameIndex", bDefaultFrameIndex, 2, "Optimum Frame Index (used to select resolution) for this stream", 0); 
    AddFieldBreak();

    AddEntry( 23, "bAspectRatioX", bAspectRatioX, 2, "The X dimension of the picture aspect ratio", 0); 
    AddFieldBreak();

    AddEntry( 24, "bAspectRatioY", bAspectRatioY, 2, "The Y dimension of the picture aspect ratio", 0); 
    AddFieldBreak();

    AddEntry( 25, "bmInterlaceFlags", bmInterlaceFlags, 2, "Specifies interlace information", 0);
    AddDescriptionOnly(Format("<br>D0: Interlaced stream or variable %d"  ,((bmInterlaceFlags >> 0) & 0x01)));
    AddDescriptionOnly(Format("<br>D1: Fields per frame %d"               ,((bmInterlaceFlags >> 1) & 0x01)));
    AddDescriptionOnly(Format("<br>D2: Field 1 first %d"                  ,((bmInterlaceFlags >> 2) & 0x01)));
    AddDescriptionOnly(Format("<br>D3: Reserved %d"                       ,((bmInterlaceFlags >> 3) & 0x01)));
    AddDescriptionOnly(Format("<br>D5..4: Field pattern %d"               ,((bmInterlaceFlags >> 4) & 0x03)));
    if(VC_Version == 0x0100)
    {
        AddDescriptionOnly(Format("<br>D7..6: Dispaly Mode %d"            ,((bmInterlaceFlags >> 6) & 0x03)));
    }
    else if(VC_Version == 0x0110)
    {    
        AddDescriptionOnly(Format("<br>D7..6: Reserved. %d"              ,((bmInterlaceFlags >> 6) & 0x03)));
    }
    else if(VC_Version == 0x0150)
    {
        AddDescriptionOnly(Format("<br>D7..6: Reserved.Do not use. %d"   ,((bmInterlaceFlags >> 6) & 0x03))); 
    }
	else
	{
		#unknown VC
	}
    AddFieldBreak();

    AddEntry( 26, "bCopyProtect", bCopyProtect, 2, "Specifies whether duplication of the video stream is restricted", 0); 
    AddDescriptionOnly(Format("D0: video stream is restricted %d",(bCopyProtect & 0x01)));
    AddFieldBreak();
     
    return 1; #decoded it
}

VS_FRAME_UNCOMPRESSED()
{
    base = Base;

    bFrameIndex              = GetDataByte(base+3);
    bmCapabilities           = GetDataByte(base+4);
    wWidth                   = GetDataWord(base+5);
    wHeight                  = GetDataWord(base+7);
    dwMinBitRate             = GetDataLong(base+9);
    dwMaxBitRate             = GetDataLong(base+13);
    dwMaxVideoFrameBufferSize= GetDataLong(base+17);
    dwDefaultFrameInterval   = GetDataLong(base+21);
    bFrameIntervalType       = GetDataByte(base+25);

    AddEntry( 3, "bFrameIndex", bFrameIndex, 2, "Index of this frame descriptor", 0); 
    AddFieldBreak();

    AddEntry( 4, "bmCapabilities", bmCapabilities, 2, "", 0);
    AddDescriptionOnly(Format("<br>D0: Still image supported %d",((bmCapabilities >> 0) & 0x01))); 
     
    if(VC_Version == 0x0100)
    {
        AddDescriptionOnly(Format("<br>D7..1: Reserved %d"     , bmCapabilities >>1 )           ); 
    }
    else if(VC_Version == 0x0110)
    {
        AddDescriptionOnly(Format("<br>D1: Fixed frame-rate %d",((bmCapabilities >> 1) & 0x01)));
        AddDescriptionOnly(Format("<br>D7..2: Reserved %d"     , bmCapabilities >> 2 )         ); 
    }
    else
    {
        #unknown VC
    }
    AddFieldBreak();

    AddEntry( 5, "wWidth", wWidth, 4, "Width of decoded bitmap frame in pixels", 0); 
    AddFieldBreak();

    AddEntry( 7, "wHeight", wHeight, 4, "Height of decoded bitmap frame in pixels", 0); 
    AddFieldBreak();

    AddEntry( 9, "dwMinBitRate", dwMinBitRate, 8, "Specifies the minimum bit rate at the longest frame interval in units of bps at which the data can be transmitted", 0); 
    AddFieldBreak();

    AddEntry( 13, "dwMaxBitRate", dwMaxBitRate, 8, "Specifies the maximum bit rate at the shortest frame interval in units of bps at which the data can be transmitted", 0); 
    AddFieldBreak();

    AddEntry( 17, "dwMaxVideoFrameBufferSize", dwMaxVideoFrameBufferSize, 8, "Specifies the maximum number of bytes that the compressor will produce for a video frame or still image", 0); 
    AddFieldBreak();

    AddEntry( 21, "dwDefaultFrameInterval", dwDefaultFrameInterval, 8, "Specifies the frame interval the device would like to indicate for use as a default", 0); 
    AddFieldBreak();

    AddEntry( 25, "bFrameIntervalType", bFrameIntervalType, 2, "Indicates how the frame interval can be programmed.<br> 0: Continuous frame interval <br>1..255: The number of discrete frame", 0); 
    AddFieldBreak();
    
    if(bFrameIntervalType == 0)
    {
        dwMinFrameInterval  = GetDataLong(base+26);
        dwMaxFrameInterval  = GetDataLong(base+30);
        dwFrameIntervalStep = GetDataLong(base+34);

        AddEntry( 26, "dwMinFrameInterval", dwMinFrameInterval, 8, "Shortest frame interval supported (at highest frame rate), in 100 ns units", 0); 
        AddFieldBreak();

        AddEntry( 30, "dwMaxFrameInterval", dwMaxFrameInterval, 8, "Longest frame interval supported (at lowest frame rate), in 100 ns units", 0); 
        AddFieldBreak();

        AddEntry( 34, "dwFrameIntervalStep", dwFrameIntervalStep, 8, "Indicates granularity of frame interval range, in 100 ns units", 0); 
        AddFieldBreak();
    }
    else
    {
        for(FrameInterval = 1; FrameInterval <= bFrameIntervalType; FrameInterval = FrameInterval + 1 )
        {
            dwCurFrameInterval = GetDataLong(base+26+((FrameInterval - 1) * 4));
            dwFrameIntervalS  = Format("dwFrameInterval(%d)", FrameInterval);
            
            if(FrameInterval == bFrameIntervalType)
                FrameIntervalDesc = "Longest frame interval supported (at lowest frame rate), in 100 ns units";
            else
               FrameIntervalDesc = "Shortest frame interval supported (at highest frame rate), in 100 ns units";
            
            AddEntry( 26+((FrameInterval - 1) * 4), dwFrameIntervalS, dwCurFrameInterval, 8, FrameIntervalDesc, 0); 
            AddFieldBreak();
        }
    }
    return 1; # decoded it
}

VS_FORMAT_MJPEG()
{
    base = Base;

    bFormatIndex             = GetDataByte(base+3);
    bNumFrameDescriptors     = GetDataByte(base+4);
    bmFlags                  = GetDataByte(base+5);
    bDefaultFrameIndex       = GetDataByte(base+6);   
    bAspectRatioX            = GetDataByte(base+7);
    bAspectRatioY            = GetDataByte(base+8);
    bmInterlaceFlags         = GetDataByte(base+9);
    bCopyProtect             = GetDataByte(base+10);

    AddEntry( 3, "bFormatIndex", bFormatIndex, 2, "Index of this Format Descriptor", 0); 
    AddFieldBreak();
    
    AddEntry( 4, "bNumFrameDescriptors", bNumFrameDescriptors, 2, "Number of Frame Descriptors following that correspond to this format", 0); 
    AddFieldBreak();

    AddEntry( 5, "bmFlags", bmFlags, 2, "Specifies characteristics of this format", 0);
    AddDescriptionOnly(Format("D0: FixedSizeSamples %d",((bmFlags >> 0) & 0x01))); 
    AddFieldBreak();

    AddEntry( 6, "bDefaultFrameIndex", bDefaultFrameIndex, 2, "Optimum Frame Index (used to select resolution) for this stream", 0); 
    AddFieldBreak();

    AddEntry( 7, "bAspectRatioX", bAspectRatioX, 2, "The X dimension of the picture aspect ratio", 0); 
    AddFieldBreak();

    AddEntry( 8, "bAspectRatioY", bAspectRatioY, 2, "The Y dimension of the picture aspect ratio", 0); 
    AddFieldBreak();

    AddEntry( 9, "bmInterlaceFlags", bmInterlaceFlags, 2, "Specifies interlace information", 0); 
    AddDescriptionOnly(Format("<br>D0: Interlaced stream or variable %d",((bmInterlaceFlags >> 0) & 0x01)));
    AddDescriptionOnly(Format("<br>D1: Fields per frame %d"             ,((bmInterlaceFlags >> 1) & 0x01)));
    AddDescriptionOnly(Format("<br>D2: Field 1 first %d"                ,((bmInterlaceFlags >> 2) & 0x01)));
    AddDescriptionOnly(Format("<br>D3: Reserved %d"                     ,((bmInterlaceFlags >> 3) & 0x01)));
    AddDescriptionOnly(Format("<br>D5..4: Field pattern %d"             ,((bmInterlaceFlags >> 4) & 0x03)));
    if(VC_Version == 0x0100)
    {
        AddDescriptionOnly(Format("<br>D7..6: Dispaly Mode %d"               ,((bmInterlaceFlags >> 6) & 0x03)));
        
    }
    else if(VC_Version == 0x0110)
    {    
        AddDescriptionOnly(Format("<br>D7..6: Reserved. %d"                 ,((bmInterlaceFlags >> 6) & 0x03)));
    }
    else
    {
        #unknown VC
    }
    AddFieldBreak();

    AddEntry( 10, "bCopyProtect", bCopyProtect, 2, "Specifies if duplication of the video stream should be restricted", 0);
    AddDescriptionOnly(Format("D0: video stream is restricted %d",((bCopyProtect >> 0) & 0x01))); 
    AddFieldBreak();

    return 1; # decoded it
}

VS_FRAME_MJPEG()
{
    base = Base;

    bFrameIndex              = GetDataByte(base+3);
    bmCapabilities           = GetDataByte(base+4);
    wWidth                   = GetDataWord(base+5);
    wHeight                  = GetDataWord(base+7);
    dwMinBitRate             = GetDataLong(base+9);
    dwMaxBitRate             = GetDataLong(base+13);
    dwMaxVideoFrameBufferSize= GetDataLong(base+17);
    dwDefaultFrameInterval   = GetDataLong(base+21);
    bFrameIntervalType       = GetDataByte(base+25);

    AddEntry( 3, "bFrameIndex", bFrameIndex, 2, "Index of this frame descriptor", 0); 
    AddFieldBreak();

    AddEntry( 4, "bmCapabilities", bmCapabilities, 2, "", 0);
    AddDescriptionOnly(Format("<br>D0: Still image supported %d",((bmCapabilities >> 0) & 0x01))); 
     
    if(VC_Version == 0x0100)
    {
        AddDescriptionOnly(Format("<br>D7..1: Reserved %d"     , bmCapabilities >>1 )           ); 
    }
    else if(VC_Version == 0x0110)
    {
        AddDescriptionOnly(Format("<br>D1: Fixed frame-rate %d",((bmCapabilities >> 1) & 0x01)));
        AddDescriptionOnly(Format("<br>D7..2: Reserved %d"     , bmCapabilities >> 2 )         ); 
    }
    else
    {
        #unknown VC version
    }
    AddFieldBreak();

    AddEntry( 5, "wWidth", wWidth, 4, "Width of decoded bitmap frame in pixels", 0); 
    AddFieldBreak();

    AddEntry( 7, "wHeight", wHeight, 4, "Height of decoded bitmap frame in pixels", 0); 
    AddFieldBreak();

    AddEntry( 9, "dwMinBitRate", dwMinBitRate, 8, "Specifies the minimum bit rate at the longest frame interval in units of bps at which the data can be transmitted", 0); 
    AddFieldBreak();

    AddEntry( 13, "dwMaxBitRate", dwMaxBitRate, 8, "Specifies the maximum bit rate at the shortest frame interval in units of bps at which the data can be transmitted", 0); 
    AddFieldBreak();

    AddEntry( 17, "dwMaxVideoFrameBufferSize", dwMaxVideoFrameBufferSize, 8, "Specifies the maximum number of bytes that the compressor will produce for a video frame or still image", 0); 
    AddFieldBreak();

    AddEntry( 21, "dwDefaultFrameInterval", dwDefaultFrameInterval, 8, "Specifies the frame interval the device would like to indicate for use as a default", 0); 
    AddFieldBreak();

    AddEntry( 25, "bFrameIntervalType", bFrameIntervalType, 2, "Indicates how the frame interval can be programmed. 0: Continuous frame interval 1..255: The number of discrete frame", 0); 
    AddFieldBreak();
    
    if(bFrameIntervalType == 0)
    {
        dwMinFrameInterval  = GetDataLong(base+26);
        dwMaxFrameInterval  = GetDataLong(base+30);
        dwFrameIntervalStep = GetDataLong(base+34);

        AddEntry( 26, "dwMinFrameInterval", dwMinFrameInterval, 8, "Shortest frame interval supported (at highest frame rate), in 100 ns units", 0); 
        AddFieldBreak();

        AddEntry( 30, "dwMaxFrameInterval", dwMaxFrameInterval, 8, "Longest frame interval supported (at lowest frame rate), in 100 ns units", 0); 
        AddFieldBreak();

        AddEntry( 34, "dwFrameIntervalStep", dwFrameIntervalStep, 8, "Indicates granularity of frame interval range, in 100 ns units", 0); 
        AddFieldBreak();
    }
    else
    {
        for(FrameInterval = 1; FrameInterval <= bFrameIntervalType; FrameInterval = FrameInterval + 1 )
        {
            dwCurFrameInterval = GetDataLong(base+26+((FrameInterval - 1) * 4));
            dwFrameIntervalS  = Format("dwFrameInterval(%d)", FrameInterval);
            
            if(FrameInterval == bFrameIntervalType)
                FrameIntervalDesc = "Longest frame interval supported (at lowest frame rate), in 100 ns units";
            else
               FrameIntervalDesc = "Shortest frame interval supported (at highest frame rate), in 100 ns units";
            
            AddEntry( 26+((FrameInterval - 1) * 4), dwFrameIntervalS, dwCurFrameInterval, 8, FrameIntervalDesc, 0); 
            AddFieldBreak();
        }
    }

    return 1; # decoded it
}

VS_FORMAT_MPEG1()
{
    base = Base;
    
    if(VC_Version == 0x0110)
    {
        #This descriptor is reserved in VC verion 1.1
    }
    else if(VC_Version == 0x0100)
    {
        bFormatIndex   = GetDataByte(base+3); 
        wPacketLength  = GetDataWord(base+4); 
        wPackLength    = GetDataWord(base+6); 
        bPackdataType  = GetDataByte(base+8); 

        AddEntry( 3, "bFormatIndex", bFormatIndex, 2, "Index of this format descriptor", 0); 
        AddFieldBreak();
        
        AddEntry( 4, "wPacketLength", wPacketLength, 4, "Indicates the fixed size of the individual data samples, in bytes", 0); 
        AddFieldBreak();
 
        AddEntry( 6, "wPackLength", wPackLength, 4, "Indicates the lengths of the MPEG1 system stream pack data size", 0); 
        AddFieldBreak();

        AddEntry( 8, "bPackdataType", bPackdataType, 2, "", 0); 
        AddDescriptionOnly(Format("<br>D0: The pack size %d",((bPackdataType >> 1) & 0x01)));
        AddDescriptionOnly(Format("<br>D7..1: Reserved %d"  , bPackdataType >> 2 )         ); 
        AddFieldBreak();
        
        return 1; #decoded it
    }
    return 0; # did not decode it
}

VS_FORMAT_MPEG2PS()
{
    base = Base;
    
    if(VC_Version == 0x0110)
    {
        #This descriptor is reserved in VC verion 1.1
    }
    else if(VC_Version == 0x0100)
    {
        bFormatIndex   = GetDataByte(base+3); 
        wPacketLength  = GetDataWord(base+4); 
        wPackLength    = GetDataWord(base+6); 
        bPackdataType  = GetDataByte(base+8); 

        AddEntry( 3, "bFormatIndex", bFormatIndex, 2, "Index of this format descriptor", 0); 
        AddFieldBreak();
        
        AddEntry( 4, "wPacketLength", wPacketLength, 4, "Indicates the fixed size of the individual data samples, in bytes", 0); 
        AddFieldBreak();
 
        AddEntry( 6, "wPackLength", wPackLength, 4, "Indicates the lengths of the MPEG2 PS pack data size in bytes", 0); 
        AddFieldBreak();

        AddEntry( 8, "bPackdataType", bPackdataType, 2, "", 0); 
        AddDescriptionOnly(Format("<br>D0: The pack size %d",((bPackdataType >> 1) & 0x01)));
        AddDescriptionOnly(Format("<br>D7..1: Reserved %d"  , bPackdataType >> 2 )         ); 
        AddFieldBreak();
        
        return 1; #decoded it
    }
    return 0; # did not decode it
}

VS_FORMAT_MPEG2TS()
{
    base = Base;

    bFormatIndex     = GetDataByte(base+3); 
    bDataOffset      = GetDataByte(base+4); 
    bPacketLength    = GetDataByte(base+5); 
    bStrideLength    = GetDataByte(base+6);

    AddEntry( 3, "bFormatIndex", bFormatIndex, 2, "Index of this format descriptor", 0); 
    AddFieldBreak();

    AddEntry( 4, "bDataOffset", bDataOffset, 2, "Offset to TSP packet within MPEG-2 TS transport stride, in bytes", 0); 
    AddFieldBreak();

    AddEntry( 5, "bPacketLength", bPacketLength, 2, "Length of TSP packet, in bytes", 0); 
    AddFieldBreak();

    AddEntry( 6, "bStrideLength", bStrideLength, 2, "Length of MPEG-2 TS transport stride", 0); 
    AddFieldBreak();

    if(VC_Version == 0x0110)
    {
     LittleEndian = 0;    
        guidStrideFormat1  = GetDataLong(base+7);
        guidStrideFormat2  = GetDataLong(base+11);
        guidStrideFormat3  = GetDataLong(base+15);
        guidStrideFormat4  = GetDataLong(base+19);
     LittleEndian = 1;
        guidStrideFormatS = FormatEx("%04X-%04X-%04X-%04X",guidStrideFormat1, guidStrideFormat2, guidStrideFormat3, guidStrideFormat4);
        AddEntry( 7, "guidStrideFormat", guidStrideFormat1, 8, "A Globally Unique Identifier indicating the format of the stride data (if any).\n" + guidStrideFormatS, 0, 0, guidStrideFormatS); 
        AddFieldBreak();
    }
   
   return 1; # decoded it
}

VS_FORMAT_MPEG4SL()
{
     base = Base;
    
    if(VC_Version == 0x0110)
    {
        #This descriptor is reserved in VC verion 1.1
    }
    else if(VC_Version == 0x0100)
    {
        bFormatIndex                    = GetDataByte(base+3);
        bInitialObjectDescriptorLength  = GetDataByte(base+4);
 
        AddEntry( 3, "bFormatIndex", bFormatIndex, 2, "Index of format descriptor", 0); 
        AddFieldBreak();

        AddEntry( 4, "bInitialObjectDescriptorLength", bInitialObjectDescriptorLength, 2, "Size of baInitialObjectDescriptor in bytes", 0); 
        AddFieldBreak();

        for(bInitialObjectDescCount = 1; bInitialObjectDescCount<= bInitialObjectDescriptorLength; bInitialObjectDescCount = bInitialObjectDescCount+ 1)
        {  
            baInitialObjectDescriptor = GetDataByte(base+5+(1*(bInitialObjectDescCount - 1)));
            AddEntry( base+5+(1*(bInitialObjectDescCount - 1)), "baInitialObjectDescriptor", baInitialObjectDescriptor, 2, "Instance of Initial Object Descriptor", 0); 
            AddFieldBreak();
        }
        
        newbase = base+ 5+ bInitialObjectDescriptorLength+ 1;
        
        bNumSystemStreams = GetDataByte(newbase);
        for(bNumSystemStreamsCount = 1; bNumSystemStreamsCount<= bNumSystemStreams; bNumSystemStreamsCount = bNumSystemStreamsCount +1)
        {
           bSystemStreamLength = GetDataByte(newbase+1);
           
           bNumsystemStreamCountS = Format("Size of bSystemStreams(%d),in bytes : %d", bNumSystemStreamsCount, bSystemStreamLength);
           AddEntry( newbase+1, "bSystemStreamLength", bSystemStreamLength, 2, bNumsystemStreamCountS, 0); 
           AddFieldBreak();

           for(bSystemStreamCount = 1 ;bSystemStreamCount<= bSystemStreamLength; bSystemStreamCount = bSystemStreamCount + 1)
           {
               bSystemStream       = GetDataByte(newbase+ 2+ (1*(bSystemStreamCount- 1)));
               
               bSystemStreamCountS = Format("Data of the %dth transmitted MPEG4_Mux Packet", bNumSystemStreamsCount);
               AddEntry( newbase+ 2+ (1*(bSystemStreamCount- 1)), "bSystemStream", bSystemStream, 2, bSystemStreamCountS, 0); 
               AddFieldBreak();
           } 
        }                    
        return 1; #decoded it
    } 
    return 0; # did not decode it
}

VS_FORMAT_DV()
{
    base = Base;
    bFormatIndex                = GetDataByte(base+3);
    dwMaxVideoFrameBufferSize   = GetDataLong(base+4);
    bFormatType                 = GetDataByte(base+8);
    
    AddEntry( 3, "bFormatIndex", bFormatIndex, 2, "Index of format descriptor", 0); 
    AddFieldBreak();

    AddEntry( 4, "dwMaxVideoFrameBufferSize", dwMaxVideoFrameBufferSize, 8, "Specifies the maximum size of a single DV frame, in bytes", 0); 
    AddFieldBreak();

    AddEntry( 8, "bFormatType", bFormatType, 2, "", 0); 
    AddDescriptionOnly(Format("<br>D7: %d"     ,((bFormatType >> 7) & 0x01))   );
    AddDescriptionOnly(Format("<br>D6..0: %d"  , bFormatType& 0x7F )         ); 
    AddFieldBreak();
  
    return 1; # decoded it
}

VS_FORMAT_FRAME_BASED()
{
    base = Base;

    bFormatIndex          = GetDataByte(base+3);
    bNumFrameDescriptors  = GetDataByte(base+4);
LittleEndian = 0;    
    guidFormat1           = GetDataLong(base+5);
    guidFormat2           = GetDataLong(base+9);
    guidFormat3           = GetDataLong(base+13);
    guidFormat4           = GetDataLong(base+17);
LittleEndian = 1;
  
    bBitsPerPixel         = GetDataByte(base+21);
    bDefaultFrameIndex    = GetDataByte(base+22);
    bAspectRatioX         = GetDataByte(base+23);
    bAspectRatioY         = GetDataByte(base+24);
    bmInterlaceFlags      = GetDataByte(base+25);
    bCopyProtect          = GetDataByte(base+26); 
    bVariableSize         = GetDataByte(base+27);
     
    AddEntry( 3, "bFormatIndex", bFormatIndex, 2, "Index of this format descriptor", 0); 
    AddFieldBreak();
 
    AddEntry( 4, "bNumFrameDescriptors", bNumFrameDescriptors, 2, "Number of frame descriptors following that correspond to this format", 0); 
    AddFieldBreak();

    guidFormatS = FormatEx("%04X-%04X-%04X-%04X",guidFormat1, guidFormat2, guidFormat3, guidFormat4);
    AddEntry( 5, "guidFormat", guidFormat1, 8, "Globally Unique Identifier used to identify stream-encoding format\n" + guidFormatS, 0, 0, guidFormatS); 
    AddFieldBreak();

    AddEntry( 21, "bBitsPerPixel", bBitsPerPixel, 2, "Number of bits per pixel used to specify color in the decoded video frame", 0); 
    AddFieldBreak();

    AddEntry( 22, "bDefaultFrameIndex", bDefaultFrameIndex, 2, "Optimum Frame Index (used to select resolution) for this stream", 0); 
    AddFieldBreak();

    AddEntry( 23, "bAspectRatioX", bAspectRatioX, 2, "The X dimension of the picture aspect ratio", 0); 
    AddFieldBreak();

    AddEntry( 24, "bAspectRatioY", bAspectRatioY, 2, "The Y dimension of the picture aspect ratio", 0); 
    AddFieldBreak();

    AddEntry( 25, "bmInterlaceFlags", bmInterlaceFlags, 2, "Specifies interlace information.", 0);
    AddDescriptionOnly(Format("<br>D0: Interlaced stream or variable %d",((bmInterlaceFlags >> 0) & 0x01)));
    AddDescriptionOnly(Format("<br>D1: Fields per frame %d"             ,((bmInterlaceFlags >> 1) & 0x01)));
    AddDescriptionOnly(Format("<br>D2: Field 1 first %d"                ,((bmInterlaceFlags >> 2) & 0x01)));
    AddDescriptionOnly(Format("<br>D3: Reserved %d"                     ,((bmInterlaceFlags >> 3) & 0x01)));
    AddDescriptionOnly(Format("<br>D5..4: Field pattern %d"             ,((bmInterlaceFlags >> 4) & 0x03)));
    AddDescriptionOnly(Format("<br>D7..6: Reserved. %d"                 ,((bmInterlaceFlags >> 6) & 0x03)));
    AddFieldBreak();

    AddEntry( 26, "bCopyProtect", bCopyProtect, 2, "Specifies whether duplication of the video stream is restricted.", 0); 
    AddDescriptionOnly(Format("D0: video stream is restricted %d",(bCopyProtect & 0x01)));
    AddFieldBreak();

    AddEntry( 27, "bVariableSize", bVariableSize, 2, "Specifies whether the data within the frame is of variable length from frame to frame", 0); 
    AddDescriptionOnly(Format("D0: %d",(bCopyProtect & 0x01)));
    AddFieldBreak();
     
    return 1; #decoded it
}

VS_FRAME_FRAME_BASED()
{
    base = Base;

    bFrameIndex              = GetDataByte(base+3);
    bmCapabilities           = GetDataByte(base+4);
    wWidth                   = GetDataWord(base+5);
    wHeight                  = GetDataWord(base+7);
    dwMinBitRate             = GetDataLong(base+9);
    dwMaxBitRate             = GetDataLong(base+13);
    dwDefaultFrameInterval   = GetDataLong(base+17);
    bFrameIntervalType       = GetDataByte(base+21);
    dwBytesPerLine           = GetDataLong(base+22);
    
    AddEntry( 3, "bFrameIndex", bFrameIndex, 2, "Index of this frame descriptor", 0); 
    AddFieldBreak();

    AddEntry( 4, "bmCapabilities", bmCapabilities, 2, "", 0);
    AddDescriptionOnly(Format("<br>D0: Still image supported %d",((bmCapabilities >> 0) & 0x01))); 
    AddDescriptionOnly(Format("<br>D1: Fixed frame-rate %d"     ,((bmCapabilities >> 1) & 0x01)));
    AddDescriptionOnly(Format("<br>D7..2: Reserved %d"          , bmCapabilities >> 2 )         ); 
    AddFieldBreak();

    AddEntry( 5, "wWidth", wWidth, 4, "Width of decoded bitmap frame in pixels", 0); 
    AddFieldBreak();

    AddEntry( 7, "wHeight", wHeight, 4, "Height of decoded bitmap frame in pixels", 0); 
    AddFieldBreak();

    AddEntry( 9, "dwMinBitRate", dwMinBitRate, 8, "Specifies the minimum bit rate at the longest frame interval in units of bps at which the data can be transmitted", 0); 
    AddFieldBreak();

    AddEntry( 13, "dwMaxBitRate", dwMaxBitRate, 8, "Specifies the maximum bit rate at the shortest frame interval in units of bps at which the data can be transmitted", 0); 
    AddFieldBreak();

    AddEntry( 17, "dwDefaultFrameInterval", dwDefaultFrameInterval, 8, "Specifies the frame interval the device would like to indicate for use as a default", 0); 
    AddFieldBreak();

    AddEntry( 21, "bFrameIntervalType", bFrameIntervalType, 2, "Indicates how the frame interval can be programmed. 0: Continuous frame interval 1..255: The number of discrete frame", 0); 
    AddFieldBreak();

    AddEntry( 22, "dwBytesPerLine", dwBytesPerLine, 8, "Specifies the number of bytes per line of video for packed fixed frame size formats, allowing the receiver to perform stride alignment of the video", 0); 
    AddFieldBreak();
    
    if(bFrameIntervalType == 0)
    {
        dwMinFrameInterval  = GetDataLong(base+26);
        dwMaxFrameInterval  = GetDataLong(base+30);
        dwFrameIntervalStep = GetDataLong(base+34);

        AddEntry( 26, "dwMinFrameInterval", dwMinFrameInterval, 8, "Shortest frame interval supported (at highest frame rate), in 100 ns units", 0); 
        AddFieldBreak();

        AddEntry( 30, "dwMaxFrameInterval", dwMaxFrameInterval, 8, "Longest frame interval supported (at lowest frame rate), in 100 ns units", 0); 
        AddFieldBreak();

        AddEntry( 34, "dwFrameIntervalStep", dwFrameIntervalStep, 8, "Indicates granularity of frame interval range, in 100 ns units", 0); 
        AddFieldBreak();
    }
    else
    {
        for(FrameInterval = 1; FrameInterval <= bFrameIntervalType; FrameInterval = FrameInterval + 1 )
        {
            dwCurFrameInterval = GetDataLong(base+26+((FrameInterval - 1) * 4));
            dwFrameIntervalS  = Format("dwFrameInterval(%d)", FrameInterval);
            
            if(FrameInterval == bFrameIntervalType)
                FrameIntervalDesc = "Longest frame interval supported (at lowest frame rate), in 100 ns units";
            else
               FrameIntervalDesc = "Shortest frame interval supported (at highest frame rate), in 100 ns units";
            
            AddEntry( 26+((FrameInterval - 1) * 4), dwFrameIntervalS, dwCurFrameInterval, 8, FrameIntervalDesc, 0); 
            AddFieldBreak();
        }
    }
    return 1; # decoded it
}

VS_FORMAT_STREAM_BASED()
{
    base = Base;
    
    bFormatIndex          = GetDataByte(base+3);

LittleEndian = 0;    
    guidFormat1           = GetDataLong(base+4);
    guidFormat2           = GetDataLong(base+8);
    guidFormat3           = GetDataLong(base+12);
    guidFormat4           = GetDataLong(base+16);
LittleEndian = 1;
    
    dwPacketLength        = GetDataLong(base+20);
 
    AddEntry( 3, "bFormatIndex", bFormatIndex, 2, "Index of this Format Descriptor", 0); 
    AddFieldBreak();

    guidFormatS = FormatEx("%04X-%04X-%04X-%04X",guidFormat1, guidFormat2, guidFormat3, guidFormat4);
    AddEntry( 4, "guidFormat", guidFormat1, 8, "Globally Unique Identifier used to identify stream-encoding format\n" + guidFormatS, 0, 0, guidFormatS); 
    AddFieldBreak();

    AddEntry( 20, "dwPacketLength", dwPacketLength, 8, "If non-zero, indicates a format-specific packet size in a Packet-Oriented stream.", 0); 
    AddDescriptionOnly( "If zero, indicates that the format-specific data is either Byte-Oriented, or consists of variable size format-specific packets." );
    AddFieldBreak();
   
    return 1; # decoded it
}

set VSFormatH264Table =
[
    [  0,      "Not supported"                                                                        ],
    [  1,      "Limited to 1.5 or 2.0 scaling in both directions, while maintaining the aspect ratio" ],
    [  2,      "Limited to 1.0, 1.5 or 2.0 scaling in either direction"                				  ],
	[  3,      "Limited to resolutions reported by the associated Frame Descriptors"                  ],
	[  4,      "Arbitrary scaling"                                                                    ]
];

VS_FORMAT_H264()
{
	base = Base;
	
	bFormatIndex                                 		   = GetDataByte(base+3);
    bNumFrameDescriptors                         		   = GetDataByte(base+4);
    bDefaultFrameIndex                           		   = GetDataByte(base+5);
    bMaxCodecConfigDelay                         		   = GetDataByte(base+6);
    bmSupportedSliceModes                        		   = GetDataByte(base+7);        
    bmSupportedSyncFrameTypes                    		   = GetDataByte(base+8);           
    bResolutionScaling    	                     		   = GetDataByte(base+9);
    Reserved1                                    		   = GetDataByte(base+10);
    bmSupportedRateControlModes                  		   = GetDataByte(base+11);
	wMaxMBperSecOneResolutionNoScalability       		   = GetDataWord(base+12);
	wMaxMBperSecTwoResolutionsNoScalability      		   = GetDataWord(base+14);
	wMaxMBperSecThreeResolutionsNoScalability    		   = GetDataWord(base+16);
	wMaxMBperSecFourResolutionsNoScalability     		   = GetDataWord(base+18);
	wMaxMBperSecOneResolutionTemporalScalability 		   = GetDataWord(base+20);
	wMaxMBperSecTwoResolutionsTemporalScalablility 		   = GetDataWord(base+22);
	wMaxMBperSecThreeResolutionsTemporalScalability        = GetDataWord(base+24);
	wMaxMBperSecFourResolutionsTemporalScalability         = GetDataWord(base+26);
	wMaxMBperSecOneResolutionTemporalQualityScalability    = GetDataWord(base+28);
	wMaxMBperSecTwoResolutionsTemporalQualityScalability   = GetDataWord(base+30);
	wMaxMBperSecThreeResolutionsTemporalQualityScalablity  = GetDataWord(base+32);
	wMaxMBperSecFourResolutionsTemporalQualityScalability  = GetDataWord(base+34);
	wMaxMBperSecOneResolutionsTemporalSpatialScalability   = GetDataWord(base+36);
	wMaxMBperSecTwoResolutionsTemporalSpatialScalability   = GetDataWord(base+38);
	wMaxMBperSecThreeResolutionsTemporalSpatialScalability = GetDataWord(base+40);
	wMaxMBperSecFourResolutionsTemporalSpatialScalability  = GetDataWord(base+42);
	wMaxMBperSecOneResolutionFullScalability 			   = GetDataWord(base+44);
	wMaxMBperSecTwoResolutionsFullScalability              = GetDataWord(base+46);
	wMaxMBperSecThreeResolutionsFullScalability            = GetDataWord(base+48);
	wMaxMBperSecFourResolutionsFullScalability			   = GetDataWord(base+50);
	
	AddEntry( 3, "bFormatIndex", bFormatIndex, 2, "Index of this format descriptor", 0); 
    AddFieldBreak();

	AddEntry( 4, "bNumFrameDescriptors", bNumFrameDescriptors, 2, "INumber of Frame Descriptors", 0); 
    AddFieldBreak();

	AddEntry( 5, "bDefaultFrameIndex", bDefaultFrameIndex, 2, "Default frame index", 0); 
    AddFieldBreak();

	AddEntry( 6, "bMaxCodecConfigDelay", bMaxCodecConfigDelay, 2, "Maximum number of frames", 0); 
    AddFieldBreak();

	AddEntry( 7, "bmSupportedSliceModes", bmSupportedSliceModes, 2, "SSlice mode", 0);
    AddDescriptionOnly(Format("<br>D0: Maximum number of MBs per slice mode %d"      , ((bmSupportedSliceModes >> 0) & 0x01)));
    AddDescriptionOnly(Format("<br>D1: Target compressed size per slice mode %d"     , ((bmSupportedSliceModes >> 1) & 0x01)));
    AddDescriptionOnly(Format("<br>D2: Number of slices per frame mode %d"           , ((bmSupportedSliceModes >> 2) & 0x01)));
    AddDescriptionOnly(Format("<br>D3: Number of Macroblock rows per slice mode %d"  , ((bmSupportedSliceModes >> 3) & 0x01)));
    AddDescriptionOnly(Format("<br>D7..4: Field pattern %d"                          , ((bmSupportedSliceModes >> 4) & 0x0F)));
    AddFieldBreak();
	
	AddEntry( 8, "bmSupportedSyncFrameTypes", bmSupportedSyncFrameTypes, 2, "", 0);
    AddDescriptionOnly(Format("<br>D0: Reset %d"      													, ((bmSupportedSyncFrameTypes >> 0) & 0x01)));
    AddDescriptionOnly(Format("<br>D1: IDR frame with SPS and PPS headers %d"     						, ((bmSupportedSyncFrameTypes >> 1) & 0x01)));
    AddDescriptionOnly(Format("<br>D2: IDR frame (with SPS and PPS headers) %d"                         , ((bmSupportedSyncFrameTypes >> 2) & 0x01)));
    AddDescriptionOnly(Format("<br>D3: Non-IDR random-access I frame (with SPS and PPS headers) %d"     , ((bmSupportedSyncFrameTypes >> 3) & 0x01)));
    AddDescriptionOnly(Format("<br>D4: Generate a random-access I frame (with SPS and PPS headers) %d"  , ((bmSupportedSyncFrameTypes >> 4) & 0x01)));
	AddDescriptionOnly(Format("<br>D5: P frame that is a long term reference frame %d" 					, ((bmSupportedSyncFrameTypes >> 5) & 0x01)));
	AddDescriptionOnly(Format("<br>D6: Gradual Decoder Refresh frames %d"  							    , ((bmSupportedSyncFrameTypes >> 6) & 0x01)));
	AddDescriptionOnly(Format("<br>D7: Reserved, set to 0 %d"                                           , ((bmSupportedSyncFrameTypes >> 7) & 0x01)));
    AddFieldBreak();	

	if( bResolutionScaling <= 4)
	{
		_row_format_H264 = Find (VSFormatH264Table, bResolutionScaling);
		AddEntry( 9, "bResolutionScaling", bResolutionScaling, 2, "Specifies the support for resolution downsizing", 0);
		AddDescriptionOnly( Format ("%s", _row_format_H264[1]) );
	}
	else
	{
		AddEntry( 9, "bResolutionScaling", bResolutionScaling, 2, "Specifies the support for resolution downsizing", 0);
		AddDescriptionOnly( Format ("%s", "Reserved") );
	}
    AddFieldBreak();	

	AddEntry( 10, "Reserved1", Reserved1, 2, "Reserved. Set to zero", 0); 
    AddFieldBreak();

	AddEntry( 11, "bmSupportedRateControlModes", bmSupportedRateControlModes, 2, "Supported rate-control modes", 0); 
    AddDescriptionOnly(Format("<br>D0: Variable bit rate (VBR) with underflow allowed %d"   , ((bmSupportedSyncFrameTypes >> 0) & 0x01)));
    AddDescriptionOnly(Format("<br>D1: Constant bit rate (CBR) %d"     						, ((bmSupportedSyncFrameTypes >> 1) & 0x01)));
    AddDescriptionOnly(Format("<br>D2: Constant QP %d"                                      , ((bmSupportedSyncFrameTypes >> 2) & 0x01)));
    AddDescriptionOnly(Format("<br>D3: Global VBR with underflow allowed %d"                , ((bmSupportedSyncFrameTypes >> 3) & 0x01)));
    AddDescriptionOnly(Format("<br>D4: VBR without underflow %d"                            , ((bmSupportedSyncFrameTypes >> 4) & 0x01)));
	AddDescriptionOnly(Format("<br>D5: Global VBR without underflow %d" 					, ((bmSupportedSyncFrameTypes >> 5) & 0x01)));
	AddDescriptionOnly(Format("<br>D7..D6: Gradual Decoder Refresh frames %d"  				, ((bmSupportedSyncFrameTypes >> 6) & 0x03)));
    AddFieldBreak();	

    AddEntry( 12, "wMaxMBperSecOneResolutionNoScalability", wMaxMBperSecOneResolutionNoScalability, 4, "Maximum macroblock processing rate, in units of 1000 MB/s, allowed for a single AVC stream", 0); 
    AddFieldBreak();
	
    AddEntry( 14, "wMaxMBperSecTwoResolutionsNoScalability", wMaxMBperSecTwoResolutionsNoScalability, 4, "Maximum macroblock processing rate, in units of 1000 MB/s, allowed for two AVC streams of different resolution", 0); 
    AddFieldBreak();
	
    AddEntry( 16, "wMaxMBperSecThreeResolutionsNoScalability", wMaxMBperSecThreeResolutionsNoScalability, 4, "Maximum macroblock processing rate, in units of 1000 MB/s, allowed for three AVC streams of different resolution", 0); 
    AddFieldBreak();

    AddEntry( 18, "wMaxMBperSecFourResolutionsNoScalability", wMaxMBperSecFourResolutionsNoScalability, 4, "Maximum macroblock processing rate, in units of 1000 MB/s, allowed for four AVC streams of different resolution", 0); 
    AddFieldBreak();

    AddEntry( 20, "wMaxMBperSecOneResolutionTemporalScalability", wMaxMBperSecOneResolutionTemporalScalability, 4, "Maximum macroblock processing rate, in units of 1000 MB/s, allowed for temporal scalable SVC, summing up across all layers when all layers have the same resolution", 0); 
    AddFieldBreak();

    AddEntry( 22, "wMaxMBperSecTwoResolutionsTemporalScalablility", wMaxMBperSecTwoResolutionsTemporalScalablility, 4, "Maximum macroblock processing rate, in units of 1000 MB/s, allowed for temporal scalable SVC, summing up across all layers when all layers consist of two different resolutions", 0); 
    AddFieldBreak();

    AddEntry( 24, "wMaxMBperSecThreeResolutionsTemporalScalability", wMaxMBperSecThreeResolutionsTemporalScalability, 4, "Maximum macroblock processing rate, in units of 1000 MB/s, allowed for temporal scalable streams, summing up across all layers when all layers consist of three different resolutions", 0); 
    AddFieldBreak();

    AddEntry( 26, "wMaxMBperSecFourResolutionsTemporalScalability", wMaxMBperSecFourResolutionsTemporalScalability, 4, "Maximum macroblock processing rate, in units of 1000 MB/s, allowed for temporal scalable streams, summing up across all layers when all layers consist of four different resolutions", 0); 
    AddFieldBreak();

    AddEntry( 28, "wMaxMBperSecOneResolutionTemporalQualityScalability", wMaxMBperSecOneResolutionTemporalQualityScalability, 4, "Maximum macroblock processing rate, in units of 1000 MB/s, allowed for temporal and quality scalable SVC streams, summing up across all layers when all layers have the same resolution", 0); 
    AddFieldBreak();

    AddEntry( 30, "wMaxMBperSecTwoResolutionsTemporalQualityScalability", wMaxMBperSecTwoResolutionsTemporalQualityScalability, 4, "Maximum macroblock processing rate, in units of 1000 MB/s, allowed for temporal and quality scalable SVC streams, summing up across all layers when all layers consist of two different resolutions", 0); 
    AddFieldBreak();

    AddEntry( 32, "wMaxMBperSecThreeResolutionsTemporalQualityScalablity", wMaxMBperSecThreeResolutionsTemporalQualityScalablity, 4, "Maximum macroblock processing rate, in units of 1000 MB/s, allowed for temporal and quality scalable SVC streams, summing up across all layers when all layers consist of three different resolutions", 0); 
    AddFieldBreak();

    AddEntry( 34, "wMaxMBperSecFourResolutionsTemporalQualityScalability", wMaxMBperSecFourResolutionsTemporalQualityScalability, 4, "Maximum macroblock processing rate, in units of 1000 MB/s, allowed for temporal and quality scalable SVC streams, summing up across all layers when all layers consist of four different resolutions", 0); 
    AddFieldBreak();

    AddEntry( 36, "wMaxMBperSecOneResolutionsTemporalSpatialScalability", wMaxMBperSecOneResolutionsTemporalSpatialScalability, 4, "Maximum macroblock processing rate, in units of 1000 MB/s, allowed for temporal and spatial scalable SVC streams, summing up across all layers when all layers have the same resolutions", 0); 
    AddFieldBreak();

    AddEntry( 38, "wMaxMBperSecTwoResolutionsTemporalSpatialScalability", wMaxMBperSecTwoResolutionsTemporalSpatialScalability, 4, "Maximum macroblock processing rate, in units of 1000 MB/s, allowed for temporal and spatial scalable SVC streams, summing up across all layers when all layers consist of two different resolutions", 0); 
    AddFieldBreak();

    AddEntry( 40, "wMaxMBperSecThreeResolutionsTemporalSpatialScalability", wMaxMBperSecThreeResolutionsTemporalSpatialScalability, 4, "Maximum macroblock processing rate, in units of 1000 MB/s, allowed for temporal and spatial scalable SVC streams, summing up across all layers when all layers consist of three different resolutions", 0); 
    AddFieldBreak();

    AddEntry( 42, "wMaxMBperSecFourResolutionsTemporalSpatialScalability", wMaxMBperSecFourResolutionsTemporalSpatialScalability, 4, "Maximum macroblock processing rate, in units of 1000 MB/s, allowed for temporal and spatial scalable SVC streams, summing up across all layers when all layers consist of four different resolutions", 0); 
    AddFieldBreak();

    AddEntry( 44, "wMaxMBperSecOneResolutionFullScalability", wMaxMBperSecOneResolutionFullScalability, 4, "Maximum macroblock processing rate, in units of 1000 MB/s, allowed for fully scalable streams, summing up across all layers when all layers have the same resolutions", 0); 
    AddFieldBreak();

    AddEntry( 46, "wMaxMBperSecTwoResolutionsFullScalability", wMaxMBperSecTwoResolutionsFullScalability, 4, "Maximum macroblock processing rate, in units of 1000 MB/s, allowed for fully scalable streams, summing up across all layers when all layers consist of two different resolutions", 0); 
    AddFieldBreak();

    AddEntry( 48, "wMaxMBperSecThreeResolutionsFullScalability", wMaxMBperSecThreeResolutionsFullScalability, 4, "Maximum macroblock processing rate, in units of 1000 MB/s, allowed for fully scalable streams, summing up across all layers when all layers consist of three different resolutions", 0); 
    AddFieldBreak();

    AddEntry( 50, "wMaxMBperSecFourResolutionsFullScalability", wMaxMBperSecFourResolutionsFullScalability, 4, "Maximum macroblock processing rate, in units of 1000 MB/s, allowed for fully scalable streams, summing up across all layers when all layers consist of four different resolutions", 0); 
    AddFieldBreak();	
}

VS_FRAME_H264()
{
	base = Base;
	
	bFrameIndex            = GetDataByte(base+3);
    wWidth                 = GetDataWord(base+4);
    wHeight                = GetDataWord(base+6);
    wSARwidth              = GetDataWord(base+8);
    wSARheight             = GetDataWord(base+10);        
    wProfile               = GetDataWord(base+12);           
    bLevelIDC    	       = GetDataByte(base+14);
    wConstrainedToolset    = GetDataWord(base+15);
    bmSupportedUsages      = GetDataLong(base+17);
	bmCapabilities         = GetDataWord(base+21);
	bmSVCCapabilities      = GetDataLong(base+23);
	bmMVCCapabilities      = GetDataLong(base+27);
	dwMinBitRate      	   = GetDataLong(base+31);
	dwMaxBitRate      	   = GetDataLong(base+35);
	dwDefaultFrameInterval = GetDataLong(base+39);
	bNumFrameIntervals     = GetDataByte(base+43);
	
	AddEntry( 3, "bFrameIndex", bFrameIndex, 2, "Index of this Frame Descriptor", 0); 
    AddFieldBreak();	
	
	AddEntry( 4, "wWidth", wWidth, 4, "The width, in pixels, of pictures output from the decoding process", 0); 
    AddFieldBreak();
	
    AddEntry( 6, "wHeight", wHeight, 4, "The height, in pixels, of pictures output from the decoding process", 0); 
    AddFieldBreak();

    AddEntry( 8, "wSARwidth", wSARwidth, 4, "Sample aspect ratio width", 0); 
    AddFieldBreak();

    AddEntry( 10, "wSARheight", wSARheight, 4, "Sample aspect ratio height", 0); 
    AddFieldBreak();

    AddEntry( 12, "wProfile", wProfile, 4, "The first two bytes of the sequence parameter set, specified by profile_idc and constraint flags in the H.264 specification, to indicate the profile and applicable constraints to be used", 0); 
    AddFieldBreak();	
	
	AddEntry( 14, "bLevelIDC", bLevelIDC, 2, "The level, as specified by the level_idc flag", 0); 
    AddFieldBreak();
	
	AddEntry( 15, "wConstrainedToolset", wConstrainedToolset, 4, "Reserved, set to zero", 0); 
    AddFieldBreak();
	
	AddEntry( 17, "bmSupportedUsages", bmSupportedUsages, 8, "", 0);
    AddDescriptionOnly(Format("<br>D0: Real-time/UCConfig mode 0 %d"      			                , ((bmSupportedUsages >> 0) & 0x01)));
    AddDescriptionOnly(Format("<br>D1: Real-time/UCConfig mode 1 %d"     						    , ((bmSupportedUsages >> 1) & 0x01)));
    AddDescriptionOnly(Format("<br>D2: Real-time/UCConfig mode 2Q %d"                               , ((bmSupportedUsages >> 2) & 0x01)));
    AddDescriptionOnly(Format("<br>D3: Real-time/UCConfig mode 2S %d"                               , ((bmSupportedUsages >> 3) & 0x01)));
    AddDescriptionOnly(Format("<br>D4: Real-time/UCConfig mode 3 %d"                                , ((bmSupportedUsages >> 4) & 0x01)));
	AddDescriptionOnly(Format("<br>D7..D5: Reserved; set to 0 %d" 					                , ((bmSupportedUsages >> 5) & 0x03)));
	AddDescriptionOnly(Format("<br>D15..D8: Gradual Decoder Refresh frames %d"  				    , ((bmSupportedUsages >> 8) & 0xFF)));
	AddDescriptionOnly(Format("<br>D16: File Storage mode with I and P slices (e.g. IPPP) %d"       , ((bmSupportedUsages >> 16) & 0x01)));
	AddDescriptionOnly(Format("<br>D17: File Storage mode with I, P, and B slices (e.g. IB…BP) %d"  , ((bmSupportedUsages >> 17) & 0x01)));
	AddDescriptionOnly(Format("<br>D18: File storage all-I-frame mode %d"                           , ((bmSupportedUsages >> 18) & 0x01)));
	AddDescriptionOnly(Format("<br>D23..D19: Reserved, set to 0 %d"                                 , ((bmSupportedUsages >> 19) & 0x1F)));
	AddDescriptionOnly(Format("<br>D24: MVC Stereo High Mode %d"                                    , ((bmSupportedUsages >> 24) & 0x01)));
	AddDescriptionOnly(Format("<br>D25: MVC Multiview Mode %d"                                      , ((bmSupportedUsages >> 25) & 0x01)));
	AddDescriptionOnly(Format("<br>D31..D26: MVC Multiview Mode %d"                                 , ((bmSupportedUsages >> 26) & 0x3F)));
    AddFieldBreak();
	
	AddEntry( 21, "bmCapabilities", bmCapabilities, 4, "", 0);
    AddDescriptionOnly(Format("<br>D0: CAVLC only %d"      			     , ((bmCapabilities >> 0) & 0x01)));
    AddDescriptionOnly(Format("<br>D1: CABAC only %d"     				 , ((bmCapabilities >> 1) & 0x01)));
    AddDescriptionOnly(Format("<br>D2: Constant frame rate %d"           , ((bmCapabilities >> 2) & 0x01)));
    AddDescriptionOnly(Format("<br>D3: Separate QP for luma/chroma %d"  , ((bmCapabilities >> 3) & 0x01)));
    AddDescriptionOnly(Format("<br>D4: Separate QP for Cb/Cr %d"         , ((bmCapabilities >> 4) & 0x01)));
	AddDescriptionOnly(Format("<br>D5: No picture reordering %d" 		 , ((bmCapabilities >> 5) & 0x01)));
	AddDescriptionOnly(Format("<br>D6: Long Term Reference frame %d"  	 , ((bmCapabilities >> 6) & 0x01)));
	AddDescriptionOnly(Format("<br>D15..D7: Reserved; set to 0 %d"       , ((bmCapabilities >> 7) & 0x1FF)));  
    AddFieldBreak();
	
	AddEntry( 23, "bmSVCCapabilities", bmSVCCapabilities, 8, "", 0);
    AddDescriptionOnly(Format("<br>D2..D0: Maximum number of temporal layers minus 1 %d"      			      , ((bmSVCCapabilities >> 0) & 0x07)));
    AddDescriptionOnly(Format("<br>D3: Rewrite support %d"     				                                  , ((bmSVCCapabilities >> 3) & 0x01)));
    AddDescriptionOnly(Format("<br>D6..D4: Maximum number of CGS layers minus 1 %d"                           , ((bmSVCCapabilities >> 4) & 0x07)));
    AddDescriptionOnly(Format("<br>D9..D7: Maximum number of MGS sublayers %d"                                , ((bmSVCCapabilities >> 7) & 0x07)));
    AddDescriptionOnly(Format("<br>D10: Additional SNR scalability support in spatial enhancement layers %d"  , ((bmSVCCapabilities >> 10) & 0x01)));
	AddDescriptionOnly(Format("<br>D13..D11: Maximum number of spatial layers minus 1 %d" 		              , ((bmSVCCapabilities >> 11) & 0x07)));
	AddDescriptionOnly(Format("<br>D31..D14: Reserved. Set to zero %d"  	                                  , ((bmSVCCapabilities >> 14) & 0x3FFFF)));
    AddFieldBreak();
	
	AddEntry( 27, "bmMVCCapabilities", bmMVCCapabilities, 8, "", 0);
    AddDescriptionOnly(Format("<br>D2..D0: Maximum number of temporal layers minus 1 %d"     , ((bmSVCCapabilities >> 0) & 0x07)));
    AddDescriptionOnly(Format("<br>D10..D3: Maximum number of view components minus 1 %d"    , ((bmSVCCapabilities >> 3) & 0xFF)));
	AddDescriptionOnly(Format("<br>D31..D11: Reserved. Set to zero %d"  	                 , ((bmSVCCapabilities >> 11) & 0x1FFFFF)));
    AddFieldBreak();
	
	AddEntry( 31, "dwMinBitRate", dwMinBitRate, 8, "Specifies the minimum bit rate, at maximum compression and longest frame interval, in units of bps, at which the data can be transmitted", 0); 
    AddFieldBreak();
	
	AddEntry( 35, "dwMaxBitRate", dwMaxBitRate, 8, "Specifies the maximum bit rate, at minimum compression and shortest frame interval, in units of bps, at which the data can be transmitted", 0); 
    AddFieldBreak();
	
	AddEntry( 39, "dwDefaultFrameInterval", dwDefaultFrameInterval, 8, "Specifies the frame interval the device indicates for use as a default, in 100-ns units", 0); 
    AddFieldBreak();
	
	AddEntry( 43, "bNumFrameIntervals", bNumFrameIntervals, 2, "Specifies the number of frame intervals supported", 0); 
    AddFieldBreak();
	
	for(FrameInterval = 1; FrameInterval <= bNumFrameIntervals; FrameInterval = FrameInterval + 1 )
    {
        dwCurFrameInterval = GetDataLong(base+44+((FrameInterval - 1) * 4));
        dwFrameIntervalS  = Format("dwFrameInterval(%d)", FrameInterval);
            
        if(FrameInterval == bNumFrameIntervals)
            FrameIntervalDesc = "Longest frame interval supported (at lowest frame rate), in 100-ns units";
        
		else
            FrameIntervalDesc = "Shortest frame interval supported (at the highest frame rate), in 100-ns units";
            
        AddEntry( 44+((FrameInterval - 1) * 4), dwFrameIntervalS, dwCurFrameInterval, 8, FrameIntervalDesc, 0); 
        AddFieldBreak();
    }
}

VS_FORMAT_H264_SIMULCAST()
{
	VS_FORMAT_H264();
}

set VSFormatVP8Table =
[
    [  0,      "Not supported"                                                                        ],
    [  1,      "Limited to 1.5 or 2.0 scaling in both directions, while maintaining the aspect ratio" ],
    [  2,      "Limited to 1.0, 1.5 or 2.0 scaling in either direction"                				  ],
	[  3,      "Limited to resolutions reported by the associated Frame Descriptors"                  ],
	[  4,      "Arbitrary scaling"                                                                    ]
];

VS_FORMAT_VP8()
{
	base = Base;
	
	bFormatIndex                       = GetDataByte(base+3);
    bNumFrameDescriptors               = GetDataByte(base+4);
    bDefaultFrameIndex                 = GetDataByte(base+5);
    bMaxCodecConfigDelay               = GetDataByte(base+6);
    bSupportedPartitionCount           = GetDataByte(base+7);        
    bmSupportedSyncFrameTypes          = GetDataByte(base+8);           
    bResolutionScaling    	           = GetDataByte(base+9);
    bmSupportedRateControlModes        = GetDataByte(base+10);
    wMaxMBperSec                  	   = GetDataWord(base+11);
	
	AddEntry( 3, "bFormatIndex", bFormatIndex, 2, "Index of this format descriptor", 0); 
    AddFieldBreak();
	
	AddEntry( 4, "bNumFrameDescriptors", bNumFrameDescriptors, 2, "Number of Frame Descriptors", 0); 
    AddFieldBreak();
	
	AddEntry( 5, "bDefaultFrameIndex", bDefaultFrameIndex, 2, "Default frame index", 0); 
    AddFieldBreak();
	
	AddEntry( 6, "bMaxCodecConfigDelay", bMaxCodecConfigDelay, 2, "Maximum number of frames the encoder takes to respond to a command", 0); 
    AddFieldBreak();
	
	AddEntry( 7, "bSupportedPartitionCount", bSupportedPartitionCount, 2, "Maximum number of supported partitions per frame", 0); 
    AddFieldBreak();
	
	AddEntry( 8, "bmSupportedSyncFrameTypes", bmSupportedSyncFrameTypes, 2, "", 0);
    AddDescriptionOnly(Format("<br>D0: Reset %d"      			           , ((bmSupportedSyncFrameTypes >> 0) & 0x01)));
    AddDescriptionOnly(Format("<br>D1: Intra frame %d"     				   , ((bmSupportedSyncFrameTypes >> 1) & 0x01)));
    AddDescriptionOnly(Format("<br>D2: Golden frame %d"                    , ((bmSupportedSyncFrameTypes >> 2) & 0x01)));
    AddDescriptionOnly(Format("<br>D3: Alternate reference frame %d"       , ((bmSupportedSyncFrameTypes >> 3) & 0x01)));
    AddDescriptionOnly(Format("<br>D4: Gradual Decoder Refresh frames %d"  , ((bmSupportedSyncFrameTypes >> 4) & 0x01)));
	AddDescriptionOnly(Format("<br>D7..D5: Reserved, set to 0 %d" 		   , ((bmSupportedSyncFrameTypes >> 5) & 0x07)));
    AddFieldBreak();
	
	_row_format_VP8 = Find (VSFormatVP8Table, bResolutionScaling);
    AddEntry( 9, "bResolutionScaling", bResolutionScaling, 2, "Specifies the support for resolution downsizing", 0);
    AddDescriptionOnly( Format ("%s", _row_format_VP8[1]) );
    AddFieldBreak();
	
	AddEntry( 10, "bmSupportedRateControlModes", bmSupportedRateControlModes, 2, "", 0);
    AddDescriptionOnly(Format("<br>D0: Variable bit rate (VBR) %d"     , ((bmSupportedRateControlModes >> 0) & 0x01)));
    AddDescriptionOnly(Format("<br>D1: Constant bit rate (CBR) %d"     , ((bmSupportedRateControlModes >> 1) & 0x01)));
    AddDescriptionOnly(Format("<br>D2: Constant QP %d"                 , ((bmSupportedRateControlModes >> 2) & 0x01)));
    AddDescriptionOnly(Format("<br>D3: Global VBR %d"                  , ((bmSupportedRateControlModes >> 3) & 0x01)));
	AddDescriptionOnly(Format("<br>D7..D4: Reserved, set to 0 %d"      , ((bmSupportedRateControlModes >> 5) & 0x0F)));
    AddFieldBreak();
	
	AddEntry( 11, "wMaxMBperSec", wMaxMBperSec, 4, "Maximum macroblock processing rate, in units of MB/s, allowed for all VP8 streams by the device", 0); 
    AddFieldBreak();
}

VS_FRAME_VP8()
{
	base = Base;
	
	bFrameIndex            			= GetDataByte(base+3);
    wWidth                 			= GetDataWord(base+4);
    wHeight                			= GetDataWord(base+6);
    bmSupportedUsages      			= GetDataLong(base+8);
    bmCapabilities         			= GetDataWord(base+12);           
    bmScalabilityCapabilities       = GetDataLong(base+14);
    dwMinBitRate    				= GetDataLong(base+18);
    dwMaxBitRate      				= GetDataLong(base+22);
	dwDefaultFrameInterval          = GetDataLong(base+26);
	bNumFrameIntervals      		= GetDataByte(base+30);
	
	AddEntry( 3, "bFrameIndex", bFrameIndex, 2, "Index of this Frame Descriptor", 0); 
    AddFieldBreak();	
	
	AddEntry( 4, "wWidth", wWidth, 4, "The width, in pixels, of valid picture area from the decoding process", 0); 
    AddFieldBreak();
	
    AddEntry( 6, "wHeight", wHeight, 4, "The height, in pixels, of pictures output from the decoding process", 0); 
    AddFieldBreak();
	
	AddEntry( 8, "bmSupportedUsages", bmSupportedUsages, 8, "", 0);
    AddDescriptionOnly(Format("<br>D15..D3: Reserved; set to 0 %d"      			  , ((bmSupportedUsages >> 3) & 0x01FFF)));
    AddDescriptionOnly(Format("<br>D16: File Storage mode with I and P frames %d"     , ((bmSupportedUsages >> 16) & 0x01)));
    AddDescriptionOnly(Format("<br>D17: Reserved; set to 0 %d"           			  , ((bmSupportedUsages >> 17) & 0x01)));
    AddDescriptionOnly(Format("<br>D18: File storage all-I-frame mode %d"  			  , ((bmSupportedUsages >> 18) & 0x01)));
    AddDescriptionOnly(Format("<br>D31..D19: Reserved; set to 0 %d"                   , ((bmSupportedUsages >> 19) & 0x01FFF)));
    AddFieldBreak();

	AddEntry( 12, "bmSupportedSyncFrameTypes", bmSupportedSyncFrameTypes, 4, "", 0);
    AddDescriptionOnly(Format("<br>D0: Reserved; set to 0 %d"      	       , ((bmSupportedSyncFrameTypes >> 0) & 0x01)));
    AddDescriptionOnly(Format("<br>D1: Reserved; set to 0 %d"     		   , ((bmSupportedSyncFrameTypes >> 1) & 0x01)));
    AddDescriptionOnly(Format("<br>D2: Constant frame rate %d"             , ((bmSupportedSyncFrameTypes >> 2) & 0x01)));
    AddDescriptionOnly(Format("<br>D3: Separate QP for luma/chroma %d"     , ((bmSupportedSyncFrameTypes >> 3) & 0x01)));
    AddDescriptionOnly(Format("<br>D4: Reserved; set to 0 %d"              , ((bmSupportedSyncFrameTypes >> 4) & 0x01)));
	AddDescriptionOnly(Format("<br>D5: Reserved; set to 0 %d" 			   , ((bmSupportedSyncFrameTypes >> 5) & 0x01)));
	AddDescriptionOnly(Format("<br>D6: Golden frame %d"  				   , ((bmSupportedSyncFrameTypes >> 6) & 0x01)));
	AddDescriptionOnly(Format("<br>D7: Alternate reference frame %d"       , ((bmSupportedSyncFrameTypes >> 7) & 0x01)));
	AddDescriptionOnly(Format("<br>D15..D8: Reserved; set to 0 %d"  	   , ((bmSupportedSyncFrameTypes >> 8) & 0xFF)));
    AddFieldBreak();	
	
	AddEntry( 14, "bmSupportedSyncFrameTypes", bmSupportedSyncFrameTypes, 8, "", 0);
    AddDescriptionOnly(Format("<br>D2..D0: Maximum number of temporal enhancement layers minus 1 %d"     , ((bmSupportedSyncFrameTypes >> 0) & 0x07)));
    AddDescriptionOnly(Format("<br>D31..D3: Reserved %d"     		                                     , ((bmSupportedSyncFrameTypes >> 3) & 0x01FFFFFFF)));
    AddFieldBreak();	

 	AddEntry( 18, "dwMinBitRate", dwMinBitRate, 8, "Specifies the minimum bit rate, at maximum compression and longest frame interval, in units of bps, at which the data can be transmitted", 0); 
    AddFieldBreak();	
	
	AddEntry( 22, "dwMaxBitRate", dwMaxBitRate, 8, "Specifies the minimum bit rate, at maximum compression and longest frame interval, in units of bps, at which the data can be transmitted", 0); 
    AddFieldBreak();
	
	AddEntry( 26, "dwDefaultFrameInterval", dwDefaultFrameInterval, 8, "Specifies the frame interval the device indicates for use as a default, in 100-ns units", 0); 
    AddFieldBreak();
	
	AddEntry( 30, "bNumFrameIntervals", bNumFrameIntervals, 2, "Specifies the number of frame intervals supported (n)", 0); 
    AddFieldBreak();
	
	for(FrameInterval = 1; FrameInterval <= bNumFrameIntervals; FrameInterval = FrameInterval + 1 )
    {
        dwCurFrameInterval = GetDataLong(base+31+((FrameInterval - 1) * 4));
        dwFrameIntervalS  = Format("dwFrameInterval(%d)", dwFrameInterval);
            
         if(FrameInterval == bNumFrameIntervals)
             FrameIntervalDesc = "Longest frame interval supported (at lowest frame rate), in 100-ns units";
         else
            FrameIntervalDesc = "Shortest frame interval supported (at the highest frame rate), in 100-ns units";
            
         AddEntry( 31+((FrameInterval - 1) * 4), dwFrameIntervalS, dwCurFrameInterval, 8, FrameIntervalDesc, 0); 
        AddFieldBreak();
    }
}

VS_FORMAT_VP8_SIMULCAST()
{
	VS_FORMAT_VP8();	
}

set ColorPrimariesTable =
[
    [0xFF, "Reserved" ],                   
    [0, "Unspecified" ],                   
    [1, "BT.709, sRGB (default)" ],        
    [2, "BT.470-2 (M)" ],                  
    [3, "BBT.470-2 (B, G)" ],               
    [4, "SMPTE 170M" ],                    
    [5, "SMPTE 240M" ] 
];

set TransferCharacteristicsTable =                       
[                                   
    [0xFF, "Reserved" ],                   
    [0, "Unspecified" ],                   
    [1, "BT.709 (default)"  ],              
    [2, "BT.470-2 M " ],                    
    [3, "BT.470-2 B, G" ],                 
    [4, "SMPTE 170M" ],                    
    [5, "SMPTE 240M" ],                     
    [6, "Linear (V = Lc)" ],                
    [7, "sRGB (very similar to BT.709)" ]
];


set MatrixCoefficientsTable =     
[    	                                
    [0xFF, "Reserved" ],                   
    [0, "Unspecified" ],                   
    [1, "BT. 709" ],                       
    [2, "FCC" ],                           
    [3, "BT.470-2 B, G" ],                 
    [4, "SMPTE 170M (BT.601, default)" ],  
    [5, "SMPTE 240M" ]
];                    
			 
#4	bTransferCharacteristics	1	Number	This field defines the opto-electronic transfer characteristic of the source picture also called the gamma function.
#5	bMatrixCoefficients	1	Number	Matrix used to compute luma and chroma values from the color primaries.


VS_COLORFORMAT()
{
    base = Base;

    bColorPrimaries           = GetDataByte(base+3);
    bTransferCharacteristics  = GetDataByte(base+4);
    bMatrixCoefficients       = GetDataByte(base+5);
    
    _row_vid_c = Find (ColorPrimariesTable, bColorPrimaries);
    AddEntry( 3, "bColorPrimaries", bColorPrimaries, 2, "Color Primaries and", 0);
    AddDescriptionOnly( "Reference White:" );
    AddDescriptionOnly( Format ("%s", _row_vid_c[1]) );
    AddFieldBreak();
     
    _row_vid_c = Find (TransferCharacteristicsTable, bTransferCharacteristics);
    AddEntry( 4, "bXferCharacteristics", bTransferCharacteristics, 2, "Color Primaries and", 0);
    AddDescriptionOnly( "Reference White:" );
    AddDescriptionOnly( Format ("%s", _row_vid_c[1]) );
    AddFieldBreak();
     
    _row_vid_c = Find (MatrixCoefficientsTable, bMatrixCoefficients);
    AddEntry( 5, "bMatrixCoefficients", bMatrixCoefficients, 2, "Color Primaries and", 0);
    AddDescriptionOnly( "Reference White:" );
    AddDescriptionOnly( Format ("%s", _row_vid_c[1]) );
    AddFieldBreak();
    
    return 1; # decoded it
}

VS_FORMAT_VENDOR()
{
    base = Base;
    
    bFormatIndex          = GetDataByte(base+3);
    bNumFrameDescriptors  = GetDataByte(base+4);
    
LittleEndian = 0;    
    guidMajorFormat1     = GetDataLong(base+5);
    guidMajorFormat2     = GetDataLong(base+9);
    guidMajorFormat3     = GetDataLong(base+13);
    guidMajorFormat4     = GetDataLong(base+17);

    guidSubFormat1       = GetDataLong(base+21);
    guidSubFormat2       = GetDataLong(base+25);
    guidSubFormat3       = GetDataLong(base+29);
    guidSubFormat4       = GetDataLong(base+33);

    guidSpecifier1       = GetDataLong(base+37);
    guidSpecifier2       = GetDataLong(base+41);
    guidSpecifier3       = GetDataLong(base+45);
    guidSpecifier4       = GetDataLong(base+49);
LittleEndian = 1;       
    
    bPayloadClass       = GetDataByte(base+53);
    bDefaultFrameIndex  = GetDataByte(base+54);
    bCopyProtect        = GetDataByte(base+55);
  
    AddEntry( 3, "bFormatIndex", bFormatIndex, 2, "Index of this Format Descriptor", 0); 
    AddFieldBreak();


    AddEntry( 4, "bNumFrameDescriptors", bNumFrameDescriptors, 2, "Number of frame descriptors following that corresponds to this format", 0); 
    AddFieldBreak();

    guidMajorFormatS = FormatEx("%04X-%04X-%04X-%04X",guidMajorFormat1, guidMajorFormat2, guidMajorFormat3, guidMajorFormat4);
    AddEntry( 5, "guidMajorFormat", guidMajorFormat1, 8, "Globally Unique Identifier used to identify the general format type\n" + guidMajorFormatS, 0, 0, guidMajorFormatS); 
    AddFieldBreak();

    guidSubFormatS = FormatEx("%04X-%04X-%04X-%04X",guidSubFormat1, guidSubFormat2, guidSubFormat3, guidSubFormat4);
    AddEntry( 21, "guidSubFormat", guidSubFormat1, 8, "Globally Unique Identifier used to identify the subformat of a general format type\n" + guidSubFormatS, 0, 0, guidSubFormatS); 
    AddFieldBreak();

    guidSpecifierS = FormatEx("%04X-%04X-%04X-%04X",guidSpecifier1, guidSpecifier2, guidSpecifier3, guidSpecifier4);
    AddEntry( 37, "guidSpecifier", guidSpecifier1, 8, "Globally Unique Identifier used to identify additional data format type\n" + guidSpecifierS, 0, 0, guidSpecifierS); 
    AddFieldBreak();


    AddEntry( 53, "bPayloadClass", bPayloadClass, 2, "Index of this Format Descriptor", 0);
    AddDescriptionOnly(Format("<br>D0: Frame/Stream based payload %d",((bPayloadClass >> 1) & 0x01)));
    AddDescriptionOnly(Format("<br>D7..1: Reserved %d"               ,  bPayloadClass >> 2)         ); 
    AddFieldBreak();

    AddEntry( 54, "bDefaultFrameIndex", bDefaultFrameIndex, 2, "Optimum Frame Index(used to select resolution) for this stream", 0); 
    AddFieldBreak();

    AddEntry( 55, "bCopyProtect", bCopyProtect, 2, "Specifies whether duplication of the video stream is restricted.", 0); 
    AddDescriptionOnly(Format("D0: video stream is restricted %d",(bCopyProtect & 0x01)));
    AddFieldBreak();
    
    return 1; #decoded it
}

VS_FRAME_VENDOR()
{
    base = Base;

    bFrameIndex              = GetDataByte(base+3);
    bmCapabilities           = GetDataByte(base+4);
    wWidth                   = GetDataWord(base+5);
    wHeight                  = GetDataWord(base+7);
    dwMinBitRate             = GetDataLong(base+9);
    dwMaxBitRate             = GetDataLong(base+13);
    dwMaxVideoFrameBufferSize= GetDataLong(base+17);
    dwDefaultFrameInterval   = GetDataLong(base+21);
    bFrameIntervalType       = GetDataByte(base+25);

    AddEntry( 3, "bFrameIndex", bFrameIndex, 2, "Index of this frame descriptor", 0); 
    AddFieldBreak();

    AddEntry( 4, "bmCapabilities", bmCapabilities, 2, "", 0);
    AddDescriptionOnly(Format("<br>D0: Still image supported %d",((bmCapabilities >> 0) & 0x01))); 
    AddDescriptionOnly(Format("<br>D7..1: Reserved %d"     , bmCapabilities >>1 )           ); 
    AddFieldBreak();

    AddEntry( 5, "wWidth", wWidth, 4, "Width of decoded bitmap frame in pixels", 0); 
    AddFieldBreak();

    AddEntry( 7, "wHeight", wHeight, 4, "Height of decoded bitmap frame in pixels", 0); 
    AddFieldBreak();

    AddEntry( 9, "dwMinBitRate", dwMinBitRate, 8, "Specifies the minimum bit rate at the longest frame interval in units of bps at which the data can be transmitted", 0); 
    AddFieldBreak();

    AddEntry( 13, "dwMaxBitRate", dwMaxBitRate, 8, "Specifies the maximum bit rate at the shortest frame interval in units of bps at which the data can be transmitted", 0); 
    AddFieldBreak();

    AddEntry( 17, "dwMaxVideoFrameBufferSize", dwMaxVideoFrameBufferSize, 8, "Specifies the maximum number of bytes that the compressor will produce for a video frame or still image", 0); 
    AddFieldBreak();

    AddEntry( 21, "dwDefaultFrameInterval", dwDefaultFrameInterval, 8, "Specifies the frame interval the device would like to indicate for use as a default", 0); 
    AddFieldBreak();

    AddEntry( 25, "bFrameIntervalType", bFrameIntervalType, 2, "Indicates how the frame interval can be programmed. 0: Continuous frame interval 1..255: The number of discrete frame", 0); 
    AddFieldBreak();
    
    if(bFrameIntervalType == 0)
    {
        dwMinFrameInterval  = GetDataLong(base+26);
        dwMaxFrameInterval  = GetDataLong(base+30);
        dwFrameIntervalStep = GetDataLong(base+34);

        AddEntry( 26, "dwMinFrameInterval", dwMinFrameInterval, 8, "Shortest frame interval supported (at highest frame rate), in 100 ns units", 0); 
        AddFieldBreak();

        AddEntry( 30, "dwMaxFrameInterval", dwMaxFrameInterval, 8, "Longest frame interval supported (at lowest frame rate), in 100 ns units", 0); 
        AddFieldBreak();

        AddEntry( 34, "dwFrameIntervalStep", dwFrameIntervalStep, 8, "Indicates granularity of frame interval range, in 100 ns units", 0); 
        AddFieldBreak();
    }
    else
    {
        for(FrameInterval = 1; FrameInterval <= bFrameIntervalType; FrameInterval = FrameInterval + 1 )
        {
            dwCurFrameInterval = GetDataLong(base+26+((FrameInterval - 1) * 4));
            dwFrameIntervalS  = Format("dwFrameInterval(%d)", FrameInterval);
            
            if(FrameInterval == bFrameIntervalType)
                FrameIntervalDesc = "Longest frame interval supported (at lowest frame rate), in 100 ns units";
            else
               FrameIntervalDesc = "Shortest frame interval supported (at highest frame rate), in 100 ns units";
            
            AddEntry( 26+((FrameInterval - 1) * 4), dwFrameIntervalS, dwCurFrameInterval, 8, FrameIntervalDesc, 0); 
            AddFieldBreak();
        }
    }
    return 1; # decoded it
}

FinishUndecodedData(bLength, amount_decoded)
{
    AddLineOfText(Format ("Remaining Undecoded %d Bytes:", bLength-amount_decoded));
    OutputUnknownData(bLength, amount_decoded);
    AddFieldBreak();
}
    

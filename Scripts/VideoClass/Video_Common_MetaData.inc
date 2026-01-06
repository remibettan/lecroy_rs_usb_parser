set ModuleType     = "DataBlock Decoder";

const ErrorColor       = 0x0000FF;

const MaxShowDataBlockSize = 12;
set CurrentPayloadColor = 0;

const Tabular_Def_Table = Map( 
[   
    #----------------------------------------------------------------------------------------------------------------------
    #       id                     ,      colId                          , 		containerCellId
    #----------------------------------------------------------------------------------------------------------------------
    [ CELL_VIDEO_REQUEST           , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE   , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ CELL_VIDEO_CONTROLL_SELECTOR , TABULAR_SCRIPT_COLUMN_ID_NONE      , TABULAR_SCRIPT_CONTAINER_CELL_ID_MISC ],
    [ CELL_REQUEST                 , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE   , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ CELL_WVALUE                  , TABULAR_SCRIPT_COLUMN_ID_NONE      , TABULAR_SCRIPT_CONTAINER_CELL_ID_MISC ],
    [ CELL_VIDEO_STATUS_TYPE       , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE   , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ CELL_VIDEO_EVENT             , TABULAR_SCRIPT_COLUMN_ID_NONE      , TABULAR_SCRIPT_CONTAINER_CELL_ID_MISC ]
] );

set bmRgbImageInfoBitmapTable =
[
    [  0, "Is Privacy       " ],
    [  1, "Is Sync          " ],
    [  2, "Is Pair          " ]
];

set bmDepthImageInfoBitmapTable =
[
    [  0, "Is Privacy       " ],
    [  1, "Is Sync          " ],
    [  2, "Is HVGA          " ]
];

DoProcessDataFirstPart()
{
    FullyDecoded = 1;
    ProcessDataInit();   #Doesn't Exist, not in use anymore
    
    
    Speed        = GetDecoderHeaderByte(0);    
    UsbSpecLevel = GetDecoderHeaderByte(1);
    out.Decoded = 0;    

    AddDecodedTextHeader(); #Exists, but commented out, not in use anymore
    AddSeparator();
    FieldColor = VideoCaptionColor;
    AddCaptionCell("Video","Class","In order to view comments in text field, user must expand this caption cell",_MONOCOLOR);  # will allow for the expansion of certain fields
    AddSeparator();
}


# must set CurrentPayloadColor before calling.
DoVideoPayloadHeader(ep)
{
    if (in.DataLength == 0)
    {
       FieldColor = CurrentPayloadColor;
       AddPayLoadCell("No", "Data", "No Header or Data Recieved in this transaction");
       AddSeparator();
       out.Decoded = 0;
       return (1);
    }
    
    AddDecodedTextHeader();
    AddSeparator();
    bHeaderLength = GetDataByte(0);
    FieldColor = CurrentPayloadColor;
    
    out.Decoded = 1;
    if (bHeaderLength < 2)
    {
        FieldColor = ErrorColor;
        AddPayLoadCell("bHeaderLength", Format ("0x%02X", bHeaderLength), "ERROR: bHeaderLength can NOT be less than 2");
        FieldColor = CurrentPayloadColor;
    }
    else if (bHeaderLength > 0xF8)
    {
        FieldColor = ErrorColor;
        AddPayLoadCell("bHeaderLength", Format ("0x%02X", bHeaderLength), "ERROR: bHeaderLength can NOT be greater than 144");
        FieldColor = CurrentPayloadColor;
    }
    else
    {
        bmHeaderInfo = GetDataByte(1);
		
        if (in.Expanded)
        {
			if (!metaDataSummary)
			{
				AddPayLoadCell("FrmId", Format ("%d", (bmHeaderInfo & 0x01)), Format("Frame Id:  Toggles with new frame.   bmHeaderInfo = 0x%02X", bmHeaderInfo));
				if ((bmHeaderInfo >> 1) & 0x01)
				{
					AddPayLoadCell("EOFrm", "Yes", Format("End of Frame: The following payload data marks the end of the current\nvideo or still image frame.   bmHeaderInfo = 0x%02X", bmHeaderInfo));
				}
				else
				{
					AddPayLoadCell("EOFrm", "No", Format("End of Frame: The following payload is NOT the end of the current\nvideo or still image frame.   bmHeaderInfo = 0x%02X", bmHeaderInfo));
				}
				
				if ((bmHeaderInfo >> 5) & 0x01)
				{
					AddPayLoadCell("Stl Img", "Yes", Format("Still Image: The following data is part of a still image frame.   bmHeaderInfo = 0x%02X", bmHeaderInfo));
				}
				else
				{
					AddPayLoadCell("Stl Img", "No", Format("Still Image: The following data is NOT part of a still image frame.   bmHeaderInfo = 0x%02X", bmHeaderInfo));
				}
				
				if ((bmHeaderInfo >> 6) & 0x01)
				{
					FieldColor = ErrorColor;
					AddPayLoadCell("Error", "Yes", Format("Error found in the video or still image transmission for this payload.   bmHeaderInfo = 0x%02X", bmHeaderInfo));
					FieldColor = CurrentPayloadColor;
				}
				else
				{
					AddPayLoadCell("Error", "No", Format("No Error in video or still image transmission for this payload.   bmHeaderInfo = 0x%02X", bmHeaderInfo));
				}
				
				AddPayLoadCell("EOH", Format ("%d", ((bmHeaderInfo >> 7) & 0x01)), Format("End of Header: If = 1, this is the last header group in the packet.   bmHeaderInfo = 0x%02X", bmHeaderInfo));
			}
        }
        else
        {
             AddPayLoadCell("bmHeaderInfo", Format ("0x%02X", bmHeaderInfo), 
                 ToBitDecode(bmHeaderInfoBitmapTable, bmHeaderInfo, ""));
        }
        out.Decoded = 2;
        
        ptOffset = 0;
        
        
        if (bmHeaderInfo & 4)
        {
            dwPresentationTime = GetDataLong(2);
            ptOffset = 4; 
            AddPayLoadCell("dwPresentationTime", Format ("%lu", dwPresentationTime), Format ("Decimal val: %u", dwPresentationTime));
            out.Decoded += 4;
        }
        
        if (bmHeaderInfo & 8)
        {
            sourceClock = GetDataLong(2+ptOffset);
            frameCount  = GetDataWord(6+ptOffset);
			if (!metaDataSummary)
			{
				AddPayLoadCell("Frame:Clock", 
					Format ("0x%04X:", frameCount) +  Format ("0x%08X", sourceClock), 
					Format ("scrSourceClock     Decimal vals:  Frame:%u  ", frameCount) +  Format ("Clock:%u", sourceClock));
			}
        }
		
		if (0xf8 == bHeaderLength || 0xC8 == bHeaderLength)
		{
			AddSeparator();
			
			#metaData Support, it will start after the basic header of 12 bytes
			metaDataStart = ptOffset + 8;
			
			if (!metaDataSummary)
			{
				AddCaptionCell("Intel Capture timing","Class","In order to view comments in text field, user must expand this caption cell",_MONOCOLOR); 
			}
			 
			if (in.Expanded)
			{ 
				
				metaDataID = GetDataLong(metaDataStart);				
				metaDataString = Find(MetaDataStructTypeMap, metaDataID);
				if (!metaDataSummary)
				{
					AddSimplePLCell("metaDataID", metaDataString[1], "MetaData ID");						
				}
				
				size = GetDataLong(metaDataStart + 4);
				if (!metaDataSummary)
				{
					AddSimplePLCell("Size", Format ("0x%08X", size), "MetaData size");
				}
				
				version = GetDataLong(metaDataStart + 8);
				if (!metaDataSummary)
				{
					AddSimplePLCell("Version", Format ("%d", version), "Version");
				}
				
				flag = GetDataLong(metaDataStart + 12);
				if (!metaDataSummary)
				{
					AddSimplePLCell("Flag", Format ("0x%08X", flag), ToBitDecode(bmIntelCaptureTimingFlags, flag, ""));
				}
									
				frameCounter = GetDataLong(metaDataStart + 16);
				AddSimplePLCell("Frame Counter", Format ("%d", frameCounter), Format ("Frame counter 0x%08X", frameCounter));
				
				opticalTimestamp = GetDataLong(metaDataStart + 20);
				if (!metaDataSummary)
				{
					AddSimplePLCell("Optical Timestamp", Format ("%d", opticalTimestamp), "Optical time stamp in microseconds unit");
				}
				
				readoutTime = GetDataLong(metaDataStart + 24);
				if (!metaDataSummary)
				{
					AddSimplePLCell("Readout Time", Format ("%d", readoutTime), "The readout time in microseconds unit");
				}
				
				exposureTime = GetDataLong(metaDataStart + 28);
				AddSimplePLCell("Exposure Time", Format ("%d", exposureTime), "The exposure time in microseconds unit");
				
				frameInterval = GetDataLong(metaDataStart + 32);
				AddSimplePLCell("Frame Interval", Format ("%d", frameInterval), "The frame interval in microseconds unit");
			
				pipeLatency = GetDataLong(metaDataStart + 36);
				if (!metaDataSummary)
				{
					AddSimplePLCell("Pipe Latency", Format ("%d", pipeLatency), "The latency between start of frame to frame ready in USB buffer");
				}
			}
			
			AddSeparator();
			
			nextHdr = GetDataLong(metaDataStart + 40);
			if (nextHdr == 0x3)
			{	
				#if (!metaDataSummary)
				{
					AddCaptionCell("Capture stats","Class","In order to view comments in text field, user must expand this caption cell",_MONOCOLOR);  # will allow for the expansion of certain fields
				}
				if (in.Expanded)
				{ 
					
					metaDataString = Find(MetaDataStructTypeMap, nextHdr);
					if (!metaDataSummary)
					{
						AddSimplePLCell("MetaDataID", metaDataString[1], "MetaData ID");
					}
					
					size = GetDataLong(metaDataStart + 44);
					if (!metaDataSummary)
					{
						AddSimplePLCell("Size", Format ("0x%08X", size), "MetaData size");
					}
					
					flag = GetDataLong(metaDataStart + 48);
					if (!metaDataSummary)
					{
						AddSimplePLCell("Flag", Format ("0x%08X", flag), ToBitDecode(bmCapturStatsFlags, flag, ""));
					}
					
					reserved = GetDataLong(metaDataStart + 52);
					if (!metaDataSummary)
					{
						AddSimplePLCell("Reserved", Format ("0x%08X", reserved), "Reserved");
					}
					
					exposureTime = GetDataLong(metaDataStart + 56,8);
					if (!metaDataSummary)
					{
						AddSimplePLCell("Exposure Time", Format ("%d", exposureTime), "Exposure Time in microseconds unit");
					}
					
					exposureCompensationFlags = GetDataByteArray(metaDataStart + 64,8);
					if (!metaDataSummary)
					{
						AddSimplePLCell("Exposure Compensation Flags", Format ("0x%08X", exposureCompensationFlags[0]), "Exposure Compensation Flags");
					}
					
					exposureCompensationValue = GetDataLong(metaDataStart + 72);
					if (!metaDataSummary)
					{
						AddSimplePLCell("Exposure Compensation Value", Format ("0x%08X", exposureCompensationValue), "Exposure Compensation Value");
					}

					if (!metaDataSummary)	
					{					
						IsoSpeed = GetDataLong(metaDataStart + 76);
						AddSimplePLCell("ISO Speed", Format ("0x%08X", IsoSpeed), "Iso Speed");
						
						FocusState = GetDataLong(metaDataStart + 80);
						AddSimplePLCell("Focus State", Format ("0x%08X", FocusState), "Focus State");
						
						LensPosition = GetDataLong(metaDataStart + 84);
						AddSimplePLCell("Lens Position", Format ("0x%08X", LensPosition), "Lens position a.k.a Focus");
						
						WhiteBalance = GetDataLong(metaDataStart + 88);
						AddSimplePLCell("White Balance", Format ("0x%08X", WhiteBalance), "White balance");
						
						Flash = GetDataLong(metaDataStart + 92);
						AddSimplePLCell("Flash", Format ("0x%08X", Flash), "Flash");
						
						FlashPower = GetDataLong(metaDataStart + 96);
						AddSimplePLCell("Flash Power", Format ("0x%08X", FlashPower), "Flash Power");
						
						ZoomFactor = GetDataLong(metaDataStart + 100);
						AddSimplePLCell("Zoom Factor", Format ("0x%08X", ZoomFactor), "Zoom Factor");
						
						SceneMode = GetDataByteArray(metaDataStart + 104,8);
						AddSimplePLCell("Scene Mode", Format ("0x%08X", SceneMode[0]), "Scene Mode");
					}	
					
					SensorFramerate = GetDataByteArray(metaDataStart + 112,8);
					AddSimplePLCell("Sensor FPS", Format ("%d", SensorFramerate[0]), "Sensor FrameRate");
					
			
				}
			
				AddSeparator();
				
				nextHdr = GetDataLong(metaDataStart + 120);
				
				if (nextHdr == 0x80000000)
				{
					if (!metaDataSummary)
					{
						AddCaptionCell("Intel depth control","Class","In order to view comments in text field, user must expand this caption cell",_MONOCOLOR);  # will allow for the expansion of certain fields
					}
					
					if (in.Expanded)
					{ 
						
						if (!metaDataSummary)	
						{
							metaDataString = Find(MetaDataStructTypeMap, nextHdr);
							AddSimplePLCell("MetaDataID", metaDataString[1], "MetaData ID");
							
							size = GetDataLong(metaDataStart + 124);
							AddSimplePLCell("Size", Format ("0x%08X", size), "MetaData size");
									
							version = GetDataLong(metaDataStart + 128);
							AddSimplePLCell("Version", Format ("%d", version), "Version");
								
							flag = GetDataLong(metaDataStart + 132);
							AddSimplePLCell("Flag", Format ("0x%08X", flag), ToBitDecode(bmIntelDepthControlFlags, flag, ""));
						}
						
						manualGain = GetDataLong(metaDataStart + 136);
						AddSimplePLCell("Manual Gain", Format ("%d", manualGain), "Manual gain value");
						
						manualExposure = GetDataLong(metaDataStart + 140);
						AddSimplePLCell("Manual Exposure", Format ("%d", manualExposure), "Manual exposure - control value in 100us units");
						
						laserPower = GetDataLong(metaDataStart + 144);
						AddSimplePLCell("Laser Power", Format ("%d", laserPower), "Laser power value");
						
						autoExposureMode = GetDataLong(metaDataStart + 148);
						metaDataString = Find(MetaDataBoolMap, autoExposureMode);
						AddSimplePLCell("Auto Exposure", metaDataString[1], Format("AE mode %d", autoExposureMode));
						
						if (!metaDataSummary)
						{
							exposurePriority = GetDataLong(metaDataStart + 152);
							AddSimplePLCell("ExposurePriority", Format ("%d", exposurePriority), "Exposure priority");
							
							exposureROILeft = GetDataLong(metaDataStart + 156);
							AddSimplePLCell("ExposureROI Left", Format ("%d", exposureROILeft), "Exposure ROI left");
							
							exposureROIRight = GetDataLong(metaDataStart + 160);
							AddSimplePLCell("ExposureROI Right", Format ("%d", exposureROIRight), "Exposure ROI right");
							
							exposureROITop = GetDataLong(metaDataStart + 164);
							AddSimplePLCell("ExposureROI Top", Format ("%d", exposureROITop), "Exposure ROI top");
							
							exposureROIBottom = GetDataLong(metaDataStart + 168);
							AddSimplePLCell("ExposureROI Bottom", Format ("%d", exposureROIBottom), "Exposure ROI bottom");
						}
						
						preset = GetDataLong(metaDataStart + 172);
						AddSimplePLCell("Preset", Format ("%d", preset), "preset");
						
						#projType = GetDataByte(metaDataStart + 173);
						#AddSimplePLCell("Projector Type", Format ("%d", projType), "Projector Type (Led or Laser)");
						
						projectorMode = GetDataByte(metaDataStart + 176);
						metaDataString = Find(MetaDataProjectorModeMap, projectorMode);
						AddSimplePLCell("Projector Mode", metaDataString[1], "projectorMode");
						
						#ledPowerMode = GetDataByte(metaDataStart + 177);
						#metaDataString = Find(MetaDataProjectorModeMap, ledPowerMode);
						#AddSimplePLCell("LED Mode", metaDataString[1], "ledPowerMode");
						
						ledPower = GetDataWord(metaDataStart + 178);
						AddSimplePLCell("Led Power", Format ("%d", ledPower), "Led power value");
					}
					AddSeparator();
										
					nextHdr1 = GetDataLong(metaDataStart + 180);
					if (!metaDataSummary)	
					{
						AddCaptionCell("Intel configuration","Class","In order to view comments in text field, user must expand this caption cell",_MONOCOLOR);  # will allow for the expansion of certain fields
					}
					
					if (in.Expanded)
					{
						if (!metaDataSummary)	
						{
							metaDataString = Find(MetaDataStructTypeMap, nextHdr1);
							AddSimplePLCell("MetaDataID", metaDataString[1], "MetaData ID");
							
							size = GetDataLong(metaDataStart + 184);
							AddSimplePLCell("Size", Format ("0x%08X", size), "MetaData size");
							
							version = GetDataLong(metaDataStart + 188);
							AddSimplePLCell("Version", Format ("%d", version), "Version");
								
							flag = GetDataLong(metaDataStart + 192);
							AddSimplePLCell("Flag", Format ("0x%08X", flag), ToBitDecode(bmIntelConfigurationFlags, flag, ""));
						}
						
						MHwType = GetDataByte(metaDataStart + 196);		
						MHwTypeString = Find(HwTypeTypeMap, MHwType);
						AddSimplePLCell("HW Type",  MHwTypeString[1], Format ("Hardware Type %d", MHwType));
						
						SKUsID = GetDataByte(metaDataStart + 197);
						SkuString = Find(SkuTypeMap, SKUsID);
						AddPayLoadCell("SKUsID", SkuString[1], ToBitDecode(bmHSkuIdBitmapTable, SKUsID, ""));
						
						cookie = GetDataLong(metaDataStart + 198);
						if (!metaDataSummary)	
						{
							AddSimplePLCell("Cookie", Format ("0x%08X", cookie), "Cookie");
						}
						
						format = GetDataLong(metaDataStart + 202);
						width = GetNBits ( format, 0, 16 );
						result = GetNBits ( format, 16, 16 );
						
						if (MHwType == 0) # DS5U USB HW
						{
							if (ep == 2)
							{
								formatString = Find(depthCameraFormats, result);
							}
							else
							{
								formatString = Find(YCameraFormats, result);
							}
							AddSimplePLCell("Format", formatString[1], Format("format index %d, ep %d", result, ep));
						}
						else
						{
							dataTypeString = Find(MipiDataTypes, result);
							AddSimplePLCell("DataType", dataTypeString[1], Format("DataType 0x%x", result));
						}
							
						AddSimplePLCell("Width", Format ("%d", width), "width");
						
						resolution = GetDataLong(metaDataStart + 206);
						height = GetNBits ( resolution, 16, 16 );
						AddSimplePLCell("Height", Format ("%d", height), "Height");
						
						fps = GetNBits ( resolution, 0, 16 );
						AddSimplePLCell("FPS", Format ("%d", fps), "FPS");
						
						data = GetDataLong(metaDataStart + 210);
						trigger = GetNBits ( data, 16, 16 );
						AddSimplePLCell("Trigger", Format ("%d", trigger), ToBitDecode(bmIntelConfigurationTriggerMode, trigger, ""));
										
						calibrationCount = GetNBits ( data, 0, 16 );
						if (!metaDataSummary)
						{
							AddSimplePLCell("Calibration Count", Format ("%d", calibrationCount), "Calibration count");
						}
						
					
					}
				}
				else if (nextHdr == 0x80000005)
				{
					AddCaptionCell("Intel RGB control","Class","In order to view comments in text field, user must expand this caption cell",_MONOCOLOR);  # will allow for the expansion of certain fields
					if (in.Expanded)
					{ 
						
						metaDataString = Find(MetaDataStructTypeMap, nextHdr);
						AddSimplePLCell("MetaDataID", metaDataString[1], "MetaData ID");
						
						size = GetDataLong(metaDataStart + 124);
						AddSimplePLCell("Size", Format ("0x%08X", size), "MetaData size");
								
						version = GetDataLong(metaDataStart + 128);
						AddSimplePLCell("Version", Format ("%d", version), "Version");
							
						flag = GetDataLong(metaDataStart + 132);
						AddSimplePLCell("Flag", Format ("0x%08X", flag), ToBitDecode(bmIntelRgbControlFlags, flag, ""));
						
						manualBrightness = GetDataLong(metaDataStart + 136);
						AddSimplePLCell("Manual brightnes", Format ("%d", manualBrightness), "Manual brightnes value");
						
						contrast = GetDataLong(metaDataStart + 140);
						AddSimplePLCell("Manual Exposure", Format ("%d", contrast), "Manual contrast");
						
						saturation = GetDataLong(metaDataStart + 144);
						AddSimplePLCell("Saturation", Format ("%d", saturation), "Laser saturation value");
					
						sharpness = GetDataLong(metaDataStart + 148);
						AddSimplePLCell("Sharpness", Format ("%d", sharpness), "Sharpness");
						
						autoExposureMode = GetDataLong(metaDataStart + 152);
						AddSimplePLCell("Auto Exposure Mode", Format ("%d", autoExposureMode), "Auto Exposure mode");
						
						auto_WB_Temp = GetDataLong(metaDataStart + 156);
						AddSimplePLCell("Auto white balance temprature", Format ("%d", auto_WB_Temp), "Auto white balance temperature");
						
						gain = GetDataLong(metaDataStart + 160);
						AddSimplePLCell("Gain", Format ("%d", gain), "Gain");
						
						backlight_Comp = GetDataLong(metaDataStart + 164);
						AddSimplePLCell("Laser backlight comp", Format ("%d", backlight_Comp), "Laser backlight Compensation");
						
						gamma = GetDataLong(metaDataStart + 168);
						AddSimplePLCell("Gama", Format ("%d", gamma), "Gama");
						
						hue = GetDataLong(metaDataStart + 172);
						AddSimplePLCell("Hue", Format ("%d", hue), "Hue");
						
						manualExp = GetDataLong(metaDataStart + 176);
						AddSimplePLCell("Manual exposure", Format ("%d", manualExp), "Manual exposure");
						
						manual_WB = GetDataLong(metaDataStart + 180);
						AddSimplePLCell("White balance", Format ("%d", manual_WB), "Manual white balance temperature");
						
						powerLineFrequncy = GetDataLong(metaDataStart + 184);
						AddSimplePLCell("Power line frequncy", Format ("%d", powerLineFrequncy), "Power line frequncy");
						
						low_Light_Comp = GetDataLong(metaDataStart + 188);
						AddSimplePLCell("AE priority control", Format ("%d", low_Light_Comp), "Low light comp");
					}
					AddSeparator();
										
					nextHdr1 = GetDataLong(metaDataStart + 192);
					AddCaptionCell("Intel configuration","Class","In order to view comments in text field, user must expand this caption cell",_MONOCOLOR);  # will allow for the expansion of certain fields
					
					if (in.Expanded)
					{
					
						metaDataString = Find(MetaDataStructTypeMap, nextHdr1);
						AddSimplePLCell("MetaDataID", metaDataString[1], "MetaData ID");
						
						size = GetDataLong(metaDataStart + 196);
						AddSimplePLCell("Size", Format ("0x%08X", size), "MetaData size");
						
						version = GetDataLong(metaDataStart + 200);
						AddSimplePLCell("Version", Format ("%d", version), "Version");
							
						flag = GetDataLong(metaDataStart + 204);
						AddSimplePLCell("Flag", Format ("0x%08X", flag), ToBitDecode(bmIntelConfigurationFlags, flag, ""));
						
						MHwType = GetDataByte(metaDataStart + 208);		
						MHwTypeString = Find(HwTypeTypeMap, MHwType);
						AddSimplePLCell("HW Type",  MHwTypeString[1], Format ("Hardware Type %d", MHwType));
						
						SKUsID = GetDataWord(metaDataStart + 209);					
						AddPayLoadCell("SKUsID", Format ("0x%02X", SKUsID), ToBitDecode(bmHSkuIdBitmapTable, SKUsID, ""));
						
						cookie = GetDataLong(metaDataStart + 210);
						AddSimplePLCell("Cookie", Format ("0x%08X", cookie), "Cookie");
						
						format = GetDataLong(metaDataStart + 214);
						width = GetNBits ( format, 0, 16 );
						result = GetNBits ( format, 16, 16 );
						
						formatString = Find(rgbCameraFormats, result);

						AddSimplePLCell("Format", formatString[1], Format("format index %d", result));
						AddSimplePLCell("Width", Format ("%d", width), "width");
						
						resolution = GetDataLong(metaDataStart + 218);
						height = GetNBits ( resolution, 16, 16 );
						AddSimplePLCell("Height", Format ("%d", height), "Height");
						
						fps = GetNBits ( resolution, 0, 16 );
						AddSimplePLCell("FPS", Format ("%d", fps), "FPS");
						
						data = GetDataLong(metaDataStart + 222);
						trigger = GetNBits ( data, 16, 16 );
						AddSimplePLCell("Trigger", Format ("%d", trigger), ToBitDecode(bmIntelConfigurationTriggerMode, trigger, ""));
										
						calibrationCount = GetNBits ( data, 0, 16 );
						AddSimplePLCell("Calibration Count", Format ("%d", calibrationCount), "Calibration count");
						
					
					}
				}
				else if (nextHdr == 0x80000004)
				{
				
					AddCaptionCell("Intel fishEye control","Class","In order to view comments in text field, user must expand this caption cell",_MONOCOLOR);  # will allow for the expansion of certain fields
					if (in.Expanded)
					{ 
						
						metaDataString = Find(MetaDataStructTypeMap, nextHdr);
						AddSimplePLCell("MetaDataID", metaDataString[1], "MetaData ID");
						
						size = GetDataLong(metaDataStart + 124);
						AddSimplePLCell("Size", Format ("0x%08X", size), "MetaData size");
								
						version = GetDataLong(metaDataStart + 128);
						AddSimplePLCell("Version", Format ("%d", version), "Version");
							
						flag = GetDataLong(metaDataStart + 132);
						AddSimplePLCell("Flag", Format ("0x%08X", flag), ToBitDecode(bmIntelFishEyeControlFlags, flag, ""));
						
						manualGain = GetDataLong(metaDataStart + 136);
						AddSimplePLCell("Manual Gain", Format ("%d", manualGain), "Manual gain value");
						
						manualExposure = GetDataLong(metaDataStart + 140);
						AddSimplePLCell("Manual Exposure", Format ("%d", manualExposure), "Manual exposure");
						
					}
					AddSeparator();
					
					nextHdr1 = GetDataLong(metaDataStart + 144);
					
					AddCaptionCell("Intel configuration","Class","In order to view comments in text field, user must expand this caption cell",_MONOCOLOR);  # will allow for the expansion of certain fields
					
					if (in.Expanded)
					{
					
						metaDataString = Find(MetaDataStructTypeMap, nextHdr1);
						AddSimplePLCell("MetaDataID", metaDataString[1], "MetaData ID");
						
						size = GetDataLong(metaDataStart + 148);
						AddSimplePLCell("Size", Format ("0x%08X", size), "MetaData size");
						
						version = GetDataLong(metaDataStart + 152);
						AddSimplePLCell("Version", Format ("%d", version), "Version");
							
						flag = GetDataLong(metaDataStart + 156);
						AddSimplePLCell("Flag", Format ("0x%08X", flag), ToBitDecode(bmIntelConfigurationFlags, flag, ""));
						
						MHwType = GetDataByte(metaDataStart + 160);		
						MHwTypeString = Find(HwTypeTypeMap, MHwType);
					
						AddSimplePLCell("HW Type",  MHwTypeString[1], Format ("Hardware Type %d", MHwType));
						
						SKUsID = GetDataWord(metaDataStart + 161);					
						AddPayLoadCell("SKUsID", Format ("0x%02X", SKUsID), ToBitDecode(bmHSkuIdBitmapTable, SKUsID, ""));
						
						cookie = GetDataLong(metaDataStart + 162);
						AddSimplePLCell("Cookie", Format ("0x%08X", cookie), "Cookie");
						
						format = GetDataLong(metaDataStart + 166);
						width = GetNBits ( format, 0, 16 );
						result = GetNBits ( format, 16, 16 );
						
						formatString = Find(fishEyeCameraFormats, result);

						AddSimplePLCell("Format", formatString[1], Format("format index %d", result));
						AddSimplePLCell("Width", Format ("%d", width), "width");
						
						resolution = GetDataLong(metaDataStart + 170);
						height = GetNBits ( resolution, 16, 16 );
						AddSimplePLCell("Height", Format ("%d", height), "Height");
						
						fps = GetNBits ( resolution, 0, 16 );
						AddSimplePLCell("FPS", Format ("%d", fps), "FPS");
						
						data = GetDataLong(metaDataStart + 174);
						trigger = GetNBits ( data, 16, 16 );
						AddSimplePLCell("Trigger", Format ("%d", trigger), ToBitDecode(bmIntelConfigurationTriggerMode, trigger, ""));
						
						calibrationCount = GetNBits ( data, 0, 178);
						AddSimplePLCell("Calibration Count", Format ("%d", calibrationCount), "Calibration count");
						
					
					}
				
				
				}
				
				
			}
			
			else if (nextHdr == 0x4)
			{
				AddCaptionCell("Camera Extrinsic","Class","In order to view comments in text field, user must expand this caption cell",_MONOCOLOR);  # will allow for the expansion of certain fields
				if (in.Expanded)
				{ 
						
					metaDataString = Find(MetaDataStructTypeMap, nextHdr);
					AddSimplePLCell("MetaDataID", metaDataString[1], "MetaData ID");
					
					size = GetDataLong(metaDataStart + 44);
					AddSimplePLCell("Size", Format ("0x%08X", size), "MetaData size");
					
					transformCount = GetDataLong(metaDataStart + 48);
					AddSimplePLCell("Transform Count", Format ("%d", transformCount), "transformCount");
					
					GUID = GetDataByteArray(metaDataStart + 52,16);
					AddCell("GUID");
					AddDataCell(GUID,_BYTES);
					
					positionX = GetDataLong(metaDataStart + 68);
					AddSimplePLCell("positionX", Format ("0x%08X", positionX), "positionX need to be translated to float");
					
					positionY = GetDataLong(metaDataStart + 72);
					AddSimplePLCell("positionY", Format ("0x%08X", positionY), "positionY, need to be translated to float");
					
					positionZ = GetDataLong(metaDataStart + 76);
					AddSimplePLCell("positionZ", Format ("0x%08X", positionZ), "positionZ, need to be translated to float");
					
					orientationX = GetDataLong(metaDataStart + 80);
					AddSimplePLCell("orientationX", Format ("0x%08X", orientationX), "orientationX, need to be translated to float");
					
					orientationY = GetDataLong(metaDataStart + 84);
					AddSimplePLCell("orientationY", Format ("0x%08X", orientationY), "orientationY, need to be translated to float");
					
					orientationZ = GetDataLong(metaDataStart + 88);
					AddSimplePLCell("orientationZ", Format ("0x%08X", orientationZ), "orientationZ, need to be translated to float");
					
					orientationW = GetDataLong(metaDataStart + 92);
					AddSimplePLCell("orientationW", Format ("0x%08X", orientationW), "orientationW, need to be translated to float");
				}
				AddSeparator();
				
				nextHdr = GetDataLong(metaDataStart + 96);
				AddCaptionCell("Camera Intrinsics","Class","In order to view comments in text field, user must expand this caption cell",_MONOCOLOR);  # will allow for the expansion of certain fields
				if (in.Expanded)
				{ 
						
					metaDataString = Find(MetaDataStructTypeMap, nextHdr);
					AddSimplePLCell("MetaDataID", metaDataString[1], "MetaData ID");
					
					size = GetDataLong(metaDataStart + 100);
					AddSimplePLCell("Size", Format ("0x%08X", size), "MetaData size");
					
					transformCount = GetDataLong(metaDataStart + 104);
					AddSimplePLCell("Transform Count", Format ("%d", transformCount), "transformCount");
					
					width = GetDataLong(metaDataStart + 108);
					AddSimplePLCell("Width", Format ("%d", width), "width");
					
					height = GetDataLong(metaDataStart + 112);
					AddSimplePLCell("Height", Format ("%d", height), "Height");
					
					FocalLengthX = GetDataLong(metaDataStart + 116);
					AddSimplePLCell("Focal Length X", Format ("0x%08X", FocalLengthX), "Focal Length X, need to be translated to float ");
					
					FocalLengthY = GetDataLong(metaDataStart + 120);
					AddSimplePLCell("Focal Length Y", Format ("0x%08X", FocalLengthY), "Focal Length Y, need to be translated to float ");
					
					PrincipalPointX = GetDataLong(metaDataStart + 124);
					AddSimplePLCell("Principal Point X", Format ("0x%08X", PrincipalPointX), "Principal Point X, need to be translated to float ");
					
					PrincipalPointY = GetDataLong(metaDataStart + 128);
					AddSimplePLCell("Principal Point Y", Format ("0x%08X", PrincipalPointY), "Principal Point Y, need to be translated to float ");
					
					radialK1 = GetDataLong(metaDataStart + 132);
					AddSimplePLCell("Radial K1", Format ("0x%08X", radialK1), "radial K1, need to be translated to float ");
					
					radialK2 = GetDataLong(metaDataStart + 136);
					AddSimplePLCell("Radial K2", Format ("0x%08X", radialK2), "radial K2, need to be translated to float ");
					
					radialK3 = GetDataLong(metaDataStart + 140);
					AddSimplePLCell("Radial K3", Format ("0x%08X", radialK3), "radial K3, need to be translated to float ");
					
					tangentialP1 = GetDataLong(metaDataStart + 144);
					AddSimplePLCell("Tangential P1", Format ("0x%08X", tangentialP1), "Tangential P1, need to be translated to float ");
					
					tangentialP2 = GetDataLong(metaDataStart + 148);
					AddSimplePLCell("Tangential P2", Format ("0x%08X", tangentialP2), "Tangential P2, need to be translated to float ");
				}	
			}
			
			else if (nextHdr == 0x80000007)
			{
				AddCaptionCell("Camera Extrinsic FE","Class","In order to view comments in text field, user must expand this caption cell",_MONOCOLOR);  # will allow for the expansion of certain fields
				if (in.Expanded)
				{ 
						
					metaDataString = Find(MetaDataStructTypeMap, nextHdr);
					AddSimplePLCell("MetaDataID", metaDataString[1], "MetaData ID");
					
					size = GetDataLong(metaDataStart + 44);
					AddSimplePLCell("Size", Format ("0x%08X", size), "MetaData size");
					
					transformCount = GetDataLong(metaDataStart + 48);
					AddSimplePLCell("Transform Count", Format ("%d", transformCount), "transformCount");
					
					GUID = GetDataByteArray(metaDataStart + 52,16);
					AddCell("GUID");
					AddDataCell(GUID,_BYTES);
					
					R_FE1 = GetDataLong(metaDataStart + 68);
					AddSimplePLCell("R_FE1", Format ("0x%08X", R_FE1), "R_FE1 need to be translated to float");
					
					R_FE2 = GetDataLong(metaDataStart + 72);
					AddSimplePLCell("R_FE2", Format ("0x%08X", R_FE2), "R_FE2, need to be translated to float");
					
					R_FE3 = GetDataLong(metaDataStart + 76);
					AddSimplePLCell("R_FE3", Format ("0x%08X", R_FE3), "R_FE3, need to be translated to float");
					
					R_FE4 = GetDataLong(metaDataStart + 80);
					AddSimplePLCell("R_FE4", Format ("0x%08X", R_FE4), "R_FE4, need to be translated to float");
					
					R_FE5 = GetDataLong(metaDataStart + 84);
					AddSimplePLCell("R_FE5", Format ("0x%08X", R_FE5), "R_FE5, need to be translated to float");
					
					R_FE6 = GetDataLong(metaDataStart + 88);
					AddSimplePLCell("R_FE6", Format ("0x%08X", R_FE6), "R_FE6, need to be translated to float");
					
					R_FE7 = GetDataLong(metaDataStart + 92);
					AddSimplePLCell("R_FE7", Format ("0x%08X", R_FE7), "R_FE7, need to be translated to float");
					
					R_FE8 = GetDataLong(metaDataStart + 96);
					AddSimplePLCell("R_FE8", Format ("0x%08X", R_FE8), "R_FE8, need to be translated to float");
					
					R_FE9 = GetDataLong(metaDataStart + 100);
					AddSimplePLCell("R_FE9", Format ("0x%08X", R_FE9), "R_FE9, need to be translated to float");
									
					T_FE1 = GetDataLong(metaDataStart + 104);
					AddSimplePLCell("T_FE1", Format ("0x%08X", T_FE1), "T_FE1, need to be translated to float");
					
					T_FE2 = GetDataLong(metaDataStart + 108);
					AddSimplePLCell("T_FE2", Format ("0x%08X", T_FE2), "T_FE2, need to be translated to float");
					
					T_FE3 = GetDataLong(metaDataStart + 112);
					AddSimplePLCell("T_FE3", Format ("0x%08X", T_FE3), "T_FE3, need to be translated to float");
				}
				AddSeparator();
				
				nextHdr = GetDataLong(metaDataStart + 116);
				AddCaptionCell("Camera Intrinsics","Class","In order to view comments in text field, user must expand this caption cell",_MONOCOLOR);  # will allow for the expansion of certain fields
				if (in.Expanded)
				{ 
						
					metaDataString = Find(MetaDataStructTypeMap, nextHdr);
					AddSimplePLCell("MetaDataID", metaDataString[1], "MetaData ID");
					
					size = GetDataLong(metaDataStart + 120);
					AddSimplePLCell("Size", Format ("0x%08X", size), "MetaData size");
					
					transformCount = GetDataLong(metaDataStart + 124);
					AddSimplePLCell("Transform Count", Format ("%d", transformCount), "transformCount");
					
					width = GetDataLong(metaDataStart + 128);
					AddSimplePLCell("Width", Format ("%d", width), "width");
					
					height = GetDataLong(metaDataStart + 132);
					AddSimplePLCell("Height", Format ("%d", height), "Height");
					
					FocalLengthX = GetDataLong(metaDataStart + 136);
					AddSimplePLCell("Focal Length X", Format ("0x%08X", FocalLengthX), "Focal Length X, need to be translated to float ");
					
					FocalLengthY = GetDataLong(metaDataStart + 142);
					AddSimplePLCell("Focal Length Y", Format ("0x%08X", FocalLengthY), "Focal Length Y, need to be translated to float ");
					
					PrincipalPointX = GetDataLong(metaDataStart + 146);
					AddSimplePLCell("Principal Point X", Format ("0x%08X", PrincipalPointX), "Principal Point X, need to be translated to float ");
					
					PrincipalPointY = GetDataLong(metaDataStart + 150);
					AddSimplePLCell("Principal Point Y", Format ("0x%08X", PrincipalPointY), "Principal Point Y, need to be translated to float ");
					
					radialK1 = GetDataLong(metaDataStart + 154);
					AddSimplePLCell("Radial K1", Format ("0x%08X", radialK1), "radial K1, need to be translated to float ");
					
					radialK2 = GetDataLong(metaDataStart + 158);
					AddSimplePLCell("Radial K2", Format ("0x%08X", radialK2), "radial K2, need to be translated to float ");
					
					radialK3 = GetDataLong(metaDataStart + 162);
					AddSimplePLCell("Radial K3", Format ("0x%08X", radialK3), "radial K3, need to be translated to float ");
					
					tangentialP1 = GetDataLong(metaDataStart + 166);
					AddSimplePLCell("Tangential P1", Format ("0x%08X", tangentialP1), "Tangential P1, need to be translated to float ");
					
					tangentialP2 = GetDataLong(metaDataStart + 170);
					AddSimplePLCell("Tangential P2", Format ("0x%08X", tangentialP2), "Tangential P2, need to be translated to float ");
				}	
			}
			
			
		}			
		
		AddSeparator();
		AddCell("Frame Size", Format ("%u", in.DataLength - bHeaderLength), Format ("Payload size with Header: %u bytes", in.DataLength), 0x000080);

		out.Decoded = in.DataLength ;
    }
           
    AddSeparator();
}



####################################################################################
#                       USBTracer specific caption cell                            #
####################################################################################

AddSpecCaptionCell(caption, text, tooltip, FieldColor, addparam, addparam1, addparam2 )
{   
    AddCell(caption, text, tooltip, FieldColor, _USBBULK_HEADER, addparam, addparam1, addparam2 );        
    return 1;        
}




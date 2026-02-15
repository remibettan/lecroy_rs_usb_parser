
set ProbeCommitIVCAM = 1;

# 0 - PSR/ASR/AWG
# 1 - AWGT
# 2 - ASRC
# 3 - DS5U F416
# 4 - AWGC
# 5 - D585
# 6 - S585

set Ds5SkuType=4;

set metaDataSummary = 1;
set CurrentInterfacesMapPSR = 
[
    [   0xFF, "NotFound"],
	[   0x00, " Depth Control "],
	[   0x01, " Depth Stream "],
	[   0x02, " Y Stream "],
	[   0x03, " WinUsb(HWM) "]
];

set CurrentInterfacesMapASRC = 
[
    [   0xFF, "NotFound"],
	[   0x00, " Depth Control "],
	[   0x01, " Depth Stream "],
	[   0x02, " Y Stream "],
	[   0x03, " RGB Control "],
	[   0x04, " RGB Stream "],
	[   0x05, " WinUsb(HWM) "]
];

set CurrentInterfacesMapAWGT = 
[
    [   0xFF, "NotFound"],
	[   0x00, " Depth Control "],
	[   0x01, " Depth Stream "],
	[   0x02, " Y Stream "],
	[   0x03, " FishEye Control "],
	[   0x04, " FishEye Stream "],
	[   0x05, " HID "],
	[   0x06, " WinUsb(HWM) "]
];

set CurrentInterfacesMapS585 = 
[
    [   0xFF, "NotFound"],
	[   0x00, " Depth Control "],
	[   0x01, " Depth Stream "],
	[   0x02, " Y Stream "],
	[   0x03, " RGB Control "],
	[   0x04, " RGB Stream "],
	[   0x05, " HID "],
	[   0x06, " WinUsb(HWM) "],
	[   0x07, " CDC ACM Control "],
	[   0x08, " CDC ACM Data "],
	[   0x09, " CDC COM Control "],
	[   0x0A, " CDC COM Data "],
	[   0x0B, " Safety Camera Control "],
	[   0x0C, " Safety Camera Stream "],
	[   0x0D, " Occupancy Camera Control "],
	[   0x0E, " Occupancy Camera Stream "]
];

set rgbCameraFormats = 
[
	[ 0x00	, "undefined format" ],
	[ 0x01	, " sfRGB_YUY2 " ],
	[ 0x02	, " sfRGB_MJEG " ],
	[ 0x03	, " sfRGB_RAW " ],
	[ 0x04	, " sfRGB_M420 " ]
];

set rgbCameraResolutions = 
[
	[ 0x00	, "undefined resolution" ],
	[ 0x09	, " ff_1920x1080 " ],
	[ 0x08	, " ff_1280x720 " ],
	[ 0x07	, " ff_1280x800 " ],
	[ 0x06	, " ff_1280x720 " ],
	[ 0x05	, " ff_848x480 " ],
	[ 0x04	, " ff_640x480 " ],
	[ 0x03	, " ff_640x360 " ],
	[ 0x02	, " ff_480x270 " ],
	[ 0x01	, " ff_424x240 " ]
];

set S585RgbCameraResolutions = 
[
	[ 0x00	, "undefined resolution" ],
	[ 0x01	, " ff_320x240 " ],
	[ 0x02	, " ff_640x480 " ],
	[ 0x03	, " ff_960x720 " ],
	[ 0x04	, " ff_1280x720 " ],
	[ 0x05	, " ff_1280x960 " ]
];

set D585RgbCameraResolutions = 
[
	[ 0x00	, "undefined resolution" ],
	[ 0x01	, " ff_320x240 " ],
	[ 0x02	, " ff_640x360 " ],
	[ 0x03	, " ff_640x480 " ],
	[ 0x04	, " ff_960x720 " ],
	[ 0x05	, " ff_1280x720 " ],
	[ 0x06	, " ff_1280x960 " ],
	[ 0x07	, " ff_1920x1080 " ],
	[ 0x08	, " ff_1920x1440 " ],
	[ 0x09	, " ff_2560x1440 " ],
	[ 0x0A	, " ff_3840x2160 " ]
];

set raw16CameraResolutions = 
[
	[ 0x00	, "undefined resolution" ],
	[ 0x01	, " ff_1920x1080 " ]
];

set S585Raw16CameraResolutions = 
[
	[ 0x00	, "undefined resolution" ],
	[ 0x01	, " ff_1600x1300 " ],
	[ 0x02	, " ff_2104x1560 " ],
	[ 0x03	, " ff_4160x2340 " ],
	[ 0x04	, " ff_4208x3120 " ]
];

set depthCameraFormats = 
[
	[ 0x00	, "undefined format" ],
	[ 0x01	, " sfDepth_Z16 " ],
	[ 0x02	, " sfDepth_D16 " ]
];

set MipiDataTypes = 
[
	[ 0x00	, "undefined dataType" ],
	[ 0x12	, " MetaData " ],
	[ 0x2A	, " RAW8 " ],
	[ 0x2B	, " RAW10 " ],
	[ 0x30	, " UserDefined1_Calib " ],
	[ 0x31	, " UserDefined2_Depth " ],
	[ 0x32	, " UserDefined3_R8L8 " ]
];

set YCameraFormats = 
[
	[ 0x00	, "undefined format" ],
	[ 0x01	, " sfY_L8 " ],
	[ 0x02	, " sfY_UYVY " ],
	[ 0x03	, " sfY_Y8 " ],
	[ 0x04	, " sfY_R8L8 " ],
	[ 0x05	, " sfY_Calib " ],
	[ 0x06	, " sfY_W10 " ]
];

set S585YCameraFormats = 
[
	[ 0x00	, "undefined format" ],
	[ 0x01	, " sfY_R8L8 " ],
	[ 0x02	, " sfY_Calib " ]
];

set S585SafetyCameraFormats = 
[
	[ 0x00	, "undefined format" ],
	[ 0x01	, " sfSafetyCamera_RAW8 " ]
];

set S585OccupancyCameraFormats = 
[
	[ 0x00	, "undefined format" ],
	[ 0x01	, " sfOccupancyCamera_RAW8 " ]
];

set depthCameraResolutions = 
[
	[ 0x00	, "undefined resolution" ],
	[ 0x01	, "ff_256x144" ],
	[ 0x02	, "ff_424x240" ],
	[ 0x03	, "ff_480x270" ],
	[ 0x04	, "ff_640x360" ],
	[ 0x05	, "ff_848x100" ],
	[ 0x06	, "ff_640x480" ],
	[ 0x07	, "ff_848x480" ],
	[ 0x08	, "ff_1280x720" ],
	
	[ 0x09	, "ff_1920x1080" ]	# for R8L8 only
];

set D585DepthCameraResolutions = 
[
	[ 0x00	, "undefined resolution" ],
	[ 0x01	, "ff_256x144" ],
	[ 0x02	, "ff_320x240" ],
	[ 0x03	, "ff_640x480" ],
	[ 0x04	, "ff_960x720" ],
	[ 0x05	, "ff_1280x720" ],
	[ 0x06	, "ff_1280x960" ]
];

set S585DepthCameraResolutions = 
[
	[ 0x00	, "undefined resolution" ],
	[ 0x01	, "ff_320x240" ],
	[ 0x02	, "ff_1280x960" ]
];

set S585YCameraResolutions = 
[
	[ 0x00	, "undefined resolution" ],
	[ 0x01	, "ff_1280x960" ]
];

set S585CalibCameraResolutions = 
[
	[ 0x00	, "undefined resolution" ],
	[ 0x01	, "ff_1600x1300" ]
];

set S585SaferyCameraResolutions = 
[
	[ 0x00	, "undefined resolution" ],
	[ 0x01	, "ff_64x4" ]
];

set S585OccupancyCameraResolutions = 
[
	[ 0x00	, "undefined resolution" ],
	[ 0x01	, "ff_256x256" ]
];

set AwgDepthCameraResolutions = 
[
	[ 0x00	, "undefined resolution" ],
	[ 0x01	, "ff_256x144" ],
	[ 0x02	, "ff_424x240" ],
	[ 0x03	, "ff_480x270" ],
	[ 0x04	, "ff_640x360" ],
	[ 0x05	, "ff_640x480" ],
	[ 0x06	, "ff_848x100" ],
	[ 0x07	, "ff_848x480" ],
	[ 0x08	, "ff_1280x720" ],
	
	[ 0x09	, "ff_1280x800" ]	# for R8L8 only
];

set F416DepthCameraResolutions = 
[
	[ 0x00	, "undefined resolution" ],
	[ 0x01	, "ff_960x960" ],
	[ 0x02	, "ff_720x720" ],
	[ 0x03	, "ff_576x576" ],
	[ 0x04	, "ff_144x144" ]
];

set YCalibCameraResolutions = 
[
	[ 0x00	, "undefined resolution" ],
	[ 0x01	, "ff_960x540" ],
	[ 0x02	, "ff_1920x1080" ]
];

set WideYCalibCameraResolutions = 
[
	[ 0x00	, "undefined resolution" ],
	[ 0x01	, "ff_640x400" ],
	[ 0x02	, "ff_1280x800" ]
];

set F416YCalibCameraResolutions = 
[
	[ 0x00	, "undefined resolution" ],
	[ 0x01	, "ff_1024x1024" ]
];

set YW10CameraResolutions = 
[
	[ 0x00	, "undefined resolution" ],
	[ 0x01	, "ff_1920x1080" ]
];

set fishEyeCameraFormats = 
[
	[ 0x00	, "undefined format" ],
	[ 0x01	, " sfFishEye_RAW8 " ]
];

set fishEyeCameraResolutions = 
[
	[ 0x00	, "undefined resolution" ],
	[ 0x01	, " ff_640x480 " ]
];

set CameraEndpointsMap = 
[
	[ 0x00	, "undefined EP" ],
	[ 0x01	, "WinUsb OUT" ],
	[ 0x81	, "WinUsb IN" ],
	[ 0x82	, "Depth Stream" ],
	[ 0x83	, "Y Stream" ],
	[ 0x84	, "RGB(FishEye) Stream" ],
	[ 0x86	, "HID Interrupt" ],
	[ 0x87	, "Depth Interrupt" ],
	[ 0x88	, "FishEye Interrupt" ]
];

set DepthMvRModeMap = 
[
	[ 0xff	, "undefined" ],
	[ 0x00	, "Manual" ],
	[ 0x01	, "Auto Range" ],
	[ 0x02	, "Single Shoot" ],
	[ 0x03	, "HDR Mode" ]
];

set MetaDataProjectorModeMap = 
[
	[ 0	, "OFF" ],
	[ 1	, "Laser ON" ],
	[ 2	, "Laser AUTO (Off)" ],
	[ 3	, "Led On" ]
];

set MetaDataBoolMap = 
[
	[ 0	, "OFF" ],
	[ 1	, "ON" ]
];

set MetaDataStructTypeMap = 
[
	[ 0x80000000	, "META_DATA_INTEL_DEPTH_CONTROL" ],
	[ 0x80000001	, "META_DATA_INTEL_CAPTURE_TIMING" ],
	[ 0x80000002	, "META_DATA_INTEL_CONFIGURATION" ],
	[ 0x80000003	, "META_DATA_INTEL_STAT" ],
	[ 0x80000004	, "META_DATA_INTEL_FISH_EYE_CONTROL" ],
	[ 0x80000005	, "META_DATA_INTEL_RGB_CONTRL" ],
	[ 0x80000006	, "META_DATA_INTEL_FE_FOV_MODEL" ],
	[ 0x80000007	, "META_DATA_INTEL_FE_CAMERA_EXTRINSICS_ID" ],
	[ 0x00000003	, "META_DATA_CAPTURE_STATS" ],
	[ 0x00000004	, "META_DATA_CAMERA_EXTRINSICS" ],
	[ 0x00000005	, "META_DATA_CAMERA_INTRINSICS" ],
	[ 0x800000FF	, "META_DATA_CAMERA_DEBUG" ]

];

set HwTypeTypeMap = 
[
	[ 0x0	, "DS5 USB" ],
	[ 0x1	, "DS5 MIPI" ],
	[ 0x2	, "D4M MIPI" ],
	[ 0x3	, "IVCAM2" ]

];

set SkuTypeMap = 
[
	[ 0x05	, "ASR" ],
	[ 0x01	, "PSR" ],
	[ 0x2D	, "ASRC" ],
	[ 0x26	, "AWG" ],
	[ 0x36	, "AWGT" ],
	[ 0x12	, "PWGT" ],
	[ 0x35	, "ASRT" ],
	[ 0x11	, "PSRT" ],
	[ 0x2E	, "AWGC" ],	# D431 or D465
	[ 0x3E	, "AWGCT" ],
	[ 0x02	, "PWG" ],
	[ 0x45	, "DS5U" ]
];


set bmHeaderInfoBitmapTable =
[
    [  0, "Frame ID         " ],
    [  1, "End of Frame     " ],
    [  2, "Presentation Time" ],
    [  3, "Source Clock     " ],
    [  4, "Reserved         " ],
    [  5, "Still Image      " ],
    [  6, "Error            " ], 
    [  7, "End of Header    " ]
 ];
set bmHSkuIdBitmapTable =
[
    [ 0, "Depth camera (bits 0..1)"],
	[ 1, "Depth camera (bits 0..1)"],
    [ 2, "depthIsActive"],
    [ 3, "RGB"],
    [ 4, "IMU"],
	[ 5, "Projector type"],
	[ 6, "Led"]
];
 
set bmIntelCaptureTimingFlags = 
[
    [ 0, "INTEL_CAPTURE_FRAME_COUNTER"],
	[ 1, "INTEL_CAPTURE_TIME_OPTICAL"],
    [ 2, "INTEL_CAPTURE_TIME_READOUT"],
    [ 3, "INTEL_CAPTURE_TIME_EXPOSURE"],
    [ 4, "INTEL_CAPTURE_TIME_FRAME_INTERVAL"],
	[ 5, "INTEL_CAPTURE_TIME_PIPE_LATENCY"]
];

set bmIntelStatFlags = 
[
    [ 0,  "INTEL_STAT_LEFT_SUM"],           
	[ 1,  "INTEL_STAT_LEFT_DARK_COUNT"],    
    [ 2,  "INTEL_STAT_LEFT_BRIGHT_COUNT"],  
    [ 3,  "INTEL_STAT_RIGHT_SUM"],          
    [ 4,  "INTEL_STAT_RIGHT_DARK_COUNT"],   
	[ 5,  "INTEL_STAT_RIGHT_BRIGHT_COUNT"], 
	[ 6,  "INTEL_STAT_REC_FRAME_COUNT"],    
	[ 7,  "INTEL_STAT_LEFT_RED_SUM"],       
    [ 8,  "INTEL_STAT_LEFT_GREEN1_SUM"],    
    [ 9,  "INTEL_STAT_LEFT_GREEN2_SUM"],    
    [ 10, "INTEL_STAT_STAT_LEFT_BLUE_SUM"], 
	[ 11, "INTEL_STAT_RIGHT_RED_SUM"],      
	[ 12, "INTEL_STAT_RIGHT_GREEN1_SUM"],   
	[ 13, "INTEL_STAT_RIGHT_GREEN2_SUM"],   
	[ 14, "INTEL_STAT_RIGHT_BLUE_SUM"]     
];

set bmCapturStatsFlags = 
[
    [ 0,  "CAPTURESTATS_FLAG_EXPOSURETIME"], 
	[ 1,  "CAPTURESTATS_FLAG_EXPOSURECOMPENSATION"], 
    [ 2,  "CAPTURESTATS_FLAG_ISOSPEED"], 
    [ 3,  "CAPTURESTATS_FLAG_FOCUSSTATE"], 
    [ 4,  "CAPTURESTATS_FLAG_LENSPOSITION"], 
	[ 5,  "CAPTURESTATS_FLAG_WHITEBALANCE"], 
	[ 6,  "CAPTURESTATS_FLAG_FLASH"], 
	[ 7,  "CAPTURESTATS_FLAG_FLASHPOWER"], 
    [ 8,  "CAPTURESTATS_FLAG_ZOOMFACTOR"], 
    [ 9,  "CAPTURESTATS_FLAG_SCENEMODE"], 
    [ 10, "CAPTURESTATS_FLAG_SENSORFRAMERATE"]
];

set bmIntelDepthControlFlags = 
[
    [ 0,  "INTEL_DEPTH_CONTROL_GAIN"], 
	[ 1,  "INTEL_DEPTH_CONTROL_MANUAL_EXPOSURE"], 
    [ 2,  "INTEL_DEPTH_CONTROL_LASER_POWER"], 
    [ 3,  "INTEL_DEPTH_CONTROL_AE_MODE"], 
    [ 4,  "INTEL_DEPTH_CONTROL_EXPOSURE_PRIORITY"], 
	[ 5,  "INTEL_DEPTH_CONTROL_ROI"], 
	[ 6,  "INTEL_DEPTH_CONTROL_PRESET"],
	[ 7,  "INTEL_DEPTH_CONTROL_LASER_PWR_MODE"]
];

set bmIntelRgbControlFlags = 
[
    [ 0,  "INTEL_RGB_CONTROL_BRIGHTNES"], 
	[ 1,  "INTEL_RGB_CONTROL_MANUAL_CONTRAST"], 
    [ 2,  "INTEL_RGB_CONTROL_LASER_SATURATION"], 
    [ 3,  "INTEL_RGB_CONTROL_SHARPNESS"], 
    [ 4,  "INTEL_RGB_CONTROL_AE_MODE"], 
	[ 5,  "INTEL_RGB_CONTROL_AWB_TEMP"], 
	[ 6,  "INTEL_RGB_CONTROL_GAIN"],
	[ 7,  "INTEL_RGB_CONTROL_LASER_BACKLIGHT_COMP"],
	[ 8,  "INTEL_RGB_CONTROL_GAMA"], 
    [ 9,  "INTEL_RGB_CONTROL_HUE"], 
	[ 10,  "INTEL_RGB_CONTROL_MANUAL_EXP"], 
	[ 11,  "INTEL_RGB_CONTROL_MANUAL_WB"],
	[ 12,  "INTEL_RGB_CONTROL_POWER_LINE_FREQUNCY"],
	[ 13,  "INTEL_RGB_CONTROL_AE_PRIORITY_CONTROL"]
];  

set bmIntelFishEyeControlFlags = 
[
    [ 0,  "INTEL_FISH_EYE_CONTROL_GAIN"], 
	[ 1,  "INTEL_FISH_EYE_CONTROL_MANUAL_EXPOSURE"]
];

set bmIntelConfigurationFlags = 
[
    [ 0,  "INTEL_CONFIGURATION_HW_TYPE"], 
	[ 1,  "INTEL_CONFIGURATION_SKU_ID"], 
    [ 2,  "INTEL_CONFIGURATION_COOKIE"], 
    [ 3,  "INTEL_CONFIGURATION_FORMAT"], 
    [ 4,  "INTEL_CONFIGURATION_WIDTH"], 
	[ 5,  "INTEL_CONFIGURATION_HEIGHT"], 
	[ 6,  "INTEL_CONFIGURATION_FPS"], 
	[ 7,  "INTEL_CONFIGURATION_TRIGGER"], 
	[ 8,  "INTEL_CONFIGURATION_CAL_COUNT"]
];
        
set bmIntelConfigurationTriggerMode = 
[
    [ 0,  "IN_SYNC"], 
	[ 1,  "EXTERNAL_TRIGGER"]
];
        
set ErrorControlMap = 
[
	[	0x00," etXuErrSuccess " ],
	[	0x01," etXuErrHotLaserPwrReduce " ],
	[	0x02," etXuErrHotLaserDisable " ],
	[	0x03," etXuErrFlagBLaserDisable " ],
	[	0x04," etXuErrStereoModuleNotConnected " ],
	[	0x05," etXuErrEepromIsCorrupted " ],
	[	0x06," etXuErrCalibrationIsCorrupted " ],
	[	0x07," etXuErrMmUpdateFailed " ],
	[	0x08," etXuErrIspUpdateFailed " ],
	[	0x09," etXuErrMmForcePause " ],
	[	0x0A," etXuErrMmFailure " ],
	[	0x0B," etXuErrUsbScpOverflow " ],
	[	0x0C," etXuErrUsbRecOverflow " ],
	[	0x0D," etXuErrUsbCamOverflow " ],
	[	0x0E," etXuErrMipiErrorLeft " ],
	[	0x0F," etXuErrMipiErrorRight " ],
	[	0x10," etXuErrMipiErrorRT " ],
	[	0x11," etXuErrMipiErrorFE " ],
	[	0x12," etXuErrI2CCfgErrLeft " ],
	[	0x13," etXuErrI2CCfgErrRight " ],
	[	0x14," etXuErrI2CCfgErrRT " ],
	[	0x15," etXuErrI2CCfgErrFE " ],
	[	0x16," etXuErrStreamNotStartDepth " ],
	[	0x17," etXuErrStreamNotStartY " ],
	[	0x18," etXuErrStreamNotStartCam " ],
	[	0x19," etXuErrRec " ],
	[	0x1A," etXuErrUSB2Limit " ],
	[	0x1B," etXuErrColdLaserDisable " ],
	[	0x1C," etXuErrNoTemperatureDisableLaser " ],
	[	0x1D," etXuErrIspBootDataUploadFailed " ]
];

# VideoTables.inc
#
# This file contains many of the tables that are used in all the .inc files and .dec files

%include "VideoIdentifiersTables.inc"


#	Appendix A. Video Device Class Codes
	
#	A.1. Video Interface Class Code
#	Table A- 1 Video Interface Class Code
#Value	Video Interface Class Code
set VideoInterfaceClassCodeTable = 
[
   [ 0xFF, "Illegal" ],
   [ 0x0E, "CC_VIDEO" ]
];
	
	
#	A.2. Video Interface Subclass Codes
#	Table A- 2 Video Interface Subclass Codes
#Value	Video Subclass Code
set VideoSubclassCodeTable = 
[
   [ 0xFF, "Illegal" ],
   [ 0x00, "SC_UNDEFINED" ],
   [ 0x01, "SC_VIDEOCONTROL" ],
   [ 0x02, "SC_VIDEOSTREAMING" ],
   [ 0x03, "SC_VIDEO_INTERFACE_COLLECTION" ]
];
	
	
#	A.3. Video Interface Protocol Codes
#	Table A- 3 Video Interface Protocol Codes
#Value	Video Protocol Code
set VideoInterfaceProtocolCodeTable = 
[
   [ 0xFF, "Illegal" ],
   [ 0x00, "PC_PROTOCOL_UNDEFINED" ],
   [ 0x01, "PC_PROTOCOL_15"]
];
	
	
#	A.4. Video Class-Specific Descriptor Types
#	Table A- 4 Video Class-Specific Descriptor Types
#Value	Descriptor Type
set VideoClassSpecificDescriptorTypesTable = 
[
   [ 0xFF, "Illegal" ],
   [ 0x20, "CS_UNDEFINED" ],
   [ 0x21, "CS_DEVICE" ],
   [ 0x22, "CS_CONFIGURATION" ],
   [ 0x23, "CS_STRING" ],
   [ 0x24, "CS_INTERFACE" ],
   [ 0x25, "CS_ENDPOINT" ]
];
	
	
#	A.5. Video Class-Specific VC Interface Descriptor Subtypes
#	Table A- 5 Video Class-Specific VC Interface Descriptor Subtypes
#Value	Descriptor Subtype
set VideoClassSpecificVCInterfaceDescriptorSubtypesTable = 
[
   [ 0xFF, "Illegal" ],
   [ 0x00, "VC_DESCRIPTOR_UNDEFINED" ],
   [ 0x01, "VC_HEADER" ],
   [ 0x02, "VC_INPUT_TERMINAL" ],
   [ 0x03, "VC_OUTPUT_TERMINAL" ],
   [ 0x04, "VC_SELECTOR_UNIT" ],
   [ 0x05, "VC_PROCESSING_UNIT" ],
   [ 0x06, "VC_EXTENSION_UNIT" ],
   [ 0x07, "VC_ENCODING_UNIT"]
];

	
	
#	A.6. Video Class-Specific VS Interface Descriptor Subtypes
#	Table A- 6 Video Class-Specific VS Interface Descriptor Subtypes
#Value	Descriptor Subtype
set VideoClassSpecificVSInterfaceDescriptorSubtypesTable = 
[
   [ 0xFF, "Illegal" ],
   [ 0x00, "VS_UNDEFINED" ],
   [ 0x01, "VS_INPUT_HEADER" ],
   [ 0x02, "VS_OUTPUT_HEADER" ],
   [ 0x03, "VS_STILL_IMAGE_FRAME" ],
   [ 0x04, "VS_FORMAT_UNCOMPRESSED" ],
   [ 0x05, "VS_FRAME_UNCOMPRESSED" ],
   [ 0x06, "VS_FORMAT_MJPEG" ],
   [ 0x07, "VS_FRAME_MJPEG" ],
   [ 0x08, "VS_FORMAT_MPEG1" ],
   [ 0x09, "VS_FORMAT_MPEG2PS" ],
   [ 0x0A, "VS_FORMAT_MPEG2TS" ],
   [ 0x0B, "VS_FORMAT_MPEG4SL" ],
   [ 0x0C, "VS_FORMAT_DV" ],
   [ 0x0D, "VS_COLORFORMAT" ],
   [ 0x0E, "VS_FORMAT_VENDOR" ],
   [ 0x0F, "VS_FRAME_VENDOR" ]
];

# Table for Version 1.1 
set VideoClassSpecificVSInterfaceDescriptorSubtypesTable_V1_1 = 
[
   [ 0xFF, "Illegal" ],
   [ 0x00, "VS_UNDEFINED" ],
   [ 0x01, "VS_INPUT_HEADER" ],
   [ 0x02, "VS_OUTPUT_HEADER" ],
   [ 0x03, "VS_STILL_IMAGE_FRAME" ],
   [ 0x04, "VS_FORMAT_UNCOMPRESSED" ],
   [ 0x05, "VS_FRAME_UNCOMPRESSED" ],
   [ 0x06, "VS_FORMAT_MJPEG" ],
   [ 0x07, "VS_FRAME_MJPEG" ],
   [ 0x08, "Reserved" ],
   [ 0x09, "Reserved" ],
   [ 0x0A, "VS_FORMAT_MPEG2TS" ],
   [ 0x0B, "Reserved" ],
   [ 0x0C, "VS_FORMAT_DV" ],
   [ 0x0D, "VS_COLORFORMAT" ],
   [ 0x0E, "Reserved" ],
   [ 0x0F, "Reserved" ],
   [ 0x10, "VS_FORMAT_FRAME_BASED" ],
   [ 0x11, "VS_FRAME_FRAME_BASED" ],
   [ 0x12, "VS_FORMAT_STREAM_BASED" ]
];	

# Table for Version 1.5 
set VideoClassSpecificVSInterfaceDescriptorSubtypesTable_V1_5 = 
[
   [ 0xFF, "Illegal" ],
   [ 0x00, "VS_UNDEFINED" ],
   [ 0x01, "VS_INPUT_HEADER" ],
   [ 0x02, "VS_OUTPUT_HEADER" ],
   [ 0x03, "VS_STILL_IMAGE_FRAME" ],
   [ 0x04, "VS_FORMAT_UNCOMPRESSED" ],
   [ 0x05, "VS_FRAME_UNCOMPRESSED" ],
   [ 0x06, "VS_FORMAT_MJPEG" ],
   [ 0x07, "VS_FRAME_MJPEG" ],
   [ 0x08, "Reserved" ],
   [ 0x09, "Reserved" ],
   [ 0x0A, "VS_FORMAT_MPEG2TS" ],
   [ 0x0B, "Reserved" ],
   [ 0x0C, "VS_FORMAT_DV" ],
   [ 0x0D, "VS_COLORFORMAT" ],
   [ 0x0E, "Reserved" ],
   [ 0x0F, "Reserved" ],
   [ 0x10, "VS_FORMAT_FRAME_BASED" ],
   [ 0x11, "VS_FRAME_FRAME_BASED" ],
   [ 0x12, "VS_FORMAT_STREAM_BASED" ],
   [ 0x13, "VS_FORMAT_H264" ],
   [ 0x14, "VS_FRAME_H264" ],
   [ 0x15, "VS_FORMAT_H264_SIMULCAST" ],
   [ 0x16, "VS_FORMAT_VP8" ],
   [ 0x17, "VS_FRAME_VP8" ],
   [ 0x18, "VS_FORMAT_VP8_SIMULCAST"]
];	
	
#	A.7. Video Class-Specific Endpoint Descriptor Subtypes
#	Table A- 7 Video Class-Specific Endpoint Descriptor Subtypes
#Value	Descriptor Subtype
set VideoClassSpecificEndpointDescriptorSubtypesTable = 
[
   [ 0xFF, "Illegal" ],
   [ 0x00, "EP_UNDEFINED" ],
   [ 0x01, "EP_GENERAL" ],
   [ 0x02, "EP_ENDPOINT" ],
   [ 0x03, "EP_INTERRUPT" ]
];
	
	
#	A.8. Video Class-Specific Request Codes
#	Table A- 8 Video Class-Specific Request Codes
#Value	Class-Specific Request Code
set VideoClassSpecificRequestCodesTable = 
[
   [ 0xFF, "Illegal" ],
   [ 0x00, "RC_UNDEFINED" ],
   [ 0x01, "SET_CUR" ],
   [ 0x81, "GET_CUR" ],
   [ 0x82, "GET_MIN" ],
   [ 0x83, "GET_MAX" ],
   [ 0x84, "GET_RES" ],
   [ 0x85, "GET_LEN" ],
   [ 0x86, "GET_INFO" ],
   [ 0x87, "GET_DEF" ]
];

#Value	Class-Specific Request Code
#Table for version 1_5
set VideoClassSpecificRequestCodesTable_V1_5 = 
[
   [ 0xFF, "Illegal" ],
   [ 0x00, "RC_UNDEFINED" ],
   [ 0x01, "SET_CUR" ],
   [ 0x11, "SET_CUR_ALL" ],
   [ 0x81, "GET_CUR" ],
   [ 0x82, "GET_MIN" ],
   [ 0x83, "GET_MAX" ],
   [ 0x84, "GET_RES" ],
   [ 0x85, "GET_LEN" ],
   [ 0x86, "GET_INFO" ],
   [ 0x87, "GET_DEF" ],
   [ 0x91, "GET_CUR_ALL" ],
   [ 0x92, "GET_MIN_ALL" ],
   [ 0x93, "GET_MAX_ALL" ],
   [ 0x94, "GET_RES_ALL" ],
   [ 0x97, "GET_DEF_ALL" ]
];	
	
#	A.9. Control Selector Codes
	
#	A.9.1. VideoControl Interface Control Selectors
#	Table A- 9 VideoControl Interface Control Selectors
#Value	Control Selector
set VideoControlInterfaceControlSelectorsTable = 
[
   [ 0xFF, "Illegal" ],
   [ 0x00, "VC_CONTROL_UNDEFINED" ],
   [ 0x01, "VC_VIDEO_POWER_MODE_CONTROL" ],
   [ 0x02, "VC_REQUEST_ERROR_CODE_CONTROL" ],
   [ 0x03, "VC_REQUEST_INDICATE_HOST_CLOCK_CONTROL" ]
];

# Table for Version 1.1 specifications
set VideoControlInterfaceControlSelectorsTable_V1_1 = 
[
   [ 0xFF, "Illegal" ],
   [ 0x00, "VC_CONTROL_UNDEFINED" ],
   [ 0x01, "VC_VIDEO_POWER_MODE_CONTROL" ],
   [ 0x02, "VC_REQUEST_ERROR_CODE_CONTROL" ],
   [ 0x03, "Reserved" ]
];

# Table for Version 1.5 specifications
set VideoControlInterfaceControlSelectorsTable_V1_5 = 
[
   [ 0xFF, "Illegal" ],
   [ 0x00, "VC_CONTROL_UNDEFINED" ],
   [ 0x01, "VC_VIDEO_POWER_MODE_CONTROL" ],
   [ 0x02, "VC_REQUEST_ERROR_CODE_CONTROL" ],
   [ 0x03, "Reserved" ]
];	
	
#	A.9.2. Terminal Control Selectors
#	Table A- 10 Terminal Control Selectors
#Value	Control Selector
set TerminalControlSelectorsTable = 
[
   [ 0xFF, "Illegal" ],
   [ 0x00, "TE_CONTROL_UNDEFINED" ]
];
	
	
#	A.9.3. Selector Unit Control Selectors
#	Table A- 11 Selector Unit Control Selectors
#Value	Control Selector
set SelectorUnitControlSelectorsTable = 
[
   [ 0xFF, "Illegal" ],
   [ 0x00, "SU_CONTROL_UNDEFINED" ],
   [ 0x01, "SU_INPUT_SELECT_CONTROL" ]
];
	
	
#	A.9.4. Camera Terminal Control Selectors
#	Table A- 12 Camera Terminal Control Selectors
#Value	Control Selector
set CameraTerminalControlSelectorsTable = 
[
   [ 0xFF, "Illegal" ],
   [ 0x00, "CT_CONTROL_UNDEFINED" ],
   [ 0x01, "CT_SCANNING_MODE_CONTROL" ],
   [ 0x02, "CT_AE_MODE_CONTROL" ],
   [ 0x03, "CT_AE_PRIORITY_CONTROL" ],
   [ 0x04, "CT_EXPOSURE_TIME_ABSOLUTE_CONTROL" ],
   [ 0x05, "CT_EXPOSURE_TIME_RELATIVE_CONTROL" ],
   [ 0x06, "CT_FOCUS_ABSOLUTE_CONTROL" ],
   [ 0x07, "CT_FOCUS_RELATIVE_CONTROL" ],
   [ 0x08, "CT_FOCUS_AUTO_CONTROL" ],
   [ 0x09, "CT_IRIS_ABSOLUTE_CONTROL" ],
   [ 0x0A, "CT_IRIS_RELATIVE_CONTROL" ],
   [ 0x0B, "CT_ZOOM_ABSOLUTE_CONTROL" ],
   [ 0x0C, "CT_ZOOM_RELATIVE_CONTROL" ],
   [ 0x0D, "CT_PANTILT_ABSOLUTE_CONTROL" ],
   [ 0x0E, "CT_PANTILT_RELATIVE_CONTROL" ],
   [ 0x0F, "CT_ROLL_ABSOLUTE_CONTROL" ],
   [ 0x10, "CT_ROLL_RELATIVE_CONTROL" ],
   [ 0x11, "CT_PRIVACY_CONTROL" ]
   
];

#	A.9.4. Camera Terminal Control Selectors
#	Table A- 12 Camera Terminal Control Selectors
#Value	Control Selector
set CameraTerminalControlSelectorsTable_V1_5 = 
[
   [ 0xFF, "Illegal" ],
   [ 0x00, "CT_CONTROL_UNDEFINED" ],
   [ 0x01, "CT_SCANNING_MODE_CONTROL" ],
   [ 0x02, "CT_AE_MODE_CONTROL" ],
   [ 0x03, "CT_AE_PRIORITY_CONTROL" ],
   [ 0x04, "CT_EXPOSURE_TIME_ABSOLUTE_CONTROL" ],
   [ 0x05, "CT_EXPOSURE_TIME_RELATIVE_CONTROL" ],
   [ 0x06, "CT_FOCUS_ABSOLUTE_CONTROL" ],
   [ 0x07, "CT_FOCUS_RELATIVE_CONTROL" ],
   [ 0x08, "CT_FOCUS_AUTO_CONTROL" ],
   [ 0x09, "CT_IRIS_ABSOLUTE_CONTROL" ],
   [ 0x0A, "CT_IRIS_RELATIVE_CONTROL" ],
   [ 0x0B, "CT_ZOOM_ABSOLUTE_CONTROL" ],
   [ 0x0C, "CT_ZOOM_RELATIVE_CONTROL" ],
   [ 0x0D, "CT_PANTILT_ABSOLUTE_CONTROL" ],
   [ 0x0E, "CT_PANTILT_RELATIVE_CONTROL" ],
   [ 0x0F, "CT_ROLL_ABSOLUTE_CONTROL" ],
   [ 0x10, "CT_ROLL_RELATIVE_CONTROL" ],
   [ 0x11, "CT_PRIVACY_CONTROL" ],
   [ 0x12, "CT_FOCUS_SIMPLE_CONTROL" ],
   [ 0x13, "CT_WINDOW_CONTROL" ],
   [ 0x14, "CT_REGION_OF_INTEREST_CONTROL" ]
];

#	A.9.5. Processing Unit Control Selectors
#	Table A- 13 Processing Unit Control Selectors
#Value	Control Selector
set ProcessingUnitControlSelectorsTable = 
[
   [ 0xFF, "Illegal" ],
   [ 0x00, "PU_CONTROL_UNDEFINED" ],
   [ 0x01, "PU_BACKLIGHT_COMPENSATION_CONTROL" ],
   [ 0x02, "PU_BRIGHTNESS_CONTROL" ],
   [ 0x03, "PU_CONTRAST_CONTROL" ],
   [ 0x04, "PU_GAIN_CONTROL" ],
   [ 0x05, "PU_POWER_LINE_FREQUENCY_CONTROL" ],
   [ 0x06, "PU_HUE_CONTROL" ],
   [ 0x07, "PU_SATURATION_CONTROL" ],
   [ 0x08, "PU_SHARPNESS_CONTROL" ],
   [ 0x09, "PU_GAMMA_CONTROL" ],
   [ 0x0A, "PU_WHITE_BALANCE_TEMPERATURE_CONTROL" ],
   [ 0x0B, "PU_WHITE_BALANCE_TEMPERATURE_AUTO_CONTROL" ],
   [ 0x0C, "PU_WHITE_BALANCE_COMPONENT_CONTROL" ],
   [ 0x0D, "PU_WHITE_BALANCE_COMPONENT_AUTO_CONTROL" ],
   [ 0x0E, "PU_DIGITAL_MULTIPLIER_CONTROL" ],
   [ 0x0F, "PU_DIGITAL_MULTIPLIER_LIMIT_CONTROL" ],
   [ 0x10, "PU_HUE_AUTO_CONTROL" ]
];

# Version 1.1 of ProcessingUnitControlSelectorsTable
set ProcessingUnitControlSelectorsTable_V1_1	 = 
[
   [ 0xFF, "Illegal" ],
   [ 0x00, "PU_CONTROL_UNDEFINED" ],
   [ 0x01, "PU_BACKLIGHT_COMPENSATION_CONTROL" ],
   [ 0x02, "PU_BRIGHTNESS_CONTROL" ],
   [ 0x03, "PU_CONTRAST_CONTROL" ],
   [ 0x04, "PU_GAIN_CONTROL" ],
   [ 0x05, "PU_POWER_LINE_FREQUENCY_CONTROL" ],
   [ 0x06, "PU_HUE_CONTROL" ],
   [ 0x07, "PU_SATURATION_CONTROL" ],
   [ 0x08, "PU_SHARPNESS_CONTROL" ],
   [ 0x09, "PU_GAMMA_CONTROL" ],
   [ 0x0A, "PU_WHITE_BALANCE_TEMPERATURE_CONTROL" ],
   [ 0x0B, "PU_WHITE_BALANCE_TEMPERATURE_AUTO_CONTROL" ],
   [ 0x0C, "PU_WHITE_BALANCE_COMPONENT_CONTROL" ],
   [ 0x0D, "PU_WHITE_BALANCE_COMPONENT_AUTO_CONTROL" ],
   [ 0x0E, "PU_DIGITAL_MULTIPLIER_CONTROL" ],
   [ 0x0F, "PU_DIGITAL_MULTIPLIER_LIMIT_CONTROL" ],
   [ 0x10, "PU_HUE_AUTO_CONTROL" ],
   [ 0x11, "PU_ANALOG_VIDEO_STANDARD_CONTROL" ],
   [ 0x12, "PU_ANALOG_LOCK_STATUS_CONTROL" ]
];

# Version 1.5 of ProcessingUnitControlSelectorsTable
set ProcessingUnitControlSelectorsTable_V1_5	 = 
[
   [ 0xFF, "Illegal" ],
   [ 0x00, "PU_CONTROL_UNDEFINED" ],
   [ 0x01, "PU_BACKLIGHT_COMPENSATION_CONTROL" ],
   [ 0x02, "PU_BRIGHTNESS_CONTROL" ],
   [ 0x03, "PU_CONTRAST_CONTROL" ],
   [ 0x04, "PU_GAIN_CONTROL" ],
   [ 0x05, "PU_POWER_LINE_FREQUENCY_CONTROL" ],
   [ 0x06, "PU_HUE_CONTROL" ],
   [ 0x07, "PU_SATURATION_CONTROL" ],
   [ 0x08, "PU_SHARPNESS_CONTROL" ],
   [ 0x09, "PU_GAMMA_CONTROL" ],
   [ 0x0A, "PU_WHITE_BALANCE_TEMPERATURE_CONTROL" ],
   [ 0x0B, "PU_WHITE_BALANCE_TEMPERATURE_AUTO_CONTROL" ],
   [ 0x0C, "PU_WHITE_BALANCE_COMPONENT_CONTROL" ],
   [ 0x0D, "PU_WHITE_BALANCE_COMPONENT_AUTO_CONTROL" ],
   [ 0x0E, "PU_DIGITAL_MULTIPLIER_CONTROL" ],
   [ 0x0F, "PU_DIGITAL_MULTIPLIER_LIMIT_CONTROL" ],
   [ 0x10, "PU_HUE_AUTO_CONTROL" ],
   [ 0x11, "PU_ANALOG_VIDEO_STANDARD_CONTROL" ],
   [ 0x12, "PU_ANALOG_LOCK_STATUS_CONTROL" ],
   [ 0x13, "PU_CONTRAST_AUTO_CONTROL" ]
];	

#	A.9.6. Extension Unit Control Selectors
#   Table A-14 Encoding Unit Control Selectors
#   Version 1.5  EncodingUnitControlSelectorsTable
set EncodingUnitControlSelectorsTable_V1_5 =
[
   [ 0xFF, "Illegal" ],
   [ 0x00, "EU_CONTROL_UNDEFINED" ],
   [ 0x01, "EU_SELECT_LAYER_CONTROL" ],
   [ 0x02, "EU_PROFILE_TOOLSET_CONTROL" ],
   [ 0x03, "EU_VIDEO_RESOLUTION_CONTROL" ],
   [ 0x04, "EU_ MIN_FRAME_INTERVAL_CONTROL" ],
   [ 0x05, "EU_ SLICE_MODE_CONTROL" ],
   [ 0x06, "EU_RATE_CONTROL_MODE_CONTROL" ],
   [ 0x07, "EU_AVERAGE_BITRATE_CONTROL" ],
   [ 0x08, "EU_CPB_SIZE_CONTROL" ],
   [ 0x09, "EU_PEAK_BIT_RATE_CONTROL" ],
   [ 0x0A, "EU_QUANTIZATION_PARAMS_CONTROL" ],
   [ 0x0B, "EU_SYNC_REF_FRAME_CONTROL" ],
   [ 0x0C, "EU_LTR_BUFFER_CONTROL" ],
   [ 0x0D, "EU_LTR_PICTURE_CONTROL" ],
   [ 0x0E, "EU_LTR_VALIDATION_CONTROL" ],
   [ 0x0F, "EU_LEVEL_IDC_LIMIT_CONTROL" ],
   [ 0x10, "EU_SEI_PAYLOADTYPE_CONTROL" ],
   [ 0x11, "EU_QP_RANGE_CONTROL" ],
   [ 0x12, "EU_PRIORITY_CONTROL" ],
   [ 0x13, "EU_START_OR_STOP_LAYER_CONTROL" ],
   [ 0x14, "EU_ERROR_RESILIENCY_CONTROL" ]
];
	
#	A.9.7. Extension Unit Control Selectors
#	Table A- 15 Extension Unit Control Selectors
#Value	Control Selector
set ExtensionUnitControlSelectorsTable = 
[
   [ 0xFF, "Illegal" ],
   [ 0x00, "XU_CONTROL_UNDEFINED" ]
];

set DepthExtensionUnitControlSelectorsTable = 
[
   [ 0xFF, "Illegal" ],
   [ 0x00, "XU_CONTROL_UNDEFINED" ],
   [ 0x01, "XU_HWM_CMD" ],
   [ 0x02, "XU_LASER_POWER_MODE" ],
   [ 0x03, "XU_EXPOSURE" ],
   [ 0x04, "XU_LASER_POWER" ],
   [ 0x05, "XU_SINGLE_SHOT_HDR" ],
   [ 0x06, "XU_PRESET" ],
   [ 0x07, "XU_ERROR_CODE" ],
   [ 0x08, "XU_EXT_TRIG" ],
   [ 0x09, "XU_TEMPERATURE" ],
   [ 0x0A, "XU_AUTO_WHITE_BALANCE" ],
   [ 0x0B, "XU_AUTO_EXPOSURE" ],
   [ 0x0C, "XU_CAMERA_EXTRINSICS" ],
   [ 0x0D, "XU_CAMERA_INTRINSICS" ],
   [ 0x0E, "XU_LED_PWR_LEVEL" ]
];	

set RgbExtensionUnitControlSelectorsTable = 
[
   [ 0xFF, "Illegal" ],
   [ 0x00, "XU_CONTROL_UNDEFINED" ]
];

set FishEyeExtensionUnitControlSelectorsTable = 
[
   [ 0xFF, "Illegal" ],
   [ 0x00, "XU_CONTROL_UNDEFINED" ],
   [ 0x01, "XU_EXPOSURE" ],
   [ 0x02, "XU_CAMERA_EXTRINSICS" ],
   [ 0x03, "XU_CAMERA_INTRINSICS" ]
];

set DepthMsExtensionUnitControlSelectorsTable = 
[
   [ 0xFF, "Illegal" ],
   [ 0x00, "MSXU_CONTROL_UNDEFINED" ],
   [ 0x01, "MSXU_CONTROL_FOCUS" ],
   [ 0x02, "MSXU_CONTROL_EXPOSURE" ],
   [ 0x03, "MSXU_CONTROL_EVCOMPENSATION" ],
   [ 0x04, "MSXU_CONTROL_WHITEBALANCE" ],
   [ 0x05, "MSXU_CONTROL_RESERVED" ],
   [ 0x06, "MSXU_CONTROL_FACE_AUTH" ],
   [ 0x07, "MSXU_CONTROL_CAMERA_EXTRINSICS" ],
   [ 0x08, "MSXU_CONTROL_CAMERA_INTRINSICS" ],
   [ 0x09, "MSXU_CONTROL_METADATA" ]
];	

#	A.9.8. VideoStreaming Interface Control Selectors
#	Table A- 16 VideoStreaming Interface Control Selectors
#Value	Control Selector
set VideoStreamingInterfaceControlSelectorsTable = 
[
   [ 0xFF, "Illegal" ],
   [ 0x00, "VS_CONTROL_UNDEFINED" ],
   [ 0x01, "VS_PROBE_CONTROL" ],
   [ 0x02, "VS_COMMIT_CONTROL" ],
   [ 0x03, "VS_STILL_PROBE_CONTROL" ],
   [ 0x04, "VS_STILL_COMMIT_CONTROL" ],
   [ 0x05, "VS_STILL_IMAGE_TRIGGER_CONTROL" ],
   [ 0x06, "VS_STREAM_ERROR_CODE_CONTROL" ],
   [ 0x07, "VS_GENERATE_KEY_FRAME_CONTROL" ],
   [ 0x08, "VS_UPDATE_FRAME_SEGMENT_CONTROL" ],
   [ 0x09, "VS_SYNCH_DELAY_CONTROL" ]
];

set ErrorCodeTable =
[
    [  0xFF, " Unknown " ],
	[  0x0, " No Error " ],
    [  0x01, " Not ready " ],
    [  0x02, " Wrong state " ],
    [  0x03, " Power " ],
    [  0x04, " Out of range " ],
    [  0x05, " Invalid unit " ],
    [  0x06, " Invalid control " ],
    [  0x07, " Invalid Request " ]
];

#	A.9.9. Additional Control Selectors
#	See “Universal Serial Bus Device Class Definition for Video Devices: Identifiers” for additional selectors.
	

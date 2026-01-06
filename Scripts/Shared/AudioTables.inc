#******************************************************************************
#
#  FILENAME: AudioTables.inc
#
#  Copyright (C) 2006 LeCroy Corporation PSG 
#
#  DESCRIPTION
#    This file contains many of the tables that are used in all the .inc files and .dec files
#    These tables are defined according to the following specs
#	
    
#		March 18, 1998		Universal Serial Bus Device Class Definition for Audio Devices Release 1.0 		
#		March 18, 1998  	Universal Serial Bus Device Class Definition for Audio Data Formats Release 1.0 
#       March 18, 1998		Universal Serial Bus Device Class Definition for Terminal Types Release 1.0
#		Nov    1, 1999		Universal Serial Bus Device Class Definition for MIDI Devices Release 1.0
#
#       April 19, 2005    File first created
#       Aug   01, 2006    Upgraded to USB 2.0
#
#******************************************************************************


set IP_VERSION_01_00 = 0x00;
set IP_VERSION_02_00 = 0x20;
set IP_VERSION_03_00 = 0x30;

#***************************************************************************************************
#Universal Serial Bus Device Class Definition for Audio Devices Release 1.0 specific
#***************************************************************************************************
#A.4 Audio Class-Specific Descriptor Types
set AudioDescriptorType_v1_Table =
[
    [ 0xFF, "Illegal"],
    [ 0x20, "Audio_CS_UNDEFINED"],
    [ 0x21, "Audio_CS_DEVICE"		],
    [ 0x22, "Audio_CS_CONFIGURATION"],
    [ 0x23, "Audio_CS_STRING"],
    [ 0x24, "Audio_CS_INTERFACE"],
    [ 0x25, "Audio_CS_ENDPOINT"]
];

#A.5 Audio Class-Specific AC Interface Descriptor Subtypes
#Table A-5: Audio Class-Specific AC Interface Descriptor Subtypes
set ACDescriptorSubType_v1_Table =
[
    [ 0xFF, "Illegal", null],
    [ 0x00, "AC_DESCRIPTOR_UNDEFINED", null],
    [ 0x01, "HEADER", "HEADER_sub"],
    [ 0x02, "INPUT_TERMINAL", "INPUT_TERMINAL_v1_sub"],
    [ 0x03, "OUTPUT_TERMINAL", "OUTPUT_TERMINAL_v1_sub"],
    [ 0x04, "MIXER_UNIT", "MIXER_UNIT_v1_sub"],
    [ 0x05, "SELECTOR_UNIT", "SELECTOR_UNIT_v1_sub"],
    [ 0x06, "FEATURE_UNIT", "FEATURE_UNIT_v1_sub"],
    [ 0x07, "PROCESSING_UNIT", "PROCESSING_UNIT_v1_sub"],
    [ 0x08, "EXTENSION_UNIT", "EXTENSION_UNIT_v1_sub"]
];

#A.6 Audio Class-Specific AS Interface Descriptor Subtypes
#Table A-6: Audio Class-Specific AS Interface Descriptor Subtypes
set ASDescriptorSubType_v1_Table = 
[
		[ 0xFF, "Illegal", null],
		[ 0x00, "AS_DESCRIPTOR_UNDEFINED", null],
		[ 0x01, "AS_GENERAL", "AS_GENERAL_v1_sub"],
		[ 0x02, "FORMAT_TYPE", "FORMAT_TYPE_v1_sub"],
		[ 0x03, "FORMAT_SPECIFIC", "FORMAT_SPECIFIC_v1_sub"]
];

#A.7 Processing Unit Process Types
#Table A-7: Processing Unit Process Types
set AudioPUPType_v1_Table = 
[
		[ 0xFF, "Illegal", null],
		[ 0x00, "PROCESS_UNDEFINED", null],
		[ 0x01, "UP_DOWNMIX_PROCESS", "UP_DOWNMIX_PROCESS_v1_sub"],
		[ 0x02, "DOLBY_PROLOGIC_PROCESS", "DOLBY_PROLOGIC_PROCESS_v1_sub"],
		[ 0x03, "3D_STEREO_EXTENDER_PROCESS", "AUDIO_3D_STEREO_EXTENDER_PROCESS_v1_sub"],
		[ 0x04, "REVERBERATION_PROCESS", "REVERBERATION_PROCESS_v1_sub"],
		[ 0x05, "CHORUS_PROCESS", "CHORUS_PROCESS_v1_sub"],
		[ 0x06, "DYN_RANGE_COMP_PROCESS", "DYN_RANGE_COMP_PROCESS_v1_sub"]
];


#A.9 Audio Class-Specific Request Codes
#Table A-9: Audio Class-Specific Request Codes
set AudioCSRequesCodes_v1_Table = 
[
		[0x00, "REQUEST_CODE_UNDEFINED"],
		[0x01, "SET_CUR"],
		[0x81, "GET_CUR"],
		[0x02, "SET_MIN"],
		[0x82, "GET_MIN"],
		[0x03, "SET_MAX"],
		[0x83, "GET_MAX"],
		[0x04, "SET_RES"],
		[0x84, "GET_RES"],
		[0x05, "SET_MEM"],
		[0x85, "GET_MEM"],
		[0xFF, "GET_STAT"]
];

#A.10 Control Selector Codes
#A.10.1 Terminal Control Selectors
#Table A-10: Terminal Control Selectors
set AudioTerminalControlSelectors_v1_Table = 
[
		[0xFF, "Illegal"],
		[0x00, "TE_CONTROL_UNDEFINED"],
		[0x01, "COPY_PROTECT_CONTROL"]
];


#A.10.2 Feature Unit Control Selectors
#Table A-11: Feature Unit Control Selectors
set AudioFeatureUnitControlSelectors_v1_Table =
[
		[0xFF, "Illegal"],
		[0x00, "FU_CONTROL_UNDEFINED"],
		[0x01, "MUTE_CONTROL"],
		[0x02, "VOLUME_CONTROL"],
		[0x03, "BASS_CONTROL"],
		[0x04, "MID_CONTROL"],
		[0x05, "TREBLE_CONTROL"],
		[0x06, "GRAPHIC_EQUALIZER_CONTROL"],
		[0x07, "AUTOMATIC_GAIN_CONTROL"],
		[0x08, "DELAY_CONTROL"],
		[0x09, "BASS_BOOST_CONTROL"],
		[0x0A, "LOUDNESS_CONTROL"]
];


#A.10.3 Processing Unit Control Selectors
#A.10.3.1 Up/Down-mix Processing Unit Control Selectors
#Table A-12: Up/Down-mix Processing Unit Control Selectors
set AudioUpDownMixProcessingUnitControlSelectors_v1_Table =
[
		[0xFF, "Illegal"],
		[0x00, "UD_CONTROL_UNDEFINED"],
		[0x01, "UD_ENABLE_CONTROL"],
		[0x02, "UD_MODE_SELECT_CONTROL"]
];

#A.10.3.2 Dolby Prologic‘ Processing Unit Control Selectors
#Table A-13: Dolby Prologic Processing Unit Control Selectors
set AudioDolbyPrologicProcessingUnitControlSelectors_v1_Table =
[
		[0xFF, "Illegal"],
		[0x00, "DP_CONTROL_UNDEFINED"],
		[0x01, "DP_ENABLE_CONTROL"],
		[0x02, "DP_MODE_SELECT_CONTROL"]
];


#A.10.3.3 3D Stereo Extender Processing Unit Control Selectors
#Table A-14: 3D Stereo Extender Processing Unit Control Selectors
set Audio3DStereoExtenderProcessingUnitControlSelectors_v1_Table = 
[
		[0xFF, "Illegal"],
		[0x00, "AUDIO_3D_CONTROL_UNDEFINED"],
		[0x01, "AUDIO_3D_ENABLE_CONTROL"],
		[0x03, "AUDIO_SPACIOUSNESS_CONTROL"]
];


#A.10.3.4 Reverberation Processing Unit Control Selectors
#Table A-15: Reverberation Processing Unit Control Selectors
set AudioReverberationProcessingUnitControlSelectors_v1_Table =
[
		[0xFF, "Illegal"],
		[0x00, "RV_CONTROL_UNDEFINED"],
		[0x01, "RV_ENABLE_CONTROL"],
		[0x02, "REVERB_LEVEL_CONTROL"],
		[0x03, "REVERB_TIME_CONTROL"],
		[0x04, "REVERB_FEEDBACK_CONTROL"]
];


#A.10.3.5 Chorus Processing Unit Control Selectors
#Table A-16: Chorus Processing Unit Control Selectors
set AudioChorusProcessingUnitControlSelectors_v1_Table = 
[
		[0xFF, "Illegal"],
		[0x00, "CH_CONTROL_UNDEFINED"],
		[0x01, "CH_ENABLE_CONTROL"],
		[0x02, "CHORUS_LEVEL_CONTROL"],
		[0x03, "CHORUS_RATE_CONTROL"],
		[0x04, "CHORUS_DEPTH_CONTROL"]
];


#A.10.3.6 Dynamic Range Compressor Processing Unit Control Selectors
#Table A-17: Dynamic Range Compressor Processing Unit Control Selectors
set AudioDynamicRangeCompressorProcessingUnitControlSelectors_v1_Table = 
[
		[0xFF, "Illegal"],
		[0x00, "DR_CONTROL_UNDEFINED"],
		[0x01, "DR_ENABLE_CONTROL"],
		[0x02, "COMPRESSION_RATE_CONTROL"],
		[0x03, "MAXAMPL_CONTROL"],
		[0x04, "THRESHOLD_CONTROL"],
		[0x05, "ATTACK_TIME"],
		[0x06, "RELEASE_TIME"]
];


#A.10.4 Extension Unit Control Selectors
#Table A-18: Extension Unit Control Selectors
set AudioExtensionUnitControlSelectors_v1_Table = 
[
		[0xFF, "Illegal"],
		[0x00, "XU_CONTROL_UNDEFINED"],
		[0x01, "XU_ENABLE_CONTROL"]
];


#A.10.5 Endpoint Control Selectors
#Table A-19: Endpoint Control Selectors
set AudioEndpointControlSelectors_v1_Table = 
[
		[0xFF, "Illegal"],
		[0x00, "EP_CONTROL_UNDEFINED"],
		[0x01, "SAMPLING_FREQ_CONTROL"],
		[0x02, "PITCH_CONTROL"]
];


#***************************************************************************************************
#Universal Serial Bus Device Class Definition for Audio Devices Release 2.0 Specific
#***************************************************************************************************
#A.8 Audio Class-Specific Descriptor Types
set AudioDescriptorType_v2_Table =
[
    [ 0xFF, "Illegal"],
    [ 0x20, "Audio_CS_UNDEFINED"],
    [ 0x21, "Audio_CS_DEVICE"		],
    [ 0x22, "Audio_CS_CONFIGURATION"],
    [ 0x23, "Audio_CS_STRING"],
    [ 0x24, "Audio_CS_INTERFACE"],
    [ 0x25, "Audio_CS_ENDPOINT"]
];

#Appendix A. Audio Device Class Codes

#A.7 Audio Function Category Codes
#Table A-7: Audio Function Category Codes
set AudioFunctionCategoryCodes_v2_Table = 
[
    [0xFF, "OTHER"],
    [0x00, "FUNCTION_SUBCLASS_UNDEFINED"],
    [0x01, "DESKTOP_SPEAKER"],
    [0x02, "HOME_THEATER"],
    [0x03, "MICROPHONE"],
    [0x04, "HEADSET"],
    [0x05, "TELEPHONE"],
    [0x06, "CONVERTER"],
    [0x07, "VOICE/SOUND_RECORDER"],
    [0x08, "I/O_BOX"],
    [0x09, "MUSICAL_INSTRUMENT"],
    [0x0A, "PRO-AUDIO"],
    [0x0B, "AUDIO/VIDEO"],
    [0x0C, "CONTROL_PANEL"]
];

#A.9 Audio Class-Specific AC Interface Descriptor Subtypes
#Table A-9: Audio Class-Specific AC Interface Descriptor Subtypes
set ACDescriptorSubType_v2_Table =
[
    [ 0xFF, "Illegal",null],
    [ 0x00, "AC_DESCRIPTOR_UNDEFINED",null],
    [ 0x01, "HEADER", "HEADER_sub"],
    [ 0x02, "INPUT_TERMINAL", "INPUT_TERMINAL_v2_sub"],
    [ 0x03, "OUTPUT_TERMINAL", "OUTPUT_TERMINAL_v2_sub"],
    [ 0x04, "MIXER_UNIT", "MIXER_UNIT_v2_sub"],
    [ 0x05, "SELECTOR_UNIT", "SELECTOR_UNIT_v2_sub"],
    [ 0x06, "FEATURE_UNIT", "FEATURE_UNIT_v2_sub"],
    [ 0x07, "EFFECT_UNIT", "EFFECT_UNIT_v2_sub"],
    [ 0x08, "PROCESSING_UNIT", "PROCESSING_UNIT_v2_sub"],
    [ 0x09, "EXTENSION_UNIT", "EXTENSION_UNIT_v2_sub"],
    [ 0x0A, "CLOCK_SOURCE", "CLOCK_SOURCE_v2_sub"],
    [ 0x0B, "CLOCK_SELECTOR", "CLOCK_SELECTOR_v2_sub"],
    [ 0x0C, "CLOCK_MULTIPLIER", "CLOCK_MULTIPLIER_v2_sub"],
    [ 0x0D, "SAMPLE_RATE_CONVERTER", "SAMPLE_RATE_CONVERTER_v2_sub"]
];

#Table A-10: Audio Class-Specific AS Interface Descriptor Subtypes
set ASDescriptorSubType_v2_Table = 
[
    [ 0xFF, "Illegal", null],
    [ 0x00, "AS_DESCRIPTOR_UNDEFINED", null],
    [ 0x01, "AS_GENERAL", "AS_GENERAL_v2_sub"],
    [ 0x02, "FORMAT_TYPE", "FORMAT_TYPE_v2_sub"],
    [ 0x03, "ENCODER", "ENCODER_v2_sub"],
    [ 0x04, "DECODER", "DECODER_v2_sub"]
];

#A.11 Effect Unit Effect Types
#Table A-11 Effect Unit Effect Types
set AudioEffectUnitEffectTypes_v2_Table = 
[
    [ 0xFF, "Illegal", null],
    [ 0x00, "EFFECT_UNDEFINED", null],
    [ 0x01, "PARAM_EQ_SECTION_EFFECT", "PARAM_EQ_SECTION_EFFECT_v2_sub"],
    [ 0x02, "REVERBERATION_EFFECT", "REVERBERATION_EFFECT_v2_sub"],
    [ 0x03, "MOD_DELAY_ERRECT", "MOD_DELAY_EFFECT_v2_v3_sub"],
    [ 0x04, "DYN_RANGE_COMP_EFFECT", "DYN_RANGE_COMP_EFFECT_v2_v3_sub"]
];


#A.12 Processing Unit Process Types
#Table A-12: Processing Unit Process Types
set AudioPUPType_v2_Table = 
[
		[ 0xFF, "Illegal", null],
		[ 0x00, "PROCESS_UNDEFINED", null],
		[ 0x01, "UP_DOWNMIX_PROCESS","UP_DOWNMIX_PROCESS_v2_sub"],
		[ 0x02, "DOLBY_PROLOGIC_PROCESS", "DOLBY_PROLOGIC_PROCESS_v2_sub"],
		[ 0x03, "STEREO_EXTENDER_PROCESS", "STEREO_EXTENDER_PROCESS_v2_sub"]
];

#A.13 Audio Class-Specific Endpoint Descriptor Subtypes
#Table A-13: Audio Class-Specific Endpoint Descriptor Subtypes
set AudioEPDescriptorSubType_v2_Table =
[
		[0xFF, "Illegal"],
		[0x00, "DESCRIPTOR_UNDEFINED"],
		[0x01, "AUDIO_EP_GENERAL"]
];

#A.15 Encoder Type Codes
set AudioEncoderTypeCodes_v2_Table = 
[
    [ 0xFF, "Illegal"],
    [ 0x00, "ENCODER_UNDEFINED"],
    [ 0x01, "OTHER_ENCODER"],
    [ 0x02, "MPEG_ENCODER"],
    [ 0x03, "AC-3_ENCODER"],
    [ 0x04, "WMA_ENCODER"],
    [ 0x05, "DTS_ENCODER"]
];

#A.16 Decoder Type Codes
set AudioDecoderType_v2_Code =
[
    [ 0xFF, "Illegal", null],
    [ 0x00, "DECODER_UNDEFINED", null],
    [ 0x01, "OTHER_DECODER", null],
    [ 0x02, "MPEG_DECODER", "MPEG_DECODER_v2_sub"],
    [ 0x03, "AC-3_DECODER", "AC3_DECODER_v2_sub"],
    [ 0x04, "WMA_DECODER", "WMA_DECODER_v2_sub"],
    [ 0x05, "DTS_DECODER", "DTS_DECODER_v2_sub"]
];

#A.14 Audio Class-Specific Request Codes
#Table A-14: Audio Class-Specific Request Codes
set AudioCSRequesCodes_v2_Table = 
[
    [0xFF, "Reserved"],
	[0x00, "REQUEST_CODE_UNDEFINED"],
	[0x01, "CUR"],
	[0x02, "RANGE"],
	[0x03, "MEM"]
];

#A.17.1 Clock Source Control Selectors
set AudioClockSourceControlSelectors_v2_Table =
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE command                     Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF  , "CS_Reserved"             , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x00  , "CS_CONTROL_UNDEFINED"    , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x01  , "CS_SAM_FREQ_CONTROL"     , "AudioLayout3"    , 0b11  ,CS_SAM_FREQ_CONTROL_Color      ,null                               ,"GENERAL_FREQUENCY_CONTROL_Tooltip"],
    [ 0x02  , "CS_CLOCK_VALID_CONTROL"  , "AudioLayout1"    , 0b10  ,CS_CLOCK_VALID_CONTROL_Color   ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"CS_CLOCK_VALID_CONTROL_Tooltip" ]
];

#A.17.2 Clock Selector Control Selectors
set AudioClockSelectorControlSelectors_v2_Table =
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE command                     Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF  , "CX_Reserved"             , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x00  , "CX_CONTROL_UNDEFINED"    , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x01  , "CX_CLOCK_SELECTOR_CONTROL", "AudioLayout1"   , 0b11  ,CX_CLOCK_SELECTOR_CONTROL_Color,"NON_ZERO_VALUE_CONTROL_Validate"  ,"CX_CLOCK_SELECTOR_CONTROL_Tooltip"]
];

#A.17.3 Clock Multiplier Control Selectors
set AudioClockMultiplierControlSelectors_v2_Table =
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE command                     Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF  , "CM_Reserved"            , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x00  , "CM_CONTROL_UNDEFINED"   , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x01  , "CM_NUMERATOR_CONTROL"   , "AudioLayout2"    , 0b10  ,CM_NUMERATOR_CONTROL_Color     ,"NON_ZERO_VALUE_CONTROL_Validate"  ,"CM_NUMERATOR_CONTROL_Tooltip"],
    [ 0x02  , "CM_DENOMINATOR_CONTROL" , "AudioLayout2"    , 0b10  ,CM_DENOMINATOR_CONTROL_Color   ,"NON_ZERO_VALUE_CONTROL_Validate"  ,"CM_DENOMINATOR_CONTROL_Tooltip"]
];

#A.17.4 Terminal Control Selectors
set AudioTerminalControlSelectors_v2_Table = 
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE command                     Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF  , "TE_Reserved"             , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x00  , "TE_CONTROL_UNDEFINED"    , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x01  , "TE_COPY_PROTECT_CONTROL" , "AudioLayout1"    , 0b10  ,TE_COPY_PROTECT_CONTROL_Color  ,"TE_COPY_PROTECT_CONTROL_Validate" ,"TE_COPY_PROTECT_CONTROL_Tooltip"],
	[ 0x02  , "TE_CONNECTOR_CONTROL"    , "TE_CONNECTOR_CONTROL_v2_sub", 0b10,TE_CONNECTOR_CONTROL_Color   ,null                               ,null],
	[ 0x03  , "TE_OVERLOAD_CONTROL"     , "AudioLayout1"    , 0b10  ,TE_OVERLOAD_CONTROL_Color      ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"TE_OVERLOAD_CONTROL_Tooltip"],
	[ 0x04  , "TE_CLUSTER_CONTROL"      , "CLUSTER_CONTROL_v2_sub",0b10,TE_CLUSTER_CONTROL_Color    ,null                               ,null],
	[ 0x05  , "TE_UNDERFLOW_CONTROL"    , "AudioLayout1"    , 0b10  ,TE_UNDERFLOW_CONTROL_Color     ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"UNDERFLOW_CONTROL_Tooltip"],
	[ 0x06  , "TE_OVERFLOW_CONTROL"     , "AudioLayout1"    , 0b10  ,TE_OVERFLOW_CONTROL_Color      ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"OVERFLOW_CONTROL_Tooltip"],
	[ 0x07  , "TE_LATENCY_CONTROL"      , "AudioLayout3"    , 0b10  ,TE_LATENCY_CONTROL_Color       ,null                               ,"LATENCY_CONTROL_Tooltip"]
];	


#A.17.5 Mixer Control Selectors
set AudioMixerControlSelectors_v2_Table =
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE command                     Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF, "MU_Reserved"               , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x00, "MU_CONTROL_UNDEFINED"      , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x01, "MU_MIXER_CONTROL"          , "AudioLayout2"    , 0b11  ,MU_MIXER_CONTROL_Color         ,null                               ,"GENERAL_VOLUME_CONTROL_Tooltip"],
    [ 0x02, "MU_CLUSTER_CONTROL"        , "CLUSTER_CONTROL_v2_sub",0b10,MU_CLUSTER_CONTROL_Color    ,null                               ,null],
    [ 0x03, "MU_UNDERFLOW_CONTROL"      , "AudioLayout1"    , 0b10  ,MU_UNDERFLOW_CONTROL_Color     ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"UNDERFLOW_CONTROL_Tooltip"],
    [ 0x04, "MU_OVERFLOW_CONTROL"       , "AudioLayout1"    , 0b10  ,MU_OVERFLOW_CONTROL_Color      ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"OVERFLOW_CONTROL_Tooltip"], 
    [ 0x05, "MU_LATENCY_CONTROL"        , "AudioLayout3"    , 0b10  ,MU_LATENCY_CONTROL_Color       ,null                               ,"LATENCY_CONTROL_Tooltip"]
];

#A.17.6 Selector Control Selectors
set AudioSelectorControlSelectors_v2_Table = 
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE command                     Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF, "SU_Reserved"               , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x00, "SU_CONTROL_UNDEFINED"      , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x01, "SU_SELECTOR_CONTROL"       , "AudioLayout1"    , 0b10  ,SU_SELECTOR_CONTROL_Color      ,"NON_ZERO_VALUE_CONTROL_Validate"  ,"SU_SELECTOR_CONTROL_Tooltip"],
    [ 0x02, "SU_LATENCY_CONTROL"        , "AudioLayout3"    , 0b10  ,SU_LATENCY_CONTROL_Color       ,null                               ,"LATENCY_CONTROL_Tooltip"]
];


#a.17.7 Feature Unit Control Selectors
set AudioFeatureUnitControlSelectors_v2_Table =
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE command                     Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF, "FU_Reserved"               , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x00, "FU_CONTROL_UNDEFINED"      , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x01, "FU_MUTE_CONTROL"           , "AudioLayout1"    , 0b10  ,FU_MUTE_CONTROL_Color          ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"FU_MUTE_CONTROL_Tooltip" ],
    [ 0x02, "FU_VOLUME_CONTROL"         , "AudioLayout2"    , 0b11  ,FU_VOLUME_CONTROL_Color        ,null                               ,"GENERAL_VOLUME_CONTROL_Tooltip"],
    [ 0x03, "FU_BASS_CONTROL"           , "AudioLayout1"    , 0b11  ,FU_BASS_CONTROL_Color          ,null                               ,"GENERAL_FEATURE_UNIT_CONTROL_Tooltip" ],
    [ 0x04, "FU_MID_CONTROL"            , "AudioLayout1"    , 0b11  ,FU_MID_CONTROL_Color           ,null                               ,"GENERAL_FEATURE_UNIT_CONTROL_Tooltip" ],
    [ 0x05, "FU_TREBLE_CONTROL"         , "AudioLayout1"    , 0b11  ,FU_TREBLE_CONTROL_Color        ,null                               ,"GENERAL_FEATURE_UNIT_CONTROL_Tooltip" ],
    [ 0x06, "FU_GRAPHIC_EQUALIZER_CONTROL","GRAPHIC_EQUALIZER_CONTROL_v2_sub", 0b11, FU_GRAPHIC_EQUALIZER_CONTROL_Color, null           ,null],
    [ 0x07, "FU_AUTOMATIC_GAIN_CONTROL" , "AudioLayout1"    , 0b10  ,FU_AUTOMATIC_GAIN_CONTROL_Color,"BOOLEAN_VALUE_CONTROL_Validate"   ,"GENERAL_TRUE_FALSE_CONTROL_Tooltip"],
    [ 0x08, "FU_DELAY_CONTROL"          , "AudioLayout3"    , 0b11  ,FU_DELAY_CONTROL_Color         ,null                               ,"FU_DELAY_CONTROL_Tooltip" ],
    [ 0x09, "FU_BASS_BOOST_CONTROL"     , "AudioLayout1"    , 0b10  ,FU_BASS_BOOST_CONTROL_Color    ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"GENERAL_TRUE_FALSE_CONTROL_Tooltip"],
    [ 0x0A, "FU_LOUDNESS_CONTROL"       , "AudioLayout1"    , 0b10  ,FU_LOUDNESS_CONTROL_Color      ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"GENERAL_TRUE_FALSE_CONTROL_Tooltip"],
    [ 0x0B, "FU_INPUT_GAIN_CONTROL"     , "AudioLayout2"    , 0b11  ,FU_INPUT_GAIN_CONTROL_Color    ,null                               ,"GENERAL_VOLUME_CONTROL_Tooltip"],
    [ 0x0C, "FU_INPUT_GAIN_PAD_CONTROL" , "AudioLayout2"    , 0b11  ,FU_INPUT_GAIN_PAD_CONTROL_Color,null                               ,"GENERAL_VOLUME_CONTROL_Tooltip"],
    [ 0x0D, "FU_PHASE_INVERTER_CONTROL" , "AudioLayout1"    , 0b10  ,FU_PHASE_INVERTER_CONTROL_Color,"BOOLEAN_VALUE_CONTROL_Validate"   ,"GENERAL_TRUE_FALSE_CONTROL_Tooltip"],
    [ 0x0E, "FU_UNDERFLOW_CONTROL"      , "AudioLayout1"    , 0b10  ,FU_UNDERFLOW_CONTROL_Color     ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"UNDERFLOW_CONTROL_Tooltip"], 
    [ 0x0F, "FU_OVERFLOW_CONTROL"       , "AudioLayout1"    , 0b10  ,FU_OVERFLOW_CONTROL_Color      ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"OVERFLOW_CONTROL_Tooltip"],  
    [ 0x10, "FU_LATENCY_CONTROL"        , "AudioLayout3"    , 0b10  ,FU_LATENCY_CONTROL_Color       ,null                               ,"LATENCY_CONTROL_Tooltip"]    
];

#A.17.8.1 Parametric Equalizer Section Effect Unit Control Selectors
set AudioPESectionEffectUnitControlSelectors_v2_Table = 
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE command                     Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF, "PE_Reserved"               , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x00, "PE_CONTROL_UNDEFINED"      , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x01, "PE_ENABLE_CONTROL"         , "AudioLayout1"    , 0b10  ,PE_ENABLE_CONTROL_Color        ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"GENERAL_TRUE_FALSE_CONTROL_Tooltip"],
    [ 0x02, "PE_CENTERFREQ_CONTROL"     , "AudioLayout3"    , 0b11  ,PE_CENTERFREQ_CONTROL_Color    ,null                               ,"GENERAL_FREQUENCY_CONTROL_Tooltip"],
    [ 0x03, "PE_QFACTOR_CONTROL"        , "AudioLayout3"    , 0b11  ,PE_QFACTOR_CONTROL_Color       ,null                               ,"PE_QFACTOR_CONTROL_Tooltip" ],
    [ 0x04, "PE_GAIN_CONTROL"           , "AudioLayout2"    , 0b11  ,PE_GAIN_CONTROL_Color          ,null                               ,"GENERAL_VOLUME_CONTROL_Tooltip" ],
    [ 0x05, "PE_UNDERFLOW_CONTROL"      , "AudioLayout1"    , 0b10  ,PE_UNDERFLOW_CONTROL_Color     ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"UNDERFLOW_CONTROL_Tooltip"], 
    [ 0x06, "PE_OVERFLOW_CONTROL"       , "AudioLayout1"    , 0b10  ,PE_OVERFLOW_CONTROL_Color      ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"OVERFLOW_CONTROL_Tooltip"],  
    [ 0x07, "PE_LATENCY_CONTROL"        , "AudioLayout3"    , 0b10  ,PE_LATENCY_CONTROL_Color       ,null                               ,"LATENCY_CONTROL_Tooltip"]    
];

#A.17.8.2 Reverberation Effect Unit Control Selectors
set AudioReverberationEffectUnitControlSelectors_v2_Table =
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE command                     Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF, "RV_Reserved"               , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x00, "RV_CONTROL_UNDEFINED"      , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x01, "RV_ENABLE_CONTROL"         , "AudioLayout1"    , 0b10  ,RV_ENABLE_CONTROL_Color        ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"GENERAL_TRUE_FALSE_CONTROL_Tooltip"],
    [ 0x02, "RV_TYPE_CONTROL"           , "AudioLayout1"    , 0b11  ,RV_TYPE_CONTROL_Color          ,null                               ,"RV_TYPE_CONTROL_Tooltip"],
    [ 0x03, "RV_LEVEL_CONTROL"          , "AudioLayout1"    , 0b11  ,RV_LEVEL_CONTROL_Color         ,null                               ,"GENERAL_PERCENTAGE_CONTROL_Tooltip"],
    [ 0x04, "RV_TIME_CONTROL"           , "AudioLayout2"    , 0b11  ,RV_TIME_CONTROL_Color          ,null                               ,"RV_TIME_CONTROL_Tooltip"],
    [ 0x05, "RV_FEEDBACK_CONTROL"       , "AudioLayout1"    , 0b11  ,RV_FEEDBACK_CONTROL_Color      ,null                               ,"GENERAL_PERCENTAGE_CONTROL_Tooltip"],
    [ 0x06, "RV_FREDELAY_CONTROL"       , "AudioLayout2"    , 0b11  ,RV_FREDELAY_CONTROL_Color      ,null                               ,"GENERAL_MICROSECOND_CONTROL_Tooltip"],
    [ 0x07, "RV_DENSITY_CONTROL"        , "AudioLayout1"    , 0b11  ,RV_DENSITY_CONTROL_Color       ,"RV_DENSITY_CONTROL_Validate"      ,"RV_DENSITY_CONTROL_Tooltip"],
    [ 0x08, "RV_HIFREQ_ROLLOFF_CONTROL" , "AudioLayout3"    , 0b11  ,RV_HIFREQ_ROLLOFF_CONTROL_Color,null                               ,"GENERAL_FREQUENCY_CONTROL_Tooltip"],
    [ 0x09, "RV_UNDERFLOW_CONTROL"      , "AudioLayout1"    , 0b10  ,RV_UNDERFLOW_CONTROL_Color     ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"UNDERFLOW_CONTROL_Tooltip"], 
    [ 0x0A, "RV_OVERFLOW_CONTROL"       , "AudioLayout1"    , 0b10  ,RV_OVERFLOW_CONTROL_Color      ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"OVERFLOW_CONTROL_Tooltip"],  
    [ 0x0B, "RV_LATENCY_CONTROL"        , "AudioLayout3"    , 0b10  ,RV_LATENCY_CONTROL_Color       ,null                               ,"LATENCY_CONTROL_Tooltip"]    
];

#A.17.8.3 Modulation Delay Effect Unit Control Selectors
set AudioMDEffectUnitControlSelectors_v2_Table = 
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE command                     Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF, "MD_Reserved"               , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x00, "MD_CONTROL_UNDEFINED"      , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x01, "MD_ENABLE_CONTROL"         , "AudioLayout1"    , 0b10  ,MD_ENABLE_CONTROL_Color        ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"GENERAL_TRUE_FALSE_CONTROL_Tooltip"],
    [ 0x02, "MD_BALANCE_CONTROL"        , "AudioLayout1"    , 0b11  ,MD_BALANCE_CONTROL_Color       ,"MD_BALANCE_CONTROL_Validate"      ,"MD_BALANCE_CONTROL_Tooltip"],
    [ 0x03, "MD_RATE_CONTROL"           , "AudioLayout2"    , 0b11  ,MD_RATE_CONTROL_Color          ,null                               ,"MD_RATE_CONTROL_Tooltip"],
    [ 0x04, "MD_DEPTH_CONTROL"          , "AudioLayout2"    , 0b11  ,MD_DEPTH_CONTROL_Color         ,null                               ,"MD_DEPTH_CONTROL_Tooltip"],
    [ 0x05, "MD_TIME_CONTROL"           , "AudioLayout2"    , 0b11  ,MD_TIME_CONTROL_Color          ,null                               ,"MD_DEPTH_CONTROL_Tooltip"],
    [ 0x06, "MD_FEEDBACK_CONTROL"       , "AudioLayout1"    , 0b11  ,MD_FEEDBACK_CONTROL_Color      ,null                               ,"GENERAL_PERCENTAGE_CONTROL_Tooltip"],
    [ 0x07, "MD_UNDERFLOW_CONTROL"      , "AudioLayout1"    , 0b10  ,MD_UNDERFLOW_CONTROL_Color     ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"UNDERFLOW_CONTROL_Tooltip"], 
    [ 0x08, "MD_OVERFLOW_CONTROL"       , "AudioLayout1"    , 0b10  ,MD_OVERFLOW_CONTROL_Color      ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"OVERFLOW_CONTROL_Tooltip"],  
    [ 0x09, "MD_LATENCY_CONTROL"        , "AudioLayout3"    , 0b10  ,MD_LATENCY_CONTROL_Color       ,null                               ,"LATENCY_CONTROL_Tooltip"]    
];

#A.17.8.4 Dynamic Range Compressor Effect Unit Control Selectors
set AudioDRCEffectUnitControlSelectors_v2_Table = 
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE command                     Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF, "DR_Reserved"               , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x00, "DR_CONTROL_UNDEFINED"      , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x01, "DR_ENABLE_CONTROL"         , "AudioLayout1"    , 0b10  ,DR_ENABLE_CONTROL_Color        ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"GENERAL_TRUE_FALSE_CONTROL_Tooltip"],
    [ 0x02, "DR_COMPRESSION_RATE_CONTROL","AudioLayout2"    , 0b11  ,DR_COMPRESSION_RATE_CONTROL_Color,null                             ,"DR_COMPRESSION_RATE_CONTROL_Tooltip"],
    [ 0x03, "DR_MAXAMPL_CONTROL"        , "AudioLayout2"    , 0b11  ,DR_MAXAMPL_CONTROL_Color       ,null                               ,"GENERAL_AMPL_CONTROL_Tooltip"],
    [ 0x04, "DR_THRESHOLD_CONTROL"      , "AudioLayout2"    , 0b11  ,DR_THRESHOLD_CONTROL_Color     ,null                               ,"GENERAL_AMPL_CONTROL_Tooltip"],
    [ 0x05, "DR_ATTACK_TIME_CONTROL"    , "AudioLayout2"    , 0b11  ,DR_ATTACK_TIME_CONTROL_Color   ,null                               ,"GENERAL_MICROSECOND_CONTROL_Tooltip" ],
    [ 0x06, "DR_RELEASE_TIME_CONTROL"   , "AudioLayout2"    , 0b11  ,DR_RELEASE_TIME_CONTROL_Color  ,null                               ,"GENERAL_MICROSECOND_CONTROL_Tooltip" ],
    [ 0x07, "DR_UNDERFLOW_CONTROL"      , "AudioLayout1"    , 0b10  ,DR_UNDERFLOW_CONTROL_Color     ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"UNDERFLOW_CONTROL_Tooltip"], 
    [ 0x08, "DR_OVERFLOW_CONTROL"       , "AudioLayout1"    , 0b10  ,DR_OVERFLOW_CONTROL_Color      ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"OVERFLOW_CONTROL_Tooltip"],  
    [ 0x09, "DR_LATENCY_CONTROL"        , "AudioLayout3"    , 0b10  ,DR_LATENCY_CONTROL_Color       ,null                               ,"LATENCY_CONTROL_Tooltip"]    
];



#A.17.9.1 Up/Down-mix Processing Unit Control Selectors
set AudioUpDownMixProcessingUnitControlSelectors_v2_Table =
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE command                     Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF, "UD_Reserved"               , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x00, "UD_CONTROL_UNDEFINED"      , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x01, "UD_ENABLE_CONTROL"         , "AudioLayout1"    , 0b10  ,UD_ENABLE_CONTROL_Color        ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"GENERAL_TRUE_FALSE_CONTROL_Tooltip"],
    [ 0x02, "UD_MODE_SELECT_CONTROL"    , "AudioLayout1"    , 0b10  ,UD_MODE_SELECT_CONTROL_Color   ,"NON_ZERO_VALUE_CONTROL_Validate"  ,"GENERAL_MODE_SELECT_CONTROL_Tooltip"],
    [ 0x03, "UD_CLUSTER_CONTROL"        , "CLUSTER_CONTROL_v2_sub", 0b10,UD_CLUSTER_CONTROL_Color   ,null                               ,null],
    [ 0x04, "UD_UNDERFLOW_CONTROL"      , "AudioLayout1"    , 0b10  ,UD_UNDERFLOW_CONTROL_Color     ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"UNDERFLOW_CONTROL_Tooltip"], 
    [ 0x05, "UD_OVERFLOW_CONTROL"       , "AudioLayout1"    , 0b10  ,UD_OVERFLOW_CONTROL_Color      ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"OVERFLOW_CONTROL_Tooltip"],  
    [ 0x06, "UD_LATENCY_CONTROL"        , "AudioLayout3"    , 0b10  ,UD_LATENCY_CONTROL_Color       ,null                               ,"LATENCY_CONTROL_Tooltip"]    
];

#A.17.9.2 Dolby Prologic Processing Unit Control Selectors
set AudioDolbyPrologicProcessingUnitControlSelectors_v2_Table =
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE command                     Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF, "DP_Reserved"               , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x00, "DP_CONTROL_UNDEFINED"      , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x01, "DP_ENABLE_CONTROL"         , "AudioLayout1"    , 0b10  ,DP_ENABLE_CONTROL_Color        ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"GENERAL_TRUE_FALSE_CONTROL_Tooltip"],
    [ 0x02, "DP_MODE_SELECT_CONTROL"    , "AudioLayout1"    , 0b10  ,DP_MODE_SELECT_CONTROL_Color   ,"NON_ZERO_VALUE_CONTROL_Validate"  ,"GENERAL_MODE_SELECT_CONTROL_Tooltip"],
    [ 0x03, "DP_CLUSTER_CONTROL"        , "CLUSTER_CONTROL_v2_sub",0b10,DP_CLUSTER_CONTROL_Color    ,null                               ,null],
    [ 0x04, "DP_UNDERFLOW_CONTROL"      , "AudioLayout1"    , 0b10  ,DP_UNDERFLOW_CONTROL_Color     ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"UNDERFLOW_CONTROL_Tooltip"], 
    [ 0x05, "DP_OVERFLOW_CONTROL"       , "AudioLayout1"    , 0b10  ,DP_OVERFLOW_CONTROL_Color      ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"OVERFLOW_CONTROL_Tooltip"],  
    [ 0x06, "DP_LATENCY_CONTROL"        , "AudioLayout3"    , 0b10  ,DP_LATENCY_CONTROL_Color       ,null                               ,"LATENCY_CONTROL_Tooltip"]    
];


#A.17.9.3 Stereo Extender Processing Unit Control Selectors
set AudioStereoExtenderProcessingUnitControlSelectors_v2_Table = 
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE command                     Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF, "ST_Reserved"               , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x00, "ST_EXT_CONTROL_UNDEFINED"  , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x01, "ST_EXT_ENABLE_CONTROL"     , "AudioLayout1"    , 0b10  ,ST_ENABLE_CONTROL_Color        ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"GENERAL_TRUE_FALSE_CONTROL_Tooltip"],
    [ 0x02, "ST_EXT_WIDTH_CONTROL"      , "AudioLayout1"    , 0b11  ,ST_WIDTH_CONTROL_Color         ,null                               ,"GENERAL_BYTE_VALUE_CONTROL_Tooltip"],
    [ 0x03, "ST_EXT_UNDERFLOW_CONTROL"  , "AudioLayout1"    , 0b10  ,ST_UNDERFLOW_CONTROL_Color     ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"UNDERFLOW_CONTROL_Tooltip"], 
    [ 0x04, "ST_EXT_OVERFLOW_CONTROL"   , "AudioLayout1"    , 0b10  ,ST_OVERFLOW_CONTROL_Color      ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"OVERFLOW_CONTROL_Tooltip"],  
    [ 0x05, "ST_EXT_LATENCY_CONTROL"    , "AudioLayout3"    , 0b10  ,ST_LATENCY_CONTROL_Color       ,null                               ,"LATENCY_CONTROL_Tooltip"]    
];

#A.17.10 Extension Unit Control Selectors
set AudioExtensionUnitControlSelectors_v2_Table = 
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE command                     Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF, "XU_Reserved"               , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x00, "XU_CONTROL_UNDEFINED"      , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x01, "XU_ENABLE_CONTROL"         , "AudioLayout1"    , 0b10  ,XU_ENABLE_CONTROL_Color        ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"GENERAL_TRUE_FALSE_CONTROL_Tooltip"],
    [ 0x02, "XU_CLUSTER_CONTROL"        , "CLUSTER_CONTROL_v2_sub",0b10,XU_CLUSTER_CONTROL_Color    ,null                               ,null],
    [ 0x03, "XU_UNDERFLOW_CONTROL"      , "AudioLayout1"    , 0b10  ,XU_UNDERFLOW_CONTROL_Color     ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"UNDERFLOW_CONTROL_Tooltip"], 
    [ 0x04, "XU_OVERFLOW_CONTROL"       , "AudioLayout1"    , 0b10  ,XU_OVERFLOW_CONTROL_Color      ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"OVERFLOW_CONTROL_Tooltip"],  
    [ 0x05, "XU_LATENCY_CONTROL"        , "AudioLayout3"    , 0b10  ,XU_LATENCY_CONTROL_Color       ,null                               ,"LATENCY_CONTROL_Tooltip"]    
];

#A.17.11 AudioStreaming Interface Control Selectors
set AudioStreamingInterfaceControlSelectors_v2_Table =
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE command                     Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF, "AS_Reserved"               , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x00, "AS_CONTROL_UNDEFINED"      , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x01, "AS_ACT_ALT_SETTING_CONTROL" , "AudioLayout1"   , 0b10  ,AS_ACT_ALT_SETTING_CONTROL_Color,null                              ,"GENERAL_BYTE_VALUE_CONTROL_Tooltip"],
    [ 0x02, "AS_VAL_ALT_SETTINGS_CONTROL", "AS_VAL_ALT_SETTINGS_CONTROL_v2_sub", 0b10,AS_VAL_ALT_SETTINGS_CONTROL_Color,null            ,null],
    [ 0x03, "AS_AUDIO_DATA_FORMAT_CONTROL", "AudioLayout3"  , 0b10  ,AS_AUDIO_DATA_FORMAT_CONTROL_Color,null                            ,"AS_AUDIO_DATA_FORMAT_CONTROL_ToolTip" ]
];

#A.17.12 Encoder Control Selectors
set AudioEncoderControlSelectors_v2_Table = 
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE command                     Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF, "EN_Reserved"               , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x00, "EN_CONTROL_UNDEFINED"      , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x01, "EN_BIT_RATE_CONTROL"       , "AudioLayout3"    , 0b11  ,EN_BIT_RATE_CONTROL_Color      ,null                               ,"EN_BIT_RATE_CONTROL_Tooltip"],
    [ 0x02, "EN_QUALITY_CONTROL"        , "AudioLayout1"    , 0b11  ,EN_QUALITY_CONTROL_Color       ,"EN_QUALITY_CONTROL_Validate"      ,"EN_QUALITY_CONTROL_Tooltip"],
    [ 0x03, "EN_VBR_CONTROL"            , "AudioLayout1"    , 0b10  ,EN_VBR_CONTROL_Color           ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"EN_VBR_CONTROL_Tooltip"],
    [ 0x04, "EN_TYPE_CONTROL"           , "AudioLayout1"    , 0b10  ,EN_TYPE_CONTROL_Color          ,"EN_TYPE_CONTROL_Validate"         ,"EN_TYPE_CONTROL_Tooltip"],
    [ 0x05, "EN_UNDERFLOW_CONTROL"      , "AudioLayout1"    , 0b10  ,EN_UNDERFLOW_CONTROL_Color     ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"UNDERFLOW_CONTROL_Tooltip"], 
    [ 0x06, "EN_OVERFLOW_CONTROL"       , "AudioLayout1"    , 0b10  ,EN_OVERFLOW_CONTROL_Color      ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"OVERFLOW_CONTROL_Tooltip"],  
    [ 0x07, "EN_ENCODER_ERROR_CONTROL"  , "AudioLayout2"    , 0b11  ,EN_ENCODER_ERROR_CONTROL_Color ,null                               ,"GENERAL_ERROR_CONTROL_Tooltip"],
    [ 0x08, "EN_PARAM1_CONTROL"         , "AudioLayout3"    , 0b11  ,EN_PARAM1_CONTROL_Color        ,null                               ,"EN_PARAMX_CONTROL_Tooltip"],
    [ 0x09, "EN_PATAM2_CONTROL"         , "AudioLayout3"    , 0b11  ,EN_PARAM2_CONTROL_Color        ,null                               ,"EN_PARAMX_CONTROL_Tooltip"],
    [ 0x0A, "EN_PATAM3_CONTROL"         , "AudioLayout3"    , 0b11  ,EN_PARAM3_CONTROL_Color        ,null                               ,"EN_PARAMX_CONTROL_Tooltip"],
    [ 0x0B, "EN_PATAM4_CONTROL"         , "AudioLayout3"    , 0b11  ,EN_PARAM4_CONTROL_Color        ,null                               ,"EN_PARAMX_CONTROL_Tooltip"],
    [ 0x0C, "EN_PATAM5_CONTROL"         , "AudioLayout3"    , 0b11  ,EN_PARAM5_CONTROL_Color        ,null                               ,"EN_PARAMX_CONTROL_Tooltip"],
    [ 0x0D, "EN_PATAM6_CONTROL"         , "AudioLayout3"    , 0b11  ,EN_PARAM6_CONTROL_Color        ,null                               ,"EN_PARAMX_CONTROL_Tooltip"],
    [ 0x0E, "EN_PATAM7_CONTROL"         , "AudioLayout3"    , 0b11  ,EN_PARAM7_CONTROL_Color        ,null                               ,"EN_PARAMX_CONTROL_Tooltip"],
    [ 0x0F, "EN_PATAM8_CONTROL"         , "AudioLayout3"    , 0b11  ,EN_PARAM8_CONTROL_Color        ,null                               ,"EN_PARAMX_CONTROL_Tooltip"]
];

#A.17.13.1 MPEG Decoder Control Selectors
set AudioMPEGDecoderControlSelectors_v2_Table =
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE command                     Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF, "MD_Reserved"               , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x00, "MD_CONTROL_UNDEFINED"      , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x01, "MD_DUAL_CHANNEL_CONTROL"   , "AudioLayout1"    , 0b10  ,MD_DUAL_CHANNEL_CONTROL_Color  ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"MD_DUAL_CHANNEL_CONTROL_Tooltip"],
    [ 0x02, "MD_SECOND_STEREO_CONTROL"  , "AudioLayout1"    , 0b10  ,MD_SECOND_STEREO_CONTROL_Color ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"MD_SECOND_STEREO_CONTROL_Tooltip"],
    [ 0x03, "MD_MULTILINGUAL_CONTROL"   , "AudioLayout1"    , 0b10  ,MD_MULTILINGUAL_CONTROL_Color  ,"MD_MULTILINGUAL_CONTROL_Validate" ,"MD_MULTILINGUAL_CONTROL_Tooltip"],
    [ 0x04, "MD_DYN_RANGE_CONTROL"      , "AudioLayout1"    , 0b10  ,MD_DYN_RANGE_CONTROL_Color     ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"DYN_RANGE_CONTROL_Tooltip"],
    [ 0x05, "MD_SCALING_CONTROL"        , "AudioLayout1"    , 0b11  ,MD_SCALING_CONTROL_Color       ,null                               ,"SCALING_CONTROL_Tooltip"],
    [ 0x06, "MD_HILO_SCALING_CONTROL"   , "HILO_SCALING_CONTROL_v2_sub", 0b11, MD_HILO_SCALING_CONTROL_color, null                      ,null],
    [ 0x07, "MD_UNDERFLOW_CONTROL"      , "AudioLayout1"    , 0b10  ,MD_UNDERFLOW_CONTROL_Color     ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"UNDERFLOW_CONTROL_Tooltip"], 
    [ 0x08, "MD_OVERFLOW_CONTROL"       , "AudioLayout1"    , 0b10  ,MD_OVERFLOW_CONTROL_Color      ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"OVERFLOW_CONTROL_Tooltip"],  
    [ 0x09, "MD_DECODER_ERROR_CONTROL"  , "AudioLayout2"    , 0b11  ,MD_DECODER_ERROR_CONTROL_Color ,null                               ,"GENERAL_ERROR_CONTROL_Tooltip"]
];

#A.17.13.2 AC-3 Decoder Control Selectors
set AudioAC3DecoderControlSelectors_v2_Table = 
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE command                     Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF, "AD_Reserved"               , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x00, "AD_CONTROL_UNDEFINED"      , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x01, "AD_MODE_CONTROL"           , "AudioLayout1"    , 0b10  ,AD_MODE_CONTROL_Color          ,"AD_MODE_CONTROL_Validate"         ,"AD_MODE_CONTROL_Tooltip"],
    [ 0x02, "AD_DYN_RANGE_CONTROL"      , "AudioLayout1"    , 0b10  ,AD_DYN_RANGE_CONTROL_Color     ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"DYN_RANGE_CONTROL_Tooltip"],
    [ 0x03, "AD_SCALING_CONTROL"        , "AudioLayout1"    , 0b11  ,AD_SCALING_CONTROL_Color       ,null                               ,"SCALING_CONTROL_Tooltip"],  
    [ 0x04, "AD_HILO_SCALING_CONTROL"   , "HILO_SCALING_CONTROL_v2_sub", 0b11, AD_HILO_SCALING_CONTROL_color, null                      ,null],                       
    [ 0x05, "AD_UNDERFLOW_CONTROL"      , "AudioLayout1"    , 0b10  ,AD_UNDERFLOW_CONTROL_Color     ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"UNDERFLOW_CONTROL_Tooltip"], 
    [ 0x06, "AD_OVERFLOW_CONTROL"       , "AudioLayout1"    , 0b10  ,AD_OVERFLOW_CONTROL_Color      ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"OVERFLOW_CONTROL_Tooltip"],  
    [ 0x07, "AD_DECODER_ERROR_CONTROL"  , "AudioLayout2"    , 0b11  ,AD_DECODER_ERROR_CONTROL_Color ,null                               ,"GENERAL_ERROR_CONTROL_Tooltip"]
];

#A.17.13.3 WMA Decoder Control Selectors
set AudioWMADecoderControlSelectors_v2_Table =
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE command                     Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF, "WD_Reserved"               , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x00, "WD_CONTROL_UNDEFINED"      , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x01, "WD_UNDERFLOW_CONTROL"      , "AudioLayout1"    , 0b10  ,WD_UNDERFLOW_CONTROL_Color     ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"UNDERFLOW_CONTROL_Tooltip"], 
    [ 0x02, "WD_OVERFLOW_CONTROL"       , "AudioLayout1"    , 0b10  ,WD_OVERFLOW_CONTROL_Color      ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"OVERFLOW_CONTROL_Tooltip"],  
    [ 0x03, "WD_DECODER_ERROR_CONTROL"  , "AudioLayout2"    , 0b11  ,WD_DECODER_ERROR_CONTROL_Color ,null                               ,"GENERAL_ERROR_CONTROL_Tooltip"]
];

#A.17.13.4 DTS Decoder Control Selectors
set AudioDTSDecoderControlSelectors_v2_Table =
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE command                     Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF, "DD_Reserved"               , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x00, "DD_CONTROL_UNDEFINED"      , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x01, "DD_UNDERFLOW_CONTROL"      , "AudioLayout1"    , 0b10  ,DD_UNDERFLOW_CONTROL_Color     ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"UNDERFLOW_CONTROL_Tooltip"], 
    [ 0x02, "DD_OVERFLOW_CONTROL"       , "AudioLayout1"    , 0b10  ,DD_OVERFLOW_CONTROL_Color      ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"OVERFLOW_CONTROL_Tooltip"],  
    [ 0x03, "DD_DECODER_ERROR_CONTROL"  , "AudioLayout2"    , 0b11  ,DD_DECODER_ERROR_CONTROL_Color ,null                               ,"GENERAL_ERROR_CONTROL_Tooltip"]
];

#A.17.14 Endpoint Control Selectors
set AudioEndpointControlSelectors_v2_Table = 
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE command                     Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF, "EP_Reserved"               , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x00, "EP_CONTROL_UNDEFINED"      , null              , 0b00  ,null                           ,null                               ,null],
    [ 0x01, "EP_PITCH_CONTROL"          , "AudioLayout1"    , 0b10  ,EP_PITCH_CONTROL_Color         ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"EP_PITCH_CONTROL_Tooltip"], 
    [ 0x02, "EP_DATA_OVERRUN_CONTROL"   , "AudioLayout1"    , 0b10  ,EP_DATA_OVERRUN_CONTROL_Color  ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"EP_DATA_OVERRUN_CONTROL_Tooltip"], 
    [ 0x03, "EP_DATA_UNDERRUN_CONTROL"  , "AudioLayout1"    , 0b10  ,EP_DATA_UNDERRUN_CONTROL_Color ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"EP_DATA_UNDERRUN_CONTROL_Tooltip"]
];

set AudioControlSelectors_v2_Table = 
[
    #-----------------------------------------------------------------------------------------------
    #  Internal Key , Name in   , The associated
    #  for this CS    Short       table  
    #-----------------------------------------------------------------------------------------------
    [   0xFF        , "XX"      ,null],
    [   0x01        , "CS"      ,AudioClockSourceControlSelectors_v2_Table],
    [   0x02        , "CX"      ,AudioClockSelectorControlSelectors_v2_Table],
    [   0x03        , "CM"      ,AudioClockMultiplierControlSelectors_v2_Table],
    [   0x04        , "TE"      ,AudioTerminalControlSelectors_v2_Table],
    [   0x05        , "MU"      ,AudioMixerControlSelectors_v2_Table],
    [   0x06        , "SU"      ,AudioSelectorControlSelectors_v2_Table],
    [   0x07        , "FU"      ,AudioFeatureUnitControlSelectors_v2_Table],
    [   0x08        , "PE"      ,AudioPESectionEffectUnitControlSelectors_v2_Table],
    [   0x09        , "RV"      ,AudioReverberationEffectUnitControlSelectors_v2_Table],
    [   0x0A        , "MD"      ,AudioMDEffectUnitControlSelectors_v2_Table],         
    [   0x0B        , "DR"      ,AudioDRCEffectUnitControlSelectors_v2_Table],  
    [   0x0C        , "UD"      ,AudioUpDownMixProcessingUnitControlSelectors_v2_Table], 
    [   0x0D        , "DP"      ,AudioDolbyPrologicProcessingUnitControlSelectors_v2_Table], 
    [   0x0E        , "ST"      ,AudioStereoExtenderProcessingUnitControlSelectors_v2_Table], 
    [   0x0F        , "XU"      ,AudioExtensionUnitControlSelectors_v2_Table], 
    [   0x10        , "AS"      ,AudioStreamingInterfaceControlSelectors_v2_Table], 
    [   0x11        , "EN"      ,AudioEncoderControlSelectors_v2_Table], 
    [   0x12        , "MD"      ,AudioMPEGDecoderControlSelectors_v2_Table], 
    [   0x13        , "AD"      ,AudioAC3DecoderControlSelectors_v2_Table],  
    [   0x14        , "WD"      ,AudioWMADecoderControlSelectors_v2_Table],  
    [   0x15        , "DD"      ,AudioDTSDecoderControlSelectors_v2_Table]
];

#***************************************************************************************************
#Universal Serial Bus Device Class Definition for Audio Devices Release 3.0 Specific
#***************************************************************************************************
#A.8 Audio Class-Specific Descriptor Types
set AudioDescriptorType_v3_Table =
[
    [ 0xFF, "Illegal"],
    [ 0x20, "Audio_CS_UNDEFINED"],
    [ 0x21, "Audio_CS_DEVICE"		],
    [ 0x22, "Audio_CS_CONFIGURATION"],
    [ 0x23, "Audio_CS_STRING"],
    [ 0x24, "Audio_CS_INTERFACE"],
    [ 0x25, "Audio_CS_ENDPOINT"],
	[ 0x26, "Audio_CS_CLUSTER"]
];

#A.10 CLUSTER DESCRIPTOR SEGMENT TYPES
#Table A-10: Cluster Descriptor Segment Types
set ClusterDescriptorSegmentTypeTable =
[
    [ 0x00, "SEGMENT_UNDEFINED",null],
    [ 0x01, "CLUSTER_DESCRIPTION", "CLUSTER_DESCRIPTION_sub"],
    [ 0x1F, "CLUSTER_VENDOR_DEFINED", "SEGMENT_VENDOR_DEFINED_sub"],
    [ 0x20, "CHANNEL_INFORMATION", "CHANNEL_INFORMATION_sub"],
    [ 0x21, "CHANNEL_AMBISONIC", "CHANNEL_AMBISONIC_sub"],
	[ 0x22, "CHANNEL_DESCRIPTION", "CHANNEL_DESCRIPTION_sub"],
    [ 0xFE, "CHANNEL_VENDOR_DEFINED", "SEGMENT_VENDOR_DEFINED_sub"],
    [ 0xFF, "END_SEGMENT", "END_SEGMENT_sub"]
];

#A.11 CHANNEL PURPOSE DEFI NITIONS
#Table A-11: Channel Purpose Definitions
set ChannelPurposeDefinitionsTable =
[
    [ 0x00, "PURPOSE_UNDEFINED"],
    [ 0x01, "GENERIC_AUDIO"],
    [ 0x02, "VOICE"],
    [ 0x03, "SPEECH"],
    [ 0x04, "AMBIENT"],
	[ 0x05, "REFERENCE"],
    [ 0x06, "ULTRASONIC"],
    [ 0x07, "VIBROKINETIC"],
    [ 0xFF, "NON_AUDIO"]
];

#A.13 AMBISONIC COMPONENT ORDERING CONVENTION  TYPES
#Table A-13: Ambisonic Component Ordering Convention Types
set AmbisonicComponentOrderingTable =
[
    [ 0x00, "ORD_TYPE_UNDEFINED"],
    [ 0x01, "AMBISONIC_CHANNEL_NUMBER (ACN)"],
    [ 0x02, "FURSE_MALHAM"],
    [ 0x03, "SINGLE_INDEX_DESIGNATION (SID)"]
];

#A.14 AMBISONIC NORMALIZATION TYPES
#Table A-14: Ambisonic Normalization Types
set AmbisonicNormalizationTypesTable =
[
    [ 0x00, "NORM_TYPE_UNDEFINED"],
    [ 0x01, "maxN"],
    [ 0x02, "SN3D"],
    [ 0x03, "N3D"],
    [ 0x04, "SN2D"],
    [ 0x05, "N2D"]
];

set AudioChannelRelationship = 
[
    #Iman: Chack Values Because Its not defined in spec.
    [ 0x00, "Relationship undefined - UND"],
    [ 0x76, "MONO - M" ],
    [ 0x77, "LEFT - L" ],
    [ 0x78, "RIGHT - R" ],
    [ 0x79, "ARRAY - AR" ],
    [ 0x7A, "PATTERN_X - PX" ],
    [ 0x7B, "PATTERN_Y - PY" ],
    [ 0x7C, "PATTERN_A - PA" ],
    [ 0x7D, "PATTERN_B - PB" ],
    [ 0x7E, "PATTERN_M - PM" ],
    [ 0x7F, "PATTERN_S - PS" ],
    [ 0x80, "Front Left - FL" ],
    [ 0x81, "Front Right - FR" ],
    [ 0x82, "Front Center - FC" ],
    [ 0x83, "Front Left of Center - FLC" ],
    [ 0x84, "Front Right of Center - FRC" ],
    [ 0x85, "Front Wide Left - FWL" ],
    [ 0x86, "Front Wide Right - FWR" ],
    [ 0x87, "Side Left - SL" ],
    [ 0x88, "Side Right - SR" ],
    [ 0x89, "Surround Array Left - SAL" ],
    [ 0x8A, "Surround Array Right - SAR" ],
    [ 0x8B, "Back Left - BL" ],
    [ 0x8C, "Back Right - BR" ],
    [ 0x8D, "Back Center - BC" ],
    [ 0x8E, "Back Left of Center - BLC" ],
    [ 0x8F, "Back Right of Center - BRC" ],
    [ 0x90, "Back Wide Left - BWL" ],
    [ 0x91, "Back Wide Right - BWR" ],
    [ 0x92, "Top Center - TC" ],
    [ 0x93, "Top Front Left - TFL" ],
    [ 0x94, "Top Front Right - TFR" ],
    [ 0x95, "Top Front Center - TFC" ],
    [ 0x96, "Top Front Left of Center - TFLC" ],
    [ 0x97, "Top Front Right of Center - TFRC" ],
    [ 0x98, "Top Front Wide Left - TFWL" ],
    [ 0x99, "Top Front Wide Right - TFWR" ],
    [ 0x9A, "Top Side Left - TSL" ],
    [ 0x9B, "Top Side Right - TSR" ],
    [ 0x9C, "Top Surround Array Left - TSAL" ],
    [ 0x9D, "Top Surround Array Right - TSAR" ],
    [ 0x9E, "Top Back Left - TBL" ],
    [ 0x9F, "Top Back Right - TBR" ],
    [ 0xA0, "Top Back Center - TBC" ],
    [ 0xA1, "Top Back Left Of Center - TBLC" ],
    [ 0xA2, "Top Back Right Of Center - TBRC" ],
    [ 0xA3, "Top Back Wide Left - TBWL" ],
    [ 0xA4, "Top Back Wide Right - TBWR" ],
    [ 0xA5, "Bottom Center - BC" ],
    [ 0xA6, "Bottom Front Left - BFL" ],
    [ 0xA7, "Bottom Front Right - BFR" ],
    [ 0xA8, "Bottom Front Center - BFC" ],
    [ 0xA9, "Bottom Front Left Of Center - BFLC" ],
    [ 0xAA, "Bottom Front Right Of Center - BFRC" ],
    [ 0xAB, "Bottom Front Wide Left - BFWL" ],
    [ 0xAC, "Bottom Front Wide Right - BFWR" ],
    [ 0xAD, "Bottom Side Left - BSL" ],
    [ 0xAE, "Bottom Side Right - BSR" ],
    [ 0xAF, "Bottom Surround Array Left - BSAL" ],
    [ 0xB0, "Bottom Surround Array Right - BSAR" ],
    [ 0xB1, "Bottom Back Left - BBL" ],
    [ 0xB2, "Bottom Back Right - BBR" ],
    [ 0xB3, "Bottom Back Center - BBC" ],
    [ 0xB4, "Bottom Back Left Of Center - BBLC" ],
    [ 0xB5, "Bottom Back Right Of Center - BBRC" ],
    [ 0xB6, "Bottom Back Wide Left - BBWL" ],
    [ 0xB7, "Bottom Back Wide Right - BBWR" ],
    [ 0xB8, "Low Frequency Effects - LFE" ],
    [ 0xB9, "Low Frequency Effects Left - LFEL" ],
    [ 0xBA, "Low Frequency Effects Right - LFER" ],
    [ 0xBB, "Headphone Left - HPL" ],
    [ 0xBC, "Headphone Right - HPR" ]
];

#Appendix A. Audio Device Class Codes

#A.2 AUDIO FUNCTION SUBCLASS CODES
#Table A-2: Audio Function Subclass Codes
set AudioFunctionSubclassCodesTable = 
[
    [0x00, "FUNCTION_SUBCLASS_UNDEFINED"],
    [0x01, "FULL_ADC_3_0"],
    [0x20, "GENERIC_I/O"],
    [0x21, "HEADPHONE"],
    [0x22, "SPEAKER"],
    [0x23, "MICROPHONE"],
    [0x24, "HEADSET"],
    [0x25, "HEADSET_ADAPTER"],
    [0x26, "SPEAKERPHONE"]
];

#A.7 Audio Function Category Codes
#Table A-7: Audio Function Category Codes
set AudioFunctionCategoryCodes_v3_Table = 
[
    [0x00, "FUNCTION_SUBCLASS_UNDEFINED"],
    [0x01, "DESKTOP_SPEAKER"],
    [0x02, "HOME_THEATER"],
    [0x03, "MICROPHONE"],
    [0x04, "HEADSET"],
    [0x05, "TELEPHONE"],
    [0x06, "CONVERTER"],
    [0x07, "VOICE/SOUND_RECORDER"],
    [0x08, "I/O_BOX"],
    [0x09, "MUSICAL_INSTRUMENT"],
    [0x0A, "PRO-AUDIO"],
    [0x0B, "AUDIO/VIDEO"],
    [0x0C, "CONTROL_PANEL"],
	[0x0D, "HEADPHONE"],
	[0x0E, "GENERIC_SPEAKER"],
	[0x0F, "HEADSET_ADAPTER"],
	[0x10, "SPEAKERPHONE"]
	
#0x11..0xFE Reserved
];

#A.24 CONNECTOR TYPES
#Table A-24: Connector Types
set ConnectorTypeTable = 
[
    [0x00, "UNDEFINED"],
    [0x01, "2.5 MM PHONE CONNECTOR"],
    [0x02, "3.5 MM PHONE CONNECTOR"],
    [0x03, "6.35 MM PHONE CONNECTOR"],
    [0x04, "XLR/6.35MM COMBO CONNECTOR"],
    [0x05, "XLR"],
    [0x06, "OPTICAL/3.5MM COMBO CONNECTOR"],
    [0x07, "RCA"],
    [0x08, "BNC"],
    [0x09, "BANANA"],
    [0x0A, "BINDING POST"],
    [0x0B, "SPEAKON"],
    [0x0C, "SPRING CLIP"],
	[0x0D, "SCREW TYPE"],
	[0x0E, "DIN"],
	[0x0F, "MINI DIN"],
	[0x10, "EUROBLOCK"],
    [0x11, "USB TYPE-C"],
    [0x12, "RJ-11"],
    [0x13, "RJ-45"],
    [0x14, "TOSLINK"],
    [0x15, "HDMI"],
    [0x16, "Mini-HDMI"],
    [0x17, "Micro-HDMI"],
    [0x18, "DP"],
    [0x19, "MINI-DP"],
    [0x1A, "D-SUB"],
    [0x1B, "THUNDERBOLT"],
    [0x1C, "LIGHTNING"],
    [0x1D, "WIRELESS"],
    [0x1E, "USB STANDARD A"],
    [0x1F, "USB STANDARD B"],
    [0x20, "USB MINI-B"],
    [0x21, "USB MICRO-B"],
    [0x22, "USB MICRO-AB"],
    [0x23, "USB 3.0 MICRO-B"],
    [0xFF, "OTHER"]
];

set ConAttributeGenderTable = 
[
    [0x00, "Gender Neutral"],
    [0x01, "Male"],
    [0x02, "Female"],
    [0x03, "Reserved"]
];

#A.15 Audio Class-Specific AC Interface Descriptor Subtypes
#Table A-15: Audio Class-Specific AC Interface Descriptor Subtypes
set ACDescriptorSubType_v3_Table =
[
    [ 0xFF, "Illegal",null],
    [ 0x00, "AC_DESCRIPTOR_UNDEFINED",null],
    [ 0x01, "HEADER", "HEADER_sub"],
    [ 0x02, "INPUT_TERMINAL", "INPUT_TERMINAL_v3_sub"],
    [ 0x03, "OUTPUT_TERMINAL", "OUTPUT_TERMINAL_v3_sub"],
	[ 0x04, "EXTENDED_TERMINAL", "EXTENDED_TERMINAL_sub"],
    [ 0x05, "MIXER_UNIT", "MIXER_UNIT_v3_sub"],
    [ 0x06, "SELECTOR_UNIT", "SELECTOR_UNIT_v3_sub"],
    [ 0x07, "FEATURE_UNIT", "FEATURE_UNIT_v3_sub"],
    [ 0x08, "EFFECT_UNIT", "EFFECT_UNIT_v3_sub"],
    [ 0x09, "PROCESSING_UNIT", "PROCESSING_UNIT_v3_sub"],
    [ 0x0A, "EXTENSION_UNIT", "EXTENSION_UNIT_v3_sub"],
    [ 0x0B, "CLOCK_SOURCE", "CLOCK_SOURCE_v3_sub"],
    [ 0x0C, "CLOCK_SELECTOR", "CLOCK_SELECTOR_v3_sub"],
    [ 0x0D, "CLOCK_MULTIPLIER", "CLOCK_MULTIPLIER_v3_sub"],
    [ 0x0E, "SAMPLE_RATE_CONVERTER", "SAMPLE_RATE_CONVERTER_v3_sub"],
	[ 0x0F, "CONNECTORS", "CONNECTORS_sub"],
	[ 0x10, "POWER_DOMAIN", "POWER_DOMAIN_sub"]
];

#A.18 EXTENDED TERMINAL SE GMENT TYPES
#Table A-18: Extended Terminal Segment Types
set ExtendedTerminalSegmentTypeTable =
[
    [ 0x00, "SEGMENT_UNDEFINED",null],
    [ 0x1F, "TERMINAL_VENDOR_DEFINED", "SEGMENT_VENDOR_DEFINED_sub"],
    [ 0x20, "CHANNEL_BANDWIDTH", "CHANNEL_BANDWIDTH_sub"],
    [ 0x21, "CHANNEL_MAGNITUDE_RESPONSE", "CHANNEL_MAGNITUDE_RESPONSE_sub"],
    [ 0x22, "CHANNEL_MAGNITUDE_PHASE_RESPONSE", "CHANNEL_MAGNITUDE_PHASE_RESPONSE_sub"],
	[ 0x23, "CHANNEL_POSITION_XYZ", "CHANNEL_POSITION_XYZ_sub"],
    [ 0x24, "CHANNEL_POSITION_THETA_PHI", "CHANNEL_POSITION_THETA_PHI_sub"],
    [ 0xFE, "CHANNEL_VENDOR_DEFINED", "SEGMENT_VENDOR_DEFINED_sub"],
    [ 0xFF, "END_SEGMENT", "END_SEGMENT_sub"]
];

#Table A-16: Audio Class-Specific AS Interface Descriptor Subtypes
set ASDescriptorSubType_v3_Table = 
[
    [ 0xFF, "Illegal", null],
    [ 0x00, "AS_DESCRIPTOR_UNDEFINED", null],
    [ 0x01, "AS_GENERAL", "AS_GENERAL_v3_sub"],
    [ 0x02, "AS_VALID_FREQ_RANGE", "AS_VALID_FREQ_RANGE_sub"]
];

#Table A-19 Effect Unit Effect Types
set AudioEffectUnitEffectTypes_v3_Table = 
[
    [ 0xFF, "Illegal", null],
    [ 0x00, "EFFECT_UNDEFINED", null],
    [ 0x01, "PARAM_EQ_SECTION_EFFECT", "PARAM_EQ_SECTION_EFFECT_v3_sub"],
    [ 0x02, "REVERBERATION_EFFECT", "REVERBERATION_EFFECT_v3_sub"],
    [ 0x03, "MOD_DELAY_ERRECT", "MOD_DELAY_EFFECT_v2_v3_sub"],
    [ 0x04, "DYN_RANGE_COMP_EFFECT", "DYN_RANGE_COMP_EFFECT_v2_v3_sub"]
];

#Table A-20: Processing Unit Process Types
set AudioPUPType_v3_Table = 
[
	[ 0xFF, "Illegal", null],
	[ 0x00, "PROCESS_UNDEFINED", null],
	[ 0x01, "UP_DOWNMIX_PROCESS","UP_DOWNMIX_PROCESS_v3_sub"],
	[ 0x02, "STEREO_EXTENDER_PROCESS", "STEREO_EXTENDER_PROCESS_v3_sub"],
	[ 0x03, "MULTI_FUNCTION_PROCESS", "MULTI_FUNCTION_PROCESS_sub"]
];

#A.21 Audio Class-Specific Endpoint Descriptor Subtypes
#Table A-21: Audio Class-Specific Endpoint Descriptor Subtypes
set AudioEPDescriptorSubType_v3_Table =
[
	[0xFF, "Illegal"],
	[0x00, "DESCRIPTOR_UNDEFINED"],
	[0x01, "AUDIO_EP_GENERAL"]
];

#Encoder and Decoder Removed ***************

#Table A-22: Audio Class-Specific Request Codes
set AudioCSRequesCodes_v3_Table = 
[
    [0xFF, "Reserved"],
	[0x00, "REQUEST_CODE_UNDEFINED"],
	[0x01, "CUR"],
	[0x02, "RANGE"],
	[0x03, "MEM"],
	[0x04, "INTEN"],
	[0x05, "STRING"],
	[0x06, "HIGH_CAPABILITY_DESCRIPTOR"]
];

#A.23.2 Clock Source Control Selectors
set AudioClockSourceControlSelectors_v3_Table =
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE and INTEN command          Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF  , "CS_Reserved"             , null              , 0b000 ,null                           ,null                               ,null],
    [ 0x00  , "CS_CONTROL_UNDEFINED"    , null              , 0b000 ,null                           ,null                               ,null],
    [ 0x01  , "CS_SAM_FREQ_CONTROL"     , "AudioLayout3"    , 0b110 ,CS_SAM_FREQ_CONTROL_Color      ,null                               ,"GENERAL_FREQUENCY_CONTROL_Tooltip"],
    [ 0x02  , "CS_CLOCK_VALID_CONTROL"  , "AudioLayout1"    , 0b100 ,CS_CLOCK_VALID_CONTROL_Color   ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"CS_CLOCK_VALID_CONTROL_Tooltip" ]
];

#A.23.3 Clock Selector Control Selectors
set AudioClockSelectorControlSelectors_v3_Table =
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE and INTEN command          Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF  , "CX_Reserved"             , null              , 0b000 ,null                           ,null                               ,null],
    [ 0x00  , "CX_CONTROL_UNDEFINED"    , null              , 0b000 ,null                           ,null                               ,null],
    [ 0x01  , "CX_CLOCK_SELECTOR_CONTROL", "AudioLayout1"   , 0b110 ,CX_CLOCK_SELECTOR_CONTROL_Color,"NON_ZERO_VALUE_CONTROL_Validate"  ,"CX_CLOCK_SELECTOR_CONTROL_Tooltip"]
];

#A.23.4 Clock Multiplier Control Selectors
set AudioClockMultiplierControlSelectors_v3_Table =
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE and INTEN command          Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF  , "CM_Reserved"            , null              , 0b000 ,null                           ,null                               ,null],
    [ 0x00  , "CM_CONTROL_UNDEFINED"   , null              , 0b000 ,null                           ,null                               ,null],
    [ 0x01  , "CM_NUMERATOR_CONTROL"   , "AudioLayout2"    , 0b100 ,CM_NUMERATOR_CONTROL_Color     ,"NON_ZERO_VALUE_CONTROL_Validate"  ,"CM_NUMERATOR_CONTROL_Tooltip"],
    [ 0x02  , "CM_DENOMINATOR_CONTROL" , "AudioLayout2"    , 0b100 ,CM_DENOMINATOR_CONTROL_Color   ,"NON_ZERO_VALUE_CONTROL_Validate"  ,"CM_DENOMINATOR_CONTROL_Tooltip"]
];

#A.23.5 Terminal Control Selectors
set AudioTerminalControlSelectors_v3_Table = 
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE and INTEN command          Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF  , "TE_Reserved"             , null                       , 0b000 ,null                           ,null                               ,null],
    [ 0x00  , "TE_CONTROL_UNDEFINED"    , null                       , 0b000 ,null                           ,null                               ,null],
    [ 0x01  , "TE_INSERTION_CONTROL"    , "TE_INSERTION_CONTROL_sub" , 0b100 ,TE_INSERTION_CONTROL_Color     ,null                               ,null],
	[ 0x02  , "TE_OVERLOAD_CONTROL"     , "AudioLayout1"             , 0b100 ,TE_OVERLOAD_CONTROL_Color      ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"TE_OVERLOAD_CONTROL_Tooltip"],
	[ 0x03  , "TE_UNDERFLOW_CONTROL"    , "AudioLayout1"             , 0b100 ,TE_UNDERFLOW_CONTROL_Color     ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"UNDERFLOW_CONTROL_Tooltip"],
	[ 0x04  , "TE_OVERFLOW_CONTROL"     , "AudioLayout1"             , 0b100 ,TE_OVERFLOW_CONTROL_Color      ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"OVERFLOW_CONTROL_Tooltip"],
	[ 0x05  , "TE_LATENCY_CONTROL"      , "AudioLayout3"             , 0b100 ,TE_LATENCY_CONTROL_Color       ,null                               ,"LATENCY_CONTROL_Tooltip"]
];

#A.23.6 Mixer Control Selectors
set AudioMixerControlSelectors_v3_Table =
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE and INTEN command          Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF, "MU_Reserved"               , null              , 0b000 ,null                           ,null                               ,null],
    [ 0x00, "MU_CONTROL_UNDEFINED"      , null              , 0b000 ,null                           ,null                               ,null],
    [ 0x01, "MU_MIXER_CONTROL"          , "AudioLayout2"    , 0b110 ,MU_MIXER_CONTROL_Color         ,null                               ,"GENERAL_VOLUME_CONTROL_Tooltip"],
    [ 0x02, "MU_UNDERFLOW_CONTROL"      , "AudioLayout1"    , 0b100 ,MU_UNDERFLOW_CONTROL_Color     ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"UNDERFLOW_CONTROL_Tooltip"],
    [ 0x03, "MU_OVERFLOW_CONTROL"       , "AudioLayout1"    , 0b100 ,MU_OVERFLOW_CONTROL_Color      ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"OVERFLOW_CONTROL_Tooltip"], 
    [ 0x04, "MU_LATENCY_CONTROL"        , "AudioLayout3"    , 0b100 ,MU_LATENCY_CONTROL_Color       ,null                               ,"LATENCY_CONTROL_Tooltip"]
];

#A.23.7 Selector Control Selectors
set AudioSelectorControlSelectors_v3_Table = 
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE and INTEN command          Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF, "SU_Reserved"               , null              , 0b000 ,null                           ,null                               ,null],
    [ 0x00, "SU_CONTROL_UNDEFINED"      , null              , 0b000 ,null                           ,null                               ,null],
    [ 0x01, "SU_SELECTOR_CONTROL"       , "AudioLayout1"    , 0b100 ,SU_SELECTOR_CONTROL_Color      ,"NON_ZERO_VALUE_CONTROL_Validate"  ,"SU_SELECTOR_CONTROL_Tooltip"],
    [ 0x02, "SU_LATENCY_CONTROL"        , "AudioLayout3"    , 0b100 ,SU_LATENCY_CONTROL_Color       ,null                               ,"LATENCY_CONTROL_Tooltip"]
];

#A.23.8 Feature Unit Control Selectors
set AudioFeatureUnitControlSelectors_v3_Table =
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE and INTEN command           Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF, "FU_Reserved"               , null              , 0b000 ,null                           ,null                               ,null],
    [ 0x00, "FU_CONTROL_UNDEFINED"      , null              , 0b000 ,null                           ,null                               ,null],
    [ 0x01, "FU_MUTE_CONTROL"           , "AudioLayout1"    , 0b100 ,FU_MUTE_CONTROL_Color          ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"FU_MUTE_CONTROL_Tooltip" ],
    [ 0x02, "FU_VOLUME_CONTROL"         , "AudioLayout2"    , 0b110 ,FU_VOLUME_CONTROL_Color        ,null                               ,"GENERAL_VOLUME_CONTROL_Tooltip"],
    [ 0x03, "FU_BASS_CONTROL"           , "AudioLayout1"    , 0b110 ,FU_BASS_CONTROL_Color          ,null                               ,"GENERAL_FEATURE_UNIT_CONTROL_Tooltip" ],
    [ 0x04, "FU_MID_CONTROL"            , "AudioLayout1"    , 0b110 ,FU_MID_CONTROL_Color           ,null                               ,"GENERAL_FEATURE_UNIT_CONTROL_Tooltip" ],
    [ 0x05, "FU_TREBLE_CONTROL"         , "AudioLayout1"    , 0b110 ,FU_TREBLE_CONTROL_Color        ,null                               ,"GENERAL_FEATURE_UNIT_CONTROL_Tooltip" ],
    [ 0x06, "FU_GRAPHIC_EQUALIZER_CONTROL","GRAPHIC_EQUALIZER_CONTROL_v3_sub", 0b110, FU_GRAPHIC_EQUALIZER_CONTROL_Color, null           ,null],
    [ 0x07, "FU_AUTOMATIC_GAIN_CONTROL" , "AudioLayout1"    , 0b100 ,FU_AUTOMATIC_GAIN_CONTROL_Color,"BOOLEAN_VALUE_CONTROL_Validate"   ,"GENERAL_TRUE_FALSE_CONTROL_Tooltip"],
    [ 0x08, "FU_DELAY_CONTROL"          , "AudioLayout3"    , 0b110 ,FU_DELAY_CONTROL_Color         ,null                               ,"FU_DELAY_CONTROL_Tooltip" ],
    [ 0x09, "FU_BASS_BOOST_CONTROL"     , "AudioLayout1"    , 0b100 ,FU_BASS_BOOST_CONTROL_Color    ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"GENERAL_TRUE_FALSE_CONTROL_Tooltip"],
    [ 0x0A, "FU_LOUDNESS_CONTROL"       , "AudioLayout1"    , 0b100 ,FU_LOUDNESS_CONTROL_Color      ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"GENERAL_TRUE_FALSE_CONTROL_Tooltip"],
    [ 0x0B, "FU_INPUT_GAIN_CONTROL"     , "AudioLayout2"    , 0b110 ,FU_INPUT_GAIN_CONTROL_Color    ,null                               ,"GENERAL_VOLUME_CONTROL_Tooltip"],
    [ 0x0C, "FU_INPUT_GAIN_PAD_CONTROL" , "AudioLayout2"    , 0b110 ,FU_INPUT_GAIN_PAD_CONTROL_Color,null                               ,"GENERAL_VOLUME_CONTROL_Tooltip"],
    [ 0x0D, "FU_PHASE_INVERTER_CONTROL" , "AudioLayout1"    , 0b100 ,FU_PHASE_INVERTER_CONTROL_Color,"BOOLEAN_VALUE_CONTROL_Validate"   ,"GENERAL_TRUE_FALSE_CONTROL_Tooltip"],
    [ 0x0E, "FU_UNDERFLOW_CONTROL"      , "AudioLayout1"    , 0b100 ,FU_UNDERFLOW_CONTROL_Color     ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"UNDERFLOW_CONTROL_Tooltip"], 
    [ 0x0F, "FU_OVERFLOW_CONTROL"       , "AudioLayout1"    , 0b100 ,FU_OVERFLOW_CONTROL_Color      ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"OVERFLOW_CONTROL_Tooltip"],  
    [ 0x10, "FU_LATENCY_CONTROL"        , "AudioLayout3"    , 0b100 ,FU_LATENCY_CONTROL_Color       ,null                               ,"LATENCY_CONTROL_Tooltip"]    
];

#A.23.9.1 Parametric Equalizer Section Effect Unit Control Selectors
set AudioPESectionEffectUnitControlSelectors_v3_Table = 
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE and INTEN command           Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF, "PE_Reserved"               , null              , 0b000 ,null                           ,null                               ,null],
    [ 0x00, "PE_CONTROL_UNDEFINED"      , null              , 0b000 ,null                           ,null                               ,null],
    [ 0x01, "PE_ENABLE_CONTROL"         , "AudioLayout1"    , 0b100 ,PE_ENABLE_CONTROL_Color        ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"GENERAL_TRUE_FALSE_CONTROL_Tooltip"],
    [ 0x02, "PE_CENTERFREQ_CONTROL"     , "AudioLayout3"    , 0b110 ,PE_CENTERFREQ_CONTROL_Color    ,null                               ,"GENERAL_FREQUENCY_CONTROL_Tooltip"],
    [ 0x03, "PE_QFACTOR_CONTROL"        , "AudioLayout3"    , 0b110 ,PE_QFACTOR_CONTROL_Color       ,null                               ,"PE_QFACTOR_CONTROL_Tooltip" ],
    [ 0x04, "PE_GAIN_CONTROL"           , "AudioLayout2"    , 0b110 ,PE_GAIN_CONTROL_Color          ,null                               ,"GENERAL_VOLUME_CONTROL_Tooltip" ],
    [ 0x05, "PE_UNDERFLOW_CONTROL"      , "AudioLayout1"    , 0b100 ,PE_UNDERFLOW_CONTROL_Color     ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"UNDERFLOW_CONTROL_Tooltip"], 
    [ 0x06, "PE_OVERFLOW_CONTROL"       , "AudioLayout1"    , 0b100 ,PE_OVERFLOW_CONTROL_Color      ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"OVERFLOW_CONTROL_Tooltip"],  
    [ 0x07, "PE_LATENCY_CONTROL"        , "AudioLayout3"    , 0b100 ,PE_LATENCY_CONTROL_Color       ,null                               ,"LATENCY_CONTROL_Tooltip"]    
];

#A.23.9.2 Reverberation Effect Unit Control Selectors
set AudioReverberationEffectUnitControlSelectors_v3_Table =
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE and INTEN command           Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF, "RV_Reserved"               , null              , 0b000 ,null                           ,null                               ,null],
    [ 0x00, "RV_CONTROL_UNDEFINED"      , null              , 0b000 ,null                           ,null                               ,null],
    [ 0x01, "RV_ENABLE_CONTROL"         , "AudioLayout1"    , 0b100 ,RV_ENABLE_CONTROL_Color        ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"GENERAL_TRUE_FALSE_CONTROL_Tooltip"],
    [ 0x02, "RV_TYPE_CONTROL"           , "AudioLayout1"    , 0b110 ,RV_TYPE_CONTROL_Color          ,null                               ,"RV_TYPE_CONTROL_Tooltip"],
    [ 0x03, "RV_LEVEL_CONTROL"          , "AudioLayout1"    , 0b110 ,RV_LEVEL_CONTROL_Color         ,null                               ,"GENERAL_PERCENTAGE_CONTROL_Tooltip"],
    [ 0x04, "RV_TIME_CONTROL"           , "AudioLayout2"    , 0b110 ,RV_TIME_CONTROL_Color          ,null                               ,"RV_TIME_CONTROL_Tooltip"],
    [ 0x05, "RV_FEEDBACK_CONTROL"       , "AudioLayout1"    , 0b110 ,RV_FEEDBACK_CONTROL_Color      ,null                               ,"GENERAL_PERCENTAGE_CONTROL_Tooltip"],
    [ 0x06, "RV_FREDELAY_CONTROL"       , "AudioLayout2"    , 0b110 ,RV_FREDELAY_CONTROL_Color      ,null                               ,"GENERAL_MICROSECOND_CONTROL_Tooltip"],
    [ 0x07, "RV_DENSITY_CONTROL"        , "AudioLayout1"    , 0b110 ,RV_DENSITY_CONTROL_Color       ,"RV_DENSITY_CONTROL_Validate"      ,"RV_DENSITY_CONTROL_Tooltip"],
    [ 0x08, "RV_HIFREQ_ROLLOFF_CONTROL" , "AudioLayout3"    , 0b110 ,RV_HIFREQ_ROLLOFF_CONTROL_Color,null                               ,"GENERAL_FREQUENCY_CONTROL_Tooltip"],
    [ 0x09, "RV_UNDERFLOW_CONTROL"      , "AudioLayout1"    , 0b100 ,RV_UNDERFLOW_CONTROL_Color     ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"UNDERFLOW_CONTROL_Tooltip"], 
    [ 0x0A, "RV_OVERFLOW_CONTROL"       , "AudioLayout1"    , 0b100 ,RV_OVERFLOW_CONTROL_Color      ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"OVERFLOW_CONTROL_Tooltip"],  
    [ 0x0B, "RV_LATENCY_CONTROL"        , "AudioLayout3"    , 0b100 ,RV_LATENCY_CONTROL_Color       ,null                               ,"LATENCY_CONTROL_Tooltip"]    
];

#A.23.9.3 Modulation Delay Effect Unit Control Selectors
set AudioMDEffectUnitControlSelectors_v3_Table = 
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE and INTEN command           Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF, "MD_Reserved"               , null              , 0b000 ,null                           ,null                               ,null],
    [ 0x00, "MD_CONTROL_UNDEFINED"      , null              , 0b000 ,null                           ,null                               ,null],
    [ 0x01, "MD_ENABLE_CONTROL"         , "AudioLayout1"    , 0b100 ,MD_ENABLE_CONTROL_Color        ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"GENERAL_TRUE_FALSE_CONTROL_Tooltip"],
    [ 0x02, "MD_BALANCE_CONTROL"        , "AudioLayout1"    , 0b110 ,MD_BALANCE_CONTROL_Color       ,"MD_BALANCE_CONTROL_Validate"      ,"MD_BALANCE_CONTROL_Tooltip"],
    [ 0x03, "MD_RATE_CONTROL"           , "AudioLayout2"    , 0b110 ,MD_RATE_CONTROL_Color          ,null                               ,"MD_RATE_CONTROL_Tooltip"],
    [ 0x04, "MD_DEPTH_CONTROL"          , "AudioLayout2"    , 0b110 ,MD_DEPTH_CONTROL_Color         ,null                               ,"MD_DEPTH_CONTROL_Tooltip"],
    [ 0x05, "MD_TIME_CONTROL"           , "AudioLayout2"    , 0b110 ,MD_TIME_CONTROL_Color          ,null                               ,"MD_DEPTH_CONTROL_Tooltip"],
    [ 0x06, "MD_FEEDBACK_CONTROL"       , "AudioLayout1"    , 0b110 ,MD_FEEDBACK_CONTROL_Color      ,null                               ,"GENERAL_PERCENTAGE_CONTROL_Tooltip"],
    [ 0x07, "MD_UNDERFLOW_CONTROL"      , "AudioLayout1"    , 0b100 ,MD_UNDERFLOW_CONTROL_Color     ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"UNDERFLOW_CONTROL_Tooltip"], 
    [ 0x08, "MD_OVERFLOW_CONTROL"       , "AudioLayout1"    , 0b100 ,MD_OVERFLOW_CONTROL_Color      ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"OVERFLOW_CONTROL_Tooltip"],  
    [ 0x09, "MD_LATENCY_CONTROL"        , "AudioLayout3"    , 0b100 ,MD_LATENCY_CONTROL_Color       ,null                               ,"LATENCY_CONTROL_Tooltip"]    
];

#A.23.9.4 Dynamic Range Compressor Effect Unit Control Selectors
set AudioDRCEffectUnitControlSelectors_v3_Table = 
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE and INTEN command           Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF, "DR_Reserved"               , null              , 0b000 ,null                           ,null                               ,null],
    [ 0x00, "DR_CONTROL_UNDEFINED"      , null              , 0b000 ,null                           ,null                               ,null],
    [ 0x01, "DR_ENABLE_CONTROL"         , "AudioLayout1"    , 0b100 ,DR_ENABLE_CONTROL_Color        ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"GENERAL_TRUE_FALSE_CONTROL_Tooltip"],
    [ 0x02, "DR_COMPRESSION_RATE_CONTROL","AudioLayout2"    , 0b110 ,DR_COMPRESSION_RATE_CONTROL_Color,null                             ,"DR_COMPRESSION_RATE_CONTROL_Tooltip"],
    [ 0x03, "DR_MAXAMPL_CONTROL"        , "AudioLayout2"    , 0b110 ,DR_MAXAMPL_CONTROL_Color       ,null                               ,"GENERAL_AMPL_CONTROL_Tooltip"],
    [ 0x04, "DR_THRESHOLD_CONTROL"      , "AudioLayout2"    , 0b110 ,DR_THRESHOLD_CONTROL_Color     ,null                               ,"GENERAL_AMPL_CONTROL_Tooltip"],
    [ 0x05, "DR_ATTACK_TIME_CONTROL"    , "AudioLayout2"    , 0b110 ,DR_ATTACK_TIME_CONTROL_Color   ,null                               ,"GENERAL_MICROSECOND_CONTROL_Tooltip" ],
    [ 0x06, "DR_RELEASE_TIME_CONTROL"   , "AudioLayout2"    , 0b110 ,DR_RELEASE_TIME_CONTROL_Color  ,null                               ,"GENERAL_MICROSECOND_CONTROL_Tooltip" ],
    [ 0x07, "DR_UNDERFLOW_CONTROL"      , "AudioLayout1"    , 0b100 ,DR_UNDERFLOW_CONTROL_Color     ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"UNDERFLOW_CONTROL_Tooltip"], 
    [ 0x08, "DR_OVERFLOW_CONTROL"       , "AudioLayout1"    , 0b100 ,DR_OVERFLOW_CONTROL_Color      ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"OVERFLOW_CONTROL_Tooltip"],  
    [ 0x09, "DR_LATENCY_CONTROL"        , "AudioLayout3"    , 0b100 ,DR_LATENCY_CONTROL_Color       ,null                               ,"LATENCY_CONTROL_Tooltip"]    
];

#A.23.10.1 Up/Down-mix Processing Unit Control Selectors
set AudioUpDownMixProcessingUnitControlSelectors_v3_Table =
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE and INTEN command           Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF, "UD_Reserved"               , null              , 0b000 ,null                           ,null                               ,null],
    [ 0x00, "UD_CONTROL_UNDEFINED"      , null              , 0b000 ,null                           ,null                               ,null],
    [ 0x01, "UD_MODE_SELECT_CONTROL"    , "AudioLayout1"    , 0b100 ,UD_MODE_SELECT_CONTROL_Color   ,"NON_ZERO_VALUE_CONTROL_Validate"  ,"GENERAL_MODE_SELECT_CONTROL_Tooltip"],
    [ 0x02, "UD_UNDERFLOW_CONTROL"      , "AudioLayout1"    , 0b100 ,UD_UNDERFLOW_CONTROL_Color     ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"UNDERFLOW_CONTROL_Tooltip"], 
    [ 0x03, "UD_OVERFLOW_CONTROL"       , "AudioLayout1"    , 0b100 ,UD_OVERFLOW_CONTROL_Color      ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"OVERFLOW_CONTROL_Tooltip"],  
    [ 0x04, "UD_LATENCY_CONTROL"        , "AudioLayout3"    , 0b100 ,UD_LATENCY_CONTROL_Color       ,null                               ,"LATENCY_CONTROL_Tooltip"]    
];

#A.23.10.2 Stereo Extender Processing Unit Control Selectors
set AudioStereoExtenderProcessingUnitControlSelectors_v3_Table = 
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE and INTEN command           Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF, "ST_Reserved"               , null              , 0b000 ,null                           ,null                               ,null],
    [ 0x00, "ST_EXT_CONTROL_UNDEFINED"  , null              , 0b000 ,null                           ,null                               ,null],
    [ 0x01, "ST_EXT_WIDTH_CONTROL"      , "AudioLayout1"    , 0b110 ,ST_WIDTH_CONTROL_Color         ,null                               ,"GENERAL_BYTE_VALUE_CONTROL_Tooltip"],
    [ 0x02, "ST_EXT_UNDERFLOW_CONTROL"  , "AudioLayout1"    , 0b100 ,ST_UNDERFLOW_CONTROL_Color     ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"UNDERFLOW_CONTROL_Tooltip"], 
    [ 0x03, "ST_EXT_OVERFLOW_CONTROL"   , "AudioLayout1"    , 0b100 ,ST_OVERFLOW_CONTROL_Color      ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"OVERFLOW_CONTROL_Tooltip"],  
    [ 0x04, "ST_EXT_LATENCY_CONTROL"    , "AudioLayout3"    , 0b100 ,ST_LATENCY_CONTROL_Color       ,null                               ,"LATENCY_CONTROL_Tooltip"]    
];

#A.23.11 Extension Unit Control Selectors
set AudioExtensionUnitControlSelectors_v3_Table = 
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE and INTEN command           Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF, "XU_Reserved"               , null              , 0b000 ,null                           ,null                               ,null],
    [ 0x00, "XU_CONTROL_UNDEFINED"      , null              , 0b000 ,null                           ,null                               ,null],
    [ 0x01, "XU_UNDERFLOW_CONTROL"      , "AudioLayout1"    , 0b100 ,XU_UNDERFLOW_CONTROL_Color     ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"UNDERFLOW_CONTROL_Tooltip"], 
    [ 0x02, "XU_OVERFLOW_CONTROL"       , "AudioLayout1"    , 0b100 ,XU_OVERFLOW_CONTROL_Color      ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"OVERFLOW_CONTROL_Tooltip"],  
    [ 0x03, "XU_LATENCY_CONTROL"        , "AudioLayout3"    , 0b100 ,XU_LATENCY_CONTROL_Color       ,null                               ,"LATENCY_CONTROL_Tooltip"]    
];

#A.23.12 AudioStreaming Interface Control Selectors
set AudioStreamingInterfaceControlSelectors_v3_Table =
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE and INTEN command           Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF, "AS_Reserved"               , null              , 0b000 ,null                           ,null                               ,null],
    [ 0x00, "AS_CONTROL_UNDEFINED"      , null              , 0b000 ,null                           ,null                               ,null],
    [ 0x01, "AS_ACT_ALT_SETTING_CONTROL" , "AudioLayout1"   , 0b100 ,AS_ACT_ALT_SETTING_CONTROL_Color,null                              ,"GENERAL_BYTE_VALUE_CONTROL_Tooltip"],
    [ 0x02, "AS_VAL_ALT_SETTINGS_CONTROL", "AS_VAL_ALT_SETTINGS_CONTROL_v3_sub", 0b100, AS_VAL_ALT_SETTINGS_CONTROL_Color,null            ,null],
    [ 0x03, "AS_AUDIO_DATA_FORMAT_CONTROL", "AudioLayout3"  , 0b100 ,AS_AUDIO_DATA_FORMAT_CONTROL_Color,null                            ,"AS_AUDIO_DATA_FORMAT_CONTROL_ToolTip" ]
];

#A.23.13 Endpoint Control Selectors
set AudioEndpointControlSelectors_v3_Table = 
[
    #---------------------------------------------------------------------------------------------------------------------------------------------
    # Value , SubName                   , Layout Function   , bitmap of supporting  ,Color          ,Validate                           ,Tooltip
    #                                                         CUR, RANGE and INTEN command           Function                            Function
    #----------------------------------------------------------------------------------------------------------------------------------------------
    [ 0xFF, "EP_Reserved"               , null              , 0b000 ,null                           ,null                               ,null],
    [ 0x00, "EP_CONTROL_UNDEFINED"      , null              , 0b000 ,null                           ,null                               ,null],
    [ 0x01, "EP_PITCH_CONTROL"          , "AudioLayout1"    , 0b100 ,EP_PITCH_CONTROL_Color         ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"EP_PITCH_CONTROL_Tooltip"], 
    [ 0x02, "EP_DATA_OVERRUN_CONTROL"   , "AudioLayout1"    , 0b100 ,EP_DATA_OVERRUN_CONTROL_Color  ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"EP_DATA_OVERRUN_CONTROL_Tooltip"], 
    [ 0x03, "EP_DATA_UNDERRUN_CONTROL"  , "AudioLayout1"    , 0b100 ,EP_DATA_UNDERRUN_CONTROL_Color ,"BOOLEAN_VALUE_CONTROL_Validate"   ,"EP_DATA_UNDERRUN_CONTROL_Tooltip"]
];

set AudioControlSelectors_v3_Table = 
[
    #-----------------------------------------------------------------------------------------------
    #  Internal Key , Name in   , The associated
    #  for this CS    Short       table  
    #-----------------------------------------------------------------------------------------------
    [   0xFF        , "XX"      ,null],
    [   0x01        , "CS"      ,AudioClockSourceControlSelectors_v3_Table],
    [   0x02        , "CX"      ,AudioClockSelectorControlSelectors_v3_Table],
    [   0x03        , "CM"      ,AudioClockMultiplierControlSelectors_v3_Table],
    [   0x04        , "TE"      ,AudioTerminalControlSelectors_v3_Table],
    [   0x05        , "MU"      ,AudioMixerControlSelectors_v3_Table],
    [   0x06        , "SU"      ,AudioSelectorControlSelectors_v3_Table],
    [   0x07        , "FU"      ,AudioFeatureUnitControlSelectors_v3_Table],
    [   0x08        , "PE"      ,AudioPESectionEffectUnitControlSelectors_v3_Table],
    [   0x09        , "RV"      ,AudioReverberationEffectUnitControlSelectors_v3_Table],
    [   0x0A        , "MD"      ,AudioMDEffectUnitControlSelectors_v3_Table],
    [   0x0B        , "DR"      ,AudioDRCEffectUnitControlSelectors_v3_Table],  
    [   0x0C        , "UD"      ,AudioUpDownMixProcessingUnitControlSelectors_v3_Table],
    [   0x0E        , "ST"      ,AudioStereoExtenderProcessingUnitControlSelectors_v3_Table], 
    [   0x0F        , "XU"      ,AudioExtensionUnitControlSelectors_v3_Table], 
    [   0x10        , "AS"      ,AudioStreamingInterfaceControlSelectors_v3_Table]
];

#***************************************************************************************************
#Universal Serial Bus Device Class Definition for Audio Data Formats Release 1.0
#***************************************************************************************************
#Table A-3: Audio Data Format Type III Codes
set AudioDataFormatSpecific_v1_Table = 
[
		[0xFFFF, "Illegal", null],
		[0x0000, "TYPE_I_UNDEFINED", null],
		[0x0001, "PCM", null],
		[0x0002, "PCM8", null],
		[0x0003, "IEEE_FLOAT", null],
		[0x0004, "ALAW", null],
		[0x0005, "MULAW", null],
		[0x1000, "TYPE_II_UNDEFINED", null],
		[0x1001, "MPEG", "MPEG_v1_sub"],
		[0x1002, "AC_3", "AC_3_v1_sub"],
		[0x2000, "TYPE_III_UNDEFINED", null],
		[0x2001, "IEC1937_AC_3", null],
		[0x2002, "IEC1937_MPEG_1_Layer1", null],
		[0x2003, "IEC1937_MPEG_1_Layer2_3_or_IEC1937_MPEG_2_NOEXT", null],
		[0x2004, "IEC1937_MPEG_2_EXT", null],
		[0x2005, "IEC1937_MPEG_2_Layer1_LS", null],
		[0x2006, "IEC1937_MPEG_2_Layer2_3_LS", null]
];

#A.2 Format Type Codes
#Table A-4: Format Type Codes
set AudioDataFormatType_v1_Table = 
[
		[0xFF, "Illegal", null],
		[0x00, "FORMAT_TYPE_UNDEFINED", null],
		[0x01, "FORMAT_TYPE_I", "FORMAT_TYPE_I_v1_sub"],
		[0x02, "FORMAT_TYPE_II", "FORMAT_TYPE_II_v1_sub"],
		[0x03, "FORMAT_TYPE_III", "FORMAT_TYPE_III_v1_sub"]
];

#A.3 Format-Specific Control Selectors
#A.3.1 MPEG Control Selectors
#Table A-5: MPEG Control Selectors
set AudioMPEGControlSelectors_v1_Table = 
[
		[0xFF, "Illegal"],
		[0x00, "MPEG_CONTROL_UNDEFINED"],
		[0x01, "MP_DUAL_CHANNEL_CONTROL"],
		[0x02, "MP_SECOND_STEREO_CONTROL"],
		[0x03, "MP_MULTILINGUAL_CONTROL"],
		[0x04, "MP_DYN_RANGE_CONTROL"],
		[0x05, "MP_SCALING_CONTROL"],
		[0x06, "MP_HILO_SCALING_CONTROL"]
];

#A.3.2 AC-3 Control Selectors
#Table A-6: AC-3 Control Selectors
set AudioAC3ControlSelectors_v1_Table = 
[
		[0xFF, "Illegal"],
		[0x00, "AC_CONTROL_UNDEFINED"],
		[0x01, "AC_MODE_CONTROL"],
		[0x02, "AC_DYN_RANGE_CONTROL"],
		[0x03, "AC_SCALING_CONTROL"],
		[0x04, "AC_HILO_SCALING_CONTROL"]
];

#***************************************************************************************************
#Universal Serial Bus Device Class Definition for Audio Data Formats Release 2.0
#***************************************************************************************************
#A.2.1 Audio Data Format Type I Bit Allocations
set AudioDataFormatTypeI_v2_Bitmap = 
[
    [ 0, "PCM"],
    [ 1, "PCM8"],
    [ 2, "IEEE_FLOAT"],
    [ 3, "ALAW"],
    [ 4, "MULAW"],
    [31, "TYPE_I_RAW_DATA"]
];

#A.2.2 Audio Data Format Type II Bit Allocations
set AudioDataFormatTypeII_v2_Bitmap = 
[
    [ 0, "MPEG"],
    [ 1, "AC-3"],
    [ 2, "WMA"],
    [ 3, "DTS"],
    [31, "TYPE_II_RAW_DATA"]
];

#A.2.3 Audio Data Format Type III Bit Allocations
set AudioDataFormatTypeIII_v2_Bitmap = 
[
    [ 0, "IEC61937_AC-3"],
    [ 1, "IEC61937_MPEG-1_Layer1"],
    [ 2, "IEC61937_MPEG-1_Layer2/3 or IEC61937__MPEG-2_NOEXT"],
    [ 3, "IEC61937_MPEG-2_EXT"],
    [ 4, "IEC61937_MPEG-2_AAC_ADTS"],
    [ 5, "IEC61937_MPEG-2_Layer1_LS"],
    [ 6, "IEC61937_MPEG-2_Layer2/3_LS"],
    [ 7, "IEC61937_DTS-I"],
    [ 8, "IEC61937_DTS-II"],
    [ 9, "IEC61937_DTS-III"],
    [10, "IEC61937_ATRAC"],
    [11, "IEC61937_ATRAC2/3"],
    [12, "TYPE_III_WMA"]
];
#A.2.4 Audio Data Format Type IV Bit Allocations
set AudioDataFormatTypeIV_v2_Bitmap = 
[
    [ 0, "PCM"],
    [ 1, "PCM8"],
    [ 2, "IEEE_FLOAT"],
    [ 3, "ALAW"],
    [ 4, "MULAW"],
    [ 5, "MPEG"],
    [ 6, "AC-3"],
    [ 7, "WMA"],
    [ 8, "IEC61937_AC-3"],
    [ 9, "IEC61937_MPEG-1_Layer1"],
    [10, "IEC61937_MPEG-1_Layer2/3 or IEC61937__MPEG-2_NOEXT"],
    [11, "IEC61937_MPEG-2_EXT"],
    [12, "IEC61937_MPEG-2_AAC_ADTS"],
    [13, "IEC61937_MPEG-2_Layer1_LS"],
    [14, "IEC61937_MPEG-2_Layer2/3_LS"],
    [15, "IEC61937_DTS-I"],
    [16, "IEC61937_DTS-II"],
    [17, "IEC61937_DTS-III"],
    [18, "IEC61937_ATRAC"],
    [19, "IEC61937_ATRAC2/3"],
    [20, "TYPE_III_WMA"],
    [21, "IEC60958_PCM"]
];

#A.1 Format Type Codes
set AudioDataFormatType_v2_Table = 
[
    [ 0xFF, "Illegal", null, null],
    [ 0x00, "FORMAT_TYPE_UNDEFINED", null, null],
    [ 0x01, "FORMAT_TYPE_I", AudioDataFormatTypeI_v2_Bitmap,"FORMAT_TYPE_I_v2_sub" ],
    [ 0x02, "FORMAT_TYPE_II", AudioDataFormatTypeII_v2_Bitmap, "FORMAT_TYPE_II_v2_sub"],
    [ 0x03, "FORMAT_TYPE_III", AudioDataFormatTypeIII_v2_Bitmap, "FORMAT_TYPE_III_v2_sub"],
    [ 0x04, "FORMAT_TYPE_IV", AudioDataFormatTypeIV_v2_Bitmap, "FORMAT_TYPE_IV_v2_sub"],
    [ 0x81, "EXT_FORMAT_TYPE_I", null,"EXT_FORMAT_TYPE_I_v2_sub" ],
    [ 0x82, "EXT_FORMAT_TYPE_II", null, "EXT_FORMAT_TYPE_II_v2_sub"],
    [ 0x83, "EXT_FORMAT_TYPE_III", null, "EXT_FORMAT_TYPE_III_v2_sub"]
];

#A.3 Side Band Protocol Codes
set AudioSideBandProtocolCodes_v2_Table = 
[
		[0xFF, "Illegal"],
		[0x00, "PROTOCOL_UNDEFINED"],
		[0x01, "PRES_TIMESTAMP_PROTOCOL"]
];

#***************************************************************************************************
#Universal Serial Bus Device Class Definition for Audio Data Formats Release 3.0
#***************************************************************************************************
#A.2 Audio Data Formats Bit Allocations in the bmFormats Field and Usage
set AudioDataFormatType_Bitmap = 
[
    [0, "PCM"],
    [1, "PCM8"],
    [2, "IEEE_FLOAT"],
    [3, "ALAW"],
    [4, "MULAW"],
    [5, "DSD"],
    [6, "RAW_DATA"],
    [7,  "PCM_IEC60958"],
    [8,  "AC-3"],
    [9,  "MPEG-1_Layer1"],
    [10, "MPEG-1_Layer2/3 or MPEG-2_NOEXT"],
    [11, "MPEG-2_EXT"],
    [12, "MPEG-2_AAC_ADTS"],
    [13, "MPEG-2_Layer1_LS"],
    [14, "MPEG-2_Layer2/3_LS"],
    [15, "DTS-I"],
    [16, "DTS-II"],
    [17, "DTS-III"],
    [18, "ATRAC"],
    [19, "ATRAC2/3"],
    [20, "WMA"],
    [21, "E-AC-3"],
    [22, "MAT"],
    [23, "DTS-IV"],
    [24, "MPEG-4_HE_AAC"],
    [25, "MPEG-4_HE_AAC_V2"],
    [26, "MPEG-4_AAC_LC"],
    [27, "DRA"],
    [28, "MPEG-4_HE_AAC_SURROUND"],
    [29, "MPEG-4_AAC_LC_SURROUND"],
    [30, "MPEG-H_3D_AUDIO"],
    [31, "AC4"],
    [32, "MPEG-4_AAC_ELD"]
];


#***************************************************************************************************
#Universal Serial Bus Device Class Definition for MIDI Devices Release 1.0
#***************************************************************************************************
#A.2 MS Class-Specific Endpoint Descriptor Subtypes
set AudioMSEndPointDescriptorSubTypeTable =
[
		[0xFF, "Illegal", null],
		[0x00, "DESCRIPTOR_UNDEFINED", null],
		[0x01, "MS_GENERAL", "MS_GENERAL_v1_sub"]
];

#A.1 MS Class-Specific Interface Descriptor Subtypes
set AudioMSInterfaceDescriptorTypeTable = 
[
		[ 0xFF, "Illegal", null],
		[ 0x00, "MS_DESCRIPTOR_UNDEFINED", null],
		[ 0x01, "MS_HEADER", "MS_HEADER_sub"],
		[ 0x02, "MIDI_IN_JACK", "MIDI_IN_JACK_sub"],
		[ 0x03, "MIDI_OUT_JACK", "MIDI_OUT_JACK_sub"],
		[ 0x04, "ELEMENT", "ELEMENT_sub"]
];

#A.3 MS MIDI IN and OUT Jack types
set AudioMSMIDIJackTypeTable = 
[
		[ 0xFF, "Illegal"],
		[ 0x00, "JACK_TYPE_UNDEFINED"],
		[ 0x01, "EMBEDDED"],
		[ 0x02, "EXTERNAL"]
];

#A.5 Control Selector Codes
#A.5.1 Endpoint Control Selectors
set AudioMIDIEndpointControlSelectorsTable = 
[
	[0xFF, "Illegal"],
	[0x00, "EP_CONTROL_UNDEFINED"],
	[0x01, "ASSOCIATION_CONTROL"]
];


#***************************************************************************************************
#Universal Serial Bus Device Class Definition for Audio Devices Release 1.0 2.0 3.0 commom
#***************************************************************************************************

set SUBTYPE_UNDEFINED = 0x00;

#AUDIO CLASS-SPECIFIC DESCRIPTOR TYPES
set AudioDescriptorTypeTable = 
[
    [IP_VERSION_01_00, AudioDescriptorType_v1_Table],
    [IP_VERSION_02_00, AudioDescriptorType_v2_Table],
    [IP_VERSION_03_00, AudioDescriptorType_v3_Table]
];

#A.2 Audio Interface Subclass Codes
set AudioInterfaceSubclassCodesTable = 
[
    [0x00, "SUBCLASS_UNDEFINED", null, null, null],
    [0x01, "AUDIOCONTROL", ACDescriptorSubType_v1_Table, ACDescriptorSubType_v2_Table, ACDescriptorSubType_v3_Table],
    [0x02, "AUDIOSTREAMING", ASDescriptorSubType_v1_Table, ASDescriptorSubType_v2_Table, ASDescriptorSubType_v3_Table],
    [0x03, "MIDISTREAMING", AudioMSInterfaceDescriptorTypeTable, AudioMSInterfaceDescriptorTypeTable, AudioMSInterfaceDescriptorTypeTable]
];

#AudioFunctionCategoryCodesTable names for Audio 1.0/2.0/3.0 
set AudioFunctionCategoryCodesTable = 
[
	#Audio 1.0: The Function Category not supported
    [IP_VERSION_01_00, null],
	
	#Audio 2.0
    [IP_VERSION_02_00, AudioFunctionCategoryCodes_v2_Table],
	
	#Audio 3.0
    [IP_VERSION_03_00, AudioFunctionCategoryCodes_v3_Table]
];

#A.8 Audio Class-Specific Endpoint Descriptor Subtypes
#Table A-8: Audio Class-Specific Endpoint Descriptor Subtypes
set AudioEPDescriptorSubTypeTable =
[
    [0xFF, "Illegal", null, null],
    [0x00, "DESCRIPTOR_UNDEFINED", null, null],
    [0x01, "AUDIO_EP_GENERAL", "AUDIO_EP_GENERAL_v1_sub", "AUDIO_EP_GENERAL_v2_sub"]
];

#************************************************************************************
#Universal Serial Bus Device Class Definition for Terminal Types 1.0, 2.0 and 3.0
#************************************************************************************
set USBTerminalTypesTable =
[
    #--------------------------------------------------------------------------------
    # Code				Terminal Type							I/O						Description
    #---------------------------------------------------------------------------------
    [0xFFFF, null							, null , null													 	],
    [0x0100, "USB Undefined"	, "I/O", "USB Terminal, undefined Type."	],
    [0x0101, "USB streaming"	, "I/O", "A Terminal dealing with a signal carried over an endpoint in an AudioStreaming interface. The AudioStreaming interface descriptor points to the associated Terminal through the bTerminalLink field."],
    [0x01FF, "USB vendor specific", "I/O", "A Terminal dealing with a signal carried over a vendor-specific interface. The vendor-specific interface descriptor must contain a field that references the Terminal."],
    [0x0200, "Input Undefined", "I", "Input Terminal, undefined Type."],
    [0x0201, "Microphone", "I", "A generic microphone that does not fit under any of the other classifications."],
    [0x0202, "Desktop microphone", "I", "A microphone normally placed on the desktop or integrated into the monitor."],
    [0x0203, "Personal microphone", "I", "A head-mounted or clip-on microphone."],
    [0x0204, "Omni-directional microphone", "I", "A microphone designed to pick up voice from more than one speaker at relatively long ranges."],
    [0x0205, "Microphone array", "I", "An array of microphones designed for directional processing using host-based signal processing algorithms."],
    [0x0206, "Processing microphone array", "I", "An array of microphones with an embedded signal processor."],
    [0x0300, "Output Undefined", "O", "Output Terminal, undefined Type."],
    [0x0301, "Speaker", "O", "A generic speaker or set of speakers that does not fit under any of the other classifications."],
    [0x0302, "Headphones", "O", "A head-mounted audio output device."],
    [0x0303, "Head Mounted Display Audio", "O", "The audio part of a VR head mounted display. The Associated Interfaces descriptor can be used to reference the HID interface used to report the position and orientation of the HMD."],
    [0x0304, "Desktop speaker", "O", "Relatively small speaker or set of speakers normally placed on the desktop or integrated into the monitor. These speakers are close to the user and have limited stereo separation."],
    [0x0305, "Room speaker", "O", "Larger speaker or set of speakers that are heard well anywhere in the room."],
    [0x0306, "Communication speaker", "O", "Speaker or set of speakers designed for voice communication."],
    [0x0307, "Low frequency effects speaker", "O", "Speaker designed for low frequencies (subwoofer). Not capable of reproducing speech or music."],
    [0x0400, "Bi-directional Undefined", "I/O", "Bi-directional Terminal, undefined Type."],
    [0x0401, "Handset", "I/O", "Hand-held bi-directional audio device."],
    [0x0402, "Headset", "I/O", "Head-mounted bi-directional audio device."],
    [0x0403, "Speakerphone, no echo reduction", "I/O", "A hands-free audio device designed for host-based echo cancellation."],
    [0x0404, "Echo-suppressing speakerphone", "I/O", "A hands-free audio device with echo suppression capable of half-duplex operation."],
    [0x0405, "Echo-canceling speakerphone", "I/O", "A hands-free audio device with echo cancellation capable of full-duplex operation."],
    [0x0500, "Telephony Undefined", "I/O", "Telephony Terminal, undefined Type."],
    [0x0501, "Phone line", "I/O", "May be an analog telephone line jack, an ISDN line, a proprietary PBX interface, or a wireless link."],
    [0x0502, "Telephone", "I/O", "Device can be used as a telephone. When not in use as a telephone, handset is used as a bi-directional audio device."],
    [0x0503, "Down Line Phone", "I/O", "A standard telephone set connected to the device. When not in use as a telephone, it can be used as a bidirectional audio device."],
    [0x0600, "External Undefined", "I/O", "External Terminal, undefined Type."],
    [0x0601, "Analog connector", "I/O", "A generic analog connector."],
    [0x0602, "Digital audio interface", "I/O", "A generic digital audio interface."],
    [0x0603, "Line connector", "I/O", "An analog connector at standard line levels. Usually uses 3.5mm."],
    [0x0604, "Legacy audio connector", "I/O", "An input connector assumed to be connected to the lineout of the legacy audio system of the host computer. Used for backward compatibility."],
    [0x0605, "S/PDIF interface", "I/O", "An S/PDIF digital audio interface. The Associated Interface descriptor can be used to reference an interface used for controlling special functions of this interface."],
    [0x0606, "1394 DA stream", "I/O", "An interface to audio streams on a 1394 bus."],
    [0x0607, "1394 DV stream soundtrack", "I/O", "An interface to soundtrack of A/V stream on a 1394 bus."],
    [0x0608, "ADAT Lightpipe", "I/O", "AN optical connection carrying the Alesis Digital Audio Tape stream. Contract Alesis for technical information."],
    [0x0609, "TDIF", "I/O", "Tascam Digital Interface. Contact Tascam for technical information"],
    [0x060A, "MADI", "I/O", "Multi-channel Audio Digital Interface as defined by AES."],
    [0x0700, "Embedded Undefined", "I/O", "Embedded Terminal, undefined Type."],
    [0x0701, "Level Calibration Noise Source", "O", "Internal Noise source for level calibration (MPEG decoding, Dolby Prologic‘, AC-3 etc.)"],
    [0x0702, "Equalization Noise", "O", "Internal Noise source for measurements."],
    [0x0703, "CD player", "I", "Audio compact disc player or CD-ROM capable of audio playback."],
    [0x0704, "DAT", "I/O", "Digital Audio Tape."],
    [0x0705, "DCC", "I/O", "Digital Compact Cassette."],
    [0x0706, "Compressed Audio Player", "I/O", "Compressed Audio Player"],
    [0x0707, "Analog Tape", "I/O", "Analog Audio Tape."],
    [0x0708, "Phonograph", "I", "Analog vinyl record player."],
    [0x0709, "VCR Audio", "I", "Audio track of VCR."],
    [0x070A, "Video Disc Audio", "I", "Audio track of VideoDisc player."],
    [0x070B, "DVD Audio", "I", "Audio track of DVD player."],
    [0x070C, "TV Tuner Audio", "I", "Audio track of TV tuner."],
    [0x070D, "Satellite Receiver Audio", "I", "Audio track of satellite receiver."],
    [0x070E, "Cable Tuner Audio", "I", "Audio track of cable tuner."],
    [0x070F, "DSS Audio", "I", "Audio track of DSS receiver."],
    [0x0710, "Radio Receiver", "I", "AM/FM radio receiver."],
    [0x0711, "Radio Transmitter", "O", "AM/FM radio transmitter."],
    [0x0712, "Multi-track Recorder", "I/O", "A multi-track recording system."],
    [0x0713, "Synthesizer", "I/O", "Synthesizer."],
    [0x0714, "Piano", "I/O", "Piano"],
    [0x0715, "Guitar", "I/O", "Guitar"],
    [0x0716, "Drums/Rhythm", "I/O", "Percussion Instrument"],
    [0x0717, "Other Musical Instrument", "I/O", "Undefined Musical Instrument"]
];

###############################################################################################
#  Other helper tables and bitmaps for 1.0
###############################################################################################
set AudioInputTerminalChannel_v1_Config = 
[
    [0, "Left Front"],
    [1, "Right Front"],
    [2, "Center Front"],
    [3, "Low Freq Enh"],
    [4, "Left Surround"],
    [5, "Right Surround"],
    [6, "Left of Center"],
    [7, "Right of Center"],
    [8, "Surround"],
    [9, "Side Left"],
    [10, "Side Right"],
    [11, "Top"]
];

set AudioFeatureUnitControls_v1_Bitmap = 
[
	[0, "Mute"],
	[1, "Volume"],
	[2, "Bass"],
	[3, "Mid"],
	[4, "Treble"],
	[5, "Graphic Equalizer"],
	[6, "Automatic Gain"],
	[7, "Delay"],
	[8, "Bass Boost"],
	[9, "Loudness"]
];

set AudioEPGeneralAttributes_v1_Bitmap = 
[
	[0, "Sampling Frequency"],
	[1, "Pitch"],
	[7, "MaxPacketsOnly"]
];

set AudioMPEGCapabilities_v1_Bitmap = 
[
    [ 0, "Layer support"],
    [ 1, "Layer support"],
    [ 2, "Layer support"],
    [ 3, "MPEG-1 only"],
    [ 4, "MPEG-1 dual-channel"],
    [ 5, "MPEG-2 second stereo"],
    [ 6, "MPEG-2 7.1 channel augmentation"],
    [ 7, "Adaptive multi-channel prediction"],
    [ 8, "MPEG-2 multilingual support"],
    [ 9, "MPEG-2 multilingual support"]
];


set AudioAC3Features_v1_Bitmap =
[
    [0, "RF mode"],
    [1, "Line mode"],
    [2, "Custom0 mode"],
    [3, "Custom1 mode"],
    [4, "Internal Dynamic Range Control:"],
    [5, "Internal Dynamic Range Control:"]
];

set AudioELEMENTCapsBitmap = 
[
	[0, "Custom Undefined Type"],
	[1, "MIDI CLOCK"],
	[2, "MTC"],
	[3, "MMC"],
	[4, "GM1"],
	[5, "GM2"],
	[6, "GS"],
	[7, "XG"],
	[8, "EFX"],
	[9, "MIDI Patch Bay"],
	[10, "DLS1"],
	[11, "DLS2"]
];

###############################################################################################
#  Other helper tables and bitmaps for 2.0
###############################################################################################
set AudioClockSourceClockTypeTable = 
[
    [ 0, "D1..0: 00: External Clock"],
    [ 1, "D1..0: 01: Internal Fixed Clock"],
    [ 2, "D1..0: 10: Internal Variable Clock"],
    [ 3, "D1..0: 11: Internal Programmable Clock"]
]; 

set AudioChannelConfigBitmap = 
[
    [ 0, "Front Left - FL"],
    [ 1, "Front Right - FR"],
    [ 2, "Front Center - FC"],
    [ 3, "Low Frequency Effects - LFE"],
    [ 4, "Back Left - BL"],
    [ 5, "Back Right - BR"],
    [ 6, "Front Left of Center - FLC"],
    [ 7, "FRONT RIght of Center - FRC"],
    [ 8, "Back Center - BC"],
    [ 9, "Side Left - SL"],
    [ 10, "Side Right - SR"],
    [ 11, "Top Center - TC"],
    [ 12, "Top Front Left - TFL"],
    [ 13, "Top Front Center - TFC"],
    [ 14, "Top Front Right - TFR"],
    [ 15, "Top Back Left - TBL"],
    [ 16, "Top Back Center - TBC"],
    [ 17, "Top Back Right - TBR"],
    [ 18, "Top Front Left of Center - TFLC"],
    [ 19, "Top Front Right of Center - TFRC"],
    [ 20, "Left Low Frequency Effects - LLFE"],
    [ 21, "Right Low Frequency Effects - RLFE"],
    [ 22, "Top Side Left - TSL"],
    [ 23, "Top Side Right - TSR"],
    [ 24, "Bottom Center - BC"],
    [ 25, "Back Left of Center - BLC"],
    [ 26, "Back Right of Center - BRC"],
    [ 31, "Raw Data - RD; Mutually exclusive with all other spatial locations"]
];

set AudioGeneralControlStatusTable = 
[
    [ 0, " is not present"],
    [ 1, " is present but read-only"],
    [ 2, " is set to Illegal value! 0b10 is not allowed"],
    [ 3, " is present and Host programmable"]
];

set AudioMPEGCapabilitiesBitmap =
[
    [ 0, "Layer I"],
    [ 1, "Layer II"],
    [ 2, "Layer III"],
    [ 3, "MPEG-1 only"],
    [ 4, "MPEG-1 dual-channel"],
    [ 5, "MPEG-2 second stereo"],
    [ 6, "MPEG-2 7.1 channel augmentation"],
    [ 7, "Adaptive multi-channel prediction"],
    [10, "Support for 1/2 Fs"]
];

set AudioMPEGCapabilitiesBit8And9Table =
[
    [ 0b00, "Not supported"],
    [ 0b01, "Supported at Fs"],
    [ 0b10, "Reserved"],
    [ 0b11, "Supported at Fs and 1/2 Fs"]
];

set AudioDecoderGeneralFeaturesBit4And5Table = 
[
    [ 0b00, "Not Supported"],
    [ 0b01, "Supported but not scalable"],
    [ 0b10, "Scalable, common boost and cut scaling value."],
    [ 0b11, "scalable, separate boost and cut scaling value."]
];

set AudioAC3FeaturesBitmap = 
[
    [ 0, "RF mode"],
    [ 1, "Line mode"],
    [ 2, "Custom0 mode"],
    [ 3, "Custom1 mode"]
];

set AudioWMAProfileBitmap = 
[
    [ 0, "WMA Profile1, L1"],
    [ 1, "WMA Profile2, L2"],
    [ 2, "WMA Profile3, L3"],
    [ 3, "WMA Profile Other, L"],
    [ 4, "WMA Speech 1, S1"],
    [ 5, "WMA Speech 2, S2"],
    [ 6, "WMAPro Profile 1, M1"],
    [ 7, "WMAPro Profile 2, M2"],
    [ 8, "WMAPro Profile 3, M3"],
    [ 9, "WMAPro Profile Other, M"],
    [ 10, "WMA lossless decoding is supported"]
];

set AudioDTSCapabilitiesBitmap = 
[
    [ 0, "Core"],
    [ 1, "Lossless"],
    [ 2, "LBR"],
    [ 3, "MultipleStreamMixing"],
    [ 4, "DualDecode"]
];

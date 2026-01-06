#
#  Copyright (c) 2002- 2006, LeCroy Corp. PSG  - All Rights Reserved
#
# PTPStillImageTables.inc
#
# This file contains many of the tables that are used in all the .inc files and .dec files


set PTPResponseCodeTable = null;
set PTPBulkTable = null;

set PTPOperationCodeTable = 
[
    [   0xFFFF, "Reserved"                    , null],
    [   0x1000, "Undefined"                   , null],
    [   0x1001, "GetDeviceInfo"               , "DeviceInfoDataset"],
    [   0x1002, "OpenSession"                 , null],
    [   0x1003, "CloseSession"                , null],
    [   0x1004, "GetStorageIDs"               , "StorageIDArray"],
    [   0x1005, "GetStorageInfo"              , "StorageInfo"],
    [   0x1006, "GetNumObjects"               , null],
    [   0x1007, "GetObjectHandles"            , "ObjectHandleArray"],
    [   0x1008, "GetObjectInfo"               , "ObjectInfoDataset"],
    [   0x1009, "GetObject"                   , "DataObject"],
    [   0x100A, "GetThumb"                    , "ThumbnailObject"],
    [   0x100B, "DeleteObject"                , null],
    [   0x100C, "SendObjectInfo"              , "ObjectInfoDataset"],
    [   0x100D, "SendObject"                  , "DataObject"],
    [   0x100E, "InitiateCapture"             , null],
    [   0x100F, "FormatStore"                 , null], 
    [   0x1010, "ResetDevice"                 , null],
    [   0x1011, "SelfTest"                    , null],
    [   0x1012, "SetObjectProtection"         , null],
    [   0x1013, "PowerDown"                   , null],
    [   0x1014, "GetDevicePropDesc"           , "DevicePropDescDataset"],
    [   0x1015, "GetDevicePropValue"          , null],
    [   0x1016, "SetDevicePropValue"          , null],
    [   0x1017, "ResetDevicePropValue"        , null],
    [   0x1018, "TerminateOpenCapture"        , null],
    [   0x1019, "MoveObject"                  , null],
    [   0x101A, "CopyObject"                  , null],
    [   0x101B, "GetPartialObject"            , "DataObject"],
    [   0x101C, "InitiateOpenCapture"         , null],
    [   0x9800, "MTP Operation Code Undefined", null],
    [   0x9801, "GetObjectPropsSupported"     , "ObjectPropCodeArray"],
    [   0x9802, "GetObjectPropDesc"           , "ObjectPropDescDataset"],
    [   0x9803, "GetObjectPropValue"          , "ObjectPropValue" ],
    [   0x9804, "SetObjectPropValue"          , "ObjectPropValue" ],
    [   0x9805, "GetObjectPropList"           , "ObjectPropValueList"],
    [   0x9806, "SetObjectPropList"           , "ObjectPropValueList"],
    [   0x9807, "GetInterdependentPropDesc"   , "InterdependentPropDesc"],
    [   0x9808, "SendObjectPropList"          , "ObjectPropValueList"],
    [   0x9810, "GetObjectReferences"         , "ObjectHandleArray" ],
    [   0x9811, "SetObjectReferences"         , "ObjectHandleArray" ]
];


set PTPEventCodeTable = 
[
    [   0xFFFF, "Reserved"],
    [   0x4000, "Undefined" ],
    [   0x4001, "CancelTransaction" ],
    [   0x4002, "ObjectAdded" ], 
    [   0x4003, "ObjectRemoved" ],
    [   0x4004, "StoreAdded" ], 
    [   0x4005, "StoreRemoved" ], 
    [   0x4006, "DevicePropChanged" ],
    [   0x4007, "ObjectInfoChanged" ],
    [   0x4008, "DeviceInfoChanged" ], 
    [   0x4009, "RequestObjectTransfer" ], 
    [   0x400A, "StoreFull" ], 
    [   0x400B, "DeviceReset" ], 
    [   0x400C, "StorageInfoChanged" ], 
    [   0x400D, "CaptureComplete" ], 
    [   0x400E, "Unreported Status" ],
    [   0xB800, "MTP Event Code undefined"],
    [   0xB801, "ObjectPropChanged" ],
    [   0xB802, "ObjectPropDescChanged" ],
    [   0xB803, "ObjectReferencesChanged" ],
    [   0xB804, "DevicePropDescChanged" ]
];


set PTPStorageTypesTable = 
[
    [ 0xFFFF, "Reserved"],
    [ 0x0000, "Undefined" ], 
    [ 0x0001, "Fixed ROM" ], 
    [ 0x0002, "Removable ROM" ], 
    [ 0x0003, "Fixed RAM" ], 
    [ 0x0004, "Removable RAM" ]
];


set PTPFilesystemTypeTable = 
[
    [ 0xFFFF, "Reserved"],
    [ 0x0000, "Undefined" ], 
    [ 0x0001, "Generic Flat" ], 
    [ 0x0002, "Generic Hierarchical" ], 
    [ 0x0003, "DCF" ]
];


set PTPStorageInfoAccessCapabilityTable = 
[
    [ 0xFFFF, "Reserved"],
    [ 0x0000, "Read-Write" ], 
    [ 0x0001, "Read-Only without Object Deletion" ], 
    [ 0x0002, "Read-Only with Object Deletion" ]
];


set PTPProtectionStatusTable = 
[
    [ 0xFFFF, "Reserved"],
    [ 0x0000, "No Protection" ], 
    [ 0x0001, "Read-Only" ],
    [ 0x8002, "Read-only data"],
    [ 0x8003, "Non-transferrable data"]
];



set PTPObjectFormatCodesTable = 
[
    [ 0xFFFF, "Reserved"],
    [ 0x3000, "Undefined" ],
    [ 0x3001, "Association" ],
    [ 0x3002, "Script" ],
    [ 0x3003, "Executable" ],
    [ 0x3004, "Text" ],
    [ 0x3005, "HTML" ],
    [ 0x3006, "DPOF" ],
    [ 0x3007, "AIFF" ],
    [ 0x3008, "WAV" ],
    [ 0x3009, "MP3" ],
    [ 0x300A, "AVI" ],
    [ 0x300B, "MPEG" ],
    [ 0x300C, "ASF" ],
    [ 0x300D, "QuickTime" ],
    [ 0x300E, "XML" ],
    [ 0x3800, "Undefined" ],
    [ 0x3801, "EXIF/JPEG" ],
    [ 0x3802, "TIFF/EP" ],
    [ 0x3803, "FlashPix" ],
    [ 0x3804, "BMP" ],
    [ 0x3805, "CIFF" ],
    [ 0x3806, "Undefined" ], 
    [ 0x3807, "GIF" ], 
    [ 0x3808, "JFIF" ], 
    [ 0x3809, "PCD" ], 
    [ 0x380A, "PICT" ], 
    [ 0x380B, "PNG" ], 
    [ 0x380C, "Undefined" ], 
    [ 0x380D, "TIFF" ], 
    [ 0x380E, "TIFF/IT" ], 
    [ 0x380F, "JP2" ], 
    [ 0x3810, "JPX" ],
    [ 0xB802, "Undefined Firmware"],
    [ 0xB881, "Windows Image Format"],
    [ 0xB900, "Undefined Audio"],
    [ 0xB901, "WMA"],
    [ 0xB902, "OGG"],
    [ 0xB903, "AAC"],
    [ 0xB904, "Audible"],
    [ 0xB906, "FLAC"],
    [ 0xB980, "Undefined Video"],
    [ 0xB981, "WMV"],
    [ 0xB982, "MP4 Container"],
    [ 0xB983, "MP2"],
    [ 0xB984, "3GP Container"],
    [ 0xBA00, "Undefined Collection"],
    [ 0xBA01, "Abstract Multimedia Album"],
    [ 0xBA02, "Abstract Image Album"],
    [ 0xBA03, "Abstract Audio Album"],
    [ 0xBA04, "Abstract Video Album"],
    [ 0xBA05, "Abstract Audio & Video Playlist"],
    [ 0xBA06, "Abstract Contact Group"],
    [ 0xBA07, "Abstract Message Folder"],
    [ 0xBA08, "Abstract Chaptered Production"],
    [ 0xBA09, "Abstract Audio Playlist"],
    [ 0xBA0A, "Abstract Video Playlist"],
    [ 0xBA0B, "Abstract Mediacast"],
    [ 0xBA10, "WPL Playlist"],
    [ 0xBA11, "M3U Playlist"],
    [ 0xBA12, "MPL Playlist"],
    [ 0xBA13, "ASX Playlist"],
    [ 0xBA14, "PLS Playlist"],
    [ 0xBA80, "Undefined Document"],
    [ 0xBA81, "Abstract Document"],
    [ 0xBA82, "XML Document"],
    [ 0xBA83, "Microsoft Word Document"],
    [ 0xBA84, "MHT Compiled HTML Document"],
    [ 0xBA85, "Microsoft Excel spreadsheet (.xls)"],
    [ 0xBA86, "Microsoft Powerpoint presentation (.ppt)"],
    [ 0xBB00, "Undefined Message"],
    [ 0xBB01, "Abstract Message"],
    [ 0xBB80, "Undefined Contact"],
    [ 0xBB81, "Abstract Contact"],
    [ 0xBB82, "vCard 2"],
    [ 0xBB83, "vCard 3"],
    [ 0xBE00, "Undefined Calender Item"],
    [ 0xBE01, "Abstract Calender Item"],
    [ 0xBE02, "vCalendar 1"],
    [ 0xBE03, "vCalendar 2"],
    [ 0xBE80, "Undefined Windows Executable"]
]; 


set AssociationTypesTable = 
[
    [ 0xFFFF, "Reserved", "Unused"],
    [ 0x0000, "Undefined", "Undefined" ], 
    [ 0x0001, "GenericFolder", "Used by MTP" ], 
    [ 0x0002, "Album", "Reserved" ], 
    [ 0x0003, "TimeSequence", "DefaultPlaybackDelta" ], 
    [ 0x0004, "HorizontalPanoramic", "Unused" ], 
    [ 0x0005, "VerticalPanoramic", "Unused" ], 
    [ 0x0006, "2DPanoramic", "ImagesPerRow" ], 
    [ 0x0007, "AncillaryData", "Undefined" ]
];



set DatatypeCodesTable =
[
    #---------------------------------------------------
    # code  , description, type(NUM,ARRAY,STR), bytes, (1 - SIGNED,0 - UNSIGNED)
    [ 0x0000, "UNDEF"    , null               , null , null ], 
    [ 0x0001, "INT8"     , "NUM"              , 1    , 1], 
    [ 0x0002, "UINT8"    , "NUM"              , 1    , 0 ], 
    [ 0x0003, "INT16"    , "NUM"              , 2    , 1 ], 
    [ 0x0004, "UINT16"   , "NUM"              , 2    , 0], 
    [ 0x0005, "INT32"    , "NUM"              , 4    , 1], 
    [ 0x0006, "UINT32"   , "NUM"              , 4    , 0 ], 
    [ 0x0007, "INT64"    , "NUM"              , 8    , 1 ], 
    [ 0x0008, "UINT64"   , "NUM"              , 8    , 0 ], 
    [ 0x0009, "INT128"   , "NUM"              , 16   , 1 ], 
    [ 0x000A, "UINT128"  , "NUM"              , 16   , 0 ], 
    [ 0x4001, "AINT8"    , "ARRAY"            , 1    , 1 ], 
    [ 0x4002, "AUINT8"   , "ARRAY"            , 1    , 0], 
    [ 0x4003, "AINT16"   , "ARRAY"            , 2    , 1 ], 
    [ 0x4004, "AUINT16"  , "ARRAY"            , 2    , 0 ], 
    [ 0x4005, "AINT32"   , "ARRAY"            , 4    , 1 ], 
    [ 0x4006, "AUINT32"  , "ARRAY"            , 4    , 0], 
    [ 0x4007, "AINT64"   , "ARRAY"            , 8    , 1 ], 
    [ 0x4008, "AUINT64"  , "ARRAY"            , 8    , 0 ], 
    [ 0x4009, "AINT128"  , "ARRAY"            , 16   , 1], 
    [ 0x400A, "AUINT128" , "ARRAY"            , 16   , 0], 
    [ 0xFFFF, "STR"      , "STR"              , null , null]
];

set WhiteBalanceSettingsTable = 
[
    [ 0xFFFF, "Reserved" ],
    [ 0x0000, "Undefined" ],
    [ 0x0001, "Manual" ], 
    [ 0x0002, "Automatic" ], 
    [ 0x0003, "One-push Automatic" ],
    [ 0x0004, "Daylight" ], 
    [ 0x0005, "Florescent" ],
    [ 0x0006, "Tungsten" ],
    [ 0x0007, "Flash" ]
];

set FocusModeSettingsTable = 
[
    [ 0xFFFF, "Reserved" ],
    [ 0x0000, "Undefined" ],
    [ 0x0001, "Manual" ],
    [ 0x0002, "Automatic" ],
    [ 0x0003, "Automatic Macro(close-up)" ]
];

set ExposureMeteringModeSettingsTable = 
[
    [ 0xFFFF, "Reserved" ],
    [ 0x0000, "Undefined" ],
    [ 0x0001, "Average" ],
    [ 0x0002, "Center-weighted average" ],
    [ 0x0003, "Multi-spot" ], 
    [ 0x0004, "Center-spot" ]
];

set FlashModeSettingsTable = 
[
    [ 0xFFFF, "Reserved" ],
    [ 0x0000, "Undefined" ],
    [ 0x0001, "Auto flash" ],
    [ 0x0002, "Flash off" ], 
    [ 0x0003, "Fill flash" ],
    [ 0x0004, "Red eye auto" ], 
    [ 0x0005, "Red eye fill" ],
    [ 0x0006, "External Sync" ]
];

set ExposureProgramModeSettingsTable = 
[
    [ 0xFFFF, "Reserved" ],
    [ 0x0000, "Undefined" ],
    [ 0x0001, "Manual" ],
    [ 0x0002, "Automatic" ],
    [ 0x0003, "Aperture Priority" ],
    [ 0x0004, "Shutter Priority" ],
    [ 0x0005, "Program Creative(greater depth of field)" ],
    [ 0x0006, "Program Action(faster shutter speed)" ],
    [ 0x0007, "Portrait" ]
];

set StillCaptureModeSettingsTable = 
[
    [ 0xFFFF, "Reserved" ],
    [ 0x0000, "Undefined" ],
    [ 0x0001, "Normal" ],
    [ 0x0002, "Burst" ],
    [ 0x0003, "Timelapse" ]
];

set EffectModeSettingsTable = 
[
    [ 0xFFFF, "Reserved" ], 
    [ 0x0000, "Undefined" ],
    [ 0x0001, "Standard(color)" ],
    [ 0x0002, "Black & White" ], 
    [ 0x0003, "Sepia" ]
];

set FocusMeteringModeSettingsTable = 
[
    [ 0xFFFF, "Reserved" ],
    [ 0x0000, "Undefined" ],
    [ 0x0001, "Center-spot" ],
    [ 0x0002, "Multi-spot" ]
];

set SupportedFormatsOrderedSettingsTable = 
[
    [ 0xFFFF, "Reserved" ],
    [ 0x0000, "Unordered" ],
    [ 0x0001, "Ordered" ]    
];

set PerceivedDeviceTypeSettingsTable = 
[
    [ 0xFFFF, "Reserved" ],
    [ 0x0000, "Generic" ],
    [ 0x0001, "Still Image/Video Camera" ],
    [ 0x0002, "Media (Audio/Video) Player" ],
    [ 0x0003, "Mobile Handset" ],
    [ 0x0004, "Digital Video Camera" ],
    [ 0x0005, "Personal Information Manager" ],
    [ 0x0006, "Audio Recorder" ]
    
];
 
set PTPDevicePropCodesTable = 
[
    [ 0xFFFF, "Reserved", null],
    [ 0x5000, "Undefined", null ],
    [ 0x5001, "BatteryLevel", null ], 
    [ 0x5002, "FunctionalMode", null ], 
    [ 0x5003, "ImageSize", null ], 
    [ 0x5004, "CompressionSetting", null ], 
    [ 0x5005, "WhiteBalance", WhiteBalanceSettingsTable ], 
    [ 0x5006, "RGBGain", null ], 
    [ 0x5007, "F_Number", null ], 
    [ 0x5008, "FocalLength", null ], 
    [ 0x5009, "FocusDistance", null ], 
    [ 0x500A, "FocusMode", FocusModeSettingsTable ], 
    [ 0x500B, "ExposureMeteringMode", ExposureMeteringModeSettingsTable ], 
    [ 0x500C, "FlashMode", FlashModeSettingsTable ], 
    [ 0x500D, "ExposureTime", null ], 
    [ 0x500E, "ExposureProgramMode", ExposureProgramModeSettingsTable ],
    [ 0x500F, "ExposureIndex", null ],
    [ 0x5010, "ExposureBiasCompensation", null ],
    [ 0x5011, "DateTime", null ],
    [ 0x5012, "CaptureDelay", null ],
    [ 0x5013, "StillCaptureMode", StillCaptureModeSettingsTable ],
    [ 0x5014, "Contrast", null ],
    [ 0x5015, "Sharpness", null ],
    [ 0x5016, "DigitalZoom", null ],
    [ 0x5017, "EffectMode", EffectModeSettingsTable ],
    [ 0x5018, "BurstNumber", null ], 
    [ 0x5019, "BurstInterval", null ], 
    [ 0x501A, "TimelapseNumber", null ], 
    [ 0x501B, "TimelapseInterval", null ], 
    [ 0x501C, "FocusMeteringMode", FocusMeteringModeSettingsTable ], 
    [ 0x501D, "UploadURL", null ], 
    [ 0x501E, "Artist", null ], 
    [ 0x501F, "CopyrightInfo", null ],
    [ 0xD401, "Synchronization Partner", null],
    [ 0xD402, "Device Friendly Name", null],
    [ 0xD403, "Volume", null],
    [ 0xD404, "SupportedFormatsOrdered", SupportedFormatsOrderedSettingsTable],
    [ 0xD405, "DeviceIcon", null],
    [ 0xD406, "Session Initiator Verion Info", null],
    [ 0xD407, "Perceived Device Type", PerceivedDeviceTypeSettingsTable],
    [ 0xD410, "Playback Rate", null],
    [ 0xD411, "Playback Object", null],
    [ 0xD412, "Playback Container", null]
];


set MonthTable = 
[
    [ "1", "January" ],
    [ "2", "February" ],
    [ "3", "March" ],
    [ "4", "April" ],
    [ "5", "May" ],
    [ "6", "June" ],
    [ "7", "July" ],
    [ "8", "August" ],
    [ "9", "September" ],
    [ "10", "October" ],
    [ "11", "November" ],
    [ "12", "December" ]
];

set MicrosoftVendorExtensionID =
[
    [ 0xFFFFFFFF, "Unknown"],
    [ 0x00000000, "No Extension"],
    [ 0x00000006, "MTP"]
];

set PTPFunctionalModeTable = 
[
    [ 0xFFFF, "Reserved"],
    [ 0x0000, "Standard mode"],
    [ 0x0001, "Sleep state"],
    [ 0xC001, "Non-responsive Playback"],
    [ 0xC002, "Responsive playback"]
];

set MTPFormFlagTable =
[
    [ 0x00, "None", null],
    [ 0x01, "Range form", "DoRangeFormDecoding"],
    [ 0x02, "Enumeration form", "DoEnumerationFormDecoding"],
    [ 0x03, "DateTime form", null],
    [ 0x04, "Fixed-length array form", "DoFixedLengthArrayFormDecoding"],
    [ 0x05, "RegularExpression form", "DoRegularExpressionFormDecoding"],
    [ 0x06, "ByteArray form", "DoByteArrayFormDecoding"],
    [ 0xFF, "LongString form", "DoLongStringFormDecoding"]
];

set MTPProtectionStatusTable =
[
    [ 0xFFFF, "Reserved"],
    [ 0x0000, "No protection"],
    [ 0x0001, "Read-only"],
    [ 0x8002, "Read-only data"],
    [ 0x8003, "Non-transferrable data"]
];

set MTPAssociationTypeTable = 
[
    [ 0xFFFF, "Reserved"],
    [ 0x0000, "Not an association"],
    [ 0x0001, "Associated"]
];

set MTPVisibilityTypeTable = 
[
    [ 0xFFFF, "Reserved"],
    [ 0x0000, "Should be visible to users"],
    [ 0x0001, "Should be hidden from users"]
];


set MTPNonConsumableTypeTable = 
[
    [ 0xFF, "Reserved"],
    [ 0x00, "Intended for consumption"],
    [ 0x01, "Simply be stored"]
];

set MTPCorruptUnplayableTable = 
[
    [ 0xFF, "Reserved"],
    [ 0x00, "Normal"],
    [ 0x01, "Corrupt or unplayable"]
];

set MTPMetaGenreTable = 
[
    [0xFFFF, "MTP vendor extension"],
    [ 0x0000, "Not Used"],
    [ 0x0001, "Generic music audio file"],
    [ 0x0011, "Generic non-music audio file"],
    [ 0x0012, "Spoken-Word Audio Book Files"],
    [ 0x0013, "Spoken-Word Files (non-Audio book)"],
    [ 0x0014, "Spoken-Word News"],
    [ 0x0015, "Spoken-Word Talk Shows"],
    [ 0x0021, "Generic video file"],
    [ 0x0022, "News video file"],
    [ 0x0023, "Music video file"],
    [ 0x0024, "Home video file"],
    [ 0x0025, "Feature Film video file"],
    [ 0x0026, "Television Show video file"],
    [ 0x0027, "Training/Educational video file"],
    [ 0x0028, "Photo montage video file"],
    [ 0x0030, "Generic non-audio, non-video"],
    [ 0x0040, "Audio Mediacast"],
    [ 0x0041, "Video Mediacast"],
    [ 0x0042, "Mixed-media Mediacast"]
];
    
set MTPDRMStatusTable =
[
    [ 0xFFFF, "Reserved/Extension"],
    [ 0x0000, "No DRM protection"],
    [ 0x0001, "DRM protection"]
];

set MTPIsCroppedTable = 
[
    [ 0xFFFF, "Reserved"],
    [ 0x0000, "Not cropped"],
    [ 0x0001, "Cropped"],
    [ 0x0002, "Not and should not cropped"]
];

set MTPIsColourCorrectedTable =
[
    [ 0xFFFF, "Reserved"],
    [ 0x0000, "Not color corrected"],
    [ 0x0001, "Color corrected"],
    [ 0x0002, "Not and should not color corrected"]
];

set MTPBitRateTypeTable =
[
    [ 0xFFFF, "Reserved/Extension"],
    [ 0x0000, "Unused"],
    [ 0x0001, "Discrete"],
    [ 0x0002, "Variable"],
    [ 0x0003, "Free"]
];

set MTPScanTypeTable =
[
    [ 0xFFFF, "Reserved/Extension"],
    [ 0x0000, "Unused"],
    [ 0x0001, "Progressive"],
    [ 0x0002, "FieldInterleavedUpperFirst"],
    [ 0x0003, "FieldInterleavedLowerFirst"],
    [ 0x0004, "FieldSingleUpperFirst"],
    [ 0x0005, "FieldSingleLowerFirst"],
    [ 0x0006, "MixedInterlace"],
    [ 0x0007, "MixedInterlaceAndProgressive"]
];


set MTPNumberOfChannelsTable = 
[
    [ 0xFFFF, "Reserved/Extension"],
    [ 0x0000, "Unused"],
    [ 0x0001, "Mono (1 channel)"],
    [ 0x0002, "Stereo (2 channels)"],
    [ 0x0003, "2.1 channels"],
    [ 0x0004, "3 channels"],
    [ 0x0005, "3.1 channels"],
    [ 0x0006, "4 channels"],
    [ 0x0007, "4.1 channels"],
    [ 0x0008, "5 channels"],
    [ 0x0009, "5.1 channels"],
    [ 0x000A, "6 channels"],
    [ 0x000B, "6.1 channels"],
    [ 0x000C, "7 channels"],
    [ 0x000D, "7.1 channels"],
    [ 0x000E, "8 channels"],
    [ 0x000F, "8.1 channels"],
    [ 0x0010, "9 channels"],
    [ 0x0011, "9.1 channels"],
    [ 0x0012, "5.2 channels"],
    [ 0x0013, "6.2 channels"],
    [ 0x0014, "7.2 channels"],
    [ 0x0015, "8.2 channels"],
    [ 0x0016, "9.2 channels"]
];

set MTPAudioWaveCodecTable = 
[
    [ 0x0000, "WAVE_FORMAT_UNKNOWN"],
    [ 0x0001, "WAVE_FORMAT_PCM"],
    [ 0x0002, "WAVE_FORMAT_ADPCM"],
    [ 0x0003, "WAVE_FORMAT_IEEE_FLOAT"],
    [ 0x0004, "WAVE_FORMAT_VSELP"],
    [ 0x0005, "WAVE_FORMAT_IBM_CVSD"],
    [ 0x0006, "WAVE_FORMAT_ALAW"],
    [ 0x0007, "WAVE_FORMAT_MULAW"],
    [ 0x0008, "WAVE_FORMAT_DTS"],
    [ 0x0009, "WAVE_FORMAT_DRM"],
    [ 0x000A, "WAVE_FORMAT_WMSP1"],
    [ 0x0010, "WAVE_FORMAT_OKI_ADPCM"],
    [ 0x0011, "WAVE_FORMAT_DVI_ADPCM"],
    [ 0x0012, "WAVE_FORMAT_MEDIASPACE_ADPCM"],
    [ 0x0013, "WAVE_FORMAT_SIERRA_ADPCM"],
    [ 0x0014, "WAVE_FORMAT_G723_ADPCM"],
    [ 0x0015, "WAVE_FORMAT_DIGISTD"],
    [ 0x0016, "WAVE_FORMAT_DIGIFIX"],
    [ 0x0017, "WAVE_FORMAT_DIALOGIC_OKI_ADPCM"],
    [ 0x0018, "WAVE_FORMAT_MEDIAVISION_ADPCM"],
    [ 0x0019, "WAVE_FORMAT_CU_CODEC"],
    [ 0x001A, "WAVE_FORMAT_HP_DYNAMIC_VOICE"],
    [ 0x0020, "WAVE_FORMAT_YAMAHA_ADPCM"],
    [ 0x0021, "WAVE_FORMAT_SONARC"],
    [ 0x0022, "WAVE_FORMAT_DSPGROUP_TRUESPEECH"],
    [ 0x0023, "WAVE_FORMAT_ECHOSC1"],
    [ 0x0024, "WAVE_FORMAT_AUDIOFILE_AF36"],
    [ 0x0025, "WAVE_FORMAT_APTX"],
    [ 0x0026, "WAVE_FORMAT_AUDIOFILE_AF10"],
    [ 0x0027, "WAVE_FORMAT_PROSODY_1612"],
    [ 0x0028, "WAVE_FORMAT_LRC"],
    [ 0x0030, "WAVE_FORMAT_DOLBY_AC2"],
    [ 0x0031, "WAVE_FORMAT_GSM610"],
    [ 0x0032, "WAVE_FORMAT_MSNAUDIO"],
    [ 0x0033, "WAVE_FORMAT_ANTEX_ADPCME"],
    [ 0x0034, "WAVE_FORMAT_CONTROL_RES_VQLPC"],
    [ 0x0035, "WAVE_FORMAT_DIGIREAL"],
    [ 0x0036, "WAVE_FORMAT_DIGIADPCM"],
    [ 0x0037, "WAVE_FORMAT_CONTROL_RES_CR10"],
    [ 0x0038, "WAVE_FORMAT_NMS_VBXADPCM"],
    [ 0x0039, "WAVE_FORMAT_ROLAND_RDAC"],
    [ 0x003A, "WAVE_FORMAT_ECHOSC3"],
    [ 0x003B, "WAVE_FORMAT_ROCKWELL_ADPCM"],
    [ 0x003C, "WAVE_FORMAT_ROCKWELL_DIGITALK"],
    [ 0x003D, "WAVE_FORMAT_XEBEC"],
    [ 0x0040, "WAVE_FORMAT_G721_ADPCM"],
    [ 0x0041, "WAVE_FORMAT_G728_CELP"],
    [ 0x0042, "WAVE_FORMAT_MSG723"],
    [ 0x0043, "WAVE_FORMAT_MSG723_1"],
    [ 0x0044, "WAVE_FORMAT_MSG729"],
    [ 0x0045, "WAVE_FORMAT_SPG726"],
    [ 0x0050, "WAVE_FORMAT_MPEG"],
    [ 0x0052, "WAVE_FORMAT_RT24"],
    [ 0x0053, "WAVE_FORMAT_PAC"],
    [ 0x0055, "WAVE_FORMAT_MPEGLAYER3"],
    [ 0x0059, "WAVE_FORMAT_LUCENT_G723"],
    [ 0x0060, "WAVE_FORMAT_CIRRUS"],
    [ 0x0061, "WAVE_FORMAT_ESPCM"],
    [ 0x0062, "WAVE_FORMAT_VOXWARE"],
    [ 0x0063, "WAVE_FORMAT_CANOPUS_ATRAC"],
    [ 0x0064, "WAVE_FORMAT_G726_ADPCM"],
    [ 0x0065, "WAVE_FORMAT_G722_ADPCM"],
    [ 0x0067, "WAVE_FORMAT_DSAT_DISPLAY"],
    [ 0x0069, "WAVE_FORMAT_VOXWARE_BYTE_ALIGNED"],
    [ 0x0070, "WAVE_FORMAT_VOXWARE_AC8"],
    [ 0x0071, "WAVE_FORMAT_VOXWARE_AC10"],
    [ 0x0072, "WAVE_FORMAT_VOXWARE_AC16"],
    [ 0x0073, "WAVE_FORMAT_VOXWARE_AC20"],
    [ 0x0074, "WAVE_FORMAT_VOXWARE_RT24"],
    [ 0x0075, "WAVE_FORMAT_VOXWARE_RT29"],
    [ 0x0076, "WAVE_FORMAT_VOXWARE_RT29HW"],
    [ 0x0077, "WAVE_FORMAT_VOXWARE_VR12"],
    [ 0x0078, "WAVE_FORMAT_VOXWARE_VR18"],
    [ 0x0079, "WAVE_FORMAT_VOXWARE_TQ40"],
    [ 0x007A, "WAVE_FORMAT_VOXWARE_SC3"],
    [ 0x007B, "WAVE_FORMAT_VOXWARE_SC3"],
    [ 0x0080, "WAVE_FORMAT_SOFTSOUND"],
    [ 0x0081, "WAVE_FORMAT_VOXWARE_TQ60"],
    [ 0x0082, "WAVE_FORMAT_MSRT24"],
    [ 0x0083, "WAVE_FORMAT_G729A"],
    [ 0x0084, "WAVE_FORMAT_MVI_MVI2"],
    [ 0x0085, "WAVE_FORMAT_DF_G726"],
    [ 0x0086, "WAVE_FORMAT_DF_GSM610"],
    [ 0x0088, "WAVE_FORMAT_ISIAUDIO"],
    [ 0x0089, "WAVE_FORMAT_ONLIVE"],
    [ 0x008A, "WAVE_FORMAT_MULTITUDE_FT_SX20"],
    [ 0x008B, "WAVE_FORMAT_MM_INFOCOM_ITS_ACM_G721"],
    [ 0x008C, "WAVE_FORMAT_CONVEDIA_G729"],
    [ 0x008D, "WAVEFORMAT_CONGRUENCY_AUDIO_CODEC"],
    [ 0x0091, "WAVE_FORMAT_SBC24"],
    [ 0x0092, "WAVE_FORMAT_DOLBY_AC3_SPDIF"],
    [ 0x0093, "WAVE_FORMAT_MEDIASONIC_G723"],
    [ 0x0094, "WAVE_FORMAT_PROSODY_8KBPS"],
    [ 0x0097, "WAVE_FORMAT_ZYXEL_ADPCM"],
    [ 0x0098, "WAVE_FORMAT_PHILIPS_LPCBB"],
    [ 0x0099, "WAVE_FORMAT_PACKED"],
    [ 0x00A0, "WAVE_FORMAT_MALDEN_PHONYTALK"],
    [ 0x00A1, "WAVE_FORMAT_RRLGSM"],
    [ 0x00A2, "WAVE_FORMAT_RRLG729A"],
    [ 0x00A3, "WAVE_FORMAT_RRLG7231"],
    [ 0x00A4, "WAVE_FORMAT_RRLTETRA_ACLEP"],
    [ 0x00B0, "WAVE_FORMAT_NEC_AAC"],
    [ 0x0100, "WAVE_FORMAT_RHETOREX_ADPCM"],
    [ 0x0101, "WAVE_FORMAT_IRAT"],
    [ 0x0111, "WAVE_FORMAT_VIVO_G723"],
    [ 0x0112, "WAVE_FORMAT_VIVO_SIREN"],
    [ 0x0120, "WAVE_FORMAT_PHILIPS_CELP"],
    [ 0x0121, "WAVE_FORMAT_PHILIPS_GRUNDIG"],
    [ 0x0123, "WAVE_FORMAT_DIGITAL_G723"],
    [ 0x0125, "WAVE_FORMAT_SANYO_LD_ADPCM"],
    [ 0x0130, "WAVE_FORMAT_SIPROLAB_ACELPNET"],
    [ 0x0131, "WAVE_FORMAT_SIPROLAB_ACELP4800"],
    [ 0x0132, "WAVE_FORMAT_SIPROLAB_ACELP8V3"],
    [ 0x0133, "WAVE_FORMAT_SIPROLAB_G729"],
    [ 0x0134, "WAVE_FORMAT_SIPROLAB_G729A"],
    [ 0x0135, "WAVE_FORMAT_SIPROLAB_KELVIN"],
    [ 0x0136, "WAVE_FORMAT_VOICEAGE_AMR"],
    [ 0x0140, "WAVE_FORMAT_G726ADPCM"],
    [ 0x0141, "WAVE_FORMAT_CELP68"],
    [ 0x0142, "WAVE_FORMAT_CELP54"],
    [ 0x0150, "WAVE_FORMAT_QUALCOMM_PUREVOICE"],
    [ 0x0151, "WAVE_FORMAT_QUALCOMM_HALFRATE"],
    [ 0x0155, "WAVE_FORMAT_TUBGSM"],
    [ 0x0160, "WAVE_FORMAT_MSAUDIO1"],
    [ 0x0161, "WAVE_FORMAT_MSAUDIO2"],
    [ 0x0162, "WAVE_FORMAT_MSAUDIO3"],
    [ 0x0170, "WAVE_FORMAT_UNISYS_NAP_ADPCM"],
    [ 0x0171, "WAVE_FORMAT_UNISYS_NAP_ULAW"],
    [ 0x0172, "WAVE_FORMAT_UNISYS_NAP_ALAW"],
    [ 0x0173, "WAVE_FORMAT_UNISYS_NAP_16K"],
    [ 0x0174, "WAVE_FORMAT_MM_SYCOM_ACM_SYC008"],
    [ 0x0175, "WAVE_FORMAT_MM_SYCOM_ACM_SYC701_G726L"],
    [ 0x0176, "WAVE_FORMAT_MM_SYCOM_ACM_SYC701_CELP54"],
    [ 0x0177, "WAVE_FORMAT_MM_SYCOM_ACM_SYC701_CELP68"],
    [ 0x0178, "WAVE_FORMAT_KNOWLEDGE_ADVENTURE_ADPCM"],
    [ 0x0180, "WAVE_FORMAT_MPEG2AAC"],
    [ 0x0190, "WAVE_FORMAT_DTS_DS"],
    [ 0x0197, "WAVE_FORMAT_INNINGS_ADPCM"],
    [ 0x0200, "WAVE_FORMAT_CREATIVE_ADPCM"],
    [ 0x0202, "WAVE_FORMAT_CREATIVE_FASTSPEECH8"],
    [ 0x0203, "WAVE_FORMAT_CREATIVE_FASTSPEECH10"],
    [ 0x0210, "WAVE_FORMAT_UHER_ADPCM"],
    [ 0x0220, "WAVE_FORMAT_QUARTERDECK"],
    [ 0x0230, "WAVE_FORMAT_ILINK_VC"],
    [ 0x0240, "WAVE_FORMAT_RAW_SPORT"],
    [ 0x0250, "WAVE_FORMAT_IPI_HSX"],
    [ 0x0251, "WAVE_FORMAT_IPI_RPELP"],
    [ 0x0260, "WAVE_FORMAT_CS2"],
    [ 0x0270, "WAVE_FORMAT_SONY_SCX"],
    [ 0x0271, "WAVE_FORMAT_SONY_SCY"],
    [ 0x0272, "WAVE_FORMAT_SONY_ATRAC3"],
    [ 0x0273, "WAVE_FORMAT_SONY_SPC"],
    [ 0x0280, "WAVE_FORMAT_TELUM"],
    [ 0x0281, "WAVE_FORMAT_TELUMIA"],
    [ 0x0285, "WAVE_FORMAT_NCVS_ADPCM"],
    [ 0x0300, "WAVE_FORMAT_FM_TOWNS_SND"],
    [ 0x0301, "Reserved"],
    [ 0x0302, "Reserved"],
    [ 0x0303, "Reserved"],
    [ 0x0304, "Reserved"],
    [ 0x0305, "Reserved"],
    [ 0x0306, "Reserved"],
    [ 0x0307, "Reserved"],
    [ 0x0308, "Reserved"],
    [ 0x0350, "WAVE_FORMAT_DEVELOPMENT"],
    [ 0x0351, "WAVE_FORMAT_CELP833"],
    [ 0x0400, "WAVE_FORMAT_BTV_DIGITAL"],
    [ 0x0450, "WAVE_FORMAT_QDESIGN_MUSIC"],
    [ 0x0680, "WAVE_FORMAT_VME_VMPCM"],
    [ 0x0681, "WAVE_FORMAT_TPC"],
    [ 0x1000, "WAVE_FORMAT_OLIGSM"],
    [ 0x1001, "WAVE_FORMAT_OLIADPCM"],
    [ 0x1002, "WAVE_FORMAT_OLICELP"],
    [ 0x1003, "WAVE_FORMAT_OLISBC"],
    [ 0x1004, "WAVE_FORMAT_OLIOPR"],
    [ 0x1100, "WAVE_FORMAT_LH_CODEC"],
    [ 0X1101, "WAVE_FORMAT_LH_CELP"],
    [ 0X1102, "WAVE_FORMAT_LH_SB8"],
    [ 0X1103, "WAVE_FORMAT_LH_SB12"],
    [ 0X1104, "WAVE_FORMAT_LH_SB16"],
    [ 0x1400, "WAVE_FORMAT_NORRIS"],
    [ 0x1500, "WAVE_FORMAT_SOUNDSPACE_MUSICOMPRESS"],
    [ 0x1630, "WAVE_FORMAT_WMAUDIO_LOSSLESS"],
    [ 0x1640, "WAVE_FORMAT_WMASPDIF"],
    [ 0x1971, "WAVE_FORMAT_SONICFOUNDRY_LOSSLESS"],
    [ 0x2000, "WAVE_FORMAT_DVM"],
    [ 0x2500, "WAVE_FORMAT_MSCE"],
    [ 0x4143, "WAVE_FORMAT_DIVIO_AAC"],
    [ 0x4201, "WAVE_FORMAT_NOKIA_AMR"],
    [ 0x4243, "WAVE_FORMAT_DIVIO_G726"],
    [ 0x7000, "WAVE_FORMAT_3COM_NBX"],
    [ 0x7A21, "WAVE_FORMAT_NTT_DOCOMO_AMR_NO_SID"],
    [ 0x7A22, "WAVE_FORMAT_NTT_DOCOMO_AMR_WITH_SID"],
    [ 0xA100, "WAVE_FORMAT_COMVERSEINFOSYS_G723_1"],
    [ 0xA101, "WAVE_FORMAT_COMVERSEINFOSYS_AVQSBC"],
    [ 0xA102, "WAVE_FORMAT_COMVERSEINFOSYS_OLDSBC"],
    [ 0xA103, "WAVE_FORMAT_SYMBOLTECH_G729A"],
    [ 0xA104, "WAVE_FORMAT_VOICEAGE_AMR_WB"],
    [ 0xA105, "WAVE_FORMAT_ITI_G726"],
    [ 0xA106, "WAVE_FORMAT_AAC"],
    [ 0xA107, "WAVE_FORMAT_ESLG726"]
];

set MTPMessageReadTypeTable = 
[
    [ 0xFFFF, "Reserved"],
    [ 0x0000, "This message has been read"],
    [ 0x0001, "This message has not been read"]
];

set MTPActivityStatusTable = 
[
    [ 0xFFFF, "Reserved"],
    [ 0x0000, "In Progress"],
    [ 0x0001, "Not yet begun"],
    [ 0x0002, "50% complete"]
];

set MTPObjectPropCodesTable = 
[
    [ 0xFFFF, "UNKNOWN", null],
    [ 0xDC01, "StorageID", null],
    [ 0xDC02, "ObjectFormat", null],
    [ 0xDC03, "ProtectionStatus", MTPProtectionStatusTable],
    [ 0xDC04, "ObjectSize", null],
    [ 0xDC05, "Association Type", MTPAssociationTypeTable],
    [ 0xDC06, "Association Desc", null],
    [ 0xDC07, "ObjectFileName", null],
    [ 0xDC08, "DateCreated", null],
    [ 0xDC09, "DateModified", null],
    [ 0xDC0A, "Keywords", null],
    [ 0xDC0B, "Parent Object", null],
    [ 0xDC0C, "Allowed Folder Contents", null],
    [ 0xDC0D, "Hidden", MTPVisibilityTypeTable],
    [ 0xDC0E, "System Object", MTPVisibilityTypeTable],    
    [ 0xDC41, "Persistent Unique Object Identifier", null],
    [ 0xDC42, "SyncID", null],
    [ 0xDC43, "Property Bag", null],
    [ 0xDC44, "Name", null],
    [ 0xDC45, "CreatedBy", null],
    [ 0xDC46, "Artist", null],
    [ 0xDC47, "DateAuthored", null],
    [ 0xDC48, "Description", null],
    [ 0xDC49, "URL Reference", null],
    [ 0xDC4A, "Language-Locale", null],
    [ 0xDC4B, "Copyright Information", null],
    [ 0xDC4C, "Source", null],
    [ 0xDC4D, "Origin Location", null],
    [ 0xDC4E, "DateAdded", null],
    [ 0xDC4F, "Non-Consumable", MTPNonConsumableTypeTable],
    [ 0xDC50, "Corrupt/Unplayable", MTPCorruptUnplayableTable],
    [ 0xDC51, "ProducerSerialNumber", null],
    [ 0xDC81, "RepresentativeSampleFormat", null],
    [ 0xDC82, "RepresentativeSampleSize", null],
    [ 0xDC83, "RepresentativeSampleHeight", null],
    [ 0xDC84, "RepresentativeSampleWidth", null],
    [ 0xDC85, "RepresentativeSampleDuration", null],
    [ 0xDC86, "RepresentativeSampleData", null],
    [ 0xDC87, "Width", null],
    [ 0xDC88, "Height", null],
    [ 0xDC89, "Duration", null],
    [ 0xDC8A, "Rating", null],
    [ 0xDC8B, "Track", null],
    [ 0xDC8C, "Genre", null],
    [ 0xDC8D, "Credits", null],
    [ 0xDC8E, "Lyrics", null],
    [ 0xDC8F, "SubscriptionContentID", null],
    [ 0xDC90, "ProducedBy", null],
    [ 0xDC91, "UseCount", null],
    [ 0xDC92, "SkipCount", null],
    [ 0xDC93, "LastAccessed", null],
    [ 0xDC94, "ParentalRating", null],
    [ 0xDC95, "MetaGenre", MTPMetaGenreTable],
    [ 0xDC96, "Composer", null],
    [ 0xDC97, "EffectiveRating", null],
    [ 0xDC98, "Subtitle", null],
    [ 0xDC99, "OriginalReleaseDate", null],
    [ 0xDC9A, "AlbumName", null],
    [ 0xDC9B, "AlbumArtist", null],
    [ 0xDC9C, "Mood", null],
    [ 0xDC9D, "DRM Status", MTPDRMStatusTable],
    [ 0xDC9E, "SubDescription", null],
    [ 0xDCD1, "IsCropped", MTPIsCroppedTable],
    [ 0xDCD2, "IsColourCorrected", MTPIsColourCorrectedTable],
    [ 0xDCD3, "Image Bit Depth", null],
    [ 0xDCD4, "Fnumber", null],
    [ 0xDCD5, "Exposure Time", null],
    [ 0xDCD6, "Exposure Index", null],    
    [ 0xDE91, "TotalBitRate", null],
    [ 0xDE92, "BitrateType", MTPBitRateTypeTable],
    [ 0xDE93, "SampleRate", null],
    [ 0xDE94, "NumberOfChannels", MTPNumberOfChannelsTable],
    [ 0xDE95, "AudioBitDepth", null],
    [ 0xDE97, "ScanType", MTPScanTypeTable],
    [ 0xDE99, "AudioWAVECodec", MTPAudioWaveCodecTable],
    [ 0xDE9A, "AudioBitRate", null],
    [ 0xDE9B, "VideoFourCCCodec", null],
    [ 0xDE9C, "VideoBitRate", null],
    [ 0xDE9D, "FramesPerThousandSeconds", null],
    [ 0xDE9E, "KeyFrameDistance", null],
    [ 0xDE9F, "BufferSize", null],
    [ 0xDEA0, "EncodingQuality", null],
    [ 0xDEA1, "Encoding Profile", null],
    [ 0xDCE0, "Display Name", null],
    [ 0xDCE1, "Body Text", null],
    [ 0xDCE2, "Subject", null],
    [ 0xDCE3, "Priority", null],
    [ 0xDD00, "Given Name", null],
    [ 0xDD01, "Middle Names", null],
    [ 0xDD02, "Family Name", null],
    [ 0xDD03, "Prefix", null],
    [ 0xDD04, "Suffix", null],
    [ 0xDD05, "Phonetic Given Name", null],
    [ 0xDD06, "Phonetic Family Name", null],
    [ 0xDD07, "Email Primary", null],
    [ 0xDD08, "Email Personal 1", null],
    [ 0xDD09, "Email Personal 2", null],
    [ 0xDD0A, "Email Business 1", null],
    [ 0xDD0B, "Email Business 2", null],
    [ 0xDD0C, "Email Others", null],
    [ 0xDD0D, "Phone Number Primary", null],
    [ 0xDD0E, "Phone Number Personal", null],
    [ 0xDD0F, "Phone Number Personal 2", null],
    [ 0xDD10, "Phone Number Business", null],
    [ 0xDD11, "Phone Number Business 2", null],
    [ 0xDD12, "Phone Number Mobile", null],
    [ 0xDD13, "Phone Number Mobile 2", null],
    [ 0xDD14, "Fax Number Primary", null],
    [ 0xDD15, "Fax Number Personal", null],
    [ 0xDD16, "Fax Number Business", null],
    [ 0xDD17, "Pager Number", null],
    [ 0xDD18, "Phone Number Others", null],
    [ 0xDD19, "Primary Web Address", null],
    [ 0xDD1A, "Persoanl Web Address", null],
    [ 0xDD1B, "Business Web Address", null],
    [ 0xDD1C, "Instant Messenger Address", null],
    [ 0xDD1D, "Instant Messenger Address 2", null],
    [ 0xDD1E, "Instant Messenger Address 3", null],
    [ 0xDD1F, "Postal Address Personal Full", null],
    [ 0xDD20, "Postal Address Personal Line 1", null],
    [ 0xDD21, "Postal Address Personal Line 2", null],
    [ 0xDD22, "Postal Address Personal City", null],
    [ 0xDD23, "Postal Address Personal Region", null],
    [ 0xDD24, "Postal Address Personal Postal Code", null],
    [ 0xDD25, "Postal Address Personal Country", null],
    [ 0xDD26, "Postal Address Business Full", null],
    [ 0xDD27, "Postal Address Business Line 1", null],
    [ 0xDD28, "Postal Address Business Line 2", null],
    [ 0xDD29, "Postal Address Business City", null],
    [ 0xDD2A, "Postal Address Business Region", null],
    [ 0xDD2B, "Postal Address Business Postal Code", null],
    [ 0xDD2C, "Postal Address Business Country", null],
    [ 0xDD2D, "Postal Address Other Full", null],
    [ 0xDD2E, "Postal Address Other Line 1", null],
    [ 0xDD2F, "Postal Address Other Line 2", null],
    [ 0xDD30, "Postal Address Other City", null],
    [ 0xDD31, "Postal Address Other Region", null],
    [ 0xDD32, "Postal Address Other Postal Code", null],
    [ 0xDD33, "Postal Address Other Country", null],
    [ 0xDD34, "Organization Name", null],
    [ 0xDD35, "Phonetic Organization Name", null],
    [ 0xDD36, "Role", null],
    [ 0xDD37, "Birthdate", null],
    [ 0xDD40, "Message To", null],
    [ 0xDD41, "Message CC", null],
    [ 0xDD42, "Message BCC", null],
    [ 0xDD43, "Message Read", MTPMessageReadTypeTable],
    [ 0xDD44, "Message Received Time", null],
    [ 0xDD45, "Message Sender", null],
    [ 0xDD50, "Activity Begin Time", null],
    [ 0xDD51, "Activity End Time", null],
    [ 0xDD52, "Activity Location", null],
    [ 0xDD54, "Activity Required Atendees", null],
    [ 0xDD55, "Activity Optional Atendees", null],
    [ 0xDD56, "Activity Resources", null],
    [ 0xDD57, "Activity Accepted", null],
    [ 0xDD58, "Activity Tentative", null],
    [ 0xDD59, "Activity Declined", null],
    [ 0xDD5A, "Activity Reminder Time ", null],
    [ 0xDD5B, "Activity Owner", null],
    [ 0xDD5C, "Activity Status", MTPActivityStatusTable],    
    [ 0xDD5D, "Owner", null],
    [ 0xDD5E, "Editor", null],
    [ 0xDD5F, "Webmaster", null],
    [ 0xDD60, "URL Source", null],
    [ 0xDD61, "URL Destination", null],
    [ 0xDD62, "Time Bookmark", null],
    [ 0xDD63, "Object Bookmark", null],
    [ 0xDD64, "Byte Bookmark", null],
    [ 0xDD70, "Last Build Date", null],
    [ 0xDD71, "Time to Live", null],
    [ 0xDD72, "Media GUID", null]
];

InitTables()
{
    if (PTPResponseCodeTable == null)
    {
        PTPResponseReservedString                                   = "Reserved";
        PTPResponseUndefinedString                                  = "Undefined";
        PTPResponseOKString                                         = "ResponseCode: 0x2001" + NewLine() + "Operation has completed successfully.";
        PTPResponseGeneral_ErrorString                              = "ResponseCode: 0x2002" + NewLine() + "This operation did not complete, and the reason for"  + NewLine() + "the failure is not known.";
        PTPResponseSession_Not_OpenString                           = "ResponseCode: 0x2003" + NewLine() + "Indicates that the session handle identified by the"  + NewLine() + "operation dataset for this operation is not a" + NewLine() + "currently open session.";
        PTPResponseInvalid_TransactionIDString                      = "ResponseCode: 0x2004" + NewLine() + "Indicates that the TransactionID of this operation"   + NewLine() + "does not identify a valid transaction.";
        PTPResponseOperation_Not_SupportedString                    = "ResponseCode: 0x2005" + NewLine() + "This response indicates that an Operation has been"   + NewLine() + "called with what appears to be a valid code,"  + NewLine() + "but the responder does not support the operation" + NewLine() + "identified by that code. The initiator should"     + NewLine() + "only invoke operations contained in the responder’s DeviceInfo dataset, so this response should not normally be returned.";
        PTPResponseParameter_Not_SupportedString                    = "ResponseCode: 0x2006" + NewLine() + "Indicates that a parameter of an operation contains"  + NewLine() + "a non-zero value, but is not supported. This"  + NewLine() + "response is different from Invalid_Parameter.";
        PTPResponseIncomplete_TransferString                        = "ResponseCode: 0x2007" + NewLine() + "This response should be sent when a transfer did not" + NewLine() + "complete successfully, and indicates that data"+ NewLine() + "transferred should be discarded.  This response"  + NewLine() + "should not be sent if the transfer was cancelled"  + NewLine() + "by the Initiator.";
        PTPResponseInvalid_StorageIDString                          = "ResponseCode: 0x2008" + NewLine() + "Indicates that one or more StorageIDs sent as"        + NewLine() + "parameters of an operation do not refer to"    + NewLine() + "actual StorageIDs on the device.";
        PTPResponseInvalid_ObjectHandleString                       = "ResponseCode: 0x2009" + NewLine() + "Indicates that one or more ObjectHandles sent as"     + NewLine() + "parameters of an operation do not refer to"    + NewLine() + "actual Objects on the device. The list of valid"  + NewLine() + "ObjectHandles should be requested again, along"    + NewLine() + "with any appropriate ObjectInfo datasets.";
        PTPResponseDeviceProp_Not_SupportedString                   = "ResponseCode: 0x200A" + NewLine() + "Indicates that a DevicePropCode sent as a parameter"  + NewLine() + "of an operation appears to be a valid code,"   + NewLine() + "but is not supported by the device. The initiator"+ NewLine() + "should only attempt to work with Device"           + NewLine() + "Properties identified in the DevicePropertiesSupported field of the DeviceInfo Dataset, so this response should not normally be returned.";
        PTPResponseInvalid_ObjectFormatCodeString                   = "ResponseCode: 0x200B" + NewLine() + "Indicates that the device does not support an"        + NewLine() + "ObjectFormatCode supplied in the given context.";
        PTPResponseStore_FullString                                 = "ResponseCode: 0x200C" + NewLine() + "Indicates that a store identified in this operation"  + NewLine() + "is full, and this is preventing the successful"+ NewLine() + "completion of that operation.";
        PTPResponseObject_WriteProtectedString                      = "ResponseCode: 0x200D" + NewLine() + "Indicates that an object referred to by the operation"+ NewLine() + "is write-protected.";
        PTPResponseStore_Read_OnlyString                            = "ResponseCode: 0x200E" + NewLine() + "Indicates that a store referred to by the operation"  + NewLine() + "is read-only.";
        PTPResponseAccess_DeniedString                              = "ResponseCode: 0x200F" + NewLine() + "This response should be sent when access to data"     + NewLine() + "required by the operation is denied. This"     + NewLine() + "should not be used when the device is busy, but"  + NewLine() + "to indicate that if the current state of the"      + NewLine() + "device does not change access will continue to be denied.";
        PTPResponseNo_Thumbnail_PresentString                       = "ResponseCode: 0x2010" + NewLine() + "Indicates that a data object exists with the"         + NewLine() + "specified ObjectHandle, but a thumbnail"       + NewLine() + "cannot be provided for that object.";
        PTPResponseSelfTest_FailedString                            = "ResponseCode: 0x2011" + NewLine() + "This should be sent when the device fails a"          + NewLine() + "device-specific self test.";
        PTPResponsePartial_DeletionString                           = "ResponseCode: 0x2012" + NewLine() + "Indicates that only a subset of the objects"          + NewLine() + "indicated for deletion were actually deleted." + NewLine() + "This could be caused by some of those objects"    + NewLine() + "being write-protected or on read-only stores.";
        PTPResponseStore_Not_AvailableString                        = "ResponseCode: 0x2013" + NewLine() + "Indicates that the store indicated (or the store that"+ NewLine() + "contains the indicated object) is not"         + NewLine() + "physically available. This can be caused by media"+ NewLine() + "ejection. This response shall not be used to"      + NewLine() + "indicate that the store is busy";
        PTPResponseSpecification_By_Format_UnsupportedString        = "ResponseCode: 0x2014" + NewLine() + "This response should be sent when an operation"       + NewLine() + "attempts to specify an action only on objects" + NewLine() + "which have a particular format code, but that"    + NewLine() + "this device does not support that capability. The" + NewLine() + "operation should be attempted again without" + NewLine() + "specifying by format. When this response is sent," + NewLine() + "it should indicate that any future attempts to call" + NewLine() + "the same operation specifying by format will"   + NewLine() + "also result in this response.";
        PTPResponseNo_Valid_ObjectInfoString                        = "ResponseCode: 0x2015" + NewLine() + "This should be sent when a SendObject operation has"  + NewLine() + "been called without the initiator having"      + NewLine() + "previously sent a corresponding SendObjectInfo"   + NewLine() + "successfully. The initiator should successfully"   + NewLine() + "complete a SendObjectInfo operation before"  + NewLine() + "attempting another SendObject operation.";
        PTPResponseInvalid_Code_FormatString                        = "ResponseCode: 0x2016" + NewLine() + "Indicates that a datacode used in this operation"     + NewLine() + "does not have the correct format, and is"      + NewLine() + "therefore known to be invalid. This response"     + NewLine() + "should be used when the most-significant bits of"  + NewLine() + "a datacode does not have the format required"+ NewLine() + "for that type of code, and not when the data"      + NewLine() + "appears to have the correct type but is invalid for" + NewLine() + "other reasons.";
        PTPResponseUnknown_Vendor_CodeString                        = "ResponseCode: 0x2017" + NewLine() + "Indicates that the indicated data code has the"       + NewLine() + "correct format, but is in a vendor extension"  + NewLine() + "range not recognized by the device. This response"+ NewLine() + "should typically not occur, as the supported"      + NewLine() + "vendor extensions should be identifiable by" + NewLine() + "examination of the DeviceInfo dataset.";
        PTPResponseCapture_Already_TerminatedString                 = "ResponseCode: 0x2018" + NewLine() + "This should be sent when an operation attempts to"    + NewLine() + "terminate a capture session, but that the"     + NewLine() + "capture session has already terminated. This"     + NewLine() + "response is only used for the TerminateOpenCapture"+ NewLine() + "operation, which is only used to terminate"  + NewLine() + "open-ended captures.";
        PTPResponseDevice_BusyString                                = "ResponseCode: 0x2019" + NewLine() + "This response should be sent when the device is not"  + NewLine() + "currently able to process a request because"   + NewLine() + "it, or the specified store, is busy. This"        + NewLine() + "response should imply that the operation may be"   + NewLine() + "successful at a later time, but is not"      + NewLine() + "possible right now. This response shall not be"    + NewLine() + "used to indicate that a store is physically unavailable.";
        PTPResponseInvalid_ParentObjectString                       = "ResponseCode: 0x201A" + NewLine() + "This response should be sent when an indicated object"+ NewLine() + "is not of type Association, but is required to"+ NewLine() + "be of type Association in the context in which it"+ NewLine() + "is used, and therefore is not a valid"             + NewLine() + "ParentObject. This response is not intended" + NewLine() + "to be used for specified ObjectHandles that do not"+ NewLine() + "refer to valid objects, but only for ObjectHandles"  + NewLine() + "which refer to actual objects which are not of" + NewLine() + "type Association.";
        PTPResponseInvalid_DeviceProp_FormatString                  = "ResponseCode: 0x201B" + NewLine() + "This response should be sent when an attempt is made" + NewLine() + "to set a DeviceProperty, but the"              + NewLine() + "DevicePropDesc dataset sent is not the correct"   + NewLine() + "size or format.";
        PTPResponseInvalid_DeviceProp_ValueString                   = "ResponseCode: 0x201C" + NewLine() + "This response should be sent when an attempt is made" + NewLine() + "to set a DeviceProperty to a particular"       + NewLine() + "value, but that value is not allowed by the device.";
        PTPResponseInvalid_ParameterString                          = "ResponseCode: 0x201D" + NewLine() + "This response indicates that a parameter of the"      + NewLine() + "operation is not a valid value.  This"         + NewLine() + "response is different from "                      + NewLine() + "Parameter_Not_Supported, which indicates that no"  + NewLine() + "value was expected in this parameter.";
        PTPResponseSession_Already_OpenString                       = "ResponseCode: 0x201E" + NewLine() + "This response may be sent in resonse to an"           + NewLine() + "OpenSession operation.  If multiple sessions"  + NewLine() + "are supported by the device and transport, this"  + NewLine() + "response indicates that a session with the"        + NewLine() + "specified SessionID is already open.  If"    + NewLine() + "multiple sessions are not supported by either the" + NewLine() + "device or the transport, this response indicates"    + NewLine() + "that a session is open and must be closed"      + NewLine() + "before another session can be opened.";
        PTPResponseTransaction_CancelledString                      = "ResponseCode: 0x201F" + NewLine() + "This response indicates that the operation was"       + NewLine() + "interrupted due to manual cancellation by the" + NewLine() + "initiator.";
        PTPResponseSpecification_of_Destination_UnsupportedString   = "ResponseCode: 0x2020" + NewLine() + "This response may be sent as a response to a"         + NewLine() + "SendObjectInfo operation to indicate that the" + NewLine() + "responder does not support the specification of"  + NewLine() + "destination. This response implies that any future"+ NewLine() + "attempts to specify the object destination"  + NewLine() + "will also fail with the same response.";
        PTPResponseMTP_Response_Code_UndefinedString                = "MTP Undefined";
        PTPResponseInvalid_ObjectPropCodeString                     = "ResponseCode: 0xA801" + NewLine() + "Indicates that the device does not support the sent"  + NewLine() + "Object Property Code in this context.";
        PTPResponseInvalid_ObjectProp_FormatString                  = "ResponseCode: 0xA802" + NewLine() + "Indicates that an object property sent to the device" + NewLine() + "is in an unsupported size or type.";
        PTPResponseInvalid_ObjectProp_ValueString                   = "ResponseCode: 0xA803" + NewLine() + "Indicates that an object property sent to the device" + NewLine() + "is the correct type, but contains a value"     + NewLine() + "which is not supported. The supported values"     + NewLine() + "should be identified by the ObjectPropDesc dataset.";
        PTPResponseInvalid_ObjectReferenceString                    = "ResponseCode: 0xA804" + NewLine() + "Indicates that a sent Object Reference is invalid."   + NewLine() + "Either the reference contains an object"       + NewLine() + "handle not present on the device, or the"         + NewLine() + "reference attempting to be set is unsupported in context.";
        PTPResponseInvalid_DatasetString                            = "ResponseCode: 0xA806" + NewLine() + "Indicates that the dataset sent in the data phase of" + NewLine() + "this operation is invalid.";
        PTPResponseSpecification_By_Group_UnsupportedString         = "ResponseCode: 0xA807" + NewLine() + "May be used as the response to indicate that the"     + NewLine() + "responder does not support the specification"  + NewLine() + "of groups by the initiator. This response implies"+ NewLine() + "that the initiator should not attempt to specify"  + NewLine() + "the group code in any future operations, as" + NewLine() + "they will also fail with the same response.";
        PTPResponseObject_Too_LargeString                           = "ResponseCode: 0xA809" + NewLine() + "Indicates that the object desired to be sent cannot"  + NewLine() + "be stored in the filesystem of the device."    + NewLine() + "This should not be used when there is"            + NewLine() + "insufficient space on the storage.";
   


        PTPResponseCodeTable = 
        [
            [   0xFFFF, "Reserved",                                 PTPResponseReservedString],
            [   0x2000, "Undefined",                                PTPResponseUndefinedString ],
            [   0x2001, "OK",                                       PTPResponseOKString ],
            [   0x2002, "General Error",                            PTPResponseGeneral_ErrorString ],
            [   0x2003, "Session Not Open",                         PTPResponseSession_Not_OpenString ],
            [   0x2004, "Invalid TransactionID",                    PTPResponseInvalid_TransactionIDString ],
            [   0x2005, "Operation Not Supported",                  PTPResponseOperation_Not_SupportedString ],
            [   0x2006, "Parameter Not Supported",                  PTPResponseParameter_Not_SupportedString ],
            [   0x2007, "Incomplete Transfer",                      PTPResponseIncomplete_TransferString ],
            [   0x2008, "Invalid StorageID",                        PTPResponseInvalid_StorageIDString ],
            [   0x2009, "Invalid ObjectHandle",                     PTPResponseInvalid_ObjectHandleString ],
            [   0x200A, "DeviceProp Not Supported",                 PTPResponseDeviceProp_Not_SupportedString ],
            [   0x200B, "Invalid ObjectFormatCode",                 PTPResponseInvalid_ObjectFormatCodeString ],
            [   0x200C, "Store Full",                               PTPResponseStore_FullString ],
            [   0x200D, "Object WriteProtected",                    PTPResponseObject_WriteProtectedString ],
            [   0x200E, "Store Read-Only",                          PTPResponseStore_Read_OnlyString ],
            [   0x200F, "Access Denied",                            PTPResponseAccess_DeniedString ],
            [   0x2010, "No Thumbnail Present",                     PTPResponseNo_Thumbnail_PresentString ],
            [   0x2011, "SelfTest Failed",                          PTPResponseSelfTest_FailedString ],
            [   0x2012, "Partial Deletion",                         PTPResponsePartial_DeletionString ],
            [   0x2013, "Store Not Available",                      PTPResponseStore_Not_AvailableString ],
            [   0x2014, "Specification By Format Unsupported",      PTPResponseSpecification_By_Format_UnsupportedString ],
            [   0x2015, "No Valid ObjectInfo",                      PTPResponseNo_Valid_ObjectInfoString ],
            [   0x2016, "Invalid Code Format",                      PTPResponseInvalid_Code_FormatString ],
            [   0x2017, "Unknown Vendor Code",                      PTPResponseUnknown_Vendor_CodeString ],
            [   0x2018, "Capture Already Terminated",               PTPResponseCapture_Already_TerminatedString ],
            [   0x2019, "Device Busy",                              PTPResponseDevice_BusyString ],
            [   0x201A, "Invalid ParentObject",                     PTPResponseInvalid_ParentObjectString ],
            [   0x201B, "Invalid DeviceProp Format",                PTPResponseInvalid_DeviceProp_FormatString ],
            [   0x201C, "Invalid DeviceProp Value",                 PTPResponseInvalid_DeviceProp_ValueString ],
            [   0x201D, "Invalid Parameter",                        PTPResponseInvalid_ParameterString ],
            [   0x201E, "Session Already Open",                     PTPResponseSession_Already_OpenString ],
            [   0x201F, "Transaction Cancelled",                    PTPResponseTransaction_CancelledString ],
            [   0x2020, "Specification of Destination Unsupported", PTPResponseSpecification_of_Destination_UnsupportedString ],
            [   0xA801, "MTP Response Code Undefined",              PTPResponseMTP_Response_Code_UndefinedString],
            [   0xA801, "Invalid_ObjectPropCode",                   PTPResponseInvalid_ObjectPropCodeString ],
            [   0xA802, "Invalid_ObjectProp_Format",                PTPResponseInvalid_ObjectProp_FormatString ],
            [   0xA803, "Invalid_ObjectProp_Value",                 PTPResponseInvalid_ObjectProp_ValueString ],
            [   0xA804, "Invalid_ObjectReference",                  PTPResponseInvalid_ObjectReferenceString ],
            [   0xA806, "Invalid_Dataset",                          PTPResponseInvalid_DatasetString ],
            [   0xA808, "Specification_By_Group_Unsupported",       PTPResponseSpecification_By_Group_UnsupportedString ],
            [   0xA809, "Object_Too_Large",                         PTPResponseObject_Too_LargeString ]
        ];
    }
    if (PTPBulkTable == null)
    {
        PTPBulkTable = 
        [
            [ 0,    "Undefined", null, "This is an undefined Container Type" ], 
            [ 1,    "Command", PTPOperationCodeTable, "This is the Operation Request Phase initiates a transaction" ],
            [ 2,    "Data", PTPOperationCodeTable, "This is an optional Data Phase." ],
            [ 3,    "Response", PTPResponseCodeTable, "This is the Response Phase transmitted from the Responder to the Initiator to report information about the preceding transaction" ],
            [ 4,    "Event", PTPEventCodeTable, "This is an Asynchronous Events." ]
        ];
    }
}

const Tabular_Def_Table = Map( 
[   
    #----------------------------------------------------------------------------------------------------------------------
    #       id                          ,      colId                          , 		containerCellId
    #----------------------------------------------------------------------------------------------------------------------
    [ CELL_STILL_IMAGE_CON_TYPE         , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE   , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ CELL_STILL_IMAGE_CODE             , TABULAR_SCRIPT_COLUMN_ID_NONE      , TABULAR_SCRIPT_CONTAINER_CELL_ID_MISC ],
    [ CELL_STILL_IMAGE_STANDARD_VERSION , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE   , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ CELL_STILL_IMAGE_STORAGE_ID       , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE   , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ CELL_STILL_IMAGE_STORAGE_TYPE     , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE   , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ CELL_STILL_IMAGE_OBJ_HAN_TOT      , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE   , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ CELL_STILL_IMAGE_DEVICE_PROP_CODE , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE   , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ CELL_STILL_IMAGE_OBJ_PROP_VALUE   , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE   , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ CELL_STILL_IMAGE_NUM_ELEMENTS     , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE   , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ CELL_STILL_IMAGE_REQUEST          , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE   , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ CELL_WVALUE                       , TABULAR_SCRIPT_COLUMN_ID_NONE      , TABULAR_SCRIPT_CONTAINER_CELL_ID_MISC ],
    [ CELL_REQUEST                      , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE   , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ]
] );
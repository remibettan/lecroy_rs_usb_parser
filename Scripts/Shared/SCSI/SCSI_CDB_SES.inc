#
#  Copyright (c) 2006, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_SES.inc
#
#  SCSI CDB definitions for SES-2 command set.
# 
################################################################################

const SES_CDB_Table = 
[
     null,                      # first item must be null for CDB definition tables
     "SCSI Enclosure Services", # the second item must specify the full name of command set covered by this table
     "SES-2"                  , # the third  item must specify the short name of command set covered by this table

#   OperCode, CDB_Name        , CDB_Decoder      , CDB_Color,         CDB_Tooltip #
#---------------------------------------------------------

    [0xA3   , "MAINTENANCE (IN)", "ShowMaintenanceIn" , CDB_MntnceIn_Color,
        "The MAINTENANCE IN command employs different\n" + 
        "service actions from the SCSI device.", "0000000000000000000000A3" ],        
    
    [0xA4   , "MAINTENANCE (OUT)" , "ShowMaintenanceOut" , CDB_MntnceOut_Color,
        "The MAINTENANCE OUT command employs different\n" + 
        "service actions from the SCSI device.", "0000000000000000000000A4"],
        
    [0xBA , "REDUNDANCY GROUP (IN)",  "ShowRedundancyGroupIn", CDB_RedundancyGroupIn_Color  , 
        "The REDUNDANCY GROUP (IN) command employs different\n" + 
        "service actions from the SCSI device.", "0000000000000000000000BA"],
    [0xBB , "REDUNDANCY GROUP (OUT)", "ShowRedundancyGroupOut", CDB_RedundancyGroupOut_Color , 
        "The REDUNDANCY GROUP (OUT) command employs different\n" + 
        "service actions from the SCSI device.", "0000000000000000000000BB"],
    [0xBC , "SPARE (IN)",             "ShowSpareIn", CDB_SpareIn_Color            , 
        "The SPARE (IN) command employs different\n" + 
        "service actions from the SCSI device.", "0000000000000000000000BC"],
    [0xBD , "SPARE (OUT)",            "ShowSpareOut", CDB_SpareOut_Color           , 
        "The SPARE (OUT) command employs different\n" + 
        "service actions from the SCSI device.", "0000000000000000000000BD"],
    [0xBE , "VOLUME SET (IN)",        "ShowVolumeSetIn", CDB_VolumeSetIn_Color        , 
        "The VOLUME SET (IN) command employs different\n" + 
        "service actions from the SCSI device.", "0000000000000000000000BE"],
    [0xBF , "VOLUME SET (OUT)",       "ShowVolumeSetOut", CDB_VolumeSetOut_Color       , 
        "The VOLUME SET (OUT) command employs different\n" + 
        "service actions from the SCSI device.", "0000000000000000000000BF"]
];
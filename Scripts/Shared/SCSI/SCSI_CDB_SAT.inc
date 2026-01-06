#
#
#  SCSI_CDB_SAT.inc
#
#  SCSI CDB definitions for SAT command set
# 
################################################################################


const SAT_CDB_Table = 
[    
    null,                                   # first item must be null for CDB definition tables
    "SCSI/ATA Transaclation Command set",   # the second item must specify the full name of command set covered by this table
    "SAT-3",                                # the third  item must specify the short name of command set covered by this table

#   OperCode, CDB_Name        , CDB_Decoder      , CDB_Color,         CDB_Tooltip #
#----------------------------------------------------------------------------------------

    
    [0xA1 , "ATA PASS-THROUGH(12)", "ShowATAPassThough12" , CDB_ATAPassThough_Color,
        "ATA PASS-THROUGH commands provide a method for:\n" + 
        "  a) an application client to transmit an ATA command to an ATA device\n" + 
        "  b) optionally, transferring data between an application client and an ATA device\n" + 
        "  c) an ATA device to transfer completion status through the SATL",
        "000000000000000000A1"],
  
    
    [0x85 , "ATA PASS-THROUGH(16)", "ShowATAPassThough16" , CDB_ATAPassThough_Color,
        "ATA PASS-THROUGH commands provide a method for:\n" + 
        "  a) an application client to transmit an ATA command to an ATA device\n" + 
        "  b) optionally, transferring data between an application client and an ATA device\n" + 
        "  c) an ATA device to transfer completion status through the SATL",
        "00000000000000000085"]
       
];
        
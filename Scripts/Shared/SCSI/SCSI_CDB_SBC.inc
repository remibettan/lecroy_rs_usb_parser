#
#  Copyright (c) 2003, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_SBC.inc
#
#  SCSI CDB definitions for SBC command set.
# 
################################################################################


const SBC_CDB_Table = 
[
     null,                     # the first item must be null for CDB definition tables
     "SCSI Block Command set", # the second item must specify the full name of command set covered by this table
     "SBC-3"                 , # the third  item must specify the short name of command set covered by this table

#   OperCode, CDB_Name        , CDB_Decoder      , CDB_Color,         CDB_Tooltip #
#---------------------------------------------------------

    [0x36 , "Obsolete", "ShowUnknownCDB" , CDB_Obsolete_Color, "Obsolete CDB", "" ],  
    [0x81 , "Obsolete", "ShowUnknownCDB" , CDB_Obsolete_Color, "Obsolete CDB", "" ],
    [0x82 , "Obsolete", "ShowUnknownCDB" , CDB_Obsolete_Color, "Obsolete CDB", "" ],     
    [0x33 , "Obsolete", "ShowUnknownCDB" , CDB_Obsolete_Color, "Obsolete CDB", "" ],         
    [0xB3 , "Obsolete", "ShowUnknownCDB" , CDB_Obsolete_Color, "Obsolete CDB", "" ], 
    [0x80 , "Obsolete", "ShowUnknownCDB" , CDB_Obsolete_Color, "Obsolete CDB", "" ],
	[0x08 , "Obsolete", "ShowUnknownCDB" , CDB_Obsolete_Color, "Obsolete CDB", "" ],
	[0x0A , "Obsolete", "ShowUnknownCDB" , CDB_Obsolete_Color, "Obsolete CDB", "" ],
	[0x52 , "Obsolete", "ShowUnknownCDB" , CDB_Obsolete_Color, "Obsolete CDB", "" ],
	[0x50 , "Obsolete", "ShowUnknownCDB" , CDB_Obsolete_Color, "Obsolete CDB", "" ],
        
    [0x04 , "FORMAT UNIT" , "ShowFormatUnit" , CDB_FormatUnit_Color , 
        "The FORMAT UNIT command formats the medium into\n" + 
        "application client addressable logical blocks\n" + 
        "per the application client defined options." ,
        "000000000004"],       
       
    [0x8B , "ORWRITE", "ShowOrWrite" , CDB_ORWrite_Color ,
        "The ORWRITE command requests that the\n" + 
        "device server read the specified logical block,\n" + 
        "transfer logical blocks from the data-out buffer,\n" + 
        "perform an OR operation with user data and \n" + 
        "write the logical blocks from that buffer.",
        "0000000000000000000000000000008B"],

    [0x34 , "PRE-FETCH(10)", "ShowPreFetch10" , CDB_PreFetch_Color , 
        "The PRE-FETCH(10) command requests that the\n" + 
        "device server transfer the specified logical\n" + 
        "blocks to the cache memory." ,
        "00000000000000000034"],
    
    [0x90 , "PRE-FETCH(16)", "ShowPreFetch16" , CDB_PreFetch_Color , 
        "The PRE-FETCH(16) command requests that the\n" + 
        "device server transfer the specified logical\n" + 
        "blocks to the cache memory.",     
        "00000000000000000000000000000090"],

    [0x1E , "PREVENT ALLW MDM RMVL", "ShowPrevAlwMdmRmvl" , CDB_PrevAlwMdmRmvl_Color,
        "The PREVENT ALLOW MEDIUM REMOVAL command\n" + 
        "requests that the  logical unit enable or disable\n" + 
        "the removal of the medium.", 
        "00000000001E" ],
    
    [0x28   , "READ(10)" , "ShowRead10" , CDB_Read_Color,
        "The READ(10) command requests that the device\n" + 
        "server transfer data to the application\n" + 
        "client.",
        "00000000000000000028"],
    
    [0xA8   , "READ(12)" , "ShowRead12" , CDB_Read_Color,
        "The READ(12) command requests that the device\n" + 
        "server transfer data to the application\n" + 
        "client.",    
        "0000000000000000000000A8"],
    
    [0x88   , "READ(16)" , "ShowRead16" , CDB_Read_Color,
        "The READ(16) command requests that the device\n" + 
        "server transfer data to the application\n" + 
        "client.",    
        "00000000000000000000000000000088"],
    
    
    [0x25   , "READ CAPACITY(10)" , "ShowReadCapacity10" , CDB_ReadCapcty_Color,
        "The READ CAPACITY (10) command provides a means\n" + 
        "for the application client to request information\n" + 
        "regarding the capacity of the block device.",
        "00000000000000000025"],
    
    [0x9E   , "READ CAPACITY(16)" , "ShowReadCapacity16" , CDB_ReadCapcty_Color,
        "The READ CAPACITY (16) command provides a means\n" + 
        "for the application client to request information\n" + 
        "regarding the capacity of the block device.",
        "0000000000000000000000000000109E"],
    
    [0x37 , "READ DEFECT DATA(10)", "ShowReadDefectData10" , CDB_ReadDefect_Color , 
        "The READ DEFECT DATA (10) command requests\n" + 
        "that the device server transfer the medium\n" + 
        "defect data to the application client.",
        "00000000000000000037"],
    
    
    [0xB7 , "READ DEFECT DATA(12)", "ShowReadDefectData12" , CDB_ReadDefect_Color , 
        "The READ DEFECT DATA (12) command requests\n" + 
        "that the device server transfer the medium\n" + 
        "defect data to the application client.",
        "0000000000000000000000B7"],
            
    [0x3E , "READ LONG(10)", "ShowReadLong10" , CDB_ReadLong_Color ,
        "The READ LONG (10) command requests that the device\n" + 
        "server transfer data from a single logical block\n" + 
        "or physical block to the data-in buffer.", 
        "0000000000000000003E"],
         
      
     # "READ LONG(16)" opcode has conflict with READ "CAPACITY(16)" ( they have 
     # different service action ) but by now we can not support them.
     # -----------------------------------------------------------------
     # [0x9E , "READ LONG(16)", "ShowReadLong16" , CDB_ReadLong_Color ,
     #   "The READ LONG (16) command requests that the device\n" + 
     #   "server transfer data from a single logical block\n" + 
     #   "or physical block to the data-in buffer.", 
     #   "0000000000000000000000000000119E"],
     # -----------------------------------------------------------------
   
    [0x07 , "REASSIGN BLOCKS", "ShowReassignBlocks" , CDB_ReassignBlcks_Color ,
        "The REASSIGN BLOCKS command requests the device\n" + 
        "server to reassign the defective logical blocks\n" + 
        "to another area on the medium set aside for this\n" + 
        "purpose.",    
        "000000000007"],                              
    
     [0x35 , "SYNC CACHE(10)", "ShowSyncCache10" , CDB_SyncCache_Color ,
        "The SYNCHRONIZE CACHE (10) command ensures that\n" + 
        "logical blocks in the cache memory, within the\n" + 
        "specified range, have their most recent data\n" + 
        "value recorded on the physical medium.",
        "00000000000000000035"],
    
    [0x91 , "SYNC CACHE(16)", "ShowSyncCache16" , CDB_SyncCache_Color ,
        "The SYNCHRONIZE CACHE (16) command ensures that\n" + 
        "logical blocks in the cache memory, within the\n" + 
        "specified range, have their most recent data\n" + 
        "value recorded on the physical medium.",
        "00000000000000000000000000000091"],
    
    [0x1B , "START STOP UNIT", "ShowStartStopUnit" , CDB_StartStopUnit_Color ,
        "The START STOP UNIT command requests that the\n" + 
        "device server enable or disable the block device\n" + 
        "for media access operations and controls certain\n" + 
        "power conditions.",
        "00000000001B"],
             
   
    [0x2F , "VERIFY(10)", "ShowVerify10" , CDB_Verify_Color ,
        "The VERIFY (10) command requests that the device\n" + 
        "server verify the specified logical block(s) on the medium.",
        "0000000000000000002F"],
    
    [0xAF , "VERIFY(12)", "ShowVerify12" , CDB_Verify_Color ,
        "The VERIFY (12) command requests that the device\n" + 
        "server verify the specified logical block(s) on the medium.",
        "0000000000000000000000AF"],
    
    [0x8F , "VERIFY(16)", "ShowVerify16" , CDB_Verify_Color ,
        "The VERIFY (16) command requests that the device\n" + 
        "server verify the specified logical block(s) on the medium.",
        "0000000000000000000000000000008F"],

    
    [0x2A   , "WRITE(10)" , "ShowWrite10" , CDB_Write_Color,
        "The WRITE (10) command requests that the device\n" + 
        "server write the data transferred by the application\n" + 
        "client to the medium.",
        "0000000000000000002A"],
    
    [0xAA   , "WRITE(12)" , "ShowWrite12" , CDB_Write_Color,
        "The WRITE (12) command requests that the device\n" + 
        "server write the data transferred by the application\n" + 
        "client to the medium.",
        "0000000000000000000000AA"],
    
    [0x8A   , "WRITE(16)" , "ShowWrite16" , CDB_Write_Color,
        "The WRITE (16) command requests that the device\n" + 
        "server write the data transferred by the application\n" + 
        "client to the medium.",
        "0000000000000000000000000000008A"],  
    
    [0x2E , "WRITE AND VERIFY(10)", "ShowWriteVerify10" , CDB_WriteVerify_Color ,
        "The WRITE AND VERIFY (10) command requests that\n" + 
        "the device server write the data transferred\n" + 
        "from the application client to the medium and\n" + 
        "then verify that the data is correctly written.",
        "0000000000000000002E"],
    
    [0xAE , "WRITE AND VERIFY(12)", "ShowWriteVerify12" , CDB_WriteVerify_Color ,
        "The WRITE AND VERIFY (12) command requests that\n" + 
        "the device server write the data transferred\n" + 
        "from the application client to the medium and\n" + 
        "then verify that the data is correctly written.",
        "0000000000000000000000AE"],
    
    [0x8E , "WRITE AND VERIFY(16)", "ShowWriteVerify16" , CDB_WriteVerify_Color ,
        "The WRITE AND VERIFY (16) command requests that\n" + 
        "the device server write the data transferred\n" + 
        "from the application client to the medium and\n" + 
        "then verify that the data is correctly written.",
        "0000000000000000000000000000008E"],

    
    [0x3F , "WRITE LONG (10)", "ShowWriteLong10" , CDB_Write_Color ,
        "The WRITE LONG (10) command requests that the\n" + 
        "device server mark a logical block or\n" + 
        "physical block as containing an error and\n" + 
        "or transfer data for to the medium.", 
        "0000000000000000003F"],

    [0x9F , "WRITE LONG (16)", "ShowWriteLong16" , CDB_Write_Color ,
        "The WRITE LONG (16) command requests that the\n" + 
        "device server mark a logical block or\n" + 
        "physical block as containing an error and\n" + 
        "or transfer data for to the medium.",   
        "0000000000000000000000000000119F"],    
    
    [0x41 , "WRITE SAME(10)", "ShowWriteSame10" , CDB_WriteSame_Color ,
        "The WRITE SAME (10) command requests that the\n" + 
        "device server write the single block of data\n" + 
        "transferred by the application client to the\n" + 
        "medium multiple times to consecutive multiple\n" + 
        "logical blocks.",
        "00000000000000000041"],
    
    [0x93 , "WRITE SAME(16)", "ShowWriteSame16" , CDB_WriteSame_Color ,
        "The WRITE SAME (16) command requests that the\n" + 
        "device server write the single block of data\n" + 
        "transferred by the application client to the\n" + 
        "medium multiple times to consecutive multiple\n" + 
        "logical blocks.",
        "00000000000000000000000000000093"],
    
    [0x53 , "XDWRITEREAD(10)", "ShowXDWriteRead10" , CDB_XDWriteRead_Color ,
        "The XDWRITEREAD (10) command requests that the\n" + 
        "target XOR the data transferred (data-out) with\n" + 
        "the data on the medium and return the resulting\n" + 
        "XOR data (data-in).", 
        "00000000000000000053"],    
    
    [0x51 , "XPWRITE(10)", "ShowXPWrite10" , CDB_XPWrite_Color ,
        "The XPWRITE(10) command requests that the\n" + 
        "target XOR the data transferred with the\n" + 
        "data on the medium and then write the XOR\n" + 
        "data to the medium.",
        "00000000000000000051"],

    [0x48 , "SANITIZE", "ShowSanitize" , CDB_Sanitize_Color ,
        "The SANITIZE command requests that the device \n" +
        "server perform a sanitize operation.",
        "00000000000000000048"],        
            
    
    # --------------- optical memory block device specific ----------
    
    [0x2C , "ERASE(10)", "ShowErase10" , CDB_Erase_Color ,
        "The ERASE (10) command requests that the\n" + 
        "device server erase the specified number\n" + 
        "of blocks starting at the specified logical\n" + 
        "block address on the medium.",
        "0000000000000000002C"],
    
    [0xAC , "ERASE(12)", "ShowErase12" , CDB_Erase_Color ,
        "The ERASE (12) command requests that the\n" + 
        "device server erase the specified number\n" + 
        "of blocks starting at the specified logical\n" + 
        "block address on the medium.",
        "0000000000000000000000AC"],
    
    
    [0x38 , "MEDIUM SCAN", "ShowMediumScan" , CDB_MediumScan_Color ,
        "The MEDIUM SCAN command requests that the device\n" + 
        "server scan the medium for a contiguous set of\n" + 
        "written or blank logical blocks.",  
        "00000000000000000038"],
    
    
    [0x29 , "READ GENERATION", "ShowReadGeneration" , CDB_Read_Color ,
        "The READ GENERATION command requests that the\n" + 
        "device server transfer to the application client\n" + 
        "the maximum generation address for the logical\n" + 
        "block specified.", 
        "00000000000000000029"], 
    
    
    [0x2D , "READ UPDATED BLOCK", "ShowReadUpdatedBlock" , CDB_Read_Color ,
        "The READ UPDATED BLOCK command requests that the\n" + 
        "device server transfer data to the application\n" + 
        "client from the specified generation and logical\n" + 
        "block.",
        "0000000000000000002D"],
  
    
    [0x3D , "UPDATE BLOCK", "ShowUpdateBlock" , CDB_UpdateBlock_Color ,
        "The UPDATE BLOCK command requests that the device\n" + 
        "server logically replace data on the medium with\n" + 
        "the data sent during the data-out buffer transfer.",
        "0000000000000000003D"]

];





#
#  Copyright (c) 2003, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_SSC.inc
#
#  SCSI CDB definitions for SSC command set.
# 
################################################################################


const SSC_CDB_Table = 
[
    null,                      # first item must be null for CDB definition tables
    "SCSI Stream Command set", # the second item must specify the full name of command set covered by this table
    "SSC-4"                  , # the third  item must specify the short name of command set covered by this table

#   OperCode, CDB_Name        , CDB_Decoder      , CDB_Color,         CDB_Tooltip #
#---------------------------------------------------------
       
    
    [0x19   , "ERASE(6)" , "ShowErase6", CDB_Erase_Color,
        "The ERASE(6) command causes part or all of\n" + 
        "the medium to be erased beginning at the\n" + 
        "current position.", "000000000019" ],
        
    [0x93 , "ERASE(16)", "ShowErase16" , CDB_Erase_Color ,
        "The ERASE (16) command  causes part or all of the\n" + 
        "volume to be erased beginning at the logical\n" + 
        "object identifier and partition specified in \n" + 
        "the command descriptor block.",
        "00000000000000000000000000000093"],
    
    [0x04 , "FORMAT MEDIUM", "ShowFormatMedium" , CDB_FormatMedium_Color ,
        "The FORMAT MEDIUM command  is used to prepare the volume\n" + 
        "for use by the logical unit.",
        "000000000004"],
            
    [0x1B   , "LOAD UNLOAD" , "ShowLoadUnload", CDB_StartStopUnit_Color,
        "The LOAD UNLOAD command requests that the\n" + 
        "logical unit enable or disable the logical\n" + 
        "unit for further operations.", "00000000001B" ],        
    
    [0x2B , "LOCATE(10)", "ShowLocate10" , CDB_Locate_Color ,
        "The LOCATE(10) command causes the logical\n" + 
        "unit to position the medium to the logical\n" + 
        "object, logical file, or logical set.", "0000000000000000002B" ],
    
    [0x92 , "LOCATE(16)", "ShowLocate16" , CDB_Locate_Color ,
        "The LOCATE(16) command causes the logical\n" + 
        "unit to position the medium to the logical\n" + 
        "object, logical file, or logical set.", "00000000000000000000000000000092" ],
         
    [0x1E , "PREVENT ALLW MDM RMVL", "ShowPrevAlwMdmRmvl" , CDB_PrevAlwMdmRmvl_Color,
        "The PREVENT ALLOW MEDIUM REMOVAL command\n" + 
        "requests that the  logical unit enable or disable\n" + 
        "the removal of the medium.", 
        "00000000001E" ], 
    
    [0x08 , "READ(6)", "ShowRead6_SSC" , CDB_Read_Color ,
        "The READ(6) command requests that the device server\n" + 
        "transfer one or more logical block(s) to the application\n" + 
		"client beginning with the next logical block.", "000000000008" ],
		
    [0x88 , "READ(16)", "ShowRead16_SSC" , CDB_Read_Color ,
        "The READ(16) command requests that the device server\n" + 
        "transfer one or more logical block(s) to the application\n" + 
		"client beginning with the next logical block.", "00000000000000000000000000000088" ],
		    
    [0x05 , "READ BLOCK LIMITS", "ShowReadBlockLimits" , CDB_Read_Color ,
        "The READ BLOCK LIMITS command requests that\n" + 
        "the READ BLOCK LIMITS data be returned.", "000000000005" ],           
    
    [0x34 , "READ POSITION", "ShowReadPosition" , CDB_Read_Color ,
        "The READ POSITION command reports the current\n" + 
        "position and provides information about logical\n" + 
        "objects contained in the object buffer.", "00000000000000000034" ],            
    
    [0x0F , "READ REVERSE(6)", "ShowReadReverse6" , CDB_Read_Color ,
        "The READ REVERSE(6) command requests that\n" + 
        "the device server transfer one or more logical\n" + 
        "block(s)to the application client beginning\n" + 
        "at the current logical position.", "00000000000F"],   
        
    [0x81 , "READ REVERSE(16)", "ShowReadReverse16" , CDB_Read_Color ,
        "The READ REVERSE(16) command requests that\n" + 
        "the device server transfer one or more logical\n" + 
        "block(s)to the application client beginning\n" + 
        "at the current logical position.", "00000000000000000000000000000081"],  
         
    [0x14 , "RCVR BUFFERED DATA", "ShowRecvrdBuffData" , CDB_RecvrdBuffData_Color ,
        "The RECOVER BUFFERED DATA command is used to recover\n" + 
        "data that has been transferred to the logical\n" + 
        "unit's buffer but has not been successfully written\n" + 
        "to the medium.", "000000000014" ],
                
    [0x01 , "REWIND", "ShowRewind" , CDB_Rewind_Color ,
        "The REWIND command causes the logical unit to\n" + 
        "position to the beginning-of-partition in the\n" + 
        "current partition.", "000000000001" ],   
    
    [0x0A   , "WRITE(6)" , "ShowSSCWrite6", CDB_Write_Color,
        "The WRITE (6) command requests that the device\n" + 
        "server write the data transferred by the application\n" + 
        "client to the medium.", "00000000000A" ],
    
    [0x8A   , "WRITE(16)" , "ShowSSCWrite16", CDB_Write_Color,
        "The WRITE (16) command requests that the device\n" + 
        "server write the data transferred by the application\n" + 
        "client to the medium.", "0000000000000000000000000000008A" ],

    [0x10   , "WRITE FILEMARKS(6)" , "ShowWriteFilemarks6", CDB_Write_Color,
        "The WRITE FILEMARKS(6) command requests that\n" + 
        "the device server write the specified number\n" + 
        "of filemarks or setmarks to the logical object\n" + 
        "identifier and partition specified in the command\n" + 
        "descriptor block.", "000000000010" ],
        
   [0x80   , "WRITE FILEMARKS(16)" , "ShowWriteFilemarks16", CDB_Write_Color,
        "The WRITE FILEMARKS(16) command requests that\n" + 
        "the device server write the specified number\n" + 
        "of filemarks or setmarks to the logical object\n" + 
        "identifier and partition specified in the command\n" + 
        "descriptor block.", "00000000000000000000000000000080" ],        
        
    
    [0x11 , "SPACE(6)", "ShowSpace6", CDB_SpaceColor ,
        "The SPACE(6) command provides a variety of\n" + 
        "positioning functions that are determined\n" + 
        "by the CODE and COUNT fields.", "000000000011" ],        
    
    [0x91 , "SPACE(16)", "ShowSpace16", CDB_SpaceColor ,
        "The SPACE(16) command provides a variety of\n" + 
        "positioning functions that are determined\n" + 
        "by the CODE and COUNT fields.", "00000000000000000000000000000091" ],
    
    [0x44 , "REPORT DNSTY SUPRT", "ShowRprtDnstySprt" , CDB_RprtDnstySprtColor ,
        "The REPORT DENSITY SUPPORT command requests that\n" + 
        "information regarding the supported densities\n" + 
        "for the logical unit be sent to the application\n" + 
        "client.", "00000000000000000044" ],
        
    [0x0B , "SET CAPACITY", "ShowSetCapacity" , CDB_SetCapacity_Color ,
        "The SET CAPACITY commands sets the available\n" + 
        "medium for the currently mounted volume to\n" + 
        "a proportion of the total capacity of that\n" + 
        "volume.", "00000000000B" ]  , 
       
    [0x13 , "VERIFY(6)", "ShowVerify6_SSC", CDB_Verify_Color ,
        "The VERIFY(6) command requests requests that the device server\n" +
        "verify one or more logical block(s) beginning at the current logical position.", "000000000013" ],                            

    [0x8F , "VERIFY(16)", "ShowVerify16_SSC", CDB_Verify_Color ,
        "The VERIFY(16) command requests requests that the device server\n" +
        "verify one or more logical block(s) beginning at the current logical position.", "0000000000000000000000000000008F" ]                            
     
];
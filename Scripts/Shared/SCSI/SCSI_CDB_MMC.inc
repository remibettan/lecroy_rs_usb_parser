#
#  Copyright (c) 2006, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_MMC.inc
#
#  SCSI CDB definitions for MMC-6 command set.
# 
################################################################################

const MMC_CDB_Table = 
[
     null,                          # first item must be null for CDB definition tables
     "SCSI Multi-Media Commands",   # the second item must specify the full name of command set covered by this table
     "MMC-6"                    ,   # the third  item must specify the short name of command set covered by this table

#   OperCode, CDB_Name          ,  CDB_Decoder      , CDB_Color,         CDB_Tooltip #
#---------------------------------------------------------

      
    [0xA1 , "BLANK"                         , "ShowBlank",				CDB_Blank_Color,
			"The BLANK command provides a re-initialization of the media\n"		+
			"to the blank state. The blanking action performed may be\n"		+
			"either Logical or physical.", "0000000000000000000000A1" ],
		
			
    [0x5B , "CLOSE TRACK/SESSION"           , "ShowCloseTrackSession",	CDB_CloseTrackSession_Color, 
			"The CLOSE TRACK/SESSION command allows closure\n"		+ 
			"of either a Logical Track or a session.", "0000000000000000005B" ],
			
    [0x04 , "FORMAT UNIT" , "ShowFormatUnit" , CDB_FormatUnit_Color , 
			"The FORMAT UNIT command formats the medium into\n" + 
			"application client addressable logical blocks\n" + 
			"per the application client defined options." ,
			"000000000004"],
        	
    [0x46 , "GET CONFIGURATION"             , "ShowGetConfiguration",	CDB_GetConfiguration_Color, 
    		"The GET CONFIGURATION command provides a Host with\n"		+ 
    		"information about the Drive capabilities; both current\n"				+
			"and potential.", "00100000000000000046" ],
    		
    		
    [0x4A , "GET EVENT STATUS NOTIFICATION" , "ShowGetEventStatNotif",	CDB_GetEventStatNotif_Color, 
			"The GET EVENT STATUS NOTIFICATION command requests that\n"		+ 
			"the Drive report events and statuses according to a\n"			+ 
			"Notification Class as a method of asynchronous notification.", "0010000000020000004A" ],
			
			
    [0xAC , "GET PERFORMANCE"               , "ShowGetPerformance",		CDB_GetPerformance_Color, 
			"The GET PERFORMANCE command provides a method for the Host to obtain\n"	+
			"detailed information about the performance of the Drive.", "0000000000000000000000AC" ],
			
	[0x12   , "INQUIRY"      , "ShowInquiryCDB"  ,  CDB_Inquiry_Color,
		    "The INQUIRY command requests that information\n" + 
			"regarding parameters of the target and a component\n" + 
			"logical unit be sent to the application client.", "000000000012" ],
			
    [0xA6 , "LOAD/UNLOAD MEDIUM"            , "ShowLoadUnloadMedium",	CDB_LoadUnloadMedium_Color, 
			"The LOAD/UNLOAD MEDIUM command requests the Drive\n"		+
			"Changer to load or unload a Disc.", "0000000000000000000000A6" ],
			
			
    [0xBD , "MECHANISM STATUS"              , "ShowMechanismStatus",	CDB_MechanismStatus_Color, 
			"The MECHANISM STATUS command requests that the Drive respond\n"	+ 
			"with the current status of the device, including any\n"			+
			"Changer Mechanism that adheres to this standard.", "0000100000000000000000BD" ],
	
    [0x55   ,"MODE SELECT(10)", "ShowModeSelect10", CDB_ModeSelect10_Color,
			"The MODE SELECT(10) command provides a means\n" + 
			"for the application client to specify medium,\n" + 
			"logical unit, or peripheral device parameters\n" + 
			"to the device server.", "00100000000000001055" ],			
			
    [0x5A   ,"MODE SENSE(10)", "ShowModeSense10"   , CDB_ModeSense10_Color,
			"The MODE SENSE(10) command provides a means\n" + 
			"for a device server to report parameters to an \n" + 
			"application client.", "0000000000000000005A" ],
       
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
                  
    [0x3C   , "READ BUFFER", "ShowReadBuffer" , CDB_ReadBuffer_Color,
			"The READ BUFFER command is used in conjunction with\n" + 
			"the WRITE BUFFER command as a diagnostic function for\n" + 
			"testing memory in the SCSI device and the integrity of the\n" + 
			"service delivery subsystem.", "0000000000000000003C" ],  
                        			
    [0x5C , "READ BUFFER CAPACITY"          , "ShowReadBufferCapacity",	CDB_ReadBufferCap_Color, 
			"The READ BUFFER CAPACITY command returns the Drive’s total\n"		+
			"length of buffer and its length of available buffer.", "000C000000000000005C" ],
			
			
    [0x25   , "READ CAPACITY" , "ShowReadCapacity10" , CDB_ReadCapcty_Color,
			"The READ CAPACITY  command provides a means\n" + 
			"for the application client to request information\n" + 
			"regarding the capacity of the block device.",
			"00000000000000000025"],
        			
    [0xBE , "READ CD"                       , "ShowReadCD",			CDB_ReadCD_Color, 
			"The READ CD command provides a method for accessing\n"			+
			"most fields within any CD sector.", "0000800200000000000000BE" ],
			
			
    [0xB9 , "READ CD MSF"                   , "ShowReadCDMsf",			CDB_ReadCD_MSF_Color, 
			"The READ CD MSF command provides a method for accessing\n"		+
			"most fields within any CD sector.", "0000800414200100000000B9" ],
			
			
    [0x51 , "READ DISC INFORMATION"         , "ShowReadDiscInfo",		CDB_ReadDiscInfo_Color, 
			"The READ DISC INFORMATION command allows the Host to request\n"		+ 
			"information about the currently mounted MM disc.", "00000000000000000051" ],
			
			
    [0xAD , "READ DISC STRUCTURE"           , "ShowReadDiscStruct",		CDB_ReadDiscStructure_Color, 
			"The READ DISC STRUCTURE command requests that the Drive\n"		+  
			"transfer data from areas on the media to the Host.", "0000080001000000000000AD" ],
			
			
    [0x23 , "READ FORMAT CAPACITIES"        , "ShowReadFmtCapacities",	CDB_ReadFormatCap_Color, 
			"The READ FORMAT CAPACITIES command allows the Host\n"		+ 
			"to request a list of the possible format\n"				+  
			"capacities for an installed writable media.", "00140000000000000023" ],
			
			
    [0xAB   , "READ MED SERIAL NUM", "ShowReadMdSerNumber" , CDB_ReadMdSerNum_Color,
			"The READ MEDIA SERIAL NUMBER command reports the\n" + 
			"media serial number reported by the device and\n" + 
			"the currently mounted media.", "0000000000000000000001AB" ],  
        			
    [0x43 , "READ TOC/PMA/ATIP"             , "ShowReadTocPmaAtip",		CDB_ReadTOC_PMA_ATIP_Color   , 
			"The READ TOC/PMA/ATIP command requests that the Drive read\n"		+  
			"data from a Table of Contents, the Program Memory Area (PMA),\n"	+ 
			"or the Absolute Time in Pre-Grove (ATIP) from CD media,\n"			+ 
			"format according to CDB parameters and transfer the\n"				+ 
			"result to the Host.", "000C0000000000000043" ],
			
			
    [0x52 , "READ TRACK INFORMATION"        , "ShowReadTrackInfo",		CDB_ReadTrackInfo_Color      , 
			"The READ TRACK INFORMATION command provides information\n"		+ 
			"about a Logical Track.", "00000000000000000052" ],
			
			
    [0x58 , "REPAIR TRACK"                  , "ShowRepairTrack",		CDB_RepairTrack_Color        , 
			"The REPAIR TRACK command shall fill multiple ECC block lengths\n"		+ 
			"with data from beginning of the damaged sector of the ECC block\n"		+ 
			"and ending with a link field. The recovery is intended\n"				+
			"only to allow the track to become writable again.", "00000000000000000058" ],
			
			
    [0xA4 , "REPORT KEY"                    , "ShowReportKey",			CDB_ReportKey_Color          , 
			"The REPORT KEY command requests the start of the authentication\n"		+ 
			"process and provides data necessary for authentication and for\n"		+ 
			"generating a Bus Key for protected transfers between the Host and Drive.", "0000080000000000000000A4" ],
			
    [0xA0   , "REPORT LUNS", "ShowRprtLUNs" , CDB_RprtLUNs_Color,
			"The REPORT LUNS command requests that the\n" + 
			"peripheral device logical unit inventory be sent to\n" + 
			"the application client.", "0000000000000000000000A0" ],
  
    [0x03   , "REQUEST SENSE", "ShowRequestSense" , CDB_RequestSense_Color,
			"The REPORT LUNS command requests that the\n" + 
			"peripheral device logical unit inventory be sent to\n" + 
			"the application client.", "000000000003" ],   
               			
    [0x53 , "RESERVE TRACK"                 , "ShowReserveTrack",		CDB_ReserveTrack_Color       , 
			"The RESERVE TRACK command allows reservation of disc\n"		+ 
			"space for a Logical Track.", "00000000000000000053" ],
			
    [0xA2   , "SECURITY PROTOCOL IN", "ShowSecurityProtocolIn", CDB_SecProtocolIn_Color,
			"The SECURITY PROTOCOL IN command is used to\n" + 
			"retrieve security protocol information or the results \n" + 
			"of one or more SECURITY PROTOCOL OUT commands.", "0000000000000000000000A2" ],  
    
    [0xB5   , "SECURITY PROTOCOL OUT", "ShowSecurityProtocolOut", CDB_SecProtocolOut_Color,
			"The SECURITY PROTOCOL OUT command is used to\n" + 
			"send data to the Drive.", "0000000000000000000000B5" ],  
         
    [0x2B   ,"SEEK(10)", "ShowSeek10", CDB_SecProtocolOut_Color,
			"SEEK(10) command requests that the Drive seek\n" + 
			"to the specified logical block address.", "0000000000000000002B" ],
			         			
    [0x5D , "SEND CUE SHEET"                , "ShowSendCueSheet",		CDB_SendCueSheet_Color       , 
			"The SEND CUE SHEET command refers to a Session-at-once recording\n"		+ 
			"where it begins with the Lead-in and continuing through the Lead-out.\n"	+ 
			"Only user data is sent with the write commands, so a guide structure\n"	+  
			"is required by the Drive in order to control the recording process.\n"		+ 
			"This guide structure is called the cue sheet. The cue sheet\n"				+  
			"is constructed in the Host and sent to the Drive.", "0000000000000000005D" ],
			
			
    [0xBF , "SEND DISC STRUCTURE"           , "ShowSendDiscStruct",		CDB_SendDiscStructure_Color  , 
			"The SEND DISC STRUCTURE command provides a means for the Host\n"	+ 
			"to transfer DISC STRUCTURE data to the Drive.", "0000100004000000000000BF" ],
			
			
    [0xA3 , "SEND KEY"                      , "ShowSendKey",			CDB_SendKey_Color            , 
			"The SEND KEY command provides data necessary for\n"	+ 
			"authentication and for generating a Bus Key for\n"		+
			"protected data transfers between the Host and Drive.", "0001100000000000000000A3" ],
			
			
    [0x54 , "SEND OPC INFORMATION"          , "ShowSendOpcInfo",		CDB_SendOPC_Info_Color       , 
			"The SEND OPC INFORMATION command is used to specify the\n"		+  
			"Optimum Power Calibration (OPC) values to the Drive for\n"		+ 
			"the currently mounted medium disc.", "00080000000000000054" ],
			
			
    [0xBB , "SET CD SPEED"                  , "ShowSetCDSpeed",			CDB_SetCDSpeed_Color         , 
			"The SET CD SPEED command provides a Host with a method\n"		+
			"to select a preferred physical speed for CD media.", "000000000000FFFFFFFF00BB" ],
			
			
    [0xA7 , "SET READ AHEAD"                , "ShowSetReadAhead",		CDB_SetReadAhead_Color       ,
			"The SET READ AHEAD command requests that the Drive perform\n"			+ 
			"Read Ahead Caching operations from the Read-Ahead Logical Block\n"		+
			"Address once the Drive encounters the Trigger LBA during its\n"		+  
			"internal read-ahead cacheing operation.", "0000000000000000000000A7" ],
			
			
    [0xB6 , "SET STREAMING"                 , "ShowSetStreaming",		CDB_SetStreaming_Color       , 
			"The SET STREAMING command provides the Host with a method\n"	+  
			"to communicate requirements for Drive performance.", "001C000000000000000000B6"],
        
    [0x1B , "START STOP UNIT", "ShowStartStopUnit" , CDB_StartStopUnit_Color ,
			"The START STOP UNIT command requests that the\n" + 
			"device server enable or disable the block device\n" + 
			"for media access operations and controls certain\n" + 
			"power conditions.",
			"00000000001B"],        
			
    [0x35 , "SYNC CACHE", "ShowSyncCache10" , CDB_SyncCache_Color ,
			"The SYNCHRONIZE CACHE command ensures that\n" + 
			"logical blocks in the cache memory, within the\n" + 
			"specified range, have their most recent data\n" + 
			"value recorded on the physical medium.",
			"00000000000000000035"],		
			
    [0x00   , "TEST UNIT READY" , "ShowTstUntReady" , CDB_TstUntReady_Color,
			"The TEST UNIT READY command provides\n" + 
			"a means to check if the logical unit is ready.\n" + 
			"This is not a request for a self-test.", "000000000000" ],	
			
    [0x2F , "VERIFY(10)", "ShowVerify10MMC" , CDB_Verify_Color ,
			"The VERIFY (10) command requests that the device\n" + 
			"server verify the specified logical block(s) on the medium.",
			"0000000000000000002F"],
			
    [0x2A   , "WRITE(10)" , "ShowWrite10MMC" , CDB_Write_Color,
			"The WRITE (10) command requests that the device\n" + 
			"server write the data transferred by the application\n" + 
			"client to the medium.",
			"0000000000000000002A"],
    
    [0xAA   , "WRITE(12)" , "ShowWrite12MMC" , CDB_Write_Color,
			"The WRITE (12) command requests that the device\n" + 
			"server write the data transferred by the application\n" + 
			"client to the medium.",
			"0000000000000000000000AA"],	
			
    [0x2E , "WRITE AND VERIFY(10)", "ShowWriteVerify10" , CDB_WriteVerify_Color ,
			"The WRITE AND VERIFY (10) command requests that\n" + 
			"the device server write the data transferred\n" + 
			"from the application client to the medium and\n" + 
			"then verify that the data is correctly written.",
			"0000000000000000002E"],	
			
    [0x3B   , "WRITE BUFFER" , "ShowWriteBuffer" , CDB_WriteBuffer_Color,
			"The WRITE BUFFER command is used as a diagnostic\n" + 
			"function for testing logical unit memory in the target SCSI\n" + 
			"device and the integrity of the service delivery subsystem.", "0000000000000000003B"]													
];
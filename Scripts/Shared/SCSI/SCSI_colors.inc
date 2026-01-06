#
#  Copyright (c) 2006, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_colors.inc
#
#  Color definitions for SCSI decoders.
#


###############################################################################
#                               Common Colors                                 #
###############################################################################

# common color used for SCSI fields
const SCSI_Color     = RGB (  5, 145, 145 );



###############################################################################
#                        SCSI Attribute Colors                                #          
###############################################################################
const SCSI_LUN_Color        = RGB ( 92,  47, 183 );
const SCSI_STATUS_Color     = RGB (255, 217, 179 );
const SCSI_SenseData_Color  = RGB (227, 254, 165 );


 
###############################################################################
#                        SCSI CDB (SPC-4) Colors                              #          
###############################################################################
const EXTCDB_Common_Color       = RGB (128, 128, 255 );
const CDB_Obsolete_Color        = RGB (  5, 145, 145 );

const CDB_AccsCtrlIn_Color      = RGB (226, 226, 240 );
const CDB_AccsCtrlOut_Color     = RGB (227, 254, 165 );

const CDB_ExtndCpy_Color        = RGB (128, 128, 255 );
const CDB_Inquiry_Color         = RGB (253, 108,  38 );
const CDB_LogSelect_Color       = RGB ( 10,  88,  65 );
const CDB_LogSense_Color        = RGB (104, 199, 162 );
const CDB_ModeSelect6_Color     = RGB (135, 135,   0 );
const CDB_ModeSelect10_Color    = RGB ( 95,  95,   0 );
const CDB_ModeSense6_Color      = RGB (187, 137,   0 );
const CDB_ModeSense10_Color     = RGB (148, 108,   0 );

const CDB_MoveMedium_Color      = RGB (205, 145, 145 );
const CDB_MoveMdmAttch_Color    = RGB (205, 100, 100 );
const CDB_PersistResIn_Color    = RGB ( 77, 150, 255 );
const CDB_PersistResOut_Color   = RGB (  9, 141, 181 );
const CDB_RcvCpyRslts_Color     = RGB (194, 152,  20 );
const CDB_RcvDiagRslts_Color    = RGB (  0,  95, 181 );
const CDB_ReadBuffer_Color      = RGB (227, 254, 165 );

const CDB_ReadMdSerNum_Color    = RGB (189, 184, 180 );
const CDB_ReadAttr_Color        = RGB (227, 254, 165 );

const CDB_ReadElmtStatus_Color  = RGB (195, 223,   0 );
const CDB_ReadElmtStAttch_Color = RGB (118, 136,   0 );
const CDB_Release10_Color       = RGB (203, 201, 181 );
const CDB_Release6_Color        = RGB (177, 176, 173 );
const CDB_RequestSense_Color    = RGB (104, 199, 162 );
const CDB_Reserve10_Color       = RGB (179, 179, 217 );
const CDB_Reserve6_Color        = RGB (121, 121, 188 );
const CDB_RprtDevID_Color       = RGB (  0,  30, 255 );
const CDB_RprtLUNs_Color        = RGB (110,  45, 145 );
const CDB_SendDiag_Color        = RGB (  0,  95, 181 );
const CDB_Send_Color            = RGB (115, 220, 255 );
const CDB_MntnceIn_Color        = RGB (  0,  95, 181 );
const CDB_MntnceOut_Color       = RGB (  0,  30, 255 );
const CDB_TstUntReady_Color     = RGB (255, 188,  94 );
const CDB_WriteBuffer_Color     = RGB (115, 220, 255 );
const CDB_ChangeAliases_Color   = RGB (80 , 220, 255 );
const CDB_SecProtocolIn_Color	= RGB (100 , 220, 200 );
const CDB_SecProtocolOut_Color	= RGB (150 , 180, 150 );
const CDB_ATAPassThough_Color	= RGB (190 , 24, 149 );



###############################################################################
#                        SCSI CDB (SBC-3) Colors                              #          
###############################################################################

const CDB_Erase_Color           = RGB (175,  94,   3 );
const CDB_FormatUnit_Color      = RGB (203, 201, 181 );
const CDB_LockUnlockCache_Color = RGB (244, 175, 198 );
const CDB_MediumScan_Color      = RGB (255, 188,  94 );
const CDB_PreFetch_Color        = RGB (175,  94,   3 );
const CDB_Read_Color            = RGB ( 10,  88,  65 );
const CDB_ReadCapcty_Color      = RGB ( 59, 255, 111 );
const CDB_ReadDefect_Color      = RGB (166, 180, 183 );
const CDB_ReadLong_Color        = RGB ( 10,  88,  65 );
const CDB_ReassignBlcks_Color   = RGB (128, 128, 255 );
const CDB_Rebuild_Color         = RGB (141,  94, 107 );
const CDB_Seek10_Color          = RGB (179, 179, 217 );
const CDB_SetLimits_Color       = RGB (253, 108,  38 );
const CDB_StartStopUnit_Color   = RGB (110,  45, 145 );
const CDB_SyncCache_Color       = RGB ( 87,  87, 255 );
const CDB_UpdateBlock_Color     = RGB (222, 190, 228 );
const CDB_Verify_Color          = RGB ( 61,  83,  61 );
const CDB_Write_Color           = RGB (115, 220, 255 );
const CDB_WriteVerify_Color     = RGB (  0, 110, 132 );
const CDB_WriteSame_Color       = RGB (  0, 191, 255 );
const CDB_XDRead_Color          = RGB ( 10,  88,  20 );
const CDB_XDWrite_Color         = RGB ( 77, 150, 255 );
const CDB_XDWriteRead_Color     = RGB ( 21, 127, 160 );
const CDB_XPWrite_Color         = RGB (  0, 101, 246 );
const CDB_ORWrite_Color         = RGB (120, 46 , 246 );
const CDB_PrevAlwMdmRmvl_Color  = RGB (187,  48,   0 );
const CDB_Sanitize_Color        = RGB (174,  25,  76 );

###############################################################################
#                        SCSI CDB (SMC-3) Colors                              #          
###############################################################################

const CDB_InitElmntSts_Color   = RGB (253, 108,  38 );
const CDB_InitElmntStsWRange_Color = RGB (153, 208,  140 );
const CDB_XchMedium_Color      = RGB (111, 101,  80 );
const CDB_ReadAttrib_Color     = RGB ( 14,  71,   0 );
const CDB_ReqVolElAddr_Color   = RGB (180, 180, 217 );
const CDB_SendVolTag_Color     = RGB (  0,  37,  72 );
const CDB_SendWriteAttr_Color  = RGB ( 46,  46, 246 );
const CDB_PosToElemnt_Color    = RGB (179, 179, 217 );
const CDB_ReqDataTrnsferElmntInq_Color = RGB (110, 140, 190 );
const CDB_RepVolTypeSupprtd_Color = RGB (210, 40, 130 );


###############################################################################
#                        SCSI CDB (SSC-4) Colors                              #          
###############################################################################

const CDB_Rewind_Color         = RGB (  0,  37,  72 );
const CDB_Locate_Color         = RGB (253, 165,  68 );
const CDB_SpaceColor           = RGB (110,  45, 145 );
const CDB_RprtDnstySprtColor   = RGB (174, 171, 140 );
const CDB_FormatMedium_Color   = RGB (220,  71, 200 );
const CDB_RecvrdBuffData_Color = RGB (150, 100, 52  );
const CDB_SetCapacity_Color	   = RGB (220, 150, 140 );	

###############################################################################
#                        SCSI CDB (MMC-6) Colors                              #          
###############################################################################

const CDB_Blank_Color             = RGB ( 115, 196, 116 );
const CDB_CloseTrackSession_Color = RGB (  01, 274, 236 );  
const CDB_GetConfiguration_Color  = RGB ( 116,  70,  16 );  
const CDB_GetEventStatNotif_Color = RGB (  47, 186, 110 );  
const CDB_GetPerformance_Color    = RGB (  87,  42, 165 );  
const CDB_LoadUnloadMedium_Color  = RGB ( 108, 176,  01 );  
const CDB_MechanismStatus_Color   = RGB (  78,  64, 125 );  
const CDB_ReadBufferCap_Color     = RGB ( 106, 100, 181 );  
const CDB_ReadCD_Color            = RGB (  96,  42, 250 );  
const CDB_ReadCD_MSF_Color        = RGB (  63, 221,  72 );  
const CDB_ReadDiscInfo_Color      = RGB (  36, 148, 170 );  
const CDB_ReadDiscStructure_Color = RGB ( 165,  77,  64 );  
const CDB_ReadFormatCap_Color     = RGB ( 290, 123,  76 );  
const CDB_ReadTOC_PMA_ATIP_Color  = RGB (  50,  98, 117 );  
const CDB_ReadTrackInfo_Color     = RGB ( 136, 248,  50 );  
const CDB_RepairTrack_Color       = RGB ( 212, 164, 230 );  
const CDB_ReportKey_Color         = RGB ( 146,  50, 191 );  
const CDB_ReserveTrack_Color      = RGB ( 227, 234,  60 );  
const CDB_SendCueSheet_Color      = RGB (  97, 185, 164 );  
const CDB_SendDiscStructure_Color = RGB ( 107,  15,  23 );  
const CDB_SendKey_Color           = RGB ( 240, 176, 151 );  
const CDB_SendOPC_Info_Color      = RGB ( 107,  43,  75 );  
const CDB_SetCDSpeed_Color        = RGB ( 180,  92, 134 );  
const CDB_SetReadAhead_Color      = RGB (  56, 179,  87 );  
const CDB_SetStreaming_Color      = RGB ( 214, 158, 201 );  
                                           
###############################################################################
#                        SCSI CDB (SCC-2) Colors                              #          
###############################################################################

const CDB_RedundancyGroupIn_Color = RGB ( 252, 252, 120 );
const CDB_RedundancyGroupOut_Color= RGB (  51, 204, 255 );
const CDB_SpareIn_Color           = RGB ( 131, 211,  90 );
const CDB_SpareOut_Color          = RGB (  88, 128,  80 );
const CDB_VolumeSetIn_Color       = RGB (  79,  77, 190 );
const CDB_VolumeSetOut_Color      = RGB ( 153, 102,  40 );


###############################################################################
#                        SCSI CDB (SES-2) Colors                              #          
###############################################################################

const CDB_SES_COMMAND_Color       = RGB (   0,   0,   0 ); 

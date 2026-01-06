################################################################################
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_defs.inc
#
#  SCSI definitions.
#
#  NOTE: THE ORDER OF INCLUDES IS IMPORTANT HERE - 
#        DON'T CHANGE IT UNLESS YOU ARE FULLY AWARE OF CONSEQUENSES
#        (SOME CONSTANTS MUST BE DECLARED BEFORE THEIR FIRST USAGE)
################################################################################

# SCCI Tabular Cell IDs
%include "SharedTabularCellId.inc"

# SCSI colors
%include "SCSI_colors.inc"


# SCSI LUN
%include "SCSI_LUN.inc"


# SCSI Status
%include "SCSI_Status.inc"


# SCSI Sense Data
%include "SCSI_SenseData.inc"

# SCSI Mode Sense
%include "SCSI_ModeSense.inc"

# SCSI Inquiry
%include "SCSI_Inquiry.inc"

# Command set CDB definitions
%include "SCSI_CDB_SPC.inc"
%include "SCSI_CDB_SBC.inc"
%include "SCSI_CDB_SMC.inc"
%include "SCSI_CDB_SSC.inc"
%include "SCSI_CDB_MMC.inc"
%include "SCSI_CDB_SCC.inc"
%include "SCSI_CDB_SES.inc"
%include "SCSI_CDB_SAT.inc"

#
# Add more files with command set CDB definitions here
#



# Command set Extended CDB definitions
%include "SCSI_ExCDB_SBC.inc"

#
# Add more files with command set Extended CDB definitions here
#



# Global tables of SCSI CDB/Extended CDB definitions.
%include "SCSI_CDB_defs.inc"


# SCSI Extended CDB decoding support
%include "SCSI_ExtCDB_defs.inc"


# SCSI CDB decoding support
%include "SCSI_CDB.inc"


# SCSI CDB Decoders
%include "SCSI_CDB_ExtndCpy.inc"
%include "SCSI_CDB_Inquiry.inc"
%include "SCSI_CDB_LogSelect.inc"
%include "SCSI_CDB_LogSense.inc"
%include "SCSI_CDB_ModeSelect6.inc"
%include "SCSI_CDB_ModeSelect10.inc"
%include "SCSI_CDB_ModeSense6.inc"
%include "SCSI_CDB_ModeSense10.inc"
%include "SCSI_CDB_PersstRsrvIN.inc"
%include "SCSI_CDB_PersstRsrvOUT.inc"
%include "SCSI_CDB_PrevAlwMdmRmvl.inc"
%include "SCSI_CDB_ReadBuffer.inc"
%include "SCSI_CDB_RcvCpyRslts.inc"
%include "SCSI_CDB_RcvDiagRslts.inc"
%include "SCSI_CDB_RepLUN_RSense.inc"
%include "SCSI_CDB_SendDiag.inc"
%include "SCSI_CDB_TstUntReady.inc"
%include "SCSI_CDB_WriteBuffer.inc"
%include "SCSI_CDB_Rebuild32.inc"
%include "SCSI_CDB_Send_Rcv.inc"
%include "SCSI_CDB_ReadWrite.inc"
%include "SCSI_CDB_ReadCapacity.inc"
%include "SCSI_CDB_FormatUnit.inc"
%include "SCSI_CDB_PreFetch.inc"
%include "SCSI_CDB_ReadDefectData.inc"
%include "SCSI_CDB_ReadLngReassgn.inc"
%include "SCSI_CDB_SeekSetLimits.inc"
%include "SCSI_CDB_StartStopUnit.inc"
%include "SCSI_CDB_SyncCache.inc"
%include "SCSI_CDB_Verify.inc"
%include "SCSI_CDB_WriteVrfy.inc"
%include "SCSI_CDB_WriteSame.inc"
%include "SCSI_CDB_XDReadWrite.inc"
%include "SCSI_CDB_XPWrite.inc"
%include "SCSI_CDB_Erase.inc"
%include "SCSI_CDB_MediumScan.inc"
%include "SCSI_CDB_UpdateBlock.inc"
%include "SCSI_CDB_XchMedium.inc"
%include "SCSI_CDB_ReadAttribute.inc"
%include "SCSI_CDB_ReqVolElmntAddr.inc"
%include "SCSI_CDB_SendVolTag.inc"
%include "SCSI_CDB_WriteAttrib.inc"
%include "SCSI_CDB_InitElmtStatus.inc"
%include "SCSI_CDB_WriteFileMarks.inc"
%include "SCSI_CDB_LoadUnload.inc"
%include "SCSI_CDB_Rewind.inc"
%include "SCSI_CDB_ReadBlockLmts.inc"
%include "SCSI_CDB_Locate.inc"
%include "SCSI_CDB_ReadPosition.inc"
%include "SCSI_CDB_AccsCtrlIn.inc"
%include "SCSI_CDB_AccsCtrlOut.inc"
%include "SCSI_CDB_MaintenanceOut.inc"
%include "SCSI_CDB_Space.inc"
%include "SCSI_CDB_RprtDnstySprt.inc"
%include "SCSI_CDB_ReadMdSerialNum.inc"
%include "SCSI_CDB_MaintenanceIn.inc"
%include "SCSI_CDB_PositionToElmnt.inc"
%include "SCSI_CDB_RedundancyGroupIn.inc"
%include "SCSI_CDB_SpareIn.inc"
%include "SCSI_CDB_SpareOut.inc"
%include "SCSI_CDB_VolumeSetIn.inc"
%include "SCSI_CDB_VolumeSetOut.inc"
%include "SCSI_CDB_RedundancyGroupOut.inc"
%include "SCSI_CDB_Blank.inc"
%include "SCSI_CDB_CloseTrackSession.inc"
%include "SCSI_CDB_GetConfiguration.inc"
%include "SCSI_CDB_GetEventStatNotif.inc"
%include "SCSI_CDB_GetPerformance.inc"
%include "SCSI_CDB_LoadUnloadMedium.inc"
%include "SCSI_CDB_MechanismStatus.inc"
%include "SCSI_CDB_ReadBufferCapacity.inc"
%include "SCSI_CDB_ReadCD.inc"
%include "SCSI_CDB_ReadCDMsf.inc"
%include "SCSI_CDB_ReadDiscInfo.inc"
%include "SCSI_CDB_ReadDiscStruct.inc"
%include "SCSI_CDB_ReadFmtCapacities.inc"
%include "SCSI_CDB_ReadTocPmaAtip.inc"
%include "SCSI_CDB_ReadTrackInfo.inc"
%include "SCSI_CDB_RepairTrack.inc"
%include "SCSI_CDB_ReportKey.inc"
%include "SCSI_CDB_ReserveTrack.inc"
%include "SCSI_CDB_SendCueSheet.inc"
%include "SCSI_CDB_SendDiscStruct.inc"
%include "SCSI_CDB_SendKey.inc"
%include "SCSI_CDB_SendOpcInfo.inc"
%include "SCSI_CDB_SetCDSpeed.inc"
%include "SCSI_CDB_SetReadAhead.inc"
%include "SCSI_CDB_SetStreaming.inc"
%include "SCSI_CDB_SecPrtcle.inc"
%include "SCSI_CDB_OpenCloseImpExp.inc"
%include "SCSI_CDB_RepVolTypeSupprtd.inc"
%include "SCSI_CDB_FormatMedium.inc"
%include "SCSI_CDB_RcvrdBuffData.inc"
%include "SCSI_CDB_SetCapacity.inc"
%include "SCSI_CDB_ATAPassThrough.inc"
%include "SCSI_CDB_SANITIZE.inc"

#%include ""
#%include ""
#%include ""
#%include ""
#%include ""
#%include ""
#%include ""
#%include ""
#%include ""
#%include ""
#%include ""
#%include ""


#---------------------------- Common SCSI functions -------------------------------



#----------------------------------------------------------------------------------
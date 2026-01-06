#
#  Copyright (c) 2003, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_SPC.inc
#
#  SCSI CDB definitions for SPC command set.
# 
################################################################################


const SPC_CDB_Table = 
[    
    null,                        # first item must be null for CDB definition tables
    "SCSI Primary Command set",  # the second item must specify the full name of command set covered by this table
    "SPC-4"                   ,  # the third  item must specify the short name of command set covered by this table

#   OperCode, CDB_Name        , CDB_Decoder      , CDB_Color,         CDB_Tooltip #
#---------------------------------------------------------
    
    [0x18   , "Obsolete", "ShowUnknownCDB" , CDB_Obsolete_Color, "Obsolete CDB", "" ],
    [0x39   , "Obsolete", "ShowUnknownCDB" , CDB_Obsolete_Color, "Obsolete CDB", "" ],
    [0x3A   , "Obsolete", "ShowUnknownCDB" , CDB_Obsolete_Color, "Obsolete CDB", "" ],
    [0x40   , "Obsolete", "ShowUnknownCDB" , CDB_Obsolete_Color, "Obsolete CDB", "" ],   
    
    
    [0x7F   , "EXTENDED CDB" , "ShowUnknownCDB" , CDB_WriteBuffer_Color,
        "EXTENDED CDB with OPERATION CODE : 7Fh\n", "" ],
    
    
    [0x86   , "ACCESS CONTROL IN" , "ShowAccsCtrlIn", CDB_AccsCtrlIn_Color,
        "The ACCESS CONTROL IN command is used to obtain\n" + 
        "information about the access controls that are\n" + 
        "active within the access controls coordinator\n" + 
        "and to perform other access control functions.", "00000000000000000000000000000086" ],
        
        
    [0x87   , "ACCESS CONTROL OUT" , "ShowAccsCtrlOut", CDB_AccsCtrlOut_Color,
        "The ACCESS CONTROL OUT command is used to request\n" + 
        "service actions by the access controls coordinator\n" + 
        "to limit or grant access to the logical units\n" + 
        "by initiator ports.", "00000000000000000000000000000087" ],
    

    [0x83   , "EXTENDED COPY" , "ShowExtndCpyCDB", CDB_ExtndCpy_Color,
        "The EXTENDED COPY command provides a means\n" + 
        "to copy data from one set of logical units to another set\n" + 
        "or to the same set of logical units.", "00000000000000000000000000000083" ],
    
         
    [0x12   , "INQUIRY"      , "ShowInquiryCDB"  ,  CDB_Inquiry_Color,
        "The INQUIRY command requests that information\n" + 
        "regarding parameters of the target and a component\n" + 
        "logical unit be sent to the application client.", "000000000012" ],
        
    [0x4C   , "LOG SELECT"   , "ShowLogSelect"   ,  CDB_LogSelect_Color,
        "The LOG SELECT command provides a means for\n" + 
        "an application client to manage statistical information\n" + 
        "maintained by the device about the device or its logical units.", "0000000000000000004C" ],
        
    
    [0x4D   , "LOG SENSE"   , "ShowLogSense"     ,  CDB_LogSense_Color,
        "The LOG SENSE command provides a means for\n" + 
        "the application client to retrieve statistical or other\n" + 
        "operational information maintained by the device\n" + 
        "about the device or its logical units.", "0000000000000000004D" ],
    
    [0xA3   , "MANAGEMENT PROTOCOL IN", "ShowMaintenanceIn" , CDB_MntnceIn_Color,
        "The MANAGEMENT PROTOCOL IN command requests the device\n" + 
        "server to return management protocol information\n" +
		"or the results of one or more MANAGEMENT PROTOCOL OUT\n" +
		"commands.", "0000000000000000000000A3" ],        
    
    [0xA4   , "MANAGEMENT PROTOCOL OUT" , "ShowMaintenanceOut" , CDB_MntnceOut_Color,
        "The MANAGEMENT PROTOCOL OUT command is used to send\n"+
		"data to the logical unit. The data sent specifies one\n"+
		"or more operations to be performed by the logical unit.", "0000000000000000000000A4" ],
        
    
    [0x15   , "MODE SELECT(6)", "ShowModeSelect6",  CDB_ModeSelect6_Color,
        "The MODE SELECT(6) command provides a means\n" + 
        "for the application client to specify medium,\n" + 
        "logical unit, or peripheral device parameters\n" + 
        "to the device server.", "000000000000000008000000000C00001015" ],   
        
        
        
    [0x55   ,"MODE SELECT(10)", "ShowModeSelect10", CDB_ModeSelect10_Color,
        "The MODE SELECT(10) command provides a means\n" + 
        "for the application client to specify medium,\n" + 
        "logical unit, or peripheral device parameters\n" + 
        "to the device server.", "00000000000000001055" ],
    
        
    [0x1A   ,"MODE SENSE(6)", "ShowModeSense6"   , CDB_ModeSense6_Color,
        "The MODE SENSE(6) command provides a means\n" + 
        "for a device server to report parameters to an \n" + 
        "application client.", "00000000001A" ],
    
        
    [0x5A   ,"MODE SENSE(10)", "ShowModeSense10"   , CDB_ModeSense10_Color,
        "The MODE SENSE(10) command provides a means\n" + 
        "for a device server to report parameters to an \n" + 
        "application client.", "0000000000000000005A" ],    
    
    
    [0x5E   , "PERSISTENT RESERVE IN", "ShowPersstRsrvIN" , CDB_PersistResIn_Color,
        "The PERSISTENT RESERVE IN command is used to\n" + 
        "obtain information about persistent reservations and\n" + 
        "reservation keys that are active within a device server.", "0000000000000000005E" ],
        
    
    [0x5F   , "PERSISTENT RESERVE OUT", "ShowPersstRsrvOUT", CDB_PersistResOut_Color,
        "The PERSISTENT RESERVE OUT command is used to\n" + 
        "request service actions that reserve a logical unit or element\n" + 
        "for the exclusive or shared use of a particular initiator.", "0000000000000000005F" ],    

    [0xA2   , "SECURITY PROTOCOL IN", "ShowSecurityProtocolIn", CDB_SecProtocolIn_Color,
        "The SECURITY PROTOCOL IN command is used to\n" + 
        "retrieve security protocol information or the results \n" + 
        "of one or more SECURITY PROTOCOL OUT commands.", "0000000000000000000000A2" ],  
    
    [0xB5   , "SECURITY PROTOCOL OUT", "ShowSecurityProtocolOut", CDB_SecProtocolOut_Color,
        "The SECURITY PROTOCOL OUT command is used to\n" + 
        "CDB_SecProtocolIn_Color.", "0000000000000000000000B5" ],  
    
    [0x3C   , "READ BUFFER", "ShowReadBuffer" , CDB_ReadBuffer_Color,
        "The READ BUFFER command is used in conjunction with\n" + 
        "the WRITE BUFFER command as a diagnostic function for\n" + 
        "testing memory in the SCSI device and the integrity of the\n" + 
        "service delivery subsystem.", "0000000000000000003C" ],  
        
     
    [0xAB   , "READ MED SERIAL NUM", "ShowReadMdSerNumber" , CDB_ReadMdSerNum_Color,
        "The READ MEDIA SERIAL NUMBER command reports the\n" + 
        "media serial number reported by the device and\n" + 
        "the currently mounted media.", "0000000000000000000001AB" ],  
        
    [0x8C , "READ ATTRIBUTE", "ShowReadAttribCDB" , CDB_ReadAttrib_Color ,
        "The READ ATTRIBUTE command allows an application\n" + 
        "client to read attribute values to Medium Auxillary\n" + 
        "Memory (MAM) and also to discover what MAM exists\n" + 
        "at the device server.", "0000000000000000000000000000008C" ],
    
    [0x84   , "RECEIVE COPY RESULTS", "ShowRcvCpyRslts"   , CDB_RcvCpyRslts_Color,
        "The RECEIVE COPY RESULTS command provides\n" + 
        "a means for the application client to receive information\n" + 
        "about the copy manager or the results of a previous or\n" + 
        "current EXTENDED COPY command.", "00000000000000000000000000000084" ],
    
    [0x1C   , "RECEIVE DIAG RESULTS", "ShowRcvDiagRslts" , CDB_RcvDiagRslts_Color,
        "The RECEIVE DIAGNOSTIC RESULTS command requests\n" + 
        "that data be sent to the application client after completion of\n" + 
        "a SEND DIAGNOSTIC command.", "00000000001C" ],   
    
    
    [0xA0   , "REPORT LUNS", "ShowRprtLUNs" , CDB_RprtLUNs_Color,
        "The REPORT LUNS command requests that the\n" + 
        "peripheral device logical unit inventory be sent to\n" + 
        "the application client.", "0000000000000000000000A0" ],
    
    [0x03   , "REQUEST SENSE", "ShowRequestSense" , CDB_RequestSense_Color,
        "The REPORT LUNS command requests that the\n" + 
        "peripheral device logical unit inventory be sent to\n" + 
        "the application client.", "000000000003" ],    
        
    
    [0x0A   , "SEND" , "ShowSend" , CDB_Send_Color,
        "The SEND command requests that the device\n" + 
        "server transfer data from the initiator.", "00000000000A" ],
            
    
    [0x1D   , "SEND DIAGNOSTIC" , "ShowSendDiag" , CDB_SendDiag_Color,
        "The SEND DIAGNOSTIC command requests the device\n" + 
        "server to perform diagnostic operations on the target, on\n" + 
        "the logical unit, or on both.", "00000000201D" ],   
    
    
   
    [0x00   , "TEST UNIT READY" , "ShowTstUntReady" , CDB_TstUntReady_Color,
        "The TEST UNIT READY command provides\n" + 
        "a means to check if the logical unit is ready.\n" + 
        "This is not a request for a self-test.", "000000000000" ],
        
    [0x8D , "WRITE ATTRIBUTE", "ShowWriteAttribCDB" , CDB_WriteAttrib_Color ,
        "The WRITE ATTRIBUTE command allows an application\n" + 
        "client to write attributes to medium Auxillary Memory (MAM).", "0000000000000000000000000000008D" ],    
    
    [0x3B   , "WRITE BUFFER" , "ShowWriteBuffer" , CDB_WriteBuffer_Color,
        "The WRITE BUFFER command is used as a diagnostic\n" + 
        "function for testing logical unit memory in the target SCSI\n" + 
        "device and the integrity of the service delivery subsystem.", "0000000000000000003B"]
    
];
        
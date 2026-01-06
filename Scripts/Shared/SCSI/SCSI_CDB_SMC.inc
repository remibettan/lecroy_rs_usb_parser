#
#  Copyright (c) 2003, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_SMC.inc
#
#  SCSI CDB definitions for SMC command set.
# 
################################################################################


const SMC_CDB_Table = 
[
     null,                             # first item must be null for CDB definition tables
     "SCSI Media Changer Command set", # the second item must specify the full name of command set covered by this table
     "SMC-3"                         , # the third  item must specify the short name of command set covered by this table

#   OperCode, CDB_Name        , CDB_Decoder      , CDB_Color,         CDB_Tooltip #
#---------------------------------------------------------
    [0xB4   , "Obsolete", "ShowUnknownCDB" , CDB_Obsolete_Color, "Obsolete CDB", "" ],
    [0x57   , "Obsolete", "ShowUnknownCDB" , CDB_Obsolete_Color, "Obsolete CDB", "" ],        
    [0x17   , "Obsolete", "ShowUnknownCDB" , CDB_Obsolete_Color, "Obsolete CDB", "" ],
    [0x56   , "Obsolete", "ShowUnknownCDB" , CDB_Obsolete_Color, "Obsolete CDB", "" ],  
    [0x16   , "Obsolete", "ShowUnknownCDB" , CDB_Obsolete_Color, "Obsolete CDB", "" ],        
    [0xA5   , "Obsolete", "ShowUnknownCDB" , CDB_Obsolete_Color, "Obsolete CDB", "" ],          
    [0xB8   , "Obsolete", "ShowUnknownCDB" , CDB_Obsolete_Color, "Obsolete CDB", "" ],          
        
    [0xA6 , "EXCHANGE MEDIUM", "ShowXchMediumCDB" , CDB_XchMedium_Color,
        "The EXCHANGE MEDIUM command provides a means to\n" + 
        "exchange the volume in the source element address,\n" + 
        "with the volume located at a destination element\n" + 
        "address.", "0000000000000000000000A6" ],
     
    [0x07 , "INIT ELEMENT STATUS", "ShowInitElmntStatus" , CDB_InitElmntSts_Color,
        "The INITIALIZE ELEMENT STATUS command shall\n" + 
        "cause the media changer to check all assigned\n" + 
        "element addresses for volume and any other\n" + 
        "status relevant to that element address.", "000000000007" ],
          
    [0x37 , "INIT ELEMENT STATUS WITH RANGE", "ShowInitElmntStatusWRange" , CDB_InitElmntStsWRange_Color,
        "The INITIALIZE ELEMENT STATUS WITH RANGE command shall\n" + 
        "cause the media changer to check the specified\n" + 
        "elements for volume status and any other\n" + 
        "relevant status.", "00000000000000000037" ],                           
    
    [0x1B   , "OPEN/CLOSE IMPORT/EXPORT ELEMENT "  , "ShowOpenCloseImpExp" , CDB_OpenCloseImpExp_Color,
        "The OPEN/CLOSE IMPORT/EXPORT ELEMENT  command provides a method for the application\n" + 
        "move a volume from a source element to a destination client to change the open/closed\n" + 
        "state of the specified import/export element.", "00000000001B" ],                 
    
    [0x1E , "PREVENT ALLW MDM RMVL", "ShowPrevAlwMdmRmvl" , CDB_PrevAlwMdmRmvl_Color,
        "The PREVENT ALLOW MEDIUM REMOVAL command\n" + 
        "requests that the  logical unit enable or disable\n" + 
        "the removal of the medium.", 
        "00000000001E" ],                                     
    
    [0x8C , "READ ATTRIBUTE", "ShowReadAttribCDB" , CDB_ReadAttrib_Color ,
        "The READ ATTRIBUTE command allows an application\n" + 
        "client to read attribute values to Medium Auxillary\n" + 
        "Memory (MAM) and also to discover what MAM exists\n" + 
        "at the device server.", "0000000000000000000000000000008C" ],       

    [0x44  , "REPORT VOLUME TYPES SUPPORTED", "ShowRepVolTypeSupprtd" , CDB_RepVolTypeSupprtd_Color,
        "The  REPORT VOLUME TYPES SUPPORTED command requests that information regarding the \n" + 
        "supported volume types for the device be sent to the application client.", "00000000000000000044" ],
            
    [0xA3  , "REQUEST DATA TRANSFER ELEMENT INQUIRY", "ShowReqDataTrnsferElmntInq" , CDB_ReqDataTrnsferElmntInq_Color,
        "The  REQUEST DATA TRANSFER ELEMENT INQUIRY command requests that the\n" + 
        "device server return to the application client INQUIRY data.", "0000000000000000000006A3" ],
        
    [0xB5 , "REQST VOL ELMNT ADDR", "ShowReqVolElmntAddrCDB" , CDB_ReqVolElAddr_Color ,
        "The REQUEST VOLUME ELEMENT ADDRESS command is\n" + 
        "used to transfer the results of a SEND VOLUME\n" + 
        "TAG command.", "0000000000000000000000B5" ],   
                
    [0xB6 , "SEND VOLUME TAG", "ShowSendVolTagCDB" , CDB_SendVolTag_Color ,
        "The SEND VOLUME TAG command transfers a volume tag\n" + 
        "template to be used for a search of existing volume\n" + 
        "tag information or new volume tag information for\n" + 
        "one media changer element address.", "0000000000000000000000B6" ],         

    
    [0x8D , "WRITE ATTRIBUTE", "ShowWriteAttribCDB" , CDB_SendWriteAttr_Color ,
        "The WRITE ATTRIBUTE command allows an\n" + 
        "application client to write attribute\n" + 
        "values to Medium Auxiliary Memory (MAM).", "0000000000000000000000000000008D"]
        
];
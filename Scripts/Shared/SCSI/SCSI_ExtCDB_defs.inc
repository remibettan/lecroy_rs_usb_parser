#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_ExtCDB_defs.inc
#
#  SCSI Extended CDB definitions.
#
#  Decoders for extended commands should parse additional CDB payload 
#  after SERVICE ACTION.
################################################################################




#-------------------------------- Common functions ------------------------------------

#############################################################
#        Function shows common part of extended CDBs.       #
#############################################################

ShowExtCDBCommonPart( cdb_len )
{    
    ShowControlByte();
        
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);
    
    PLReservedCheck(3);
    AddBlockPLCell("GROUP NUMBER", Format("0x%02X", NextNBits_(5)), "GROUP NUMBER field.");
    
    #------------------------- ADDITIONAL CDB LENGTH -----------------------------    
    val = NextNBits_(8);
    error = null;
    tooltip = "";               
         
    if( (cdb_len - 8)  != val  ) #cdb_len for XDWriteExtended64 must be 64 but since the additional cdb_length is still 0x18 
								 #we can use this code to check the error (32 - 8 = 24 (0x18))
    {
        error = _ERROR;
        tooltip  = Format("ADDITIONAL CDB LENGTH(%d) not correct !!!\n", val);
        tooltip += Format("It should be equal to %d.", cdb_len - 8) ;
    }
    
    AddBlockPLCell("Add CDB Len", Format("%d", val ), 
    "The ADDITIONAL CDB LENGTH field indicates\n" +
    "the number of additional CDB bytes." + AddWarningTooltip(tooltip), error );
     
    #----------------------------------------------------------------------------- 
     
    service_actn = NextNBits_(16);
    tooltip =  "The SERVICE ACTION field indicates the action\n" + 
    "being requested by the application client.";
    
    AddBlockPLCell("SERVICE ACTION", Format("0x%04X", service_actn ), tooltip );
    
     # Special cell for SERVICE ACTION code in collapsed state 
     if( !IsExpanded() && !VS[COLLAPSED] && (CDB_Name == "EXTENDED") )
     {
        AddCell( "Service Action", Format("0x%04X", service_actn ), tooltip, EXTCDB_Common_Color );
        #AddCell( "SERVICE ACTION", null, tooltip, SCSI_Color , _MONOFIELD );
        #AddCell( Format("0x%04X", service_actn ), null, null, CDB_Color , _MONOFIELD );
     }
}



ShowExtCDBUnknown( cdb_len )
{      
	if( !AddSpecDataBlockVS( cdb_len - 10, VS ))  # Check if some project-specific ShowSpecDataBlockVS hook handled call        
		ShowDataBlockVS( cdb_len - 10, VS ); 
}
 
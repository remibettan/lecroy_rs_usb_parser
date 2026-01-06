#
#  Copyright (c) 2010, LeCroy. - All Rights Reserved
#
#  SCSI_CDB_SetReadAhead.inc
#
#  SCSI CDB SET READ AHEAD Command decoder functions
################################################################################


ShowSetReadAhead()
{
 
    PLReservedCheck(8);
    
	
	val = NextNBits_(32);
	AddBlockPLCell( "Trigger Logical Block Address", Format ("0x%08X", val), 
					"Trigger Logical Block Address field.\n\n"		+
					"Identify the last sector that shall be cached during\n"		+ 
					"the current read-ahead cacheing process." );
	
	
	val = NextNBits_(32);
	AddBlockPLCell( "Read Ahead Logical Block Address", Format ("0x%08X", val), 
					"Read Ahead Logical Block Address field.\n\n"	+
					"Identify the first sector at which cacheing shall continue.");
	
	PLReservedCheck(8);

}
#
#  Copyright (c) 2010, LeCroy. - All Rights Reserved
#
#  SCSI_CDB_CloseTrackSession.inc
#
#  SCSI CDB CLOSE TRACK SESSION Command decoder functions
################################################################################


ShowCloseTrackSession()
{
 
    PLReservedCheck(7);
    
    val = NextNBits_(1);
	AddBlockPLCell(	"IMMED", Format ("0x%X", val), 
					"IMMED field.\n\n"		+
					"Bit 0: Return status when the operation is completed.\n"	+ 
					"Bit 1: Return status once the operation begins." );
		
	PLReservedCheck(5);
	
	val = NextNBits_(3);
	AddBlockPLCell(	"Close Function", Format ("0x%X", val), 
					"Close Function field.\n\n"	+
					"The Close Functions are specific to disc type."); 
	
	PLReservedCheck(8);
	
	val = NextNBits_(16);
	AddBlockPLCell(	"Logical Track Number", Format ("0x%04X", val), 
					"Logical Track Number field.\n\n" );
	
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	
}




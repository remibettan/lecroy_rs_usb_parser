#
#  Copyright (c) 2010, LeCroy. - All Rights Reserved
#
#  SCSI_CDB_ReadBufferCapacity.inc
#
#  SCSI CDB READ BUFFER CAPACITY Command decoder functions
################################################################################


ShowReadBufferCapacity()
{
 
    PLReservedCheck(7);
    
	
	val = NextNBits_(1);
	AddBlockPLCell( "Block", Format ("0x%X", val), 
					"Block field.\n\n"		+
					"Bit 0: Buffer length information report as bytes.\n" + 
					"Bit 1: Buffer length information report as blocks.");
	
	
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	
	ShowAllocLen(16);
	
	
}
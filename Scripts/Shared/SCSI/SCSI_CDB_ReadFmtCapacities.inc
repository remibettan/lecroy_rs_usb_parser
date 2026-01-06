#
#  Copyright (c) 2010, LeCroy. - All Rights Reserved
#
#  SCSI_CDB_ReadFmtCapacities.inc
#
#  SCSI CDB READ FORMAT CAPACITIES Command decoder functions
################################################################################


ShowReadFmtCapacities()
{
 
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	ShowAllocLen(16);
	
}
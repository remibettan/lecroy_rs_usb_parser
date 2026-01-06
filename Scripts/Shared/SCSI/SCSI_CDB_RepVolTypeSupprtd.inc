#
#  Copyright (c) 2010, LeCroy - All Rights Reserved
#
#  SCSI_CDB_RepVolTypeSupprtd.inc
#
#  SCSI CDB REPORT VOLUME TYPES SUPPORTED Command decoder functions
################################################################################


ShowRepVolTypeSupprtd()
{
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	ShowAllocLen(16);
}
#
#  Copyright (c) 2010, LeCroy. - All Rights Reserved
#
#  SCSI_CDB_MechanismStatus.inc
#
#  SCSI CDB MECHANISM STATUS Command decoder functions
################################################################################


ShowMechanismStatus()
{
 
 	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
    PLReservedCheck(8);
	
	ShowAllocLen(16);
   
	PLReservedCheck(8);
    
}
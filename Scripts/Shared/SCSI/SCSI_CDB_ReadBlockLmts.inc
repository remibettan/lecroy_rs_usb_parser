#
#  Copyright (c) 2003, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_ReadBlockLmts.inc
#
#  SCSI CDB READ BLOCK LIMITS decoder functions
################################################################################




ShowReadBlockLimits()
{
    PLReservedCheck(8);            
    PLReservedCheck(8);         
    PLReservedCheck(8);
    PLReservedCheck(8);    
}
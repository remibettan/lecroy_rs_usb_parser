#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_ExtndCpy.inc
#
#  SCSI CDB EXTEND COPY Command decoder functions
################################################################################


ShowExtndCpyCDB()
{
     for(i = 0; i < 9; i++)
        PLReservedCheck(8);
     
     ShowParamListLen();     
     PLReservedCheck(8);
}
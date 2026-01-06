#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_SeekSetLimits.inc
#
#  SCSI CDB Seek10 and SetLimits Command decoder functions
#
################################################################################



ShowSeek10( )
{
    PLReservedCheck(8);
    ShowLBA(32);
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);
}

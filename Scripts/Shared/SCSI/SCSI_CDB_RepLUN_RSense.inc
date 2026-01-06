#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_RepLUN_RSense.inc
#
#  SCSI CDB REPORT LUNS and REQUEST SENSE Command decoder functions
################################################################################


ShowRprtLUNs()
{
    PLReservedCheck(8);
    
    AddBlockPLCell("SELECT REPORT", Format("0x%04X", NextNBits_(8)), "SELECT REPORT field.", FieldColor, [_CELLINFO, 0, options ]);
    
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);    
    
    ShowAllocLen   (32);
    PLReservedCheck(8);    
}



ShowRequestSense()
{
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);    
    ShowAllocLen   (8);   
}
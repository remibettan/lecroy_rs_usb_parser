#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_RprtDevID.inc
#
#  SCSI CDB REPORT DEVICE IDENTIFIER Command decoder functions
################################################################################


ShowRepDevID()
{
    PLReservedCheck(8);
    PLReservedCheck(8);
    
    AddBlockPLCell("Restricted", GetFld16H(), "The Restricted field.");    
    
    ShowAllocLen(32);
    
    PLReservedCheck(6);
    AddBlockPLCell("Restricted", GetBitStr(), "The Restricted field.");
    PLReservedCheck(1);    
        
}

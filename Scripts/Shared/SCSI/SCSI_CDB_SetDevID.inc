#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_SetDevID.inc
#
#  SCSI CDB SET DEVICE IDENTIFIER Command decoder functions
################################################################################


ShowSetDevID()
{        
    PLReservedCheck(8);
    PLReservedCheck(8);
    
    AddBlockPLCell("Restricted", Format("0x%04X", NextNBits_(16)), "Restricted field.");
    
    ShowParamListLen(32);
    PLReservedCheck(6);
    
    AddBlockPLCell("Restricted", GetBitStr(), "Restricted bit field.");
    PLReservedCheck(1);
}

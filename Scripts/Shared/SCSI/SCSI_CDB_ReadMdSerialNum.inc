#
#  Copyright (c) 2003, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_ReadMdSerialNum.inc
#
#  SCSI CDB READ MEDIA SERIAL NUMBER decoder functions
################################################################################


ShowReadMdSerNumber()
{
    PLReservedCheck(3);
    
    AddBlockPLCell( "SERVICE ACTION", GetFldH(5), "The SERVICE ACTION field." , FieldColor, [_CELLINFO, 1]);
    
    PLReservedCheck(32);    
    
    ShowAllocLen(32);  

    PLReservedCheck(8);    
}
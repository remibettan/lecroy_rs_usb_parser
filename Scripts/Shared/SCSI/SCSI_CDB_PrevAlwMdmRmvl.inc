#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_PrevAlwMdmRmvl.inc
#
#  SCSI CDB PREVENT ALLOW MEDIUM REMOVAL Command decoder functions
################################################################################


ShowPrevAlwMdmRmvl()
{
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(6);
         
   options = [ ["set", 1], ["Not set", 0] ];
   
   AddBlockPLCell("Persistent", GetBitStr(), "A Persistent bit field.", FieldColor, [_CELLINFO, 0, options ]);
    
   AddBlockPLCell("Prevent " , GetBitStr(), "A Prevent  bit field.", FieldColor, [_CELLINFO, 0, options ]);
    
}

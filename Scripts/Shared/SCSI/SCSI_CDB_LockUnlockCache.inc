#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_LockUnlockCache.inc
#
#  SCSI CDB Lock Unlock Cache Commands decoder functions
################################################################################



ShowLockUnlockCache10()
{
    PLReservedCheck(6);
    
    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("LOCK", GetBitStr(), 
    "A LOCK bit of zero indicates that all logical blocks\n" + 
    "in the specified range that are currently locked into\n" + 
    "the cache memory shall be unlocked, but may not be\n" + 
    "removed. A LOCK bit of one indicates that any logical\n" + 
    "block in the specified range that is currently present\n" + 
    "in the cache memory shall be locked into cache memory.", FieldColor, [_CELLINFO, 0, options ]);
    
    ShowRELADR();
    ShowLBA(32);
    
    PLReservedCheck(8);
    
    AddBlockPLCell("NumOfBlocks", Format("%u", NextNBits_(16)),
    "The NUMBER OF BLOCKS field specifies the total\n" + 
    "number of contiguous logical blocks within the\n" + 
    "range. A NUMBER OF BLOCKS field of zero indicates\n" + 
    "that all remaining logical blocks on the block\n" + 
    "device shall be within the range.");  
}



ShowLockUnlockCache16()
{
    PLReservedCheck(6);
    
    options = [ ["set", 1], ["Not set", 0] ];
    
    AddBlockPLCell("LOCK", GetBitStr(), 
    "A LOCK bit of zero indicates that all logical blocks\n" + 
    "in the specified range that are currently locked into\n" + 
    "the cache memory shall be unlocked, but may not be\n" + 
    "removed. A LOCK bit of one indicates that any logical\n" + 
    "block in the specified range that is currently present\n" + 
    "in the cache memory shall be locked into cache memory.", FieldColor, [_CELLINFO, 0, options ]);
    
    ShowRELADR();
    ShowLBA(64);    
    
    AddBlockPLCell("NumOfBlocks", Format("%u", NextNBits_(32)),
    "The NUMBER OF BLOCKS field specifies the total\n" + 
    "number of contiguous logical blocks within the\n" + 
    "range. A NUMBER OF BLOCKS field of zero indicates\n" + 
    "that all remaining logical blocks on the block\n" + 
    "device shall be within the range.");  
    
    PLReservedCheck(8);
}





#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_SyncCache.inc
#
#  SCSI CDB Synchronize Cache Command decoder functions
#
################################################################################



ShowSyncCache10( )
{
    PLReservedCheck(5);    
    
    options = [ ["set", 1], ["Not set", 0] ];
    
    AddBlockPLCell("SYNC_NV", GetBitStr(), "SYNC_NV bit field.", FieldColor, [_CELLINFO, 0, options ]);
    AddBlockPLCell("IMMED", GetBitStr(), "An immediate (IMMED) bit field.", FieldColor, [_CELLINFO, 0, options ]);
    
    AddBlockPLCell("Obsolete", GetBitStr(), "Obsoleted field.", FieldColor, [_CELLINFO, 0, options ]);
   
    ShowLBA(32);
    
    PLReservedCheck(3);
    
    AddBlockPLCell("GROUP NUMBER", Format("0x%02X", NextNBits_(5)), "GROUP NUMBER field.");  
    
    AddBlockPLCell("NumOfBlocks" , Format("%u", NextNBits_(16)),
		"The NUMBER OF BLOCKS field specifies the total\n" + 
		"number of contiguous logical blocks within the\n" + 
		"range. A number of blocks of zero indicates that\n" + 
		"all remaining logical blocks on the block device\n" + 
		"shall be within the range.");    
}



ShowSyncCache16( )
{
    PLReservedCheck(6);    
    
    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("IMMED", GetBitStr(), "An immediate (IMMED) bit field.", FieldColor, [_CELLINFO, 0, options ]);
    ShowRELADR();    
    
    ShowLBA(64);    
    
    AddBlockPLCell("NumOfBlocks" , Format("%u", NextNBits_(32)),
    "The NUMBER OF BLOCKS field specifies the total\n" + 
    "number of contiguous logical blocks within the\n" + 
    "range. A number of blocks of zero indicates that\n" + 
    "all remaining logical blocks on the block device\n" + 
    "shall be within the range.");
    
    PLReservedCheck(8);
}




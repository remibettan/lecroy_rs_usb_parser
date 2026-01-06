#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_WriteSame.inc
#
#  SCSI CDB WriteSame Commands decoder functions
################################################################################



ShowWriteSame10()
{
    ShowWriteSameCommon();

    PLReservedCheck( 3 );
    
    AddBlockPLCell("GROUP NUMBER", Format("0x%02X", NextNBits_(5)), "GROUP NUMBER field."); 

    AddBlockPLCell("NumOfLogicalBlocks", Format("%u", NextNBits_(16)),
    "The NUMBER OF LOGICAL BLOCKS field specifies the\n" + 
    "number of contiguous logical blocks to be\n" + 
    "written. A NUMBER OF BLOCKS field of zero\n" + 
    "requests that all the remaining logical\n" + 
    "blocks on the medium be written." );    
}



ShowWriteSame16()
{
    ShowWriteSameCommon(64,1);

    AddBlockPLCell("NumOfLogicalBlocks", Format("%u", NextNBits_(32)),
    "The NUMBER OF LOGICAL BLOCKS field specifies the\n" + 
    "number of contiguous logical blocks to be\n" + 
    "written. A NUMBER OF BLOCKS field of zero\n" + 
    "requests that all the remaining logical\n" + 
    "blocks on the medium be written." );
    
    PLReservedCheck( 3 );
    
    AddBlockPLCell("GROUP NUMBER", Format("0x%02X", NextNBits_(5)), "GROUP NUMBER field."); 
}

ShowWriteSame32()
{
    ShowWriteSameCommon(64,1,1);
    
    AddBlockPLCell("EXPECTED INITIAL LOGICAL BLOCK REFERENCE TAG", Format("0x%8X", NextNBits_(32)), "EXPECTED INITIAL LOGICAL BLOCK REFERENCE TAG field." );   
    AddBlockPLCell("EXPECTED LOGICAL BLOCK APPLICATION TAG", Format("0x%4X", NextNBits_(16)), "EXPECTED LOGICAL BLOCK APPLICATION TAG field." ); 
    AddBlockPLCell("LOGICAL BLOCK APPLICATION TAG MASK", Format("0x%4X", NextNBits_(16)), "LOGICAL BLOCK APPLICATION TAG MASK field." ); 
    
    AddBlockPLCell("NumOfLogicalBlocks", Format("%u", NextNBits_(32)),
    "The NUMBER OF LOGICAL BLOCKS field specifies the\n" + 
    "number of contiguous logical blocks to be\n" + 
    "written. A NUMBER OF BLOCKS field of zero\n" + 
    "requests that all the remaining logical\n" + 
    "blocks on the medium be written." );
}

ShowWriteSameCommon( lba_len , reserved, bit_32_cmd)
{   
    AddBlockPLCell("WRPROTECT", Format("0x%1X", NextNBits_(3)), "WRPROTECT field." );  
    PLReservedCheck( 2 );

    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("PBDATA", GetBitStr(), "Physical block data (PBDATA) bit field.", FieldColor, [_CELLINFO, 0, options ]);
    
    AddBlockPLCell("LBDATA", GetBitStr(), "Logical block data (LBDATA) bit field.", FieldColor, [_CELLINFO, 0, options ]);

    if(reserved == null) #obsoleted in Read 10 and Read 12
        AddBlockPLCell("Obsolete", GetBitStr(), "Obsolete field.", FieldColor, [_CELLINFO, 0, options ]); 
    else	                  
	PLReservedCheck( 1 );

    if(bit_32_cmd != null) # used when we must add a reserved field as row to 32 bit operation
        PLReservedCheck( 8 );  

    if( lba_len == null ) lba_len = 32;   
    ShowLBA( lba_len );
}

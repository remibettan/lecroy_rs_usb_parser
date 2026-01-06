#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_ReadLngReassgn.inc
#
#  SCSI CDB Read Long and Reassign Commands decoder functions
################################################################################



ShowReadLong10()
{
    PLReservedCheck(5);    
    
    options = [ ["set", 1], ["Not set", 0] ];
    
    AddBlockPLCell("PBLOCK", GetBitStr(), "A PBLOCK (PBLOCK) bit field.", FieldColor, [_CELLINFO, 0, options ]);

    AddBlockPLCell("CORRCT", GetBitStr(), "A correct (CORRCT) bit field.", FieldColor, [_CELLINFO, 0, options ]);
    ShowRELADR();
    ShowLBA(32);
    
    PLReservedCheck(8);    
    ShowTransferLen(16);
}

ShowReadLong16()
{
    PLReservedCheck(3);    
    
    serv_action = NextNBits_(5);
    AddPayLoadCell( "SERVICE ACTION", Format ("0x%0X", serv_action), "SERVICE ACTION");

    ShowLBA(64);
    PLReservedCheck( 8 );
    PLReservedCheck( 8 );
 
    ShowTransferLen(16);

    PLReservedCheck(6); 
    AddBlockPLCell("PBLOCK", GetBitStr(), "A PBLOCK (PBLOCK) bit field.", FieldColor, [_CELLINFO, 0, options ]);
 
    AddBlockPLCell("CORRCT", GetBitStr(), "A correct (CORRCT) bit field.", FieldColor, [_CELLINFO, 0, options ]);
}

ShowReassignBlocks()
{
    PLReservedCheck(6);    
    
    options = [ ["set", 1], ["Not set", 0] ];
    
    AddBlockPLCell("LONGLBA", GetBitStr(),
    "A long LBA (LONGLBA) bit of zero requests that\n" + 
    "four byte defect descriptors be returned in the\n" + 
    "REASSIGN BLOCKS defect list. A LONGLBA bit of\n" + 
    "one requests that eight byte defect descriptors\n" + 
    "be returned in the REASSIGN BLOCKS defect list.", FieldColor, [_CELLINFO, 0, options ]);
    
    AddBlockPLCell("LONGLIST", GetBitStr(), "A LONGLIST bit field.", FieldColor, [_CELLINFO, 0, options ]);
    
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);
}


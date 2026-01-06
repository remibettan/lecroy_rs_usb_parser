#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_XPWrite.inc
#
#  SCSI CDB XP Write Commands decoder functions
################################################################################



ShowXPWrite10()
{
    PLReservedCheck( 3 );
    ShowDPO();        
    ShowFUA();
    PLReservedCheck( 1 );    
    
    options = [ ["set", 1], ["Not set", 0] ];   
    AddBlockPLCell("FUA_NV", GetBitStr(), "non-volatile cache field.", FieldColor, [_CELLINFO, 0, options ]);    
    AddBlockPLCell("XORPINFO", GetBitStr(), "XORPINFO field." , FieldColor, [_CELLINFO, 0, options ]);
    
    ShowLBA(32);
    PLReservedCheck( 3 );
    AddBlockPLCell("GROUP NUMBER", Format("0x%02X", NextNBits_(5)), "GROUP NUMBER field.");

    ShowTransferLen( 16 );
}




ShowXPWrite32()
{    
    PLReservedCheck( 3 );
    ShowDPO();        
    ShowFUA();
    PLReservedCheck( 1 );    
    
    options = [ ["set", 1], ["Not set", 0] ];   
    AddBlockPLCell("FUA_NV", GetBitStr(), "non-volatile cache field.", FieldColor, [_CELLINFO, 0, options ]);    
    AddBlockPLCell("XORPINFO", GetBitStr(), "XORPINFO field." , FieldColor, [_CELLINFO, 0, options ]);
    
    PLReservedCheck( 8 ); 

    ShowLBA( 64 );
    PLReservedCheck( 32 );
    PLReservedCheck( 32 );
   
    ShowTransferLen( 32 );
}

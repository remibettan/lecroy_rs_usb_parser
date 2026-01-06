#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_XDReadWrite.inc
#
#  SCSI CDB XD Read and Write Commands decoder functions
################################################################################


#----------------------------- READ Commands -----------------------------------

ShowXDRead10()
{
    PLReservedCheck( 8 );
    ShowLBA(32);
    PLReservedCheck( 3 );

    AddBlockPLCell("GROUP NUMBER", Format("0x%02X", NextNBits_(5)), "GROUP NUMBER field.");

    ShowTransferLen( 16 );
}




ShowXDRead32()
{    
    PLReservedCheck( 7 );

    options = [ ["set", 1], ["Not set", 0] ];
    
    AddBlockPLCell("XORPINFO", GetBitStr(), "XORPINFO field." , FieldColor, [_CELLINFO, 0, options ]);

    PLReservedCheck( 8 );
    
    ShowLBA(64);
    PLReservedCheck( 32 );
    PLReservedCheck( 32 );
    
    ShowTransferLen( 32 );
}





#-------------------------------- WRITE Commands -----------------------------------

ShowXDWrite10()
{
    ShowXDWriteCommon();

    PLReservedCheck( 3 );    
    AddBlockPLCell("GROUP NUMBER", Format("0x%02X", NextNBits_(5)), "GROUP NUMBER field.");

    ShowTransferLen( 16 );
}


ShowXDWrite32()
{
    ShowXDWriteCommon( 64 );
    PLReservedCheck( 32 );
    PLReservedCheck( 32 );
    
    ShowTransferLen( 32 );   
}



ShowXDWriteRead10()
{
    ShowXDWriteCommon(null, 1);
    
    PLReservedCheck( 3 );    
    AddBlockPLCell("GROUP NUMBER", Format("0x%02X", NextNBits_(5)), "GROUP NUMBER field.");

    ShowTransferLen( 16 );
}


ShowXDWriteRead32()
{
    ShowXDWriteCommon( 64 , 1);
    PLReservedCheck( 32 );
    PLReservedCheck( 32 );
    
    ShowTransferLen( 32 );   
}


ShowXDWriteExtended32()
{
    PLReservedCheck( 1 );
    PLReservedCheck( 2 );
    ShowDPO();    
    ShowFUA();    
    ShowDisableWrite();    
    ShowPortControl();
    
    ShowSecondaryAddr();    
    ShowLBA(64);    
    ShowSecondaryLBA(64);    
    ShowTransferLen( 32 );   
}



ShowXDWriteExtended64()
{
    PLReservedCheck( 3 );
    ShowDPO();    
    ShowFUA();    
    ShowDisableWrite();    
    ShowPortControl();
    
    PLReservedCheck( 8 );
    
    AddBlockPLCell("Secondary ADDR Descr", Format("0x%08X", NextNBits_(32)),
    "The SECONDARY ADDRESS DESCRIPTOR field contains\n" + 
    "the logical unit identifier of the logical unit\n" + 
    "that will receive the XOR data transfer.");            
       
    ShowLBA(64);
    ShowSecondaryLBA(64);
    
    ShowTransferLen( 32 );
}




#------------------------------ READ and WRITE CDB Common Functions ----------------
ShowXDWriteCommon( lba_len , xor_or_reserved)
{
    AddBlockPLCell("WRPROTECT", Format("0x%1X", NextNBits_(3)), "WRPROTECT field." ); 

    ShowDPO();    
    ShowFUA();
    
    options = [ ["set", 1], ["Not set", 0] ];
    
    AddBlockPLCell("DISABLE WRITE", GetBitStr(), 
    "A DISABLE WRITE bit of zero indicates that the\n" + 
    "data transferred from the initiator shall be\n" + 
    "written to the medium after the XOR operation\n" + 
    "is complete. A DISABLE WRITE bit of one indicates\n" + 
    "that the data shall not be written to the medium.", FieldColor, [_CELLINFO, 0, options ]);
    
    AddBlockPLCell("FUA_NV", GetBitStr(), "non-volatile cache field.", FieldColor, [_CELLINFO, 0, options ]);
 
    if(xor_or_reserved)	
        AddBlockPLCell("XORPINFO", GetBitStr(), "XORPINFO field.", FieldColor, [_CELLINFO, 0, options ]);
    else
        PLReservedCheck( 1 );
    
    if( lba_len > 32 ) PLReservedCheck( 8 );
    
    if( lba_len == null ) lba_len = 32;
    ShowLBA( lba_len );
}




ShowDisableWrite()
{
	options = [ ["set", 1], ["Not set", 0] ];
	
    AddBlockPLCell("DISABLE WRITE", GetBitStr(), 
    "A DISABLE WRITE bit of zero indicates that the\n" + 
    "data transferred from the initiator shall be\n" + 
    "written to the medium after the XOR operation\n" + 
    "is complete. A DISABLE WRITE bit of one indicates\n" + 
    "that the data shall not be written to the medium.", FieldColor, [_CELLINFO, 0, options ]);
}



ShowSecondaryLBA( lba_len )
{    
    len = lba_len;
    if( !lba_len || lba_len > 32 ) len = 32;    
    
    
    str = Format("0x%08X", NextNBits(len));    
    if( lba_len > 32 ) str += Format(" %08X", NextNBits(lba_len - len));
    
    if( !lba_len ) lba_len = 32;
    IncFieldOffset( lba_len );
    
    AddBlockPLCell("Secondary LBA", str, "SECONDARY LOGICAL BLOCK ADDRESS field.");
}



ShowSecondaryAddr()
{
     AddBlockPLCell("Secondary ADDR", Format("0x%02X", NextNBits_(8)),
     "The SECONDARY ADDRESS field contains the target\n" + 
     "identifier of the target that will receive the\n" + 
     "XOR data transfer." );    
}
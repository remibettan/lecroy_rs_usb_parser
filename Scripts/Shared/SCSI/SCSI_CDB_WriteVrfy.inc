#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_WriteVrfy.inc
#
#  SCSI CDB Write and Verify Commands decoder functions
################################################################################


ShowWriteVerify10()
{
    ShowWriteVerifyCommon();
    PLReservedCheck(3);       

    AddBlockPLCell("GROUP NUMBER", Format("0x%02X", NextNBits_(5)), "GROUP NUMBER field.");
    
    ShowTransferLen( 16 );
}


ShowWriteVerify12()
{
    ShowWriteVerifyCommon();        

    ShowTransferLen();

    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("Restricted for MMC-4", GetBitStr(), "Restricted for MMC-4 field.", FieldColor, [_CELLINFO, 0, options ]);

    PLReservedCheck(2);  
    
    AddBlockPLCell("GROUP NUMBER", Format("0x%02X", NextNBits_(5)), "GROUP NUMBER field.");
}


ShowWriteVerify16()
{
    ShowWriteVerifyCommon( 64 , 1);
        
    ShowTransferLen();
    options = [ ["set", 1], ["Not set", 0] ];
    
    AddBlockPLCell("Restricted for MMC-4", GetBitStr(), "Restricted for MMC-4 field.", FieldColor, [_CELLINFO, 0, options ]);

    PLReservedCheck(2);  
    
    AddBlockPLCell("GROUP NUMBER", Format("0x%02X", NextNBits_(5)), "GROUP NUMBER field.");
}

ShowWriteVerify32()
{

    ShowWriteVerifyCommon(64, 1, 1);

    AddBlockPLCell("EXPECTED INITIAL LOGICAL BLOCK REFERENCE TAG", Format("0x%8X", NextNBits_(32)), "EXPECTED INITIAL LOGICAL BLOCK REFERENCE TAG field." );   
    AddBlockPLCell("EXPECTED LOGICAL BLOCK APPLICATION TAG", Format("0x%4X", NextNBits_(16)), "EXPECTED LOGICAL BLOCK APPLICATION TAG field." ); 
    AddBlockPLCell("LOGICAL BLOCK APPLICATION TAG MASK", Format("0x%4X", NextNBits_(16)), "LOGICAL BLOCK APPLICATION TAG MASK field." ); 
    
    ShowTransferLen();
}


#------------------------- WriteVerify CDB Common Functions ---------------------------------

ShowWriteVerifyCommon( lba_len ,  reserved, bit_32_cmd)
{
    AddBlockPLCell("WRPROTECT", Format("0x%1X", NextNBits_(3)), "WRPROTECT field." );  
    ShowDPO();
    PLReservedCheck( 2 );
      
    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("BYTCHK", GetBitStr(), "Byte check (BYTCHK) bit field.", FieldColor, [_CELLINFO, 0, options ]);

    if(reserved == null) #obsoleted in Verify 10 and Verify 12
        AddBlockPLCell("Obsolete", GetBitStr(), "Obsolete field.", FieldColor, [_CELLINFO, 0, options ]); 
    else	                  
	PLReservedCheck( 1 );

    if(bit_32_cmd != null) # used when we must add a reserved field as row to 32 bit operation
        PLReservedCheck( 8 );    

    if( lba_len == null ) lba_len = 32;
    ShowLBA( lba_len );
}


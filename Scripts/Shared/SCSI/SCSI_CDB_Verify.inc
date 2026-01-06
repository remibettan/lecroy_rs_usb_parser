#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_Verify.inc
#
#  SCSI CDB Verify Commands decoder functions
################################################################################


ShowVerify10()
{
    ShowVerifyCommon();   

    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("G3tout", GetBitStr(), " Group3 timeout field.", FieldColor, [_CELLINFO, 0, options ]);
    PLReservedCheck(2);  

    AddBlockPLCell("GROUP NUMBER", Format("0x%02X", NextNBits_(5)), "GROUP NUMBER field.");
    ShowVerifyLen( 16 );
}

ShowVerify10MMC()
{
    ShowVerifyCommon();   

    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("G3tout", GetBitStr(), " Group3 timeout field.", FieldColor, [_CELLINFO, 0, options ]);
    PLReservedCheck(2);  

    AddBlockPLCell("GROUP NUMBER", Format("0x%02X", NextNBits_(5)), "GROUP NUMBER field.");
		AddBlockPLCell("NumOfBlocks", Format("%u", NextNBits_(16)),
		"The NUMBER OF BLOCKS field specifies the total\n" + 
		"number of contiguous logical blocks within the\n" + 
		"range. A NUMBER OF BLOCKS field of zero indicates\n" + 
		"that all remaining logical blocks on the block\n" + 
		"device shall be within the range.");  
}

ShowVerify12()
{
    ShowVerifyCommon();
        
    ShowVerifyLen();

    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("G3tout", GetBitStr(), " Group3 timeout field.", FieldColor, [_CELLINFO, 0, options ]);
    PLReservedCheck(2);  

    AddBlockPLCell("GROUP NUMBER", Format("0x%02X", NextNBits_(5)), "GROUP NUMBER field.");
}


ShowVerify16()
{
    ShowVerifyCommon( 64 , 1);
        
    ShowVerifyLen();

    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("G3tout", GetBitStr(), "Group3 timeout field.", FieldColor, [_CELLINFO, 0, options ]);
    PLReservedCheck(2);  

    AddBlockPLCell("GROUP NUMBER", Format("0x%02X", NextNBits_(5)), "GROUP NUMBER field.");
}


ShowVerify32()
{

    ShowVerifyCommon(64, 1);

    AddBlockPLCell("EXPECTED INITIAL LOGICAL BLOCK REFERENCE TAG", Format("0x%8X", NextNBits_(32)), "EXPECTED INITIAL LOGICAL BLOCK REFERENCE TAG field." );   
    AddBlockPLCell("EXPECTED LOGICAL BLOCK APPLICATION TAG", Format("0x%4X", NextNBits_(16)), "EXPECTED LOGICAL BLOCK APPLICATION TAG field." ); 
    AddBlockPLCell("LOGICAL BLOCK APPLICATION TAG MASK", Format("0x%4X", NextNBits_(16)), "LOGICAL BLOCK APPLICATION TAG MASK field." ); 
    
    ShowVerifyLen();
}

ShowVerify6_SSC()
{
	PLReservedCheck(5); 
	
	options = [ ["set", 1], ["Not set", 0] ];     
    AddBlockPLCell("IMMED", GetBitStr(), 
         "An immediate (IMMED) bit of one specifies the\n" + 
         "device server shall return status as soon as\n" + 
         "the command descriptor block has been validated.", FieldColor, [_CELLINFO, 0, options ]);	
         
    AddBlockPLCell("BYTCMP", GetBitStr(), 
         "A BYTCMP bit of one specifies the device server\n" +  
         "shall perform a byte-by-byte compare of the data\n" + 
         "on the medium and the data transferred from the application client." ,FieldColor, [_CELLINFO, 0, options ]);
         
   AddBlockPLCell("FIXED", GetBitStr(), "If the FIXED bit is one, the TRANSFER LENGTH specifies\n" + 
				 "the number of fixed-length blocks to be transferred." , FieldColor, [_CELLINFO, 0, options ]); 

   ShowVerifyLen(24);				 
				  	         
}


ShowVerify16_SSC()
{
	PLReservedCheck(5); 
	
	options = [ ["set", 1], ["Not set", 0] ];     
    AddBlockPLCell("IMMED", GetBitStr(), 
         "An immediate (IMMED) bit of one specifies the\n" + 
         "device server shall return status as soon as\n" + 
         "the command descriptor block has been validated.", FieldColor, [_CELLINFO, 0, options ]);	
         
    AddBlockPLCell("BYTCMP", GetBitStr(), 
         "A BYTCMP bit of one specifies the device server\n" +  
         "shall perform a byte-by-byte compare of the data\n" + 
         "on the medium and the data transferred from the application client." ,FieldColor, [_CELLINFO, 0, options ]);
         
   AddBlockPLCell("FIXED", GetBitStr(), "If the FIXED bit is one, the TRANSFER LENGTH specifies\n" + 
				 "the number of fixed-length blocks to be transferred." , FieldColor, [_CELLINFO, 0, options ]); 

   PLReservedCheck(8); 
    
   AddBlockPLCell("PARTITION", GetFld8H(), 
        "PARTITION field.\n\n" +
        "This field specifies the partition to select\n" +
        "if the CP bit is one."  );   
        
   AddBlockPLCell("LOGICAL OBJECT IDENTIFIER", GetFld64(), 
        "LOGICAL OBJECT IDENTIFIER field.\n\n" +
        "specify the position at which the ERASE(16)\n" +
		"command shall start.");   
		        
   ShowVerifyLen(24);				 
				  	         
}
#------------------------- Verify CDB Common Functions ---------------------------------

ShowVerifyCommon( lba_len ,  reserved)
{
    AddBlockPLCell("VRPROTECT", Format("0x%1X", NextNBits_(3)), "VRPROTECT field." );  
    
    ShowDPO();
    PLReservedCheck( 2 );
    
    options = [ ["set", 1], ["Not set", 0] ];
    
    AddBlockPLCell("BYTCHK", GetBitStr(), "Byte check (BYTCHK) bit field.", FieldColor, [_CELLINFO, 0, options ]);
    
    if(reserved == null) #obsoleted in Verify 10 and Verify 12
        AddBlockPLCell("Obsolete", GetBitStr(), "Obsolete field.", FieldColor, [_CELLINFO, 0, options ]); 
    else	                  
	PLReservedCheck( 1 );
    
    if( lba_len == null ) lba_len = 32;   
    ShowLBA( lba_len );
}


ShowVerifyLen( len )
{
    if( len == null ) len = 32;

    AddBlockPLCell("Verification Len", Format("%u", NextNBits_(len) ), 
    "The VERIFICATION LENGTH field specifies the\n" + 
    "number of contiguous logical blocks of data\n" + 
    "or blanks that shall be verified." );
}


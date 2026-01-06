#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_ReadWrite.inc
#
#  SCSI CDB Read and Write Commands decoder functions
################################################################################


#----------------------------- READ Commands -----------------------------------

ShowRead6()
{
    PLReservedCheck(3);    
    ShowLBA(21);    
    ShowReadWriteTranferLen( 8 );
}

ShowRead16_SSC()
{
    PLReservedCheck(6);    
   
    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("SILI", GetBitStr(), "If the SILI bit is one and the FIXED bit is one\n" + 
				 "the device server shall terminate the command with CHECK CONDITION status" , FieldColor, [_CELLINFO, 0, options ]);  
				 
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
		
    ShowReadWriteTranferLen( 24 );
}

ShowRead6_SSC()
{
   PLReservedCheck(6);    
   
   options = [ ["set", 1], ["Not set", 0] ];
   AddBlockPLCell("SILI", GetBitStr(), "If the SILI bit is one and the FIXED bit is one\n" + 
				 "the device server shall terminate the command with CHECK CONDITION status" , FieldColor, [_CELLINFO, 0, options ]);  
				 
   AddBlockPLCell("FIXED", GetBitStr(), "If the FIXED bit is one, the TRANSFER LENGTH specifies\n" + 
				 "the number of fixed-length blocks to be transferred." , FieldColor, [_CELLINFO, 0, options ]);  
   
   ShowReadWriteTranferLen( 24 );
}

ShowReadReverse6()
{
   PLReservedCheck(5);    
   
   options = [ ["set", 1], ["Not set", 0] ];
   AddBlockPLCell("BYTORD", GetBitStr(), "A byte order (BYTORD) bit of zero specifies all\n" + 
				 "logical block(s), and the byte(s) within the logical\n" + 
				 "block(s) are trans-ferred in the reverse order", FieldColor, [_CELLINFO, 0, options ]);  
				 
   AddBlockPLCell("SILI", GetBitStr(), "If the SILI bit is one and the FIXED bit is one\n" + 
				 "the device server shall terminate the command with CHECK CONDITION status" , FieldColor, [_CELLINFO, 0, options ]);  
				 
   AddBlockPLCell("FIXED", GetBitStr(), "If the FIXED bit is one, the TRANSFER LENGTH specifies\n" + 
				 "the number of fixed-length blocks to be transferred." , FieldColor, [_CELLINFO, 0, options ]);  
   
   ShowReadWriteTranferLen( 24 );
}

ShowReadReverse16()
{
   PLReservedCheck(5);    
   
   options = [ ["set", 1], ["Not set", 0] ];
   AddBlockPLCell("BYTORD", GetBitStr(), "A byte order (BYTORD) bit of zero specifies all\n" + 
				 "logical block(s), and the byte(s) within the logical\n" + 
				 "block(s) are trans-ferred in the reverse order", FieldColor, [_CELLINFO, 0, options ]);  
				 
   AddBlockPLCell("SILI", GetBitStr(), "If the SILI bit is one and the FIXED bit is one\n" + 
				 "the device server shall terminate the command with CHECK CONDITION status" , FieldColor, [_CELLINFO, 0, options ]);  
				 
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
	    
   ShowReadWriteTranferLen( 24 );
}

ShowRead10()
{
    ShowReadCommon();    
    PLReservedCheck( 3 );
    AddBlockPLCell("GROUP NUMBER", Format("0x%02X", NextNBits_(5)), "GROUP NUMBER field.");  
    ShowReadWriteTranferLen( 16 );
}



ShowRead12()
{
    ShowReadCommon();   
    ShowReadWriteTranferLen( 32 );

    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("Streaming", GetBitStr(), "Streaming field. Restricted for MMC-4.", FieldColor, [_CELLINFO, 0, options ]);

    PLReservedCheck( 2 );               
    AddBlockPLCell("GROUP NUMBER", Format("0x%02X", NextNBits_(5)), "GROUP NUMBER field.");  
}



ShowRead16()
{

    ShowReadCommon ( 64 , 1);   
    ShowReadWriteTranferLen( 32 );

    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("Restricted for MMC-4", GetBitStr(), "Restricted for MMC-4 field.", FieldColor, [_CELLINFO, 0, options ]);

    PLReservedCheck( 2 );               
    AddBlockPLCell("GROUP NUMBER", Format("0x%02X", NextNBits_(5)), "GROUP NUMBER field."); 
}

ShowRead32()
{
    ShowReadCommon(64, 1, 1);

    AddBlockPLCell("EXPECTED INITIAL LOGICAL BLOCK REFERENCE TAG", Format("0x%8X", NextNBits_(32)), "EXPECTED INITIAL LOGICAL BLOCK REFERENCE TAG field." );   
    AddBlockPLCell("EXPECTED LOGICAL BLOCK APPLICATION TAG", Format("0x%4X", NextNBits_(16)), "EXPECTED LOGICAL BLOCK APPLICATION TAG field." ); 
    AddBlockPLCell("LOGICAL BLOCK APPLICATION TAG MASK", Format("0x%4X", NextNBits_(16)), "LOGICAL BLOCK APPLICATION TAG MASK field." ); 
    
    ShowTransferLen();
}

ShowReadGeneration()
{
    PLReservedCheck( 7 );
    ShowRELADR();
    ShowLBA( 32 );
    PLReservedCheck( 8 );
    PLReservedCheck( 8 );
    ShowAllocLen( 8 );
}


ShowReadUpdatedBlock()
{
    PLReservedCheck( 3 );
    ShowDPO();
    ShowFUA();
    PLReservedCheck( 2 );
    ShowRELADR();    
    ShowLBA( 32 );
    
    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("LATEST", GetBitStr(), "The LATEST bit field.", FieldColor, [_CELLINFO, 0, options ]);
    
    AddBlockPLCell("GENERATION ADDRESS", Format("0x%04X", NextNBits_(15)), 
    "GENERATION ADDRESS field." );   
    
    PLReservedCheck( 8 );   
}



#-------------------------------- WRITE Commands -----------------------------------
ShowSSCWrite6()
{
    PLReservedCheck( 7 );
    
    options = [ ["set", 1], ["Not set", 0] ];
    
     AddBlockPLCell("FIXED", GetBitStr(), 
    "The FIXED bit specifies whether fixed-block transfers or\n" + 
    "variable-block transfers are to be used.\n\n" +
    "If the FIXED bit is one, the TRANSFER LENGTH value specifies the number\n" + 
    "of fixed-length blocks to be transferred, using the current\n" + 
    "block length reported in the mode parameter block descriptor.\n\n" + 
    "If the FIXED bit is zero, a single logical block is transferred\n" + 
    "with TRANSFER LENGTH specifying the logical block length\n" + 
    "in bytes." , FieldColor, [_CELLINFO, 0, options ]);
    
    
    ShowReadWriteTranferLen( 24 );
}

ShowSSCWrite16()
{
    PLReservedCheck( 4 );
        
	options = [ ["set", 1], ["Not set", 0] ];
        
    AddBlockPLCell("FCS" , GetBitStr(), "An FCS bit of zero specifies this command is\n" + 
		"not the first command in a tagged write sequence.",FieldColor, [_CELLINFO, 0, options ]);
    
    AddBlockPLCell("LCS" , GetBitStr(), "An LCS bit of zero specifies this command is\n" + "
		not the last command in a tagged write sequence.",FieldColor, [_CELLINFO, 0, options ]);
		
    PLReservedCheck( 1 );        
    
     AddBlockPLCell("FIXED", GetBitStr(), 
		"The FIXED bit specifies whether fixed-block transfers or\n" + 
		"variable-block transfers are to be used.\n\n" +
		"If the FIXED bit is one, the TRANSFER LENGTH value specifies the number\n" + 
		"of fixed-length blocks to be transferred, using the current\n" + 
		"block length reported in the mode parameter block descriptor.\n\n" + 
		"If the FIXED bit is zero, a single logical block is transferred\n" + 
		"with TRANSFER LENGTH specifying the logical block length\n" + 
		"in bytes." , FieldColor, [_CELLINFO, 0, options ]);
    
    PLReservedCheck( 8 );
    
    AddBlockPLCell("PARTITION", GetFld8H(), 
        "PARTITION field.\n\n" +
        "This field specifies the partition to select\n" +
        "if the CP bit is one."  );   
        
    AddBlockPLCell("LOGICAL OBJECT IDENTIFIER", GetFld64(), 
        "LOGICAL OBJECT IDENTIFIER field.\n\n" +
        "specify the position at which the ERASE(16)\n" +
		"command shall start.");  
		
    ShowReadWriteTranferLen( 24 );
}

ShowSBCWrite6()
{
    PLReservedCheck( 3 );
    ShowLBA( 21 );
    ShowReadWriteTranferLen( 8 );
}



ShowWrite10()
{
    ShowWriteCommon();      
    PLReservedCheck( 3 );
    
    AddBlockPLCell("GROUP NUMBER", Format("0x%02X", NextNBits_(5)), "GROUP NUMBER field."); 
    
    ShowReadWriteTranferLen( 16 );
}

ShowWrite10MMC()
{
    AddBlockPLCell("WRPROTECT", Format("0x%1X", NextNBits_(3)), "WRPROTECT field." );  

    ShowDPO();    
    ShowFUA();    
    options = [ ["set", 1], ["Not set", 0] ];
    
    AddBlockPLCell("TSR", GetBitStr(), "non-volatile cache field.", FieldColor, [_CELLINFO, 0, options ]);
        
    AddBlockPLCell("FUA_NV", GetBitStr(), "non-volatile cache field.", FieldColor, [_CELLINFO, 0, options ]);

    AddBlockPLCell("Obsolete", GetBitStr(), "Obsolete field.", FieldColor, [_CELLINFO, 0, options ]); 

    ShowLBA( 32 );    
    PLReservedCheck( 3 );
    
    AddBlockPLCell("GROUP NUMBER", Format("0x%02X", NextNBits_(5)), "GROUP NUMBER field."); 
    
    ShowReadWriteTranferLen( 16 );
}

ShowWrite12()
{
    ShowWriteCommon(); 

    ShowReadWriteTranferLen( 32 );

    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("Streaming", GetBitStr(), "Streaming field.", FieldColor, [_CELLINFO, 0, options ]);

    PLReservedCheck( 2 );               
    AddBlockPLCell("GROUP NUMBER", Format("0x%02X", NextNBits_(5)), "GROUP NUMBER field."); 
}

ShowWrite12MMC()
{
    AddBlockPLCell("WRPROTECT", Format("0x%1X", NextNBits_(3)), "WRPROTECT field." );  

    ShowDPO();    
    ShowFUA();    
    options = [ ["set", 1], ["Not set", 0] ];
    
    AddBlockPLCell("TSR", GetBitStr(), "non-volatile cache field.", FieldColor, [_CELLINFO, 0, options ]);
        
    AddBlockPLCell("FUA_NV", GetBitStr(), "non-volatile cache field.", FieldColor, [_CELLINFO, 0, options ]);

    AddBlockPLCell("Obsolete", GetBitStr(), "Obsolete field.", FieldColor, [_CELLINFO, 0, options ]);  

	ShowLBA( 32 ); 

    ShowReadWriteTranferLen( 32 );

    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("Streaming", GetBitStr(), "Streaming field.", FieldColor, [_CELLINFO, 0, options ]);
    AddBlockPLCell("VNR", GetBitStr(), "VNR field.", FieldColor, [_CELLINFO, 0, options ]);
    PLReservedCheck( 1 );               
    AddBlockPLCell("GROUP NUMBER", Format("0x%02X", NextNBits_(5)), "GROUP NUMBER field."); 
}

ShowWrite16()
{
    ShowWriteCommon(64, 1); 

    ShowReadWriteTranferLen( 32 );

    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("Restricted for MMC-4", GetBitStr(), "Restricted for MMC-4 field.", FieldColor, [_CELLINFO, 0, options ]);

    PLReservedCheck( 2 );               
    AddBlockPLCell("GROUP NUMBER", Format("0x%02X", NextNBits_(5)), "GROUP NUMBER field.");   
}

ShowWrite32()
{
    ShowWriteCommon(64, 1, 1);

    AddBlockPLCell("EXPECTED INITIAL LOGICAL BLOCK REFERENCE TAG", Format("0x%8X", NextNBits_(32)), "EXPECTED INITIAL LOGICAL BLOCK REFERENCE TAG field." );   
    AddBlockPLCell("EXPECTED LOGICAL BLOCK APPLICATION TAG", Format("0x%4X", NextNBits_(16)), "EXPECTED LOGICAL BLOCK APPLICATION TAG field." ); 
    AddBlockPLCell("LOGICAL BLOCK APPLICATION TAG MASK", Format("0x%4X", NextNBits_(16)), "LOGICAL BLOCK APPLICATION TAG MASK field." ); 
    
    ShowTransferLen();
}

ShowWriteLong10()
{
    options = [ ["set", 1], ["Not set", 0] ];

    AddBlockPLCell("COR_DIS", GetBitStr(), "COR_DIS field.", FieldColor, [_CELLINFO, 0, options ]);
    AddBlockPLCell("WR_UNCOR", GetBitStr(), "WR_UNCOR field.", FieldColor, [_CELLINFO, 0, options ]);
    AddBlockPLCell("PBLOCK", GetBitStr(), "PBLOCK field.", FieldColor, [_CELLINFO, 0, options ]);

    PLReservedCheck( 4 );

    AddBlockPLCell("Obsolete", GetBitStr(), "Obsolete field.", FieldColor, [_CELLINFO, 0, options ]);
    
    ShowLBA( 32 );
    PLReservedCheck( 8 );

    ShowReadWriteTranferLen( 16 );
}


ShowWriteLong16()
{   
    options = [ ["set", 1], ["Not set", 0] ];

    AddBlockPLCell("COR_DIS", GetBitStr(), "COR_DIS field.", FieldColor, [_CELLINFO, 0, options ]);
    AddBlockPLCell("WR_UNCOR", GetBitStr(), "WR_UNCOR field.", FieldColor, [_CELLINFO, 0, options ]);
    AddBlockPLCell("PBLOCK", GetBitStr(), "PBLOCK field.", FieldColor, [_CELLINFO, 0, options ]);
       
    serv_action = NextNBits_(5);
    AddPayLoadCell( "SERVICE ACTION", Format ("0x%0X", serv_action), "SERVICE ACTION");

    ShowLBA(64);
    PLReservedCheck( 16 );
 
    ShowTransferLen(16);

    PLReservedCheck(8); 
}

ShowOrWrite()
{
    AddBlockPLCell("ORPROTECT", Format("0x%1X", NextNBits_(3)), "ORPROTECT field." );  

    ShowDPO();    
    ShowFUA();    
    PLReservedCheck( 1 );     

    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("FUA_NV", GetBitStr(), "non-volatile cache field.", FieldColor, [_CELLINFO, 0, options ]);
             
    PLReservedCheck( 1 );
 
    ShowLBA( 64 );

    ShowReadWriteTranferLen();

    PLReservedCheck( 3 );
    
    AddBlockPLCell("GROUP NUMBER", Format("0x%02X", NextNBits_(5)), "GROUP NUMBER field."); 
}


#------------------------------ READ and WRITE CDB Common Functions ----------------
ShowReadCommon( lba_len , reserved, bit_32_cmd)
{   
    AddBlockPLCell("RDPROTECT", Format("0x%1X", NextNBits_(3)), "RDPROTECT field." );  

    ShowDPO();    
    ShowFUA();    
    PLReservedCheck( 1 );     

    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("FUA_NV", GetBitStr(), "non-volatile cache field.", FieldColor, [_CELLINFO, 0, options ]);

    if(reserved == null) #obsoleted in Read 10 and Read 12
        AddBlockPLCell("Obsolete", GetBitStr(), "Obsolete field.", FieldColor, [_CELLINFO, 0, options ]); 
    else	                  
	PLReservedCheck( 1 );

    if(bit_32_cmd != null) # used when we must add a reserved field as row to 32 bit operation
        PLReservedCheck( 8 );  

    if( lba_len == null ) lba_len = 32;   
    ShowLBA( lba_len );
}


ShowDPO()
{
	options = [ ["set", 1], ["Not set", 0] ];
		
     AddBlockPLCell("DPO", GetBitStr(), 
    "A disable page out (DPO) bit of zero indicates the priority\n" + 
    "shall be determined by the RETENTION PRIORITY fields in\n" + 
    "the caching page. A DPO bit of one indicates that the device\n" + 
    "server shall assign the logical blocks accessed by this\n" + 
    "command the lowest priority for being fetched into or retained\n" + 
    "by the cache.", FieldColor, [_CELLINFO, 0, options ]);
}


ShowEBP()
{
	options = [ ["set", 1], ["Not set", 0] ];
	
     AddBlockPLCell("EBP", GetBitStr(), 
    "An erase by-pass (EBP) bit of zero indicates that\n" + 
    "the block device shall default to the normal\n" + 
    "write operation. An EBP bit of one indicates\n" + 
    "that the device server is allowed to by-pass\n" + 
    "the erase operation prior to writing the data.", FieldColor, [_CELLINFO, 0, options ]);
}


ShowFUA()
{
    options = [ ["set", 1], ["Not set", 0] ];
	
    AddBlockPLCell("FUA", GetBitStr(), "A force unit access (FUA)", FieldColor, [_CELLINFO, 0, options ]);
}


ShowReadWriteTranferLen( len )
{
    if( !len ) len = 32; 

	transfer_len = NextNBits_(len);	
	
	if (!AddSpecReadWriteTransferLenCell(transfer_len) )
	{
		AddBlockPLCell("Transfer Len", Format("%u", transfer_len), 
			"The TRANSFER LENGTH field specifies\n" + 
			"the number of contiguous logical blocks\n" + 
			"of data to be transferred.");
	}
}

ShowWriteCommon( lba_len , reserved, bit_32_cmd)
{ 
    AddBlockPLCell("WRPROTECT", Format("0x%1X", NextNBits_(3)), "WRPROTECT field." );  

    ShowDPO();    
    ShowFUA();    
    PLReservedCheck( 1 );     

    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("FUA_NV", GetBitStr(), "non-volatile cache field.", FieldColor, [_CELLINFO, 0, options ]);

    if(reserved == null) #obsoleted in Read 10 and Read 12
        AddBlockPLCell("Obsolete", GetBitStr(), "Obsolete field.", FieldColor, [_CELLINFO, 0, options ]); 
    else	                  
	PLReservedCheck( 1 );

    if(bit_32_cmd != null) # used when we must add a reserved field as row to 32 bit operation
        PLReservedCheck( 8 );  

    if( lba_len == null ) lba_len = 32;   
    ShowLBA( lba_len );
}
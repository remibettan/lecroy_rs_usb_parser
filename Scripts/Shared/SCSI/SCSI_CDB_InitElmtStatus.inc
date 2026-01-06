#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_InitElmtStatus.inc
#
#  SCSI CDB INITIALIZE ELEMENT STATUS decoder functions
################################################################################


ShowInitElmntStatus()
{
    PLReservedCheck(8);    
    PLReservedCheck(8);    
    PLReservedCheck(8);    
    PLReservedCheck(8);    
}

ShowInitElmntStatusWRange()
{
    PLReservedCheck(6);   
    
    options = [ ["set", 1], ["Not set", 0] ];
    
    AddBlockPLCell("FAST", GetBitStr(), 
        "A FAST bit set to one indicates that the specified elements\n" + 
        "shall be scanned for media presence only\n"  
        , FieldColor, [_CELLINFO, 0, options ]);   
        
    AddBlockPLCell("RANGE", GetBitStr(), 
        "A RANGE bit set to zero specifies that all element addresses shall\n" + 
        "be checked and that the NUMBER OF ELEMENTS field\n" + 
        "and STARTING ELEMENT ADDRESS field are ignored\n" 
        ,FieldColor, [_CELLINFO, 0, options ]);  
        
    AddBlockPLCell("Start Elmt Addr", Format("0x%04X", NextNBits_(16)),
		"STARTING ELEMENT ADDRESS field.\n\n" + 
		"The STARTING ELEMENT ADDRESS field specifies\n" + 
		"the minimum element address to report.");  
		
	PLReservedCheck(8);    
    PLReservedCheck(8);
    
    AddBlockPLCell("Number Of Elmts", Format("%d", NextNBits_(16)),
		"The NUMBER OF ELEMENTS field specifies the\n" + 
		"maximum number of element descriptors to\n" + 
		"be created by the target for this command.");    	 
		
	PLReservedCheck(8);	
}
#
#  Copyright (c) 2003, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_WriteFileMarks.inc
#
#  SCSI CDB WriteFilemarks Commands decoder functions
################################################################################


ShowWriteFilemarks6()
{
    PLReservedCheck(6);
    
    options = [ ["set", 1], ["Not set", 0] ];
    
    AddBlockPLCell("Obsolete" , GetBitStr(), "Obsoleted field.", FieldColor, [_CELLINFO, 0, options ]);
     
    AddBlockPLCell("IMMED", GetBitStr(), 
         "An immediate (IMMED) bit of one specifies the\n" + 
         "device server shall return status as soon as\n" + 
         "the command descriptor block has been validated.", FieldColor, [_CELLINFO, 0, options ]);
    
    AddBlockPLCell("FILEMARK COUNT", GetFld24D(), 
        "FILEMARK COUNT field.\n" +
        "specifies the number of filemarks to be written.");
        
}

ShowWriteFilemarks16()
{
    PLReservedCheck( 4 );
        
    options = [ ["set", 1], ["Not set", 0] ];        
    AddBlockPLCell("FCS" , GetBitStr(), "An FCS bit of zero specifies this command is\n" + 
		"not the first command in a tagged write sequence.",FieldColor, [_CELLINFO, 0, options ]);
    
    AddBlockPLCell("LCS" , GetBitStr(), "An LCS bit of zero specifies this command is\n" + "
		not the last command in a tagged write sequence.",FieldColor, [_CELLINFO, 0, options ]);
		
    AddBlockPLCell("Obsolete" , GetBitStr(), "Obsoleted field.", FieldColor, [_CELLINFO, 0, options ]);
     
    AddBlockPLCell("IMMED", GetBitStr(), 
         "An immediate (IMMED) bit of one specifies the\n" + 
         "device server shall return status as soon as\n" + 
         "the command descriptor block has been validated.", FieldColor, [_CELLINFO, 0, options ]);		
         
	PLReservedCheck(8);    
	
    AddBlockPLCell("PARTITION", GetFld8H(), 
        "PARTITION field.\n\n" +
        "This field specifies the partition to select\n" +
        "if the CP bit is one."  );  	
        
    AddBlockPLCell("LOGICAL OBJECT IDENTIFIER", GetFld64(), 
        "LOGICAL OBJECT IDENTIFIER field.\n\n" +
        "specify the position at which the ERASE(16)\n" +
		"command shall start."); 
		
    AddBlockPLCell("FILEMARK COUNT", GetFld24D(), 
        "FILEMARK COUNT field.\n" +
        "specifies the number of filemarks to be written.");		               
}
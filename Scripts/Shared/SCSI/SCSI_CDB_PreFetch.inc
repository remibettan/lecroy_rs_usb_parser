#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_PreFetch.inc
#
#  SCSI CDB PreFetch Commands decoder functions
################################################################################



ShowPreFetch10()
{
    PLReservedCheck(6);
    
    options = [ ["set", 1], ["Not set", 0] ];
   
    AddBlockPLCell("IMMED", GetBitStr(), 
    "An immediate (IMMED) bit of zero indicates that\n" + 
    "status shall be returned after the operation\n" + 
    "is complete. An IMMED bit of one indicates that\n" + 
    "status shall be returned as soon as the command\n" + 
    "descriptor block has been validated.", FieldColor, [_CELLINFO, 0, options ]);
    
    ShowRELADR();
    ShowLBA(32);
    
    PLReservedCheck(8);    
    ShowTransferLen(16);
}


ShowPreFetch16()
{
    PLReservedCheck(6);
    
    options = [ ["set", 1], ["Not set", 0] ];
    
    AddBlockPLCell("IMMED", GetBitStr(), 
    "An immediate (IMMED) bit of zero indicates that\n" + 
    "status shall be returned after the operation\n" + 
    "is complete. An IMMED bit of one indicates that\n" + 
    "status shall be returned as soon as the command\n" + 
    "descriptor block has been validated.", FieldColor, [_CELLINFO, 0, options ]);
    
    ShowRELADR();
    ShowLBA( 64 );    
    ShowTransferLen(32);
    PLReservedCheck(8);  
}



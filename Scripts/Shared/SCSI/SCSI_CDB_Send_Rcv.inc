#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_Send_Rcv.inc
#
#  SCSI CDB SEND and RECEIVE Command decoder functions
################################################################################


ShowSend()
{
    PLReservedCheck(7);
    
    options = [ ["set", 1], ["Not set", 0] ];
    
    AddBlockPLCell("AER", GetBitStr(), "An asynchronous event reporting (AER) bit of one\n" + 
    "indicates that the data to be transferred conforms\n" + 
    "to AER data format as in SPC-2 standard. An AER\n" + 
    "bit of zero indicates that the data to be transferred\n" + 
    "are vendor specific.", FieldColor, [_CELLINFO, 0, options ]);
   
    
    ShowTransferLen( 24 );
}



ShowReceive()
{
    PLReservedCheck(8);    
    ShowTransferLen( 24 );
}

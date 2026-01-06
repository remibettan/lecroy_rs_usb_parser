#
#  Copyright (c) 2010, LeCroy - All Rights Reserved
#
#  SCSI_CDB_RcvrdBuffData.inc
#
#  SCSI CDB RECOVER BUFFERED DATA Command decoder functions
################################################################################

ShowRecvrdBuffData()
{   
   PLReservedCheck(6);    
   
   options = [ ["set", 1], ["Not set", 0] ];
   AddBlockPLCell("SILI", GetBitStr(), "If the SILI bit is one and the FIXED bit is one\n" + 
				 "the device server shall terminate the command with CHECK CONDITION status" , FieldColor, [_CELLINFO, 0, options ]);  
				 
   AddBlockPLCell("FIXED", GetBitStr(), "If the FIXED bit is one, the TRANSFER LENGTH specifies\n" + 
				 "the number of fixed-length blocks to be transferred." , FieldColor, [_CELLINFO, 0, options ]);  
   
   ShowReadWriteTranferLen( 24 );
}
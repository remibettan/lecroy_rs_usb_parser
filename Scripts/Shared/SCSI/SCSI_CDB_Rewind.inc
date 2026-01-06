#
#  Copyright (c) 2003, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_Rewind.inc
#
#  SCSI CDB Rewind decoder functions
################################################################################




ShowRewind()
{
    PLReservedCheck(7);
     
     
    options = [ ["set", 1], ["Not set", 0] ];
   
    AddBlockPLCell("IMMED", GetBitStr(), 
        "An immediate (IMMED) bit of zero specifies\n" + 
        "the device server shall not return status\n" + 
        "until the load or unload operation has completed.", FieldColor, [_CELLINFO, 0, options ]);
         
    PLReservedCheck(8);         
    PLReservedCheck(8);
    PLReservedCheck(8);          
}
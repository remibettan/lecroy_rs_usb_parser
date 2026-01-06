#
#  Copyright (c) 2010, LeCroy - All Rights Reserved
#
#  SCSI_CDB_SetCapacity.inc
#
#  SCSI CDB SET CAPACITY Command decoder functions
################################################################################

ShowSetCapacity()
{
    PLReservedCheck(7);     
     
	options = [ ["set", 1], ["Not set", 0] ];     
    AddBlockPLCell("IMMED", GetBitStr(), 
         "An immediate (IMMED) bit of one specifies the\n" + 
         "device server shall return status as soon as\n" + 
         "the command descriptor block has been validated.", FieldColor, [_CELLINFO, 0, options ]);
        
    PLReservedCheck(8);     
    
    AddBlockPLCell("CAPACITY PROPORTION VALUE", Format("0x%04X", NextNBits_(16)), "CAPACITY PROPORTION VALUE field.\n", error );  
}
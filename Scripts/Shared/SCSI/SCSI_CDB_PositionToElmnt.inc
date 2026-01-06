#
#  Copyright (c) 2003, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_PositionToElmnt.inc
#
#  SCSI CDB POSITION TO ELEMENT Command decoder functions
################################################################################


ShowPositionToElmnt()
{
    PLReservedCheck(8);
    
    AddBlockPLCell("Medium Trnspt Addr", GetFld16H()  , "MEDIUM TRANSPORT ADDRESS field.");
    
    AddBlockPLCell("Destination Addr"  , GetFld16H()  , "DESTINATION ADDRESS field.");
    
    
    PLReservedCheck(16);    
    
    PLReservedCheck(7);
    
    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("INVERT"  , GetBitStr()  , "INVERT bit field.", FieldColor, [_CELLINFO, 0, options ]);
}

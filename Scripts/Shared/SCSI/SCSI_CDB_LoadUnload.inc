#
#  Copyright (c) 2003, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_LoadUnload.inc
#
#  SCSI CDB LoadUnload decoder functions
################################################################################




ShowLoadUnload()
{
    PLReservedCheck(7);
     
    options = [ ["set", 1], ["Not set", 0] ];
   
    AddBlockPLCell("IMMED", GetBitStr(), 
        "An immediate (IMMED) bit of zero specifies\n" + 
        "the device server shall not return status\n" + 
        "until the load or unload operation has completed.", FieldColor, [_CELLINFO, 0, options ]);
         
    PLReservedCheck(8);         
    PLReservedCheck(8);
    PLReservedCheck(4);
    
    AddBlockPLCell("HOLD" , GetBitStr(), "The HOLD bit field.", FieldColor, [_CELLINFO, 0, options ]);
    
    
    AddBlockPLCell("EOT"  , GetBitStr(), 
        "An end-of-tape (EOT) bit of one specifies\n" + 
        "an unload operation (LOAD bit set to zero)\n" + 
        "shall position the medium at end-of-medium\n" + 
        "for removal from the device.", FieldColor, [_CELLINFO, 0, options ]);
        
    AddBlockPLCell("RETEN"  , GetBitStr(), 
        "A retension (RETEN) bit of one specifies\n" + 
        "the logical unit shall perform a retension\n" + 
        "function on the current medium.", FieldColor, [_CELLINFO, 0, options ]);
        
        
    AddBlockPLCell("LOAD" , GetBitStr(), "The HOLD bit field.", FieldColor, [_CELLINFO, 0, options ]);
}
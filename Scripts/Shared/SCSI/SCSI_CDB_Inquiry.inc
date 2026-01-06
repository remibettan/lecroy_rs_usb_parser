#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_Inquiry.inc
#
#  SCSI CDB INQUIRY Command decoder functions
################################################################################



ShowInquiryCDB()
{
    PLReservedCheck(6);
    
    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("Obsolete", GetBitStr(), "Obsolete field.", FieldColor, [_CELLINFO, 0, options ]);    
    
    #-------------------------------- EVPD -------------------------------------
    if( NextNBits_(1) ) str = "set";
    else                str = "Not set";
    
    AddBlockPLCell("EVPD", str,
    "An enable vital product data (EVPD) bit of one specifies\n" + 
    "that the device server shall return the vital product data\n" + 
    "specified by the PAGE OR OPERATION CODE field.", FieldColor, [_CELLINFO, 0, options ]);
    #---------------------------------------------------------------------------
    
    AddBlockPLCell("Page Code", Format("0x%01X", NextNBits_(8)) ,"PAGE CODE field.");
      
    AddBlockPLCell("AllocLen", Format("%d", NextNBits_(16)) , "ALLOCATION LENGTH field.");
}


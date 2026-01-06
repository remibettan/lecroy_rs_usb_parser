#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_MediumScan.inc
#
#  SCSI CDB Medium Scan Commands decoder functions
################################################################################



ShowMediumScan()
{
    PLReservedCheck( 3 );
    
    options = [ ["set", 1], ["Not set", 0] ];
    
    AddBlockPLCell("WBS", GetBitStr(), 
    "A written block search (WBS) bit of zero indicates\n" + 
    "that the scan is for blank blocks. A WBS bit\n" + 
    "of one indicates that the scan is for written\n" + 
    "blocks.", FieldColor, [_CELLINFO, 0, options ]);
    
    AddBlockPLCell("ASA", GetBitStr(), 
    "An advanced scan algorithm (ASA) bit of zero indicates\n" + 
    "that the scan area is scanned in sequential order\n" + 
    "(as selected by the RSD bit). An ASA bit of one\n" + 
    "indicates to the device server that the written\n" + 
    "and blank areas within the scan area form contiguous\n" + 
    "extents (as opposed to scattered blocks).", FieldColor, [_CELLINFO, 0, options ]);
    
    AddBlockPLCell("RSD", GetBitStr(), 
    "A reverse scan direction (RSD) bit of zero indicates\n" + 
    "the scan shall begin with the first logical block\n" + 
    "of the scan area. A RSD bit of one indicates\n" + 
    "the scan shall begin with the last logical block\n" + 
    "of the scan area.", FieldColor, [_CELLINFO, 0, options ]);
    
    AddBlockPLCell("PRA", GetBitStr(), "A partial results acceptable (PRA) bit field.", FieldColor, [_CELLINFO, 0, options ]);
    
    ShowRELADR();
    ShowLBA();
    
    PLReservedCheck( 8 );
    PLReservedCheck( 8 );
    
    ShowParamListLen( 8 );    
}

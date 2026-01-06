#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_ReadDefectData.inc
#
#  SCSI CDB Read Defect Data Commands decoder functions
################################################################################



ShowReadDefectData10()
{
    PLReservedCheck(8);
    PLReservedCheck(3);
    
    options = [ ["set", 1], ["Not set", 0] ];
    
    AddBlockPLCell("REQ_PLIST", GetBitStr(), 
    "A primary defect list (PLIST) bit of zero requests\n" + 
    "that the device server not return the primary\n" + 
    "list of defects. A PLIST bit of one requests\n" + 
    "that the device server return the primary list\n" + 
    "of defects.", FieldColor, [_CELLINFO, 0, options ]);

    
    AddBlockPLCell("REQ_GLIST", GetBitStr(), 
    "A grown defect list (GLIST) bit of zero requests\n" + 
    "that the device server not return the grown defect\n" + 
    "list. A GLIST bit of one requests that the device\n" + 
    "server return the grown defect list.", FieldColor, [_CELLINFO, 0, options ]);
    
    AddBlockPLCell("Defect List FMT", Format("0x%01X", NextNBits_(3)), 
    "The DEFECT LIST FORMAT field specifies the\n" + 
    "defect descriptor to be used if the FMTDATA\n" + 
    "bit is one.");
    
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);    
    
    ShowAllocLen  (16);
}


ShowReadDefectData12()
{    
    PLReservedCheck(3);
    
    options = [ ["set", 1], ["Not set", 0] ];
    
    AddBlockPLCell("REQ_PLIST", GetBitStr(), 
    "A primary defect list (PLIST) bit of zero requests\n" + 
    "that the device server not return the primary\n" + 
    "list of defects. A PLIST bit of one requests\n" + 
    "that the device server return the primary list\n" + 
    "of defects.", FieldColor, [_CELLINFO, 0, options ]);
    
    AddBlockPLCell("REQ_GLIST", GetBitStr(), 
    "A grown defect list (GLIST) bit of zero requests\n" + 
    "that the device server not return the grown defect\n" + 
    "list. A GLIST bit of one requests that the device\n" + 
    "server return the grown defect list.", FieldColor, [_CELLINFO, 0, options ]);
    
    AddBlockPLCell("Defect List FMT", Format("0x%01X", NextNBits_(3)), 
    "The DEFECT LIST FORMAT field specifies the\n" + 
    "defect descriptor to be used if the FMTDATA\n" + 
    "bit is one.");
    
    AddBlockPLCell("Address Descriptor Index", Format("0x%08X", NextNBits_(32)), 
    "The ADDRESS DESCRIPTOR INDEXfield specifies the index of the first " +
    " address descriptor in the defect list that the device server shall return.");
    
    ShowAllocLen  (32);
    PLReservedCheck(8);
}





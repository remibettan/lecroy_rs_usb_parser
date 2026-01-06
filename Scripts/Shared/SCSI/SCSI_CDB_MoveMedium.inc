#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_MoveMedium.inc
#
#  SCSI CDB MOVE MEDIUM Command decoder functions
################################################################################


ShowMoveMedium()
{
    PLReservedCheck(8);
    
    AddBlockPLCell("Medium Trt ADDR", Format("0x%04X", NextNBits_(16)), 
    "The MEDIUM TRANSPORT ADDRESS field specifies\n" + 
    "the medium transport element that is to be\n" + 
    "used in executing this command." );
    
    
    AddBlockPLCell("Src ADDR", Format("0x%04X", NextNBits_(16)), 
    "The SOURCE ADDRESS  field may represent a storage\n" + 
    "element, an import/export element, a data transfer\n" + 
    "element, or a medium transport element." );
    
    
    AddBlockPLCell("Destn ADDR", Format("0x%04X", NextNBits_(16)), 
    "The DESTINATION ADDRESS field may represent a storage\n" + 
    "element, an import/export element, a data transfer\n" + 
    "element, or a medium transport element." );
    
     PLReservedCheck(16);
     PLReservedCheck(7);
     
	options = [ ["set", 1], ["Not set", 0] ];     
     
    AddBlockPLCell("INV", GetBitStr(), 
    "An INVERT bit set specifies that the volume shall\n" + 
    "be inverted or rotated prior to depositing the\n" + 
    "medium into the DESTINATION ADDRESS element.\n" + 
    "\n" + 
    "If the media changer does not support volume\n" + 
    "rotation for handling double sided media, the\n" + 
    "INVERT bit should be set to zero.", FieldColor, [_CELLINFO, 0, options ]);
   
}

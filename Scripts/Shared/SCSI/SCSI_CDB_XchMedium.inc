#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_XchMedium.inc
#
#  SCSI CDB EXCHANGE MEDIUM Command decoder functions
################################################################################



ShowXchMediumCDB()
{
    PLReservedCheck(8);
    
    
    AddBlockPLCell( "MEDIUM TRA ADDR", Format("0x%04X", NextNBits_(16)),
        "MEDIUM TRANSPORT ADDRESS field.\n" +
        "This field specifies the medium transport element\n" + 
        "that is to be used in executing this command." );
    
    
    str = "The volume in the SOURCE ADDRESS element is moved to\n" + 
            "the FIRST DESTINATION ADDRESS element and the volume\n" + 
            "that previously occupied the FIRST DESTINATION ADDRESS\n" + 
            "element is moved to the SECOND DESTINATION ADDRESS\n" + 
            "element.";
    
    AddBlockPLCell( "SOURCE ADDR", Format("0x%04X", NextNBits_(16)),
        "SOURCE ADDRESS field.\n" + str );
        
   
    AddBlockPLCell( "FIRST DEST ADDR", Format("0x%04X", NextNBits_(16)),
        "FIRST DESTINATION ADDRESS field.\n" + str );     
        
        
    AddBlockPLCell( "SECOND DEST ADDR", Format("0x%04X", NextNBits_(16)),
        "SECOND DESTINATION ADDRESS field.\n" + str );     
        
    
    PLReservedCheck(6);    
   
    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("Inv1", GetBitStr(), 
        "An INV1 bit of one specifies that the volume shall\n" + 
        "be inverted prior to depositing the volume into the\n" + 
        "FIRST DESTINATION ADDRESS element." , FieldColor, [_CELLINFO, 0, options ]);
        
        
   AddBlockPLCell("Inv2", GetBitStr(), 
        "An INV2 bit of one specifies that the volume shall\n" + 
        "be inverted prior to depositing the volume into the\n" + 
        "SECOND DESTINATION ADDRESS element." , FieldColor, [_CELLINFO, 0, options ]);
}


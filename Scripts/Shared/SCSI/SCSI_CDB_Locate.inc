#
#  Copyright (c) 2003, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_Locate.inc
#
#  SCSI CDB LOCATE decoder functions
################################################################################


ShowLocate10()
{
    PLReservedCheck(5);    
    
    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("BT"   , GetBitStr(), "Block identifier Type (BT) bit bit field.", FieldColor, [_CELLINFO, 0, options ]);
    
    AddBlockPLCell("CP"   , GetBitStr(), "Change Partition (CP) bit field.", FieldColor, [_CELLINFO, 0, options ]);
    
    AddBlockPLCell("IMMED", GetBitStr(), "An immediate (IMMED) bit field.", FieldColor, [_CELLINFO, 0, options ]);
    
    PLReservedCheck(8);
    
    AddBlockPLCell( "LOGICAL OBJECT IDENTIFIER", GetFld32H(), 
        "The LOGICAL OBJECT IDENTIFIER field specifies the logical\n" + 
        "identifier to which the logical unit shall position\n" + 
        "the medium based on the current setting of the\n" + 
        "DEST_TYPE field." );  
    
    
    PLReservedCheck(8);    
   
        
    AddBlockPLCell("PARTITION", GetFld8H(), 
        "PARTITION field.\n\n" +
        "This field specifies the partition to select\n" +
        "if the CP bit is one."  );   
}




ShowLocate16()
{
    PLReservedCheck(3);
    
    
    #------------------------------------ DEST_TYPE ---------------------------------------
    val = NextNBits_(2);
    
    tooltip = "DEST_TYPE field.\n" + 
    Format("Value   : 0x%X\n", val) +
           "Meaning : ";
    
    
    ClearError();
    select
    {
        val == 0b00 : { str = "Logical object ID";  tooltip += "Logical object identifier"; }    
        val == 0b01 : { str = "Logical file ID"  ;  tooltip += "Logical file identifier"  ; }
        val == 0b10 : { str = "Obsoleted"   ;  tooltip += "Obsoleted"  ; }
        default    : SetReservedError();
    };
    
    
    
    
    tooltip += "\n\nThis field specifies whether the location specified\n" + 
               "is a logical object identifier, logical file\n" + 
               "identifier, or a logical set identifier.";
    
    options = [ ["Logical object ID", 0], ["Logical file ID", 1]];
    
   AddBlockPLCell( "DEST_TYPE", str, tooltip + AddErrorTooltip(), error , [_CELLINFO, 0, options ] );
    
    #-----------------------------------------------------------------------------------------
    
    
    PLReservedCheck(1);
    
    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("CP"   , GetBitStr(), "Change Partition (CP) bit field.", FieldColor, [_CELLINFO, 0, options ]);
    
    AddBlockPLCell("IMMED", GetBitStr(), "An immediate (IMMED) bit field.", FieldColor, [_CELLINFO, 0, options ]);
    
    PLReservedCheck(7);
    
    AddBlockPLCell("BAM", GetBitStr(), "Block Address Mode type (BAM) bit field.\n\n" +
        "A BAM bit of zero specifies the logical unit shall\n" + 
        "process this command as an implicit address command.\n" + 
        "A BAM bit of one specifies the logical unit shall\n" + 
        "process this command as an explicit address command.", FieldColor, [_CELLINFO, 0, options ]);
        
        
    AddBlockPLCell("PARTITION", GetFld8H(), 
        "PARTITION field.\n\n" +
        "This field specifies the partition to select\n" +
        "if the CP bit is one."  );    
        
        
    AddBlockPLCell( "LOGICAL IDENTIFIER", GetFld64(), 
        "The LOGICAL IDENTIFIER field specifies the logical\n" + 
        "identifier to which the logical unit shall position\n" + 
        "the medium based on the current setting of the\n" + 
        "DEST_TYPE field." );  
   
   PLReservedCheck(8);
   PLReservedCheck(8);
   PLReservedCheck(8);   
}
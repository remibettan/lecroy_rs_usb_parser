#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_ModeSense10.inc
#
#  SCSI CDB MODE SENSE(10) Command decoder functions
################################################################################


ShowModeSense10()
{
    PLReservedCheck(3);
    
    
    #-------------------------------- LLBAA ------------------------------------
    if( NextNBits_(1) ) str = "set"    ;
    else                str = "Not set";
    
    options = [ ["set", 1], ["Not set", 0] ];
       
    AddBlockPLCell("LLBAA", str, "Long LBA Accepted (LLBAA) bit.", FieldColor, [_CELLINFO, 0, options ]);
    #---------------------------------------------------------------------------
        
    
    
    #-------------------------------- DBD -------------------------------------
    if( NextNBits_(1) ) str = "set"    ;
    else                str = "Not set";
    
    
    AddBlockPLCell("DBD", str, 
    "A disable block descriptors (DBD) bit of zero indicates that\n" + 
    "the device server may return zero or more block descriptors\n" + 
    "in the returned MODE SENSE data.\n" + 
    "A DBD bit of one specifies that the device server shall not\n" + 
    "return any block descriptors in the returned MODE SENSE\n" + 
    "data.", FieldColor, [_CELLINFO, 0, options ]);
    #---------------------------------------------------------------------------
    
    
    PLReservedCheck(3);
    
    
    #-------------------------------- PC ---------------------------------------
    val = NextNBits_(2);      
    
    select{
        val == 0b00 : { text = "Cur vals"; str = "00b"; tooltip = "Current values" ; }
        val == 0b01 : { text = "Chg vals"; str = "01b"; tooltip = "Changeable values"; }
        val == 0b10 : { text = "Def vals"; str = "10b"; tooltip = "Default values" ; }
        val == 0b11 : { text = "Sav vals"; str = "11b"; tooltip = "Saved values"; }
    };
    
    tooltip = "The page control (PC) field defines the type of mode\n" + 
              "parameter values to be returned in the mode pages.\n\n" + 
    Format("Value   : %s.\n", str) + Format("Meaning : %s.", tooltip);
    
    options = [ ["Cur vals", 0], ["Chg vals", 1], ["Def vals", 2], ["Sav vals", 3] ];
    
    AddBlockPLCell("PC", text, tooltip, FieldColor, [_CELLINFO, 0, options ]);
    #---------------------------------------------------------------------------    
    
    
    #-------------------------------- PAGE CODE --------------------------------
    val = NextNBits_(6);
    
    tooltip = select {
         val == 0x00                     : "Vendor specific (does not require page format)";
        (val >= 0x01) || ( val <= 0x1F ) : "Device-types specific.";                     
        (val >= 0x20) || ( val <= 0x3E ) : "Vendor specific (page format required).";        
         val == 0x3F                     : "Vendor specific (does not require page format)"; 
    };
    
    tooltip = "The PAGE CODE field specifies\n" + 
    "which mode page(s) to return.\n\nMeaning : " + tooltip;
    
    AddBlockPLCell("PAGE CODE", Format("0x%02X", val), tooltip);    
    #---------------------------------------------------------------------------            
        
    AddBlockPLCell("SUBPAGE CODE", Format("0x%02X", NextNBits_(8)) ,"SUBPAGE CODE field."); 

    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);
    
    
    AddBlockPLCell("AllocLen", Format("%d", NextNBits_(16)),
     "ALLOCATION LENGTH field.");    
}

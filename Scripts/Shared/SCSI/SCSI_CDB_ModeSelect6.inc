#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_ModeSelect6.inc
#
#  SCSI CDB MODE SELECT(6) Command decoder functions
################################################################################


ShowModeSelect6()
{
    PLReservedCheck(3);
    
    #-------------------------------- PF -------------------------------------
    if( NextNBits_(1) )
    { 
        str = "set";
        tooltip = "A PF bit of one indicates that the MODE SELECT parameters\n" + 
        "following the header and block descriptor(s) are structured as\n" + 
        "pages of related parameters and are as specified in this standard.";
    }
    else 
    { 
        str = "Not set";
        tooltip = "A PF bit of zero indicates that all parameters\n" + 
        "after the block descriptors are vendor specific.";
    }
    
    tooltip = "Page format (PF) bit.\n\n" + tooltip;
    
    options = [ ["set", 1], ["Not set", 0] ];
    
    AddBlockPLCell("PF", str, tooltip, FieldColor, [_CELLINFO, 0, options ]);
    #---------------------------------------------------------------------------
    
    
    PLReservedCheck(3);
    
    
    #-------------------------------- SP ---------------------------------------
    if( NextNBits_(1) ) str = "set";
    else                str = "Not set";
    
    AddBlockPLCell("SP", str, "Save pages (SP) bit.", FieldColor, [_CELLINFO, 0, options ]);
    #---------------------------------------------------------------------------
    
    
    PLReservedCheck(8);
    PLReservedCheck(8);
    
    ShowParamListLen(8); 
}

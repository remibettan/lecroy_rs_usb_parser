#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_ReadElmtStatus.inc
#
#  SCSI CDB READ ELEMENT STATUS Command decoder functions
################################################################################


ShowReadElmtStatus()
{
    PLReservedCheck(3);
    
    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("VOLTAG", GetBitStr(),
    "A volume tag (VOLTAG) bit of one indicates that\n" + 
    "the target shall report volume tag information\n" + 
    "if this feature is supported.", FieldColor, [_CELLINFO, 0, options ]);
    
     
    #------------------------------- ELEMENT TYPE CODE -----------------------------------
    val = NextNBits_(4);    
    
    error = null;
    select{
        val == 0x00   : { str = "All"           ; tooltip = "All element types reported" ; }
        val == 0x01   : { str = "Medium"        ; tooltip = "Storage element"            ; }
        val == 0x02   : { str = "Storage"       ; tooltip = "Medium transport element"   ; }
        val == 0x03   : { str = "Import/export" ; tooltip = "Import/export element"      ; }
        val == 0x04   : { str = "Data transfer" ; tooltip = "Import/export element"      ; }
        
        default       : { str = "Reserved"      ; tooltip = "Reserved element type code" ;
                          error = _ERROR; }
    };    
    
    tooltip = "ELEMENT TYPE CODE field.\n\n" + 
    Format("Value   : %01Xh.\n", str) + Format("Meaning : %s.", str) + 
    Format("\n%s.", tooltip);
    
    
    options = [ ["All", 0], ["Medium", 1], ["Storage", 2], ["Import/export", 3], ["Data transfer", 4] ];
    AddBlockPLCell("MODE", str, tooltip, error, [_CELLINFO, 0, options ] );
    #---------------------------------------------------------------------------
    
        
    AddBlockPLCell("Start Elmt Addr", Format("0x%04X", NextNBits_(16)),
    "STARTING ELEMENT ADDRESS field.\n\n" + 
    "The STARTING ELEMENT ADDRESS field specifies\n" + 
    "the minimum element address to report.");
    
    
    AddBlockPLCell("Number Of Elmts", Format("%d", NextNBits_(16)),
    "The NUMBER OF ELEMENTS field specifies the\n" + 
    "maximum number of element descriptors to\n" + 
    "be created by the target for this command.");
    
    
    PLReservedCheck(6);
    
    options = [ ["set", 1], ["Not set", 0] ];
    
    AddBlockPLCell("CURDATA", GetBitStr(),
    "Current data (CURDATA) bit field.\n" +
    "If the CURDATA bit is one, the target shall\n" + 
    "return element status data without causing\n" + 
    "device motion. If the CURDATA bit is zero,\n" + 
    "the target may cause device motion to confirm\n" + 
    "element status data.", FieldColor, [_CELLINFO, 0, options ]);
    
    
    AddBlockPLCell("DVCID", GetBitStr(),
    "DVCID bit of one specifies that the target\n" + 
    "shall return device identifiers, if available,\n" + 
    "for the specified range.", FieldColor, [_CELLINFO, 0, options ]);
    
    
    ShowAllocLen( 24 );    
    PLReservedCheck(8);
}

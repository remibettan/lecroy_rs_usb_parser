#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_LogSense.inc
#
#  SCSI CDB LOG SENSE Command decoder functions
################################################################################


ShowLogSense()
{
     PLReservedCheck(6);
    
    #-------------------------------- Obselete -------------------------------------
    if( NextNBits_(1) ) str = "1";
    else                str = "0";
    AddBlockPLCell("Obsolete", str, "This field is obsolete.", FieldColor, [_CELLINFO, 0, options ]);
    
    #-------------------------------- SP ---------------------------------------
    if( NextNBits_(1) ) str = "set";
    else                str = "Not set";
    
    AddBlockPLCell("SP", str,
    "Saving parameters (SP) bit.", FieldColor, [_CELLINFO, 0, options ]);
    
    #-------------------------------- PC ---------------------------------------
    val = NextNBits_(2);      
    
    select{
        val == 0b00 : { text = "Cur Trhd"; str = "00b"; tooltip = "Threshold values" ; }
        val == 0b01 : { text = "Cur Cumv"; str = "01b"; tooltip = "Cumulative values"; }
        val == 0b10 : { text = "Def Trhd"; str = "10b"; tooltip = "Default threshold values" ; }
        val == 0b11 : { text = "Def Cumv"; str = "11b"; tooltip = "Default cumulative values"; }
    };
    
    tooltip = "The page control (PC) field defines the type\n" +
              "of parameter values to be selected.\n\n" + 
    Format("Value   : %s.\n", str) + Format("Meaning : %s.", tooltip);
    
    options = [ ["Cur Trhd", 0], ["Cur Cumv", 1], ["Def Trhd", 2], ["Def Cumv", 3] ];
    
    AddBlockPLCell("PC", text, tooltip, FieldColor, [_CELLINFO, 0, options ]);
    #---------------------------------------------------------------------------    
    
    
    AddBlockPLCell("PAGE CODE", Format("0x%02X", NextNBits_(6)),
    "The PAGE CODE field identifies which page\n" + 
    "of data is being requested.");
        
    AddBlockPLCell("SUBPAGE CODE", Format("0x%02X", NextNBits_(8)) ,"SUBPAGE CODE field.");
    
    PLReservedCheck(8);
    
    
    AddBlockPLCell("ParamPTR", Format("0x%04X", NextNBits_(16)),    
    "The PARAMETER POINTER field allows the application client\n" + 
    "to request parameter data beginning from a specific parameter\n" + 
    "code to the maximum allocation length or the maximum parameter\n" + 
    "code supported by the target, whichever is less.");
    
    AddBlockPLCell("AllocLen", Format("%d", NextNBits_(16)),
     "ALLOCATION LENGTH field.");    
}

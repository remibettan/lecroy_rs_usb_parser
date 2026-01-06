#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_LogSelect.inc
#
#  SCSI CDB LOG SELECT Command decoder functions
################################################################################


ShowLogSelect()
{
     PLReservedCheck(6);
    
    #-------------------------------- PCR -------------------------------------
    if( NextNBits_(1) ) str = "set";
    else                str = "Not set";
    
    options = [ ["set", 1], ["Not set", 0] ];
    
    AddBlockPLCell("PCR", str, "A parameter code reset (PCR) bit of one and a parameter list length\n" + 
    "of zero shall cause all implemented parameters to be set to\n" + 
    "the target-defined default values. \n" + 
    "A PCR bit of zero specifies that the log parameters shall not be reset.", FieldColor, [_CELLINFO, 0, options ]);
    #---------------------------------------------------------------------------
    
    
    #-------------------------------- SP ---------------------------------------
    if( NextNBits_(1) ) str = "set";
    else                str = "Not set";
    
    AddBlockPLCell("SP", str,
    "A save parameters (SP) bit of one indicates that after\n" + 
    "performing the specified LOG SELECT operation the target\n" + 
    "shall save to nonvolatile memory all parameters identified as\n" + 
    "savable by the DS bit in the log page.", FieldColor, [_CELLINFO, 0, options ]);
    #---------------------------------------------------------------------------
    
    
    #-------------------------------- PC ---------------------------------------
    val = NextNBits_(2);      
    
    select{
        val == 0b00 : { text = "Cur Trhd"; str = "00b"; tooltip = "Current threshold values" ; }
        val == 0b01 : { text = "Cur Cumv"; str = "01b"; tooltip = "Current cumulative values"; }
        val == 0b10 : { text = "Def Trhd"; str = "10b"; tooltip = "Default threshold values" ; }
        val == 0b11 : { text = "Def Cumv"; str = "11b"; tooltip = "Default cumulative values"; }
    };
    
    tooltip = "The page control (PC) field defines the type\n" +
              "of parameter values to be selected.\n\n" + 
    Format("Value   : %s.\n", str) + Format("Meaning : %s.", tooltip);
    
    options = [ ["Cur Trhd", 0], ["Cur Cumv", 1], ["Def Trhd", 2], ["Def Cumv", 3] ];
    
    AddBlockPLCell("PC", text, tooltip, FieldColor, [_CELLINFO, 0, options ]);
    #---------------------------------------------------------------------------    
    
    AddBlockPLCell("PAGE CODE", Format("0x%02X", NextNBits_(6)) , "PAGE CODE field.");
    AddBlockPLCell("SUBPAGE CODE", Format("0x%02X", NextNBits_(8)) ,"SUBPAGE CODE field. ");
    
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);
    
    ShowParamListLen(16);    
}

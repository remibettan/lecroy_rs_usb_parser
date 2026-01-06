#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_SendDiag.inc
#
#  SCSI CDB SEND DIAGNOSTIC Command decoder functions
################################################################################


ShowSendDiag()
{    
    
    self_test_bit = GetBit( 2, PeekNBits(8) );    
        
    #------------------------------------- SELF-TEST CODE -------------------------------------------
    val = NextNBits_(3);
    
    error = null;
    err_tooltip = "";
    if( self_test_bit && val )
    {
        error = _ERROR;
        err_tooltip = "The SELFTEST bit is one but the SELF-TEST CODE\nfield is not 000b.";
    }
    
    
    if( !self_test_bit && !val )
    {
        error = _ERROR;
        err_tooltip = "The SELFTEST bit is zero but the SELF-TEST CODE\nfield is 000b.";
    }    
    
    no_param = 1;
    
    select{
        val == 0b000 : { str = "Null"        ; tooltip = "This value shall be used when the\nSELFTEST bit is set to one.";
                         no_param = 0; }
        
        
        val == 0b001 : { str = "Bkgnd shrt"; tooltip = "The device server shall start its short\n" + 
                                               "self-test in the background mode."; }
                                               
        val == 0b010 : { str = "Bkgnd ext" ; tooltip = "The device server shall start its extended\n" + 
                                               "self-test in the background mode."; }
        
        val == 0b100 : { str = "Abort Bkgnd ext" ; tooltip = "The device server shall abort the current\n" + 
                                               "self-test running in background mode."; }
                                               
        val == 0b101 : { str = "Frgnd shrt"; tooltip = "The device server shall start its short\n" + 
                                               "self-test in the foreground mode."; }
                                               
        val == 0b110 : { str = "Frgnd ext"; tooltip = "The device server shall start its extended\n" + 
                                               "self-test in the foreground mode."; }                                
      
        default    :   { str = "Reserved"; tooltip = "Reserved SELF-TEST CODE value.";
                         no_param = 0; error = _ERROR; }
    };
    
    tooltip = "SELF-TEST CODE field.\n" +
    Format("Value   : %01Xh.\nMeaning : ", val) + str +
    Format(".\n%s", tooltip);
    
    options = [ ["Null", 0], ["Bkgnd shrt", 1], ["Bkgnd ext", 2], ["Abort Bkgnd ext", 4], ["Frgnd shrt", 5], ["Frgnd ext", 6] ];
    
    AddBlockPLCell("SELF-TEST CODE", str, tooltip + AddWarningTooltip(err_tooltip), error, [_CELLINFO, 0, options ]);
    #-----------------------------------------------------------------------------------------
    
    options = [ ["set", 1], ["Not set", 0] ];
    
    AddBlockPLCell("PF", GetBitStr(), "A page format (PF) bit of one specifies that the\n" + 
    "SEND DIAGNOSTIC parameters and any parameters\n" + 
    "returned by a following RECEIVE DIAGNOSTIC RESULTS\n" + 
    "command shall conform to the page structure as\n" + 
    "specified in SPC-2 standard.", FieldColor, [_CELLINFO, 0, options ]);
    
    PLReservedCheck(1);
    
    AddBlockPLCell("SelfTest", GetBitStr(),
    "A self-test (SELFTEST) bit of one directs the\n" + 
    "device server to complete the target’s default\n" + 
    "self-test.", FieldColor, [_CELLINFO, 0, options ]);
    
    
    AddBlockPLCell("DevOffL", GetBitStr(),
    "A DEVOFFL bit of one grants permission to the\n" + 
    "device server to perform diagnostic operations\n" + 
    "that may affect all the logical units on a target.", FieldColor, [_CELLINFO, 0, options ]);
    
    
    AddBlockPLCell("UnitOffL", GetBitStr(),
    "A UNITOFFL bit of one grants permission to the\n" + 
    "device server to perform diagnostic operations\n" + 
    "that may affect the user accessible medium on\n" + 
    "the logical unit.", FieldColor, [_CELLINFO, 0, options ]);
    
    
    PLReservedCheck(8);
    
    if( no_param )
        ShowParamListLen( 16, 0 );
    else
        ShowParamListLen( 16 );
    
}

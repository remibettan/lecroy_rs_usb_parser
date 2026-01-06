#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_StartStopUnit.inc
#
#  SCSI CDB StartStopUnit Command decoder functions
#
################################################################################



ShowStartStopUnit( )
{
    PLReservedCheck(7);
    
    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("IMMED", GetBitStr(), "An immediate (IMMED) bit field.", FieldColor, [_CELLINFO, 0, options ]);
    
    PLReservedCheck(8);
    PLReservedCheck(6);
    
    AddBlockPLCell( "Format-Layer Number", Format ("0x%1X", NextNBits_(2)), "Format-Layer Number field" );
        
    #--------------------------- Power Conditions --------------------------------
    val = NextNBits_(4);
    
    Error = null;
    
    tooltip  = "POWER CONDITIONS field.\n";
    tooltip +=  Format("Value   : %01Xh\n", val);
    tooltip += "Meaning : "; 
    
    select {
        val == 0x0 : { str = "No change";
                       tooltip += "No change in power conditions or in the device\n" + 
                                 "that is controlling power conditions."; }
                                 
        val == 0x1 : { str = "Active"            ; tooltip += "Place device into the Active condition.";  }
        val == 0x2 : { str = "Idle"              ; tooltip += "Place device into the Idle condition.";    }
        val == 0x3 : { str = "Standby"           ; tooltip += "Place device into the Standby condition."; }
        val == 0x5 : { str = "Sleep"             ; tooltip += "Place device into the Sleep condition."; }
        val == 0x7 : { str = "To Block Device"   ; tooltip += "Transfer control of power\nconditions to block device."; }
        val == 0xA : { str = "Idle Timer ->0"    ; tooltip += "Force Idle Condition Timer to zero."; }
        val == 0xB : { str = "Standby Timer ->0" ; tooltip += "Force Standby Condition Timer to zero."; }
        
        default    : { str =  "Reserved"         ; tooltip += (str + WARNING_SIGN + "Reserved value."); Error = _ERROR; }
    };
    
	options = [ ["No change", 0], ["Active", 1], ["Idle", 2], ["Standby", 3], ["Sleep", 5], ["To Block Device", 7], ["Idle Timer ->0", 0xA], ["Standby Timer ->0", 0xB] ];
   
    AddBlockPLCell( "POWER CONDITIONS", str, tooltip, Error, [_CELLINFO, 0, options ] );
    #-----------------------------------------------------------------------------
    
    PLReservedCheck(1);
    
    options = [ ["set", 1], ["Not set", 0] ];

    AddBlockPLCell("FL" , GetBitStr(), "A Format-layer (FL) bit field.", FieldColor, [_CELLINFO, 0, options ]);
    AddBlockPLCell("LOEJ" , GetBitStr(), "A load eject (LOEJ) bit field.", FieldColor, [_CELLINFO, 0, options ]);
 
    AddBlockPLCell("START", GetBitStr(), "A START bit of zero requests that the block\n" + 
    "device be stopped (media shall not be accessed\n" + 
    "by the application client). \n" + 
    "\n" + 
    "A START bit of one requests \n" + 
    "the block device be made ready for use.", FieldColor, [_CELLINFO, 0, options ]);
}

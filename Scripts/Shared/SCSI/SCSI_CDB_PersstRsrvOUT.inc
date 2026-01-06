#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_PersstRsrvOUT.inc
#
#  SCSI CDB PERSISTENT RESERVE OUT Command decoder functions
################################################################################


ShowPersstRsrvOUT()
{
    PLReservedCheck(3);
    
    #--------------------------- SERVICE ACTION -----------------------------
    val = NextNBits_(5);
    
    error = null;
    select{
        val == 0x0 : { str = "REGISTER"; tooltip = "Register a reservation key with the device server"; }
        val == 0x1 : { str = "RESERVE" ; tooltip = "Creates a persistent reservation\n" + 
                                                    "having a specified SCOPE and TYPE."; }
                                                    
        val == 0x2 : { str = "RELEASE" ; tooltip = "Releases the selected reservation\n" + 
                                                   "for the requesting initiator."; }
        
        val == 0x3 : { str = "CLEAR"   ; tooltip = "Clears all reservation keys and\n" + 
                                                   "all persistent reservations."; }
        val == 0x4 : { str = "PREEMPT" ; tooltip = "Preempts persistent reservations\n" + 
                                                   "from another initiator."; }
                                                   
        val == 0x5 : { str = "PREEMPT AND ABORT"   ; tooltip = "Preempts persistent reservations from another\n" + 
                                                   "initiator and aborts all tasks for all initiators\n" + 
                                                   "registered with the specified reservation key."; }
                                                   
        val == 0x6 : { str = "REGISTER AND IGNORE EXISTING KEY" ; tooltip = "Register a reservation key with\n" + 
                                                   "the device server."; }   
                                                   
        val == 0x7 : { str = "REGISTER AND MOVE" ; tooltip = "RRegister a reservation key for another I_T 
												   nexus with the device server and move a persistent reservation
												   to that I_T nexus ."; }                                        
                                                    
        default    : { str = "Reserved"        ; tooltip = "Reserved SERVICE ACTION value."; error = _ERROR;}
    };
    
    tooltip = "SERVICE ACTION field.\n" +
    Format("Value   : %01Xh.\nMeaning : ", val) + str +
    Format(".\n%s", tooltip);
    
    options = [ ["REGISTER", 0], ["RESERVE", 1], ["RELEASE", 2], ["CLEAR", 3], ["PREEMPT", 4], ["PREEMPT AND ABORT", 5], ["REGISTER AND IGNORE EXISTING KEY", 6] , ["REGISTER AND MOVE", 7]];
    
    AddBlockPLCell("SERVICE ACTION", str, tooltip, error, [_CELLINFO, 0, options ]);
    #------------------------------------------------------------------------    
    
    
    #-------------------------------- SCOPE ---------------------------------
    val = NextNBits_(4);
    
    error = null;
    select{
        val == 0x0 : { str = "LU_SCOPE"     ; tooltip = "Persistent reservation applies to the\nfull logical unit."; }
        val == 0x1 : { str = "Obsolete"     ; tooltip = "Obsolete SCOPE value."; }                                                    
        val == 0x2 : { str = "Obsolete"     ; tooltip = "Obsolete SCOPE value."; }                                                                                                        
        default    : { str = "Reserved"     ; tooltip = "Reserved SERVICE ACTION value."; error = _ERROR; }
    };
    
    tooltip = "SCOPE field.\n" +
    Format("Value   : %01Xh.\nMeaning : ", val) + str +
    Format(".\n%s", tooltip);
    
    options = [ ["LU_SCOPE", 0], ["Obsolete", 1]];
    
    AddBlockPLCell("SCOPE", str, tooltip, error, [_CELLINFO, 0, options ] );
    #------------------------------------------------------------------------    
    
    
    #-------------------------------- TYPE ---------------------------------
    val = NextNBits_(4);
    
    error = null;
    select {
        val == 0x0 : { str = "Obsolete"             ; tooltip = "Obsolete TYPE value"; } 
        val == 0x1 : { str = "Wrte Excl"            ; tooltip = "Write Exclusive"; } 
        val == 0x2 : { str = "Obsolete"             ; tooltip = "Obsolete TYPE value"; }         
        val == 0x3 : { str = "Excl Accs"            ; tooltip = "Exclusive Access"; }
        val == 0x4 : { str = "Obsolete"             ; tooltip = "Obsolete TYPE value"; }
        val == 0x5 : { str = "Wrte Excl Rgts Only"  ; tooltip = "Write Exclusive Registrants Only"; }
        val == 0x6 : { str = "Excl Accs Rgts Only"  ; tooltip = "Exclusive Access Registrants Only"; }
        val == 0x7 : { str = "Wrte Excl All Rgts"   ; tooltip = "Write Exclusive Registrants Only"; }
        val == 0x8 : { str = "Excl Accs All Rgts"   ; tooltip = "Exclusive Access Registrants Only"; }
                                                         
        default    : { str = "Reserved"             ; tooltip = "Reserved TYPE value"; error = _ERROR;}
    };
    
    tooltip = "TYPE field.\n" +
    Format("Value   : %01Xh.\nMeaning : ", val) + str +
    Format(".\n%s.", tooltip);
    
    options = [ ["Obsolete", 0], ["Wrte Excl", 1], ["Obsolete", 2], ["Excl Accs", 3], ["Obsolete", 4], ["Wrte Excl Rgts Only", 5], ["Excl Accs Rgts Only", 6], ["Wrte Excl All Rgts", 7], ["Excl Accs All Rgts", 8] ];
    
    AddBlockPLCell("TYPE", str, tooltip, error, [_CELLINFO, 0, options ]);
    #------------------------------------------------------------------------    
    
    PLReservedCheck(8);
    PLReservedCheck(8);   
     
    ShowParamListLen( 32 );
}

#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_PersstRsrvIN.inc
#
#  SCSI CDB PERSISTENT RESERVE IN Command decoder functions
################################################################################


ShowPersstRsrvIN()
{
    PLReservedCheck(3);
    
    #--------------------------- SERVICE ACTION -----------------------------
    val = NextNBits_(5);
    
    error = null;
    select{
        val == 0x0 : { str = "READ KEYS"       ; tooltip = "Reads all registered Reservation Keys"    ; }
        val == 0x1 : { str = "READ RESERVATION"; tooltip = "Reads the current persistent reservations"; }
        val == 0x2 : { str = "REPORT CAPABILITIES"; tooltip = "Returns capability information"; }
        val == 0x3 : { str = "READ FULL STATUS"; tooltip = "Reads complete information about all registrations and the persistent reservations, if any"; }
        default    : { str = "Reserved"        ; tooltip = "Reserved SERVICE ACTION value."; error = _ERROR; }
    };
    
    tooltip = "SERVICE ACTION field.\n" +
    Format("Value   : %01Xh.\nMeaning : ", val) + str +
    Format(".\n%s", tooltip);
    
    options = [ ["READ KEYS", 0], ["READ RESERVATION", 1] , ["REPORT CAPABILITIES" , 2], ["READ FULL STATUS" , 3]];
    
    AddBlockPLCell("SERVICE ACTION", str, tooltip, error, [_CELLINFO, 0, options ]);
    #------------------------------------------------------------------------    
    
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);
     
    ShowAllocLen  (16);
}

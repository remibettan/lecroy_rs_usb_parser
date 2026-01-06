#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_RcvCpyRslts.inc
#
#  SCSI CDB RECEIVE COPY RESULTS Command decoder functions
################################################################################


ShowRcvCpyRslts()
{
    PLReservedCheck(3);    
     
    #------------------------------- SERVICE ACTION --------------------------------
    val = NextNBits_(5);
    
    error = null;
    select{
        val == 0x00   : { str = "COPY STATUS"   ; tooltip = "Return the current copy status of the\n" + 
                                                "EXTENDED COPY command identified by\n" + 
                                                "the LIST IDENTIFIER field." ; }
                                                
        val == 0x01   : { str = "RECEIVE DATA"  ; tooltip = "Return the held data read by EXTENDED\n" + 
                                                "COPY command identified by the LIST\n" + 
                                                "IDENTIFIER field."            ; }
                                                
        val == 0x03   : { str = "OPERATING PARAMS"; tooltip = "Return copy manager operating parameters."; }
        
        
        val == 0x04   : { str = "FAILED SEG DTLS" ; tooltip = "Return copy target device sense data and other\n" + 
                                                "information about the progress of processing\n" + 
                                                "a segment descriptor whose processing was not\n" + 
                                                "completed during processing of the EXTENDED COPY\n" + 
                                                "command identified by the LIST IDENTIFIER field."; }
        
        val == 0x1F   : { str = "Vendor" ; tooltip = "Vendor Specific SERVICE ACTION."; }
        
        default       : { str = "Reserved"      ; tooltip = "Reserved SERVICE ACTION value." ; error = _ERROR; }
    };    
    
    tooltip = "SERVICE ACTION field.\n\n" + 
    Format("Value   : %01Xh.\n", val) + Format("Meaning : %s.", str) + 
    Format("\n%s", tooltip);
    
    options = [ ["COPY STATUS", 0], ["RECEIVE DATA", 1], ["OPERATING PARAMS", 3], ["FAILED SEG DTLS", 4] ];
    
    AddBlockPLCell("SERVICE ACTION", str, tooltip, error, [_CELLINFO, 0, options ]);
    #---------------------------------------------------------------------------
    
        
    AddBlockPLCell("LIST IDENTIFIER", Format("0x%01X", NextNBits_(8)),
    "The LIST IDENTIFIER field identifies the EXTENDED\n" + 
    "COPY command about which information is desired.");    
    
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);    
    
    ShowAllocLen( 32 );
    PLReservedCheck(8);
}

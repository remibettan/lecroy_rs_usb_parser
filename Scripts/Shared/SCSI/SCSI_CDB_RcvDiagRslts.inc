#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_RcvDiagRslts.inc
#
#  SCSI CDB RECEIVE DIAGNOSTIC RESULTS Command decoder functions
################################################################################


ShowRcvDiagRslts()
{
    PLReservedCheck(7);
    
    options = [ ["set", 1], ["Not set", 0] ];
    
    AddBlockPLCell("PCV",  GetBitStr(), 
    "A page code valid (PCV) bit of zero indicates\n" + 
    "that the most recent SEND DIAGNOSTIC command\n" + 
    "shall define the data returned by this command.\n" + 
    "Optionally, a PCV bit of one indicates that the\n" + 
    "contents of the PAGE CODE field shall define\n" + 
    "the data returned by this command.", FieldColor, [_CELLINFO, 0, options ]);
    
    
    
     
    #------------------------------- PAGE CODE --------------------------------
    val = NextNBits_(8);
    
    select{
        val == 0x00   : { str = "Supported"        ; tooltip = "Supported diagnostics" ; }                                                
        val == 0x01   : { str = "Config"           ; tooltip = "Configuration"            ; }
        val == 0x02   : { str = "Enclosure St/Ctrl"; tooltip = "Enclosure Status/Control" ; }                                                   
        val == 0x03   : { str = "Help Text"        ; tooltip = "Help Text"; }        
        val == 0x04   : { str = "String In/Out"    ; tooltip = str; }          
        val == 0x05   : { str = "Threshold In/Out" ; tooltip = str; }
        val == 0x06   : { str = "Array St/Ctrl"    ; tooltip = "Array Status/Control" ; }
        val == 0x07   : { str = "Elmnt Descriptor" ; tooltip = "Element Descriptor" ; }
        val == 0x08   : { str = "SES"              ; tooltip = "Short Enclosure Status" ; }
        
        (val >= 0x09) &&
        (val <= 0x2F) : { str = "Reserved for SES" ; tooltip = str ; }
        
        (val >= 0x30) &&
        (val < 0x3E)  : { str = "Reserved"          ; tooltip = "Reserved" ; }
        
         val == 0x3F  : { str = "SCSI transport"   ; tooltip = "SCSI transport protocol" ; }
                
        (val >= 0x40) &&
        (val <= 0x7F) : { str = "Specific Device"  ; tooltip = "Specific device type" ; }
        
        default       : { str = "Vendor"           ; tooltip = "Vendor specific" ; }
    };    
    
    tooltip = "PAGE CODE field.\n" + 
    "The PAGE CODE field identifies which diagnostic\n" + 
    "page is being sent as a result of command.\n\n" +
    Format("Value   : %01Xh.\n", val) + Format("Meaning : %s.", str) + 
    Format("(%s pages)", tooltip);
    
    options = [ ["Supported", 0], ["Config", 1], ["Enclosure St/Ctrl", 2], ["Help Text", 3], 
    ["String In/Out", 4], ["Threshold In/Out", 5], ["Array St/Ctrl", 6], ["Elmnt Descriptor", 7], 
    ["SES", 8], ["Reserved for SES", 9], ["Reserved", 0x30], ["SCSI transport", 0x3F], ["Specific Device", 0x40] ];
    
    AddBlockPLCell("PAGE CODE", str, tooltip, FieldColor, [_CELLINFO, 0, options ]);
    #---------------------------------------------------------------------------       
      
    ShowAllocLen  (16);   
}

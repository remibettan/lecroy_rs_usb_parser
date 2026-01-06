#
#  Copyright (c) 2010, LeCroy - All Rights Reserved
#
#  SCSI_CDB_SecPrtcle.inc
#
#  SCSI CDB Security Protocol IN/OUT Commands decoder functions
################################################################################



ShowSecurityProtocolIn()
{      
    #------------------------------------ SECURITY PROTOCOL -----------------------------------
    val = NextNBits_(8);
    
    error = null;
    tooltip = "";
    select{
        val == 0x00 :  { str = "Security protocol information"; }
        val >= 0x01 
			&& 
        val <= 0x06:    str = "Defined by the TCG";                            
        
        val == 0x20 :   str = "Tape Data Encryption";
        
        val == 0x21 :   str = "Data Encryption Configuration"  ;  
        
        val == 0x40 :  str = "SA Creation Capabilities";  
        val == 0x41 :  str = "IKEv2-SCS" ;  
        val == 0xED :  str = "SD Card TrustedFlash specification"; 
        
        val == 0xEE :  { str = "Authentication in Host Atchmnts Tran Devs"      ; tooltip = "Authentication in Host Attachments of Transient Storage Devices"; }    
        val == 0xEF :  str = "ATA Device Server Password Security"; 
        
        val >= 0xF0
			&&
	    val <= 0xFF:   { str = "Vendor Specific"; }
	    
        default     :  { str = "Reserved"; error = _ERROR; }
    };
    
    if( tooltip == "" ) tooltip = str;
    tooltip += " Security Protocol";
    
    tooltip = "SECURITY PROTOCOL field.\n\n" + 
    Format("Value   : %s.\n", str) + Format("Meaning : %s.", tooltip);
    
    options = [ ["Security protocol information", 0], ["Defined by the TCG", 1], ["Tape Data Encryption", 0x20], ["Data Encryption Configuration", 0x21], 
    ["SA Creation Capabilities", 0x40], ["IKEv2-SCS", 0x41], ["SD Card TrustedFlash specification", 0xED],
    ["Authentication in Host Atchmnts Tran Devs", 0xEE], ["ATA Device Server Password Security", 0xEF]]; 
    
    AddBlockPLCell("SECURITY PROTOCOL", Format("0x%02X", val), tooltip);
    #---------------------------------------------------------------------------    
           
    AddBlockPLCell("SECURITY PROTOCOL SPECIFIC", Format("0x%04X", NextNBits_(16)), "SECURITY PROTOCOL SPECIFIC field.");
    
    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("INC_512", GetBitStr(), "INC_512 field.", FieldColor, [_CELLINFO, 0, options ]);
    
    PLReservedCheck(7);
    
    PLReservedCheck(8);
    
    ShowAllocLen(32);
    PLReservedCheck(8);
}


ShowSecurityProtocolOut()
{
    #------------------------------------ SECURITY PROTOCOL -----------------------------------
    val = NextNBits_(8);
    
    error = null;
    tooltip = "";
    select{
        val == 0x00 :  { str = "Security protocol information"; }
        val >= 0x01 
			&& 
        val <= 0x06:    str = "Defined by the TCG";                            
        
        val == 0x20 :   str = "Tape Data Encryption";
        
        val == 0x21 :   str = "Data Encryption Configuration"  ;  
        
        val == 0x40 :  str = "SA Creation Capabilities";  
        val == 0x41 :  str = "IKEv2-SCS" ;  
        val == 0xED :  str = "SD Card TrustedFlash specification"; 
        
        val == 0xEE :  { str = "Authentication in Host Atchmnts Tran Devs"      ; tooltip = "Authentication in Host Attachments of Transient Storage Devices"; }    
        val == 0xEF :  str = "ATA Device Server Password Security"; 
        
        val >= 0xF0
			&&
	    val <= 0xFF:   { str = "Vendor Specific"; }
	    
        default     :  { str = "Reserved"; error = _ERROR; }
    };
    
    if( tooltip == "" ) tooltip = str;
    tooltip += " Security Protocol";
    
    tooltip = "SECURITY PROTOCOL field.\n\n" + 
    Format("Value   : %s.\n", str) + Format("Meaning : %s.", tooltip);
    
    options = [ ["Security protocol information", 0], ["Defined by the TCG", 1], ["Tape Data Encryption", 0x20], ["Data Encryption Configuration", 0x21], 
    ["SA Creation Capabilities", 0x40], ["IKEv2-SCS", 0x41], ["SD Card TrustedFlash specification", 0xED],
    ["Authentication in Host Atchmnts Tran Devs", 0xEE], ["ATA Device Server Password Security", 0xEF]]; 
    
    AddBlockPLCell("SECURITY PROTOCOL", Format("0x%02X", val), tooltip);
    #---------------------------------------------------------------------------    
           
    AddBlockPLCell("SECURITY PROTOCOL SPECIFIC", Format("0x%04X", NextNBits_(16)), "SECURITY PROTOCOL SPECIFIC field.");
    
    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("INC_512", GetBitStr(), "INC_512 field.", FieldColor, [_CELLINFO, 0, options ]);
    
    PLReservedCheck(7);    
    PLReservedCheck(8); 
       
    ShowTransferLen(32);    
    
    PLReservedCheck(8);
}
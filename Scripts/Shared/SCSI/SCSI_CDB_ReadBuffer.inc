#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_ReadBuffer.inc
#
#  SCSI CDB READ BUFFER Command decoder functions
################################################################################


ShowReadBuffer()
{
    #------------------------------------ RESERVED -----------------------------------
    PLReservedCheck(3);  
        
    #-------------------------------------- MODE -----------------------------------
    val = NextNBits_(5);      
    
    error = null;
    tooltip = "";
    select{
        val == 0x00 : { str = "Obsolete"; tooltip = "Obsolete" ; }
        val == 0x01 : { str = "Vendor"           ; tooltip = "Vendor specific"          ; }                        
        val == 0x02 :   str = "Data";
        val == 0x03 :   str = "Descriptor";
        val == 0x0A : { str = "Read echo buffer" ;     tooltip = "Read data from echo buffer"; }
        val == 0x0B :   str = "Echo buffer descriptor";
        
        val == 0x1A : { str = "Obsolete";	tooltip = "Obsolete"; }
        val == 0x1C :   str = "Error history";        
        
        default       :  { str = "Reserved";  error = _ERROR; }
    };
    
    if( tooltip == "" ) tooltip = str;
    tooltip += " Mode";
    
    tooltip = "MODE field.\n\n" + 
    Format("Value   : %s.\n", str) + Format("Meaning : %s.", tooltip);
    
    options = [ ["Obsolete", 0], ["Data", 2], ["Descriptor", 3], ["Read echo buffer", 0xA], ["Echo buffer descriptor", 0xB], ["Obsolete", 0x1A], ["Error history", 0x1C]];
    
    AddBlockPLCell("MODE", str, tooltip, error, [_CELLINFO, 0, options ]);
    
    #------------------------------------ BUFFER OFFSET ---------------------------------------
     if( val == 0x0B )
        PLReservedCheck(8);
     else
        AddBlockPLCell("BUFFER ID", Format("0x%02X", NextNBits_(8)),
        "The BUFFER ID field identifies a specific\n" + 
        "buffer within the logical unit from\n" + 
        "which data shall be transferred.");
    
     if( val == 0x03 || val == 0x0B )
        PLReservedCheck(24);
     else   
        AddBlockPLCell("BUFFER OFFSET", Format("0x%04X", NextNBits_(24)),
        "The BUFFER OFFSET field contains the\n" + 
        "byte offset within the specified buffer\n" + 
        "from which data shall be transferred.");
    
    #------------------------------------ ALLOCATION LENGTH ---------------------------------------
    alloc_len = NextNBits_(24);
    error = null;
    if((alloc_len < 0x4) && (val == 0x03 || val == 0x0B))
    {
	    tooltip = Format("The ALLOCATION LENGTH (%u) is not greater/equal than 4h. \n" , alloc_len); 
	    error = _ERROR;
    }
    
    AddBlockPLCell("AllocLen", Format("0x%04X", alloc_len), 
          "The ALLOCATION LENGTH field in the CDB indicates\n" + 
          "how much space has been allocated for the returned\n" + 
          "parameter list." + AddWarningTooltip(tooltip), error);
}

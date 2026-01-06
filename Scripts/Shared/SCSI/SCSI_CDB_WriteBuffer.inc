#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_WriteBuffer.inc
#
#  SCSI CDB WRITE BUFFER Command decoder functions
################################################################################


ShowWriteBuffer()
{
    #------------------------------------------------- MODE SPECIFIC ------------------------------------------  
    val = NextNBits_(3);
    AddBlockPLCell( "MODE SPECIFIC", Format("0x%02X", val),  "The usage of the MODE SPECIFICfield depends on the value in the MODEfield.", null );    
    
    #------------------------------------------------------ MODE -----------------------------------
    val = NextNBits_(5);
    
    error = null;
    tooltip = "";
    select{
        val == 0x00 : { str = "Obsolete"                  ; tooltip = "Obsolete" ; }
        val == 0x01 : { str = "Vendor"                    ; tooltip = "Vendor specific"          ; }                        
        val == 0x02 :   str = "Data";
        
        val == 0x04 :  { str = "Dnld microcd"             ; tooltip = "Download microcode"          ; }
        val == 0x05 :  { str = "Dnld microcd/Save"        ; tooltip = "Download microcode and save" ; }
        val == 0x06 :  { str = "Dnld microcd w/Offst"     ; tooltip = "Download microcode with offsets" ; }
        val == 0x07 :  { str = "Dnld microcd w/Offst/Save"; tooltip = "Download microcode with offsets and save" ; }
        
        val == 0x0A :  { str = "Write to echo buffer"      ; tooltip = "Write data to echo buffer"; }    
        val == 0x0E :  { str = "Dnld microcd w/Offst/Save/def act"; tooltip = "Download microcode with offsets, save, and defer active" ; }
        val == 0x0F :    str = "Activate deferred microcod"; 
        val == 0x1A :  { str = "Obsolete"; tooltip = "Obsolete" ; }
        val == 0x1B :  { str = "Obsolete"; tooltip = "Obsolete" ; }
        val == 0x1C :  { str = "Dnld app client err"; tooltip = "Download application client error history" ; }
        
        default     :  { str = "Reserved"; error = _ERROR; }
    };
    
    if( tooltip == "" ) tooltip = str;
    tooltip += " Mode";
    
    tooltip = "MODE field.\n\n" + 
    Format("Value   : %s.\n", str) + Format("Meaning : %s.", tooltip);
    
    options = [ ["Obsolete", 0], ["Data", 2], ["Dnld microcd", 4], ["Dnld microcd/Save", 5], 
    ["Dnld microcd w/Offst", 6], ["Dnld microcd w/Offst/Save", 7], ["Write to echo buffer", 0x0A],
    ["Dnld microcd w/Offst/Save/def act", 0x0E], ["Activate deferred microcod", 0x0F], ["Obsolete", 0x1A],
    ["Obsolete", 0x1B], ["Dnld app client err", 0x1C] ];
    
    AddBlockPLCell("MODE", str, tooltip, error, [_CELLINFO, 0, options ]);


    #------------------------------------------------- BUFFER ID ------------------------------------------  
    buffer_id = NextNBits_(8);
    error = null;
    
    if( buffer_id != 0 && val == 0 )
    {
   	    tooltip = Format("The BUFFER ID (%u) shall be set to zero. \n" , buffer_id); 
	    error = _ERROR; 
    }
    
    AddBlockPLCell("BUFFER ID", Format("0x%02X", buffer_id),
        "The BUFFER ID field identifies a specific\n" + 
        "buffer within the logical unit from\n" + 
        "which data shall be transferred." + AddWarningTooltip(tooltip), error);
    
    #------------------------------------------------- BUFFER ID ------------------------------------------          
    buffer_offset = NextNBits_(24);
    error = null;
    
    if( buffer_offset != 0 && val == 0 )
    {
   	    tooltip = Format("The BUFFER OFFSET (%u) shall be set to zero. \n" , buffer_offset); 
	    error = _ERROR; 
    }
    
    AddBlockPLCell("BUFFER OFFSET", Format("0x%08X", buffer_offset),
        "The BUFFER OFFSET field contains the\n" + 
        "byte offset within the specified buffer\n" + 
        "from which data shall be transferred." + AddWarningTooltip(tooltip), error);
           
           
    #---------------------------------------- PARAMETER LIST LENGTH --------------------------------
    ShowParamListLen( 24 );
}

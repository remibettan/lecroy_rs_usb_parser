#
#  Copyright (c) 2003, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_Space.inc
#
#  SCSI CDB SPACE commands decoder functions
################################################################################


ShowSpace6()
{
    PLReservedCheck(4);        
    
    
    #------------------------------------ CODE ---------------------------------------
    
    val = NextNBits_(4);
    
    tooltip = "CODE field.\n" + 
    Format("Value   : 0x%X\n", val) +
           "Meaning : ";
    
    
    ClearError();
    select
    {
        val == 0b000 : { str = "Logical blocks";  tooltip += str; }    
        val == 0b001 : { str = "Filemarks"     ;  tooltip += str; }
        val == 0b010 : { str = "Seq filemarks" ;  tooltip += "Sequential filemarks"; }
        val == 0b011 : { str = "End-of-data"   ;  tooltip += str; }
        val == 0b100 : { str = "Obsoleted"      ; tooltip += str; }
        val == 0b101 : { str = "ObSoleted"  ;	  tooltip += str; }
        
        default     : SetReservedError();
    };    
    
    options = [ ["Logical blocks", 0], ["Filemarks", 1], ["Seq filemarks", 2], ["End-of-data", 3]];
    
    AddBlockPLCell( "CODE", str, tooltip + AddErrorTooltip(), error, [_CELLINFO, 0, options ] );
    
    #-----------------------------------------------------------------------------------------
        
    
    AddBlockPLCell( "COUNT", GetFld24D(), "The COUNT field." );  
}


ShowSpace16()
{
    PLReservedCheck(4);        
            
    AddBlockPLCell( "CODE", Format("0x%01X", NextNBits_(4)), tooltip + AddErrorTooltip(), error, [_CELLINFO, 0, options ] );           
        
    PLReservedCheck(8);
    PLReservedCheck(8);
    
    AddBlockPLCell( "COUNT", GetFld64(), "The COUNT field." );  
    
    ShowParamListLen( 16 );
 
	PLReservedCheck(8);
}
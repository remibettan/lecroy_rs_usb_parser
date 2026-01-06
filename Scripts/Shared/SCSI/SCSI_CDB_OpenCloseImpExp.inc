#
#  Copyright (c) 2010, LeCroy - All Rights Reserved
#
#  SCSI_CDB_OpenCloseImpExp.inc
#
#  OPEN/CLOSE IMPORT/EXPORT ELEMENT Command decoder functions
################################################################################



ShowOpenCloseImpExp()
{
    PLReservedCheck(8);
    
    ShowElementAddr();
    
    PLReservedCheck(3);
    
    val = NextNBits_(5);
    tooltip  = "ACTION CODE  field.\n";
    tooltip += Format("Value   : 0x%02X\n", val );
    tooltip +=        "Meaning : ";    
    ClearError();  
    
    select
    {
          val == 0 : { tooltip += "OPEN IMPORT/EXPORT ELEMENT "  ; }  
          val == 1 : { tooltip += "CLOSE IMPORT/EXPORT ELEMENT " ; }
          
          default : { SetReservedError(); }    
    };
     
    AddBlockPLCell( "ACTION CODE", Format("0x%02X",val), tooltip + AddErrorTooltip(), error );
}
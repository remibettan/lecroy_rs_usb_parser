#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_ReadAttribute.inc
#
#  SCSI CDB READ ATTRIBUTE Command decoder functions
################################################################################



ShowReadAttribCDB()
{
    PLReservedCheck(3);
    
    
    #----------------------------- SERVICE ACTION -----------------------------
    serv_actn = NextNBits_(5);
    
    tooltip  = "SERVICE ACTION field.\n";
    tooltip += Format("Value   : 0x%02X\n", serv_actn );
    tooltip +=        "Meaning : ";
    
    
    ClearError();    
    select
    {
       serv_actn == 0x00 : { str = "ATTRIBUTE VALUES"; }  
       serv_actn == 0x01 : { str = "ATTRIBUTE LIST"  ; }  
       serv_actn == 0x02 : { str = "VOLUME LIST"     ; }  
       serv_actn == 0x03 : { str = "PARTITION LIST"  ; } 
       serv_actn == 0x04 : { str = "ELEMENT LIST"    ; }  
       
       default : { SetReservedError(); }
    };
    
    tooltip += str;
    
    options = [ ["ATTRIBUTE VALUES", 0], ["ATTRIBUTE LIST", 1], ["VOLUME LIST", 2], ["PARTITION LIST", 3], ["ELEMENT LIST", 4] ];
    
    AddBlockPLCell( "SERVICE ACTION", str, tooltip + AddErrorTooltip(), error, [_CELLINFO, 0, options ] );
    #--------------------------------------------------------------------------
    
    
    if( serv_actn == 0x04 )
    {    
        ShowElementAddr();        
        PLReservedCheck(4);        
        
        #  ELEMENT TYPE CODE 
        ShowElementTypeCode();
    }
    else
        AddBlockPLCell( "RESTRICTED", GetFld24H(), "RESTRICTED field."  );
    
    
    AddBlockPLCell( "VOLUME NUM", GetFld8D(), 
        "The VOLUME NUMBER field specifies a volume\n" + 
        "within the medium auxiliary memory."  );
    
    
    
    PLReservedCheck(8);
    
    
    AddBlockPLCell( "PARTITION NUM", GetFld8D(), 
        "The PARTITION NUMBER field specifies a partition\n" + 
        "within the medium auxiliary memory."  );
    
    
    AddBlockPLCell( "FIRST ATTR ID", GetFld16H(), 
        "The PARTITION NUMBER field specifies a partition\n" + 
        "within the medium auxiliary memory."  );
    
    
    ShowAllocLen();            
    
    PLReservedCheck(8);    
}





#-------------------------------------------------------------------------------------
#                                   Working functions
#-------------------------------------------------------------------------------------

ShowElementTypeCode( len )
{
    if( !len ) len = 4;
    val = NextNBits_(len);
        
    tooltip  = "ELEMENT TYPE CODE field.\n";
    tooltip += Format("Value   : 0x%01X\n", val );
    tooltip +=        "Meaning : ";    
    
    ClearError();    
    select
    {
       val == 0x00 : { str = "All"              ; }  
       val == 0x01 : { str = "Medium transport" ; }  
       val == 0x02 : { str = "Storage"          ; }  
       val == 0x03 : { str = "Import/export"    ; } 
       val == 0x04 : { str = "Data transfer"    ; }  
       
       default : { SetReservedError(); }
    };
    
    tooltip += str;
    
    options = [ ["All", 0], ["Medium transport", 1], ["Storage", 2], ["Import/export", 3], ["Data transfer", 4]];
    
    AddBlockPLCell( "ELEMENT TYPE", str, tooltip + AddErrorTooltip(), error, [_CELLINFO, 0, options ] );
}


ShowElementAddr()
{
    AddBlockPLCell( "ELEMENT ADDR", GetFld16H(),
        "The ELEMENT ADDRESS field specifies the element\n" + 
        "where the Medium Auxiliary Memory (MAM) currently\n" + 
        "resides as part of a medium." );
}
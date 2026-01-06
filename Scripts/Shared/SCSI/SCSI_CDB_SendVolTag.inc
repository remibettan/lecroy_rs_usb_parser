#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_SendVolTag.inc
#
#  SCSI CDB SEND VOLUME TAG Command decoder functions
################################################################################



ShowSendVolTagCDB()
{
    PLReservedCheck(4); 
    
    ShowElementTypeCode();    
    ShowElementAddr();
    
    PLReservedCheck(8);
    PLReservedCheck(3);
    
    
    
    #----------------------------- SEND ACTION CODE -----------------------------
    val = NextNBits_(5);
    
    str = Format("0x%02X", val );
    
    tooltip  = "SEND ACTION CODE field.\n";
    tooltip += "Value   : " + str + "\n";
    tooltip += "Meaning : ";
    
    
    ClearError();
    select
    {
       val == 0x0 : { tooltip += "Translate - search all defined volume tags"; }  
       val == 0x1 : { tooltip += "Translate - search only primary volume tags"; }  
       val == 0x2 : { tooltip += "Translate - search only alternate volume tags"; }         
       val == 0x4 : { tooltip += "Translate - search all defined tags\n - ignore sequence numbers"; }
       
       val == 0x5 : { tooltip += "Translate - search primary tags\n - ignore sequence numbers"; } 
       val == 0x6 : { tooltip += "Translate - search alternate tags\n - ignore sequence numbers"; } 
       
       val == 0x8 : { tooltip += "Assert - as the primary volume tag\n - if tag now undefined"; } 
       val == 0x9 : { tooltip += "Assert - as the alternate volume tag\n - if tag now undefined"; } 
       val == 0xA : { tooltip += "Replace - the primary volume tag\n - current tag ignored"; } 
       val == 0xB : { tooltip += "Replace - the alternate volume tag\n - current tag ignored"; } 
       val == 0xC : { tooltip += "Undefine - the primary volume tag - current tag ignored"; } 
       val == 0xD : { tooltip += "Undefine - the alternate volume tag - current tag ignored"; } 
       
       (val >= 0x1C) &&
       (val <= 0x1F) : { tooltip += "Vendor-specific"; } 
       
       default : { tooltip += "Reserved"; SetReservedError(); }
    };
    
        
    AddBlockPLCell( "SEND ACTION CODE", str, tooltip + AddErrorTooltip(), error );
    
    #--------------------------------------------------------------------------
    
    
    PLReservedCheck(16);    
    
    ShowParamListLen(16);
    
    PLReservedCheck(8);
}





#-------------------------------------------------------------------------------------
#                                   Working functions
#-------------------------------------------------------------------------------------


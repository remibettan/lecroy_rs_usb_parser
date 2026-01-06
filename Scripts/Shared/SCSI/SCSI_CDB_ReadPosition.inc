#
#  Copyright (c) 2003, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_ReadPosition.inc
#
#  SCSI CDB READ POSITION decoder functions
################################################################################


ShowReadPosition()
{
    PLReservedCheck(3);
        
    
    
    #------------------------------------ SERVICE ACTION ---------------------------------------
    val = NextNBits_(5);
    
    tooltip = "SERVICE ACTION field.\n" + 
    Format("Value   : 0x%X\n", val) +
           "Meaning : ";
    
    
    ClearError();
    select
    {
        val == 0x0 : 
        { 
            str = "SHORT FORM BLOCK ID";
            tooltip += str +
                        "\n\nDevice server shall return 20 bytes of data with\n" + 
                        "the FIRST LOGICAL OBJECT LOCATION and LAST LOGICAL\n" + 
                        "OBJECT LOCATION fields as logical object identifier\n" + 
                        "values, relative to a partition.";
        }
        
        
        val == 0x1 : 
        { 
            str = "SHORT FORM VENDOR";
            tooltip += str +
                        "\n\nDevice server shall return 20 bytes of data with\n" + 
                        "the FIRST LOGICAL OBJECT LOCATION and LAST LOGICAL\n" + 
                        "OBJECT LOCATION fields as vendor-specific values.";
        }
            
            
        val == 0x6 : 
        { 
            str = "LONG FORM";
            tooltip += str + "\n\nDevice server shall return 32 bytes of data.";
        }
                
        
        
        val == 0x8 : 
        { 
            str = "EXTENDED FORM";
            tooltip += str +
                        "\n\nDevice server shall return 28 bytes of data up\n" + 
                        "to the maximum length specified by the ALLOCATION\n" + 
                        "LENGTH field.";
        }            
            
        
        default    : SetReservedError();
    };
    
	options = [ ["SHORT FORM BLOCK ID", 0], ["SHORT FORM VENDOR", 1], ["LONG FORM", 6], ["EXTENDED FORM", 8]];
   
    AddBlockPLCell( "SERVICE ACTION", str, tooltip + AddErrorTooltip(), error, [_CELLINFO, 0, options ] );
    
    #-----------------------------------------------------------------------------------------
    
    
   PLReservedCheck(8);
   PLReservedCheck(8);
   PLReservedCheck(8);
   PLReservedCheck(8);
   PLReservedCheck(8);
   
   ShowAllocLen(16);   
}
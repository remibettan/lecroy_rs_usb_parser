#
#  Copyright (c) 2015, Teledyne LeCroy - All Rights Reserved
#
#  SCSI_CDB_Locate.inc
#
#  SCSI CDB Sanitize decoder functions
################################################################################


ShowSanitize()
{
    #--------------------------- IMMED ------------------------------------------
    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("IMMED"   , GetBitStr(), "If the immediate (IMMED) bit is set to zero, then the device server " +
                                            "shall return status after the sanitize operation is completed. If the " +
                                            "IMMEDbit set to one, then the device server shall return status as soon " +
                                            "as the CDB and parameter data, if any, have been validated.", 
                                            FieldColor, [_CELLINFO, 0, options ]);

    #--------------------------- Reserved ------------------------------------------                                            
    PLReservedCheck(1);

    #--------------------------- AUSE ------------------------------------------   
    AddBlockPLCell("AUSE"   , GetBitStr(), "Allow Unrestricted Sanitize ", FieldColor, [_CELLINFO, 0, options ]);
    
    #--------------------------- Service Action ------------------------------------------   
    val = NextNBits_(5);
    
    ClearError();
       
    select
    {
        val == 0x01 : { str = "OVERWRITE";              tooltip += "Perform a sanitize overwrite operation"; }    
        val == 0x02 : { str = "BLOCK ERASE";            tooltip += "Perform a sanitize block erase operation"; }
        val == 0x03 : { str = "CRYPTOGRAPHIC ERASE";    tooltip += "Perform a sanitize cryptographic erase operation"; }
        val == 0x1F : { str = "EXIT FAILURE MODE";      tooltip += "Exit the sanitize failure mode"; }
        default    : SetReservedError();
    };
    
    options = [ ["OVERWRITE", 0x01], ["BLOCK ERASE", 0x02], ["CRYPTOGRAPHIC ERASE", 0x03], ["EXIT FAILURE MODE", 0x1F] ];
    
    AddBlockPLCell("SERVICE ACTION", str, tooltip, error, [_CELLINFO, 0, options ]);
        
    #--------------------------- Reserved ------------------------------------------   
    PLReservedCheck(40);
    
    #--------------------------- Parameter List Length List ------------------------------------------   
    ShowParamListLen( 16 );
}

#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_Rebuild16.inc
#
#  SCSI CDB REBUILD(16) (SBC-3) Command decoder functions
#
################################################################################

const CDB_IS_GENERATE = 0xFFFF;


ShowRebuild16( is_regenerate )
{
     PLReservedCheck(3);    
    
    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("DPO"    , GetBitStr(), "DPO bit field.", FieldColor, [_CELLINFO, 0, options ]);
    
    AddBlockPLCell("FUA"    , GetBitStr(), "FUA bit field.", FieldColor, [_CELLINFO, 0, options ]);

    AddBlockPLCell("INTDATA", GetBitStr(), "Intermediate data (INTDATA) bit.", FieldColor, [_CELLINFO, 0, options ]);
    
    ShowPortControl();    
    ShowLBA(32);
    
    str = "REBUILD LENGTH";
    tooltip = "The REBUILD LENGTH field specifies the number\n" + 
    "of blocks to be written to the medium. It\n" + 
    "also specifies the number of blocks that\n" + 
    "are read from each source.";    
    
    
    if( is_regenerate == CDB_IS_GENERATE )
    {
        str = "REGENERATE LENGTH";
        tooltip = "The REGENERATE LENGTH field indicates the length\n" + 
        "in logical blocks of the resulting XOR data.\n" + 
        "It also specifies the length in logical blocks\n" + 
        "that is transferred from each of the specified\n" + 
        "sources.";
    }
      
    AddBlockPLCell( str, Format("%u", NextNBits_(32)), tooltip );
    
    
    ShowParamListLen();
    PLReservedCheck(8);   
}


ShowRegenerate16( )
{
    ShowRebuild16( CDB_IS_GENERATE );
}
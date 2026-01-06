#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_ReadCapacity.inc
#
#  SCSI CDB ReadCapacity Commands decoder functions
################################################################################



ShowReadCapacity10()
{
    PLReservedCheck( 7 );
    
    options = [ ["set", 1], ["Not set", 0] ];
           
    AddBlockPLCell("Obsolete", GetBitStr(), "Obsoleted  field.", FieldColor, [_CELLINFO, 0, options ]);
    
    #------------------------------ Get PMI ------------------------------        
    val = GetBitOffset(); # saving global bit offset
    NextNBits(32+8+8+7);
    
    pmi = NextNBits(1);
    
    error       = null;
    err_tooltip = "";
    
    GetNBits( in.Data, val, 0 ); # restore offset 

    if( !pmi && NextNBits(32) ) # LBA should be zero
    {
        error = _ERROR;
        error_tooltip = WARNING_SIGN + "When PMI bit is zero LBA should be zero too !!!";
    }
    
    GetNBits( in.Data, val, 0 ); # restore offset 
    #---------------------------------------------------------------------
            
    ShowLBA( 32, error, error_tooltip );
    
    PLReservedCheck( 8 );
    PLReservedCheck( 8 );
    PLReservedCheck( 7 );
    
    
    
    AddBlockPLCell("PMI", GetBitStr(), 
    "A partial medium indicator (PMI) bit of zero indicates that\n" + 
    "the RETURNED LOGICAL BLOCK ADDRESS and the BLOCK LENGTH\n" + 
    "IN BYTES are those of the last logical block on the block\n" + 
    "device. A PMI bit of one indicates that the RETURNED LOGICAL\n" + 
    "BLOCK ADDRESS and BLOCK LENGTH IN BYTES are those of the\n" + 
    "last logical block address before a substantial delay in\n" + 
    "data transfer may be encountered.", FieldColor, [_CELLINFO, 0, options ]);
}


ShowReadCapacity16()
{
    PLReservedCheck( 3 );
    
    #-------------------------- Service Action ---------------------------
    val = NextNBits_(5);
    
    error       = null;
    err_tooltip = "";
    
    if( val != 0x10 )
    {
        error = _ERROR;
        err_tooltip = "Service action for this command should be 10h !!!";
    }
    
    AddBlockPLCell("SERVICE ACTION", Format("%02Xh", val ), "SERVICE ACTION field" +
    AddWarningTooltip( err_tooltip ), error, [_CELLINFO, 1] );
    #---------------------------------------------------------------------
    
    #------------------------------ Get PMI ------------------------------        
    val = GetBitOffset(); # saving global bit offset
    NextNBits(8+64+32+6+1);
    
    pmi = NextNBits(1);
    
    error       = null;
    err_tooltip = "";    
    
    GetNBits( in.Data, val, 0 ); # restore offset 

    if( !pmi && ( NextNBits(32) || NextNBits(32) ) ) # LBA should be zero
    {
        error = _ERROR;
        error_tooltip = WARNING_SIGN + "When PMI bit is zero LBA should be zero too !!!";
    }
    
    GetNBits( in.Data, val, 0 ); # restore offset 
    #---------------------------------------------------------------------
    
    
    ShowLBA( 64, error, error_tooltip );
    ShowAllocLen( 32 );
    
    PLReservedCheck( 6 );
    ShowRELADR();
    
    options = [ ["set", 1], ["Not set", 0] ];
    
    AddBlockPLCell("PMI", GetBitStr(), 
    "A partial medium indicator (PMI) bit of zero indicates that\n" + 
    "the RETURNED LOGICAL BLOCK ADDRESS and the BLOCK LENGTH\n" + 
    "IN BYTES are those of the last logical block on the block\n" + 
    "device. A PMI bit of one indicates that the RETURNED LOGICAL\n" + 
    "BLOCK ADDRESS and BLOCK LENGTH IN BYTES are those of the\n" + 
    "last logical block address before a substantial delay in\n" + 
    "data transfer may be encountered.", FieldColor, [_CELLINFO, 0, options ]);
}
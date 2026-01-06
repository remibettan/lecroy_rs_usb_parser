#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_Erase.inc
#
#  SCSI CDB Erase Commands decoder functions
################################################################################





ShowErase6()
{
    PLReservedCheck(6);     
     
	options = [ ["set", 1], ["Not set", 0] ];     
    AddBlockPLCell("IMMED", GetBitStr(), 
         "An immediate (IMMED) bit of one specifies the\n" + 
         "device server shall return status as soon as\n" + 
         "the command descriptor block has been validated.", FieldColor, [_CELLINFO, 0, options ]);
         
    AddBlockPLCell("LONG" , GetBitStr(), "The LONG bit field.", FieldColor, [_CELLINFO, 0, options ]);
    
	PLReservedCheck(2);	
	AddBlockPLCell("METHOD", Format("0x%01X", NextNBits_(2)), "METHOD field.");    
	PLReservedCheck(2);
    AddBlockPLCell("SMD" , GetBitStr(), "The SMD bit field.", FieldColor, [_CELLINFO, 0, options ]);
    AddBlockPLCell("VCM" , GetBitStr(), "The VCM bit field.", FieldColor, [_CELLINFO, 0, options ]);

    PLReservedCheck(8);
    PLReservedCheck(8);
}



ShowErase10()
{
    PLReservedCheck( 5 );    
    
    options = [ ["set", 1], ["Not set", 0] ];
    
    AddBlockPLCell("ERA", GetBitStr(), "An erase all (ERA) bit field.", FieldColor, [_CELLINFO, 0, options ]);
    PLReservedCheck( 1 );
        
    ShowRELADR();    
    ShowLBA(32);
    
    PLReservedCheck( 8 );
    ShowTransferLen( 16 );
}




ShowErase12()
{    
    PLReservedCheck( 5 );
    
    options = [ ["set", 1], ["Not set", 0] ];
    
    AddBlockPLCell("ERA", GetBitStr(), "An erase all (ERA) bit field.", FieldColor, [_CELLINFO, 0, options ]);
    PLReservedCheck( 1 );
        
    ShowRELADR();    
    ShowLBA(32);
    
    ShowTransferLen( 32 );
    PLReservedCheck( 8 );
}


ShowErase16()
{
	PLReservedCheck( 4 );
	
	options = [ ["set", 1], ["Not set", 0] ];     
    
    AddBlockPLCell("FCS" , GetBitStr(), "An FCS bit of zero specifies this command is\n" + 
		"not the first command in a tagged write sequence."
		,FieldColor, [_CELLINFO, 0, options ]);
    
    AddBlockPLCell("LCS" , GetBitStr(), "An LCS bit of zero specifies this command is\n" + "
		not the last command in a tagged write sequence."
		,FieldColor, [_CELLINFO, 0, options ]);
    
    AddBlockPLCell("IMMED", GetBitStr(), 
         "An immediate (IMMED) bit of one specifies the\n" + 
         "device server shall return status as soon as\n" + 
         "the command descriptor block has been validated.", FieldColor, [_CELLINFO, 0, options ]);
         
    AddBlockPLCell("LONG" , GetBitStr(), "The LONG bit field.", FieldColor, [_CELLINFO, 0, options ]);	
    
   	PLReservedCheck(2);	
   	tooltip = null;
   	ClearError();
   	val = NextNBits_(2);
   	select
    {
		val == 0b00 : tooltip = "Vendor specific";
		val == 0b01 : tooltip = "Upon successful processing of the command the volume\n" + "may contain fragments of data specified for erasure.";
		val == 0b10 : tooltip = "Upon successful processing of the command the volume\n" + "shall not contain fragments of data specified for erasure.";
		
		default: SetReservedError();
    };
    
	AddBlockPLCell("METHOD", Format("0x%01X", val), "METHOD field.\n" + tooltip + AddErrorTooltip(), error );    
	PLReservedCheck(2);
    AddBlockPLCell("SMD" , GetBitStr(), "The SMD bit field.", FieldColor, [_CELLINFO, 0, options ]);
    AddBlockPLCell("VCM" , GetBitStr(), "The VCM bit field.", FieldColor, [_CELLINFO, 0, options ]);


    AddBlockPLCell("PARTITION", GetFld8H(), 
        "PARTITION field.\n\n" +
        "This field specifies the partition to select\n" +
        "if the CP bit is one."  );   
         
    AddBlockPLCell("LOGICAL OBJECT IDENTIFIER", GetFld64(), 
        "LOGICAL OBJECT IDENTIFIER field.\n\n" +
        "specify the position at which the ERASE(16)\n" +
		"command shall start.");   
 
   PLReservedCheck( 8 );
   PLReservedCheck( 8 );
   PLReservedCheck( 8 );
}
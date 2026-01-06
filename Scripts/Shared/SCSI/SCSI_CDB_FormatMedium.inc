#
#  Copyright (c) 2010, LeCroy - All Rights Reserved
#
#  SCSI_CDB_FormatMedium.inc
#
#  SCSI CDB FORMAT MEDIUM Command decoder functions
################################################################################


ShowFormatMedium()
{
	PLReservedCheck( 6 );
	
	options = [ ["set", 1], ["Not set", 0] ]; 
	AddBlockPLCell("VERIFY", GetBitStr(), "VERIFY.", FieldColor, [_CELLINFO, 0, options ]);
         	
	AddBlockPLCell("IMMED", GetBitStr(), 
         "An immediate (IMMED) bit of one specifies the\n" + 
         "device server shall return status as soon as\n" + 
         "the command descriptor block has been validated.", FieldColor, [_CELLINFO, 0, options ]);
         
	PLReservedCheck( 4 );         
	
   	tooltip = "Meaning : ";
   	ClearError();
   	val = NextNBits_(4);
   	select
    {
		val == 0x0 : { str = "Use default format"; tooltip += "Use default format";}
		val == 0x1 : { str = "Partition volume"; tooltip += "Partition volume.";}
		val == 0x2 : { str = "Default frmt & partition"; tooltip += "Default format then partition.";}
		
		val >= 0x8
		&& val <= 0xF : tooltip = "Vendor specific.";
		
		default: SetReservedError();
    };
    
    options = [ ["Use default format", 0], ["Partition volume", 1], ["Default frmt & partition", 2]];
    
	AddBlockPLCell("Format", str, "Format field.\n" + tooltip + AddErrorTooltip(), error, [_CELLINFO, 0, options ] );  
	
	ShowTransferLen( 16 );
}
#
#  Copyright (c) 2010, LeCroy. - All Rights Reserved
#
#  SCSI_CDB_ReportKey.inc
#
#  SCSI CDB REPORT KEY Command decoder functions
################################################################################


ShowReportKey()
{
 
    PLReservedCheck(8);
    
	val = NextNBits_(32);
	AddBlockPLCell(	"Reserved/Logical Block Address/Starting Offset", Format ("0x%08X", val), 
					"Reserved/Logical Block Address/Starting Offset field.\n\n"	+
					"The field is dependent upon the Key Class and Key Format Fields." );
	
	
	val = NextNBits_(8);
	AddBlockPLCell(	"Reserved/Block Count Function", Format ("0x%02X", val), 
					"Reserved/Block Count Function field.\n\n"		+
					"The field is dependent upon the Key Class\n"	+
					"and Key Format Fields." );
	
	
	ShowKeyClass();
		
	ShowAllocLen(16);
	
	
	val = NextNBits_(2);
	AddBlockPLCell(	"AGID", Format ("0x%X", val), 
					"AGID field.\n\n"		+
					"The field is used to control simultaneous\n"		+
					"key exchange sequences." );
	
		
	val = NextNBits_(6);
	AddBlockPLCell(	"Key Format", Format ("0x%02X", val), 
					"Key Format field.\n\n"		+
					"The Key Format field indicates the types of\n"		+
					"information that is to be sent to the Host." );
					
}



ShowKeyClass()
{
	val = NextNBits_(8);
		
	base_tooltip =	"Key Class field.\n\n" +
					Format("Value   : 0x%02X\n", val)	+
					"Meaning : ";
	
	ClearError();
    select
    {		
    
		val == 0x00 :
		{	
			tooltip	= "DVD CSS/CPPM or CPRM";
		}		
		
		val == 0x01 :
		{
			tooltip	= "Obsolete";
		}
		
		val == 0x02 :
		{
			tooltip	= "AACS";			
		}
				 
		(val >= 0x03) && (val <= 0x1F) :
		{
			tooltip	= "Reserved";
		}
		
		val == 0x20 :
		{
			tooltip	= "Legacy";		
		}
		
		val == 0x21 :
		{
			tooltip	= "SecurDisc";	
		}
		
		(val >= 0x22) && (val <= 0xFF) :
		{
			str		= "Reserved";
		}
	};	
	
	base_tooltip += tooltip;
	
	
	AddBlockPLCell("Key Class", Format ("0x%02X", val), base_tooltip);
}


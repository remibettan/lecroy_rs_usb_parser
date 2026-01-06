#
#  Copyright (c) 2010, LeCroy. - All Rights Reserved
#
#  SCSI_CDB_ReadTocPmaAtip.inc
#
#  SCSI CDB READ TOC/PMA/ATIP Command decoder functions
################################################################################


ShowReadTocPmaAtip()
{
 
    PLReservedCheck(6);

	options = [ ["set", 1], ["Not set", 0] ];
		
	AddBlockPLCell(	"MSF", GetBitStr(), 
					"MSF field.\n\n"		+
					"Bit 0: Address in some data formats shall be in LBA form. \n" + 
					"Bit 1: Address in some data formats shall be in MSF form.", FieldColor, [_CELLINFO, 0, options ]);
	
	
	PLReservedCheck(1);
	PLReservedCheck(4);
	

	ShowFormat();
	
	
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);

	
	val = NextNBits_(8);
	AddBlockPLCell(	"Track/Session Number", Format ("0x%02X", val), 
					"Track/Session Number field.\n\n"	+
					"The Track/Session Number field provides a method to restrict\n"		+
					"the returned of some data formats to a specific session\n"				+ 
					"or a track range." );
	
	ShowAllocLen(16);
	
}


ShowFormat()
{
	val = NextNBits_(4);
	
	
	base_tooltip =	"Format field.\n"	+
					"This field is use to select specific returned data format.\n\n"	+ 
					Format("Value   : 0x%X\n", val)	+
					"Meaning : ";
	
	ClearError();
    select
    {		
    
		val == 0b0000 :
		{	
			tooltip =	"The Track/Session Number field specifies starting track\n"	+ 
						"number for which the data is returned.";
		}		
		
		val == 0b0001 :
		{
			tooltip =	"This format returns the first complete session number,\n"	+ 
						"last complete session number and last complete\n"			+ 
						"session starting address.";		
		}
		
		val == 0b0010 :
		{
			tooltip =	"This format returns all Q sub-code data in the Lead-In\n"	+
						"(TOC) areas starting from a session number as specified\n"	+ 
						"in the Track/Session Number field.";		
		}
		
		val == 0b0011 :
		{
			tooltip =	"This format returns Q sub-channel data in the PMA area.";		
		}
		
		val == 0b0100 :
		{
			tooltip =	"This format returns ATIP data.";		
		}
				 
		val == 0b0101 :
		{
			tooltip =	"This format returns CD-TEXT information that is recorded\n"	+
						"in the Lead-in area as R-W Sub-channel Data.";		
		}
			 
		(val >= 0b0110) && (val <= 0b1111) :
		{
			tooltip	= "Reserved";
		}
		
	};	
	
	base_tooltip += tooltip;
	
	
	AddBlockPLCell("Format", Format ("0x%X", val), 	base_tooltip);

}
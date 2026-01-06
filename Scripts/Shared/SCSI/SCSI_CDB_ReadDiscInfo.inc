#
#  Copyright (c) 2010, LeCroy. - All Rights Reserved
#
#  SCSI_CDB_ReadDiscInfo.inc
#
#  SCSI CDB READ DISC INFORMATION Command decoder functions
################################################################################


ShowReadDiscInfo()
{
 
    PLReservedCheck(5);
    
    
    ShowDataType();
	
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	ShowAllocLen(16);
	
}



ShowDataType()
{
	val = NextNBits_(3);
	
	base_tooltip =	"Data Type field.\n\n" +
					Format("Value   : 0x%X\n", val)	+
					"Meaning : ";
	
	ClearError();
    select
    {		
    
		val == 0b000 :
		{	
			tooltip	= "Standard Disc Information";
		}		
		
		val == 0b001 :
		{
			tooltip	= "Track Resources Information";
		}
		
		val == 0b010 :
		{
			tooltip	= "POW Resources Information";
		}
		 
		(val >= 0b011) && (val <= 0b111) :
		{
			tooltip	= "Reserved";
		}
		
	};	
	
	base_tooltip += tooltip;
	
	AddBlockPLCell(	"Data Type",Format ("0x%X", val), base_tooltip );
	
}
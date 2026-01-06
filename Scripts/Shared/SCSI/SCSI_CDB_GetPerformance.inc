#
#  Copyright (c) 2010, LeCroy. - All Rights Reserved
#
#  SCSI_CDB_GetPerformance.inc
#
#  SCSI CDB GET PERFORMANCE Command decoder functions
################################################################################


ShowGetPerformance()
{
 
    PLReservedCheck(3);
    
	val = NextNBits_(5);
	AddBlockPLCell( "Data Type", Format ("0x%02X", val), 
					"Data Type field.\n\n"	+
					"The field definition is dependent upon the Type field value."	);
					
	
	val = NextNBits_(32);
	AddBlockPLCell(	"Starting LBA", Format ("0x%08X", val), 
					"Starting LBA field.\n\n"	+
					"The field is determined by the contents of the Type field."	);
	
	
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	
	val = NextNBits_(16);
	AddBlockPLCell(	"Maximum Number of Descriptors", Format ("0x%04X", val), 
					"Maximum Number of Descriptors field.\n\n"	+
					"The Drive shall not return more performance descriptors\n"		+
					"than specified by the Maximum Number of Descriptors field."	);
	
	ShowType();
}


ShowType()
{
	val = NextNBits_(8);
	
	base_tooltip =	"Type field.\n\n" +
					Format("Value   : 0x%02X\n", val)	+
					"Meaning : ";
	
	ClearError();
    select
    {		
    
		val == 0x00 :
		{	
			str		= "Performance data";
			tooltip = "Required by the Real-time Streaming Feature.";
		}		
		
		val == 0x01 :
		{
			str		= "Unusable Area data";
			tooltip = "Required when SW bit of Real-time Streaming\n"		+ 
					  "Feature is set to 1.";			
		}
		
		val == 0x02 :
		{
			str		= "Defect Status data";
			tooltip = "Required when TSR Feature is supported.";
		}
		 
		val == 0x03 :
		{
			str		= "Write Speed Descriptor";
			tooltip = "Required if WSPD bit of Real-time Streaming\n"		+
					  "Feature is set to 1.";
		}
		
		val == 0x04 :
		{
			str		= "DBI";
			tooltip = "Optional for BD drives.";
		}
		
		val == 0x05 :
		{
			str		= "DBI Cache Zone";
			tooltip = "Optional for BD drives.";
		}
		
		( val >= 0x06 ) && ( val <= 0xFF ):
		{
			str		=	"Reserved";
			tooltip = str;
		}
	};	
	
	base_tooltip += str + "\n\n" + tooltip;
	
	options = [ ["Performance data", 0], ["Unusable Area data", 1], ["Defect Status data", 2], ["Write Speed Descriptor", 3], 
				["DBI", 4], ["DBI Cache Zone", 5] ];
	
	AddBlockPLCell(	"Type", str, base_tooltip, FieldColor, [_CELLINFO, 0, options ] );

}
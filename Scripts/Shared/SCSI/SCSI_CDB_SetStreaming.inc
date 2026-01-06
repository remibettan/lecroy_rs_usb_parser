#
#  Copyright (c) 2010, LeCroy. - All Rights Reserved
#
#  SCSI_CDB_SetStreaming.inc
#
#  SCSI CDB SET STREAMING Command decoder functions
################################################################################


ShowSetStreaming()
{
 
    PLReservedCheck(8);
    PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	
	val = NextNBits_(8);
	
	base_tooltip =	"Type field.\n"			+
					"Specify the type of data that shall be transferred.\n\n"	+
					Format("Value   : 0x%02X\n", val)		+
					"Meaning : ";
					
	ClearError();
	select
	{
		val == 0x00 :
		{
			tooltip = "Performance descriptor";
		}
		
		(val >= 0x01) && ( val <= 0x04) :
		{
			tooltip = "Reserved";
		}
		
		val == 0x05 :
		{
			tooltip = "DBI cache zone descriptor";
		}
		
		(val >= 0x06) && ( val <= 0xFF) :
		{
			tooltip = "Reserved";
		}
	};
		
	base_tooltip +=  tooltip;

	AddBlockPLCell(	"Type", Format ("0x%02X", val), base_tooltip );
	
	
	ShowParamListLen(16);
	
}


#
#  Copyright (c) 2010, LeCroy. - All Rights Reserved
#
#  SCSI_CDB_SendDiscStruct.inc
#
#  SCSI CDB SEND DISC STRUCTURE Command decoder functions
################################################################################


ShowSendDiscStruct()
{
 
    PLReservedCheck(4);
    
	
	ShowMediaType();
	
	
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
		
	
	val = NextNBits_(8);
	AddBlockPLCell(	"Format Code", Format ("0x%02X", val), 
					"Format Code field.\n\n"		+
					"The Format Code specifies the type of\n"		+
					"information to be sent to the Drive." );
	
	
	ShowParamListLen(16);
	
	
	val = NextNBits_(2);
	AddBlockPLCell(	"AGID", Format ("0x%X", val), 
					"AGID field.\n\n"				+
					"The field is used to control simultaneous\n"	+
					"key exchange sequences." );
					
					
	PLReservedCheck(6);
	
}

ShowMediaType()
{
	
	val = NextNBits_(4);
	
	base_tooltip =	"Media Type field.\n"		+
					"The field identifies the Media Type\n"	+
					"to which this command is directed.\n\n"			+
					Format("Value   : 0x%X\n", val)		+
					"Meaning : ";
	
	ClearError();
    select
    {		
    
		val == 0x0 :
		{	
			tooltip = "DVD";
		}		
		
		val == 0x1 :
		{
			tooltip = "BD";
		}
		 
		( val >= 0x2 ) && ( val <= 0xF ):
		{
			tooltip =	"Reserved";
		}
	};	
	
	base_tooltip += tooltip;
	
	AddBlockPLCell(	"Media Type", Format ("0x%X", val), base_tooltip );
	
}
#
#  Copyright (c) 2010, LeCroy. - All Rights Reserved
#
#  SCSI_CDB_GetEventStatNotif.inc
#
#  SCSI CDB GET EVENT STATUS NOTIFICATION Command decoder functions
################################################################################


ShowGetEventStatNotif()
{
    PLReservedCheck(7);
    
	options = [ ["set", 1], ["Not set", 0] ];
	AddBlockPLCell(	"Polled", GetBitStr(), 
					"Polled field.\n\n"		+
					"Bit 0: Host requests asynchronous operation.\n"	+ 
					"Bit 1: Host requests polled operation.", FieldColor, [_CELLINFO, 0, options ] );
	
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	
	ShowNotificationClassReq();
	
	PLReservedCheck(8);
	PLReservedCheck(8);

	ShowAllocLen(16);

}

ShowNotificationClassReq()
{

	val = NextNBits_(8);
	
	base_tooltip =	"Notification Class Request field.\n\n" +
					Format("Value   : 0x%02X\n", val)	+
					"Meaning : ";
	
	ClearError();
    select
    {		
    
		(val == 0x00) || (val == 0x07) :
		{	
			str		=	"Reserved";

		}		
		
		val == 0x01 :
		{
			str		=	"Operational Change";
		
		}
		
		val == 0x02 :
		{
			str		=	"Power Management";
	
		}
		 
		val == 0x03 :
		{
			str		=	"External Request";
		
		}
		
		val == 0x04 :
		{
			str		=	"Media";
		
		}
		
		val == 0x05 :
		{
			str		=	"Multi-Host";
		
		}
		
		val == 0x06 :
		{
			str		=	"Device Busy";
		
		}
	};	
	
	base_tooltip += str;
	
	options = [ ["Operational Change", 1], ["Power Management", 2], ["External Request", 3], ["Media", 4], 
				["Multi-Host", 5], ["Device Busy", 6] ];
	
	AddBlockPLCell(	"Notification Class Request", str, base_tooltip, FieldColor, [_CELLINFO, 0, options ] );

}
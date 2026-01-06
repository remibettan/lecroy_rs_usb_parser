#
#  Copyright (c) 2010, LeCroy. - All Rights Reserved
#
#  SCSI_CDB_SetCDSpeed.inc
#
#  SCSI CDB SET CD SPEED Command decoder functions
################################################################################


ShowSetCDSpeed()
{
 
    PLReservedCheck(6);
    
	ShowRotationalCtrl();

	
	val = NextNBits_(16);
	AddBlockPLCell( "Drive Read Speed", Format ("0x%04X", val), 
					"Drive Read Speed (bytes/sec) field.\n\n"	+
					"A Drive Read Speed of 0000h through FFFEh specifies a minimum\n"	+ 
					"read speed required by the Host. A value of FFFFh requests that\n"	+ 
					"the Drive Read Speed be set for optimal performance." );
	
	
	val = NextNBits_(16);
	AddBlockPLCell( "Drive Write Speed", Format ("0x%04X", val), 
					"Drive Write Speed (bytes/sec)field\n\n"	+
					"A Drive Write Speed of 0000h through FFFEh specifies the write\n"	+ 
					"speed required by the Host. A value of FFFFh requests that\n"		+ 
					"the Drive Write Speed be set for optimal performance." );
	
	
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	
}


ShowRotationalCtrl()
{
	val = NextNBits_(2);
	
	
	base_tooltip =	"Rotational Control field.\n"				+
					"Identify how the Drive shall interpret\n"	+ 
					"the requested Drive Write Speed.\n\n"		+	
					Format("Value   : 0x%X\n", val)				+
					"Meaning : ";
	
	
	ClearError();
	select
	{
		val == 0b00 : 
		{
			str = "CLV and non-pure CAV";
			tooltip = str;
		}
		
		val == 0b01 : 
		{
			str = "Pure CAV";
			tooltip = str;
		}
		
		(val == 0b10) || (val == 0b11) : 
		{
			str = "Reserved";
			tooltip = str;
		}
	};
	
	base_tooltip += str;
	
	options = [ ["CLV and non-pure CAV", 0], ["Pure CAV", 1] ];
	
	AddBlockPLCell(	"Rotational Control", str, base_tooltip, FieldColor, [_CELLINFO, 0, options ]);


}
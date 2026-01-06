#
#  Copyright (c) 2010, LeCroy. - All Rights Reserved
#
#  SCSI_CDB_LoadUnloadMedium.inc
#
#  SCSI CDB LOAD UNLOAD MEDIUM Command decoder functions
################################################################################


ShowLoadUnloadMedium()
{
    PLReservedCheck(7);
    
    options = [ ["set", 1], ["Not set", 0] ];
	AddBlockPLCell(	"IMMED", GetBitStr(), 
					"IMMED field.\n\n"		+
					"Bit 0: Terminate command when load/unload operation completed.\n" + 
					"Bit 1: Drive will return status when CDB has been validated." ,FieldColor, [_CELLINFO, 0, options ]);
	
	
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(6);
	
	
	AddBlockPLCell(	"LoUnlo", GetBitStr(), 
					"LoUnlo field.\n ",FieldColor, [_CELLINFO, 0, options ]);
	
	
	AddBlockPLCell(	"Start", GetBitStr(), 
					"Start field.\n",FieldColor, [_CELLINFO, 0, options ]);
		
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	
	val = NextNBits_(8);
	AddBlockPLCell(	"Slot", Format ("0x%02X", val), 
					"Slot field.\n\n"	+
					"The Slot field indicates the Slot to be loaded.");
					
	
	PLReservedCheck(8);
	PLReservedCheck(8);
	

}
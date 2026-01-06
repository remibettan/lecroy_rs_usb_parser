#
#  Copyright (c) 2010, LeCroy. - All Rights Reserved
#
#  SCSI_CDB_ReadTrackInfo.inc
#
#  SCSI CDB READ TRACK INFORMATION Command decoder functions
################################################################################


ShowReadTrackInfo()
{
 
    PLReservedCheck(5);
    	
    options = [ ["set", 1], ["Not set", 0] ];
	AddBlockPLCell(	"Open", GetBitStr(), 
					"Open field.\n\n"		+
					"Bit 0: Locate Logical Track according to Logical Block \n"				+
					"       Address/Track/Session Number.\n"								+ 
					"Bit 1: Locate the first open Logical Track\ that is greater or\n"		+ 
					"       equal to the Logical Block Address/Track/Session Number." , FieldColor, [_CELLINFO, 0, options ]);
       
              
	val = NextNBits_(2);
	AddBlockPLCell(	"Address/Number Type", Format ("0x%X", val), 
					"Address/Number Type field.\n\n"						+
					"This field is used to specify the contents of\n"		+
					"the Logical Block Address/Track/Session Number." );
	
	
	val = NextNBits_(32);
	AddBlockPLCell(	"Logical Block Address/Track/Session Number", Format ("0x%08X", val), 
					"Logical Block Address/Track/Session Number field.\n\n"				+	
					"This field either directly or indirectly specifies the Logical\n"	+
					"Track Number for which the Drive is to provide track information." );
	
	
	PLReservedCheck(8);
		
	ShowAllocLen(16);
	
}


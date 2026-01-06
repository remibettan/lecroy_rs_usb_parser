#
#  Copyright (c) 2010, LeCroy. - All Rights Reserved
#
#  SCSI_CDB_RepairTrack.inc
#
#  SCSI CDB REPAIR TRACK Command decoder functions
################################################################################


ShowRepairTrack()
{
 
    PLReservedCheck(7);
    
    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell(	"IMMED", GetBitStr(), 
					"IMMED field.\n\n"		+
					"Bit 0: Return status when repair operation is completed.\n" + 
					"Bit 1: Return status once the CDB has been validated." , FieldColor, [_CELLINFO, 0, options ]);
	
	
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	
	val = NextNBits_(16);
	AddBlockPLCell(	"Logical Track Number",Format ("0x%04X", val), 
					"Logical Track Number field.\n\n"		+
					"The field specifies the Logical Track that requires repair.");
	
	
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	

}
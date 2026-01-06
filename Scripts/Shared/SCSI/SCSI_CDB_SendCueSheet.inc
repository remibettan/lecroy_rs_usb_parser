#
#  Copyright (c) 2010, LeCroy. - All Rights Reserved
#
#  SCSI_CDB_SendCueSheet.inc
#
#  SCSI CDB SEND CUE SHEET Command decoder functions
################################################################################


ShowSendCueSheet()
{
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);

    
	val = NextNBits_(24);
	AddBlockPLCell(	"Cue Sheet Size",Format ("0x%06X", val), 
					"Cue Sheet Size field.\n\n"		+
					"The number of bytes in the cue sheet\n"	+
					"to be sent to the Logical Unit." );
	
}
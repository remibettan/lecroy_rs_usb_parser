#
#  Copyright (c) 2010, LeCroy. - All Rights Reserved
#
#  SCSI_CDB_ReserveTrack.inc
#
#  SCSI CDB RESERVE TRACK Command decoder functions
################################################################################


ShowReserveTrack()
{
 
    PLReservedCheck(7);
    
    options = [ ["set", 1], ["Not set", 0] ];

	AddBlockPLCell(	"ARSV", GetBitStr(), 
					"ARSV field.\n\n"		+
					"The ARSV bit defines the format the\n"		+ 
					"Logical Track Reservation Parameter." , FieldColor, [_CELLINFO, 0, options ]);

	
	val = NextNBits_(56);
	AddBlockPLCell(	"Logical Track Reservation Parameter", Format ("0x%014X", val), 
					"Logical Track Reservation Parameter field.\n\n"				+
					"If ARSV is zero, Logical Track Reservation Parameter\n"	+
					"has the Reservation Size format. If ARSV is one,\n"		+
					"Logical Track Reservation Parameter has the LBA format." );
					

}
#
#  Copyright (c) 2010, LeCroy. - All Rights Reserved
#
#  SCSI_CDB_Blank.inc
#
#  SCSI CDB BLANK Command decoder functions
################################################################################


ShowBlank()
{
 
    PLReservedCheck(3);
    
	val = NextNBits_(1);
	AddBlockPLCell(	"IMMED", Format ("0x%X", val), 
					"IMMED field.\n\n"									+
					"Bit 0: Return status when the peration is completed.\n"	+ 
					"Bit 1: Return status once the operation begins.");
	
	
	PLReservedCheck(1);
		
	blank_type = NextNBits_(3);
    
    tooltip = "Blanking Type field.\n" + 
    Format("Value   : 0x%X\n", blank_type) +
           "Meaning : ";           
    
    ClearError();
    select
    {
		blank_type == 0b000: {str = "Blank the disc"; tooltip += "The entire disc is to be blanked";}
		blank_type == 0b001: {str = "Minimally blank the disc"; tooltip += "Blanks only the PMA, disc Lead-in and the pre-gap of the first track";}
		blank_type == 0b010: {str = "Blank a Track"; tooltip += "Blanks the track specified in the Start Address/Track Number field";}
		blank_type == 0b011: {str = "Un-reserve a Track"; tooltip += "All data for the last track in the incomplete session shall be blanked.";}
		blank_type == 0b100: {str = "Blank a Track Tail"; tooltip += "This blank type is valid only for packet tracks within the incomplete session.";}
		blank_type == 0b101: {str = "Unclose the last complete session"; tooltip += "If the disc is blank or the last session is not empty and\n" + "not closed, then this command shall be terminated with GOOD status.";}
		blank_type == 0b110: {str = "Blank the last non-empty Session"; tooltip += "If the last session is empty, then the Lead-in, program area\n" + "and Lead-out of the last compete session shall be blanked.";}
		
		default    : SetReservedError();
    };		
		
    options = [["Blank the disc", 0], ["Minimally blank the disc", 1] , ["Blank a Track", 2], ["Un-reserve a Track",3 ],
		["Blank a Track Tail" , 4], ["Unclose the last complete session", 5], ["Blank the last non-empty Session", 6]];
		
	AddBlockPLCell( "Blanking Type", str, tooltip + AddErrorTooltip(), error,  [_CELLINFO, 0, options ] ); 
		
	val = NextNBits_(32);
	AddBlockPLCell(	"Start Address/Logical Track Number", Format ("0x%08X", val),
					"Start Address/Logical Track Number field.\n\n"		+
					"The field specifies the area that needs to be blanked.");
	
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	
}

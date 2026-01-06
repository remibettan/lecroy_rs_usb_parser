#
#  Copyright (c) 2010, LeCroy. - All Rights Reserved
#
#  SCSI_CDB_ReadDiscStruct.inc
#
#  SCSI CDB READ DISC STRUCTURE Command decoder functions
################################################################################


ShowReadDiscStruct()
{
 
    PLReservedCheck(4);
    
	ShowMediaType();

	
	val = NextNBits_(32);
	AddBlockPLCell(	"Address", Format ("0x%08X", val), 
					"Address field.\n\n"			+
					"The Address field definition is dependent\n"	+
					"upon the value in the Format field." );
	
	
	val = NextNBits_(8);
	AddBlockPLCell( "Layer Number", Format ("0x%02X", val), 
					"Layer Number field.\n\n"		+	
					"Use of the Layer Number field is dependent\n"	+
					"upon the Media Type and Format fields." );
	
	
	val = NextNBits_(8);
	AddBlockPLCell(	"Format", Format ("0x%02X", val), 
					"Format field.\n\n"				+
					"The Format field specifies the disc structure\n"	+ 
					"that is requested by the Host." );
	
			
	ShowAllocLen(16);
	
	
	val = NextNBits_(2);
	AddBlockPLCell(	"AGID", Format ("0x%X", val), 
					"AGID field.\n\n"				+
					"The field is used to control simultaneous\n"		+
					"key exchange sequences." );
					
	
	PLReservedCheck(6);

}

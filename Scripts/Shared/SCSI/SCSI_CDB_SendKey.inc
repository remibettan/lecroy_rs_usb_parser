#
#  Copyright (c) 2010, LeCroy. - All Rights Reserved
#
#  SCSI_CDB_SendKey.inc
#
#  SCSI CDB SEND KEY Command decoder functions
################################################################################


ShowSendKey()
{
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
 
	val = NextNBits_(8);
	AddBlockPLCell( "Reserved Function", Format ("0x%02X", val), 
					"Reserved Function field.\n\n");
 
    ShowKeyClass();

    
    ShowParamListLen(16);
    
    val = NextNBits_(2);
	AddBlockPLCell(	"AGID", Format ("0x%X", val), 
					"AGID field.\n\n"		+
					"The field is used to control simultaneous\n"	+
					"key exchange sequences." );
    
    
	val = NextNBits_(6);
	AddBlockPLCell( "Key Format", Format ("0x%02X", val), 
					"Key Format field.\n\n"		+
					"The field indicates the types of information\n"	+
					"that is to be sent to the Drive.");
	
}
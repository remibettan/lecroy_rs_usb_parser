#
#  Copyright (c) 2010, LeCroy. - All Rights Reserved
#
#  SCSI_CDB_ReadCDMsf.inc
#
#  SCSI CDB READ CD MSF Command decoder functions
################################################################################


ShowReadCDMsf()
{
 
    PLReservedCheck(3);
    
	ShowExpectdSectorType();
	
	options = [ ["set", 1], ["Not set", 0] ];
		
	AddBlockPLCell( "DAP", GetBitStr(), 
					"DAP field.\n\n"		+
					"Bit 0: User data returned should not be modified.\n" + 
					"Bit 1: User data returned should be modified."	, FieldColor, [_CELLINFO, 0, options ]);
				
					
	PLReservedCheck(1);	
	PLReservedCheck(8);
				
				
	val = NextNBits_(8);
	AddBlockPLCell( "Starting M Field", Format ("0x%02X", val), 
					"Starting M Field field.\n\n"				+
					"Specify the absolute MSF address where\n"	+
					"the Read operation shall begin." );
	
	
	val = NextNBits_(8);
	AddBlockPLCell( "Starting S Field", Format ("0x%02X", val), 
					"Starting S Field field.\n\n"				+
					"Specify the absolute MSF address where\n"	+
					"the Read operation shall begin." );
	
	
	val = NextNBits_(8);
	AddBlockPLCell( "Starting F Field", Format ("0x%02X", val), 
					"Starting F Field field.\n\n"				+
					"Specify the absolute MSF address where\n"	+
					"the Read operation shall begin." );
	
	
	val = NextNBits_(8);
	AddBlockPLCell( "Ending M Field", Format ("0x%02X", val), 
					"Ending M Field field.\n\n"					+
					"Specify the absolute MSF address where\n"	+
					"the Read operation shall end." );
	
	
	val = NextNBits_(8);
	AddBlockPLCell( "Ending S Field", Format ("0x%02X", val), 
					"Ending S Field field.\n\n"					+
					"Specify the absolute MSF address where\n"	+
					"the Read operation shall end." );
	
	
	val = NextNBits_(8);
	AddBlockPLCell( "Ending F Field", Format ("0x%02X", val), 
					"Ending F Field field.\n\n"					+
					"Specify the absolute MSF address where\n"	+
					"the Read operation shall end." );
	
	
	AddBlockPLCell( "SYNC", GetBitStr(), 
					"SYNC field.\n\n"		+
					"Bit 0: Sync field of data sectors shall not\n"		+ 
					"       be included in the read data stream.\n"		+ 
					"Bit 1: Sync field of data sectors shall be\n"		+  
					"       included in the read data stream." , FieldColor, [_CELLINFO, 0, options ]);
	
					
	ShowHeaderCodes();				
				
					
	AddBlockPLCell( "User Data", GetBitStr(), 
					"User Data field.\n\n"		+
					"Bit 0: User Data field shall not be included\n"	+  
					"       in the read data stream.\n"					+ 
					"Bit 1: User Data field shall be included\n"		+
					"       in the read data stream." , FieldColor, [_CELLINFO, 0, options ]);
					
					
	AddBlockPLCell( "EDC & ECC", GetBitStr(), 
					"EDC & ECC field.\n\n"		+
					"Bit 0: No field that follows the user data field\n"	+ 
					"       shall be included in the read data stream.\n"	+ 
					"Bit 1: All fields that follow the user data field\n"	+ 
					"       shall be included in the read data stream." , FieldColor, [_CELLINFO, 0, options ]);
	
	ShowC2Error();

						
	PLReservedCheck(1);
	PLReservedCheck(5);

	
	ShowSubChannelSelBit();
	
	
}
#
#  Copyright (c) 2010, LeCroy. - All Rights Reserved
#
#  SCSI_CDB_ReadCD.inc
#
#  SCSI CDB READ CD Command decoder functions
################################################################################


ShowReadCD()
{
 
    PLReservedCheck(3);
    
	ShowExpectdSectorType();
	
	options = [ ["set", 1], ["Not set", 0] ];
	
	AddBlockPLCell( "DAP", GetBitStr(), 
					"DAP field.\n\n"		+
					"Bit 0: User data returned should not be modified.\n"	+ 
					"Bit 1: User data returned should be modified.", FieldColor, [_CELLINFO, 0, options ]);

	
	AddBlockPLCell( "Obsolete", GetBitStr(), 
					"Obsolete.\n", FieldColor, [_CELLINFO, 0, options ]);
	
	
	val = NextNBits_(32);
	AddBlockPLCell( "Starting Logical Block Address",Format ("0x%08X", val), 
					"Starting Logical Block Address field.\n\n"			+
					"The field specifies the logical block that\n"		+
					"read operation shall begin." );
	
	
	val = NextNBits_(24);
	AddBlockPLCell(	"Transfer Length",Format ("0x%06X", val), 
					"Transfer Length field.\n\n"	+
					"The field specifies the number of contiguous\n"	+
					"logical blocks data that shall be transferred.");
	
	
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
					"       in the read data stream.", FieldColor, [_CELLINFO, 0, options ]);
					
					
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


ShowExpectdSectorType()
{
	val = NextNBits_(3);
	
	base_tooltip =	"Expected Sector Type field.\n\n" +
					Format("Value   : 0x%X\n", val)	+
					"Meaning : ";
	
	ClearError();
    select
    {		
    
		val == 0b000 :
		{	
			str		=	"All types";
			tooltip =	"No checking of the data type is performed.";
		}		
		
		val == 0b001 :
		{
			str		=	"CD-DA";
			tooltip =	"Only CD-DA sectors shall be returned.";			
		}
		
		val == 0b010 :
		{
			str		=	"Mode 1";
			tooltip =	"Only sectors with a user data field of 2\n"	+ 
						"048 bytes shall be returned.";
		}
		 
		val == 0b011 :
		{
			str		=	"Mode 2 formless";
			tooltip =	"Only sectors with the expanded user data\n"	+ 
						"field (2 336 bytes) shall be returned.";
		}
		
		val == 0b100 :
		{
			str		=	"Mode 2 form 1";
			tooltip =	"Only sectors that have a user data field\n"	+  
						"of 2 048 bytes shall be returned.";
		}
		
		val == 0b101 :
		{
			str		=	"Mode 2 form 2";
			tooltip =	"Only sectors that have a user data field\n"	+ 
						"of 2 324 bytes shall be returned.";
		}
		
		(val >= 0b110) && (val <= 0b111) :
		{
			str		= "Reserved";
			tooltip = str;
		}
	};	
	
	base_tooltip += str + "\n\n" + tooltip;
	
	options = [ ["All types", 0], ["CD-DA", 1], ["Mode 1", 2], ["Mode 2 formless", 3], 
				["Mode 2 form 1", 4], ["Mode 2 form 2", 5] ];
	
	AddBlockPLCell(	"Expected Sector Type", str, base_tooltip, FieldColor, [_CELLINFO, 0, options ] );
	
}

ShowHeaderCodes()
{

	val = NextNBits_(2);
	
	base_tooltip =	"Header Codes field.\n\n" +
					Format("Value   : 0x%X\n", val)	+
					"Meaning : ";
	
	ClearError();
    select
    {
    
		val == 0b00 :
		{	
			tooltip	=	"No header information shall be transferred.";	 
		}		
		
		val == 0b01 :
		{
			tooltip	=	"The 4-byte sector header of data sectors\n"			+ 
						"shall be transferred.";				
		}
		
		val == 0b10 :
		{
			tooltip	=	"The 8-byte sector sub-header of mode 2 formed\n"		+
						"sectors shall be transferred.";
		}
		 
		val == 0b11 :
		{
			tooltip	=	"Both sector header and sub-header (12 bytes) shall\n"	+ 
						"be transferred. Header shall be transferred first.";
		}  
    
    };		
    
	base_tooltip += tooltip;
	

	AddBlockPLCell( "Header Codes", Format ("0x%X", val), base_tooltip);

}




ShowC2Error()
{
	val = NextNBits_(2);
	
	base_tooltip =	"C2 Error Information field.\n\n" +
					Format("Value   : 0x%X\n", val)	+
					"Meaning : ";
	
	ClearError();
    select
    {		
    
		val == 0b00 :
		{	
			tooltip	=	"No error information is returned.";	 
		}		
		
		val == 0b01 :
		{
			tooltip	=	"Return the 294 bytes of C2 error bits \n"	+ 
						"in the data stream.";				
		}
		
		val == 0b10 :
		{
			tooltip	=	"First return Block Error Byte, then a pad byte\n"	+
						"of zero and finally the 294 bytes of C2 error bits.";
		}
		 
		val == 0b11 :
		{
			tooltip	=	"Reserved";
		}
				
	};	
	
	base_tooltip +=  tooltip + "\n" ;
	
	AddBlockPLCell( "C2 Error Information", Format ("0x%X", val), base_tooltip);	

}


ShowSubChannelSelBit()
{
	val = NextNBits_(3);
	
	base_tooltip =	"Sub-channel Selection Bits field.\n\n" +
					Format("Value   : 0x%X\n", val)	+
					"Meaning : ";
	
	ClearError();
    select
    {		
    	val == 0b000 :
		{	
			tooltip		=	"No Sub-channel data shall be returned.";
		}		
		
		val == 0b001 :
		{
			tooltip		=	"Reserved";
		}
		
		val == 0b010 :
		{
			tooltip		=	"Formatted Q sub-channel data shall be transferred.";
		}
		 
		val == 0b011 :
		{
			tooltip		=	"Reserved";
		}
		
		val == 0b100 :
		{
			tooltip		=	"Corrected and de-interleaved R-W sub-channel\n"	+
							"data shall be transferred.";
		}
		
		(val >= 0b101) && (val <= 0b111) :
		{
			tooltip		=	"Reserved";
		
		}
	};

	base_tooltip +=  tooltip + "\n" ;
	
	AddBlockPLCell( "Sub-channel Selection Bits", Format ("0x%X", val), base_tooltip);	


}

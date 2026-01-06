#
#  Copyright (c) 2010, LeCroy. - All Rights Reserved
#
#  SCSI_CDB_SendOpcInfo.inc
#
#  SCSI CDB SEND OPC INFORMATION Command decoder functions
################################################################################


ShowSendOpcInfo()
{
   PLReservedCheck(7);
    
   options = [ ["set", 1], ["Not set", 0] ];
   
   AddBlockPLCell( "DoOpc", GetBitStr(), 
					"DoOpc field.\n\n"		+
					"Bit 0: Drive shall transfer the Parameter List and\n"		+ 
					"       attempt to set OPC values.\n"				+ 
					"Bit 1: Drive shall determine OPC values for\n"		+ 
					"       the current recording conditions." , FieldColor, [_CELLINFO, 0, options ]);
	
	
	PLReservedCheck(6);

    AddBlockPLCell( "Exclude1", GetBitStr(), 
					"Exclude1 field.\n\n"		+
					"Exclude1 allow the Host to select\n"	+ 
					"the layers to be calibrated."  , FieldColor, [_CELLINFO, 0, options ]);
		
	
	AddBlockPLCell( "Exclude0", GetBitStr(), 
					"Exclude0 field.\n\n"		+
					"Exclude0 allow the Host to select\n"	 + 
					"the layers to be calibrated."  , FieldColor, [_CELLINFO, 0, options ]);
					
					
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);

	ShowParamListLen(16);
    
}
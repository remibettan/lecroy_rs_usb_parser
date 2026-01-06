#
#  Copyright (c) 2010, LeCroy. - All Rights Reserved
#
#  SCSI_CDB_GetConfiguration.inc
#
#  SCSI CDB GET CONFIGURATION Command decoder functions
################################################################################


ShowGetConfiguration()
{
 
    PLReservedCheck(6);
    
    ShowRT();
	
	val = NextNBits_(16);
	AddBlockPLCell(	"Starting Feature Number", Format ("0x%04X", val), 
					"Starting Feature Number field.\n\n"	+
					"The field indicates the first Feature Number to be returned.\n" );
	
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	ShowAllocLen(16);
	
}

ShowRT()
{

	val = NextNBits_(2);
	
	base_tooltip =	"RT field.\n" +
					"Identify the type of data to be returned by the Drive.\n\n" +
					Format("Value   : 0x%X\n", val)	+
					"Meaning : ";	
					
	ClearError();
	select
	{
		val == 0b00 :
		{	
			tooltip =	"Drive shall return the Feature Header and all Feature \n"	+
						"Descriptors supported by the Drive without regard to currency.";
		}		
		
		val == 0b01 :
		{
			tooltip =	"Drive shall return the Feature Header and only those Feature \n"	+
						"Descriptors in which the Current bit is set to one.";
		} 
		
		val == 0b10 :
		{
			tooltip =	"Feature Header and Feature Descriptor identified by Starting  \n"		+
						"Feature Number shall be returned.";
		}

		val == 0b11 :
		{
			tooltip =	"Reserved.";
		}
	};
	
	base_tooltip += tooltip + "\n\n";
	
	AddBlockPLCell("RT", Format ("0x%X", val), base_tooltip);

}
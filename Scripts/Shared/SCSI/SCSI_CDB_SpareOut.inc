#
#  Copyright (c) 2010, LeCroy - All Rights Reserved
#
#  SCSI_CDB_SpareOut.inc
#
#  SCSI CDB SPARE OUT Command decoder functions
################################################################################


ShowSpareOut()
{
   
    PLReservedCheck(3);
    
    #------------------------------------ SERVICE ACTION ---------------------------------------
    
	serv_action = NextNBits_(5);
    
    tooltip = "SERVICE ACTION field.\n" + 
    Format("Value   : 0x%X\n", serv_action) +
           "Meaning : ";
    
    
    decoder = null;
    
    
    ClearError();
    select
    {
       
        serv_action == 0x00 : 
        { 
            str = "CREATE/MODIFY P_EXTENT SPARE";
            tooltip += str +
					"\n\nThe CREATE/MODIFY P_EXTENT SPARE command requests the target \n"	+ 
	                " to create a p_extent spare or modify an existing p_extent spare .";
	        
	        decoder = "ShowCr_ModExtentSpare";
	                
        }
                    
        serv_action == 0x01 : 
        { 
            str = "CREATE/MDFY PERPH DEV/COMP DEV SPARE";
            tooltip += str +
        			"\n\nThe CREATE/MODIFY PERIPHERAL DEVICE/COMPONENT DEVICE SPARE command requests \n"	+ 
                    "the target to create a peripheral device spare or a component device spare or \n"	+
                    "modify an existing peripheral device spare or a component device spare.";
            
            decoder = "ShowCr_ModPeripheralDeviceSpare";
        }        
		
		serv_action == 0x02 : 
		{ 
			str = "DELETE SPARE";
			tooltip += str +
					"\n\nThe DELETE SPARE command requests the target to delete the addressed spare.";	
		}
		
		(serv_action >= 0x03) && (serv_action < 0x18) :
		{
			str = "RESERVED";
			tooltip += str;
		}
	
		(serv_action >= 0x18) && (serv_action <= 0x1F) :
		{
			str = "VENDOR SPECIFIC";
			tooltip += str;
		}
        
       	default    : 
       	{
            str = Format("0x%X", serv_action);
            tooltip += str;
        }
    };

	val = VS;  # save global View Settings
    
    # we use a simple adding payload cell function here - 
    # in order to show 'SERVICE ACTION' cell in collapsed state.
    #
    
    options = [ ["CREATE/MODIFY P_EXTENT SPARE", 0], ["CREATE/MODIFY PERIPHERAL DEVICE/COMPONENT DEVICE SPARE", 1], ["DELETE SPARE", 2] ];
    
    AddPayLoadCell( "SERVICE ACTION", str, tooltip + AddErrorTooltip(), error, [_CELLINFO, 0, options ] );
    
    VS = val;  # restore global View Settings
    
    #-----------------------------------------------------------------------------------------
    
    if( decoder != null ) Call( decoder );
    else                  ShowDeleteSpare();  
 }

#--------------------------------------------------------------------

ShowDeleteSpare()
{

	PLReservedCheck(8);
	PLReservedCheck(8);
	
	ShowLUN_S();

	PLReservedCheck(8);
	PLReservedCheck(8);	
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
}

#---------------------------CREATE/MODIFY P_EXTENT SPARE--------------------------------------
ShowCr_ModExtentSpare()
{
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	ShowLUN_S();
	ShowParamListLen(32);
	
	val = NextNBits_(2);
	base_tooltip =	"CREATE/MODIFY field.\n\n"		+
					Format("Value   : 0x%X\n", val)	+
					"Meaning : ";
	
	ClearError();
	select
	{	
		val == 0b00 :
		{	
			tooltip =	"Target shall create a p_extent spare and assign it the logical\n"				+
						"unit number contained in LUN_S. If it is already exists,\n"	+
						"target shall modify the existing p_extent spare as requested.";
		}						
		val == 0b01 :
		{
			tooltip =	"Target shall create a p_extent spare and assign it to a logical\n"		+
						"unit number per the addressing rules.";
		}
		val == 0b10 :
		{
			tooltip =	"Target shall modify the p_extent spare addressed in LUN_S.\n"	+
						"If the address not exist, target shall terminate the command.";
		}
		val == 0b11 :
		{
			tooltip =	"Reserved.";
		}
	};
	base_tooltip += tooltip + "\n\n";
	AddBlockPLCell("CREATE/MODIFY", Format ("0x%X", val), base_tooltip);

	
	val = NextNBits_(2);
	base_tooltip = "COVER field.\n\n"	+
					Format("Value   : 0x%X\n", val)		+
					"Meaning : ";
	select
	{
		val == 0b00 :
		{	
			tooltip =	"Target shall use the parameter list to determine\n"	+
						"the p_extents and/or redundancy groups to be covered.";
		}
		
		val == 0b01 :
		{
			tooltip =	"All p_extents that are equal in size shall be covered by \n"	+
						"the spare p_extent except those listed in the parameter list.";
		}
		
		val == 0b10 :
		{
			tooltip =	"All p_extents that are equal in size that are not already \n"	+ 
						"covered by a spare shall be covered by the spare p_extent.";
		}
		
		val == 0b11 :
		{
			tooltip =	"All p_extents that are equal in size shall be covered \n"	+
						"by the spare p_extent.\n";
		}
	};
	base_tooltip += tooltip + "\n\n";
	AddBlockPLCell("COVER", Format ("0x%X", val), base_tooltip);
	
	
	PLReservedCheck(3);
	
	options = [ ["set", 1], ["Not set", 0] ];
	
	AddBlockPLCell("IMMED", GetBitStr(), 
	"IMMED field.\n\n"		+
    "Bit 0: Return status after the create/modify has completed. \n" +
	"Bit 1: Return status as soon as the CDB has been validated.", FieldColor, [_CELLINFO, 0, options ]);


}	


#----------------CREATE/MODIFY PERIPHERAL DEVICE/COMPONENT DEVICE SPARE------------------

ShowCr_ModPeripheralDeviceSpare()
{
	ShowLUN_P_C();
	ShowLUN_S();
	ShowParamListLen(32);

	val = NextNBits_(2);
	base_tooltip =	"CREATE/MODIFY field.\n\n"		+
					Format("Value   : 0x%X\n", val)	+
					"Meaning : ";
	ClearError();
	select
	{	
		val == 0b00 :
		{	
			tooltip =	"Target shall create a peripheral/component device spare and assign it \n"			+
						"the logical unit number contained in the LUN_S. If it is already exists,\n"	+
						"target shall modify the existing spare as requested.";
		}						
		
		val == 0b01 :
		{
			tooltip =	"Target shall create a peripheral/component device spare and assign it \n"		+
						"to a logical unit number per the addressing rules.";
		}
		
		val == 0b10 :
		{
			tooltip =	"Target shall modify the peripheral/component device spare addressed \n"	+
						"in the LUN_S. If it does not exist, target shall terminate the command.";
		}
		
		val == 0b11 :
		{
			tooltip =	"Reserved.";
		}
	};
	base_tooltip += tooltip + "\n\n";
	AddBlockPLCell("CREATE/MODIFY", Format ("0x%X", val), base_tooltip);
	
	val = NextNBits_(2);
	base_tooltip = "COVER field.\n\n"	+
					Format("Value   : 0x%X\n", val)		+
					"Meaning : ";
	select
	{
		val == 0b00 :
		{	
			tooltip =	"Target shall use the parameter list to determine the \n"	+
						"peripheral/component device and/or redundancy groups \n"	+
						"to be covered.";
		}
		
		val == 0b01 :
		{
			tooltip =	"Any peripheral/component device listed in parameter list\n"	+
						"shall not be covered by the spare peripheral/component\n"		+ 
						"device being created or modified.";
		}
		val == 0b10 :
		{
			tooltip =	"All peripheral/component device that are equal or less\n"		+
						"in size with the peripheral/component device addressed\n"		+
						"in the LUN_P/LUN_C that were not covered shall be covered\n"	+
						"by spare peripheral/component device being created or modified.";
			}	

	
		val == 0b11 :
		{
			tooltip =	"All peripheral/component device that are equal or less\n"		+
						"in size with the peripheral/component device addressed\n"		+
						"in the LUN_P/LUN_C field shall be covered by except \n"		+
						"those listed in the parameter list.";
		}
	};
	base_tooltip += tooltip + "\n\n";
	AddBlockPLCell("COVER", Format ("0x%X", val), base_tooltip );
	
	PLReservedCheck(2);
		
	options = [ ["set", 1], ["Not set", 0] ];
		
	AddBlockPLCell("PORCSEL", GetBitStr(),
	"PORCSEL field.\n\n"	+ 
	"Bit 0: Report on all the peripheral device spares within the target.\n" +
	"Bit 1: Report on all the component device spares within the target.", FieldColor, [_CELLINFO, 0, options ]);

	AddBlockPLCell("IMMED", GetBitStr(), 
	"IMMED field.\n\n"		+
    "Bit 0: Return status after the create/modify has completed. \n" +
	"Bit 1: Return status as soon as the when CDB has validated.", FieldColor, [_CELLINFO, 0, options ]);
		
}


#--------------------LUN_P/LUN_C----------------------
ShowLUN_P_C()
{
	val = NextNBits_(16);
	
	AddBlockPLCell("LUN_P/LUN_C", Format ("0x%04X", val),
	"The LUN_S field specifies the logical unit that defines\ n"  +
	"the component device spare addressed in the LUN_S.");
	
}

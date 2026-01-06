#
#  Copyright (c) 2010, LeCroy - All Rights Reserved
#
#  SCSI_CDB_RedundancyGroupOut.inc
#
#  SCSI CDB REDUNDANCY GROUP OUT Command decoder functions
################################################################################


ShowRedundancyGroupOut()
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
            str = "CONTROL GENERATION OF CHECK DATA";
            tooltip += str +
					"\n\nCONTROL GENERATION OF CHECK DATA command requests that the \n" + 
	                "generation of check data within a redundancy group be enabled \n" +
                	"or disabled.";
        }
        
        serv_action == 0x01 : 
        { 
            str = "CREATE/MODIFY REDUNDANCY GROUP";
            tooltip += str +
        			"\n\nThe CREATE/MODIFY REDUNDANCY GROUP command requests\n"    + 
                    "the creation of a new redundancy group or the modification\n" + 
					"of an existing redundancy group.";

		  decoder = "ShowCreateModifyRedunGrp";		
		}
        
        serv_action == 0x02 : 
        { 
        	str = "DELETE REDUNDANCY GROUP";
            tooltip += str +
                        "\n\nThe DELETE REDUNDANCY GROUP command requests that \n"	+ 
                        "information regarding the selected redundancy group be sent\n" +
                        "to the application client.";
                        
			decoder = "ShowDeleteRedunGrp";                      
        }
		
		serv_action == 0x03 :
		{
			str = "REBUILD P_EXTENT";
			tooltip += str +
					"\n\n The REBUILD P_EXTENT command requests the \n"	+
					"rebuild of all or part of one or more redundancy group.";
			
			decoder = "ShowRebuildPExtent";		
					
		}
		
		serv_action == 0x04 :
		{	
			str = "REBUILD PERIPHERAL DEVICE";
			tooltip += str +
					"\n\n The REBUILD PERIPHERAL DEVICE command requests the \n"  +
					"rebuild of all or part of one or more redundancy group\n" +
					"located on a selected peripheral device.";
			
			decoder = "ShowRebuildPeripheralDevice";
		
		}
		
		serv_action == 0x05 :
		{
			str = "RECALCULATE CHECK DATA";
			tooltip += str +
					"\n\n The RECALCULATE CHECK DATA command requests the \n"  	+
					"target to recalculate check data within a redundancy group." ;
					
			decoder = "ShowRecalCheckData";
		}
		
		serv_action == 0x06 :
		{	
			str = "VERIFY CHECK DATA";
			tooltip += str +
					"\n\n VERIFY CHECK DATA command requests that check data\n" +
					"be verified consistent with the protected space within\n"  + 
					"a redundancy group.";
			
			decoder = "ShowVerifyCheckData";
		}

		serv_action == 0x07 : 
		{	
			str = "CREATE/MODIFY BASIC REDUNDANCY GROUP";
			tooltip += str +
					"\n\n CREATE/MODIFY BASIC REDUNDANCY GROUP command requests the creation\n" +
					"of a new redundancy group, or the modification of an existing redundancy group.";
					
			decoder = "ShowCreateModifyBasicRedunGrp";
		}

      	(serv_action >= 0x08) && (serv_action < 0x18) :
      	{
            str = "RESERVED";
            tooltip += str;
      	}
	
	
      	(serv_action >= 0x18) && (serv_action < 0x1F) :
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
    
    options = [ ["CONTROL GENERATION OF CHECK DATA", 0], ["CREATE/MODIFY REDUNDANCY GROUP", 1], ["DELETE REDUNDANCY GROUP", 2], ["REBUILD P_EXTENT", 3], ["REBUILD PERIPHERAL DEVICE", 4], 
				["RECALCULATE CHECK DATA", 5],["VERIFY CHECK DATA", 6], ["CREATE/MODIFY BASIC REDUNDANCY GROUP", 7] ];
    
    AddPayLoadCell( "SERVICE ACTION", str, tooltip + AddErrorTooltip(), error, [_CELLINFO, 0, options ] );
    
    VS = val;  # restore global View Settings
    
    #-----------------------------------------------------------------------------------------
    
    if( decoder != null ) Call( decoder );
    else                  ShowRedundancyGrpOut();  
}

#--------------------------------------------------------------------

ShowRedundancyGrpOut()
{

	PLReservedCheck(8);
	PLReservedCheck(8);
	
	ShowLUN_R();
	
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
 	PLReservedCheck(8);
 	
 	PLReservedCheck(4);
 	
 	val = NextNBits_(1);
 	AddBlockPLCell("DISCHK", Format ("0x%X", val), 
 	"DISCHK field.\n\n"	+
 	"Bit 0: Check data shall be enabled.\n"	+
 	"Bit 1: Check data shall be disabled.");
 	
 	PLReservedCheck(1);
 	
 	val = NextNBits_(1);
 	AddBlockPLCell("ALLRG", Format ("0x%X", val), 
 	"ALLRG field.\n\n"		+
 	"Bit 0: Check data only be enabled/disabled on the addressed redundancy group\n"	+
 	"Bit 1: Check data be enabled/disabled on all the redundancy groups within target."); 
 	
 	PLReservedCheck(1);
 	
}

#-----------------------CREATE/MODIFY_BASIC_REDUNDANCY_GROUP----------------------------------------

ShowCreateModifyBasicRedunGrp()
{
	ShowRedunGrpMethod();
		
	val = nextNBits(1);
	AddBlockPLCell("BUSPROC", Format ("0x%X", val),
	"BUSPROC field.\n\n"		+
	"Bit 0: Failure will loose access to user data associated with redundancy group.\n" +
	"Bit 1: Failure will not loose access to any user data associated with redundancy group.");

	PLReservedCheck(2);
	
	val = nextNBits(1);
	AddBlockPLCell("EQSPRD", Format ("0x%X", val), 
	"EQSPRD field.\n\n"		+
	"Bit 0: Spread protected space and check data in a nonuniform manner.\n" +
	"Bit 1: Spread protected space and check data in a uniform manner.");
	
	PLReservedCheck(4);
	
	ShowLUN_R();
	ShowParamListLen(32);
	
	ShowCr_ModRedundancyGrp();

	ShowConfigureRedundancyGrp();

	PLReservedCheck(3);
	
    options = [ ["set", 1], ["Not set", 0] ]; 

	AddBlockPLCell("IMMED", GetBitStr(), 
	"IMMED field.\n\n"		+
    "Bit 0: Return status when create/modify completed.\n" + 
	"Bit 1: Return status when CDB and parameter list validated.", FieldColor, [_CELLINFO, 0, options ]);

} 



#------------------------------ CREATE/MODIFY REDUNDANCY GROUP--------------------

ShowCreateModifyRedunGrp()
{
	ShowRedunGrpMethod();
	
	PLReservedCheck(4);
	
	ShowGranularityOfUnits();
	
	ShowLUN_R();
	ShowParamListLen(32);
	ShowCr_ModRedundancyGrp();
	
	PLReservedCheck(5);
	
	options = [ ["set", 1], ["Not set", 0] ];
	
	AddBlockPLCell("IMMED", GetBitStr(), 
	"IMMED field.\n\n"		+
    "Bit 0: Return status when create/modify completed.\n" + 
	"Bit 1: Return status when CDB and parameter list validated.", FieldColor, [_CELLINFO, 0, options ]);

	
}



#-----------------------------DELETE REDUNDANCY GROUP----------------------------	
ShowDeleteRedunGrp()
{

	PLReservedCheck(8);
	PLReservedCheck(8);
	
	ShowLUN_R();
	
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);

}
	

#--------------------------REBUILD P_EXTENT----------------------------
ShowRebuildPExtent()
{
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);

	ShowParamListLen(32);

	PLReservedCheck(2);

	ShowRebuildRedunGrp();
	
	PLReservedCheck(3);	
	
	options = [ ["set", 1], ["Not set", 0] ];
	
	AddBlockPLCell("IMMED", GetBitStr(), 
	"IMMED field.\n\n"		+
    "Bit 0: Return status when create/modify completed.\n" + 
	"Bit 1: Return status when CDB and parameter list validated.", FieldColor, [_CELLINFO, 0, options ]);
	
}


#-----------------REBUILD PERIPHERAL DEVICE-------------------
	
ShowRebuildPeripheralDevice()
{

	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	ShowParamListLen(32);
		
	PLReservedCheck(2);
	
	ShowRebuildRedunGrp();
	
	PLReservedCheck(3);	
	
	options = [ ["set", 1], ["Not set", 0] ];
		
	AddBlockPLCell("IMMED", GetBitStr(), 
	"IMMED field.\n\n"		+
    "Bit 0: Return status when create/modify completed.\n" + 
	"Bit 1: Return status when CDB and parameter list validated.", FieldColor, [_CELLINFO, 0, options ]);

}


#-------------------------RECALCULATE CHECK DATA-----------------------

ShowRecalCheckData()
{

	PLReservedCheck(8);
	PLReservedCheck(8);
	
	ShowLUN_R();
	
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	PLReservedCheck(8);
	PLReservedCheck(8);
		
	PLReservedCheck(6);
	
	val = NextNBits_(1);
 	AddBlockPLCell("ALLRG", Format ("0x%X", val), 
 	"ALLRG field.\n\n"		+
	"Bit 0: Check data recalculation only occur on the addressed redundancy group.\n"	+
	"Bit 1: Check data recalculation occur on all redundancy groups within the target.");
		
    options = [ ["set", 1], ["Not set", 0] ];
	AddBlockPLCell("IMMED", GetBitStr(),
	"IMMED field.\n\n"		+ 
    "Bit 0: Return status when create/modify completed.\n" + 
	"Bit 1: Return status when CDB and parameter list validated.", FieldColor, [_CELLINFO, 0, options ]);

}


#-----------------------VERIFY CHECK DATA-------------------------------

ShowVerifyCheckData()
{

	PLReservedCheck(8);
	PLReservedCheck(8);
	
	ShowLUN_R();
	
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	PLReservedCheck(4);
	
	val = NextNBits_(1);
 	AddBlockPLCell("CONTVER", Format ("0x%X", val), 
 	"CONTVER field.\n\n"		+
 	"Bit 0: Check data shall be verified only once.\n"	+
 	"Bit 1: Check data shall be continuously verified.");
	
	PLReservedCheck(1);
		
	val = NextNBits_(1);
 	AddBlockPLCell("ALLRG", Format ("0x%X", val), 
 	"ALLRG field.\n\n"		+
 	"Bit 0: Check data verification only occur on the addressed redundancy group.\n"	+
 	"Bit 1: Check data Verification occur on all redundancy groups within the target.");
		
		
    options = [ ["set", 1], ["Not set", 0] ];
	AddBlockPLCell("IMMED", GetBitStr(), 
	"IMMED field.\n\n"		+
    "Bit 0: Return status when create/modify completed.\n" + 
	"Bit 1: Return status when CDB and parameter list validated.", FieldColor, [_CELLINFO, 0, options ]);

}

#----------------------------------Configure field-------------------------------
ShowConfigureRedundancyGrp()
{
	val = NextNBits_(2);
		
	base_tooltip = "CONFIGURE field.\n\n"	+
					Format("Value   : 0x%X\n", val)		+
					"Meaning : ";
	select
	{
		val == 0b00 :
		{	
			tooltip =	"Any unassigned ps_extent within the target may be used to\n"	+
						"configure the selected volume set to the requested capacity."; 
		}		
		
		val == 0b01 :
		{
			tooltip =	"Target use the parameter list to determine\n"	+
						"the configuration of the volume set and redundancy group.";
		}
		
		val == 0b10 :
		{
			tooltip =	"All unassigned p_extents within the target shall be configured \n"		+
						"into a volume set and a redundancy group."; 
		}

		val == 0b11 :
		{
			tooltip =	"Reserved.";
		}
	};	
	base_tooltip += tooltip + "\n\n";
	
	AddBlockPLCell("CONFIGURE", Format ("0x%X", val), base_tooltip);
}

#----------------------------CREATE/MODIFY----------------------------------------

ShowCr_ModRedundancyGrp()
{
	val = NextNBits_(2);
	base_tooltip =	"CREATE/MODIFY field.\n\n"		+
					Format("Value   : 0x%X\n", val)	+
					"Meaning : ";
			
	select
	{	
			
		val == 0b00 :
		{
						
			tooltip =	"Target shall create a redundancy group and shall assign\n"	+
						"to the created redundancy group the logical unit number\n"	+ 
						"contained in the LUN_R.";
				
		}

		val == 0b01 :
		{
			tooltip =	"Target shall create a redundancy group and\n"	+
						"assign to the created and redundancy group\n"	+
						"logical unit numbers per the addressing rules.";
						
		}

		val == 0b10 :
		{
			tooltip =	"Target shall modify the redundancy group.Target may \n"	+
						"preserve the contents of protected space on completion \n"	+
						"of the modify.";
		}
	
		val == 0b11 :
		{
			tooltip =	"Target shall modify the redundancy group.Target \n"	+
						"shall preserve the contents of protected space on \n"	+ 
						"completion of the modify.";
		}
	};
	
	base_tooltip += tooltip + "\n\n";

	AddBlockPLCell("CREATE/MODIFY", Format ("0x%X", val), base_tooltip);
}

#-------------------------------------Rebuild----------------------------------------

ShowRebuildRedunGrp()
{
	val = NextNBits_(2);
		
	base_tooltip = "REBUILD field.\n\n"	+
					Format("Value   : 0x%X\n", val)		+
					"Meaning : ";
	select
	{
		val == 0b00 :
		{	
			tooltip =	"All assigned space associated with selected \n"	+
						"p_extent shall be rebuilt."; 
		}		
		
		val == 0b01 :
		{
			tooltip =	"All assigned space association with selected p_extent\n"	+
						"shall be rebuilt using any associated redundancy group.";
		}
				
		val == 0b10 :
		{
			tooltip =	"All assigned space associated with selected p_extent\n"		+
						"shall be rebuilt.Any redundancy group in parameter\n"		+
						"list shall not be used to rebuild."; 
		}

		val == 0b11 :
		{
			tooltip =	"Reserved.";
		}
	};	
	base_tooltip += tooltip + "\n\n";
	
	AddBlockPLCell("REBUILD", Format ("0x%X", val), base_tooltip);

}

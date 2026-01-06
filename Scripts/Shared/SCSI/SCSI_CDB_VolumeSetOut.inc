#
#  Copyright (c) 2010, LeCroy - All Rights Reserved
#
#  SCSI_CDB_VolumeSetOut.inc
#
#  SCSI CDB VOLUME SET OUT Command decoder functions
################################################################################


ShowVolumeSetOut()
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
					"\n\nThe CONTROL GENERATION OF CHECK DATA command requests that the generation \n"	+ 
	                "of check data within the underlaying redundancy group(s) of a volume set be \n"	+
	                "enabled or disabled.";
         
			decoder = "ShowCtrlGenCheckData";
        }
                    
        serv_action == 0x01 : 
        { 
            str = "CONTROL WRITE OPERATIONS";
            tooltip += str +
        			"\n\nThe CONTROL WRITE OPERATIONS command requests that write operations to a \n"	+ 
                    " volume set be enabled or disabled.";
            
            decoder = "ShowCtrlWriteOperations";
        }        
		
		serv_action == 0x02 : 
		{ 
			str = "CREATE/MODIFY VOLUME SET";
			tooltip += str +
					"\n\nThe CREATE/MODIFY VOLUME SET command requests the creation of a new \n"	+ 
                    "volume set or the modification of an existing volume set. \n"					+
              
            decoder = "ShowCreateModifyVolSet";
		}
		
		serv_action == 0x03 :
		{	
			str = "DELETE VOLUME SET";
			tooltip += str +
					"\n\n The DELETE VOLUME SET command requests that the selected volume set \n"	+
					"be deleted. If the remove operation fails to complete successfully, \n"		+
					"the command shall be terminated with a CHECK CONDITION status.";
			
			decoder = "ShowDeleteVolSet";
		}

		serv_action == 0x04 :
		{	
			str = "RECALCULATE VOLUME SET CHECK DATA";
			tooltip += str +
					"\n\n The RECALCULATE VOLUME SET CHECK DATA command requests the target \n"		+
					"to recalculate check data within the portion of any redundancy group(s) \n"	+
					"overlaid by the selected a volume set.";
				
			decoder = "ShowRecalcVolSetCheckData";
		}

		serv_action == 0x05 :
		{	
			str = "VERIFY VOLUME SET CHECK DATA";
			tooltip += str +
					"\n\n The VERIFY VOLUME SET CHECK DATA command requests that check data be \n"	 +
					"verified consistent with the protected space within any redundancy group(s) \n" +
					"overlaid by the selected range of LBA_V(s).";
			
			decoder = "ShowVerifyVolSetCheckData";
		}

		serv_action == 0x06 :
		{	
			str = "DEASSIGN LUN_V";
			tooltip += str +
					"\n\n The DEASSIGN LUN_V command requests that a LUN_V be deassigned. \n"			+
					"After a successful completion of this service action the selected LUN_V(s) \n"		+
					"are free to be used in the creation of new volume set(s).";
			
			decoder = "ShowDeassignLUN_V";
		}

		serv_action == 0x07 :
		{	
			str = "ASSIGN LUN_V";
			tooltip += str +
					"\n\n The ASSIGN LUN_V command requests a LUN_V be assigned to volume set\n"			+ 
					"that has been configured. If the assign operation fails to complete successfully,\n"	+ 
					"the command shall be terminated with a CHECK CONDITION status.";
			
			#decoder = "ShowAssignLUN";
		}
		
		serv_action == 0x08 :
		{	
			str = "CREATE/MODIFY STORAGE ARRAY CONFIGURATION";
			tooltip += str +
					"\n\n The CREATE/MODIFY STORAGE ARRAY CONFIGURATION command requests the creation \n"	+
					"of a new volume set and redundancy group, or the modification of an existing \n"		+
					"volume set and redundancy group.";
				
			decoder = "ShowCreateModifyArrayConfg";
		}
		
		serv_action == 0x09 :
		{	
			str = "CREATE/MODIFY BASIC VOLUME SET";
			tooltip += str +
					"\n\n The CREATE/MODIFY BASIC VOLUME SET command requests the creation \n"	+
					"of a new volume set or the modification of an existing volume set.";
			
			decoder = "ShowCreateModifyBasicVolSet";
		}
		
		(serv_action >= 0x0A) && (serv_action < 0x18) :
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
	
    
    options = [ ["CONTROL GENERATION OF CHECK DATA", 0], ["CONTROL WRITE OPERATIONS", 1], ["CREATE/MODIFY VOLUME SET", 2], ["DELETE VOLUME SET", 3], 
				["RECALCULATE VOLUME SET CHECK DATA", 4], ["VERIFY VOLUME SET CHECK DATA", 5],["DEASSIGN LUN_V", 6], ["ASSIGN LUN_V", 7],
				["CREATE/MODIFY STORAGE ARRAY CONFIGURATION", 8], ["CREATE/MODIFY BASIC VOLUME SET", 9] ];
    
    
    
    AddPayLoadCell( "SERVICE ACTION", str, tooltip + AddErrorTooltip(), error, [_CELLINFO, 0, options ] );
  	
    VS = val;  # restore global View Settings
    
    #-----------------------------------------------------------------------------------------
    
    if( decoder != null ) Call( decoder );
    else                  ShowAssignLUN();  
 }



#----------------------------ASSIGN LUN_V---------------------------
ShowAssignLUN()
{
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	ShowLUN_V();
	ShowParamListLen(32);
	
	PLReservedCheck(5);
	
	val = NextNBits_(2);
 	base_tooltip =	"ENABLE RANGE\n\n"	+
					Format("Value   : 0x%X\n", val)	+
					"Meaning : ";
 	ClearError();
 	select
 	{
 		val == 0b00 :
		{	
			tooltip =	"Target shall assign the logical unit number to \n"		+
						"the selected unassigned volume set.";
		}
		
		val == 0b01 :
		{
			tooltip =	"Assign a LUN_V to the volume set selected\n"		+
						" in IDENTIFIER.The LUN_V shall be ignored. ";
		}
		
		val == 0b10 :
		{
			tooltip =	"Assign LUN_V to all unassigned volume sets \n"	+
						"within the selected target.";
		}	

		val == 0b11 :
		{
			tooltip =	"Reserved.";
		}
	};
	base_tooltip += tooltip + "\n\n";
 	
 	AddBlockPLCell("ENABLE RANGE", Format ("0x%X", val), base_tooltip);
 		
	PLReservedCheck(1);

}


#-----------------CONTROL GENERATION OF CHECK DATA----------------------

ShowCtrlGenCheckData()
{

	PLReservedCheck(8);
	PLReservedCheck(8);
	
	ShowLUN_V();
	
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	PLReservedCheck(4);

	val = NextNBits_(1);
	AddBlockPLCell("DISCHK", Format ("0x%X", val), 
 	"A disable check data bit.\n"	+
 	"Bit 0: Check data within the selected volume set shall be enabled\n"	+
 	"Bit 1: Check data within the selected volume set shall be disabled.");
	
	PLReservedCheck(1);
	
	val = NextNBits_(1);
 	AddBlockPLCell("ALLVLU", Format ("0x%X", val), 
 	"An all volume set bit\n"	+
 	"Bit 0: Check data generation shall only be enabled/disabled within the addressed volume set.\n"	+
 	"Bit 1: Check data generation shall be enabled/disabled within all volume set within the target." );
 	
 	PLReservedCheck(1);	
 
}



#-------------------------CONTROL WRITE OPERATIONS------------------------

ShowCtrlWriteOperations()
{
	
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	ShowLUN_V();
	
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);

	PLReservedCheck(4);
	
	val = NextNBits_(1);
 	AddBlockPLCell("DISWR", Format ("0x%X", val), 
 	"DISWR field.\n\n"	+
 	"Bit 0: Write operations shall be enabled on the selected volume set.\n"		+
 	"Bit 1: Write operations shall be disabled on the selected volume set.");
 	
 	PLReservedCheck(1);
		
	val = NextNBits_(1);
 	AddBlockPLCell("ALLVLU", Format ("0x%X", val), 
 	"ALLVLU field.\n\n"	+
 	"Bit 0: Write operation control only apply to the addressed volume set.\n"	+
 	"Bit 1: Write operation control only apply to all volume set within the target.");
 	
 	PLReservedCheck(1);

}


#---------------------CREATE/MODIFY BASIC VOLUME SET----------------------
ShowCreateModifyBasicVolSet()
{
	PLReservedCheck(8);
	
	PLReservedCheck(3);
	
	val = nextNBits(1);
	AddBlockPLCell("EQSPRD", Format ("0x%X", val), 
	"EQSPRD field.\n\n"		+
	"Bit 0: User data are spread in a nonuniform manner.\n"		+
	"Bit 1: User data are spread in a uniform manner.");
	
	PLReservedCheck(4);

	ShowLUN_V();
	ShowParamListLen(32);

	ShowCreate_Modify();
	
	ShowConfigureVolSet();
	
	PLReservedCheck(3);
	
    options = [ ["set", 1], ["Not set", 0] ];
	AddBlockPLCell("IMMED", GetBitStr(), 
	"IMMED field.\n\n"		+
    "Bit 0: Return status when create/modify basic redundancy group completed.\n" + 
	"Bit 1: Return status when CDB and parameter list validated.", FieldColor, [_CELLINFO, 0, options ]);

}


#---------------------------------CREATE/MODIFY STORAGE ARRAY CONFIGURATION------------------------------

ShowCreateModifyArrayConfg()
{
	
	ShowRedunGrpMethod();
		
	val = nextNBits(1);
	AddBlockPLCell("BUSPROC", Format ("0x%X", val),
	"BUSPROC field.\n\n"		+
	"Bit 0: Failure will loose access to user data associated with redundancy group.\n" +
	"Bit 1: Failure will not loose access to user data associated with redundancy group.");

	PLReservedCheck(2);
	
	val = nextNBits(1);
	AddBlockPLCell("EQSPRD", Format ("0x%X", val), 
	"EQSPRD field.\n\n"		+
	"Bit 0: User data are spread in a nonuniform manner.\n"		+
	"Bit 1: User data are spread in a uniform manner.");
	
	PLReservedCheck(4);
	
	ShowLUN_V();
	ShowParamListLen(32);
	
	ShowCreate_Modify();
		
	ShowConfigureVolSet();
	
	PLReservedCheck(3);
	
    options = [ ["set", 1], ["Not set", 0] ];

	AddBlockPLCell("IMMED", GetBitStr(), 
	"IMMED field.\n\n"		+
    "Bit 0: Return status when create/modify basic redundancy group completed.\n"	+ 
	"Bit 1: Return status when CDB and parameter list validated.", FieldColor, [_CELLINFO, 0, options ]);

}




#---------------------------CREATE/MODIFY VOLUME SET------------------------------
ShowCreateModifyVolSet()
{
	PLReservedCheck(8);
	PLReservedCheck(4);
	ShowGranularityOfUnits();
	
	ShowLUN_V();
	ShowParamListLen(32);
	
	ShowCreate_Modify();

	PLReservedCheck(5);
	
    options = [ ["set", 1], ["Not set", 0] ];
	AddBlockPLCell("IMMED", GetBitStr(), 
	"IMMED field.\n\n"		+
    "Bit 0: Return Status after the verification operation completed.\n"	+ 
	"Bit 1: Return status when CDB and parameter list validated.", FieldColor, [_CELLINFO, 0, options ]);

}


#-------------------------DEASSIGN LUN_V--------------------------------
ShowDeassignLUN_V()
{
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	ShowLUN_V();

	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	PLReservedCheck(6);
	
	val = NextNBits_(1);
 	AddBlockPLCell("ALLVLU", Format ("0x%X", val), 
 	"ALLVLU field.\n\n"		+
	"Bit 0: Only selected LUN_V shall be deassigned.\n"		+
	"Bit 1:	All LUN_V within the target shall be deassigned.");
	
	PLReservedCheck(1);
	
}


#---------------------------DELETE VOLUME SET---------------------------------
ShowDeleteVolSet()
{
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	ShowLUN_V();

	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	
}


#-------------------------RECALCULATE VOLUME SET CHECK DATA------------
ShowRecalcVolSetCheckData()
{
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	ShowLUN_V();
	ShowParamListLen(32);

	PLReservedCheck(6);
	
	val = NextNBits_(1);
 	AddBlockPLCell("ALLVLU", Format ("0x%X", val), 
 	"ALLVLU field.\n\n"		+
	"Bit 0: Check data associated with selected range of LBA_Vs shall be recalculated.\n"		+
	"Bit 1:	Check data associated with selected volume set shall be recalculated.");
	
    options = [ ["set", 1], ["Not set", 0] ];
	AddBlockPLCell("IMMED", GetBitStr(),
	"IMMED field.\n\n"		+ 
    "Bit 0: Return Status after the verification operation completed.\n"	+ 
	"Bit 1: Return status when CDB and parameter list validated.", FieldColor, [_CELLINFO, 0, options ]);

}




#--------------------------VERIFY VOLUME SET CHECK DATA----------------

ShowVerifyVolSetCheckData()
{
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	ShowLUN_V();
	ShowParamListLen(32);
	
	PLReservedCheck(4);
	
	val = NextNBits_(1);
 	AddBlockPLCell("CONTVER", Format ("0x%X", val), 
 	"CONTVER field.\n\n"		+
 	"Bit 0: Check data shall be verified only once.\n"	+
 	"Bit 1: Check data shall be continuously verified.");
 	
 	val = NextNBits_(2);
 	base_tooltip =	"VERIFY RANGE field.\n\n" +
					Format("Value   : 0x%X\n", val)	+
					"Meaning : ";	
	ClearError();
	select
	{
		val == 0b00 :
		{	
			tooltip =	"Verify all volume sets within the selected target.";
		}		
		
		val == 0b01 :
		{
			tooltip =	"Verify the entire selected volume set.";
		} 
		
		val == 0b10 :
		{
			tooltip =	"Only verify the selected LBA_V range \n"		+
						"within the selected volume set."; 
		}

		val == 0b11 :
		{
			tooltip =	"Reserved.";
		}
	};
	base_tooltip += tooltip + "\n\n";
	AddBlockPLCell("VERIFY RANGE", Format ("0x%X", val), base_tooltip);

    options = [ ["set", 1], ["Not set", 0] ];
	AddBlockPLCell("IMMED", GetBitStr(), 
	"IMMED field.\n\n"		+
    "Bit 0: Return Status after the verification completed.\n" + 
	"Bit 1: Return status when CDB and parameter list validated.", FieldColor, [_CELLINFO, 0, options ]);
 	
}


#----------------------------Create_Modify------------------------------------------
ShowCreate_Modify()
{
	val = NextNBits_(2);
	base_tooltip =	"CREATE/MODIFY field.\n\n"		+
					Format("Value   : 0x%X\n", val)	+
					"Meaning : ";
	ClearError();
	select
	{
		val == 0b00 :
		{
			tooltip =	"Target shall create a volume set and shall assign\n"	+
						"to the created volume set the logical unit number\n"	+ 
						"contained in the LUN_V.";
		}
		val == 0b01 :
		{
			tooltip =	"Target shall create a volume set and a redundancy group,\n"	+
						"and shall assign to the created volume set and redundancy \n"	+
						"group logical unit numbers per the addressing rules.";
		}
		val == 0b10 :
		{
			tooltip =	"Target shall modify the volume set.Target may preserve \n"	+
						"the contents of and access to user data on completion \n"	+
						"of the modify.";
		}
		val == 0b11 :
		{
			tooltip +=	"Target shall modify the volume set.Target shall preserve\n"	+
						"the contents of and access to user data on completion\n"	+ 
						"of the modify.";
		}
	};
	base_tooltip += tooltip + "\n\n";
	
	AddBlockPLCell("CREATE/MODIFY", Format ("0x%X", val), base_tooltip);
}




#----------------------------------Configure-------------------------------
ShowConfigureVolSet()
{
	val = NextNBits_(2);
		
	base_tooltip = "CONFIGURE field.\n\n"	+
					Format("Value   : 0x%X\n", val)		+
					"Meaning : ";
	ClearError();
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


#-----------------ShowGranularityOfUnits------------------------

ShowGranularityOfUnits()
{

	val = NextNBits_(4);
	
	base_tooltip = "GRANULARITY OF UNITS field.\n\n"	+
					Format("Value   : 0x%X\n", val)		+
					"Meaning : ";
	
	ClearError();
	select
	{
		val == 0x0 : 
		{
			str = "Bit";
			tooltip = str;
		}
		val == 0x1 : 
		{
			str = "Byte";
			tooltip = str;
		}
		val == 0x2 : 
		{
			str = "2-Byte Word";
			tooltip = str;
		}
		
		val == 0x3 : 
		{
			str = "4-Byte Word";
			tooltip = str;
		}
		val == 0x4 : 
		{
			str = "Logical Block";
			tooltip = str;
		}
		(val >= 0x5) && (val <= 0xB): 
		{			
			str = "Reserved";
			tooltip = str;
		}
		(val >= 0xC) && (val <= 0xF): 
		{
			str = "Vendor Specific";
			tooltip = str;
		}
	};
	
	base_tooltip += str + "\n\n";
	
	options = [ ["Bit", 0], ["Byte", 1], ["2-Byte Word", 2], ["4-Byte Word", 3], 
				["Logical Block", 4]];
	
	AddBlockPLCell("GRANULARITY OF UNITS", str, base_tooltip, FieldColor, [_CELLINFO, 0, options ] );

}

#----------------------REDUNDANCY GROUP METHOD--------------------

ShowRedunGrpMethod()
{
	type_grpmethod = NextNBits_(8);
	
	base_tooltip  =	"REDUNDANCY GROUP METHOD field.\n\n"	+
					Format("Value   : 0x%02X\n", type_grpmethod)	+
					"Meaning : ";
    
    ClearError();
    select
    {
		type_grpmethod == 0x00 :
		{	
				str = "No Redundancy";
				
				tooltip = "\nThe SACL is not required to protect user data.";
		}
		
		type_grpmethod == 0x01 :
		{
				str = "Copy Redundancy";
				tooltip =	"\nThe SACL shall duplicate all user data at least one time on different\n" +
							"peripheral devices.";
		}
		
		type_grpmethod == 0x02 :
		{
				str = "XOR Redundancy";
				tooltip = "\nThe SACL shall protect user data such that a single peripheral device\n" +
						"failure does not cause loss of user data.";
		}
		
		type_grpmethod == 0x03 :
		{
				str = "P+Q Redundancy";
				tooltip =	"\nThe SACL shall protect user data such that the failure of two peripheral\n" +
							"devices does not cause loss of user data.";
		}
		
		type_grpmethod == 0x04 :
		{
				str = "P+S Redundancy";
				tooltip =	"\nThe SACL shall protect user data such that the failure of a single peripheral\n"       +
							"device does not cause loss of user data and after some vendor specific amount of time\n" +
							"a second peripheral device failure shall not cause loss of user data. If a second\n"	  +
							"peripheral device fails within the vendor specific amount of time user data may be lost.";
		}
		
		type_grpmethod == 0x05 :
		{
				str = "S Redundancy";
				tooltip =	"\nThe SACL shall have access to at least enough spare space to allow a rebuild of\n"		  +
							"one peripheral device within that space. User data may be lost if the SACL cannot predict\n" + 
							"or predicts incorrectly a peripheral device failure. User data may also be lost if the\n"    +
							"SACL does not complete a rebuild before the peripheral device fails.";
		}
			
		(type_grpmethod <= 0x06) && (type_grpmethod <= 0x7F) :
		{
				str = "Reserved";
				tooltip = str;
		}
			
		(type_grpmethod <= 0x80) && (type_grpmethod <= 0xFF) :
		{
				str = "Vendor Specific";
				tooltip = str;
		}
			
		default : 
		{
				str = "Reserved"; tooltip = "Reserved." + AddWarningTooltip("Reserved value");
                error = _ERROR; 
        }                            
	};
	
	base_tooltip += str + "\n" + tooltip;
	
	options = [ ["No Redundancy", 0], ["Copy Redundancy", 1], ["XOR Redundancy", 2], ["P+Q Redundancy", 3], 
				["P+S Redundancy", 4], ["S Redundancy", 5]];
	 
	AddBlockPLCell("REDUNDANCY GROUP METHOD", str, base_tooltip, FieldColor, [_CELLINFO, 0, options ]);
	
}





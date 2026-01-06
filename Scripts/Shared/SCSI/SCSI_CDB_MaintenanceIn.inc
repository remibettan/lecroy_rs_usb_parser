#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_MaintenanceIn.inc
#
#  SCSI CDB MAINTENANCE In Command decoder functions
################################################################################




ShowMaintenanceIn()
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
            str = "REPORT ASSIGNED/UNASSIGNED P_EXTENT";
            tooltip += str +
                        "\n\nThe REPORT ASSIGNED/UNASSIGNED P_EXTENT command requests\n" + 
                        "information regarding assigned p_extents or unassigned\n" + 
                        "p_extents within the target be sent to the application client.";
                        
            decoder = "ShowAsigndUnAsignedPExt";
        }				
		
		serv_action == 0x01 : 
        { 
            str = "REPORT COMPONENT DEVICE";
            tooltip += str +
                        "\n\nThe REPORT COMPONENT DEVICE command requests\n" + 
                        "that regarding component device(s) within the target\n" + 
                        "be sent to the application client.";
                        
            decoder = "ShowRptCompDev";
        } 
        
        serv_action == 0x02 : 
        { 
            str = "REPORT COMPONENT DEVICE ATTACHMENTS";
            tooltip += str +
                        "\n\nThe REPORT COMPONENT DEVICE ATTACHMENTS command requests\n" + 
                        "information regarding logical units that are attached\n" + 
                        "to component device(s) be sent to the application client.";
                        
            decoder = "ShowRptCompDevAttch";
        }
                    
        serv_action == 0x03 : 
        { 
            str = "REPORT PERIPHERAL DEVICE";
            tooltip += str +
                        "\n\nThe REPORT PERIPHERAL DEVICE command requests\n" + 
                        "that information regarding peripheral device(s) within the target\n" + 
                        "be sent to the application client.";
                        
            decoder = "ShowPerphDev";
        }
         
        serv_action == 0x04 : 
        { 
            str = "REPORT PERIPHERAL DEVICE ASSOCIATIONS";
            tooltip += str +
                        "\n\nThe REPORT PERIPHERAL DEVICE ASSOCIATIONS command requests\n" + 
                        "that information regarding logical units that are associated\n" + 
                        "with peripheral device(s) be sent to the application client.";
                        
            decoder = "ShowPerphDevAssoc";
        }
                
        serv_action == 0x05 : 
        { 
            str = "REPORT IDENTIFYING INFORMATION";
            tooltip += str +
                        "\n\nThe REPORT IDENTIFYING INFORMATION command requests\n" + 
                        "that the device server send identifying information\n" + 
                        "to the application client.";
                        
            decoder = "ShowRepIDInfo";
        }            
        
        serv_action == 0x06 : 
        { 
            str = "REPORT STATES";
            tooltip += str +
                        "\n\nThe REPORT STATES command requests\n" + 
                        "that information about the selected logical unit(s)\n" + 
                        "within the target be sent to the application client.";
                        
            decoder = "ShowReportStates";
        }        
                        
        serv_action == 0x07 : 
        { 
            str = "REPORT DEVICE IDENTIFICATION";
            tooltip += str +
                        "\n\nThe REPORT DEVICE IDENTIFICATION command requests\n" + 
                        "the vital product data’s device identification page.";
                        
            decoder = "ShowRptDevID";
        }  
          
        serv_action == 0x08 : 
        { 
            str = "REPORT UNCONFIGURED CAPACITY";
            tooltip += str +
                        "\n\nThe REPORT UNCONFIGURED CAPACITY command requests\n" + 
                        "information regarding the unconfigured capacity within\n" + 
                        "the target be sent to the application client.";

                        
            decoder = "ShowUnCfgCapacity";
        }
                
        serv_action == 0x09 : 
        { 
            str = "REPORT SUPPORTED CONFIGURATION METHOD";
            tooltip += str +
                        "\n\nThe REPORT SUPPORTED CONFIGURATION METHOD command requests\n" + 
                        "that information regarding the configuration method(s) the\n" + 
                        "target supports and wether an application client\n" + 
                        "may change configurations using those methods.";
                        
            decoder = "ShowRptSuppCfgMethod";
        }
                     
        serv_action == 0x0A : 
        { 
            str = "REPORT TRGT PORT GRPS";
            tooltip += "REPORT TARGET PORT GROUPS" +
                        "\n\nThe REPORT TARGET PORT GROUPS command requests\n" + 
                        "that the device server send target port group\n" + 
                        "information to the application client."; 
        }
         
        serv_action == 0x0B : 
        { 
            str = "REPORT ALIASES";
            tooltip += str +
                        "\n\nThe REPORT ALIASES command requests\n" + 
                        "that the device server return the alias list.";                                                                               
        }                     
                        
        serv_action == 0x0C : 
        { 
            str = "REPORT SPRTD OPCODES";
            tooltip += "REPORT SUPPORTED OPERATION CODES" +
                    "\n\nThe REPORT SUPPORTED OPERATION CODES command\n" + 
                    "requests information on commands the addressed\n" + 
                    "logical unit supports.";
                    
            decoder = "ShowRepSprtdOprCds";        
        }        
       
       
        
        serv_action == 0x0D : 
        { 
            str = "REPORT SPRTD TSK MGMT FNS";
            tooltip += "REPORT SUPPORTED TASK MANAGEMENT FUNCTIONS" +
                        "\n\nThe REPORT SUPPORTED TASK MANAGEMENT FUNCTIONS\n" + 
                        "command requests information on task management\n" + 
                        "functions the addressed logical unit supports.";  
           
           decoder = "ShowSupportedTaskManagement";                                                                      
        }                      

        serv_action == 0x0E :
        {
            str = "REPORT PRIORITY";
            tooltip += "REPORT PRIORITY" +
                        "\n\nREPORT PRIORITY command requests the priority\n" +
                        "that has been assigned to one or more I_T nexuses\n" +
                        "associated with the logical unit (i.e., I_T_L nexuses).";
            
            decoder = "ShowRepPriority";                                                           
        }

        serv_action == 0x0F :
        {
            str = "REPORT TIMESTAMP";
            tooltip += "REPORT TIMESTAMP" +
                        "\n\nThe REPORT TIMESTAMP command requests that the device\n" + 
                        "server return the value of the logical unit's timestamp.";                                               
        }
        
        serv_action == 0x10 :
        {
            str = "MANAGEMENT PROTOCOL IN";
            tooltip += "MANAGEMENT PROTOCOL IN" +
                        "\n\nThe MANAGEMENT PROTOCOL IN command is used to \n" + 
                        "retrieve management protocol information.";
                        
             decoder = "ShowMgmProtocolIn";                                                                       
        }
        
        default    : 
        {
            str = Format("0x%X", serv_action);
            tooltip += str;
        }
    };
    
    options = [["REPORT ASSIGNED/UNASSIGNED P_EXTENT", 0x00], ["REPORT COMPONENT DEVICE", 0x01] , ["REPORT COMPONENT DEVICE ATTACHMENTS", 0x02], ["REPORT PERIPHERAL DEVICE",0x03 ],
		["REPORT PERIPHERAL DEVICE ASSOCIATIONS" , 0x04], ["REPORT IDENTIFYING INFORMATION", 0x05], ["REPORT STATES", 0x06],
		["REPORT DEVICE IDENTIFICATION", 0x07], ["REPORT UNCONFIGURED CAPACITY", 0x08], ["REPORT SUPPORTED CONFIGURATION METHOD", 0x09],
		["REPORT TRGT PORT GRPS", 0x0A], ["REPORT ALIASES", 0x0B], ["REPORT SPRTD OPCODES",0x0C] ,["REPORT SPRTD TSK MGMT FNS", 0x0D],
		["REPORT PRIORITY",0x0E], ["REPORT TIMESTAMP",0x0F], ["MANAGEMENT PROTOCOL IN",0x10]];

    val = VS;  # save global View Settings
    
    # we use a simple adding payload cell function here - 
    # in order to show 'SERVICE ACTION' cell in collapsed state.
    #
    AddPayLoadCell( "Service Action", str, tooltip + AddErrorTooltip(), error, [_CELLINFO, 0, options ]  );
    
    VS = val;  # restore global View Settings
    
    
    #-----------------------------------------------------------------------------------------
    
    if( decoder != null ) Call( decoder );
    else                  ShowMntnInCommon();  
    
}


ShowMgmProtocolIn()
{
    val = NextNBits_(8);
    tooltip = "MANAGEMENT PROTOCOL field.\n";
                    
    select
    {
        val == 0x00:
			tooltip += "Management protocol information";
        
        val == 0x30:
            tooltip += "Defined by the SNIA";
        val == 0x31:
            tooltip += "Defined by the SNIA";
        val == 0x32:
            tooltip += "Defined by the SNIA";
        val == 0x33:
            tooltip += "Defined by the SNIA";
        val == 0x34:
            tooltip += "Defined by the SNIA";
        val == 0x35:
			tooltip += "Defined by the SNIA";
        
    };
    
    AddBlockPLCell("MANAGEMENT PROTOCOL", Format("0x%02X", val) ,tooltip,  "The MANAGEMENT PROTOCOL field.");    
    
    AddBlockPLCell("MANAGEMENT PROTOCOL SPECIFIC1", Format("0x%06X", NextNBits_(24)), "The MANAGEMENT PROTOCOL SPECIFIC1 field.");
    
    ShowAllocLen(32);
    
    AddBlockPLCell("MANAGEMENT PROTOCOL SPECIFIC2", Format("0x%02X", NextNBits_(8)), "The MANAGEMENT PROTOCOL SPECIFIC2 field.");        
}

ShowMntnInCommon()
{
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);
    
    ShowAllocLen(32);
    
    PLReservedCheck(8);    
}

ShowRepPriority()
{   
    AddBlockPLCell("PRIORITY REPORTED", NextNBits_(2), "PRIORITY REPORTED field.", FieldColor, [_CELLINFO, 0, options ]);

    PLReservedCheck(6);
    
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);
    
    ShowAllocLen(32);
    
    PLReservedCheck(8);  
}

ShowSupportedTaskManagement()
{
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);
    
    val = NextNBits_(32);
    
    if(val < 0x4)
    {
	    tooltip = Format("The ALLOCATION LENGTH (%u) is not greater than 4h. \n" , val); 
    }
    
    AddBlockPLCell("AllocLen", Format("0x%02X", val), 
          "The ALLOCATION LENGTH field in the CDB indicates\n" + 
          "how much space has been allocated for the returned\n" + 
          "parameter list." + AddWarningTooltip(tooltip), _ERROR);
    
    PLReservedCheck(8);   
}

ShowRepIDInfo()
{
    PLReservedCheck(8);
    PLReservedCheck(8);
    
    AddBlockPLCell("LUN", GetFld16H(), "The LUN field.");    
    
    ShowAllocLen(32);
    
    AddBlockPLCell("INFORMATION TYPE", NextNBits_(7), "The INFORMATION TYPE field.");
    
    PLReservedCheck(1);            
}


ShowRepSprtdOprCds()
{
    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("RCTD", GetBitStr(), "RCTD field.", FieldColor, [_CELLINFO, 0, options ]);

    PLReservedCheck(4);
    
    
    #------------------------------------ REPORTING OPTIONS ---------------------------------------
    val = NextNBits_(3);
    
    tooltip = "REPORTING OPTIONS field.\n" + 
    Format("Value   : 0x%X\n", val) +
           "Meaning : ";
    
    
    ClearError();
    select
    {
        val == 0b000 : 
        { 
            str = "All";
            tooltip += str +
                    "\n\nA list of all operation codes and service actions\n" + 
                    "supported by the logical unit shall be returned\n" + 
                    "in the all_commands parameter data format.";
        }
        
        
        val == 0b001 :
        { 
            str = "All opcodes";
            tooltip += str +
                    "\n\nThe command support data for the operation code\n" + 
                    "specified in the REQUESTED OPERATION CODE field\n" + 
                    "shall be returned in the one_command parameter\n" + 
                    "data format.";
        }
        
        
        val == 0b010 :
        { 
            str = "All service actions";
            tooltip += str +
                    "\n\nThe command support data for the operation code\n" + 
                    "specified in the REQUESTED OPERATION CODE field\n" + 
                    "shall be returned in the one_command parameter\n" + 
                    "data format.";
        }       
        
        default    : SetReservedError();
    };
    
       
    
    AddBlockPLCell( "REPORTING OPTIONS", str, tooltip + AddErrorTooltip(), error );
    
    #-----------------------------------------------------------------------------------------
    
    
    AddBlockPLCell("REQ OPCODE", GetFld8H(), 
        "The REQUESTED OPERATION CODE field specifies the\n" + 
        "operation code of the command to be returned\n" + 
        "in the one_command parameter data format.");    
    
    
    AddBlockPLCell("REQ SERVICE ACTN", GetFld16H(), 
        "The REQUESTED SERVICE ACTION field specifies the\n" + 
        "service action of the command to be returned\n" + 
        "in the one_command parameter data format.");    
        
    
    ShowAllocLen(32);
    PLReservedCheck(8);   
}

ShowReqDataTrnsferElmntInq()
{
    PLReservedCheck(3);
    
    ClearError();
    serv_action = NextNBits_(5);
      
    tooltip = "SERVICE ACTION field";
    if(serv_action != 0x06)
    {
		error = _ERROR;
		tooltip = "The service action value must be 0x06";
    }
		
	AddBlockPLCell("SERVICE ACTION", Format("%02Xh", serv_action ), tooltip , error);
	
    AddBlockPLCell( "DATA TRANSFER ELEMENT ADDR", GetFld16H(),
        "The DATA TRANSFER ELEMENT ADDRESS field specifies the element\n" + 
        "is to be used in processing this command.");
        
    PLReservedCheck(7);
    
    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("EVPD", GetBitStr(), "An enable vital product data (EVPD) bit of one specifies\n" + 
		"that the device server shall return the vital product data\n" + 
		"specified by the PAGE OR OPERATION CODE field.", FieldColor, [_CELLINFO, 0, options ]);

	AddBlockPLCell("PAGE CODE", Format("0x%02X", NextNBits_(8)) , "PAGE CODE field.");          	
	
    AddBlockPLCell("AllocLen", Format("%d", NextNBits_(32)), "ALLOCATION LENGTH field.");
    
    PLReservedCheck(8);    	
}

ShowAsigndUnAsignedPExt()
{
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	AddBlockPLCell("LUN_P", Format ("0x%04X", NextNBits_(16)),"The LUN_P field.");
	
	ShowAllocLen(32);
	
	PLReservedCheck(5);
	
    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("ASSIGN", GetBitStr(), "ASSIGN field", FieldColor, [_CELLINFO, 0, options ]);	
    
    PLReservedCheck(1);
    
    AddBlockPLCell("RPTSEL", GetBitStr(), "RPTSEL field", FieldColor, [_CELLINFO, 0, options ]);	
}

ShowRptCompDev()
{
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	AddBlockPLCell("LUN_C", Format ("0x%04X", NextNBits_(16)),"The LUN_C field.");
	
	ShowAllocLen(32);
	
	PLReservedCheck(7);
	    
    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("RPTSEL", GetBitStr(), "RPTSEL field", FieldColor, [_CELLINFO, 0, options ]);
}

ShowRptCompDevAttch()
{
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	AddBlockPLCell("LUN_C", Format ("0x%04X", NextNBits_(16)),"The LUN_C field.");
	
	ShowAllocLen(32);
	
	PLReservedCheck(7);
	    
    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("RPTSEL", GetBitStr(), "RPTSEL field", FieldColor, [_CELLINFO, 0, options ]);
}

ShowPerphDev()
{
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	AddBlockPLCell("LUN_P", Format ("0x%04X", NextNBits_(16)),"The LUN_P field.");
	
	ShowAllocLen(32);
	
	PLReservedCheck(4);
	
    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("RPTMBUS", GetBitStr(), "RPTMBUS field", FieldColor, [_CELLINFO, 0, options ]);	
    
    PLReservedCheck(1);
    
    sel_port = NextNBits_(2);
    
    tooltip = "SELECT REPORT field.\n" +     
    Format("Value   : 0x%X\n", sel_port) +
           "Meaning : ";           
    
    ClearError();
    select
    {
		sel_port == 0b00: tooltip+= "The target shall report on all the peripheral\n" + "device(s) within the target.";
		sel_port == 0b01: tooltip+= "The target shall report only on the peripheral\n" + "device indicated in the LUN_P field."; 
		sel_port == 0b10: tooltip+= "The target shall report all the peripheral device(s)\n" + "within the target that have the state of not available";
		
		default    : SetReservedError();
    };
     
                   
    AddBlockPLCell("SELECT REPORT", Format ("0x%01X", sel_port), tooltip + AddErrorTooltip(), error );	
}

ShowPerphDevAssoc()
{	
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	AddBlockPLCell("LUN_P", Format ("0x%04X", NextNBits_(16)),"The LUN_P field.");
	
	ShowAllocLen(32);
	
	PLReservedCheck(4);
	
    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("RPTMBUS", GetBitStr(), "RPTMBUS field", FieldColor, [_CELLINFO, 0, options ]);	
          
    PLReservedCheck(1);
    PLReservedCheck(1);
    
    AddBlockPLCell("RPTSEL", GetBitStr(), "RPTSEL field", FieldColor, [_CELLINFO, 0, options ]);
}

ShowReportStates()
{
	PLReservedCheck(8);
	PLReservedCheck(4);
	
	AddBlockPLCell("LOGICAL UNIT TYPE", Format ("0x%04X", NextNBits_(4)),"The LOGICAL UNIT TYPE field contains the type\n" +
		"of logical unit designated by the LUN field.");
	
	AddBlockPLCell("LUN", Format ("0x%04X", NextNBits_(16)),"The LUN field.");
	
	ShowAllocLen(32);	
	
	PLReservedCheck(2);	 
	
    report_state = NextNBits_(2);
    
    tooltip = "REPORT STATES field.\n" +     
    Format("Value   : 0x%X\n", report_state) +
           "Meaning : ";           
    
    ClearError();
    select
    {
		report_state == 0b00: tooltip+= "Report all states for all logical units.";
		report_state == 0b01: tooltip+= "Report all states for all of the logical unit(s)\n" + "of the type listed in the LOGICAL UNIT TYPE field."; 
		report_state == 0b10: tooltip+= "Report all states for the selected logical unit.\n";
		
		default    : SetReservedError();
    };
     
                   
    AddBlockPLCell("REPORT STATES", Format ("0x%01X", report_state), tooltip + AddErrorTooltip(), error );
    	
	PLReservedCheck(4);	 
}

ShowRptDevID()
{
	PLReservedCheck(8);
	PLReservedCheck(4);
	
	AddBlockPLCell("LOGICAL UNIT TYPE", Format ("0x%04X", NextNBits_(4)),"The LOGICAL UNIT TYPE field contains the type\n" +
		"of logical unit designated by the LUN field.");
	
	AddBlockPLCell("LUN", Format ("0x%04X", NextNBits_(16)),"The LUN field.");
	
	ShowAllocLen(32);
	
	PLReservedCheck(8);	    
}

ShowUnCfgCapacity()
{
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	ShowAllocLen(32);
	
	PLReservedCheck(8);
}

ShowRptSuppCfgMethod()
{	
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	ShowAllocLen(32);
	
	PLReservedCheck(8);

}
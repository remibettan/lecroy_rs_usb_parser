#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_MaintenanceOut.inc
#
#  SCSI CDB MAINTENANCE OUT Command decoder functions
################################################################################




ShowMaintenanceOut()
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
            str = "ADD PERPH DEV/COMP DEV ATCH";
            tooltip += str +
                        "\n\nThe ADD PERIPHERAL DEVICE/COMPONENT DEVICE ATTACH TO COMPONENT DEVICE command requests that\n" + 
                        "peripheral device or a component device be added to the target." ;
                        
            decoder = "ShowPerphDevCompDevAttch";            
        }
        
        serv_action == 0x01 : 
        { 
            str = "ATTACH TO COMPONENT DEVICE";
            tooltip += str +
                        "\n\nThe ATTACH TO COMPONENT DEVICE command requests that\n" + 
                        "the target logically attach one or more logical\n" + 
                        "unit(s) to a component device.";  
                        
            decoder = "ShowAttchToCompDev";            
        }        

        serv_action == 0x02 : 
        { 
            str = "EXCHANGE P_EXTENT";
            tooltip += str +
                        "\n\nThe EXCHANGE P_EXTENT command requests that\n" + 
                        "the target replace a p_extent with another p_extent";
                        
            decoder = "ShowExchPExtent";            
 
        }
         
        serv_action == 0x03 : 
        { 
            str = "XCHG PERPH DEV/COMP DEV";
            tooltip += str +
                        "\n\nThe EXCHANGE PERIPHERAL DEVICE/COMPONENT DEVICE command requests that\n" + 
                        "the target replace one peripheral device or component device with\n" + 
                        "another peripheral device or component device.";
                        
            decoder = "ShowExchPerphDevCompDev";          
        }
        
        serv_action == 0x04 : 
        { 
            str = "INSTRUCT COMPONENT DEVICE";
            tooltip += str +
                        "\n\nThe  INSTRUCT COMPONENT DEVICE command requests that\n" + 
                        "the target to take the requested action on the\n" + 
                        "addressed component device.";
                        
            decoder = "ShowInsertCompDev";            
        }        
        
        serv_action == 0x05 : 
        { 
            str = "REMOVE PERPH DEV/COMP DEV";
            tooltip += str +
                        "\n\nThe  REMOVE PERIPHERAL DEVICE/COMPONENT DEVICE command requests that\n" + 
                        "peripheral device or a component device be removed from the target."; 

            decoder = "ShowRemPerphDevCompDev";            
        }
                            
        serv_action == 0x06 : 
        { 
            str = "SET IDENTIFYING INFORMATION";
            tooltip += str +
                        "\n\nThe SET IDENTIFYING INFORMATION command requests that\n" + 
                        "the device server set identifying information in the logical\n" + 
                        "unit be set to the value received in the SET\n" + 
                        "SET IDENTIFYING INFORMATION parameter list.";
                        
            decoder = "ShowSetDevID";            
        }
         
        serv_action == 0x07 : 
        { 
            str = "BRK PERPH DEV/COM DEV";
            tooltip += str +
                        "\n\nThe BREAK PERIPHERIAL DEVICE/COMPONENT DEVICE command requests that\n" + 
                        "peripheral device or a component device be placed into a broken state.";
                        
            decoder = "ShowBrkPerphDevCompDev";            
        }
                 
        serv_action == 0x0B : 
        { 
            str = "CHANGE ALIASES";
            tooltip += str +
                        "\n\nThe CHANGE ALIASES command requests that the device\n" + 
                        "server maintain and make changes to a list of\n" + 
                        "associations between eight byte alias values\n" + 
                        "and SCSI device or port designations.";                                               
        }                              
            
        serv_action == 0x0A : 
        { 
            str = "SET TARGET PORT GROUPS";
            tooltip += str +
                    "\n\nThe SET TARGET PORT GROUPS command requests the\n" + 
                    "device server to set the asymmetric access state\n" + 
                    "of all of the target ports in the specified target\n" + 
                    "port groups.";                                
        }        


        serv_action == 0x0E :
        {
            str = "SET PRIORITY";
            tooltip += "SET PRIORITY" +
                        "\n\nSET PRIORITY command requests\n" +
                        "that a priority be set to the specified value.";
                        
            decoder = "ShowSetPriority";
        }


        serv_action == 0x0F :
        {
            str = "SET TIMESTAMP";
            tooltip += "SET TIMESTAMP" +
                        "\n\nThe SET TIMESTAMP command requests\n" + 
                        "the device server to initialize the timestamp.";                                               
        }

        serv_action == 0x10 :
        {
            str = "MANAGEMENT PROTOCOL OUT";
            tooltip += "MANAGEMENT PROTOCOL OUT" +
                        "\n\nThe MANAGEMENT PROTOCOL OUT command\n" + 
                        "is used to send data to the logical unit.";  
                        
            decoder = "ShowMgmProtocolOut";                                             
        }
                
        default    : 
        {
            str = Format("0x%X", serv_action);
            tooltip += str;
        }
    };
    
   
    options = [["ADD PERPH DEV/COMP DEV ATCH", 0x00], ["ATTACH TO COMPONENT DEVICE", 0x01] , ["EXCHANGE P_EXTENT", 0x02],
		["XCHG PERPH DEV/COMP DEV", 0x03], ["INSTRUCT COMPONENT DEVICE" , 0x04], ["REMOVE PERPH DEV/COMP DEV", 0x05], 
		["SET IDENTIFYING INFORMATION", 0x06], ["BRK PERPH DEV/COM DEV", 0x07], ["CHANGE ALIASES", 0x0B], 
		["SET TARGET PORT GROUPS", 0x0A],["SET PRIORITY", 0x0E],["SET TIMESTAMP", 0x0F], ["MANAGEMENT PROTOCOL OUT", 0x10]];

    val = VS;  # save global View Settings
    
    # we use a simple adding payload cell function here - 
    # in order to show 'SERVICE ACTION' cell in collapsed state.
    #
    AddPayLoadCell( "Service Action", str, tooltip + AddErrorTooltip(), error , [_CELLINFO, 0, options ]);
    
    VS = val;  # restore global View Settings
    
    #-----------------------------------------------------------------------------------------
    
    if( decoder != null ) Call( decoder );
    else                  ShowMntnOutCommon();  
    
}

ShowSetPriority()
{
    AddBlockPLCell("I_T_L NEXUS TO SET", NextNBits_(2), "I_T_L NEXUS TO SET field.", FieldColor, [_CELLINFO, 0, options ]);
    
    PLReservedCheck(6);
    
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8); 
    
    ShowParamListLen(32);
    
    PLReservedCheck(8); 
}

ShowSetDevID()
{        
    PLReservedCheck(8);
    PLReservedCheck(8);
    
    AddBlockPLCell("LUN", GetFld16H(), "The LUN field.");    
    
    ShowParamListLen(32);
    
    AddBlockPLCell("INFORMATION TYPE", NextNBits_(7), "The INFORMATION TYPE field.");
    
    PLReservedCheck(1); 
}

ShowMntnOutCommon()
{
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);
    
    ShowParamListLen(32);
    
    PLReservedCheck(8);
    
}


ShowMgmProtocolOut()
{
    val = NextNBits_(8);
    tooltip = "MANAGEMENT PROTOCOL field.\n";                    
    
    select
    {      
        (val == 0x30) :  tooltip += "Defined by the SNIA";
        (val == 0x31) :  tooltip += "Defined by the SNIA";
        (val == 0x32) :  tooltip += "Defined by the SNIA";
        (val == 0x33) :  tooltip += "Defined by the SNIA";
        (val == 0x34) :  tooltip += "Defined by the SNIA";
        (val == 0x35) :  tooltip += "Defined by the SNIA";
        
    };
     
    AddBlockPLCell("MANAGEMENT PROTOCOL", Format("0x%02X", val), tooltip, "The MANAGEMENT PROTOCOL field.");    
    
    AddBlockPLCell("MANAGEMENT PROTOCOL SPECIFIC1", Format("0x%06X", NextNBits_(24)), "The MANAGEMENT PROTOCOL SPECIFIC1 field.");
    
    ShowParamListLen(32);
    
    AddBlockPLCell("MANAGEMENT PROTOCOL SPECIFIC2", Format("0x%02X", NextNBits_(8)), "The MANAGEMENT PROTOCOL SPECIFIC2 field.");        
}


ShowPerphDevCompDevAttch()
{
	AddBlockPLCell("DEVICE TYPE", Format ("0x%02X", NextNBits_(8)), "Peripheral Device Type or the component device type");

	PLReservedCheck(8);

	AddBlockPLCell("LUN", GetFld16H(), "The LUN field.");  

    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);
    
    PLReservedCheck(1);
    
    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("SETLUN", GetBitStr(), "SETLUN field", FieldColor, [_CELLINFO, 0, options ]);	 
    
    PLReservedCheck(4);
           
    AddBlockPLCell("ADDPORC", GetBitStr(), "ADDPORC field", FieldColor, [_CELLINFO, 0, options ]);	 
    
    PLReservedCheck(1);
}

ShowAttchToCompDev()
{
    PLReservedCheck(8);
    PLReservedCheck(8);

	AddBlockPLCell("LUN_C", Format ("0x%04X", NextNBits_(16)),"The LUN_C field.");
	
    AddBlockPLCell("LIST LENGTH", Format ("0x%04X", NextNBits_(32)),"The LIST LENGTH field.");
    
    PLReservedCheck(8);
}

ShowBrkPerphDevCompDev()
{
	AddBlockPLCell("DEVICE TYPE", Format ("0x%02X", NextNBits_(8)), "Peripheral Device Type or the component device type");

	PLReservedCheck(8);

	AddBlockPLCell("LUN", GetFld16H(), "The LUN field.");  

    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);
       
    PLReservedCheck(6);
   
    options = [ ["set", 1], ["Not set", 0] ];       
    AddBlockPLCell("BRKPORC", GetBitStr(), "BRKPORC field", FieldColor, [_CELLINFO, 0, options ]);	 
    
    PLReservedCheck(1);
}

ShowExchPExtent()
{
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);
    
    AddBlockPLCell("LIST LENGTH", Format ("0x%04X", NextNBits_(32)),"The LIST LENGTH field.");
    
    PLReservedCheck(7);    
    
    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("IMMED", GetBitStr(), "IMMED field", FieldColor, [_CELLINFO, 0, options ]);	 
}

ShowExchPerphDevCompDev()
{
    PLReservedCheck(8);
    PLReservedCheck(8);
    
    AddBlockPLCell("OLD LUN", Format ("0x%04X", NextNBits_(16)),"The OLD LUN field.");
    
    PLReservedCheck(8);
    PLReservedCheck(8);
    
    AddBlockPLCell("NEW LUN", Format ("0x%04X", NextNBits_(16)),"The NEW LUN field.");
    
    PLReservedCheck(6);
    
    options = [ ["set", 1], ["Not set", 0] ];
    
    AddBlockPLCell("EXPORC", GetBitStr(), "EXPORC field", FieldColor, [_CELLINFO, 0, options ]);	         
    AddBlockPLCell("IMMED", GetBitStr(), "IMMED field", FieldColor, [_CELLINFO, 0, options ]);	 
}

ShowInsertCompDev()
{
    come_device_ins = NextNBits_(8);
    
    tooltip = "OMPONENT DEVICE INSTRUCTION field.\n" +     
    Format("Value   : 0x%X\n", come_device_ins) +
           "Meaning : ";           
    
    ClearError();
    select
    {
		come_device_ins == 0x00: tooltip+= "Turn selected component device off.";
		come_device_ins == 0x01: tooltip+= "Turn selected component device on."; 
		
		come_device_ins >= 0x80
		&& come_device_ins <= 0xFF: tooltip+= "Vendor specific";
		
		default    : SetReservedError();
    };
    
	AddBlockPLCell("COMPONENT DEVICE INSTRUCTION", Format ("0x%01X", come_device_ins), tooltip + AddErrorTooltip(), error);

    PLReservedCheck(8);
    
    AddBlockPLCell("LUN_C", Format ("0x%04X", NextNBits_(16)),"The LUN_C field.");
    
	AddBlockPLCell("LIST LENGTH", Format ("0x%04X", NextNBits_(32)),"The LIST LENGTH field.");    
       
    PLReservedCheck(8);   
}

ShowRemPerphDevCompDev()
{
    PLReservedCheck(8);
    PLReservedCheck(8);
    
    AddBlockPLCell("LUN", Format ("0x%04X", NextNBits_(16)),"The LUN field.");
    
    PLReservedCheck(8);
    PLReservedCheck(8);    
    PLReservedCheck(8);
    PLReservedCheck(8);
    
    PLReservedCheck(6);
     
    options = [ ["set", 1], ["Not set", 0] ];    
    AddBlockPLCell("REMPORC", GetBitStr(), "REMPORC field", FieldColor, [_CELLINFO, 0, options ]);	
    
    PLReservedCheck(1);
}
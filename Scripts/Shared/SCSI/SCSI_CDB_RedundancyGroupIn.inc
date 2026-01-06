#
#  Copyright (c) 2010, LeCroy - All Rights Reserved
#
#  SCSI_CDB_RedundancyGroupIn.inc
#
#  SCSI CDB REDUNDANCY GROUP IN Command decoder functions
################################################################################


ShowRedundancyGroupIn()
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
            str = "REPORT REDUNDANCY GROUPS";
            tooltip += 
                        "\n\nThe REPORT REDUNDANCY GROUPS command requests that\n" + 
                        "information regarding redundancy groups within the target\n" +
		                "be sent to the application client.";
		                
        }
            
        serv_action == 0x01 : 
        { 
            str = "REPORT UNASSIGNED REDUNDANCY GROUP SPACE";
            tooltip += str +
                    "\n\nThe REPORT UNASSIGNED REDUNDANCY GROUP SPACE command requests that\n" + 
                    "information regarding the redundancy groups within the target that have  \n" +
                    "protected space which has not yet be configured into to any volume sets, \n" +
                    "be sent to the application client.";
        }        

		serv_action == 0x02 : 
        { 
            str = "REPORT BASIC REDUNDANCY GROUP";
            tooltip += str +
                        "\n\nThe REPORT BASIC REDUNDANCY GROUP command requests that \n" + 
                        "information regarding the selected redundancy group be sent\n" +
                        "to the application client.";
			
			decoder = "ShowReportRedundancyGrp";
        }
			
		(serv_action >= 0x03) && (serv_action < 0x18):
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
    
    options = [ ["REPORT REDUNDANCY GROUPS", 0], ["REPORT UNASSIGNED REDUNDANCY GROUP SPACE", 1], ["REPORT BASIC REDUNDANCY GROUP", 2]];
    
    AddPayLoadCell( "SERVICE ACTION", str, tooltip + AddErrorTooltip(), error, [_CELLINFO, 0, options ] );
    
    VS = val;  # restore global View Settings
    
    #-----------------------------------------------------------------------------------------
    
    if( decoder != null ) Call( decoder );
    else                  ShowRedundancyGrpIn();  
    
}



#-----------------------------

ShowRedundancyGrpIn()
{
	PLReservedCheck(8);
	PLReservedCheck(8);

	ShowLUN_R();
	ShowAllocLen( 32);

	PLReservedCheck(7);
	
	val = NextNBits_(1);
	AddBlockPLCell("RPTSEL", Format ("0x%X", val),
	"RPTSEL field.\n\n"	+
	"Bit 0: Report all the redundancy group within the target.\n"  +
	"Bit 1: Report only on the redundancy group indicated in LUN_R.");
	


}

#-----------------------REPORT_REDUNDANCY_GROUP------------------------

ShowReportRedundancyGrp()
{
	PLReservedCheck(8);
	PLReservedCheck(8);

	ShowLUN_R();
	ShowAllocLen( 32);

	PLReservedCheck(8);
}

#--------------------- LUN_R--------------

ShowLUN_R()
{
	val = NextNBits_(16);
	
	AddBlockPLCell("LUN_R", Format ("0x%04X", val),
	"The LUN_R field specifies the address of the redundancy group\n"  +
	"for which information shall be reported.");
}


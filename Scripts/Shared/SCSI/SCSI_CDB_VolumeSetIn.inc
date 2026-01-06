#
#  Copyright (c) 2010, LeCroy - All Rights Reserved
#
#  SCSI_CDB_VolumeSetIn.inc
#
#  SCSI CDB VOLUME SET IN Command decoder functions
################################################################################


ShowVolumeSetIn()
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
            str = "REPORT VOLUME SETS";
            tooltip += str +
					"\n\nThe REPORT VOLUME SETS command requests that the information \n" + 
	                "regarding volume sets within the target be sent to the application client.";
        
			decoder = "ShowReportVolSet";
        }
            
            
        serv_action == 0x01 : 
        { 
            str = "REPORT UNASSIGNED VOLUME SETS";
            tooltip += str +
        			"\n\nThe REPORT UNASSIGNED VOLUME SETS command requests that an identifier for \n"	+ 
                    "each configured volume set, that does not already have a LUN_V assigned \n"		+ 
					"within the target be sent to the application client.";
			
			decoder = "ShowUnassignedVolSet";
        }        

		serv_action == 0x02 : 
		{ 
			str = "REPORT STORAGE ARRAY CONFIGURATION";
			tooltip += str +
					"\n\nThe REPORT STORAGE ARRAY CONFIGURATION command requests that information \n"	+ 
                    "regarding the selected volume set be sent to the application client.";
		}
			
		serv_action == 0x03 :
		{	
			str = "REPORT BASIC VOLUME SET";
			tooltip += str +
					"\n\n The REPORT BASIC VOLUME SET command requests that information regarding\n"	+
					"the selected volume set within the target be sent to the application client.\n"	+
					"It does not report detailed information on the mapping of the user data.";
		}

		(serv_action >= 0x04) && (serv_action < 0x18) :
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
    
    options = [ ["REPORT VOLUME SETS", 0], ["REPORT UNASSIGNED VOLUME SETS", 1], ["REPORT STORAGE ARRAY CONFIGURATION", 2],
				["REPORT BASIC VOLUME SET", 3] ];
    
    AddPayLoadCell( "SERVICE ACTION", str, tooltip + AddErrorTooltip(), error, [_CELLINFO, 0, options ] );
    
    VS = val;  # restore global View Settings
    
    #-----------------------------------------------------------------------------------------
    
    if( decoder != null ) Call( decoder );
    else                  ShowVolSetIn();  
 }



#--------------------------------------------------------------------

ShowVolSetIn()
{

	PLReservedCheck(8);
	PLReservedCheck(8);
	
	ShowLUN_V();
	ShowAllocLen(32);
	
	PLReservedCheck(8);
}

#---------------REPORT UNASSIGNED_VOLUME_SET---------------------

ShowUnassignedVolSet()
{
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	ShowAllocLen(32);
	
	PLReservedCheck(8);
}


#-------------------REPORT_VOLUME_SET--------------------------

ShowReportVolSet()
{
	PLReservedCheck(8);
	PLReservedCheck(8);
	
	ShowLUN_V();
	ShowAllocLen(32);
	
	PLReservedCheck(7);
	
	val = NextNBits_(1);
	AddBlockPLCell("RPTSEL", Format ("0x%X", val), 
	"RPTSEL field.\n\n"	+
	"Bit 0: Report all the redundancy group within the target.\n" +
	"Bit 1: Report only on the redundancy group indicated in the LUN_R field.");

}

#--------------------LUN_V----------------------
ShowLUN_V()
{
	val = NextNBits_(16);
	
	AddBlockPLCell("LUN_V", Format ("0x%04X", val),
	"The LUN_V field specifies the address of the volume set\n"  +
	"for which information shall be reported.");
}
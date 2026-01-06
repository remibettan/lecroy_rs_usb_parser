#
#  Copyright (c) 2010, LeCroy - All Rights Reserved
#
#  SCSI_CDB_SpareIn.inc
#
#  SCSI CDB SPARE IN Command decoder functions
################################################################################


ShowSpareIn()
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
            str = "REPORT P_EXTENT SPARE";
            tooltip += str +
					"\n\nThe REPORT P_EXTENT SPARE command requests that the information \n"	+ 
	                "regarding p_extent spares within the target be sent to the application client.";

			decoder = "ShowReportPExtentSpare";
        }
            
        serv_action == 0x01 : 
        { 
            str = "REPORT PERIPHERAL DEVICE/COMPONENT DEVICE SPARE";
            tooltip += str +
        			"\n\nThe REPORT PERIPHERAL DEVICE/COMPONENT DEVICE SPARE command requests \n"	+ 
					"the target to create a peripheral device spare or a component device spare\n"	+  
					"or modify an existing peripheral device spare or a component device spare.";
         }        

		(serv_action >= 0x02) && (serv_action < 0x18) :
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
    
    options = [ ["REPORT P_EXTENT SPARE", 0], ["REPORT PERIPHERAL DEVICE/COMPONENT DEVICE SPARE", 1]];
    
    AddPayLoadCell( "SERVICE ACTION", str, tooltip + AddErrorTooltip(), error, [_CELLINFO, 0, options ] );
    
    VS = val;  # restore global View Settings
    
    #-----------------------------------------------------------------------------------------
    
    if( decoder != null ) Call( decoder );
    else                  ShowSprIn();  
 }


#-------------------------REPORT PERIPHERAL DEVICE/COMPONENT DEVICE SPARE---------------------

ShowSprIn()
{

	PLReservedCheck(8);
	PLReservedCheck(8);
	
	ShowLUN_S();
	ShowAllocLen(32);
	
	PLReservedCheck(6);
	
	val = NextNBits_(1);	
	AddBlockPLCell("PORCSEL", Format ("0x%X", val), 
	"PORCSEL field.\n\n"	+
	"Bit 0: Report on all the peripheral device spares within target.\n" +
	"Bit 1: Report on all the component device spares within target.");
	
	val = NextNBits_(1);
	AddBlockPLCell("RPTSel", Format ("0x%X", val), 
	"RPTSEL field.\n\n"		+
	"Bit 0: Report all peripheral/component device spare within target.\n"	+
	"Bit 1: Report peripheral/component device spare indicated in LUN only.");

}



#---------------------------REPORT_P_EXTENT_SPARE-----------------------------------------

ShowReportPExtentSpare()
{

	PLReservedCheck(8);
	PLReservedCheck(8);
	
	ShowLUN_S();
	ShowAllocLen(32);
	
	PLReservedCheck(7);
	
	val = NextNBits_(1);
	AddBlockPLCell("RPTSel", Format ("0x%X", val), 
	"RPTSEL field.\n\n"		+
	"Bit 0: Report all the p_extent spare within target.\n"		+
	"Bit 1: Report p_extent spare indicated in LUN only.");
	
}


#--------------------LUN_S----------------------
ShowLUN_S()
{
	val = NextNBits_(16);
	
	AddBlockPLCell("LUN_S", Format ("0x%04X", val),
	"The LUN_S field specifies the address of the p_extent\n"  +
	"spare for which information shall be reported.");
}

#
#  Copyright (c) 2003, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_AccsCtrlIn.inc
#
#  SCSI CDB ACCESS CONTROL IN decoder functions
################################################################################


ShowAccsCtrlIn()
{
    PLReservedCheck(3);
        
    
    
    #------------------------------------ SERVICE ACTION ---------------------------------------
    serv_action = NextNBits_(5);
    
    tooltip = "SERVICE ACTION field.\n" + 
    Format("Value   : 0x%X\n", serv_action) +
           "Meaning : ";
    
    
    ClearError();
    select
    {
        serv_action == 0x0 : 
        { 
            str = "REPORT ACL";
            tooltip += str +
                        "\n\nThe REPORT ACL service action is used to query\n" + 
                        "the ACL maintained by the access controls coordinator.";
        }
        
        
        
        serv_action == 0x1 : 
        { 
            str = "REPORT LU DESCRIPTORS";
            tooltip += str +
                        "\n\nThe REPORT LU DESCRIPTORS service action reports\n" + 
                        "the inventory of logical units for which access\n" + 
                        "controls may be established.";
        }
            
            
        serv_action == 0x2 : 
        { 
            str = "REPORT ACCS CTRLS LOG";
            tooltip += "REPORT ACCESS CONTROLS LOG" +
                     "\n\nThe REPORT ACCESS CONTROLS LOG service action\n" + 
                     "is used to obtain the access controls log." ;
        }
                
        
        
        serv_action == 0x3 : 
        { 
            str = "REPORT OVERRD LCKUT TMR";
            tooltip += "REPORT OVERRIDE LOCKOUT TIMER" +
                        "\n\nREPORT OVERRIDE LOCKOUT TIMER service action is\n" + 
                        "used query the value of the override lockout\n" + 
                        "timer.";
        }
        
        
        serv_action == 0x4 : 
        { 
            str = "REQUEST PROXY TOKEN";
            tooltip += str +
                        "\n\nREQUEST PROXY TOKEN service action is used to\n" + 
                        "obtain a proxy token for a logical unit to which\n" + 
                        "that initiator port has non-proxy access rights.";
        }
        
        
        (serv_action >= 0x18) && (serv_action <= 0x1F) : 
        { 
            str = "Vendor";
            tooltip += str;
        }            
        
        default    : SetReservedError();
    };
    
    options = [ ["REPORT ACL", 0], ["REPORT LU DESCRIPTORS", 1], ["REPORT ACCS CTRLS LOG", 2], ["REPORT OVERRD LCKUT TMR", 3], ["REQUEST PROXY TOKEN", 4] ];
    
    AddBlockPLCell( "SERVICE ACTION", str, tooltip + AddErrorTooltip(), error, [_CELLINFO, 0, options ] );
    
    #-----------------------------------------------------------------------------------------
    
   if( serv_action == 0x04 ) # REQUEST PROXY TOKEN
   {
  		AddBlockPLCell( "LUN VALUE", GetFld64(), 
			"If the LUN value corresponds to a logical unit that\n" + 
			"is accessible to the requesting initiator port \n" + 
			"either through a TransportID or through the AccessID." ); 
   }
   else
   {
		AddBlockPLCell( "MANAGEMENT ID KEY", GetFld64(), 
			"The management identifier key identifies the application\n" + 
			"that is responsible for managing access controls\n" + 
			"for a SCSI target device." );
   }    
        
   if( serv_action == 0x2 ) # REPORT ACCESS CONTROLS LOG
   {
       PLReservedCheck(6);
       
       
       #------------------------------------ LOG PORTION ---------------------------------------
        val = NextNBits_(2);
        
        tooltip = "LOG PORTION field.\n" + 
        Format("Value   : 0x%X\n", val) +
               "Meaning : ";
        
        
        ClearError();
        select
        {
            val == 0b00 : { str = "Key Overrides"    ;  tooltip += "Key Overrides portion"    ; }    
            val == 0b01 : { str = "Invalid Keys"     ;  tooltip += "Invalid Keys portion"     ; }
            val == 0b10 : { str = "ACL LUN Conflicts";  tooltip += "ACL LUN Conflicts portion"; }
            default    : SetReservedError();
        };
                
        tooltip += "\n\nThe LOG PORTION field specifies\n" + 
                   "the access controls log portion being requested.";
        
        options = [ ["Key Overrides", 0], ["Invalid Keys", 1], ["ACL LUN Conflicts", 2] ];
        
        AddBlockPLCell( "LOG PORTION", str, tooltip + AddErrorTooltip(), error, [_CELLINFO, 0, options ] );
        
        #----------------------------------------------------------------------------------------
        
        PLReservedCheck(8);
        ShowAllocLen(16);        
   }
   else 
        ShowAllocLen(32);
   
   PLReservedCheck(8);   
}
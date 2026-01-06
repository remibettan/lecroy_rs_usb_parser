#
#  Copyright (c) 2003, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_AccsCtrlOut.inc
#
#  SCSI CDB ACCESS CONTROL OUT decoder functions
################################################################################


ShowAccsCtrlOut()
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
            str = "MANAGE ACL";
            tooltip += str +
                        "\n\nThe MANAGE ACL service action is used to authorize\n" + 
                        "access or revoke access to a logical unit or\n" + 
                        "logical units by initiator ports.";
        }
        
        
        
        serv_action == 0x1 : 
        { 
            str = "DISABLE ACCESS CTRLS";
            tooltip += str +
                        "\n\nThe DISABLE ACCESS CONTROLS service action is\n" + 
                        "used to place the access controls coordinator\n" + 
                        "in the access controls disabled state.";
        }
            
            
        serv_action == 0x2 : 
        { 
            str = "ACCESS ID ENROLL";
            tooltip += str +
                    "\n\nThe ACCESS ID ENROLL service action is used by\n" + 
                    "an application client to enroll an AccessID for\n" + 
                    "an initiator port with the access controls coordinator." ;
        }
                
        
        
        serv_action == 0x3 : 
        { 
            str = "CANCEL ENROLLMENT";
            tooltip += str +
                        "\n\nThe CANCEL ENROLLMENT service action is used to\n" + 
                        "remove an initiator port’s enrollment with the\n" + 
                        "access controls coordinator.";
        }
        
        
        serv_action == 0x4 : 
        { 
            str = "CLR ACCS CTRL LOG";
            tooltip += "CLEAR ACCESS CONTROLS LOG" +
                        "\n\nThe CLEAR ACCESS CONTROLS LOG service action is\n" + 
                        "used to instruct the access controls coordinator\n" + 
                        "to reset a specific access control log counter\n" + 
                        "to zero and to clear a portion of the access\n" + 
                        "controls log.";
        }
        
        
        
        serv_action == 0x5 : 
        { 
            str = "MNG OVERRD LCKT TMR";
            tooltip += "MANAGE OVERRIDE LOCKOUT TIMER" +
                        "\n\nThe MANAGE OVERRIDE LOCKOUT TIMER service action\n" + 
                        "is used to manage the override lockout timer.";
        }
        
        
        
        serv_action == 0x6 : 
        { 
            str = "OVERRIDE MGMT ID KEY";
            tooltip += "OVERRIDE MGMT ID KEY" +
                        "\n\nThe OVERRIDE MGMT ID KEY service action is used\n" + 
                        "to override the current management identifier key.";
        }
        
        
        serv_action == 0x7 : 
        { 
            str = "REVOKE PROXY TOKEN";
            tooltip += str +
                        "\n\nThe REVOKE PROXY TOKEN service action is used\n" + 
                        "to cancel all proxy access rights to a logical\n" + 
                        "unit that have been granted under the specified\n" + 
                        "proxy token";
        }
        
        serv_action == 0x8 : 
        { 
            str = "REVOKE ALL PROXY TOKENS";
            tooltip += str +
                        "\n\nThe REVOKE ALL PROXY TOKENS service action is used\n" + 
                        " to cancel all proxy access rights to a specified \n" + 
                        "logical unit that it obtained with zero or more \n" + 
                        "proxy tokens";
        }
                
        serv_action == 0x9 : 
        { 
            str = "ASSIGN PROXY LUN";
            tooltip += str +
                        "\n\nThe ASSIGN PROXY LUN service action is used to request\n" + 
                        "access to a logical unit under the rights of\n" + 
                        "a proxy token.";
        }
        
        
        
        serv_action == 0xA : 
        { 
            str = "RELEASE PROXY LUN";
            tooltip += str +
                        "\n\nThe RELEASE PROXY LUN service action is used to\n" + 
                        "release proxy access to a logical unit created\n" + 
                        "with a proxy token.";
        }
        
        
        
        (serv_action >= 0x18) && (serv_action <= 0x1F) : 
        { 
            str = "Vendor";
            tooltip += str;
        }            
        
        default    : SetReservedError();
    };
    
    options = [ ["MANAGE ACL", 0], ["DISABLE ACCESS CTRLS", 1], ["ACCESS ID ENROLL", 2], ["CANCEL ENROLLMENT", 3], ["CLR ACCS CTRL LOG", 4],
     ["MNG OVERRD LCKT TMR", 5], ["OVERRIDE MGMT ID KEY", 6], ["REVOKE PROXY TOKEN", 7], ["REVOKE ALL PROXY TOKENS" , 8], ["ASSIGN PROXY LUN", 9], ["RELEASE PROXY LUN", 0xA] ];
    
    AddBlockPLCell( "SERVICE ACTION", str, tooltip + AddErrorTooltip(), error, [_CELLINFO, 0, options ] );
    
    #-----------------------------------------------------------------------------------------
    
    
    PLReservedCheck(32);
    PLReservedCheck(32);    
    
    ShowParamListLen(32);   
   
    PLReservedCheck(8);   
}
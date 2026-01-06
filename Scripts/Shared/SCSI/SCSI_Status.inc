#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_Status.inc
#
#  SCSI Status decoder functions
################################################################################



const SCSI_Status_Table = 
[    
#   StatusCode, Status_Name    #
#---------------------------------------------------------
    
    [0x00   , "GOOD"],
    [0x02   , "CHECK CONDITION"],  
    [0x04   , "CONDITION MET"], 
    [0x08   , "BUSY"], 
    [0x10   , "Obsolete"], 
    [0x14   , "Obsolete"], 
    [0x18   , "RESERVATION CONFLICT"], 
    [0x22   , "Obsolete"], 
    [0x28   , "TASK SET FULL"], 
    [0x30   , "ACA ACTIVE"], 
    [0x40   , "TASK ABORTED"]
];
    

ShowSCSIStatus ( status )
{
    SetCellColor ( SCSI_Color );
    
    error = null;

    status_desc = Find ( SCSI_Status_Table, status );
    if ( status_desc  )
    {
        str = status_desc[1];
    }
    else
    {
        str = "Reserved";
        error = _ERROR;
    }
    
    
    tooltip = "SCSI STATUS field.\n" + Format("Value   : 0x%02X.\n", status) 
    + Format("Meaning : %s.\n\n", str) +     
    "Status shall be sent from the logical unit to the\n" + 
    "application client whenever a command ends with a \n" +
    "service response of TASK COMPLETE or LINKED COMMAND\n" +
    "COMPLETE.";
    
    
    
    #------------ Special cells for STATUS in collapsed state ----------    
    VS = Resolve( Prefix + "_STATUS" );
    if( !IsExpanded() && !VS[COLLAPSED] ) 
    {   
        AddSeparator();        
        
        val = SCSI_STATUS_Color;
        if( error ) val = ERROR_COLOR;        

        AddCell( "SCSI STATUS", str, tooltip, SCSI_Color, [_LOWERCOLOR,  val] );
        AddSeparator();
    }
    #--------------------------------------------------------------------    
    
    
    AddPayLoadCell("STATUS", str, tooltip, error );
    RestoreCellColor();
}

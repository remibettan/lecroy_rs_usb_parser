#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_Release10_6.inc
#
#  SCSI CDB RELEASE ELEMENT Commands decoder functions
################################################################################


ShowRelease6()
{
    PLReservedCheck(3);
    
    AddBlockPLCell("Obsolete", GetFld4H(), "Obsolete field.") ;    
    
    ShowElement();    
    ShowReservationID();
    
    PLReservedCheck(16);    
}


ShowRelease10()
{
    PLReservedCheck(3);
    options = [ ["set", 1], ["Not set", 0] ];
    
    AddBlockPLCell("3RDPTY",  GetBitStr(), "The third-party (3RDPTY) bit" , FieldColor, [_CELLINFO, 0, options ]);
    PLReservedCheck(2);    
    

    AddBlockPLCell("LONGID",  GetBitStr(), "The LONGID bit" , FieldColor, [_CELLINFO, 0, options ]);
    
    ShowElement();    
    ShowReservationID();
    
    AddBlockPLCell("3RD Prty DevID", GetFld8H(), "The THIRD-PARTY DEVICE ID field." );    
    
    PLReservedCheck(24);
         
    ShowParamListLen(16);
}



#-------------------------------------------------------------------------------------
#                                   Working functions
#-------------------------------------------------------------------------------------


ShowElement()
{
		options = [ ["set", 1], ["Not set", 0] ];
		
        AddBlockPLCell("ELEMENT",  GetBitStr(), 
        "ELEMENT bit field.\n\n" +
        "If the ELEMENT bit is NOT set, this command shall\n" + 
        "cause the device server to release all unit and\n" + 
        "element reservations that are active from the\n" + 
        "SCSI initiator port to the specified logical\n" + 
        "unit." , FieldColor, [_CELLINFO, 0, options ]);
}



ShowReservationID()
{
    AddBlockPLCell("RESERVATION ID", GetFld8H(), "RESERVATION IDENTIFICATION field.") ;
}
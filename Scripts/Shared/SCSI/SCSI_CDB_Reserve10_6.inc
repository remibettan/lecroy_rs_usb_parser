#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_Reserve10_6.inc
#
#  SCSI CDB Reserve(10) and (6) Command decoder functions
################################################################################


ShowReserve6()
{
    PLReservedCheck(3);    
    AddBlockPLCell("Obsolete", GetFld4H(), "Obsolete field.");
    
    ShowElement();    
    ShowReservationID();    
    
    AddBlockPLCell("ElmtListLen", GetFld16D(), "ELEMENT LIST LENGTH field.");        
}




ShowReserve10()
{
    PLReservedCheck(3);
    
    options = [ ["set", 1], ["Not set", 0] ];
    AddBlockPLCell("3RDPTY",  GetBitStr(), "The third-party (3RDPTY) bit", FieldColor, [_CELLINFO, 0, options ]);
    
    PLReservedCheck(2);
    
    AddBlockPLCell("LONGID",  GetBitStr(), "The LONGID bit", FieldColor, [_CELLINFO, 0, options ]);
    
    ShowElement();    
    ShowReservationID(); 
    
    AddBlockPLCell("3RD Prty DevID",  GetFld8H(), "The THIRD-PARTY DEVICE ID field." );
    
    PLReservedCheck(24);   
    
    ShowParamListLen(16);
}


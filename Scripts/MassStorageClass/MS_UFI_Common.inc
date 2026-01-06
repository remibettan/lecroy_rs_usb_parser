#
#  Copyright (c) 2003, Computer Access Technology Corp. - All Rights Reserved
#
#  MS_UFI_Common.inc
#
#


DoInitialCell(oper_code)
{
    
    CDB_Name = "";  
                
    cdb_dec = FindCDBDefinition( oper_code );  #Find( CDB_DecTable, oper_code );
    if (cdb_dec != null)
    {
        CDB_Name    = cdb_dec[1];
        CDB_Color   = cdb_dec[3];
        CDB_Tooltip = cdb_dec[4]; # Use the ones from SCSI
    }
    if (CDB_Name == "")
    {
        select
        {
            (oper_code == 0x23) : DoReadFormatCap();
            (oper_code == 0x10) : DoRezeroName();
            default             : DoBadOpcode();
        };
    }
}    


DoReadFormatCap()
{
    CDB_Name    = "Read Format Cap";
    CDB_Color   = 0xE02050;
    CDB_Tooltip = "Read Format Capacities";
}


DoRezeroName()
{
    CDB_Name    = "Rezero";
    CDB_Color   = 0x30F040;
    CDB_Tooltip = "Rezero";
}



DoBadOpcode()
{
    CDB_Name    = "INVALID";
    CDB_Color   = ErrorColor;
    CDB_Tooltip = "This value is not defined in UFI";
}



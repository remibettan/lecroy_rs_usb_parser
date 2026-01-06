#
#  Copyright (c) 2003, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_RprtDnstySprt.inc
#
#  SCSI CDB REPORT DENSITY SUPPORT decoder functions
################################################################################


ShowRprtDnstySprt()
{
    PLReservedCheck(6);
    
    options = [ ["set", 1], ["Not set", 0] ];
    
    AddBlockPLCell("MEDIUM TYPE", GetBitStr(), "MEDIUM TYPE field" , FieldColor, [_CELLINFO, 0, options ]);  

    AddBlockPLCell( "MEDIA", GetBitStr(),
        "A MEDIA bit of zero specifies the device server shall\n" + 
        "return density support data block descriptors for\n" + 
        "densities supported by the logical unit for any supported\n" + 
        "media.\n\n" +
        "A MEDIA bit of one specifies the device server\n" + 
        "shall return density support data block descriptors\n" + 
        "for densities supported by the mounted medium.", FieldColor, [_CELLINFO, 0, options ]);
            
    
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);
    PLReservedCheck(8);
    
    ShowAllocLen( 16 );  
}
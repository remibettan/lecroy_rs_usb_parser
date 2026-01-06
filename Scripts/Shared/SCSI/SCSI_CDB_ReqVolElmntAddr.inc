#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_ReqVolElmntAddr.inc
#
#  SCSI CDB REQUEST VOLUME ELEMENT ADDRESS Command decoder functions
################################################################################



ShowReqVolElmntAddrCDB()
{
    PLReservedCheck(3);
    
    options = [ ["set", 1], ["Not set", 0] ];
    
    AddBlockPLCell("VOLTAG",  GetBitStr(), 
        "VOLTAG bit field.\n\n" +
        "A volume tag (VOLTAG) bit of one indicates that\n" + 
        "the logical unit shall report volume tag information,\n" + 
        "if implemented by the logical unit.", FieldColor, [_CELLINFO, 0, options ]); 
       
    AddBlockPLCell( "Obsolete", Format("%d", NextNBits_(4)) , "Obsoleted." );
    
    AddBlockPLCell( "Start Elmt Addr", GetFld16H() , "STARTING ELEMENT ADDRESS  field." );
    
    AddBlockPLCell( "NumOfElmtsToRprt", GetFld16D() , 
        "The NUMBER OF ELEMENTS TO REPORT field specifies\n" + 
        "the maximum number of elements to be reported\n" + 
        "for this command." );
    
    
    PLReservedCheck(8);
        
    ShowAllocLen(24);    
    
    PLReservedCheck(8);        
}


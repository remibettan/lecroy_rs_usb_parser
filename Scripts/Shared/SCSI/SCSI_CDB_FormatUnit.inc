#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_FormatUnit.inc
#
#  SCSI CDB FormatUnit Commands decoder functions
################################################################################




ShowFormatUnit()
{  
   #------------------------------------------- FMTPINFO --------------------------------------------------- 
   fmtpinfo = NextNBits_(2);

   AddBlockPLCell("FMTPINFO", Format("0x%01X", fmtpinfo ), "The combination this field with PROTECTION FIELD USAGE field " +
                                                            "specifies the requested protection type.", 
                                                            FieldColor);

   #------------------------------------------- LONGLIST --------------------------------------------------   
   options = [ ["set", 1], ["Not set", 0] ];   
   AddBlockPLCell("LONGLIST", GetBitStr(), "A LONGLIST bit field.", FieldColor, [_CELLINFO, 0, options ]);
    
   #------------------------------------------- FMTDATA --------------------------------------------------
   fmtdata = NextNBits_(1);
   
   if( fmtdata ) str = "set";
   else          str = "Not set";
    
   AddBlockPLCell("FMTDATA" , str, "A FMTDATA bit field.", FieldColor, [_CELLINFO, 0, options ]);
   
   #------------------------------------------- CMPLST ---------------------------------------------------
   cmplst = NextNBits_(1);
   
   if( cmplst ) str = "set";
   else         str = "Not set";
   
   AddBlockPLCell("CMPLST"  , str, "A complete list (CMPLST) bit field.", FieldColor, [_CELLINFO, 0, options ]);

   #------------------------------------------- Defect List Format ---------------------------------------------------
   defectformat = NextNBits_(3);
   
   str = Format("0x%02X", defectformat );       
    
   AddBlockPLCell("Defect List Format", str, "If the FMTDATA bit is set to one, then the this field " +
                                             "specifies the format of the address descriptors " + 
                                             "in the defect list in the FORMAT UNIT parameter list.", 
                                             FieldColor);
  
   #------------------------------------------- Vendor Specific ---------------------------------------------------    
   AddBlockPLCell("Vendor Specific" , Format("0x%02X", NextNBits_(8)), "Vendor Specific");
  
   #------------------------------------------- Obsolete ---------------------------------------------------    
   AddBlockPLCell("Obsolete" , Format("0x%04X", NextNBits_(16)), "Obsoleted field.");
}
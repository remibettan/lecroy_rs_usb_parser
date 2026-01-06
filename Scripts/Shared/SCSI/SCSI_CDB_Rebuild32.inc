#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_Rebuild32.inc
#
#  SCSI CDB REBUILD(32) (SBC-3) Command decoder functions
#
#  REBUILD(32) is an extended command with operation code - 7Fh.
#  Decoder for extended command should parse CDB payload after 
#  SERVICE ACTION code.
################################################################################


ShowRebuild32()
{
     PLReservedCheck(3);    
    
    
    AddBlockPLCell("DPO"    , GetBitStr(), "DPO bit field.");
    AddBlockPLCell("FUA"    , GetBitStr(), "FUA bit field.");
    AddBlockPLCell("INTDATA", GetBitStr(), "Intermediate data (INTDATA) bit.");     
  
    
    
    #-------------------------------- PORT CONTROL -----------------------------
    val = NextNBits_(2);      
    
    select{
        val == 0b00 : { text = "Same As Rcvd"; str = "00b"; tooltip = "The target transfers the data using the\n" + 
                                                            "same port that received the command." ; }

        val == 0b01 : { text = "Dffr From Rcvd"; str = "01b"; tooltip = "The target transfers the data using a\n" + 
                                                            "different port than the one that received\n" + 
                                                            "the command."; }
                                                            

        val == 0b10 : { text = "One TRGT choice"; str = "10b"; tooltip = "The target transfers the data using one\n" + 
                                                             "port of the target’s choice." ; }
        
        val == 0b11 : { text = "One/More TRGT choice"; str = "11b"; tooltip = "The target transfers the data using one\n" + 
                                                             "or more ports of the target’s choice."; }
    };
    
    tooltip = "PORT CONTROL field.\n\n" + 
    Format("Value   : %s.\n", str) + Format("Meaning : %s.", tooltip);
    
    AddBlockPLCell("PORT CONTROL", text, tooltip);
    #---------------------------------------------------------------------------------
    
    PLReservedCheck(8);
    
    
    #---------------------------- LOGICAL BLOCK ADDRESS -----------------------------
    str  = Format("0x%08X", NextNBits(32));
    str += Format(" %08X" , NextNBits(32));

    IncFieldOffset( 64 );
    
    AddBlockPLCell("LOGICAL BLOCK ADDRESS", str, "The LOGICAL BLOCK ADDRESS field specifies\n" + 
    "the starting logical block address where\n" + 
    "the target shall write the XOR result data\n" + 
    "on its own medium.");
    #--------------------------------------------------------------------------------       
    
    
    PLReservedCheck(32);
    
    AddBlockPLCell("REBUILD LENGTH", Format("%d", NextNBits_(32)), "The REBUILD LENGTH field specifies the number\n" + 
    "of blocks to be written to the medium. It\n" + 
    "also specifies the number of blocks that\n" + 
    "are read from each source.");
    
    ShowParamListLen();    
}

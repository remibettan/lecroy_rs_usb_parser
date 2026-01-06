#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_WriteAttrib.inc
#
#  SCSI CDB WRITE ATTRIBUTE Command decoder functions
################################################################################



ShowWriteAttribCDB()
{
    PLReservedCheck(8); 
    ShowElementAddr();      
    
    AddBlockPLCell("Obsolete", GetFld8D(), "Obsolete");
    
    AddBlockPLCell( "Volume Num", GetFld8D(), "VOLUME NUMBER field." );
    PLReservedCheck(8);     
    AddBlockPLCell( "Partition Num", GetFld8D(), "PARTITION NUMBER field." );
    
    PLReservedCheck(8);
    PLReservedCheck(8);
    
    ShowParamListLen();
    
    PLReservedCheck(8);
}





#-------------------------------------------------------------------------------------
#                                   Working functions
#-------------------------------------------------------------------------------------


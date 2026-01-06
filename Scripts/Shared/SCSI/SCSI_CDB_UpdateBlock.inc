#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_UpdateBlock.inc
#
#  SCSI CDB UpdateBlock Commands decoder functions
################################################################################



ShowUpdateBlock()
{
    PLReservedCheck( 7 );    
    ShowRELADR();
    ShowLBA();
    
    PLReservedCheck( 8 );
    PLReservedCheck( 8 );
    PLReservedCheck( 8 );   
}

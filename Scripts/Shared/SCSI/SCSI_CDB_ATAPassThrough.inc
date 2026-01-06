#
#  Copyright (c) 2013, Teledyne LeCroy Corp. - All Rights Reserved
#
#  SCSI_CDB_AccsCtrlIn.inc
#
#  SCSI CDB ATA PASS-THROUGH functions
################################################################################


ShowATAPassThough12()
{
 
 	Multiple_Count = NextNBits_(3);
	AddPayLoadCell("MULTIPLE_COUNT", Format ("%d",Multiple_Count), "");
    
 	Protocol = NextNBits_(4);
    tooltip = " 0h : Hw Reset \n 1h : Sw reset \n 2h : Reserved \n 3h : Non-data \n 4h : PIO Data-In \n" +
              " 5h : PIO Data-Out \n 6h : DMA \n 7h : DMA Queued \n 8h : Execute Device Diagnostic \n" + 
              " 9h : Device Reset \n Ah : UDMA Data In \n Bh : UDMA Data Out \n Ch : FPDMA \n" + 
              " Dh, Eh : Reserved \n Fh : Return Response Information ";
	AddPayLoadCell("Protocol", Format ("%d",Protocol), tooltip );
    
    PLReservedCheck(1);   
    
 	OffLine = NextNBits_(2);
	AddPayLoadCell("OFF_LINE", Format ("%d",OffLine), "");
    
 	CK_COND = NextNBits_(1);
	AddPayLoadCell("CK_COND", Format ("%d",CK_COND), "");

    PLReservedCheck(1);   
    
    T_DIR = NextNBits_(1);
	AddPayLoadCell("T_DIR", Format ("%d",T_DIR), "");

    BYTE_BLOCK = NextNBits_(1);
	AddPayLoadCell("BYTE_BLOCK", Format ("%d",BYTE_BLOCK), "");
    
    T_LENGTH = NextNBits_(2);
    tooltip = " 00b : No data is transferred \n" +
              " 01b : The transfer length is an unsigned integer specified in the FEATURES (7:0) field \n" + 
              " 10b : The transfer length is an unsigned integer specified in the SECTOR_COUNT (7:0) field \n" +
              " 11b : The transfer length is an unsigned integer specified in the TPSIU ";
	AddPayLoadCell("T_LENGTH", Format ("%d",T_LENGTH), tooltip);

    Features = NextNBits_(8);
	AddPayLoadCell("FEATURES", Format ("%d",Features), "");
    
    SECTOR_COUNT = NextNBits_(8);
	AddPayLoadCell("SECTOR_COUNT", Format ("%d",SECTOR_COUNT), "");

    LBA_LOW = NextNBits_(8);
	AddPayLoadCell("LBA_LOW", Format ("0x%02X",LBA_LOW), "");

    LBA_MID = NextNBits_(8);
	AddPayLoadCell("LBA_MID", Format ("0x%02X",LBA_MID), "");

    LBA_HIGH = NextNBits_(8);
	AddPayLoadCell("LBA_HIGH", Format ("0x%02X",LBA_HIGH), "");
    
    Device = NextNBits_(8);
	AddPayLoadCell("DEVICE", Format ("0x%02X",Device), "");
    
    Command = NextNBits_(8);
	AddPayLoadCell("COMMAND", Format ("%d",Command), "");
    
    PLReservedCheck(8);           
}

ShowATAPassThough16()
{
 	Multiple_Count = NextNBits_(3);
	AddPayLoadCell("MULTIPLE_COUNT", Format ("%d",Multiple_Count), "Multiple Count");
    
 	Protocol = NextNBits_(4);
    tooltip = " 0h : Hw Reset \n 1h : Sw reset \n 2h : Reserved \n 3h : Non-data \n 4h : PIO Data-In \n" +
              " 5h : PIO Data-Out \n 6h : DMA \n 7h : DMA Queued \n 8h : Execute Device Diagnostic \n" + 
              " 9h : Device Reset \n Ah : UDMA Data In \n Bh : UDMA Data Out \n Ch : FPDMA \n" + 
              " Dh, Eh : Reserved \n Fh : Return Response Information ";
	AddPayLoadCell("Protocol", Format ("%d",Protocol), tooltip );
    
 	Extend = NextNBits_(1);
	AddPayLoadCell("EXTEND", Format ("%d",Extend), "");
    
 	OffLine = NextNBits_(2);
	AddPayLoadCell("OFF_LINE", Format ("%d",OffLine), "");
    
 	CK_COND = NextNBits_(1);
	AddPayLoadCell("CK_COND", Format ("%d",CK_COND), "");

    PLReservedCheck(1);   
    
    T_DIR = NextNBits_(1);
	AddPayLoadCell("T_DIR", Format ("%d",T_DIR), "");

    BYTE_BLOCK = NextNBits_(1);
	AddPayLoadCell("BYTE_BLOCK", Format ("%d",BYTE_BLOCK), "");
    
    T_LENGTH = NextNBits_(2);
    tooltip = " 00b : No data is transferred \n" +
              " 01b : The transfer length is an unsigned integer specified in the FEATURES field \n" + 
              " 10b : The transfer length is an unsigned integer specified in the SECTOR_COUNT field \n" +
              " 11b : The transfer length is an unsigned integer specified in the TPSIU ";
	AddPayLoadCell("T_LENGTH", Format ("%d",T_LENGTH), tooltip);

    Features = NextNBits_(16);
	AddPayLoadCell("FEATURES", Format ("%d",Features), "");
    
    SECTOR_COUNT = NextNBits_(16);
	AddPayLoadCell("SECTOR_COUNT", Format ("%d",SECTOR_COUNT), "");

    LBA_LOW = NextNBits_(16);
	AddPayLoadCell("LBA_LOW", Format ("0x%04x",LBA_LOW), "");

    LBA_MID = NextNBits_(16);
	AddPayLoadCell("LBA_MID", Format ("0x%04x",LBA_MID), "");

    LBA_HIGH = NextNBits_(16);
	AddPayLoadCell("LBA_HIGH", Format ("0x%04x",LBA_HIGH), "");
    
    Device = NextNBits_(8);
	AddPayLoadCell("DEVICE", Format ("0x%02X",Device), "");
    
    Command = NextNBits_(8);
	AddPayLoadCell("COMMAND", Format ("%d",Command), "");    
}

ShowATAReturnDescriptor()
{
    Descriptor_Code = NextNBits_(8);
	AddPayLoadCell("DescCode", Format ("ATA Return Descriptor(%xh)",Descriptor_Code), "Descriptor Code");
    
    Add_Desc_Len = NextNBits_(8);
	AddPayLoadCell("AddDescCode", Format ("%d",Add_Desc_Len), "Additional Descriptor Length");
    
    PLReservedCheck(7);   
    
    Extend = NextNBits_(1);
	AddPayLoadCell("Extend", Format ("%d",Extend), "Extend");
    
    Error = NextNBits_(8);
	AddPayLoadCell("Error", Format ("0x%02x",Error), "Error");
    
    Sector_Count = NextNBits_(16);
	AddPayLoadCell("SECTOR_COUNT", Format ("0x%04x",Sector_Count), "");

    LBA_Low = NextNBits_(16);
	AddPayLoadCell("LBA_LOW", Format ("0x%04x",LBA_Low), "LBA Low");

    LBA_Mid = NextNBits_(16);
	AddPayLoadCell("LBA_MID", Format ("0x%04x",LBA_Mid), "LBA Mid");
    
    LBA_High = NextNBits_(16);
	AddPayLoadCell("LBA_HIGH", Format ("0x%04x",LBA_High), "LBA High");

    Device = NextNBits_(8);
	AddPayLoadCell("Device", Format ("0x%02x",Device), "Device");

    Status = NextNBits_(8);
	AddPayLoadCell("Status", Format ("%d",Status), "Status");    
}

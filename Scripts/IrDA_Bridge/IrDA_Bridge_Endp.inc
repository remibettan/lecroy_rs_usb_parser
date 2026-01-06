
%include "CataLyst_Common.inc"
%include "CATCScriptAPI.inc"
%include "UsbCommon.inc"


const IrDAHeaderColor   = 0x004080FF;
const IrDAPayloadColor  = 0x0080A9FF;

#----  Input
# in.Data       - Data_block to decode
# in.DataLength - Length of Data_block 
#
#----  Output
# out.Decoded   - amount of data has been decoded
#


#------------------------  Common Globals -----------------------------------
set UsbDecodeType = "Endpoint";
set UsbEndpType   = "Bulk";
set UsbMaxXferSize = 0x7FFFFFFF;  #try largest possible positive value  
set UsbMaxXferDecodeSize   = 36;  # Max bytes that we will be decoding  
set UsbMaxPktSize          = 512;   
set UsbScriptDecodeType    = 2; # Combined decoding for Cells and Text decoding
set UsbDecHdrType = 2; # This type references decoder byte containing the SCSI Opcode  
set UsbDecHdrLen  = 1; # This 1 byte is passed in to this via the in context
set UsbDecExtraInfoBytePos = 15; # Position of Additional Info byte
set UsbXferCompleteClue = 4;     # this Xfer ends if Bulk In seen during decoding  

# User can select the colors for the fields he chooses
#-------------------------------------------------------------------------------



#############################################################################
#                               View Settings                               #
#############################################################################
#           [collapsed, expanded]   
# const IRDA_#####    = [0, 1];
#-----------------------------------------------------------------------------

#
# Parsing entry point
#

ProcessData_IrDA()
{
    InitType2Decoder();
    Prefix =  "IRDA";   
    
    return ProcessIrDAData();
}

set XBOFs	= 0x55;
set BOF		= 0x53;
set FCS		= 0x33;		# FCS: Frame Check Sequence
set EOF		= 0x44;


ProcessBulkInData()
{
    length = in.DataLength;
    if (length < 4)
    {
        return (0); 
    }
    
   
    byte_0   = GetDataByte(0);
    byte_1   = GetDataByte(1);

	byte_n_1 = GetDataByte(in.DataLength - 2);
	byte_n   = GetDataByte(in.DataLength - 1);

    if( (byte_0 == XBOFs) && (byte_1 == BOF) )
    {
        return IrLAPPayloadWrapper( in.DataLength - 4 );
    }
    else
    {
        return 0;
    }    
}


IrLAPPayloadWrapper(length)
{
       
    AddDecSeparator();
    FieldColor = IrDAHeaderColor;
    AddCaptionCell("  IrDA  ", "Bridge", "This data payload represents a IrLAP Payload."); 
	 
    FieldColor = IrDAPayloadColor;

    
    if (in.Expanded || in.PrepareFldsForDlg)
    {
        AddDecodedTextHeader();
        AddDecSeparator();
        AddStringToDlg("Wrapped IrLAP Payload", "", "");


		xbofs   = GetDataByte(0);
		bof     = GetDataByte(1);

		fcs     = GetDataByte(in.DataLength - 2);
		eof     = GetDataByte(in.DataLength - 1);

		if(xbofs == XBOFs)
		   AddSimplePLCell("XBOFs", Format ("0x%X", xbofs), "XBOFs or STA or 16 PA");
	   else
		   AddSimplePLCell("XBOFs", Format ("0x%X", xbofs), Format("Error: Expected value for XBOFs: 0x%02X", XBOFs), _ERROR);


		if(bof == BOF)
		   AddSimplePLCell("BOF", Format ("0x%X", bof), "BOF or STA");
	   else
		   AddSimplePLCell("BOF", Format ("0x%X", bof), Format("Error: Expected value for BOF: 0x%02X", BOF), _ERROR);


		#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		IrDataLen = (in.DataLength - 4) * 8;
		#AddSimplePLCell("IrDataLen", Format ("0x%X", IrDataLen), "IrDataLen");

		# IrLAP Payload
		AddDataCell( GetNBits ( in.Data, 2*8, IrDataLen ) );
		#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        
		if(fcs == FCS)
		   AddSimplePLCell("FCS", Format ("0x%X", fcs), "FCS");
	   else
		   AddSimplePLCell("FCS", Format ("0x%X", fcs), Format("Error: Expected value for FCS: 0x%02X", FCS), _ERROR);


		if(eof == EOF)
		   AddSimplePLCell("EOF", Format ("0x%X", eof), "EOF or STO");
	   else
		   AddSimplePLCell("EOF", Format ("0x%X", eof), Format("Error: Expected value for EOF: 0x%02X", EOF), _ERROR);

    }
    else # Collapsed
    {
		# No Cell! 
    }

    out.Decoded = in.DataLength;
}

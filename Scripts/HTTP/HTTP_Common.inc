
%include "CataLyst_Common.inc"

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


const HTTP_CaptionColor	= 0x008080FF;
const HTTP_PayLoadColor	= 0x006A9BFF; 

set HTTP_SIGNATURE = 0x43425355;	# OK: 0x43425355


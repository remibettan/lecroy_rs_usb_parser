#
#  Copyright (c) 2002- 2006, LeCroy Corp. PSG  - All Rights Reserved
#
#  PTPStillImageBulkCommon.inc
#
#  Used by Bulk In and Bulk Out
#  

%include "CATCScriptAPI.inc"  
%include "UsbCommon.inc" 
%include "PTPStillImage_Common.inc"
%include "PTPStillImageTables.inc"       #has all the tables that are accessed in this file
%include "PTPStillImageCellColors.inc"
%include "PTPStillImageDeviceInfoDataset.inc"
%include "PTPStillImageStorageInfo.inc"
%include "PTPStillImageObjectInfoDataset.inc"
%include "PTPStillIImageDevicePropDescDataset.inc"
%include "PTPStillIImageObjectPropDescDataset.inc"
%include "PictBridgeTables.inc"
%include "XML.inc"


#----  Input
# in.Data       - Data_block to decode  
# in.DataLength - Length of Data_block  
#
#----  Output
# out.Decoded   - amount of data has been decoded
#

set CellsCount = 0;
set IsDumpPayLoadOccurs = 0;
set UsbDecodeType = "Endpoint";
set UsbClassCode = 0x06;
set UsbMaxXferSize = 0xFFFFFF;
set UsbMaxPktSize          = 512; # will automatically be reduced to 64 if branch is Full Speed     
set UsbMaxXferDecodeSize   = 50000;  # Max bytes that we will be decoding   User can up this if he likes
set UsbDecHdrType = 4; # This type references decoder byte containing the PTP Opcode  
set UsbDecHdrLen  = 2; # This 2 byte is passed in to this via the in context


 
set UsbScriptDecodeType = 2; # Combined decoding for Cells and Text decoding 

#
# Parsing entry point
#
  


# User can select the colors for the fields he chooses


set ContainerLength = 0;
set ContainerType = 0;
set Code = 0;
set TransactionID = 0;
set Payload = 0;
set numOfParams = 0;



#set IsUsb2Hub = 1; # default value
set FullyDecoded = 1;

ProcessBulkData()
{

       
    CellsCount = 0;
    #UnitDecoderInit("PBC");
    
    Code = GetNBits(in.DecodeParams,0, 16);   

    CommonDecoderInit(); 
    
    InitTables();
    AddSeparator();
    FieldColor = StillImageCaptionColor;
    AddCaptionCell("Still","Image","In order to view comments in text field, user must expand this caption cell",_MONOCOLOR);  # will allow for the expansion of certain fields
    AddSeparator();
    isEnoughData = 1; # true
    out.Decoded = 0;
    if (Code == 0)
    {
        if (in.DataLength >= out.Decoded + 4)
        {
            ContainerLength = NextDataDWord_();
            FieldColor = ContainerLengthColor;
            if (ContainerLength == 0xFFFFFFFF)
            {
                AddLimitedPayLoadCell("ConLen", "Unknown Length", Format("ContainerLength HexVal: 0x%08X. Special value for unknown length", ContainerLength));
                ContainerLength = in.DataLength;
            }
            else
            {
                AddLimitedPayLoadCell("ConLen", Format("%d", ContainerLength), Format("ContainerLength: %d bytes in the container(decimal)", ContainerLength)+Format("\nContainerLength HexVal: 0x%08X", ContainerLength));
            }
            out.Decoded += 4;
        }
        else
            isEoughData = 0;
        
        if (isEnoughData == 1 && in.DataLength >= out.Decoded + 2)
        {
            FieldColor = ContainerTypeColor;
            ContainerType = NextDataWord_();
            _row = Find(PTPBulkTable, ContainerType);
            AddLimitedPayLoadCell("ConType", _row[1], _row[3], FieldColor, [_TABULARCELL, CELL_STILL_IMAGE_CON_TYPE]);
            out.Decoded += 2;
        }
        else
            isEoughData = 0;
        
        if (isEnoughData == 1 && in.DataLength >= out.Decoded + 2)
        {
            Code = NextDataWord_();
            FieldColor = CodeColor;
            if (_row[2] != null)
            {
                _subCode = Find( _row[2], Code);
                keyBit = Code >> 15;
                if (_subCode[0] == 0xFFFF && keyBit == 0b1)
                {
                    keyBit = Code >> 11;
                    keyBit = keyBit & 0b00001;   # check the 11th bit
                    if (keyBit == 0b00001)
                    {
                        _subCode[1] = "MTP Extension";
                    }
                    else
                    {
                        _subCode[1] = "Vendor Extension";
                    }
                }
                if (_row[0] == 3)
                    AddLimitedPayLoadCell("Code", _subCode[1], _subCode[2], FieldColor, [_TABULARCELL, CELL_STILL_IMAGE_CODE]);
                else
                    AddLimitedPayLoadCell("Code", _subCode[1], FormatEx("Code for %s: 0x%04X.", _row[1], Code), FieldColor, [_TABULARCELL, CELL_STILL_IMAGE_CODE]);
            }
            else
            {
                AddLimitedPayLoadCell("Code", Format("0x%04X", Code), "Code Hex value", FieldColor, [_TABULARCELL, CELL_STILL_IMAGE_CODE]);
            }
            out.Decoded += 2;
        }
        else
            isEoughData = 0;
        
        if (isEnoughData == 1 && in.DataLength >= out.Decoded + 4)
        {        
            FieldColor = TransactionIDColor;
            TransactionID = NextDataDWord_();
            if (TransactionID == 0xFFFFFFFF)
            {
                AddLimitedPayLoadCell("TransID", "Invalid", Format("HexVal of TransactionID: 0x%08X", TransactionID));
            }
            else
            {
                AddLimitedPayLoadCell("TransID", Format("%u", TransactionID), Format("HexVal of TransactionID: 0x%08X", TransactionID));
            }
            out.Decoded +=4;
        }
        else
            isEnoughData = 0;
        FieldColor = GeneralFieldDataColor;
        if (isEnoughData == 1 && _row[1] != null && in.DataLength > out.Decoded)
            isEnoughData = Call (_row[1]);
    }
    else
    {
        #AddLimitedCell( "Code", Format("0x%04X", Code) );
        
        FieldColor = GeneralFieldDataColor;
        isEnoughData = Data();
    }

    if (isEnoughData == 0 && IsDumpPayLoadOccurs == 0)
        AddNoEnoughDataCell(); 

    return Complete();
}





#
#  Copyright (c) 2002, Computer Access Technology Corp. - All Rights Reserved
#
#  MS_Requests.dec
#
#  Mass Storage Request Decoder
#

#----  Input
# in.Data       - Data_block to decode
# in.DataLength - Length of Data_block 
#
#----  Output
# out.Decoded   - amount of data has been decoded
#


set bReqType = 0;
set bRequest = 0;
set wValue   = 0;
set wIndex   = 0;
set wLength  = 0;

set ReqType = 0xFFFF;

ProcessMassStorageData()
{
    ProcessDataInit();
    
    ReqType = 73;
    
    #SCSILevel = GetNBits(in.DecodeParams, 8, 8);
    Read_SCSILevel();
    GetNBits(in.Data, 0, 0); # reset pointers  
      
    bReqType = GetDataByte(0);
    bRequest = GetDataByte(1);
    
    _row = Find(MassStorageRequestTable, bRequest);
    ReqType = _row[0];
               
    AddDecSeparator();
    FieldColor = MassStorageColor;
    if (in.PrepareFldsForDlg == 1)
    {
        DoRequestStringTop();   
    }
    else
    {
        if ( SCSILevel == 0) # Xfer level
            AddCaptionCell("  Mass  ", "Storage", "This data payload represents a Mass Storage Command.");  
    }
        
    save_endian = LittleEndian;
    LittleEndian = 1;
        
    wValue   = GetDataWord(2); # Now that Endian is set...
    wIndex   = GetDataWord(4);
    wLength  = GetDataWord(6);
   
    if (Call ( _row[1] ) == null)
    {
        DoNormalRequestSecondPart(0xFFFFF);
        EndOfRequest();
        DoDefaultDecodeX();
    }
    LittleEndian = save_endian;

############ for Debug purposes
#    GetNBits(in.Data, 0, 0);
#    ShowDataBlock(in.DataLength);
############

    #GetNBits(in.Data, 7*8, 8);
    #ShowDataBlockReOrder(wLength);
        
	return ReqType;
}


set MassStorageRequestTable = 
[
    [0x00, "ADSC"                       , "ADSC Accept Device-Specific Command" ],
    [0xFF, "BulkOnlyReset"              , "Bulk-Only Mass Storage Reset" ],
    [0xFE, "GetMaxLUN"                  , "Get Maximum Logical Unit Number" ]
];




ADSC()
{
    #AddDecodedTextHeader();
    FieldColor = RequestFieldColor;
        
    if ((UsbProtocol == 0) || (UsbProtocol == 1))
    {
        if (in.PrepareFldsForDlg == 1)
        {
            DoNormalRequestSecondPart(12);
            str = "ADSC  "; # We cant get here otherwise!
            AddCaptionToDlg(" bRequest", str, "");   
        }
        else
        {
            AddDecSeparator();
            AddPayLoadCell("    ADSC    ",   Format("Intrfce# %d", wIndex),   
                   Format ("Accept Device-Specific Command for Interface 0x%02X", wIndex));
            if (in.Expanded)
            {
                if (bReqType != 0x21)
                {
                    AddPayLoadCell("bReqType", Format("Error: 0x%02X", bReqType), "Expected ADSC bReqType 0x21",  _ERROR);
                }
                else
                {
                    AddPayLoadCell("bReqType", Format("0x%02X", bReqType), "ADSC Request Type");
                }
                if (wValue != 0)
                {
                    AddPayLoadCell("wValue",   Format("Error: 0x%04X", wValue),   "Expected ADSC wValue: 0x00",  _ERROR);
                }
                if (UsbSubClass == 0x04) 
                {
                    # it's a UFI
                    if (wLength != 12)
                    {
                        AddPayLoadCell("wLength",  Format("Error in CTD: %d", wLength),  "For UFI, length expected is 12",  
                            _Error);
                    }
                    else
                    {
                        AddPayLoadCell("wLength",  Format("%d", wLength),  "Command Transport Data Size");
                     }
                }
                else
                {
                    AddPayLoadCell("wLength",  Format("CTD: %d", wLength),  Decode_wLength());
                }
            }
            else
            {
                if (bReqType != 0x21)
                {
                    AddPayLoadCell("bReqType", Format("Error: 0x%02X", bReqType), "Expected ADSC bReqType 0x21",  _ERROR);
                }
                if (wValue != 0)
                {
                    AddPayLoadCell("wValue",   Format("Error: 0x%04X", wValue),   "Expected ADSC wValue: 0x00",  _ERROR);
                }
                if (UsbSubClass == 0x04) 
                {
                    # it's a UFI
                    if (wLength != 12)
                    {
                        AddPayLoadCell("wLength",  Format("Error in CTD: %d", wLength),  "For UFI, length expected is 12",  
                            _ERROR);
                    }
                }
                else
                {
                    AddPayLoadCell("wLength",  Format("CTD: %d", wLength),  Decode_wLength());
                }
            }
        }
    }
    else
    {
        DoDefaultDecodeX();
    }
    return 1;
}

BulkOnlyReset()
{
    if (UsbProtocol == 0x50)
    {
        if (in.PrepareFldsForDlg == 1)
        {
            DoNormalRequestSecondPart(0);
            str = "RESET  "; # We cant get here otherwise!
            AddCaptionToDlg(" bRequest", str, "");
        }
        else
        {
            AddDecSeparator();
            if (bReqType != 0x21)
            {
                AddPayLoadCell("bReqType", Format("Error: 0x%02X", bReqType), "Expected bReqType 0x21",  _ERROR);
            }
            if (wValue != 0)
            {
                AddPayLoadCell("wValue",   Format("Error: 0x%04X", wValue),   "Expected wValue: 0x00",  _ERROR);
            }
            AddPayLoadCell("RESET",   Format("Interface#: %d", wIndex),   "Bulk-Only Reset for this interface");
            if (wLength != 0)
            {
                AddPayLoadCell("wLength",   Format("Error: 0x%04X", wLength),   "Expected wLength: 0x00",  _ERROR);
            }
        }
    }
    else
    {
        DoDefaultDecodeX();        
    }
    EndOfRequest();
    return 1;

}

GetMaxLUN()
{
    if (UsbProtocol == 0x50)
    {
        if (in.PrepareFldsForDlg == 1)
        {
            DoNormalRequestSecondPart(0);
            str = "GET_MAX_LUN  "; # We cant get here otherwise!   
            AddCaptionToDlg(" bRequest", str, "");
            
        }
        else
        {
            AddDecSeparator();
            if (bReqType != 0xA1)
            {
                AddPayLoadCell("bReqType", Format("Error: 0x%02X", bReqType), "Expected bReqType 0xA1",  _ERROR);
            }
            if (wValue != 0)
            {
                AddPayLoadCell("wValue",   Format("Error: 0x%04X", wValue),   "Expected wValue: 0x00",  _ERROR);
            }
            AddPayLoadCell("GetMaxLUN",   Format("Interface#: %d", wIndex),   "GetMax LUN on this interface", FieldColor, [_TABULARCELL, MS_GET_MAX_LUN]);
            
            if (wLength != 1)
            {
                AddPayLoadCell("wLength",   Format("Error: 0x%04X", wLength),   "Expected wLength: 0x01",  _ERROR);
            }          
        }
    }
    else
    {
        DoDefaultDecodeX();
        EndOfRequest();        
    }
    return 1;

}


DoDefaultDecodeX()
{
    ReqType = 0xFFFF;
    DoNormalRequestSecondPart(0xFFFFF);
 }

DoRequestStringTop()
{
    str = "";
    for (i=0; i<8; i++)
    {
        str += Format ("%02X ", GetDataByte(i));
    }
    AddCaptionToDlg("Mass Storage ", "Request  ", "");          
    AddCaptionToDlg("Setup Data", str+"  ", "");
    AddCaptionToDlg("------------------------------------", "", "");
    if (bReqType & 0x80)
    {
        str = "Host-to-device  ";
    }
    else
    {
        str = "Device-to-host  ";
    }
    AddCaptionToDlg("Direction", str, "");
    select 
    {
        ((bReqType & 0x60) == 0x00) : str = "Standard  ";
        ((bReqType & 0x60) == 0x20) : str = "Class  ";
        ((bReqType & 0x60) == 0x40) : str = "Vendor  ";
        ((bReqType & 0x60) == 0x60) : str = "RESERVED  ";
    };
    AddCaptionToDlg("     Type", str, "");
    select 
    {
        ((bReqType & 0x1F) == 0x00) : str = "Device  ";
        ((bReqType & 0x1F) == 0x01) : str = "Interface  ";
        ((bReqType & 0x1F) == 0x02) : str = "Endpoint  ";
        ((bReqType & 0x1F) == 0x03) : str = "Other  ";
        default                     : str = "RESERVED  ";
    };
    AddCaptionToDlg("Recipient", str, "");
    AddCaptionToDlg("------------------------------------", "", "");
}


DoNormalRequestSecondPart(length)
{
    AddCaptionToDlg("", "", "");
    
    if (wValue == 0)
    {
        str = "0x0000  ";
    }
    else
    {
        str = Format("0x%04X (Error!)  ", wValue);
    }
    AddCaptionToDlg("   wValue", str, "");
    AddCaptionToDlg("", "", "");
    
    str = Format("Interface=0x%04X  ", wIndex);
    if (wIndex > 255)
    {
        str += " (Error!)";
    }
    AddCaptionToDlg("   wIndex", str, "");
    AddCaptionToDlg("", "", "");
    
    str = Format("%d  ", wLength);
    if ((wLength < 0x10000) && (wLength != length))
    {
        str += " (Error!)";
    }
    AddCaptionToDlg("  wLength", str, "");
    EndOfRequest();
}
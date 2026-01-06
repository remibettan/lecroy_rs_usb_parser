#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  MS_CBI_InterruptEndp.inc
#
#  Mass Storage Control-Bulk-Interrupt Interrupt Endpoint Decoder
#


ProcessCBIEndpointData()
{
    
    AddDecSeparator();
	FieldColor = MassStorageColor;
    
    #SCSILevel = GetNBits(in.DecodeParams, 8, 8);
    Read_SCSILevel();
    GetNBits(in.Data, 0, 0); # reset pointers    

    if (SCSILevel == 0) # Xfer level    
        AddCaptionCell("  Mass  ", "Storage", "This data payload represents a Mass Storage Interrupt Status."); 
        
    FieldColor = CBI_IntBlkColor;
    AddDecSeparator();
    AddCaptionToDlg("Interrupt Data Block", "2 Bytes  ","");
    if (UsbSubClass == 0x01)
    {
        #???
    }
    else if (UsbSubClass == 0x04)
    {
        if (in.PrepareFldsForDlg)
        {
            AddCaptionToDlg("Command Completion / Block Status  ","","");
            bASC = GetDataByte(0);
            AddSimplePLCell("bASC", Format ("0x%02X", bASC), "Additional Sense Code");
            bASCQ = GetDataByte(1);
            AddSimplePLCell("bASCQ", Format ("0x%02X", bASCQ), "Additional Sense Code Qualifier");
        }
        else
        {
            bASC = GetDataByte(0);
            bASCQ = GetDataByte(1);
            if (bASC || bASCQ)
            {
                str = Format ("CBI-UFI Additional Sense Code values:  bASC=0x%02X  ", bASC);
                str += Format ("bASCQ=0x%02X", bASCQ);
                
                if (SCSILevel == 0) # Xfer Level
                    AddPayLoadCell("UFI Sense", Format ("0x%04X", (bASC<<8) | bASCQ), str, FieldColor, [_TABULARCELL, MS_UFI_SENSE]);
                else
                    AddPayLoadCell("UFI Sense", Format ("0x%04X", (bASC<<8) | bASCQ), str);
            }
            else
            {
                if (SCSILevel == 0) # Xfer Level
                    AddPayLoadCell("UFI Sense", "GOOD", "CBI-UFI Additional Sense Code values were 0.", FieldColor, [_TABULARCELL, MS_UFI_SENSE]);
                else                    
                    AddPayLoadCell("UFI Sense", "GOOD", "CBI-UFI Additional Sense Code values were 0.");
            }
            if (in.Expanded)
            {
                bASC = GetDataByte(0);
                AddSimplePLCell("bASC", Format ("0x%02X", bASC), "Additional Sense Code");
                bASCQ = GetDataByte(1);
                AddSimplePLCell("bASCQ", Format ("0x%02X", bASCQ), "Additional Sense Code Qualifier");
            }
        }  
    }
    else
    {
        AddCaptionToDlg("UFI Sense Codes  ","","");
        bType = GetDataByte(0);
        bValue = GetDataByte(1);
        if (bType == 0)
        {
            status_str = "Pass";
            is_error = 0;
            if (bValue & 1)
            {
                is_error = 1;
                if (bValue & 2)
                {
                    status_str = "Persistent Fail";
                }
                else
                {
                    status_str = "Fail";
                }
            }
            else
            {
                if (bValue & 2)
                {
                    status_str = "Phase Error";
                    is_error = 1;
                }
            }
            if (is_error == 1)
            {
                AddSimplePLCell("Cmd Complete", status_str, 
                    Format ("Vendor Nibble: 0x%01X", ((bValue >> 4) & 0xF)), _ERROR);
            }
            else
            {
                AddSimplePLCell("Cmd Complete", status_str, 
                    Format ("Vendor Nibble: 0x%01X", ((bValue >> 4) & 0xF)));
            }
        }
        else
        {
            AddSimplePLCell("bType", Format ("Error: 0x%02X", bType), "Expected only 0x00", _ERROR);        
            AddSimplePLCell("bValue", Format ("0x%02X", bType), "Undefined if bType not equal 0", _ERROR);        
        }
        
    }
    out.Decoded = 2;
    SCSILevel = 0;
   

############ for Debug purposes
#    GetNBits(in.Data, 0, 0);
#    ShowDataBlock(in.DataLength);
############
     #Trace ("This");
}


     
        
        
        
 
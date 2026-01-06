#
#  Copyright (c) 2003, Computer Access Technology Corp. - All Rights Reserved
#
#  MS_BulkOnlyOutEndp.inc
#
#  Mass Storage Class Bulk-Only Out Endpoint Decoder
#


ProcessBulkOnlyCBW()
{
    length = in.DataLength;
    if (length < 4)
    {
        return (0); 
    }
    
   
    signature = GetDataLong(0);
    if (signature == 0x43425355)
    {
        return CommandBlockWrapper(length);
    }
    else
    {
        return 0;
    }    
}




CommandBlockWrapper(length)
{
       
    AddDecSeparator();
    FieldColor = MassStorageColor;
    #SCSILevel = GetNBits(in.DecodeParams, 8, 8);
    Read_SCSILevel();
    GetNBits(in.Data, 0, 0); # reset pointers    

    if (SCSILevel == 0) # Xfer level
    {
        AddCaptionCell("  Mass  ", "Storage", "This data payload represents a Mass Storage Data Bulk."); 
    }
	 
    FieldColor = Bulk_CBWCellColor;

    #for testing
    #AddCaptionCell("AddCaptionCell", "AddCaptionCell!", "ToolTip");
    #AddPayLoadCell("AddPayLoadCell", "AddPayLoadCell!", "ToolTip");
    #AddPayLoadCellMono("AddPayLoadCellMono", "AddPayLoadCellMono!", "ToolTip");
    #AddPLCellMonoStr("AddPLCellMonoStr", "AddPLCellMonoStr!", "ToolTip");
    #AddPLCellMonoCap("AddPLCellMonoCap", "AddPLCellMonoCap!", "ToolTip");
    #AddPLCellMonoNoDlg("AddPLCellMonoNoDlg", "AddPLCellMonoNoDlg!", "ToolTip");
    #AddSimplePLCell("AddSimplePLCell", "AddSimplePLCell!", "ToolTip");
    #AddSimplePLCellMonoCap("AddSimplePLCellMonoCap", "AddSimplePLCellMonoCap!", "ToolTip");
    #AddCaptionToDlg("AddCaptionToDlg", "AddCaptionToDlg!", "AddCaptionToDlg");
    #AddStringToDlg("AddStringToDlg", "AddStringToDlg!", "AddStringToDlg");

    
    if (in.Expanded || in.PrepareFldsForDlg)
    {
        AddDecodedTextHeader();
        AddDecSeparator();
        AddStringToDlg("Command Block Wrapper", "", "");
        if (in.PrepareFldsForDlg)
        {
            tag = GetDataLong(0);
            AddSimplePLCell("Signature", Format ("0x%08X", tag), "Command Block Wrapper Signature: dCBWSignature", FieldColor, [_CELLINFO, 1]);

            tag = GetDataLong(4);
            AddSimplePLCell("Tag", Format ("0x%08X", tag), 
                "Command Block Tag: dCBWTag (in Hex)");
        }
        else
        {
            tag = GetDataLong(4);
            AddSimplePLCell("CBSU Tag", Format ("%08X", tag), 
                "Command Block Wrapper Signature: dCBWSignature\nCommand Block Tag: dCBWTag (in Hex)");
        }

        xfer_len = GetDataLong(8);
        AddSimplePLCell("XferLen", Format ("0x%X", xfer_len), 
            Format ("Data Transfer Length: dCBWDataTransferLength\n%d bytes", xfer_len), FieldColor, [_TABULARCELL, SCSI_CELL_LENGTH, "TEXT_CAPTION" ]);
        
        flags = GetDataByte(12);
        if (flags == 0x80)
        {
            AddSimplePLCell("Dir", "In", "bmCBWFlags: Data-In from Device to Host", FieldColor, [_CELLINFO, 0, [["In", 0x80], ["Out", 0]]]);
        }
        else if (flags == 0)
        {
            AddSimplePLCell("Dir", "Out", "bmCBWFlags: Data-Out from Host to Device", FieldColor, [_CELLINFO, 0, [["In", 0x80], ["Out", 0]]]);
        }
        else
        {
            AddSimplePLCell("Flags", Format ("Error: 0x%02X", flags), "Flags: Expect 0x80 or 0x00 only", _ERROR);
        }
        lun = GetDataByte(13);
        AddSimplePLCell("Lun", Format ("0x%01X", lun), "Logical Unit Number: bCBWLUN");
         
        cmd_len = GetDataByte(14);
        AddSimplePLCell("CB Len", Format ("0x%02X", cmd_len), 
            Format("Command Block Length = %d", cmd_len));
    }
    else if (SCSILevel == 0) # Xfer level
    {
        AddDecSeparator();
        xfer_len = GetDataLong(8);
        #AddSimplePLCell("XferLen", Format ("0x%X", xfer_len), 
            #Format ("Data Transfer Length: dCBWDataTransferLength\n%d bytes", xfer_len));
    
        flags = GetDataByte(12);
                
        if (flags == 0x80)
        {
            AddPayLoadCell("CBSU In Len", Format ("0x%08X", xfer_len), 
                   Format ("Command Block Wrapper, Data-In, Length=%d", xfer_len));
        }
        else if (flags == 0)
        {
            AddPayLoadCell("CBSU Out Len", Format ("0x%08X", xfer_len), 
                   Format ("Command Block Wrapper, Data-Out, Length=%d", xfer_len));
        }
        else
        {
            temp_str = Format("\nError: Flags val=0x%2X.  Expected 0x80 or 0x00 only", flags); 
            AddPayLoadCell("CBSU ?? Len", Format ("0x%08X", xfer_len), 
                   Format ("Command Block Wrapper, Length=%d", xfer_len) + temp_str);
        }
    }
    return cmd_len;        
}

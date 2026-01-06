#
#  Copyright (c) 2003, Computer Access Technology Corp. - All Rights Reserved
#
#  MS_BulkOnlyInEndp.inc
#
#  Mass Storage Class Bulk-Only In Endpoint Decoder
#

set Signature = 0xFFFFFFF;

ProcessBulkOnlyCSW(offset)
{
 
    length = in.DataLength;
    if (length < 4)
    {
        return (0); 
    }
    if (offset > 0)
    {
        GetDataByte(offset-1); # So we are pinting to the correct place
        SaveFieldSettings();
        DataByteHeaderOffset = offset;                                            
        CurrentFldInit();
    }              
         
    Signature = GetDataLong(0);
    #Trace ("Glob:", Global_BitField_offset, " BitCurrFldOff:", BitCurrentFieldOffset, " Sig:", signature, " offset:", offset, "\n");
    if (Signature == 0x53425355)
    {
        #SCSILevel = GetNBits(in.DecodeParams, 8, 8);
        Read_SCSILevel();
        GetNBits(in.Data, 0, 0); # reset pointers    
        if (offset == 0 && SCSILevel == 0) # Xfer level
        {
            AddDecSeparator();
			FieldColor = MassStorageColor;
            AddCaptionCell("  Mass  ", "Storage", "This data payload represents a Mass Storage Data Bulk."); 
             
            FieldColor = Bulk_CSWCellColor;
        }
        CommandStatusWrapper(length-offset);
        
    }
    else
    {
        length = 0;
    }
    if (offset > 0)
    {
        RestoreFieldSettings( );
        DataByteHeaderOffset = 0;
    }
    return length;    
}
 
 
CommandStatusWrapper(length)
{
    FieldColor = Bulk_CSWCellColor;
       
    AddDecSeparator();

    status = 0;
    if ( length > 12)
    {   
        status = GetDataByte(12);
    }
    
    
    # get view setting for CDB
    cdb_vs = Resolve( Prefix + "_CDB" );
    
    if (in.Expanded || (length < 13) || (status != 0))
    {
        if (HeaderPrinted == 0)
        {        
            AddDecodedTextHeader();
            HeaderPrinted = 1;
        }   
        AddStringToDlg("Command Status Wrapper", "", "");
        
        if (in.PrepareFldsForDlg)
        {
            GetDataLong(0);
            AddSimplePLCell("Signature", Format ("%08X", Signature), "Command Status Wrapper Signature: dCSWSignature");

            tag = GetDataLong(4);
            AddSimplePLCell("Tag", Format ("%08X", tag), 
                "Command Status Wrapper Tag: dCSWTag (in Hex)");
        }
        else
        {        
            if (length > 7)
            {
                tag = GetDataLong(4);
                AddSimplePLCell("SBSU Tag", Format ("%08X", tag), 
                    "Status Block Wrapper Signature: dCSWSignature\nCommand Block Tag: dCSWTag (in Hex)\n\nIf no status field is shown, the status was GOOD.");
            }
        }
            
        if (length > 11)
        {
            residue = GetDataLong(8);
            AddSimplePLCell("Residue", Format ("0x%X", residue), 
                Format ("Residue Length: dCSWDataResidue\n%d bytes", residue));
        } 
        
        if (length > 12)
        {
            status = GetDataByte(12); # get it again to reset the offsets
            if (SCSILevel == 0) # Xfer level
            {
                if (status == 0x0)
                {
                    AddSimplePLCell("Status", "Passed", "Command Passed, Status (bCSWStatus) Good.", FieldColor, [_TABULARCELL, MS_CELL_STATUS]);
                }
                else if (status == 1)
                {
                    AddSimplePLCell("Status", "Failed", "Command Failed, Status (bCSWStatus) = 1.", _ERROR, FieldColor, [_TABULARCELL, MS_CELL_STATUS]);
                }
                else if (status == 2)
                {
                    AddSimplePLCell("Status", "Phase Err", "Phase Error Status (bCSWStatus) = 2", _ERROR, FieldColor, [_TABULARCELL, MS_CELL_STATUS]);
                }
                else
                {
                    AddSimplePLCell("Status", Format ("Err: 0x02X", status), Format ("Unknown status value: 0x02X", status), _ERROR, FieldColor, [_TABULARCELL, MS_CELL_STATUS]);
                }
            }
            else
            {
                if (status == 0x0)
                {
                    AddSimplePLCell("Status", "Passed", "Command Passed, Status (bCSWStatus) Good.");
                }
                else if (status == 1)
                {
                    AddSimplePLCell("Status", "Failed", "Command Failed, Status (bCSWStatus) = 1.", _ERROR);
                }
                else if (status == 2)
                {
                    AddSimplePLCell("Status", "Phase Err", "Phase Error Status (bCSWStatus) = 2", _ERROR);
                }
                else
                {
                    AddSimplePLCell("Status", Format ("Err: 0x02X", status), Format ("Unknown status value: 0x02X", status), _ERROR);
                }
            }
        }
    }
    else
    {
       residue = GetDataLong(8);
       AddPayLoadCell("SBSU Passed", Format ("res=0x%X", residue), 
                   Format ("Command Status Wrapper, GOOD status, Residue Length=%d", residue));
         
    }
    
    if (length < 13)
    {
        AddSimplePLCell("CSW Error2", Format ("Too Short: 0x%08X", length), Format ("Expected 13 bytes"), _ERROR);
    }
    else if ((length-offset) > 13)
    {
        AddSimplePLCell("CSW Error1", Format ("Too Long: 0x%08X", length), Format ("Expected 13 bytes"),_ERROR);
    }
}

       
        
        
        
 
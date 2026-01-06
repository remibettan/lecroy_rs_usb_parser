#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_SenseData.inc
#
#  SCSI Sense Data decoder functions
################################################################################


#---------------------------- Common Globals --------------------------------

const SenseKeyTable = 
[       
        [0x0, "NO SENSE", 
        "Indicates that there is no specific sense key information\n" + 
        "to be reported."],
                       
        [0x1, "RECOVERED ERROR", 
        "Indicates that the last command completed successfully, with\n" + 
        "some recovery action performed by the device server."],
        
        [0x2, "NOT READY",
        "Indicates that the logical unit addressed cannot be accessed."],
                       
        [0x3, "MEDIUM ERROR",
        "Indicates that the command terminated with a non-recovered\n" + 
        "error condition that was probably caused by a flaw in the\n" + 
        "medium or an error in the recorded data."],
                        
        [0x4, "HARDWARE ERROR",
        "Indicates that the device server detected a non-recoverable\n" + 
        "hardware fail- ure (e.g., controller failure, device failure,\n" + 
        "or parity error) while performing the command or during\n" + 
        "a self test."],
                        
        [0x5, "ILLEGAL REQUEST",
        "Indicates that there was an illegal parameter in the\n" + 
        "CDB or in the additional parameters supplied as data\n" + 
        "for some commands."],        
        
        [0x6, "UNIT ATTENTION",
        "Indicates that the removable medium may have\n" + 
        "been changed or the target has been reset."],
        
        [0x7, "DATA PROTECT",
        "Indicates that a command that reads or writes the medium was\n" + 
        "attempted on a block that is protected from this operation."],
        
        [0x8, "BLANK CHECK",
        "Indicates that a write-once device or a sequential-access device\n" + 
        "encountered blank medium or format-defined end-of-data indication\n" + 
        "while reading or a write-once device encountered a non-blank\n" + 
        "medium while writing."],
        
        [0x9, "VENDOR SPECIFIC",
        "This sense key is available for reporting\n" + 
        "vendor specific conditions."],
        
        [0xA, "COPY ABORTED",
        "Indicates an EXTENDED COPY command was aborted due\n" + 
        "to an error condition on the source device, the destination\n" + 
        "device, or both."],
        
        [0xB, "ABORTED COMMAND",
        "Indicates that the device server aborted the command."],
        
        [0xC, "Obsolete", ""],
        
        [0xD, "VOLUME OVERFLOW",
        "Dh Indicates that a buffered SCSI device has reached\n" + 
        "the end-of-partition and data may remain in the buffer\n" + 
        "that has not been written to the medium."],
        
        [0xE, "MISCOMPARE",
        "Indicates that the source data did not match the data\n" + 
        "read from the medium."],
        
        [0xF, "Reserved", ""]
];


#MGD Added additionl sense code response decode as per appendix A
const SenseCodeTable = 
[ 
[0xFFFF , "(Not found)"],
[0x0000 , "No additional sense information"],
[0x0001 , "Filemark detected"],
[0x0002 , "End-of-partitions/medium detected"],
[0x0003 , "Setmark detected"],
[0x0004 , "Beginning of partition/medium detected"],
[0x0005 , "End-of-data detected"],
[0x0006 , "I/O process terminated"],
[0x0011 , "Audio play operation in progress"],
[0x0012 , "Audio play operation paused"],
[0x0013 , "Audio play operation successfully completed"],
[0x0014 , "Audio play operation stopped due to error"],
[0x0015 , "No current audio status to return"],
[0x001D , "ATA Pass Through information available"],
[0x0100 , "No index/sector signal"],
[0x0200 , "No seek complete"],
[0x0300 , "Peripheral device write fault"],
[0x0301 , "No write current"],
[0x0302 , "Excessive write errors"],
[0x0400 , "Logical unit not ready, cause not reportable"],
[0x0401 , "Logical unit in process of becoming ready"],
[0x0402 , "Logical unit not ready, initializing command required"],
[0x0403 , "Logical unit not ready, manual intervention required"],
[0x0404 , "Logical unit not ready, format in progress"],
[0x0500 , "Logical unit does not respond to selection"],
[0x0600 , "Reference position found"],
[0x0700 , "Multiple peripheral devices selected"],
[0x0800 , "Logical unit communication failure"],
[0x0801 , "Logical unit communication time-out"],
[0x0802 , "Logical unit communication parity error"],
[0x0900 , "Track following error"],
[0x0901 , "Tracking servo failure"],
[0x0902 , "Focus servo failure"],
[0x0903 , "Spindle servo failure"],
[0x0A00 , "Error log overflow"],
[0x0C00 , "Write error"],
[0x0C01 , "Write error recovered with auto reallocation"],
[0x0C02 , "Write error—auto reallocation failed"],
[0x1000 , "ID crc or ecc error"],
[0x1100 , "Unrecovered read error"],
[0x1101 , "Read retries exhausted"],
[0x1102 , "Error too long to correct"],
[0x1103 , "Multiple read errors"],
[0x1104 , "Unrecovered read error—auto reallocate failed"],
[0x1105 , "l-ec uncorrectable error"],
[0x1106 , "circ unrecovered error"],
[0x1107 , "Data resynchronization error"],
[0x1108 , "Incomplete block read"],
[0x1109 , "No gap found"],
[0x110A , "Miscorrected error"],
[0x110B , "Unrecovered read error—recommend reassignment"],
[0x110C , "Unrecovered read error—recommend rewrite the data"],
[0x1200 , "Address mark not found for ID field"],
[0x1300 , "Address mark not found for data field"],
[0x1400 , "Recorded entity not found"],
[0x1401 , "Record not found"],
[0x1402 , "Filemark or setmark not found"],
[0x1403 , "End-of-data not found"],
[0x1404 , "Block sequence error"],
[0x1500 , "Random positioning error"],
[0x1501 , "Mechanical positioning error"],
[0x1502 , "Positioning error detected by read of medium"],
[0x1600 , "Data synchronization mark error"],
[0x1700 , "Recovered data with no error correction applied"],
[0x1701 , "Recovered data with retries"],
[0x1702 , "Recovered data with positive head offset"],
[0x1703 , "Recovered data with negative head offset"],
[0x1704 , "Recovered data with retries and/or circ applied"],
[0x1705 , "Recovered data using previous sector ID"],
[0x1706 , "Recovered data without ecc—data auto-reallocated"],
[0x1707 , "Recovered data without ecc—recommend reassignment"],
[0x1708 , "Recovered data without ecc—recommend rewrite"],
[0x1800 , "Recovered data with error correction applied"],
[0x1801 , "Recovered data with error correction and retries applied"],
[0x1802 , "Recovered data—data auto-reallocated"],
[0x1803 , "Recovered data with circ"],
[0x1804 , "Recovered data with lec"],
[0x1805 , "Recovered data—recommend reassignment"],
[0x1806 , "Recovered data—recommend rewrite"],
[0x1900 , "Defect list error"],
[0x1901 , "Defect list not available"],
[0x1902 , "Defect list error in primary list"],
[0x1903 , "Defect list error in grown list"],
[0x1A00 , "Parameter list length error"],
[0x1B00 , "Synchronous data transfer error"],
[0x1C00 , "Defect list not found"],
[0x1C01 , "Primary defect list not found"],
[0x1C02 , "Grown defect list not found"],
[0x1D00 , "Miscompare during verify operation"],
[0x1E00 , "Recovered ID with ecc"],
[0x2000 , "Invalid command operation code"],
[0x2100 , "Logical block address out of range"],
[0x2101 , "Invalid element address"],
[0x2200 , "Illegal function"],
[0x2400 , "Invalid field in cdb"],
[0x2500 , "Logical unit not supported"],
[0x2600 , "Invalid field in parameter list"],
[0x2601 , "Parameter not supported"],
[0x2602 , "Parameter value invalid"],
[0x2603 , "Threshold parameters not supported"],
[0x2700 , "Write protected"],
[0x2800 , "Not ready to ready transition (medium may have changed)"],
[0x2801 , "Import or export element assessed"],
[0x2900 , "Power on, reset, or bus device reset occurred"],
[0x2A00 , "Parameters changed"],
[0x2A01 , "Mode parameters changed"],
[0x2A02 , "Log parameters changed"],
[0x2B00 , "Copy cannot execute since host cannot disconnect"],
[0x2C00 , "Command sequence error"],
[0x2C01 , "Too many windows specified"],
[0x2F00 , "Commands cleared by another initiator"],
[0x3000 , "Incompatible medium installed"],
[0x3001 , "Cannot read medium—unknown format"],
[0x3002 , "Cannot read medium—incompatible format"],
[0x3003 , "Cleaning cartridge installed"],
[0x3100 , "Medium format corrupted"],
[0x3200 , "No defect spare location available"],
[0x3201 , "Defect list update failure"],
[0x3300 , "Tape length error"],
[0x3600 , "Ribbon, ink, or tower failure"],
[0x3700 , "Rounded parameter"],
[0x3900 , "Saving parameters not supported"],
[0x3A00 , "Medium not present"],
[0x3B00 , "Sequential positioning error"],
[0x3B01 , "Tape position error at beginning-of-medium"],
[0x3B02 , "Tape position error at end-of-medium"],
[0x3B03 , "Tape or electronic vertical forms unit not ready"],
[0x3B04 , "Slew failure"],
[0x3B05 , "Paper jam"],
[0x3B06 , "Failed to sense top-of-form"],
[0x3B07 , "Failed to sense bottom-of-form"],
[0x3B08 , "Reposition error"],
[0x3B09 , "Read past end of medium"],
[0x3B0A , "Read past beginning of medium"],
[0x3B0B , "Position past end of medium"],
[0x3B0C , "Position past beginning of medium"],
[0x3B0D , "Medium destination element full"],
[0x3B0E , "Medium source element empty"],
[0x3D00 , "Invalid bits in identify message"],
[0x3E00 , "Logical unit has not self-configured yet"],
[0x3F00 , "Target operation conditions have changed"],
[0x3F01 , "Microcode has been changed"],
[0x3F02 , "Changed operating definition"],
[0x3F03 , "Inquiry data has changed"],
[0x4000 , "RAM failure nn Diagnostic failure on component nn"],
[0x4100 , "Data path failure"],
[0x4200 , "Power-on or self-test failure"],
[0x4300 , "Message error"],
[0x4400 , "Internal target failure"],
[0x4500 , "Select or reselect failure"],
[0x4600 , "Unsuccessful soft reset"],
[0x4700 , "SCSI parity error"],
[0x4800 , "Initiator detected error message received"],
[0x4900 , "Invalid message error"],
[0x4A00 , "Command phase error"],
[0x4B00 , "Data phase error"],
[0x4C00 , "Logical unit failed self-configuration"],
[0x4E00 , "Overlapped commands attempted"],
[0x5000 , "Write append error"],
[0x5001 , "Write append position error"],
[0x5002 , "Position error related to timing"],
[0x5100 , "Erase failure"],
[0x5200 , "Cartridge fault"],
[0x5300 , "Media load or eject failed"],
[0x5301 , "Unload tape failure"],
[0x5302 , "Medium removal prevented"],
[0x5400 , "SCSI to host system interface failure"],
[0x5500 , "System resource failure"],
[0x5600 , "Reserved"],
[0x5700 , "Unable to recover table of contents"],
[0x5800 , "Generation does not exist"],
[0x5900 , "Updated block read"],
[0x5A00 , "Operator request or state change input (unspecified)"],
[0x5A01 , "Operator medium removal request"],
[0x5A02 , "Operator selected write protect"],
[0x5A02 , "Operator selected write permit"],
[0x5B00 , "Log exception"],
[0x5B01 , "Threshold condition met"],
[0x5B02 , "Log counter at maximum"],
[0x5B03 , "Log list codes exhausted"],
[0x5C00 , "RPL status change"],
[0x5C01 , "Spindles synchronized"],
[0x5C02 , "Spindles not synchronized"],
[0x5D00 , "Reserved"],
[0x5E00 , "Reserved"],
[0x5F00 , "Reserved"],
[0x6000 , "Lamp failure"],
[0x6100 , "Video acquisition error"],
[0x6101 , "Unable to acquire video"],
[0x6102 , "Out of focus"],
[0x6200 , "Scan head positioning error"],
[0x6300 , "End of user area encountered on this track"],
[0x6400 , "Illegal mode for this track"],
[0x6500 , "Reserved"],
[0x6600 , "Reserved"],
[0x6700 , "Reserved"],
[0x6800 , "Reserved"],
[0x6900 , "Reserved"],
[0x6A00 , "Reserved"],
[0x6B00 , "Reserved"],
[0x6C00 , "Reserved"],
[0x6D00 , "Reserved"],
[0x6E00 , "Reserved"],
[0x6F00 , "Reserved"]
];
#MGD Mod end

#----------------------------------------------------------------------------



ShowSenseData( len )
{
    SetCellColor ( SCSI_Color );    
    AddDecSeparator();    
    
    
    VS = Resolve( Prefix + "_SenseData" );    
    
    
    #------------------------------------------------------------------
    # Show special cells in collapsed state
    #
    if( IsExpanded() || VS[COLLAPSED] ) 
    {
        AddPLCellMonoStr("SCSI SENSE DATA", "",
        "Sense data shall be made available by the logical unit\n" + 
        "in the event a command completes with a CHECK CONDITION\n" + 
        "status or other conditions.", _MONOFIELD); 
        
        VS = Resolve( Prefix + "_SenseData" ); # restore VS after changing it in AddPLCellMonoStr
    }
        
    #------------------------------------------------------------------
        
    
    AddBlockPLCell("VALID", GetBitStr(), 
    "A VALID bit not set indicates that the INFORMATION field\n" + 
    "is not as defined in SPC-2 standard. \n" + 
    "\n" + 
    "A VALID bit set indicates the INFORMATION field contains\n" + 
    "valid information as defined in SPC-2 standard.");
    
    
    #------------------------------ RESPONSE CODE -----------------------------
    val = NextNBits_(7);
    
    is_std_format = 1;
    error = null;
    
    select{
        val == 0x70 : { str = "Current"; tooltip = 
        "Response code 70h (current errors) indicates that the CHECK\n" + 
        "CONDITION status returned is the result of an error or\n" + 
        "exception condition on the task that returned the CHECK\n" + 
        "CONDITION status or a protocol specific failure condition.";  }
        
        val == 0x71 : { str = "Deferred"; tooltip = 
        "Response code 71h (deferred errors) indicates that the CHECK\n" + 
        "CONDITION status returned is the result of an error or\n" + 
        "exception condition that occurred during processing of\n" + 
        "a previous command for which GOOD status has already been\n" + 
        "returned." ;}
        
        val == 0x7F : { str = "Vendor"; tooltip = 
        "Response code 71h.\nVendor specific sense data formats."; is_std_format = 0; }
        
        default     : { str = "Reserved"; tooltip = Format("Response code %02Xh.\n", val) +
                        "Unknown sense data format."; is_std_format = 0; error = _ERROR; }
    };
    
    AddBlockPLCell("RESPONSE CODE", str, tooltip, error );
    #--------------------------------------------------------------------------
    
    
    
    #--------------------------------------------------------------------------
    # Show special cells in collapsed state
    #
    if( !IsExpanded() && !VS[COLLAPSED] )
    {            
            val = SCSI_SenseData_Color;
            if( error ) val = ERROR_COLOR;
            
            AddCell("SCSI RESP CODE", str, "SCSI Sense Data RESPONSE CODE field.",
                 SCSI_Color, [_LOWERCOLOR, SCSI_SenseData_Color]  );         

    }   
    #--------------------------------------------------------------------------
    
    
         
    
    # Show datablock for not standard formats
    if( !is_std_format )
    {   
		if( !AddSpecDataBlockVS( len - 1, VS ))  # Check if some project-specific ShowSpecDataBlockVS hook handled call        
			ShowDataBlockVS( len - 1, VS );   
        return 0;
    }                
    
    
    AddBlockPLCell("Obsolete", Format("0x%02X", NextNBits_(8)), 
    "The obsolete byte contained information\nused by the COPY command.");
    
    
    AddBlockPLCell("FILEMARK", GetBitStr(),     
    "A FILEMARK bit set indicates that the current command has\n" + 
    "read a filemark or setmark.");
    
    
    AddBlockPLCell("EOM", GetBitStr(),     
    "An EOM bit set indicates that an end-of-medium\n" + 
    "condition (e.g., end-of-partition, beginning-of-partition,\n" + 
    "or out-of-paper) exists.");
    
    
    AddBlockPLCell("ILI", GetBitStr(), 
    "An incorrect length indicator (ILI) bit of one usually indicates\n" + 
    "that the requested logical block length did not match the\n" + 
    "logical block length of the data on the medium.");
    
    PLReservedCheck(1);
    
    
    
    #-------------------------------- SENSE KEY -------------------------------
    sense_key = NextNBits_(4);   
    
    tooltip = Format("Sense Key.\nValue   : %01Xh.\nMeaning : ", sense_key);
    
    entry = Find(SenseKeyTable, sense_key);
    str   = entry[1];
    
    tooltip += Format("%s.\n", str);
    tooltip += entry[2];
    
    error = null;
    if( sense_key == 0xF ) error = _ERROR;
    
    AddBlockPLCell("SENSE KEY", str, tooltip, error );
    
    if( !IsExpanded() && !VS[COLLAPSED] )
    {    
       # AddCell("SCSI SENSE KEY", null, "SCSI Sense Data SENSE KEY field.", 
       #      SCSI_Color, _MONOFIELD ); 
          
        val = SCSI_SenseData_Color;
        if( error ) val = ERROR_COLOR;
         
        AddCell("SCSI SENSE KEY", str, "SCSI Sense Data SENSE KEY field.", 
             SCSI_Color, [_LOWERCOLOR, SCSI_SenseData_Color] );   
        
        #AddCell( str , null, tooltip,
        #    val , _MONOFIELD); 
    }
    #--------------------------------------------------------------------------
    
    
    
    AddBlockPLCell("INFORMATION", Format("0x%08X", NextNBits_(32)), "INFORMATION field");
    AddBlockPLCell("AddSenseLen", Format("%d", NextNBits_(8)), "ADDITIONAL SENSE LENGTH field.");
    AddBlockPLCell("CmdSpecINFO", Format("0x%08X", NextNBits_(32)), "COMMAND-SPECIFIC INFORMATION field");
    
    #MGD Added additionl sense code response decode as per appendix A

    addlsenseCode=NextNBits_(8);
    addlsenseQual=NextNBits_(8);
    snsCkey="0x" + Format("%01X", addlsenseCode)  + Format("%02X", addlsenseQual);

    #AddBlockPLCell("AddSenseCQ", "(" + snsCkey + ")", "ADDITIONAL SENSE CODE field.");

    scentry = Find(SenseCodeTable, snsCkey);    
 
    sctooltip = Format("%02X", addlsenseCode) + "/" + Format("%02X", addlsenseQual) + " = " + scentry[1];

    
    AddBlockPLCell("AddSenseCode", Format("0x%01X", addlsenseCode), "ADDITIONAL SENSE CODE field.\n" + sctooltip);
    AddBlockPLCell("AddSnsCodeQlfr", Format("0x%01X", addlsenseQual), "ADDITIONAL SENSE CODE QUALIFIER field.\n" + sctooltip);

    #MGD mod end    

    AddBlockPLCell("FldReplUnitCode", Format("0x%01X", NextNBits_(8)), "FIELD REPLACEABLE UNIT CODE field.\n" +
    "Non-zero values in this field are used to define a\n" + 
    "device-specific mechanism or unit that has failed.");    
 
    sksv_bit = NextNBits_(1);
    AddBlockPLCell("SKSV", GetBitStr(sksv_bit), 
    "A sense-key specific valid (SKSV) bit of one indicates\n" + 
    "the SENSE-KEY SPECIFIC field contains valid information\n" + 
    "as defined in SPC-2 standard.");
    
    
    #-------------------------------- SENSE-KEY SPECIFIC --------------------------------    
    select{
        
        # ILLEGAL REQUEST 
        (sksv_bit == 1) && (sense_key == 0x5) :  
        {
            AddBlockPLCell("C/D", GetBitStr(),
            "A command data (C/D) bit of one indicates that the illegal parameter\n" + 
            "is in the CDB. A C/D bit of zero indicates that the illegal parameter\n" + 
            "is in the data parameters sent by the application client in the Data-Out\n" + 
            "Buffer." );
            
            PLReservedCheck(2);
            
            bit = NextNBits_(1);
            AddBlockPLCell("BPV", GetBitStr(bit),
            "A bit pointer valid (BPV) bit of zero indicates that the value in\n" + 
            "the BIT POINTER field is not valid." );            
            
            str = Format("%d", NextNBits_(3));
            if( !bit ) str = "Not Valid";
            
            AddBlockPLCell("BIT POINTER", str,
            "BIT POINTER field specifies which bit of the byte\n" +
            "designated by the FIELD POINTER field is in error." );
            
            AddBlockPLCell("FIELD POINTER", Format("%d", NextNBits_(16)),
            "The FIELD POINTER field indicates which byte of\n" + 
            "the CDB or of the parameter data was in error.");        
        }
        
        
        # RECOVERED ERROR, HARDWARE ERROR or MEDIUM ERROR
        (sksv_bit == 1) && ((sense_key == 0x1) || (sense_key == 0x4) || (sense_key == 0x3)) :  
        {
            PLReservedCheck(7);
            AddBlockPLCell("ACTUAL RETRY COUNT", Format("%d", NextNBits_(16)),
            "The ACTUAL RETRY COUNT field returns vendor specific\n" + 
            "information on the actual number of retries of\n" + 
            "the recovery algorithm used in attempting to recover\n" + 
            "an error or exception condition."); 
        }
        
        
        # NOT READY or NO SENSE
        (sksv_bit == 1) && ( (sense_key == 0x2) || (sense_key == 0x0) ) : 
        {
            PLReservedCheck(7);
            AddBlockPLCell("PROGRESS INDICATION", Format("%d", NextNBits_(16)),
            "The PROGRESS INDICATION field is a percent complete\n" + 
            "indication in which the returned value is the numerator\n" + 
            "that has 65 536 (10000h) as its denominator. The\n" + 
            "progress indication shall be based upon the total\n" + 
            "operation."); 
        }
        
        
        # COPY ABORTED 
        (sksv_bit == 1) && (sense_key == 0xA) :  
        {
            PLReservedCheck(1);
        
            AddBlockPLCell("SD", GetBitStr(),
            "The segment descriptor (SD) bit indicates whether\n" + 
            "the field pointer is with reference to the start\n" + 
            "of the parameter list or to the start of a segment\n" + 
            "descriptor." );            
            
            PLReservedCheck(1);            
            
            
            bit = NextNBits_(1);
            AddBlockPLCell("BPV", GetBitStr(bit),
            "A bit pointer valid (BPV) bit of zero indicates that the value in\n" + 
            "the BIT POINTER field is not valid." );            
            
            str = Format("%d", NextNBits_(3));
            if( !bit ) str = "Not Valid";
            
            AddBlockPLCell("BIT POINTER", str,
            "BIT POINTER field specifies which bit of the byte\n" +
            "designated by the FIELD POINTER field is in error." );
            
            AddBlockPLCell("FIELD POINTER", Format("%d", NextNBits_(16)),
            "The FIELD POINTER field indicates which byte of\n" + 
            "the CDB or of the parameter data was in error.");        
        }
        
        default : 
        { 
            str = Format("0x%04X", NextNBits_(23));
            if( !sksv_bit ) str = "Not Valid";
            AddBlockPLCell("SenseKey Spec", str, "SENSE-KEY SPECIFIC field.");
        }
    };    
    #------------------------------------------------------------------------------------
    
    #---------------------------- Additional sense bytes --------------------------------
    if( (len - 18) > 0 )
    {
        AddBlockPLCellMonoCap("Additional" , "sense bytes", "Additional sense bytes field.",
        NOT_USE_COLON_AS_DVDR);
        
		if( !AddSpecDataBlockVS( len - 17, VS ))  # Check if some project-specific ShowSpecDataBlockVS hook handled call        
			ShowDataBlockVS( len - 17, VS ); 
    }
    #------------------------------------------------------------------------------------
    
    
    AddDecSeparator();
    RestoreCellColor();
}



#####################################################################################
#                                Working functions                                  #
#####################################################################################

# -----------------------------------------------------------------------------------

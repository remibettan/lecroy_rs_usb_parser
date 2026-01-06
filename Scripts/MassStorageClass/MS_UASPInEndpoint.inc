#
#  Copyright (c) 2010, LeCroy - All Rights Reserved
#
#  MS_UASPInEndpoint.inc
#
#  Prefix =  "SOB" 
#

%include "CATCScriptAPI.inc"

# SCSI definitions
%include "..\Shared\SCSI\SCSI_Defs.inc"

%include "UsbCommon.inc"
%include "MS_Common.inc"

#----  Input
# in.Data       - Data_block to decode
# in.DataLength - Length of Data_block 
#
#----  Output
# out.Decoded   - amount of data has been decoded
#


set UsbDecodeType = "Endpoint";
set UsbClassCode  = 0x8; # Mass Storage Class
set UsbSubClass   = 0x06;
set UsbProtocol   = 0x62; # UASP
set UsbEndpType   = "Bulk";
set UsbEndpDir    = "In";

set UsbMaxXferSize       = 0x7FFFFFFF;  #try largest possible positive value  
set UsbMaxXferDecodeSize = 36;  # Max bytes that we will be decoding  
set UsbMaxPktSize        = 512;
set UsbScriptDecodeType  = 2; # Combined decoding for Cells and Text decoding  
set UsbDecHdrType = 2; # This type references decoder byte containing the SCSI Opcode  
set UsbDecHdrLen  = 1; # This 1 byte is passed in to this via the in context
set UsbXferCompleteClue = 8; # An Xfer of this type will complete an OUT in progress  




#############################################################################
#                               View Settings                               #
#############################################################################
#
#    In this section user can set up which fields are to be shown and 
#    which are to be hidden in expanded and collapsed states.
#    Zero-value everywhere means that fields will not be shown,
#    otherwise means opposite.
#

# -----------------------  Separate Field View Settings ---------------------
# The FIRST value in list-variables defines if the field is to be shown or
# hidden in COLLAPSED state. 
# 0 - means the field is to be shown.
# 1 - means the field is to be hidden.
# 
# The SECOND value in list-variables defines if the field is to be shown or
# hidden in EXPANDED state. 
# 0 - means the field is to be shown.
# 1 - means the field is to be hidden.
#
# i.e.  const RPD_Field = [0, 1]; - means that field 'Field' will be hidden
# in collapsed state and will be shown in expanded state. 
#

#           [collapsed, expanded]   
 const SOB_CDB    = [0, 1];
#-----------------------------------------------------------------------------


set HeaderPrinted = 0;
set PrevOpcode = 0;

#
# Parsing entry point
#


ProcessUASInData(process_as_data)
{
    InitType2Decoder();
    Prefix =  "SOB";
        
    HeaderPrinted = 0;
    
    #SCSILevel = GetNBits(in.DecodeParams, 8, 8);
    Read_SCSILevel();    

    IUIdentifier = GetNBits(in.Data, 0, 8);
    IncFieldOffset(8);

    FieldColor = MassStorageColor;
    
    if (SCSILevel == 0) # Xfer level
    {
    	AddCaptionCell("UASP", null, "", FieldColor, _MONOFIELD);
	    AddDecSeparator();
    }

	if( process_as_data == 0 )
    {
		select
		{
			(IUIdentifier == 0x07)    : block_size = WriteReadyIU();
			(IUIdentifier == 0x06)    : block_size = ReadReadyIU();
			(IUIdentifier == 0x04)    : block_size = ResponseIU();
			(IUIdentifier == 0x03)    : block_size = SenseIU();
			default                   : block_size = 0;
		};
		
		if (block_size != 0)
		{
			out.Decoded = in.DataLength;
			return Complete();
		}
	}
    else if( process_as_data == 1 )
    {
    
		# check if this is a response to a control command,
		# as opposed to a block of READ data
	    
		PrevOpcode = GetNBits(in.DecodeParams, 0, 8);
		# Trace ("PrevOpcode:", PrevOpcode, "\n");
	    
		GetNBits(in.Data, 0, 0); # reset pointers    
		SetFieldOffsetLen(0, 8);
	    
		if (HeaderPrinted == 0)
		{
			AddDecodedTextHeader();
			HeaderPrinted = 1;
		}
	 
		if (SCSILevel == 0) # Xfer level
		{
			AddCell(" Data IN", null, "This data payload represents a UASP Data Bulk.", FieldColor, _MONOFIELD, [_TABULARCELL, MS_UASP_IDENTIFIER]);
		}
		  
		FieldColor = Bulk_CSWCellColor;
	    
		save_endian = LittleEndian;
		LittleEndian = 0;

		select
		{
			((PrevOpcode == 0x08) || 
			 (PrevOpcode == 0x28) || 
			 (PrevOpcode == 0x3E))  : DoRead();         # READ (6, 10, LONG)       
			(PrevOpcode == 0x12)    : DoInquiry();      # INQUIRY   
			(PrevOpcode == 0x25)    : DoReadCapacity(); # READ_CAPACITY
			((PrevOpcode == 0x1A) || 
			 (PrevOpcode == 0x5A))  : DoModeSense();    # MODE_SENSE (6, 10)       
			(PrevOpcode == 0x03)    : DoRequestSense(); # REQUEST_SENSE       
		};
	        
		LittleEndian = save_endian;       
		#Anything else will be shown as raw data.
	}
	
    SCSILevel = 0;
    return Complete();
}
 
ReadReadyIU()
{
    FieldColor = MassStorageColor;
    AddCell(" Read Ready IU ", null, "Read Ready IU", FieldColor, _MONOFIELD, [_TABULARCELL, MS_UASP_IDENTIFIER]); 
    
    val = NextNBits_(8); #8bit as Reserved
    
    if (in.Expanded || in.PrepareFldsForDlg)
    {
        AddDecodedTextHeader();
        AddStringToDlg("Read Ready Information Unit", "", "");
        
        AddTag( 16 );
    }
    else
    {
        AddTag( 16 );
    }
    
    out.Decoded = GetBitOffset() / 8;    
}

WriteReadyIU()
{
    FieldColor = MassStorageColor;
    AddCell(" Write Ready IU ", null, "Write Ready IU", FieldColor, _MONOFIELD, [_TABULARCELL, MS_UASP_IDENTIFIER]); 
     
    val = NextNBits_(8); #8bit as Reserved
    
    if (in.Expanded || in.PrepareFldsForDlg)
    {
        AddDecodedTextHeader();
        AddStringToDlg("Write Ready Information Unit", "", "");
        
        AddTag( 16 );
    }
    else
    {
        AddTag( 16 );
    }
    
    out.Decoded = GetBitOffset() / 8;    
}

ResponseIU()
{
    FieldColor = MassStorageColor;
    
    if (SCSILevel == 1) # SCSI level
    {
        response = GetDataByte(7);
        ShowRESPONSE_CODE( response );
        
        AddDecSeparator();
    }
    else
    {
        AddCell("Response IU ", null, "Response IU", FieldColor, _MONOFIELD, [_TABULARCELL, MS_UASP_IDENTIFIER]); 
        val = NextNBits_(8); #8bit as Reserved
        
        if (in.Expanded || in.PrepareFldsForDlg)
        {
            AddDecodedTextHeader();
            AddStringToDlg("Response Information Unit", "", "");
            
            AddTag( 16 );
            
            AddRspInfo = NextNBits_(24);
            AddSimplePLCell("Additional Rsp Info", Format ("%06X", AddRspInfo), "ADDITIONAL RESPONSE INFORMATION");
            
            response = NextNBits_(8);
            ShowRESPONSE_CODE( response );
            
            AddDecSeparator();
        }
        else
        {     
            AddTag( 16 );
            AddDecSeparator();
            
            response = GetDataByte(7);
            ShowRESPONSE_CODE( response );
            
            AddDecSeparator();
        }
     }
    
    out.Decoded = GetBitOffset() / 8;    
}

SenseIU()
{    
    FieldColor = MassStorageColor;
    
    if (in.DataLength < 16)
    {
		AddDecSeparator();
        AddCaptionCell(" Sense IU ", "Short Status", "Packet is too short to contain a Sense IU", _ERROR);       
    }
    else
    {
		if (SCSILevel == 0)
			AddCell("Sense IU ", null, "Sense IU", FieldColor, _MONOFIELD, [_TABULARCELL, MS_UASP_IDENTIFIER]); 
    }
    
	if (SCSILevel == 1) # SCSI level
	{
		if (in.DataLength >= 8 )
		{
			status = GetDataByte(6);
			ShowStatus(status);
	        
			AddDecSeparator();
		}
	}
	else
	{
		val = NextNBits_(8); #8bit as Reserved
     
		if (in.Expanded || in.PrepareFldsForDlg)
		{
			AddDecodedTextHeader();
			AddStringToDlg("Sense Information Unit", "", "");
            
            if (in.DataLength >= 8 )
			{
				AddTag( 16 );
	            
				ShowStatusQualifier();
	            
				ShowStatus(NextNBits_(8));
				
				if (in.DataLength >= 16 )
				{
			
					PLReservedCheck( 32 );
					PLReservedCheck( 24 );
		            
					length = NextNBits_(16);
					AddSimplePLCell("Length", Format ("0x%04X", length), "Length");
		            
					if (length != 0)
					{
						ShowSenseData(length);
					}
				}
			}
		}
		else
		{     
			AddTag( 16 );
            
			status = GetDataByte(6);
			ShowStatus(status);	

			AddDecSeparator();
		}
	 }
    
    out.Decoded = GetBitOffset() / 8;    
}

ShowStatus(status)
{
    error = null;

    status_desc = Find ( SCSI_Status_Table, status );
    if ( status_desc  )
    {
        str = status_desc[1];
    }
    else
    {
        str = "Reserved";
        error = _ERROR;
    }
    
    
    tooltip = "SCSI STATUS field.\n" + Format("Value   : 0x%02X.\n", status) 
    + Format("Meaning : %s.\n\n", str) +     
    "Status shall be sent from the logical unit to the\n" + 
    "application client whenever a command ends with a \n" +
    "service response of TASK COMPLETE or LINKED COMMAND\n" +
    "COMPLETE.";
    
    AddPayLoadCell("STATUS", str, tooltip, error, FieldColor, [_TABULARCELL, MS_UASP_STATUS]);
}
DoRead()
{
    if (in.DataLength < 13)
    {
        AddDecSeparator();
        AddCaptionCell("  READ  ", "Short Response", "Response is too short to contain a Command Status Wrapper Block", _ERROR);       
        out.Decoded = 0;
        ShowDataBlockReOrder(in.DataLength);    
    }
    else
    {
        #ShowDataBlockReOrder(in.DataLength - 13);
        #out.Decoded = in.DataLength;
         out.Decoded = 0;
    }
}



DoInquiry()
{
    DoInquiryResponse();
   
    out.Decoded = 36;
    if (in.DataLength > 36) #djdj remove when out.Decoded examined
    {
        if (in.DataLength < MaxShowDataBlockSize)
        {         
            ShowDataBlockReOrder(in.DataLength - 36);
        }
    }
    else
    {
        out.Decoded = in.DataLength;
    }
}


DoModeSense()
{
    AddDecSeparator();

    if (PrevOpcode == 0x1A)
    {
        FieldColor = CDB_ModeSense6_Color;
	    DoModeSense6Response();
    }
    else
    {
        FieldColor = CDB_ModeSense10_Color;
        DoModeSense10Response();
    }
    out.Decoded = in.DataLength;
}


DoRequestSense()
{
    AddDecSeparator();
    FieldColor = CDB_RequestSense_Color;
    if (in.DataLength == 0)
    {
        AddCaptionCell("  REQUEST_SENSE  ", "No Response", "Device server returned nothing in response to MODE_SENSE Command", _MONOCOLOR);
    }
    else
    {
        AddCaptionCell("  REQUEST_SENSE  ", "Response", "Response to MODE_SENSE Command", _MONOCOLOR);
        ShowSenseData(in.DataLength);
    }
    out.Decoded = in.DataLength;
}



DoReadCapacity()
{
    AddDecSeparator();
    FieldColor = CDB_ReadCapcty_Color;
    AddCaptionCell("  READ_CAPACITY  ", "Response", "Response to READ_CAPACITY Command", _MONOCOLOR);
    
    lba = GetDataLong(0);
    if (lba & 0x80000000)
    {
        #AddSimplePLCell("LBA", Format ("0x%08X", lba), "Logical Block Address");
        AddPayLoadCell("LBA", Format ("0x%08X", lba), "Logical Block Address");
    }
    else
    {
        #AddSimplePLCell("LBA", Format ("0x%08X", lba), Format ("Logical Block Address: %d", lba));
        AddPayLoadCell("LBA", Format ("0x%08X", lba), Format ("Logical Block Address: %d", lba));
    }
    
    block_len = GetDataLong(4);
    if (block_len & 0x80000000)
    {
        #AddSimplePLCell("Block Len", Format ("0x%08X", block_len), "Block Length");
        AddPayLoadCell("Block Len", Format ("0x%08X", block_len), "Block Length");
    }
    else
    {
        #AddSimplePLCell("Block Len", Format ("0x%08X", block_len), Format ("Block Length: %d", block_len));
        AddPayLoadCell("Block Len", Format ("0x%08X", block_len), Format ("Block Length: %d", block_len));
    }
    out.Decoded = in.DataLength;         
}    

# -----------------------------------------------------------------------------------

ShowRESPONSE_CODE( val )
{
      #val = NextNBits_(8);
      
      tooltip  =         "RESPONSE CODE field.\n\n";
      tooltip += Format( "Code        : 0x%02X.\n", val );
      tooltip +=         "Description : ";
      
      error = null;            
      
      select
      {
          val == 0x00 : { str = "TMF COMPLETE";         tooltip += "TASK MANAGEMENT FUNCTION COMPLETE"       ; }
          val == 0x02 : { str = "INVALID IFORMATION UNIT"    ;    tooltip += "INVALID IFORMATION UNIT"       ; }
          val == 0x04 : { str = "TMF NOT SUPPORTED";    tooltip += "TASK MANAGEMENT FUNCTION NOT SUPPORTED"  ; }
          val == 0x05 : { str = "TMF FAILED"  ;         tooltip += "TASK MANAGEMENT FUNCTION FAILED"         ; }
          val == 0x08 : { str = "TMF SUCCEEDED"  ;      tooltip += "TASK MANAGEMENT FUNCTION SUCCEEDED"      ; }
          val == 0x09 : { str = "INVALID LUN"  ;        tooltip += "INVALID LOGICAL UNIT NUMBER"             ; }
          val == 0x0A : { str = "OVERLAPPED TAG"  ;     tooltip += "OVERLAPPED TAG ATTEMPTED"             ; }

          default     : { str = "Reserved"        ; tooltip += "Reserved." + AddWarningTooltip("Reserved value");
                         error = _ERROR ; }
      };
      
      tooltip += ".";
      
     if (SCSILevel == 1) # SCSI Level
        AddPayLoadCell( "RESPONSE_CODE", str, tooltip, error, FieldColor, [_TABULARCELL, MS_UASP_RESPONSE_CODE] );
     else
        AddPayLoadCell( "RESPONSE_CODE", str, tooltip, error);               
      
}	

ShowStatusQualifier()
{
	scope = NextNBits_(2);
	
	select
	{
		  scope == 0x0 : { tooltip = "The logical unit addressed by the command\nassociated with the status."; }
		  scope == 0x1 : { tooltip = "All logical units accessible by the SCSI\ntarget port through which the command associated\nwith the status was routed."; }
		  scope == 0x2 : { tooltip = "All logical unit(s) contained within the\nSCSI device that contains the logical unit addressed\nby the command associated with\nthe status."; }
		  default      : { tooltip += "Reserved." + AddWarningTooltip("Reserved value"); error = _ERROR ; }
	};
	
	AddSimplePLCell("Scope", Format ("0x%02X", scope), tooltip );
	
	qualifier = NextNBits_(14);
	AddSimplePLCell("Qualifier", Format ("0x%04X", qualifier), "Status Qualifier");
}
#
#  Copyright (c) 2010, LeCroy - All Rights Reserved
#
#  MS_UASPOutEndpoint.inc
#
#  Prefix =  "SOB" 
#

%include "CATCScriptAPI.inc"
%include "UsbCommon.inc"

# SCSI definitions
%include "..\Shared\SCSI\SCSI_Defs.inc"

%include "MS_Common.inc"
#----  Input
# in.Data       - Data_block to decode
# in.DataLength - Length of Data_block 
#
#----  Output
# out.Decoded   - amount of data has been decoded
#


#------------------------  Common Globals -----------------------------------

set UsbDecodeType = "Endpoint";
set UsbClassCode  = 0x8; # Mass Storage Class
set UsbSubClass   = 0x06;
set UsbProtocol   = 0x62; # UASP
set UsbEndpType   = "Bulk";
set UsbEndpDir    = "Out";

set UsbMaxXferSize = 0x7FFFFFFF;  #try largest possible positive value  
set UsbMaxXferDecodeSize   = 36;  # Max bytes that we will be decoding  
set UsbMaxPktSize          = 512;   
set UsbScriptDecodeType    = 2; # Combined decoding for Cells and Text decoding
set UsbDecHdrType = 2; # This type references decoder byte containing the SCSI Opcode  
set UsbDecHdrLen  = 1; # This 1 byte is passed in to this via the in context
set UsbDecExtraInfoBytePos = 16; # Position of Additional Info byte
set UsbXferCompleteClue = 4;     # this Xfer ends if Bulk In seen during decoding  

# User can select the colors for the fields he chooses


#-------------------------------------------------------------------------------



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

set PrevOpcode = 0;

#
# Parsing entry point
#

ProcessUASOutData(process_as_data)
{
    InitType2Decoder();
    Prefix =  "SOB";   
    
    PrevOpcode = GetNBits(in.DecodeParams, 0, 8);
    #SCSILevel = GetNBits(in.DecodeParams, 8, 8);
    Read_SCSILevel();
        
    IUIdentifier = GetNBits(in.Data, 0, 8);
    IncFieldOffset(8);

    #Trace ("PrevOpcode:", PrevOpcode, "\n");
    #if the file has had its decoding refreshed, the previous opcode will appear to
    # be a 0, or Test Unit Ready.  Let the user know he should refresh decoding.
    # if it REALLY is a Test Unit Ready, the length should be less than 33
    #if ((PrevOpcode == 0) && (in.DataLength > 33))
    #{
    #    Trace(in.DataLength,"\n");
    #    out.Decoded = 0;  
    #    AddCaptionCell("Unable to decode",
	#	"Use tooltip for more info",
	#	 "To complete decoding, select Refresh Decoding by left-clicking\non the Bulk or Interrupt field to the left\nThis will allow the SCSI Requests and Responses to be associated.\n\nIf this trace missed part of the SCSI command,\nwe will still be unable to decode this transfer");
    #    return Complete();
    #}

    FieldColor = MassStorageColor;
    if (SCSILevel == 0) # Xfer level
    {
        AddCaptionCell("UASP", null, "", FieldColor, _MONOFIELD);
        AddDecSeparator();
    }
        
    if( process_as_data == 0 )
    {
		if ( IUIdentifier == 0x01 )
		{
			if (SCSILevel == 0 ) # Xfer level
			{
				command_block_size = CommandIU();
			}

			GetNBits(in.Data, 15*8, 8);    
	    
	    
    		#------------------------------- SCSI CDB -----------------------------
	        
    		# The line below specifies that the following SCSI CDB decoded unit
    		# is a kind of "field" having its own subfield order - and we need to
    		# make initialization procedure here - in order to show CDB field
    		# offsets in dialog view relatively the start point of CDB but not the one
    		# of the payload..
    		#
    		SaveFieldSettings();
    		CurrentFldInit(); 
    		ShowCDB( command_block_size );
	    	
    		#----------------------------------------------------------------------

		}
		else if ( IUIdentifier == 0x05 )
		{
			command_block_size = TaskManagmentIU();
		}    
	}
	else if( process_as_data == 1 )
	{
		if (SCSILevel == 0) # Xfer level
		{
			# No command block, so this is just raw data out
			if ((PrevOpcode != 0x3F) && (PrevOpcode != 0x2A) && (PrevOpcode != 0x0A))
			{
				DoCommandDataBlock(); # in case this is a Command with Data
			}
			else
			{
				AddCell(" Data OUT ", null, "This data payload represents a UASP Data Bulk.", FieldColor, _MONOFIELD, [_TABULARCELL, MS_UASP_IDENTIFIER]);   
			}
	        
			return Complete();
		}
	}
    
    out.Decoded = 32;  
    SCSILevel = 0;
    return Complete();
}

TaskManagmentIU()
{
    FieldColor = MassStorageColor;
    if (SCSILevel == 1) # SCSI level
    {
        func = GetDataByte(4);
	    tm_function = ShowTaskMgmtFunction( func );
	    AddDecSeparator();
    }
    else
    {
        if (in.Expanded || in.PrepareFldsForDlg)
        {
            AddDecodedTextHeader();
            
            AddSimplePLCell("IU ID", "Task Managment IU", "Task Managment Information Unit", FieldColor, [_CELLINFO, 1]);
        
			PLReservedCheck( 8 );
        
            AddTag( 16 );

			func = NextNBits_(8);
            tm_function = ShowTaskMgmtFunction( func );

	        PLReservedCheck( 8 );
	        
	        save_endian = LittleEndian;
            LittleEndian = 0;
        
	        tagOfTask = NextNBits_(16);
            AddSimplePLCell( "TAG_OF_TASK", Format("0x%04X", tagOfTask),
                            "TAG OF TASK TO BE MANAGED field.\n\n" +
                            "If TASK MANAGEMENT FUNCTION is set to ABORT TASK or QUERY TASK,\n" +
                            "the TAG OF TASK TO BE MANAGED field specifies the TAG value from\n" + 
                            "the COMMAND frame that contained the task to be aborted or checked.\n" +
                            "For all other task management functions, this field shall be ignored." );        
                            
            ShowLUNo();
            LittleEndian = save_endian;
        }
        else
        {     
			AddCell("Task Managment IU ", null, "Task Managment IU", FieldColor, _MONOFIELD, [_TABULARCELL, MS_UASP_IDENTIFIER]); 
         
			val = NextNBits_(8); #8bit as Reserved
        
            AddTag( 16 );
            
            AddDecSeparator();
            ShowLUNo();
        }
    }
    
    out.Decoded = GetBitOffset() / 8;    
}

CommandIU()
{
    FieldColor = MassStorageColor;
    addi_length_in_dword = 0;
    
    if (in.Expanded || in.PrepareFldsForDlg)
    {
        AddDecodedTextHeader();        AddStringToDlg("Command Information Unit", "", "");
        
        AddSimplePLCell("IU ID", "Command IU", "Command Information Unit", FieldColor, [_CELLINFO, 1]);
        
        PLReservedCheck( 8 );
        
        AddTag( 16 );
        
        PLReservedCheck( 1 );
        # val = NextNBits_(1); #1bit as Reserved
        ShowTaskPriority();   
        ShowTaskAttribute();
        
        PLReservedCheck( 8 );
        
        addi_length_in_dword = NextNBits_(6);
        AddSimplePLCell("Length", Format ("0x%02X", addi_length_in_dword), "Length");
        
        PLReservedCheck( 2 );

		PLReservedCheck( 8 );
        # val = NextNBits_(8); #8bit as Reserved
        
        ShowLUNo();

    }
    else
    {
		AddCell(" Command IU", null, "Command IU", FieldColor, _MONOFIELD);
		val = NextNBits_(8); #8bit as Reserved
    
        AddTag( 16 );
        
        NextNBits_(8); # Priority & Attribute
        NextNBits_(8); #8bit as Reserved
        
        addi_length_in_dword = NextNBits_(6);
        
        AddDecSeparator();
        ShowLUNo();
    }
    
    out.Decoded = GetBitOffset() / 8;    
    
    return 32 + addi_length_in_dword*4;
}

ShowLUNo()
{
    GetNBits( in.Data, 64, 0 );
    #------------------------------ LUN ----------------------------------------
    val = GetBitOffset();        # save offset    
    
    str = "0x";
    for( i = 0; i < 4; i++ )
        str += Format(" %04X", NextNBits(16));
        
    GetNBits( in.Data, val, 0 ); # restore offset    
    #---------------------------------------------------------------------------
    
    tooltip = "LUN (hex) : " + str + ".\n\n" + 
    "The LOGICAL UNIT NUMBER field specifies the address \n" + 
    "of the logical unit component of the nexus for the\n" + 
    "task request.";
    
    NextNBits_( 64 );    
    # Special cell for LUN in collapsed state
    if (in.Expanded || in.PrepareFldsForDlg)
    {
        AddPayLoadCell( "Logical Unit Number", str, tooltip, FieldColor );   
    }
    else
    {
        AddCell( "Logical Unit Number", str, tooltip, SCSI_Color );   
    }
    
}

ShowTaskAttribute()
{
       val = NextNBits_(3);
       
       base_tooltip  = "TASK ATTRIBUTE field.\n\n";
       base_tooltip += Format("Value   : 0x%01X.\n");
       base_tooltip +=        "Meaning : ";
       
       error = null;
       
       select 
       {
          val == 0b000 : { str = "SIMPLE";
                           tooltip = "It requests that the task be managed according\n" + 
                                     "to the rules for a SIMPLE task attribute.\n\n" +
									 "A task having the SIMPLE attribute shall be accepted\n" +
									 "into the task set in the dormant task state.\n" +
									 "The task shall not enter the enabled task state until\n" + 
									 "all older head of queue and older ordered tasks\n" + 
									 "in the task set have ended." ; }
          
          val == 0b001 : { str = "HEAD OF QUEUE";
                           tooltip = "It requests that the task be managed according\n" + 
                                     "to the rules for a HEAD OF QUEUE task attribute.\n\n" + 
                                     "A task having the HEAD OF QUEUE attribute shall be\n" +
									 "accepted into the task set in the enabled task state."; }
                                
          val == 0b010 : { str = "ORDERED";
                           tooltip = "It requests that the task be managed according\n" + 
                                     "to the rules for an ORDERED task attribute.\n\n" +
									 "A task having the ORDERED attribute shall be accepted\n" +
									 "into the task set in the dormant task state.\n" +
									 "The task shall not enter the enabled task state\n" + 
									 "until all older tasks in the task set have ended."; }
                                
          val == 0b100 : { str = "ACA";
                           tooltip = "It requests that the task be managed according\n" + 
                                     "to the rules for an automatic contingent allegiance\n" + 
                                     "(ACA) task attribute.\n\n" +
									 "A task having the ACA attribute shall be accepted into\n" +
									 "the task set in the enabled task state.\n" +
									 "There shall be no more than one ACA task per task set."; }                      
         
          default :      { str = "Reserved"; tooltip = "Reserved." + AddWarningTooltip("Reserved value");
                           error = _ERROR; }                            
       };
       
       base_tooltip += str + ".\n\n" + tooltip;
       
       options = [ ["SIMPLE", 0], ["HEAD OF QUEUE", 1], ["ORDERED", 2], ["ACA", 4] ];
       AddPayLoadCell( "TASK ATTRIBUTE", str, base_tooltip, FieldColor, [_CELLINFO, 0, options] );
}

ShowTaskPriority()
{
    val = NextNBits_(4);

    base_tooltip  = "TASK PRIORITY field.\n\n";
    base_tooltip += Format("Value   : 0x%01X.\n");
    base_tooltip +=        "Meaning : ";

    error = null;
    str = Format("0x%01X" , val);
    tooltip = " The TASK PRIORITY field specifies the relative scheduling of the task \n";
    tooltip += " containing this command in relation to other tasks already in the task set,\n";
    tooltip += " if the tasks have SIMPLE task attributes (see SAM-3).";
    base_tooltip += str + ".\n\n" + tooltip;

    AddPayLoadCell( "TASK PRIORITY", str, base_tooltip );
}

DoCommandDataBlock()
{
    save_endian = LittleEndian;
    LittleEndian = 0;
    out.Decoded = 0;
    
    CDB_Name = "";  
                
    cdb_dec = Find( CDB_DecTable, PrevOpcode );
    if (cdb_dec != null)
    {
        CDB_Name    = cdb_dec[1];
        CDB_Color   = cdb_dec[3];
        CDB_Tooltip = cdb_dec[4]; # Use the ones from SCSI
    }
    if (CDB_Name != "")
    {
     
        FieldColor = CDB_Color;
        
        select
        {
            (PrevOpcode == 0x04)   : DoFormatData(); 
            (PrevOpcode == 0x07)   : DoReassignBlocksData(); 
            (PrevOpcode == 0x15)   : DoModeSelectData();               
            (PrevOpcode == 0x18)   : DoCopyData();       
            (PrevOpcode == 0x1D)   : DoSendDiagnosticData(); # There are more...
        };
        
        AddDecSeparator();
        AddCaptionCell(CDB_Name, "Data", "Data corresponding to previous Command", _MONOCOLOR);
        
        
        if (in.DataLength > 0)
        {                    
            GetNBits(in.Data, 0, 0);
            SetFieldOffsetLen(0, 8);
            if (in.DataLength < MaxShowDataBlockSize)
            {         
                ShowDataBlockReOrder(in.DataLength);
            }
        }
    } 
    LittleEndian = save_endian;       
}

# Decode these in the future...
DoFormatData()
{
} 
DoReassignBlocksData()
{
} 
DoModeSelectData()
{
}
DoCopyData()
{
}
DoSendDiagnosticData()
{
}
#there's more!  

#------------------------ TASK MANAGEMENT FUNCTION ------------------------

ShowTaskMgmtFunction( val )
{    
    #val = NextNBits_(8);
    
    base_tooltip = "TASK MANAGEMENT FUNCTION field.";
    error = null;    
    
    base_tooltip += Format("\nValue   : %02Xh.\nMeaning : ", val);
            
        
    select {        
        val == 0x01 : { str = "ABORT TASK"    ; tooltip = "The task manager shall perform the ABORT TASK task\n" +
                                                          "management function with L set to the value of the\n" +
                                                          "LOGICAL UNIT NUMBER field and Q set to the value of the\n" +
                                                          "TAG OF TASK TO BE MANAGED field";
                      }

        val == 0x02 : { str = "ABORT TASK SET"; tooltip = "The task manager shall perform the ABORT TASK SET\n" +
                                                          "task management function with L set to the value of the\n" +
                                                          "LOGICAL UNIT NUMBER field";    
                      }

        val == 0x04 : { str = "CLEAR TASK SET"; tooltip = "The task manager shall perform the CLEAR TASK SET\n" +
                                                          "task management function with L set to the value of the\n" +
                                                          "LOGICAL UNIT NUMBER field";
                      }
        
        val == 0x08 : { str = "LUN RESET"     ; tooltip = "The task manager shall perform the LOGICAL UNIT\n" +
                                                          "RESET task management function with L set to the value\n" +
                                                          "of the LOGICAL UNIT NUMBER field";
                      }
		val == 0x10 : { str = "I_T NEXUS RESET"; tooltip = "The task manager shall perform the I_T NEXUS\n" +
                                                           "RESET task management function";
                      }
        
        val == 0x40 : { str = "CLEAR ACA"     ; tooltip = "The task manager shall perform the CLEAR ACA task\n" +
                                                          "management function with L set to the value of the\n" +
                                                          "LOGICAL UNIT NUMBER field";
                      }
                      
        val == 0x80 : { str = "QUERY TASK"    ; tooltip = "The task manager shall perform the QUERY TASK task\n" +
                                                          "management function with L set to the value of the\n" +
                                                          "LOGICAL UNIT NUMBER field and Q set to the value of the\n" +
                                                          "TAG OF TASK TO BE MANAGED field";
                      } 
                      
		val == 0x81 : { str = "QUERY TASK SET"; tooltip = "The task manager shall perform the QUERY\n" +
                                                          "TASK SET task management function with L set\n" +
                                                          "to the value of the LOGICAL UNIT NUMBER field";
                      } 
                      
        val == 0x82 : { str = "QUERY ASYNCHRONOUS EVENT"; tooltip = "The task manager shall perform the QUERY\n" +
                                                          "ASYNCHRONOUS EVENT task management\n" +
                                                          "function with L set to the value of the LOGICAL UNIT NUMBER field";
                      } 
                
        default     : { str = Format("%02Xh", val); 
                        tooltip  = AddWarningTooltip("Reserved function value"); 
                        tooltip += "\n\nThe task manager shall return a RESPONSE frame with\n" +
                                   "the DATAPRES field set to RESPONSE_DATA and its\n" +
                                   "RESPONSE CODE field set to TASK MANAGEMENT FUNCTION NOT SUPPORTED.";
                        error = _ERROR; 
                      }
    };
    
    base_tooltip += str + ".\n\n" + tooltip + ".";

	options = [ ["ABORT TASK", 1], ["ABORT TASK SET", 2], ["CLEAR TASK SET", 4], ["LUN RESET", 8], 
					["I_T NEXUS RESET", 0x10], ["CLEAR ACA", 0x40], ["QUERY TASK", 0x80], ["QUERY TASK SET", 0x81],
					["QUERY ASYNCHRONOUS EVENT", 0x82] ];
					
    if (SCSILevel == 1) # SCSI Level
        AddPayLoadCell( "TSK_MGMT_FN", str, base_tooltip, error, FieldColor, [_TABULARCELL, MS_UASP_TSK_MGM] );
    else
        AddPayLoadCell( "TSK_MGMT_FN", str, base_tooltip, error, [_CELLINFO, 0, options] );
        
    
    
    return str;
}

ProcessCDB()
{    
    InitType2Decoder();
    
    ShowCDB(command_block_size );
        
    return Complete();
}

ProcessTaskMgm()
{    
    InitType2Decoder();
    
    FieldColor = MassStorageColor;
    
    func = NextNBits_(8);
	tm_function = ShowTaskMgmtFunction( func );

	if( func == 0x01 || func == 0x80 )
	{
		tagOfTask = NextNBits_(16);
		AddSimplePLCell( "TAG_OF_TASK", Format("0x%04X", tagOfTask),
						"TAG OF TASK TO BE MANAGED field.\n\n" +
						"If TASK MANAGEMENT FUNCTION is set to ABORT TASK or QUERY TASK,\n" +
						"the TAG OF TASK TO BE MANAGED field specifies the TAG value from\n" + 
						"the COMMAND frame that contained the task to be aborted or checked.\n" +
						"For all other task management functions, this field shall be ignored." );  
	}
                            
    return Complete();
}

ProcessTransfer()
{    
	InitType2Decoder();
    
    IUIdentifier = NextNBits_(8);
    if ( IUIdentifier == 0x01 )
    {
		CommandIU();
		
		ProcessCDBs();
	}
	else if ( IUIdentifier == 0x05 )
    {	
		TaskManagmentIU();
    }
     
    return Complete();
}
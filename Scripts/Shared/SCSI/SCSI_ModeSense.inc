#
#  Copyright (c) 2010, LeCroy - All Rights Reserved
#
#  SCSI_ModeSense.inc
#
#  SCSI Mode Sense decoder functions
################################################################################

#----------------------------Mode Parameter General Block Descriptor Length 8 Bytes----------------------------

DoGenBlockDesc8(offset_num, make_string)
{	    
	if(make_string == 1)
	{
		AddLineOfText("RIGHT CLICK ON DESCRIPTORS FIELD TO SHOW ALL DESCRIPTORS DECODED!\n");

		AddColumnTitles();
	
		if( in.PrepareFldsForDlg == FALSE )
		{
			AddFieldBreak();
		}
	}
	
	density_code		= NextNBits_(8);
	num_blocks		    = NextNBits_(24);
	temp_Reserved		= NextNBits_(8);
	temp_block_len		= NextNBits_(24);
	
	if(make_string == 1)
	{
		AddEntry(offset_num , "Density Code", density_code, 2, "Unique for each device type.", 0);
		AddFieldBreak();
			
		AddEntry(offset_num+1, "Number of Blocks", num_blocks, 6, "Number of logical blocks.", 0);
		AddFieldBreak();

		AddEntry(offset_num+4, "Reserved", temp_Reserved, 2, "Reserved, should be set to 0.", 0);
		AddFieldBreak();
		
		AddEntry(offset_num+5, "Block Length", temp_block_len, 6, "Length of logical block.", 0);
		AddFieldBreak();	
		AddBlankLine();
		
		return GetFinalText();
	}
}


#----------------------------Mode Pages----------------------------
DoModePages()
{
	page_code = NextNBits_(8); 
    AddPayLoadCell("Page Code", Format ("0x%02X", page_code), "Page Code");
   
    #check SPF bit for sub_page or page_0
    if( page_code & 0x40 )	#sub_page
    {
		sub_page_code = NextNBits_(8); 
		AddPayLoadCell("SubPage Code", Format ("0x%02X", sub_page_code), "SubPage Code");
		
		page_length = NextNBits_(16); 
		AddSimplePLCell("Page Length", Format ("0x%04X", page_length), "Page Length.");
		
		str = "0x";

		for (i = 0; i < page_length; i++ )
		{
			val = NextNBits_(8);
			str += Format(" %02X", val);
		}
				
		AddSimplePLCell("Mode Parameters", str, "Mode Parameters.");
    }
    else					#page_0
    {
		page_length = NextNBits_(8); 
		AddSimplePLCell("Page Length", Format ("0x%02X", page_length), "Page Length.");
		
		str = "0x";

		for (i = 0; i < page_length; i++ )
		{
			val = NextNBits_(8);
			str += Format(" %02X", val);
		}
				
		AddSimplePLCell("Mode Parameters", str, "Mode Parameters.");
    }
}

#--------------------------------Mode Parameter Block Descriptor Length 16 Bytes-------------------------------

DoGenBlockDesc16(offset_numm , make_string)
{	
	if(make_string == 1)
	{
		AddLineOfText("RIGHT CLICK ON DESCRIPTORS FIELD TO SHOW ALL DESCRIPTORS DECODED!\n");
		
		AddColumnTitles();
		
		if( in.PrepareFldsForDlg == FALSE )
		{
			AddFieldBreak();
		}
	}	
	
	num_blocks		    = NextNBits_(16);
	density_code		= NextNBits_(8);
	temp_Reserved		= NextNBits_(8);
	temp_Reserved1		= NextNBits_(8);
	temp_Reserved2		= NextNBits_(8);
	temp_block_len		= NextNBits_(16);

	if(make_string == 1)
	{
		AddEntry(offset_num, "Number of Blocks", num_blocks, 4, "Number of logical blocks.", 0);
		AddFieldBreak();

		AddEntry(offset_num+2 , "Density Code", density_code, 2, "Unique for each device type.", 0);
		AddFieldBreak();
		
		AddEntry(offset_num+3, "Reserved", temp_Reserved, 2, "Reserved, should be set to 0.", 0);
		AddFieldBreak();
		
		AddEntry(offset_num+4, "Reserved", temp_Reserved1, 2, "Reserved, should be set to 0.", 0);
		AddFieldBreak();
		
		AddEntry(offset_num+5, "Reserved", temp_Reserved2, 2, "Reserved, should be set to 0.", 0);
		AddFieldBreak();
		
		AddEntry(offset_num+6, "Block Length", temp_block_len, 4, "Length of logical blocks.", 0);
		AddFieldBreak();
		
		AddBlankLine();
	
		return GetFinalText();
	}
}


#------------------ Mode Sense 6 Response ----------------------------

DoModeSense6Response()
{
	if (in.DataLength == 0)
	{	
		AddCaptionCell(	"  MODE_SENSE  ", "No Response", 
						"Device server returned 0 Block descriptors in response to MODE_SENSE Command", _MONOCOLOR);
	}
	else
	{
		AddCaptionCell("  MODE_SENSE  ", "Response", "Mode Parameter Header", _MONOCOLOR);
	
		data_len = NextNBits_(8);
		AddPayLoadCell("Mode Data Len", Format ("0x%02X", data_len), "Mode Data Length");
		
		med_type = NextNBits_(8);
		AddPayLoadCell("Medium Type", Format ("0x%02X", med_type), "Medium Type");
		
		device_spec_param = NextNBits_(8);
		AddSimplePLCell("Dev-Spec Params", Format ("0x%02X", device_spec_param ), "Device-Specific Parameters");
				
		block_len = NextNBits_(8); 
		AddSimplePLCell("Block Desc Len", Format ("0x%02X", block_len), "Block Descriptor Length");		
	
		BlockDescTooltip = "";
		offset_num = 4;
		num_block_desc = ( block_len / 8);
		str = num_block_desc + " Descriptor(s)";
		for(i = 0; i < num_block_desc; i++)
		{
            tooltip = "Mode Parameter Block Descriptor : " + (i+1);
            AddStrCellInDlg("","", tooltip + "\nBlock descriptors specify the medium characteristics for logical unit.");
            if( i == 0 )
            {
                BlockDescTooltip = DoGenBlockDesc8(offset_num, 1);
            }
            else
            {
                DoGenBlockDesc8(offset_num, 0);
            }
            offset_num +=8;
        }

        InitText();
        
        AddPLCellNoDlg("Block Descriptor", str, "Block Descriptor \n" +  BlockDescTooltip);
        
        DoModePages();
        
        out.decoded = in.DataLength;
    }
}

#--------------------------------------------Mode Sense 10 Response-------------------------------------------------

DoModeSense10Response()
{        
	if (in.DataLength == 0)
	{
		AddCaptionCell(	"  MODE_SENSE  ", "No Response", 
						"Device server returned 0 Block descriptors in response to MODE_SENSE Command", _MONOCOLOR);
	}
	else
	{
		AddCaptionCell("  MODE_SENSE  ", "Response", "Mode Parameter Header", _MONOCOLOR);
		
		DataByteHeaderOffset = 0;
		data_len = NextNBits_(16);
		AddPayLoadCell("Mode Data Len", Format ("0x%04X", data_len), "Mode Data Length");

		med_type = NextNBits_(8);
		AddPayLoadCell("Medium Type", Format ("0x%02X", med_type), "Medium Type");
		
		device_spec_param = NextNBits_(8); 
		AddSimplePLCell("Dev-Spec Params", Format ("0x%02X", device_spec_param ), "Device-Specific Parameters");
		
		PLReservedCheck(7);
		longlba	= NextNBits_(1);
		AddSimplePLCell(    "LONGLBA", Format ("0x%X", longlba), 
        					"LONGLBA field.\n\n"		+
		        			"Bit 0: Block descriptors are each 8 bytes long.\n"	+ 
				        	"Bit 1: Block descriptors are each 16 bytes long.");
		
		PLReservedCheck(8);

		block_len = NextNBits_(16); 
		AddSimplePLCell("Block Desc Len", Format ("0x%04X", block_len), "Block Descriptor Length");

		BlockDescTooltip = "";
		offset_num = 8;
		if(longlba == 0)
		{	
		    num_block_desc = ( block_len / 8);
            str = num_block_desc + " Descriptor(s)";
            for(i = 0; i < num_block_desc; i++)
            {
                tooltip = "Mode Parameter Block Descriptor : " + (i+1);
                AddStrCellInDlg("", "", tooltip + "\n Block descriptors specify the medium characteristics for logical unit.");
                if( i == 0 )
                {
                    BlockDescTooltip = DoGenBlockDesc8(offset_num, 1);
                }
                else
                {
                    DoGenBlockDesc8(offset_num, 0);
                }
                offset_num +=8;
            }
        }
        else
        {	
            num_block_desc = ( block_len / 16);
            str = num_block_desc + " Descriptor(s)";
            for(i = 0 ; i < num_block_desc; i++)
            {
                tooltip = "Mode Parameter Block Descriptor : " + (i+1);
                AddStrCellInDlg("", "", tooltip + "\n  Block descriptors specify the medium characteristics for logical unit.");
                if( i == 0 )
                {
                    BlockDescTooltip = DoGenBlockDesc16(offset_num, 1);
                }
                else
                {
                    DoGenBlockDesc16(offset_num, 0);
                }
                offset_num +=16;
            }
        }

        InitText();

        AddPLCellNoDlg("Block Descriptor", str, "Block Descriptor \n" +  BlockDescTooltip);

		DoModePages();
		
        out.decoded = in.DataLength;
    }
}
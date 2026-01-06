#
#  Copyright (c) 2010, LeCroy - All Rights Reserved
#
#  SCSI_Inquiry.inc
#
#  SCSI Inquiry Response decoder functions
################################################################################

set EVPD = 0;
set CMDDT = 0;
set PageCode = 0;

DoInquiryResponse()
{
	if( in.EVPD != null ) EVPD = in.EVPD;
	if( in.CMDDT != null ) CMDDT = in.CMDDT;    
	if( in.PageCode != null ) PageCode = in.PageCode;    
	
	if( in.DataLength == null || in.DataLength <= 0 )
		return 0;
	
	if( EVPD == 1 && CMDDT == 0 )
	{
		if ( PageCode >= 0x01 && PageCode <=  0x7F )
		{
			DoPageCode_01_7F();
			
		}
		else if ( PageCode == 0x82 )
		{
			DoPageCode_82();
			
		}
		else if( PageCode == 0x83 )
		{
			DoPageCode_83();
			
		}
		else if( PageCode == 0x84 || PageCode == 0 || PageCode == 0x80)
		{
			DoPageCode_84_80_00();
		}
		else if( PageCode == 0x85 )
		{
			DoPageCode_85();
		}
		else if( PageCode == 0x86 )
		{
			DoPageCode_86();
		}
		else if( PageCode == 0x87 )
		{
			DoPageCode_87();
		}
		else if( PageCode == 0x88 )
		{
			DoPageCode_88();
		}
		else if( PageCode == 0x89 )
		{
			DoPageCode_89();
		}
		else if( PageCode == 0x90 || PageCode == 0x91 )
		{
			DoPageCode_90_91();
		}
		else if( PageCode == 0xb0 )
		{
			DoPageCode_b0();
		}
		else if( PageCode == 0xb1 )
		{
			DoPageCode_b1();
		}
	}
	else if(  EVPD == 0 && CMDDT == 1 )
	{
		DoCommandSupport();
	}
	else
	{
		DoStandardInquiry();
	}	    
}

GetUnicodeString(length)
{
    done = 0;
    str = "";
    offset = 8;
    index = 0;
    val = 0;
    while ((done == 0) && (index < length))
    {
        val = NextNBits_(8);

        if (val != null)
        {
			if (val != 0)
				str += Format("%c", val);
            index++;
        } 
        else
        {
            done = 1;
        }
    }
    
    if(index != length)
    {
      trash = 0;
      trash = NextNBits_((length - index)*8);
    }
    return str;   
}

DoCommandSupport()
{
	AddDecSeparator();
	FieldColor = CDB_Inquiry_Color;
	AddCaptionCell("  INQUIRY  ", "Response", "Response to INQUIRY Command", _MONOCOLOR); 
    
	PQ = NextNBits_(3);
	AddPayLoadCell("PQ", Format ("%d",PQ), "Peripheral Qualifier");
	DevType = NextNBits_(5);
	AddPayLoadCell("Dev Typ", Format ("0x%02X", DevType), "Peripheral Device Type");
	
	PLReservedCheck( 5 );
	
	support = NextNBits_(3);
	tooltip    = "";
	select
	{
		support == 0x00 :   { tooltip += "Data about the requested SCSI operation\ncode is not currently available.";}
		support == 0x01 :   { tooltip += "The device server does not support the\ntested SCSI operation code.\nAll data after byte 1 is undefined."; }
		support == 0x03 :   { tooltip += "The device server supports the tested\nSCSI operation code in conformance with a SCSI standard.\nThe data format conforms to the definition in table 84."; }	
		support == 0x04 :   { tooltip += "Vendor specific"; }	
		support == 0x05 :   { tooltip += "The device server supports the tested\nSCSI operation code in a vendor specific manner.\nThe data format conforms to the definition in table 84."; }	
		support == 0x06 :   { tooltip += "Vendor specific"; }	
		default     :	    { tooltip += "Reserved." + AddWarningTooltip("Reserved value"); }
	};


	AddPayLoadCell("Support", Format ("0x%02X", support), tooltip);
			
	val = NextNBits_(8);
	AddSimplePLCell("Version", Format ("0x%02X", val), "Version");
	
	PLReservedCheck( 8 );
	PLReservedCheck( 8 );
	
	cdb_size = NextNBits_(8);
	AddSimplePLCell("CDB Size", Format ("0x%02X", cdb_size), "CDB Size");
	
	str = "0x";
	for (i = 0; i < cdb_size; i++ )
	{
		val = NextNBits_(8);
		str += Format(" %02X", val);
	}
			
	AddSimplePLCell("CDB Data", str, "CDB Usage Data.");
}

DoStandardInquiry()
{
	AddDecSeparator();
	FieldColor = CDB_Inquiry_Color;
	AddCaptionCell("  INQUIRY  ", "Response", "Response to INQUIRY Command", _MONOCOLOR); 
    
	# val = NextNBits_(8);
	# AddSimplePLCell("PQ", Format ("%d", (val >> 5)), "Peripheral Qualifier");
	# AddPayLoadCell("Dev Typ", Format ("0x%02X", (val & 0x1F)), "Peripheral Device Type");
	
	PQ = NextNBits_(3);
	AddPayLoadCell("PQ", Format ("%d",PQ), "Peripheral Qualifier");
	DevType = NextNBits_(5);
	AddPayLoadCell("Dev Typ", Format ("0x%02X", DevType), "Peripheral Device Type");
    
	val = NextNBits_(8);
	AddPayLoadCell("Rem", Format ("%d", (val >> 7)), Format ("Removable Medium   (Byte 1 = 0x%02X)", val));
    
	val = NextNBits_(8);
	AddSimplePLCell("Version", Format ("0x%02X", val), "Version");
    
	val = NextNBits_(8);
	str  = "Byte 3 Flags:\n";      
	str += Format ("AENC       Async Event Notification Capable: %d\n", (val >> 7));      
	str += Format ("NormACA    Normal ACA Supported:             %d\n", ((val >> 5) & 0x1));      
	str += Format ("HiSup      Hierarchical Support (LUN Addr):  %d\n", ((val >> 4) & 0x1));      
	str += Format ("           Response Data Format:             0x%01X", val & 0xF);             
	AddSimplePLCell("Flags(3)", Format ("0x%02X", val), str);
    
	val = NextNBits_(8);
	AddSimplePLCell("Addl Len", Format ("0x%02X", val), Format ("Additional Length = %d", vaL));
    
	val = NextNBits_(8);
	str  = "Byte 5 Flag:\n";      
	str += Format ("SCCS   SCC Support:   %d", val >> 7);      
	AddSimplePLCell("SCCS", Format ("0x%02X", val), str);
    
	val = NextNBits_(8);
	str  = "Byte 6 Flags:\n";      
	str += Format ("BQue       Basic Queueing Supt for Log Unit:      %d\n", (val >> 7));      
	str += Format ("EncServ    Contains enclosure services component: %d\n", ((val >> 6) & 0x1));      
	str += Format ("VS         Vendor-Specific:                       %d\n", ((val >> 5) & 0x1));      
	str += Format ("MultiP     MultiPort Device:                      %d\n", ((val >> 4) & 0x1));      
	str += Format ("MChngr     Embedded/Attached meduim changer:      %d\n", ((val >> 3) & 0x1));      
	str += Format ("Addr16     16-bit Address Supported:              %d", (val & 0x1));      
	AddSimplePLCell("Flags(6)", Format ("0x%02X", val), str);
   
	val = NextNBits_(8);
	str  = "Byte 7 Flags:\n";      
	str += Format ("RelAdr     Relative Addressing Supported:  %d\n", (val >> 7));      
	str += Format ("WBus16     Wide Bus 16 Bit:                %d\n", ((val >> 5) & 0x1));      
	str += Format ("Sync       Synchronous Transfer Supported: %d\n", ((val >> 4) & 0x1));      
	str += Format ("Linked     Linked Commands Supported:      %d\n", ((val >> 3) & 0x1));      
	str += Format ("TransDis   Transfer Disable Supported:     %d\n", ((val >> 2) & 0x1));      
	str += Format ("CmdQue     Command Queuing Supported):     %d\n", ((val >> 1) & 0x1));      
	str += Format ("VS         Vendor Specific:                %d\n", (val & 0xF));             
	AddSimplePLCell("Flags(7)", Format ("0x%02X", val), str);
  
	if (in.DataLength >= 16)
	{
		AddPayLoadCell("Vendor Id", GetUnicodeString(8), "Vendor Identification");      
	}
	else
	{
		AddPayLoadCell("Vendor Id", "", "Vendor Identification");      	
	}
	
	if (in.DataLength >= 32)
	{
		AddPayLoadCell("Product Id", GetUnicodeString(16), "Product Identification");       	
	}
	else 
	{
		AddPayLoadCell("Product Id", "", "Product Identification");       		
	}

	if (in.DataLength >= 36)
	{
		AddPayLoadCell("Product Rev", GetUnicodeString(4), "Product Revision Level");       	
	}
	else 
	{
		AddPayLoadCell("Product Rev", "", "Product Revision Level");       		
	}
}

DoPageCode_01_7F()	
{
	AddDecSeparator();
	FieldColor = CDB_Inquiry_Color;
	AddCaptionCell("  INQUIRY  ", "Response", "ASCII Information VPD page", _MONOCOLOR); 
    
	PQ = NextNBits_(3);
	AddPayLoadCell("PQ", Format ("%d",PQ), "Peripheral Qualifier");
	DevType = NextNBits_(5);
	AddPayLoadCell("Dev Typ", Format ("0x%02X", DevType), "Peripheral Device Type");
	
	page_code = NextNBits_(8); 
	AddPayLoadCell("Page Code", Format ("0x%02X", page_code), "Page Code");
	
	PLReservedCheck( 8 );
	
	page_length = NextNBits_(8); 
	AddSimplePLCell("Page Length", Format ("0x%02X", page_length), "Page Length.");
	
	inquiry_ascii_length = NextNBits_(8); 
	AddSimplePLCell("ASCII Length", Format ("0x%02X", inquiry_ascii_length), "Inquiry ASCII Length.");
	
	AddSimplePLCell("ASCII Info", GetUnicodeString(inquiry_ascii_length), "Inquiry ASCII Information");
			
	if( page_length - inquiry_ascii_length - 1 > 0 )
	{
		AddPayLoadCell("Vendor Id", GetUnicodeString(8, 8), "Vendor Identification");      
		str = "0x";

		for (i = 0; i < page_length - inquiry_ascii_length - 1; i++ )
		{
			val = NextNBits_(8);
			str += Format(" %02X", val);
		}
				
		AddSimplePLCell("Vendor Info", str, "Vendor Specific Information.");
	}
}

DoPageCode_82()
{
	AddDecSeparator();
	FieldColor = CDB_Inquiry_Color;
	AddCaptionCell("  INQUIRY  ", "Response", "Vital product data", _MONOCOLOR); 
    
	PQ = NextNBits_(3);
	AddPayLoadCell("PQ", Format ("%d",PQ), "Peripheral Qualifier");
	DevType = NextNBits_(5);
	AddPayLoadCell("Dev Typ", Format ("0x%02X", DevType), "Peripheral Device Type");
	
	page_code = NextNBits_(8); 
	AddPayLoadCell("Page Code", Format ("0x%02X", page_code), "Page Code");
	
	PLReservedCheck( 8 );
	
	page_length = NextNBits_(8); 
	AddSimplePLCell("Page Length", Format ("0x%02X", page_length), "Page Length.");
	
	ascii_operating_desc_length = NextNBits_(8); 
	AddSimplePLCell("ASCII Desc Length", Format ("0x%02X", ascii_operating_desc_length), "Ascii Operating Definition Description Length.");
	
	AddSimplePLCell("Operation Desc Data", GetUnicodeString(ascii_operating_desc_length), "Operating Definition Description Data");
			
	if( page_length - ascii_operating_desc_length - 1 > 0 )
	{
		str = "0x";

		for (i = 0; i < page_length - ascii_operating_desc_length - 1; i++ )
		{
			val = NextNBits_(8);
			str += Format(" %02X", val);
		}
				
		AddSimplePLCell("Vendor Info", str, "Vendor Specific Information.");
	}
}

DoPageCode_83()
{
	AddDecSeparator();
	FieldColor = CDB_Inquiry_Color;
	AddCaptionCell("  INQUIRY  ", "Response", "Device Identification VPD page", _MONOCOLOR); 
    
	PQ = NextNBits_(3);
	AddPayLoadCell("PQ", Format ("%d",PQ), "Peripheral Qualifier");
	DevType = NextNBits_(5);
	AddPayLoadCell("Dev Typ", Format ("0x%02X", DevType), "Peripheral Device Type");
	
	page_code = NextNBits_(8); 
	AddPayLoadCell("Page Code", Format ("0x%02X", page_code), "Page Code");
	
	page_length = NextNBits_(16); 
	AddSimplePLCell("Page Length", Format ("0x%04X", page_length), "Page Length.");
			
	while( page_length > 0)
	{
		pro_id = NextNBits_(4);
		AddSimplePLCell("Protocol Id", Format ("%d", pro_id ), "Protocol Identifier");
		
		code_set = NextNBits_(4);
		tooltip    = "";
		select
		{
			code_set == 0x01 :   { tooltip += "The IDENTIFIER field shall contain binary values.";}
			code_set == 0x02 :   { tooltip += "The IDENTIFIER field shall contain ASCII graphic codes."; }
			default     :		 { tooltip += "Reserved." + AddWarningTooltip("Reserved value"); }
		};
		
		AddSimplePLCell("Code Set", Format ("0x%02X", code_set ), tooltip);
		
		piv = NextNBits_(1);
		AddSimplePLCell("PIV", Format ("%d", piv), "PIV");
		
		PLReservedCheck( 1 );
		
		assoc = NextNBits_(2);
		tooltip    = "";
		select
		{
			assoc == 0x00 :   { tooltip += "The IDENTIFIER field is associated\nwith the addressed logical unit.";}
			assoc == 0x01 :   { tooltip += "The IDENTIFIER field is associated\nwith the port that received the request."; }
			assoc == 0x02 :   { tooltip += "The IDENTIFIER field is associated\nwith the SCSI target device that contains\nthe addressed logical unit."; }
			default     :	  { tooltip += "Reserved." + AddWarningTooltip("Reserved value"); }
		};
		
		AddSimplePLCell("Association", Format ("0x%02X",assoc ), tooltip);
		
		id_type = NextNBits_(4);
		tooltip    = "";
		select
		{
			id_type == 0x00 :   { tooltip += "Vendor specific";}
			id_type == 0x01 :   { tooltip += "T10 vendor identification"; }
			id_type == 0x02 :   { tooltip += "EUI-64"; }
			id_type == 0x03 :   { tooltip += "NAA"; }	
			id_type == 0x04 :   { tooltip += "Relative target port"; }	
			id_type == 0x05 :   { tooltip += "Target port group"; }	
			id_type == 0x06 :   { tooltip += "Logical unit group"; }	
			id_type == 0x07 :   { tooltip += "MD5 logical unit identifier"; }	
			default     :	    { tooltip += "Reserved." + AddWarningTooltip("Reserved value"); }
		};
	
	
		AddSimplePLCell("Id Type", Format ("0x%02X", id_type), tooltip);
		
		PLReservedCheck( 8 );
	
		id_len = NextNBits_(8);
		AddSimplePLCell("Id Length", Format ("0x%02X", id_len), "Identifier Length");
	
		correct_id_len = id_len;
		
		if( id_len > in.DataLength - GetBitOffset() / 8 )
			correct_id_len = in.DataLength - GetBitOffset() / 8;
		
		
		if( code_set == 0x02 ) #ASCII
		{
			AddSimplePLCell("Identifier", GetUnicodeString(correct_id_len), "IDENTIFIER");
		}
		else
		{
			str = "0x";

			for (i = 0; i < correct_id_len; i++ )
			{
				val = NextNBits_(8);
				str += Format(" %02X", val);
			}
					
			AddSimplePLCell("Identifier", str, "IDENTIFIER");
		}
		page_length = page_length - (id_len + 4);
	}
}

DoPageCode_84_80_00()
{
	AddDecSeparator();
	FieldColor = CDB_Inquiry_Color;
	
	if( PageCode == 0x84 )
		AddCaptionCell("  INQUIRY  ", "Response", "Software Interface Identification VPD page", _MONOCOLOR); 
	else if( PageCode == 0x00 )
		AddCaptionCell("  INQUIRY  ", "Response", "Supported VPD Pages VPD page", _MONOCOLOR); 
	else if( PageCode == 0x80 )
		AddCaptionCell("  INQUIRY  ", "Response", "Unit Serial Number VPD page", _MONOCOLOR); 
	
    
	PQ = NextNBits_(3);
	AddPayLoadCell("PQ", Format ("%d",PQ), "Peripheral Qualifier");
	DevType = NextNBits_(5);
	AddPayLoadCell("Dev Typ", Format ("0x%02X", DevType), "Peripheral Device Type");
	
	page_code = NextNBits_(8); 
	AddPayLoadCell("Page Code", Format ("0x%02X", page_code), "Page Code");
	
	PLReservedCheck( 8 );
	
	page_length = NextNBits_(8); 
	AddSimplePLCell("Page Length", Format ("0x%02X", page_length), "Page Length.");
	
	str = "0x";

	for (i = 0; i < page_length; i++ )
	{
		val = NextNBits_(8);
		str += Format(" %02X", val);
	}
			
	if( PageCode == 0x84 )
		AddSimplePLCell("Software Id List", str, "Software interface identifier list.");
	else if( PageCode == 0x00 )
		AddSimplePLCell("VPD List", str, "Supported VPD page list.");
	else if( PageCode == 0x80 )
		AddSimplePLCell("Product No", GetUnicodeString(page_length), "Product Serial Number.");
}

DoPageCode_85()
{
	AddDecSeparator();
	FieldColor = CDB_Inquiry_Color;
	AddCaptionCell("  INQUIRY  ", "Response", "Management Network Addresses VPD page", _MONOCOLOR); 
    
	PQ = NextNBits_(3);
	AddPayLoadCell("PQ", Format ("%d",PQ), "Peripheral Qualifier");
	DevType = NextNBits_(5);
	AddPayLoadCell("Dev Typ", Format ("0x%02X", DevType), "Peripheral Device Type");
	
	page_code = NextNBits_(8); 
	AddPayLoadCell("Page Code", Format ("0x%02X", page_code), "Page Code");
	
	page_length = NextNBits_(16); 
	AddSimplePLCell("Page Length", Format ("0x%04X", page_length), "Page Length.");
			
	while( page_length > 0)
	{
		PLReservedCheck( 1 );
		
		assoc = NextNBits_(2);
		tooltip    = "";
		select
		{
			assoc == 0x00 :   { tooltip += "The IDENTIFIER field is associated\nwith the addressed logical unit.";}
			assoc == 0x01 :   { tooltip += "The IDENTIFIER field is associated\nwith the port that received the request."; }
			assoc == 0x02 :   { tooltip += "The IDENTIFIER field is associated\nwith the SCSI target device that contains\nthe addressed logical unit."; }
			default     :	  { tooltip += "Reserved." + AddWarningTooltip("Reserved value"); }
		};
		
		AddSimplePLCell("Association", Format ("0x%02X",assoc ), tooltip);
		
		service_type = NextNBits_(5);
		tooltip    = "";
		select
		{
			service_type == 0x00 :   { str = "Unspecified";			tooltip += "Unspecified";}
			service_type == 0x01 :   { str = "Storage Cfg Service";	tooltip += "Storage Configuration Service"; }
			service_type == 0x02 :   { str = "Diagnostics";			tooltip += "Diagnostics"; }
			service_type == 0x03 :   { str = "Status";				tooltip += "Status"; }	
			service_type == 0x04 :   { str = "Logging";				tooltip += "Logging"; }	
			service_type == 0x05 :   { str = "Code Dwnld";			tooltip += "Code Download"; }	
			default     :			 { str = "Reserved";			tooltip += "Reserved." + AddWarningTooltip("Reserved value"); }
		};
	
	
		AddSimplePLCell("Service Type", str, tooltip);
		
		PLReservedCheck( 8 );
	
		net_address_len = NextNBits_(8);
		AddSimplePLCell("Network Addr Length", Format ("0x%02X", net_address_len), "Network Address Length");
	
		correct_address_len = net_address_len;
		
		if( net_address_len > in.DataLength - GetBitOffset() / 8 )
			correct_address_len = in.DataLength - GetBitOffset() / 8;
		
		
		if( code_set == 0x02 ) #ASCII
		{
			AddSimplePLCell("Identifier", GetUnicodeString(correct_address_len), "IDENTIFIER");
		}
		else
		{
			str = "0x";

			for (i = 0; i < correct_address_len; i++ )
			{
				val = NextNBits_(8);
				str += Format(" %02X", val);
			}
					
			AddSimplePLCell("Network Addr", str, "Network Address");
		}
		page_length = page_length - (net_address_len + 4);
	}
}

DoPageCode_86()
{
	AddDecSeparator();
	FieldColor = CDB_Inquiry_Color;
	AddCaptionCell("  INQUIRY  ", "Response", "Extended INQUIRY Data VPD page", _MONOCOLOR); 
    
	PQ = NextNBits_(3);
	AddPayLoadCell("PQ", Format ("%d",PQ), "Peripheral Qualifier");
	DevType = NextNBits_(5);
	AddPayLoadCell("Dev Typ", Format ("0x%02X", DevType), "Peripheral Device Type");
	
	page_code = NextNBits_(8); 
	AddPayLoadCell("Page Code", Format ("0x%02X", page_code), "Page Code");
	
	PLReservedCheck( 8 );
	
	page_length = NextNBits_(8); 
	AddSimplePLCell("Page Length", Format ("0x%02X", page_length), "Page Length.");
	
	PLReservedCheck( 2 );
	
	spt = NextNBits_(3);
	tooltip    = "Supported protection type: \n";
	select
	{
		spt == 0x00 :   { tooltip += "The logical unit supports type 1 protection";}
		spt == 0x01 :   { tooltip += "The logical unit supports type 1 and type 2 protection"; }
		spt == 0x03 :   { tooltip += "The logical unit supports type 1 and type 3 protection"; }	
		default     :	{ tooltip += "Reserved." + AddWarningTooltip("Reserved value"); }
	};

	AddSimplePLCell("SPT", Format ("0x%02X", spt), tooltip);
	AddSimplePLCell("GRD_CHK", GetBitStr(), "A guard check (GRD_CHK) bit set to zero indicates\nthat the device server does not check the LOGICAL BLOCK GUARD\nfield in the protection information, if any.");
	AddSimplePLCell("APP_CHK", GetBitStr(), "An application tag check (APP_CHK) bit set to zero\nindicates that the device server does not check the LOGICAL\nBLOCK APPLICATION TAG field in the protection information.");
	AddSimplePLCell("REF_CHK", GetBitStr(), "A reference tag check (REF_CHK) bit set to zero\nindicates that the device server does not check the LOGICAL\nBLOCK REFERENCE TAG field in the protection information.");
	
	PLReservedCheck( 2 );
	AddSimplePLCell("UASK_SUP", GetBitStr(), "A unit attention condition sense key specific data\nsupported (UASK_SUP) bit set to one indicates that the\ndevice server returns sense-key specific data for the\nUNIT ATTENTION sense key.");
	AddSimplePLCell("GROUP_SUP", GetBitStr(), "A grouping function supported (GROUP_SUP) bit set\nto one indicates that the grouping function is supported\nby the device server.");
	AddSimplePLCell("PRIOR_SUP", GetBitStr(), "A priority supported (PRIOR_SUP) bit set to one indicates\nthat command priority is supported by the logical unit.\nA PRIOR_SUP bit set to zero indicates that command\npriority is not supported.");
	AddSimplePLCell("HEADSUP", GetBitStr(), "A head of queue supported (HEADSUP) bit set to one indicates\nthat the HEAD OF QUEUE task attribute is\nsupported by the logical unit.");
	AddSimplePLCell("ORDSUP", GetBitStr(), "An ordered supported (ORDSUP) bit set to one indicates that\nthe ORDERED task attribute is supported\nby the logical unit.");
	AddSimplePLCell("SIMPSUP", GetBitStr(), "The simple supported (SIMPSUP) bit shall be set to\none indicating that the SIMPLE task attribute is\nsupported by the logical unit.");
	
	PLReservedCheck( 4 );
	AddSimplePLCell("WU_SUP", GetBitStr(), "A write uncorrectable supported (WU_SUP) bit set\nto zero indicates that the device server does not\nsupport application clients setting the WR_UNCOR bit\nto one in the WRITE LONG command.");
	AddSimplePLCell("CRD_SUP", GetBitStr(), "A correction disable supported (CRD_SUP) bit set\nto zero indicates that the device server does not\nsupport application clients setting the COR_DIS bit\nto one in the WRITE LONG command.");
	AddSimplePLCell("NV_SUP", GetBitStr(), "A non-volatile cache supported (NV_SUP) bit set\nto one indicates that the device server supports a\nnon-volatile cache and that the applicable command\nstandard defines features using this cache.");
	AddSimplePLCell("V_SUP", GetBitStr(), "A volatile cache supported (V_SUP) bit set to\none indicates that the device server supports\na volatile cache and that the applicable command\nstandard defines features using this cache.");
	
	PLReservedCheck( 7 );
	AddSimplePLCell("LUICLR", GetBitStr(), "A logical unit I_T nexus clear (LUICLR) bit\nset to one indicates the SCSI target device clears any\nunit attention condition with an additional sense\ncode of REPORTED LUNS DATA HAS CHANGED in each logical\nunit accessible to an I_T nexus after reporting the unit attention condition for any\nlogical unit over that I_T nexus");
	
	PLReservedCheck( 8 );
	
	PLReservedCheck( 4 );
	
	microcode_download = NextNBits_(4);
	AddSimplePLCell("Microcode Download", Format ("%d",microcode_download), "The MULTI I_T NEXUS MICROCODE DOWNLOAD field indicates\nhow the device server handles concurrent attempts to\ndownload microcode using the WRITE BUFFER command from multiple\nI_T nexuses.");
	
	
	PLReservedCheck( 16 );
	PLReservedCheck( 32 );
	PLReservedCheck( 32 );
	PLReservedCheck( 32 );
	PLReservedCheck( 32 );
	PLReservedCheck( 32 );
	PLReservedCheck( 32 );
	PLReservedCheck( 32 );
	PLReservedCheck( 32 );
	PLReservedCheck( 32 );
	PLReservedCheck( 32 );
	PLReservedCheck( 32 );
	PLReservedCheck( 32 );
	PLReservedCheck( 32 );
}

DoPageCode_87()
{
	AddDecSeparator();
	FieldColor = CDB_Inquiry_Color;
	AddCaptionCell("  INQUIRY  ", "Response", "Mode Page Policy VPD page", _MONOCOLOR); 
    
	PQ = NextNBits_(3);
	AddPayLoadCell("PQ", Format ("%d",PQ), "Peripheral Qualifier");
	DevType = NextNBits_(5);
	AddPayLoadCell("Dev Typ", Format ("0x%02X", DevType), "Peripheral Device Type");
	
	page_code = NextNBits_(8); 
	AddPayLoadCell("Page Code", Format ("0x%02X", page_code), "Page Code");
	
	page_length = NextNBits_(16); 
	AddSimplePLCell("Page Length", Format ("0x%04X", page_length), "Page Length.");
			
	while( page_length > 0)
	{
		PLReservedCheck( 2 );
		
		policy_page_code = NextNBits_(6);
		AddSimplePLCell("Policy Page Code", Format ("0x%02X", policy_page_code ), "The POLICY PAGE CODE field and POLICY SUBPAGE CODE\nfield indicate the mode page and subpage to which\nthe descriptor applies.");
		
		policy_subpage_code = NextNBits_(8);
		AddSimplePLCell("Policy Subpage Code", Format ("0x%02X", policy_subpage_code ), "If the POLICY SUBPAGE CODE field contains a value\nother than FFh, then POLICY PAGE CODE field\nshall contain a\nvalue other than 3Fh.");
		
		
		AddSimplePLCell("MLUS", GetBitStr(), "The MLUS bit is set to one in the mode page policy descriptors\nor descriptor that indicates the mode page policy.");
		
		PLReservedCheck( 5 );
		
		mode_page_policy = NextNBits_(2);
		tooltip    = "";
		select
		{
			mode_page_policy == 0x00 :   { str = "Shared";			tooltip += "Shared";}
			mode_page_policy == 0x01 :   { str = "Per target port";	tooltip += "Per target port"; }
			mode_page_policy == 0x02 :   { str = "Obsolete";		tooltip += "Obsolete"; }
			mode_page_policy == 0x03 :   { str = "Per I_T nexus";	tooltip += "Per I_T nexus"; }	
		};
	
	
		AddSimplePLCell("Mode Page Policy", str, tooltip);
		
		PLReservedCheck( 8 );

		page_length = page_length - 4;
	}
}

DoPageCode_88()
{
	AddDecSeparator();
	FieldColor = CDB_Inquiry_Color;
	AddCaptionCell("  INQUIRY  ", "Response", "SCSI Ports VPD page", _MONOCOLOR); 
    
	PQ = NextNBits_(3);
	AddPayLoadCell("PQ", Format ("%d",PQ), "Peripheral Qualifier");
	DevType = NextNBits_(5);
	AddPayLoadCell("Dev Typ", Format ("0x%02X", DevType), "Peripheral Device Type");
	
	page_code = NextNBits_(8); 
	AddPayLoadCell("Page Code", Format ("0x%02X", page_code), "Page Code");
	
	page_length = NextNBits_(16); 
	AddSimplePLCell("Page Length", Format ("0x%04X", page_length), "Page Length.");
			
	while( page_length > 0)
	{
		PLReservedCheck( 16 );
		
		relative_port_identifier = NextNBits_(16);
		tooltip    = "";
		select
		{
			relative_port_identifier == 0x00 :   { tooltip += "Reserved";}
			relative_port_identifier == 0x01 :   { tooltip += "Relative port 2, historically known as port B"; }
			relative_port_identifier == 0x02 :   { tooltip += "Relative port 2, historically known as port B"; }
			default     :						 { tooltip += "Reserved"; }	
		};
		AddSimplePLCell("Relative Port Identifier", Format ("0x%04X", relative_port_identifier ), tooltip);
		
		PLReservedCheck( 16 );
		
		initiator_port_length = NextNBits_(16);
		AddSimplePLCell("Ini Port Trans Len", Format ("0x%04X", initiator_port_length ), "Initiator Port Transportid Length");
		
		if( initiator_port_length > 0 )		
		{
			str = "0x";
			for (i = 0; i < initiator_port_length; i++ )
			{
				val = NextNBits_(8);
				str += Format(" %02X", val);
			}
					
			AddSimplePLCell("Ini Port Trans", str, "Initiator Port Transportid");
		}
			
		PLReservedCheck( 16 );
		
		targ_port_desc_length = NextNBits_(16);
		AddSimplePLCell("Targ Desc Len", Format ("0x%04X", targ_port_desc_length ), "Target Port Descriptors Length");
		
		if( targ_port_desc_length > 0 )		
		{
			str = "0x";
			for (i = 0; i < targ_port_desc_length; i++ )
			{
				val = NextNBits_(8);
				str += Format(" %02X", val);
			}
					
			AddSimplePLCell("Targ Port Desc List", str, "Target Port Descriptor List");
		}
		
		page_length = page_length - (initiator_port_length + 6 + targ_port_desc_length + 2);
	}	
}

DoPageCode_89()
{
	AddDecSeparator();
	FieldColor = CDB_Inquiry_Color;
	AddCaptionCell("  INQUIRY  ", "Response", "SCSI Ports VPD page", _MONOCOLOR); 
    
	PQ = NextNBits_(3);
	AddPayLoadCell("PQ", Format ("%d",PQ), "Peripheral Qualifier");
	DevType = NextNBits_(5);
	AddPayLoadCell("Dev Typ", Format ("0x%02X", DevType), "Peripheral Device Type");
	
	page_code = NextNBits_(8); 
	AddPayLoadCell("Page Code", Format ("0x%02X", page_code), "Page Code");
	
	page_length = NextNBits_(16); 
	AddSimplePLCell("Page Length", Format ("0x%04X", page_length), "Page Length.");
	
	PLReservedCheck( 32 );
	
	str = "0x";
	for (i = 0; i < 2; i++ ) # 64 bits
	{
		val = NextNBits_(32);
		str += Format(" %02X", val);
	}
			
	AddSimplePLCell("SAT Vendor Id", str, "SAT Vendor Identification");
	
	str = "0x";
	for (i = 0; i < 4; i++ ) # 16 bytes
	{
		val = NextNBits_(32);
		str += Format(" %04X", val);
	}
			
	AddSimplePLCell("SAT Product Id", str, "SAT Product Identification");
	
	sat_product_rev_level = NextNBits_(32); 
	AddSimplePLCell("SAT Product Rev Level", Format ("0x%04X", sat_product_rev_level), "SAT Product Revision Level.");
	
	str = "0x";
	for (i = 0; i < 5; i++ ) # 160 bits
	{
		val = NextNBits_(32);
		str += Format(" %04X", val);
	}
			
	AddSimplePLCell("Device Sign", str, "Device signature");
	
	command_code = NextNBits_(8); 
	AddPayLoadCell("Command Code", Format ("0x%02X", command_code), "Command Code");
	
	PLReservedCheck( 24 );
	
	# Add 512 byte data to decode as data cell as ATA IDENTIFY DEVICE data or ATA IDENTIFY PACKET DEVICE data
	
	if (in.DataLength - GetBitOffset() / 8 >= 512) 
    {         
        ShowDataBlockReOrder(512);
    }
}

DoPageCode_90_91()
{
	AddDecSeparator();
	FieldColor = CDB_Inquiry_Color;
	
	if( PageCode == 0x90 )
		AddCaptionCell("  INQUIRY  ", "Response", "Protocol Specific Logical Unit Information VPD page", _MONOCOLOR); 
	else if( PageCode == 0x91 )	
		AddCaptionCell("  INQUIRY  ", "Response", "Protocol Specific Port Information VPD page", _MONOCOLOR); 
    
	PQ = NextNBits_(3);
	AddPayLoadCell("PQ", Format ("%d",PQ), "Peripheral Qualifier");
	DevType = NextNBits_(5);
	AddPayLoadCell("Dev Typ", Format ("0x%02X", DevType), "Peripheral Device Type");
	
	page_code = NextNBits_(8); 
	AddPayLoadCell("Page Code", Format ("0x%02X", page_code), "Page Code");
	
	page_length = NextNBits_(16); 
	AddSimplePLCell("Page Length", Format ("0x%04X", page_length), "Page Length.");
			
	while( page_length > 0)
	{
		relative_port_identifier = NextNBits_(16);
		tooltip    = "";
		select
		{
			relative_port_identifier == 0x00 :   { tooltip += "Reserved";}
			relative_port_identifier == 0x01 :   { tooltip += "Relative port 1, historically known as port A"; }
			relative_port_identifier == 0x02 :   { tooltip += "Relative port 2, historically known as port B"; }
			default     :						 { tooltip += "Relative port 3 through 65 535"; }	
		};
		AddSimplePLCell("Relative Port Identifier", Format ("0x%04X", relative_port_identifier ), tooltip);
		
		PLReservedCheck( 4 );
		pro_id = NextNBits_(4);
		AddSimplePLCell("Protocol Id", Format ("%d", pro_id ), "Protocol Identifier");
		
		PLReservedCheck( 24 );
		
		proto_data_length = NextNBits_(16);
		AddSimplePLCell("Protocol Data Len", Format ("0x%04X", proto_data_length ), "Protocol Specific Data Length");
		
		if( proto_data_length > 0 )		
		{
			str = "0x";
			for (i = 0; i < proto_data_length; i++ )
			{
				val = NextNBits_(8);
				str += Format(" %02X", val);
			}
		
			if( PageCode == 0x90 )
				AddSimplePLCell("LUN Specific Data", str, "Per logical unit SCSI transport protocol specific data");
			else if( PageCode == 0x91 )			
				AddSimplePLCell("Shared Specific Data", str, "Shared SCSI transport protocol specific data");
		}
		
		page_length = page_length - (proto_data_length + 8 );
	}	
}

DoPageCode_b0()
{
	AddDecSeparator();
	FieldColor = CDB_Inquiry_Color;
	AddCaptionCell("  INQUIRY  ", "Response", "Block Limits VPD page", _MONOCOLOR); 
    
	PQ = NextNBits_(3);
	AddPayLoadCell("PQ", Format ("%d",PQ), "Peripheral Qualifier");
	DevType = NextNBits_(5);
	AddPayLoadCell("Dev Typ", Format ("0x%02X", DevType), "Peripheral Device Type");
	
	page_code = NextNBits_(8); 
	AddPayLoadCell("Page Code", Format ("0x%02X", page_code), "Page Code");
	
	PLReservedCheck( 8 );
	
	page_length = NextNBits_(8); 
	AddSimplePLCell("Page Length", Format ("0x%02X", page_length), "Page Length.");
	
	PLReservedCheck( 16 );
	
	optimal_transfer_length_granularity = NextNBits_(16); 
	AddSimplePLCell("Optimal Trans Len Granularity", Format ("0x%04X", optimal_transfer_length_granularity), "Optimal Transfer Length Granularity.");
	
	maximum_transfer_length = NextNBits_(32); 
	AddSimplePLCell("Max Trans Len", Format ("0x%08X", maximum_transfer_length), "Maximum Transfer Length");
	
	optimal_transfer_length = NextNBits_(32); 
	AddSimplePLCell("Optimal Trans Len", Format ("0x%08X", optimal_transfer_length), "Optimal Transfer Length");
	
	max_prefetch_trans_len = NextNBits_(32); 
	AddSimplePLCell("Max Prefetch Trans Len", Format ("0x%08X", max_prefetch_trans_len), "Maximum Prefetch Xdread Xdwrite Transfer Length");
}

DoPageCode_b1()
{
	AddDecSeparator();
	FieldColor = CDB_Inquiry_Color;
	AddCaptionCell("  INQUIRY  ", "Response", "Block Limits VPD page", _MONOCOLOR); 
    
	PQ = NextNBits_(3);
	AddPayLoadCell("PQ", Format ("%d",PQ), "Peripheral Qualifier");
	DevType = NextNBits_(5);
	AddPayLoadCell("Dev Typ", Format ("0x%02X", DevType), "Peripheral Device Type");
	
	page_code = NextNBits_(8); 
	AddPayLoadCell("Page Code", Format ("0x%02X", page_code), "Page Code");
	
	PLReservedCheck( 8 );
	
	page_length = NextNBits_(8); 
	AddSimplePLCell("Page Length", Format ("0x%02X", page_length), "Page Length.");
	
	medium_rotation_rate = NextNBits_(16); 
	AddSimplePLCell("Medium Rotation Rate", Format ("0x%04X", medium_rotation_rate), "Medium Rotation Rate.");
	
	PLReservedCheck( 8 );
	
	PLReservedCheck( 4 );
	
	nominal_form_factor = NextNBits_(4); 
	AddSimplePLCell("Nominal Factor", Format ("0x%01X", nominal_form_factor), "Nominal Form Factor.");
	
	PLReservedCheck( 32 );
	PLReservedCheck( 32 );
	PLReservedCheck( 32 );
	PLReservedCheck( 32 );
	PLReservedCheck( 32 );
	PLReservedCheck( 32 );
	PLReservedCheck( 32 );
	PLReservedCheck( 32 );
	PLReservedCheck( 32 );
	PLReservedCheck( 32 );
	PLReservedCheck( 32 );
	PLReservedCheck( 32 );
	PLReservedCheck( 32 );
	PLReservedCheck( 32 );
	
}
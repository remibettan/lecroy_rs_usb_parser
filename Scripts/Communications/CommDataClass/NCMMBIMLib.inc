#*******************************************************************************
#
#  FILENAME: NCMLib.inc
#
#  Copyright (c) 2012, LeCroy - All Rights Reserved
#
#  DESCRIPTION
#    This is the request file for USB Class Definition for Communication Devices subclass NCM. 
#    This file is prepared as per the USB Class Definitions for Communication Devices v1.1 subclass NCM
#
#  REVISION HISTORY
#
#*******************************************************************************

%include "CATCScriptAPI.inc"   
%include "UsbCommon.inc"  

const Tabular_Def_Table = Map(
[
    #-----------------------------------------------------------------------------------------------------
    #       id            ,      colId                          , 		containerCellId
    #-----------------------------------------------------------------------------------------------------
    [ CELL_REQUEST        , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE   , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ CELL_WVALUE         , TABULAR_SCRIPT_COLUMN_ID_NONE      , TABULAR_SCRIPT_CONTAINER_CELL_ID_MISC ]

] );
#############################################################################
#                               View Settings                               #
#############################################################################
#
#    In this section user can set up which fields are to be shown and
#    which are to be hidden in expanded and collapsed states.
#    Zero-value everywhere means that fields will not be shown,
#    otherwise means opposite.
#


# ----------------------- All Field View Settings ---------------------------
#   These settings have priority above separate field View Settings in
#   expanded state ONLY.
#   In order separate field View Settings to work properly
#   BOTH All Field View Settings should be set to 0.
#
#   Due to the fact that ViewAll-setting and HideAll-setting are
#   exceptive propositions - ViewAll has been set a higher priority.
# ---------------------------------------------------------------------------

const NCM_ViewAll  = 0;
const NCM_HideAll  = 0;
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
# i.e.  const RPD_Field = [0, 1]# - means that field 'Field' will be hidden
# in collapsed state and will be shown in expanded state.
#

#                            [collapsed, expanded]


#[ ID, Offset, Len, Name, ValueFormat, Tooltip ]
set NCM16_Fields = Map( 
[
	["NTHSig16", 				0, 	4, "dwSignature", 	"0x%04X", 	"Signature of the 16 Bit NTH"],
	["wHeaderLength16",			4, 	2, "wHeaderLength",	"%d", 	 	"Size in bytes of NTH structure"],
	["wSequence16", 			6, 	2, "wSequence",		"%d",  	 	"Sequence number"],
	["wBlockLength16", 			8, 	2, "wBlockLength",	"%d",  	 	"Size of NTB in bytes"],
	["wNdpIndex16", 			10, 2, "wNdpIndex",		"0x%02X", 	"Offset of the first NDP from byte zero of the NTB."],

	["NDPSig16", 				0, 	4, "dwSignature",	"0x%04X", 	"Signature of 16 Bit NDP"],
	["MBIMSignature16", 		0, 	3, "Signature",		"0x%03X", 	"Signature of 16 Bit NDP"],
	["MBIMSessionID16", 		3, 	1, "SessionID",		"%d", 	 	"Session ID"],	
	["wLength16",				4, 	2, "wLength",		"%d", 	 	"Size in bytes of this NDP structure"],
	["wNextNdpIndex16", 		6, 	2, "wNextNdpIndex",	"0x%02X", 	"Reserved for use as a link to the next NDP in the NTB"],
	["FirstDataIndex16",		8, 	2, "Index",			"0x%02X", 	"wDatagramIndex"],
	["FirstDataLength16", 		10, 2, "Length",		"%d", 	 	"wDatagramLength"],
	
	["NTHSig32", 				0, 	4, "dwSignature", 	"0x%04X", 	"Signature of the 32 Bit NTH"],
	["wHeaderLength32",			4, 	2, "wHeaderLength",	"%d", 	 	"Size in bytes of NTH structure"],
	["wSequence32", 			6, 	2, "wSequence",		"%d",  	 	"Sequence number"],
	["dwBlockLength32", 		8, 	4, "dwBlockLength",	"%d",  	 	"Size of NTB in bytes"],
	["dwNdpIndex32", 			12, 4, "dwNdpIndex",	"0x%04X", 	"Offset of the first NDP from byte zero of the NTB."],

	["NDPSig32", 				0, 	4, "dwSignature",	"0x%04X", 	"Signature of 32 Bit NDP"],
	["MBIMSignature32", 		0, 	3, "Signature",		"0x%03X", 	"Signature of 32 Bit NDP"],
	["MBIMSessionID32", 		3, 	1, "SessionID",		"%d", 	 	"Session ID"],	
	["wLength32",				4, 	2, "wLength",		"%d", 	 	"Size in bytes of this NDP structure"],
	["wReserved6", 				6, 	2, "wReserved6",	"0x%02X", 	"Reserved for future use"],
	["dwNextNdpIndex32", 		8, 	4, "dwNextNdpIndex","0x%04X", 	"Reserved for use as a link to the next NDP in the NTB"],
	["dwReserved12", 			12,	4, "dwReserved12",	"0x%04X", 	"Reserved for future use"],
	["FirstDataIndex32",		16,	4, "Index",			"0x%04X", 	"wDatagramIndex"],
	["FirstDataLength32", 		20, 4, "Length",		"%d", 	 	"wDatagramLength"]
	
] );

ProcessNCMData()
{
    CommonDecoderInit();
    UnitDecoderInit("NCM");
    FieldColor = 0x76A8F4;
  
	if (in.DataLength < 4)
    {
        AddCell("Error", "Illegal Length", "Length has to be at least 4 to be decoded", 0x0000FF);
        return Complete();
    }
    
	dwSignature = GetDataLong(base);
		
	if ( dwSignature == 0x484D434E )
	    DecodeNCM16_Data();
	else if ( dwSignature == 0x686D636E )
		DecodeNCM32_Data();
	else
	{
		AddCell("Error", "Illegal NTH Signature", "NTH signature should be 0x484D434E or 0x686D636E for NCM", 0x0000FF);
		return Complete();
	}
	
    out.Decoded = in.DataLength;
    
    return Complete();
}

ProcessMBIMData()
{
    CommonDecoderInit();
    UnitDecoderInit("MBIM");
    FieldColor = 0x76A8F4;
    
    if (in.DataLength < 4)
    {
		AddCell("Error", "Illegal Length", "Length has to be at least 4 to be decoded", 0x0000FF);
        return Complete();
    }
    
	dwSignature = GetDataLong(base);
	
	if ( dwSignature == 0x484D434E )
	    DecodeNCM16_Data();
	else if ( dwSignature == 0x686D636E )
		DecodeNCM32_Data();
	else
	{
		AddCell("Error", "Illegal NTH Signature", "NTH signature should be 0x686D636E or 0x484D434E for MBIM", 0x0000FF);
		return Complete();
	}
	
    out.Decoded = in.DataLength;
    
    return Complete();
}

####################################################################################################
#											16 Bit functions									   #
####################################################################################################

DecodeNCM16_Data()
{
	GetNBits(in.Data, 0, 0);

	RetValues = GetNCMFieldData("NTHSig16", 0);
	if( RetValues[0] == 0 ) return 0;	
	dwSignature = RetValues[1];	

	if( dwSignature != 0x484D434E )
		return 0;
	
	AddSeparator();
	SetCellColor(0x349933);
	AddCaptionCell("NTH16","NTH16","16 Bit NCM Transfer Header", _MONOCOLOR, _MONOFIELD);
	RestoreCellColor();
	AddSeparator();        
		
    if(SimpleShowItem())
    {		
		AddNCMField("NTHSig16", 0);
		AddNCMField("wHeaderLength16", 0);
	}
	
	AddNCMField("wSequence16", 0);

    if(SimpleShowItem())
    {		
		AddNCMField("wBlockLength16", 0);
		
		RetValues = AddNCMField("wNdpIndex16", 0);
		wNdpIndex = RetValues[1];
	}
	else
	{
		RetValues = GetNCMFieldData("wNdpIndex16", 0);
		wNdpIndex = RetValues[1];	
	}
	
		
	if( wNdpIndex == 0 )
		return 0;

	offset = wNdpIndex;
	while( offset != 0 )
	{	
		RetValues = GetNCMFieldData("NDPSig16", offset);

		if( RetValues[0] == 0 ) return 0;	
		dwSignature = RetValues[1];	

		if( Prefix == "NCM" )
		{	
			if( dwSignature != 0x304D434E && dwSignature != 0x314D434E )
			{
				AddCell("Error", "Illegal NDP Signature", "NDP signature should be 0x314D434E or 0x304D434E for 16 bit NCM", 0x0000FF);
				return 0;
			}

			DataName = "Datagram";					
		}			
		else if( Prefix == "MBIM" )
		{
			MBIMSessionID = dwSignature > 24;
			MBIMSignature = dwSignature & 0x00FFFFFF ;
			
			if( MBIMSignature != 0x00535049 && MBIMSignature != 0x00535344 ) # IPS<SessionID> or DSS<SesssionID>
			{
				AddCell("Error", "Illegal NDP Signature", "NDP signature should be 0x535049 or 0x535344 for 16 bit MBIM", 0x0000FF);
				return 0;
			}
				
			if( MBIMSignature == 0x00535049 )
				DataName = "IPS";
			else if( MBIMSignature == 0x00535344 )
				DataName = "DSS";				
		}

		AddSeparator();
		SetCellColor(0x349933);
		AddCaptionCell("NDP16","NDP16","16 Bit NCM Datagram Pointer", 0x349933, _MONOFIELD, _SHOWN);
		RestoreCellColor();
		AddSeparator();        
		
		if(SimpleShowItem())
		{
			if( Prefix == "NCM" )
			{					
				AddNCMField("NDPSig16", offset);			
			}
			else if( Prefix == "MBIM" )
			{			
				AddNCMField("MBIMSignature16", offset);				
				AddNCMField("MBIMSessionID16", offset);									
			}
			
			RetValues = AddNCMField("wLength16", offset);				
			wLength = RetValues[1];
			
			RetValues = AddNCMField("wNextNdpIndex16", offset);				
			wNextNdpIndex = RetValues[1];			
		}
		else
		{
			RetValues = GetNCMFieldData("wLength16", offset);				
			wLength = RetValues[1];
		
			RetValues = GetNCMFieldData("wNextNdpIndex16", offset);				
			wNextNdpIndex = RetValues[1];		

		}

		DecodeNCM16_NDP_Datagrams(offset, wLength, DataName);	

		offset = wNextNdpIndex;		
	}

	return 1;
}

DecodeNCM16_NDP_Datagrams(offset, wLength, caption)
{
	count = (wLength - 8) / 4;

	for(cnt = 0; cnt < count; cnt++)
	{
		AddSeparator();
		if( cnt < count - 1)
			AddCell( Format(caption + " %d",  cnt), null, null, 0x3668b4, _MONOFIELD);

		if(SimpleShowItem())
		{						
			RetValues = AddNCMField("FirstDataIndex16", offset + cnt * 4);
			if( !RetValues[0] ) return 0;		
			datagram_index = RetValues[1];
			
			RetValues = AddNCMField("FirstDataLength16", offset + cnt * 4);				
			if( !RetValues[0] ) return 0;		
			datagram_length = RetValues[1];
			
			if( datagram_index != 0 )
			{
				GetNBits(in.Data, datagram_index * 8, 0);

				SetFieldOffsetLen(datagram_index * 8, datagram_length * 8);						
				ShowDataBlockReOrder(datagram_length);
				
				GetNBits(in.Data, 0, 0);
			}
		}
	}
	
	return 1;
}

####################################################################################################
#											32 Bit functions									   #
####################################################################################################

DecodeNCM32_Data()
{
	GetNBits(in.Data, 0, 0);
	
	RetValues = GetNCMFieldData("NTHSig32", 0);
	if( RetValues[0] == 0 ) return 0;	
	dwSignature = RetValues[1];	

	if( dwSignature != 0x686D636E )
		return 0;
	
	AddSeparator();
	SetCellColor(0x349933);
	AddCaptionCell("NTH32","NTH32","32 Bit NCM Transfer Header", _MONOCOLOR, _MONOFIELD);
	RestoreCellColor();
	AddSeparator();        
		
    if(SimpleShowItem())
    {		
		AddNCMField("NTHSig32", 0);
		AddNCMField("wHeaderLength32", 0);
	}
	
	AddNCMField("wSequence32", 0);
	
    if(SimpleShowItem())
    {		
		AddNCMField("dwBlockLength32", 0);
		
		RetValues = AddNCMField("dwNdpIndex32", 0);
		dwNdpIndex = RetValues[1];
	}
	else
	{
		RetValues = GetNCMFieldData("dwNdpIndex32", 0);
		dwNdpIndex = RetValues[1];	
	}
	
	if( dwNdpIndex == 0 )
		return 0;
	
	offset = dwNdpIndex;	
	while( offset != 0 )
	{	
		RetValues = GetNCMFieldData("NDPSig32", offset);

		if( RetValues[0] == 0 ) return 0;	
		dwSignature = RetValues[1];	
		
		if( Prefix == "NCM" )
		{
			if( dwSignature != 0x306D636E && dwSignature != 0x316D636E )
			{
				AddCell("Error", "Illegal NDP Signature", "NDP signature should be 0x316D636E or 0x306D636E for 32 bit NCM", 0x0000FF);
				return 0;
			}
				
			DataName = "Datagram";						
		}			
		else if( Prefix == "MBIM" )
		{
			MBIMSessionID = dwSignature > 24;
			MBIMSignature = dwSignature & 0x00FFFFFF ;
			
			# Signature is ips<SessionID> or dss<SesssionID>
			if( MBIMSignature != 0x00737069 && MBIMSignature != 0x00737364 ) 
			{
				AddCell("Error", "Illegal NDP Signature", "NDP signature should be IPS or DSS for 32 bit MBIM", 0x0000FF);
				return 0;
			}
				
			if( MBIMSignature == 0x00535049 )
				DataName = "IPS";
			else if( MBIMSignature == 0x00535344 )
				DataName = "DSS";							
		}
		
		AddSeparator();
		SetCellColor(0x349933);
		AddCaptionCell("NDP32","NDP32","32 Bit NCM Datagram Pointer", 0x349933, _MONOFIELD, _SHOWN);
		RestoreCellColor();
		AddSeparator();        
		
		if(SimpleShowItem())
		{				
			if( Prefix == "NCM" )
			{						
				AddNCMField("NDPSig32", offset);			
			}
			else if( Prefix == "MBIM" )
			{			
				AddNCMField("MBIMSignature32", offset);				
				AddNCMField("MBIMSessionID32", offset);									
			}
			
			RetValues = AddNCMField("wLength32", offset);				
			wLength = RetValues[1];
			
			AddNCMField("wReserved6", offset);		
			
			RetValues = AddNCMField("dwNextNdpIndex32", offset);						
			dwNextNdpIndex = RetValues[1];
			
			AddNCMField("dwReserved12", offset);		
		}
		else
		{
			RetValues = GetNCMFieldData("wLength32", offset);				
			wLength = RetValues[1];
		
			RetValues = GetNCMFieldData("dwNextNdpIndex32", offset);						
			dwNextNdpIndex = RetValues[1];		
		}
		
		DecodeNCM32_NDP_Datagrams(offset, wLength, DataName);	
		
		offset = dwNextNdpIndex;		
	}

	return 1;
}

DecodeNCM32_NDP_Datagrams(offset, wLength, caption)
{
	count = (wLength - 16) / 8;

	for(cnt = 0; cnt < count; cnt++)
	{
		AddSeparator();
		if( cnt < count - 1)
			AddCell(Format(caption + " %d", cnt), null, null, 0x3668b4, _MONOFIELD);

		if(SimpleShowItem())
		{
			RetValues = AddNCMField("FirstDataIndex32", offset + cnt * 8);
			if( !RetValues[0] ) return 0;
			datagram_index = RetValues[1];
							
			RetValues = AddNCMField("FirstDataLength32", offset + cnt * 8);
			if( !RetValues[0] ) return 0;
			datagram_length = RetValues[1];
						
			if( datagram_index != 0 )
			{
				GetNBits(in.Data, datagram_index * 8, 0);

				SetFieldOffsetLen(datagram_index * 8, datagram_length * 8);
				ShowDataBlockReOrder(datagram_length);
				
				GetNBits(in.Data, 0, 0);
			}
		}
	}
	
	return 1;
}

####################################################################################################
#											Utility functions									   #
####################################################################################################

AddNCMField(FieldId, offset)
{
		ReturnValues[0] = 0;
		ReturnValues[1] = 0;

		_row = Find(NCM16_Fields, FieldId);
											
		offset 		= _row[1] + offset;
		len 		= _row[2];
		name 		= _row[3];
		valueformat	= _row[4];
		tooltip 	= _row[5];		
		valuearray  = _row[6];
		value 		= 0;
	
		if( offset + len > in.DataLength ) return ReturnValues;
		
		if(len == 1)
		{
			value = GetDataByte(offset);
		}
		else if(len == 2)
		{		
			value = GetDataWord(offset);
		}
		else if(len == 3)		
		{
			value = GetDataLong(offset);
			value &= 0x00FFFFFF;
		}	
		else if(len == 4)		
		{
			value = GetDataLong(offset);
		}
		else
		{
			value = GetDataByteArray(offset, len);
			value = GetArrayHexString(value);			
		}

		ReturnValues[0] = 1;		
		ReturnValues[1] = value;

		if(valuearray != null)
        {        
            if( isvaluebitmap == 1 )
            {
                strvalues = "";
                for( i = 0; i < len * 8; i++ )
                {                
                    maskedvalue = value & (1 << i);
                    if( maskedvalue )
                    {
                        if( strvalues != "" )
                            strvalues += ", ";
                    
                        _names = Find(valuearray, maskedvalue);
                        if(_names != null)
                            strvalues += Format( valueformat, _names[1] );    
                        else 
                            strvalues += Format( valueformat, Format("0x%04x", maskedvalue) );    
                    }
                }
    
                value = strvalues;
            }
            else
            {
                _names = Find(valuearray, value);            
                if(_names != null)
                    value = _names[1];
                else 
                    value = Format("0x%x", value);
            }

        }
		AddPayLoadCell(name, Format(valueformat, value), tooltip);
				
		return ReturnValues;
}

GetNCMFieldData(FieldId, offset)
{
		ReturnValues[0] = 0;
		ReturnValues[1] = 0;

		_row = Find(NCM16_Fields, FieldId);

		offset 	= _row[1] + offset;
		len 	= _row[2];
		value 	= 0;

		if( offset + len > in.DataLength ) return ReturnValues;
	
		if(len == 1)
			value = GetDataByte(offset);
		else if(len == 2)		
			value = GetDataWord(offset);
		else if(len == 3)		
		{
			value = GetDataLong(offset);
			value &= 0x00FFFFFF;
		}	
		else if(len == 4)		
			value = GetDataLong(offset);
		else 
		{
			value = GetDataByteArray(offset, len);
		}
		
		ReturnValues[0] = 1;
		ReturnValues[1] = value;
		
		return ReturnValues;
}

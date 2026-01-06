
#const IRDA_descriptor_type = 0x21; # OK
const IRDA_descriptor_type = 0x21;



set sizeOf_b = 1;
set CurrentIndex = 0;
set ReportData = 0;
set ReportUsagePage = 0;


DataAvailable(decoded)
{
    return (in.DataLength - decoded);
}


set IrDA_DescriptorsTypeTabe =
[
   [ 0xFF,                  "Illegal"                    ,"Illegal_sub"     ],
   [ IRDA_descriptor_type,  "IrDA_DESCRIPTOR"            ,"IrDA_class_sub"  ]
];

TryIrDA_Descriptors(bDescriptorType)
{
   
   AddPayLoadCell("bDescriptorType", Format("0x%02X", bDescriptorType), "For Debug", _WARNING);

   _row_dt = Find (IrDA_DescriptorsTypeTabe, bDescriptorType);
 
   AddPayLoadCell("Descriptor", _row_dt[1], "For Debug", _WARNING);
  
   bLengh = 0;
   CurrentByteOffset = 0; 

   if (_row_dt[0] == 0xFF) 
       return 0;
   Call (_row_dt[1]);
   return 1;   
}



DecodeIrDADescriptor()
{
    # let's set the class-specific table 
    # wValue = GetDataWord(CurrentIndex); CurrentIndex = CurrentIndex + sizeOf_w;
    # wIndex = GetDataWord(CurrentIndex); CurrentIndex = CurrentIndex + sizeOf_w;


    ####### copied from do_descriptor()

	CurrentByteOffset = 0;

    if(wValue != 0x00)
    {
        AddPayLoadCell("Invalid wValue", Format("Error: 0x%02X", wValue), "Expected wValue for IrDA Bridge: 0x00", _ERROR);
        #return 0;
    }

    descriptor_type = IRDA_descriptor_type;

    
    #--------------------- Descriptors ----------------------------

    AddPayLoadCell("Start", "IrDA Bridge", "For Debug", _WARNING);

    SaveOffset();    
    FieldColor = wDescriptorColor;
    InitText();
    #AddLineOfText("From do_descriptor()");
    DescriptorCellString = "N/A";
    UsbDescTooltipStr = DoIrDADescriptors(descriptor_type, 1);

    SetFieldOffsetLen( B_offset, GetBitOffset() - B_offset );
    
    # Use simple AddCell() function here because we don't want to send this cell
    # information to dialog view. 
    # All the discriptors information for dialog view is provided
    # by DoIrDADescriptors() function.
    AddCell("Descriptors", DescriptorCellString, "");    

}


DoIrDADescriptors( descriptor_type, is_tooltip ) # copied from DoStandardDescriptors()
{
    if(descriptor_type != IRDA_descriptor_type)
    {
        AddPayLoadCell("Descriptor Type", Format("Error: 0x%02X", wValue), Format("Expected Descriptor Type for IrDA Bridge: 0x%02X", IRDA_descriptor_type), _ERROR);
        return 0;
    }


    InitText();
    
    if( in.DataLength == 8 ) bad_data = 1;
    else                     bad_data = 0; 
    
    if( in.PrepareFldsForDlg )
    {        
        IsTooltip = 0;
        
        Global_BitField_offset = REQ_DATA_OFFSET;
        CurrentFldInit();
        
        EntryBaseOffset    = 0;
        EntryFieldGroupLen = 0;        
    }
    else
    {
        IsTooltip = is_tooltip;        
    }
    
    _row_sd = _row_sd = Find( IrDA_DescriptorsTypeTabe, descriptor_type );  # will determine which request is being used
    #_row_sd = [ IRDA_descriptor_type, "IrDA_DESCRIPTOR", "IrDA_class_sub"];
    
    if( bad_data )
    {
        if( in.PrepareFldsForDlg )
        {
            AddStringToDlg( "Not enough data to decode descriptor(s).", "", "", _ERROR ); 
            return null;
        }
        else
        {
            str = "";
            
            if( _row_sd[0] != 0xFF )
            {
                DescriptorCellString = _row_sd[1] + " Descriptor";
                
                str  = Format( "Data stage : %d bytes", in.DataLength );
                str += "\n--------------------------------------------\n";
                str += DescriptorCellString + "\n\n";
                
            }
                
            return str + "Not enough data to decode descriptor(s).";
        }     
    }
    
    
    MaxDataBytes = in.DataLength - 8;
    
    if( _row_sd[0] != 0xFF )
    {            
        standard_desc_string = Call (_row_sd[1]); # Will call IrDA_DESCRIPTOR()
        return standard_desc_string;
    }
    else
    {
        return "No Descriptor Match";
    }
}  



IrDA_DESCRIPTOR()
{
    #AddPayLoadCell("IrDA_DESCRIPTOR", "Function called", "For Debug", _WARNING);

    bLengh = 0;
    CurrentByteOffset = 0;

    DescriptorCellString = "IrDA Bridge Class Specific";     
    AddDataHeader( "IrDA Bridge Descriptor", in.DataLength - 8 );
    IrDA_class_sub();
    return GetFinalText();  
}



IrDA_class_sub()
{    
    #AddPayLoadCell("IrDA_class_sub", "Function called", "For Debug", _WARNING);


	#~~~~~~ Field 1 [bLength] ~~~~~~
    bLength         = GetDataByte( Base + CurrentByteOffset );   
    AddByteEntry( "bLength", "Length of descriptor. It must be at least 12 bytes.", 0);   
    # IncCurrByteOffset() is called by AddByteEntry()


	#~~~~~~ Field 2 [bDescriptorType] ~~~~~~
    bDescriptorType = GetDataByte( Base + CurrentByteOffset );      
    _row = Find (DescriptorTypeTable, bDescriptorType);
	temp_str = GetDescriptorTypeString(_row[1]);
	if(_row[0] == 0xFF)
		temp_str += Format(". Expected: 0x%02X", IRDA_descriptor_type);
    AddByteEntry( "bDescriptorType", temp_str, 0);
    # IncCurrByteOffset() is called by AddByteEntry()


	#~~~~~~ Field 3 [bcdSpecRevision] ~~~~~~
    bcdSpecRevision = GetDataWord( Base + CurrentByteOffset );      
    AddEntry( CurrentByteOffset, "bcdSpecRevision", bcdSpecRevision, 4, "Revision of USB-IrDA Bridge Specification:", 0);
    AddDescriptionOnly( FormatEx( "version %X.%02X", (bcdSpecRevision & 0xFF00)>> 8, bcdSpecRevision & 0xFF) );
    AddFieldBreak();
	IncCurrByteOffset(2);


	#~~~~~~ Field 4 [bmDataSize] ~~~~~~
    bmDataSize      = GetDataByte( Base + CurrentByteOffset);
    AddEntry( CurrentByteOffset, "bmDataSize", bmDataSize, 2, "The maximum number of bytes allowed in any frame", 0);
    AddDescriptionOnly( "for the duration of the connection." );
    AddDescriptionOnly( "See IrLAP Specification." );
    AddDescriptionOnly( GetDataSizeString(bmDataSize) );
    AddFieldBreak();
	IncCurrByteOffset(1);


	#~~~~~~ Field 5 [bmWindowSize] ~~~~~~
    bmWindowSize     = GetDataByte( Base + CurrentByteOffset );
    AddEntry( CurrentByteOffset, "bmWindowSize", bmWindowSize, 2, "The maximum number of unacknowledged IrDA frames that", 0);
    AddDescriptionOnly( "can be received before an acknowledgement is sent." );
    AddDescriptionOnly( "See IrLAP Specification for details." );
    AddDescriptionOnly( GetWindowSizeString(bmWindowSize) );
    AddFieldBreak();
	IncCurrByteOffset(1);


	#~~~~~~ Field 6 [bmMinTurnaroundTime] ~~~~~~
    bmMinTurnaroundTime  = GetDataByte( Base + CurrentByteOffset );
    AddEntry( CurrentByteOffset, "bmMinTurnaroundTime", bmMinTurnaroundTime, 2, "The length of time in microseconds required for recovery", 0);
    AddDescriptionOnly( "time between the moment the device stops transmitting" );
    AddDescriptionOnly( "on the infrared media and the moment it is capable of receiving." );
    AddDescriptionOnly( "See IrLAP Specification for details." );
    AddDescriptionOnly( GetMinTurnaroundTimeString(bmMinTurnaroundTime) );
    AddFieldBreak();
	IncCurrByteOffset(1);


	#~~~~~~ Field 7 [wBaudRate] ~~~~~~
    wBaudRate  = GetDataWord( Base + CurrentByteOffset );
    AddEntry( CurrentByteOffset, "wBaudRate", wBaudRate, 4, "The length of time in microseconds required for recovery", 0);
    AddDescriptionOnly( "time between the moment the device stops transmitting" );
    AddDescriptionOnly( "on the infrared media and the moment it is capable of receiving." );
    AddDescriptionOnly( "See IrLAP Specification for details." );
    AddDescriptionOnly( GetBaudRateString(wBaudRate) );
    AddFieldBreak();
	IncCurrByteOffset(2);


	#~~~~~~ Field 8 [bmAdditionalBOFs] ~~~~~~
    bmAdditionalBOFs  = GetDataByte( Base + CurrentByteOffset );
    AddEntry( CurrentByteOffset, "bmAdditionalBOFs", bmAdditionalBOFs, 2, "The number of extra BOFs to be added to a frame for", 0);
    AddDescriptionOnly( "proper reception at 115,200 bps. If the Device does not" );
    AddDescriptionOnly( "support speeds at or below 115,200 bps this field shall be zero (0)." );
    AddDescriptionOnly( "See IrLAP Specification for details." );
    AddDescriptionOnly( GetAdditionalBOFsString(bmAdditionalBOFs) );
    AddFieldBreak();
	IncCurrByteOffset(1);


	#~~~~~~ Field 9 [bIrDARateSniff] ~~~~~~
    bIrDARateSniff  = GetDataByte( Base + CurrentByteOffset );
    AddEntry( CurrentByteOffset, "bIrDARateSniff", bIrDARateSniff, 2, "This field shall be one (1) if the Device can dynamically", 0);
    AddDescriptionOnly( "accept frames transmitted at any speed. This field shall" );
    AddDescriptionOnly( "be zero (0) if the Device can only accept frames" );
    AddDescriptionOnly( "transmitted at a pre-specified speed." );
    AddDescriptionOnly( GetIrDARateSniffString(bIrDARateSniff) );
    AddFieldBreak();
	IncCurrByteOffset(1);


	#~~~~~~ Field 10 [bMaxUnicastList] ~~~~~~
    bMaxUnicastList  = GetDataByte( Base + CurrentByteOffset );
    AddEntry( CurrentByteOffset, "bMaxUnicastList", bMaxUnicastList, 2, "The maximum number of addresses that can be", 0);
    AddDescriptionOnly( "specified in a class-specific Set IrDA Unicast List" );
    AddDescriptionOnly( "request. If the device does not support the capability of" );
    AddDescriptionOnly( "filtering valid frames by their addresses, this field shall" );
    AddDescriptionOnly( "be set to zero (0)." );
    AddFieldBreak();
	IncCurrByteOffset(1);


    return 1;  
}


#// Field 4
GetDataSizeString(bmDataSize)
{
    str = "Max Data Size: ";

    if (bmDataSize & 0b00100000) # D5
	   return (str + "2048 bytes");

    if (bmDataSize & 0b00010000) # D4
	   return (str + "1024 bytes");

    if (bmDataSize & 0b00001000) # D3
	   return (str + "512 bytes");

    if (bmDataSize & 0b00000100) # D2
	   return (str + "256 bytes");

    if (bmDataSize & 0b00000010) # D1
	   return (str + "128 bytes");

    if (bmDataSize & 0b00000001) # D0
	   return (str + "64 bytes");

    return (str + "Unknown! [Note: D7..6 are Reserved (must be zero)]");
}


#// Field 5
GetWindowSizeString(bmWindowSize)
{
    str = "Window Size: ";

    if (bmWindowSize & 0b01000000) # D6
	   return (str + "7 Frames");

    if (bmWindowSize & 0b00100000) # D5
	   return (str + "6 Frames");

    if (bmWindowSize & 0b00010000) # D4
	   return (str + "5 Frames");

    if (bmWindowSize & 0b00001000) # D3
	   return (str + "4 Frames");

    if (bmWindowSize & 0b00000100) # D2
	   return (str + "3 Frames");

    if (bmWindowSize & 0b00000010) # D1
	   return (str + "2 Frames");

    if (bmWindowSize & 0b00000001) # D0
	   return (str + "1 Frame");

    return (str + "Unknown! [Note: D7 is Reserved (must be 0)]");
}


#// Field 6
GetMinTurnaroundTimeString(bmMinTurnaroundTime)
{
    str = "Min Turnaround Time: ";

    if (bmMinTurnaroundTime & 0b10000000) # D7
	   return (str + "0 ms");

    if (bmMinTurnaroundTime & 0b01000000) # D6
	   return (str + "0.01 ms");

    if (bmMinTurnaroundTime & 0b00100000) # D5
	   return (str + "0.05 ms");

    if (bmMinTurnaroundTime & 0b00010000) # D4
	   return (str + "0.1 ms");

    if (bmMinTurnaroundTime & 0b00001000) # D3
	   return (str + "0.5 ms");

    if (bmMinTurnaroundTime & 0b00000100) # D2
	   return (str + "1 ms");

    if (bmMinTurnaroundTime & 0b00000010) # D1
	   return (str + "5 ms");

    if (bmMinTurnaroundTime & 0b00000001) # D0
	   return (str + "10 ms");

    return (str + "Unknown!");
}


#// Field 7
GetBaudRateString(wBaudRate)
{
    str = "IrDA Baud Rate: ";

    if (wBaudRate & 0b0000000100000000) # D8
	   return (str + "4 Mbps");

    if (wBaudRate & 0b10000000) # D7
	   return (str + "1.152 Mbps");

    if (wBaudRate & 0b01000000) # D6
	   return (str + "576,000 bps");

    if (wBaudRate & 0b00100000) # D5
	   return (str + "115,200 bps");

    if (wBaudRate & 0b00010000) # D4
	   return (str + "57,600 bps");

    if (wBaudRate & 0b00001000) # D3
	   return (str + "38,400 bps");

    if (wBaudRate & 0b00000100) # D2
	   return (str + "19,200 bps");

    if (wBaudRate & 0b00000010) # D1
	   return (str + "9,600 bps");

    if (wBaudRate & 0b00000001) # D0
	   return (str + "9,600 bps");

    return (str + "Unknown! [Note: D15..D9 are Reserved (must be zero)]");
}


#// Field 8
GetAdditionalBOFsString(bmAdditionalBOFs)
{
    str = "Additional BOFs: ";

    if (bmAdditionalBOFs & 0b10000000) # D7
	   return (str + "0 BOFs at 115,200 bps");

    if (bmAdditionalBOFs & 0b01000000) # D6
	   return (str + "1 BOFs at 115,200 bps");

    if (bmAdditionalBOFs & 0b00100000) # D5
	   return (str + "2 BOFs at 115,200 bps");

    if (bmAdditionalBOFs & 0b00010000) # D4
	   return (str + "3 BOFs at 115,200 bps");

    if (bmAdditionalBOFs & 0b00001000) # D3
	   return (str + "6 BOFs at 115,200 bps");

    if (bmAdditionalBOFs & 0b00000100) # D2
	   return (str + "12 BOFs at 115,200 bps");

    if (bmAdditionalBOFs & 0b00000010) # D1
	   return (str + "24 BOFs at 115,200 bps");

    if (bmAdditionalBOFs & 0b00000001) # D0
	   return (str + "48 BOFs at 115,200 bps");

    return (str + "Unknown!");
}


#// Field 9
GetIrDARateSniffString(bIrDARateSniff)
{
    str = "IrDA Rate Sniff Flag: ";

    if (bIrDARateSniff == 0)
	   return (str + "0");

    if (bIrDARateSniff == 1)
	   return (str + "1");

    return (str + "Invalid Value!");
}

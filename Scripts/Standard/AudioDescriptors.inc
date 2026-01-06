#******************************************************************************
#
#  FILENAME: AudioDescriptors.inc
#
#  Copyright (C) 2006 LeCroy Corporation
#
#  DESCRIPTION
#    This descriptor definition file is supplied by LeCroy.
#    This file defines standard USB Communication descriptors.
#    File version is 1.0.
#    Convert to 2.0  Aug 02, 2006 - jz
#    Adding dding Audio 3.0 Dec 15 2016
#
#******************************************************************************
%include "AudioTables.inc"



set bLength = 0;
TryAudioDescriptors(bDescriptorType)
{
    CurrentByteOffset = 0;
    _row = Find(AudioDescriptorTypeTable, MostRecentProtocol);
    table     = _row[1];
    
    _row_desc_type = Find (table, bDescriptorType);
        
    AddShortDataHeader(FormatEx ("%s Descriptor  (%X type)", _row_desc_type[1], bDescriptorType ));
    if (_row_desc_type[0] == 0xFF)
        return 0;

    Call (_row_desc_type[1]);
    return 1;
}

Audio_CS_UNDEFINED()
{
    return 0;
}
Audio_CS_DEVICE()
{
    return 0;
}
Audio_CS_CONFIGURATION()
{
    return 0;
}

Audio_CS_STRING()
{
    return 0;
}

Audio_CS_INTERFACE()
{
    AddShortDataHeader(FormatEx ("%s Descriptor  (%d bytes)", "Audio Class Specific INTERFACE", bLength ));
    if (bLength > in.DataLength - Base )
    {
        AddStringToDlg("No enough data for this descriptor",FormatEx("Length required %d bytes, Actual Length %d bytes", bLength, in.DataLength - Base), OutputUnknownData(in.DataLength - Base, 0));
        return 0;
    }
    AddByteEntry("bLength", "Size of the descriptor, in bytes");
    if (CurrentByteOffset + 1 > bLength) return 1;

    AddByteEntry("bDescriptorType", GetDescriptorTypeString("CS_INTERFACE"));

    if (CurrentByteOffset + 1 > bLength) return 1;


    bDescriptorSubType = GetDataByte(Base + CurrentByteOffset);

    # We need to use the most recent interface subtype to see which type (streaming, control, etc)
    # we are looking for
    _row_vid_if = Find(AudioInterfaceSubclassCodesTable, MostRecentInterfaceSubClass);
    if (MostRecentProtocol == IP_VERSION_01_00)
        table = _row_vid_if[2];
    else if (MostRecentProtocol == IP_VERSION_02_00)
        table = _row_vid_if[3];
    else if (MostRecentProtocol == IP_VERSION_03_00)
        table = _row_vid_if[4];

    if (table != null)
    {
        func_row = Find(table, bDescriptorSubType);
        AddByteEntry( "bDescriptorSubType", Format ("%s descriptor subtype", func_row[1]));
        if (func_row[2] != null)
            Call(func_row[2]);
    }
    else
        AddStringToDlg(FormatEx("Unknown subtype 0x%02X for subclass 0x%02X", bDescriptorSubType, MostRecentInterfaceSubClass),"","",_ERROR);
    return 1;
}


Audio_CS_ENDPOINT()
{
    AddShortDataHeader(FormatEx ("%s Descriptor  (%d bytes)", "Audio Class Specific ENDPOINT", bLength ));
    if (bLength > in.DataLength - Base )
    {
        AddStringToDlg("No enough data for this descriptor",FormatEx("Length required %d bytes, Actual Length %d bytes", bLength, in.DataLength - Base), OutputUnknownData(in.DataLength - Base, 0));
        return 0;
    }
    AddByteEntry("bLength", "Size of the descriptor, in bytes");

    if (CurrentByteOffset + 1 > bLength)
        return 1;

    AddByteEntry("bDescriptorType", GetDescriptorTypeString("CS_ENDPOINT"));

    if (CurrentByteOffset + 1 > bLength)
        return 1;
    bDescriptorSubType = GetDataByte(Base + CurrentByteOffset);

    # We need to use the most recent interface subtype to see which type (streaming, control, etc)
    # we are looking for
    if (MostRecentEndpointType == 1) # ISOCHRONOUS
    {
        _row_vid_if = Find (AudioEPDescriptorSubTypeTable, bDescriptorSubType);
        if (MostRecentProtocol == IP_VERSION_01_00)
            func = _row_vid_if[2];
        else if (MostRecentProtocol == IP_VERSION_02_00)
            func = _row_vid_if[3];
        else
            func = null;
    }
    else if (MostRecentEndpointType == 2) # BULK
    {
        _row_vid_if = Find (AudioMSEndPointDescriptorSubTypeTable, bDescriptorSubType);
        func = _row_vid_if[2];
    }
    else
    {
        _row_vid_if = [0xFF];
    }


    if (_row_vid_if[0] == 0xFF || _row_vid_if[0] == 0x00)
    {
        AddEntry( CurrentByteOffset, "bDescriptorSubType", bDescriptorSubType, 2, _row_vid_if[1]);
        AddFieldBreak();
        IncCurrByteOffset( 1 );
        return 0;
    }
    AddEntry( CurrentByteOffset, "bDescriptorSubType",bDescriptorSubType,2, Format ("%s descriptor subtype", _row_vid_if[1]));
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (func != null)
        Call (func);
    return 1;
}

Audio_CS_CLUSTER()
{
    return 0;
}
#***************************************************************************************************
#Universal Serial Bus Device Class Implementation for Audio Devices Release 1.0 2.0 3.0 common
#*********************************************************************************h******************
HEADER_sub()
{
    if (MostRecentProtocol < IP_VERSION_03_00)
    {
        if (CurrentByteOffset + 2 > bLength) return 1;
        bcdADC  = GetDataWord( Base + CurrentByteOffset );
        AddEntry( CurrentByteOffset, "bcdADC", bcdADC, 4, "Audio Device compliant to " , 0);
        AddDescriptionOnly( "the USB Audio specification" );
        AddDescriptionOnly( FormatEx( "version %X.%02X", (bcdADC & 0xFF00)>> 8, bcdADC & 0xFF) );
        AddFieldBreak();
        IncCurrByteOffset( 2 );
    }

    if (MostRecentProtocol >= IP_VERSION_02_00)
    {
        if (CurrentByteOffset + 1 > bLength) return 1;
        
        _row_item = Find(AudioFunctionCategoryCodesTable, MostRecentProtocol);
        table     = _row_item[1];
        
        bCategory  = GetDataByte( Base + CurrentByteOffset );
        row = Find (table, bCategory);
        AddEntry( CurrentByteOffset, "bCategory", row[1], 2, row[1] + Format("(0x%02X)", bCategory) , 0);
        AddDescriptionOnly( ": Indicating the primary use " );
        AddDescriptionOnly( "of this audio function" );
        AddFieldBreak();
        IncCurrByteOffset( 1 );
    }

    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wTotalLength", "Total number of bytes returned for the class-specific AudioControl interface descriptor. Includes the combined length of this descriptor header and all Unit and Terminal descriptors.");
    
    
    if (MostRecentProtocol >= IP_VERSION_02_00)
    {
        bm_controls_len = 0;
        
        if (MostRecentProtocol == IP_VERSION_02_00)
        {
            bm_controls_len = 1;
            
            if (CurrentByteOffset + bm_controls_len > bLength) return 1;
            bmControls = GetDataByte(Base + CurrentByteOffset);
            
        }
        
        if (MostRecentProtocol == IP_VERSION_03_00)
        {
            bm_controls_len = 4;
            
            if (CurrentByteOffset + bm_controls_len > bLength) return 1;
            bmControls = GetNBits(in.Data, ((Base+CurrentByteOffset+DataByteHeaderOffset)*8), 32);
        }
        
        #Get D1..0(Bits 0 and 1)
        controlStatus = bmControls & 3;
        row = find (AudioGeneralControlStatusTable, controlStatus);
        
        nibbles = bm_controls_len * 2;
        AddEntry(CurrentByteOffset, "bmControls", bmControls, nibbles, "D1..0:  Latency Control" + row[1], 0);
        AddFieldBreak();
        IncCurrByteOffset( bm_controls_len );
    }
    else
    {
        if (CurrentByteOffset + 1 > bLength) return 1;
        bInCollection  = GetDataByte( Base + CurrentByteOffset );
        AddByteEntry("bInCollection","The number of AudioStreaming and MIDIStreaming interfaces in the Audio Interface Collection to which this AudioControl interface belongs", 0);
        
        for (i = 0 ; i < bInCollection ; i++)
        {
            if (CurrentByteOffset + 1 > bLength) return 1;
            AddByteEntry(Format("baInterfaceNr(%d)",i), "Interface number of the AudioStreaming or MIDIStreaming interface in the Collection",0);
        }
    }
}

# This function returns the function's subclass description that normally use to interpret bFunctionSubClass inside INTERFACE_ASSOCIATION Descriptor
AD_FUNCTION_SUBCLASS_sub(bFunctionSubClass, bFunctionProtocol)
{
    #Is Audio 1.0
    if(bFunctionProtocol == IP_VERSION_01_00)
    {
        #In Audio 1.0 spec, we don't have any suggestion about using INTERFACE_ASSOCIATION Descriptor(IAD) to describe the audio function, but in some trace samples
        #Like microsoft webcam usb2.0 that used IAD for audio 1.0 and it sets InterfaceSubClass code for the bFunctionSubClass.
        _row_d = Find(AudioInterfaceSubclassCodesTable, bFunctionSubClass);
        function_subclass_desc = _row_d[1];
    }
    #Is Audio 2.0
    else if(bFunctionProtocol == IP_VERSION_02_00)
    {
        #According to Table A-2, we just have FUNCTION_SUBCLASS_UNDEFINED(0x00) for Audio Function Subclass Code.
    }
    #Is Audio 3.0
    else if(bFunctionProtocol == IP_VERSION_03_00)
    {
        _row_d = Find(AudioFunctionSubclassCodesTable, bFunctionSubClass);
        function_subclass_desc = _row_d[1];
    }
    
    return function_subclass_desc;
}

#***************************************************************************************************
#Universal Serial Bus Device Class Implementation for Audio Devices Release 1.0 specific
#***************************************************************************************************
INPUT_TERMINAL_v1_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bTerminalID", "Constant uniquely identifying the Terminal within the audio function. This value is used in all requests to address this Terminal.",0);
    if (CurrentByteOffset + 2 > bLength) return 1;
    wTerminalType = GetDataWord(Base + CurrentByteOffset);
    _row = Find(USBTerminalTypesTable, wTerminalType);
    AddEntry(CurrentByteOffset, "wTerminalType",wTerminalType,4, _row[3]);
    AddFieldBreak();
    IncCurrByteOffset( 2 );
    if (CurrentByteOffset + 1 > bLength) return 1;
    bAssocTerminal = GetDataByte(Base + CurrentByteOffset);
    if (bAssocTerminal == 0)
        text = "This Input Terminal has no association";
    else
        text = Format("This Input Terminal is associated with Output Terminal %d",wAssocTerminal);
    AddEntry(CurrentByteOffset, "bAssocTerminal", bAssocTerminal,2, text);
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    bNrChannels = GetDataByte(Base + CurrentByteOffset);
    AddEntry(CurrentByteOffset, "bNrChannels", bNrChannels,2, Format("This Terminal's output audio channel cluster has %d logical output channels",bNrChannels));
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 2 > bLength) return 1;
    AddwChannelConfigEntry();

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iChannelNames","Index of a string descriptor, describing the name of the first logical channel.",0);

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iTerminal", "Index of a string descriptor, describing the Input Terminal.",0);
}

OUTPUT_TERMINAL_v1_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bTerminalID","Constant uniquely identifying the Terminal within the audio function. This value is used in all requests to address this Terminal.",0);
    if (CurrentByteOffset + 2 > bLength) return 1;
    wTerminalType = GetDataWord(Base + CurrentByteOffset);
    _row = Find(USBTerminalTypesTable, wTerminalType);
    AddEntry(CurrentByteOffset, "wTerminalType",wTerminalType,4, _row[3]);
    AddFieldBreak();
    IncCurrByteOffset( 2 );
    if (CurrentByteOffset + 1 > bLength) return 1;
    bAssocTerminal = GetDataByte(Base + CurrentByteOffset);
    if (bAssocTerminal == 0)
        text = "This Output Terminal has no association";
    else
        text = Format("This Output Terminal is associated with Input Terminal %d",wAssocTerminal);
    AddEntry(CurrentByteOffset, "bAssocTerminal", bAssocTerminal,2, text);
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSourceID", "ID of the Unit or Terminal to which this Terminal is connected.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iTerminal", "Index of a string descriptor, describing the Output Terminal.",0);
}

MIXER_UNIT_v1_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bUnitID","Constant uniquely identifying the Unit within the audio function. This value is used in all requests to address this Unit.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrInPins", "Number of Input Pins of this Unit",0);

    bNrInPins = val;

    for (i = 0; i < bNrInPins; i++)
    {
        if (CurrentByteOffset + 1 > bLength) return 1;
        AddByteEntry(Format("baSourceID%d",i), Format("ID of the Unit or Terminal to which the %d Input Pin of this Mixer Unit is connected.",i),0);

    }
    if (CurrentByteOffset + 1 > bLength) return 1;
    bNrChannels = GetDataByte(Base + CurrentByteOffset);
    AddEntry(CurrentByteOffset, "bNrChannels", bNrChannels,2, Format("This Mixer’s output audio channel cluster has %d logical output channels",bNrChannels));
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 2 > bLength) return 1;
    AddwChannelConfigEntry();

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iChannelNames", "Index of a string descriptor, describing the name of the first logical channel.",0);


    sizeN = bLength - 10 - bNrInPins;
    if (CurrentByteOffset + sizeN > bLength) return 1;
    bmControls = GetNBits(in.Data,((Base+CurrentByteOffset+DataByteHeaderOffset)*8), sizeN * 8);
    SetFieldOffsetLen(((Base+CurrentByteOffset)*8) + sizeN * 8, sizeN * 8);
    AddEntry(CurrentByteOffset, "bmControls", bmControls, sizeN * 2, "Bit map indicating which mixing Controls are programmable.",0);
    AddFieldBreak();
    IncCurrByteOffset( sizeN );
    if (CurrentByteOffset + 1 > bLength) return 1;

    AddByteEntry("iMixer","Index of a string descriptor, describing the Mixer Unit.",0);
}

SELECTOR_UNIT_v1_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bUnitID", "Constant uniquely identifying the Unit within the audio function. This value is used in all requests to address this Unit.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrInPins", "Number of Input Pins of this Unit",0);

    bNrInPins = val;

    for (i = 0; i < bNrInPins; i++)
    {
        if (CurrentByteOffset + 1 > bLength) return 1;
        AddByteEntry(Format("baSourceID%d",i), Format("ID of the Unit or Terminal to which the %d Input Pin of this Mixer Unit is connected.",i),0);

    }
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iSelector", "Index of a string descriptor, describing the Selector Unit.",0);
}

FEATURE_UNIT_v1_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bUnitID", "Constant uniquely identifying the Unit within the audio function. This value is used in all requests to address this Unit.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSourceID", "ID of the Unit or Terminal to which this Feature Unit is connected.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bControlSize", "Size in bytes of an element of the bmaControls() array:",0);
    bControlSize = val;

    sizeN = (bLength - 7) / bControlSize;
    for (i = 0; i < sizeN; i++)
    {
        if (CurrentByteOffset + bControlSize > bLength) return 1;
        bmControls = GetNBits(in.Data,((Base+CurrentByteOffset+DataByteHeaderOffset)*8), bControlSize * 8);
        SetFieldOffsetLen(((Base+CurrentByteOffset)*8) + bControlSize * 8, bControlSize * 8);
        toolTip = ToBitDecode_old(AudioFeatureUnitControls_v1_Bitmap, bmControls);
        AddEntry(CurrentByteOffset, Format("bmaControls(%d)", i), bmControls, bControlSize * 2, Format("master channel %d:",i)+ toolTip,0);
        AddFieldBreak();
        IncCurrByteOffset( bControlSize );

    }
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iFeature","Index of a string descriptor, describing this Feature Unit.",0);
}

PROCESSING_UNIT_v1_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bUnitID", "Constant uniquely identifying the Unit" + "within the audio function. This value is" + "used in all requests to address this Unit.",0);

    if (CurrentByteOffset + 2 > bLength) return 1;
    wProcessType = GetDataWord(Base + CurrentByteOffset);
    
    processTypeRow = Find( AudioPUPType_v1_Table, wProcessType);
    
    AddEntry(CurrentByteOffset, "wProcessType", processTypeRow[1], 2, FormatEx("Type of the processing this unit is performing %s (0x%04X)",processTypeRow[1], wProcessType) ,0);
    AddFieldBreak();
    IncCurrByteOffset( 2 );

    if (processTypeRow[2] != null)
        Call(processTypeRow[2]);
}

EXTENSION_UNIT_v1_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bUnitID","Constant uniquely identifying the Unit within the audio function. This value is used in all requests to address this Unit.",0);
    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wExtensionCode", "Vendor-specific code identifying the Extension Unit.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrInPins", "Number of Input Pins of this Unit",0);
    bNrInPins = val;

    for (i = 0; i < bNrInPins; i++)
    {
        if (CurrentByteOffset + 1 > bLength) return 1;
        AddByteEntry(Format("baSourceID%d",i),Format("ID of the Unit or Terminal to which the %d Input Pin of this Mixer Unit is connected.",i),0);

    }

    if (CurrentByteOffset + 1 > bLength) return 1;
    bNrChannels = GetDataByte(Base + CurrentByteOffset);
    AddEntry(CurrentByteOffset, "bNrChannels", bNrChannels,2, Format("This Extension Unit's audio channel cluster has %d logical output channels",bNrChannels));
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddwChannelConfigEntry();

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iChannelNames","Index of a string descriptor, describing the name of the first logical channel in the audio channel cluster of the Extension Unit.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bControlSize","Size, in bytes, of the bmControls field",0);
    bControlSize = val;

    if (CurrentByteOffset + bControlSize > bLength) return 1;
    bmControls = GetNBits(in.Data,((Base+CurrentByteOffset+DataByteHeaderOffset)*8), bControlSize * 8);
    SetFieldOffsetLen(((Base+CurrentByteOffset)*8) + bControlSize * 8, bControlSize * 8);
    AddEntry(CurrentByteOffset, "bmControls", bmControls, bControlSize * 2, "A bit set to 1 indicates that the mentioned Control is supported: D0: Enable Processing.",0);
    AddFieldBreak();
    IncCurrByteOffset( bControlSize );
    if (CurrentByteOffset + 1 > bLength) return 1;

    AddByteEntry("iExtension","Index of a string descriptor, describing this Extension Unit.",0);
}

AUDIO_EP_GENERAL_v1_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    bmAttributes = GetDataByte(Base + CurrentByteOffset);
    toolTip = ToBitDecode_old(AudioEPGeneralAttributes_v1_Bitmap, bmAttributes);
    AddEntry(CurrentByteOffset, "bmAttributes", bmAttributes, 2, toolTip,0);
    AddFieldBreak();
    IncCurrByteOffset( 1 );
    if (CurrentByteOffset + 1 > bLength) return 1;

    bLockDelayUnits =GetDataByte(Base + CurrentByteOffset);
    if (bLockDelayUnits == 0)
        toolTip = "0: Undefined";
    else if (bLockDelayUnits == 1)
        toolTip = "1: Milliseconds";
    else if (bLockDelayUnits == 2)
        toolTip = "2: Decoded PCM samples";
    else
        toolTip = "Reserved";
    AddEntry(CurrentByteOffset, "bLockDelayUnits", bLockDelayUnits, 2, "Indicates the units used for the wLockDelay field: " + toolTip,0);
    AddFieldBreak();
    IncCurrByteOffset( 1 );
    if (CurrentByteOffset + 2 > bLength) return 1;

    AddWordEntry("wLockDelay", "Indicates the time it takes this endpoint to reliably lock its internal clock recovery circuitry. Units used depend on the value of the bLockDelayUnits field.",0);
}

################################################################
# Audio Devices sub functions for PROCESSING_UNIT_v1_sub()
################################################################
UP_DOWNMIX_PROCESS_v1_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrInPins","Number of Input Pins of this Unit",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSourceID","ID of the Unit or Terminal to which the Input Pin of this Mixer Unit is connected.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    bNrChannels = GetDataByte(Base + CurrentByteOffset);
    AddEntry(CurrentByteOffset, "bNrChannels", bNrChannels,2, Format("This Processing Unit's audio channel cluster has %d logical output channels",bNrChannels));
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 2 > bLength) return 1;
    AddwChannelConfigEntry();

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iChannelNames","Index of a string descriptor, describing the name of the first logical channel.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bControlSize","Size, in bytes, of the bmControls field",0);

    bControlSize = val;

    if (CurrentByteOffset + bControlSize > bLength) return 1;
    bmControls = GetNBits(in.Data,((Base+CurrentByteOffset+DataByteHeaderOffset)*8), bControlSize * 8);
    SetFieldOffsetLen(((Base+CurrentByteOffset)*8) + bControlSize * 8, bControlSize * 8);
    AddEntry(CurrentByteOffset, "bmControls", bmControls, bControlSize * 2, "A bit set to 1 indicates that the mentioned Control is supported: D0: Enable Processing. D1: Mode Select.",0);
    AddFieldBreak();
    IncCurrByteOffset( bControlSize );
    if (CurrentByteOffset + 1 > bLength) return 1;

    AddByteEntry("iProcessing","Index of a string descriptor, describing this Processing Unit.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrModes","Number of modes, supported by this Processing Unit",0);

    bNrModes = val;

    for (i = 1; i < bNrModes + 1; i++)
    {
        if (CurrentByteOffset + 2 > bLength) return 1;
        Add2BytesEntry(Format("waModes%d",i), Format("Describes the active logical channels in mode %d",i),0);

    }
}

DOLBY_PROLOGIC_PROCESS_v1_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrInPins","Number of Input Pins of this Unit",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSourceID","ID of the Unit or Terminal to which the Input Pin of this Mixer Unit is connected.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    bNrChannels = GetDataByte(Base + CurrentByteOffset);
    AddEntry(CurrentByteOffset, "bNrChannels", bNrChannels,2, Format("This Processing Unit's audio channel cluster has %d logical output channels",bNrChannels));
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 2 > bLength) return 1;
    AddwChannelConfigEntry();

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iChannelNames","Index of a string descriptor, describing the name of the first logical channel.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bControlSize","Size, in bytes, of the bmControls field",0);

    bControlSize = val;

    if (CurrentByteOffset + bControlSize > bLength) return 1;
    bmControls = GetNBits(in.Data,((Base+CurrentByteOffset+DataByteHeaderOffset)*8), bControlSize * 8);
    SetFieldOffsetLen(((Base+CurrentByteOffset)*8) + bControlSize * 8, bControlSize * 8);
    AddEntry(CurrentByteOffset, "bmControls", bmControls, bControlSize * 2, "A bit set to 1 indicates that the mentioned Control is supported: D0: Enable Processing. D1: Mode Select.",0);
    AddFieldBreak();
    IncCurrByteOffset( bControlSize );
    if (CurrentByteOffset + 1 > bLength) return 1;

    AddByteEntry("iProcessing","Index of a string descriptor, describing this Processing Unit.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrModes","Number of modes, supported by this Processing Unit. A maximum of 3 different modes is possible.",0);

    bNrModes = val;

    for (i = 1; i < bNrModes + 1; i++)
    {
        if (CurrentByteOffset + 2 > bLength) return 1;
        Add2BytesEntry(Format("waModes%d",i), Format("Describes the active logical channels in mode %d",i),0);

    }
}
AUDIO_3D_STEREO_EXTENDER_PROCESS_v1_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrInPins","Number of Input Pins of this Unit",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSourceID","ID of the Unit or Terminal to which the Input Pin of this Mixer Unit is connected.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    bNrChannels = GetDataByte(Base + CurrentByteOffset);
    AddEntry(CurrentByteOffset, "bNrChannels", bNrChannels,2, Format("This Processing Unit's audio channel cluster has %d logical output channels",bNrChannels));
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 2 > bLength) return 1;
    AddwChannelConfigEntry();

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iChannelNames", "Index of a string descriptor, describing the name of the first logical channel.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bControlSize","Size, in bytes, of the bmControls field",0);

    bControlSize = val;

    if (CurrentByteOffset + bControlSize > bLength) return 1;
    bmControls = GetNBits(in.Data,((Base+CurrentByteOffset+DataByteHeaderOffset)*8), bControlSize * 8);
    SetFieldOffsetLen(((Base+CurrentByteOffset)*8) + bControlSize * 8, bControlSize * 8);
    AddEntry(CurrentByteOffset, "bmControls", bmControls, bControlSize * 2, "A bit set to 1 indicates that the mentioned Control is supported: D0: Enable Processing. D1: Spaciousness.",0);
    AddFieldBreak();
    IncCurrByteOffset( bControlSize );
    if (CurrentByteOffset + 1 > bLength) return 1;

    AddByteEntry("iProcessing","Index of a string descriptor, describing this Processing Unit.",0);
}

REVERBERATION_PROCESS_v1_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrInPins","Number of Input Pins of this Unit",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSourceID","ID of the Unit or Terminal to which the Input Pin of this Mixer Unit is connected.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    bNrChannels = GetDataByte(Base + CurrentByteOffset);
    AddEntry(CurrentByteOffset, "bNrChannels", bNrChannels,2, Format("This Processing Unit's audio channel cluster has %d logical output channels",bNrChannels));
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 2 > bLength) return 1;
    AddwChannelConfigEntry();

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iChannelNames", "Index of a string descriptor, describing the name of the first logical channel.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bControlSize","Size, in bytes, of the bmControls field",0);

    bControlSize = val;

    if (CurrentByteOffset + bControlSize > bLength) return 1;
    bmControls = GetNBits(in.Data,((Base+CurrentByteOffset+DataByteHeaderOffset)*8), bControlSize * 8);
    SetFieldOffsetLen(((Base+CurrentByteOffset)*8) + bControlSize * 8, bControlSize * 8);
    AddEntry(CurrentByteOffset, "bmControls", bmControls, bControlSize * 2, "A bit set to 1 indicates that the mentioned Control is supported: D0: Enable Processing. D1: Reverb Type. D2: Reverb Level. D3: Reverb Time. D4: Reverb Delay Feedback.",0);
    AddFieldBreak();
    IncCurrByteOffset( bControlSize );
    if (CurrentByteOffset + 1 > bLength) return 1;

    AddByteEntry("iProcessing","Index of a string descriptor, describing this Processing Unit.",0);

}

CHORUS_PROCESS_v1_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrInPins","Number of Input Pins of this Unit",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSourceID","ID of the Unit or Terminal to which the Input Pin of this Mixer Unit is connected.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    bNrChannels = GetDataByte(Base + CurrentByteOffset);
    AddEntry(CurrentByteOffset, "bNrChannels", bNrChannels,2, Format("This Processing Unit's audio channel cluster has %d logical output channels",bNrChannels));
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 2 > bLength) return 1;
    AddwChannelConfigEntry();

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iChannelNames", "Index of a string descriptor, describing the name of the first logical channel.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bControlSize","Size, in bytes, of the bmControls field",0);

    bControlSize = val;

    if (CurrentByteOffset + bControlSize > bLength) return 1;
    bmControls = GetNBits(in.Data,((Base+CurrentByteOffset+DataByteHeaderOffset)*8), bControlSize * 8);
    SetFieldOffsetLen(((Base+CurrentByteOffset)*8) + bControlSize * 8, bControlSize * 8);
    AddEntry(CurrentByteOffset, "bmControls", bmControls, bControlSize * 2, "A bit set to 1 indicates that the mentioned Control is supported: D0: Enable Processing. D1: Chorus Level. D2: Chorus Modulation Rate. D3: Chorus Modulation Depth.",0);
    AddFieldBreak();
    IncCurrByteOffset( bControlSize );
    if (CurrentByteOffset + 1 > bLength) return 1;

    AddByteEntry("iProcessing","Index of a string descriptor, describing this Processing Unit.",0);
}
DYN_RANGE_COMP_PROCESS_v1_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrInPins","Number of Input Pins of this Unit",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSourceID","ID of the Unit or Terminal to which the Input Pin of this Mixer Unit is connected.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    bNrChannels = GetDataByte(Base + CurrentByteOffset);
    AddEntry(CurrentByteOffset, "bNrChannels", bNrChannels,2, Format("This Processing Unit's audio channel cluster has %d logical output channels",bNrChannels));
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 2 > bLength) return 1;
    AddwChannelConfigEntry();

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iChannelNames", "Index of a string descriptor, describing the name of the first logical channel.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bControlSize","Size, in bytes, of the bmControls field",0);

    bControlSize = val;

    if (CurrentByteOffset + bControlSize > bLength) return 1;
    bmControls = GetNBits(in.Data,((Base+CurrentByteOffset+DataByteHeaderOffset)*8), bControlSize * 8);
    SetFieldOffsetLen(((Base+CurrentByteOffset)*8) + bControlSize * 8, bControlSize * 8);
    AddEntry(CurrentByteOffset, "bmControls", bmControls, bControlSize * 2, "A bit set to 1 indicates that the mentioned Control is supported: D0: Enable Processing. D1: Compression Ratio. D2: MaxAmpl. D3: Threshold. D4: Attack time. D5: Release time.",0);
    AddFieldBreak();
    IncCurrByteOffset( bControlSize );
    if (CurrentByteOffset + 1 > bLength) return 1;

    AddByteEntry("iProcessing","Index of a string descriptor, describing this Processing Unit.",0);

}


#***************************************************************************************************
#Universal Serial Bus Device Class Definition for Audio Data Formats Release 1.0
#***************************************************************************************************
AS_GENERAL_v1_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bTerminalLink", "The Terminal ID of the Terminal to which the endpoint of this interface is connected.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bDelay", "Delay introduced by the data path. Expressed in number of frames.",0);
    if (CurrentByteOffset + 2 > bLength) return 1;

    wFormatTag = GetDataWord(Base + CurrentByteOffset);
    _row = Find(AudioDataFormatSpecific_v1_Table ,wFormatTag);
    AddEntry(CurrentByteOffset, "wFormatTag", wFormatTag, 4, _row[1],0);
    AddFieldBreak();
    IncCurrByteOffset( 2 );
}

FORMAT_TYPE_v1_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    bFormatType = GetDataByte(Base + CurrentByteOffset);
    _row = Find(AudioDataFormatType_v1_Table, bFormatType);
    AddEntry(CurrentByteOffset, "bFormatType", bFormatType, 2, _row[1],0);
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (_row[2] != null)
    {
        Call(_row[2]);
    }
}

FORMAT_SPECIFIC_v1_sub()
{
    if (CurrentByteOffset + 2 > bLength) return 1;
    wFormatTag = GetDataWord(Base + CurrentByteOffset);
    _row = Find(AudioDataFormatSpecific_v1_Table ,wFormatTag);
    AddEntry(CurrentByteOffset, "wFormatTag", wFormatTag, 4, _row[1],0);
    AddFieldBreak();
    IncCurrByteOffset( 2 );

    if (_row[2] != null)
    {
        Call(_row[2]);
    }
}

################################################################
# Audio Devices sub functions for FORMAT_TYPE_v1_sub()
################################################################
FORMAT_TYPE_I_v1_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrChannels","Indicates the number of physical channels in the audio data stream.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSubframeSize","The number of bytes occupied by one audio subframe. Can be 1, 2, 3 or 4.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bBitResolution", "The number of effectively used bits from the available bits in an audio subframe.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSamFreqType", "Indicates how the sampling frequency can be programmed:",0);
    if (CurrentByteOffset + 3 > bLength) return 1;
    bSamFreqType = val;

    if (bSamFreqType == 0)
    {
        Add3BytesEntry("tLowerSamFreq",  "Lower bound in Hz of the sampling frequency range for this isochronous data endpoint.",0);
        if (CurrentByteOffset + 3 > bLength) return 1;
        Add3BytesEntry("tUpperSamFreq","Upper bound in Hz of the sampling frequency range for this isochronous data endpoint.",0);
        if (CurrentByteOffset + 3 > bLength) return 1;
    }

    for (i = 1; i <= bSamFreqType ; i++)
    {
        Add3BytesEntry(Format("tSamFreq[%d]",i),Format("Sampling frequency %d in Hz for this isochronous data endpoint.",i),0);
        if (CurrentByteOffset + 3 > bLength) return 1;
    }
}

FORMAT_TYPE_II_v1_sub()
{
    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wMaxBitRate", "Indicates the maximum number of bits per second this interface can handle. Expressed in kbits/s.",0);
    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wSamplesPerFrame", "Indicates the number of PCM audio samples contained in one encoded audio frame.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSamFreqType","Indicates how the sampling frequency can be programmed:",0);

    bSamFreqType = val;

    if (bSamFreqType == 0)
    {
        if (CurrentByteOffset + 3 > bLength) return 1;
        Add3BytesEntry("tLowerSamFreq","Lower bound in Hz of the sampling frequency range for this isochronous data endpoint.",0);
        if (CurrentByteOffset + 3 > bLength) return 1;
        Add3BytesEntry("tUpperSamFreq","Upper bound in Hz of the sampling frequency range for this isochronous data endpoint.",0);
    }
    for (i = 1; i <= bSamFreqType ; i++)
    {
        if (CurrentByteOffset + 3 > bLength) return 1;
        Add3BytesEntry(Format("tSamFreq[%d]",i), Format("Sampling frequency %d in Hz for this isochronous data endpoint.",i),0);
    }
}

FORMAT_TYPE_III_v1_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrChannels","Indicates the number of ‘virtual’ physical channels in the audio data stream. Must be set to two.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSubframeSize","The number of bytes occupied by one audio subframe. Must be set to 2.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bBitResolution","The number of effectively used bits from the available bits in an audio subframe.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSamFreqType", "Indicates how the sampling frequency can be programmed:",0);
    bSamFreqType = val;

    if (bSamFreqType == 0)
    {
        if (CurrentByteOffset + 3 > bLength) return 1;
        Add3BytesEntry("tLowerSamFreq", "Lower bound in Hz of the sampling frequency range for this isochronous data endpoint.",0);
        if (CurrentByteOffset + 3 > bLength) return 1;
        Add3BytesEntry("tUpperSamFreq", "Upper bound in Hz of the sampling frequency range for this isochronous data endpoint.",0);
    }
    for (i = 1; i <= bSamFreqType ; i++)
    {
        if (CurrentByteOffset + 3 > bLength) return 1;
        Add3BytesEntry(Format("tSamFreq[%d]",i),Format("Sampling frequency %d in Hz for this isochronous data endpoint.",i),0);
    }
}

################################################################
# Audio Devices sub functions for FORMAT_SPECIFIC_v1_sub()
################################################################
MPEG_v1_sub()
{
    if (CurrentByteOffset + 2 > bLength) return 1;
    bmMPEGCapabilities = GetNBits(in.Data,((Base+CurrentByteOffset+DataByteHeaderOffset)*8), 16);
    SetFieldOffsetLen(((Base+CurrentByteOffset)*8) + 16, 16);
    toolTip = ToBitDecode_old(AudioMPEGCapabilities_v1_Bitmap, bmMPEGCapabilities);
    AddEntry(CurrentByteOffset, "bmMPEGCapabilities", bmMPEGCapabilities, 4, "Bitmap identifying the MPEG capabilities of the decoder. A bit set indicates that the capability is supported:" + toolTip,0);
    AddFieldBreak();
    IncCurrByteOffset( 2 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bmMPEGFeatures","Bitmap identifying the features the decoder supports. A bit set indicates that the feature is supported: D5..4: Internal Dynamic Range Control: 00 = not supported. 01 = supported but not scalable. 10 = scalable, common boost and cut scaling value. 11 = scalable, separate boost and cut scaling value.",0);
}

AC_3_v1_sub()
{
    if (CurrentByteOffset + 4 > bLength) return 1;
    bmBSID = GetNBits(in.Data,((Base+CurrentByteOffset+DataByteHeaderOffset)*8), 32);
    SetFieldOffsetLen(((Base+CurrentByteOffset)*8) + 32, 32);
    AddEntry(CurrentByteOffset, "bmBSID", bmBSID, 8, "A bit set to 1 indicates that the corresponding BSID mode is supported.",0);
    AddFieldBreak();
    IncCurrByteOffset( 4 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    bmAC3Features = GetDataByte(Base + CurrentByteOffset);
    toolTip = ToBitDecode_old(AudioAC3Features_v1_Bitmap, bmAC3Features);
    AddEntry(CurrentByteOffset, "bmAC3Features", bmAC3Features, 2, "A bit set to 1 indicates that the mentioned feature is supported:" + toolTip,0);
    AddFieldBreak();
    IncCurrByteOffset( 1 );
}
#***************************************************************************************************
#Universal Serial Bus Device Class Definition for MIDI Devices Release 1.0
#***************************************************************************************************
MS_GENERAL_v1_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNumEmbMIDIJack", "Number of Embedded MIDI Jacks",0);
    bNumEmbMIDIJack = val;

    for (i = 1; i <= bNumEmbMIDIJack; i++)
    {
        if (CurrentByteOffset + 1 > bLength) return 1;
        AddByteEntry(Format("baAssocJackID(%d)",i), Format("ID %d of the Embedded Jack that is associated with this endpoint.",i),0);
    }
}

MS_HEADER_sub()
{
    if (CurrentByteOffset + 2 > bLength) return 1;
    bcdMSC = GetDataWord( Base + CurrentByteOffset );
    AddEntry( CurrentByteOffset, "bcdMSC", bcdMSC, 4, "MIDIStreaming subclass compliant to " , 0);
    AddDescriptionOnly( "the MIDIStreaming specification" );
    AddDescriptionOnly( FormatEx( "version %X.%02X", (bcdMSC & 0xFF00)>> 8, bcdMSC & 0xFF) );
    AddFieldBreak();
    IncCurrByteOffset( 2 );
    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wTotalLength","Total number of bytes returned for the class-specific MIDIStreaming interface descriptor. Includes the combined length of this descriptor header and all Jack and Element descriptors.",0);
}

MIDI_IN_JACK_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    bJackType = GetDataByte(Base + CurrentByteOffset);
    _row = Find(AudioMSMIDIJackTypeTable, bJackType);
    AddEntry(CurrentByteOffset, "bJackType", bJackType, 2, _row[1],0);
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bJackID","Constant uniquely identifying the MIDI IN Jack within the USB-MIDI function.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iJack","Index of a string descriptor, describing the MIDI IN Jack.",0);
}

MIDI_OUT_JACK_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    bJackType = GetDataByte(Base + CurrentByteOffset);
    _row = Find(AudioMSMIDIJackTypeTable, bJackType);
    AddEntry(CurrentByteOffset, "bJackType", bJackType, 2, _row[1],0);
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bJackID","Constant uniquely identifying the MIDI OUT Jack within the USB-MIDI function.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrInputPins","Number of Input Pins of this MIDI OUT Jack:",0);
    bNrInputPins = val;

    for (i = 1; i <= bNrInputPins; i++)
    {
       if (CurrentByteOffset + 1 > bLength) return 1;
        AddByteEntry(Format("baSourceID(%d)",i),"ID of the Entity to which the first Input Pin of this MIDI OUT Jack is connected.",0);
        if (CurrentByteOffset + 1 > bLength) return 1;
        AddByteEntry(Format("baSourcePin(%d)",i),"Output Pin number of the Entity to which the first Input Pin of this MIDI OUT Jack is connected.",0);
    }

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iJack","Index of a string descriptor, describing the MIDI OUT Jack.",0);
}

ELEMENT_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bElementID","Constant uniquely identifying the MIDI OUT Jack within the USB-MIDI function.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrInputPins", "Number of Input Pins of this Element",0);
    bNrInputPins = val;

    for (i = 1; i <= bNrInputPins; i++)
    {
        if (CurrentByteOffset + 1 > bLength) return 1;
        AddByteEntry(Format("baSourceID(%d)",i),"ID of the Entity to which the first Input Pin of this MIDI OUT Jack is connected.",0);
        if (CurrentByteOffset + 1 > bLength) return 1;
        AddByteEntry(Format("baSourcePin(%d)",i),"Output Pin number of the Entity to which the first Input Pin of this MIDI OUT Jack is connected.",0);
    }

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrOutputPins", "Number of Output Pins of this Element",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bInTerminalLink", "The Terminal ID of the Input Terminal to which this Element is connected",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bOutTerminalLink","The Terminal ID of the Output Terminal to which this Element is connected",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bElCapsSize","Size, in bytes of the bmElementCaps field.",0);

    sizeN = bLength - 10 - 2 * bNrInputPins;
    if (CurrentByteOffset + sizeN > bLength) return 1;
    bmElementCaps = GetNBits(in.Data,((Base+CurrentByteOffset+DataByteHeaderOffset)*8), sizeN * 8);
    SetFieldOffsetLen(((Base+CurrentByteOffset)*8) + sizeN * 8, sizeN * 8);
    toolTip = ToBitDecode_old(AudioELEMENTCapsBitmap, bmElementCaps);
    AddEntry(CurrentByteOffset, "bmElementCaps", bmElementCaps, sizeN * 2, toolTip,0);
    AddFieldBreak();
    IncCurrByteOffset( sizeN );

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iElement","Index of a string descriptor, describing the Element.",0);
}

#***************************************************************************************************
#Universal Serial Bus Device Class Implementation for Audio Devices Release 2.0 specific
#***************************************************************************************************
INPUT_TERMINAL_v2_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bTerminalID", "Constant uniquely identifying the Terminal within the audio function. This value is used in all requests to address this Terminal.");

    if (CurrentByteOffset + 2 > bLength) return 1;
    wTerminalType = GetDataWord(Base + CurrentByteOffset);
    _row = Find(USBTerminalTypesTable, wTerminalType);
    AddEntry(CurrentByteOffset, "wTerminalType",wTerminalType,4, _row[3]);
    AddFieldBreak();
    IncCurrByteOffset( 2 );

    if (CurrentByteOffset + 1 > bLength) return 1;
        bAssocTerminal = GetDataByte(Base + CurrentByteOffset);
    if (bAssocTerminal == 0)
        text = "This Input Terminal has no association";
    else
        text = Format("This Input Terminal is associated with Output Terminal %d",wAssocTerminal);
    AddEntry(CurrentByteOffset, "bAssocTerminal", bAssocTerminal,2, text);
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bCSourceID", "ID of the Clock Entity to which this Input Terminal is connected.");

    if (CurrentByteOffset + 1 > bLength) return 1;
    bNrChannels = GetDataByte(Base + CurrentByteOffset);
    AddEntry(CurrentByteOffset, "bNrChannels", bNrChannels,2, Format("This Terminal's output audio channel cluster has %d logical output channels",bNrChannels));
    AddFieldBreak();
    IncCurrByteOffset( 1 );


    if (CurrentByteOffset + 4 > bLength) return 1;
    bmChannelConfig = AddbmChannelConfigEntry();


    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iChannelNames","Index of a string descriptor, describing the name of the first logical channel.",0);

    if (CurrentByteOffset + 2 > bLength) return 1;
    bmControls = GetNBits(in.Data, ((Base + CurrentByteOffset+DataByteHeaderOffset)*8), 16);
    SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 8, 16);
    copyProtectControl = bmControls & 0x0003;
    connectorControl = (bmControls & 0x000C) >> 2;
    overLoadControl = (bmControls & 0x0030) >> 4;
    clusterControl = (bmControls & 0x00C0) >> 6;
    underflowControl = (bmControls & 0x0300) >> 8;
    overflowControl = (bmControls & 0x0C00) >> 10;
    copyProtectControlRow = Find(AudioGeneralControlStatusTable, copyProtectControl);
    connectorControlRow = Find(AudioGeneralControlStatusTable, connectorControl);
    overLoadControlRow = Find(AudioGeneralControlStatusTable, overLoadControl);
    clusterControlRow = Find(AudioGeneralControlStatusTable, clusterControl);
    underflowControlRow = Find(AudioGeneralControlStatusTable, underflowControl);
    overflowControlRow = Find(AudioGeneralControlStatusTable, overflowControl);
    reservedText = "D15..12: Reserved, should set to 0";
    bmControlsText = "<html>";
    bmControlsText += "<br>&nbsp;&nbsp;" + "D1..0: Copy Protect Control" + copyProtectControlRow[1];
    bmControlsText += "<br>&nbsp;&nbsp;" + "D3..2: Connector Control" + connectorControlRow[1];
    bmControlsText += "<br>&nbsp;&nbsp;" + "D5..4: Overload Control" + overLoadControlRow[1];
    bmControlsText += "<br>&nbsp;&nbsp;" + "D7..6: Cluster Control" + clusterControlRow[1];
    bmControlsText += "<br>&nbsp;&nbsp;" + "D9..8: Underflow Control" + underflowControlRow[1];
    bmControlsText += "<br>&nbsp;&nbsp;" + "D11..10: Overflow Control" + overflowControlRow[1];
    bmControlsText += "<br>&nbsp;&nbsp;" + reservedText + "<br>";
    bmControlsText +="</html>";

    AddEntry( CurrentByteOffset, "bmControls", bmControls, 4, bmControlsText, 0);
    AddFieldBreak();
    IncCurrByteOffset( 2 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iTerminal", "Index of a string descriptor, describing the Input Terminal.",0);
}

OUTPUT_TERMINAL_v2_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bTerminalID","Constant uniquely identifying the Terminal within the audio function. This value is used in all requests to address this Terminal.",0);

    if (CurrentByteOffset + 2 > bLength) return 1;
    wTerminalType = GetDataWord(Base + CurrentByteOffset);
    _row = Find(USBTerminalTypesTable, wTerminalType);
    AddEntry(CurrentByteOffset, "wTerminalType",wTerminalType,4, _row[3]);
    AddFieldBreak();
    IncCurrByteOffset( 2 );

    if (CurrentByteOffset + 1 > bLength) return 1;
        bAssocTerminal = GetDataByte(Base + CurrentByteOffset);
    if (bAssocTerminal == 0)
        text = "This Output Terminal has no association";
    else
        text = Format("This Output Terminal is associated with Input Terminal %d",wAssocTerminal);
    AddEntry(CurrentByteOffset, "bAssocTerminal", bAssocTerminal,2, text);
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSourceID", "ID of the Unit or Terminal to which this Terminal is connected.",0);

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bCSourceID", "ID of the Clock Entity to which this Output Terminal is connected");

    if (CurrentByteOffset + 2 > bLength) return 1;
    bmControls = GetNBits(in.Data, ((Base + CurrentByteOffset+DataByteHeaderOffset)*8), 16);
    SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 8, 16);
    copyProtectControl = bmControls & 0x0003;
    connectorControl = (bmControls & 0x000C) >> 2;
    overLoadControl = (bmControls & 0x0030) >> 4;
    underflowControl = (bmControls & 0x00C0) >> 6;
    overflowControl = (bmControls & 0x0300) >> 8;
    copyProtectControlRow = Find(AudioGeneralControlStatusTable, copyProtectControl);
    connectorControlRow = Find(AudioGeneralControlStatusTable, connectorControl);
    overLoadControlRow = Find(AudioGeneralControlStatusTable, overLoadControl);
    underflowControlRow = Find(AudioGeneralControlStatusTable, underflowControl);
    overflowControlRow = Find(AudioGeneralControlStatusTable, overflowControl);
    reservedText = "D15..10: Reserved, should set to 0";
    bmControlsText = "<html>";
    bmControlsText += "D1..0: Copy Protect Control" + copyProtectControlRow[1];
    bmControlsText += "<br>&nbsp;&nbsp;" + "D3..2: Connector Control" + connectorControlRow[1];
    bmControlsText += "<br>&nbsp;&nbsp;" + "D5..4: Overload Control" + overLoadControlRow[1];
    bmControlsText += "<br>&nbsp;&nbsp;" + "D7..6: Underflow Control" + underflowControlRow[1];
    bmControlsText += "<br>&nbsp;&nbsp;" + "D9..8: Overflow Control" + overflowControlRow[1];
    bmControlsText += "<br>&nbsp;&nbsp;" + reservedText;
    bmControlsText += "</html>";
    AddEntry( CurrentByteOffset, "bmControls", bmControls, 4, bmControlsText , 0);
    AddFieldBreak();
    IncCurrByteOffset( 2 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iTerminal", "Index of a string descriptor, describing the Output Terminal.",0);
}

MIXER_UNIT_v2_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bUnitID","Constant uniquely identifying the Unit within the audio function. This value is used in all requests to address this Unit.",0);

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrInPins", "Number of Input Pins of this Unit",0);
   bNrInPins = val;

    for (i = 0; i < bNrInPins; i++)
    {
        if (CurrentByteOffset + 1 > bLength) return 1;
        AddByteEntry(Format("baSourceID%d",i), Format("ID of the Unit or Terminal to which the %d Input Pin of this Mixer Unit is connected.",i),0);

    }

    if (CurrentByteOffset + 1 > bLength) return 1;
    bNrChannels = GetDataByte(Base + CurrentByteOffset);
    AddEntry(CurrentByteOffset, "bNrChannels", bNrChannels,2, Format("This Mixer Unit's audio channel cluster has %d logical output channels",bNrChannels));
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 4 > bLength) return 1;
    AddbmChannelConfigEntry();

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iChannelNames", "Index of a string descriptor, describing the name of the first logical channel.",0);

    sizeN = bLength - 13 - bNrInPins;
    if (CurrentByteOffset + sizeN > bLength) return 1;
    bmMixerConfig = GetNBits(in.Data,((Base+CurrentByteOffset+DataByteHeaderOffset)*8), sizeN * 8);
    SetFieldOffsetLen(((Base+CurrentByteOffset)*8) + sizeN * 8, sizeN * 8);
    AddEntry(CurrentByteOffset, "bmMixerConfig", bmMixerConfig, sizeN * 2, "Bit map indicating which mixing Controls are programmable.",0);
    AddFieldBreak();
    IncCurrByteOffset( sizeN );

    if (CurrentByteOffset + 1 > bLength) return 1;
    bmControls = GetDataByte(base + CurrentByteOffset);
    clusterControl = bmControls & 0x03;
    underflowControl = (bmControls & 0x0C) >> 2;
    overflowControl = (bmControls & 0x30) >> 4;
    clusterControlRow = Find(AudioGeneralControlStatusTable, clusterControl);
    underflowControlRow = Find(AudioGeneralControlStatusTable, underflowControl);
    overflowControlRow = Find(AudioGeneralControlStatusTable, overflowControl);
    reservedText = "&nbsp;&nbsp;D7..6: Reserved, should set to 0";
    AddEntry( CurrentByteOffset, "bmControls", bmControls, 2, "D1..0: Cluster Control Control" + clusterControlRow[1] , 0);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D3..2: Underflow Control" + underflowControlRow[1]);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D5..4: Overflow Control" + overflowControlRow[1]);
    AddDescriptionOnly( NewLine() + reservedText );
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iMixer","Index of a string descriptor, describing the Mixer Unit.",0);
}

SELECTOR_UNIT_v2_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bUnitID", "Constant uniquely identifying the Unit within the audio function. This value is used in all requests to address this Unit.",0);
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrInPins", "Number of Input Pins of this Unit",0);
    bNrInPins = val;

    for (i = 0; i < bNrInPins; i++)
    {
        if (CurrentByteOffset + 1 > bLength) return 1;
        AddByteEntry(Format("baSourceID%d",i), Format("ID of the Unit or Terminal to which the %d Input Pin of this Mixer Unit is connected.",i),0);
    }

    if (CurrentByteOffset + 1 > bLength) return 1;
    bmControls = GetDataByte(base + CurrentByteOffset);
    selectorControl = bmControls & 0x03;
    selectorControlRow = Find(AudioGeneralControlStatusTable, selectorControl);
    reservedText = "D7..2: Reserved, should set to 0";
    AddEntry( CurrentByteOffset, "bmControls", bmControls, 2, "D1..0: Selector Control" + selectorControlRow[1] , 0);
    AddDescriptionOnly( "<br>" + reservedText );
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iSelector", "Index of a string descriptor, describing the Selector Unit.",0);
}

FEATURE_UNIT_v2_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bUnitID", "Constant uniquely identifying the Unit " + "within the audio function. This value is " + "used in all requests to address this Unit.",0);

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSourceID", "ID of the Unit or Terminal to which this Feature Unit is connected.",0);

    sizeN = (bLength - 6) / 4;
    for (i = 0; i < sizeN; i++)
    {
        if (CurrentByteOffset + 4 > bLength) return 1;
        bmControls = GetNBits(in.Data, ((Base + CurrentByteOffset+DataByteHeaderOffset)*8), 32);
        SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 8, 32);
        muteControl = bmControls & 0x00000003;
        volumeControl = (bmControls & 0x0000000C) >> 2;
        bassControl = (bmControls & 0x00000030) >> 4;
        midControl = (bmControls & 0x000000C0) >> 6;
        TrebleControl = (bmControls & 0x00000300) >> 8;
        graphicEqualizerControl = (bmControls & 0x00000C00) >> 10;
        automaticGainControl = (bmControls & 0x00003000) >> 12;
        delayControl = (bmControls & 0x0000C000) >> 14;
        bassBoostControl = (bmControls & 0x00030000) >> 16;
        loudnessControl = (bmControls & 0x000C0000) >> 18;
        inputGainControl = (bmControls & 0x00300000) >> 20;
        inputGainPadControl = (bmControls & 0x000C0000) >> 22;
        phaseInverterControl = (bmControls & 0x03000000) >> 24;
        underflowControl = (bmControls & 0x0C000000) >> 26;
        overflowControl = (bmControls & 0x30000000) >> 28;
        muteControlRow = Find(AudioGeneralControlStatusTable, muteControl);
        volumeControlRow = Find(AudioGeneralControlStatusTable, volumeControl);
        bassControlRow = Find(AudioGeneralControlStatusTable, bassControl);
        midControlRow = Find(AudioGeneralControlStatusTable, midControl);
        TrebleControlRow = Find(AudioGeneralControlStatusTable, TrebleControl);
        graphicEqualizerControlRow = Find(AudioGeneralControlStatusTable, graphicEqualizerControl);
        automaticGainControlRow = Find(AudioGeneralControlStatusTable, automaticGainControl);
        delayControlRow = Find(AudioGeneralControlStatusTable, delayControl);
        bassBoostControlRow = Find(AudioGeneralControlStatusTable, bassBoostControl);
        loudnessControlRow = Find(AudioGeneralControlStatusTable, loudnessControl);
        inputGainControlRow = Find(AudioGeneralControlStatusTable, inputGainControl);
        inputGainPadControlRow = Find(AudioGeneralControlStatusTable, inputGainPadControl);
        phaseInverterControlRow = Find(AudioGeneralControlStatusTable, phaseInverterControl);
        underflowControlRow = Find(AudioGeneralControlStatusTable, underflowControl);
        overflowControlRow = Find(AudioGeneralControlStatusTable, overflowControl);
        reservedText = "D31..30: Reserved, should set to 0";
        #AddEntry( CurrentByteOffset, Format( "bmaControls(%d)", i ), bmControls, 8, "D1..0: Mute Control" + muteControlRow[1] , 0 );

        bmaControlsText = "<html>";
        bmaControlsText += "<br>&nbsp;&nbsp;" + "D1..0: Mute Control" + muteControlRow[1];
        bmaControlsText += "<br>&nbsp;&nbsp;" + "D3..2: Volume Control" + volumeControlRow[1];
        bmaControlsText += "<br>&nbsp;&nbsp;" + "D5..4: Bass Control" + bassControlRow[1];
        bmaControlsText += "<br>&nbsp;&nbsp;" + "D7..6: Mid Control" + midControlRow[1];
        bmaControlsText += "<br>&nbsp;&nbsp;" + "D9..8: Treble Control" + TrebleControlRow[1];
        bmaControlsText += "<br>&nbsp;&nbsp;" + "D11..10: Graphic Equalizer Control" + graphicEqualizerControlRow[1];
        bmaControlsText += "<br>&nbsp;&nbsp;" + "D13..12: Automatic Gain Control" + automaticGainControlRow[1];
        bmaControlsText += "<br>&nbsp;&nbsp;" + "D15..14: Delay Control" + delayControlRow[1];
        bmaControlsText += "<br>&nbsp;&nbsp;" + "D17..16: Bass Control" + bassBoostControlRow[1];
        bmaControlsText += "<br>&nbsp;&nbsp;" + "D19..18: Loudness Control" + loudnessControlRow[1];
        bmaControlsText += "<br>&nbsp;&nbsp;" + "D21..20: Input Gain Control" + inputGainControlRow[1];
        bmaControlsText += "<br>&nbsp;&nbsp;" + "D23..22: Input Gain Pad Control" + inputGainPadControlRow[1];
        bmaControlsText += "<br>&nbsp;&nbsp;" + "D25..24: Phase Inverter Control" + phaseInverterControlRow[1];
        bmaControlsText += "<br>&nbsp;&nbsp;" + "D27..26: Underflow Control" + underflowControlRow[1];
        bmaControlsText += "<br>&nbsp;&nbsp;" + "D29..28: Overflow Control" + overflowControlRow[1];
        bmaControlsText += "<br>&nbsp;&nbsp;" + reservedText + "<br>";
        bmaControlsText += "</html>";

        AddEntry( CurrentByteOffset, Format( "bmaControls(%d)", i ), bmControls, 8, bmaControlsText , 0 );

        AddFieldBreak();
        IncCurrByteOffset( 4 );
    }

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iFeature","Index of a string descriptor, describing this Feature Unit.",0);
}

EFFECT_UNIT_v2_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bUnitID", "Constant uniquely identifying the Unit" + "within the audio function. This value is" + "used in all requests to address this Unit.",0);

    if (CurrentByteOffset + 2 > bLength) return 1;
    wEffectType = GetDataWord(Base + CurrentByteOffset);
    effectTypeRow = Find( AudioEffectUnitEffectTypes_v2_Table, wEffectType);
    AddEntry(CurrentByteOffset, "wEffectType", effectTypeRow[1], 2, FormatEx("Type of the effect this unit is performing %s (0x%04X)",effectTypeRow[1], wEffectType) ,0);
    AddFieldBreak();
    IncCurrByteOffset( 2 );

    if (effectTypeRow[2] != null)
        Call(effectTypeRow[2]);
}

PROCESSING_UNIT_v2_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bUnitID", "Constant uniquely identifying the Unit" + "within the audio function. This value is" + "used in all requests to address this Unit.",0);

    if (CurrentByteOffset + 2 > bLength) return 1;
    wProcessType = GetDataWord(Base + CurrentByteOffset);
    
    processTypeRow = Find( AudioPUPType_v2_Table, wProcessType);
    
    AddEntry(CurrentByteOffset, "wProcessType", processTypeRow[1], 2, FormatEx("Type of the processing this unit is performing %s (0x%04X)",processTypeRow[1], wProcessType) ,0);
    AddFieldBreak();
    IncCurrByteOffset( 2 );

    if (processTypeRow[2] != null)
        Call(processTypeRow[2]);
}

EXTENSION_UNIT_v2_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bUnitID", "Constant uniquely identifying the Unit" + "within the audio function. This value is" + "used in all requests to address this Unit.",0);

    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wExtensionCode", "Vendor-specific code identifying the Extension Unit");

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrInPins", "Number of Input Pins of this Unit",0);
    bNrInPins = val;

    for (i = 0; i < bNrInPins; i++)
    {
        if (CurrentByteOffset + 1 > bLength) return 1;
        AddByteEntry(Format("baSourceID%d",i), Format("ID of the Unit or Terminal to which the Input Pin of this Extension Unit is connected: %d",i),0);

    }
    if (CurrentByteOffset + 1 > bLength) return 1;
    bNrChannels = GetDataByte(Base + CurrentByteOffset);
    AddEntry(CurrentByteOffset, "bNrChannels", bNrChannels,2, Format("This Extension Unit's audio channel cluster has %d logical output channels",bNrChannels));
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 4 > bLength) return 1;
    AddbmChannelConfigEntry();

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iChannelNames", "Index of a string descriptor, describing the name of the first logical channel.",0);

    if (CurrentByteOffset + 1 > bLength) return 1;
    bmControls = GetDataByte(Base + CurrentByteOffset);
    enableControl = bmControls & 0x03;
    clusterControl = (bmControls & 0x0C) >> 2;
    underflowControl = (bmControls & 0x30) >> 4;
    overflowControl = (bmControls & 0xC0) >> 6;
    enableControlRow = Find(AudioGeneralControlStatusTable, enableControl);
    clusterControlRow = Find(AudioGeneralControlStatusTable, clusterControl);
    underflowControlRow = Find(AudioGeneralControlStatusTable, underflowControl);
    overflowControlRow = Find(AudioGeneralControlStatusTable, overflowControl);
    AddEntry( CurrentByteOffset, "bmControls", bmControls, 2, "D1..0: Enable Control" + enableControlRow[1] , 0);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D3..2: Cluster Control" + clusterControlRow[1]);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D5..4: Underflow Control" + underflowControlRow[1]);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D7..6: Overflow Control" + overflowControlRow[1]);
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iExtension", "Index of a string descriptor, describing this Extension Unit.",0);


}

CLOCK_SOURCE_v2_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bClockID", "Constant uniquely identifying the Clock Source Entity within the audio funcion.");

    if (CurrentByteOffset + 1 > bLength) return 1;
    bmAttrButes = GetDataByte(Base + CurrentByteOffset);
    clockType = bmAttrButes & 0x03;
    clockTypeRow = Find(AudioClockSourceClockTypeTable, clockType);
    if (bmAttrButes & 0x04)
        clockSyncText = "D2: 1  Clock synchronized to SOF";
    else
        clockSyncText = "D2: 0 Clock is not synchronized to SOF";

    reservedText = "&nbsp;&nbsp;D7..3: Reserved, should set to 0";
    AddEntry( CurrentByteOffset, "bmAttrButes", bmAttrButes, 2, clockTypeRow[1] , 0);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;" + clockSyncText);
    AddDescriptionOnly( NewLine() + reservedText );
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    bmControls = GetDataByte(Base + CurrentByteOffset);
    frequencyControl = bmControls & 0b00000011;
    validityControl = (bmControls & 0b00001100) >> 2;
    frequencyControlRow = Find(AudioGeneralControlStatusTable, frequencyControl);
    validityControlRow = Find(AudioGeneralControlStatusTable, validityControl);
    reservedText = "&nbsp;&nbsp;D7..4: Reserved, should set to 0";
    AddEntry( CurrentByteOffset, "bmControls", bmControls, 2, "D1..0: Clock Frequency Control" + frequencyControlRow[1] , 0);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D3..2: Clock Validity Control" + validityControlRow[1]);
    AddDescriptionOnly( NewLine() + reservedText );
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 1 > bLength) return 1;
        bAssocTerminal = GetDataByte(Base + CurrentByteOffset);
    if (bAssocTerminal == 0)
        text = "This Clock Source has no association";
    else
        text = Format("This Clock Source is associated with Input Terminal %d",wAssocTerminal);
    AddEntry(CurrentByteOffset, "bAssocTerminal", bAssocTerminal,2, text);
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iClockSource", "Index of a string descriptor, describing the Clock Source Entity");
}


CLOCK_SELECTOR_v2_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bClockID", "Constant uniquely identifying the Clock Selector Entity within the audio function.");

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrInPins", "Number of Input Pins of this Unit",0);
    bNrInPins = val;

    for (i = 0; i < bNrInPins; i++)
    {
        if (CurrentByteOffset + 1 > bLength) return 1;
        AddByteEntry(Format("baCSourceID%d",i), Format("ID of the Clock Entity to which ID %d Clock Input Pin of this Clock Selector Entity is connected",i),0);
    }

    if (CurrentByteOffset + 1 > bLength) return 1;
    bmControls = GetDataByte(Base + CurrentByteOffset);
    selectorControl = bmControls & 0b00000011;
    selectorControlRow = Find(AudioGeneralControlStatusTable, selectorControl);
    reservedText = "&nbsp; D7..2: Reserved, should set to 0";
    AddEntry( CurrentByteOffset, "bmControls", bmControls, 2, "D1..0: Clock Selector Control" + selectorControlRow[1] , 0);
    AddDescriptionOnly( NewLine() + reservedText );
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iClockSelector", "Index of a string descriptor, describing the Clock Selector Entity");

}

CLOCK_MULTIPLIER_v2_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bClockID", "Constant uniquely identifying the Clock Multiplier Entity within the audio funcion.");

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bCSourceID", "ID of the Clock Entity to which the last Clock Input Pin of this Clock Selector Entity is connected");

    if (CurrentByteOffset + 1 > bLength) return 1;
    bmControls = GetDataByte(Base + CurrentByteOffset);
    numeratorControl = bmControls & 0b00000011;
    denominatorControl = (bmControls & 0b00001100) >> 2;
    numeratorControlRow = Find(AudioGeneralControlStatusTable, numeratorControl);
    denominatorControlRow = Find(AudioGeneralControlStatusTable, denominatorControl);
    reservedText = "&nbsp;&nbsp;D7..4: Reserved, should set to 0";
    AddEntry( CurrentByteOffset, "bmControls", bmControls, 2, "D1..0: Clock Numerator Control" + numeratorControlRow[1] , 0);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D3..2: Clock Denominator Control" + denominatorControlRow[1]);
    AddDescriptionOnly( NewLine() + reservedText );
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iClockMultiplier", "Index of a string descriptor, describing the Clock Multiplier Entity");
}

SAMPLE_RATE_CONVERTER_v2_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bUnitID", "Constant uniquely identifying the Unit" + "within the audio function. This value is" + "used in all requests to address this Unit.",0);

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSourceID", "ID of the Unit or Terminal to which this SRC Unit is connected.",0);

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bCSourceInID", "ID of the Clock Entity to which this SRC Unit input section is connected.",0);

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bCSourceOutID", "ID of the Clock Entity to which this SRC Unit output section is connected.",0);

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iSRC", "Index of a string descriptor, describing the SRC Unit");
}

AUDIO_EP_GENERAL_v2_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    bEndpointAddress = GetDataByte(Base + CurrentByteOffset);
    if (bEndpointAddress & 0x80)
        directionTooltip = "D7: Direction. 1 = IN endpoint";
    else
        directionTooltip = "D7: Direction. 0 = OUT endpoint";

    reserveTooltip = "D6..4: Reserved, reset to zero";
    endpointNumberTooltip = Format("D3..0 : The endpoint number 0x%1X", bEndpointAddress & 0x07);
    AddEntry(CurrentByteOffset, "bEndpointAddress", bEndpointAddress, 2, "The address of the endpoint on the USB device described by this descriptor. The address is encoded as follows:",0);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;" + directionTooltip);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;" + reserveTooltip);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;" + endpointNumberTooltip);
    AddFieldBreak();
    IncCurrByteOffset( 2 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    bmAttributes = GetDataByte(Base + CurrentByteOffset);
    toolTip = ToBitDecode_old(AudioEPGeneralAttributes_v1_Bitmap, bmAttributes);
    AddEntry(CurrentByteOffset, "bmAttributes", bmAttributes, 2, toolTip,0);
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wMaxPacketSize", "Maximum packet size this endpoint is capable of sending or receiving when this configuration is selected. Used here to pass 6-byte interrupt information");

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bInterval", "Interval for polling the Interrupt endpoint");
}

#***************************************************************************************************
#Universal Serial Bus Device Class Implementation for Audio Devices Release 3.0 specific
#***************************************************************************************************
INPUT_TERMINAL_v3_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bTerminalID", "Constant uniquely identifying the Terminal within the audio function. This value is used in all requests to address this Terminal.");

    if (CurrentByteOffset + 2 > bLength) return 1;
    wTerminalType = GetDataWord(Base + CurrentByteOffset);
    _row = Find(USBTerminalTypesTable, wTerminalType);
    AddEntry(CurrentByteOffset, "wTerminalType",wTerminalType,4, _row[3]);
    AddFieldBreak();
    IncCurrByteOffset( 2 );

    if (CurrentByteOffset + 1 > bLength) return 1;
        bAssocTerminal = GetDataByte(Base + CurrentByteOffset);
    if (bAssocTerminal == 0)
        text = "This Input Terminal has no association";
    else
        text = Format("This Input Terminal is associated with Output Terminal %d",wAssocTerminal);
    AddEntry(CurrentByteOffset, "bAssocTerminal", bAssocTerminal,2, text);
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bCSourceID", "ID of the Clock Entity to which this Input Terminal is connected.");

    
    if (CurrentByteOffset + 4 > bLength) return 1;
    bmControls = GetNBits(in.Data, ((Base + CurrentByteOffset + DataByteHeaderOffset)*8), 32);
    SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 8, 32);
    
    InsertionControl =  bmControls & 0x00000003;
    OverLoadControl  = (bmControls & 0x0000000C) >> 2;
    UnderflowControl = (bmControls & 0x00000030) >> 4;
    OverflowControl  = (bmControls & 0x000000C0) >> 6;
    
    InsertionControlRow = Find(AudioGeneralControlStatusTable, InsertionControl);
    OverLoadControlRow  = Find(AudioGeneralControlStatusTable, OverLoadControl);
    UnderflowControlRow = Find(AudioGeneralControlStatusTable, UnderflowControl);
    OverflowControlRow  = Find(AudioGeneralControlStatusTable, OverflowControl);

    reservedText = "D31..8: Reserved, should set to 0";
    
    bmControlsText = "<html>";
    bmControlsText += "<br>&nbsp;&nbsp;" + "D1..0: Insertion Control" + InsertionControlRow[1];
    bmControlsText += "<br>&nbsp;&nbsp;" + "D3..2: Overload Control"  + OverLoadControlRow[1];
    bmControlsText += "<br>&nbsp;&nbsp;" + "D5..4: Underflow Control" + UnderflowControlRow[1];
    bmControlsText += "<br>&nbsp;&nbsp;" + "D7..6: Overflow Control"  + OverflowControlRow[1];
    bmControlsText += "<br>&nbsp;&nbsp;" + reservedText + "<br>";
    bmControlsText +="</html>";

    AddEntry( CurrentByteOffset, "bmControls", bmControls, 8, bmControlsText, 0);
    AddFieldBreak();
    IncCurrByteOffset( 4 );
    
    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wClusterDescrID", "ID of the Cluster descriptor for this Input Terminal.", 0);
    
    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wExTerminalDescrID", "ID of the Extended Terminal descriptor for this Input Terminal.", 0);
    
    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wConnectorsDescrID", "ID of the Connectors descriptor for this Input Terminal.", 0);
    
    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wTerminalDescrStr", "ID of a class-specific String descriptor, describing the Input Terminal.", 0);
}

OUTPUT_TERMINAL_v3_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bTerminalID","Constant uniquely identifying the Terminal within the audio function. This value is used in all requests to address this Terminal.",0);

    if (CurrentByteOffset + 2 > bLength) return 1;
    wTerminalType = GetDataWord(Base + CurrentByteOffset);
    _row = Find(USBTerminalTypesTable, wTerminalType);
    AddEntry(CurrentByteOffset, "wTerminalType",wTerminalType,4, _row[3]);
    AddFieldBreak();
    IncCurrByteOffset( 2 );

    if (CurrentByteOffset + 1 > bLength) return 1;
        bAssocTerminal = GetDataByte(Base + CurrentByteOffset);
    if (bAssocTerminal == 0)
        text = "This Output Terminal has no association";
    else
        text = Format("This Output Terminal is associated with Input Terminal %d",wAssocTerminal);
    AddEntry(CurrentByteOffset, "bAssocTerminal", bAssocTerminal,2, text);
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSourceID", "ID of the Unit or Terminal to which this Terminal is connected.",0);

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bCSourceID", "ID of the Clock Entity to which this Output Terminal is connected");

    
    if (CurrentByteOffset + 4 > bLength) return 1;
    bmControls = GetNBits(in.Data, ((Base + CurrentByteOffset + DataByteHeaderOffset)*8), 32);
    SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 8, 32);
    
    InsertionControl =  bmControls & 0x00000003;
    OverLoadControl  = (bmControls & 0x0000000C) >> 2;
    UnderflowControl = (bmControls & 0x00000030) >> 4;
    OverflowControl  = (bmControls & 0x000000C0) >> 6;
    
    InsertionControlRow = Find(AudioGeneralControlStatusTable, InsertionControl);
    OverLoadControlRow  = Find(AudioGeneralControlStatusTable, OverLoadControl);
    UnderflowControlRow = Find(AudioGeneralControlStatusTable, UnderflowControl);
    OverflowControlRow  = Find(AudioGeneralControlStatusTable, OverflowControl);

    reservedText = "D31..8: Reserved, should set to 0";
    
    bmControlsText = "<html>";
    bmControlsText += "<br>&nbsp;&nbsp;" + "D1..0: Insertion Control" + InsertionControlRow[1];
    bmControlsText += "<br>&nbsp;&nbsp;" + "D3..2: Overload Control"  + OverLoadControlRow[1];
    bmControlsText += "<br>&nbsp;&nbsp;" + "D5..4: Underflow Control" + UnderflowControlRow[1];
    bmControlsText += "<br>&nbsp;&nbsp;" + "D7..6: Overflow Control"  + OverflowControlRow[1];
    bmControlsText += "<br>&nbsp;&nbsp;" + reservedText + "<br>";
    bmControlsText +="</html>";
    
    AddEntry( CurrentByteOffset, "bmControls", bmControls, 8, bmControlsText, 0);
    AddFieldBreak();
    IncCurrByteOffset( 4 );
    
    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wExTerminalDescrID", "ID of the Extended Terminal descriptor for this Output Terminal.", 0);
    
    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wConnectorsDescrID", "ID of the Connectors descriptor for this Output Terminal.", 0);
    
    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wTerminalDescrStr", "ID of a class-specific String descriptor, describing the Output Terminal.", 0);
}

EXTENDED_TERMINAL_sub()
{
    AddStringToDlg("The EXTENDED_TERMINAL interface descriptor subtypes is just supported by HIGH CAPABILITY_DESCRIPTOR REQUEST","","",_ERROR);
    return 0;
}

MIXER_UNIT_v3_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bUnitID","Constant uniquely identifying the Unit within the audio function. This value is used in all requests to address this Unit.",0);

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrInPins", "Number of Input Pins of this Unit",0);
    bNrInPins = val;

    for (i = 0 ; i < bNrInPins ; i++)
    {
        if (CurrentByteOffset + 1 > bLength) return 1;
        AddByteEntry(Format("baSourceID%d",i), Format("ID of the Unit or Terminal to which the %d Input Pin of this Mixer Unit is connected.",i), 0);
    }
    
    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wClusterDescrID", "ID of the Cluster descriptor for this Mixer Unit.", 0);

    size_n = bLength - 13 - bNrInPins;
    
    if (CurrentByteOffset + size_n > bLength) return 1;
    bmMixerControls = GetNBits(in.Data,((Base + CurrentByteOffset + DataByteHeaderOffset)*8), size_n * 8);
    SetFieldOffsetLen(((Base+CurrentByteOffset)*8) + size_n * 8, size_n * 8);
    AddEntry(CurrentByteOffset, "bmMixerControls", bmMixerControls, size_n * 2, "Bit map indicating which mixing controls are programmable.",0);
    AddFieldBreak();
    IncCurrByteOffset( size_n );
    
    if (CurrentByteOffset + 4 > bLength) return 1;
    bmControls = GetNBits(in.Data, ((Base + CurrentByteOffset + DataByteHeaderOffset)*8), 32);
    SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 8, 32);
    
    UnderflowControl =  bmControls & 0x00000003;
    OverflowControl  = (bmControls & 0x0000000C) >> 2;

    UnderflowControlRow = Find(AudioGeneralControlStatusTable, UnderflowControl);
    OverflowControlRow  = Find(AudioGeneralControlStatusTable, OverflowControl);
    
    reservedText = "D31..4: Reserved, should set to 0";
    
    bmControlsText = "<html>";
    bmControlsText += "<br>&nbsp;&nbsp;" + "D5..4: Underflow Control" + UnderflowControlRow[1];
    bmControlsText += "<br>&nbsp;&nbsp;" + "D7..6: Overflow Control"  + OverflowControlRow[1];
    bmControlsText += "<br>&nbsp;&nbsp;" + reservedText + "<br>";
    bmControlsText +="</html>";
    
    AddEntry( CurrentByteOffset, "bmControls", bmControls, 8, bmControlsText, 0);
    AddFieldBreak();
    IncCurrByteOffset( 4 );
    
    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wMixerDescrStr", "ID of a class-specific String descriptor, describing the Mixer Unit.", 0);
}

SELECTOR_UNIT_v3_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bUnitID", "Constant uniquely identifying the Unit within the audio function. This value is used in all requests to address this Unit.",0);
    
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrInPins", "Number of Input Pins of this Unit",0);
    bNrInPins = val;

    for (i = 0; i < bNrInPins; i++)
    {
        if (CurrentByteOffset + 1 > bLength) return 1;
        AddByteEntry(Format("baSourceID%d",i), Format("ID of the Unit or Terminal to which the %d Input Pin of this Mixer Unit is connected.",i),0);
    }

    if (CurrentByteOffset + 4 > bLength) return 1;
    bmControls = GetNBits(in.Data, ((Base + CurrentByteOffset + DataByteHeaderOffset)*8), 32);
    SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 8, 32);
    
    selectorControl = bmControls & 0x00000003;
    selectorControlRow = Find(AudioGeneralControlStatusTable, selectorControl);
    
    reservedText = "D31..2: Reserved, should set to 0";
    
    AddEntry( CurrentByteOffset, "bmControls", bmControls, 8, "D1..0: Selector Control" + selectorControlRow[1] , 0);
    AddDescriptionOnly( "<br>" + reservedText );
    AddFieldBreak();
    IncCurrByteOffset( 4 );

    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wSelectorDescrStr", "ID of a class-specific String descriptor, describing the Selector Unit.", 0);
}

FEATURE_UNIT_v3_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bUnitID", "Constant uniquely identifying the Unit " + "within the audio function. This value is " + "used in all requests to address this Unit.",0);

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSourceID", "ID of the Unit or Terminal to which this Feature Unit is connected.",0);

    sizeN = (bLength - 6) / 4;
    
    for (i = 0; i < sizeN; i++)
    {
        if (CurrentByteOffset + 4 > bLength) return 1;
        bmControls = GetNBits(in.Data, ((Base + CurrentByteOffset+DataByteHeaderOffset)*8), 32);
        
        SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 8, 32);
        
        muteControl   =  bmControls & 0x00000003;
        volumeControl = (bmControls & 0x0000000C) >> 2;
        bassControl   = (bmControls & 0x00000030) >> 4;
        midControl    = (bmControls & 0x000000C0) >> 6;
        TrebleControl = (bmControls & 0x00000300) >> 8;
        graphicEqualizerControl = (bmControls & 0x00000C00) >> 10;
        automaticGainControl    = (bmControls & 0x00003000) >> 12;
        delayControl            = (bmControls & 0x0000C000) >> 14;
        bassBoostControl        = (bmControls & 0x00030000) >> 16;
        loudnessControl         = (bmControls & 0x000C0000) >> 18;
        inputGainControl        = (bmControls & 0x00300000) >> 20;
        inputGainPadControl     = (bmControls & 0x000C0000) >> 22;
        phaseInverterControl    = (bmControls & 0x03000000) >> 24;
        underflowControl        = (bmControls & 0x0C000000) >> 26;
        overflowControl         = (bmControls & 0x30000000) >> 28;
        muteControlRow          = Find(AudioGeneralControlStatusTable, muteControl);
        volumeControlRow        = Find(AudioGeneralControlStatusTable, volumeControl);
        bassControlRow          = Find(AudioGeneralControlStatusTable, bassControl);
        midControlRow           = Find(AudioGeneralControlStatusTable, midControl);
        TrebleControlRow        = Find(AudioGeneralControlStatusTable, TrebleControl);
        graphicEqualizerControlRow = Find(AudioGeneralControlStatusTable, graphicEqualizerControl);
        automaticGainControlRow    = Find(AudioGeneralControlStatusTable, automaticGainControl);
        delayControlRow            = Find(AudioGeneralControlStatusTable, delayControl);
        bassBoostControlRow        = Find(AudioGeneralControlStatusTable, bassBoostControl);
        loudnessControlRow         = Find(AudioGeneralControlStatusTable, loudnessControl);
        inputGainControlRow        = Find(AudioGeneralControlStatusTable, inputGainControl);
        inputGainPadControlRow     = Find(AudioGeneralControlStatusTable, inputGainPadControl);
        phaseInverterControlRow    = Find(AudioGeneralControlStatusTable, phaseInverterControl);
        underflowControlRow        = Find(AudioGeneralControlStatusTable, underflowControl);
        overflowControlRow         = Find(AudioGeneralControlStatusTable, overflowControl);
        
        reservedText = "D31..30: Reserved, should set to 0";

        bmaControlsText = "<html>";
        bmaControlsText += "<br>&nbsp;&nbsp;" + "D1..0: Mute Control" + muteControlRow[1];
        bmaControlsText += "<br>&nbsp;&nbsp;" + "D3..2: Volume Control" + volumeControlRow[1];
        bmaControlsText += "<br>&nbsp;&nbsp;" + "D5..4: Bass Control" + bassControlRow[1];
        bmaControlsText += "<br>&nbsp;&nbsp;" + "D7..6: Mid Control" + midControlRow[1];
        bmaControlsText += "<br>&nbsp;&nbsp;" + "D9..8: Treble Control" + TrebleControlRow[1];
        bmaControlsText += "<br>&nbsp;&nbsp;" + "D11..10: Graphic Equalizer Control" + graphicEqualizerControlRow[1];
        bmaControlsText += "<br>&nbsp;&nbsp;" + "D13..12: Automatic Gain Control" + automaticGainControlRow[1];
        bmaControlsText += "<br>&nbsp;&nbsp;" + "D15..14: Delay Control" + delayControlRow[1];
        bmaControlsText += "<br>&nbsp;&nbsp;" + "D17..16: Bass Control" + bassBoostControlRow[1];
        bmaControlsText += "<br>&nbsp;&nbsp;" + "D19..18: Loudness Control" + loudnessControlRow[1];
        bmaControlsText += "<br>&nbsp;&nbsp;" + "D21..20: Input Gain Control" + inputGainControlRow[1];
        bmaControlsText += "<br>&nbsp;&nbsp;" + "D23..22: Input Gain Pad Control" + inputGainPadControlRow[1];
        bmaControlsText += "<br>&nbsp;&nbsp;" + "D25..24: Phase Inverter Control" + phaseInverterControlRow[1];
        bmaControlsText += "<br>&nbsp;&nbsp;" + "D27..26: Underflow Control" + underflowControlRow[1];
        bmaControlsText += "<br>&nbsp;&nbsp;" + "D29..28: Overflow Control" + overflowControlRow[1];
        bmaControlsText += "<br>&nbsp;&nbsp;" + reservedText + "<br>";
        bmaControlsText += "</html>";

        AddEntry( CurrentByteOffset, Format( "bmaControls(%d)", i ), bmControls, 8, bmaControlsText , 0 );

        AddFieldBreak();
        IncCurrByteOffset( 4 );
    }

    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wFeatureDescrStr", "ID of a class-specific String descriptor, describing the Feature Unit.", 0);
}

EFFECT_UNIT_v3_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bUnitID", "Constant uniquely identifying the Unit" + "within the audio function. This value is" + "used in all requests to address this Unit.",0);

    if (CurrentByteOffset + 2 > bLength) return 1;
    wEffectType = GetDataWord(Base + CurrentByteOffset);
    effectTypeRow = Find( AudioEffectUnitEffectTypes_v3_Table, wEffectType);
    
    AddEntry(CurrentByteOffset, "wEffectType", effectTypeRow[1], 2, FormatEx("Type of the effect this unit is performing %s (0x%04X)",effectTypeRow[1], wEffectType) ,0);
    AddFieldBreak();
    IncCurrByteOffset( 2 );

    if (effectTypeRow[2] != null)
        Call(effectTypeRow[2]);
}

PROCESSING_UNIT_v3_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bUnitID", "Constant uniquely identifying the Unit" + "within the audio function. This value is" + "used in all requests to address this Unit.",0);

    if (CurrentByteOffset + 2 > bLength) return 1;
    wProcessType = GetDataWord(Base + CurrentByteOffset);
    
    processTypeRow = Find( AudioPUPType_v3_Table, wProcessType);
    
    AddEntry(CurrentByteOffset, "wProcessType", processTypeRow[1], 2, FormatEx("Type of the processing this unit is performing %s (0x%04X)",processTypeRow[1], wProcessType) ,0);
    AddFieldBreak();
    IncCurrByteOffset( 2 );

    if (processTypeRow[2] != null)
        Call(processTypeRow[2]);
}

EXTENSION_UNIT_v3_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bUnitID", "Constant uniquely identifying the Unit" + "within the audio function. This value is" + "used in all requests to address this Unit.",0);

    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wExtensionCode", "Vendor-specific code identifying the Extension Unit");

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrInPins", "Number of Input Pins of this Unit",0);
    bNrInPins = val;

    for (i = 0; i < bNrInPins; i++)
    {
        if (CurrentByteOffset + 1 > bLength) return 1;
        AddByteEntry(Format("baSourceID%d",i), Format("ID of the Unit or Terminal to which the Input Pin of this Extension Unit is connected: %d",i),0);

    }
    
    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wExtensionDescrStr", "ID of a class-specific String descriptor, describing the Extension Unit.", 0);
    
    if (CurrentByteOffset + 4 > bLength) return 1;
    bmControls = GetNBits(in.Data, ((Base + CurrentByteOffset+DataByteHeaderOffset)*8), 32);
    
    SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 8, 32);
    
    underflowControl =  bmControls & 0x00000003;
    overflowControl  = (bmControls & 0x0000000C) >> 2;
    
    underflowControlRow = Find(AudioGeneralControlStatusTable, underflowControl);
    overflowControlRow  = Find(AudioGeneralControlStatusTable, overflowControl);
    
    reservedText = "D31..4: Reserved";
    
    AddEntry( CurrentByteOffset, "bmControls", bmControls, 8, "D1..0: Underflow Control" + underflowControlRow[1] , 0);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D3..2: Overflow Control" + overflowControlRow[1]);
    AddDescriptionOnly( NewLine() + reservedText );
    AddFieldBreak();
    IncCurrByteOffset( 4 );
    
    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wClusterDescrID", "Unique ID of the Cluster descriptor for this Extension Unit.", 0);
}

CLOCK_SOURCE_v3_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bClockID", "Constant uniquely identifying the Clock Source Entity within the audio funcion.");

    if (CurrentByteOffset + 1 > bLength) return 1;
    bmAttrButes = GetDataByte(Base + CurrentByteOffset);
    
    if (bmAttrButes & 0x01)
        clockTypeText = "D0: 1 Internal Clock";
    else
        clockTypeText = "D0: 0 External Clock";
    
    if ((bmAttrButes & 0x02) >> 1)
        SynchronizationTypeText = "D1: 1 Clock synchronized to SOF";
    else
        SynchronizationTypeText = "D1: 0 Asynchronous";

    reservedText = "&nbsp;&nbsp;D7..2: Reserved, should set to 0";
    
    AddEntry( CurrentByteOffset, "bmAttrButes", bmAttrButes, 2, clockTypeText , 0);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;" + SynchronizationTypeText);
    AddDescriptionOnly( NewLine() + reservedText );
    AddFieldBreak();
    IncCurrByteOffset( 1 );
    
    
    if (CurrentByteOffset + 4 > bLength) return 1;
    bmControls = GetNBits(in.Data, ((Base + CurrentByteOffset+DataByteHeaderOffset)*8), 32);
    
    SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 8, 32);
    
    frequencyControl =  bmControls & 0x00000003;
    validityControl  = (bmControls & 0x0000000C) >> 2;
    
    frequencyControlRow = Find(AudioGeneralControlStatusTable, frequencyControl);
    validityControlRow  = Find(AudioGeneralControlStatusTable, validityControl);
    
    reservedText = "&nbsp;&nbsp;D31..4: Reserved";
    
    AddEntry( CurrentByteOffset, "bmControls", bmControls, 2, "D1..0: Clock Frequency Control" + frequencyControlRow[1] , 0);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D3..2: Clock Validity Control" + validityControlRow[1]);
    AddDescriptionOnly( NewLine() + reservedText );
    AddFieldBreak();
    IncCurrByteOffset( 4 );
    
    
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bReferenceTerminal", "Terminal ID of the Terminal from which this Clock Source is derived.");
    
    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wClockSourceStr", "ID of a class-specific String descriptor, describing the Clock Source Entity.", 0);
}

CLOCK_SELECTOR_v3_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bClockID", "Constant uniquely identifying the Clock Selector Entity within the audio function.");

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrInPins", "Number of Input Pins of this Unit",0);
    bNrInPins = val;

    for (i = 0; i < bNrInPins; i++)
    {
        if (CurrentByteOffset + 1 > bLength) return 1;
        AddByteEntry(Format("baCSourceID%d",i), Format("ID of the Clock Entity to which ID %d Clock Input Pin of this Clock Selector Entity is connected",i),0);
    }

    
    if (CurrentByteOffset + 4 > bLength) return 1;
    bmControls = GetNBits(in.Data, ((Base + CurrentByteOffset+DataByteHeaderOffset)*8), 32);
    SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 8, 32);
    
    selectorControl = bmControls & 0x00000003;
    
    selectorControlRow = Find(AudioGeneralControlStatusTable, selectorControl);
    
    reservedText = "&nbsp; D31..2: Reserved";
    
    AddEntry( CurrentByteOffset, "bmControls", bmControls, 8, "D1..0: Clock Selector Control" + selectorControlRow[1] , 0);
    AddDescriptionOnly( NewLine() + reservedText );
    AddFieldBreak();
    IncCurrByteOffset( 4 );

    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wCSelectorDescrStr", "ID of a class-specific String descriptor, describing the Clock Selector Entity.", 0);
}

CLOCK_MULTIPLIER_v3_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bClockID", "Constant uniquely identifying the Clock Multiplier Entity within the audio funcion.");

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bCSourceID", "ID of the Clock Entity to which the last Clock Input Pin of this Clock Selector Entity is connected");

    if (CurrentByteOffset + 4 > bLength) return 1;
    bmControls = GetNBits(in.Data, ((Base + CurrentByteOffset+DataByteHeaderOffset)*8), 32);
    SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 8, 32);
    
    numeratorControl   =  bmControls & 0x00000003;
    denominatorControl = (bmControls & 0x0000000C) >> 2;
    
    numeratorControlRow   = Find(AudioGeneralControlStatusTable, numeratorControl);
    denominatorControlRow = Find(AudioGeneralControlStatusTable, denominatorControl);
    
    reservedText = "&nbsp;&nbsp;D31..4: Reserved";
    
    AddEntry( CurrentByteOffset, "bmControls", bmControls, 8, "D1..0: Clock Numerator Control" + numeratorControlRow[1] , 0);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D3..2: Clock Denominator Control" + denominatorControlRow[1]);
    AddDescriptionOnly( NewLine() + reservedText );
    AddFieldBreak();
    IncCurrByteOffset( 4 );

    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wCMultiplierDescrStr", "ID of a class-specific String descriptor, describing the Clock Multiplier Entity.", 0);
}

SAMPLE_RATE_CONVERTER_v3_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bUnitID", "Constant uniquely identifying the Unit" + "within the audio function. This value is" + "used in all requests to address this Unit.",0);

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSourceID", "ID of the Unit or Terminal to which this SRC Unit is connected.",0);

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bCSourceInID", "ID of the Clock Entity to which this SRC Unit input section is connected.",0);

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bCSourceOutID", "ID of the Clock Entity to which this SRC Unit output section is connected.",0);

    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wSRCDescrStr", "ID of a class-specific String descriptor, describing the SRC Unit.", 0);
}

CONNECTORS_sub()
{
    AddStringToDlg("The CONNECTORS interface descriptor subtypes is just supported by HIGH CAPABILITY_DESCRIPTOR REQUEST","","",_ERROR);
    return 0;
}

POWER_DOMAIN_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bPowerDomainID", "Value uniquely identifying the Power Domain within the Audio Function.");
    
    if (CurrentByteOffset + 2 > bLength) return 1;  
    AddWordEntry("waRecoveryTime(1)", "Time to recover from D1 to D0. Expressed in 50us increments.", 0);
    
    if (CurrentByteOffset + 2 > bLength) return 1;  
    AddWordEntry("waRecoveryTime(2)", "Time to recover from D2 to D0. Expressed in 50us increments.", 0);
    
    if (CurrentByteOffset + 1 > bLength) return 1;
    bNrEntities = GetDataByte(base + CurrentByteOffset);
    AddEntry(CurrentByteOffset, "bNrEntities", bNrEntities, 2, Format("Number of Entities belonging to this Power Domain: %d", bNrEntities));
    AddFieldBreak();
    IncCurrByteOffset( 1 );
    
    for (i = 0 ; i < bNrEntities ; i++)
    {
        if (CurrentByteOffset + 1 > bLength) return 1;
        AddByteEntry(Format("baEntityID(%d)", i + 1), "ID of the Entity that belongs to this Power Domain.", 0);
    }
    
    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wPDomainDescrStr", "ID of a class-specific String descriptor, describing this Power Domain.", 0);
}
################################################################
# Audio Devices sub functions for EFFECT_UNIT Audio 2.0 and 3.0
################################################################
MOD_DELAY_EFFECT_v2_v3_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSourceID", "ID of the Unit or Terminal to which this Feature Unit is connected.",0);
    
    basic_size = 0;
    if (MostRecentProtocol == IP_VERSION_02_00)
    {
        basic_size = 16;
    }
    else if (MostRecentProtocol == IP_VERSION_03_00)
    {
        basic_size = 17;
    }

    sizeN = (bLength - basic_size) / 4;
    for (i = 0; i < sizeN; i++)
    {
        if (CurrentByteOffset + 4 > bLength) return 1;
        bmControls = GetNBits(in.Data, ((Base + CurrentByteOffset+DataByteHeaderOffset)*8), 32);
        SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 8, 32);
        enableControl = bmControls & 0x00000003;
        balanceControl = (bmControls & 0x0000000C) >> 2;
        rateControl = (bmControls & 0x00000030) >> 4;
        depthControl = (bmControls & 0x000000C0) >> 6;
        timeControl = (bmControls & 0x00000300) >> 8;
        feedbackLevelControl = (bmControls & 0x00000C00) >> 10;
        underflowControl = (bmControls & 0x00003000) >> 12;
        overflowControl = (bmControls & 0x0000C000) >> 14;

        enableControlRow = Find(AudioGeneralControlStatusTable, enableControl);
        balanceControlRow = Find(AudioGeneralControlStatusTable, balanceControl);
        rateControlRow = Find(AudioGeneralControlStatusTable, rateControl);
        depthControlRow = Find(AudioGeneralControlStatusTable, depthControl);
        timeControlRow = Find(AudioGeneralControlStatusTable, timeControl);
        feedbackLevelControlRow = Find(AudioGeneralControlStatusTable, feedbackLevelControl);
        underflowControlRow = Find(AudioGeneralControlStatusTable, underflowControl);
        overflowControlRow = Find(AudioGeneralControlStatusTable, overflowControl);
        reservedText = "&nbsp;&nbsp;D31..16: Reserved, should set to 0";
        AddEntry( CurrentByteOffset, "bmControls", bmControls, 8, "D1..0: Enable Control" + enableControlRow[1] , 0);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D3..2: Balance Control" + balanceControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D5..4: Rate Control" + rateControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D7..6: Depth Control" + depthControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D9..8: Time Control" + timeControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D11..10: Feedback Level Control" + feedbackLevelControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D13..12: Underflow Control" + underflowControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D15..14: Overflow Control" + overflowControlRow[1]);
        AddDescriptionOnly( NewLine() + reservedText );
        AddFieldBreak();
        IncCurrByteOffset( 4 );
    }

    if (MostRecentProtocol == IP_VERSION_02_00)
    {
        if (CurrentByteOffset + 1 > bLength) return 1;
        AddByteEntry("iEffects","Index of a string descriptor, describing this Effect Unit.",0);
    }
    else if (MostRecentProtocol == IP_VERSION_03_00)
    {
        if (CurrentByteOffset + 2 > bLength) return 1;
        AddWordEntry("wEffectsDescrStr", "ID of a class-specific String descriptor, describing the Effect Unit.", 0);
    }
}

DYN_RANGE_COMP_EFFECT_v2_v3_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSourceID", "ID of the Unit or Terminal to which this Feature Unit is connected.",0);

    basic_size = 0;
    if (MostRecentProtocol == IP_VERSION_02_00)
    {
        basic_size = 16;
    }
    else if (MostRecentProtocol == IP_VERSION_03_00)
    {
        basic_size = 17;
    }
    
    sizeN = (bLength - basic_size) / 4;
    for (i = 0; i < sizeN; i++)
    {
        if (CurrentByteOffset + 4 > bLength) return 1;
        bmControls = GetNBits(in.Data, ((Base + CurrentByteOffset+DataByteHeaderOffset)*8), 32);
        SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 8, 32);
        enableControl = bmControls & 0x00000003;
        compressionRadioControl = (bmControls & 0x0000000C) >> 2;
        maxAmplControl = (bmControls & 0x00000030) >> 4;
        thresholdControl = (bmControls & 0x000000C0) >> 6;
        attackTimeControl = (bmControls & 0x00000300) >> 8;
        releaseTimeControl = (bmControls & 0x00000C00) >> 10;
        underflowControl = (bmControls & 0x00003000) >> 12;
        overflowControl = (bmControls & 0x0000C000) >> 14;

        enableControlRow = Find(AudioGeneralControlStatusTable, enableControl);
        compressionRadioControlRow = Find(AudioGeneralControlStatusTable, compressionRadioControl);
        maxAmplControlRow = Find(AudioGeneralControlStatusTable, maxAmplControl);
        thresholdControlRow = Find(AudioGeneralControlStatusTable, thresholdControl);
        attackTimeControlRow = Find(AudioGeneralControlStatusTable, attackTimeControl);
        releaseTimeControlRow = Find(AudioGeneralControlStatusTable, releaseTimeControl);
        underflowControlRow = Find(AudioGeneralControlStatusTable, underflowControl);
        overflowControlRow = Find(AudioGeneralControlStatusTable, overflowControl);
        reservedText = "&nbsp;&nbsp;D31..16: Reserved, should set to 0";
        AddEntry( CurrentByteOffset, "bmControls", bmControls, 8, "D1..0: Enable Control" + enableControlRow[1] , 0);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D3..2: Compression Ratio Control" + compressionRadioControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D5..4: MaxAmpl Control" + maxAmplControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D7..6: Threshold Control" + thresholdControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D9..8: Attack Time Control" + attackTimeControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D11..10: Release Time Control" + releaseTimeControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D13..12: Underflow Control" + underflowControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D15..14: Overflow Control" + overflowControlRow[1]);
        AddDescriptionOnly( NewLine() + reservedText );
        AddFieldBreak();
        IncCurrByteOffset( 4 );

    }

    if (MostRecentProtocol == IP_VERSION_02_00)
    {
        if (CurrentByteOffset + 1 > bLength) return 1;
        AddByteEntry("iEffects","Index of a string descriptor, describing this Effect Unit.",0);
    }
    else if (MostRecentProtocol == IP_VERSION_03_00)
    {
        if (CurrentByteOffset + 2 > bLength) return 1;
        AddWordEntry("wEffectsDescrStr", "ID of a class-specific String descriptor, describing the Effect Unit.", 0);
    }
}

################################################################
# Audio Devices sub functions for EFFECT_UNIT_v2_sub()
################################################################
PARAM_EQ_SECTION_EFFECT_v2_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSourceID", "ID of the Unit or Terminal to which this Feature Unit is connected.",0);

    sizeN = (bLength - 16) / 4;
    for (i = 0; i < sizeN; i++)
    {
        if (CurrentByteOffset + 4 > bLength) return 1;
        bmControls = GetNBits(in.Data, ((Base + CurrentByteOffset+DataByteHeaderOffset)*8), 32);
        SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 8, 32);
        enableControl = bmControls & 0x00000003;
        centerFrequencyControl = (bmControls & 0x0000000C) >> 2;
        qFactorControl = (bmControls & 0x00000030) >> 4;
        gainControl = (bmControls & 0x000000C0) >> 6;
        underflowControl = (bmControls & 0x00000300) >> 8;
        overflowControl = (bmControls & 0x00000C00) >> 10;
        enableControlRow = Find(AudioGeneralControlStatusTable, enableControl);
        centerFrequencyControlRow = Find(AudioGeneralControlStatusTable, centerFrequencyControl);
        qFactorControlRow = Find(AudioGeneralControlStatusTable, qFactorControl);
        gainControlRow = Find(AudioGeneralControlStatusTable, gainControl);
        underflowControlRow = Find(AudioGeneralControlStatusTable, underflowControl);
        overflowControlRow = Find(AudioGeneralControlStatusTable, overflowControl);
        reservedText = "&nbsp;&nbsp;D31..12: Reserved, should set to 0";
        AddEntry( CurrentByteOffset, "bmControls", bmControls, 8, "D1..0: Enable Control" + enableControlRow[1] , 0);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D3..2: Center Frequency Control" + centerFrequencyControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D5..4: Q Factor Control" + qFactorControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D7..6: Gain Control" + gainControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D9..8: Underflow Control" + underflowControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D11..10: Overflow Control" + overflowControlRow[1]);
        AddDescriptionOnly( NewLine() + reservedText );
        AddFieldBreak();
        IncCurrByteOffset( 4 );

    }

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iEffects","Index of a string descriptor, describing this Effect Unit.",0);
}

REVERBERATION_EFFECT_v2_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSourceID", "ID of the Unit or Terminal to which this Feature Unit is connected.",0);

    sizeN = (bLength - 16) / 4;
    for (i = 0; i < sizeN; i++)
    {
        if (CurrentByteOffset + 4 > bLength) return 1;
        bmControls = GetNBits(in.Data, ((Base + CurrentByteOffset+DataByteHeaderOffset)*8), 32);
        SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 8, 32);
        enableControl = bmControls & 0x00000003;
        typeControl = (bmControls & 0x0000000C) >> 2;
        levelControl = (bmControls & 0x00000030) >> 4;
        timeControl = (bmControls & 0x000000C0) >> 6;
        delayFeedbackControl = (bmControls & 0x00000300) >> 8;
        preDelayControl = (bmControls & 0x00000C00) >> 10;
        densityControl = (bmControls & 0x00003000) >> 12;
        hiFreqRollOffControl = (bmControls & 0x0000C000) >> 14;
        underflowControl = (bmControls & 0x00030000) >> 16;
        overflowControl = (bmControls & 0x000C0000) >> 18;

        enableControlRow = Find(AudioGeneralControlStatusTable, enableControl);
        typeControlRow = Find(AudioGeneralControlStatusTable, typeControl);
        levelControlRow = Find(AudioGeneralControlStatusTable, levelControl);
        timeControlRow = Find(AudioGeneralControlStatusTable, timeControl);
        delayFeedbackControlRow = Find(AudioGeneralControlStatusTable, delayFeedbackControl);
        preDelayControlRow = Find(AudioGeneralControlStatusTable, preDelayControl);
        densityControlRow = Find(AudioGeneralControlStatusTable, densityControl);
        hiFreqRollOffControlRow = Find(AudioGeneralControlStatusTable, hiFreqRollOffControl);
        underflowControlRow = Find(AudioGeneralControlStatusTable, underflowControl);
        overflowControlRow = Find(AudioGeneralControlStatusTable, overflowControl);
        reservedText = "&nbsp;&nbsp;D31..20: Reserved, should set to 0";
        AddEntry( CurrentByteOffset, "bmControls", bmControls, 8, "D1..0: Enable Control" + enableControlRow[1] , 0);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D3..2: Type Control" + typeControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D5..4: Level Control" + levelControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D7..6: Time Control" + timeControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D9..8: Delay Feedback Control" + delayFeedbackControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D11..10: Pre-Delay Control" + preDelayControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D13..12: Density Control" + densityControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D15..14: Hi-Freq Roll-Off Control" + hiFreqRollOffControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D17..16: Underflow Control" + underflowControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D19..18: Overflow Control" + overflowControlRow[1]);
        AddDescriptionOnly( NewLine() + reservedText );
        AddFieldBreak();
        IncCurrByteOffset( 4 );

    }

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iEffects","Index of a string descriptor, describing this Effect Unit.",0);
}

################################################################
# Audio Devices sub functions for EFFECT_UNIT_v3_sub()
################################################################
PARAM_EQ_SECTION_EFFECT_v3_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSourceID", "ID of the Unit or Terminal to which this Feature Unit is connected.",0);

    sizeN = (bLength - 17) / 4;
    for (i = 0; i < sizeN; i++)
    {
        if (CurrentByteOffset + 4 > bLength) return 1;
        
        bmControls = GetNBits(in.Data, ((Base + CurrentByteOffset+DataByteHeaderOffset)*8), 32);
        SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 8, 32);
        
        centerFrequencyControl =  bmControls & 0x00000003;
        qFactorControl         = (bmControls & 0x0000000C) >> 2;
        gainControl            = (bmControls & 0x00000030) >> 4;
        underflowControl       = (bmControls & 0x000000C0) >> 6;
        overflowControl        = (bmControls & 0x00000300) >> 8;
        
        centerFrequencyControlRow = Find(AudioGeneralControlStatusTable, centerFrequencyControl);
        qFactorControlRow         = Find(AudioGeneralControlStatusTable, qFactorControl);
        gainControlRow            = Find(AudioGeneralControlStatusTable, gainControl);
        underflowControlRow       = Find(AudioGeneralControlStatusTable, underflowControl);
        overflowControlRow        = Find(AudioGeneralControlStatusTable, overflowControl);

        reservedText = "&nbsp;&nbsp;D31..10: Reserved, should set to 0";
        
        AddEntry( CurrentByteOffset, "bmControls", bmControls, 8, "D1..0: Center Frequency Control" + centerFrequencyControlRow[1] , 0);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D3..2: Q Factor Control" + qFactorControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D5..4: Gain Control" + gainControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D7..6: Underflow Control" + underflowControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D9..8: Overflow Control" + overflowControlRow[1]);
        
        AddDescriptionOnly( NewLine() + reservedText );
        AddFieldBreak();
        IncCurrByteOffset( 4 );
    }

    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wEffectsDescrStr", "ID of a class-specific String descriptor, describing the Effect Unit.", 0);
}

EVERBERATION_EFFECT_v3_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSourceID", "ID of the Unit or Terminal to which this Feature Unit is connected.",0);

    sizeN = (bLength - 17) / 4;
    
    for (i = 0; i < sizeN; i++)
    {
        if (CurrentByteOffset + 4 > bLength) return 1;
        bmControls = GetNBits(in.Data, ((Base + CurrentByteOffset+DataByteHeaderOffset)*8), 32);
        SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 8, 32);
        
        typeControl          =  bmControls & 0x00000003;
        levelControl         = (bmControls & 0x0000000C) >> 2;
        timeControl          = (bmControls & 0x00000030) >> 4;
        delayFeedbackControl = (bmControls & 0x000000C0) >> 6;
        preDelayControl      = (bmControls & 0x00000300) >> 8;
        densityControl       = (bmControls & 0x00000C00) >> 10;
        hiFreqRollOffControl = (bmControls & 0x00003000) >> 12;
        underflowControl     = (bmControls & 0x0000C000) >> 14;
        overflowControl      = (bmControls & 0x00030000) >> 16;

        typeControlRow          = Find(AudioGeneralControlStatusTable, typeControl);
        levelControlRow         = Find(AudioGeneralControlStatusTable, levelControl);
        timeControlRow          = Find(AudioGeneralControlStatusTable, timeControl);
        delayFeedbackControlRow = Find(AudioGeneralControlStatusTable, delayFeedbackControl);
        preDelayControlRow      = Find(AudioGeneralControlStatusTable, preDelayControl);
        densityControlRow       = Find(AudioGeneralControlStatusTable, densityControl);
        hiFreqRollOffControlRow = Find(AudioGeneralControlStatusTable, hiFreqRollOffControl);
        underflowControlRow     = Find(AudioGeneralControlStatusTable, underflowControl);
        overflowControlRow      = Find(AudioGeneralControlStatusTable, overflowControl);
        
        reservedText = "&nbsp;&nbsp;D31..18: Reserved, should set to 0";
        
        AddEntry( CurrentByteOffset, "bmControls", bmControls, 8, "D1..0: Type Control" + typeControlRow[1] , 0);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D3..2: Level Control" + levelControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D5..4: Time Control" + timeControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D7..6: Delay Feedback Control" + delayFeedbackControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D9..8: Pre-Delay Control" + preDelayControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D11..10: Density Control" + densityControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D13..12: Hi-Freq Roll-Off Control" + hiFreqRollOffControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D15..14: Underflow Control" + underflowControlRow[1]);
        AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D17..16: Overflow Control" + overflowControlRow[1]);
        AddDescriptionOnly( NewLine() + reservedText );
        AddFieldBreak();
        IncCurrByteOffset( 4 );
    }

    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wEffectsDescrStr", "ID of a class-specific String descriptor, describing the Effect Unit.", 0);
}

################################################################
# Audio Devices sub functions for PROCESSING_UNIT_v2_sub()
################################################################
UP_DOWNMIX_PROCESS_v2_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrInPins", "Number of Input Pins of this Unit",0);

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSourceID", "ID of the Unit or Terminal to which the Input Pin of this Processing Unit is connected.",0);

    if (CurrentByteOffset + 1 > bLength) return 1;
    bNrChannels = GetDataByte(Base + CurrentByteOffset);
    AddEntry(CurrentByteOffset, "bNrChannels", bNrChannels,2, Format("This Processing Unit's audio channel cluster has %d logical output channels",bNrChannels));
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 4 > bLength) return 1;
    AddbmChannelConfigEntry();

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iChannelNames","Index of a string descriptor, describing the name of the first logical channel in the Processing Unit's output channel cluster",0);

    if (CurrentByteOffset + 2 > bLength) return 1;
    bmControls = GetNBits(in.Data, ((Base + CurrentByteOffset+DataByteHeaderOffset)*8), 16);
    SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 8, 16);
    enableControl = bmControls & 0x0003;
    modeSelectControl = (bmControls & 0x000C) >> 2;
    clusterControl = (bmControls & 0x0030) >> 4;
    underflowControl = (bmControls & 0x00C0) >> 6;
    overflowControl = (bmControls & 0x0300) >> 8;
    enableControlRow = Find(AudioGeneralControlStatusTable, enableControl);
    modeSelectControlRow = Find(AudioGeneralControlStatusTable, modeSelectControl);
    clusterControlRow = Find(AudioGeneralControlStatusTable, clusterControl);
    underflowControlRow = Find(AudioGeneralControlStatusTable, underflowControl);
    overflowControlRow = Find(AudioGeneralControlStatusTable, overflowControl);
    reservedText = "&nbsp;&nbsp;D15..10: Reserved, should set to 0";
    AddEntry( CurrentByteOffset, "bmControls", bmControls, 4, "D1..0: Enable Control" + enableControlRow[1] , 0);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D3..2: Mode Select Control" + modeSelectControlRow[1]);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D5..4: Cluster Control" + clusterControlRow[1]);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D7..6: Underflow Control" + underflowControlRow[1]);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D9..8: Overflow Control" + overflowControlRow[1]);
    AddDescriptionOnly( NewLine() + reservedText );
    AddFieldBreak();
    IncCurrByteOffset( 2 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iProcessing","Index of a string descriptor, describing this Processing Unit",0);

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrModes","Number of modes, supported by this Processing Unit",0);
    bNrModes = val;

    for (i = 0; i < bNrModes; i++)
        AddbmChannelConfigEntry();

}

DOLBY_PROLOGIC_PROCESS_v2_sub()
{
    UP_DOWNMIX_PROCESS_v2_sub(); # they are identical, only some fields contains different value,
                                # but we will not do the check
}

STEREO_EXTENDER_PROCESS_v2_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrInPins", "Number of Input Pins of this Unit",0);

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSourceID", "ID of the Unit or Terminal to which the Input Pin of this Processing Unit is connected.",0);

    if (CurrentByteOffset + 1 > bLength) return 1;
    bNrChannels = GetDataByte(Base + CurrentByteOffset);
    AddEntry(CurrentByteOffset, "bNrChannels", bNrChannels,2, Format("This Processing Unit's audio channel cluster has %d logical output channels",bNrChannels));
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 4 > bLength) return 1;
    AddbmChannelConfigEntry();

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iChannelNames","Index of a string descriptor, describing the name of the first logical channel in the Processing Unit's output channel cluster",0);

    if (CurrentByteOffset + 2 > bLength) return 1;
    bmControls = GetNBits(in.Data, ((Base + CurrentByteOffset+DataByteHeaderOffset)*8), 16);
    SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 8, 16);
    enableControl = bmControls & 0x0003;
    WidthControl = (bmControls & 0x000C) >> 2;
    clusterControl = (bmControls & 0x0030) >> 4;
    underflowControl = (bmControls & 0x00C0) >> 6;
    overflowControl = (bmControls & 0x0300) >> 8;
    enableControlRow = Find(AudioGeneralControlStatusTable, enableControl);
    WidthControlRow = Find(AudioGeneralControlStatusTable, WidthControl);
    clusterControlRow = Find(AudioGeneralControlStatusTable, clusterControl);
    underflowControlRow = Find(AudioGeneralControlStatusTable, underflowControl);
    overflowControlRow = Find(AudioGeneralControlStatusTable, overflowControl);
    reservedText = "&nbsp;&nbsp;D15..10: Reserved, should set to 0";
    AddEntry( CurrentByteOffset, "bmControls", bmControls, 4, "D1..0: Enable Control" + enableControlRow[1] , 0);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D3..2: Width Control" + WidthControlRow[1]);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D5..4: Cluster Control" + clusterControlRow[1]);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D7..6: Underflow Control" + underflowControlRow[1]);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D9..8: Overflow Control" + overflowControlRow[1]);
    AddDescriptionOnly( NewLine() + reservedText );
    AddFieldBreak();
    IncCurrByteOffset( 2 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iProcessing","Index of a string descriptor, describing this Processing Unit",0);
}

#***************************************************************************************************
#Universal Serial Bus Device Class Definition for Audio Data Formats Release 2.0
#***************************************************************************************************

AS_GENERAL_v2_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bTerminalLink", "The Terminal ID of the terminal to which this interface is connected");

    if (CurrentByteOffset + 1 > bLength) return 1;
    bmControls = GetDataByte(Base + CurrentByteOffset);
    activeControl = bmControls & 0x03;
    validControl = (bmControls & 0x0C) >> 2;
    activeControlRow = Find(AudioGeneralControlStatusTable, activeControl);
    validControlRow = Find(AudioGeneralControlStatusTable, validControl);
    reservedText = "&nbsp;&nbsp;D7..4: Reserved, should set to 0";
    AddEntry( CurrentByteOffset, "bmControls", bmControls, 2, "D1..0: Active Alternate Setting Control" + activeControlRow[1] , 0);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D3..2: Valid Alternate Settings Control" + validControlRow[1]);
    AddDescriptionOnly( NewLine() + reservedText );
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    bFormatType = GetDataByte(Base + CurrentByteOffset);
    formatTypeRow = Find(AudioDataFormatType_v2_Table, bFormatType);
    AddEntry( CurrentByteOffset, "bFormatType", formatTypeRow[1], 2, FormatEx("The format type AudioStreaming interfae using is %s (0x%02X)", formatTypeRow[1], bFormatType) , 0);
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 4 > bLength) return 1;
    bmFormats = GetNBits(in.Data, ((Base + CurrentByteOffset+DataByteHeaderOffset)*8), 32);
    SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 8, 32);

    title = "The Audio Data Format that can be Used to communicate with this interface:";
    desc = "";
    if (formatTypeRow[2] != null)
        desc = ToBitDecode_old_ex(formatTypeRow[2], bmFormats, "", title);
    AddEntry(CurrentByteOffset, "bmFormats", bmFormats, 8, desc , 0);
    AddFieldBreak();
    IncCurrByteOffset( 4 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrChannels", "Number of physical channels in the AS Interface audio channel cluster");

    if (CurrentByteOffset + 4 > bLength) return 1;
    AddbmChannelConfigEntry();

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iChannelNames", "Index of a string descriptor, describing the name of the first physical channel");
}


FORMAT_TYPE_v2_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    bFormatType = GetDataByte(Base + CurrentByteOffset);
    formatTypeRow = Find(AudioDataFormatType_v2_Table, bFormatType);
    AddEntry( CurrentByteOffset, "bFormatType", formatTypeRow[1], 2, FormatEx("The format type AudioStreaming interfae using is %s (0x%02X)", formatTypeRow[1], bFormatType) , 0);
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (formatTypeRow[3] != null)
        Call(formatTypeRow[3]);
}

ENCODER_v2_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bEncoderID", "Constant uniquely identifying the encoder within the interface. This value is used in all requests to address this encoder");

    if (CurrentByteOffset + 1 > bLength) return 1;
    bEncoder = GetDataByte(Base + CurrentByteOffset);
    encoderTextRow = Find (AudioEncoderTypeCodes_v2_Table, bEncoder);
    AddEntry(CurrentByteOffset, "bEncoder", encoderTextRow[1], 2, FormatEx("Constant identifying the encoder is %s (0x%02X)", encoderTextRow[1], bEncoder), 0);
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 4 > bLength) return 1;
    bmControls = GetNBits(in.Data, ((Base + CurrentByteOffset+DataByteHeaderOffset)*8), 32);
    SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 8, 32);
    bitRateControl = bmControls & 0x00000003;
    qualityControl = (bmControls & 0x0000000C) >> 2;
    VBRControl = (bmControls & 0x00000030) >> 4;
    typeControl = (bmControls & 0x000000C0) >> 6;
    underflowControl = (bmControls & 0x00000300) >> 8;
    overflowControl = (bmControls & 0x00000C00) >> 10;
    encoderErrorControl = (bmControls & 0x00003000) >> 12;
    param1Control = (bmControls & 0x0000C000) >> 14;
    param2Control = (bmControls & 0x00030000) >> 16;
    param3Control = (bmControls & 0x000C0000) >> 18;
    param4Control = (bmControls & 0x00300000) >> 20;
    param5Control = (bmControls & 0x000C0000) >> 22;
    param6Control = (bmControls & 0x03000000) >> 24;
    param7Control = (bmControls & 0x0C000000) >> 26;
    param8Control = (bmControls & 0x30000000) >> 28;
    bitRateControlRow = Find(AudioGeneralControlStatusTable, bitRateControl);
    qualityControlRow = Find(AudioGeneralControlStatusTable, qualityControl);
    VBRControlRow = Find(AudioGeneralControlStatusTable, VBRControl);
    typeControlRow = Find(AudioGeneralControlStatusTable, typeControl);
    underflowControlRow = Find(AudioGeneralControlStatusTable, underflowControl);
    overflowControlRow = Find(AudioGeneralControlStatusTable, overflowControl);
    encoderErrorControlRow = Find(AudioGeneralControlStatusTable, encoderErrorControl);
    param1ControlRow = Find(AudioGeneralControlStatusTable, param1Control);
    param2ControlRow = Find(AudioGeneralControlStatusTable, param2Control);
    param3ControlRow = Find(AudioGeneralControlStatusTable, param3Control);
    param4ControlRow = Find(AudioGeneralControlStatusTable, param4Control);
    param5ControlRow = Find(AudioGeneralControlStatusTable, param5Control);
    param6ControlRow = Find(AudioGeneralControlStatusTable, param6Control);
    param7ControlRow = Find(AudioGeneralControlStatusTable, param7Control);
    param8ControlRow = Find(AudioGeneralControlStatusTable, param8Control);
    reservedText = "&nbsp;&nbsp;D31..30: Reserved, should set to 0";
    AddEntry( CurrentByteOffset, "bmControls", bmControls, 8, "D1..0: Bite Rate Control" + bitRateControlRow[1] , 0);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D3..2: Quality Control" + qualityControlRow[1]);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D5..4: VBR Control" + VBRControlRow[1]);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D7..6: Type Control" + typeControlRow[1]);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D9..8: Underflow Control" + underflowControlRow[1]);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D11..10: Overflow Control" + overflowControlRow[1]);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D13..12: Encoder Error Control" + encoderErrorControlRow[1]);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D15..14: Param1 Control" + param1ControlRow[1]);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D17..16: Param2 Control" + param2ControlRow[1]);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D19..18: Param3 Control" + param3ControlRow[1]);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D21..20: Param4 Control" + param4ControlRow[1]);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D23..22: Param5 Control" + param5ControlRow[1]);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D25..24: Param6 Control" + param6ControlRow[1]);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D27..26: Param7 Control" + param7ControlRow[1]);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D29..28: Param8 Control" + param8ControlRow[1]);
    AddDescriptionOnly( NewLine() + reservedText );
    AddFieldBreak();
    IncCurrByteOffset( 4 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iParam1", "Index of a string descriptor, describing the purpose of Param1");

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iParam2", "Index of a string descriptor, describing the purpose of Param2");

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iParam3", "Index of a string descriptor, describing the purpose of Param3");

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iParam4", "Index of a string descriptor, describing the purpose of Param4");

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iParam5", "Index of a string descriptor, describing the purpose of Param5");

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iParam6", "Index of a string descriptor, describing the purpose of Param6");

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iParam7", "Index of a string descriptor, describing the purpose of Param7");

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iParam8", "Index of a string descriptor, describing the purpose of Param8");

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iEncoder", "Index of a string descriptor, describing the encoder");

}

DECODER_v2_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bDecoderID", "Constant uniquely identifying the decoder within the interface. This value is used in all requests to address this decoder");

    if (CurrentByteOffset + 1 > bLength) return 1;
    bDecoder = GetDataByte(Base + CurrentByteOffset);
    decoderTextRow = Find (AudioDecoderType_v2_Code, bDecoder);
    AddEntry(CurrentByteOffset, "bDecoder", decoderTextRow[1], 2, FormatEx("Constant identifying the decoder is %s (0x%02X)", decoderTextRow[1], bDecoder), 0);
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (decoderTextRow[2] != null)
        Call(decoderTextRow[2]);
}

#***************************************************************************************************
#Universal Serial Bus Device Class Definition for Audio Data Formats Release 3.0
#***************************************************************************************************

AS_GENERAL_v3_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bTerminalLink", "The Terminal ID of the terminal to which this interface is connected");

    if (CurrentByteOffset + 4 > bLength) return 1;
    bmControls = GetNBits(in.Data, ((Base + CurrentByteOffset+DataByteHeaderOffset)*8), 32);
    SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 8, 32);
    
    activeAltControl   =  bmControls & 0x00000003;
    validAltControl    = (bmControls & 0x0000000C) >> 2;
    audioFormatControl = (bmControls & 0x00000030) >> 4;
    
    reservedText = "&nbsp;&nbsp;D31..6: Reserved, should set to 0";
    
    AddEntry( CurrentByteOffset, "bmControls", bmControls, 8, FormatEx("D1..0: Active Alternate Setting Control: %d", activeAltControl), 0);
    AddDescriptionOnly( NewLine() + FormatEx("&nbsp;&nbsp;D3..2: Valid Alternate Settings Control: %d", validAltControl));
    AddDescriptionOnly( NewLine() + FormatEx("&nbsp;&nbsp;D5..4: Audio Data Format Control: %d", audioFormatControl));
    AddDescriptionOnly( NewLine() + reservedText );
    AddFieldBreak();
    IncCurrByteOffset( 4 );

    if (CurrentByteOffset + 2 > bLength) return 1;
    wClusterDescrID = GetDataWord(Base + CurrentByteOffset);
    AddEntry( CurrentByteOffset, "wClusterDescrID", wClusterDescrID, 4, "ID of the cluster descriptor of the AS Interface.", 0);
    AddFieldBreak();
    IncCurrByteOffset( 2 );

    if (CurrentByteOffset + 8 > bLength) return 1;
    bmFormats = GetNBits(in.Data, ((Base + CurrentByteOffset+DataByteHeaderOffset)*8), 64);
    SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 8, 64);

    title = "The Audio Data Format that can be Used to communicate with this interface:";
    desc = "";
    if (formatTypeRow[2] != null)
        desc = ToBitDecode_old_ex(formatTypeRow[2], bmFormats, "", title);
    AddEntry(CurrentByteOffset, "bmFormats", bmFormats, 8, desc , 0);
    AddFieldBreak();
    IncCurrByteOffset( 4 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrChannels", "Number of physical channels in the AS Interface audio channel cluster");

    if (CurrentByteOffset + 4 > bLength) return 1;
    AddbmChannelConfigEntry();

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iChannelNames", "Index of a string descriptor, describing the name of the first physical channel");
}

################################################################
# Audio Devices sub functions for PROCESSING_UNIT_v3_sub()
################################################################
UP_DOWNMIX_PROCESS_v3_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrInPins", "Number of Input Pins of this Unit",0);

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSourceID", "ID of the Unit or Terminal to which the Input Pin of this Processing Unit is connected.",0);

    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wProcessingDescrStr", "ID of a class-specific String descriptor, describing this Processing Unit.", 0);
    
    if (CurrentByteOffset + 4 > bLength) return 1;
    bmControls = GetNBits(in.Data, ((Base + CurrentByteOffset+DataByteHeaderOffset)*8), 32);
    
    SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 8, 32);
    
    modeSelectControl =  bmControls & 0x00000003;
    underflowControl  = (bmControls & 0x0000000C) >> 2;
    overflowControl   = (bmControls & 0x00000030) >> 4;
    
    modeSelectControlRow = Find(AudioGeneralControlStatusTable, modeSelectControl);
    underflowControlRow = Find(AudioGeneralControlStatusTable, underflowControl);
    overflowControlRow = Find(AudioGeneralControlStatusTable, overflowControl);
    
    reservedText = "&nbsp;&nbsp;D31..6: Reserved, should set to 0";
    
    AddEntry( CurrentByteOffset, "bmControls", bmControls, 8, "D1..0: Mode Select Control" + modeSelectControlRow[1] , 0);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D3..2: Underflow Control" + underflowControlRow[1]);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D5..4: Overflow Control" + overflowControlRow[1]);
    AddDescriptionOnly( NewLine() + reservedText );
    AddFieldBreak();
    IncCurrByteOffset( 4 );
    
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrModes", "Number of modes, supported by this Processing Unit", 0);
    bNrModes = val;
    
    for (i = 0; i < bNrModes; i++)
    {
        if (CurrentByteOffset + 2 > bLength) return 1;
        AddWordEntry(FormatEx("waClusterDescrID(%d)", i + 1), FormatEx("Unique ID of the Cluster descriptor for mode(%d)", i + 1), 0);
    }
}

STEREO_EXTENDER_PROCESS_v3_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrInPins", "Number of Input Pins of this Unit",0);

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSourceID", "ID of the Unit or Terminal to which the Input Pin of this Processing Unit is connected.",0);
    
    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wProcessingDescrStr", "ID of a class-specific String descriptor, describing this Processing Unit.", 0);

    if (CurrentByteOffset + 4 > bLength) return 1;
    bmControls = GetNBits(in.Data, ((Base + CurrentByteOffset+DataByteHeaderOffset)*8), 32);
    
    SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 8, 32);
    
    widthControl     =  bmControls & 0x00000003;
    underflowControl = (bmControls & 0x0000000C) >> 2;
    overflowControl  = (bmControls & 0x00000030) >> 4;

    widthControlRow     = Find(AudioGeneralControlStatusTable, widthControl);
    underflowControlRow = Find(AudioGeneralControlStatusTable, underflowControl);
    overflowControlRow  = Find(AudioGeneralControlStatusTable, overflowControl);
    
    reservedText = "&nbsp;&nbsp;D31..6: Reserved, should set to 0";
    
    AddEntry( CurrentByteOffset, "bmControls", bmControls, 8, "D1..0: Width Control" + widthControlRow[1] , 0);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D3..2: Underflow Control" + underflowControlRow[1]);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D5..4: Overflow Control" + overflowControlRow[1]);
    AddDescriptionOnly( NewLine() + reservedText );
    AddFieldBreak();
    IncCurrByteOffset( 4 );
}

MULTI_FUNCTION_PROCESS_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bNrInPins", "Number of Input Pins of this Unit",0);
    
    number_of_source_ids = bLength - 19;
    for (i = 0 ; i < number_of_source_ids ; i++)
    {
        if (CurrentByteOffset + 1 > bLength) return 1;
        AddByteEntry(FormatEx("baSourceID(%d)", i + 1), "ID of the Unit or Terminal to which Input Pin 1 of this Processing Unit is connected.",0);
    }
    
    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wProcessingDescrStr", "ID of a class-specific String descriptor, describing this Processing Unit.", 0);
    
    if (CurrentByteOffset + 4 > bLength) return 1;
    bmControls = GetNBits(in.Data, ((Base + CurrentByteOffset+DataByteHeaderOffset)*8), 32);
    
    SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 8, 32);
    
    underflowControl =  bmControls & 0x00000003;
    overflowControl  = (bmControls & 0x0000000C) >> 2;
    
    underflowControlRow = Find(AudioGeneralControlStatusTable, underflowControl);
    overflowControlRow  = Find(AudioGeneralControlStatusTable, overflowControl);
    
    reservedText = "&nbsp;&nbsp;D31..4: Reserved, should set to 0";
    
    AddEntry( CurrentByteOffset, "bmControls", bmControls, 8, "D1..0: Underflow Control" + underflowControl[1] , 0);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D3..2: Overflow Control" + overflowControl[1]);
    AddDescriptionOnly( NewLine() + reservedText );
    AddFieldBreak();
    IncCurrByteOffset( 4 );
    
    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wClusterDescrID", "Unique ID of the Cluster descriptor for this Processing Unit.", 0);
    
    
    if (CurrentByteOffset + 4 > bLength) return 1;
    bmAlgorithms = GetNBits(in.Data, ((Base + CurrentByteOffset+DataByteHeaderOffset)*8), 32);
    
    SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 8, 32);
    
    AlgorithmUndefined        =  bmAlgorithms & 0x00000001;
    BeamForming               = (bmAlgorithms & 0x00000002) >> 1;
    AcousticEchoCancellation  = (bmAlgorithms & 0x00000004) >> 2;
    ActiveNoiseCancellation   = (bmAlgorithms & 0x00000008) >> 3;
    BlindSourceSeparation     = (bmAlgorithms & 0x00000010) >> 4;
    NoiseSuppressionReduction = (bmAlgorithms & 0x00000020) >> 5;
    
    reservedText = "&nbsp;&nbsp;D31..6: Reserved";
    
    AddEntry( CurrentByteOffset, "bmAlgorithms", bmAlgorithms, 8, FormatEx("D0: Algorithm Undefined = %d", AlgorithmUndefined) , 0);
    AddDescriptionOnly( NewLine() + FormatEx("&nbsp;&nbsp;D1: Beam Forming", BeamForming));
    AddDescriptionOnly( NewLine() + FormatEx("&nbsp;&nbsp;D2: Acoustic Echo Cancellation", AcousticEchoCancellation));
    AddDescriptionOnly( NewLine() + FormatEx("&nbsp;&nbsp;D3: Active Noise Cancellation", ActiveNoiseCancellation));
    AddDescriptionOnly( NewLine() + FormatEx("&nbsp;&nbsp;D4: Blind Source Separation", BlindSourceSeparation));
    AddDescriptionOnly( NewLine() + FormatEx("&nbsp;&nbsp;D5: Noise Suppression/Reduction", NoiseSuppressionReduction));
    AddDescriptionOnly( NewLine() + reservedText );
    AddFieldBreak();
    IncCurrByteOffset( 4 );
}
################################################################
# Audio Devices sub functions for FORMAT_TYPE_v2_sub()
################################################################
FORMAT_TYPE_I_v2_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSubslotSize", "The number of bytes occupied by one audio subslot. Can be 1, 2, 3 or 4.");

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bBitResolution", "The number of effectively used bits from the available bits in an audio subslot");
}

FORMAT_TYPE_II_v2_sub()
{
    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wMaxBitRate", "Indicates the maximum number of bits per second this interface can handle. Expresed in kbits/s");

    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wSlotsPerFrame", "Indicates the number of PCM audio slots contained in one encoded audio frame.");
}

FORMAT_TYPE_III_v2_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSubslotSize", "The number of bytes occupied by one audio subslot. Must be set to two.");

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bBitResolution", "The number of effectively used bits from the available bits in an audio subframe.");
}
FORMAT_TYPE_IV_v2_sub()
{
    # nothing for type IV
}

EXT_FORMAT_TYPE_I_v2_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSubslotSize", "The number of bytes occupied by one audio subslot. Can be 1, 2, 3 or 4.");

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bBitResolution", "The number of effectively used bits from the available bits in an audio subslot");

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bHeaderLength", "Size of the Packet Header, in bytes");

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bControlSize", "Size of the Control Channel Words, in bytes");

    if (CurrentByteOffset + 1 > bLength) return 1;
    bSideBandProtocol = GetDataByte(Base + CurrentByteOffset);
    sideBandProtocolRow = Find (AudioSideBandProtocolCodes_v2_Table, bSideBandProtocol);
    AddEntry(CurrentByteOffset, "bSideBandProtocol",sideBandProtocolRow[1],2, FormatEx("The Side Band Protocol to use is : %s (0x%02X)",sideBandProtocolRow[1],bSideBandProtocol),0 );
    AddFieldBreak();
    IncCurrByteOffset( 1 );
}
EXT_FORMAT_TYPE_II_v2_sub()
{
    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wMaxBitRate", "Indicates the maximum number of bits per second this interface can handle. Expresed in kbits/s");

    if (CurrentByteOffset + 2 > bLength) return 1;
    AddWordEntry("wSlotsPerFrame", "Indicates the number of PCM audio slots contained in one encoded audio frame.");

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bHeaderLength", "Size of the Packet Header, in bytes");

    if (CurrentByteOffset + 1 > bLength) return 1;
    bSideBandProtocol = GetDataByte(Base + CurrentByteOffset);
    sideBandProtocolRow = Find (AudioSideBandProtocolCodes_v2_Table, bSideBandProtocol);
    AddEntry(CurrentByteOffset, "bSideBandProtocol",sideBandProtocolRow[1],2, FormatEx("The Side Band Protocol to use is : %s (0x%02X)",sideBandProtocolRow[1],bSideBandProtocol),0 );
    AddFieldBreak();
    IncCurrByteOffset( 1 );
}


EXT_FORMAT_TYPE_III_v2_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bSubslotSize", "The number of bytes occupied by one audio subslot. Must be set to two.");

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bBitResolution", "The number of effectively used bits from the available bits in an audio subframe.");

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("bHeaderLength", "Size of the Packet Header, in bytes");

    if (CurrentByteOffset + 1 > bLength) return 1;
    bSideBandProtocol = GetDataByte(Base + CurrentByteOffset);
    sideBandProtocolRow = Find (AudioSideBandProtocolCodes_v2_Table, bSideBandProtocol);
    AddEntry(CurrentByteOffset, "bSideBandProtocol",sideBandProtocolRow[1],2, FormatEx("The Side Band Protocol to use is : %s (0x%02X)",sideBandProtocolRow[1],bSideBandProtocol),0 );
    AddFieldBreak();
    IncCurrByteOffset( 1 );
}
################################################################
# Audio Devices sub functions for DECODER_v2_sub()
################################################################
MPEG_DECODER_v2_sub()
{
    if (CurrentByteOffset + 2 > bLength) return 1;
    bmMPEGCapabilities = GetNBits(in.Data, ((Base + CurrentByteOffset+DataByteHeaderOffset)*8), 16);
    SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 8, 16);
    desc = "Bitmap identifying the MPEG capabilities of the decoder. A bit set indicates that the capability is supported:";
    desc += ToBitDecode_old(AudioMPEGCapabilitiesBitmap, bmMPEGCapabilities);
    row = Find (AudioMPEGCapabilitiesBit8And9Table, (bmMPEGCapabilities >> 8) & 0x3);
    desc += "D9..8: MPEG-2 multilingual support:" + NewLine() + FormatEx("%d%d = ",row[0] >> 1, row[0] & 0b1) + row[1];
    AddEntry(CurrentByteOffset, "bmMPEGCapabilities", bmMPEGCapabilities, 4, desc, 0);
    AddFieldBreak();
    IncCurrByteOffset( 2 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    bmMPEGFeatures = GetDataByte(Base + CurrentByteOffset);
    row = Find(AudioDecoderGeneralFeaturesBit4And5Table, (bmMPEGFeatures >> 4) & 0x3);
    desc = "Bitmap identifying the features the decoder supports. A bit set indicates that the feature is supported:";
    AddEntry(CurrentByteOffset, "bmMPEGFeatures", bmMPEGFeatures, 2, desc, 0);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D3..0: Reserved");
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D5..4:  Internal Dynamic Range Control:");
    AddDescriptionOnly(FormatEx("%d%d = ", row[0] >> 1, row[0] & 0b1) + row[1]);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D7..6 Reserved. Must be set to 0");
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    bmControls = GetDataByte(base + CurrentByteOffset);
    underflowControl = bmControls & 0x03;
    overflowControl = (bmControls & 0x0C) >> 2;
    decoderErrorControl = (bmControls & 0x30) >> 4;
    underflowControlRow = Find(AudioGeneralControlStatusTable, underflowControl);
    overflowControlRow = Find(AudioGeneralControlStatusTable, overflowControl);
    decoderErrorControlRow = Find(AudioGeneralControlStatusTable, decoderErrorControl);
    reservedText = "&nbsp;&nbsp;D7..6: Reserved, should set to 0";
    AddEntry( CurrentByteOffset, "bmControls", bmControls, 2, "D1..0: Underflow Control Control" + underflowControlRow[1] , 0);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D3..2: Overflow Control" + overflowControlRow[1]);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D5..4: Decoder Error Control" + decoderErrorControlRow[1]);
    AddDescriptionOnly( NewLine() + reservedText );
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iDecoder", "Index of a string descriptor, describing the decoder.");

}

AC3_DECODER_v2_sub()
{
    if (CurrentByteOffset + 4 > bLength) return 1;
    bmBSID = GetNBits(in.Data, ((Base + CurrentByteOffset+DataByteHeaderOffset)*8), 32);
    SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 8, 32);
    AddEntry(CurrentByteOffset, "bmBSID", bmBSID, 8, "A bit set to 1 indicates that the corresponding BSID mode is supported",0);
    AddFieldBreak();
    IncCurrByteOffset( 4 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    bmAC3Features = GetDataByte(Base + CurrentByteOffset);
    row = Find(AudioDecoderGeneralFeaturesBit4And5Table, (bmAC3Features >> 4) & 0x3);
    desc = "A bit set to 1 indicates that the mentioned feature is supported:";
    AddEntry(CurrentByteOffset, "bmAC3Features", bmAC3Features, 2, desc, 0);
    AddDescriptionOnly(ToBitDecode_old(AudioAC3FeaturesBitmap, bmAC3Features));
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D5..4:  Internal Dynamic Range Control:");
    AddDescriptionOnly(FormatEx("%d%d = ", row[0] >> 1, row[0] & 0b1) + row[1]);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D7..6: Reserved. Must be set to 0");
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    bmControls = GetDataByte(base + CurrentByteOffset);
    underflowControl = bmControls & 0x03;
    overflowControl = (bmControls & 0x0C) >> 2;
    decoderErrorControl = (bmControls & 0x30) >> 4;
    underflowControlRow = Find(AudioGeneralControlStatusTable, underflowControl);
    overflowControlRow = Find(AudioGeneralControlStatusTable, overflowControl);
    decoderErrorControlRow = Find(AudioGeneralControlStatusTable, decoderErrorControl);
    reservedText = "&nbsp;&nbsp;D7..6: Reserved, should set to 0";
    AddEntry( CurrentByteOffset, "bmControls", bmControls, 2, "D1..0: Underflow Control Control" + underflowControlRow[1] , 0);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D3..2: Overflow Control" + overflowControlRow[1]);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D5..4: Decoder Error Control" + decoderErrorControlRow[1]);
    AddDescriptionOnly( NewLine() + reservedText );
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iDecoder", "Index of a string descriptor, describing the decoder.");
}

WMA_DECODER_v2_sub()
{
    if (CurrentByteOffset + 2 > bLength) return 1;
    bmWMAProfile = GetNBits(in.Data, ((Base + CurrentByteOffset+DataByteHeaderOffset)*8), 16);
    SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 8, 16);
    desc = "A bit set to 1 indicates that the mentioned feature is supported:";
    AddEntry(CurrentByteOffset, "bmWMAProfile", bmWMAProfile, 4, desc, 0);
    AddDescriptionOnly(ToBitDecode_old(AudioWMAProfileBitmap, bmWMAProfile));
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D15..11: Reserved. Must be set to 0");
    AddFieldBreak();
    IncCurrByteOffset( 2 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    bmControls = GetDataByte(base + CurrentByteOffset);
    underflowControl = bmControls & 0x03;
    overflowControl = (bmControls & 0x0C) >> 2;
    decoderErrorControl = (bmControls & 0x30) >> 4;
    underflowControlRow = Find(AudioGeneralControlStatusTable, underflowControl);
    overflowControlRow = Find(AudioGeneralControlStatusTable, overflowControl);
    decoderErrorControlRow = Find(AudioGeneralControlStatusTable, decoderErrorControl);
    reservedText = "&nbsp;&nbsp;D7..6: Reserved, should set to 0";
    AddEntry( CurrentByteOffset, "bmControls", bmControls, 2, "D1..0: Underflow Control Control" + underflowControlRow[1] , 0);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D3..2: Overflow Control" + overflowControlRow[1]);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D5..4: Decoder Error Control" + decoderErrorControlRow[1]);
    AddDescriptionOnly( NewLine() + reservedText );
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iDecoder", "Index of a string descriptor, describing the decoder.");
}

DTS_DECODER_v2_sub()
{
    if (CurrentByteOffset + 1 > bLength) return 1;
    bmCapabilities = GetDataByte(Base + CurrentByteOffset);
    desc = "A bit set to 1 indicates that the mentioned feature is supported:";
    AddEntry(CurrentByteOffset, "bmCapabilities", bmCapabilities, 2, desc, 0);
    AddDescriptionOnly(ToBitDecode_old(AudioDTSCapabilitiesBitmap, bmCapabilities));
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D7..5: Reserved. Must be set to 0");
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    bmControls = GetDataByte(base + CurrentByteOffset);
    underflowControl = (bmControls & 0x0C) >> 2;
    overflowControl = (bmControls & 0x30) >> 4;
    decoderErrorControl = (bmControls & 0xC0) >> 6;
    underflowControlRow = Find(AudioGeneralControlStatusTable, underflowControl);
    overflowControlRow = Find(AudioGeneralControlStatusTable, overflowControl);
    decoderErrorControlRow = Find(AudioGeneralControlStatusTable, decoderErrorControl);
    reservedText = "&nbsp;&nbsp;D1..0: Reserved, should set to 0";
    AddEntry( CurrentByteOffset, "bmControls", bmControls, 2, reservedText , 0);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D3..2: Underflow Control Control" + underflowControlRow[1]);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D5..4: Overflow Control" + overflowControlRow[1]);
    AddDescriptionOnly( NewLine() + "&nbsp;&nbsp;D7..6: Decoder Error Control" + decoderErrorControlRow[1]);
    AddFieldBreak();
    IncCurrByteOffset( 1 );

    if (CurrentByteOffset + 1 > bLength) return 1;
    AddByteEntry("iDecoder", "Index of a string descriptor, describing the decoder.");
}

################################################################
# Audio Devices Help functions
################################################################
AddbmChannelConfigEntry()
{
    val = GetNBits(in.Data, ((Base + CurrentByteOffset+DataByteHeaderOffset)*8), 32);
    SetFieldOffsetLen(((Base + CurrentByteOffset)*8) + 8, 32);

    #desc = "<html>";
    title = "Describes the spatial location of the  logical channels:";
    desc = ToBitDecode_old_ex(AudioChannelConfigBitmap, val, "", title );
    #desc += "</html>";

    AddEntry( CurrentByteOffset, "bmChannelConfig", val, 8, desc, 0, 0 );
    AddFieldBreak();

    IncCurrByteOffset( 4 );
}


AddwChannelConfigEntry()
{
    val = GetNBits(in.Data,((Base+CurrentByteOffset+DataByteHeaderOffset)*8), 16);
    SetFieldOffsetLen(((Base+CurrentByteOffset)*8) + 16, 16);

    AddEntry( CurrentByteOffset, "bmChannelConfig", val, 4, "Spatial locations present in the cluster" + ToBitDecode_old(AudioInputTerminalChannel_v1_Config, val));
    AddFieldBreak();

    IncCurrByteOffset( 2 );
}

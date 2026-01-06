 
# Copyright (c) 2006, LeCroy Corp PSG. - All Rights Reserved
 
#   Audio2.0RequestsHelper.inc

#   Some helper fucntion used in Audio2.0Requests.dec

BOOLEAN_VALUE_CONTROL_Validate(byteValue)
{
    if (byteValue == 0 || byteValue == 1)
        return 1;
    else
        return 0;
}

CS_CLOCK_VALID_CONTROL_Tooltip(byteValue)
{
    if (byteValue == 0)
        return "FALSE: Clock Invalid";
    else if (byteValue == 1)
        return "TRUE: Clock Valid";
    else
        return WARNING_SIGN + Format("Invalid CS_CLOCK_VALID_CONTROL value (0x%02X)", byteValue);
}


NON_ZERO_VALUE_CONTROL_Validate(Value)
{
    if (Value != 0)
        return 1;
    else
        return 0;
}

CX_CLOCK_SELECTOR_CONTROL_Tooltip(byteValue)
{   
    if (byteValue != 0)
        return Format("%d Clock Signal(s)", byteValue);
    else
        return WARNING_SIGN + Format("%d Clock Signal is not allowed", byteValue);
}

CM_NUMERATOR_CONTROL_Tooltip(wordValue)
{
    if (wordValue != 0)
        return Format("0x%04X", wordValue);
    else
        return WARNING_SIGN + Format("0x%04X is not a valid value", wordValue);
}

CM_DENOMINATOR_CONTROL_Tooltip(wordValue)
{
    if (wordValue != 0)
        return Format("0x%04X", wordValue);
    else
        return WARNING_SIGN + Format("0x%04X is not a valid value", wordValue);
}

TE_COPY_PROTECT_CONTROL_Validate(byteValue)
{
    if (byteValue == 0 || byteValue == 1 || byteValue == 2)
        return 1;
    else
        return 0;
}

TE_COPY_PROTECT_CONTROL_Tooltip(byteValue)
{
    if (byteValue == 0)
        return "0: CPL0: Copying is permitted without restriction. The material is either not copyrighted, or the copyright is not asserted.";
    else if (byteValue == 1)
        return "1: CPL1: One generation of copies may be made. The material is copyright protected and is the original.";
    else if (byteValue == 2)
        return "2: CPL2: The material is copyright protected and no digital copying is permitted.";
    else
        return WARNING_SIGN + Format("Invalid TE_COPY_PROTECT_CONTROL value (0x%02X)", byteValue);
}

TE_OVERLOAD_CONTROL_Tooltip(byteValue)
{
    if (byteValue == 1)
        return "TRUE: Overload condition exists";
    else if (byteValue == 0)
        return "FALSE: Normal";
    else
        return WARNING_SIGN + Format("Invalid TE_OVERLOAD_CONTROL value (0x%02X)", byteValue);
}


UNDERFLOW_CONTROL_Tooltip(byteValue)
{
    if (byteValue == 1)
        return "TRUE: Underflow condition exists";
    else if (byteValue == 0)
        return "FALSE: Normal";
    else
        return WARNING_SIGN + Format("Invalid UNDERFLOW_CONTROL value (0x%02X)", byteValue);
}

OVERFLOW_CONTROL_Tooltip(byteValue)
{
    if (byteValue == 1)
        return "TRUE: Overflow condition exists";
    else if (byteValue == 0)
        return "FALSE: Normal";
    else
        return WARNING_SIGN + Format("Invalid OVERFLOW_CONTROL value (0x%02X)", byteValue);
}

LATENCY_CONTROL_Tooltip(dwordValue)
{
    return Format("0x%08X ns", dwordValue);
}

GENERAL_VOLUME_CONTROL_Tooltip( wordValue )
{
    if ( wordValue < 0x8000 )
        return Format("%d / 256 dB", wordValue);
    else if (wordValue == 0x8000)
        return "silence (- max dB)";
    else
        return Format("%d / 256 dB", (wordValue | 0xFFFF0000));
}

SU_SELECTOR_CONTROL_Tooltip( byteValue)
{   
    if (byteValue != 0)
        return Format("%d identically configured audio channel cluster(s)", byteValue);
    else
        return WARNING_SIGN + Format("%d identically configured audio channel clusters is not valid", byteValue);
}

FU_MUTE_CONTROL_Tooltip(byteValue)
{
    if (byteValue == 1)
        return "TRUE: Muted";
    else if (byteValue == 0)
        return "FALSE: Not muted";
    else
        return WARNING_SIGN + Format("Invalid FU_MUTE_CONTROL value (0x%02X)", byteValue);
}

GENERAL_FEATURE_UNIT_CONTROL_Tooltip(byteValue)
{
    if ( byteValue < 0x7F )
        return Format("%d / 4 dB", byteValue);
    else
        return Format("%d / 4 db", (byteValue | 0xFFFFFF00));
}

GENERAL_TRUE_FALSE_CONTROL_Tooltip(byteValue)
{
    if (byteValue == 1)
        return "TRUE";
    else if (byteValue == 0)
        return "FALSE";
    else
        return WARNING_SIGN + Format("Invalid value (0x%02X)", byteValue);
}

FU_DELAY_CONTROL_Tooltip( dwordValue)
{
    return FormatEx("%d / 4194394 s", dwordValue);
}

GENERAL_MODE_SELECT_CONTROL_Tooltip( byteValue )
{   
    if (byteValue != 0)
        return Format("%d mode(s)", byteValue);
    else
        return WARNING_SIGN + Format("%d modes is not valid", byteValue);
}

GENERAL_FREQUENCY_CONTROL_Tooltip (dwordValue)
{
    return Format("%u Hz", dwordValue);
}

PE_QFACTOR_CONTROL_Tooltip (dwordValue)
{
    return FormatEx("%d * 0.000000953674316406", dwordValue);
}

RV_TYPE_CONTROL_Tooltip ( byteValue)
{
    if (byteValue == 0)
        return "0: Room 1         - simulates the reverberation of a small room.";
    else if (byteValue == 1)
        return "1: Room 2         - simulates the reverberation of a medium room.";
    else if (byteValue == 2)
        return "2: Room 3         - simulates the reverberation of a large room.";
    else if (byteValue == 3)
        return "3: Hall 1         - simulates the reverberation of a medium concert hall.";
    else if (byteValue == 4)
        return "4: Hall 2         - simulates the reverberation of a large concert hall.";
    else if (byteValue == 5)
        return "5: Plate          - simulates a plate reverberation ( a studio device using a metal plate).";
    else if (byteValue == 6)
        return "6: Delay          - conventional delay that produces echo effects.";
    else if (byteValue == 7)
        return "7: Panning Delay  - special delay in which the delayed sounds move left and right.";
    else
        return Format("%d: Reserved behavior", byteValue);
}

GENERAL_PERCENTAGE_CONTROL_Tooltip( byteValue )
{
    return Format("%d\%", byteValue);
}

RV_TIME_CONTROL_Tooltip( wordValue )
{
    return Format("%d / 256 s", wordValue);
}

RV_FREDELAY_CONTROL_Tooltip( wordValue )
{
    return Format("%u ms", wordValue);
}

RV_DENSITY_CONTROL_Validate ( byteValue )
{
    if (byteValue <= 100)
        return 1;
    else
        return 0;
}

RV_DENSITY_CONTROL_Tooltip( byteValue )
{
    if (byteValue <= 100)
        return Format("%d", byteValue);
    else
        return WARNING_SIGN + Format("%d is out of range [0-100]", byteValue);
}

MD_BALANCE_CONTROL_Validate ( byteValue )
{

    if (byteValue <= 0x64 || byteValue >= 0x9C)
        return 1;
    else
        return 0;
}

MD_BALANCE_CONTROL_Tooltip ( byteValue )
{
     if (byteValue <= 0x64 || byteValue >= 0x9C)
        return FormatEx(" %d\% of original signal and %d\% of effected signal.", 50 - (byteValue / 2), 50 + (byteValue / 2));
    else
        return WARNING_SIGN + Format("value %d out of range (-100 ~ 100)", byteValue);
}

MD_RATE_CONTROL_Tooltip ( wordValue )
{
    return Format("%d / 256 Hz", wordValue);
}

MD_DEPTH_CONTROL_Tooltip ( wordValue )
{
    return Format("%d / 256 ms", wordValue);
}

DR_COMPRESSION_RATE_CONTROL_Tooltip( wordValue )
{
    return Format("%d / 256", wordValue);
}

GENERAL_AMPL_CONTROL_Tooltip(wordValue)
{
    if ( wordValue < 0x8000 )
        return Format("%d / 256 dB", wordValue);
    else
        return Format("%d / 256 dB", (wordValue | 0xFFFF0000));
}

GENERAL_BYTE_VALUE_CONTROL_Tooltip ( byteValue )
{
    return Format("%u", byteValue);
}

AS_AUDIO_DATA_FORMAT_CONTROL_ToolTip ( dwordValue )
{
    return "The value should follows the definition of the bmFormats field in the CS AS interfece descriptor";
}

EN_BIT_RATE_CONTROL_Tooltip ( dwordValue )
{
    return Format("%u bits/s", dwordValue);
}

EN_QUALITY_CONTROL_Validate ( byteValue )
{
    if ( byteValue <= 100)
        return 1;
    else
        return 0;
}

EN_QUALITY_CONTROL_Tooltip ( byteValue )
{
    if ( byteValue <= 100 )
        return Format("Quality = %u, 0 is the lowest quality and 100 is the highest quality", byteValue);
    else
        return WARNING_SIGN + Format("Quality = %u is out of range. The valid number is between 0 and 100", byteValue);
}

EN_VBR_CONTROL_Tooltip ( byteValue )
{
    if (byteValue == 1)
        return "TRUE: Variable bitrate mode selected";
    else if ( byteValue == 0 )
        return "FALSE: Constant bitrate mode selected";
    else
        return WARNING_SIGN + Format("Invalid EN_VBR_CONTROL value (0x%02X)", byteValue);
}

EN_TYPE_CONTROL_Validate ( byteValue )
{
    if ( byteValue >= 1 && byteValue <= 9)
        return 1;
    else
        return 0;
}

EN_TYPE_CONTROL_Tooltip ( byteValue )
{
    if ( byteValue == 1 )
        return "1: UNSPECIFIED: The naturae, quality and number of channels of the audio is unspecified and can change over time.";
    else if (byteValue == 2)
        return "2: SPEECH: Hgh-quality spoken audio.";
    else if (byteValue == 3)
        return "3: TELEPHONY: Low-quality or limited bandwidth spoken audio.";
    else if (byteValue == 4)
        return "4: MONOPHONIC MUSIC: Monophonic music.";
    else if (byteValue == 5)
        return "5: POLYPHONIC MUSIC: Polyphonic music.";
    else if (byteValue == 6)
        return "6: MOVIE: Multi-channel high dynamic range movie soundtracks.";
    else if (byteValue == 7)
        return "7: GAME: Multi-channel high dynamic range game audio.";
    else if (byteValue == 8)
        return "8: LOSSLESS: Encoder operates in a lossless mode.";
    else if (byteValue == 9)
        return "9: OTHER: Vendor-defined";
    else
        return WARNING_SIGN + Format("Unknown value (0x%02X)", byteValue);
}

GENERAL_ERROR_CONTROL_Tooltip ( wordValue )
{
    if ( wordValue >= 0x8000 )
        wordValue |= 0xFFFF0000;
        
    if (wordValue < 0 )
        return Format( "Error Code %d : Reserved for Vendor Extensions.", wordValue);
    else if ( wordValue == 0 )
        return "Error Code 0 : No Error.";
    else if ( wordValue == 1 )
        return "Error Code 1 : Out of memory.";
    else if ( wordValue == 2 )
        return "Error Code 2 : Out of Bandwidth.";
    else if ( wordValue == 3 )
        return "Error Code 3 : Out of Processing Cycles.";
    else if ( wordValue == 4 )
        return "Error Code 4 : General Format Frame Error.";
    else if ( wordValue == 5 )
        return "Error Code 5 : Format Frame Too Small.";
    else if ( wordValue == 6 )
        return "Error Code 6 : Format Frame Too Large.";
    else if ( wordValue == 7 )
        return "Error Code 7 : Bad Data Format.";
    else if ( wordValue == 8 )
        return "Error Code 8 : Incorrect Number of Channels.";
    else if ( wordValue == 9 )
        return "Error Code 9 : Incorrect Sampling Rate.";
    else if ( wordValue == 10 )
        return "Error Code 10 : Unable to meet Target Bitrate.";
    else if ( wordValue == 11 )
        return "Error Code 11 : Inconsistent Set of Parameters.";
    else if ( wordValue == 12 )
        return "Error Code 12 : Not Ready.";
    else if ( wordValue == 13 )
        return "Error Code 13 : Busy.";
    else
        return Format("Error Code %d : Reserved for future USB Audio Device Class Extensions.", wordValue);
}

EN_PARAMX_CONTROL_Tooltip ( dwordValue )
{
    return Format ("Vendor-specific paramters: %d", dwordValue);
}

MD_DUAL_CHANNEL_CONTROL_Tooltip ( byteValue )
{
    if ( byteValue == 1)
        return "TRUE: Channel II is selected.";
    else if ( byteValue == 0 )
        return "FALSE: Channel I is selected.";
    else
        return WARNING_SIGN + Format("Invalid MD_DUAL_CHANNEL_CONTROL value (0x%02X)", byteValue);
}

MD_SECOND_STEREO_CONTROL_Tooltip( byteValue )
{
    if ( byteValue == 1)
        return "TRUE: the second stereo channel pair is selected.";
    else if ( byteValue == 0 )
        return "FALSE: the main stereo channel pair is selected.";
    else
        return WARNING_SIGN + Format("Invalid MD_SECOND_STEREO_CONTROL value (0x%02X)", byteValue);
}

MD_MULTILINGUAL_CONTROL_Validate ( byteValue )
{
    if ( byteValue <= 7 )
        return 1;
    else
        return 0;
}

MD_MULTILINGUAL_CONTROL_Tooltip ( byteValue )
{
    if (byteValue <= 7)
        return Format("Select the %d multilingual channel actually retrieved from the MPEG stream.", byteValue);
    else
        return WARNING_SIGN + Format("Invalid MD_MULTILINGUAL_CONTROL value %d out of range (0~7)", byteValue);
}

DYN_RANGE_CONTROL_Tooltip ( byteValue )
{
    if ( byteValue == 1)
        return "TRUE: the MPEG decoder is using the Dynamic Range control words.";
    else if ( byteValue == 0 )
        return "FALSE: the control words are being ignored, and the original signal dynamic range is beding reproduced.";
    else
        return WARNING_SIGN + Format("Invalid MD_DYN_RANGE_CONTROL value (0x%02X)", byteValue);
}

SCALING_CONTROL_Tooltip ( byteValue )
{
    return Format("The common boost/cut scaling value is %u", byteValue);
}

EP_PITCH_CONTROL_Tooltip ( byteValue )
{
    if ( byteValue == 1)
        return "TRUE: The Pitch Control enables the ability of an adaptive endpoint to dynamically track its sampling frequency.";
    else if ( byteValue == 0 )
        return "FALSE: The Pitch Control disables the ability of an adaptive endpoint to dynamically track its sampling frequency.";
    else
        return WARNING_SIGN + Format("Invalid EP_PITCH_CONTROL value (0x%02X)", byteValue);
}

EP_DATA_OVERRUN_CONTROL_Tooltip ( byteValue )
{
    if ( byteValue == 1)
        return "TRUE: The Overrun condition occured.";
    else if ( byteValue == 0 )
        return "FALSE: Normal.";
    else
        return WARNING_SIGN + Format("Invalid EP_DATA_OVERRUN_CONTROL value (0x%02X)", byteValue);
}

EP_DATA_UNDERRUN_CONTROL_Tooltip ( byteValue )
{
    if ( byteValue == 1)
        return "TRUE: The underrun condition occured.";
    else if ( byteValue == 0 )
        return "FALSE: Normal.";
    else
        return WARNING_SIGN + Format("Invalid EP_DATA_UNDERRUN_CONTROL value (0x%02X)", byteValue);
}
AD_MODE_CONTROL_Validate ( byteValue )
{
    if ( byteValue < 4 )
        return 1;
    else
        return 0;
}
AD_MODE_CONTROL_Tooltip ( byteValue )
{
    if ( byteValue == 0 )
        return "0: RF mode";
    else if ( byteValue == 1 )
        return "1: Line mode";
    else if ( byteValue == 2 )
        return "2: Custom0 mode";
    else if ( byteValue == 3 )
        return "3: Custom1 mode";
    else
        return WARNING_SIGN + Format("%d: Unknown mode", byteValue);
}
    
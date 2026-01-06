#S******************************************************************************
#*
#*  FILENAME: PDStandardRequests.dec
#*
#*  Copyright (C) 2015 Teledyn LeCroy
#*
#*  DESCRIPTION
#*    This is the request file for standard PD device requests.
#*
#*  REVISION HISTORY
#*            File Created -mm
#*******************************************************************************

%include "PDCommon.inc"

############################################################
# Power Delivery      Table 9-8 PD Class Feature Selectors #
############################################################
set PDFeatureSelectorTable =
[   # Value # Title           # HasFunction
    [0xFFFF, "UNDEFINED",         0 ],  #default value
    [0x28, "BATTERY_WAKE_MASK", 1 ],
    [0x29, "OS_IS_PD_AWARE",    1 ],
    [0x2A, "POLICY_MODE",       1 ],    
    [0x36, "CHARGING_POLICY",   1 ]  
];	

IsPDFeature( feature )
{
    _row = Find(PDFeatureSelectorTable, feature);
    if ( _row[0] != 0xFFFF)    
        return 1;
	else
        return 0;
}

set PDBattryWakeMaskTable =
[
    [0xFF,  "Reserved",         "This bit is reserved for later use."],
    [0x0,   "Battery Present",  "When this bit is set\nthe PDUSB Device shall generate a wake event\nif it detects that a battery has been attached."],
    [0x1,   "Charging Flow",    "When this bit is set\nthe PDUSB Device shall generate a wake event\nif it detects that a battery switched from charging to discharging or vice versa."],
    [0x2,   "Battery Error",    "When this bit is set\nthe PDUSB Device shall generate a wake event\nif the battery has detected an error condition."]
];

set PDPolicyModeTable =
[
    [0xFF,  "Reserved",     "This value is reserved and shall not be used."],
    [0x0,   "Local",        "Status Reporting only (Default)"],
    [0x1,   "Intrusive",    "All requests are sent to the SPM"],
    [0x2,   "Hybrid",       "Send only requests that cannot be accommodated to the SPM"]
];

set PDChargingPolicyTable =
[
    [0xFF,  "Reserved", "This value is reserved and shall not be used."],
    [0x0,   "Default",  "The device shall follow the default current limits as defined in the USB 2.0 or USB 3.1 specification,\
or as negotiated through other USB mechanisms such as BC.\n\nThis is the default value."],
    [0x1,   "ICCHPF",   "The Device may draw additional power during the unconfigured and suspend states for the purposes of charging.\
For charging the device itself, the device shall limit its current draw to the higher of these two values:\
\t- ICCHPF as defined in the USB 2.0 or USB 3.1 specification, regardless of its USB state.\
\t- Current limit as negotiated through other USB mechanisms such as BC."],
    [0x2,   "ICCLPF",   "The Device may draw additional power during the unconfigured and suspend states for the purposes of charging.\
For charging the device itself, the device shall limit its current draw to the higher of these two values:\
\t- ICCLPF as defined in the USB 2.0 or USB 3.1 specification, regardless of its USB state.\
\t- Current limit as negotiated through other USB mechanisms such as BC."],
    [0x3,   "None",     "The device shall not consume any current for charging the device itself regardless of its USB state."]
];

set PDRemoteWakeStateMaskTable =
[
    [ 0, "Battery present event."],
    [ 1, "Charging flow."],
    [ 2, "Battery error."],
    [ 3, "Undefined."],
    [ 4, "Undefined."],
    [ 5, "Undefined."],
    [ 6, "Undefined."],
    [ 7, "Undefined."]
];
##########################################################################
PD_DecodeSetPDFeature() #Peripherals
{
    out.Decoded = 8;
    
    row = Find(PDFeatureSelectorTable, wValue);
    AddWValueCell(row[1], FormatEx("wValue = 0x%04X\n\n",wValue) + row[1]);
    
    AddWIndexCell("", "Index");
    
    if (wLength != 0)
        AddWLengthCell( FormatEx(_err_Illegal_Value, "wLength", wLength, 0), 1 );  
    else
        AddWLengthCell( "Correct Value of 0", 0 );

    has_function = row[2];
    if( has_function )
    {
        Call( row[1] );
    }
    ForceFullDescriptions();
}

BATTERY_WAKE_MASK()
{
    Tooltip = ToBitDecode(PDBattryWakeMaskTable, wIndex, "", "Battery Wake Mask\n");
    MaskText = ToBitString(wIndex, 16);
    FieldColor = wIndexColor;
    AddPayLoadCell("Battery Wake Mask", MaskText, Tooltip);    
}

OS_IS_PD_AWARE()
{
    tooltip = "Invalid wIndex value. it should be either 0 or 1.";
    FieldColor = ErrorColor;
    txt = "";
    if ( wIndex == 1 )
    {
        txt = "Active SPM";
        tooltip = "The SPM is active on the host";
        FieldColor = wIndexColor;
    }
    else if ( wIndex == 0 )
    {
        txt = "Inactive SPM";
        tooltip = "The SPM is not active on the host";
        FieldColor = wIndexColor;
    }
    
    AddPayLoadCell( txt, wIndex, tooltip );
}

POLICY_MODE()
{
    FieldColor = wIndexColor;
    row = Find(PDPolicyModeTable, wIndex);
    AddPayLoadCell( "Policy Mode", row[1], row[2] );
}

CHARGING_POLICY()
{
    FieldColor = wIndexColor;
    row = Find(PDChargingPolicyTable, wIndex);
    AddPayLoadCell( "Charging Policy", row[1], row[2] );
}
########################################################################

PD_GET_BATTERY_STATUS()
{
    out.Decoded = 16;
    if ( bReqType == 0x80 )
    {
        if (wValue != 0)
            AddWValueCell("", FormatEx(_err_Illegal_Value, "wValue", wValue, 0 ), 1 );  
        else
            AddWValueCell("", "Correct Value of 0", 0 );

        AddWIndexCell("", "Battery ID", 0 );
        
        if (wLength != 8)
            AddWLengthCell( FormatEx(_err_Illegal_Value, "wLength", wLength, 8 ), 1 );
        else
            AddWLengthCell( "Correct Value of 8", 0 );
            
        
        Global_BitField_offset = 64;
        CurrentFldInit();
        curr_offset = 8;
        FieldColor = 0xABCDEF;

        bat_attr          = GetDataByte(curr_offset);
        bat_soc           = GetDataByte(curr_offset + 1);
        bat_stat          = GetDataByte(curr_offset + 2);
        remot_wake_stat   = GetDataByte(curr_offset + 3);
        
        remain_opr_time   = GetDataWord(curr_offset + 4);
        remain_charg_time = GetDataWord(curr_offset + 6);
        
        bat_attr_txt = select {
            bat_attr == 0 : "No battery";
            bat_attr == 1 : "Charging";
            bat_attr == 2 : "Discharging";
            bat_attr == 3 : "Neither discharging nor charging";
            default       : "Undefined";
        };
        AddBlockPLCell( "Battery Attributes", bat_attr_txt, "" );

        AddBlockPLCell( "Battery SOC", Format("%%%d", bat_soc), "Battery Remaining Capacity" );

        bat_stat_txt = select {
            bat_stat == 0 : "No Error";
            bat_stat == 1 : "Battery required and not present";
            bat_stat == 2 : "Battery non-chargeable/wrong chemistry";
            bat_stat == 3 : "Over-temp shutdown";
            bat_stat == 4 : "Over-voltage shutdown";
            bat_stat == 5 : "Over-current shutdown";
            bat_stat == 6 : "Fatigued battery";
            bat_stat == 7 : "Unspecified error";
            default       : "Undefined (Reserved and shall not be used)";
        };
        AddBlockPLCell( "Battery Status", bat_stat_txt, "" );
        
        remot_wake_stat_tooltip = "The Remote wake events turned off.";
        if( remot_wake_stat != 0 )
        {
            remot_wake_stat_tooltip = ToBitDecode(PDRemoteWakeStateMaskTable, remot_wake_stat, "", "Status\n");            
        }
        AddBlockPLCell( "Remote Wake Cap Status", ToBitString(remot_wake_stat, 8), remot_wake_stat_tooltip );
        
        remain_opr_time_str = Format("%d minutes", remain_opr_time);
        remain_opr_tooltip = "Remaining operating time is ";
        if( remain_opr_time == 0xFFFF )
        {
            remain_opr_time_str = "Unknown";
            remain_opr_tooltip += "unknown";
        }
        else
        {
            remain_opr_tooltip += remain_opr_time_str;
        }
        AddBlockPLCell( "Remaining Operating Time", remain_opr_time_str, remain_opr_tooltip );
        
        remain_charg_time_str = Format("%d minutes", remain_charg_time);
        remain_charg_tooltip = "Remaining operating time is ";
        if( remain_charg_time == 0xFFFF )
        {
            remain_charg_time_str = "Unknown";
            remain_charg_tooltip += "unknown";
        }
        else
        {
            remain_charg_tooltip += remain_charg_time_str;            
        }
        AddBlockPLCell( "Remaining Charge Time", remain_charg_time_str, remain_charg_tooltip );        
    }
    else
    {
        AddPayLoadCell("Invalid bReqType value",   Format("0x%02X", bReqType),   "Expected 0x80 only",  ErrorColor); 
    }
}

PD_GET_BATTERY_STATUS_text()
{}

#%include "StandardDescriptors.inc"

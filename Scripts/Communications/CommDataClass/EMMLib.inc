#*******************************************************************************
#
#  FILENAME: Comm_CDC_EEM.dec
#
#  Copyright (c) 2012, LeCroy - All Rights Reserved
#
#  DESCRIPTION
#    This file isThis document specifies the behavior of Ethernet Emulation Model (EEM) Devices. 
#
#  REVISION HISTORY
#    
#
#*******************************************************************************

#*******************************************************************************
# Specify the name for this set of requests as GroupName. This name is listed 
# under Decode Vendor/Class Request menu depending on the GroupType specified 
# and the Type field of the request you are trying to decode. 
#*******************************************************************************
%include "CATCScriptAPI.inc"             #.inc files that are included
%include "UsbCommon.inc" 

 #----  Input
 # in.Data       - Data_block to decode
 # in.DataLength - Length of Data_block 
 
 #----  Output
 # out.Decoded   - amount of data has been decoded
 
const Tabular_Def_Table = Map( 
[   
    #-----------------------------------------------------------------------------------------------------
    #       id            ,      colId                          , 		containerCellId
    #-----------------------------------------------------------------------------------------------------
    [ CELL_COMM_BMTYPE    , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE   , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ CELL_COMM_LENGTH    , TABULAR_SCRIPT_COLUMN_ID_NONE      , TABULAR_SCRIPT_CONTAINER_CELL_ID_MISC ],
    [ CELL_COMM_COMMAND   , TABULAR_SCRIPT_COLUMN_ID_NONE      , TABULAR_SCRIPT_CONTAINER_CELL_ID_MISC ]
] );

###############################################
set bmEEMCmdSelectorTable =
[
    [ 7, "RESERVED"],
    [ 0, "ECHO"     ],
    [ 1, "ECHO_RESPONSE"],
    [ 2, "SUSPEND_HINT"  ],
    [ 3, "RESPONSE_HINT" ],
    [ 4, "RESPONSE_COMPLETE_HINT"],
    [ 5, "TICKLE"]
];
########################################################

#******************************************************
# bmCmdName: Reserved
#******************************************************
RESERVED()
{
    EEMCommandHdr = NextDataWord_();
    extraData = EEMCommandHdr & 0x03FF;
    AddPayLoadCell("Unknown Data", Format("0x%03X", extraData), "Extra Unknown Data");
    if (in.DataLength > 2)
    {
        ShowDataBlock(in.DataLength - 2);
        
    }
    out.Decoded = in.DataLength;
}
#******************************************************
# bmCmdName: Echo
#******************************************************
ECHO()
{
    EEMCommandHdr = NextDataWord_();
    length = EEMCommandHdr & 0x03FF;
    if (in.DataLength == length + 2)
        isError = null;
    else
        isError = _ERROR;
            
    AddPayLoadCell("Length", Format("%d", length), "Length of the data payload", isError);
    ShowDataBlock(in.DataLength - 2);
    out.Decoded = in.DataLength;
}

#******************************************************
# bmCmdName: Echo Response
#******************************************************
ECHO_RESPONSE()
{
    EEMCommandHdr = NextDataWord_();
    length = EEMCommandHdr & 0x03FF;
    if (in.DataLength == length + 2)
        isError = null;
    else
        isError = _ERROR;
            
    AddPayLoadCell("Length", Format("%d", length), "Length of the data payload", isError);
    ShowDataBlock(in.DataLength - 2);
    out.Decoded = in.DataLength;
}

#******************************************************
# bmCmdName: Suspend Hint
#******************************************************
SUSPEND_HINT()
{
    PLReservedCheck(11);
    if (in.DataLength > length + 2)
        AddExtraBytesPayloadCell(in.DataLength - 2);
    out.Decoded = in.DataLength;
}

#******************************************************
# bmCmdName: Response Hint
#******************************************************
RESPONSE_HINT()
{
    EEMCommandHdr = NextDataWord_();
    responseTime = EEMCommandHdr & 0x03FF;
    AddPayLoadCell("Response Interval", Format("%d ms",responseTime), "Suggested Response Inteval in milliseconds"); 
    if (in.DataLength > length + 2)
        AddExtraBytesPayloadCell(in.DataLength - 2);
    out.Decoded = in.DataLength;
}

#******************************************************
# bmCmdName: Response Complete Hint
#******************************************************
RESPONSE_COMPLETE_HINT()
{
    EEMCommandHdr = NextDataWord_();
    timeout = EEMCommandHdr & 0x03FF;
    AddPayLoadCell("Timeout", Format("%d s",timeout), "Timeout in seconds"); 
    if (in.DataLength > length + 2)
        AddExtraBytesPayloadCell(in.DataLength - 2);
    out.Decoded = in.DataLength;
}

#******************************************************
# bmCmdName: Tickle
#******************************************************
TICKLE()
{
    TickleData = NextDataWord_();
    if (in.DataLength > length + 2)
        AddExtraBytesPayloadCell(in.DataLength - 2);
    out.Decoded = in.DataLength;
}

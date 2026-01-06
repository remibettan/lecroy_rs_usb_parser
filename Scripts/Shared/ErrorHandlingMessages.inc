#S******************************************************************************
#*
#*  FILENAME: ErrorHandlingMessages.inc
#*
#*  Copyright (C) 2008 Elecomp Corporation
#*
#*  DESCRIPTION
#*    This is the message file for standard USB 3.0 error handling .
#*
#*  REVISION HISTORY
#*            File Created 
#*
#*******************************************************************************
set _err_NotEnoughData_Header = "Not Enough Data";
set _err_NotEnoughData_Data =  " %d bytes";
set _err_NotEnoughData_ToolTip =  " Not enough data to decode descriptor(s).";
set _err_NotMatchingDescriptor = "No Descriptor Match";
set _err_IllegalTypeCell_Header = "bReqType";
set _err_IllegalTypeCell_Data = "Illegal";
set _err_IllegalTypeCell_ToolTip = "The bmRequestType value 0x%02X is illegal for %s request";
set _err_Illegal_Value = "%s = 0x%02X \nError: only legal value is %d";
set _err_Illegal_2Values = "%s = 0x%02X \nError: only legal values are %d and %d";
set _err_GetStatus_Interface_ToolTip = "Any interface in a function other than the first one, should return all zeros";
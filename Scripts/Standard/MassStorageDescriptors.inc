#******************************************************************************
#
#  FILENAME: MassStorageDescriptors.inc
#
#  Copyright (C) 2008 LeCroy Corporation
#
#  DESCRIPTION
#    This descriptor definition file is supplied by LeCroy.
#    This file defines standard USB Mass Storage Descriptors.
#    File version is 1.0.
#       Based on Mass Storage Revision 1.0 released April , 2009
#
#
#******************************************************************************

set MassStorageDescriptorTypeTable =         #Table for Mass Storage Class specific Descriptor Type
[
    [ 0xFF, "UNKNOWN" ],
    [ 0x24, "PIPE_USAGE", "Pipe Usage" ]
];


TryMassStorageDescriptors(bDescriptorType)  #If (Mass Storage Class specific descriptor) decode; else return 0
{
    CurrentByteOffset = 0;                                              #Global variable from UsbCommon.inc
    MS_row = Find (MassStorageDescriptorTypeTable, bDescriptorType);    #Find specific descriptor

    if (MS_row[0] == 0xFF)
        return 0;

    AddShortDataHeader(FormatEx ("%s Descriptor  (%d bytes)", MS_row[2], bLength ));
    
    dataLength = bLength;                   #Length of Data from encapsulating call: bLength is defined in StandardDescriptors.inc
                                            #via other .inc files; this file is included in StandardDescriptors.inc

    if (dataLength > in.DataLength - Base ) #Checking if there is enough data
    {
      AddStringToDlg("Not enough data for this descriptor",FormatEx("Expected Length %d bytes, Actual Length %d bytes", dataLength, in.DataLength - Base), OutputUnknownData(in.DataLength - Base, 0));
      return 0;
    }

    Call (MS_row[1]);
    return 1;
}

PIPE_USAGE()
{
    base = Base;
    bLength         = GetDataByte(base);
    bDescriptorType = GetDataByte(base+1);
    bPipeId         = GetDataByte(base+2);
    
    AddEntry( 0, "bLength", bLength, 2, "Descriptor size, in bytes (including this field)", 0, 1);
    AddDescriptorSizeString(bLength);
    AddFieldBreak();

    AddEntry( 1, "bDescriptorType", bDescriptorType, 2, "The pipe associated with the endpoint descriptor", 0);
    AddFieldBreak();

    if ( bPipeId == 0x01 )
        str_PipeId = "Command Pipe";
    else if ( bPipeId == 0x02 )
        str_PipeId = "Status Pipe";
    else if ( bPipeId == 0x03 )
        str_PipeId = "Data-in Pipe";
    else if ( bPipeId == 0x04 )
        str_PipeId = "Data-out Pipe";
    else
        str_PipeId = "Reserved";

    AddEntry( 2, "B Pipe Id", bPipeId, 2,  str_PipeId , 0);
    AddFieldBreak();
}


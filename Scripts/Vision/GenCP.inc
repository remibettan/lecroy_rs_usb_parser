#*******************************************************************************
#
#  FILENAME: GenCP.inc
#
#  Copyright (c) 2013, Teledyne LeCroy - All Rights Reserved
#
#  DESCRIPTION
#    This is the Message Decode file for GenCP Standard.
#    This file is prepared as per Generic Control Protocol Version 1.0
#
#  REVISION HISTORY
#    13MAR13 First created -ag-
#
#*******************************************************************************

%include "VisionCommon.inc"    

set REQUEST_ACK = Map(
[
    [0x0000, "No"],
    [0x4000, "Yes"]
] );

set ACKNOWLEDGE_NAMESPACE = Map(
[
    [0x0000, "GenCP Status Code"],
    [0x2000, "Technology specific Code"],
    [0x4000, "Device specific Code"]
] );

set ACKNOWLEDGE_SEVERITY = Map(
[
    [0x0000, "Warning/Info"],
    [0x8000, "Error"]
] );

set COMMAND_IDs = 
[
    [0x0000, "UNKNOWN_CMD"],
    [0x0800, "READMEM_CMD"],
    [0x0801, "READMEM_ACK"],
    [0x0802, "WRITEMEM_CMD"],
    [0x0803, "WRITEMEM_ACK"],
    [0x0805, "PENDING_ACK"],
    [0x0C00, "EVENT_CMD"],
    [0x0C01, "EVENT_ACK"]
];

set STATUS_CODES = Map(
[
    [0x0000, "SUCCESS"],
    [0x8001, "NOT_IMPLEMENTED"],
    [0x8002, "INVALID_PARAMETER"],
    [0x8003, "INVALID_ADDRESS"],
    [0x8004, "WRITE_PROTECT"],
    [0x8005, "BAD_ALIGNMENT"],
    [0x8006, "ACCESS_DENIED"],
    [0x8007, "BUSY"],
    [0x800B, "MSG_TIMEOUT"],
    [0x800E, "INVALID_HEADER"],
    [0x800F, "WRONG_CONFIG"],
    [0x8FFF, "ERROR"]
] );
#-----------------------------------------------------------------------------

#####################################################################################################
# Common GenCP fields information are kept in this map.
# Each row consist of below attribute for each field :
# Field ID            : Field unique Id 
# Offset              : Field offset in byte
# Size                : Field size in byte
# Mask 	              : Field mask that can be used for masking some bits or bytes of value
# Field Name          : Field name that is shown in packet viewer
# Value Format        : This format is used in Format() method to convert field's value to string
# Value Substitute    : This array can define substitute for each field value. for example when we want to show meaningful name for numeric values
# Is Value Bitmap     : Specifies if value is a bitmap or not. 
# Tooltip             : Field tooltip that is shown in packet viewer
#####################################################################################################

set GenCP_Packet_Fields = Map(
[

    # Command Packet Layout
    # flags
    ["CCD_CMD_Reserved",                    0,  2,  0x3FFF,                  "Reserved",         "0x%04x",   null,           0,  "Reserved, set to 0"],
    ["CCD_CMD_RequestAck",                  0,  2,  0x4000,                  "RequestAck",       "%s",       REQUEST_ACK,    0,  "If set the sender requests an acknowledge packet from the command receiver"],
    ["CCD_CMD_CommandResend",               0,  2,  0x8000,                  "CommandResend",    "%d",       null,           0,  "If set the command is sent as a retry of a previous sent that failed"], 
    
    ["CCD_command_id",                      2,  2,  0xFFFF,                  "Command_id",       "%s",       COMMAND_IDs,    0,  "Command id"],
    
    ["CCD_CMD_length",                      4,  2,  0xFFFF,                  "Length",           "%d",       null,           0,  "Length of the Specific Command Data depending on the command ID not including Prefix, Postfix and CCD"],
    ["CCD_CMD_request_id",                  6,  2,  0xFFFF,                  "Request_id",       "0x%04x",   null,           0,  "Sequential number to identify a single command. This id is provided by the command sender and incremented every time a new command is issued"],

    # Acknowledge Packet Layout
    # status code
    ["CCD_ACK_StatusCode",                  0,  2,  0x0FFF,                  "Status Code",      "%s",       STATUS_CODES,   0,  "Status Code, indicating the result of the operation"],
    ["CCD_ACK_Reserved",                    0,  2,  0x1000,                  "Reserved",         "%d",       null,           0,  "Reserved Set to 0"],
    ["CCD_ACK_Namespace",                   0,  2,  0x6000,                  "Namespace",        "%s",       ACKNOWLEDGE_NAMESPACE,    0,  "0 = GenCP Status Code \n1 = Technology specific Code \n2 = Device specific Code"],
    ["CCD_ACK_Severity",                    0,  2,  0x8000,                  "Severity",         "%s",       ACKNOWLEDGE_SEVERITY,     0,  "0 = Warning/Info \n1 = Error"],
    
    ["CCD_ACK_CMD_length",                  4,  2,  0xFFFF,                  "Length",           "%d",       null,           0,  "Length of the Specific Command Data depending on the command in bytes"],
    ["CCD_ACK_CMD_request_id",              6,  2,  0xFFFF,                  "Request_id",       "0x%04x",   null,           0,  "Sequential number to identify a single command. This id is provided by the command sender and incremented every time a new command is issued"],
    
    # Specific Command Data
    # Offset of SCD fields are based on first byte of CCD
    
    # ReadMem Command
    ["CSD_READMEM_CMD_register_address",    8,  8,  0xFFFFFFFFFFFFFFFF,      "Register Address", "%s",       null,           0, "64 bit register address."],
    ["CSD_READMEM_CMD_reserved",           16,  2,  0xFFFF,                  "Reserved",         "0x%04x",   null,           0, "Reserved, set to 0"],
    ["CSD_READMEM_CMD_read_length",        18,  2,  0xFFFF,                  "Read Length",      "%d",       null,           0, "Number of bytes to read."],
    
    # ReadMem Acknowledge
    ["CSD_READMEM_ACK_Data",                8,  0,  0xFFFF,                  "Data",             "0x%x",     null,           0, "Data read from the remote device’s register map. If the number of bytes read is different than the specified in the relating READMEM_CMD the status of the READMEM_ACK must indicate the reason"],
    
    # WriteMem Command
    ["CSD_WRITEMEM_CMD_register_address",   8,  8,  0xFFFFFFFFFFFFFFFF,     "Register Address", "%s",       null,            0, "64 bit register address"],
    ["CSD_WRITEMEM_CMD_Data",              16,  0,  0xFFFF,                 "Data",             "0x%x",     null,            0, "Number of bytes to write to the remote device’s register map"],
    
    # WriteMem Acknowledge
    ["CSD_WRITEMEM_ACK_reserved",           8,  2,  0xFFFF,                 "Reserved",         "0x%04x",   null,            0, "This reserved field is only sent if the length_written field is sent with the acknowledge. If it is sent it is to be set to 0"],
    ["CSD_WRITEMEM_ACK_length_written",    10,  2,  0xFFFF,                 "Length Written",   "0x%04x",   null,            0, "Number of bytes successfully written to the remote device’s register map. The length written field must only be sent if the according bit in the Device Capability register is set"],
    
    # Pending Acknowledge
    ["CSD_PND_ACK_reserved",                8,  2,  0xFFFF,                 "Reserved",         "0x%04x",   null,            0, "Reserved, set to 0"],
    ["CSD_PND_ACK_temporary_timeout",      10,  2,  0xFFFF,                 "Temporary Timeout","0x%04x",   null,            0, "Temporary timeout for the command sent with the given request_id. The timeout is specified in ms"],
    
    # Event Command
    ["CSD_EVNT_CMD_reserved",               8,  2,  0xFFFF,                 "Reserved",         "0x%04x",   null,            0, "Reserved, set to 0"],
    ["CSD_EVNT_CMD_Event_ID",              10,  2,  0x0FFF,                 "Event ID",         "%d",       null,            0, "The event_id is a number identifying an event source"],
    ["CSD_EVNT_CMD_Event_ID_Reserved",     10,  2,  0x3000,                 "Reserved",         "%d",       null,            0, "Set to 0"],
    ["CSD_EVNT_CMD_Event_ID_Namespace",    10,  2,  0xC000,                 "Namespace",        "%s",       ACKNOWLEDGE_NAMESPACE,     0, "0 = GenCP Event ID\n1 = Technology specific Event ID\n2 = Device specific Event ID"],
    ["CSD_EVNT_CMD_timestamp",             12,  8,  0xFFFFFFFFFFFFFFFF,     "Timestamp",        "%s",       null,            0, "64 bit timestamp value in ns as defined in the timestamp bootstrap register"],
    ["CSD_EVNT_CMD_data",                  20,  0,  0xFFFF,                 "Data",             "0x%x",     null,            0, "Optional event specific data"]
] );

####################################################################################
#                                   Utility functions                              #
####################################################################################

# Decodes GenCP CCD and CSD fields
DecodeGenCPPackets(offset)
{
    # Retrieve command id
    _result = GetGenCPFieldData("CCD_command_id", offset);   
    
    # Find function name corresponding to the command id
    _func = Find( COMMAND_IDs, _result[1] );
      
    # Call proper function to decode current command 
    Call( _func[1], [offset] );        
}


UNKNOWN_CMD(offset)
{
    AddCommandPacket(offset);
    AddSeparator();
    AddCell("Unknown Command", "", "", 0x0000FF, _MONOFIELD, _MONOCOLOR); 
}

READMEM_CMD(offset)
{
    AddCommandPacket(offset);
    
    # Add CSD
    AddSeparator();    
    AddCaptionCell("SCD","","SCD - Specific Command Data(Technology agnostic)", _MONOCOLOR, _MONOFIELD);  

    AddGenCPField("CSD_READMEM_CMD_register_address",   offset);    
    if(SimpleShowItem())
        AddGenCPField("CSD_READMEM_CMD_reserved",           offset);
    AddGenCPField("CSD_READMEM_CMD_read_length",        offset);    
    
    out.Decoded += 12;    
}

READMEM_ACK(offset)
{
    CSD_length = AddAcknowledgePacket(offset);
    
    # Add CSD
    AddSeparator();    
    AddCaptionCell("SCD","","SCD - Specific Command Data(Technology agnostic)", _MONOCOLOR, _MONOFIELD);  
    
    if(SimpleShowItem())
    {
        AddGenCPDataPayloadField("CSD_READMEM_ACK_Data", offset, CSD_length);
    }
    
    out.Decoded += CSD_length;
}

WRITEMEM_CMD(offset)
{
    CSD_length = AddCommandPacket(offset);

    # Add CSD
    AddSeparator();    
    AddCaptionCell("SCD","","SCD - Specific Command Data(Technology agnostic)", _MONOCOLOR, _MONOFIELD);  
    
    if(SimpleShowItem())
    { 
        AddGenCPField("CSD_WRITEMEM_CMD_register_address",  offset);
        
        data_len = 0;
        if( CSD_length > 8)
            data_len = CSD_length - 8;

        AddGenCPDataPayloadField("CSD_WRITEMEM_CMD_Data", offset, data_len);
    }
    
    out.Decoded += CSD_length;    
}


WRITEMEM_ACK(offset)
{
    AddAcknowledgePacket(offset);
    
    # Add CSD
    AddSeparator();    
    AddCaptionCell("SCD","","SCD - Specific Command Data(Technology agnostic)", _MONOCOLOR, _MONOFIELD);  
    
    if(SimpleShowItem())
        AddGenCPField("CSD_WRITEMEM_ACK_reserved",          offset);   
    AddGenCPField("CSD_WRITEMEM_ACK_length_written",    offset);
    
    out.Decoded += 4;
}

PENDING_ACK(offset)
{
    AddAcknowledgePacket(offset);
    
    # Add CSD
    AddSeparator();
    AddCaptionCell("SCD","","SCD - Specific Command Data(Technology agnostic)", _MONOCOLOR, _MONOFIELD);  

    if(SimpleShowItem())
        AddGenCPField("CSD_PND_ACK_reserved",           offset);
    AddGenCPField("CSD_PND_ACK_temporary_timeout",  offset);
    
    out.Decoded += 4;
}

EVENT_CMD(offset)
{
    CSD_length = AddCommandPacket(offset);
    
    # Add CSD
    AddSeparator();
    AddCaptionCell("SCD","","SCD - Specific Command Data(Technology agnostic)", _MONOCOLOR, _MONOFIELD);  
    
    if(SimpleShowItem())
        AddGenCPField("CSD_EVNT_CMD_reserved",              offset);
    AddGenCPField("CSD_EVNT_CMD_Event_ID",              offset);
    if(SimpleShowItem())    
    {
        AddGenCPField("CSD_EVNT_CMD_Event_ID_Reserved",     offset);
        AddGenCPField("CSD_EVNT_CMD_Event_ID_Namespace",    offset);
    }
    AddGenCPField("CSD_EVNT_CMD_timestamp",             offset);
    
    if(SimpleShowItem())
    {
        data_len = 0;
        if( CSD_length > 12)
            data_len = CSD_length - 12;
                
        AddGenCPDataPayloadField("CSD_EVNT_CMD_data",       offset, data_len);                
    }
    
    out.Decoded += CSD_length;
}

EVENT_ACK(offset)
{
    AddAcknowledgePacket(offset);
}

# Returns length of SCD
AddCommandPacket(offset)
{   
    AddCaptionCell("CCD","Command","CCD - Common Command Data(Technology agnostic)", _MONOCOLOR);  
    
    if(SimpleShowItem())
    {
        AddGenCPField("CCD_CMD_Reserved",       offset);        
        AddGenCPField("CCD_CMD_RequestAck",     offset);
        AddGenCPField("CCD_CMD_CommandResend",  offset);
    }
    
    AddGenCPField("CCD_command_id", offset);

    if(SimpleShowItem())
    {
        _length = AddGenCPField("CCD_CMD_length",   offset);
        AddGenCPField("CCD_CMD_request_id",         offset);
    }
    else
    {
        _length = GetGenCPFieldData("CCD_CMD_length",  offset);
    }
     
    out.Decoded += 8;
     
    return _length[1];
}

AddAcknowledgePacket(offset)
{  
    AddCaptionCell("CCD","Acknowledge","CCD - Common Command Data(Technology agnostic)", _MONOCOLOR);  

    AddGenCPField("CCD_ACK_StatusCode", offset);

    if(SimpleShowItem())
    {
        AddGenCPField("CCD_ACK_Reserved",   offset);
        AddGenCPField("CCD_ACK_Namespace",  offset);
        AddGenCPField("CCD_ACK_Severity",   offset);
    }
    
    AddGenCPField("CCD_command_id", offset);
    
    if(SimpleShowItem())
    {
        _length = AddGenCPField("CCD_ACK_CMD_length",   offset);
        AddGenCPField("CCD_ACK_CMD_request_id",         offset);
    }
    else
    {
        _length = GetGenCPFieldData("CCD_ACK_CMD_length",  offset);
    }

    out.Decoded += 8;
    
    return _length[1];
}

AddGenCPDataPayloadField(FieldId, offset, len)
{
    AddDataPayloadField(FieldId, offset, len, GenCP_Packet_Fields);
}


GetGenCPFieldData(FieldId, offset)
{
    return GetFieldData(FieldId, offset, GenCP_Packet_Fields);
}
            
AddGenCPField(FieldId, offset)
{
    AddField(FieldId, offset, GenCP_Packet_Fields);
}

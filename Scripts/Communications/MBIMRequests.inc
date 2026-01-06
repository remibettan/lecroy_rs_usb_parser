#*******************************************************************************
#  Copyright (c) 2013, LeCroy - All Rights Reserved
#
#  Mobile Broadband Interface Model request decoder
#
#*******************************************************************************

#------------------------------------------------------------------------------------------
# type,     type name                                                    |
#------------------------------------------------------------------------------------------
set MBIMRequestTypeTable = Map(
[   
	[0x05,  "RESET_FUNCTION" ]
] );

set MBIM_Message_Direction = Map(
[
    [0xFF, "-"],
    [0x00, "H->F"],
    [0x80, "F->H"]
] );

set MBIM_Command_type = Map(
[
    [0xFF, "-"],
    [0x00, "Query"],
    [0x01, "Set"]
] );

# Host to Function commands
set MBIM_Message_Types = 
[
    [0x00000001, "MBIM_OPEN_MSG"],
    [0x00000002, "MBIM_CLOSE_MSG"],
    [0x00000003, "MBIM_COMMAND_MSG"],
    [0x00000004, "MBIM_HOST_ERROR_MSG"],
    [0x80000001, "MBIM_OPEN_DONE"],
    [0x80000002, "MBIM_CLOSE_DONE"],
    [0x80000003, "MBIM_COMMAND_DONE"],
    [0x80000004, "MBIM_FUNCTION_ERROR_MSG"],
    [0x80000007, "MBIM_INDICATE_STATUS_MSG"]
];

set MBIM_PROTOCOL_ERROR_CODES = Map(
[
    [1, "MBIM_ERROR_TIMEOUT_FRAGMENT"],
    [2, "MBIM_ERROR_FRAGMENT_OUT_OF_SEQUENCE"],
    [3, "MBIM_ERROR_LENTH_MISMATCH"],
    [4, "MBIM_ERROR_DUPLICATED_TID"],
    [5, "MBIM_ERROR_NOT_OPENED"],
    [6, "MBIM_ERROR_UNKNOWN"],
    [7, "MBIM_ERROR_CANCEL"],
    [7, "MBIM_ERROR_MAX_TRANSFER"]
] );

set MBIM_Service_UUID = Map(
[
    [ "00000000000000000000000000000000", "UUID_Unknown"],
    [ "a289cc33bcbb8b4fb6b0133ec2aae6df", "UUID_BASIC_CONNECT"],
    [ "533fbeeb14fe44679f9033a223e56c3f", "UUID_SMS"],
    [ "e550a0c85e82479e82f710abf4c3351f", "UUID_USSD"],
    [ "4bf384761e6a41dbb1d8bed289c25bdb", "UUID_PHONEBOOK"],
    [ "d8f20131fcb54e178602d6ed3816164c", "UUID_STK"],
    [ "1d2b5ff70aa148b2aa5250f15767174e", "UUID_AUTH"],
    [ "c08a26dd7718438284826e0d583c4d0e", "UUID_DSS"]    
       
] );

set MBIM_BASIC_CONNECT_CIDs = Map(
[
    [0, "Unknown"],
    [1, "MBIM_CID_DEVICE_CAPS"],
    [2, "MBIM_CID_SUBSCRIBER_READY_STATUS"],
    [3, "MBIM_CID_RADIO_STATE"],
    [4, "MBIM_CID_PIN"],    
    [5, "MBIM_CID_PIN_LIST"],
    [6, "MBIM_CID_HOME_PROVIDER"],
    [7, "MBIM_CID_PREFERRED_PROVIDERS"],    
    [8, "MBIM_CID_VISIBLE_PROVIDERS"],
    [9, "MBIM_CID_REGISTER_STATE"],
    [10, "MBIM_CID_PACKET_SERVICE"],    
    [11, "MBIM_CID_SIGNAL_STATE"],
    [12, "MBIM_CID_CONNECT"],
    [13, "MBIM_CID_PROVISIONED_CONTEXTS"],    
    [14, "MBIM_CID_SERVICE_ACTIVATION"],
    [15, "MBIM_CID_IP_CONFIGURATION"],
    [16, "MBIM_CID_DEVICE_SERVICES"],    
    [19, "MBIM_CID_DEVICE_SERVICE_SUBSCRIBE_LIST"],
    [20, "MBIM_CID_PACKET_STATISTICS"],
    [21, "MBIM_CID_NETWORK_IDLE_HINT"],    
    [22, "MBIM_CID_EMERGENCY_MODE"],
    [23, "MBIM_CID_IP_PACKET_FILTERS"],
    [24, "MBIM_CID_MULTICARRIER_PROVIDERS"]
] );

set MBIM_SMS_CIDs = Map(
[
    [0, "Unknown"],
    [1, "MBIM_CID_SMS_CONFIGURATION"],
    [2, "MBIM_CID_SMS_READ"],
    [3, "MBIM_CID_SMS_SEND"],    
    [4, "MBIM_CID_SMS_DELETE"],
    [5, "MBIM_CID_SMS_MESSAGE_STORE_STATUS"]
] );
    
set MBIM_USSD_CIDs = Map(
[
    [0, "Unknown"],
    [1, "MBIM_CID_USSD"]
] );

set MBIM_PHONEBOOK_CIDs = Map(
[
    [0, "Unknown"],
    [1, "MBIM_CID_PHONEBOOK_CONFIGURATION"],
    [2, "MBIM_CID_PHONEBOOK_READ"],
    [3, "MBIM_CID_PHONEBOOK_DELETE"],
    [3, "MBIM_CID_PHONEBOOK_WRITE"]
] );

set MBIM_STK_CIDs = Map(
[
    [0, "Unknown"],
    [1, "MBIM_CID_STK_PAC"],
    [2, "MBIM_CID_STK_TERMINAL_RESPONSE"],
    [3, "MBIM_CID_ENVELOPE"]
] );

set MBIM_AUTH_CIDs = Map(
[    
    [0, "Unknown"],
    [1, "MBIM_CID_AKA_AUTH"],
    [2, "MBIM_CID_AKAP_AUTH"],
    [3, "MBIM_CID_SIM_AUTH"]
] );

set MBIM_DSS_CIDs = Map(
[
    [0, "Unknown"],
    [1, "MBIM_CID_DSS_CONNECT"]
] );

set MBIM_STATUS_CODES = Map(
[
    [0xFFFFFFFF, "Device Service Specific"],
    [0, "MBIM_STATUS_SUCCESS"],
    [1, "MBIM_STATUS_BUSY"],
    [2, "MBIM_STATUS_FAILURE"],
    [3, "MBIM_STATUS_SIM_NOT_INSERTED"],
    [4, "MBIM_STATUS_BAD_SIM"],
    [5, "MBIM_STATUS_PIN_REQUIRED"],
    [6, "MBIM_STATUS_PIN_DISABLED"],
    [7, "MBIM_STATUS_NOT_REGISTERED"],
    [8, "MBIM_STATUS_PROVIDERS_NOT_FOUND"],
    [9, "MBIM_STATUS_NO_DEVICE_SUPPORT"],
    [10, "MBIM_STATUS_PROVIDER_NOT_VISIBLE"],
    [11, "MBIM_STATUS_DATA_CLASS_NOT_AVAILABLE"],
    [12, "MBIM_STATUS_PACKET_SERVICE_DETACHED"],
    [13, "MBIM_STATUS_MAX_ACTIVATED_CONTEXTS"],
    [14, "MBIM_STATUS_NOT_INITIALIZED"],
    [15, "MBIM_STATUS_VOICE_CALL_IN_PROGRESS"],
    [16, "MBIM_STATUS_CONTEXT_NOT_ACTIVATED"],
    [17, "MBIM_STATUS_SERVICE_NOT_ACTIVATED"],
    [18, "MBIM_STATUS_INVALID_ACCESS_STRING"],
    [19, "MBIM_STATUS_INVALID_USER_NAME_PWD"],
    [20, "MBIM_STATUS_RADIO_POWER_OFF"],
    [21, "MBIM_STATUS_INVALID_PARAMETERS"],
    [22, "MBIM_STATUS_READ_FAILURE"],
    [23, "MBIM_STATUS_WRITE_FAILURE"],
    [24, "Reserved"],
    [25, "MBIM_STATUS_NO_PHONEBOOK"],
    [26, "MBIM_STATUS_PARAMETER_TOO_LONG"],
    [27, "MBIM_STATUS_STK_BUSY"],
    [28, "MBIM_STATUS_OPERATION_NOT_ALLOWED"],
    [29, "MBIM_STATUS_MEMORY_FAILURE"],
    [30, "MBIM_STATUS_INVALID_MEMORY_INDEX"],
    [31, "MBIM_STATUS_MEMORY_FULL"],
    [32, "MBIM_STATUS_FILTER_NOT_SUPPORTED"],
    [33, "MBIM_STATUS_DSS_INSTANT_LIMIT"],
    [34, "MBIM_STATUS_INVALID_DEVICE_SERVICE_OPERATION"],
    [35, "MBIM_STATUS_AUTH_INCORRECT_AUTN"],
    [36, "MBIM_STATUS_AUTH_SYNC_FAILURE"],
    [37, "MBIM_STATUS_AUTH_AMF_NOT_SET"],    
    [100, "MBIM_STATUS_SMS_UNKNOWN_SMSC_ADDRESS"],
    [101, "MBIM_STATUS_SMS_NETWORK_TIMEOUT"],
    [102, "MBIM_STATUS_SMS_LANG_NOT_SUPPORTED"],
    [103, "MBIM_STATUS_SMS_ENCODING_NOT_SUPPORTED"],
    [104, "MBIM_STATUS_SMS_FORMAT_NOT_SUPPORTED"]            
] );

#####################################################################################################
# Common MBIM fields information are kept in this map.
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
set MBIM_Request_Fields = Map( 
[
    ["MessageType",             0, 4,     0xFFFFFFFF, "MessageType",       "%s", MBIM_Message_Types,       0, "MBIM Message Type"],
    ["Direction",               3, 1,     0x80,       "Dir",               "%s", MBIM_Message_Direction,   0, "Message Direction"],
    ["MessageLength",           4, 4,     0xFFFFFFFF, "MessageLen",        "%d", null,                     0, "Total length of this MBIM Message"],
    ["TransactionId",           8, 4,     0xFFFFFFFF, "TransId",           "%d", null,                     0, "This value is used to match host-sent message with function responses"],
    
    ["TotalFragments",          12, 4,     0xFFFFFFFF, "TotalFrag",        "%d", null,                     0, "This field indicates how many fragments there are in total"],
    ["CurrentFragment",         16, 4,     0xFFFFFFFF, "CurrFrag",         "%d", null,                     0, "This field indicates which fragment this message is"],
    
    ["MaxControlTransfer",      12, 4,     0xFFFFFFFF, "MaxCtlTransfer",   "%d", null,                     0, "Maximum control transfer the host supports"],
    
    ["DeviceServiceId",         20, 16, 0,             "DevSrvcId",        "%s", MBIM_Service_UUID,        0, "A 16 byte UUID that identifies the device service the following CID value applies"],    
    
    ["CID_UUID_Unknown",        36, 4,     0xFFFFFFFF, "CID",      "%d", null,                      0, "Specifies the CID that identifies the parameter being queried for"],
    ["CID_UUID_BASIC_CONNECT",  36, 4,     0xFFFFFFFF, "CID",      "%s", MBIM_BASIC_CONNECT_CIDs,   0, "Specifies the CID that identifies the parameter being queried for"],
    ["CID_UUID_SMS",            36, 4,     0xFFFFFFFF, "CID",      "%s", MBIM_SMS_CIDs,             0, "Specifies the CID that identifies the parameter being queried for"],
    ["CID_UUID_USSD",           36, 4,     0xFFFFFFFF, "CID",      "%s", MBIM_USSD_CIDs,            0, "Specifies the CID that identifies the parameter being queried for"],
    ["CID_UUID_PHONEBOOK",      36, 4,     0xFFFFFFFF, "CID",      "%s", MBIM_PHONEBOOK_CIDs,       0, "Specifies the CID that identifies the parameter being queried for"],
    ["CID_UUID_STK",            36, 4,     0xFFFFFFFF, "CID",      "%s", MBIM_STK_CIDs,             0, "Specifies the CID that identifies the parameter being queried for"],
    ["CID_UUID_AUTH",           36, 4,     0xFFFFFFFF, "CID",      "%s", MBIM_AUTH_CIDs,            0, "Specifies the CID that identifies the parameter being queried for"],
    ["CID_UUID_DSS",            36, 4,     0xFFFFFFFF, "CID",      "%s", MBIM_DSS_CIDs,             0, "Specifies the CID that identifies the parameter being queried for"],
    
    ["CommandType",             40, 4,     0xFFFFFFFF, "CommType",         "%s", MBIM_Command_type,         0, "Command Type: 0 for a Query operation, 1 for a Set operation"],
    ["Status",                  40, 4,     0xFFFFFFFF, "Status",           "%s", MBIM_STATUS_CODES,         0, ""],    
    
    ["InfoBufferLenComm",       44, 4,     0xFFFFFFFF, "InfoBufferLen",     "%d", null,                     0, "Size of the total information buffer"],
    ["InfoBufferComm",          48, 0,     0,          "InfoBuffer",        "%d", null,                     0, ""],
    
    ["ErrorStatusCode",         12, 4,     0xFFFFFFFF, "ErrorStatusCode",   "%s", MBIM_PROTOCOL_ERROR_CODES,0, ""],
    
    ["OpenCloseStatus",         12, 4,     0xFFFFFFFF, "Status",             "%s", MBIM_STATUS_CODES,       0, ""],
            
    ["InfoBufferLenStatus",     40, 4,     0xFFFFFFFF, "InfoBufferLen",     "%d", null,                     0, "Size of the total information buffer"],    
    ["InfoBufferStatus",        44, 0,     0,          "InfoBuffer",        "%d", null,                     0, ""]
    
] );

####################################################################################################
#                                        Main Fields Functions                                          #
####################################################################################################

ShowMBIMCommandField( request_type )
{       
    offset = 8;
    
    _row = GetMBIMFieldData("MessageType", offset, MBIM_Request_Fields);
    if( _row[0] != 1 ) 
    {
        AddDataPayloadFieldForRemain(offset);
        
        return 0;
    }

    MessageType = _row[1];

    _row = Find( MBIM_Message_Types, MessageType );
    
    AddSeparator();
    AddCaptionCell("Message","Message","MBIM Control Message", _MONOCOLOR, _MONOFIELD);
    AddSeparator();        

    Call( _row[1], [offset], request_type );
	
	out.Decoded = in.DataLength;
}

ShowMBIMMessageHeader(offset)
{
    AddMBIMRequestField("MessageType", offset);
    AddMBIMRequestField("MessageLength", offset);    
    AddMBIMRequestField("TransactionId", offset);
}

ShowMBIMFragmentHeader(offset)
{
    curr_fragment = 0;
    
    if( SimpleShowItem() )
    {
        AddMBIMRequestField("TotalFragments", offset);
        _row = AddMBIMRequestField("CurrentFragment", offset); 
        curr_fragment = _row[1];
    }
    else
    {
        _row = GetMBIMRequestFieldData("CurrentFragment", offset);
        curr_fragment = _row[1];
    }

    if(curr_fragment == 0)
        return 1;
    else
        return 0;
}

MBIM_OPEN_MSG(offset, request_type)
{    
    ShowMBIMMessageHeader(offset);
    
    if( SimpleShowItem() )
    {
        AddMBIMRequestField("MaxControlTransfer", offset);
    }
}

MBIM_CLOSE_MSG(offset, request_type)
{
    ShowMBIMMessageHeader(offset);
}

MBIM_COMMAND_MSG(offset, request_type)
{
    ShowMBIMMessageHeader(offset);
    can_decode = ShowMBIMFragmentHeader(offset);

    if( !can_decode )
    {
        AddCell("Current Decoder does not support fragmented commands", "", "", 0x00FFFF, _MONOCOLOR, _MONOFIELD);
        AddDataPayloadFieldForRemain(offset);
        return 0;
    }
    
    _row = AddMBIMRequestField("DeviceServiceId", offset);    
    service_uuid = _row[1];    
    
    _row = Find(MBIM_Service_UUID, service_uuid);    
    service_name = _row[1];    

    SetCellColor(MBIM_COMMAND_COLOR);    
    
    service_name_CID = "CID_" + service_name;        
    _row = AddMBIMRequestField(service_name_CID, offset);
    CID_value = _row[1];

    RestoreCellColor();
    
    _row = AddMBIMRequestField("CommandType", offset);
    command_type = _row[1];
    
    _row = AddMBIMRequestField("InfoBufferLenComm", offset);
    InfoBufferLen = _row[1];
    
    if( InfoBufferLen > 0 )
    {
        # Just to find offset of payload        
        _row = Find(MBIM_Request_Fields, "InfoBufferComm");
        CID_offset = offset + _row[1];
        
        
        # To find CID name that is used as function name
        CID_Function_Name = "";
        _row = Find(MBIM_Request_Fields, service_name_CID);
        values_array = _row[6];
        if( values_array != null )
        {
            _names = Find(values_array, CID_value);
            CID_Function_Name = _names[1];
                
            # command_type == 0 means Query             
            if(command_type == 0) 
            {
                # request_type == 0 means SEND_ENCAPSULATED_COMMAND
                if( request_type == 0)
                    CID_Function_Name += "_Query_Com";
                else
                    CID_Function_Name += "_Response";
                
            }
            # command_type == 1 means Set            
            else 
            {
                if( request_type == 0)
                    CID_Function_Name += "_Set_Com";
                else
                    CID_Function_Name += "_Response";
            }

            SetCellColor(MBIM_COMMAND_COLOR);            
            
            AddSeparator();            
            AddCaptionCell("Command","","", _MONOCOLOR, _MONOFIELD);            
            AddSeparator();
            
            if( SimpleShowItem() )
            {
                Call( CID_Function_Name, [CID_offset] );
            }
            
            RestoreCellColor();
        }
        else
        {
            AddMBIMDataPayloadFieldForRemain("InfoBufferComm", offset, MBIM_Request_Fields);    
        }
    }

}

MBIM_HOST_ERROR_MSG(offset, request_type)
{
    ShowMBIMMessageHeader(offset);
    AddMBIMRequestField("ErrorStatusCode", offset);
}

MBIM_OPEN_DONE(offset, request_type)
{
    ShowMBIMMessageHeader(offset);
    AddMBIMRequestField("OpenCloseStatus", offset);
}

MBIM_CLOSE_DONE(offset, request_type)
{
    ShowMBIMMessageHeader(offset);
    AddMBIMRequestField("OpenCloseStatus", offset);
}

MBIM_COMMAND_DONE(offset, request_type)
{
    ShowMBIMMessageHeader(offset);
    can_decode = ShowMBIMFragmentHeader(offset);

    if( !can_decode )
    {
        AddCell("Current Decoder does not support fragmented commands", "", "", 0x00FFFF, _MONOCOLOR, _MONOFIELD);
        AddDataPayloadFieldForRemain(offset);
        
        return 0;
    }
    

    _row = AddMBIMRequestField("DeviceServiceId", offset);
    service_uuid = _row[1];
    
    _row = Find(MBIM_Service_UUID, service_uuid);    
    service_name = _row[1];    
    
    SetCellColor(MBIM_COMMAND_COLOR);                
    
    service_name_CID = "CID_" + service_name;            
    _row = AddMBIMRequestField(service_name_CID, offset);
    CID_value = _row[1];

    RestoreCellColor();

    
    AddMBIMRequestField("Status", offset);
    
    _row = AddMBIMRequestField("InfoBufferLenComm", offset);
    InfoBufferLen = _row[1];
    
    if( InfoBufferLen > 0 )
    {
        # Just to find offset of payload        
        _row = Find(MBIM_Request_Fields, "InfoBufferComm");
        CID_offset = offset + _row[1];

        # To find CID name that is used as function name
        CID_Function_Name = "";
        _row = Find(MBIM_Request_Fields, service_name_CID);
        values_array = _row[6];
        if( values_array != null )
        {
            _names = Find(values_array, CID_value);
            CID_Function_Name = _names[1];

            # request_type == 0 means SEND_ENCAPSULATED_COMMAND
        
            CID_Function_Name += "_Response";

            SetCellColor(MBIM_COMMAND_COLOR);            
            
            AddSeparator();
            AddCaptionCell("Command","","", _MONOCOLOR, _MONOFIELD);            
            AddSeparator();
                                        
            if( SimpleShowItem() )
            {
                Call( CID_Function_Name, [CID_offset] );
            }
            
            RestoreCellColor();
        }
        else
        {    
            AddMBIMDataPayloadFieldForRemain("InfoBufferComm", offset, MBIM_Request_Fields);
        }
    }
    
}

MBIM_FUNCTION_ERROR_MSG(offset, request_type)
{
    ShowMBIMMessageHeader(offset);
    AddMBIMRequestField("ErrorStatusCode", offset);    
}

MBIM_INDICATE_STATUS_MSG(offset, request_type)
{
    ShowMBIMMessageHeader(offset);
    can_decode = ShowMBIMFragmentHeader(offset);
    
    if( !can_decode )
    {
        AddCell("Current Decoder does not support fragmented commands", "", "", 0x00FFFF, _MONOCOLOR, _MONOFIELD);
        AddDataPayloadFieldForRemain(offset);
        
        return 0;
    }
    
    _row = AddMBIMRequestField("DeviceServiceId", offset);
    service_uuid = _row[1];
        
    _row = Find(MBIM_Service_UUID, service_uuid);    
    service_name = _row[1];    
    
    SetCellColor(MBIM_COMMAND_COLOR);                
    
    service_name_CID = "CID_" + service_name;
    _row = AddMBIMRequestField(service_name_CID, offset);
    CID_value = _row[1];

    RestoreCellColor();
    
    _row = AddMBIMRequestField("InfoBufferLenStatus", offset);
    InfoBufferLen = _row[1];
        
    if( InfoBufferLen > 0 )
    {
        # Just to find offset of payload
        _row = Find(MBIM_Request_Fields, "InfoBufferComm");
        CID_offset = offset + _row[1];
        
        
        # To find CID name that is used as function name
        CID_Function_Name = "";
        _row = Find(MBIM_Request_Fields, service_name_CID);
        values_array = _row[6];
        if( values_array != null )
        {
            _names = Find(values_array, CID_value);
            CID_Function_Name = _names[1];
            
            CID_Function_Name += "_Notification_Res";

            SetCellColor(MBIM_COMMAND_COLOR);            
            
            AddSeparator();
            AddCaptionCell("Command","","", _MONOCOLOR, _MONOFIELD);            
            AddSeparator();
            
            if( SimpleShowItem() )
            {
                Call( CID_Function_Name, [CID_offset] );
            }
            
            RestoreCellColor();            
        }
        else
        {            
            AddMBIMDataPayloadFieldForRemain("InfoBufferStatus", offset, MBIM_Request_Fields);    
        }
    }

}

####################################################################################################
#                                            CID Structures                                                  #
####################################################################################################


######################### CID DEVICE CAPS INFO #################

set MBIM_DEVICE_TYPE = Map(
[    
    [1, "Embedded"],
    [2, "Removable"],
    [3, "Remote"]
] );

set MBIM_CELLULAR_CLASS = Map(
[    
    [1, "Gsm"],
    [2, "Cdma"]
] );

set MBIM_VOICE_CLASS = Map(
[    
    [0, "Unknown"],
    [1, "NoVoice"],
    [2, "SeparateVoiceData"],
    [3, "SimultaneousVoiceData"]
] );

set MBIM_SIM_CLASS = Map(
[    
    [1, "SimLogical"],
    [2, "SimRemovable"]
] );

set MBIM_DATA_CLASS = Map(
[    
    [0xFF, "Reserved"],
    [0x00, "None"],
    [0x01, "GPRS"],
    [0x02, "EDGE"],
    [0x04, "UMTS"],
    [0x08, "HSDPA"],
    [0x10, "HSUPA"],
    [0x20, "LTE"],
    [0x10000, "1XRTT"],
    [0x20000, "1xEVDO"],
    [0x40000, "1xEVDORevA"],    
    [0x80000, "1XEVDV"],
    [0x100000, "3XRTT"],
    [0x200000, "1XEVDORevB"],    
    [0x400000, "UMB"],    
    [0x80000000, "Custom"]
] );

set MBIM_SMS_CAPS = Map(
[    
    [0x00, "None"],
    [0x01, "PduReceive"],
    [0x02, "PduSend"],
    [0x04, "TextReceive"],
    [0x08, "TextSend"]
] );

set MBIM_CTRL_CAPS = Map(
[    
    [0x00, "None"],
    [0x01, "RegManual"],
    [0x02, "HwRadioSwitch"],
    [0x04, "CdmaMobileIp"],
    [0x08, "CdmaSimpleIp"],
    [0x10, "MultiCarrier"]
] );

################## CID Subscriber Ready Status #################

set MBIM_SUBSCRIBER_READY_STATE = Map(
[    
    [0, "NotInitialized"],
    [1, "Initialized"],
    [2, "SimNotInserted"],
    [3, "BadSim"],
    [4, "Failure"],
    [5, "NotActivated"],
    [6, "DeviceLocked"]
] );

set MBIM_UNIQUE_ID_FLAGS = Map(
[    
    [0, "None"],
    [1, "ProtectUniqueID"]
] );

######################### CID Radio state ######################

set MBIM_RADIO_SWITCH_STATE = Map(
[    
    [0, "Off"],
    [1, "On"]
] );

########################### CID PIN ########################

set MBIM_PIN_TYPE = Map(
[    
    [0, "None"],
    [1, "Custom"],
    [2, "Pin1"],
    [3, "Pin2"],
    [4, "DeviceSimPin"],
    [5, "DeviceFirstSimPin"],
    [6, "NetworkPin"],
    [7, "NetworkSubsetPin"],
    [8, "ServiceProviderPin"],
    [9, "CorporatePin"],
    [10, "SubsidyLock"],
    [11, "Puk1"],
    [12, "Puk2"],
    [13, "DeviceFirstSimPuk"],
    [14, "NetworkPuk"],
    [15, "NetworkSubsetPuk"],
    [16, "ServiceProviderPuk"],
    [17, "CorporatePuk"]
] );

set MBIM_PIN_STATE = Map(
[    
    [0, "Unlocked"],
    [1, "Locked"]
] );

set MBIM_PIN_OPERATION = Map(
[    
    [0, "Enter"],
    [1, "Enable"],
    [2, "Disable"],
    [3, "Change"]
] );

########################### CID PIN LIST ########################

set MBIM_PIN_MODE = Map(
[    
    [0, "NotSupported"],
    [1, "Enabled"],
    [2, "Disabled"]
] );

set MBIM_PIN_FORMAT = Map(
[    
    [0, "Unknown"],
    [1, "Numeric"],
    [2, "AlphaNumeric"]
] );

####################### CID HOME PROVIDER #######################

set MBIM_HOME_PROVIDER_STATE = Map(
[    
    [0x00, "Unknown"],
    [0x01, "Home"],
    [0x02, "Forbidden"],
    [0x04, "Preferred"],
    [0x08, "Visible"],
    [0x10, "Registered"],
    [0x20, "Preferred Multicarrier"]
] );

#####################  CID VISIBLE PROVIDER #####################

set MBIM_VISIBLE_PROVIDERS_ACTION = Map(
[    
    [0, "ActionFullScan"],
    [1, "ActionRestrictedScan"]
] );

####################### CID REGISTER_STATE  #####################

set MBIM_REGISTER_ACTION = Map(
[    
    [0, "Automatic"],
    [1, "Manual"]
] );

set MBIM_REGISTER_STATE = Map(
[    
    [0, "Unknown"],
    [1, "Deregistered"],
    [2, "Searching"],
    [3, "Home"],
    [4, "Roaming"],
    [5, "Partner"],
    [6, "Denied"]
] );

set MBIM_REGISTER_MODE = Map(
[    
    [0, "Unknown"],
    [1, "Automatic"],
    [2, "Manual"]
] );

set MBIM_REGISTER_FLAG = Map(
[    
    [0, "None"],
    [1, "Manual Selection Not Available"],
    [2, "Packet Service Automatic Attach"]
] );

##################### CID PACKET SERVICE  ###################

set MBIM_PACKET_SERVICE_ACTION = Map(
[    
    [0, "Attach"],
    [1, "Detach"]
] );

set MBIM_PACKET_SERVICE_STATE = Map(
[    
    [0, "Unknown"],
    [1, "Attaching"],
    [2, "Attached"],
    [3, "Detaching"],
    [4, "Detached"]
] );

##################### CID CONNECT #####################

set MBIM_ACTIVATION_COMMAND = Map(
[    
    [0, "Deactivate"],
    [1, "Activate"]
] );

set MBIM_COMPRESSION = Map(
[    
    [0, "None"],
    [1, "Enable"]
] );

set MBIM_AUTH_PROTOCOL = Map(
[    
    [0, "None"],
    [1, "Pap"],
    [2, "Chap"],    
    [3, "MsChapV2"]
] );

set MBIM_CONTEXT_IP_TYPE = Map(
[    
    [0, "Default"],
    [1, "IPv4"],
    [2, "IPv6"],    
    [3, "IPv4v6"],
    [4, "IPv4AndIPv6"]
] );

set MBIM_ACTIVATION_STATE = Map(
[    
    [0, "Unknown"],
    [1, "Activated"],
    [2, "Activating"],    
    [3, "Deactivated"],
    [4, "Deactivating"]
] );

set MBIM_VOICE_CALL_STATE = Map(
[    
    [0, "None"],
    [1, "InProgress"],
    [2, "HangUp"]
] );

set MBIM_CONTEXT_TYPE = Map(
[    
    ["b43f758ca5604b46b35ec5869641fb54", "None"],
    ["7e5e2a7e4e6f7272736b656e7e5e2a7e", "Internet"],
    ["9b9f7bbe895244b783acca41318df7a0", "Vpn"],
    ["889182940ef443968ccaa8588fbc02b2", "Voice"],
    ["05a2a7167c344b4d9a91c5ef0c7aaacc", "VideoShare"],
    ["b3272496ac6c422ba8c0acf687a27217", "Purchase"],
    ["21610d0130744bce9425b53a07d697d6", "IMS"],
    ["4672666472696bc69624d1d35389aca9", "MMS"],
    ["a57a9afcb09f45d7bb40033c39f60db9", "Local"]
] );

################# CID SMS CONFIGURATION ################

set MBIM_SMS_STORAGE_STATE = Map(
[    
    [0, "NotInitialized"],
    [1, "Initialized"]
] );

set MBIM_SMS_FORMAT = Map(
[    
    [0, "Pdu"],
    [1, "Cdma"]
] );

##################### CID SMS READ  ####################

set MBIM_SMS_FLAG = Map(
[    
    [0, "All"],
    [1, "Index"],
    [2, "New"],
    [3, "Old"],
    [4, "Sent"],
    [5, "Draft"]
] );

set MBIM_SMS_CDMA_LANG = Map(
[    
    [0, "Unknown"],
    [1, "English"],
    [2, "French"],
    [3, "Spanish"],
    [4, "Japanese"],
    [5, "Korean"],
    [6, "Chinese"],
    [7, "Hebrew"]
    
] );

set MBIM_SMS_CDMA_ENCODING = Map(
[    
    [0, "Octet"],
    [1, "Epm"],
    [2, "7BitAscii"],
    [3, "Ia5"],
    [4, "Unicode"],
    [5, "ShiftJis"],
    [6, "Korean"],
    [7, "LatinHebrew"],
    [8, "Latin"],
    [9, "Gsm7Bit"]    
] );

set MBIM_SMS_MESSAGE_STATUS = Map(
[    
    [0, "New"],
    [1, "Old"],
    [2, "Draft"],
    [3, "Sent"]
] );

########## CID SMS MESSAGE STORE STATUS  ##########

set MBIM_SMS_STATUS_FLAGS = Map(
[    
    [0, "None"],
    [1, "MessageStoreFull"],
    [2, "NewMessage"]
] );

################### CID USSD  ####################

set MBIM_USSD_ACTION = Map(
[    
    [0, "Initiate"],
    [1, "Continue"],
    [2, "Cancel"]
] );

set MBIM_USSD_RESPONSE = Map(
[    
    [0, "NoActionRequired"],
    [1, "ActionRequired"],
    [2, "TerminatedByNW"],
    [3, "OtherLocalClient"],
    [4, "OperationNotSupported"],
    [5, "NetworkTimeOut"]    
] );

set MBIM_USSD_SESSION_STATE = Map(
[    
    [0, "NewSession"],
    [1, "ExistingSession"]
] );

########## CID PHONEBOOK CONFIGURATION  ##########

set MBIM_PHONEBOOK_STATE = Map(
[    
    [0, "NotInitialized"],
    [1, "Initialized"]
] );

############### CID PHONEBOOK READ ###############

set MBIM_PHONEBOOK_FLAG = Map(
[    
    [0, "FlagAll"],
    [1, "FlagIndex"]
] );

############### CID PHONEBOOK WRITE  #############

set MBIM_PHONEBOOK_WRITE_FLAG = Map(
[    
    [0, "SaveUnused"],
    [1, "SaveIndex"]
] );

################# CID STK PAC   ##################

set MBIM_STK_PAC_TYPE = Map(
[    
    [0, "ProactiveCommand"],
    [1, "Notification"]
] );

########## CID NETWORK IDLE HINT  ###############

set MBIM_NETWORK_IDLE_HINT_STATES = Map(
[    
    [0, "Disabled"],
    [1, "Enabled"]
] );

############# CID EMERGENCY MODE  ###############

set MBIM_EMERGENCY_MODE_STATES = Map(
[    
    [0, "ModeOff"],
    [1, "ModeOn"]
] );

############### CID DSS CONNECT  ################

set MBIM_DSS_LINK_STATE = Map(
[    
    [0, "Deactivate"],
    [1, "Activate"]
] );

#####################################################################################################
# MBIM commands fields information are kept in this map.
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
set MBIM_CID_Fields = Map( 
[
    # MBIM_DEVICE_CAPS_INFO
    ["DeviceType",         0, 4, 0xFFFFFFFF,  "DeviceType",             "%s",         MBIM_DEVICE_TYPE,     0, "Device Type"],
    ["CellularClass",      4, 4, 0xFFFFFFFF,  "CellularClass",          "%s",         MBIM_CELLULAR_CLASS,  0, "Cellular class"],
    ["VoiceClass",         8, 4, 0xFFFFFFFF,  "VoiceClass",             "%s",         MBIM_VOICE_CLASS,     0, "Voice class"],
    ["SimClass",           12,4, 0xFFFFFFFF,  "SIMClass",               "%s",         MBIM_SIM_CLASS,       0, "SIM class"],
    ["DataClass",          16,4, 0xFFFFFFFF,  "DataClass",              "%s",         MBIM_DATA_CLASS,      1, "Data class"],
    ["SmsCaps",            20,4, 0xFFFFFFFF,  "SMSCaps",                "%s",         MBIM_SMS_CAPS,        1, "SMS Capabilities"],
    ["ControlCaps",        24,4, 0xFFFFFFFF,  "ControlCaps",            "%s",         MBIM_CTRL_CAPS,       1, "Control Capabilities"],
    ["MaxSession",         28,4, 0xFFFFFFFF,  "MaxSession",             "%d",         null,                 0, "Maximum number of activated IP data stream session that are supported by the function"],
    ["CusDataOffset",      32,4, 0xFFFFFFFF,  "CustomDataClassOffset",  "0x%04x",     null,                 0, "Offset in bytes, calculated from the beginning of this structure, to a string CustomDataClass that represents the name of the custom data class"],
    ["CusDataSize",        36,4, 0xFFFFFFFF,  "CustomDataClassSize",    "%d",         null,                 0, "Size used for CustomDataClass"],
    ["DeviceIdOffset",     40,4, 0xFFFFFFFF,  "DeviceIdOffset",         "0x%04x",     null,                 0, "Offset in bytes, calculated from the beginning of this structure, to a string DeviceId that represents the function ID"],
    ["DeviceIdSize",       44,4, 0xFFFFFFFF,  "DeviceIdSize",           "%d",         null,                 0, "Size used for DeviceId"],
    ["FrmwrInfoOffset",    48,4, 0xFFFFFFFF,  "FrmwrInfoOffset",        "0x%04x",     null,                 0, "Offset in bytes, calculated from the begining of this structure, to a string FirmwareInfo that represents firmware-specific information about the function"],
    ["FrmwrInfoSize",      52,4, 0xFFFFFFFF,  "FrmwrInfoSize",          "%d",         null,                 0, "Size used for FirmwareInfo"],
    ["HwInfoOffset",       56,4, 0xFFFFFFFF,  "HwInfoOffset",           "0x%04x",     null,                 0, "Offset in bytes, calculated from the begining of this structure, to a string HardwareInfo that represents firmware-specific information about the function"],
    ["HwInfoSize",         60,4, 0xFFFFFFFF,  "HwInfoSize",             "%d",         null,                 0, "Size used for HardwareInfo"],
    ["CapsInfoBuffer",     64,0, 0,           "DataBuffer",             "",           null,                 0, ""],
    
    
    
    # MBIM_SUBSCRIBER_READY_INFO
    ["ReadyState",            0, 4, 0xFFFFFFFF,  "ReadyState",         "%s",         MBIM_SUBSCRIBER_READY_STATE,     0, "Ready State"],    
    ["SubscriberIdOffset",    4, 4, 0xFFFFFFFF,  "SubscriberIdOffset", "0x%04x",     null,                            0, "Offset in bytes, calculated from the begining of this structure, to a string SubscriberId of digits that represents the identity of subscriber"],    
    ["SubscriberIdSize",      8, 4, 0xFFFFFFFF,  "SubscriberIdSize",   "%d",         null,                            0, "Size used for SubscriberId"],
    ["SimIccIdOffset",        12,4, 0xFFFFFFFF,  "SimIccIdOffset",     "0x%04x",     null,                            0, "Offset in bytes, calculated from the begining of this structure, to a string SimIccId of digits that represents the International Circuit Card (ICC) ID of the SIM"],    
    ["SimIccIdSize",          16,4, 0xFFFFFFFF,  "SimIccIdSize",       "%d",         null,                            0, "Size used for SimIccId"],
    ["ReadyInfo",             20,4, 0xFFFFFFFF,  "ReadyInfo",          "%s",         MBIM_UNIQUE_ID_FLAGS,            0, ""],
    ["ElementCount",          24,4, 0xFFFFFFFF,  "EC",                 "%d",         null,                            0, "Count of telephone numbers following this element"],
    ["TelephoneNumbers",      28,0, 0,           "TelephoneNumbers",   "",           null,                            0, ""],    
    ["SubscriberBuffer",      0, 0, 0,           "DataBuffer",         "",           null,                            0, ""],    
    
    # MBIM_SET_RADIO_STATE
    ["RadioState",       0, 4, 0xFFFFFFFF,  "RadioState",    "%s",    MBIM_RADIO_SWITCH_STATE,    0, "Software Radio State"],    
    
    # MBIM_RADIO_STATE_INFO
    ["HwRadioState",     0, 4, 0xFFFFFFFF,  "HwRadioState",    "%s",    MBIM_RADIO_SWITCH_STATE,    0, "The state of the W_DISABLE switch"],    
    ["SwRadioState",     4, 4, 0xFFFFFFFF,  "SwRadioState",    "%s",    MBIM_RADIO_SWITCH_STATE,    0, "Software configured Radio State"],    
    
    # MBIM_SET_PIN
    ["PinType",          0, 4, 0xFFFFFFFF,  "PinType",          "%s",         MBIM_PIN_TYPE,           0, "Pin Type"],    
    ["PinOperation",     4, 4, 0xFFFFFFFF,  "PinOperation",     "%s",         MBIM_PIN_OPERATION,      0, "Pin Operation"],    
    ["PinOffset",        8, 4, 0xFFFFFFFF,  "PinOffset",        "0x%04x",     null,                    0, ""],    
    ["PinSize",          12,4, 0xFFFFFFFF,  "PinSize",          "%d",         null,                    0, "Size in bytes used for the Pin"],
    ["NewPinOffset",     16,4, 0xFFFFFFFF,  "NewPinOffset",     "0x%04x",     null,                    0, ""],    
    ["NewPinSize",       20,4, 0xFFFFFFFF,  "NewPinSize",       "%d",         null,                    0, "Size in bytes used for the NewPin"],
    ["SetPinBuffer",     24,0, 0,           "DataBuffer",       "%d",         null,                    0, ""],    
    
    # MBIM_PIN_INFO
    ["PinState",            4, 4, 0xFFFFFFFF,  "PinState",             "%s",    MBIM_PIN_STATE,        0, "Pin State"],            
    ["RemaininAttempts",    8, 4, 0xFFFFFFFF,  "RemaininAttempts",     "%d",     null,                 0, "Number of remaining attempts for any pin-related operation such as enter, enable, disable"],
    
    # MBIM_PIN_DESC
    ["PinMode",          0, 4, 0xFFFFFFFF,  "PinMode",           "%s",     MBIM_PIN_MODE,           0, "Pin Mode"],        
    ["PinFormat",        4, 4, 0xFFFFFFFF,  "PinFormat",         "%s",     MBIM_PIN_FORMAT,         0, "Pin Format"],        
    ["PinLengthMin",     8, 4, 0xFFFFFFFF,  "PinLengthMin",      "%d",     null,                    0, "The minimum number of characters in the PIN"],            
    ["PinLengthMax",     12,4, 0xFFFFFFFF,  "PinLengthMax",      "%d",     null,                    0, "The maximum number of characters in the PIN"],            

    # MBIM_PIN_LIST_INFO : uses MBIM_PIN_DESC
    
    # MBIM_PROVIDER
    ["ProvIdOffset",        0,  4,     0xFFFFFFFF,  "ProviderIdOffset",    "0x%04x",     null,                     0, ""],    
    ["ProvIdSize",          4,  4,     0xFFFFFFFF,  "ProviderIdSize",      "%d",         null,                     0, ""],
    ["ProvState",           8,  4,     0xFFFFFFFF,  "ProviderState",       "%s",         MBIM_HOME_PROVIDER_STATE, 0, "Provider State"],            
    ["ProvNameOffset",      12, 4,     0xFFFFFFFF,  "ProviderNameOffset",  "0x%04x",     null,                     0, ""],    
    ["ProvNameSize",        16, 4,     0xFFFFFFFF,  "ProviderNameSize",    "%d",         null,                     0, ""],
    ["ProvCellularClass",   20, 4,     0xFFFFFFFF,  "CellularClass",       "%s",         MBIM_CELLULAR_CLASS,      0, "Cellular class"],
    ["ProvRssi",            24, 4,     0xFFFFFFFF,  "Rssi",                "%d",         null,                     0, "Represent the strength of the wireless signal"],            
    ["ProvErrorRate",       28, 4,     0xFFFFFFFF,  "ErrorRate",           "%d",         null,                     0, "A Coded value that represents a percentage range of error rate"],            
    ["ProvBuffer",          32, 0,     0,           "DataBuffer",          "",           null,                     0, ""],            
    
    # MBIM_PROVIDERS
    ["ProvsElementCount",   0, 4, 0xFFFFFFFF,   "EC",                   "%d",       null,    0, "Number of structures that follow"],
    ["ProvsRefList",        4, 0, 0,            "ProviderRefList",      "",         null,    0, ""],    


    # MBIM_VISIBLE_PROVIDERS_REQ
    ["Action",    0, 4, 0xFFFFFFFF,    "Action",    "%s",    MBIM_VISIBLE_PROVIDERS_ACTION,    0, "Type Of Scan"],    
    
    # MBIM_SET_REGISTERATION_STATE
    ["RegisterAction",        8,  4, 0xFFFFFFFF,  "RegisterAction",    "%s",    MBIM_REGISTER_ACTION,    0, ""],            
    ["RegisterDataClass",    12, 4, 0xFFFFFFFF,   "Data Class",        "%s",    MBIM_DATA_CLASS,         1, "Data class"],
    ["RegBuffer",            16, 0, 0,            "DataBuffer",        "",      null,                    0, ""],        
    
    # MBIM_REGISTERATION_STATE_INFO
    ["NwError",                 0,  4, 0xFFFFFFFF,  "NwError",                "%s",        null,                    0, ""],            
    ["RegisterState",           4,  4, 0xFFFFFFFF,  "RegisterState",          "%s",        MBIM_REGISTER_STATE,     0, ""],            
    ["RegisterMode",            8,  4, 0xFFFFFFFF,  "RegisterMode",           "%s",        MBIM_REGISTER_MODE,      0, ""],        
    ["AvDataClasses",           12, 4, 0xFFFFFFFF,  "AvailableDataClasses",   "%s",        MBIM_DATA_CLASS,         0, ""],            
    ["RegCellularClass",        16, 4, 0xFFFFFFFF,  "CellularClass",          "%s",        MBIM_CELLULAR_CLASS,     0, "Cellular class"],
    ["RegProviderIdOffset",     20, 4, 0xFFFFFFFF,  "ProviderIdOffset",       "0x%04x",    null,                    0, ""],        
    ["RegProviderIdSize",       24, 4, 0xFFFFFFFF,  "ProviderIdSize",         "%d",        null,                    0, ""],
    ["RegProviderNameOffset",   28, 4, 0xFFFFFFFF,  "ProviderNameOffset",     "0x%04x",    null,                    0, ""],    
    ["RegProviderNameSize",     32, 4, 0xFFFFFFFF,  "ProviderNameSize",       "%d",        null,                    0, ""],
    ["RegRoamingTextOffset",    36, 4, 0xFFFFFFFF,  "RoamingTextOffset",      "0x%04x",    null,                    0, ""],    
    ["RegRoamingTextSize",      40, 4, 0xFFFFFFFF,  "RoamingTextSize",        "%d",        null,                    0, ""],
    ["RegisterationFlag",       44, 4, 0xFFFFFFFF,  "RegisterationFlag",      "%s",        MBIM_REGISTER_FLAG,      0, "Cellular class"],
    ["RegInfoBuffer",           48, 0, 0,           "DataBuffer",             "",          null,                    0, ""],
    
    # MBIM_SET_PACKET_SERVICE
    ["PktSrvcAction",            0,  4, 0xFFFFFFFF,  "PacketServiceAction",    "%s",        MBIM_PACKET_SERVICE_ACTION,    0, ""],
    
    # MBIM_SET_PACKET_SERVICE_INFO
    ["PktSrvNwError",           0,  4, 0xFFFFFFFF,  "NwError",              "%d",    null,                        0, ""],
    ["PktSrvcState",            4,  4, 0xFFFFFFFF,  "PacketServiceState",   "%s",    MBIM_PACKET_SERVICE_STATE,   0, ""],    
    ["HighestAvDataClass",      8,  4, 0xFFFFFFFF,  "HighestAvDataClass",   "%s",    MBIM_DATA_CLASS,             0, ""],            
    ["UplinkSpeed",             12, 8, 0xFFFFFFFF,  "UplinkSpeed",          "%s",    null,                        0, "Contains the uplink bit rate, in bits per second"],    
    ["DownlinkSpeed",           20, 8, 0xFFFFFFFF,  "DownlinkSpeed",        "%s",    null,                        0, "Contains the downlink bit rate, in bits per second"],    

    # MBIM_SET_SIGNAL_STATE
    ["SigStrengthInterval",     0,  4, 0xFFFFFFFF,  "SigStrengthInterval",    "%d",    null,    0, "The reporting interval, in second"],
    ["RssiThreshold",           4,  4, 0xFFFFFFFF,  "RssiThreshold",         "%d",    null,    0, "The difference in RSSI coded values that trigger report"],    
    ["ErrorRateThreshold",      8,  4, 0xFFFFFFFF,  "ErrorRateThreshold",     "%d",    null,    0, "The difference in ErrorRate coded values that trigger a report"],
    
    # MBIM_SIGNAL_STATE_INFO
    ["SigRssi",                  0,  4, 0xFFFFFFFF,  "Rssi",                  "%d",    null,    0, ""],    
    ["SigErrorRate",             4,  4, 0xFFFFFFFF,  "ErrorRate",             "%d",    null,    0, ""],    
    ["InfoSigStrengthInterval",  8,  4, 0xFFFFFFFF,  "SigStrengthInterval",   "%d",    null,    0, "The reporting interval, in second"],    
    ["InfoRssiThreshold",        12, 4, 0xFFFFFFFF,  "RssiThreshold",         "%d",    null,    0, "The difference in RSSI coded values that trigger a report"],        
    ["InfoErrorRateThreshold",   16, 4, 0xFFFFFFFF,  "ErrorRateThreshold",    "%d",    null,    0, "The difference in ErrorRate coded values that trigger a report"],
    
    # MBIM_SET_CONNECT
    ["SessionId",        0,  4, 0xFFFFFFFF,  "SessionId",        "%d",        null,                        0, "Host specifies this member to uniquely identify the session for IP data stream and its corresponding state"],    
    ["ActivationCmd",    4,  4, 0xFFFFFFFF,  "ActivationCmd",    "%s",        MBIM_ACTIVATION_COMMAND,     0, ""],        
    ["AccessStrOffset",  8,  4, 0xFFFFFFFF,  "AccessStrOffset",  "0x%04x",    null,                        0, ""],        
    ["AccessStrSize",    12, 4, 0xFFFFFFFF,  "AccessStrSize",    "%d",        null,                        0, ""],
    ["UserNameOffset",   16, 4, 0xFFFFFFFF,  "UserNameOffset",   "0x%04x",    null,                        0, ""],        
    ["UserNameSize",     20, 4, 0xFFFFFFFF,  "UserNameSize",     "%d",        null,                        0, ""],
    ["PasswordOffset",   24, 4, 0xFFFFFFFF,  "PasswordOffset",   "0x%04x",    null,                        0, ""],        
    ["PasswordSize",     28, 4, 0xFFFFFFFF,  "PasswordSize",     "%d",        null,                        0, ""],
    ["Compression",      32, 4, 0xFFFFFFFF,  "Compression",      "%s",        MBIM_COMPRESSION,            0, ""],
    ["AuthProtocol",     36, 4, 0xFFFFFFFF,  "AuthProtocol",     "%s",        MBIM_AUTH_PROTOCOL,          0, ""],
    ["IPType",           40, 4, 0xFFFFFFFF,  "IPType",           "%s",        MBIM_CONTEXT_IP_TYPE,        0, ""],    
    ["ConContextType",   44, 16,0xFFFFFFFF,  "ContextType",      "%s",        MBIM_CONTEXT_TYPE,           0, "Specifies the type of context being represented"],    
    ["ConnectBuffer",    60, 0, 0,           "DataBuffer",       "",          null,                        0, ""],
    
    # MBIM_CONNECT_INFO
    ["ActivationState",   4,   4, 0xFFFFFFFF,  "ActivationState",    "%s",        MBIM_ACTIVATION_STATE,       0, ""],
    ["VoiceCallState",    8,   4, 0xFFFFFFFF,  "VoiceCallState",     "%s",        MBIM_VOICE_CALL_STATE,       0, ""],
    ["InfoIPType",        12,  4, 0xFFFFFFFF,  "IPType",             "%s",        MBIM_CONTEXT_IP_TYPE,        0, ""],
    ["ContextType",       16, 16, 0xFFFFFFFF,  "ContextType",        "%s",        MBIM_CONTEXT_TYPE,           0, "Specifies the type of context being represented"],        
    ["ConnectNwError",    32,  4, 0xFFFFFFFF,  "NwError",            "%d",        null,                        0, ""],
    
    # MBIM_CONTEXT
    ["ContextId",              0,  4, 0xFFFFFFFF,  "ContextId",         "%d",        null,                        0, "A Unique ID for this context"],
    ["ProvContextType",        4, 16, 0xFFFFFFFF,  "ContextType",       "%s",        MBIM_CONTEXT_TYPE,           0, "Specifies the type of context being represented"],
    ["ProvAccessStrOffset",    20, 4, 0xFFFFFFFF,  "AccessStrOffset",   "0x%04x",    null,                        0, ""],        
    ["ProvAccessStrSize",      24, 4, 0xFFFFFFFF,  "AccessStrSize",     "%d",        null,                        0, ""],
    ["ProvUserNameOffset",     28, 4, 0xFFFFFFFF,  "UserNameOffset",    "0x%04x",    null,                        0, ""],        
    ["ProvUserNameSize",       32, 4, 0xFFFFFFFF,  "UserNameSize",      "%d",        null,                        0, ""],
    ["ProvPasswordOffset",     36, 4, 0xFFFFFFFF,  "PasswordOffset",    "0x%04x",    null,                        0, ""],        
    ["ProvPasswordSize",       40, 4, 0xFFFFFFFF,  "PasswordSize",      "%d",        null,                        0, ""],
    ["ProvCompression",        44, 4, 0xFFFFFFFF,  "Compression",       "%s",        MBIM_COMPRESSION,            0, ""],
    ["ProvAuthProtocol",       48, 4, 0xFFFFFFFF,  "AuthProtocol",      "%s",        MBIM_AUTH_PROTOCOL,          0, ""],
    ["ProvisionBuffer",        52, 0, 0,           "DataBuffer",        "",          null,                        0, ""],
    
    # MBIM_SET_PROVISIONED_CONTEXT
    ["ContProviderIdOffset",   52, 4, 0xFFFFFFFF,  "ProviderIdOffset",     "0x%04x",     null,    0, ""],        
    ["ContProviderIdSize",     56, 4, 0xFFFFFFFF,  "ProviderIdSize",       "%d",         null,    0, ""],
    ["ContextBuffer",          60, 0, 0,           "DataBuffer",           "",           null,    0, ""],    
    
    # MBIM_PROVISIONED_CONTEXTS_INFO
    ["ContElementCount",       0,  4,    0xFFFFFFFF,  "EC",                            "0x%04x",     null,    0, ""],        
    ["ContProvContRefList",    4,  0,    0,           "ProvisionedContextRefList",     "0x%04x",     null,    0, ""],        

    # MBIM_SET_SERVICE_ACTIVATION
    # MBIM_SERVICE_ACTIVATION_INFO
    
    # MBIM_SET_SMS_CONFIGURATION
    ["SmsFormat",              0,  4, 0xFFFFFFFF,  "Format",             "%s",        MBIM_SMS_FORMAT,    0, ""],    
    ["SmsScAddressOffset",     4,  4, 0xFFFFFFFF,  "ScAddressOffset",    "0x%04x",    null,               0, ""],        
    ["SmsScScAddressSize",     8,  4, 0xFFFFFFFF,  "ScAddressSize",      "%d",        null,               0, ""],
    ["SmsBuffer",              12, 0, 0,           "DataBuffer",         "",          null,               0, ""],    
    
    # MBIM_SMS_CONFIGURATION_INFO
    ["SmsStorageState",          0,  4, 0xFFFFFFFF,  "SmsStorageState",    "%s",        MBIM_SMS_STORAGE_STATE,  0, ""],        
    ["SmsInfoFormat",            4,  4, 0xFFFFFFFF,  "Format",             "%s",        MBIM_SMS_FORMAT,         0, ""],    
    ["MaxMessage",               8,  4, 0xFFFFFFFF,  "MaxMessage",         "%d",        null,                    0, "The maximum number of messages that can be stored on the device"],    
    ["CdmaShortMsgSize",         12, 4, 0xFFFFFFFF,  "CdmaShortMsgSize",   "%d",        null,                    0, "The maximum SMS character length that is supported by the device"],        
    ["SmsInfoScAddressOffset",   16, 4, 0xFFFFFFFF,  "ScAddressOffset",    "0x%04x",    null,                    0, ""],        
    ["SmsInfoScScAddressSize",   20, 4, 0xFFFFFFFF,  "ScAddressSize",      "%d",        null,                    0, ""],
    ["SmsInfoBuffer",            24, 0, 0,           "DataBuffer",         "",          null,                    0, ""],    
        
    # MBIM_SMS_PDU_RECORD
    ["SmsMessageIndex",  0, 4, 0xFFFFFFFF,  "MessageIndex",     "%d",        null,                        0, "An index into the virtual message store that is maintained by the device"],        
    ["MessageStatus",    4, 4, 0xFFFFFFFF,  "MessageStatus",    "%s",        MBIM_SMS_MESSAGE_STATUS,     0, ""],        
    ["PduDataOffset",    8, 4, 0xFFFFFFFF,  "DataOffset",       "0x%04x",    null,                        0, ""],        
    ["PduDataSize",     12, 4, 0xFFFFFFFF,  "DataSize",         "%d",        null,                        0, ""],
    ["PduBuffer",       16, 0, 0,           "DataBuffer",       "",          null,                        0, ""],    
    
    # MBIM_SMS_CDMA_RECORD
    ["AddrOffset",         8, 4, 0xFFFFFFFF,  "AddressOffset",      "0x%04x",     null,                        0, ""],        
    ["AddrSize",          12, 4, 0xFFFFFFFF,  "AddressSize",        "%d",         null,                        0, ""],
    ["TimeStampOffset",   16, 4, 0xFFFFFFFF,  "TimeStampOffset",    "0x%04x",     null,                        0, ""],        
    ["TimeStampSize",     20, 4, 0xFFFFFFFF,  "TimeStampSize",      "%d",         null,                        0, ""],
    ["EncodingId",        24, 4, 0xFFFFFFFF,  "EncodingId",         "%s",         MBIM_SMS_CDMA_ENCODING,      0, ""],            
    ["LanguageId",        28, 4, 0xFFFFFFFF,  "LanguageId",         "%s",         MBIM_SMS_CDMA_LANG,          0, ""],
    ["EncodMsgOffset",    32, 4, 0xFFFFFFFF,  "EncodedMsgOffset",   "0x%04x",     null,                        0, ""],        
    ["SizeInBytes",       36, 4, 0xFFFFFFFF,  "SizeInBytes",        "%d",         null,                        0, "The size, in bytes, of EncodedMessage"],    
    ["SizeInChar",        40, 4, 0xFFFFFFFF,  "SizeInChar",         "%d",         null,                        0, "Size of EncodedMessage in number of characters represented by the encoded data"],        
    ["CdmaBuffer",        44, 0, 0,           "DataBuffer",         "",           null,                        0, ""],    

    # MBIM_SMS_READ_REQ
    ["SmsFlag",           4,  4, 0xFFFFFFFF,  "Flag",             "%s",    MBIM_SMS_FLAG,    0, ""],    
    ["MessageIndex",      8,  4, 0xFFFFFFFF,  "MessageIndex",     "%d",    null,             0, "A value between 1 and MaxMessages that is an index into the device's message store"],            
    
    # MBIM_SMS_READ_INFO
    ["SmsElementCount",   4,    4, 0xFFFFFFFF,  "EC",   "%d",   null,     0, ""],
    ["SmsRefList",        8,    4, 0,           "",     "",     null,     0, ""],
        
    # MBIM_SMS_SEND_PDU
    ["SndPduDataOffset",   0,  4, 0xFFFFFFFF,  "PduDataOffset",     "0x%04x",   null,        0, ""],        
    ["SndPduDataSize",     4,  4, 0xFFFFFFFF,  "PduDataSize",       "%d",       null,        0, ""],
    ["SndPduBuffer",       8,  0, 0,           "DataBuffer",        "",         null,        0, ""],    
    
    # MBIM_SMS_SEND_CDMA
    ["SndEncodingId",        0,  4, 0xFFFFFFFF,  "EncodingId",         "%s",        MBIM_SMS_CDMA_ENCODING,    0, ""],            
    ["SndLanguageId",        4,  4, 0xFFFFFFFF,  "LanguageId",         "%s",        MBIM_SMS_CDMA_LANG,        0, ""],
    ["sndEncodMsgOffset",    16, 4, 0xFFFFFFFF,  "EncodedMsgOffset",   "0x%04x",    null,                      0, ""],        
    ["SndSizeInBytes",       20, 4, 0xFFFFFFFF,  "SizeInBytes",        "%d",        null,                      0, "The size, in bytes, of EncodedMessage"],    
    ["SndSizeInChar",        24, 4, 0xFFFFFFFF,  "SizeInChar",         "%d",        null,                      0, "Size of EncodedMessage in number of characters represented by the encoded data"],        
    ["SndBuffer",            28, 0, 0,           "DataBuffer",         "",          null,                      0, ""],    
    
    # MBIM_SET_SMS_SEND
    
    # MBIM_SMS_SEND_INFO
    ["MessageReference",     0,    4, 0xFFFFFFFF,  "MessageReference",       "%d",     null,     0, "A reference number that is returned upon successful delivery of the SMS text message"],
    
    # MBIM_SET_SMS_DELETE : Same as MBIM_SMS_READ_REQ
    
    # MBIM_SMS_STATUS_INFO
    ["StatusFlag",        0,     4, 0xFFFFFFFF,  "Flag",         "%s",    MBIM_SMS_STATUS_FLAGS,    0, ""],    
    ["StatusMsgIndex",    4,     4, 0xFFFFFFFF,  "MessageIndex", "%d",    null,                     0, "An index into the virtual message store that is maintained by the device"],
    
    # MBIM_IPV4_ELEMENT
    ["OnLinkPrefixLen",        0,     4, 0xFFFFFFFF,  "OnLinkPrefixLen",     "%d",    null,    0, "The length, in bits, of the prefix or network part of the IP address"],    
    ["IPv4Address",            4,     4, 0xFFFFFFFF,  "IPv4Address",         "%d",    null,    0, "Unicast IPv4 Address"],    
    
    # MBIM_IPV6_ELEMENT
    ["IPv6Address",        4,     16, 0xFFFFFFFF,  "IPv4Address", "%s",    null,    0, "Unicast IPv6 Address"],    
    
    # MBIM_IP_CONFIGURATION_INFO
    ["IpSessionId",                0, 4, 0xFFFFFFFF,  "SessionId",              "%d",        null,    0, ""],
    ["IPv4ConfigAvailable",        4, 4, 0xFFFFFFFF,  "IPv4ConfigAvailable",    "%d",        null,    0, "Bit 0 : IPv4 Address info available \nBit 1: IPv4 gateway info available \nBit 2 : IPv4 DNS server info available \nBit 3 : IPv4 MTU info available"],
    ["IPv6ConfigAvailable",        8, 4, 0xFFFFFFFF,  "IPv6ConfigAvailable",    "%d",        null,    0, "Bit 0 : IPv6 Address info available \nBit 1: IPv6 gateway info available \nBit 2 : IPv6 DNS server info available \nBit 3 : IPv6 MTU info available"],
    ["IPv4AddrCount",             12, 4, 0xFFFFFFFF,  "IPv4AddrCount",          "%d",        null,    0, "Count of IPv4 Element supplied"],
    ["IPv4AddrOffset",            16, 4, 0xFFFFFFFF,  "IPv4AddrOffset",         "0x%04x",    null,    0, ""],
    ["IPv6AddrCount",             20, 4, 0xFFFFFFFF,  "IPv6AddrCount",          "%d",        null,    0, "Count of IPv6 Elements supplied"],
    ["IPv6AddrOffset",            24, 4, 0xFFFFFFFF,  "IPv6AddrOffset",         "0x%04x",    null,    0, ""],
    ["IPv4GatewayOffset",         28, 4, 0xFFFFFFFF,  "IPv4GatewayOffset",      "0x%04x",    null,    0, ""],
    ["IPv6GatewayOffset",         32, 4, 0xFFFFFFFF,  "IPv6GatewayOffset",      "0x%04x",    null,    0, ""],
    ["IPv4DnsSrvCount",           36, 4, 0xFFFFFFFF,  "IPv4DnsSrvCount",        "%d",        null,    0, "Count of address supplied"],
    ["IPv4DnsSrvOffset",          40, 4, 0xFFFFFFFF,  "IPv4DnsSrvOffset",       "0x%04x",    null,    0, ""],
    ["IPv6DnsSrvCount",           44, 4, 0xFFFFFFFF,  "IPv6DnsSrvCount",        "%d",        null,    0, "Count of address supplied"],
    ["IPv6DnsSrvOffset",          48, 4, 0xFFFFFFFF,  "IPv6DnsSrvOffset",       "0x%04x",    null,    0, ""],
    ["IPv4Mtu",                   52, 4, 0xFFFFFFFF,  "IPv4Mtu",                "%d",        null,    0, "MTU for IPv4"],
    ["IPv6Mtu",                   56, 4, 0xFFFFFFFF,  "IPv6Mtu",                "%d",        null,    0, "MTU for IPv6"],
    ["IPBuffer",                  60, 0, 0,           "DataBuffer",             "",          null,    0, ""],
    
    # MBIM_SET_USSD
    ["USSDAction",           0,  4, 0xFFFFFFFF,  "USSDAction",           "%s",        MBIM_USSD_ACTION,    0, ""],    
    ["USSDDataCodingSch",    4,  4, 0xFFFFFFFF,  "USSDDataCodingScheme", "%d",        null,                0, "Value of the Data Coding Scheme as defined in 3GPP 23.038[3GPP23038]"],        
    ["USSDPayloadOffset",    8,  4, 0xFFFFFFFF,  "USSDPayloadOffset",    "0x%04x",    null,                0, ""],        
    ["USSDPayloadLen",       12, 4, 0xFFFFFFFF,  "USSDPayloadLen",       "%d",        null,                0, ""],            
    ["USSDBuffer",           16, 0, 0,           "DataBuffer",           "",          null,                0, ""],    
        
    # MBIM_USSD_INFO
    ["USSDResponse",            0,  4, 0xFFFFFFFF,  "USSDResponse",           "%s",        MBIM_USSD_RESPONSE,      0, ""],    
    ["USSDSessionState",        4,  4, 0xFFFFFFFF,  "USSDSessionState",       "%s",        MBIM_USSD_SESSION_STATE, 0, ""],        
    ["InfoUSSDDataCodingSch",   8,  4, 0xFFFFFFFF,  "USSDDataCodingScheme",   "%d",        null,                    0, "Value of the Data Coding Scheme as defined in 3GPP 23.038[3GPP23038]"],        
    ["InfoUSSDPayloadOffset",   12, 4, 0xFFFFFFFF,  "USSDPayloadOffset",      "0x%04x",    null,                    0, ""],        
    ["InfoUSSDPayloadLen",      16, 4, 0xFFFFFFFF,  "USSDPayloadLen",         "%d",        null,                    0, ""],            
    ["InfoUSSDBuffer",          20, 0, 0,           "DataBuffer",             "",          null,                    0, ""],    
    
    # MBIM_PHONEBOOK_CONFIGURATION_INFO
    ["PhonebookState",        4, 4, 0xFFFFFFFF,  "PhonebookState",       "%s",    MBIM_PHONEBOOK_STATE,    0, ""],
    ["TotalNbrOfEntries",     8, 4, 0xFFFFFFFF,  "TotalNbrOfEntries",    "%d",    null,                    0, "Total number of entries in the phonebook"],
    ["UsedEntries",          12, 4, 0xFFFFFFFF,  "UsedEntries",          "%d",    null,                    0, "Number of phonebook entries that are currently used"],
    ["MaxNumberLen",         16, 4, 0xFFFFFFFF,  "MaxNumberLen",         "%d",    null,                    0, "Maximum number of bytes for the phone number of a phonebook entry"],
    ["MaxNameLen",           20, 4, 0xFFFFFFFF,  "MaxNameLen",           "%d",    null,                    0, "Maximum number of bytes for the name of a phonebook entry"],    
    
    # MBIM_PHONEBOOK_ENTRY
    ["EntryIndex",      0, 4, 0xFFFFFFFF,  "EntryIndex",    "%d",        null,    0, "Index for the phonebook entry"],
    ["NumberOffset",    4, 4, 0xFFFFFFFF,  "NumberOffset",  "0x%04x",    null,    0, ""],    
    ["NumberLength",    8, 4, 0xFFFFFFFF,  "NumberLength",  "%d",        null,    0, ""],    
    ["NameOffset",     12, 4, 0xFFFFFFFF,  "NameOffset",    "0x%04x",    null,    0, ""],    
    ["NameLength",     16, 4, 0xFFFFFFFF,  "NameLength",    "%d",        null,    0, ""],    
    ["EnryBuffer",     20, 0, 0,           "DataBuffer",    "",          null,    0, ""],    
    
    # MBIM_PHONEBOOK_READ_REQ
    ["FilterFlag",        0, 4, 0xFFFFFFFF,  "FilterFlag",        "%d",    MBIM_PHONEBOOK_FLAG,     0, ""],
    ["FilterMsgIndex",    4, 4, 0xFFFFFFFF,  "FilterMsgIndex",    "%d",    null,                    0, "A value between 1 and TotalNbrOfEntries that is an index into the device's phonebook store"],    
    
    # MBIM_PHONEBOOK_READ_INFO
    ["EntryElementCnt",     0, 4, 0xFFFFFFFF,      "EC",                  "%d",    null,    0, "Number of phonebook entries"],
    ["PhoneBookRefList",    4, 0, 0,               "PhoneBookRefList",    "%s",    null,    0, ""],    
    
    # MBIM_SET_PHONEBOOK_DELETE : same as MBIM_PHONEBOOK_READ_REQ
    
    # MBIM_SET_PHONEBOOK_WRITE
    ["SaveFlag",             0,  4, 0xFFFFFFFF,  "SaveFlag",       "%s",        MBIM_PHONEBOOK_WRITE_FLAG,   0, ""],        
    ["SaveIndex",            4,  4, 0xFFFFFFFF,  "SaveIndex",      "%d",        null,                        0, "A value between 1 and TotalNbrOfEntries that is an index into the device's phonebook store"],            
    ["WriteNumberOffset",    8,  4, 0xFFFFFFFF,  "NumberOffset",   "0x%04x",    null,                        0, ""],
    ["WriteNumberLength",    12, 4, 0xFFFFFFFF,  "NumberLength",   "%d",        null,                        0, ""],    
    ["WriteNameOffset",      16, 4, 0xFFFFFFFF,  "NameOffset",     "0x%04x",    null,                        0, ""],    
    ["WriteNameLength",      20, 4, 0xFFFFFFFF,  "NameLength",     "%d",        null,                        0, ""],    
    ["WriteBuffer",          24, 0, 0,           "DataBuffer",     "",          null,                        0, ""],    
    
    # MBIM_SET_STK_PAC
    ["PacHostControl",    0, 32, 0xFFFFFFFF,  "PacHostControl",    "%s",    null,     0, ""],    
    
    # MBIM_STK_PAC_INFO
    ["PacSupport",    0, 256, 0,  "PacSupport", "%s",    null,     0, "256 bytes where each byte identifies the current support for a specific proactive command"],
    
    # MBIM_STK_PAC
    ["PacType",      0, 4, 0xFFFFFFFF,     "PacType",        "%s",        MBIM_STK_PAC_TYPE,    0, ""],
    ["PacBuffer",    4, 0, 0,              "DataBuffer",     "",          null,                 0, ""],        
    
    # MBIM_SET_STK_TERMINAL_RESPONSE
    ["ResponseLength",    0, 4, 0xFFFFFFFF,     "ResponseLength",    "%d",    null,    0, ""],
    ["StkBuffer",         4, 0, 0,              "DataBuffer",         "",     null,    0, ""],        
    
    # MBIM_STK_TERMINAL_RESPONSE_INFO
    ["ResultDataStrOffset",    0, 4, 0xFFFFFFFF,  "ResultDataStrOffset",    "0x%04x",    null,    0, ""],
    ["ResultLength",           4, 4, 0xFFFFFFFF,  "ResultLength",           "%d",        null,    0, ""],    
    ["StatusWords",            8, 4, 0xFFFFFFFF,  "StatusWords",            "%d",        null,    0, "Status words SW1 and SW2 in the APDU response structure. Coded as 0xAABB if SW1 = AA and SW2 = BB"],        
    ["TerminalBuffer",        12, 0, 0xFFFFFFFF,  "DataBuffer",             "",          null,    0, ""],            
    
    # MBIM_SET_STK_ENVELOPE
    ["EnvelopeBuffer",        0,0, 0xFFFFFFFF,  "DataBuffer",     "",         null,    0, ""],            
    
    # MBIM_STK_ENVELOPE_INFO
    ["EnvelopeSupport",        0, 32, 0,  "EnvelopeSupport", "%s",    null,     0, "32 bytes where each byte indicates if a specific envelope command is expected to be sent by the host"],

    # MBIM_DEVICE_SERVICE_ELEMENT
    ["DeviceServiceId",        0, 16,   0,          "DeviceServiceId",    "%s",    null,    0, "A 16 byte UUID that identifies the device service"],
    ["DssPayload",            16, 4,    0xFFFFFFFF, "DssPayload",         "%d",    null,    0, ""],    
    ["MaxDssInstances",       20, 4,    0xFFFFFFFF, "MaxDssInstances",    "%d",    null,    0, "Max amount of instances of this service, which device can handle"],    
    ["CidCount",              24, 4,    0xFFFFFFFF, "CidCount",           "%d",    null,    0, "Number of CIDs supported for this device service"],
    ["ServiceBuffer",         28, 0,    0,          "DataBuffer",         "",      null,    0, ""],                
    
    # MBIM_DEVICE_SERVICE_INFO
    ["DeviceServiceCount",    0, 4,     0xFFFFFFFF, "DSC",                "%d",    null,    0, "Number of MBIM_DEVICE_SERVICE_ELEMENT structure that follow in the DataBuffer"],    
    ["MaxDssSession",         4, 4,     0xFFFFFFFF, "MaxDssSession",      "%d",    null,    0, "The maximum number of activated Device Service Stream sessions that are supported by the function"],
    ["DeviceSrvRefList",      8, 0,     0,          "DeviceSrvRefList",   "%s",    null,    0, ""],    
    
    # MBIM_EVENT_ENTRY
    ["EventCidCount",        16, 4,   0xFFFFFFFF, "CidCount",        "%d",   null,    0, "The number of CID values that follow"],
    ["EventBuffer",          20, 0,   0,          "DataBuffer",      "",     null,    0, ""],                
    
    # MBIM_DEVICE_SERVICE_SUBSCRIBE_LIST
    ["DevSrvElementCount",        0, 4,     0xFFFFFFFF, "EC",                "%d",    null,    0, "Number of structure that follow in DataBuffer"],
    ["DevSrvSubscriberRefList",   4, 0,     0,          "PhoneBookRefList",  "%s",    null,    0, ""],            
    
    # MBIM_AKA_AUTH_REQ
    ["Rand",    0,   16,    0, "Rand",    "%s",    null,    0, "Random number challenge of 128 bit"],
    ["Autn",    16,  16,    0, "Autn",    "%s",    null,    0, "AUTN is an authentication value generated by the AuC, which, together with Rand, authenticates the server to the peer"],
    
    # MBIM_AKA_AUTH_INFO
    ["Res",        0, 16,    0, "Res",       "%s",    null,    0, "Authentication result from peer, which, together with Rand, authenticates the peer to the server, 128 bits"],
    ["ResLen",    16, 4,     0, "ResLen",    "%d",    null,    0, "Response Length"],    
    ["IK",        20, 16,    0, "IK",        "%s",    null,    0, "Integrating Key"],    
    ["CK",        36, 16,    0, "CK",        "%s",    null,    0, "Ciphering Key"],    
    ["Auts",      52, 14,    0, "Auts",      "%s",    null,    0, "A value generated by the peer upon experiencing a synchronization failure, 112 bits"],    

    # MBIM_AKAP_AUTH_REQ 
    ["NetworkNameOffset",     32, 4, 0xFFFFFFFF,  "NetworkNameOffset",    "0x%04x",    null,    0, ""],
    ["NetworkNameLen",        36, 4, 0xFFFFFFFF,  "NetworkNameLen",       "%d",        null,    0, ""],
    ["AUTHBuffer",            40, 0, 0,           "DataBuffer",           "",          null,    0, ""],
    
    # MBIM_AKAP_AUTH_INFO : same as MBIM_AKA_AUTH_INFO
    
    # MBIM_SIM_AUTH_REQ
    ["Rand1",        0,     16,    0,             "Rand1",        "%s",    null,    0, "Random number challenge of 128 bit"], 
    ["Rand2",        16,    16,    0,             "Rand2",        "%s",    null,    0, "Random number challenge of 128 bit"],    
    ["Rand3",        32,    16,    0,             "Rand3",        "%s",    null,    0, "Random number challenge of 128 bit"],        
    ["n",            48,    4,     0xFFFFFFFF,    "n",            "%d",    null,    0, "Number of random number challenge.'n' can be 2 or 3 per RFC 4186"],
    
    # MBIM_SIM_AUTH_INFO
    ["Sres1",    0,  4,    0xFFFFFFFF,  "Sres1",    "%d",    null,    0, "Response1 of 32 bit"],
    ["Kc1",      4,  8,    0,           "Kc1",      "%s",    null,    0, "Encryption key1 of 64 bit"],
    ["Sres2",    12, 4,    0xFFFFFFFF,  "Sres2",    "%d",    null,    0, "Response2 of 32 bit"],
    ["Kc2",      16, 8,    0,           "Kc2",      "%s",    null,    0, "Encryption key2 of 64 bit"],
    ["Sres3",    24, 4,    0xFFFFFFFF,  "Sres3",    "%d",    null,    0, "Response3 of 32 bit"],
    ["Kc3",      28, 8,    0,           "Kc3",      "%s",    null,    0, "Encryption key3 of 64 bit"],
    ["Infon",    36, 4,    0xFFFFFFFF,  "n",        "%d",    null,    0, "Number of random number challenge.'n' can be 2 or 3 per RFC 4186"],    
    
    # MBIM_PACKET_STATISTICS_INFO
    ["InDiscards",    0, 4,    0xFFFFFFFF,    "InDiscards",   "%d",    null,    0, ""],
    ["InErrors",      4, 4,    0xFFFFFFFF,    "InErrors",     "%d",    null,    0, "The number of inbound IP packets that have not been sent to the host because of errors"],
    ["InOctets",      8, 8,    0,             "InOctets",     "%s",    null,    0, "The total number of raw IP bytes successfully sent to the host"],    
    ["InPackets",    16, 8,    0,             "InPackets",    "%s",    null,    0, "The number of IP packets successfully sent to the host"],        
    ["OutOctets",    24, 8,    0,             "OutOctets",    "%s",    null,    0, "The total number of raw IP bytes successfully transmitted out of the function"],    
    ["OutPackets",   32, 8,    0,             "OutPackets",   "%s",    null,    0, "The total number of raw IP packets successfully received by the function from the host"],        
    ["OutErrors",    40, 4,    0xFFFFFFFF,    "OutErrors",    "%d",    null,    0, "The number of outbound IP packets received by the function from the host that could not be delivered out of the function because of errors"],
    ["OutDiscards",  44, 4,    0xFFFFFFFF,    "OutDiscards",  "%d",    null,    0, ""],    

    # MBIM_NETWORK_IDLE_HINT
    ["NetIdleHintState",    0,     4,    0xFFFFFFFF, "NetIdleHintState",    "%s",    MBIM_NETWORK_IDLE_HINT_STATES,    0, ""],
    
    # MBIM_EMERGENCY_MODE_INFO
    ["EmergencyMode",    0,     4,    0xFFFFFFFF, "EmergencyMode",    "%s",    MBIM_EMERGENCY_MODE_STATES,    0, ""],    
    
    # MBIM_SINGLE_PACKET_FILTER
    ["FilterSize",          0,   4,    0xFFFFFFFF, "FilterSize",       "%d",        null,    0, "Size in byte of the PacketFilter field as well as the PacketMask field at the end of this structure"],    
    ["PktFilterOffset",     4,   4,    0xFFFFFFFF, "PktFilterOffset",  "0x%04x",    null,    0, "Offset in bytes, calculated from the beginning of this structure, to a PacketFilter of size FilterSize"],
    ["PktMaskOffset",       8,   4,    0xFFFFFFFF, "PktMaskOffset",    "0x%04x",    null,    0, "Offset in bytes, calculated from the beginning of this structure, to a PacketMask of size FilterSize"],    
    ["PktBuffer",           12,  0,    0,          "DataBuffer",       "",          null,    0, ""],    
    
    # MBIM_PACKET_FILTERS
    ["PktFilterCount",      4,     4,    0xFFFFFFFF, "PFC",                "%d",    null,     0, "Number of Table MBIM_SINGLE_PACKET_FILTER structure that follow in the DataBuffer"],
    ["PktFilterRefList",    8,     4,    0xFFFFFFFF, "PktFilterRefList",    "%d",    null,    0, ""],    
    
    # MBIM_SET_DSS_CONNECT
    ["DssSessionId",    16,     4,    0xFFFFFFFF, "DssSessionId",    "%d",    null,                   0, "Host specifies this member to uniquely identify the session for the Device Service Stream"],
    ["DssLinkState",    20,     4,    0xFFFFFFFF, "DssLinkState",    "%s",    MBIM_DSS_LINK_STATE,    0, ""]
    
] );

####################################################################################################
#                                        CID Fields Functions                                          #
####################################################################################################

Unknown_Set_Com() {}
Unknown_Query_Com() {}
Unknown_Response() {}
Unknown_Notification_Res() {}

MBIM_CID_DEVICE_CAPS_Response(offset)
{        
    # MBIM_DEVICE_CAPS_INFO
    AddMBIMCIDField("DeviceType", offset);    
    AddMBIMCIDField("CellularClass", offset);    
    AddMBIMCIDField("VoiceClass", offset);
    AddMBIMCIDField("SimClass", offset);
    AddMBIMCIDField("DataClass", offset);
    AddMBIMCIDField("SmsCaps", offset);
    AddMBIMCIDField("ControlCaps", offset);
    AddMBIMCIDField("MaxSession", offset);
    AddMBIMCIDField("CusDataOffset", offset);
    AddMBIMCIDField("CusDataSize", offset);
    AddMBIMCIDField("DeviceIdOffset", offset);
    AddMBIMCIDField("DeviceIdSize", offset);
    AddMBIMCIDField("FrmwrInfoOffset", offset);
    AddMBIMCIDField("FrmwrInfoSize", offset);
    AddMBIMCIDField("HwInfoOffset", offset);
    AddMBIMCIDField("HwInfoSize", offset);
    AddMBIMDataPayloadFieldForRemain("CapsInfoBuffer", offset, MBIM_CID_Fields);
}

MBIM_CID_SUBSCRIBER_READY_STATUS_Response(offset)
{
    # MBIM_SUBSCRIBER_READY_INFO
    AddMBIMCIDField("ReadyState", offset);
    AddMBIMCIDField("SubscriberIdOffset", offset);
    AddMBIMCIDField("SubscriberIdSize", offset);
    AddMBIMCIDField("SimIccIdOffset", offset);
    AddMBIMCIDField("SimIccIdSize", offset);
    AddMBIMCIDField("ReadyInfo", offset);

    _row = AddMBIMCIDField("ElementCount", offset);
    count = _row[1];

    curr_offset = offset + GetFieldOffset("TelephoneNumbers", MBIM_CID_Fields);    
    data_buffer_offset = offset + count * 8;

    for(index = 0; index < count; index++)
    {
        AddSeparator();
        AddCaptionCell( Format("TN %d", index + 1), "", "", _MONOCOLOR, _MONOFIELD );
    
        offset_value = GetDataLong(curr_offset);
        curr_offset += 4;
        AddPayLoadCell("Offset", Format("%d", offset_value), "");
        
        length_value = GetDataLong(curr_offset);
        curr_offset += 4;    
        AddPayLoadCell("Length", Format("%d", length_value), "");
        
        offset_value += offset;

        value = GetNBits(in.Data, offset_value*8, length_value * 8);
        curr_string = GetArrayHexString(value);

        AddPayLoadCell("String", curr_string, "");        
    }    
}
MBIM_CID_SUBSCRIBER_READY_STATUS_Notification_Res(offset)
{
    # MBIM_SUBSCRIBER_READY_INFO
    MBIM_CID_SUBSCRIBER_READY_STATUS_Query_Res(offset);
}


MBIM_CID_RADIO_STATE_Set_Com(offset)
{
    # MBIM_SET_RADIO_STATE
    AddMBIMCIDField("RadioState", offset);
}
MBIM_CID_RADIO_STATE_Response(offset) 
{
    # MBIM_RADIO_STATE_INFO
    AddMBIMCIDField("HwRadioState", offset);
    AddMBIMCIDField("SwRadioState", offset);
}
MBIM_CID_RADIO_STATE_Notification_Res(offset) 
{
    # MBIM_RADIO_STATE_INFO
    MBIM_CID_RADIO_STATE_Response(offset);
}


MBIM_CID_PIN_Set_Com(offset)
{
    # MBIM_SET_PIN
    AddMBIMCIDField("PinType", offset);
    AddMBIMCIDField("PinOperation", offset);
    AddMBIMCIDField("PinOffset", offset);
    AddMBIMCIDField("PinSize", offset);
    AddMBIMCIDField("NewPinOffset", offset);
    AddMBIMCIDField("NewPinSize", offset);
    AddMBIMDataPayloadFieldForRemain("SetPinBuffer", offset, MBIM_CID_Fields);
}
MBIM_CID_PIN_Response(offset) 
{
    # MBIM_PIN_INFO
    AddMBIMCIDField("PinType", offset);    
    AddMBIMCIDField("PinState", offset);
    AddMBIMCIDField("RemaininAttempts", offset);    
}

MBIM_CID_PIN_LIST_Response(offset) 
{
    # MBIM_PIN_LIST_INFO
    AddSeparator();
    AddCaptionCell("Pin1","","", _MONOCOLOR, _MONOFIELD);
    AddMBIMCIDField("PinMode", offset);
    AddMBIMCIDField("PinFormat", offset);
    AddMBIMCIDField("PinLengthMin", offset);
    AddMBIMCIDField("PinLengthMax", offset);        
    offset += 16;
    
    AddSeparator();
    AddCaptionCell("Pin2","","", _MONOCOLOR, _MONOFIELD);
    AddMBIMCIDField("PinMode", offset);
    AddMBIMCIDField("PinFormat", offset);
    AddMBIMCIDField("PinLengthMin", offset);
    AddMBIMCIDField("PinLengthMax", offset);    
    offset += 16;

    AddSeparator();
    AddCaptionCell("DevSimPin","","", _MONOCOLOR, _MONOFIELD);
    AddMBIMCIDField("PinMode", offset);
    AddMBIMCIDField("PinFormat", offset);
    AddMBIMCIDField("PinLengthMin", offset);
    AddMBIMCIDField("PinLengthMax", offset);    
    offset += 16;

    AddSeparator();
    AddCaptionCell("DevFrstSimPin","","", _MONOCOLOR, _MONOFIELD);
    AddMBIMCIDField("PinMode", offset);
    AddMBIMCIDField("PinFormat", offset);
    AddMBIMCIDField("PinLengthMin", offset);
    AddMBIMCIDField("PinLengthMax", offset);    
    offset += 16;

    AddSeparator();
    AddCaptionCell("NetworkPin","","", _MONOCOLOR, _MONOFIELD);
    AddMBIMCIDField("PinMode", offset);
    AddMBIMCIDField("PinFormat", offset);
    AddMBIMCIDField("PinLengthMin", offset);
    AddMBIMCIDField("PinLengthMax", offset);    
    offset += 16;
    
    AddSeparator();
    AddCaptionCell("NetworkSubsetPin","","", _MONOCOLOR, _MONOFIELD);
    AddMBIMCIDField("PinMode", offset);
    AddMBIMCIDField("PinFormat", offset);
    AddMBIMCIDField("PinLengthMin", offset);
    AddMBIMCIDField("PinLengthMax", offset);    
    offset += 16;

    AddSeparator();
    AddCaptionCell("SrvcProviderPin","","", _MONOCOLOR, _MONOFIELD);
    AddMBIMCIDField("PinMode", offset);
    AddMBIMCIDField("PinFormat", offset);
    AddMBIMCIDField("PinLengthMin", offset);
    AddMBIMCIDField("PinLengthMax", offset);    
    offset += 16;

    AddSeparator();
    AddCaptionCell("CorporatePin","","", _MONOCOLOR, _MONOFIELD);
    AddMBIMCIDField("PinMode", offset);
    AddMBIMCIDField("PinFormat", offset);
    AddMBIMCIDField("PinLengthMin", offset);
    AddMBIMCIDField("PinLengthMax", offset);    
    offset += 16;

    AddSeparator();
    AddCaptionCell("SubsidyLock","","", _MONOCOLOR, _MONOFIELD);
    AddMBIMCIDField("PinMode", offset);
    AddMBIMCIDField("PinFormat", offset);
    AddMBIMCIDField("PinLengthMin", offset);
    AddMBIMCIDField("PinLengthMax", offset);    
    offset += 16;

    AddSeparator();
    AddCaptionCell("Custom","","", _MONOCOLOR, _MONOFIELD);
    AddMBIMCIDField("PinMode", offset);
    AddMBIMCIDField("PinFormat", offset);
    AddMBIMCIDField("PinLengthMin", offset);
    AddMBIMCIDField("PinLengthMax", offset);    
    offset += 16;
    
}

MBIM_CID_HOME_PROVIDER_Set_Com(offset) 
{
    # MBIM_PROVIDER
    AddMBIMCIDField("ProvIdOffset", offset);    
    AddMBIMCIDField("ProvIdSize", offset);    
    AddMBIMCIDField("ProvState", offset);    
    AddMBIMCIDField("ProvNameOffset", offset);    
    AddMBIMCIDField("ProvNameSize", offset);    
    AddMBIMCIDField("ProvCellularClass", offset);    
    AddMBIMCIDField("ProvRssi", offset);    
    AddMBIMCIDField("ProvErrorRate", offset);    
    AddMBIMDataPayloadFieldForRemain("ProvBuffer", offset, MBIM_CID_Fields);
}
MBIM_CID_HOME_PROVIDER_Response(offset) 
{
    MBIM_CID_HOME_PROVIDER_Set_Com(offset);
}

MBIM_CID_PREFERRED_PROVIDERS_Set_Com(offset) 
{
    # MBIM_PROVIDERS
    _row = AddMBIMCIDField("ProvsElementCount", offset);
    count = _row[1];

    curr_offset = offset + GetFieldOffset("ProvsRefList", MBIM_CID_Fields);
    data_buffer_offset = offset + count * 8;

    for(index = 0; index < count; index++)
    {
        AddSeparator();
        AddCaptionCell( Format("Provider %d", index + 1), "", "", _MONOCOLOR, _MONOFIELD );
    
        offset_value = GetDataLong(curr_offset);
        curr_offset += 4;
        AddPayLoadCell("Offset", Format("%d", offset_value), "");
        
        length_value = GetDataLong(curr_offset);
        curr_offset += 4;    
        AddPayLoadCell("Length", Format("%d", length_value), "");
        
        offset_value += offset;

        # MBIM_PROVIDER
        AddMBIMCIDField("ProvIdOffset", offset_value);    
        AddMBIMCIDField("ProvIdSize", offset_value);    
        AddMBIMCIDField("ProvState", offset_value);    
        AddMBIMCIDField("ProvNameOffset", offset_value);    
        AddMBIMCIDField("ProvNameSize", offset_value);    
        AddMBIMCIDField("ProvCellularClass", offset_value);    
        AddMBIMCIDField("ProvRssi", offset_value);    
        AddMBIMCIDField("ProvErrorRate", offset_value);    
        
        curr_len = GetFieldOffset("ProvBuffer", MBIM_CID_Fields);    
        succeeded = AddMBIMDataPayloadField("ProvBuffer", offset_value, length_value - curr_len,  MBIM_CID_Fields);
        if( !succeeded )
            return 0;
        
    }
}
MBIM_CID_PREFERRED_PROVIDERS_Response(offset) 
{
    MBIM_CID_PREFERRED_PROVIDERS_Set_Com(offset);
}
MBIM_CID_PREFERRED_PROVIDERS_Notification_Res(offset) 
{
    MBIM_CID_PREFERRED_PROVIDERS_Set_Com(offset);
}

MBIM_CID_VISIBLE_PROVIDERS_Query_Com(offset) 
{
    # MBIM_VISIBLE_PROVIDERS_REQ
    AddMBIMCIDField("Action", offset);    
}
MBIM_CID_VISIBLE_PROVIDERS_Response(offset) 
{
    # MBIM_PROVIDERS
    MBIM_CID_PREFERRED_PROVIDERS_Set_Com(offset);
}

MBIM_CID_REGISTER_STATE_Set_Com(offset) 
{
    # MBIM_SET_REGISTERATION_STATE
    AddMBIMCIDField("ProvIdOffset", offset);    
    AddMBIMCIDField("ProvIdSize", offset);        
    AddMBIMCIDField("RegisterAction", offset);
    AddMBIMCIDField("RegisterDataClass", offset);
    AddMBIMDataPayloadFieldForRemain("RegBuffer", offset, MBIM_CID_Fields);
}
MBIM_CID_REGISTER_STATE_Response(offset) 
{
    # MBIM_REGISTERATION_STATE_INFO
    AddMBIMCIDField("NwError", offset);
    AddMBIMCIDField("RegisterState", offset);
    AddMBIMCIDField("RegisterMode", offset);
    AddMBIMCIDField("AvDataClasses", offset);
    AddMBIMCIDField("RegCellularClass", offset);
    AddMBIMCIDField("RegProviderIdOffset", offset);
    AddMBIMCIDField("RegProviderIdSize", offset);
    AddMBIMCIDField("RegProviderNameOffset", offset);
    AddMBIMCIDField("RegProviderNameSize", offset);
    AddMBIMCIDField("RegRoamingTextOffset", offset);
    AddMBIMCIDField("RegRoamingTextSize", offset);
    AddMBIMCIDField("RegisterationFlag", offset);
    AddMBIMDataPayloadFieldForRemain("RegInfoBuffer", offset, MBIM_CID_Fields);
}
MBIM_CID_REGISTER_STATE_Notification_Res(offset) 
{
    MBIM_CID_REGISTER_STATE_Response(offset);
}

MBIM_CID_PACKET_SERVICE_Set_Com(offset) 
{
    # MBIM_SET_PACKET_SERVICE
    AddMBIMCIDField("PktSrvcAction", offset);
}
MBIM_CID_PACKET_SERVICE_Response(offset) 
{
    # MBIM_SET_PACKET_SERVICE_INFO
    AddMBIMCIDField("PktSrvNwError", offset);
    AddMBIMCIDField("PktSrvcState", offset);
    AddMBIMCIDField("HighestAvDataClass", offset);
    AddMBIMCIDField("UplinkSpeed", offset);
    AddMBIMCIDField("DownlinkSpeed", offset);
}
MBIM_CID_PACKET_SERVICE_Notification_Res(offset) 
{
    MBIM_CID_PACKET_SERVICE_Response(offset);
}
 
MBIM_CID_SIGNAL_STATE_Set_Com(offset) 
{
    # MBIM_SET_SIGNAL_STATE
    AddMBIMCIDField("SigStrengthInterval", offset);
    AddMBIMCIDField("RssiThreshold", offset);
    AddMBIMCIDField("ErrorRateThreshold", offset);
}
MBIM_CID_SIGNAL_STATE_Response(offset) 
{
    # MBIM_SIGNAL_STATE_INFO
    AddMBIMCIDField("SigRssi", offset);
    AddMBIMCIDField("SigErrorRate", offset);
    AddMBIMCIDField("InfoSigStrengthInterval", offset);
    AddMBIMCIDField("InfoRssiThreshold", offset);
    AddMBIMCIDField("InfoErrorRateThreshold", offset);
}
MBIM_CID_SIGNAL_STATE_Notification_Res(offset) 
{
    MBIM_CID_SIGNAL_STATE_Response(offset);
}

MBIM_CID_CONNECT_Set_Com(offset) 
{
    # MBIM_SET_CONNECT
    AddMBIMCIDField("SessionId", offset);
    AddMBIMCIDField("ActivationCmd", offset);
    AddMBIMCIDField("AccessStrOffset", offset);
    AddMBIMCIDField("AccessStrSize", offset);
    AddMBIMCIDField("UserNameOffset", offset);
    AddMBIMCIDField("UserNameSize", offset);
    AddMBIMCIDField("PasswordOffset", offset);
    AddMBIMCIDField("PasswordSize", offset);
    AddMBIMCIDField("Compression", offset);
    AddMBIMCIDField("AuthProtocol", offset);
    AddMBIMCIDField("IPType", offset);
    AddMBIMCIDField("ConContextType", offset);
    AddMBIMDataPayloadFieldForRemain("ConnectBuffer", offset, MBIM_CID_Fields);
}
MBIM_CID_CONNECT_Query_Com(offset) 
{
    # MBIM_CONNECT_INFO
    AddMBIMCIDField("SessionId", offset);
    AddMBIMCIDField("ActivationState", offset);
    AddMBIMCIDField("VoiceCallState", offset);
    AddMBIMCIDField("InfoIPType", offset);
    AddMBIMCIDField("ContextType", offset);
    AddMBIMCIDField("ConnectNwError", offset);
}
MBIM_CID_CONNECT_Response(offset) 
{
    MBIM_CID_CONNECT_Query_Com(offset);
}
MBIM_CID_CONNECT_Notification_Res(offset) 
{
    MBIM_CID_CONNECT_Query_Com(offset);
}

MBIM_CID_PROVISIONED_CONTEXTS_Set_Com(offset) 
{
    # MBIM_SET_PROVISIONED_CONTEXT
    AddMBIMCIDField("ContextId", offset);
    AddMBIMCIDField("ProvContextType", offset);
    AddMBIMCIDField("ProvAccessStrOffset", offset);
    AddMBIMCIDField("ProvAccessStrSize", offset);
    AddMBIMCIDField("ProvUserNameOffset", offset);
    AddMBIMCIDField("ProvUserNameSize", offset);
    AddMBIMCIDField("ProvPasswordOffset", offset);
    AddMBIMCIDField("ProvPasswordSize", offset);
    AddMBIMCIDField("ProvCompression", offset);
    AddMBIMCIDField("ProvAuthProtocol", offset);
    AddMBIMCIDField("ContProviderIdOffset", offset);
    AddMBIMCIDField("ContProviderIdSize", offset);
    AddMBIMDataPayloadFieldForRemain("ContextBuffer", offset, MBIM_CID_Fields);    
}
MBIM_CID_PROVISIONED_CONTEXTS_Response(offset) 
{
    # MBIM_PROVISIONED_CONTEXTS_INFO    
    _row = AddMBIMCIDField("ContElementCount", offset);    
    count = _row[1];

    curr_offset = offset + GetFieldOffset("ContProvContRefList", MBIM_CID_Fields);    
    data_buffer_offset = offset + count * 8;

    for(index = 0; index < count; index++)
    {
        AddSeparator();
        AddCaptionCell( Format("ProvCntxt %d", index + 1), "", "", _MONOCOLOR, _MONOFIELD );
    
        offset_value = GetDataLong(curr_offset);
        curr_offset += 4;
        AddPayLoadCell("Offset", Format("%d", offset_value), "");
        
        length_value = GetDataLong(curr_offset);
        curr_offset += 4;    
        AddPayLoadCell("Length", Format("%d", length_value), "");
        
        offset_value += offset;
        # MBIM_CONTEXT
        AddMBIMCIDField("ContextId", offset_value);
        AddMBIMCIDField("ProvContextType", offset_value);
        AddMBIMCIDField("ProvAccessStrOffset", offset_value);
        AddMBIMCIDField("ProvAccessStrSize", offset_value);
        AddMBIMCIDField("ProvUserNameOffset", offset_value);
        AddMBIMCIDField("ProvUserNameSize", offset_value);
        AddMBIMCIDField("ProvPasswordOffset", offset_value);
        AddMBIMCIDField("ProvPasswordSize", offset_value);
        AddMBIMCIDField("ProvCompression", offset_value);
        AddMBIMCIDField("ProvAuthProtocol", offset_value);
        
        curr_len = GetFieldOffset("ProvisionBuffer", MBIM_CID_Fields);    
        succeeded = AddMBIMDataPayloadField("ProvisionBuffer", offset_value, length_value - curr_len, MBIM_CID_Fields);
        if( !succeeded )
            return 0;

    }    
}
MBIM_CID_PROVISIONED_CONTEXTS_Notification_Res(offset) 
{
    MBIM_CID_PROVISIONED_CONTEXTS_Response(offset);
}

MBIM_CID_SERVICE_ACTIVATION_Set_Com(offset) 
{
    # MBIM_SET_SERVICE_ACTIVATION
    AddDataPayloadFieldForRemain(offset);
}
MBIM_CID_SERVICE_ACTIVATION_Response(offset) 
{
    # MBIM_SERVICE_ACTIVATION_INFO
    AddMBIMCIDField("NwError", offset);
    AddDataPayloadFieldForRemain(offset + 4);    
}

MBIM_CID_SMS_CONFIGURATION_Set_Com(offset) 
{
    # MBIM_SET_SMS_CONFIGURATION
    AddMBIMCIDField("SmsFormat", offset);
    AddMBIMCIDField("SmsScAddressOffset", offset);
    AddMBIMCIDField("SmsScScAddressSize", offset);
    AddMBIMDataPayloadFieldForRemain("SmsBuffer", offset, MBIM_CID_Fields);    
}
MBIM_CID_SMS_CONFIGURATION_Response(offset) 
{
    # MBIM_SMS_CONFIGURATION_INFO
    AddMBIMCIDField("SmsStorageState", offset);
    AddMBIMCIDField("SmsInfoFormat", offset);
    AddMBIMCIDField("MaxMessage", offset);
    AddMBIMCIDField("CdmaShortMsgSize", offset);
    AddMBIMCIDField("SmsInfoScAddressOffset", offset);
    AddMBIMCIDField("SmsInfoScScAddressSize", offset);
    AddMBIMDataPayloadFieldForRemain("SmsInfoBuffer", offset, MBIM_CID_Fields);    
}
MBIM_CID_SMS_CONFIGURATION_Notification_Res(offset) 
{
    MBIM_CID_SMS_CONFIGURATION_Response(offset);
}

MBIM_CID_SMS_READ_Query_Com(offset) 
{
    # MBIM_SMS_READ_REQ
    AddMBIMCIDField("SmsFormat", offset);    
    AddMBIMCIDField("SmsFlag", offset);    
    AddMBIMCIDField("MessageIndex", offset);    
}
MBIM_CID_SMS_READ_Response(offset) 
{
    # MBIM_SMS_READ_INFO
    _row = AddMBIMCIDField("SmsFormat", offset);    
    format = _row[1];
    
    _row = AddMBIMCIDField("SmsElementCount", offset);    
    count = _row[1];

    curr_offset = offset +  GetFieldOffset("SmsRefList", MBIM_CID_Fields);
    data_buffer_offset = offset + count * 8;

    for(index = 0; index < count; index++)
    {
        AddSeparator();
        AddCaptionCell( Format("SMS Record %d", index + 1), "", "", _MONOCOLOR, _MONOFIELD );
    
        offset_value = GetDataLong(curr_offset);
        curr_offset += 4;
        AddPayLoadCell("Offset", Format("%d", offset_value), "");
        
        length_value = GetDataLong(curr_offset);
        curr_offset += 4;    
        AddPayLoadCell("Length", Format("%d", length_value), "");
        
        offset_value += offset;
        
        # PDU Record
        if( format == 0)
        {
            # MBIM_SMS_PDU_RECORD
            AddMBIMCIDField("SmsMessageIndex", offset_value);
            AddMBIMCIDField("MessageStatus", offset_value);
            AddMBIMCIDField("PduDataOffset", offset_value);
            AddMBIMCIDField("PduDataSize", offset_value);
            
            curr_len = GetFieldOffset("PduBuffer", MBIM_CID_Fields);    
            succeeded = AddMBIMDataPayloadField("PduBuffer", offset_value, length_value - curr_len, MBIM_CID_Fields);
            if( !succeeded )
                return 0;
            
        }
        # CDMA Record        
        else
        {
            # MBIM_SMS_CDMA_RECORD
            AddMBIMCIDField("SmsMessageIndex", offset_value);
            AddMBIMCIDField("MessageStatus", offset_value);
            AddMBIMCIDField("AddrOffset", offset_value);
            AddMBIMCIDField("AddrSize", offset_value);
            AddMBIMCIDField("TimeStampOffset", offset_value);
            AddMBIMCIDField("TimeStampSize", offset_value);
            AddMBIMCIDField("EncodingId", offset_value);
            AddMBIMCIDField("LanguageId", offset_value);
            AddMBIMCIDField("EncodMsgOffset", offset_value);
            AddMBIMCIDField("SizeInBytes", offset_value);
            AddMBIMCIDField("SizeInChar", offset_value);
            
            curr_len = GetFieldOffset("CdmaBuffer", MBIM_CID_Fields);    
            succeeded = AddMBIMDataPayloadField("CdmaBuffer", offset_value, length_value - curr_len, MBIM_CID_Fields);
            if( !succeeded )
                return 0;
            
        }        
    }        
}
MBIM_CID_SMS_READ_Notification_Res(offset) 
{
    MBIM_CID_SMS_READ_Response(offset);
}

MBIM_CID_SMS_SEND_Set_Com(offset) 
{
    # MBIM_SET_SMS_SEND
    _row = AddMBIMCIDField("SmsFormat", offset);    
    format = _row[1];
    
    offset += 4;
    
    # PDU Format
    if( format == 0)
    {
        # MBIM_SMS_SEND_PDU
        AddMBIMCIDField("SndPduDataOffset", offset);
        AddMBIMCIDField("SndPduDataSize", offset);
        AddMBIMDataPayloadFieldForRemain("SndPduBuffer", offset, MBIM_CID_Fields);        
    }
    # CDMA Format
    else
    {
        # MBIM_SMS_SEND_CDMA
        AddMBIMCIDField("SndEncodingId", offset);
        AddMBIMCIDField("SndLanguageId", offset);
        AddMBIMCIDField("AddrOffset", offset);
        AddMBIMCIDField("AddrSize", offset);
        AddMBIMCIDField("sndEncodMsgOffset", offset);
        AddMBIMCIDField("SndSizeInBytes", offset);
        AddMBIMCIDField("SndSizeInChar", offset);
        AddMBIMDataPayloadFieldForRemain("SndBuffer", offset, MBIM_CID_Fields);                
    }
}
MBIM_CID_SMS_SEND_Response(offset) 
{
    # MBIM_SMS_SEND_INFO
    AddMBIMCIDField("MessageReference", offset);
}

MBIM_CID_SMS_DELETE_Set_Com(offset) 
{
    # MBIM_SET_SMS_DELETE
    AddMBIMCIDField("SmsFlag", offset);
    AddMBIMCIDField("MessageIndex", offset);
}

MBIM_CID_SMS_MESSAGE_STORE_STATUS_Response(offset) 
{
    # MBIM_SMS_STATUS_INFO
    AddMBIMCIDField("StatusFlag", offset);
    AddMBIMCIDField("StatusMsgIndex", offset);
}
MBIM_CID_SMS_MESSAGE_STORE_STATUS_Notification_Res(offset) 
{
    MBIM_CID_SMS_MESSAGE_STORE_STATUS_Response(offset);
}

MBIM_CID_IP_CONFIGURATION_Query_Com(offset) 
{
    MBIM_CID_IP_CONFIGURATION_Response(offset);    
}
MBIM_CID_IP_CONFIGURATION_Response(offset) 
{
    # MBIM_IP_CONFIGURATION_INFO
    AddMBIMCIDField("IpSessionId", offset);
    AddMBIMCIDField("IPv4ConfigAvailable", offset);
    AddMBIMCIDField("IPv6ConfigAvailable", offset);
    AddMBIMCIDField("IPv4AddrCount", offset);
    AddMBIMCIDField("IPv4AddrOffset", offset);
    AddMBIMCIDField("IPv6AddrCount", offset);
    AddMBIMCIDField("IPv6AddrOffset", offset);
    AddMBIMCIDField("IPv4GatewayOffset", offset);
    AddMBIMCIDField("IPv6GatewayOffset", offset);
    AddMBIMCIDField("IPv4DnsSrvCount", offset);
    AddMBIMCIDField("IPv4DnsSrvOffset", offset);
    AddMBIMCIDField("IPv6DnsSrvCount", offset);
    AddMBIMCIDField("IPv6DnsSrvOffset", offset);
    AddMBIMCIDField("IPv4Mtu", offset);
    AddMBIMCIDField("IPv6Mtu", offset);
    AddMBIMDataPayloadFieldForRemain("IPBuffer", offset, MBIM_CID_Fields);        
}
MBIM_CID_IP_CONFIGURATION_Notification_Res(offset) 
{
    MBIM_CID_IP_CONFIGURATION_Response(offset);
}

MBIM_CID_USSD_Set_Com(offset) 
{
    # MBIM_SET_USSD
    AddMBIMCIDField("USSDAction", offset);
    AddMBIMCIDField("USSDDataCodingSch", offset);
    AddMBIMCIDField("USSDPayloadOffset", offset);
    AddMBIMCIDField("USSDPayloadLen", offset);
    AddMBIMDataPayloadFieldForRemain("USSDBuffer", offset, MBIM_CID_Fields);        
}
MBIM_CID_USSD_Set_Res(offset) 
{
    # MBIM_USSD_INFO
    AddMBIMCIDField("USSDResponse", offset);
    AddMBIMCIDField("USSDSessionState", offset);
    AddMBIMCIDField("InfoUSSDDataCodingSch", offset);
    AddMBIMCIDField("InfoUSSDPayloadOffset", offset);
    AddMBIMCIDField("InfoUSSDPayloadLen", offset);
    AddMBIMDataPayloadFieldForRemain("InfoUSSDBuffer", offset, MBIM_CID_Fields);        
}
MBIM_CID_USSD_Notification_Res(offset) 
{
    MBIM_CID_USSD_Set_Res(offset);
}

MBIM_CID_PHONEBOOK_CONFIGURATION_Response(offset) 
{
    # MBIM_PHONEBOOK_CONFIGURATION_INFO
    AddMBIMCIDField("PhonebookState", offset);
    AddMBIMCIDField("TotalNbrOfEntries", offset);
    AddMBIMCIDField("UsedEntries", offset);
    AddMBIMCIDField("MaxNumberLen", offset);
    AddMBIMCIDField("MaxNameLen", offset);
}
MBIM_CID_PHONEBOOK_CONFIGURATION_Notification_Res(offset) 
{
    MBIM_CID_PHONEBOOK_CONFIGURATION_Response(offset);
}

MBIM_CID_PHONEBOOK_READ_Query_Com(offset) 
{
    # MBIM_PHONEBOOK_READ_REQ
    AddMBIMCIDField("FilterFlag", offset);
    AddMBIMCIDField("FilterMsgIndex", offset);    
}
MBIM_CID_PHONEBOOK_READ_Response(offset) 
{
    # MBIM_PHONEBOOK_READ_INFO
    _row = AddMBIMCIDField("EntryElementCnt", offset);    
    count = _row[1];

    curr_offset = offset + GetFieldOffset("PhoneBookRefList", MBIM_CID_Fields);
    data_buffer_offset = offset + count * 8;

    for(index = 0; index < count; index++)
    {
        AddSeparator();
        AddCaptionCell( Format("Entry %d", index + 1), "", "", _MONOCOLOR, _MONOFIELD );
    
        offset_value = GetDataLong(curr_offset);
        curr_offset += 4;
        AddPayLoadCell("Offset", Format("%d", offset_value), "");
        
        length_value = GetDataLong(curr_offset);
        curr_offset += 4;    
        AddPayLoadCell("Length", Format("%d", length_value), "");
        
        offset_value += offset;
        
        # MBIM_PHONEBOOK_ENTRY
        AddMBIMCIDField("EntryIndex", offset_value);
        AddMBIMCIDField("NumberOffset", offset_value);
        AddMBIMCIDField("NumberLength", offset_value);
        AddMBIMCIDField("NameOffset", offset_value);
        AddMBIMCIDField("NameLength", offset_value);
        
        curr_len = GetFieldOffset("EnryBuffer", MBIM_CID_Fields);    
        succeeded = AddMBIMDataPayloadField("EnryBuffer", offset_value, length_value - curr_len, MBIM_CID_Fields);
        if( !succeeded )
            return 0;        
    }
}

MBIM_CID_PHONEBOOK_DELETE_Set_Com(offset) 
{
    # MBIM_SET_PHONEBOOK_DELETE
    AddMBIMCIDField("FilterFlag", offset);
    AddMBIMCIDField("FilterMsgIndex", offset);
}

MBIM_CID_PHONEBOOK_WRITE_Set_Com(offset) 
{
    # MBIM_SET_PHONEBOOK_WRITE
    AddMBIMCIDField("SaveFlag", offset);
    AddMBIMCIDField("SaveIndex", offset);
    AddMBIMCIDField("WriteNumberOffset", offset);
    AddMBIMCIDField("WriteNumberLength", offset);
    AddMBIMCIDField("WriteNameOffset", offset);
    AddMBIMCIDField("WriteNameLength", offset);
    AddMBIMDataPayloadFieldForRemain("WriteBuffer", offset, MBIM_CID_Fields);        
}

MBIM_CID_STK_PAC_Set_Com(offset) 
{
    # MBIM_SET_STK_PAC
    AddMBIMCIDField("PacHostControl", offset);
}
MBIM_CID_STK_PAC_Response(offset) 
{
    # MBIM_STK_PAC_INFO
    AddMBIMDataPayloadField("PacSupport", offset_value, 255, MBIM_CID_Fields);
}
MBIM_CID_STK_PAC_Notification_Res(offset) 
{
    # MBIM_STK_PAC
    AddMBIMCIDField("PacType", offset);
    AddMBIMDataPayloadFieldForRemain("PacBuffer", offset, MBIM_CID_Fields);        
}

MBIM_CID_STK_TERMINAL_RESPONSE_Set_Com(offset) 
{
    # MBIM_SET_STK_TERMINAL_RESPONSE
    AddMBIMCIDField("ResponseLength", offset);
    AddMBIMDataPayloadFieldForRemain("StkBuffer", offset, MBIM_CID_Fields);        
}
MBIM_CID_STK_TERMINAL_RESPONSE_Response(offset) 
{
    # MBIM_STK_TERMINAL_RESPONse_INFO
    AddMBIMCIDField("ResultDataStrOffset", offset);
    AddMBIMCIDField("ResultLength", offset);
    AddMBIMCIDField("StatusWords", offset);
    AddMBIMDataPayloadFieldForRemain("TerminalBuffer", offset, MBIM_CID_Fields);        
}

MBIM_CID_ENVELOPE_Set_Com(offset) 
{
    # MBIM_SET_STK_ENVELOPE
    AddMBIMDataPayloadFieldForRemain("EnvelopeBuffer", offset, MBIM_CID_Fields);        
}
MBIM_CID_ENVELOPE_Response(offset) 
{
    # MBIM_STK_ENVELOPE_INFO
    AddMBIMCIDField("EnvelopeSupport", offset);
}

MBIM_CID_DEVICE_SERVICES_Response(offset) 
{
    # MBIM_DEVICE_SERVICE_INFO
    _row = AddMBIMCIDField("DeviceServiceCount", offset);
    count = _row[1];

    AddMBIMCIDField("MaxDssSession", offset);
    
    curr_offset = offset + GetFieldOffset("DeviceSrvRefList", MBIM_CID_Fields);
    data_buffer_offset = offset + count * 8;

    for(index = 0; index < count; index++)
    {
        AddSeparator();
        AddCaptionCell( Format("Entry %d", index + 1), "", "", _MONOCOLOR, _MONOFIELD );
    
        offset_value = GetDataLong(curr_offset);
        curr_offset += 4;
        AddPayLoadCell("Offset", Format("%d", offset_value), "");
        
        length_value = GetDataLong(curr_offset);
        curr_offset += 4;    
        AddPayLoadCell("Length", Format("%d", length_value), "");
        
        offset_value += offset;

        # MBIM_DEVICE_SERVICE_ELEMENT
        AddMBIMCIDField("DeviceServiceId", offset_value);
        AddMBIMCIDField("DssPayload", offset_value);
        AddMBIMCIDField("MaxDssInstances", offset_value);
        AddMBIMCIDField("CidCount", offset_value);
        
        curr_len = GetFieldOffset("ServiceBuffer", MBIM_CID_Fields);    
        succeeded = AddMBIMDataPayloadField("ServiceBuffer", offset_value, length_value - curr_len, MBIM_CID_Fields);
        if( !succeeded )
            return 0;        
        
    }
}

MBIM_CID_DEVICE_SERVICE_SUBSCRIBE_LIST_Set_Com(offset) 
{
    MBIM_CID_DEVICE_SERVICE_SUBSCRIBE_LIST_Response(offset);
}
MBIM_CID_DEVICE_SERVICE_SUBSCRIBE_LIST_Response(offset) 
{
    # MBIM_DEVICE_SERVICE_SUBSCRIBE_LIST
    _row = AddMBIMCIDField("DevSrvElementCount", offset);
    count = _row[1];
    
    curr_offset = offset + GetFieldOffset("DevSrvSubscriberRefList", MBIM_CID_Fields);
    data_buffer_offset = offset + count * 8;

    for(index = 0; index < count; index++)
    {
        AddSeparator();
        AddCaptionCell( Format("Entry %d", index + 1), "", "", _MONOCOLOR, _MONOFIELD );
    
        offset_value = GetDataLong(curr_offset);
        curr_offset += 4;
        AddPayLoadCell("Offset", Format("%d", offset_value), "");
        
        length_value = GetDataLong(curr_offset);
        curr_offset += 4;    
        AddPayLoadCell("Length", Format("%d", length_value), "");
        
        offset_value += offset;

        # MBIM_EVENT_ENTRY
        AddMBIMCIDField("DeviceServiceId", offset_value);
        AddMBIMCIDField("EventCidCount", offset_value);
        
        curr_len = GetFieldOffset("EventBuffer", MBIM_CID_Fields);    
        succeeded = AddMBIMDataPayloadField("EventBuffer", offset_value, length_value - curr_len, MBIM_CID_Fields);    
        if( !succeeded )
            return 0;        
        
    }    
}

MBIM_CID_PACKET_STATISTICS_Notification_Res(offset) 
{
    # MBIM_PACKET_STATISTICS_INFO
    AddMBIMCIDField("InDiscards", offset);
    AddMBIMCIDField("InErrors", offset);
    AddMBIMCIDField("InOctets", offset);
    AddMBIMCIDField("InPackets", offset);
    AddMBIMCIDField("OutOctets", offset);
    AddMBIMCIDField("OutPackets", offset);
    AddMBIMCIDField("OutErrors", offset);
    AddMBIMCIDField("OutDiscards", offset);    
}

MBIM_CID_NETWORK_IDLE_HINT_Set_Com(offset) 
{
    # MBIM_NETWORK_IDLE_HINT
    AddMBIMCIDField("NetIdleHintState", offset);
}
MBIM_CID_NETWORK_IDLE_HINT_Response(offset)
{
    MBIM_CID_NETWORK_IDLE_HINT_Set_Com(offset);
}

MBIM_CID_EMERGENCY_MODE_Response(offset) 
{
    # MBIM_EMERGENCY_MODE_INFO
    AddMBIMCIDField("EmergencyMode", offset);
}

MBIM_CID_IP_PACKET_FILTERS_Set_Com(offset) 
{
    # MBIM_PACKET_FILTERS
    AddMBIMCIDField("SessionId", offset);
    
    _row = AddMBIMCIDField("PktFilterCount", offset);    
    count = _row[1];
    
    curr_offset = offset + GetFieldOffset("PktFilterRefList", MBIM_CID_Fields);    
    data_buffer_offset = offset + count * 8;

    for(index = 0; index < count; index++)
    {
        AddSeparator();
        AddCaptionCell( Format("Filter %d", index + 1), "", "", _MONOCOLOR, _MONOFIELD );
    
        offset_value = GetDataLong(curr_offset);
        curr_offset += 4;
        AddPayLoadCell("Offset", Format("%d", offset_value), "");
        
        length_value = GetDataLong(curr_offset);
        curr_offset += 4;    
        AddPayLoadCell("Length", Format("%d", length_value), "");
        
        offset_value += offset;
            
        # MBIM_SINGLE_PACKET_FILTER
        AddMBIMCIDField("FilterSize", offset_value);
        AddMBIMCIDField("PktFilterOffset", offset_value);
        AddMBIMCIDField("PktMaskOffset", offset_value);
        
        curr_len = GetFieldOffset("PktBuffer", MBIM_CID_Fields);    
        succeeded = AddMBIMDataPayloadField("PktBuffer", offset_value, length_value - curr_len, MBIM_CID_Fields);                
        if( !succeeded )
            return 0;        
        
    }
}
MBIM_CID_IP_PACKET_FILTERS_Query_Com(offset) 
{
    MBIM_CID_IP_PACKET_FILTERS_Set_Com(offset);
}
MBIM_CID_IP_PACKET_FILTERS_Response(offset) 
{
    MBIM_CID_IP_PACKET_FILTERS_Set_Com(offset);
}

MBIM_CID_DSS_CONNECT_Set_Com(offset) 
{
    # MBIM_SET_DSS_CONNECT
    AddMBIMCIDField("DeviceServiceId", offset);
    AddMBIMCIDField("DssSessionId", offset);
    AddMBIMCIDField("DssLinkState", offset);
}

MBIM_CID_MULTICARRIER_PROVIDERS_Set_Com(offset) 
{
    # MBIM_PROVIDERS
    MBIM_CID_PREFERRED_PROVIDERS_Set_Com(offset);

}
MBIM_CID_MULTICARRIER_PROVIDERS_Response(offset) 
{
    MBIM_CID_MULTICARRIER_PROVIDERS_Set_Com(offset);
}
MBIM_CID_MULTICARRIER_PROVIDERS_Notification_Res(offset) 
{
    MBIM_CID_MULTICARRIER_PROVIDERS_Set_Com(offset);
}

MBIM_CID_AKA_AUTH_Query_Com(offset) 
{
    # MBIM_AKA_AUTH_REQ
    AddMBIMCIDField("Rand",    offset);
    AddMBIMCIDField("Autn",    offset);    
}
MBIM_CID_AKA_AUTH_Response(offset) 
{
    # MBIM_AKA_AUTH_INFO
    AddMBIMCIDField("Res", offset);    
    AddMBIMCIDField("ResLen", offset);
    AddMBIMCIDField("IK", offset);
    AddMBIMCIDField("CK", offset);
    AddMBIMCIDField("Auts", offset);
}

MBIM_CID_AKAP_AUTH_Query_Com(offset) 
{
    # MBIM_AKAP_AUTH_REQ
    AddMBIMCIDField("Rand",    offset);
    AddMBIMCIDField("Autn",    offset);    
    AddMBIMCIDField("NetworkNameOffset", offset);
    AddMBIMCIDField("NetworkNameLen", offset);
    AddMBIMDataPayloadFieldForRemain("AUTHBuffer", offset, MBIM_CID_Fields);        
}
MBIM_CID_AKAP_AUTH_Response(offset) 
{
    # MBIM_AKAP_AUTH_INFO
    AddMBIMCIDField("Res", offset);    
    AddMBIMCIDField("ResLen", offset);
    AddMBIMCIDField("IK", offset);
    AddMBIMCIDField("CK", offset);
    AddMBIMCIDField("Auts", offset);
}

MBIM_CID_SIM_AUTH_Query_Com(offset) 
{
    # MBIM_SIM_AUTH_REQ
    AddMBIMCIDField("Rand1", offset);
    AddMBIMCIDField("Rand2", offset);
    AddMBIMCIDField("Rand3", offset);
    AddMBIMCIDField("n", offset);
}
MBIM_CID_SIM_AUTH_Response(offset) 
{
    # MBIM_SIM_AUTH_INFO
    AddMBIMCIDField("Sres1", offset);
    AddMBIMCIDField("Kc1", offset);
    AddMBIMCIDField("Sres2", offset);
    AddMBIMCIDField("Kc2", offset);
    AddMBIMCIDField("Sres3", offset);
    AddMBIMCIDField("Kc3", offset);
    AddMBIMCIDField("Infon", offset);    
}

####################################################################################################
#                                            Utility functions                                       #
####################################################################################################

GetFieldOffset(FieldId, FieldsArray)
{
    _row = Find(FieldsArray, FieldId);
    
    return _row[1];
}

AddDataPayloadFieldForRemain(offset)
{
    GetNBits(in.Data, offset * 8, 0);

    len = in.DataLength - 8;
    SetFieldOffsetLen(offset * 8, len * 8);
    ShowDataBlockReOrder(len);                
}

AddMBIMDataPayloadField(FieldId, offset, len, FieldsArray)
{    
        _row = Find(FieldsArray, FieldId);
    
        offset = _row[1] + offset;
    
        if( offset + len > in.DataLength ) return 0;

        GetNBits(in.Data, offset * 8, 0);

        SetFieldOffsetLen(offset * 8, len * 8);
        ShowDataBlockReOrder(len);                
        
        return 1;
}

AddMBIMDataPayloadFieldForRemain(FieldId, offset, FieldsArray)
{
        _row = Find(FieldsArray, FieldId);
    
        offset = _row[1] + offset;
    
        len = in.DataLength - offset;
    
        if( offset + len > in.DataLength ) return 0;

        GetNBits(in.Data, offset * 8, 0);

        SetFieldOffsetLen(offset * 8, len * 8);
        ShowDataBlockReOrder(len);                
        
        return 1;
}

AddMBIMCIDField(FieldId, offset)
{
    return AddMBIMField( FieldId, offset, MBIM_CID_Fields);
}

GetMBIMCIDFieldData(FieldId, offset)
{
    return GetMBIMFieldData( FieldId, offset, MBIM_CID_Fields);
}

AddMBIMRequestField(FieldId, offset)
{
    return AddMBIMField( FieldId, offset, MBIM_Request_Fields);
}

GetMBIMRequestFieldData(FieldId, offset)
{
    return GetMBIMFieldData( FieldId, offset, MBIM_Request_Fields);
}

AddMBIMField(FieldId, offset, FieldsArray)
{    
        ReturnValues[0] = 0;
        ReturnValues[1] = 0;
        
        _row = Find(FieldsArray, FieldId);
                                                    
        offset             = _row[1] + offset;
        len             = _row[2];
        mask             = _row[3];
        name             = _row[4];
        valueformat        = _row[5];
        valuearray      = _row[6];
        isvaluebitmap     = _row[7];
        tooltip         = _row[8];        
        value             = 0;

        if( offset + len > in.DataLength ) return ReturnValues;
        
        if(len == 1)
        {
            value = GetDataByte(offset);
            value &= mask;
        }
        else if(len == 2)
        {        
            value = GetDataWord(offset);
            value &= mask;
        }
        else if(len == 3)        
        {
            value = GetDataLong(offset);
            value &= 0x00FFFFFF;
            value &= mask;
        }    
        else if(len == 4)        
        {
            value = GetDataLong(offset);
            value &= mask;
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

GetMBIMFieldData(FieldId, offset, FieldsArray)
{
        ReturnValues[0] = 0;
        ReturnValues[1] = 0;

        _row = Find(FieldsArray, FieldId);

        offset         = _row[1] + offset;
        len         = _row[2];
        mask         = _row[3];
        value         = 0;

        if( offset + len > in.DataLength ) return ReturnValues;

        if(len == 1)
        {
            value = GetDataByte(offset);
            value &= mask;            
        }
        else if(len == 2)        
        {
            value = GetDataWord(offset);
            value &= mask;
        }
        else if(len == 3)        
        {
            value = GetDataLong(offset);
            value &= 0x00FFFFFF;
            value &= mask;
        }    
        else if(len == 4)        
        {
            value = GetDataLong(offset);
            value &= mask;
        }
        else
        {
         	value = GetDataByteArray(offset, len);		    
        }

        ReturnValues[0] = 1;
        ReturnValues[1] = value;
        
        return ReturnValues;
}

#*******************************************************************************
# RESET_FUNCTION :
#                 Reset the to its initial state
# bmRequestType : 0x21
# bRequest      : 0x05
# wValue        : 0x0000
# wIndex        : Interface 
# wLength       : 0x0000
# Data          : 0x0000
#*******************************************************************************
# start RESET_FUNCTION
RESET_FUNCTION()
{
    wValue   = NextDataWord_();
    if (wValue == 0)
    {
        AddPayLoadCell("wValue", Format("0x%04X", wValue), "wValue is zero", FieldColor, [_TABULARCELL, CELL_WVALUE, "TEXT_CAPTION"]);
    }
    else
    {
        err_tooltip = "Illegal wValue value, should set to zero!";
        AddPayLoadCell("wValue", Format("0x%04X", wValue), AddErrorTooltip(), _ERROR, [_TABULARCELL, CELL_WVALUE, "TEXT_CAPTION"]);
    }
    wIndex   = NextDataWord_();
    if (bmRequestType == 0x21 )
    {
        AddPayLoadCell("wIndex", Format("Interface %d", wIndex), "Interface ID");
    }
    else if (bmRequestType == 0x22)
    {
        AddPayLoadCell("wIndex", Format("Endpoint %d", wIndex), "Endpoint ID");
    }
    else
    {
        err_tooltip = Format("Unknown bmRequestType (0x%02X)! ", bmRequestType);
        AddPayLoadCell("wIndex", Format("0x%04X", wIndex), AddErrorTooltip(), _ERROR);
    }
    wLength  = NextDataWord_();
    if (wLength == 0)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data");
        ShowDataBlock(wLength);
		out.Decoded = 8 + wLength;
		
    }
    else
    {
        err_tooltip = "Illegal wLength Value" ;
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
		out.Decoded = 8;
    }
}
#end  RESET_FUNCTION


####################################################################################
#                       USBTracer specific caption cell                            #
####################################################################################

AddSpecCaptionCell(caption, text, tooltip, FieldColor, addparam, addparam1, addparam2 )
{   
    AddCell(caption, text, tooltip, FieldColor, _USBBULK_HEADER, addparam, addparam1, addparam2 );        
    return 1;        
}

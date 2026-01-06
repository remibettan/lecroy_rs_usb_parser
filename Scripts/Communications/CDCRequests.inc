#*******************************************************************************
#  Copyright (c) 2013, LeCroy - All Rights Reserved
#
#  Communication and CDC Control request decoder
#
#*******************************************************************************



set RequestTypeTable =
[
    #------------------------------------------------------------------------------------------
    # type,     type name                                                    |
    #------------------------------------------------------------------------------------------
    [0xFF,      "RESERVED"                                        ],
    [0x00,      "SEND_ENCAPSULATED_COMMAND"                       ],
    [0x01,      "GET_ENCAPSULATED_RESPONSE"                       ],
    [0x02,      "SET_COMM_FEATURE"                                ],
    [0x03,      "GET_COMM_FEATURE"                                ],
    [0x04,      "CLEAR_COMM_FEATURE"                              ],	
    [0x10,      "SET_AUX_LINE_STATE"                              ],
    [0x11,      "SET_HOOK_STATE"                                  ],
    [0x12,      "PULSE_SETUP"                                     ],
    [0x13,      "SEND_PULSE"                                      ],
    [0x14,      "SET_PULSE_TIME"                                  ],
    [0x15,      "RING_AUX_JACK"                                   ],
    [0x20,      "SET_LINE_CODING"                                 ],
    [0x21,      "GET_LINE_CODING"                                 ],
    [0x22,      "SET_CONTROL_LINE_STATE"                          ],
    [0x23,      "SEND_BREAK"                                      ],
    [0x30,      "SET_RINGER_PARMS"                                ],
    [0x31,      "GET_RINGER_PARMS"                                ],
    [0x32,      "SET_OPERATION_PARMS"                             ],
    [0x33,      "GET_OPERATION_PARMS"                             ],
    [0x34,      "SET_LINE_PARMS"                                  ],
    [0x35,      "GET_LINE_PARMS"                                  ],
    [0x36,      "DIAL_DIGITS"                                     ],
    [0x37,      "SET_UNIT_PARAMETER"                              ],
    [0x38,      "GET_UNIT_PARAMETER"                              ],
    [0x39,      "CLEAR_UNIT_PARAMETER"                            ],
    [0x3A,      "GET_PROFILE"                                     ],
    [0x40,      "SET_ETHERNET_MULTICAST_FILTERS"                  ],
    [0x41,      "SET_ETHERNET_POWER_MANAGEMENT_PATTERN_FILTER"    ],
    [0x42,      "GET_ETHERNET_POWER_MANAGEMENT_PATTERN_FILTER"    ],
    [0x43,      "SET_ETHERNET_PACKET_FILTER"                      ],
    [0x44,      "GET_ETHERNET_STATISTIC"                          ],
    [0x50,      "SET_ATM_DATAFORMAT"                              ],
    [0x51,      "GET_ATM_DEVICE_STATISTICS"                       ],
    [0x52,      "SET_ATM_DEFAULT_VC"                              ],
    [0x53,      "GET_ATM_VC_STATISTICS"                           ]
];



set NotificationTypeTable =
[
    #------------------------------------------------------------------------------------------
    # type,     type name                                                    |
    #------------------------------------------------------------------------------------------
    [0xFF,      "RESERVED_NOTIFICATION"   ],
    [0x00,      "NETWORK_CONNECTION"      ],
    [0x01,      "RESPONSE_AVAILABLE"      ],
    [0x08,      "AUX_JACK_HOOK_STATE"     ],  
    [0x09,      "RING_DETECT"             ],
    [0x20,      "SERIAL_STATE"            ],
    [0x28,      "CALL_STATE_CHANGE"       ],
    [0x29,      "LINE_STATE_CHANGE"       ],
    [0x2A,      "CONNECTION_SPEED_CHANGE" ]
];



#*******************************************************************************
# RESERVED :
#                 This request is used for all unknown requests
# bmRequestType : Ignored
# bRequest      : Out of Range
# wValue        : Ignored
# wIndex        : Ignored
# wLength       : Ignored
# Data          : Ignored
#*******************************************************************************
RESERVED()
{
	wValue   = GetDataWord(2); 
	wIndex   = GetDataWord(4);
	wLength  = GetDataWord(6);

	val_text =  Format("0x%04X", wValue);
	val_text_Tooltip =  Format("wValue HexVal: 0x%04X", wValue);
	AddWValueCell (val_text, val_text_Tooltip);

	wIndex_text =  Format("0x%04X", wIndex);
	wIndex_text_Tooltip =  Format("wIndex HexVal: 0x%04X", wIndex);
	AddWIndexCell (wIndex_text, wIndex_text_Tooltip);

	wLength_text =  Format("wLength HexVal: 0x%04X", wLength);
	wLength_text_Tooltip =  Format("wLength HexVal: 0x%04X", wLength);
	AddWLengthCell(wLength_text, wLength_text_Tooltip);
	
	out.Decoded = 8;
}

#*******************************************************************************
# SEND_ENCAPSULATED_COMMAND :
#                 This request is used to issue a command in the form of the
#                 supported control protocol of the communication class interface
# bmRequestType : 0x21/0x22
# bRequest      : 0x00
# wValue        : 0x0000
# wIndex        : Interface / Endpoint
# wLength       : Amount of data in bytes associated with this recipient
# Data          : Control Protocol-based Command
#*******************************************************************************
# start SEND_ENCAPSULATED_COMMAND
SEND_ENCAPSULATED_COMMAND()
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
    if (wLength >= 0)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data");
    }
    else
    {
        err_tooltip = "Illegal wLength Value" ;
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
    }
	
	out.Decoded = 8;	
}

# end SEND_ENCAPSULATED_COMMAND


#*******************************************************************************
# GET_ENCAPSULATED_RESPONSE :
#                 This request is used to request a response in the form of the
#                 supported control protocol of the communication class interface
# bmRequestType : 0xA1/0xA2
# bRequest      : 0x00
# wValue        : 0x0000
# wIndex        : Interface / Endpoint
# wLength       : Amount of data in bytes associated with this recipient
# Data          : Protocol Dependent Data
#*******************************************************************************
# start GET_ENCAPSULATED_RESPONSE
GET_ENCAPSULATED_RESPONSE()
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
    if (bmRequestType == 0xA1 )
    {
        AddPayLoadCell("wIndex", Format("Interface %d", wIndex), "Interface ID");
    }
    else if (bmRequestType == 0xA2)
    {
        AddPayLoadCell("wIndex", Format("Endpoint %d", wIndex), "Endpoint ID");
    }
    else
    {
        err_tooltip = Format("Unknown bmRequestType (0x%02X)! ", bmRequestType);
        AddPayLoadCell("wIndex", Format("0x%04X", wIndex), AddErrorTooltip(), _ERROR);
    }
    wLength  = NextDataWord_();
    if (wLength >= 0)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data");
    }
    else
    {
        err_tooltip = "Illegal wLength Value" ;
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
    }
	
	out.Decoded = 8;
}

# end GET_ENCAPSULATED_RESPONSE

#*******************************************************************************
# SET_COMM_FEATURE : This request controls the settings for a particular
#                 communication feature of a particular target
# bmRequestType : 0x21/0x22
# bRequest      : 0x02
# wValue        : Feature Selector
# wIndex        : Interface / Endpoint
# wLength       : Length of State Data
# Data          : State
#*******************************************************************************
set CommFeatureSelectorTable =
[
    #------------------------------------------------------------------------------------------
    # type, Feature name,   wLength, Error cell                                               |
    #------------------------------------------------------------------------------------------
    [ 0xF,  "UNKNOWN",        0,      _ERROR],
    [ 0x0,  "Reserved",       0,      null],
    [ 0x1,  "ABSTRACT_STATE", 2,      null],
    [ 0x2,  "COUNTRY_SETTING",2,      null]
];

# start SET_COMM_FEATURE & GET_COMM_FEATURE
SET_COMM_FEATURE()
{
    wValue   = NextDataWord_();
    _row = Find(CommFeatureSelectorTable, wValue);
    AddPayLoadCell("wValue", _row[1], Format("wValue = 0x%04X", wValue), _row[3], FieldColor, [_TABULARCELL, CELL_WVALUE, "TEXT_CAPTION"]);
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
    if (wLength == _row[2])
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of the status data");
        if (wValue == 0x1 ) # ABSTRACT_STATE
        {
            PLReservedCheck (15);
            multiState = NextNBits_(1);
            if ( multiState)
                text = "Enabled";
            else
                text = "Disabled";
            AddPayLoadCell("DMS", text, "Data Multiplexed State" + text + Format(" - 0x%X", multiState));
        }
        else if (wValue == 0x2)
        {
            code = NextDataWord_();
            AddPayLoadCell("Country Code", Format("0x%04X", code), "Country code specified in ISO 3166");
        }


        out.Decoded = 8 + wLength;
    }
    else
    {
        err_tooltip = Format("Illegal wLength Value! The length for should be %d", _row[2]);
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        /*
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
        */
            out.Decoded = 8;
    }
}

GET_COMM_FEATURE()
{
    wValue   = NextDataWord_();
    _row = Find(CommFeatureSelectorTable, wValue);
    AddPayLoadCell("wValue", _row[1], Format("wValue = 0x%04X", wValue), _row[3], FieldColor, [_TABULARCELL, CELL_WVALUE, "TEXT_CAPTION"]);
    wIndex   = NextDataWord_();
    if (bmRequestType == 0xA1 )
    {
        AddPayLoadCell("wIndex", Format("Interface %d", wIndex), "Interface ID");
    }
    else if (bmRequestType == 0xA2)
    {
        AddPayLoadCell("wIndex", Format("Endpoint %d", wIndex), "Endpoint ID");
    }
    else
    {
        err_tooltip = Format("Unknown bmRequestType (0x%02X)! ", bmRequestType);
        AddPayLoadCell("wIndex", Format("0x%04X", wIndex), AddErrorTooltip(), _ERROR);
    }
    wLength  = NextDataWord_();
    if (wLength == _row[2])
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of the status data");
        if (wValue == 0x1 ) # ABSTRACT_STATE
        {
            PLReservedCheck (15);
            multiState = NextNBits_(1);
            if ( multiState)
                text = "Enabled";
            else
                text = "Disabled";
            AddPayLoadCell("DMS", text, "Data Multiplexed State" + text + Format(" - 0x%X", multiState));
        }
        else if (wValue == 0x2)
        {
            code = NextDataWord_();
            AddPayLoadCell("Country Code", Format("0x%04X", code), "Country code specified in ISO 3166");
        }


        out.Decoded = 8 + wLength;
    }
    else
    {
        err_tooltip = Format("Illegal wLength Value! The length for should be %d", _row[2]);
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        /*
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
        */
            out.Decoded = 8;
    }
}


# end SET_COMM_FEATURE & GET_COMM_FEATURE


#*******************************************************************************
# CLEAR_COMM_FEATURE : This request controls the settings for a particular
#                 communication feature of a particular target, setting the selected
#                 feature to its default state
# bmRequestType : 0x21/0x22
# bRequest      : 0x04
# wValue        : Feature Selector
# wIndex        : Interface / Endpoint
# wLength       : 0x0000
# Data          : None
#*******************************************************************************
# start CLEAR_COMM_FEATURE
CLEAR_COMM_FEATURE()
{
    wValue   = NextDataWord_();
    _row = Find(CommFeatureSelectorTable, wValue);
    AddPayLoadCell("wValue", _row[1], Format("wValue = 0x%04X", wValue), FieldColor, [_TABULARCELL, CELL_WVALUE, "TEXT_CAPTION"]);
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
        isError = null;
    }
    else
    {
        isError = _ERROR;
    }
    AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data", isError);
    out.Decoded = 8;
/*
    if (wLength == 0)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data");
        out.Decoded = 8;
    }
    else
    {
        err_tooltip = "Illegal wLength Value" ;
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);

        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else

            out.Decoded = 8;
    }
*/
}

# end CLEAR_COMM_FEATURE

#*******************************************************************************
# SET_AUX_LINE_STATE : This request is used to connect or disconnect a secondary
#                    jack to PORTS circuit or CODEC, depending on hook state
# bmRequestType : 0x21/0x22
# bRequest      : 0x10
# wValue        : Disconnect/Connect
# wIndex        : Interface / Endpoint
# wLength       : 0x0000
# Data          : None
#*******************************************************************************
# start SET_AUX_LINE_STATE
SET_AUX_LINE_STATE()
{
    wValue   = NextDataWord_();
    if (wValue == 0)
        text = "Disconnect";
    else if (wValue == 1)
        text = "Connect";
    else
        text = "UNKNOWN";
    if (wValue == 0 || wValue == 1)
        AddPayLoadCell("wValue", text, Format("wValue = 0x%04X", wValue), FieldColor, [_TABULARCELL, CELL_WVALUE, "TEXT_CAPTION"]);
    else
    {
        err_tooltip = Format("Unknown wValue (0x%04X)! ", wValue);
        AddPayLoadCell("wIndex", Format("0x%04X", wIndex), AddErrorTooltip(), _ERROR);
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
        isError = null;
    }
    else
    {
        isError = _ERROR;
    }
    AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data", isError);
    out.Decoded = 8;
/*
    if (wLength == 0)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data");
        out.Decoded = 8;
    }
    else
    {
        err_tooltip = "Illegal wLength Value" ;
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
            out.Decoded = 8;
    }
*/
}

# end SET_AUX_LINE_STATE

#*******************************************************************************
# SET_HOOK_STATE : This request is used to set the necessary POTS line relay code
#                  for on-hook, off-hook, and clear ID states
# bmRequestType : 0x21/0x22
# bRequest      : 0x11
# wValue        : Relay Config
# wIndex        : Interface / Endpoint
# wLength       : 0x0000
# Data          : None
#*******************************************************************************
# start SET_HOOK_STATE
set RelayConfigSelectorTable =
[
    #------------------------------------------------------------------------------------------
    # value, code,      Error Cell                                                            |
    #------------------------------------------------------------------------------------------
    [ 0xFF,  "UNKNOWN",   _ERROR    ],
    [ 0x00,  "ON_HOOK",   null      ],
    [ 0x1,   "OFF_HOOK",  null      ],
    [ 0x2,   "SNOOPING",  null      ]
];

SET_HOOK_STATE()
{
    wValue   = NextDataWord_();
    _row = Find(RelayConfigSelectorTable, wValue);
    VS = "wValue";
    AddBlockPLCell("Relay Config", _row[1], Format("wValue = 0x%04X", wValue), _row[2]);

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
        isError = null;
    }
    else
    {
        isError = _ERROR;
    }
    AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data", isError);
    out.Decoded = 8;
/*
    if (wLength == 0)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data");
        out.Decoded = 8;
    }
    else
    {
        err_tooltip = "Illegal wLength Value" ;
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
            out.Decoded = 8;
    }
*/
}
# end SET_HOOK_STATE

#*******************************************************************************
# PULSE_SETUP   : This request is used to prepare for a pulse-dialing
# bmRequestType : 0x21/0x22
# bRequest      : 0x12
# wValue        : Enable/Disable
# wIndex        : Interface / Endpoint
# wLength       : 0x0000
# Data          : None
#*******************************************************************************
# start PULSE_SETUP
set PulseSetupSelectorTable =
[
    #------------------------------------------------------------------------------------------
    # value, code,                                                                            |
    #------------------------------------------------------------------------------------------
    [ 0x00,  "Enable" ],
    [ 0xFF,  "Disable"]
];
PULSE_SETUP()
{
    wValue   = NextDataWord_();
    _row = Find(PulseSetupSelectorTable, wValue);
    AddPayLoadCell("wValue", _row[1], Format("wValue = 0x%04X", wValue), FieldColor, [_TABULARCELL, CELL_WVALUE, "TEXT_CAPTION"]);

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
        isError = null;
    }
    else
    {
        isError = _ERROR;
    }
    AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data", isError);
    out.Decoded = 8;
/*
    if (wLength == 0)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data");
        out.Decoded = 8;
    }
    else
    {
        err_tooltip = "Illegal wLength Value" ;
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
            out.Decoded = 8;
    }
*/
}
# end PULSE_SETUP

#*******************************************************************************
# SEND_PULSE    : This request is used to generate a specified number of make/break
#                 pulses
# bmRequestType : 0x21/0x22
# bRequest      : 0x13
# wValue        : Cycles
# wIndex        : Interface / Endpoint
# wLength       : 0x0000
# Data          : None
#*******************************************************************************
# start SEND_PULSE
SEND_PULSE()
{
    wValue   = NextDataWord_();
    VS = "wValue";
    AddBlockPLCell("Cycles", Format("0x%04X", wValue), Format("%d cycles", wValue));

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
        isError = null;
    }
    else
    {
        isError = _ERROR;
    }
    AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data", isError);
    out.Decoded = 8;
/*
    if (wLength == 0)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data");
        out.Decoded = 8;
    }
    else
    {
        err_tooltip = "Illegal wLength Value" ;
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
            out.Decoded = 8;
    }
*/
}
# end SEND_PULSE

#*******************************************************************************
# SET_PULSE_TIME : This request sets the timing of make/break periods for pulse
#                  dialing
# bmRequestType : 0x21/0x22
# bRequest      : 0x14
# wValue        : Timing
# wIndex        : Interface / Endpoint
# wLength       : 0x0000
# Data          : None
#*******************************************************************************
# start SET_PULSE_TIME
SET_PULSE_TIME()
{
    breakTime   = NextNBits_(8);
    VS = "wValue";
    AddBlockPLCell("Break Time", Format("0x%02X", breakTime), "The high byte of the wValue specifies the break time period");
    makeTime = NextNBits_(8);
    VS = "wValue";
    AddBlockPLCell("Make Time", Format("0x%02X", makeTime), "The low byte of the wValue specifies the make time period");

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
        isError = null;
    }
    else
    {
        isError = _ERROR;
    }
    AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data", isError);
    out.Decoded = 8;
/*
    if (wLength == 0)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data");
        out.Decoded = 8;
    }
    else
    {
        err_tooltip = "Illegal wLength Value" ;
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
            out.Decoded = 8;
    }
*/
}
# end SET_PULSE_TIME

#*******************************************************************************
# RING_AUX_JACK : This request is used to generate a ring signal on a secondary
#                 phone jack
# bmRequestType : 0x21/0x22
# bRequest      : 0x15
# wValue        : Number of Rings
# wIndex        : Interface / Endpoint
# wLength       : 0x0000
# Data          : None
#*******************************************************************************
# start RING_AUX_JACK
RING_AUX_JACK()
{
    wValue   = NextDataWord_();
    VS = "wValue";
    AddBlockPLCell("# of Rings", Format("0x%04X", wValue), Format("%d Rings", wValue));

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
        isError = null;
    }
    else
    {
        isError = _ERROR;
    }
    AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data", isError);
    out.Decoded = 8;
/*
    if (wLength == 0)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data");
        out.Decoded = 8;
    }
    else
    {
        err_tooltip = "Illegal wLength Value" ;
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
            out.Decoded = 8;
    }
*/
}
# end RING_AUX_JACK

#*******************************************************************************
# SET_LINE_CODING : This request allows the host to specify typical asynchronous
#                   line-character formatting properties
# bmRequestType : 0x21/0x22
# bRequest      : 0x20
# wValue        : 0x0000
# wIndex        : Interface / Endpoint
# wLength       : Size of Structure
# Data          : Line Coding Structure
#*******************************************************************************
set LineCodingStopBitsTable =
[
    [0xFF, "Unknown",      _ERROR],
    [0x00, "1 Stop bit",    null],
    [0x01, "1.5 Stop bits", null],
    [0x02, "2 Stop bits",   null]
];

set LineCodingParityTable =
[
    [0xFF, "Unknown", _ERROR],
    [0x00, "No Parity"   , null  ],
    [0x01, "Odd Parity"   , null  ],
    [0x02, "Even Parity"   , null  ],
    [0x03, "Mark Parity"   , null  ],
    [0x04, "Space Parity"   , null  ]
];

# start SET_LINE_CODING & GET_LINE_CODING
SET_LINE_CODING()
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
    if (wLength == 7)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Size of line coding structure");
        dwDTERate = NextDataDWord_();
        AddPayLoadCell("dwDTERate", Format("0x%08X", dwDTERate), "Data terminal rate, in bits per second");

        bCharFormat = NextNBits_(8);
        _row = Find(LineCodingStopBitsTable, bCharFormat);
        AddPayLoadCell("Stop Bits", _row[1],Format("Stop Bits = %d", bCharFormat), _row[2]);

        bParityType = NextNBits_(8);
        _row = Find(LineCodingParityTable, bParityType);
        AddPayLoadCell("Parity", _row[1], Format("Parity = %d", bParityType), _row[2]);

        bDataBits = NextNBits_(8);
        if (bDataBits == 5 ||bDataBits == 6 ||bDataBits == 7 ||bDataBits == 8 ||bDataBits == 16)
            isError = null;
        else
            isError = _ERROR;
        AddPayLoadCell("Data Bits", Format("%d", bDataBits), "Data bits (5, 6, 7, 8, or 16)", isError);

        out.Decoded = 8 + wLength;
    }
    else
    {
        err_tooltip = "Illegal wLength Value! The length for should be 7";
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        /*
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
        */
            out.Decoded = 8;
    }
}

GET_LINE_CODING()
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
    if (bmRequestType == 0xA1 )
    {
        AddPayLoadCell("wIndex", Format("Interface %d", wIndex), "Interface ID");
    }
    else if (bmRequestType == 0xA2)
    {
        AddPayLoadCell("wIndex", Format("Endpoint %d", wIndex), "Endpoint ID");
    }
    else
    {
        err_tooltip = Format("Unknown bmRequestType (0x%02X)! ", bmRequestType);
        AddPayLoadCell("wIndex", Format("0x%04X", wIndex), AddErrorTooltip(), _ERROR);
    }
    wLength  = NextDataWord_();
    if (wLength == 7)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Size of line coding structure");
        dwDTERate = NextDataDWord_();
        AddPayLoadCell("dwDTERate", Format("0x%08X", dwDTERate), "Data terminal rate, in bits per second");

        bCharFormat = NextNBits_(8);
        _row = Find(LineCodingStopBitsTable, bCharFormat);
        AddPayLoadCell("Stop Bits", _row[1],Format("Stop Bits = %d", bCharFormat), _row[2]);

        bParityType = NextNBits_(8);
        _row = Find(LineCodingParityTable, bParityType);
        AddPayLoadCell("Parity", _row[1], Format("Parity = %d", bParityType), _row[2]);

        bDataBits = NextNBits_(8);
        if (bDataBits == 5 ||bDataBits == 6 ||bDataBits == 7 ||bDataBits == 8 ||bDataBits == 16)
            isError = null;
        else
            isError = _ERROR;
        AddPayLoadCell("Data Bits", Format("%d", bDataBits), "Data bits (5, 6, 7, 8, or 16)", isError);

        out.Decoded = 8 + wLength;
    }
    else
    {
        err_tooltip = "Illegal wLength Value! The length for should be 7";
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        /*
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
        */
            out.Decoded = 8;
    }
}
# end SET_LINE_CODING & GET_LINE_CODING


#*******************************************************************************
# SET_CONTROL_LINE_STATE :
#                 This request generates RS-232/V.24 style control signals
# bmRequestType : 0x21/0x22
# bRequest      : 0x22
# wValue        : Control Signal Bitmap
# wIndex        : Interface / Endpoint
# wLength       : 0x0000
# Data          : None
#*******************************************************************************
# start SET_CONTROL_LINE_STATE
SET_CONTROL_LINE_STATE()
{
    wValue   = NextDataWord_();
	if (wValue > 3) {
	    err_tooltip = "Illegal wValue value, Bits 15-2 should set to zero!";
        AddPayLoadCell("wValue", Format("0x%04X", wValue), AddErrorTooltip(), _ERROR);
    }
	CarrierControl = (wValue & 2)>>1;
    if (CarrierControl == 1)
        text = "Activate";
    else
        text = "Deactivate";
    VS = "wValue";
    AddBlockPLCell("Carrier Ctrl", text, "Carrier Control for half duplex modems.\nThis value should ignored when operating in full duplex mode.");
	DTEPresent = wValue & 1;
    if (DTEPresent == 1)
        text = "Present";
    else
        text = "Not Present";
    VS = "wValue";
    AddBlockPLCell("DTE", text, "This signal corresponds to V.24 signal 108/2 and RS-232 signal DTR");
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
        isError = null;
    }
    else
    {
        isError = _ERROR;
    }
    AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data", isError);
    out.Decoded = 8;
/*
    if (wLength == 0)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data");
        out.Decoded = 8;
    }
    else
    {
        err_tooltip = "Illegal wLength Value" ;
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
            out.Decoded = 8;
    }
    */
}
# end SET_CONTROL_LINE_STATE

#*******************************************************************************
# SEND_BREAK    : This request sends special carrier modulation that generates
#                 RS-232/V.24 style break
# bmRequestType : 0x21/0x22
# bRequest      : 0x23
# wValue        : Duration of break
# wIndex        : Interface / Endpoint
# wLength       : 0x0000
# Data          : None
#*******************************************************************************
# start SEND_BREAK
SEND_BREAK()
{
    wValue = NextDataWord_();
    if (wValue == 0x0000)
        text = "Stop";
    else if (wValue == 0xFFFF)
        text = "Unlimited";
    else
        text = Format("0x%04X ms", wValue);
    VS = "wValue";
    AddBlockPLCell("Break Duration", text, "The length of the time, in milliseconds, of the break signal");
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
        isError = null;
    }
    else
    {
        isError = _ERROR;
    }
    AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data", isError);
    out.Decoded = 8;
/*
    if (wLength == 0)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data");
        out.Decoded = 8;
    }
    else
    {
        err_tooltip = "Illegal wLength Value" ;
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
            out.Decoded = 8;
    }
    */
}
# end SEND_BREAK

#*******************************************************************************
# SET_RINGER_PARMS : This request configures the ringer for the communication
#                    device, either on a global basis or on a per-line basis
#                    for multiple line devices
# bmRequestType : 0x21/0x22
# bRequest      : 0x30
# wValue        : 0x0000
# wIndex        : Interface / Endpoint
# wLength       : 0x04
# Data          : Ringer configuration bitmap
#*******************************************************************************
# start SET_RINGER_PARMS & GET_RINGER_PARMS
SET_RINGER_PARMS()
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
    if (wLength == 4)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Size of line coding structure");
        ringer = NextNBits_(1);
        if (ringer == 1)
            text = "Exist";
        else
            text = "Not exist";
        AddPayLoadCell("Ringer", text, Format("Ringer = %d", ringer));

        PLReservedCheck(15);
        ringerVolume = NextNBits_(8);
        if (ringerVolume == 0)
            text = "Off";
        else if (ringerVolume == 255)
            text = "Maximum";
        else
            text = Format("%d", ringerVolume);
        AddPayLoadCell("Ringer Volume", text, "Ringer Volume Setting");
        ringerPattern = NextNBits_(8);
        AddPayLoadCell("Ringer Pattern", Format("%d", ringerPattern), "Ringer pattern Type Selection");


        out.Decoded = 8 + wLength;
    }
    else
    {
        err_tooltip = "Illegal wLength Value! The length for should be 4";
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        /*
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
        */
            out.Decoded = 8;
    }
}

GET_RINGER_PARMS()
{
    Call("SET_RINGER_PARMS");
}
# end SET_RINGER_PARMS & GET_RINGER_PARMS


#*******************************************************************************
# SET_OPERATION_PARMS :
#                  This request sets the operational mode for the device,
#                  between a simple mode, standalone mode and a host centric mode.
#                  Standalone mode means no controls from host, host centric mode
#                  means all controls from host
# bmRequestType : 0x21/0x22
# bRequest      : 0x32
# wValue        : Operation Mode
# wIndex        : Interface / Endpoint
# wLength       : 0x0000
# Data          : None
#*******************************************************************************
# start SET_OPERATION_PARMS
set OperationModeSelectorTable =
[
    #------------------------------------------------------------------------------------------
    # value, text,          error                                                             |
    #------------------------------------------------------------------------------------------
    [ 0xFFFF,  "Unknown Mode", _ERROR   ],
    [ 0x0000,  "Simple Mode", null      ],
    [ 0x0001,  "Standalone Mode", null  ],
    [ 0x0002,  "Host Centric Mode", null]
];
SET_OPERATION_PARMS()
{
    wValue   = NextDataWord_();
    _row = Find(OperationModeSelectorTable, wValue);
    VS = "wValue";
    AddBlockPLCell("Operation Mode", _row[1], Format("wValue = 0x%04X", wValue), row[2]);

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
        isError = null;
    }
    else
    {
        isError = _ERROR;
    }
    AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data", isError);
    out.Decoded = 8;
/*
    if (wLength == 0)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data");
        out.Decoded = 8;
    }
    else
    {
        err_tooltip = "Illegal wLength Value" ;
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
            out.Decoded = 8;
    }
    */
}
# end SET_OPERATION_PARMS

#*******************************************************************************
# GET_OPERATION_PARMS :
#                  This request gets the operational mode from the device.
# bmRequestType : 0xA1/0xA2
# bRequest      : 0x33
# wValue        : Operation Mode
# wIndex        : Interface / Endpoint
# wLength       : 0x0000
# Data          : Operation Mode
#*******************************************************************************
# start GET_OPERATION_PARMS
GET_OPERATION_PARMS()
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
    if (bmRequestType == 0xA1 )
    {
        AddPayLoadCell("wIndex", Format("Interface %d", wIndex), "Interface ID");
    }
    else if (bmRequestType == 0xA2)
    {
        AddPayLoadCell("wIndex", Format("Endpoint %d", wIndex), "Endpoint ID");
    }
    else
    {
        err_tooltip = Format("Unknown bmRequestType (0x%02X)! ", bmRequestType);
        AddPayLoadCell("wIndex", Format("0x%04X", wIndex), AddErrorTooltip(), _ERROR);
    }
    wLength  = NextDataWord_();
    if (wLength == 2)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Size of line coding structure");
        opertaionMode = NextDataWord_();
        _row = Find(OperationModeSelectorTable, operationMode);
        AddPayLoadCell("Operation Mode", _row[1], Format("Operation Mode = 0x%04X", wValue), row[2]);

        out.Decoded = 8 + wLength;
    }
    else
    {
        err_tooltip = "Illegal wLength Value! The length for should be 2";
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        /*
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
        */
            out.Decoded = 8;
    }
}
# end GET_OPERATION_PARMS


#*******************************************************************************
# SET_LINE_PARMS : This request is used to change the state of the line,
#                  corresponding to the interface or master interface of a union
#                  to which the command was sent
# bmRequestType : 0x21/0x22
# bRequest      : 0x34
# wValue        : Line State Change
# wIndex        : Interface / Endpoint
# wLength       : Length of Data
# Data          : Data
#*******************************************************************************
# start SET_LINE_PARMS
set LineStateSelectorTable =
[
    #------------------------------------------------------------------------------------------
    # value, text,          error                                                             |
    #------------------------------------------------------------------------------------------
    [ 0xFFFF,  "Unknown Line State value", _ERROR   ],
    [ 0x0000,  "Drop the active call on the line", null      ],
    [ 0x0001,  "Start a new call on the line", null  ],
    [ 0x0002,  "Apply ringing to the line", null],
    [ 0x0003,  "Remove ringing from the line", null],
    [ 0x0004,  "Switch to a specific call on the line", null]
];
SET_LINE_PARMS()
{
    wValue   = NextDataWord_();
    _row = Find(LineStateSelectorTable, wValue);
    VS = "wValue";
    AddBlockPLCell("Line State", Format("wValue = 0x%04X", wValue), _row[1], row[2]);

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
    if (wLength >= 0)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data");
        if (wLength > 0)
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
# end SET_LINE_PARMS

#*******************************************************************************
# GET_LINE_PARMS : This request is used to report the state of the line, that
#                  corresponds to the interface or master interface of a union
#                  to which the command was sent
# bmRequestType : 0xA1/0xA2
# bRequest      : 0x35
# wValue        : 0x0000
# wIndex        : Interface / Endpoint
# wLength       : Size of Structure
# Data          : Line Status Information Structure
#*******************************************************************************
# start GET_LINE_PARMS
set CallStateChangeValueSelectorTable =
[
    [0xFF, "Unknown",       _ERROR  ],
    [0x00, "Reserved",      null    ],
    [0x01, "Idle",          null    ],
    [0x02, "Dialing",       null    ],
    [0x03, "Ringback",      null    ],
    [0x04, "Connected",     null    ],
    [0x05, "Incoming Call", null    ]
];

set CallStateValueSelectorTable =
[
    [0xFF, "Unknown",       _ERROR  ],
    [0x00, "Call is idle",  null    ],
    [0x01, "Typical dial tone", null    ],
    [0x02, "Interrupted dial tone", null    ],
    [0x03, "Dialing is in progress", null   ],
    [0x04, "Ringback",               null   ],
    [0x05, "Connected",              null   ],
    [0x06, "Incoming call",          null   ]
];

set CallStateRingbackSelectorTable =
[
    [3, "Reserved"],
    [0, "normal"],
    [1, "busy"  ],
    [2, "fast busy"],
    [255, "Unknown type"]
];

set CallStateConnectedSelectorTable =
[
    [4, "Reserved"],
    [0, "voice connection"],
    [1, "answering machine connection"],
    [2, "fax machine connection"],
    [3, "data modem connection"],
    [255, "unknown connection type"]
];

set CallStateImcomingSelectorTable =
[
    [4, "Reserved for future use"],
    [0, "Ringing pattern 1 (default or normal pattern)"],
    [1, "Ringing pattern 2"],
    [2, "Ringing pattern 3"],
    [3, "Ringing pattern 4"]
];

GET_LINE_PARMS()
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
    if (bmRequestType == 0xA1 )
    {
        AddPayLoadCell("wIndex", Format("Interface %d", wIndex), "Interface ID");
    }
    else if (bmRequestType == 0xA2)
    {
        AddPayLoadCell("wIndex", Format("Endpoint %d", wIndex), "Endpoint ID");
    }
    else
    {
        err_tooltip = Format("Unknown bmRequestType (0x%02X)! ", bmRequestType);
        AddPayLoadCell("wIndex", Format("0x%04X", wIndex), AddErrorTooltip(), _ERROR);
    }
    wLength  = NextDataWord_();
    if (wLength >=  10)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Size of line Status Information structure");
        length = NextDataWord_();
        if (wLength == length)
            isError = null;
        else
            isError = _ERROR;
        AddPayLoadCell("Length", Format("%d", wLength), "Should match the Previous wLength value", isError);

        #Ringer Bitmap
        ringer = NextNBits_(1);
        if (ringer == 1)
            text = "Exist";
        else
            text = "Not exist";
        AddPayLoadCell("Ringer", text, Format("Ringer = %d", ringer));

        PLReservedCheck(15);
        ringerVolume = NextNBits_(8);
        if (ringerVolume == 0)
            text = "Off";
        else if (ringerVolume == 255)
            text = "Maximum";
        else
            text = Format("%d", ringerVolume);
        AddPayLoadCell("Ringer Volume", text, "Ringer Volume Setting");
        ringerPattern = NextNBits_(8);
        AddPayLoadCell("Ringer Pattern", Format("%d", ringerPattern), "Ringer pattern Type Selection");


        #Line State
        activeFlag = NextNBits_(1);
        if (activeFlag == 1)
            text = "Active";
        else
            text = "Inactive";
        AddPayLoadCell("Active Flag", text, "Line active flag");
        PLReservedCheck(23);
        indexActive = NextNBits_(8);
        if (indexActive == 255)
            text = "N/A";
        else
            text = Format("%d", indexActive);
        AddPayLoadCell("Index", text, "Index of active call on this line");
        bytesLeft = wLength - 10;
        stateID = 0;
        hasError = 0;
        while (bytesLeft >= 4 && hasError == 0)
        {
            ActiveFlag = NextNBits_(1);
            if (ActiveFlag == 1)
                text = "Active";
            else
                text = "Inactive";
            VS = "Active Flag";
            AddBlockPLCell(Format("Active Flag %d", stateID), text, Format("Active flag for call state %d", stateID));
            PLReservedCheck(15);
            changeValue = NextNBits_(8);
            _row = Find(CallStateChangeValueSelectorTable, changeValue);
            VS = "Change Value";
            AddBlockPLCell(Format("Change Value %d", stateID), _row[1], Format("Call State Change Value = %d", changeValue), _row[2]);
            if (changeValue == 3)
            {
                stateValue = NextNBits_(8);
                _row = Find(CallStateRingbackSelectorTable, stateValue);
                AddPayLoadCell("Ringback Type", Format("%d", stateValue), _row[1]);
                bytesLeft -= 4;
            }
            else if (changeValue == 4)
            {
                stateValue = NextNBits_(8);
                _row = Find(CallStateConnectedSelectorTable, stateValue);
                AddPayLoadCell("Connection Type", Format("%d", stateValue), _row[1]);
                bytesLeft -= 4;
            }
            else if (changeValue == 5)
            {
                stateValue = NextNBits_(8);
                _row = Find(CallStateImcomingSelectorTable, stateValue);
                AddPayLoadCell("Ringing Type", Format("%d", stateValue), _row[1]);
                bytesLeft -= 4;
                if (bytesLeft <= 0)
                    hasError = 1;
                else
                {
                    size = NextNBits_(8);
                    bytesLeft --;
                    AddPayLoadCell("Time Str size", Format("%d", size), "Size of the string following");
                }
                if (bytesLeft < size || hasError == 1)
                    hasError = 1;
                else
                {
                    text = GetStrFld(size);
                    bytesLeft -= size;
                    AddPayLoadCell("Time Str", text, "The time of the incoming call as delivered via caller ID");
                }
                if (bytesLeft <= 0 || hasError == 1)
                    hasError = 1;
                else
                {
                    size = NextNBits_(8);
                    bytesLeft --;
                    AddPayLoadCell("PN Str size", Format("%d", size), "Size of the Phone number string following");
                }
                if (bytesLeft < size || hasError == 1)
                    hasError = 1;
                else
                {
                    text = GetStrFld(size);
                    bytesLeft -= size;
                    AddPayLoadCell("PN Str", text, "The phone number of the incoming call as delivered via caller ID");
                }
                if (bytesLeft <= 0 || hasError == 1)
                    hasError = 1;
                else
                {
                    size = NextNBits_(8);
                    bytesLeft --;
                    AddPayLoadCell("Name Str size", Format("%d", size), "Size of the string following");
                }
                if (bytesLeft < size || hasError == 1)
                    hasError = 1;
                else
                {
                    text = GetStrFld(size);
                    bytesLeft -= size;
                    AddPayLoadCell("Name Str", text, "The name of the calling party as delivered via caller ID");
                }
            }
            else
            {
                stateValue = NextNBits_(8);
                _row = Find(CallStateChangeValueSelectorTable, changeValue);
                VS = "Change Value";
                AddBlockPLCell(Format("Change Value %d", stateID), _row[1], Format("Call State Change Value = %d", changeValue), _row[2]);
                bytesLeft -= 4;
            }
        }
        if (bytesLeft >0)
            AddExtraBytesPayloadCell(bytesLeft);


        out.Decoded = 8 + wLength;
    }
    else
    {
        err_tooltip = "Illegal wLength Value!The length of the the payload has to be at least 10 bytes";
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        /*
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
        */
            out.Decoded = 8;
    }
}

# end GET_LINE_PARMS

#*******************************************************************************
# DIAL_DIGITS   : This request dials the DTMF digits over the specified line
# bmRequestType : 0x21/0x22
# bRequest      : 0x36
# wValue        : Line State Change
# wIndex        : Interface / Endpoint
# wLength       : Length of Dialing String
# Data          : Dialing String
#*******************************************************************************
# start DIAL_DIGITS
DIAL_DIGITS()
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
    if (wLength >= 0)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of Dialing String");
        text = GetStrFld(wLength);
        AddPayLoadCell("Dialing str", text, "String of dialing commands");
        out.Decoded = 8 + wLength;
    }
    else
    {
        err_tooltip = "Illegal wLength Value!";
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        out.Decoded = 8;
    }
}
# end DIAL_DIGITS

#*******************************************************************************
# SET_UNIT_PARAMETER : This request sets the value of a parameter belonging to a
#                 Unit identified by Unit Parameter Structure.
# GET_UNIT_PARAMETER : This request returns the current value of a parameter
#                 belonging to a Unit pointed out by a Unit Parameter Structure.
# bmRequestType : 0x21/0xA1
# bRequest      : 0x37/0x38
# wValue        : Unit Parameter Structure
# wIndex        : Interface
# wLength       : Length of Unit Parameter
# Data          : Unit Parameter
#
#*******************************************************************************
# start SET_UNIT_PARAMETER/GET_UNIT_PARAMETER
SET_UNIT_PARAMETER()
{
    bEntityId = NextNBits_(8);
    VS = "wValue";
    AddBlockPLCell("Unit Id", Format("%d", bEntityId), Format("Unit Id %d", bEntityId));
    bParamenterIndex = NextNBits_(8);
    VS = "wValue";
    AddBlockPLCell("Param Id", Format("%d", bParamenterIndex), "A zero based value indicating Unit parameter index");
    wIndex   = NextDataWord_();
    if (bmRequestType == 0x21 || bmRequestType == 0xA1)
    {
        AddPayLoadCell("wIndex", Format("Interface %d", wIndex), "Interface ID");
    }
    else
    {
        err_tooltip = Format("Unknown bmRequestType (0x%02X)! ", bmRequestType);
        AddPayLoadCell("wIndex", Format("0x%04X", wIndex), AddErrorTooltip(), _ERROR);
    }
    wLength  = NextDataWord_();
    if (wLength >= 0)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of Dialing String");
        text = GetStrFld(wLength);
        AddExtraBytesPayloadCell(wLength);
        out.Decoded = 8 + wLength;
    }
    else
    {
        err_tooltip = "Illegal wLength Value!";
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        out.Decoded = 8;
    }
}

GET_UNIT_PARAMETER()
{
    Call("SET_UNIT_PARAMETER");
}
# end SET_UNIT_PARAMETER/GET_UNIT_PARAMETER

#*******************************************************************************
# CLEAR_UNIT_PARAMETER : This request restores the default value of a parameter
#                 belonging to a Unit identified by Unit Parameter Structure.
# bmRequestType : 0x21
# bRequest      : 0x39
# wValue        : Unit Parameter Structure
# wIndex        : Interface
# wLength       : 0x00
# Data          : None
#*******************************************************************************
# start CLEAR_UNIT_PARAMETER
CLEAR_UNIT_PARAMETER()
{
    bEntityId = NextNBits_(8);
    VS = "wValue";
    AddBlockPLCell("Unit Id", Format("%d", bEntityId), Format("Unit Id %d", bEntityId));
    bParamenterIndex = NextNBits_(8);
   VS = "wValue";
    AddBlockPLCell("Param Id", Format("%d", bParamenterIndex), "A zero based value indicating Unit parameter index");
    wIndex   = NextDataWord_();
    if (bmRequestType == 0x21)
    {
        AddPayLoadCell("wIndex", Format("Interface %d", wIndex), "Interface ID");
    }
    else
    {
        err_tooltip = Format("Unknown bmRequestType (0x%02X)! ", bmRequestType);
        AddPayLoadCell("wIndex", Format("0x%04X", wIndex), AddErrorTooltip(), _ERROR);
    }
    wLength  = NextDataWord_();
    if (wLength == 0)
    {
        isError = null;
    }
    else
    {
        isError = _ERROR;
    }
    AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data", isError);
    out.Decoded = 8;
/*
    if (wLength == 0)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data");
        out.Decoded = 8;
    }
    else
    {
        err_tooltip = "Illegal wLength Value" ;
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
            out.Decoded = 8;
    }
    */
}
# end CLEAR_UNIT_PARAMETER

#*******************************************************************************
# GET_PROFILE   : This request returns the profile information as defined by CAPI2.0.
#                 The profile describes the implemented capabilities of the device.
# bmRequestType : 0xA1
# bRequest      : 0x3A
# wValue        : 0x00
# wIndex        : Interface
# wLength       : 64
# Data          : Profile Information according to CAPI2.0 chapter8
#*******************************************************************************
# start GET_PROFILE
GET_PROFILE()
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
    if (bmRequestType == 0xA1 )
    {
        AddPayLoadCell("wIndex", Format("Interface %d", wIndex), "Interface ID");
    }
    else
    {
        err_tooltip = Format("Unknown bmRequestType (0x%02X)! ", bmRequestType);
        AddPayLoadCell("wIndex", Format("0x%04X", wIndex), AddErrorTooltip(), _ERROR);
    }
    wLength  = NextDataWord_();
    if (wLength == 64)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of the profile");
        AddBlockPLCellMonoCap( "Profile", "Information" );
        ShowDataBlockVS( wLength );
        out.Decoded = 8 + wLength;
    }
    else
    {
        err_tooltip = "Illegal wLength Value! The length for should be 64";
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        /*
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
        */
            out.Decoded = 8;
    }
}
# end GET_PROFILE

#*******************************************************************************
# SET_ETHERNET_MULTICAST_FILTERS :
#                 This request sets the Ethernet Device multicast filters as
#                 specified in the sequential list of 48 bit Ethernet multicast address.
# bmRequestType : 0x21
# bRequest      : 0x40
# wValue        : Number of Filters(N)
# wIndex        : Interface
# wLength       : N*6
# Data          : List of N 48bit multicast addresses, in network byte order
#*******************************************************************************
# start SET_ETHERNET_MULTICAST_FILTERS
SET_ETHERNET_MULTICAST_FILTERS()
{
    wValue = NextDataWord_();
    VS = "wValue";
    AddBlockPLCell("Num filters", Format("%d", wValue), Format("Number of filters = %d", wValue));
    wIndex   = NextDataWord_();
    if (bmRequestType == 0x21 )
    {
        AddPayLoadCell("wIndex", Format("Interface %d", wIndex), "Interface ID");
    }
    else
    {
        err_tooltip = Format("Unknown bmRequestType (0x%02X)! ", bmRequestType);
        AddPayLoadCell("wIndex", Format("0x%04X", wIndex), AddErrorTooltip(), _ERROR);
    }
    wLength  = NextDataWord_();
    if (wLength == wValue * 6)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of multicast addresses");
        AddBlockPLCellMonoCap( "Multicast", "Addresses" );
        ShowDataBlockVS( wLength );
        out.Decoded = 8 + wLength;
    }
    else
    {
        err_tooltip = Format("Illegal wLength Value! The length for should be %d", wValue * 6);
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        /*
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
        */
            out.Decoded = 8;
    }
}
# end SET_ETHERNET_MULTICAST_FILTERS

#*******************************************************************************
# SET_ETHERNET_POWER_MANAGEMENT_PATTERN_FILTER :
#                 This request sets up the specified Ethernet power management
#                 pattern filter as described in the data structure.
# bmRequestType : 0x21
# bRequest      : 0x41
# wValue        : Filter Number
# wIndex        : Interface
# wLength       : Size of Structure
# Data          : Power management pattern filter structure
#*******************************************************************************
# start SET_ETHERNET_POWER_MANAGEMENT_PATTERN_FILTER
SET_ETHERNET_POWER_MANAGEMENT_PATTERN_FILTER()
{
    wValue = NextDataWord_();
    VS = "wValue";
    AddBlockPLCell("Filter num", Format("%d", wValue), Format("Filter Number = %d", wValue));
    wIndex   = NextDataWord_();
    if (bmRequestType == 0x21 )
    {
        AddPayLoadCell("wIndex", Format("Interface %d", wIndex), "Interface ID");
    }
    else
    {
        err_tooltip = Format("Unknown bmRequestType (0x%02X)! ", bmRequestType);
        AddPayLoadCell("wIndex", Format("0x%04X", wIndex), AddErrorTooltip(), _ERROR);
    }
    wLength  = NextDataWord_();
    if (wLength >= 2)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Size of the power management pattern filter structure");
        maskSize = NextDataWord_();
        AddPayLoadCell("Mask Size", Format("%d", maskSize), "Size of the Mask");
        decodedBytes = 2;
        if (wLength >= maskSize + decodedBytes)
        {
            IncFieldOffset( maskSize * 8 );
            text = "0x";
            for(i = 0; i < maskSize; i++)
                text += Format("%02X", NextNBits(8));
            AddPayLoadCell("Mask", text, "Bitmask");
            decodedBytes += maskSize;
            if (wLength >= maskSize * 8 + decodedBytes)
            {
                text = GetStrFld(maskSize * 8);
                AddPayLoadCell("Match Str", text, "The string of bytes to perform pattern matching");
                decodedBytes += maskSize * 8;
            }
        }

        if (wLength > decodedBytes)
            AddExtraBytesPayloadCell(wLength - decodedBytes);

        out.Decoded = 8 + wLength;
    }
    else
    {
        err_tooltip = "Illegal wLength Value!";
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        /*
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
        */
            out.Decoded = 8;
    }
}
# end SET_ETHERNET_POWER_MANAGEMENT_PATTERN_FILTER

#*******************************************************************************
# GET_ETHERNET_POWER_MANAGEMENT_PATTERN_FILTERS :
#                 This request retrieves the status of the specified Ethernet
#                 power management pattern filter from the device.
# bmRequestType : 0xA1
# bRequest      : 0x42
# wValue        : Filter Number
# wIndex        : Interface
# wLength       : 0x02
# Data          : Patteren active boolean
#*******************************************************************************
# start GET_ETHERNET_POWER_MANAGEMENT_PATTERN_FILTER
GET_ETHERNET_POWER_MANAGEMENT_PATTERN_FILTER()
{
    wValue = NextDataWord_();
    VS = "wValue";
    AddBlockPLCell("Filter Num", Format("%d", wValue), Format("Filter Number = %d", wValue));
    wIndex   = NextDataWord_();
    if (bmRequestType == 0xA1 )
    {
        AddPayLoadCell("wIndex", Format("Interface %d", wIndex), "Interface ID");
    }
    else
    {
        err_tooltip = Format("Unknown bmRequestType (0x%02X)! ", bmRequestType);
        AddPayLoadCell("wIndex", Format("0x%04X", wIndex), AddErrorTooltip(), _ERROR);
    }
    wLength  = NextDataWord_();
    if (wLength == 2)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Size of the pattern active boolean");
        patternBoolean = NextDataWord_();
        if (patternBoolean == 0x0000)
            text = FALSE;
        else if (patternBoolean == 0x0001)
            text = TRUE;
        else
            text = Format("Undefined %d", patternBoolean);
        AddPayLoadCell("Pattern Active", text, "If an active pattern has been set for the specified filter");
        out.Decoded = 8 + wLength;
    }
    else
    {
        err_tooltip = "Illegal wLength Value!";
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        /*
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
        */
            out.Decoded = 8;
    }
}
# end GET_ETHERNET_POWER_MANAGEMENT_PATTERN_FILTER

#*******************************************************************************
# SET_ETHERNET_PACKET_FILTER : This request is used to configure device packet
#                 filter settings.
# bmRequestType : 0x21
# bRequest      : 0x43
# wValue        : Packet Filter Bitmap
# wIndex        : Interface
# wLength       : 0x00
# Data          : None
#*******************************************************************************
# start SET_ETHERNET_PACKET_FILTER
SET_ETHERNET_PACKET_FILTER()
{
    packet_filter_bitmap = NextDataWord_();	
	multicast = (packet_filter_bitmap & 0x10) >> 4;
    if (multicast == 1)
        text = "Enabled";
    else
        text = "Disabled";
    VS = "wValue";
    AddBlockPLCell("Multicast", text, Format("Packet type multicast = %d",multicast));

    broadcast = (packet_filter_bitmap & 0x8) >> 3;
    if (broadcast == 1)
        text = "Enabled";
    else
        text = "Disabled";
    VS = "wValue";
    AddBlockPLCell("Broadcast", text, Format("Packet type broadcast = %d",broadcast));

	directed  = (packet_filter_bitmap & 0x4) >> 2;
    if (directed == 1)
        text = "Enabled";
    else
        text = "Disabled";
    VS = "wValue";
    AddBlockPLCell("Directed", text, Format("Packet type directed = %d",directed));

    all_multicast  = (packet_filter_bitmap & 0x2) >> 1;
    if (all_multicast == 1)
        text = "Enabled";
    else
        text = "Disabled";
    VS = "wValue";
    AddBlockPLCell("All Multicast", text, Format("Packet type all multicast = %d",all_multicast));

    promiscuous  = (packet_filter_bitmap & 0x1);
    if (promiscuous == 1)
        text = "Enabled";
    else
        text = "Disabled";
    VS = "wValue";
    AddBlockPLCell("Promiscuous", text, Format("Packet type promiscuous = %d",promiscuous));

    wIndex   = NextDataWord_();
    if (bmRequestType == 0x21 )
    {
        AddPayLoadCell("wIndex", Format("Interface %d", wIndex), "Interface ID");
    }
    else
    {
        err_tooltip = Format("Unknown bmRequestType (0x%02X)! ", bmRequestType);
        AddPayLoadCell("wIndex", Format("0x%04X", wIndex), AddErrorTooltip(), _ERROR);
    }
    wLength  = NextDataWord_();
    if (wLength == 0)
    {
        isError = null;
    }
    else
    {
        isError = _ERROR;
    }
    AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data", isError);
    out.Decoded = 8;
/*
    if (wLength == 0)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Size of the pattern active boolean");
        out.Decoded = 8;
    }
    else
    {
        err_tooltip = "Illegal wLength Value!";
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
            out.Decoded = 8;
    }
    */
}
# end SET_ETHERNET_PACKET_FILTER

#*******************************************************************************
# GET_ETHERNET_STATISTIC :
#                 This request is used to retrieve a statistic based on the
#                 feature selector.
# bmRequestType : 0xA1
# bRequest      : 0x44
# wValue        : Feature Selector
# wIndex        : Interface
# wLength       : 0x04
# Data          : 32 bit unsigned integer
#*******************************************************************************
# start GET_ETHERNET_STATISTIC
set EthernetStatisticsFeatureSlectorTable =
[
    #------------------------------------------------------------------
    # Code, Feature,                length,     description
    #------------------------------------------------------------------
    [ 0x00, "RESERVED",             0, "Reserved for future use"                                                        ],
    [ 0x01, "XMIT_OK",              4, "Frames transmitted without errors"                                              ],
    [ 0x02, "RCV_OK",               4, "Frames received without errors"                                                 ],
    [ 0x03, "XMIT_ERROR",           4, "Frames not transmitted, or transmitted with errors"                             ],
    [ 0x04, "RCV_ERROR",            4, "Frames received with errors"                                                    ],
    [ 0x05, "RCV_NO_BUFFOR",        4, "Frames missed, no buffers"                                                      ],
    [ 0x06, "DIRECTED_BYTES_XMIT",  4, "Direct bytes transmitted without errors"                                        ],
    [ 0x07, "DIRECTED_FRAMES_XMIT", 4, "Direct frames transmitted without errors"                                       ],
    [ 0x08, "MULTICAST_BYTES_XMIT", 4, "Multicast bytes transmitted without errors"                                     ],
    [ 0x09, "MULTICAST_FRAMES_XMIT",4, "Multicast frames transmitted without errors"                                    ],
    [ 0x0A, "BROADCAST_BYTES_XMIT", 4, "Broadcast bytes transmitted without errors"                                     ],
    [ 0x0B, "BROADCAST_FRAMES_XMIT",4, "Broadcast frames transmitted without errors"                                    ],
    [ 0x0C, "DIRECTED_BYTES_RCV",   4, "Direct bytes received without errors"                                           ],
    [ 0x0D, "DIRECTED_FRAMES_RCV",  4, "Direct frames received without errors"                                          ],
    [ 0x0E, "MULTICAST_BYTES_RCV",  4, "Multicast bytes received without errors"                                        ],
    [ 0x0F, "MULTICAST_FRAMES_RCV", 4, "Multicast frames received without errors"                                       ],
    [ 0x10, "BROADCAST_BYTES_RCV",  4, "Broadcast bytes received without errors"                                        ],
    [ 0x11, "BROADCAST_FRAMES_RCV", 4, "Broadcast frames received without errors"                                       ],
    [ 0x12, "RCV_CRC_ERROR",        4, "Frames received with Cyclic Redundancy Check(CRC) or Frame check sequence(FCS)" ],
    [ 0x13, "TRANSMIT_QUEUE_LENGTH",4, "Length of transmit queue"                                                       ],
    [ 0x14, "RCV_ERROR_ALLIGNMENT", 4, "Frames received with alignment error"                                           ],
    [ 0x15, "XMIT_ONE_COLLISION",   4, "Frames transmitted with one collision"                                          ],
    [ 0x16, "XMIT_MORE_COLLISIONS", 4, "Frames transmitted with more than one collision"                                ],
    [ 0x17, "XMIT_DEFERRED",        4, "Frames transmitted after deferral"                                              ],
    [ 0x18, "XMIT_MAX_COLLISIONS",  4, "Frames not transmitted due to collisions"                                       ],
    [ 0x19, "RCV_OVERRUN",          4, "Frames not received due to overrun"                                             ],
    [ 0x1A, "XMIT_UNDERRUN",        4, "Frames not transmitted due to underrun"                                         ],
    [ 0x1B, "XMIT_HEARTBEAT_FAILURE",4, "Frames transmitted with heartbeat failure"                                     ],
    [ 0x1C, "XMIT_TIMES_CRS_LOST",  4, "The carrier sense signal lost during transmission"                              ],
    [ 0x1D, "XMIT_LATE_COLLISIONS", 4, "Late collision detected"                                                        ]
];
GET_ETHERNET_STATISTIC()
{
    wValue   = NextDataWord_();
    _row = Find(EthernetStatisticsFeatureSlectorTable, wValue);
    VS = "wValue";
    AddBlockPLCell("Feature Selector", _row[1], _row[3]);

    wIndex   = NextDataWord_();
    if (bmRequestType == 0xA1 )
    {
        AddPayLoadCell("wIndex", Format("Interface %d", wIndex), "Interface ID");
    }
    else
    {
        err_tooltip = Format("Unknown bmRequestType (0x%02X)! ", bmRequestType);
        AddPayLoadCell("wIndex", Format("0x%04X", wIndex), AddErrorTooltip(), _ERROR);
    }
    wLength  = NextDataWord_();
    if (wLength == _row[2])
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data");
        if (wLength == 4)
        {
            data = NextDataDWord_();
            AddPayLoadCell("Data", Format("%u", data), "32-bit unsigned integer");
        }
        out.Decoded = 8 + wLength;
    }
    else
    {
        err_tooltip = "Illegal wLength Value" ;
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        /*
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
        */
            out.Decoded = 8;
    }
}

# end GET_ETHERNET_STATISTIC

#*******************************************************************************
# SET_ATM_DATAFORMAT : This request is used to set the data format selected by
#                 the host in the wValue field.
# bmRequestType : 0x21
# bRequest      : 0x50
# wValue        : Data Format
# wIndex        : Interface
# wLength       : 0x00
# Data          : None
#*******************************************************************************
# start SET_ATM_DATAFORMAT
set ATMDataFormatTable =
[
    [ 0x0000, "Unknown Type", "The Type number is never specified", _ERROR],
    [ 0x0001, "Type 1", "Type 1 Format:concatenated ATM cells", null    ],
    [ 0x0002, "Type 2", "Type 2 Format:ATM Header template + concatenated ATM cell payloads", null],
    [ 0x0003, "Type 3", "Type 3 Format:AAL 5 SDU", null]
];
SET_ATM_DATAFORMAT()
{
    wValue   = NextDataWord_();
    _row = Find(ATMDataFormatTable, wValue);
    VS = "wValue";
    AddBlockPLCell("Feature Selector", _row[1], _row[2], _row[3]);
    wIndex   = NextDataWord_();
    if (bmRequestType == 0x21 )
    {
        AddPayLoadCell("wIndex", Format("Interface %d", wIndex), "Interface ID");
    }
    else
    {
        err_tooltip = Format("Unknown bmRequestType (0x%02X)! ", bmRequestType);
        AddPayLoadCell("wIndex", Format("0x%04X", wIndex), AddErrorTooltip(), _ERROR);
    }
    wLength  = NextDataWord_();
    if (wLength == 0)
    {
        isError = null;
    }
    else
    {
        isError = _ERROR;
    }
    AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data", isError);
    out.Decoded = 8;
/*
    if (wLength == 0)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data");
        out.Decoded = 8 + wLength;
    }
    else
    {
        err_tooltip = "Illegal wLength Value" ;
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
            out.Decoded = 8;
    }
    */
}
# end SET_ATM_DATAFORMAT

#*******************************************************************************
# GET_ATM_DEVICE_STATISTICS : This request is used to retrieve the device
#                 statistics based on the feature selector.
# bmRequestType : 0xA1
# bRequest      : 0x51
# wValue        : Feature Selector
# wIndex        : Interface
# wLength       : 0x04
# Data          : 32 bit unsigned integer
#*******************************************************************************
# start GET_ATM_DEVICE_STATISTICS
set ATMDeviceStatisticsFeatureSelectorTable =
[
    [ 0x00, "RESERVED",                     0, "Reserved for future use"],
    [ 0x01, "US_CELLS_SENT",                4, "No.of cells sent upstream to the WAN link by the ATM layer"],
    [ 0x02, "DS_CELLS_RECEIVED",            4, "No.of cells received downstream from the WAN link by the ATM layer"],
    [ 0x03, "DS_CELLS_USB_CONGESTION",      4, "No.of cells received and discarded due to congestion on USB link"],
    [ 0x04, "DS_CELLS_AAL5_CRC_ERROR",      4, "No.of cells received and discarded due to AAL5 CRC error"],
    [ 0x05, "DS_CELLS_HEC_ERROR",           4, "No.of cells received and discarded due to HEC errors in the cell header"],
    [ 0x06, "DS_CELLS_HEC_ERROR_CORRECTED", 4, "No.of cells received with HEC errors in the cell header and successfully corrected"]
];

GET_ATM_DEVICE_STATISTICS()
{
    wValue   = NextDataWord_();
    _row = Find(ATMDeviceStatisticsFeatureSelectorTable, wValue);
    VS = "wValue";
    AddBlockPLCell("Feature Selector", _row[1], _row[3]);

    wIndex   = NextDataWord_();
    if (bmRequestType == 0xA1 )
    {
        AddPayLoadCell("wIndex", Format("Interface %d", wIndex), "Interface ID");
    }
    else
    {
        err_tooltip = Format("Unknown bmRequestType (0x%02X)! ", bmRequestType);
        AddPayLoadCell("wIndex", Format("0x%04X", wIndex), AddErrorTooltip(), _ERROR);
    }
    wLength  = NextDataWord_();
    if (wLength == _row[2])
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data");
        if (wLength == 4)
        {
            data = NextDataDWord_();
            AddPayLoadCell("Data", Format("%u", data), "32-bit unsigned integer");
        }
        out.Decoded = 8 + wLength;
    }
    else
    {
        err_tooltip = "Illegal wLength Value" ;
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        /*
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
        */
            out.Decoded = 8;
    }
}
# end GET_ATM_DEVICE_STATISTICS

#*******************************************************************************
# SET_ATM_DEFAULT_VC : This request is used to pre-select the VPI/VCI value for
#                 subsequent GET_ATM_VC_STATISTICS requests.
# bmRequestType : 0x21
# bRequest      : 0x52
# wValue        : 0x00
# wIndex        : Interface
# wLength       : 0x03
# Data          : 1-byte VPI followed by 2-byte VCI value
#*******************************************************************************
# start SET_ATM_DEFAULT_VC
SET_ATM_DEFAULT_VC()
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
    else
    {
        err_tooltip = Format("Unknown bmRequestType (0x%02X)! ", bmRequestType);
        AddPayLoadCell("wIndex", Format("0x%04X", wIndex), AddErrorTooltip(), _ERROR);
    }
    wLength  = NextDataWord_();
    if (wLength == 3)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Size of the data");
        VPI = NextNBits_(8);
        AddPayLoadCell("VPI", Format("%02X", VPI), "VPI value");
        VCI = NextDataWord_();
        AddPayLoadCell("VCI", Format("%04X", VCI), "VCI value");

        out.Decoded = 8 + wLength;
    }
    else
    {
        err_tooltip = "Illegal wLength Value! The length for should be 3";
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        /*
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
        */
            out.Decoded = 8;
    }
}
# end SET_ATM_DEFAULT_VC

#*******************************************************************************
# GET_ATM_VC_STATISTICS : This request is used to retrieve the ATM device statistics
#                 based on the feature selector for a pre-selected VPI/VCI as
#                 stipulated in the latest preceding SET_ATM_DEFAULT_VC request.
# bmRequestType : 0xA1
# bRequest      : 0x53
# wValue        : Feature Selector
# wIndex        : Interface
# wLength       : 0x04
# Data          : 32 bit unsigned integer
#*******************************************************************************
# start GET_ATM_VC_STATISTICS
set ATMVCSelectorTable =
[
    [ 0x00, "RESERVED",             0, "Reserved for future use"],
    [ 0x01, "VC_US_CELLS_SENT",     4, "No.of cells sent upstream to the WAN link for the specified VPI/VCI"],
    [ 0x02, "VC_DS_CELLS_RECEIVED", 4, "No.of cells received downstream from the WAN link for the specified VPI/VCI"]
];
GET_ATM_VC_STATISTICS()
{
    wValue   = NextDataWord_();
    _row = Find(ATMVCSelectorTable, wValue);
    VS = "wValue";
    AddBlockPLCell("Feature Selector", _row[1], _row[3]);

    wIndex   = NextDataWord_();
    if (bmRequestType == 0xA1 )
    {
        AddPayLoadCell("wIndex", Format("Interface %d", wIndex), "Interface ID");
    }
    else
    {
        err_tooltip = Format("Unknown bmRequestType (0x%02X)! ", bmRequestType);
        AddPayLoadCell("wIndex", Format("0x%04X", wIndex), AddErrorTooltip(), _ERROR);
    }
    wLength  = NextDataWord_();
    if (wLength == _row[2])
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data");
        if (wLength == 4)
        {
            data = NextDataDWord_();
            AddPayLoadCell("Data", Format("%u", data), "32-bit unsigned integer");
        }
        out.Decoded = 8 + wLength;
    }
    else
    {
        err_tooltip = "Illegal wLength Value" ;
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        /*
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
        */
            out.Decoded = 8;
    }
}

# end GET_ATM_VC_STATISTICS

#*******************************************************************************
# NTB_Parameter_Structure :
#                 This function make NTB Parameter Structure data payload string
#*******************************************************************************
NTB_Parameter_Structure()
{
    dummy = NextNBits(6*8);
    save_endian = LittleEndian;
    LittleEndian = 1;
    Len   = NextDataWord_();

    if (Len > 0)
    {
        wLength                 = NextDataWord_();
        bmNtbFormatsSupported   = NextDataWord_();
        dwNtbInMaxSize          = NextDataDWord_();
        wNdpInDivisor           = NextDataWord_();
        wNdpInPayloadRemainder  = NextDataWord_();
        wNdpInAlignment         = NextDataWord_();
        reserved1               = NextDataWord_();
        dwNtbOutMaxSize         = NextDataWord_();
        wNdpOutDivisor          = NextDataWord_();
        wNdpOutPayloadRemainder = NextDataWord_();
        wNdpOutAlignment        = NextDataWord_();
        reserved2               = NextDataWord_();

        str = "<HTML>";
        str += "<b>" + " " + "</b>";
        str += "<table cellspacing=1 cellpadding=1 border=1>";
        str += "<tr> </tr>";

        str += "<tr><td><b align=left>Offset</b></td><td><b align=left>  Field  </b>
                </td><td><b align=left>  Value  </b></td>
                </tr>";

        #wLength
        str += "<tr>";
        str += FormatEx( "<td align=left>%d</td>", 0);
        str += Format( "<td align=left>%s</td>", "wLength");
        str += Format( "<td align=left><font color=#0000FF>0x%02X</font></td>", wLength );
        str += "</tr>";

        #bmNtbFormatsSupported
        str += "<tr>";
        str += FormatEx( "<td align=left>%d</td>", 2);
        str += Format( "<td align=left>%s</td>", "bmNtbFormatsSupported");
        str += Format( "<td align=left><font color=#0000FF>0x%02X</font></td>", bmNtbFormatsSupported );
        str += "</tr>";

        #dwNtbInMaxSize
        str += "<tr>";
        str += FormatEx( "<td align=left>%d</td>", 4);
        str += Format( "<td align=left>%s</td>", "dwNtbInMaxSize");
        str += Format( "<td align=left><font color=#0000FF>0x%02X</font></td>", dwNtbInMaxSize );
        str += "</tr>";

        #wNdpInDivisor
        str += "<tr>";
        str += FormatEx( "<td align=left>%d</td>", 8);
        str += Format( "<td align=left>%s</td>", "wNdpInDivisor");
        str += Format( "<td align=left><font color=#0000FF>0x%02X</font></td>", wNdpInDivisor );
        str += "</tr>";

        #wNdpInPayloadRemainder
        str += "<tr>";
        str += FormatEx( "<td align=left>%d</td>", 10);
        str += Format( "<td align=left>%s</td>", "wNdpInPayloadRemainder");
        str += Format( "<td align=left><font color=#0000FF>0x%02X</font></td>",
                    wNdpInPayloadRemainder );
        str += "</tr>";

        #wNdpInAlignment
        str += "<tr>";
        str += FormatEx( "<td align=left>%d</td>", 12);
        str += Format( "<td align=left>%s</td>", "wNdpInAlignment");
        str += Format( "<td align=left><font color=#0000FF>0x%02X</font></td>", wNdpInAlignment );
        str += "</tr>";

        #reserved1
        str += "<tr>";
        str += FormatEx( "<td align=left>%d</td>", 14);
        str += Format( "<td align=left>%s</td>", "reserved");
        str += Format( "<td align=left><font color=#0000FF>0x%02X</font></td>", reserved1 );
        str += "</tr>";

        #dwNtbOutMaxSize
        str += "<tr>";
        str += FormatEx( "<td align=left>%d</td>", 16);
        str += Format( "<td align=left>%s</td>", "dwNtbOutMaxSize");
        str += Format( "<td align=left><font color=#0000FF>0x%02X</font></td>", dwNtbOutMaxSize );
        str += "</tr>";

        #wNdpOutDivisor
        str += "<tr>";
        str += FormatEx( "<td align=left>%d</td>", 20);
        str += Format( "<td align=left>%s</td>", "wNdpOutDivisor");
        str += Format( "<td align=left><font color=#0000FF>0x%02X</font></td>", wNdpOutDivisor );
        str += "</tr>";

        #wNdpOutPayloadRemainder
        str += "<tr>";
        str += FormatEx( "<td align=left>%d</td>", 22);
        str += Format( "<td align=left>%s</td>", "wNdpOutPayloadRemainder");
        str += Format( "<td align=left><font color=#0000FF>0x%02X</font></td>",
                        wNdpOutPayloadRemainder );
        str += "</tr>";

        #wNdpOutAlignment
        str += "<tr>";
        str += FormatEx( "<td align=left>%d</td>", 24);
        str += Format( "<td align=left>%s</td>", "wNdpOutAlignment");
        str += Format( "<td align=left><font color=#0000FF>0x%02X</font></td>", wNdpOutAlignment );
        str += "</tr>";

        #reserved2
        str += "<tr>";
        str += FormatEx( "<td align=left>%d</td>", 26);
        str += Format( "<td align=left>%s</td>", "reserved");
        str += Format( "<td align=left><font color=#0000FF>0x%02X</font></td>", reserved2 );
        str += "</tr>";


        str += "</table></HTML>";
    }

    LittleEndian = save_endian;
    return str;
}

#*******************************************************************************
# RESERVED_NOTIFICATION : 
#                 This request is used for all unknown requests
# bmRequestType : Ignored
# bRequest      : Out of Range
# wValue        : Ignored
# wIndex        : Ignored
# wLength       : Ignored
# Data          : Ignored
#*******************************************************************************
RESERVED_NOTIFICATION()
{
    #AddExtraBytesPayloadCell(in.DataLength - 2);
    #out.Decoded = in.DataLength;
	RESERVED();
}


#*******************************************************************************
# NETWORK_CONNECTION : 
#                 This notification allows the device to notify the host about 
#                 network connection status
# bmRequestType : 0xA1
# bRequest      : 0x00
# wValue        : 0x0000
# wIndex        : Interface
# wLength       : 0x0000
# Data          : None
#*******************************************************************************
# start NETWORK_CONNECTION
NETWORK_CONNECTION()
{
    wValue   = NextDataWord_();
    if (wValue == 0)
        text = "Disconnect";
    else if (wValue == 1)
        text = "Connect";
    else
        text = "UNKNOWN";
    if (wValue == 0 || wValue == 1)
        AddPayLoadCell("wValue", text, Format("wValue = 0x%04X", wValue), FieldColor, [_TABULARCELL, CELL_WVALUE, "TEXT_CAPTION"]);
    else
    {
        err_tooltip = Format("Unknown wValue (0x%04X)! ", wValue);
        AddPayLoadCell("wValue", Format("0x%04X", wValue), AddErrorTooltip(), _ERROR, [_TABULARCELL, CELL_WVALUE, "TEXT_CAPTION"]);        
    }
    wIndex   = NextDataWord_();
    FieldColor = wIndexColor;
    if (bmRequestType == 0xA1 )
    {
        AddPayLoadCell("wIndex", Format("Interface %d", wIndex), "Interface ID");
    }
    else
    {
        err_tooltip = Format("Unknown bmRequestType (0x%02X)! ", bmRequestType);
        AddPayLoadCell("wIndex", Format("0x%04X", wIndex), AddErrorTooltip(), _ERROR);        
    }
    wLength  = NextDataWord_();
    FieldColor = wLengthColor;
    if (wLength == 0)
    {
        isError = null;
    }
    else
    {
        isError = _ERROR;
    }
    AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data", isError);
    out.Decoded = 8;
/*
    if (wLength == 0)
    {
        
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data");
        out.Decoded = 8;
    }
    else
    {
        err_tooltip = "Illegal wLength Value" ;
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
            out.Decoded = 8;
    }
    */
}
#end NETWORK_CONNECTION

#*******************************************************************************
# RESPONSE_AVAILABLE : This notification allows the device to notify the host 
#                      that a response is available. This response can be retrieved 
#                      with a subsequent GetEncapsulated Response request
# bmRequestType : 0xA1
# bRequest      : 0x01
# wValue        : 0x0000
# wIndex        : Interface
# wLength       : 0x0000
# Data          : None
#*******************************************************************************
# start RESPONSE_AVAILABLE
RESPONSE_AVAILABLE()
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
    FieldColor = wIndexColor;
    if (bmRequestType == 0xA1 )
    {
        AddPayLoadCell("wIndex", Format("Interface %d", wIndex), "Interface ID");
    }
    else
    {
        err_tooltip = Format("Unknown bmRequestType (0x%02X)! ", bmRequestType);
        AddPayLoadCell("wIndex", Format("0x%04X", wIndex), AddErrorTooltip(), _ERROR);        
    }
    wLength  = NextDataWord_();
    FieldColor = wLengthColor;
    if (wLength == 0)
    {
        isError = null;
    }
    else
    {
        isError = _ERROR;
    }
    AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data", isError);
    out.Decoded = 8;
/*
    if (wLength == 0)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data");
        out.Decoded = 8;
    }
    else
    {
        err_tooltip = "Illegal wLength Value" ;
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
            out.Decoded = 8;
    }
    */
}
# end RESPONSE_AVAILABLE
      
#*******************************************************************************
# AUX_JACK_HOOK_STATE : 
# This notification indicates the loop has changed on the 
# auxilary phone interface of the USB device.
# bmRequestType : 0xA1
# bRequest      : 0x08
# wValue        : On Hook/Off Hook
# wIndex        : Interface
# wLength       : 0x0000
# Data          : None
#*******************************************************************************
# start AUX_JACK_HOOK_STATE
AUX_JACK_HOOK_STATE()
{
    wValue   = NextDataWord_();
    if (wValue == 0)
        text = "0 - On hook";
    else if (wValue == 1)
        text = "1 - Off hook";
    else
        text = "UNKNOWN";
    if (wValue == 0 || wValue == 1)
        AddPayLoadCell("wValue", text, Format("wValue = 0x%04X", wValue), FieldColor, [_TABULARCELL, CELL_WVALUE, "TEXT_CAPTION"]);
    else
    {
        err_tooltip = Format("Unknown wValue (0x%04X)! ", wValue);
        AddPayLoadCell("wIndex", Format("0x%04X", wIndex), AddErrorTooltip(), _ERROR, [_TABULARCELL, CELL_WVALUE, "TEXT_CAPTION"]);        
    }
    wIndex   = NextDataWord_();
    FieldColor = wIndexColor;
    if (bmRequestType == 0xA1 )
    {
        AddPayLoadCell("wIndex", Format("Interface %d", wIndex), "Interface ID");
    }
    else
    {
        err_tooltip = Format("Unknown bmRequestType (0x%02X)! ", bmRequestType);
        AddPayLoadCell("wIndex", Format("0x%04X", wIndex), AddErrorTooltip(), _ERROR);        
    }
    wLength  = NextDataWord_();
    FieldColor = wLengthColor;
    if (wLength == 0)
    {
        isError = null;
    }
    else
    {
        isError = _ERROR;
    }
    AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data", isError);
    out.Decoded = 8;
/*
    if (wLength == 0)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data");
        out.Decoded = 8;
    }
    else
    {
        err_tooltip = "Illegal wLength Value" ;
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
            out.Decoded = 8;
    }
    */
}
# end AUX_JACK_HOOK_STATE
      
#*******************************************************************************
# RING_DETECT   : This notification indicates ring voltage on the POTS line 
#                 interface of the USB device
# bmRequestType : 0xA1
# bRequest      : 0x09
# wValue        : 0x0000
# wIndex        : Interface
# wLength       : 0x0000
# Data          : None
#*******************************************************************************
# start RING_DETECT
RING_DETECT()
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
    FieldColor = wIndexColor;
    if (bmRequestType == 0xA1 )
    {
        AddPayLoadCell("wIndex", Format("Interface %d", wIndex), "Interface ID");
    }
    else
    {
        err_tooltip = Format("Unknown bmRequestType (0x%02X)! ", bmRequestType);
        AddPayLoadCell("wIndex", Format("0x%04X", wIndex), AddErrorTooltip(), _ERROR);        
    }
    wLength  = NextDataWord_();
    FieldColor = wLengthColor;
    if (wLength == 0)
    {
        isError = null;
    }
    else
    {
        isError = _ERROR;
    }
    AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data", isError);
    out.Decoded = 8;
/*

    if (wLength == 0)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data");
        out.Decoded = 8;
    }
    else
    {
        err_tooltip = "Illegal wLength Value" ;
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
            out.Decoded = 8;
    }
    */
}       
# end RING_DETECT
      
#*******************************************************************************
# SERIAL_STATE  : This notification sends asynchronous notification of UART status
# bmRequestType : 0xA1
# bRequest      : 0x20
# wValue        : 0x0000
# wIndex        : Interface
# wLength       : 0x02
# Data          : UART State bitmap
#*******************************************************************************
# start SERIAL_STATE
SERIAL_STATE()
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
    FieldColor = wIndexColor;
    if (bmRequestType == 0xA1 )
    {
        AddPayLoadCell("wIndex", Format("Interface %d", wIndex), "Interface ID");
    }
    else
    {
        err_tooltip = Format("Unknown bmRequestType (0x%02X)! ", bmRequestType);
        AddPayLoadCell("wIndex", Format("0x%04X", wIndex), AddErrorTooltip(), _ERROR);        
    }
    wLength  = NextDataWord_();
    FieldColor = wLengthColor;
    if (wLength == 2)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Size of line coding structure");
        FieldColor = CurrentDefaultColor;
		rsvdD7 = NextNBits_(1);
        bOverRun = NextNBits_(1);
        if (bOverRun == 1)
            text = "Received data has been discarded dur to overrun in the device";
        else
            text = "Normal, no overrun occurred";
        AddPayLoadCell("Over Run", Format("%X", bOverRun), text);
        bParity = NextNBits_(1);
        if (bParity == 1)
            text = "A Parity error has occurred";
        else
            text = "Normal, no parity errors";
        AddPayLoadCell("Parity", Format("%X", bParity), text);
        bFraming = NextNBits_(1);
        if (bFraming == 1)
            text = "A framing error has occurred";
        else
            text = "Normal, no framing errors";
        AddPayLoadCell("Framing", Format("%X", bFraming), text);
        bRingSignal = NextNBits_(1);
        if (bRingSignal == 1)
            text = "Ring signal detection of the device has been enabled";
        else
            text = "Ring signal detection of the device has been disabled";
        AddPayLoadCell("Ring Sig", Format("%X", bRingSignal), text);
        bBreak = NextNBits_(1);
        if (bBreak == 1)
            text = "Break detection of the device has been enabled";
        else
            text = "Break detection of the device has been disabled";
        AddPayLoadCell("Break", Format("%X", bBreak), text);
        bTxCarrier = NextNBits_(1);
        if (bTxCarrier == 1)
            text = "Transmission Carrier has been enabled";
        else
            text = "Transmission Carrier has been disabled";
        AddPayLoadCell("Trans Carir", Format("%X", bTxCarrier), text);
        bRxCarrier = NextNBits_(1);
        if (bRxCarrier == 1)
            text = "Receiver Carrier has been enabled";
        else
            text = "Receiver Carrier has been disabled";
        AddPayLoadCell("Rcv Carir", Format("%X", bRxCarrier), text);

        out.Decoded = 8 + wLength;
    }
    else
    {
        err_tooltip = "Illegal wLength Value! The length for should be 2";
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        /*
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
        */
            out.Decoded = 8;
    }
}

# end SERIAL_STATE

#*******************************************************************************
# CALL_STATE_CHANGE : This notification indicates a changed has occured to the 
#                 state of a call on the line corresponding to the interface or 
#                 union for the line
# bmRequestType : 0xA1
# bRequest      : 0x28
# wValue        : Call Index and Call change state value
# wIndex        : Interface
# wLength       : Length of Data
# Data          : Additional Information for call state change
#*******************************************************************************
# start CALL_STATE_CHANGE
set CallStateChangeValueSelectorTable = 
[
    [0xFF, "Unknown",       _ERROR  ],
    [0x00, "Reserved",      null    ],
    [0x01, "Idle",          null    ],
    [0x02, "Dialing",       null    ],
    [0x03, "Ringback",      null    ],
    [0x04, "Connected",     null    ],
    [0x05, "Incoming Call", null    ]
];

set CallStateRingbackSelectorTable =
[
    [3, "Reserved"],
    [0, "normal"],
    [1, "busy"  ],
    [2, "fast busy"],
    [255, "Unknown type"]
];

set CallStateConnectedSelectorTable = 
[
    [4, "Reserved"],
    [0, "voice connection"],
    [1, "answering machine connection"],
    [2, "fax machine connection"],
    [3, "data modem connection"],
    [255, "unknown connection type"]
];

set CallStateImcomingSelectorTable = 
[
    [4, "Reserved for future use"],
    [0, "Ringing pattern 1 (default or normal pattern)"],
    [1, "Ringing pattern 2"],
    [2, "Ringing pattern 3"],
    [3, "Ringing pattern 4"]
];

CALL_STATE_CHANGE()
{
    callerIndex = NextNBits_(8);
    VS = "wValue";
    AddBlockPLCell("Call Index", Format("%d", callerIndex), "Caller Index");
    changeValue = NextNBits_(8);
    _row = Find(CallStateChangeValueSelectorTable, changeValue);
    VS = "wValue";
    AddBlockPLCell("Change Value", _row[1], "Call State Change Value", _row[2]);
    wIndex   = NextDataWord_();
    FieldColor = wIndexColor;
    if (bmRequestType == 0xA1 )
    {
        AddPayLoadCell("wIndex", Format("Interface %d", wIndex), "Interface ID");
    }
    else if (bmRequestType == 0xA2)
    {
        AddPayLoadCell("wIndex", Format("Endpoint %d", wIndex), "Endpoint ID");
    }
    else
    {
        err_tooltip = Format("Unknown bmRequestType (0x%02X)! ", bmRequestType);
        AddPayLoadCell("wIndex", Format("0x%04X", wIndex), AddErrorTooltip(), _ERROR);        
    }
    wLength  = NextDataWord_();
    FieldColor = wLengthColor;
    AddPayLoadCell("wLength", Format("%d", wLength), Format("wLength = 0x%04X", wLength));
    FieldColor = CurrentDefaultColor;
    if (changeValue == 3 && wLength == 1)
    {
        stateValue = NextNBits_(8);
        _row = Find(CallStateRingbackSelectorTable, stateValue);
        AddPayLoadCell("Rngbck Tp", Format("%d", stateValue), _row[1]);
        out.Decoded = 8 + wLength;
    }
    else if (changeValue == 4 && wLength == 1)
    {
        stateValue = NextNBits_(8);
        _row = Find(CallStateConnectedSelectorTable, stateValue);
        AddPayLoadCell("Conn Tp", Format("%d", stateValue), _row[1]);
        out.Decoded = 8 + wLength;
    }
    else if (changeValue == 5 && wLength > 4) 
    {
        stateValue = NextNBits_(8);
        _row = Find(CallStateImcomingSelectorTable, stateValue);
        AddPayLoadCell("Rng Ptn", Format("%d", stateValue), _row[1]);
        bytesDecoded = 1;
        size = NextNBits_(8);
        AddPayLoadCell("Tm Str Sz", Format("%d", size), "Size of the string following");
        bytesDecoded ++;
        if (wLength >= bytesDecoded + size)
        {
            text = GetStrFld(size);
            bytesDecoded += size;
            AddPayLoadCell("Tm Str", text, "The time of the incoming call as delivered via caller ID");
            if (wLength >= bytesDecoded + 1)
            {
                size = NextNBits_(8);
                AddPayLoadCell("PN Str Sz", Format("%d", size), "Size of the string following");
                bytesDecoded ++;
                if (wLength >= bytesDecoded + size)
                {
                    text = GetStrFld(size);
                    bytesDecoded += size;
                    AddPayLoadCell("PN Str", text, "The phone number of the incoming call as delivered via caller ID");
                    if (wLength >= bytesDecoded + 1)
                    {
                        size = NextNBits_(8);
                        AddPayLoadCell("Nm Str Sz", Format("%d", size), "Size of the string following");
                        BytesDecoded ++;
                        if (wLength >= bytesDecoded + size)
                        {
                            text = GetStrFld(size);
                            AddPayLoadCell("Nm Str", text, "The name of the calling patry as delivered via caller ID");
                            bytesDecoded += size;
                        }
                    }
                }
            }
        }
        if (wLength > bytesDecoded)
            AddExtraBytesPayloadCell(wLength - bytesDecoded);
        out.Decoded = 8 + wLength;
    }
    else if (wLength == 0)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data");
        out.Decoded = 8 + wLength;
    }
    else
    {
        err_tooltip = "Illegal wLength Value!";
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        /*
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
        */
            out.Decoded = 8;
    }
}
# end CALL_STATE_CHANGE

#*******************************************************************************
# LINE_STATE_CHANGE : This notification identifies that a change has occured to 
#                 the state of the line corresponding to the interface or 
#                 master interface of an union sending the notification message
# bmRequestType : 0xA1
# bRequest      : 0x29
# wValue        : Line State Change Values
# wIndex        : Interface
# wLength       : Length of Data
# Data          : Line State structure
#*******************************************************************************
# start LINE_STATE_CHANGE
set LineStateChangeValueTable =
[
    [0xFFFF, "Unknown", "Unknown Value",        _ERROR],
    [0x0000, "Idle",    "Line has become idle", null  ],
    [0x0001, "Hold",    "Line connected to hold position", null],
    [0x0002, "Off",     "Hook-Switch has gone off hook", null],
    [0x0003, "On",      "Hook-Switch has gone on hook", null]
];
LINE_STATE_CHANGE()
{
    wValue = NextDataWord_();
    _row = Find (LineStateChangeValueTable, wValue);
    AddPayLoadCell("Value", _row[1], _row[2], _row[3]);
    wIndex   = NextDataWord_();
    FieldColor = wIndexColor;
    if (bmRequestType == 0xA1 )
    {
        AddPayLoadCell("wIndex", Format("Interface %d", wIndex), "Interface ID");
    }
    else
    {
        err_tooltip = Format("Unknown bmRequestType (0x%02X)! ", bmRequestType);
        AddPayLoadCell("wIndex", Format("0x%04X", wIndex), AddErrorTooltip(), _ERROR);        
    }
    wLength  = NextDataWord_();
    FieldColor = wLengthColor;
    if (wLength >= 0)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data");
        if (wLength > 0)
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
# end LINE_STATE_CHANGE

#*******************************************************************************
# CONNECTION_SPEED_CHANGE : This notification allows the device to inform the 
#                 host-networking deriver that a change in either the upstream 
#                 or the downstream bit rate of the connection has occured.
# bmRequestType : 0xA1
# bRequest      : 0x2A
# wValue        : 0x00
# wIndex        : Interface
# wLength       : 0x08
# Data          : Connection Speed Change Data Structure
#*******************************************************************************
# start CONNECTION_SPEED_CHANGE
CONNECTION_SPEED_CHANGE()
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
    FieldColor = wIndexColor;
    if (bmRequestType == 0xA1 )
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
    FieldColor = wLengthColor;
    if (wLength == 8)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "Size of line coding structure");
        FieldColor = CurrentDefaultColor;
        USBitRate = NextDataDWord_();
        AddPayLoadCell("DLBitRate", Format("%d bits per second", USBitRate), "Contains the downlink bit rate, as sent on the IN pipe");
        DSBitRate = NextDataDWord_();
        AddPayLoadCell("ULBitRate", Format("%d bits per second", DSBitRate), "Contains the uplink bit rate, as sent on the OUT pipe");
        out.Decoded = 8 + wLength;
    }
    else
    {
        err_tooltip = "Illegal wLength Value! The length for should be 8";
        AddPayLoadCell("wLength", Format("%d", wLength), AddErrorTooltip(), _ERROR);
        /*
        if (wLength > 0)
        {
            AddExtraBytesPayloadCell(wLength);
            out.Decoded = 8 + wLength;
        }
        else
        */
            out.Decoded = 8;
    }
}  
# end CONNECTION_SPEED_CHANGE


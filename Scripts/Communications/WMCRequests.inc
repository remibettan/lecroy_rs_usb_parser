#*******************************************************************************
#  Copyright (c) 2013, LeCroy - All Rights Reserved
#
#  Wireless Mobile Communications request decoder
#
#*******************************************************************************

#------------------------------------------------------------------------------------------
# type,     type name                                                    |
#------------------------------------------------------------------------------------------
set WMCRequestTypeTable = Map(
[   
	[0x60,      "MDLM_SEMANTIC_MODEL_REQUEST"                     ],
    [0x61,      "MDLM_SEMANTIC_MODEL_REQUEST"                     ],
    [0x62,      "MDLM_SEMANTIC_MODEL_REQUEST"                     ],
    [0x63,      "MDLM_SEMANTIC_MODEL_REQUEST"                     ],
    [0x64,      "MDLM_SEMANTIC_MODEL_REQUEST"                     ],
    [0x65,      "MDLM_SEMANTIC_MODEL_REQUEST"                     ],
    [0x66,      "MDLM_SEMANTIC_MODEL_REQUEST"                     ],
    [0x67,      "MDLM_SEMANTIC_MODEL_REQUEST"                     ],
    [0x68,      "MDLM_SEMANTIC_MODEL_REQUEST"                     ],
    [0x69,      "MDLM_SEMANTIC_MODEL_REQUEST"                     ],
    [0x6A,      "MDLM_SEMANTIC_MODEL_REQUEST"                     ],
    [0x6B,      "MDLM_SEMANTIC_MODEL_REQUEST"                     ],
    [0x6C,      "MDLM_SEMANTIC_MODEL_REQUEST"                     ],
    [0x6D,      "MDLM_SEMANTIC_MODEL_REQUEST"                     ],
    [0x6E,      "MDLM_SEMANTIC_MODEL_REQUEST"                     ],
    [0x6F,      "MDLM_SEMANTIC_MODEL_REQUEST"                     ],
    [0x70,      "MDLM_SEMANTIC_MODEL_REQUEST"                     ],
    [0x71,      "MDLM_SEMANTIC_MODEL_REQUEST"                     ],
    [0x72,      "MDLM_SEMANTIC_MODEL_REQUEST"                     ],
    [0x73,      "MDLM_SEMANTIC_MODEL_REQUEST"                     ],
    [0x74,      "MDLM_SEMANTIC_MODEL_REQUEST"                     ],
    [0x75,      "MDLM_SEMANTIC_MODEL_REQUEST"                     ],
    [0x76,      "MDLM_SEMANTIC_MODEL_REQUEST"                     ],
    [0x77,      "MDLM_SEMANTIC_MODEL_REQUEST"                     ],
    [0x78,      "MDLM_SEMANTIC_MODEL_REQUEST"                     ],
    [0x79,      "MDLM_SEMANTIC_MODEL_REQUEST"                     ],
    [0x7A,      "MDLM_SEMANTIC_MODEL_REQUEST"                     ],
    [0x7B,      "MDLM_SEMANTIC_MODEL_REQUEST"                     ],
    [0x7C,      "MDLM_SEMANTIC_MODEL_REQUEST"                     ],
    [0x7D,      "MDLM_SEMANTIC_MODEL_REQUEST"                     ],
    [0x7E,      "MDLM_SEMANTIC_MODEL_REQUEST"                     ],
    [0x7F,      "MDLM_SEMANTIC_MODEL_REQUEST"                     ]
] );

#------------------------------------------------------------------------------------------
# type,     type name                                                    |
#------------------------------------------------------------------------------------------
set WMCNotificationTypeTable = Map(
[
    [0x40,      "MDLM_SEMANTIC_MODEL_NOTIF"],
    [0x41,      "MDLM_SEMANTIC_MODEL_NOTIF"],
    [0x42,      "MDLM_SEMANTIC_MODEL_NOTIF"],
    [0x43,      "MDLM_SEMANTIC_MODEL_NOTIF"],
    [0x44,      "MDLM_SEMANTIC_MODEL_NOTIF"],
    [0x45,      "MDLM_SEMANTIC_MODEL_NOTIF"],
    [0x46,      "MDLM_SEMANTIC_MODEL_NOTIF"],
    [0x47,      "MDLM_SEMANTIC_MODEL_NOTIF"],
    [0x48,      "MDLM_SEMANTIC_MODEL_NOTIF"],
    [0x49,      "MDLM_SEMANTIC_MODEL_NOTIF"],
    [0x4A,      "MDLM_SEMANTIC_MODEL_NOTIF"],
    [0x4B,      "MDLM_SEMANTIC_MODEL_NOTIF"],
    [0x4C,      "MDLM_SEMANTIC_MODEL_NOTIF"],
    [0x4D,      "MDLM_SEMANTIC_MODEL_NOTIF"],
    [0x4E,      "MDLM_SEMANTIC_MODEL_NOTIF"],
    [0x4F,      "MDLM_SEMANTIC_MODEL_NOTIF"],
    [0x50,      "MDLM_SEMANTIC_MODEL_NOTIF"],
    [0x51,      "MDLM_SEMANTIC_MODEL_NOTIF"],
    [0x52,      "MDLM_SEMANTIC_MODEL_NOTIF"],
    [0x53,      "MDLM_SEMANTIC_MODEL_NOTIF"],
    [0x54,      "MDLM_SEMANTIC_MODEL_NOTIF"],
    [0x55,      "MDLM_SEMANTIC_MODEL_NOTIF"],
    [0x56,      "MDLM_SEMANTIC_MODEL_NOTIF"],
    [0x57,      "MDLM_SEMANTIC_MODEL_NOTIF"],
    [0x58,      "MDLM_SEMANTIC_MODEL_NOTIF"],
    [0x59,      "MDLM_SEMANTIC_MODEL_NOTIF"],
    [0x5A,      "MDLM_SEMANTIC_MODEL_NOTIF"],
    [0x5B,      "MDLM_SEMANTIC_MODEL_NOTIF"],
    [0x5C,      "MDLM_SEMANTIC_MODEL_NOTIF"],
    [0x5D,      "MDLM_SEMANTIC_MODEL_NOTIF"],
    [0x5E,      "MDLM_SEMANTIC_MODEL_NOTIF"],
    [0x5F,      "MDLM_SEMANTIC_MODEL_NOTIF"]    
] );


#*******************************************************************************
# MDLM_SEMANTIC_MODEL_REQUEST : This request is an MDLM request. MDLM is part of
#                 the CDC Wireless Mobile Communication Devices spec. Requests
#                 for MDLM are Semantic-Model specific, they are defined by the
#                 model being used by the Interface reported in wIndex.
#                 [Currently no explicit decoding tables available].
#
# bmRequestType : 0x??
# bRequest      : 0x60-0x7F
# wValue        : 0x????
# wIndex        : Interface (????)
# wLength       : 0x????
# Data          : ?
#*******************************************************************************
# start MDLM_SEMANTIC_MODEL_REQUEST
MDLM_SEMANTIC_MODEL_REQUEST()
{
    wValue = NextDataWord_();
    text = "Defined by semantic model of MDLM interface identified by wIndex";
    AddPayLoadCell("wValue", Format("0x%04X",wValue), Format("wValue = 0x%04X\n", wValue) + text, FieldColor, [_TABULARCELL, CELL_WVALUE, "TEXT_CAPTION"]);

    wIndex   = NextDataWord_();
    FieldColor = wIndexColor;
    AddPayLoadCell("wIndex", Format("Interface %d", wIndex), "MDLM Interface");

    wLength  = NextDataWord_();
    FieldColor = wLengthColor;
    if(wLength>0)
        text = "\nData for designated operation as defined\nby the semantic model of the MDLM \ninterface identified by wIndex";
    else
        text = "";

    if(wLength != in.DataLength - 8)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "!!! WARNING !!! \n" + FormatEx("Data Length discrepancy between wLength (%d)\n and actual data in PayLoad (%d)...\n\n",wLength,in.DataLength - 8) + "Length of the data." + text,_ERROR);
    }
    else
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data." + text);

      out.Decoded = 8;
}
# end MDLM_SEMANTIC_MODEL_REQUEST

#*******************************************************************************
# MDLM_SEMANTIC_MODEL_NOTIF : This notification is an MDLM Notification. MDLM is 
#                 part of the CDC Wireless Mobile Communication Devices spec. 
#                 Notifications for MDLM are Semantic-Model specific, they are 
#                 defined by the model being used by the Interface reported in 
#                 wIndex. [Currently no explicit decoding tables available].
# bmRequestType : 0x??
# bRequest      : 0x40-0x5F
# wValue        : 0x????
# wIndex        : Interface (????)
# wLength       : 0x????
# Data          : ?
#*******************************************************************************
# start MDLM_SEMANTIC_MODEL_NOTIF
MDLM_SEMANTIC_MODEL_NOTIF()
{
    wValue = NextDataWord_();
    text = "Defined by semantic model of MDLM interface identified by wIndex";
    AddPayLoadCell("wValue", Format("0x%04X",wValue), Format("wValue = 0x%04X\n", wValue) + text, FieldColor, [_TABULARCELL, CELL_WVALUE, "TEXT_CAPTION"]);

    wIndex   = NextDataWord_();
    FieldColor = wIndexColor;
    AddPayLoadCell("wIndex", Format("Interface %d", wIndex), "MDLM Interface");
    
    wLength  = NextDataWord_();
    FieldColor = wLengthColor;
    if(wLength>0)
        text = "\nData for designated operation as defined\nby the semantic model of the MDLM \ninterface identified by wIndex";
    else
        text = "";
    
    if(wLength != in.DataLength - 8)
    {
        AddPayLoadCell("wLength", Format("%d", wLength), "!!! WARNING !!! \n" + FormatEx("Data Length discrepancy between wLength (%d)\n and actual data in PayLoad (%d)...\n\n",wLength,in.DataLength - 8) + "Length of the data." + text,_ERROR);
    }
    else
        AddPayLoadCell("wLength", Format("%d", wLength), "Length of the data." + text);
    out.Decoded = 8;  
}
# end MDLM_SEMANTIC_MODEL_NOTIF

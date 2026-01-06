
#########################################################
#   Copyright (c) 2005, LeCroy - All Rights Reserved    #
#   Printer_Req.inc                                     #
#########################################################

const Tabular_Def_Table = Map( 
[   
    #-----------------------------------------------------------------------------------------------------
    #       id            ,      colId                          , 		containerCellId
    #-----------------------------------------------------------------------------------------------------
    [ CELL_REQUEST        , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE   , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ CELL_WVALUE         , TABULAR_SCRIPT_COLUMN_ID_NONE      , TABULAR_SCRIPT_CONTAINER_CELL_ID_MISC ]
] );


set PrinterClassReqType = 
[
    [0x03, "UNKNOWN_REQ"    ],
    [0x00, "GET_DEVICE_ID"  ], # bmRequestType = A1
    [0x01, "GET_PORT_STATUS"], # bmRequestType = A1
    [0x02, "SOFT_RESET"     ]  # bmRequestType = 21
];




PrinterClassRequest ()
{
    
    FieldColor = RequestDataFieldColor;
    CurrentIndex = 0;
    CurrentFldInit();
    
    if (in.DataLength < 6) # we need at least to have wValue + wIndex + wLength.
        return 0;

    bReqType = GetDataByte(CurrentIndex); CurrentIndex = CurrentIndex + sizeOf_b;
    _row = Find (PrinterClassReqType, GetDataByte(CurrentIndex)); CurrentIndex = CurrentIndex + sizeOf_b;
    
    bRequest = _row[1];

    if (bRequest == "Reserved")
    {
        AddPayLoadCell("bReqType", Format("Error: 0x%02X", bReqType), "Reserved bRequest", _ERROR);  
        return 0;
    }
      
    AddCaptionCell("bRequest", bRequest , Format("bRequest HexVal: 0x%04X", _row[0]), FieldColor, [_TABULARCELL, CELL_REQUEST]);   
        
    return Call(bRequest);
}



GET_DEVICE_ID ()
{
    if (bReqType != 0xA1)
    {
        AddPayLoadCell("bReqType", Format("Error: 0x%02X", bReqType), "Expected bRequestType 0xA1", _ERROR);
        return 0;
    }
    wValue      = GetDataWord(CurrentIndex); CurrentIndex = CurrentIndex + sizeOf_w;             
    AddSimplePLCell( "wValue" , Format ("0x%04X", wValue), "Config Index", FieldColor, [_TABULARCELL, CELL_WVALUE, "TEXT_CAPTION"]);    
    wIndex   = GetDataWord(CurrentIndex); CurrentIndex = CurrentIndex + sizeOf_w;
    AddSimplePLCell( "wIndex" , Format ("0x%04X", wIndex) , "Interface");
    
    wLength = GetDataWord(CurrentIndex); CurrentIndex = CurrentIndex + sizeOf_w;
    AddSimplePLCell( "wLength" , Format ("0x%04X", wLength) , "Maximum Length");
    
    if( DataAvailable(CurrentIndex) >0)
    {
        actualLen = DataAvailable(CurrentIndex);
        Data  = Format("0x%02X ", GetDataByte (CurrentIndex)); CurrentIndex = CurrentIndex + sizeOf_b;
        for ( i = 1; i < actualLen ; i ++ )
        {
            Data += Format("%02X "  , GetDataByte(CurrentIndex));
            CurrentIndex = CurrentIndex + sizeOf_b;
        }
        SetFieldOffsetLen( GetBitOffset(), actualLen * 8);
        AddSimplePLCell ("1284 Device ID",Data, "IEEE 1284 device ID string.");
    }
    else
    {
        err_tooltip = "No data for device ID available";
        AddSimplePLCell ("Data", "No data", err_tooltip , _ERROR);
    }
        
return CurrentIndex;    
}

GET_PORT_STATUS ()
{
    if (bReqType != 0xA1)
    {
        AddPayLoadCell("bReqType", Format("Error: 0x%02X", bReqType), "Expected bRequestType 0xA1", _ERROR);
        return 0;
    }
    wValue      = GetDataWord(CurrentIndex); CurrentIndex = CurrentIndex + sizeOf_w;             
    if (wValue == 0x0)
        AddSimplePLCell( "wValue" , Format ("0x%04X", wValue), "Zero", FieldColor, [_TABULARCELL, CELL_WVALUE, "TEXT_CAPTION"]);
    else
        AddSimplePLCell( "wValue" , Format ("0x%04X", wValue), "Should be zero", _ERROR, FieldColor, [_TABULARCELL, CELL_WVALUE, "TEXT_CAPTION"]);

    wIndex   = GetDataWord(CurrentIndex); CurrentIndex = CurrentIndex + sizeOf_w;
    AddSimplePLCell( "wIndex" , Format ("0x%04X", wIndex) , "Interface");

    wLength = GetDataWord(CurrentIndex); CurrentIndex = CurrentIndex + sizeOf_w;
    if (wLength != 0x01)  AddSimplePLCell( "wLength" , Format ("0x%04X", wLength), "Should be one", _ERROR);
    else AddSimplePLCell( "wLength" , Format ("0x%04X", wLength) , "One");

    Data   = GetDataByte(CurrentIndex); CurrentIndex = CurrentIndex + sizeOf_b;
    Status = (Data & 0x3F) >> 3;
    tooltip = "Port Status:";
    tooltip += Format ("Paper Empty %1X, Select %1X, Not Error %1X", (Status & 0x4), (Status & 0x2), (Status & 0x1));
    AddSimplePLCell( "BYTE" , Format ("0x%04X", Data) , tooltip);

return CurrentIndex;    
}

SOFT_RESET ()
{
    if (bReqType != 0x21)
    {
        AddPayLoadCell("bReqType", Format("Error: 0x%02X", bReqType), "Expected bRequestType 0x21", _ERROR);
        return 0;
    }
    wValue      = GetDataWord(CurrentIndex); CurrentIndex = CurrentIndex + sizeOf_w;             
    if (wValue == 0x0)
        AddSimplePLCell( "wValue" , Format ("0x%04X", wValue), "Zero", FieldColor, [_TABULARCELL, CELL_WVALUE, "TEXT_CAPTION"]);
    else
        AddSimplePLCell( "wValue" , Format ("0x%04X", wValue), "Should be zero", _ERROR, FieldColor, [_TABULARCELL, CELL_WVALUE, "TEXT_CAPTION"]);

    wIndex   = GetDataWord(CurrentIndex); CurrentIndex = CurrentIndex + sizeOf_w;
    AddSimplePLCell( "wIndex" , Format ("0x%04X", wIndex) , "Interface");

return CurrentIndex;    
}
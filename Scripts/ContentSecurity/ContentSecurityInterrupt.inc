#*******************************************************************************
#
#  FILENAME: ContentSecurityInterrupt.inc
#
#  Copyright (c) 2008, LeCroy - All Rights Reserved
#
#  DESCRIPTION
#    This is the Interrupt Endpoint Message Include file for Content Security
#      Device Class (CSDC) Interrupt Messages.
#    This file is prepared as per the Specification Revision 1.0.
#    This file is prepared as per the Devices Specification for the Content
#      Security Device Class.
#
#  REVISION HISTORY
#    03/01/2008 Created. - RK and JC
#
#*******************************************************************************

const Tabular_Def_Table = Map( 
[   
    #-----------------------------------------------------------------------------------------------------
    #       id                  ,      colId                          , 		containerCellId
    #-----------------------------------------------------------------------------------------------------
    [ CELL_CSDC_NOTIFICATION    , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE   , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ CELL_CSDC_BDATA           , TABULAR_SCRIPT_COLUMN_ID_NONE      , TABULAR_SCRIPT_CONTAINER_CELL_ID_MISC ]
    
] );

# Need to have UsbCommon.inc and CATCScriptAPI.inc included in calling file.

# User can select the colors for the fields he chooses
set CSDCColor           = 0x85CC9A;
set CSDC_CaptionColor   = 0x875476;

set RestoreBitCurrentFieldOffset = 0;    #Temp Variables to store a restore value
set RestoreBitCurrentFieldLength = 0;

#Interrupt Messages
set InterruptMesgTypeTable =[
    [ 0x00, "UNDEFINED", "UNDEFINED", "UNDEFINED Notification (0x00)"],
    [ 0x01, "CHANGE_CHANNEL_SETTINGS", "CHANGE_CHANNEL_SETTINGS", "CHANGE CHANNEL SETTINGS Notification (0x01)"]
];

# Need to define InterruptDescriptionString in calling file for AddCaptionCell().
ProcessData()
{
    CommonDecoderInit();        # Initialization of SRP common global variables [found in CATCScriptAPI.inc]

    SetCellColor(CSDC_CaptionColor);
    AddCaptionCell( "ContentSecurity", "CSDC", InterruptDescriptionString , _MONOCOLOR );  # Will allow for the expansion of certain fields

    SetCellColor(CSDCColor);

    AddSeparator();

    FullyDecoded = 1;
    out.Decoded  = 0;           # Nothing has been decoded yet

    if( in.DataLength > 0 )
    {
        if( in.DataLength > 3 )
        {
            bLength       = NextNBits_(8);
            bChannel      = NextNBits_(8);
            bNotification = NextNBits_(8);
            bData         = NextNBits_(8);

            bNotification_row = Find( InterruptMesgTypeTable, bNotification );

            if( bNotification_row[0] == 0 )
            {
                if( ( bNotification > 0x01 ) && ( bNotification < 0x80 ) )
                {
                    AddShortDataHeader( "RESERVED FOR FUTURE EXTENSION Notification" );
                }
                else if( bNotification > 0x7F )
                {
                    AddShortDataHeader( Format( "CSM DEFINED Notification (0x%02X)", bNotification ) );
                }
                else
                {
                    AddShortDataHeader( bNotification_row[3] );
                }
            }
            else
                AddShortDataHeader( bNotification_row[3] );

            SetFieldOffsetLen_CSDC( 8, 8 );
            if( bLength != in.DataLength )
            {
                SetCellColor(WarningColor);
                AddPayLoadCell( "bLength", Format( "%d", bLength ), Format( "***ERROR***\nbLength DOES NOT MATCH length\nof data found in PayLoad!\nWill attempt to decode...\n\nHeader offset Bytes 1-4.\n bLength = 0x%02X", bLength ), _ERROR );
                RestoreCellColor();
            }
            else if( SimpleShowItem() )
                AddPayLoadCell( "bLength", Format( "%d", bLength ), "Byte length of this notification." );

            RestoreFieldOffsetLen_CSDC();

            SetFieldOffsetLen_CSDC( 16, 8 );
            AddPayLoadCell( "bChannel", Format( "%d", bChannel ), "ID of Channel that generated\nthis notification." );
            RestoreFieldOffsetLen_CSDC();

            SetFieldOffsetLen_CSDC( 24, 8 );
            if( bNotification_row[0] == 0 )
            {
                if( ( bNotification > 0x01 ) && ( bNotification < 0x80 ) )
                {
                    SetCellColor(WarningColor);
                    AddPayLoadCell( "bNotification", "RESERVED", FormatEx( "!!!WARNING!!! - RESERVED FOR FUTURE EXTENSION (0x%02X)\nUnknown Content Security Interface Notification Format.\nbNotification = 0x%02X", bNotification, bNotification )
                                , _ERROR, [_TABULARCELL, CELL_CSDC_NOTIFICATION, "TEXT_CAPTION"] );
                    RestoreCellColor();
                }
                else if( bNotification > 0x7F )
                {
                    AddPayLoadCell( "bNotification", Format( "%d", bNotification ), Format( "CSM DEFINED (0x%02X).", bNotification )
                    , FieldColor, [_TABULARCELL, CELL_CSDC_NOTIFICATION, "TEXT_CAPTION"] );
                }
                else
                {
                    SetCellColor(WarningColor);
                    AddPayLoadCell( "bNotification", bNotification_row[2], "!!!WARNING!!!\n" + bNotification_row[3], _ERROR
                        , [_TABULARCELL, CELL_CSDC_NOTIFICATION, "TEXT_CAPTION"] );
                    RestoreCellColor();
                }
            }
            else
                AddPayLoadCell( "bNotification", bNotification_row[2], bNotification_row[3], FieldColor, [_TABULARCELL, CELL_CSDC_NOTIFICATION, "TEXT_CAPTION"] );

            RestoreFieldOffsetLen_CSDC();

            AddPayLoadCell( "bData", Format( "%d", bData ) , "The CSM number that this USB device wants\nactivated on the given bChannel."
                        , FieldColor, [_TABULARCELL, CELL_CSDC_BDATA, "TEXT_CAPTION"]);

            AddSeparator();
            out.Decoded = 4;
        }
        else
        {
            str = "0x";
            str2= "Byte Data:";
            for( i = 0; i < in.DataLength; i++ )
            {
                tmp   = Format("%02X", NextNBits_(8));
                str  += tmp;
                str2 += " " + tmp;
            }
            #IncFieldOffset( in.DataLength * 8);
            FieldColor = RED;
            AddPayLoadCell( "PayLoad Too Short", str, Format( "***ERROR*** \nExpecting at least 4 bytes.\nFound only %d bytes...\n\n" + str2, in.DataLength ), _ERROR );
            out.Decoded = in.DataLength;
        }

        if( out.Decoded != in.DataLength )
            FullyDecoded = 0;

        out.State = "Complete";
        return Complete();
    }
    else
    {
        FieldColor = RED;
        AddPayLoadCell( "EMPTY PAYLOAD", "**EMPTY**", "No Data!", _ERROR );
        AddSeparator();
        return Complete();
    }
}

#Helper Functions

SetFieldOffsetLen_CSDC( offset, len )
{
    RestoreBitCurrentFieldOffset = BitCurrentFieldOffset;
    RestoreBitCurrentFieldLength = BitCurrentFieldLength;
    BitCurrentFieldOffset = offset;
    BitCurrentFieldLength = len;
}

RestoreFieldOffsetLen_CSDC()
{
    BitCurrentFieldOffset = RestoreBitCurrentFieldOffset;
    BitCurrentFieldLength = RestoreBitCurrentFieldLength;
}

####################################################################################
#                       USBTracer specific caption cell                            #
####################################################################################

AddSpecCaptionCell( caption, text, tooltip, FieldColor, addparam, addparam1, addparam2 )
{
    AddCell( caption, text, tooltip, FieldColor, _USBBULK_HEADER, addparam, addparam1, addparam2 );
    return 1;
}
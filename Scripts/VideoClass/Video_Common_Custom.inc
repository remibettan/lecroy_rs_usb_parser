set ModuleType     = "DataBlock Decoder";

const ErrorColor       = 0x0000FF;

const MaxShowDataBlockSize = 12;
set CurrentPayloadColor = 0;


const Tabular_Def_Table = Map( 
[   
    #----------------------------------------------------------------------------------------------------------------------
    #       id                     ,      colId                          , 		containerCellId
    #----------------------------------------------------------------------------------------------------------------------
    [ CELL_VIDEO_REQUEST           , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE   , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ CELL_VIDEO_CONTROLL_SELECTOR , TABULAR_SCRIPT_COLUMN_ID_NONE      , TABULAR_SCRIPT_CONTAINER_CELL_ID_MISC ],
    [ CELL_REQUEST                 , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE   , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ CELL_WVALUE                  , TABULAR_SCRIPT_COLUMN_ID_NONE      , TABULAR_SCRIPT_CONTAINER_CELL_ID_MISC ],
    [ CELL_VIDEO_STATUS_TYPE       , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE   , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ CELL_VIDEO_EVENT             , TABULAR_SCRIPT_COLUMN_ID_NONE      , TABULAR_SCRIPT_CONTAINER_CELL_ID_MISC ]
] );

set bmHeaderInfoBitmapTable =
[
                   [  0, "Frame ID         " ],
                   [  1, "End of Frame     " ],
                   [  2, "Presentation Time" ],
                   [  3, "Source Clock     " ],
                   [  4, "Reserved         " ],
                   [  5, "Still Image      " ],
                   [  6, "Error            " ], 
                   [  7, "End of Header    " ]
 ];

DoProcessDataFirstPart()
{
    FullyDecoded = 1;
    ProcessDataInit();   #Doesn't Exist, not in use anymore
    
    
    Speed        = GetDecoderHeaderByte(0);    
    UsbSpecLevel = GetDecoderHeaderByte(1);
    out.Decoded = 0;    

    AddDecodedTextHeader(); #Exists, but commented out, not in use anymore
    AddSeparator();
    FieldColor = VideoCaptionColor;
    AddCaptionCell("Video","Class","In order to view comments in text field, user must expand this caption cell",_MONOCOLOR);  # will allow for the expansion of certain fields
    AddSeparator();
}





# must set CurrentPayloadColor before calling.
DoVideoPayloadHeader()
{
    if (in.DataLength == 0)
    {
       FieldColor = CurrentPayloadColor;
       AddPayLoadCell("No", "Data", "No Header or Data Recieved in this transaction");
       AddSeparator();
       out.Decoded = 0;
       return (1);
    }
    
    AddDecodedTextHeader();
    AddSeparator();
    bHeaderLength = GetDataByte(0);
    FieldColor = CurrentPayloadColor;
    
    out.Decoded = 1;
    if (bHeaderLength < 2)
    {
        FieldColor = ErrorColor;
        AddPayLoadCell("bHeaderLength", Format ("0x%02X", bHeaderLength), "ERROR: bHeaderLength can NOT be less than 2");
        FieldColor = CurrentPayloadColor;
    }
    else if (bHeaderLength > 16)
    {
        FieldColor = ErrorColor;
        AddPayLoadCell("bHeaderLength", Format ("0x%02X", bHeaderLength), "ERROR: bHeaderLength can NOT be greater than 16");
        FieldColor = CurrentPayloadColor;
    }
    else
    {
        bmHeaderInfo = GetDataByte(1);
        if (in.Expanded)
        {
            AddPayLoadCell("FrmId", Format ("%d", (bmHeaderInfo & 0x01)), Format("Frame Id:  Toggles with new frame.   bmHeaderInfo = 0x%02X", bmHeaderInfo));
            if ((bmHeaderInfo >> 1) & 0x01)
            {
                AddPayLoadCell("EOFrm", "Yes", Format("End of Frame: The following payload data marks the end of the current\nvideo or still image frame.   bmHeaderInfo = 0x%02X", bmHeaderInfo));
            }
            else
            {
                AddPayLoadCell("EOFrm", "No", Format("End of Frame: The following payload is NOT the end of the current\nvideo or still image frame.   bmHeaderInfo = 0x%02X", bmHeaderInfo));
            }
            
            if ((bmHeaderInfo >> 5) & 0x01)
            {
                AddPayLoadCell("Stl Img", "Yes", Format("Still Image: The following data is part of a still image frame.   bmHeaderInfo = 0x%02X", bmHeaderInfo));
            }
            else
            {
                AddPayLoadCell("Stl Img", "No", Format("Still Image: The following data is NOT part of a still image frame.   bmHeaderInfo = 0x%02X", bmHeaderInfo));
            }
            
            if ((bmHeaderInfo >> 6) & 0x01)
            {
                FieldColor = ErrorColor;
                AddPayLoadCell("Error", "Yes", Format("Error found in the video or still image transmission for this payload.   bmHeaderInfo = 0x%02X", bmHeaderInfo));
                FieldColor = CurrentPayloadColor;
            }
            else
            {
                AddPayLoadCell("Error", "No", Format("No Error in video or still image transmission for this payload.   bmHeaderInfo = 0x%02X", bmHeaderInfo));
            }
            
            AddPayLoadCell("EOH", Format ("%d", ((bmHeaderInfo >> 7) & 0x01)), Format("End of Header: If = 1, this is the last header group in the packet.   bmHeaderInfo = 0x%02X", bmHeaderInfo));
        }
        else
        {
             AddPayLoadCell("bmHeaderInfo", Format ("0x%02X", bmHeaderInfo), 
                 ToBitDecode(bmHeaderInfoBitmapTable, bmHeaderInfo, ""));
        }
        out.Decoded = 2;
        
        ptOffset = 0;
        
        
        if (bmHeaderInfo & 4)
        {
            dwPresentationTime = GetDataLong(2);
            ptOffset = 4; 
            AddPayLoadCell("dwPresentationTime", Format ("0x%08X", dwPresentationTime), Format ("Decimal val: %u", dwPresentationTime));
            out.Decoded += 4;
        }
        
        if (bmHeaderInfo & 8)
        {
            sourceClock = GetDataLong(2+ptOffset);
            frameCount  = GetDataWord(6+ptOffset);
            AddPayLoadCell("Frame:Clock", 
                Format ("0x%04X:", frameCount) +  Format ("0x%08X", sourceClock), 
                Format ("scrSourceClock     Decimal vals:  Frame:%u  ", frameCount) +  Format ("Clock:%u", sourceClock));
			AddSeparator();
			if (bmHeaderInfo & 2)
			{
				AddCell("Bytes Transferred", Format ("%u", in.DataLength), null, 0x000080);
			}
			else
			{
				AddCell("Bytes Transferred", Format ("%u", in.DataLength), Format ("Payload size (w/o Header): %u bytes", in.DataLength - bHeaderLength), 0x000080);
			}
            out.Decoded = in.DataLength ;
        }
    }
           
    AddSeparator();
}



####################################################################################
#                       USBTracer specific caption cell                            #
####################################################################################

AddSpecCaptionCell(caption, text, tooltip, FieldColor, addparam, addparam1, addparam2 )
{   
    AddCell(caption, text, tooltip, FieldColor, _USBBULK_HEADER, addparam, addparam1, addparam2 );        
    return 1;        
}

 


#*******************************************************************************
#
#  FILENAME: CDCData.inc
#
#  Copyright (c) 2007, LeCroy - All Rights Reserved
#
#  DESCRIPTION
#    This is an include file for CDC Data Endpoints.
#    To utilize this file, the endpoint decode file(s) including this ProcessData
#      module must define the following variables:
#
#    ProtocolWrapper_FLAG    --  Flag for Class Protocol Wrapping Decoding
#    CommandTypeEncode_FLAG  --  Flag for Command Type Encoding Decoding
#    msg_type                --  Name of Endpoint type (i.e. Bulk-Out or Isoch-In)
#
#  REVISION HISTORY
#    07FEB07 First created -RK-
#
#*******************************************************************************

const Tabular_Def_Table = Map( 
[   
    #-----------------------------------------------------------------------------------------------------
    #       id              ,      colId                        , 		containerCellId
    #-----------------------------------------------------------------------------------------------------
    [ CELL_COMM_CMD_TYPE    , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE  , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ CELL_COMM_COMMAND     , TABULAR_SCRIPT_COLUMN_ID_NONE     , TABULAR_SCRIPT_CONTAINER_CELL_ID_MISC ],
    [ CELL_COMM_WRAPPER_SIZE, TABULAR_SCRIPT_COLUMN_ID_NONE     , TABULAR_SCRIPT_CONTAINER_CELL_ID_MISC ]
      
] );

ProcessData()
{
    NoteAddedFlag = 0;
    CommonDecoderInit();
    FullyDecoded = 1;
    out.Decoded = 0;
    DatLength = in.DataLength;

    FieldColor = 0x5499AC - 10000;
    AddCaptionCell("CDC","DATA",Format("This data payload represents a CDC Data %s message.",msg_type) + FormatEx("\n\nFeatures:\n  Class Protocol Wrapper Enable = %d\n  Command Type Encoding Enable  = %d\n\nThese settings enable/disable the respective decoding of\nthe features.\nTo view any enabled features, the specific payload must\nbe expanded. This is done for the case that data is split\namong different payloads (which might share one wrapper or\ncommand encoding).",ProtocolWrapper_FLAG,CommandTypeEncode_FLAG),_MONOCOLOR);  # Will allow for the expansion of certain fields
    AddSeparator();

/*
    FieldColor = 0x5499AC - 1000;
    AddCell("Decode Options", FormatEx("PW=%d, CTE=%d",ProtocolWrapper_FLAG,CommandTypeEncode_FLAG), FormatEx("Features:\n  Class Protocol Wrapper Enable = %d\n  Command Type Encoding Enable  = %d\n\nThese settings enable/disable the respective\ndecoding of the features.\nTo view any enabled features, the specific\npayload must be expanded. This is done for\nthe case that data is split among different\npayloads (which might share one wrapper or\ncommand encoding).",ProtocolWrapper_FLAG,CommandTypeEncode_FLAG),FieldColor,_MONOCOLOR);
    AddSeparator();
*/

    if(ProtocolWrapper_FLAG)
    {
        if (DatLength == 0)
        {
            AddPLCellMonoNoDlg("NO DATA", "Payload is empy", "EMPTY", _WARNING);
            return Complete();
        }
        else if (DatLength < 4)
        {
            AddPLCellMonoNoDlg("Error", "Illegal Payload", "Nothing is being decoded\nSee 'Data' for Raw Bytes", _ERROR);
            ShowDataBlockReOrder(in.DataLength-out.Decoded);
            return Complete();
        }
        else
        {
            if(SimpleShowItem())
            {
                AddStringToDlg( " *Note", "The data shown here is based on the CDC decode applied. In the case that this payload was not expanded, look at 'Bytes Transferred' for raw data. This view will show the enabled options as decoded even if the payload is not expanded.", "", "", "" );
                NoteAddedFlag = 1;

                FieldColor -= 1000;
                AddCell("PW:","","",FieldColor,_MONOFIELD);

                wWrapperSize = NextDataWord_();
                descr_txt = "Size of wrapper in bytes.";
                AddCell("WrapperSize",Format("%u",wWrapperSize),descr_txt, FieldColor, [_TABULARCELL, CELL_COMM_WRAPPER_SIZE, "TEXT_CAPTION"]);
                AddEntry( (BitCurrentFieldOffset-BitCurrentFieldLength)/8, "WrapperSize", wWrapperSize, 4, descr_txt, 1, 0);
                AddFieldBreak();

                bDstProtocol = NextNBits_(8);
                descr_txt = "Destination protocol ID.";
                AddCell("DstProtocol",Format("0x%02X",bDstProtocol),descr_txt,FieldColor);
                AddEntry( (BitCurrentFieldOffset-BitCurrentFieldLength)/8, "DstProtocol", bDstProtocol, 2, descr_txt, 0, 0);
                AddFieldBreak();

                bSrcProtocol = NextNBits_(8);
                descr_txt = "Source Protocol ID.";
                AddCell("SrcProtocol",Format("0x%02X",bSrcProtocol),descr_txt,FieldColor);
                AddEntry( (BitCurrentFieldOffset-BitCurrentFieldLength)/8, "SrcProtocol", bSrcProtocol, 2, descr_txt, 0, 0);
                AddFieldBreak();

                out.Decoded += 4;
                DatLength -= 4;
                FieldColor += 1000;
                AddSeparator();
            }
        }
    }

    if(DatLength > 0)
    {
        if(CommandTypeEncode_FLAG)
        {
            if(SimpleShowItem())
            {
                if(!NoteAddedFlag)
                {
                    AddStringToDlg( " *Note", "The data shown here is based on the CDC decode applied. In the case that this payload was not expanded, look at 'Bytes Transferred' for raw data. This view will show the enabled options as decoded even if the payload is not expanded.", "", "", "" );
                    NoteAddedFlag = 1;
                }

                FieldColor -= 2000;
                AddCell("CTE:","","",FieldColor,_MONOFIELD);

                bCommand =  NextNBits_(8);
                cmdType_val = bCommand&0x03;        #Bits 1-0;

                cmdType = "";
                cmdDescr = select{
                    cmdType_val == 0    :    {
                                                cmdType = "REQ";
                                                "A REQuest is a command from a higher\nprotocol level to a lower.";
                                             }
                    cmdType_val == 1    :    {
                                                cmdType = "CON";
                                                "A CONfirm is an answer from a lower\nprotocol level to a higher on a\nRequest.";
                                             }
                    cmdType_val == 2    :    {
                                                cmdType = "IND";
                                                "An INDication is a command from a\nlower protocol level to a higher.";
                                             }
                    cmdType_val == 3    :    {
                                                cmdType = "RES";
                                                "A RESsponse is an answer from a\nhigher protocol level to a lower\non an Indication.";
                                             }
                };
                cmdDescr2 = "Bits 1-0 of bCommand: " + ToBitString(cmdType_val,2) + "b";

                AddCell("CmdType",cmdType,cmdDescr2 + "\n\n" + cmdDescr, FieldColor, [_TABULARCELL, CELL_COMM_CMD_TYPE]);

                cmdDescr3 = "Bits 7-2 of bCommand: " + ToBitString(bCommand>>2,6)+ Format("b\n bCommand = 0x%02X",bCommand);
                AddCell("Command",ToBitString(bCommand>>2,6)+"b",cmdDescr3, FieldColor, [_TABULARCELL, CELL_COMM_COMMAND, "TEXT_CAPTION"]);

                AddEntry((BitCurrentFieldOffset-BitCurrentFieldLength)/8, "bCommand",bCommand,2, cmdDescr2 + "<br>&nbsp&nbsp&nbsp&nbsp" + cmdDescr + "<br>&nbsp&nbsp" + cmdDescr3);
                AddFieldBreak();

                out.Decoded += 1;
                DatLength -= 1;
                FieldColor += 2000;
                AddSeparator();
            }
        }

        #ShowDataBlockReOrder(in.DataLength-out.Decoded);
        return Complete();
    }
    else
        return Complete();
}




####################################################################################
#                       USBTracer specific caption cell                            #
####################################################################################

AddSpecCaptionCell(caption, text, tooltip, FieldColor, addparam, addparam1, addparam2 )
{
    AddCell(caption, text, tooltip, FieldColor, _USBBULK_HEADER, addparam, addparam1, addparam2 );
    return 1;
}
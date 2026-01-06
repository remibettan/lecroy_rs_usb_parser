#******************************************************************************
#
#  FILENAME: PersonalHealthcareDataBulk.inc
#
#  Copyright (C) 2008 LeCroy Corporation
#
#  DESCRIPTION
#    This descriptor definition file is supplied by LeCroy.
#    This file defines Personal Healthcare Data Bulk.
#    File version is 1.0.
#       Based on Personal Healthcare Devices Revision 1.0 released November 8, 2007
#
#  REVISION HISTORY
#    01/30/2008 Created. - RK and JC
#
#******************************************************************************

# User can select the colors for the fields he chooses
set PHDCColor         = 0xB016BB; #0xA45A8A; #0x11B066;
set PHDC_CaptionColor = 0xFFAF11;

set aSignature           = 0;
set bNumTransfers        = 0;
set bQoSEncodingVersion  = 0;
set bmLatencyReliability = 0;
set bOpaqueDataSize      = 0;
set bOpaqueData          = 0;

const Tabular_Def_Table = Map( 
[   
    #-----------------------------------------------------------------------------------------------------
    #       id             ,      colId                          , 		containerCellId
    #-----------------------------------------------------------------------------------------------------
    [ CELL_PHC_A_SIGNATURE , TABULAR_SCRIPT_COLUMN_ID_NONE       , TABULAR_SCRIPT_CONTAINER_CELL_ID_MISC ]
    
] );

PHDC_DATA_BULK()
{
    base = Base;

    GetNBits(in.Data, 0, 0);              #Initialize pointer/counter for NextNBits_()

    if (in.DataLength >= 20 )
    {
        aSignature = "0x";
        for(i = 0; i < 16; i++)
        aSignature += Format("%02X", NextNBits_(8));                                #0-127
        AddPayLoadCell( "aSignature", aSignature, Format( "Constant used to give preamble verifiability.\nSet to 16 byte string: \"PhdcQoSSignature\". \naSignature = %s", aSignature ), FieldColor, [_TABULARCELL, CELL_PHC_A_SIGNATURE]);

        bNumTransfers         = NextNBits_(8);                                      #128-135
        if(bNumTransfers == 0)
        {
            SetCellColor(RED);
            AddPayLoadCell( "bNumTransfers", bNumTransfers, "***ERROR*** \nbNumTransfers shall never equal zero!", _ERROR );
            RestoreCellColor();
        }
        else
        {
            AddPayLoadCell( "bNumTransfers", bNumTransfers, Format( "Count of following transfers to\nwhich the QoS setting applies.\nbNumTransfers = %d", bNumTransfers ) );
        }

        bQoSEncodingVersion = NextNBits_(8);                                        #136-143

        if (bQoSEncodingVersion == 1)#& 0x01)
        {
            if( SimpleShowItem() )
                AddPayLoadCell( "bQoSEncodingVersion", bQoSEncodingVersion, FormatEx( "bQoSEncodingVersion = 0x%02X", bQoSEncodingVersion ) );

            bmLatencyReliability = NextNBits_(8);                                   #144-151
            bmLatencyReliability_str  = Format( "0x%02X", bmLatencyReliability );   #144-151

            if ((bmLatencyReliability & 0x40) || (bmLatencyReliability & 0x80) )
                AddPayLoadCell( "bmLatencyReliability", bmLatencyReliability_str, Format("!!!WARNING!!! \nBits 6..7 are reserved and set to 0. \nbmLatencyReliability = %s", bmLatencyReliability_str));
            else if ( bmLatencyReliability & 0x20)
                AddPayLoadCell( "bmLatencyReliability", bmLatencyReliability_str, Format("Bit 5: Very High. Best Latency, reliability bin. \nbmLatencyReliability = %s", bmLatencyReliability_str));
            else if ( bmLatencyReliability & 0x10)
                AddPayLoadCell( "bmLatencyReliability", bmLatencyReliability_str, Format("Bit 4: High. Best Latency, reliability bin. \nbmLatencyReliability = %s", bmLatencyReliability_str));
            else if ( bmLatencyReliability & 0x08)
                AddPayLoadCell( "bmLatencyReliability", bmLatencyReliability_str, Format("Bit 3: Medium. Best Latency, reliability bin. \nbmLatencyReliability = %s", bmLatencyReliability_str));
            else if ( bmLatencyReliability & 0x04)
                AddPayLoadCell( "bmLatencyReliability", bmLatencyReliability_str, Format("Bit 2: Medium. Better Latency, reliability bin. \nbmLatencyReliability = %s", bmLatencyReliability_str));
            else if ( bmLatencyReliability & 0x02)
                AddPayLoadCell( "bmLatencyReliability", bmLatencyReliability_str, Format("Bit 1: Medium. Good Latency, reliability bin. \nbmLatencyReliability = %s", bmLatencyReliability_str));
            else if ( bmLatencyReliability & 0x01)
                AddPayLoadCell( "bmLatencyReliability", bmLatencyReliability_str, Format("Bit 0: Low. Good latency, reliability bin. \nbmLatencyReliability = %s", bmLatencyReliability_str));
            else
            {
                SetCellColor(RED);
                AddPayLoadCell( "bmLatencyReliability", bmLatencyReliability_str, Format("***ERROR*** \nInvalid bmLatencyReliability value.\nbmLatencyReliability = %s", bmLatencyReliability_str), _ERROR);
                RestoreCellColor();
            }

            bOpaqueDataSize = NextNBits_(8);                                        #152-159

            if (bOpaqueDataSize == (in.DataLength - 20))
            {
                AddPayLoadCell( "bOpaqueDataSize", bOpaqueDataSize, Format("Size, in bytes, of opaque QoS data or meta-data.\nbOpaqueDataSize = %d", bOpaqueDataSize ) );
            }
            else
            {
                SetCellColor(WarningColor);
                AddPayLoadCell( "bOpaqueDataSize", bOpaqueDataSize, "!!!WARNING!!!\nOpaqueDataSize does not match with Opaque Data length.", _ERROR );
                RestoreCellColor();
            }

            out.Decoded = 20;
        }
        else
        {
            SetCellColor(RED);
            AddPayLoadCell( "bQoSEncodingVersion", bQoSEncodingVersion, FormatEx( "***ERROR***\nDecoding Aborted. UNKNOWN/INVALID QoS information encoding.\nbQoSEncodingVersion = 0x%02X. Expected 0x01.", bQoSEncodingVersion ), _ERROR);
            RestoreCellColor();
            out.Decoded = 18;
        }

        AddSeparator();

        /*
            if (in.DataLength > 20)
            {
                bOpaqueData = "0x";
                for(i = 0; i < (in.DataLength - 20); i++)
                {
                    bOpaqueData += Format("%02X", NextNBits_(8));   #0-127
                    out.Decoded += 1;
                }

                if( bQoSEncodingVersion == 1) #& 0x01 )
                {
                    AddPayLoadCell( "bOpaqueData", bOpaqueData, Format("Opaque meta-data. \nbOpaqueData = %s", bOpaqueData));
                }
                else
                {
                    SetCellColor(WarningColor);
                    AddPayLoadCell( "bOpaqueData", bOpaqueData, Format("!!!WARNING!!! \nAn invalid bQoSEncodingVersion.  bQ0SEncodingVersion must be 01h. \nbOpaqueData = %s", bOpaqueData));
                    RestoreCellColor();
                }
            }

            AddSeparator();
        */
    }
    else
    {
        AddCell( "ERROR", "Decoding Aborted", "***ERROR***\nShort Payload - Expect at least 20 bytes!" + Format( "\nPayload Length = %d bytes", in.DataLength ), RED, _ERROR );
        AddSeparator();
        out.Decoded = 0;
        FullyDecoded = 0;

        /*
        done = 0;
        if ( in.DataLength >= 16)
        {
            aSignature = "0x";
            for(i = 0; i < 16; i++)
                aSignature += Format("%02X", NextNBits_(8));   #0-127
            SetCellColor(WarningColor);
            AddPayLoadCell( "aSignature", aSignature, Format("!!! WARNING !!! \nShort payload. \nConstant used to give preamble verifiability.  Set to 16 byte string: \"PhdcQoSSignature\". \naSignature = %s",aSignature));
            RestoreCellColor();
        }
        else
        {
            error_string = "!!! ERROR !!! \nShort payload. Decoding Aborted.";
            aSignature = "0x";
            for(i = 0; i < in.DataLength; i++)
                aSignature += Format("%02X", NextNBits_(8));   #0-127
            SetCellColor(WarningColor);
            AddPayLoadCell( "aSignature", aSignature, error_string, RED,_ERROR);
            RestoreCellColor();

            done = 1;
            #AddSeparator();
            out.Decoded=in.DataLength;
            return 0;
        }

        if ( in.DataLength >= 17 && !done)
        {
            bNumTransfers         = NextNBits_(8);        #128-135
            SetCellColor(WarningColor);
            AddPayLoadCell( "bNumTransfers", bNumTransfers, "!!!ERROR!!! \nShort payload.", RED, _ERROR);
            RestoreCellColor();
        }
        else
        {
            error_string += "Short Payload.";
            SetCellColor(WarningColor);
            AddCell("ERROR","Decoding Aborted",error_string,RED,_ERROR);
            RestoreCellColor();
            done = 1;
            AddSeparator();
            out.Decoded=in.DataLength;
            return 0;
        }

        if ( in.DataLength >= 18 && !done)
        {
            bQoSEncodingVersion   = NextNBits_(8);        #136-143
            SetCellColor(WarningColor);
            AddPayLoadCell( "bQoSEncodingVersion", bQoSEncodingVersion, "!!!ERROR!!! \nShort payload.", RED, _ERROR);
            RestoreCellColor();
        }
        else
        {
            error_string += "Short Payload.";
            SetCellColor(WarningColor);
            AddCell("ERROR","Decoding Aborted",error_string,RED,_ERROR);
            RestoreCellColor();
            done = 1;
            AddSeparator();
            out.Decoded=in.DataLength;
            return 0;
        }

        if ( in.DataLength >= 19 && !done)
        {
            bmLatencyReliability  = NextNBits_(8);        #144-151
            SetCellColor(WarningColor);
            AddPayLoadCell( "bmLatencyReliability", bmLatencyReliability, "!!!ERROR!!! \nShort payload.", RED, _ERROR);
            RestoreCellColor();
        }
        else
        {
            error_string += "Short Payload.";
            SetCellColor(WarningColor);
            AddCell("ERROR","Decoding Aborted",error_string,RED,_ERROR);
            RestoreCellColor();
            done = 1;
            AddSeparator();
            out.Decoded=in.DataLength;
            return 0;
        }
        */
    }
}

# Helper Functions

ShowDataBlockReOrder_PHDC( len, no_cells, show_in_collapsed )
{
   # no need to do anything if len = 0 or len < 0
   if( !len )    return 0;
   if( len < 0 ) return 0;

  if( in.PrepareFldsForDlg )
  {
        lenbits = len * 8;
        BitCurrentFieldOffset = BitCurrentFieldOffset + lenbits;
        BitCurrentFieldLength = lenbits;


        str = Format("%d bytes", len);
        PrepareFieldForDlg( "DATA_BLOCK", str,
        "Data Block containing " + str, !no_cells, show_in_collapsed );

        #NextNBitsReOrder( lenbits );
        DataBlockReOrder( len );
  }
  else
  {
        if( !no_cells )
            DataBlockReOrder( len );
        else
            DataBlockReOrder( len );
            #NextNBitsReOrder( lenbits );
  }

  out.Decoded += len;
}

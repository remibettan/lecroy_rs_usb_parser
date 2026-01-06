
set ModuleType              = "DataBlock Decoder";
const ErrorColor            = 0x0000FF;
const ReservedColor         = 0x808080;
const MaxShowDataBlockSize  = 512;
const DARK_COLOR_OFFSET     = 0x202020;


#############################################################################
#                               View Settings                               #
#############################################################################
#
#    In this section user can set up which fields are to be shown and
#    which are to be hidden in expanded and collapsed states.
#    Zero-value everywhere means that fields will not be shown,
#    otherwise means opposite.
#

# -----------------------  Separate Field View Settings ---------------------
# The FIRST value in list-variables defines if the field is to be shown or
# hidden in COLLAPSED state.
# 0 - means the field is to be shown.
# 1 - means the field is to be hidden.
#
# The SECOND value in list-variables defines if the field is to be shown or
# hidden in EXPANDED state.
# 0 - means the field is to be shown.
# 1 - means the field is to be hidden.
#
# i.e.  const RPD_Field = [0, 1]; - means that field 'Field' will be hidden
# in collapsed state and will be shown in expanded state.
#
#############################################################################



#~~~~~~ USBTracer specific caption cell ~~~~~~~~~~~~~~~~
AddSpecCaptionCell(caption, text, tooltip, FieldColor, addparam, addparam1, addparam2 )
{
    AddCell(caption, text, tooltip, FieldColor, _USBBULK_HEADER, addparam, addparam1, addparam2 );
    return 1;
}


#~~~~~~~~~~~~~~~~~~~~~~
# Return an slice of in.Data from specified index
# Globale BitCurrentFieldOffset will be updated.
#~~~~~~~~~~~~~~~~~~~~~~

set dataBuf1 = null;
set dataBuf2 = null;
set nRemainDataBits = 0;
set dataIsString = 0;    #-->Added string data for data greater than d-word

GetDataCustom(bitIndex, length)
{
    bitOffset = DataByteHeaderOffset*8 + bitIndex;
    bitCount  = length;
    dataIsString = 0;

    # LittleEndian = 1;

    if((bitCount % 8) == 0)
    {
        if(bitCount < 33)    #-->Logic for data greater than d-word
        {
            val = GetNBits(in.Data, bitOffset, bitCount);

            val2 = 0;
            for (i = 0; i < (bitCount); i += 8)
                 val2 = (val2 << 8) | ((val >> i) & 0xFF);
        }
        else
        {
            val2 = "";
            dataIsString = 1;
            for (i = 0; i < (bitCount); i += 8)
            {
                val = GetNBits(in.Data, bitOffset + i, 8 );

                if(i==0)
                    val2 = FormatEx("0x%02X",val);
                else
                    val2 += FormatEx("%02X",val);
            }
        }

        SetFieldOffsetLen(bitOffset + bitCount, bitCount);
    }
    else
    {
        getnextdataflag = 1;           #--> Added this flag for getting data after initial pass
        if(nRemainDataBits == 0)
        {
            bitCount8 = bitCount;
            while((bitCount8 % 8) != 0)
                bitCount8++;

            nRemainDataBits = bitCount8;

            dataBuf1 = GetNBits(in.Data, bitOffset, bitCount8);

            dataBuf2 = 0;
            for (i = 0; i < (bitCount8); i += 8)
                dataBuf2 = (dataBuf2 << 8) + ((dataBuf1 >> i) & 0xFF);

            SetFieldOffsetLen(bitOffset + bitCount8, bitCount8);

            val2 = GetNBits(dataBuf2,0,bitCount);   #--> Changing GetNBits source
            getnextdataflag = 0;                    #--> Initial pass, data shouldn't be read again
        }
        else #-->Looks like this is needed, commented out, waiting review. *Uncommented this.
        {
            SetFieldOffsetLen(bitOffset + bitCount, bitCount);
        }

#xxx        mask = 1;
#xxx        for(j = 1; j < bitCount; j++)
#xxx            mask += (1 << j);

#xxx        val2 = dataBuf2 & mask;

        if(getnextdataflag)                         #--> If not initial pass, get next data
            val2 = NextNBits(bitCount);             #--> Source set from GetNBits

#xxx        dataBuf2 = dataBuf2 >> bitCount;

        nRemainDataBits -= bitCount;
    }

    return val2;
}

#############################################################################
# ShowArrowFields: Gets and shows the fields that placed in passed table
#
# Parameter arrowFieldsTable:
#   It is an array of tables that contain properties of fields.
#
# set SampleFieldTable =
# [
#   [fieldName1, fieldLenInBit1, fieldTooltip1, fieldDecodeTable1],
#   [fieldName2, fieldLenInBit2, fieldTooltip2, fieldDecodeTable2],
#   ....
#   [fieldName_n, fieldLenInBit_n, fieldTooltip_n, fieldDecodeTable_n]
# ];
#
# Specifing 'fieldName' and 'fieldLenInBit' is mandatory.
# Specifing 'fieldTooltip' and 'fieldDecodeTable' is arbitrary.
# If 'fieldLenInBit' be null or zero, it will be added as non-spec field in _MONOFIELD format.
# If 'fieldTooltip' be null, 'fieldName' will be used in tooltip.
# The 'fieldDecodeTable' contains a table that it decoces each value of field as spec.
#
# set FormatOf_FieldDecodeTable =
# [
#   [Value1, Decode1],
#   [Value2, Decode2],
#   ....
#   [Value_n, Decode_n]
# ];
#
# set Protocol_FieldDecodeTable =
# [
#   [0xFF, "INVALID"],
#   [0x04, "SSP"],
#   [0x05, "SMP"],
#   [0x06, "STP"]
# ];
#
#############################################################################
ShowArrowFields(arrowFieldsTable)
{
    # Get color setting for payload fields fields
    payLoadColor = Resolve( Prefix + "_PayLoadColor" );
    if(payLoadColor != null)
        FieldColor = payLoadColor;

    for( nIndex = 0; nIndex < sizeof(arrowFieldsTable); nIndex = nIndex + 1 )
    {
        fieldAttr         = arrowFieldsTable[nIndex];
        fieldName         = fieldAttr[0];
        fieldLength       = fieldAttr[1];
        fieldTooltip      = fieldAttr[2];
        fieldDecodeTable  = fieldAttr[3];
        addparamTabular   = fieldAttr[4]; # Tabular Info

        if((fieldLength == 0) || (fieldLength == null))
        {
            # AddCaptionCell("fieldName", "", fieldName, fieldTooltip);
            if( IsExpanded() )
                AddPayLoadCell(fieldName, "", fieldTooltip, FieldColor - DARK_COLOR_OFFSET, _MONOFIELD);
        }
        else
        {
            fieldData = GetDataCustom(BitCurrentFieldOffset, fieldLength );

            digitFormat = Format("0x%%0%dX", fieldLength/4); # Calculate digit counts
            tooltip = fieldName;

            flag = 0;
          if( (fieldName == "Reserved") && (fieldData != 0) )
          {
              tooltip += " (Should be Zero)";
              flag = _ERROR;
          }

          if(fieldTooltip != null)
              tooltip += "\n" + fieldTooltip;

          tooltip += Format("\n[Length: %d bits]",  fieldLength);

          # Get view setting for field
          field_vs = Resolve( Prefix + "_" + fieldName );

          oldColor = null;
          if(fieldName == "Reserved")
          {
              oldColor = FieldColor;
              FieldColor = ReservedColor;
          }

          if(fieldDecodeTable == null)
          {
              if(dataIsString)  #-->If data is a string, no need to format it.
              {
                  if( in.Expanded || (field_vs == null) )
                      AddSimplePLCell(fieldName, fieldData, tooltip, flag, addparamTabular);
                  else if( !field_vs[COLLAPSED] )
                      AddPayLoadCell(fieldName, fieldData, tooltip, flag, addparamTabular);
              }
              else
              {
                  if( in.Expanded || (field_vs == null) )
                      AddSimplePLCell(fieldName, Format(digitFormat, fieldData ), tooltip, flag, addparamTabular);
                  else if( !field_vs[COLLAPSED] )
                      AddPayLoadCell(fieldName, Format(digitFormat, fieldData ), tooltip, flag, addparamTabular);
              }
          }
          else
          {
              decodeRow = Find(fieldDecodeTable, fieldData);

              dataNum = fieldData;
              dataDesc = Format(": %s", decodeRow[1] );

              # Make dark those fields that has decoded table
              oldColor = FieldColor;
              FieldColor -= DARK_COLOR_OFFSET;

              if(dataIsString)   #-->If data is a string, no need to format it.
              {
                  if( in.Expanded || (field_vs == null) )
                      AddSimplePLCell(fieldName, dataNum + dataDesc, tooltip, flag, addparamTabular);
                  else if( !field_vs[COLLAPSED] )
                      AddPayLoadCell(fieldName, dataNum + dataDesc, tooltip, flag, addparamTabular);
              }
              else
              {
                  if( in.Expanded || (field_vs == null) )
                      AddSimplePLCell(fieldName, dataNum + dataDesc, tooltip, flag, addparamTabular);
                  else if( !field_vs[COLLAPSED] )
                      AddPayLoadCell(fieldName, dataNum + dataDesc, tooltip, flag, addparamTabular);
              }

              FieldColor = oldColor;
          }

          if(oldColor != null)
              FieldColor = oldColor;
        }
    }
}
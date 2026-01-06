%include "PTPUserEditParams.inc"
set ModuleType     = "DataBlock Decoder";

#const MassStorageColor = 0x80B0D0;


const ErrorColor       = 0x0000FF;

const MaxShowDataBlockSize = 512;

set MAX_TOOLTIP_LINES = 25;


####################################################################################
#                       USBTracer Length Limited cell functions                    #
####################################################################################
AddLimitedPayLoadCell(caption, text, tooltip, FieldColor, addparam, addparam1 )
{
    if( in.PrepareFldsForDlg )
    {
        PrepareFieldForDlg(caption , text, tooltip, addparam, VS[COLLAPSED] );   
    }
    else 
    {
        if( ShowItemByCaptn( caption ) )
        {
            if (CellsCount < MAX_CELLS_TO_DISPLAY)
            {
                if ( !AddSpecPayLoadCell(caption, text, tooltip, FieldColor, addparam, addparam1 ) )   # Check if some specific AddPayLoadCell hook handled call
                    AddCell(caption, text, tooltip, FieldColor, addparam, addparam1 );
            }
        }
        if (CellsCount == MAX_CELLS_TO_DISPLAY)
            AddMaxCell(FieldColor);
        CellsCount++;
    }
}

AddLimitedSimplePLCell(caption, text, tooltip, FieldColor, addparam, addparam1 )
{
   if( in.PrepareFldsForDlg )
   {
        PrepareFieldForDlg(caption , text, tooltip, addparam, 0 ); 
   }
   else 
   {
        if( SimpleShowItem() )
        {
            if (CellsCount < MAX_CELLS_TO_DISPLAY)
            {
                if ( !AddSpecSimplePLCell(caption, text, tooltip, FieldColor, addparam, addparam1 ) )  # Check if some specific AddSimplePLCell hook handled call
                    AddCell(caption, text , tooltip, FieldColor, addparam, addparam1 ); 
            }
        }
        if (CellsCount == MAX_CELLS_TO_DISPLAY)
            AddMaxCell(FieldColor);
        CellsCount++;             
    }
}

AddLimitedCell(caption, text, tooltip, FieldColor, addparam, addparam1 )
{
    if (CellsCount < MAX_CELLS_TO_DISPLAY)
        AddCell(caption, text, tooltip, FieldColor, addparam, addparam1 );
}


AddMaxCell(FieldColor)
{
    AddSeparator();
            explain = "You have reached the MAX ALLOWED cells that can be displayed\nPlease use View Decoded Fields to see the\n complete list of data.";
    if (IF_CONTINUE_ON_PROCESSING_DATA == 1)
        AddCell("MORE CELLS...", "More cells...", explain, FieldColor, _MONOCOLOR); 
    else
    {
        explain += "\nBecause the IF_CONTINUE_ON_PROCESSING_DATA is set to 0,\nthe rest of data will be dumped without error checking.\nTo check how to change this setting, please refer to readme file";
        AddCell("MORE CELLS...", "More cells...", explain, FieldColor, _MONOCOLOR); 
        out.Decoded = in.DataLength;
        IsDumpPayLoadOccurs = 1;
    }
}

####################################################################################
#                       USBTracer specific caption cell                            #
####################################################################################

AddSpecCaptionCell(caption, text, tooltip, FieldColor, addparam, addparam1, addparam2 )
{   
    AddLimitedCell(caption, text, tooltip, FieldColor, _USBBULK_HEADER, addparam, addparam1, addparam2 );        
    return 1;        
}

GetDateTimeString (length)   
{
    CapYear = ObtainUnicodeNextString(4);   # these values are for the DateTimeString 
    CapMonth = ObtainUnicodeNextString(2); 
    CapDay = ObtainUnicodeNextString(2);
    CapT = ObtainUnicodeNextString(1);
    CapHour = ObtainUnicodeNextString(2);
    CapMin = ObtainUnicodeNextString(2);
    CapSec = ObtainUnicodeNextString(length-13);
    _capMonth = Find(MonthTable,Format("%d",CapMonth));
	return  Format("%s",_capMonth[1])+Format(" %s",CapDay)+Format(", %s",CapYear)+Format(" at %s:",CapHour)+Format("%s:",CapMin)+Format("%s",CapSec);
} 

DoDefaultValueDecoding(dataTypeArray, caption, toolTip, isSimple)
{
    isEnoughData = 1;
    if (dataTypeArray[2] == "NUM")
    {
        if ( in.DataLength >= out.Decoded + dataTypeArray[3])
        {
            myTooltip = ProcessNumPayLoad(dataTypeArray[3], dataTypeArray[4], caption, toolTip, null, isSimple);
            out.Decoded += dataTypeArray[3];
        }
        else
            isEnoughData = 0;
    }
    else if (dataTypeArray[2] == "ARRAY")
    {
        if (in.DataLength >= out.Decoded + 4)
        {
            size = NextDataDWord_();
            out.Decoded += 4;
        }
        else 
            isEnoughData = 0;
        if (isEnoughData == 1)
        {
            myTooltip = "The List of value in the Array";
            for (i = 0; i < size && isEnoughData == 1; i ++)
            {
                if ( i % 20 == 0)
                {
                    if ( i + 20 < size )
                        max = i + 20;
                    else
                        max = size;
                    AddStringToDlg(FormatEx("Array Elements %d to %d", i + 1, max),"","");
                }
                if (in.DataLength >= out.Decoded + dataTypeArray[3])
                {
                    newMessage = ProcessNumPayLoad(dataTypeArray[3], dataTypeArray[4], caption + Format(" %d", i+1), toolTip, null , 1);
                    if (i < MAX_TOOLTIP_LINES)
                    {
                        myTooltip += NewLine();
                        myTooltip += newMessage;
                    }
                    else if ( i == MAX_TOOLTIP_LINES)
                    {
                        myTooltip += NewLine();
                        myTooltip += "... Expand the cell to see the complete list of elements";
                    }
                    out.Decoded += dataTypeArray[3];
                }
                else
                    isEnoughData = 0;
            }
            if (! IsExpanded() || size <= 0 )
                AddLimitedCell(caption, Format("%u elements array", size), myTooltip, NumElementsColor );
            myTooltip = "A List of value in the Array";
        }
    }
    else if (dataTypeArray[2] == "STR")
    {
        if (in.DataLength >= out.Decoded + 1)
        {
            stringSize = NextNBits_(8);
            out.Decoded ++;
        }
        else
            isEnoughData = 0;

        if (isEnoughData == 1 && in.DataLength >= out.Decoded + stringSize * 2)
        {
            myTooltip = ObtainUnicodeStringPTP(stringSize);
            FieldColor = DataTypeStringColor;
            if (isSimple == 1)
                AddLimitedSimplePLCell(caption, myTooltip, toolTip);
            else
                AddLimitedPayLoadCell(caption, myTooltip, toolTip);
            out.Decoded += stringSize * 2;
        }
        else
            isEnoughData = 0;
    }
    if (isEnoughData == 1)
        return myTooltip;
    else
        return null;
}

ProcessNumPayLoad(length, ifSigned, caption, tooltip, lookupTable, isSimple)
{
    if (length == 1)
    {
        data = NextNBits_(8);
        FieldColor = ByteValueColor;
        if (lookupTable != null)
        {
            _row = Find(lookupTable, data);
            
            if (isSimple == 1)
                AddLimitedSimplePLCell(caption, _row[1], tooltip);
            else
                AddLimitedPayLoadCell(caption, _row[1], tooltip);
                
            return _row[1];
        }
        else if (ifSigned == 1)
        {
            if (isSimple == 1)
                AddLimitedSimplePLCell(caption, Format("%d", data), tooltip);
            else
                AddLimitedPayLoadCell(caption, Format("%d", data), tooltip);
            return Format("%d", data);
        }
        else if (ifSigned == 0)
        {
            if (isSimple == 1)
                AddLimitedSimplePLCell(caption, Format("%u", data), tooltip);
            else
                AddLimitedPayLoadCell(caption, Format("%u", data), tooltip);
            return Format("%u", data);
        }
    }
    else if (length == 2)
    {
        FieldColor = WordValueColor;
        data = NextDataWord_();
        if (lookupTable != null)
        {
            _row = Find(lookupTable, data);
            if (isSimple == 1)
                AddLimitedSimplePLCell(caption, _row[1], tooltip);
            else
                AddLimitedPayLoadCell(caption, _row[1], tooltip);
            return _row[1];
        }
        else if (ifSigned == 1)
        {
            if (isSimple == 1)
                AddLimitedSimplePLCell(caption, Format("%d", data), tooltip);
            else
                AddLimitedPayLoadCell(caption, Format("%d", data), tooltip);
            return Format("%d", data);
        }
        else if (ifSigned == 0)
        {
            if (isSimple == 1)
                AddLimitedSimplePLCell(caption, Format("%u", data), tooltip);
            else
                AddLimitedPayLoadCell(caption, Format("%u", data), tooltip);
            return Format("%u", data);
        }
    }    
    else if (length == 4)
    {
        FieldColor = DWordValueColor;
        data = NextDataDWord_();
        if (lookupTable != null)
        {
            _row = Find(lookupTable, data);
            if (isSimple == 1)
                AddLimitedSimplePLCell(caption, _row[1], tooltip);
            else
                AddLimitedPayLoadCell(caption, _row[1], tooltip);
            return _row[1];
        }
        else if (ifSigned == 1)
        {
            if (isSimple == 1)
                AddLimitedSimplePLCell(caption, Format("%d", data), tooltip);
            else
                AddLimitedPayLoadCell(caption, Format("%d", data), tooltip);
            return Format("%d", data);
        }
        else if (ifSigned == 0)
        {
            if (isSimple == 1)
                AddLimitedSimplePLCell(caption, Format("%u", data), tooltip);
            else
                AddLimitedPayLoadCell(caption, Format("%u", data), tooltip);
            return Format("%u", data);
        }
    }
    else if (length == 8 )
    {
        FieldColor = EightBytesValueColor;
        text = Get8BytesValue();
        if (isSimple == 1)
            AddLimitedSimplePLCell(caption,text , tooltip);
        else
            AddLimitedPayLoadCell(caption, text, tooltip);
        return text;
    }
    else if (length == 16)
    {
        FieldColor = SixteenBytesValueColor;
        text = Get16BytesValue();
        if (isSimple == 1)
            AddLimitedSimplePLCell(caption,text , tooltip);
        else
            AddLimitedPayLoadCell(caption, text, tooltip);
        return text;
    }
}




 
DoRangeFormDecoding(dataTypeArray)
{
    isEnoughData = 1;
    if (dataTypeArray[3] != null)
    {
        if (in.DataLength >= out.Decoded + dataTypeArray[3])
        {
            ProcessNumPayLoad(dataTypeArray[3], dataTypeArray[4], "Min Value", "Minimum value supported by this property.", null, 0);
            out.Decoded += dataTypeArray[3];
        }
        else
            isEnoughData = 0;
         
        if (isEnoughData == 1 && in.DataLength >= out.Decoded + dataTypeArray[3])
        {
            ProcessNumPayLoad(dataTypeArray[3], dataTypeArray[4], "Max Value", "Maximum value supported by this property.", null, 0);
            out.Decoded += dataTypeArray[3];
        }
        else
            isEnoughData = 0;
         
        if (isEnoughData == 1 && in.DataLength >= out.Decoded + dataTypeArray[3])
        {
            ProcessNumPayLoad(dataTypeArray[3], dataTypeArray[4], "Step Size", "The value for each step within the min max value range", null, 0);
            out.Decoded += dataTypeArray[3];
        }
        else
            isEnoughData = 0;
    }
    return isEnoughData;
    
}


DoEnumerationFormDecoding(dataTypeArray, lookupTable)
{
    isEnoughData = 1;
    if (in.DataLength >= out.Decoded + 2)
    {
        numberOfValues = NextDataWord_();
        out.Decoded += 2;
    }
    else
        isEnoughData = 0;    
    if (dataTypeArray[3] != null && isEnoughData == 1)
    {
        myTooltip = "The number of values supported by the property";
        for (i = 0; i < numberOfValues && isEnoughData == 1; i++)
        {
            if (in.DataLength >= out.Decoded + dataTypeArray[3])
            {
                newMessage = ProcessNumPayLoad(dataTypeArray[3], dataTypeArray[4], "Value "+ Format("%d", i), "The Property shall support this value.", lookupTable, 1);
                if (i < MAX_TOOLTIP_LINES)
                {
                    myTooltip += NewLine();
                    myTooltip += newMessage;
                }
                else if (i == MAX_TOOLTIP_LINES)
                {
                    myTooltip += NewLine();
                    myTooltip += "... Expand the cell to see all the values";
                }                    
                out.Decoded += dataTypeArray[3];
            }
            else
                isEnoughData = 0;
        }
        if (!IsExpanded() || numberOfValues <= 0 )
            AddLimitedCell("Num Values", Format("%u", numberOfValues), myTooltip, NumValuesColor);
    }
    return isEnoughData;
}




DoFixedLengthArrayFormDecoding(dataTypeArray)
{
    isEnoughData = 1;
    if (in.DataLength >= out.Decoded + 2)
    {
        length = NextDataWord_();
        FieldColor = FixedLengthColor;
        AddLimitedPayLoadCell("Fixed length", Format("%u", length), "A 16-bit unsigned integer giving the number of elements which must be included in the array contained by this property.");
        out.Decoded += 2;
    }
    else
        isEnoughData = 0;
    return isEnoughData;
}


DoRegularExpressionFormDecoding(dataTypeArray)
{
    isEnoughData = 1;
    if (in.DataLength >= out.Decoded + 1)
    {
        stringSize = NextNBits_(8);
        out.Decoded ++;
    }
    else
        isEnoughData = 0;
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + stringSize * 2)
    {
        text = GetDateTimeString(stringSize);
        FieldColor = RegularExpressionColor;
        AddLimitedPayLoadCell("Regular Expression", text, "A regular expression that must exactly generate the value of this property.");
        out.Decoded += stringSize * 2;
    }
    else
        isEnoughData = 0;
    return isEnoughData;
}


DoByteArrayFormDecoding(dataTypeArray)
{
    isEnoughData = 1;
    if (in.DataLength >= out.Decoded + 4)
    {
        MaxLength = NextDataDWord_();
        FieldColor = MaxLengthColor;
        AddLimitedPayLoadCell("Max Length", Format("%u", MaxLength), "The maximum length of the ByteArray that may be contained by this property.");
        out.Decoded += 4;
    }
    else
        isEnoughData = 0;
    return isEnoughData;
}


DoLongStringFormDecoding(dataTypeArray)
{
    isEnoughData = 1;
    if (in.DataLength >= out.Decoded + 4)
    {
        MaxLength = NextDataDWord_();
        FieldColor = MaxLengthColor;
        AddLimitedPayLoadCell("Max Length", Format("%u", MaxLength), "The maximum length of the LongString that may be contained by this property.");
        out.Decoded += 4;
    }
    else
        isEnoughData = 0;
    return isEnoughData;
}

ObtainUnicodeStringPTP( length )
{
    ObtainUnicodeNextString( length);
}

Undefined()
{
    return 1;
}


Data()
{ 
    _code2 = Find(PTPOperationCodeTable, Code);
    if (_code2[2] != null)
		return Call(_code2[2]);
    return 1;
}

Response()
{
    return AddParams();
}

Event()
{
    return AddParams();
}

Command()
{
    return AddParams();
}

AddParams()
{
    numOfParams = (in.DataLength-out.Decoded)/4;   # calculates the number of parameters in the response field
    if (numOfParams > 5)
        numOfParams = 5; # the max parameters in current version of spec is 5
    FieldColor = PayloadColor;
    for(i = 0; i <= numOfParams-1; i++)
    {  
		param = NextDataDWord_();
		FieldColor = ParametersColor;
		AddLimitedPayLoadCell(Format("Parameter %d",i+1), Format("0x%08X",param), Format("Parameter %d = ", i+1) + Format("0x%08X(hexidecimal)", param));
    }
    out.Decoded += numOfParams * 4;
    return 1;
}
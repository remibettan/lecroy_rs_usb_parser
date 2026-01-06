#
#  Copyright (c) 2002- 2006, LeCroy Corp. PSG  - All Rights Reserved
#
#  PTPStillImageObjectPropDescDataset.inc
#
#  This file contains functional decoding related to the object propety Description Dataset
#  
ObjectPropDescDataset()
{    
    isEnoughData = 1; # true
    AddSeparator();
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 2)
    {    
        ObjectPropertyCode = NextDataWord_();
        _supObjectPropertyCode = Find(MTPObjectPropCodesTable, ObjectPropertyCode);
    	if(_supObjectPropertyCode[0] == 0xFFFF && (ObjectPropertyCode >> 15) == 0b1)
    	{
    	    if (((ObjectPropertyCode >> 15) & 0b00001) == 0b00001)
    	    _supObjectPropertyCode[1] = "MTP Extension";
    		else
        	    _supObjectPropertyCode[1] = "Vendor Extension";
        }
        FieldColor = DevicePropCodeColor;
        AddLimitedPayLoadCell("ObjectPropCode", _supObjectPropertyCode[1], Format("0x%04X",ObjectPropertyCode)
                        ,FieldColor, [_TABULARCELL, CELL_STILL_IMAGE_DEVICE_PROP_CODE]);
        out.Decoded += 2;
    }
    else
        isEnoughData = 0;
        
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 2)
    {
        DataType = NextDataWord_();
        _supDatatype = Find(DatatypeCodesTable,DataType); 
        FieldColor = DataTypeColor;
        AddLimitedPayLoadCell("DataType",_supDatatype[1],Format("Datatype code = 0x%04X", _supDatatype[0]));
        out.Decoded += 2;
    }
    else
        isEnoughData = 0;
        
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 1)
    {   
        GetSet = NextNBits_(8);
        FieldColor = GetSetColor;
        if(GetSet == 0x00)
        {
            AddLimitedPayLoadCell("GetSet", "Get", "Get(read-only)");
        }
        else if(GetSet == 0x01)
        {
            AddLimitedPayLoadCell("GetSet","Get/Set","Get/Set(read-write)");
        }
        else
        {
            FieldColor = ErrorColor;
            AddLimitedPayLoadCell("Error","Incorrect GetSet","");
        }
        out.Decoded ++;
    }
    if (isEnoughData == 1)
    {
        message = DoDefaultValueDecoding(_supDatatype, "Default Value", "Default Value");
        if (message == null)
            isEnoughData = 0;
    }

    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 4)
    {    
        GroupCode = NextDataDWord_();
        FieldColor = GroupCodeColor;
        AddLimitedPayLoadCell("Group Code", Format("0x%08X", GroupCode), "This field identifies the retrieval group this property belongs to.");
        out.Decoded += 4;
    }
    else
        isEnoughData = 0;
        
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 1)
    {    
        FormFlag = NextNBits_(8);
        FieldColor = FormFlagColor;
        result = Find(MTPFormFlagTable, FormFlag);
        AddLimitedPayLoadCell("FormFlag", Format("0x%02X", FormFlag), result[1]);
        out.Decoded ++;
    }

    if (result[2] != null)
    {
        if (FormFlag == 0x02)
            isEnoughData = Call(result[2], [_supDatatype, _supObjectPropertyCode[2] ]);
        else
            isEnoughData = Call(result[2], [_supDatatype]);
    }
    return isEnoughData;
}
 

ObjectPropCodeArray()
{
    isEnoughData = 1;
    AddSeparator();
    if (in.DataLength >= out.Decoded + 4)
    {
        ObjectPropCodenumElements = NextDataDWord_();
        FieldColor = ObjectPropCodeColor;
        out.Decoded += 4;
    }
    else
        isEnoughData = 0;
    
    if (isEnoughData == 1)
    {
        myTooltip = "The list of ObjectProp Codes supported.";
    	for(i = 0; i < ObjectPropCodenumElements && isEnoughData == 1; i++)
    	{
    	    if (in.DataLength >= out.Decoded + 2)
    	    {
    	        g = NextDataWord_();
    	        out.Decoded += 2;
    	        _code = Find(MTPObjectPropCodesTable, g);
    	        FieldColor = ObjectPropCodeColor;
    	        AddLimitedSimplePLCell("ObjectPropCode", _code[1], Format("ObjectPropCode on device with value %d (decimal)", g) + Format(" = 0x%04X(hexidecimal)", g)
    	                                , FieldColor, [_TABULARCELL, CELL_STILL_IMAGE_DEVICE_PROP_CODE]);
    	        if (i < MAX_TOOLTIP_LINES)
    	        {
    	            myTooltip += NewLine();
    	            myTooltip += _code[1];
    	        }
    	        else if (i == MAX_TOOLTIP_LINES)
    	        {
    	            myTooltip += NewLine();
    	            myTooltip += "... Expand to see the complete list of ObjectProp codes supported";
    	        }
    	    }
    	    else
    	        isEnoughData = 0;
    	}
  	    if (!isExpanded() || ObjectPropCodenumElements <= 0)
   	        AddLimitedCell("ObjElements", Format("%u", ObjectPropCodenumElements), myTooltip, ObjectPropCodeColor);
    }
	return isEnoughData;
}

ObjectPropValue()
{
    if (in.DataLength >= out.Decoded + 2)
    {
        ObjectCode = NextDataWord_();
        _code = Find(MTPObjectPropCodesTable, ObjectCode);
        FieldColor = ObjectPropValueColor;
        AddLimitedPayLoadCell("ObjectPropValue", _code[2], Format("ObjectPropValue = 0x%04X", ObjectCode), FieldColor, [_TABULARCELL, CELL_STILL_IMAGE_OBJ_PROP_VALUE]);
        out.Decoded += 2;
        return 1;
    }
    else
        return 0;
}

ObjectPropValueList()
{
    isEnoughData = 1;
    if (in.DataLength >= out.Decoded + 4)
    {
        numberOfElements = NextDataDWord_();
        FieldColor = NumElementsColor;
        AddLimitedPayLoadCell("Num Elements", Format("%u", numberOfElements), "Count of property quadruples in this dataset.",
                            FieldColor, [_TABULARCELL, CELL_STILL_IMAGE_NUM_ELEMENTS]);
        out.Decoded += 4;
    }
    else
        isEnoughData = 0;
        
    AddSeparator();
    for (i = 0 ; i < numberOfElements && isEnoughData == 1; i++)
    {
        myTooltip = "The Element contains the following information.";
        myTooltip += NewLine();
        AddStringToDlg(Format("Element %d", i + 1),"","");
        if (in.DataLength >= out.Decoded + 4)
        {
            elementObjectHandle = NextDataDWord_();
            FieldColor = ObjectHandleColor;
            AddLimitedSimplePLCell("Object Handle " + Format("%d", i + 1), Format("0x%08X", elementObjectHandle), Format("ObjectHandle of the object to which Property %d applies", i + 1));
            myTooltip += "Object Handle " + Format("%d = ", i + 1) + Format("0x%08X", elementObjectHandle);
            myTooltip += NewLine();
            out.Decoded += 4;
        }
        else
            isEnoughData = 0;
              
        if (isEnoughData == 1 && in.DataLength >= out.Decoded + 2)
        {
            elementObjectPropertyCode = NextDataWord_();
            _code = Find(MTPObjectPropCodesTable, elementObjectPropertyCode);
            FieldColor = PropertyCodeColor;
            AddLimitedSimplePLCell("Property Code " + Format("%d", i + 1), _code[1], FormatEx("Datacode = 0x%04X identifying the ObjectPropDesc describing Property %d", elementObjectPropertyCode, i + 1));
            myTooltip += "Property Code " + Format("%d = ", i + 1) + _code[1];
            myTooltip += NewLine();            
            out.Decoded += 2;
        }
        else
            isEnoughData = 0;
              
        if (isEnoughData == 1 && in.DataLength >= out.Decoded + 2)
        {        
            elementDataType = NextDataWord_();
            _typeCode = Find(DatatypeCodesTable, elementDataType);
            FieldColor = DataTypeColor;
            AddLimitedSimplePLCell(Format("Data Type %d", i+1), _typeCode[1], Format("This field identifies the DatatypeCode of Property %d.", i+1));
            myTooltip += Format("Data Type %d = ", i+1) + _typeCode[1];
            myTooltip += NewLine();               
            out.Decoded += 2;
        }
        else
            isEnoughData = 0;
                
        if (isEnoughData == 1)
        {
            message = DoDefaultValueDecoding(_typeCode, Format("Element %d Value", i+1), Format("Value of Property %d", i + 1), 1);
            if (message == null)
                isEnoughData = 0;
            else
            {
                myTooltip += "Default value = " + message;
                myTooltip += NewLine();
            }
        }
        
        myTooltip += "Expend the cell to see the detail list of cells";
        
        if (!IsExpanded())
            AddLimitedCell(_code[1],message, myTooltip, ElementNumberColor); 
        AddSeparator();
    }
    return isEnoughData;
}

InterdependentPropDesc()
{
    isEnoughData = 1; # true
    AddSeparator();
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 2)
    {
        FieldColor = NumDependenciesColor; 
        if (InterdependentPropDescDatasetSizeBytes == 2)
        {
            numberOfDependencies = NextDataWord_();
            out.Decoded += 2;
        }
        else
        {
            numberOfDependencies = NextDataDWord_();
            out.Decoded += 4;
        }
        AddLimitedPayLoadCell("# Dependencies", Format("%u", numberOfDependencies, "Count of arrays of interdependencies to follow."));
        
    }
    else
        isEnoughData = 0;

    for (i = 0; i < numberOfDependencies && isEnoughData == 1 && in.DataLength >= out.Decoded + 2; i ++)
    {
        AddSeparator();
        if (InterdependentPropDescDatasetSizeBytes == 2)
        {
            numberOfPropDesc = NextDataWord_();
            out.Decoded += 2;
        }
        else
        {
            numberOfPropDesc = NextDataDWord_();
            out.Decoded += 4;
        }

        AddLimitedPayLoadCell(Format("# PropDesc %d", i + 1), Format("%u", numberOfPropDesc, "Count of arrays of numberOfPropDesc to follow."));
        for (j = 0; j < numberOfPropDesc && isEnoughData == 1 ; j++)
        {
            AddStringToDlg(FormatEx("Dependency %d, PropDesc %d", i + 1, j + 1),"","");
            isEnoughData = ObjectPropDescDataset();
        }
    }
    return isEnoughData;
}
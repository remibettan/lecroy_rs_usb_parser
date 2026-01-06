#
#  Copyright (c) 2002- 2006, LeCroy Corp. PSG  - All Rights Reserved
#
#  PTPStillImageDevicePropDescDataset.inc
#
#  This file contains functional decoding related to the Device propety Description Dataset
#  


DevicePropDescDataset()
{    
    isEnoughData = 1; # true
    AddSeparator();
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 2)
    {    
        DevicePropertyCode = NextDataWord_();
        _supDevicePropertyCode = Find(PTPDevicePropCodesTable, DevicePropertyCode);
    	if(_supObjectPropertyCode[0] == 0xFFFF && (DevicePropertyCode >> 15) == 0b1)
    	{
    	    if (((DevicePropertyCode >> 15) & 0b00001) == 0b00001)
    	    _supDevicePropertyCode[1] = "MTP Extension";
    		else
        	    _supDevicePropertyCode[1] = "Vendor Extension";
        }
        FieldColor = DevicePropCodeColor;
        AddLimitedPayLoadCell("DevicePropCode", _supDevicePropertyCode[1], Format("0x%04X",DevicePropertyCode), 
                    FieldColor, [_TABULARCELL, CELL_STILL_IMAGE_DEVICE_PROP_CODE]);
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
        message = DoDefaultValueDecoding(_supDatatype, "Default Value", "Factory Default Value", 0);
        if (message == null)
            isEnoughData = 0;
     }

    if (isEnoughData == 1)
    {
        returnText = DoDefaultValueDecoding(_supDatatype, "Current Value", "Current Value");
        if (returnText == null)
            isEnoughData = 0;
        else
            isEnoughData = 1;
    }

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
            isEnoughData = Call(result[2], [_supDatatype, _supDevicePropertyCode[2] ]);
        else
            isEnoughData = Call(result[2], [_supDatatype]);
    }
    
    return isEnoughData;
} 
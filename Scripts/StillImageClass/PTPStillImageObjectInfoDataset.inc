#
#  Copyright (c) 2002- 2006, LeCroy Corp. PSG  - All Rights Reserved
#
#  PTPStillImageObjectInfoDataset.inc
#
#  This file contains functional decoding related to the object Information Dataset
#  

ObjectHandleArray()  
{
    if (in.DataLength >= out.Decoded + 4)
    {
        ObjectHandlenumElements = NextDataDWord_();
        out.Decoded += 4;
        FieldColor = ObjectHandleColor;
        if(ObjectHandlenumElements == 0x00000000)
        {
    	    AddLimitedPayLoadCell("ObjectHandle","0","Undefined");
        }
        else if ( in.DataLength < out.Decoded + ObjecthandlenumElements * 4)
        {
            
        }
        else
        {
            Objectstatement = " ...Check the expanded version of this field to see rest of object handles supported.";
            AddLimitedSimplePLCell("ObjHanTot",ObjectHandlenumElements,"Number of ObjectHandle elements in ObjectHandle array", 
                                                    FieldColor, [_TABULARCELL, CELL_STILL_IMAGE_OBJ_HAN_TOT, "TEXT_CAPTION"]);
            for(i = 0; i < ObjectHandlenumElements; i++)
            {
    	        h = NextDataDWord_();
    	        out.Decoded += 4;
                objCounter++;
     	        AddLimitedSimplePLCell("ObjectHandle",Format("0x%08X",h),Format("Reference of an image or data file(hexidecimal) with decimal value of %d ", h));
                if(objCounter < 25)   # to make sure that there are no more than 24 objectHandles displayed in the tooltip
                {
                    objHandles += Format(" 0x%08X\n",h);
                }
                else if(objCounter == 25)
                {
                    objHandles += Format("%s",Objectstatement);
                }
            }   
            if(!in.Expanded)
            {
                AddLimitedCell("ObjHan", "Supported", Format("ObjectHandles Supported:\n%s",objHandles),ObjectHandleColor);  # cell that the user sees pre-expansion
            }
        }
        return 1;
    }
    else
        return 0;
}
 
DataObject()   
{
    FieldColor = XMLCellColor;
    stringLength = in.DataLength - out.Decoded;
    if (stringLength > 5)
    {
        validateString = ObtainString( out.Decoded, 5);
        if (validateString == "<?xml") # validate if using xml transfer
        {
            # Pic Bridge decoding
			XMLSource = validateString + ObtainString( out.Decoded + 5, stringLength - 5);
			#Text and ToolTip are automaticly generated in XML.inc
			SpecificationCommandTable = PictBridgeCommandTable; #tell which table to use for XML command lookup
			AddSeparator();
			ShowXMLCells( XMLSource );
			out.Decoded = in.DataLength;
		}
    }
    return 1;
}   

ThumbnailObject()
{
    # nothing is handled in this function
    return 1;

}

ObjectInfoDataset()
{
    isEnoughData = 1; # true
    AddSeparator();
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 4)
    {    
        StorageID = NextDataDWord_();
        FieldColor = StorageIDColor;
        AddLimitedPayLoadCell("StorageID", Format("0x%08X",StorageID), Format("StorageID of the device's store in which the image resides(hexidecimal) \nStorageID decimal value: %d", StorageID)
                            , FieldColor, [_TABULARCELL, CELL_STILL_IMAGE_STORAGE_ID, "TEXT_CAPTION"]);
        out.Decoded += 4;
    }
    else
        isEnoughData = 0;
        
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 2)
    {
        ObjectFormat = NextDataWord_(); 
        _supObjectFormat = Find(PTPObjectFormatCodesTable, ObjectFormat);

        # special cases for values in ObjectFormat
        if(_supObjectFormat[0] == 0xFFFF && (ObjectFormat >> 15) == 0b1)
        {
            if (((ObjectFormat >> 11) & 0b00001) == 0b00001)
      	        _supObjectFormat[1] = "MTP Extension";
            else
      	        _supObjectFormat[1] = "Vendor Extension";
        }
        FieldColor = ObjectFormatColor;
        AddLimitedPayLoadCell("ObjectFormat", _supObjectFormat[1], Format("Object Format code value = 0x%04X", ObjectFormat));
        out.Decoded += 2;
    }
    else
        isEnoughData = 0;
        
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 2)
    {
        ProtectionStatus = NextDataWord_();
        _supProtection = Find(PTPProtectionStatusTable, ProtectionStatus);
        FieldColor = ProtectionStatusColor;
        AddLimitedPayLoadCell("ProtectStat", _supProtection[1], Format("ProtectionStatus: Protection Status value is 0x%04X",_supProtection[0]));
        out.Decoded += 2;
    }
    else
        isEnoughData = 0;
        
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 4)
    {    
        FieldColor = ObjectCompressedSizeColor;
        ObjectCompressedSize = NextDataDWord_();
        AddLimitedPayLoadCell("ObjCompSize", Format("0x%04X",ObjectCompressedSize), Format("ObjectCompressedSize: Size of buffer needed to hold entire binaryobject in bytes(hexidecimal) \nObjectCompressedSize DecimalVal: %d", ObjectCompressedSize));
        out.Decoded += 4;
    }
    else
        isEnoughData = 0;
        
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 2)
    {    
        ThumbFormat = NextDataWord_();
        _supThumbFormat = Find(PTPObjectFormatCodesTable, ThumbFormat);  # search for name of ThumbFormat in ObjectFormatCodesTable
        
        # special cases for ThumbFormat
        if(_supThumbFormat[0] == 0xFFFF && (ThumbFormat >> 15) == 0b1)
        {
            if (((ThumbFormat >> 11) & 0b00001) == 0b00001)
      	        _supThumbFormat[1] = "MTP Extension";
            else
         	    _supThumbFormat[1] = "Vendor Extension";
        }
        FieldColor = ThumbFormatColor;
        AddLimitedSimplePLCell("ThumbFormat", _supThumbFormat[1], Format("ThumbFormat value = 0x%04X(hexidecimal)",ThumbFormat));
        out.Decoded += 2;
    }
    else
        isEnoughData = 0;
        
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 4)
    {     
        ThumbCompressedSize = NextDataDWord_();
        FieldColor = ThumbCompressedSizeColor;
        AddLimitedSimplePLCell("ThumbCompSize",ThumbCompressedSize,Format("ThumbCompressedSize: Size of buffer needed to hold the thumbnail in decimal and HexVal is 0x%08X", ThumbCompressedSize));
        out.Decoded += 4;
    }
    else
        isEnoughData = 0;
        
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 4)
    {    
        FieldColor = ThumbPixWidthColor;
        ThumbPixWidth = NextDataDWord_();
        if(ThumbPixWidth == 0)
        {
            AddLimitedSimplePLCell("ThumbPixWidth", "0x00000000", "Not supported or not an image");
        }
        else
        {
            AddLimitedSimplePLCell("ThumbPixWidth", ThumbPixWidth, Format("Width of the thumbnail in pixels in decimal and HexVal is 0x%04X", ThumbPixWidth));
        }
        out.Decoded += 4;
    }
    else
        isEnoughData = 0;
        
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 4)
    {      
        FieldColor = ThumbPixHeightColor;
        ThumbPixHeight = NextDataDWord_();
        if(ThumbPixHeight == 0)
        {
            AddLimitedSimplePLCell("ThumbPixHeight", "0x00000000", "Not supported or not an image");
        }
        else
        {
            AddLimitedSimplePLCell("ThumbPixHeight", ThumbPixHeight, Format("Height of the thumbnail in pixels in decimal and HexVal is 0x%08X", ThumbPixHeight));
        }
        out.Decoded += 4;
    }
    else
        isEnoughData = 0;    
    # this will cause there to be a cell called "Thumb Info" when not expanded and it will give the three thumb cells when expanded
    if(!IsExpanded() && isEnoughData == 1)
    {
        AddLimitedCell("Thumb","Info",Format("Expansion will show information on thumb which includes:\n ThumbCompressedSize: %d(decimal)", ThumbCompressedSize) + Format("\n ThumbPixWidth: %d(decimal)", ThumbPixWidth) + Format("\n ThumbPixHeight: %d(decimal)", ThumbPixHeight), ThumbInfoColor);
    }
    AddSeparator();

    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 4)
    { 
        FieldColor = ImagePixWidthColor;
        ImagePixWidth = NextDataDWord_();
        if(ImagePixWidth == 0)
        {
            AddLimitedSimplePLCell("ImagePixWidth", "0x00000000", "Not supported or not an image");
        }
        else
        {
            AddLimitedSimplePLCell("ImagePixWidth", ImagePixWidth, Format("Width of the image in pixels in decimal and HexVal is 0x%08X", ImagePixWidth));
        }
        out.Decoded += 4;
    }
    else
        isEnoughData = 0;
        
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 4)
    {    
        FieldColor = ImagePixHeightColor;
        ImagePixHeight = NextDataDWord_();
        if(ImagePixHeight == 0 || ImagePixHeight == null)
        {
            AddLimitedSimplePLCell("ImagePixHeight", "0x00000000", "Not supported or not an image");
        }
        else
        {
            AddLimitedSimplePLCell("ImagePixHeight", ImagePixHeight, Format("Height of the image in pixels in decimal and HexVal is 0x%08X", ImagePixHeight));
        }
        out.Decoded += 4;
    }
    else
        isEnoughData = 0;
        
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 4)
    {     
        FieldColor = ImageBitDepthColor;
        ImageBitDepth = NextDataDWord_();
        if(ImageBitDepth == 0)
        {
            AddLimitedSimplePLCell("ImageBitDepth", "0x00000000", "Unused");
        }
        else
        {
            AddLimitedSimplePLCell("ImageBitDepth", ImageBitDepth, Format("Total number of bits per pixel of the uncompressed image in decimal and HexVal is 0x%08X", ImageBitDepth));
        }
        out.Decoded += 4;
    }
    else
        isEnoughData = 0;

    
    # this will cause there to be a cell called "Image Info" when not expanded and it will give the three image cells when expanded
    if(!isExpanded() && isEnoughData == 1)
    {
        AddLimitedCell("Image","Info",Format("Expansion shows image information including:\n ImagePixWidth: %d(decimal)", ImagePixWidth) + Format("\n ImagePixHeight: %d(decimal)", ImagePixHeight) + Format("\n ImageBitDepth: %d(decimal)", ImageBitDepth), ImageInfoColor);
    }
    AddSeparator();

    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 4)
    {     
        FieldColor = ParentObjectColor;
        ParentObject = NextDataDWord_();
        AddLimitedPayLoadCell("ParentObject", ParentObject,Format("Indicates the handle of the object that is the parent\nof this object(decimal) and the HexVal is 0x%08X", ParentObject));
        out.Decoded += 4;
    }
    else
        isEnoughData = 0;
        
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 2)
    {     
        AssociationType = NextDataWord_();
        _supAssociation = Find(AssociationTypesTable, AssociationType);
        if (_supAssociation[0] == 0xFFFF && ((AssociationType >> 14) == 0b10))
        {
        	  _supAssociation[2] = "Undefined";
     	      _supAssociation[1] = "Vendor_defined";
        }
        else if(_supAssociation[0] == 0xFFFF && ((AssociationType >> 14) == 0b11)) 
        {
        	  _supAssociation[2] = "Undefined";
     	      _supAssociation[1] = "MTP";
        }
        FieldColor = AssociationTypeColor;
        AddLimitedPayLoadCell("AssocType", _supAssociation[1], Format("AssociationType: AssociationType code = 0x%04X(hexidecimal)", AssociationType));   
        out.Decoded += 2;
    }
    else
        isEnoughData = 0;
        
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 4)
    {    
        AssociationDesc = NextDataDWord_();
        FieldColor = AssociationDescColor;
        AddLimitedPayLoadCell("Asso. Desc", Format("0x%08X", AssociationDesc), "Association Description");
        out.Decoded += 4;
    }
    else
        isEnoughData = 0;
        
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 4)
    { 
        FieldColor = SequenceNumberColor;
        SequenceNumber = NextDataDWord_();
        AddLimitedPayLoadCell("SeqNum",Format("0x%08X",SequenceNumber),Format("SequenceNumber: Sequence number of object(hexidecimal) and decimal value is %d", SequenceNumber));
        out.Decoded += 4;
    }
    else
        isEnoughData = 0;
        
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 1)
    { 
        FilenamenumChars = NextNBits_(8);   # number of characters in the Filename string
        out.Decoded += 1;
    }
    else
        isEnoughData = 0;
        
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + FilenamenumChars * 2)
    {
        FieldColor = FilenameColor;
        if(FilenamenumChars > 0)
        {
            Filename = ObtainUnicodeStringPTP(FilenamenumChars);
            out.Decoded += FilenamenumChars * 2;
            FieldColor = FilenameColor;
    	    AddLimitedPayLoadCell("Filename", Filename, "Name of file");           
        }
    }
    else
        isEnoughData = 0;
        
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 1)
    {
        CaptureStringSize = NextNBits_(8);
        out.Decoded += 1;
    }
    else
        isEnoughData = 0;
        
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + CaptureStringSize * 2)
    {
        if (CaptureStringSize > 0)
        {
            CaptureString = GetDateTimeString( CaptureStringSize);
            out.Decoded += CaptureStringSize * 2;
            FieldColor = CaptureDateColor;
    	    AddLimitedPayLoadCell("CaptureDate", CaptureString, "Time that data object was initially captured\nFormat:YYYYMMDDThhmmss.s where YYYY is the year,\nMM is the month, DD is the day,T is a const character,\nhh is the hour,mm is the minute, ss.s is the seconds with .s being optional\ntenths of a second");
        }
    }
    else
        isEnoughData = 0;
        
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 1)
    {
        ModificationStringSize = NextNBits_(8);
        out.Decoded += 1;
    }
    else
        isEnoughData = 0;
    
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + ModificationStringSize * 2)
    {
        if (ModificationStringSize > 0)
        {
            ModificationString = GetDateTimeString( ModificationStringSize);
            out.Decoded += ModificationStringSize * 2;
            FieldColor = ModificationDateColor;
    	    AddLimitedPayLoadCell("ModDate", ModificationString, "Time that data object was Modified\nFormat:YYYYMMDDThhmmss.s where YYYY is the year,\nMM is the month, DD is the day,T is a const character,\nhh is the hour,mm is the minute, ss.s is the seconds with .s being optional\ntenths of a second");          
        }
    }
    else
        isEnoughData = 0;
        
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 1)
    {
        KeywordsStringSize = NextNBits_(8);
        out.Decoded += 1;
    }
    else
        isEnoughData = 0;
    
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + KeywordsStringSize * 2)
    {
        if (KeywordsStringSize > 0)
        {
            KeywordsString = ObtainUnicodeStringPTP(KeywordsStringSize);
            out.Decoded += KeywordsStringSize * 2;
            FieldColor = KeywordColor;
    	    AddLimitedPayLoadCell("Keywords", KeywordsString, "List of keywords");           
        }
    }
    else
        isEnoughData = 0;
        
    return isEnoughData;
}


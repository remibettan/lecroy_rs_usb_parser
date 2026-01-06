StorageIDArray()
{
    if (in.DataLength > out.Decoded + 4)
    {
        StorageIDnumElements = NextDataDWord_();
        out.Decoded += 4;
        FieldColor = StorageIDColor;
        if(StorageIDnumElements == 0x00000000)
        {
            AddLimitedPayLoadCell("StorageID", "0", "No StorageID", FieldColor, [_TABULARCELL, CELL_STILL_IMAGE_STORAGE_ID, "TEXT_CAPTION"]);
        }
    	else if ( in.DataLength < out.Decoded + StorageIDnumElements * 4)
    	{
    	    AddNoEnoughDataCell();
    	}
        else
        {
            Storagestatement = " ...Check the expanded version of this field to see rest of storageIDs supported.";
            AddLimitedSimplePLCell("StorIDTot",StorageIDnumElements,"Number of StorageID elements in StorageID array");
            #SetFieldOffset(44,32);
    	    for(i = 0; i < StorageIDnumElements; i++)
    	    {
    	        g = NextDataDWord_();
    	        out.Decoded += 4; 
    	        IDs++; 
    	        
    	        AddLimitedSimplePLCell("StorageID", g, Format("StorageID on device with value %d (decimal)", g) + Format(" = 0x%04X(hexidecimal)", g)
    	                                    , FieldColor, [_TABULARCELL, CELL_STILL_IMAGE_STORAGE_ID, "TEXT_CAPTION"]);
    	                                    
    	        if(IDs < 25)           # this if statement is to make sure that the tooltip does not show more than 24 storageIDs
    	        {
    	            storIDs += Format(" 0x%04X\n",g);
    	        }
    	        else if(IDs == 25)
    	        {
    	            storIDs += Format("%s",Storagestatement);
    	        }
            }
            if(!in.Expanded)
            {
                AddLimitedCell("StorID","Supported",Format("StorageIDs Supported:\n%s",storIDs),StorageIDColor);   # cell that the user sees pre-expansion
            }
        }
        return 1;
    }
    else
        return 0;
}

StorageInfo()
{
    isEnoughData = 1; # true
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 2)
    {
        StorageType = NextDataWord_(); 
        out.Decoded += 2;
   	    _supStorage = Find(PTPStorageTypesTable, StorageType);   # search for storageType name in StorageTypesTable
        FieldColor = StorageTypeColor;
        AddLimitedPayLoadCell("Storagetype", _supStorage[1], Format("Storage type code =  0x%04X(hexidecimal)", _supStorage[0]), FieldColor, [_TABULARCELL, CELL_STILL_IMAGE_STORAGE_TYPE]);
    }
    else
        isEnoughData = 0;
        
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 2)
    {
        FilesystemType = NextDataWord_();
        out.Decoded += 2;
        _supFile = Find(PTPFilesystemTypeTable, FilesystemType);
        if (_supFile[0] == 0xFFFF && (FilesystemType & 0x8000))
        {
    	    if (FilesystemType & 0x4000)
    	        _supFile[1] = "MTP Extension";
    	    else
    	        _supFile[1] = "Vendor Extension";
        }
        FieldColor = FilesystemTypeColor;
        AddLimitedPayLoadCell("FilesysType", _supFile[1], Format("FileSystemType: FilesystemType value =  0x%04X(hexidecimal)", _supFile[0]));
    }
    else
        isEnoughData = 0;    

    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 2)
    {    
        AccessCapability = NextDataWord_();
        out.Decoded += 2;
        _supAccess = Find(PTPStorageInfoAccessCapabilityTable, AccessCapabililty);
        FieldColor = AccessCapabilityColor;
        AddLimitedPayLoadCell("AccCapab", _supAccess[1], Format("AccessCapability: AccessCapability value =  0x%04X(hexidecimal)", _supAccess[0]));
    }
    else
        isEnoughData = 0;    

    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 8)
    {
        MaxCapacity = Get8BytesData();
        FieldColor = MaxCapacityColor;
        AddLimitedPayLoadCell("MaxCapacity", MaxCapacity, "Indicates total storage capacity of the store in bytes");
        out.Decoded += 8;
    }
    else
        isEnoughData = 0;    

    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 8)
    {
        FreeSpaceInBytes = Get8BytesData();
        out.Decoded += 8;
        FieldColor = FreeSapceInBytesColor;
        if (FreeSpaceInBytes == "0xFFFFFFFFFFFFFFFF")
        {
            AddLimitedPayLoadCell("FreeSpaceInBytes", "Not Used", "FreeSpaceInBytes: Unused field");
        }
        else
        {
            AddLimitedPayLoadCell("FreeSpaceInBytes", FreeSpaceInBytes, "FreeSpaceInBytes: Amount of free space available in the store in bytes");
        }
    }
    else
        isEnoughData = 0;   
     
    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 4)
    {
        FreeSpaceInObjects = NextDataDWord_();
        out.Decoded += 4;
        FieldColor = FreeSpaceInObjectsColor;
        if (FreeSpaceInObjects == 0xFFFFFFFF)
        {
            AddLimitedPayLoadCell("FreeSpaceInObjects", "Not Used", "FreeSpaceInBytes: Unused field");
        }
        else
        {
            AddLimitedPayLoadCell("FreeSpaceInObjects", Format("0x%08X",FreeSpaceInObjects), "FreeSpaceInObjects: Amount of additional objects may be written to this device.");
        }
    }
    else
        isEnoughData = 0;   

    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 1)
    { 
        StorageDescriptionnumChars = NextNBits_(8);   # this byte gives the amount of characters in the storageDescription string
        out.Decoded += 1;
    }
    else
        isEnoughData = 0;    


    if (isEnoughData == 1 && in.DataLength >= out.Decoded + StorageDescriptionnumChars * 2)
    {
        FieldColor = StorageDescriptionColor;
        if (StorageDescriptionnumChars > 0)
        {
            StorageDescription = ObtainUnicodeStringPTP(StorageDescriptionnumChars);
            out.Decoded += StorageDescriptionnumChars * 2;
            AddLimitedPayLoadCell("StorageDesc", StorageDescription, Format("Storage Description String, length = %d",StorageDescriptionnumChars));
        }        
    }
    else
        isEnoughData = 0;    

    if (isEnoughData == 1 && in.DataLength >= out.Decoded + 1)
    { 
        VolumeLabelnumChars = NextNBits_(8);   # this byte gives the amount of characters in the storageDescription string
        out.Decoded += 1;
    }
    else
        isEnoughData = 0;    

    if (isEnoughData == 1 && in.DataLength >= out.Decoded + VolumeLabelnumChars * 2)
    {
        
        if (VolumeLabelnumChars > 0)
        {
            VolumeLabel = ObtainUnicodeStringPTP(VolumeLabelnumChars);
            out.Decoded += VolumeLabelnumChars * 2;
            FieldColor = VolumeLabelColor;
            AddLimitedPayLoadCell("VolumeLabel", VolumeLabel, Format("programmatically relevant volume identifier, length = %d",VolumeLabelnumChars));
	    }
    }
    else
        isEnoughData = 0;   
    
    return isEnoughData;
}
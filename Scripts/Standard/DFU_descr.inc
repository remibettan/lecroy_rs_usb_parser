
#*******************************************************************************
#
#  FILENAME: DFU_descr.inc
#
#  Copyright (c)  2015 Teledyne LeCroy, Inc.
#
#*******************************************************************************

set DFU_Descriptors =
[
   [ 0x21, "DFU_FUNCTIONAL"             ,"DFU_functional_sub"                 ]
];

TryDFU_Descriptors(bDescriptorType)
{
   _row_vid = Find (DFU_Descriptors, bDescriptorType);

   bLengh = 0;
   CurrentByteOffset = 0;

   if (_row_vid[0] == 0xFF)
       return 0;
   Call (_row_vid[1]);
   return 1;
}

DFU_FUNCTIONAL()
{
    DescriptorCellString = "DFU Descriptor";
    AddDataHeader( "DFU Descriptor", in.DataLength - 8 );
	
    DFU_functional_sub();
    return GetFinalText();
}

DFU_functional_sub()
{    
	base = Base;
    bLength         = GetDataByte(base);
    AddByteEntry( "bLength", "The total size of the DFU descriptor.", 0, 1);
	
	bDescriptorType = GetDataByte(base+1);
    _row = Find (DFU_Descriptors, bDescriptorType);
    AddByteEntry( "bDescriptorType", GetDescriptorTypeString( _row[1]), 0, 1);
	
	bmAttributesData      = GetDataByte(base+2);
	AddByteEntry( "bmAttributes", DecodeAttributesData(bmAttributesData), 0, 1);
		
	AddWordEntry( "wDetachTimeOut", "Time, in milliseconds, that the device will wait after receipt of the DFU_DETACH request", 0, 1);
	
	AddWordEntry( "wTransferSize", "Maximum number of bytes that the device can accept per control-write transaction", 0, 1);
	
	AddWordEntry( "bcdDFUVersion", "Numeric expression identifying the version of the DFU Specification release", 0, 1);
	
    return 1;
}

DecodeAttributesData(AttributesData)
{
    str = "DFU attributes";
	str += "<BR>&nbsp;&nbsp; [Bit 0] Download capable: ";
    if ((AttributesData & 0x01) == 0)
        str += "No";
    else
        str += "Yes";
    
	str += "<BR>&nbsp;&nbsp; [Bit 1] Upload capable: ";
    if ((AttributesData & 0x02) == 0)
        str += "No";
    else
        str += "Yes";
		
	str += "<BR>&nbsp;&nbsp; [Bit 2] Communicate via USB after Manifestation: ";
    if ((AttributesData & 0x04) == 0)
        str += "No";
    else
        str += "Yes";
		
	str += "<BR>&nbsp;&nbsp; [Bit 3] Perform a bus detach-attach after DFU_DETACH: ";
    if ((AttributesData & 0x8) == 0)
        str += "No";
    else
        str += "Yes";
		
	str += "<BR>&nbsp;&nbsp; [Bit 4-7] Reserved:";
    str += FormatEx("0x%X", ((AttributesData & 0xF0) >> 4));
				
    return str;
}

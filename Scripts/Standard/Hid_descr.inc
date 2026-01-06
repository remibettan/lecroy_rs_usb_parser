
#*******************************************************************************
#
#  FILENAME: Hid_descr.inc
#
#  Copyright (c) 2008, LeCroy - All Rights Reserved
#
#  DESCRIPTION
#    HID Usage Tables
#
#  FILE HISTORY:
#     01/03/06  Added table Hid_Descriptors and updated necessary logic.
#               Descriptor Types were Hid specific in Standard DescrType
#               Table. - jd
#     06/25/08  Added fix to properly report Usage for all descriptors. - RK
#     09/12/16  Edited by FJ
#
#*******************************************************************************

%include "hut.inc"

set REPORT_TAG_USAGE_PAGE   = 0x04; 
set REPORT_TAG_USAGE        = 0x08; 
set REPORT_TAG_REPORT_ID    = 0x84; 
set REPORT_TAG_FEATURE      = 0xB0; 
set REPORT_TAG_USAGE_MIN    = 0x18; 
set REPORT_TAG_USAGE_MAX    = 0x28; 
set REPORT_TAG_REPORT_COUNT = 0x94; 
set REPORT_TAG_REPORT_SIZE  = 0x74; 
set REPORT_TAG_INPUT        = 0x80;
set REPORT_TAG_OUTPUT       = 0x90;
set REPORT_TAG_COLLECTION   = 0xA0;

set HIDReportTags =
[
    [REPORT_TAG_USAGE_PAGE,     "Usage Page"],
    [REPORT_TAG_USAGE,          "Usage"],
    [REPORT_TAG_COLLECTION,     "Collection"],
    [REPORT_TAG_USAGE_MIN,      "Usage Minimum"],
    [REPORT_TAG_USAGE_MAX,      "Usage Maximun"],
    [REPORT_TAG_REPORT_COUNT,   "Report Count"],
    [REPORT_TAG_REPORT_SIZE,    "Report Size"],
    [REPORT_TAG_INPUT,          "Input"],
    [REPORT_TAG_OUTPUT,         "Output"],
    [REPORT_TAG_REPORT_ID,      "Report ID"]
];

set CountryCodeList = ["Not Supported","Arabic","Belgian","Canadian-Bilingual", "Canadian-French","Czech Republic", "Danish", "Finnish",
                       "French", "German", "Greek", "Hebrew", "Hungary","International (ISO)", "Italian", "Japan (Katakana)", "Korean",
                       "Latin American", "Netherlands/Dutch", "Norwegian", "Persian (Farsi)", "Poland", "Portuguese", "Russia", "Slovakia",
                       "Spanish", "Swedish", "Swiss/French", "Swiss/German", "Switzerland", "Taiwan", "Turkish-Q", "UK", "US", "Yugoslavia",
                       "Turkish-F"] ;


set ReportItemType =
[
    [0xFF,"Reserved", null                  ],
    [0x00,"Main", "ReportMainItemTag"       ],
    [0x01,"Global", "ReportGlobalItemTag"   ],
    [0x02,"Local", "ReportLocalItemTag"     ]
];

set ReportMainItemTag =
[
    #------------------------------------------------------
    #ID  ,Tag name          , subFunction
    #------------------------------------------------------
    [0x0F,"Reserved"        , null],
    [0x08,"Input"           , "ReportSubfunctionInput"],
    [0x09,"Output"          , "ReportSubfunctionOutput"],
    [0x0B,"Feature"         , "ReportSubfunctionFeature"],
    [0x0A,"Collection"      , "ReportSubfunctionCollection"],
    [0x0C,"End Collection"  , null]
];
set ReportGlobalItemTag =
[
    #------------------------------------------------------
    #ID  ,Tag name          , subFunction
    #------------------------------------------------------
    [0x0C, "Reserved"       , null],
    [0x00, "Usage Page"     , "ReportSubfunctionUsagePage"],
    [0x01, "Logical Minimum", "ReportSubfunctionNum"],
    [0x02, "Logical Maximum", "ReportSubfunctionNum"],
    [0x03, "Physical Minimum", "ReportSubfunctionNum"],
    [0x04, "Physical Maximum", "ReportSubfunctionNum"],
    [0x05, "Unit Exponent"   , "ReportSubfunctionNum"],
    [0x06, "Unit"           , "ReportSubfunctionNum"],
    [0x07, "Report Size"    , "ReportSubfunctionNum"],
    [0x08, "Report ID"      , "ReportSubfunctionNum"],
    [0x09, "Report Count"   , "ReportSubfunctionNum"],
    [0x0A, "Push"           , "ReportSubfunctionNum"],
    [0x0B, "Pop"            , "ReportSubfunctionNum"]
];

set ReportLocalItemTag =
[
    #------------------------------------------------------
    #ID  ,Tag name          , subFunction
    #------------------------------------------------------
    [0xFF, "Reserved"       , null],
    [0x00, "Usage"          , "ReportSubfunctionUsage"],
    [0x01, "Usage Minimum"  , "ReportSubfunctionNum"],
    [0x02, "Usage Maximum"  , "ReportSubfunctionNum"],
    [0x03, "Designator Index", "ReportSubfunctionNum"],
    [0x04, "Designator Minimum", "ReportSubfunctionNum"],
    [0x05, "Designator Maximum", "ReportSubfunctionNum"],
    [0x06, "String Index"   , "ReportSubfunctionNum"],
    [0x07, "String Minimum" , "ReportSubfunctionNum"],
    [0x08, "String Maximum" , "ReportSubfunctionNum"],
    [0x09, "Delimiter"      , "ReportSubfunctionDelimiter"]
];

set ReportCollectionTable =
[
    [0xFF, "Reserved"],
    [0x00, "Physical"],
    [0x01, "Application"],
    [0x02, "Logical"],
    [0x03, "Report"],
    [0x04, "Named Array"],
    [0x05, "Usage Switch"],
    [0x06, "Usage Modifier"]
];

set BiasTable =
[
    [0x05, "Reserved"   ],
    [0x00, "N/A"        ],
    [0x01, "Right Hand" ],
    [0x02, "Left Hand"  ],
    [0x03, "Both Hand"  ],
    [0x04, "Either Hand"]
];

set DesignatorList = [ "None", "Hand", "Eyeball", "Eyebrow", "Eyelid", "Ear", "Nose", "Mouth", "Upper lip", "Lower lip", "Jaw", "Neck",
                        "Upper arm", "Elbow", "Forearm", "Wrist", "Palm", "Thumb", "Index finger", "Middle finger", "Ring finger",
                        "Little finger", "Head", "Shoulder", "Hip", "Waist", "Thigh", "Knee", "Calf", "Ankle", "Foot", "Heel", "Ball of foot",
                        "Big toe", "Second toe", "Third toe", "Fourth toe", "Little toe", "Brow", "Cheek" ]; # more than this are reserved


set QualifierList = ["Not applicable", "Right", "Left", "Both", "Either", "Center"];



set sizeOf_b = 1;
set CurrentIndex = 0;
set ReportData = 0;
set ReportUsagePage = 0;


DataAvailable(decoded)
{
    return (in.DataLength - decoded);
}

set ShortItemSize =
[
    [0, 0],
    [1, 1],
    [2, 2],
    [3, 4]
];

set Hid_Descriptors =
[
   [ 0xFF, "Illegal"                    ,"Illegal_sub"                   ],
   [ 0x21, "HID_DESCRIPTOR"             ,"Hid_class_sub"                 ],
   [ 0x22, "REPORT_DESCRIPTOR"          ,"Hid_Report_sub"                ],
   [ 0x23, "PHYSICAL_DESCRIPTOR"        ,"Hid_Physical_sub"              ]
];

TryHid_Descriptors(bDescriptorType)
{
   _row_vid = Find (Hid_Descriptors, bDescriptorType);

   bLengh = 0;
   CurrentByteOffset = 0;

   if (_row_vid[0] == 0xFF)
       return 0;
   Call (_row_vid[1]);
   return 1;
}



DecodeHidDescriptor()
{
   # let's set the class-specific table
  # wValue = GetDataWord(CurrentIndex); CurrentIndex = CurrentIndex + sizeOf_w;
  # wIndex = GetDataWord(CurrentIndex); CurrentIndex = CurrentIndex + sizeOf_w;

   ClassDescriptorTable = DescriptorTypeTable;

   Base = 8;
   CurrentByteOffset = 0;

   do_descriptor(); # this function is defined in UsbCommon.inc
}



HID_DESCRIPTOR()
{
    DescriptorCellString = "HID Descriptor";
    AddDataHeader( "HID Descriptor", in.DataLength - 8 );
    Hid_class_sub();
    return GetFinalText();
}



Hid_class_sub()
{
    base = Base;
    bLength         = GetDataByte(base);
    AddByteEntry( "bLength", "the total size of the HID descriptor.", 0, 1);

    bDescriptorType = GetDataByte(base+1);
     _row = Find (DescriptorTypeTable, bDescriptorType);
    AddByteEntry( "bDescriptorType", GetDescriptorTypeString( _row[1]), 0, 1);

    bcdHID          = GetDataWord(base+2);
    AddWordEntry( "bcdHID", "Numeric expression identifying the HID Class Specification release.", 0, 0);

     bCountryCode    = GetDataByte (base+4);
     if (bCountryCode > sizeof(CountryCodeList)) tootip = "Reserved";

    else tooltip = CountryCodeList[bCountryCode];
    AddByteEntry("bCountryCode", tooltip, 0);

     bNumDescriptor  = GetDataByte (base+5);
    AddByteEntry ("bNumDescriptor", "number of class descriptors.", 0, 1);

    bDescriptortype = GetDataByte (base+6);
     _row = Find(DescriptorTypeTable, bDescriptortype );
    AddByteEntry("bDescriptorType", _row[1], 0);

    wDescriptorLen  = GetDataWord (base+7);
    AddWordEntry("wDescriptorLen", "the total size of the Report descriptor.", 0, 1);

    return 1;

}


REPORT_DESCRIPTOR()
{
    DescriptorCellString = "REPORT Descriptor";

    AddDataHeader( "REPORT Descriptor", in.DataLength - 8 );
    CurrentIndex = Base;
    Hid_Report_sub();
    return GetFinalText();
}

Hid_Report_sub()
{
# first byte decodes as this: bSize(0-1), bType (2-3), bTag(4-7)

   byte_prefix  = GetDataByte(CurrentIndex);CurrentIndex = CurrentIndex + sizeOf_b;
   bSize = Find (ShortItemSize, (byte_prefix & 0x03));
   bType = Find (ReportItemType, (byte_prefix & 0x0C) >>2);
   select
        {
        bType[1] == "Main"      : bTag = Find (ReportMainItemTag,((byte_prefix & 0xF0)>> 4));
        bType[1] == "Global"    : bTag = Find (ReportGlobalItemTag,((byte_prefix & 0xF0)>> 4));
        bType[1] == "Local"     : bTag = Find (ReportLocalItemTag,((byte_prefix & 0xF0)>> 4));
        };
   AddByteEntry( "Prefix byte", FormatEx ("bSize: 0x%02X, bType: %s, bTag: %s ", bSize[1], bType[1], bTag[1]), 0);
   if (bSize[1] == 1)
   {
       ReportData = GetDataByte(CurrentIndex);
       CurrentIndex = CurrentIndex + 1;
       if (bTag[2] != null)
       {
           str = Call(bTag[2]);
           AddByteEntry("Data", bTag[1] + str, 0);
       }
       else
           AddByteEntry("Data", "Extra Data", 0);
   }
   else if (bSize[1] == 2)
   {
       ReportData = GetDataWord(CurrentIndex);
       CurrentIndex = CurrentIndex + 2;
       if (bTag[2] != null)
       {
           str = Call(bTag[2]);
           AddWordEntry("Data", bTag[1] + str, 0);
       }
       else
           AddWordEntry("Data", "Extra Data", 0);
   }
   else if (bSize[1] == 4)
   {
       ReportData = GetDataLong(CurrentIndex);
       CurrentIndex = CurrentIndex + 4;
       if (bTag[2] != null)
       {
           str = Call(bTag[2]);
           AddDwordEntry("Data", bTag[1] + str, 0);
       }
       else
           AddDwordEntry("Data", "Extra Data", 0);
   }
    # we do nothing if bSize[1] == 0

   if (DataAvailable(CurrentIndex) >0)
   {
       Hid_Report_sub();
      # AddByteEntry( "Data Avail",  FormatEx (" 0x%04X", (in.DataLength - CurrentIndex)  ), 0);
   }
return 1;
}

PHYSICAL_DESCRIPTOR()
{
    DescriptorCellString = "PHYSICAL Descriptor";

    AddDataHeader( "PHYSICAL Descriptor", in.DataLength - 8 );
    if ((wValue & 0x00FF) == 0x00)
        Hid_Physical_Zero_sub();
    else
        Hid_Physiscal_sub();
    return GetFinalText();
}

Hid_Physical_sub()
{
# bPhysicalInfo formats: Bias(7..5) Preference(4..0)

    bPhysicalInfo = GetDataByte(CurrentIndex);CurrentIndex = CurrentIndex + sizeOf_b;
    Bias = Find( BiasTable, ((bPhysicalInfo & b11100000 ) >> 5));
    Preference = bPhysicalInfo & b00011111 ;
    AddByteEntry( "bPhysicalInfo", FormatEx ("Bias: 0x%02X, Preference: 0x%02X ", Bias[1], Prererence), 0);
    numDescriptors = (DataAvailable(CurrentIndex)) / 2;
    if (numDescriptors >=1 )
    {
        for( i = 1; i <= numDescriptors; i++)
        {
            dPhysical   = GetDataWord(CurrentIndex);CurrentIndex = CurrentIndex + sizeOf_w;
            bDesignator = ( dPhysical & 0xFF00 ) >> 8 ;
            bFlags      = ( dPhysical & 0x00FF );
            Qualifier   = bFlags & b11100000;
            Effort      = bFlags & b0001111;
            if (bDesignator > sizeof(DesignatorList)) Designator_toottip = "Reserved";
            else Designator_toottip = DesignatorList[bDesignator];
            if (Qualifier > sizeof(QualifierList)) Qualifier_tooltip = "Reserved";
            else Qualifier_tooltip = QualifierList[Qualifier];
            AddByteEntry( "dPhysical", FormatEx ("bDesignator: %s, Qualifier: %s ", Designator_toottip, Qualifier_tooltip), 0);
        }
    }
}

Hid_Physiscal_Zero_sub()
{
    bNumber = GetDataByte(CurrentIndex);CurrentIndex = CurrentIndex + sizeOf_b;
    AddByteEntry( "bNumber", "Numeric expression specifying the number of Physical Descriptor sets.", 0);
    bLength = GetDataByte(CurrentIndex);CurrentIndex = CurrentIndex + sizeOf_b;
    AddByteEntry( "bLength", "Length of each Physical descriptor", 0);
}


ReportSubfunctionInput()
{
    str = "(";
    if ((ReportData & 0x00000001) == 0)
        str += "Data, ";
    else
        str += "Constant, ";

    if ((ReportData & 0x00000002) == 0)
        str += "Array, ";
    else
        str += "Variable, ";

    if ((ReportData & 0x00000004) == 0)
        str += "Absolute, ";
    else
        str += "Relative, ";

    if ((ReportData & 0x00000008) == 0)
        str += "No Wrap, ";
    else
        str += "Wrap, ";

    if ((ReportData & 0x00000010) == 0)
        str += "Linear, ";
    else
        str += "Non Linear, ";

    if ((ReportData & 0x00000020) == 0)
        str += "Preferred State, ";
    else
        str += "No Preferred, ";

    if ((ReportData & 0x00000040) == 0)
        str += "No Null Position, ";
    else
        str += "Null State, ";

    if ((ReportData & 0x00000100) == 0)
        str += "Bit Field";
    else
        str += "Buffered Bytes";

    str += ")";
    return str;


}

ReportSubfunctionOutput()
{
     str = "(";
    if ((ReportData & 0x00000001) == 0)
        str += "Data, ";
    else
        str += "Constant, ";

    if ((ReportData & 0x00000002) == 0)
        str += "Array, ";
    else
        str += "Variable, ";

    if ((ReportData & 0x00000004) == 0)
        str += "Absolute, ";
    else
        str += "Relative, ";

    if ((ReportData & 0x00000008) == 0)
        str += "No Wrap, ";
    else
        str += "Wrap, ";

    if ((ReportData & 0x00000010) == 0)
        str += "Linear, ";
    else
        str += "Non Linear, ";

    if ((ReportData & 0x00000020) == 0)
        str += "Preferred State, ";
    else
        str += "No Preferred, ";

    if ((ReportData & 0x00000040) == 0)
        str += "No Null Position, ";
    else
        str += "Null State, ";

    if ((ReportData & 0x00000080) == 0)
        str += "Non Volatile";
    else
        str += "Volatile";

    if ((ReportData & 0x00000100) == 0)
        str += "Bit Field";
    else
        str += "Buffered Bytes";

    str += ")";
    return str;
}

ReportSubfunctionFeature()
{
    return ReportSubfunctionOutput();
}


ReportSubfunctionCollection()
{
     str = "(";
    collection = Find (ReportCollectionTable, ReportData);
    str += collection[1] + " )";
    return str;
}

ReportSubfunctionUsagePage()
{
     str = "(";
    ReportUsagePage = ReportData;
    usagePage = Find (HIDUsageTable, ReportData);
    str += usagePage[1] + " )";
    return str;
}

ReportSubfunctionNum()
{
     str = "(";
    str += Format("0x%X", ReportData) + " )";
    return str;
}

ReportSubfunctionUsage()
{
    str = "(";
    usagePage = Find (HIDUsageTable, ReportUsagePage);
    kludge_row = Call(usagePage[2]);
    str += kludge_row;

    str += ")";
    return str;
}

ReportSubfunctionDelimiter()
{
     str = "(";
    if (ReportData == 0)
        str += "close set )";
    else if (ReportData == 1)
        str += "open set )";
    else
        str += Format("Unknown Value %d )", ReportData);
    return str;
}

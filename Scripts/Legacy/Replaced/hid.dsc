*******************************************************************************
*
*  FILENAME: hid.dsc
*
*  Copyright (C) 1999 Computer Access Technology Corporation
*
*  DESCRIPTION
*    This descriptor definition file is supplied by CATC.
*    This file defines HID class USB descriptors.
*    File version is 1.0.
*
*******************************************************************************


*******************************************************************************
* HID Descriptor definitions
*******************************************************************************
DescriptorName=HID
DescriptorType=0x21
ClassCode=0x03

AllOffsets={
 2=bcdHID
 4=bCountryCode
 5=bNumDescriptors
 6=bDescriptorType
 7=wDescriptorlength
}

Offset(2)={

   Size=2  
   BCD=TRUE
   FormatValue=Device compliant to the HID specification version %X.%02X   
}

Offset(4)={

   WordValue={
	0x00= Localisation Not Supported 
01= The hardware is localized for Arabic 
02= The hardware is localized for Belgian 
03= The hardware is localized for Canadian-Bilingual 
04= The hardware is localized for Canadian-French 
05= The hardware is localized for Czech Republic 
06= The hardware is localized for Danish 
07= The hardware is localized for Finnish 
08= The hardware is localized for French 
09= The hardware is localized for German 
10= The hardware is localized for Greek 
11= The hardware is localized for Hebrew 
12= The hardware is localized for Hungary 
13= The hardware is localized for International (ISO) 
14= The hardware is localized for Italian 
15= The hardware is localized for Japan (Katakana) 
16= The hardware is localized for Korean 
17= The hardware is localized for Latin American 
18= The hardware is localized for Netherlands/Dutch
19= The hardware is localized for Norwegian
20= The hardware is localized for Persian (Farsi)
21= The hardware is localized for Poland
22= The hardware is localized for Portuguese
23= The hardware is localized for Russia
24= The hardware is localized for Slovakia
25= The hardware is localized for Spanish
26= The hardware is localized for Swedish
27= The hardware is localized for Swiss/French
28= The hardware is localized for Swiss/German
29= The hardware is localized for Switzerland
30= The hardware is localized for Taiwan
31= The hardware is localized for Turkish-Q
32= The hardware is localized for UK
33= The hardware is localized for US
34= The hardware is localized for Yugoslavia
35= The hardware is localized for Turkish-F
   }
   FormatValue=The country code is 0x%02X

}

Offset(5)={

   FormatValue=The number of class descriptors is %i

}

Offset(6)={

   WordValue={
      0x22=The class descriptor is Report descriptor
   }
   FormatValue=The class descriptor type is 0x%02X

}

Offset(7)={
   Size=2
   FormatValue=The total size of the class descriptor is %d
}


*******************************************************************************
* HID Report and Phyzical Descriptor definitions
* Since this descriptors don't follow the standard descriptor format, USB Chief
* performs special decoding for them. It is using the same HID decoding DLL
* USB Inspector is using.
*******************************************************************************
DescriptorName=HID Report
DescriptorType=0x22
ClassCode=0x03

AllOffsets={
SpecialHIDtreatment
}


DescriptorName=HID Physical
DescriptorType=0x23
ClassCode=0x03

AllOffsets={
SpecialHIDtreatment
}

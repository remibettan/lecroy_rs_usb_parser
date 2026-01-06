# VideoIdentifiersTables.inc
#
# This file contains many of the tables that are used in all the .inc files and .dec files


#Table 2-1 Video Class-Specific VC Interface Descriptor Subtypes
#Value  Descriptor Subtype
set VideoClassSpecificVCInterfaceDescriptorSubtypesTable =
[
[ 0xFF, "Illegal" ],
[ 0x00, "VC_DESCRIPTOR_UNDEFINED"],
[ 0x01, "VC_HEADER"],
[ 0x02, "VC_INPUT_TERMINAL"],
[ 0x03, "VC_OUTPUT_TERMINAL"],
[ 0x04, "VC_SELECTOR_UNIT"],
[ 0x05, "VC_PROCESSING_UNIT"],
[ 0x06, "VC_EXTENSION_UNIT"]
];
    
#   1.1         Video Class-Specific VS Interface Descriptor Subtypes   
#   Table 2-2 Video Class-Specific VS Interface Descriptor Subtypes
#Value  Descriptor Subtype  
set VideoClassSpecificVSInterfaceDescriptorSubtypesTable =
[
[ 0xFF, "Illegal" ],
[ 0x00, "VS_UNDEFINED"],
[ 0x01, "VS_INPUT_HEADER"],
[ 0x02, "VS_OUTPUT_HEADER"],
[ 0x03, "VS_STILL_IMAGE_FRAME"],
[ 0x04, "VS_FORMAT_UNCOMPRESSED"],
[ 0x05, "VS_FRAME_UNCOMPRESSED"],
[ 0x06, "VS_FORMAT_MJPEG"],
[ 0x07, "VS_FRAME_MJPEG"],
[ 0x08, "VS_FORMAT_MPEG1"],
[ 0x09, "VS_FORMAT_MPEG2PS"],
[ 0x0A, "VS_FORMAT_MPEG2TS"],
[ 0x0B, "VS_FORMAT_MPEG4SL"],
[ 0x0C, "VS_FORMAT_DV"],
[ 0x0D, "VS_COLORFORMAT"],
[ 0x0E, "VS_FORMAT_VENDOR"],
[ 0x0F, "VS_FRAME_VENDOR"]
];
    
#   "These Terminal types describe Terminals that handle signals carried over the USB, through isochronous or bulk pipes. These Terminal types are valid for both Input and Output Terminals."          
#   Table 3-1 USB Terminal Types            
#Code   Terminal Type       I/O Description
set USBTerminalTypes =
[
[ 0xFF, "Illegal" ],
[ 0x0100, "TT_VENDOR_SPECIFIC"], #      I/O A Terminal dealing with a signal carried over a vendor-specific interface. The vendor-specific interface descriptor must contain a field that references the Terminal.
[ 0x0101, "TT_STREAMING"]       #      I/O A Terminal dealing with a signal carried over an endpoint in a VideoStreaming interface. The VideoStreaming interface descriptor points to the associated Terminal through the bTerminalLink field.
];              
#   2.2         Input Terminal Types            
#   These Terminal Types describe Terminals that are designed to capture video. They either are physically part of the video function or can be assumed to be connected to it in normal operation. These Terminal Types are valid only for Input Terminals          

                
#   Table 3-2 Input Terminal Types          
#Code   Terminal Type       I/O Description
set InputTerminalTypes =
[
[ 0xFF, "Illegal" ],
[ 0x0200, "ITT_VENDOR_SPECIFIC"],      #   I    Vendor-Specific Input Terminal.
[ 0x0201, "ITT_CAMERA"],               #   I    Camera sensor. To be used only in Camera Terminal descriptors.
[ 0x0202, "ITT_MEDIA_TRANSPORT_INPUT"] #   I    Sequential media. To be used only in Media Transport Terminal Descriptors.
];
                
#   2.3         Output Terminal Types           
#   These Terminal types describe Terminals that are designed to render video. They are either physically part of the video function or can be assumed to be connected to it in normal operation. These Terminal types are only valid for Output Terminals.         
#   Table 3-3 Output Terminal Types         
#Code   Terminal Type       I/O Description
set OutputTerminalTypes =
[
[ 0xFF, "Illegal" ],
[ 0x0300, "OTT_VENDOR_SPECIFIC"],       #      O   Vendor-Specific Output Terminal.
[ 0x0301, "OTT_DISPLAY"],                #      O   "Generic display (LCD, CRT, etc.)."
[ 0x0302, "OTT_MEDIA_TRANSPORT_OUTPUT"]  #      O   Sequential media . To be used only in Media Transport Terminal Descriptors.
];
                
#   2.4         External Terminal Types         
#   These Terminal types describe external resources and connections that do not fit under the categories of Input or Output Terminals because they do not necessarily translate video signals to or from the user of the computer. Most of them may be either Input or Output Terminals.           
#   Table 3-4 External Terminal Types           
#Code   Terminal type       I/O Description
set ExternalTerminalTypesTable =
[
[ 0xFF, "Illegal" ],
[ 0x0400, "EXTERNAL_VENDOR_SPECIFIC"],  #       I/O Vendor-Specific External Terminal.
[ 0x0401, "COMPOSITE_CONNECTOR"],       #       I/O Composite video connector.
[ 0x0402, "SVIDEO_CONNECTOR"],          #       I/O S-video connector.
[ 0x0403, "COMPONENT_CONNECTOR"]        #       I/O Component video connector.
];



set MonthTable = 
[
    [ "1", "January" ],
    [ "2", "February" ],
    [ "3", "March" ],
    [ "4", "April" ],
    [ "5", "May" ],
    [ "6", "June" ],
    [ "7", "July" ],
    [ "8", "August" ],
    [ "9", "September" ],
    [ "10", "October" ],
    [ "11", "November" ],
    [ "12", "December" ]
];
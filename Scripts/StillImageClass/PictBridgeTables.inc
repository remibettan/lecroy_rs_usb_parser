#  Copyright (c) 2006, LeCroy Corp. PSG - All Rights Reserved
#
#  PictBridgeTables.inc
#
# Define PictBridge defines base on CIPA DC-001-2003
#

set PictBridgeResultCodes =
[
    [ null, "Unrecognized code"],
    [ "10000000", "OK"],
    [ "10010000", "Not executed"],
    [ "10020000", "Operation not supported"],
    [ "10030000", "Operation not recognized"],
    [ "10020001", "A parameter used in the request was not recognized"],
    [ "10020002", "A parameter value used in the request is not allowed"],
    [ "10020003", "A required parameter is missing from the request"],
    [ "10020004", "The request could not be processed because the request was bigger than the receive buffer"]
];

set PictBridgePrintServiceAvailableCodes =
[
    [ null, "Unrecognized code"],
    [ "30000000", "False: Print Service is not available"],
    [ "30010000", "True: Print service is available"]
];

set PictBridgeQualitiesCodes = 
[
    [ null, "Unrecognized code"],
    ["50000000", "Default quality"],
    ["50010000", "normal"],
    ["50020000", "draft"],
    ["50030000", "fine"]
];

set PictBridgePaperSizesCodes =
[
    [ null, "Unrecognized code"],
    ["51000000", "Default record media size of Printer"],
    ["51010000", "L (89.0 mm x 127.0 mm)"],
    ["51020000", "2L (127.0 mm x 178.0 mm)"],
    ["51030000", "Hagaki Postcard (100.0 mm x 148.0 mm)"],
    ["51040000", "Card Size (54.0 mm x 85.6 mm)"],
    ["51050000", "100 mm x 150 mm"],
    ["51060000", "4” x 6” (101.6 mm x 152.4 mm)"],
    ["51070000", "8” x 10” (203.2 mm x 254.0 mm)"],
    ["51080000", "Letter (216.0 mm x 279.4 mm)"],
    ["510A0000", "11\" x 17\" (279.4 mm x 431.8 mm)"],
    ["511n0000", "An (n=0~9) (Note2)"],
    ["51140000", "A4 (210.0 mm x 297.0 mm)"],
    ["51160000", "A6 (105 mm x 148.5 mm)"],
    ["51200000", "B0"],
    ["51210000", "B1"],
    ["51220000", "B2"],
    ["51230000", "B3"],
    ["51240000", "B4"],
    ["51250000", "B5"],
    ["51260000", "B6"],
    ["51270000", "B7"],
    ["51280000", "B8"],
    ["51290000", "B9"],
    ["51810000", "89 mm Roll (L)"],
    ["51820000", "127 mm Roll (2L)"],
    ["51860000", "100 mm Roll (4 inch)"],
    ["51940000", "210 mm Roll (A4)"]
];

set PictBridgePaperTypesCodes =
[
    [ null, "Unrecognized code"],
    ["5200", "Default record media of Printer"],
    ["5201", "Plain Paper"],
    ["5202", "Photo Paper"],
    ["5203", "Fast Photo Paper"]
];

set PictBridgeFileTypesCodes =
[
    [ null, "Unrecognized code"],
    ["53000000", "Default fileType of Printer"],
    ["53010000", "Exif / JPEG Format"],
    ["53020000", "Exif Format"],
    ["53030000", "JPEG Format"],
    ["53040000", "TIFF/EP Format"],
    ["53050000", "FlashPix Format"],
    ["53060000", "BMP Format"],
    ["53070000", "CIFF Format"],
    ["53080000", "GIF Format"],
    ["53090000", "JFIF Format"],
    ["530A0000", "PCD Format"],
    ["530B0000", "PICT Format"],
    ["530C0000", "PNG Format"],
    ["530D0000", "TIFF Format"],
    ["530E0000", "TIFF/IT Format"],
    ["530F0000", "JP2 Format"],
    ["53100000", "JPX Format"],
    ["53110000", "Undefined non-image Format"],
    ["53120000", "Association"],
    ["53130000", "Script"],
    ["53140000", "Executable"],
    ["53150000", "Text"],
    ["53160000", "HTML"],
    ["53170000", "XHTML-Print"],
    ["53180000", "DPOF"],
    ["53190000", "AIFF"],
    ["531A0000", "WAV"],
    ["531B0000", "MP3"],
    ["531C0000", "AVI"],
    ["531D0000", "MPEG"],
    ["531E0000", "ASF"]
];

set PictBridgeDatePrintsCodes =
[
    [ null, "Unrecognized code"],
    ["54000000", "Default setting of Printer"],
    ["54010000", "off"],
    ["54020000", "on"]
];

set PictBridgeFileNamePrintsCodes =
[
    [ null, "Unrecognized code"],
    ["55000000", "Default setting of Printer"],
    ["55010000", "off"],
    ["55020000", "on"]
];

set PictBridgeImageOptimizesCodes =
[
    [ null, "Unrecognized code"],
    ["56000000", "Default setting of Printer"],
    ["56010000", "off"],
    ["56020000", "on"]
];

set PictBridgeLayoutsCodes =
[
    [ null, "Unrecognized code"],
    ["57000000", "Default Layout of Printer"],
    ["57010000", "1-Up Layout"],
    ["57020000", "2-Up Layout"],
    ["57030000", "3-Up Layout"],
    ["57040000", "4-Up Layout"],
    ["57050000", "5-Up Layout"],
    ["57060000", "6-Up Layout"],
    ["57070000", "7-Up Layout"],
    ["57080000", "8-Up Layout"],
    ["57090000", "9-Up Layout"],
    ["570A0000", "10-Up Layout"],
    ["570B0000", "11-Up Layout"],
    ["570C0000", "12-Up Layout"],
    ["570D0000", "13-Up Layout"],
    ["570E0000", "14-Up Layout"],
    ["570F0000", "15-Up Layout"],
    ["57100000", "16-Up Layout"],
    ["57110000", "17-Up Layout"],
    ["57120000", "18-Up Layout"],
    ["57130000", "19-Up Layout"],
    ["57140000", "20-Up Layout"],
    ["57150000", "21-Up Layout"],
    ["57160000", "22-Up Layout"],
    ["57170000", "23-Up Layout"],
    ["57180000", "24-Up Layout"],
    ["57190000", "25-Up Layout"],
    ["571A0000", "26-Up Layout"],
    ["571B0000", "27-Up Layout"],
    ["571C0000", "28-Up Layout"],
    ["571D0000", "29-Up Layout"],
    ["571E0000", "30-Up Layout"],
    ["571F0000", "31-Up Layout"],
    ["57200000", "32-Up Layout"],
    ["57210000", "33-Up Layout"],
    ["57220000", "34-Up Layout"],
    ["57230000", "35-Up Layout"],
    ["57240000", "36-Up Layout"],
    ["57250000", "37-Up Layout"],
    ["57260000", "38-Up Layout"],
    ["57270000", "39-Up Layout"],
    ["57280000", "40-Up Layout"],
    ["57290000", "41-Up Layout"],
    ["572A0000", "42-Up Layout"],
    ["572B0000", "43-Up Layout"],
    ["572C0000", "44-Up Layout"],
    ["572D0000", "45-Up Layout"],
    ["572E0000", "46-Up Layout"],
    ["572F0000", "47-Up Layout"],
    ["57300000", "48-Up Layout"],
    ["57310000", "49-Up Layout"],
    ["57320000", "50-Up Layout"],
    ["57330000", "51-Up Layout"],
    ["57340000", "52-Up Layout"],
    ["57350000", "53-Up Layout"],
    ["57360000", "54-Up Layout"],
    ["57370000", "55-Up Layout"],
    ["57380000", "56-Up Layout"],
    ["57390000", "57-Up Layout"],
    ["573A0000", "58-Up Layout"],
    ["573B0000", "59-Up Layout"],
    ["573C0000", "60-Up Layout"],
    ["573D0000", "61-Up Layout"],
    ["573E0000", "62-Up Layout"],
    ["573F0000", "63-Up Layout"],
    ["57400000", "64-Up Layout"],
    ["57410000", "65-Up Layout"],
    ["57420000", "66-Up Layout"],
    ["57430000", "67-Up Layout"],
    ["57440000", "68-Up Layout"],
    ["57450000", "69-Up Layout"],
    ["57460000", "70-Up Layout"],
    ["57470000", "71-Up Layout"],
    ["57480000", "72-Up Layout"],
    ["57490000", "73-Up Layout"],
    ["574A0000", "74-Up Layout"],
    ["574B0000", "75-Up Layout"],
    ["574C0000", "76-Up Layout"],
    ["574D0000", "77-Up Layout"],
    ["574E0000", "78-Up Layout"],
    ["574F0000", "79-Up Layout"],
    ["57500000", "80-Up Layout"],
    ["57510000", "81-Up Layout"],
    ["57520000", "82-Up Layout"],
    ["57530000", "83-Up Layout"],
    ["57540000", "84-Up Layout"],
    ["57550000", "85-Up Layout"],
    ["57560000", "86-Up Layout"],
    ["57570000", "87-Up Layout"],
    ["57580000", "88-Up Layout"],
    ["57590000", "89-Up Layout"],
    ["575A0000", "90-Up Layout"],
    ["575B0000", "91-Up Layout"],
    ["575C0000", "92-Up Layout"],
    ["575D0000", "93-Up Layout"],
    ["575E0000", "94-Up Layout"],
    ["575F0000", "95-Up Layout"],
    ["57600000", "96-Up Layout"],
    ["57610000", "97-Up Layout"],
    ["57620000", "98-Up Layout"],
    ["57630000", "99-Up Layout"],
    ["57640000", "100-Up Layout"],
    ["57650000", "101-Up Layout"],
    ["57660000", "102-Up Layout"],
    ["57670000", "103-Up Layout"],
    ["57680000", "104-Up Layout"],
    ["57690000", "105-Up Layout"],
    ["576A0000", "106-Up Layout"],
    ["576B0000", "107-Up Layout"],
    ["576C0000", "108-Up Layout"],
    ["576D0000", "109-Up Layout"],
    ["576E0000", "110-Up Layout"],
    ["576F0000", "111-Up Layout"],
    ["57700000", "112-Up Layout"],
    ["57710000", "113-Up Layout"],
    ["57720000", "114-Up Layout"],
    ["57730000", "115-Up Layout"],
    ["57740000", "116-Up Layout"],
    ["57750000", "117-Up Layout"],
    ["57760000", "118-Up Layout"],
    ["57770000", "119-Up Layout"],
    ["57780000", "120-Up Layout"],
    ["57790000", "121-Up Layout"],
    ["577A0000", "122-Up Layout"],
    ["577B0000", "123-Up Layout"],
    ["577C0000", "124-Up Layout"],
    ["577D0000", "125-Up Layout"],
    ["577E0000", "126-Up Layout"],
    ["577F0000", "127-Up Layout"],
    ["57800000", "128-Up Layout"],
    ["57810000", "129-Up Layout"],
    ["57820000", "130-Up Layout"],
    ["57830000", "131-Up Layout"],
    ["57840000", "132-Up Layout"],
    ["57850000", "133-Up Layout"],
    ["57860000", "134-Up Layout"],
    ["57870000", "135-Up Layout"],
    ["57880000", "136-Up Layout"],
    ["57890000", "137-Up Layout"],
    ["578A0000", "138-Up Layout"],
    ["578B0000", "139-Up Layout"],
    ["578C0000", "140-Up Layout"],
    ["578D0000", "141-Up Layout"],
    ["578E0000", "142-Up Layout"],
    ["578F0000", "143-Up Layout"],
    ["57900000", "144-Up Layout"],
    ["57910000", "145-Up Layout"],
    ["57920000", "146-Up Layout"],
    ["57930000", "147-Up Layout"],
    ["57940000", "148-Up Layout"],
    ["57950000", "149-Up Layout"],
    ["57960000", "150-Up Layout"],
    ["57970000", "151-Up Layout"],
    ["57980000", "152-Up Layout"],
    ["57990000", "153-Up Layout"],
    ["579A0000", "154-Up Layout"],
    ["579B0000", "155-Up Layout"],
    ["579C0000", "156-Up Layout"],
    ["579D0000", "157-Up Layout"],
    ["579E0000", "158-Up Layout"],
    ["579F0000", "159-Up Layout"],
    ["57A00000", "160-Up Layout"],
    ["57A10000", "161-Up Layout"],
    ["57A20000", "162-Up Layout"],
    ["57A30000", "163-Up Layout"],
    ["57A40000", "164-Up Layout"],
    ["57A50000", "165-Up Layout"],
    ["57A60000", "166-Up Layout"],
    ["57A70000", "167-Up Layout"],
    ["57A80000", "168-Up Layout"],
    ["57A90000", "169-Up Layout"],
    ["57AA0000", "170-Up Layout"],
    ["57AB0000", "171-Up Layout"],
    ["57AC0000", "172-Up Layout"],
    ["57AD0000", "173-Up Layout"],
    ["57AE0000", "174-Up Layout"],
    ["57AF0000", "175-Up Layout"],
    ["57B00000", "176-Up Layout"],
    ["57B10000", "177-Up Layout"],
    ["57B20000", "178-Up Layout"],
    ["57B30000", "179-Up Layout"],
    ["57B40000", "180-Up Layout"],
    ["57B50000", "181-Up Layout"],
    ["57B60000", "182-Up Layout"],
    ["57B70000", "183-Up Layout"],
    ["57B80000", "184-Up Layout"],
    ["57B90000", "185-Up Layout"],
    ["57BA0000", "186-Up Layout"],
    ["57BB0000", "187-Up Layout"],
    ["57BC0000", "188-Up Layout"],
    ["57BD0000", "189-Up Layout"],
    ["57BE0000", "190-Up Layout"],
    ["57BF0000", "191-Up Layout"],
    ["57C00000", "192-Up Layout"],
    ["57C10000", "193-Up Layout"],
    ["57C20000", "194-Up Layout"],
    ["57C30000", "195-Up Layout"],
    ["57C40000", "196-Up Layout"],
    ["57C50000", "197-Up Layout"],
    ["57C60000", "198-Up Layout"],
    ["57C70000", "199-Up Layout"],
    ["57C80000", "200-Up Layout"],
    ["57C90000", "201-Up Layout"],
    ["57CA0000", "202-Up Layout"],
    ["57CB0000", "203-Up Layout"],
    ["57CC0000", "204-Up Layout"],
    ["57CD0000", "205-Up Layout"],
    ["57CE0000", "206-Up Layout"],
    ["57CF0000", "207-Up Layout"],
    ["57D00000", "208-Up Layout"],
    ["57D10000", "209-Up Layout"],
    ["57D20000", "210-Up Layout"],
    ["57D30000", "211-Up Layout"],
    ["57D40000", "212-Up Layout"],
    ["57D50000", "213-Up Layout"],
    ["57D60000", "214-Up Layout"],
    ["57D70000", "215-Up Layout"],
    ["57D80000", "216-Up Layout"],
    ["57D90000", "217-Up Layout"],
    ["57DA0000", "218-Up Layout"],
    ["57DB0000", "219-Up Layout"],
    ["57DC0000", "220-Up Layout"],
    ["57DD0000", "221-Up Layout"],
    ["57DE0000", "222-Up Layout"],
    ["57DF0000", "223-Up Layout"],
    ["57E00000", "224-Up Layout"],
    ["57E10000", "225-Up Layout"],
    ["57E20000", "226-Up Layout"],
    ["57E30000", "227-Up Layout"],
    ["57E40000", "228-Up Layout"],
    ["57E50000", "229-Up Layout"],
    ["57E60000", "230-Up Layout"],
    ["57E70000", "231-Up Layout"],
    ["57E80000", "232-Up Layout"],
    ["57E90000", "233-Up Layout"],
    ["57EA0000", "234-Up Layout"],
    ["57EB0000", "235-Up Layout"],
    ["57EC0000", "236-Up Layout"],
    ["57ED0000", "237-Up Layout"],
    ["57EE0000", "238-Up Layout"],
    ["57EF0000", "239-Up Layout"],
    ["57F00000", "240-Up Layout"],
    ["57F10000", "241-Up Layout"],
    ["57F20000", "242-Up Layout"],
    ["57F30000", "243-Up Layout"],
    ["57F40000", "244-Up Layout"],
    ["57F50000", "245-Up Layout"],
    ["57F60000", "246-Up Layout"],
    ["57F70000", "247-Up Layout"],
    ["57F80000", "248-Up Layout"],
    ["57F90000", "249-Up Layout"],
    ["57FA0000", "250-Up Layout"],
    ["57FE0000", "Index Print"],
    ["57FF0000", "1-Up Borderless(full bleed) Printing"]
];

set PictBridgeFixedSizesCodes =
[
    [ null, "Unrecognized code"],
    ["58000000", "Default fixedSize of Printer"],
    ["58010000", "2 ½\" x 3 ¼\""],
    ["58020000", "3.5\" x 5\" (127 mm x 89 mm)"],
    ["58030000", "4\" x 6\""],
    ["58040000", "5\" x 7\" (178 mm x 127 mm)"],
    ["58050000", "8\" x10\""],
    ["58060000", "254 mm x 178 mm"],
    ["58070000", "110 mm x 74 mm"],
    ["58080000", "89 mm x 55 mm"],
    ["58090000", "100 mm x 148 mm"],
    ["580A0000", "6 cm x 8 cm"],
    ["580B0000", "7 cm x 10 cm"],
    ["580C0000", "9 cm x13 cm"],
    ["580D0000", "10 cm x15 cm"],
    ["580E0000", "13 cm x18 cm"],
    ["580F0000", "15 cm x 21 cm"],
    ["58100000", "18 cm x 24 cm"],
    ["58110000", "A4 (210 mm x 297 mm full bleed)"],
    ["58120000", "Letter (8.5\" x 11\" full bleed)"]
];

set PictBridgeCroppingsCodes =
[
    [ null, "Unrecognized code"],
    ["59000000", "Default setting of Printer"],
    ["59010000", "off"],
    ["59020000", "on"]
];

set PictBridgePaperTypeMinorCodes =
[
    [ null,  "Default type"],
    ["0001", "Separately cut sheets of an opaque material."],
    ["0002", "Separately cut sheets of an opaque material with a coating of unspecified type."],
    ["0003", "Separately cut sheets of an opaque material designed to minimize the spread of liquid inks. May be accomplished using a coating."],
    ["0004", "Separately cut sheets of an opaque material with a preprinted image."],
    ["0005", "Separately cut sheets of an opaque material with a preprinted letterhead."],
    ["0006", "Separately cut sheets of an opaque material that are punched with an unspecified hole pattern."],
    ["0007", "Separately cut sheets of vellum or other high quality opaque material."],
    ["0008", "Separately cut sheets of a heavy stock opaque material."],
    ["0009", "Separately cut sheets of a light stock opaque material."],
    ["000A", "Separately cut sheets of a transparent material"],
    ["000B", "Envelopes that can be used for conventional mailing purposes."],
    ["000C", "Envelopes that are not preprinted and have no windows."],
    ["000D", "Envelopes that have windows for addressing purposes"],
    ["000E", "Continuously connected sheets of an opaque material – which edge is connected is not specified."],
    ["000F", "Continuously connected sheets of an opaque material connected along the long edge."],
    ["0010", "Continuously connected sheets of an opaque material connected along the short edge."],
    ["0011", "Media with tabs (either pre-cut or fullcut)."],
    ["0012", "Media with tabs that are cut so that more than one tab is visible extending out beyond the edge of non-tabbed media in an Output-Document."],
    ["0013", "Media with a tab that runs the full length of the sheet so that only one tab is visible extending out beyond the edge of non-tabbed media in an Output-Document."],
    ["0014", "Form medium composed of multiple layers not pre-attached to one another; each sheet may be drawn separately from an input source."],
    ["0015", "Label stock (For example, a sheet of peel-off labels)."],
    ["0016", "Form medium composed of multiple layers which are pre-attached to one another; e.g., for use with impact printers."],
    ["0017", "A refreshable display."],
    ["0018", "A refreshable display which cannot scroll."],
    ["0019", "Separately cut sheets of an opaque material to produce photographic quality images. The coating is unspecified."],
    ["001A", "Separately cut sheets of an opaque material that has a “glossy” coating to produce photographic quality images."],
    ["001B", "Separately cut sheets of an opaque material that has a “high-gloss” coating to produce photographic quality images."],
    ["001C", "Separately cut sheets of an opaque material that has a “semi-gloss” coating to produce photographic quality images."],
    ["001D", "Separately cut sheets of an opaque material that has a “satin” coating to produce photographic quality images."],
    ["001E", "Separately cut sheets of an opaque material that has a “matte” coating to produce photographic quality images."],
    ["001F", "Separately cut sheets of film used to produce photographic quality images."],
    ["0020", "Separately cut sheet of a translucent film that the user can view with or without backlighting."],
    ["0021", "Separately cut sheets of a heavier or stiffer opaque material than stationery."]
];

set PictBridgeDpsPrintServiceStatusCodes =
[
    [ null, "Unrecognized code"],
    ["70000000", "Printing: The DPS job is active and the Printer is busy printing the DPS job."],
    ["70010000", "Idle: The DPS job is not active."],
    ["70020000", "Paused: The DPS job is active and the Printer is either paused due to an error or is waiting for user intervention or input."]
];

set PictBridgeJobEndReasonCodes =
[
    [ null, "Unrecognized code"],
    ["71000000", "Job not ended."],
    ["71010000", "Job ended normally."],
    ["71020000", "Job ended due to DPS_AbortJob with “abortstyle” = 90000000."],
    ["71030000", "Job ended due to DPS_AbortJob with “abortstyle” = 90010000."],
    ["71040000", "Job ended due to other reason."]
];

set PictBridgeErrorStatusCodes =
[
    [ null, "Unrecognized code"],
    ["72000000", "No error."],
    ["72010000", "Warning (recoverable error)."],
    ["72020000", "Fatal error (unrecoverable error)."]
];

set PictBridgeErrorReasonCodes =
[
    [ null, "Unrecognized code"],
    ["73000000", "No reason."],
    ["73010000", "Paper related error (default)."],
    ["73010100", "Paper is empty."],
    ["73010200", "Load Error - paper not loaded correctly."],
    ["73010300", "Eject Error - paper not ejected correctly."],
    ["73010400", "Media Error - paper not detected, paper skewed, roll paper cannot be cut or torn -off."],
    ["73010500", "Paper jam."],
    ["73010600", "Paper nearly empty."],
    ["73010700", "Paper type/paper size combination not supported, or paper found in Printer does not match request."],
    ["73020000", "Ink related reason (default)."],
    ["73020100", "Ink empty."],
    ["73020200", "Ink low."],
    ["73020300", "Waste ink error (waste-ink reservoir full)."],
    ["73030000", "Hardware related error (default)."],
    ["73030100", "Fatal error."],
    ["73030200", "Service call."],
    ["73030300", "Printer unavailable (performing maintenance or otherwise occupied)."],
    ["73030400", "Printer busy (processing a job from another source, e.g., a PC)."],
    ["73030500", "Lever error (lever position not correct)."],
    ["73030600", "Cover open."],
    ["73030700", "No marking agent (e.g., missing print head)."],
    ["73030800", "Ink Cover open."],
    ["73030900", "No Ink Cartridge"],
    ["73040000", "File related reason (default)."],
    ["73040100", "printInfo error (specified <printInfo> is too large)."],
    ["73040200", "File decode error (picture format of specified image cannot be decoded)."]
];

set PictBridgeDisconnectEnableCodes =
[
    [ null, "Unrecognized code"],
    ["74000000", "False: Cannot be disconnected. Printer is still accessing the DSC."],
    ["74010000", "True: Can be disconnected. Printer is finished accessing the DSC."]
];

set PictBridgeCapabilityChangedCodes =
[
    [ null, "Unrecognized code"],
    ["75000000", "False: Printer capability is unchanged."],
    ["75010000", "True: Printer capability has changed."]
];

set PictBridgeNewJobOKCodes =
[
    [ null, "Unrecognized code"],
    ["76000000", "False: Printer cannot accept a DPS_StartJob request now."],
    ["76010000", "True: Printer can accept a DPS_StartJob request now."]
];

set PictBridgeAbortStyleCodes =
[
    [ null, "Unrecognized code"],
    ["90000000", "Abort job immediately"],
    ["90010000", "Abort job after completing the current page"]
];


set PictBridgeCommandTable = 
[
    #-----------------------------------------------------------------------------------------------------------------------------
    # node name             , node description      , Function of node text in tooltip, Function of node tex description in tooltip
    #------------------------------------------------------------------------------------------------------------------------------
    [null                   , "Unrecognized Command", null, null],
    ["configurePrintService", "Parameters for DPS_ConfigurePrintService", null,null],
    ["dpsVersions"          , "The list of DPS versions that can be supported", null,null],
    ["vendorName"           , "Manufacturer's name", null,null],
    ["vendorSpecificVersion", "The vendor-specific profile version supported", null,null],
    ["productName"          , "Product name", null,null],
    ["serialNo"             , "The device serial number, provided as an ASCII string", null,null],
    ["result"               , "Operation result", null,"GetPictBridgeResultCodesString"],
    ["printServiceAvailable", "Indicates whether or not the Print Server is available for processing the Print Client's job", null,"GetPictBridgePrintServiceAvailableCodesString"],
    ["getCapability"        , "Parameters for DPS_GetCapability", null,null],
    ["capability"           , "Parameter specifying the printer attribute", null,null],
    ["qualities"            , "Requests a space-separated list of quality levels supported by the Printer","ConvertSpaceToLineBreak", "GetPictBridgeQualitiesCodesString"],
    ["paperSizes"           , "Requests a space-separated list of paperSize values supported by the Printer","ConvertSpaceToLineBreak","GetPictBridgePaperSizesCodesString"],
    ["paperTypes"           , "Requests a space-separated list of the paperType values supported by the Printer.When unqualified by the paperSize attribute, the entire set of paperTypes supported by the Printer is requested.When qualified by the paperSize attribute, only the set of paperTypes supported for the indicated paperSize is returned","ConvertSpaceToLineBreak","GetPictBridgePaperTypesCodesString"],
    ["fileTypes"            , "Requests a space-separated list of fileType values supported by the Printer","ConvertSpaceToLineBreak","GetPictBridgeFileTypesCodesString"],
    ["datePrints"           , "Requests information as to whether the Printer supports printing dates adjacent to images","ConvertSpaceToLineBreak","GetPictBridgeDatePrintsCodesString"],
    ["fileNamePrints"       , "Requests information as to whether the Printer supports printing file names adjacent to images","ConvertSpaceToLineBreak","GetPictBridgeFileNamePrintsCodesString"],
    ["imageOptimizes"       , "Requests information as to whether the Printer can enhance or optimize images","ConvertSpaceToLineBreak","GetPictBridgeImageOptimizesCodesString"],
    ["layouts"              , "Request for information about the Printer’s ability to support various page layouts.This parameter shall contain an attribute specifying the paperSize for which layout information is requested.That is, this parameter requests a list of layout parameters supported for a particular paperSize","ConvertSpaceToLineBreak","GetPictBridgeLayoutsCodesString"],
    ["paperSize"            , "The size of the paper", null,null],
    ["fixedSizes"           , "Requests a list of values supported by the Printer for fixed image size output","ConvertSpaceToLineBreak","GetPictBridgeFixedSizesCodesString"],
    ["croppings"            , "Requests an indication as to whether the Printer supports the cropping of images","ConvertSpaceToLineBreak","GetPictBridgeCroppingsCodesString"],
    ["getJobStatus"         , "Parameters for DPS_GetJobStatus", null,null],
    ["prtPID"               , "Three-digit decimal job number defined in the DPOF file.Only present when the Printer is processing a DPOF file; a response shall not contain both prtPID and imagesPrinted", null,null],
    ["filePath"             , "Path for the file", null,null],
    ["copyID"               , "Current three-digit decimal page number for the DPOF print job. Only present when the Printer is processing DPOF file;a response shall not contain both copyID and imagesPrinted", null,null],
    ["progress"             , "String value of N/T where N is the three-digit decimal number of the current page being printed and T is the three-digit decimal total number of pages to be printed for this job.The minimum value of N and T is one (001). If multiple jobs have been submitted by the DSC, the progress reported is for the first job submitted that has not yet completed", null,null],
    ["imagesPrinted"        , "Three-digit decimal indicating the number of images in the current job that have been printed.In the case of multiple copies of an image, each copy of the image shall be included in the overall count. This parameter shall be updated at the beginning of each page.A response shall not contain both imagesPrinted and prtPID or filePath or copyID", null,null],
    ["getDeviceStatus"      , "Parameters for DPS_GetDeviceStatus", null,null],
    ["dpsPrintServiceStatus", "Current print service status", null,"GetPictBridgeDpsPrintServiceStatusCodesString"],
    ["jobEndReason"         , "Indicates whether or not a job has terminated, and if so, whether it terminated normally or abnormally", null,"GetPictBridgeJobEndReasonCodesString"],
    ["errorStatus"          , "Current Printer status, including ‘no error’", null,"GetPictBridgeErrorStatusCodesString"],
    ["errorReason"          , "Reason(s) for current status, if other than ‘no error’", null,"GetPictBridgeErrorReasonCodesString"],
    ["disconnectEnable"     , "Indicates whether or not it is OK for the DSC to disconnect, since the Printer has all data necessary for the print job", null,"GetPictBridgeDisconnectEnableCodesString"],
    ["capabilityChanged"    , "Indicates whether or not the Printer's capabilities have changed since the last DPS_GetCapability operation", null,"GetPictBridgeCapabilityChangedCodesString"],
    ["newJobOK"             , "Indicates that the Printer is ready to receive another job from the DSC", null,"GetPictBridgeNewJobOKCodesString"],
    ["startJob"             , "Parameters for DPS_StartJob", null,null],
    ["jobConfig"            , "The requested job configuration parameters", null,null],
    ["quality"              , "Print quality level selected for the job", null,"GetPictBridgeQualitieCodesString"],
    ["paperType"            , "The type of the paper", null,"PictBridgePaperType"],
    ["fileType"             , "Image type for all the images selected for the job", null,"GetPictBridgeFileTypeCodesString"],
    ["datePrint"            , "Whether or not to print dates provided by printInfo date", null,"GetPictBridgeDatePrintCodesString"],
    ["fileNamePrint"        , "Whether or not to print file names given in printInfo fileName", null,"GetPictBridgeFileNamePrintCodesString"],
    ["imageOptimize"        , "Whether or not to enhance or optimize images", null,"GetPictBridgeImageOptimizeCodesString"],
    ["layout"               , "The page layout selected for the job", null,"GetPictBridgeLayoutCodesString"],
    ["fixedSize"            , "If present, provides the physical dimensions of the output image size for all images in this job.Note that fixedSize shall not be specified with layout at the same time", null,"GetPictBridgeFixedSizeCodesString"],
    ["cropping"             , "Whether or not to specify the cropping area to be printed", null,"GetPictBridgeCroppingCodesString"],
    ["printInfo"            , "Parameters for each image to be printed", null,null],
    ["croppingArea"         , "Position of upper-left, width and height of the area to be printed", null,null],
    ["fileID"               , "ID of the image file", null,null],
    ["fileName"             , "Filename to be printed", null,null],
    ["date"                 , "Date to be printed adjacent to image given by the Print Client (on DSC). The date is given as an arbitrary string", null,null],
    ["copies"               , "Number of copies to be printed of the image corresponding to fileID", null,null],
    ["prtPID"               , "prtPID is used for the DPOF restart operation", null,null],
    ["copyID"               , "copyID is used for the DPOF restart operation", null,null],
    ["abortJob"             , "Parameters for DPS_AbortJob", null,null],
    ["abortStyle"           , "Indicates whether the Print Server should abort after printing to the end of the current page", null,"GetPictBridgeAbortStyleCodesString"],
    ["continueJob"          , "Parameters for DPS_ContinueJob", null,null],
    ["notifyJobStatus"      , "Parameters for DPS_NotifyJobStatus", null,null],
    ["notifyDeviceStatus"   , "Parameters for DPS_NotifyDeviceStatus", null,null],
    ["getFileID"            , "Parameters for DPS_GetFileID", null,null],
    ["basePathID"           , "The fileID of the base directory for the filePath parameter.The fileID of a file can be specified as basePathID.In case of a DPOF parser in the Printer, the basePathID shall be the object ID for the “AUTPRINT.MRK” file", null,null],
    ["getFileInfo"          , "Parameters for DPS GetFileInfo", null,null],
    ["thumbFormat"          , "Indicates whether the thumbnail format is compressed or uncompressed", null,"GetPictBridgeFileTypeCodesString"],
    ["thumbSize"            , "Size in bytes of the thumbnail file associated with fileID (8-character hexadecimal)", null,null],
    ["getFile"              , "Parameters for DPS_GetFile", null,null],
    ["bytesRead"            , "Actual size in bytes of file that was transferred (8-character hexadecimal)", null,null],
    ["getPartialFile"       , "Parameters for DPS GetPartialFile", null,null],
    ["offset"               , "The offset in bytes from the beginning of the referenced file to the positionfrom which to start reading data (8-character hexadecimal)", null,null],
    ["maxSize"              , "Maximum number of bytes to read from the file (8-character hexadecimal)", null,null],
    ["getFileList"          , "Parameters for DPS_GetFileList", null,null],
    ["parentFileID"         , "The directory containing the files whose fileIDs are to be retrieved", null,null],
    ["maxNumIDs"            , "The maximum number of fileIDs to be retrieved (8-character hexadecimal)", null,null],
    ["fileIDs"              , "The list of fileIDs that were retrieved", null,null],
    ["numIDs"               , "Number of files that satisfy the request (8-character hexadecimal)", null,null],
    ["getThumb"             , "Parameters for DPS_ GetThumb", null, null]
];	

GetPictBridgeResultCodesString(lookupString)
{
	  result = Find(PictBridgeResultCodes, lookupString);
	  return result[1];
}

GetPictBridgePrintServiceAvailableCodesString(lookupString)
{
	  result = Find(PictBridgePrintServiceAvailableCodes, lookupString);
	  return result[1];
}

GetPictBridgeQualitiesCodesString(lookupString)
{
	  keyLength = sizeof(lookupString);
	  returnString = "";
	  for(i = 0; i + 8 <= keyLength ; i += 9)
	  {
	  	  subKey = Mid(lookupString, i, 8);
	  	  subResult = Find(PictBridgeQualitiesCodes, subKey);
	  	  returnString += subResult[1];
	  	  returnString += "\n";
	  }
	  if (Right(returnString, 1) == "\n")
	      returnString = Left(returnString, sizeof(returnString) - 1); # trim the last \n character
	  return returnString;
}
	  	  
	  
GetPictBridgePaperSizesCodesString(lookupString)
{
	  keyLength = sizeof(lookupString);
	  returnString = "";
	  for(i = 0; i + 8 <= keyLength ; i += 9)
	  {
	  	  subKey = Mid(lookupString, i, 8);
	  	  subResult = Find(PictBridgePaperSizesCodes, subKey);
	  	  returnString += subResult[1];
	  	  returnString += "\n";
	  }
	  if (Right(returnString, 1) == "\n")
	      returnString = Left(returnString, sizeof(returnString) - 1); # trim the last \n character
	  return returnString;
}
GetPictBridgePaperTypesCodesString(lookupString)
{
	  keyLength = sizeof(lookupString);
	  returnString = "";
	  for(i = 0; i + 8 <= keyLength ; i += 9)
	  {
	  	  subKey = Mid(lookupString, i, 8);
	      majorCode = Left(subKey, 4);
	      minorCode = Right(subKey, 4);
	      majorText = Find(PictBridgePaperTypesCodes, majorCode);
	      minorText = Find(PictBridgePaperTypeMinorCodes, minorCode);
	  	  returnString += majorText[1] + " -- " + minorText[1];
	  	  returnString += "\n";
	  }
	  if (Right(returnString, 1) == "\n")
	      returnString = Left(returnString, sizeof(returnString) - 1); # trim the last \n character
	  return returnString;
}

GetPictBridgeFileTypesCodesString(lookupString)
{
	  keyLength = sizeof(lookupString);
	  returnString = "";
	  for(i = 0; i + 8 <= keyLength ; i += 9)
	  {
	  	  subKey = Mid(lookupString, i, 8);
	  	  subResult = Find(PictBridgeFileTypesCodes, subKey);
	  	  returnString += subResult[1];
	  	  returnString += "\n";
	  }
	  if (Right(returnString, 1) == "\n")
	      returnString = Left(returnString, sizeof(returnString) - 1); # trim the last \n character
	  return returnString;
}

GetPictBridgeDatePrintsCodesString(lookupString)
{
	  keyLength = sizeof(lookupString);
	  returnString = "";
	  for(i = 0; i + 8 <= keyLength ; i += 9)
	  {
	  	  subKey = Mid(lookupString, i, 8);
	  	  subResult = Find(PictBridgeDatePrintsCodes, subKey);
	  	  returnString += subResult[1];
	  	  returnString += "\n";
	  }
	  if (Right(returnString, 1) == "\n")
	      returnString = Left(returnString, sizeof(returnString) - 1); # trim the last \n character
	  return returnString;
}

GetPictBridgeFileNamePrintsCodesString(lookupString)
{
	  keyLength = sizeof(lookupString);
	  returnString = "";
	  for(i = 0; i + 8 <= keyLength ; i += 9)
	  {
	  	  subKey = Mid(lookupString, i, 8);
	  	  subResult = Find(PictBridgeFileNamePrintsCodes, subKey);
	  	  returnString += subResult[1];
	  	  returnString += "\n";
	  }
	  if (Right(returnString, 1) == "\n")
	      returnString = Left(returnString, sizeof(returnString) - 1); # trim the last \n character
	  return returnString;
}

GetPictBridgeImageOptimizesCodesString(lookupString)
{
	  keyLength = sizeof(lookupString);
	  returnString = "";
	  for(i = 0; i + 8 <= keyLength ; i += 9)
	  {
	  	  subKey = Mid(lookupString, i, 8);
	  	  subResult = Find(PictBridgeImageOptimizesCodes, subKey);
	  	  returnString += subResult[1];
	  	  returnString += "\n";
	  }
	  if (Right(returnString, 1) == "\n")
	      returnString = Left(returnString, sizeof(returnString) - 1); # trim the last \n character
	  return returnString;
}

GetPictBridgeLayoutsCodesString(lookupString)
{
	  keyLength = sizeof(lookupString);
	  returnString = "";
	  for(i = 0; i + 8 <= keyLength ; i += 9)
	  {
	  	  subKey = Mid(lookupString, i, 8);
	  	  subResult = Find(PictBridgeLayoutsCodes, subKey);
	  	  returnString += subResult[1];
	  	  returnString += "\n";
	  }
	  if (Right(returnString, 1) == "\n")
	      returnString = Left(returnString, sizeof(returnString) - 1); # trim the last \n character
	  return returnString;
}

GetPictBridgeFixedSizesCodesString(lookupString)
{
	  keyLength = sizeof(lookupString);
	  returnString = "";
	  for(i = 0; i + 8 <= keyLength ; i += 9)
	  {
	  	  subKey = Mid(lookupString, i, 8);
	  	  subResult = Find(PictBridgeFixedSizesCodes, subKey);
	  	  returnString += subResult[1];
	  	  returnString += "\n";
	  }
	  if (Right(returnString, 1) == "\n")
	      returnString = Left(returnString, sizeof(returnString) - 1); # trim the last \n character
	  return returnString;
}

GetPictBridgeCroppingsCodesString(lookupString)
{
	  keyLength = sizeof(lookupString);
	  returnString = "";
	  for(i = 0; i + 8 <= keyLength ; i += 9)
	  {
	  	  subKey = Mid(lookupString, i, 8);
	  	  subResult = Find(PictBridgeCroppingsCodes, subKey);
	  	  returnString += subResult[1];
	  	  returnString += "\n";
	  }
	  if (Right(returnString, 1) == "\n")
	      returnString = Left(returnString, sizeof(returnString) - 1); # trim the last \n character
	  return returnString;
}

GetPictBridgeDpsPrintServiceStatusCodesString(lookupString)
{
	  result = Find(PictBridgeDpsPrintServiceStatusCodes, lookupString);
	  return result[1];
}

GetPictBridgeJobEndReasonCodesString(lookupString)
{
	  result = Find(PictBridgeJobEndReasonCodes, lookupString);
	  return result[1];
}

GetPictBridgeErrorStatusCodesString(lookupString)
{
	  result = Find(PictBridgeErrorStatusCodes, lookupString);
	  return result[1];
}

GetPictBridgeErrorReasonCodesString(lookupString)
{
	  result = Find(PictBridgeErrorReasonCodes, lookupString);
	  return result[1];
}
GetPictBridgeDisconnectEnableCodesString(lookupString)
{
	  result = Find(PictBridgeDisconnectEnableCodes, lookupString);
	  return result[1];
}
GetPictBridgeCapabilityChangedCodesString(lookupString)
{
	  result = Find(PictBridgeCapabilityChangedCodes, lookupString);
	  return result[1];
}

GetPictBridgeNewJobOKCodesString(lookupString)
{
	  result = Find(PictBridgeNewJobOKCodes, lookupString);
	  return result[1];
}
GetPictBridgeQualitieCodesString(lookupString)
{
	  result = Find(PictBridgeQualitiesCodes, lookupString);
	  return result[1];
}

GetPictBridgePaperTypeCodesString(lookupString)
{
	  majorCode = Left(lookupString, 4);
	  minorCode = Right(lookupString, 4);
	  majorText = Find(PictBridgePaperTypesCodes, majorCode);
	  minorText = Find(PictBridgePaperTypeMinorCodes, minorCode);
	  finalText = majorText[1] + " -- " + minorText[1];
	  return finalText;
}

GetPictBridgeFileTypeCodesString(lookupString)
{
	  result = Find(PictBridgeFileTypesCodes, lookupString);
	  return result[1];
}

GetPictBridgeDatePrintCodesString(lookupString)
{
	  result = Find(PictBridgeDatePrintsCodes, lookupString);
	  return result[1];
}

GetPictBridgeFileNamePrintCodesString(lookupString)
{
	  result = Find(PictBridgeFileNamePrintsCodes, lookupString);
	  return result[1];
}

GetPictBridgeImageOptimizeCodesString(lookupString)
{
	  result = Find(PictBridgeImageOptimizesCodes, lookupString);
	  return result[1];
}

GetPictBridgeLayoutCodesString(lookupString)
{
	  result = Find(PictBridgeLayoutsCodes, lookupString);
	  return result[1];
}

GetPictBridgeFixedSizeCodesString(lookupString)
{
	  result = Find(PictBridgeFixedSizesCodes, lookupString);
	  return result[1];
}

GetPictBridgeCroppingCodesString(lookupString)
{
	  result = Find(PictBridgeCroppingsCodes, lookupString);
	  return result[1];
}

GetPictBridgeAbortStyleCodesString(lookupString)
{
	  result = Find(PictBridgeAbortStyleCodes, lookupString);
	  return result[1];
}

ConvertSpaceToLineBreak(input)
{
	  output = "";
	  str_length = sizeof(input);
	  for (i = 0; i < str_length; i++)
	  {
	  	  temp = Mid(input, i, 1);
	  	  if (temp == " ")
	  	      output += "\n";
	  	  else
	  	      output += temp;
	  }
	  return output;
}
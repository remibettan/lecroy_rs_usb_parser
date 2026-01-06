*******************************************************************************
*
*  FILENAME: standard.dsc
*
*  Copyright (C) 1999 Computer Access Technology Corporation
*
*  DESCRIPTION
*    This descriptor definition file is supplied by CATC.
*    This file defines standard USB descriptors.
*    File version is 1.1.
*
*    09/24/2001  Added  DEVICE_QUALIFIER and OTHER_SPEED_CONFIGURATION 
*    10/01/2001  Added  OTG
*    05/11/2004  Added  INTERFACE_ASSOCIATION and Video and Miscellaneous classes
*
*******************************************************************************


*******************************************************************************
* DEVICE Descriptor definitions
*******************************************************************************
DescriptorName=DEVICE
DescriptorType=0x01

AllOffsets={
 2=bcdUSB
 4=bDeviceClass
 5=bDeviceSubClass
 6=bDeviceProtocol
 7=bMaxPacketSize0
 8=idVendor
10=idProduct
12=bcdDevice
14=iManufacturer
15=iProduct
16=iSerialNumber
17=bNumConfigurations
}

; bcdUSB  description
Offset(2)={

   Size=2  
   BCD=TRUE
   FormatValue=Device compliant to the USB specification version %X.%02X   
}

; bDeviceClass  description
Offset(4)={

   WordValue={
      0xFF=The device class is vendor-specific
      0x00=Each interface specifies its own class information
      0x01=The device belongs to the Audio Interface class
      0x02=The device belongs tot he Communication Class
      0x03=The device belongs to the HID class
      0x05=The device belongs to the Physical class
      0x06=The device belongs to the Image class
      0x07=The device belongs to the Printer class
      0x08=The device belongs to the Mass Storage class
      0x09=The device belongs to the HUB class
      0x0A=The device belongs to the CDC Data Class
      0x0B=The device belongs to the Chip Smart Card Class
      0x0D=The device belongs to the Content Security Class
      0x0E=The device belongs to the Video class
      0xDC=The device belongs to the Diagnostic Device Class 
      0xE0=The device belongs to the Wireless Controller Class

      0xEF=The device belongs to the Miscellaneous Device Class
      0xFE=The device belongs to the Application Specifc Class
      0xFF=The device belongs to the Vendor Specifc Class

   }
   FormatValue=The class code is 0x%02X

}

; bDeviceSubClass  description
Offset(5)={

   WordValue={
      0xFF=The device subclass is vendor-specific
      0x00=Each interface specifies its own subclass information
   }
   FormatValue=The subclass code is 0x%02X

}

; bDeviceProtocol  description
Offset(6)={

   WordValue={
      0xFF=The device protocol is vendor-specific
      0x00=No protocols on the device basis
   }
   FormatValue=The protocol code is 0x%02X

}

; bMaxPacketSize0  description
Offset(7)={

   WordValue={
      0x08=Maximum packet size for endpoint zero is 8
      0x10=Maximum packet size for endpoint zero is 16
      0x20=Maximum packet size for endpoint zero is 32
      0x40=Maximum packet size for endpoint zero is 64
   }
   FormatValue=Maximum packet size for endpoint zero is %d (invalid size)!

}

; idVendor  description
Offset(8)={

   Size=2
   WordValue={
   
; Downloaded and messaged from http://www.usb.org/app/pub/dump/comp_dump/

1000=Vendor ID is 1000: EndPoints Inc. / Aox
1001=Vendor ID is 1001: Thesys Microelectronics
1002=Vendor ID is 1002: Data Broadcasting
1003=Vendor ID is 1003: Atmel Corporation
1004=Vendor ID is 1004: Iwatsu America
1005=Vendor ID is 1005: Mitel
1006=Vendor ID is 1006: Mitsumi
1008=Vendor ID is 1008: Hewlett Packard
1009=Vendor ID is 1009: Genoa Technology
1010=Vendor ID is 1010: Oak Technology, Inc
1011=Vendor ID is 1011: Adaptec, Inc.
1012=Vendor ID is 1012: Diebold, Inc.
1013=Vendor ID is 1013: Siemens Electromechanical
1016=Vendor ID is 1016: Epson Research Center
1017=Vendor ID is 1017: KeyTronic Corp.
1019=Vendor ID is 1019: OPTi
1020=Vendor ID is 1020: Elitegroup Computer Systems
1021=Vendor ID is 1021: Xilinx
1022=Vendor ID is 1022: Farallon
1024=Vendor ID is 1024: National Semiconductor
1025=Vendor ID is 1025: National Registry
1026=Vendor ID is 1026: ALi Corporation
1027=Vendor ID is 1027: Future Technology Devices International Limited
1028=Vendor ID is 1028: NCR
1029=Vendor ID is 1029: Sand
1030=Vendor ID is 1030: Fujitsu-ICL Computers
1031=Vendor ID is 1031: Fujitsu Personal Systems
1032=Vendor ID is 1032: Quanta Computer
1033=Vendor ID is 1033: NEC Corporation
1034=Vendor ID is 1034: Kodak Co.
1035=Vendor ID is 1035: Weltrend Semiconductor
1036=Vendor ID is 1036: VTech Computers
1037=Vendor ID is 1037: VIA Technologies, Inc.
1038=Vendor ID is 1038: MCCI
1039=Vendor ID is 1039: Echo Speech
1041=Vendor ID is 1041: BUFFALO INC. / Melco
1042=Vendor ID is 1042: Award Software
1043=Vendor ID is 1043: Leadtek Research Inc.
1044=Vendor ID is 1044: Giga-Byte Technology Co., Ltd.
1046=Vendor ID is 1046: Winbond Electronics Corp.
1047=Vendor ID is 1047: Symbios Logic
1048=Vendor ID is 1048: AST Research
1049=Vendor ID is 1049: Samsung Info. Systems America
1050=Vendor ID is 1050: Phoenix Technologies Ltd.
1051=Vendor ID is 1051: d'TV
1053=Vendor ID is 1053: S3
1054=Vendor ID is 1054: Creative Labs
1055=Vendor ID is 1055: LCS Telegraphics
1056=Vendor ID is 1056: Chips and Technologies
1057=Vendor ID is 1057: Nokia Corporation
1058=Vendor ID is 1058: ADI System
1059=Vendor ID is 1059: CATC
1060=Vendor ID is 1060: Standard Microsystems Corp.
1061=Vendor ID is 1061: Motorola Semiconductors HK, Ltd.
1062=Vendor ID is 1062: Integrated Device Technology
1063=Vendor ID is 1063: Motorola
1064=Vendor ID is 1064: Advanced Gravis Computer
1065=Vendor ID is 1065: Cirrus Logic Inc.
1066=Vendor ID is 1066: Ericsson
1067=Vendor ID is 1067: Intel
1068=Vendor ID is 1068: Innovative Semiconductors, Inc.
1069=Vendor ID is 1069: Micronics
1070=Vendor ID is 1070: Acer
1071=Vendor ID is 1071: Molex Inc.
1072=Vendor ID is 1072: Fujitsu
1073=Vendor ID is 1073: Itac Systems
1074=Vendor ID is 1074: Unisys Corp.
1075=Vendor ID is 1075: Alps Electric
1076=Vendor ID is 1076: Samsung Info. Systems America
1077=Vendor ID is 1077: Hyundai Electronics America
1078=Vendor ID is 1078: Taugagreining HF
1079=Vendor ID is 1079: Framatome Connectors USA
1080=Vendor ID is 1080: Advanced Micro Devices
1081=Vendor ID is 1081: Voice Technologies Group
1085=Vendor ID is 1085: Lexmark International Inc.
1086=Vendor ID is 1086: LG Electronics USA Inc.
1087=Vendor ID is 1087: RadiSys
1088=Vendor ID is 1088: EIZO NANAO CORPORATION
1089=Vendor ID is 1089: Winbond Systems
1090=Vendor ID is 1090: Ericsson
1091=Vendor ID is 1091: Gateway 2000
1093=Vendor ID is 1093: Lucent Technologies
1094=Vendor ID is 1094: NMB Technologies Corporation
1095=Vendor ID is 1095: Momentum Microsystems
1098=Vendor ID is 1098: Shamrock Tech
1099=Vendor ID is 1099: WSI
1100=Vendor ID is 1100: CCL/ITRI
1101=Vendor ID is 1101: Siemens Nixdorf
1102=Vendor ID is 1102: Alps Electric Co., Ltd.
1103=Vendor ID is 1103: ThrustMaster
1104=Vendor ID is 1104: DFI
1105=Vendor ID is 1105: Texas Instruments
1106=Vendor ID is 1106: Mitsubishi Electronics America
1107=Vendor ID is 1107: CMD Technology
1108=Vendor ID is 1108: Vobis Microcomputer AG
1109=Vendor ID is 1109: Telematics International
1110=Vendor ID is 1110: Analog Devices, Inc.
1111=Vendor ID is 1111: Silicon Integrated Systems Corp.
1112=Vendor ID is 1112: KYE Systems Corp. (Mouse Systems) / Genius
1113=Vendor ID is 1113: Adobe Systems
1114=Vendor ID is 1114: Diamond Multimedia Systems
1115=Vendor ID is 1115: Renesas Technology Corp. / Hitachi
1117=Vendor ID is 1117: Northern Telecom
1118=Vendor ID is 1118: Microsoft Corporation
1120=Vendor ID is 1120: Ace Cad Enterprise
1121=Vendor ID is 1121: Primax Electronics
1123=Vendor ID is 1123: MGE UPS Systems
1124=Vendor ID is 1124: AMP/Tycoelectronics
1127=Vendor ID is 1127: AT&T Paradyne
1128=Vendor ID is 1128: Wieson Electronic
1130=Vendor ID is 1130: Cherry GMBH
1131=Vendor ID is 1131: American Megatrends
1132=Vendor ID is 1132: Toshiba
1133=Vendor ID is 1133: Logitech Inc.
1134=Vendor ID is 1134: Behavior Tech. Computer Corporation(BTC)
1135=Vendor ID is 1135: Crystal Semiconductor
1137=Vendor ID is 1137: Philips
1138=Vendor ID is 1138: Sun Microsystems
1139=Vendor ID is 1139: Sanyo Information Business
1140=Vendor ID is 1140: Sanyo Electric Co. Ltd.
1141=Vendor ID is 1141: Relisys/TECO Information System
1142=Vendor ID is 1142: AESP
1143=Vendor ID is 1143: Seagate Technology
1144=Vendor ID is 1144: Connectix
1145=Vendor ID is 1145: Advanced Peripheral Laboratories
1146=Vendor ID is 1146: Semtech Corporation / USAR Systems
1147=Vendor ID is 1147: Silitek
1148=Vendor ID is 1148: Dell Computer
1149=Vendor ID is 1149: Kensington
1150=Vendor ID is 1150: Agere Systems Inc. / Lucent Microelectronics
1151=Vendor ID is 1151: Plantronics, Inc.
1152=Vendor ID is 1152: Toshiba America Info. Systems
1153=Vendor ID is 1153: Zenith Data Systems
1154=Vendor ID is 1154: Kyocera Corporation
1155=Vendor ID is 1155: STMicroelectronics
1156=Vendor ID is 1156: Specialix
1157=Vendor ID is 1157: Nokia Monitors
1158=Vendor ID is 1158: ASUS Computers
1159=Vendor ID is 1159: Stewart Connector
1160=Vendor ID is 1160: Cirque
1161=Vendor ID is 1161: Foxconn / Hon Hai
1162=Vendor ID is 1162: S-MOS Systems
1164=Vendor ID is 1164: Alps Electric
1165=Vendor ID is 1165: Integrated Technology Express, Inc.
1167=Vendor ID is 1167: Eicon Tech.
1168=Vendor ID is 1168: United Microelectronics
1169=Vendor ID is 1169: Capetronic
1170=Vendor ID is 1170: Samsung Semiconductor, Inc.
1171=Vendor ID is 1171: MAG Technology
1173=Vendor ID is 1173: ESS Technology
1174=Vendor ID is 1174: Micron Electronics
1175=Vendor ID is 1175: Smile International
1176=Vendor ID is 1176: Capetronic/Kaohsiung
1177=Vendor ID is 1177: Yamaha Corporation
1178=Vendor ID is 1178: Gandalf Technologies
1179=Vendor ID is 1179: System Connection
1180=Vendor ID is 1180: Acer Advanced Labs
1181=Vendor ID is 1181: VLSI Technology
1183=Vendor ID is 1183: Compaq
1184=Vendor ID is 1184: Digital Equipment
1185=Vendor ID is 1185: SystemSoft
1186=Vendor ID is 1186: FirePower Systems
1187=Vendor ID is 1187: Trident Microsystems
1188=Vendor ID is 1188: Hitachi, Ltd.
1189=Vendor ID is 1189: Benq Corporation
1190=Vendor ID is 1190: Nokia Display Products
1191=Vendor ID is 1191: Visioneer
1192=Vendor ID is 1192: Multivideo Labs
1193=Vendor ID is 1193: Canon Inc. (Kosugi Office)
1194=Vendor ID is 1194: DaeWoo Telecom
1195=Vendor ID is 1195: Chromatic Research
1196=Vendor ID is 1196: Micro Audiometrics
1197=Vendor ID is 1197: Dooin Electronics
1199=Vendor ID is 1199: Winnov L.P.
1200=Vendor ID is 1200: Nikon Corporation
1201=Vendor ID is 1201: Pan International
1203=Vendor ID is 1203: IBM Corporation
1204=Vendor ID is 1204: Cypress Semiconductor
1205=Vendor ID is 1205: ROHM LSI Systems USA, LLC
1206=Vendor ID is 1206: Hint
1207=Vendor ID is 1207: Compal Electronics, Inc.
1208=Vendor ID is 1208: Seiko Epson Corp.
1209=Vendor ID is 1209: Rainbow Technologies
1210=Vendor ID is 1210: Toucan Systems
1211=Vendor ID is 1211: I-O Data Device, Inc.
1213=Vendor ID is 1213: Toshiba Electronics Taiwan
1214=Vendor ID is 1214: Telia Research AB
1215=Vendor ID is 1215: TDK Corporation
1217=Vendor ID is 1217: U.S. Robotics
1218=Vendor ID is 1218: Methode Electronics Far East
1219=Vendor ID is 1219: Maxi Switch
1220=Vendor ID is 1220: Lockheed Martin Energy Research
1221=Vendor ID is 1221: Fujitsu Ltd.
1222=Vendor ID is 1222: Toshiba America Electronic
1223=Vendor ID is 1223: Micro Macro Technologies
1224=Vendor ID is 1224: Konica Corporation
1226=Vendor ID is 1226: Lite-On Technology Corp.
1227=Vendor ID is 1227: Fuji Photo Film Co., Ltd.
1228=Vendor ID is 1228: Philips Semiconductors
1229=Vendor ID is 1229: Tatung America
1230=Vendor ID is 1230: ScanLogic
1231=Vendor ID is 1231: Myson Century, Inc.
1232=Vendor ID is 1232: Digi International
1233=Vendor ID is 1233: ITT Canon
1234=Vendor ID is 1234: Altec Lansing Technologies
1235=Vendor ID is 1235: VidUS
1236=Vendor ID is 1236: LSI Logic Inc.
1237=Vendor ID is 1237: Forte Technologies
1238=Vendor ID is 1238: Mentor Graphics / CAE Technology
1239=Vendor ID is 1239: Oki Semiconductor
1240=Vendor ID is 1240: Micro Chip Technology
1241=Vendor ID is 1241: Holtek Semiconductor, Inc.
1242=Vendor ID is 1242: Panasonic (Matsushita)
1243=Vendor ID is 1243: Hypertec
1244=Vendor ID is 1244: Huan Hsin Holdings Ltd.
1245=Vendor ID is 1245: Sharp Corporation
1246=Vendor ID is 1246: MindShare
1247=Vendor ID is 1247: Interlink Electronics
1249=Vendor ID is 1249: Iiyama Corporation
1250=Vendor ID is 1250: Exar
1251=Vendor ID is 1251: Zilog
1252=Vendor ID is 1252: ACC Microelectronics
1253=Vendor ID is 1253: Promise Technology
1254=Vendor ID is 1254: SCM Microsystems / Shuttle Technology
1255=Vendor ID is 1255: Elo TouchSystems
1256=Vendor ID is 1256: Samsung Electronics Co., Ltd.
1257=Vendor ID is 1257: PC-Tel
1258=Vendor ID is 1258: Sipex
1259=Vendor ID is 1259: Northstar Systems, Inc.
1260=Vendor ID is 1260: Tokyo Electron Device Limited
1261=Vendor ID is 1261: Annabooks
1263=Vendor ID is 1263: Pacific Electronic International
1264=Vendor ID is 1264: Daewoo Electronics
1265=Vendor ID is 1265: Victor Company of Japan, Limited
1266=Vendor ID is 1266: Chicony Electronics Co., Ltd.
1267=Vendor ID is 1267: Elan Microelectronics Corportation
1268=Vendor ID is 1268: Harting Elektronik
1269=Vendor ID is 1269: Fujitsu-ICL Systems
1270=Vendor ID is 1270: Norand
1271=Vendor ID is 1271: Newnex Technology Corp.
1272=Vendor ID is 1272: FuturePlus Systems
1273=Vendor ID is 1273: Brother Industries, Ltd.
1274=Vendor ID is 1274: Dallas Semiconductor
1275=Vendor ID is 1275: Biostar Microtech
1276=Vendor ID is 1276: SUNPLUS TECHNOLOGY CO., LTD.
1277=Vendor ID is 1277: Soliton Systems
1278=Vendor ID is 1278: PFU Limited
1279=Vendor ID is 1279: E-CMOS
1280=Vendor ID is 1280: SUH
1281=Vendor ID is 1281: Fujikura / DDK Electronics
1282=Vendor ID is 1282: Acer
1283=Vendor ID is 1283: Hitachi America
1284=Vendor ID is 1284: Hayes Microcomputer Products
1286=Vendor ID is 1286: 3Com
1287=Vendor ID is 1287: Hosiden Corporation
1288=Vendor ID is 1288: Clarion
1289=Vendor ID is 1289: Aztech Systems
1290=Vendor ID is 1290: Cinch Connectors
1291=Vendor ID is 1291: Cable System International
1292=Vendor ID is 1292: InnoMedia
1293=Vendor ID is 1293: Belkin Components
1294=Vendor ID is 1294: Neon Technology
1295=Vendor ID is 1295: Kawatsu Semiconductor
1296=Vendor ID is 1296: Sejin
1297=Vendor ID is 1297: N'ABLE Technologies
1298=Vendor ID is 1298: Hualon Microelectronics
1299=Vendor ID is 1299: digital-X
1300=Vendor ID is 1300: FCI Electronics/ Berg Electronics
1301=Vendor ID is 1301: ACTC
1302=Vendor ID is 1302: Longwell Electronics/Longwell Company
1303=Vendor ID is 1303: Butterfly Communications
1304=Vendor ID is 1304: EzKEY
1305=Vendor ID is 1305: Star Micronics Co., LTD
1306=Vendor ID is 1306: WYSE Technology
1307=Vendor ID is 1307: Silicon Graphics
1308=Vendor ID is 1308: Holco Enterprise
1309=Vendor ID is 1309: American Power Conversion
1310=Vendor ID is 1310: Scientific Atlanta, Inc.
1311=Vendor ID is 1311: Elite Electronics
1312=Vendor ID is 1312: Taiwan Semiconductor Manufacturing Co.
1313=Vendor ID is 1313: Airborn Connectors
1314=Vendor ID is 1314: ACON, Advanced-Connectek, Inc.
1315=Vendor ID is 1315: ATEN GMBH
1316=Vendor ID is 1316: Micro Devices Technology
1317=Vendor ID is 1317: PLX Technology, Inc. / NetChip Technology Inc.
1318=Vendor ID is 1318: Temic Matra
1319=Vendor ID is 1319: ALTRA
1320=Vendor ID is 1320: ATI Technologies, Inc.
1321=Vendor ID is 1321: Fast Security AG
1322=Vendor ID is 1322: Crescent Heart Software
1323=Vendor ID is 1323: Tekom Technologies, Inc
1324=Vendor ID is 1324: Canon Development Americas / Canon Information System
1325=Vendor ID is 1325: Avid Electronics
1326=Vendor ID is 1326: Standard Microsystems
1327=Vendor ID is 1327: Unicore Software
1328=Vendor ID is 1328: American Microsystems
1329=Vendor ID is 1329: Wacom Technology Corp.
1330=Vendor ID is 1330: Systech
1331=Vendor ID is 1331: Alcatel Mobile Phones
1332=Vendor ID is 1332: Motorola
1333=Vendor ID is 1333: LIH TZU Electric
1334=Vendor ID is 1334: Welch Allyn
1335=Vendor ID is 1335: Inventec Corporation
1336=Vendor ID is 1336: The SCO Group / Santa Cruz Operation
1337=Vendor ID is 1337: Shyh Shiun Terminals Co. LTD
1338=Vendor ID is 1338: Preh Werke Gmbh & Co. KG
1339=Vendor ID is 1339: Global Village Communication
1340=Vendor ID is 1340: Institut of Microelectronic & Mechatronic Systems
1341=Vendor ID is 1341: Silicon Architect
1342=Vendor ID is 1342: Electronic Accessory Specialists
1343=Vendor ID is 1343: Synopsys, Inc.
1344=Vendor ID is 1344: Universal Access
1345=Vendor ID is 1345: Sirf Technology
1347=Vendor ID is 1347: ViewSonic Corporation
1348=Vendor ID is 1348: Cristie Electronics
1349=Vendor ID is 1349: Veo / Xirlink
1350=Vendor ID is 1350: Polaroid
1351=Vendor ID is 1351: Anchor Chips
1352=Vendor ID is 1352: Tyan Computer
1353=Vendor ID is 1353: Pixera
1354=Vendor ID is 1354: Fujitsu Microelectronics
1355=Vendor ID is 1355: New Media
1356=Vendor ID is 1356: Sony Corporation
1357=Vendor ID is 1357: Try
1358=Vendor ID is 1358: Proside
1359=Vendor ID is 1359: WYSE Technology Taiwan
1360=Vendor ID is 1360: Fuji Xerox Co., Ltd.
1361=Vendor ID is 1361: CompuTrend  Systems
1362=Vendor ID is 1362: Philips Monitors
1363=Vendor ID is 1363: STMicroelectronics Imaging Division/ VLSI Vision
1364=Vendor ID is 1364: Dictaphone
1365=Vendor ID is 1365: ANAM S&T
1366=Vendor ID is 1366: Asahi Kasei Microsystems Co., Ltd.
1367=Vendor ID is 1367: ATEN International Co. Ltd.
1368=Vendor ID is 1368: Truevision
1369=Vendor ID is 1369: Cadence Design Systems
1370=Vendor ID is 1370: Kenwood USA
1371=Vendor ID is 1371: KnowledgeTek
1372=Vendor ID is 1372: Proton Electronic
1373=Vendor ID is 1373: Samsung
1374=Vendor ID is 1374: CTX
1375=Vendor ID is 1375: Mustek Systems
1376=Vendor ID is 1376: Interface
1377=Vendor ID is 1377: Oasis Design
1378=Vendor ID is 1378: Telex Communications
1379=Vendor ID is 1379: Immersion
1380=Vendor ID is 1380: Chinon Industries, Inc.
1381=Vendor ID is 1381: Peracom Networks
1382=Vendor ID is 1382: Monterey International Corp.
1383=Vendor ID is 1383: Xyratex
1384=Vendor ID is 1384: Quartz Ingenierie
1385=Vendor ID is 1385: SegaSoft
1386=Vendor ID is 1386: WACOM Co., Ltd.
1387=Vendor ID is 1387: Decicon
1388=Vendor ID is 1388: e-TEK Labs
1389=Vendor ID is 1389: EIZO
1390=Vendor ID is 1390: Elecom Co., Ltd.
1391=Vendor ID is 1391: Korea Data Systems
1392=Vendor ID is 1392: Epson America
1393=Vendor ID is 1393: Interex
1394=Vendor ID is 1394: Conexant Systems, Inc. / Rockwell Semiconductor Systems
1395=Vendor ID is 1395: Zoran Co. Personal Media Division/Nogatech
1396=Vendor ID is 1396: City University of Hong Kong
1397=Vendor ID is 1397: Swets & Zeitlinger BV
1398=Vendor ID is 1398: BAFO/Quality Computer Accessories
1399=Vendor ID is 1399: ELSA
1400=Vendor ID is 1400: Intrinsix
1401=Vendor ID is 1401: GVC
1402=Vendor ID is 1402: Samsung Electronics America
1403=Vendor ID is 1403: Y-E Data, Inc.
1404=Vendor ID is 1404: AVM GmbH
1405=Vendor ID is 1405: Shark Multimedia
1406=Vendor ID is 1406: Nintendo
1407=Vendor ID is 1407: Quickshot Technology
1408=Vendor ID is 1408: Denron
1409=Vendor ID is 1409: Racal Data Group
1410=Vendor ID is 1410: Roland Corporation
1411=Vendor ID is 1411: Padix Co., Ltd.
1412=Vendor ID is 1412: RATOC System Inc.
1413=Vendor ID is 1413: FlashPoint Technology
1414=Vendor ID is 1414: ZyXEL Communications
1415=Vendor ID is 1415: America Kotobuki Electronics
1416=Vendor ID is 1416: Sapien Design
1417=Vendor ID is 1417: Victron
1418=Vendor ID is 1418: Nohau
1419=Vendor ID is 1419: Infineon Technologies / Siemens Semiconductor
1420=Vendor ID is 1420: In Focus Systems
1421=Vendor ID is 1421: Micrel Semiconductor
1422=Vendor ID is 1422: Tripath Technology
1423=Vendor ID is 1423: Alcor Micro, Corp.
1424=Vendor ID is 1424: OMRON Corporation
1425=Vendor ID is 1425: Questra Consulting
1426=Vendor ID is 1426: Exide Electronics
1427=Vendor ID is 1427: Incite
1428=Vendor ID is 1428: Princeton Graphic Systems
1429=Vendor ID is 1429: Zoran Microelectronics
1430=Vendor ID is 1430: Microtouch Systems
1431=Vendor ID is 1431: Trisignal Communications
1432=Vendor ID is 1432: Niigata Canotec Co., Inc.
1433=Vendor ID is 1433: Brilliance Semiconductor
1434=Vendor ID is 1434: Spectrum Signal Processing
1435=Vendor ID is 1435: Iomega Corporation
1436=Vendor ID is 1436: A-Trend Technology
1437=Vendor ID is 1437: Advanced Input Devices
1438=Vendor ID is 1438: Intelligent Instrumentation
1439=Vendor ID is 1439: LaCie / Electronique D2
1440=Vendor ID is 1440: Vetronix
1441=Vendor ID is 1441: USC
1442=Vendor ID is 1442: Fuji Film Microdevices Co. Ltd.
1443=Vendor ID is 1443: TransDimension-NH LLC / ARC International / Vautomation
1444=Vendor ID is 1444: Ortek Technology, Inc.
1445=Vendor ID is 1445: Sampo Technology
1446=Vendor ID is 1446: Cisco Systems
1447=Vendor ID is 1447: Bose Corporation
1448=Vendor ID is 1448: Spacetec IMC
1449=Vendor ID is 1449: OmniVision Technologies, Inc.
1450=Vendor ID is 1450: Utilux South China
1451=Vendor ID is 1451: In-System Design
1452=Vendor ID is 1452: Apple Computer
1453=Vendor ID is 1453: Y.C. Cable U.S.A., Inc
1454=Vendor ID is 1454: Synopsys
1455=Vendor ID is 1455: Jing-Mold Enterprise
1456=Vendor ID is 1456: Fountain Technologies
1457=Vendor ID is 1457: First International Computer
1458=Vendor ID is 1458: Focus
1460=Vendor ID is 1460: eXputer
1461=Vendor ID is 1461: Dialogic
1462=Vendor ID is 1462: Proxima
1463=Vendor ID is 1463: Medianix Semiconductor
1464=Vendor ID is 1464: Agiler
1465=Vendor ID is 1465: Philips Research Laboratories
1466=Vendor ID is 1466: DigitalPersona, Inc.
1467=Vendor ID is 1467: Grey Cell Systems
1468=Vendor ID is 1468: Forward
1469=Vendor ID is 1469: RAFI GmbH & Co. KG
1470=Vendor ID is 1470: Tyco Electronics / Raychem
1471=Vendor ID is 1471: S & S Research
1472=Vendor ID is 1472: Keil Software
1473=Vendor ID is 1473: Kawasaki Microelectronics, Inc,
1474=Vendor ID is 1474: Mediaphonics S.A.
1477=Vendor ID is 1477: Central Data
1478=Vendor ID is 1478: Qualcomm, Inc
1479=Vendor ID is 1479: Qtronix
1480=Vendor ID is 1480: Foxlink/Cheng Uei Precision Industry Co., Ltd
1481=Vendor ID is 1481: Semtech
1482=Vendor ID is 1482: Ricoh Company Ltd.
1483=Vendor ID is 1483: Powerchip Semiconductor
1484=Vendor ID is 1484: ELSA Gmbh
1485=Vendor ID is 1485: Silicom
1486=Vendor ID is 1486: sci-worx GmbH / SICAN Gmbh
1487=Vendor ID is 1487: Sung Forn
1488=Vendor ID is 1488: Lunar
1489=Vendor ID is 1489: Brainboxes
1490=Vendor ID is 1490: Wave Systems
1493=Vendor ID is 1493: SuperGate
1494=Vendor ID is 1494: Philips Semiconductors
1495=Vendor ID is 1495: Thomas & Betts
1496=Vendor ID is 1496: Ultima Electronics
1497=Vendor ID is 1497: Axiohm Transaction Solutions
1498=Vendor ID is 1498: Microtek International Inc.
1499=Vendor ID is 1499: Sun
1500=Vendor ID is 1500: Lexar Media, Inc.
1501=Vendor ID is 1501: Delta Electronics Inc.
1504=Vendor ID is 1504: Symbol Technologies
1505=Vendor ID is 1505: Syntek Semiconductor Co., Ltd.
1507=Vendor ID is 1507: Genesys Logic, Inc.
1509=Vendor ID is 1509: Fuji Electric Co., Ltd.
1510=Vendor ID is 1510: Keithley Instruments
1513=Vendor ID is 1513: Kawasaki LSI
1515=Vendor ID is 1515: FFC
1519=Vendor ID is 1519: AVB
1520=Vendor ID is 1520: Canopus Co., Ltd.
1522=Vendor ID is 1522: Dexin
1523=Vendor ID is 1523: PI Engineering
1525=Vendor ID is 1525: Unixtar Technology Inc.
1526=Vendor ID is 1526: AOC International
1527=Vendor ID is 1527: RFC Distribution
1529=Vendor ID is 1529: PSC Scanning
1530=Vendor ID is 1530: STSL
1532=Vendor ID is 1532: Harman Multimedia
1533=Vendor ID is 1533: InterAct
1534=Vendor ID is 1534: CHIC TECHNOLOGY CORP
1535=Vendor ID is 1535: LeCroy Corporation
1536=Vendor ID is 1536: Barco Display Systems
1537=Vendor ID is 1537: Jazz Hipster
1538=Vendor ID is 1538: Vista Imaging
1539=Vendor ID is 1539: Novatek Microelectronics Corp.
1540=Vendor ID is 1540: Jean
1541=Vendor ID is 1541: Anchor
1542=Vendor ID is 1542: Royal Information Electronics
1543=Vendor ID is 1543: Bridge Information
1545=Vendor ID is 1545: SMK Manufacturing Inc.
1546=Vendor ID is 1546: Worthington Data Solutions
1547=Vendor ID is 1547: Solid Year
1548=Vendor ID is 1548: EEH Datalink GmbH
1551=Vendor ID is 1551: Joinsoon Electronics Mfg. Co., Ltd.
1553=Vendor ID is 1553: Totoku Electric Co., LTD.
1555=Vendor ID is 1555: TransAct Technologies Incorporated
1556=Vendor ID is 1556: Bio-Rad Laboratories
1558=Vendor ID is 1558: Future Techno Designs PVT. LTD.
1560=Vendor ID is 1560: MacAlly
1561=Vendor ID is 1561: Seiko Instruments Inc.
1564=Vendor ID is 1564: Act Labs
1565=Vendor ID is 1565: Quatech, Inc.
1566=Vendor ID is 1566: Nissei Electric
1568=Vendor ID is 1568: Alaris
1569=Vendor ID is 1569: ODU-Steckverbindungssysteme
1571=Vendor ID is 1571: Littelfuse, Inc.
1572=Vendor ID is 1572: Apex
1574=Vendor ID is 1574: Nippon Systems Development
1577=Vendor ID is 1577: Zida Technologies
1579=Vendor ID is 1579: Greatlink Electronics Taiwan
1581=Vendor ID is 1581: Taiwan Tai-Hao Enterprises
1582=Vendor ID is 1582: Mainsuper Enterprises Co., Ltd.
1583=Vendor ID is 1583: Sin Sheng Terminal & Machine Inc.
1588=Vendor ID is 1588: Micron Technology, Inc.
1590=Vendor ID is 1590: Sierra Imaging
1592=Vendor ID is 1592: Avision, Inc.
1593=Vendor ID is 1593: Chrontel, Inc.
1597=Vendor ID is 1597: Fong Kai Industrial
1599=Vendor ID is 1599: New Technology Cable
1600=Vendor ID is 1600: Hitex Development Tools
1601=Vendor ID is 1601: Woods Industries
1602=Vendor ID is 1602: VIA Medical
1604=Vendor ID is 1604: TEAC Corporation
1605=Vendor ID is 1605: Who? Vision Systems
1606=Vendor ID is 1606: UMAX
1607=Vendor ID is 1607: Acton Research
1608=Vendor ID is 1608: Inside Out Networks
1611=Vendor ID is 1611: White Mountain DSP
1612=Vendor ID is 1612: Ji-Haw Industrial Co., Ltd
1614=Vendor ID is 1614: Suyin Corporation
1615=Vendor ID is 1615: WIBU-Systems AG
1617=Vendor ID is 1617: Likom Technology Sdn. Bhd.
1618=Vendor ID is 1618: Stargate Solutions
1620=Vendor ID is 1620: Granite Microsystems
1621=Vendor ID is 1621: Space Shuttle Hi-Tech Co.,Ltd.
1622=Vendor ID is 1622: Glory Mark Electronic Ltd.
1623=Vendor ID is 1623: Tekcon Electronics Corp.
1626=Vendor ID is 1626: Optoelectronics
1630=Vendor ID is 1630: Silicon Graphics
1631=Vendor ID is 1631: Good Way Technology Co., Ltd. & GWC technology Inc
1632=Vendor ID is 1632: TSAY-E (BVI) International Inc.
1633=Vendor ID is 1633: Hamamatsu Photonics K.K.
1635=Vendor ID is 1635: Topmax Electronic Co., Ltd.
1639=Vendor ID is 1639: Aiwa
1640=Vendor ID is 1640: WordWand
1641=Vendor ID is 1641: Oce' Printing Systems GmbH
1642=Vendor ID is 1642: Total Technologies, Ltd.
1643=Vendor ID is 1643: Linksys
1645=Vendor ID is 1645: Entrega
1646=Vendor ID is 1646: Acer Semiconductor America
1647=Vendor ID is 1647: SigmaTel, Inc.
1650=Vendor ID is 1650: Labtec Inc.
1651=Vendor ID is 1651: HCL
1652=Vendor ID is 1652: Key Mouse Electronic
1653=Vendor ID is 1653: Draytech
1654=Vendor ID is 1654: Teles AG
1655=Vendor ID is 1655: Aiwa
1656=Vendor ID is 1656: ACARD Technology Corp.
1659=Vendor ID is 1659: Prolific Technology, Inc.
1660=Vendor ID is 1660: Efficient Networks
1661=Vendor ID is 1661: Hohner
1662=Vendor ID is 1662: Intermec
1663=Vendor ID is 1663: Virata
1664=Vendor ID is 1664: Realtek Semiconductor Corp., CPP Div.
1665=Vendor ID is 1665: Siemens Information and Communication Products
1668=Vendor ID is 1668: Actiontec Electronics
1670=Vendor ID is 1670: Minolta Co., Ltd.
1674=Vendor ID is 1674: Pertech
1678=Vendor ID is 1678: CH Products
1680=Vendor ID is 1680: Golden Bridge Electech Inc.
1683=Vendor ID is 1683: Hagiwara Sys-Com Co., Ltd.
1684=Vendor ID is 1684: Lego Group
1688=Vendor ID is 1688: Chuntex (CTX)
1689=Vendor ID is 1689: Tektronix, Inc.
1690=Vendor ID is 1690: Askey Computer Corporation
1691=Vendor ID is 1691: Thomson Inc.
1693=Vendor ID is 1693: Hughes Network Systems (HNS)
1694=Vendor ID is 1694: Marx
1695=Vendor ID is 1695: Allied Data Technologies BV
1698=Vendor ID is 1698: Topro Technology
1699=Vendor ID is 1699: Saitek PLC
1700=Vendor ID is 1700: Xiamen Doowell Electron Co., Ltd.
1701=Vendor ID is 1701: Divio
1704=Vendor ID is 1704: Topaz Systems
1705=Vendor ID is 1705: Westell
1706=Vendor ID is 1706: Sysgration
1708=Vendor ID is 1708: Fujitsu Laboratories of America
1709=Vendor ID is 1709: Greatland Electronics Taiwan Ltd.
1710=Vendor ID is 1710: Professional Multimedia Testing Centre
1720=Vendor ID is 1720: Pixela Corporation
1721=Vendor ID is 1721: Alcatel Telecom
1722=Vendor ID is 1722: Smooth Cord & Connector Co., Ltd.
1723=Vendor ID is 1723: EDA
1724=Vendor ID is 1724: Oki Data Corporation
1725=Vendor ID is 1725: AGFA-Gevaert NV
1726=Vendor ID is 1726: AME Optimedia Technology Co. Ltd.
1727=Vendor ID is 1727: Leoco Corporation
1732=Vendor ID is 1732: Bizlink International Corporation
1733=Vendor ID is 1733: Hagenuk, GmbH
1734=Vendor ID is 1734: Infowave Software
1736=Vendor ID is 1736: SIIG, Inc.
1737=Vendor ID is 1737: Taxan (Europe)
1738=Vendor ID is 1738: Newer Technology
1739=Vendor ID is 1739: Synaptics Inc.
1740=Vendor ID is 1740: Terayon Communication Systems
1741=Vendor ID is 1741: Keyspan
1743=Vendor ID is 1743: SpheronVR AG
1744=Vendor ID is 1744: LapLink
1745=Vendor ID is 1745: Daewoo Electronics
1747=Vendor ID is 1747: Mitsubishi Electric Corporation
1749=Vendor ID is 1749: Toshiba
1750=Vendor ID is 1750: Aashima Technology B.V.
1751=Vendor ID is 1751: Network Computing Devices (NCD)
1752=Vendor ID is 1752: Technical Marketing Research
1754=Vendor ID is 1754: Phoenixtec Power
1755=Vendor ID is 1755: Paradyne
1756=Vendor ID is 1756: Foxlink Image Technology Co., Ltd.
1758=Vendor ID is 1758: Heisei Electronics
1760=Vendor ID is 1760: Multi-Tech Systems
1761=Vendor ID is 1761: ADS Technologies
1764=Vendor ID is 1764: Alcatel Microelectronics
1766=Vendor ID is 1766: Tiger Jet Network
1770=Vendor ID is 1770: Sirius Technologies
1775=Vendor ID is 1775: I.A.C. Geometrische Ingenieurs B.V.
1776=Vendor ID is 1776: T.N.C Industrial
1777=Vendor ID is 1777: Opcode Systems
1778=Vendor ID is 1778: Emine Technology Company
1782=Vendor ID is 1782: Wintrend Technology
1784=Vendor ID is 1784: Guillemot
1786=Vendor ID is 1786: HSD S.r.L
1789=Vendor ID is 1789: Boston Acoustics
1790=Vendor ID is 1790: Gallant Computer
1793=Vendor ID is 1793: Supercomal Wire & Cable SDN. BHD.
1795=Vendor ID is 1795: Bvtech Industry Inc.
1797=Vendor ID is 1797: NKK
1799=Vendor ID is 1799: SMC
1800=Vendor ID is 1800: Putercom
1801=Vendor ID is 1801: Silicon Systems
1802=Vendor ID is 1802: Oki Electric Industry Co., Ltd
1805=Vendor ID is 1805: Comoss Electronic Co., Ltd.
1806=Vendor ID is 1806: Excel Cell Electronic Co., Ltd.
1808=Vendor ID is 1808: Connect Tech Inc.
1809=Vendor ID is 1809: Magic Control Technology Corp.
1812=Vendor ID is 1812: NewMotion
1816=Vendor ID is 1816: Imation Corp.
1817=Vendor ID is 1817: Tremon Enterprises
1819=Vendor ID is 1819: Domain Technologies
1820=Vendor ID is 1820: Xionics Document Technologies
1821=Vendor ID is 1821: Eicon Networks Corporation
1827=Vendor ID is 1827: Centillium Communications Corporation
1830=Vendor ID is 1830: Vanguard International Semiconductor-America
1833=Vendor ID is 1833: Amitm
1838=Vendor ID is 1838: Sunix
1839=Vendor ID is 1839: ACS
1841=Vendor ID is 1841: Susteen
1842=Vendor ID is 1842: Goldfull Electronics & Telecommunications Corp.
1843=Vendor ID is 1843: ViewQuest Technologies, Inc./ Intel
1844=Vendor ID is 1844: Lasat Communications A/S
1845=Vendor ID is 1845: Asuscom Network
1846=Vendor ID is 1846: Lorom Industrial Co., Ltd.
1848=Vendor ID is 1848: Mad Catz, Inc.
1851=Vendor ID is 1851: Suncom Technologies
1854=Vendor ID is 1854: NEC
1861=Vendor ID is 1861: Syntech Information
1862=Vendor ID is 1862: ONKYO Corporation
1863=Vendor ID is 1863: Labway
1864=Vendor ID is 1864: Strong Man Enterprise
1865=Vendor ID is 1865: EVer Electronics
1866=Vendor ID is 1866: Ming Fortune Industry
1867=Vendor ID is 1867: Polestar Tech.
1868=Vendor ID is 1868: C-C-C Group PLC
1869=Vendor ID is 1869: Micronas GmbH
1870=Vendor ID is 1870: Digital Stream
1877=Vendor ID is 1877: Aureal Semiconductor
1879=Vendor ID is 1879: Network Technologies, Inc.
1891=Vendor ID is 1891: Midiman
1892=Vendor ID is 1892: Cyber Power System, Inc.
1893=Vendor ID is 1893: X-Rite Incorporated
1894=Vendor ID is 1894: Jess-Link Products Co., Ltd. (JPC)
1896=Vendor ID is 1896: Camtel Technology Corp.
1897=Vendor ID is 1897: Surecom Technology
1898=Vendor ID is 1898: Smart Technology Enablers
1899=Vendor ID is 1899: OMNIKEY AG
1900=Vendor ID is 1900: Partner Tech
1901=Vendor ID is 1901: Denso Corporation
1902=Vendor ID is 1902: Kuan Tech Enterprise
1903=Vendor ID is 1903: Jhen Vei Electronic Co., Ltd.
1908=Vendor ID is 1908: AmTRAN Technology
1909=Vendor ID is 1909: Longshine Electronics
1910=Vendor ID is 1910: Inalways
1911=Vendor ID is 1911: Comda Enterprise Corporation
1913=Vendor ID is 1913: Fairchild Semiconductor
1914=Vendor ID is 1914: Sankyo Seiki Mfg. Co., Ltd.
1915=Vendor ID is 1915: Linksys
1916=Vendor ID is 1916: Forward Electronics
1917=Vendor ID is 1917: Griffin Technology
1919=Vendor ID is 1919: Well Excellent & Most
1921=Vendor ID is 1921: SanDisk Corporation
1922=Vendor ID is 1922: Trackerball
1924=Vendor ID is 1924: Vivitar
1925=Vendor ID is 1925: NTT-ME
1929=Vendor ID is 1929: Logitec Corporation
1931=Vendor ID is 1931: Happ Controls
1934=Vendor ID is 1934: Brincom
1936=Vendor ID is 1936: Pro-Image Manufacturing
1937=Vendor ID is 1937: Copartner Wire and Cable Mfg. Corp.
1938=Vendor ID is 1938: Axis Communications AB
1939=Vendor ID is 1939: Wha Yu Industrial Co., Ltd.
1940=Vendor ID is 1940: ABL Electronics
1941=Vendor ID is 1941: RealChip
1942=Vendor ID is 1942: Certicom
1943=Vendor ID is 1943: Grandtech Semiconductor
1947=Vendor ID is 1947: Sagem
1949=Vendor ID is 1949: Alfadata
1953=Vendor ID is 1953: Digicom S.p.A.
1954=Vendor ID is 1954: National Technical Systems
1955=Vendor ID is 1955: ONNTO Corp.
1956=Vendor ID is 1956: Be
1958=Vendor ID is 1958: ADMtek Incorporated
1962=Vendor ID is 1962: corega K.K.
1963=Vendor ID is 1963: Freecom Technologies
1967=Vendor ID is 1967: Microtech
1968=Vendor ID is 1968: Trust Technologies
1969=Vendor ID is 1969: IMP
1970=Vendor ID is 1970: Motorola BCS
1971=Vendor ID is 1971: Plustek, Inc.
1972=Vendor ID is 1972: Olympus Optical
1973=Vendor ID is 1973: Mega World International Ltd.
1974=Vendor ID is 1974: Marubun
1975=Vendor ID is 1975: TIME Interconnect Ltd.
1976=Vendor ID is 1976: AboCom Systems, Inc.
1980=Vendor ID is 1980: Canon Computer Systems
1981=Vendor ID is 1981: Webgear
1982=Vendor ID is 1982: Veridicom
1984=Vendor ID is 1984: Code Mercenaries Hard- und Software GmbH
1988=Vendor ID is 1988: Datafab Systems Inc.
1989=Vendor ID is 1989: APG Cash Drawer
1990=Vendor ID is 1990: ShareWave
1991=Vendor ID is 1991: Powertech Industrial
1992=Vendor ID is 1992: B.U.G.
1993=Vendor ID is 1993: Allied Telesyn International
1994=Vendor ID is 1994: AVerMedia Technologies, Inc.
1995=Vendor ID is 1995: Kingmax Technology
1996=Vendor ID is 1996: Carry Computer Eng., Co., Ltd.
1997=Vendor ID is 1997: Elektor
1999=Vendor ID is 1999: Casio Computer
2000=Vendor ID is 2000: Dazzle
2001=Vendor ID is 2001: D-Link System
2002=Vendor ID is 2002: Aptio Products
2003=Vendor ID is 2003: Cyberdata Corp.
2007=Vendor ID is 2007: GCC Technologies
2010=Vendor ID is 2010: Arasan Chip Systems
2015=Vendor ID is 2015: David Electronics Company, Ltd.
2017=Vendor ID is 2017: Ambient Technologies
2018=Vendor ID is 2018: Elmeg
2019=Vendor ID is 2019: Planex Communications
2020=Vendor ID is 2020: Movado Enterprise
2021=Vendor ID is 2021: QPS
2022=Vendor ID is 2022: Allied Cable Corporation
2023=Vendor ID is 2023: Mirvo Toys
2024=Vendor ID is 2024: Labsystems
2026=Vendor ID is 2026: Iwatsu Electric
2027=Vendor ID is 2027: Double-H Technology Co., Ltd.
2028=Vendor ID is 2028: Taiyo Electric Wire & Cable Co., Ltd.
2034=Vendor ID is 2034: General CADD
2038=Vendor ID is 2038: Circuit Assembly Corp
2039=Vendor ID is 2039: Century Corporation
2041=Vendor ID is 2041: Dotop Technology, Inc.
2042=Vendor ID is 2042: Draytek
2045=Vendor ID is 2045: Mark of the Unicorn
2049=Vendor ID is 2049: Mag-Tek
2050=Vendor ID is 2050: Mako Technologies, LLC
2051=Vendor ID is 2051: Zoom Telephonics
2057=Vendor ID is 2057: Genicom Technology
2058=Vendor ID is 2058: Evermuch Technology Co., Ltd.
2061=Vendor ID is 2061: Teco Image Systems
2064=Vendor ID is 2064: Personal Communication Systems
2067=Vendor ID is 2067: Mattel
2074=Vendor ID is 2074: MG Logic
2075=Vendor ID is 2075: Indigita Corporation
2076=Vendor ID is 2076: Mipsys
2078=Vendor ID is 2078: AlphaSmart, Inc.
2082=Vendor ID is 2082: Reudo
2085=Vendor ID is 2085: GC Protronics
2086=Vendor ID is 2086: Data Transit
2087=Vendor ID is 2087: BroadLogic
2088=Vendor ID is 2088: Sato Corporation
2089=Vendor ID is 2089: DirecTV Broadband
2093=Vendor ID is 2093: Handspring
2096=Vendor ID is 2096: Palm
2098=Vendor ID is 2098: Kouwell Electronics
2099=Vendor ID is 2099: Sourcenext
2101=Vendor ID is 2101: Action Star Enterprise Co., Ltd.
2105=Vendor ID is 2105: Samsung Techwin
2106=Vendor ID is 2106: Accton Technology Corporation
2111=Vendor ID is 2111: Global Village
2112=Vendor ID is 2112: Argosy Research Inc.
2113=Vendor ID is 2113: Rioport.com
2116=Vendor ID is 2116: Welland Industrial Co., Ltd.
2118=Vendor ID is 2118: NETGEAR, Inc.
2125=Vendor ID is 2125: Minton Optic Industry
2126=Vendor ID is 2126: KB Gear
2127=Vendor ID is 2127: Empeg
2128=Vendor ID is 2128: Fast Point Technologies
2129=Vendor ID is 2129: Macronix International
2130=Vendor ID is 2130: CSEM
2132=Vendor ID is 2132: ActiveWire
2136=Vendor ID is 2136: Hitachi Maxell
2137=Vendor ID is 2137: Minolta Systems Laboratory
2138=Vendor ID is 2138: Xircom
2146=Vendor ID is 2146: Teletrol Systems
2147=Vendor ID is 2147: Filanet
2148=Vendor ID is 2148: NetGear
2154=Vendor ID is 2154: Emagic Soft-und Hardware Gmbh
2156=Vendor ID is 2156: DeTeWe - Deutsche Telephonwerke AG &
2158=Vendor ID is 2158: System TALKS Inc.
2159=Vendor ID is 2159: MEC IMEX INC/HPT
2160=Vendor ID is 2160: Metricom
2161=Vendor ID is 2161: SanDisk
2163=Vendor ID is 2163: Xpeed
2164=Vendor ID is 2164: A-Tec Subsystem, Inc.
2169=Vendor ID is 2169: Comtrol
2172=Vendor ID is 2172: Adesso/Kbtek America
2173=Vendor ID is 2173: Jaton
2174=Vendor ID is 2174: Fujitsu Computer Products of America
2175=Vendor ID is 2175: QualCore Logic Inc
2176=Vendor ID is 2176: APT Technologies
2179=Vendor ID is 2179: Recording Industry Association of America (RIAA)
2181=Vendor ID is 2181: Boca Research
2182=Vendor ID is 2182: XAC Automation Corp.
2183=Vendor ID is 2183: Hannstar Electronics
2187=Vendor ID is 2187: MassWorks
2194=Vendor ID is 2194: DioGraphy
2199=Vendor ID is 2199: Lauterbach
2204=Vendor ID is 2204: United Technologies Research Cntr.
2205=Vendor ID is 2205: Icron Technologies Corporation
2206=Vendor ID is 2206: NST Co., Ltd.
2207=Vendor ID is 2207: Primex Aerospace
2213=Vendor ID is 2213: e9
2216=Vendor ID is 2216: Andrea Electronics
2222=Vendor ID is 2222: Macally (Mace Group, Inc.)
2228=Vendor ID is 2228: Sorenson Vision
2232=Vendor ID is 2232: J. Gordon Electronic Design
2233=Vendor ID is 2233: RadioShack Corporation
2235=Vendor ID is 2235: Texas Instruments Japan
2237=Vendor ID is 2237: Citizen Watch
2243=Vendor ID is 2243: Precise Biometrics
2244=Vendor ID is 2244: Proxim
2247=Vendor ID is 2247: TAI TWUN ENTERPRISE CO., LTD.
2248=Vendor ID is 2248: 2Wire, Inc
2249=Vendor ID is 2249: Nippon Telegraph and Telephone
2250=Vendor ID is 2250: AIPTEK International Inc.
2253=Vendor ID is 2253: Jue Hsun Ind.
2254=Vendor ID is 2254: Long Well Electronics
2255=Vendor ID is 2255: Productivity Enhancement Products
2257=Vendor ID is 2257: smartBridges
2259=Vendor ID is 2259: Virtual Ink
2260=Vendor ID is 2260: Siemens PC Systems
2265=Vendor ID is 2265: Increment P
2269=Vendor ID is 2269: Billionton Systems, Inc.
2270=Vendor ID is 2270: NonRegisteredID?
2271=Vendor ID is 2271: Spyrus
2275=Vendor ID is 2275: Olitec
2276=Vendor ID is 2276: Pioneer Corporation
2277=Vendor ID is 2277: Litronic
2278=Vendor ID is 2278: GEMPLUS
2279=Vendor ID is 2279: Pan-International Wire & Cable
2280=Vendor ID is 2280: Integrated Memory Logic
2281=Vendor ID is 2281: Extended Systems
2282=Vendor ID is 2282: Ericsson
2284=Vendor ID is 2284: M-Systems Flash Disk Pioneers
2286=Vendor ID is 2286: CCSI/Hesso
2288=Vendor ID is 2288: Corex Technologies
2289=Vendor ID is 2289: CTI Electronics Corporation
2293=Vendor ID is 2293: SysTec
2294=Vendor ID is 2294: Logic 3 International
2296=Vendor ID is 2296: Keen Top International Enterprise
2297=Vendor ID is 2297: Wipro Technologies
2298=Vendor ID is 2298: Caere
2299=Vendor ID is 2299: Socket Communications
2300=Vendor ID is 2300: Sicon Cable Technology
2301=Vendor ID is 2301: Digianswer A/S
2303=Vendor ID is 2303: AuthenTec, Inc.
2304=Vendor ID is 2304: Pinnacle Systems
2305=Vendor ID is 2305: VST Technologies
2310=Vendor ID is 2310: FARADAY Technology Corp.
2313=Vendor ID is 2313: Audio-Technica Corp.
2314=Vendor ID is 2314: Trumpion Microelectronics
2315=Vendor ID is 2315: Neurosmith
2316=Vendor ID is 2316: Silicon Motion, Inc. - Taiwan
2317=Vendor ID is 2317: Multiport Computer Vertriebs GmbH
2318=Vendor ID is 2318: Shining Technology
2319=Vendor ID is 2319: Fujitsu Devices Inc.
2320=Vendor ID is 2320: Alation Systems
2321=Vendor ID is 2321: Philips Speech Processing
2322=Vendor ID is 2322: Voquette
2325=Vendor ID is 2325: GlobespanVirata, Inc.
2327=Vendor ID is 2327: SmartDisk Corporation
2329=Vendor ID is 2329: Tiger Electronics
2334=Vendor ID is 2334: Garmin International
2336=Vendor ID is 2336: Echelon
2337=Vendor ID is 2337: GoHubs
2338=Vendor ID is 2338: Dymo-CoStar
2339=Vendor ID is 2339: IC Media
2340=Vendor ID is 2340: Xerox Corporation
2343=Vendor ID is 2343: Summus
2344=Vendor ID is 2344: Oxford Semiconductor Ltd.
2345=Vendor ID is 2345: American Biometric
2346=Vendor ID is 2346: Toshiba Information & Industrial Sys. And Services
2347=Vendor ID is 2347: Sena Technologies
2352=Vendor ID is 2352: Toshiba Corporation
2353=Vendor ID is 2353: Harmonic Data Systems
2354=Vendor ID is 2354: Crescentec Corporation
2355=Vendor ID is 2355: Quantum
2356=Vendor ID is 2356: Netcom Systems
2361=Vendor ID is 2361: Lumberg, Inc.
2362=Vendor ID is 2362: Pixart Imaging
2363=Vendor ID is 2363: Plextor Corp.
2365=Vendor ID is 2365: InnoSync
2366=Vendor ID is 2366: J.S.T. Mfg. Co., Ltd.
2367=Vendor ID is 2367: Olympia Telecom Vertriebs GmbH
2368=Vendor ID is 2368: Japan Storage Battery
2369=Vendor ID is 2369: Photobit
2370=Vendor ID is 2370: i2Go.com, LLC
2371=Vendor ID is 2371: HCL Technologies India Private
2372=Vendor ID is 2372: KORG
2373=Vendor ID is 2373: Pasco Scientific
2376=Vendor ID is 2376: Kronauer music in digital
2379=Vendor ID is 2379: Linkup Systems
2381=Vendor ID is 2381: Cable Television Laboratories
2385=Vendor ID is 2385: Kingston Technology
2388=Vendor ID is 2388: RPM Systems
2389=Vendor ID is 2389: NVIDIA
2390=Vendor ID is 2390: BSquare
2391=Vendor ID is 2391: Agilent Technologies, Inc.
2392=Vendor ID is 2392: CompuLink Research
2393=Vendor ID is 2393: Cologne Chip AG
2394=Vendor ID is 2394: Portsmith
2395=Vendor ID is 2395: Medialogic Corporation
2396=Vendor ID is 2396: K-Tec Electronics
2397=Vendor ID is 2397: Polycom, Inc.
2407=Vendor ID is 2407: Acer (??)
2408=Vendor ID is 2408: Catalyst Enterprises, Inc.
2417=Vendor ID is 2417: Gretag-Macbeth AG
2419=Vendor ID is 2419: Schlumberger
2420=Vendor ID is 2420: Datagraphix, a business unit of Anacomp
2421=Vendor ID is 2421: OL'E Communications
2422=Vendor ID is 2422: Adirondack Wire & Cable
2423=Vendor ID is 2423: Lightsurf Technologies
2424=Vendor ID is 2424: Beckhoff GmbH
2425=Vendor ID is 2425: Jeilin Technology
2426=Vendor ID is 2426: Minds At Work LLC
2427=Vendor ID is 2427: Knudsen Engineering
2428=Vendor ID is 2428: Marunix Co., Ltd.
2429=Vendor ID is 2429: Rosun Technologies
2431=Vendor ID is 2431: Barun Electronics Co. Ltd.
2433=Vendor ID is 2433: Oak Technology
2436=Vendor ID is 2436: Apricorn
2437=Vendor ID is 2437: cab Produkttechnik
2444=Vendor ID is 2444: Vitana
2445=Vendor ID is 2445: INDesign
2446=Vendor ID is 2446: Integrated Intellectual Property
2447=Vendor ID is 2447: Kenwood TMI
2451=Vendor ID is 2451: Gemstar eBook Group
2454=Vendor ID is 2454: Integrated Telecom Express
2467=Vendor ID is 2467: PairGain Technologies
2468=Vendor ID is 2468: Contech Research, Inc.
2469=Vendor ID is 2469: VCON Telecommunications
2470=Vendor ID is 2470: Poinchips
2471=Vendor ID is 2471: Data Transmission Network
2472=Vendor ID is 2472: Lin Shiung Enterprise Co., Ltd.
2473=Vendor ID is 2473: Smart Card Technologies
2474=Vendor ID is 2474: Intersil
2478=Vendor ID is 2478: Tripp Lite
2482=Vendor ID is 2482: Franklin Electronic Publishers
2483=Vendor ID is 2483: Altius Solutions
2484=Vendor ID is 2484: MDS Telephone Systems
2485=Vendor ID is 2485: Celltrix Technology
2494=Vendor ID is 2494: MySmart.Com
2495=Vendor ID is 2495: Auerswald
2497=Vendor ID is 2497: Arris Interactive LLC
2498=Vendor ID is 2498: NISCA Corporation
2499=Vendor ID is 2499: ACTIVCARD
2500=Vendor ID is 2500: ACTiSYS
2501=Vendor ID is 2501: Memory
2508=Vendor ID is 2508: Workbit Corporation
2509=Vendor ID is 2509: Psion Dacom Home Networks
2510=Vendor ID is 2510: City Electronics
2511=Vendor ID is 2511: Electronics Testing Center, Taiwan
2513=Vendor ID is 2513: NeoMagic Inc.
2514=Vendor ID is 2514: Vreelin Engineering
2515=Vendor ID is 2515: Com One
2521=Vendor ID is 2521: KRF Tech
2522=Vendor ID is 2522: A-FOUR TECH CO., LTD.
2523=Vendor ID is 2523: Measurement Computing
2524=Vendor ID is 2524: Aimex
2525=Vendor ID is 2525: Fellowes Inc.
2527=Vendor ID is 2527: Addonics Technologies
2529=Vendor ID is 2529: Intellon
2533=Vendor ID is 2533: Jo-Dan International, Inc.
2534=Vendor ID is 2534: Silutia
2535=Vendor ID is 2535: Real 3D
2536=Vendor ID is 2536: AKAI  professional M.I. Corp.
2537=Vendor ID is 2537: CHEN-SOURCE INC.
2539=Vendor ID is 2539: IM Networks
2543=Vendor ID is 2543: Xitel
2549=Vendor ID is 2549: AresCom
2550=Vendor ID is 2550: RocketChips
2551=Vendor ID is 2551: Edu-Science (H.K.)
2552=Vendor ID is 2552: SoftConnex Technologies, Inc.
2553=Vendor ID is 2553: Bay Associates
2554=Vendor ID is 2554: Mtek Vision
2555=Vendor ID is 2555: Altera
2559=Vendor ID is 2559: Gain Technology
2560=Vendor ID is 2560: Liquid Audio
2561=Vendor ID is 2561: ViA
2571=Vendor ID is 2571: Cybex Computer Products
2577=Vendor ID is 2577: Xentec
2578=Vendor ID is 2578: Cambridge Silicon Radio Ltd.
2579=Vendor ID is 2579: Telebyte
2580=Vendor ID is 2580: Spacelabs Medical Inc.
2581=Vendor ID is 2581: Scalar
2582=Vendor ID is 2582: Trek Technology (S) Pte Ltd
2583=Vendor ID is 2583: PENTAX Corporation
2584=Vendor ID is 2584: Heidelberger Druckmaschinen AG
2585=Vendor ID is 2585: Hua Geng Technologies
2593=Vendor ID is 2593: Medtronic Physio Control Corp.
2594=Vendor ID is 2594: Century Semiconductor USA
2604=Vendor ID is 2604: AK-Modul-Bus Computer GmbH
2617=Vendor ID is 2617: Gilat Satellite Networks
2618=Vendor ID is 2618: PentaMedia
2620=Vendor ID is 2620: NTT DoCoMo,Inc.
2621=Vendor ID is 2621: Varo Vision
2627=Vendor ID is 2627: Boca Systems
2630=Vendor ID is 2630: Davicom Semiconductor
2631=Vendor ID is 2631: Hirose Electric
2632=Vendor ID is 2632: I/O Interconnect
2635=Vendor ID is 2635: Fujitsu Media Devices
2636=Vendor ID is 2636: COMPUTEX Co., Ltd.
2637=Vendor ID is 2637: Evolution Electronics
2638=Vendor ID is 2638: Steinberg Soft-und Hardware GmbH
2639=Vendor ID is 2639: Litton Systems
2640=Vendor ID is 2640: Mimaki Engineering Co., Ltd.
2641=Vendor ID is 2641: Sony Electronics
2642=Vendor ID is 2642: Jebsee Electronics
2643=Vendor ID is 2643: Portable Peripheral Co., Ltd.
2650=Vendor ID is 2650: Electronics For Imaging
2651=Vendor ID is 2651: EAsics NV
2652=Vendor ID is 2652: Broadcom Corp.
2653=Vendor ID is 2653: Diatrend
2655=Vendor ID is 2655: Zebra
2662=Vendor ID is 2662: ClearCube Technology
2663=Vendor ID is 2663: Medeli Electronics
2664=Vendor ID is 2664: COMAIDE Corporation
2665=Vendor ID is 2665: Chroma ate
2667=Vendor ID is 2667: Green House Co., Ltd.
2668=Vendor ID is 2668: Integrated Circuit Systems
2669=Vendor ID is 2669: UPS Manufacturing
2670=Vendor ID is 2670: Benwin
2671=Vendor ID is 2671: Core Technology
2672=Vendor ID is 2672: International Game Technology
2674=Vendor ID is 2674: Sanwa Denshi
2685=Vendor ID is 2685: NSTL, Inc.
2686=Vendor ID is 2686: Octagon Systems
2688=Vendor ID is 2688: Rexon Technology
2689=Vendor ID is 2689: CHESEN ELECTRONICS CORP.
2690=Vendor ID is 2690: SYSCAN
2691=Vendor ID is 2691: NextComm, Inc.
2692=Vendor ID is 2692: Maui Innovative Peripherals
2693=Vendor ID is 2693: Idexx Labs
2694=Vendor ID is 2694: NITGen
2701=Vendor ID is 2701: Picturetel
2702=Vendor ID is 2702: Japan Aviation Electronics Industry Ltd. (JAE)
2704=Vendor ID is 2704: Candy Technology
2705=Vendor ID is 2705: Globlink Technology Inc.
2706=Vendor ID is 2706: EGO SYStems
2707=Vendor ID is 2707: C Technologies AB (publ)
2708=Vendor ID is 2708: Intersense
2723=Vendor ID is 2723: Lava Computer
2724=Vendor ID is 2724: Develco Elektronik
2725=Vendor ID is 2725: First International Digital
2726=Vendor ID is 2726: Perception Digital
2727=Vendor ID is 2727: Wincor Nixdorf GmbH &Co KG
2728=Vendor ID is 2728: TriGem Computer, Inc.
2729=Vendor ID is 2729: Baromtec
2730=Vendor ID is 2730: Japan CBM
2731=Vendor ID is 2731: Vision Shape Europe SA
2732=Vendor ID is 2732: iCompression
2733=Vendor ID is 2733: Rohde & Schwarz GmbH & Co. KG
2734=Vendor ID is 2734: NEC infrontia
2735=Vendor ID is 2735: Digitalway
2736=Vendor ID is 2736: Arrow Strong Electronics
2746=Vendor ID is 2746: Ellisys
2750=Vendor ID is 2750: Stereo-Link
2755=Vendor ID is 2755: SANYO Semiconductor Company Micro
2756=Vendor ID is 2756: LECO CORPORATION
2757=Vendor ID is 2757: I & C
2758=Vendor ID is 2758: Singing Electrons
2759=Vendor ID is 2759: Panwest
2760=Vendor ID is 2760: Vimicro Corporation
2761=Vendor ID is 2761: Micro Solutions, Inc.
2764=Vendor ID is 2764: Koga Electronics
2765=Vendor ID is 2765: ID Tech
2767=Vendor ID is 2767: Intoto
2768=Vendor ID is 2768: Intellix
2769=Vendor ID is 2769: Remotec Technology
2770=Vendor ID is 2770: Service & Quality Technology
2787=Vendor ID is 2787: Allion Computer
2788=Vendor ID is 2788: Taito Corporation
2791=Vendor ID is 2791: Neodym Systems
2792=Vendor ID is 2792: System Support
2793=Vendor ID is 2793: North Shore Circuit Design L.L.P.
2794=Vendor ID is 2794: SciEssence, LLC
2795=Vendor ID is 2795: TTP Communications
2796=Vendor ID is 2796: Neodio Technologies Corporation
2806=Vendor ID is 2806: Silver I
2807=Vendor ID is 2807: B2C2
2809=Vendor ID is 2809: Hama
2812=Vendor ID is 2812: Zaptronix
2813=Vendor ID is 2813: Tateno Dennou, Inc.
2814=Vendor ID is 2814: Cummins Engine Company
2815=Vendor ID is 2815: Jump Zone Network Products
2816=Vendor ID is 2816: INGENICO
2821=Vendor ID is 2821: ASUSTek Computer
2828=Vendor ID is 2828: Todos Data System AB
2830=Vendor ID is 2830: GN Netcom
2831=Vendor ID is 2831: AVID Technology
2832=Vendor ID is 2832: Pcally
2833=Vendor ID is 2833: I Tech Solutions
2846=Vendor ID is 2846: Electronic Warfare Assoc., Inc. (EWA)
2847=Vendor ID is 2847: Insyde Software
2848=Vendor ID is 2848: TransDimension Inc.
2849=Vendor ID is 2849: Yokogawa Electric Corporation
2850=Vendor ID is 2850: Japan System Development
2851=Vendor ID is 2851: Pan-Asia Electronics Co., Ltd.
2852=Vendor ID is 2852: Link Evolution
2855=Vendor ID is 2855: Ritek Corporation
2856=Vendor ID is 2856: Kenwood
2860=Vendor ID is 2860: Village Center
2864=Vendor ID is 2864: PNY Technologies
2867=Vendor ID is 2867: Contour Design
2871=Vendor ID is 2871: Hitachi ULSI Systems Co., Ltd.
2873=Vendor ID is 2873: Omnidirectional Control Technology
2874=Vendor ID is 2874: IPaxess
2875=Vendor ID is 2875: Tekram Technology
2876=Vendor ID is 2876: Olivetti Tecnost
2878=Vendor ID is 2878: Kikusui Electronics
2881=Vendor ID is 2881: Hal
2887=Vendor ID is 2887: Sportbug.com
2888=Vendor ID is 2888: TechnoTrend AG
2889=Vendor ID is 2889: ASCII
2891=Vendor ID is 2891: Pine
2894=Vendor ID is 2894: Musical Electronics Ltd.
2896=Vendor ID is 2896: Dumpries
2898=Vendor ID is 2898: Colorado MicroDisplay
2900=Vendor ID is 2900: Sinbon Electronics Co., Ltd.
2902=Vendor ID is 2902: TYI Systems
2903=Vendor ID is 2903: Beijing HanwangTechnology
2905=Vendor ID is 2905: Lake Communications
2906=Vendor ID is 2906: Corel
2911=Vendor ID is 2911: Green Electronics
2912=Vendor ID is 2912: Nsine
2913=Vendor ID is 2913: NEC Viewtechnology, Ltd.
2914=Vendor ID is 2914: Orange Micro, Inc.
2915=Vendor ID is 2915: ADLink Technology
2916=Vendor ID is 2916: Wonderful Wire Cable
2917=Vendor ID is 2917: Expert Magnetics
2921=Vendor ID is 2921: CacheVision
2922=Vendor ID is 2922: Maxim Integrated Products
2927=Vendor ID is 2927: Nagano Japan Radio Co., Ltd
2928=Vendor ID is 2928: PortalPlayer, Inc
2929=Vendor ID is 2929: SHIN-EI Sangyo
2930=Vendor ID is 2930: Embedded Wireless Technology
2931=Vendor ID is 2931: Computone
2933=Vendor ID is 2933: Roland DG Corporation
2937=Vendor ID is 2937: Sunrise Telecom
2938=Vendor ID is 2938: Zeevo
2939=Vendor ID is 2939: Taiko Denki
2940=Vendor ID is 2940: ITRAN Communications
2941=Vendor ID is 2941: Astrodesign
2948=Vendor ID is 2948: Rextron Technology
2949=Vendor ID is 2949: Elkat Electronics (M) SDN. BHD.
2950=Vendor ID is 2950: eXputer
2951=Vendor ID is 2951: Plus-One I & T
2952=Vendor ID is 2952: Sigma Koki
2953=Vendor ID is 2953: Advanced Digital Broadcast
2965=Vendor ID is 2965: ASIX Electronics Corp.
2966=Vendor ID is 2966: SEWON TELECOM
2967=Vendor ID is 2967: O2 Micro
2968=Vendor ID is 2968: Playmates Toys
2969=Vendor ID is 2969: Audio International
2973=Vendor ID is 2973: Softprotec
2975=Vendor ID is 2975: Chippo Technologies
2991=Vendor ID is 2991: U.S. Robotics
2992=Vendor ID is 2992: Concord Camera Corp.
2993=Vendor ID is 2993: Infinilink
2994=Vendor ID is 2994: Ambit Microsystems Corporation
2995=Vendor ID is 2995: Ofuji Technology
2996=Vendor ID is 2996: High Tech Computer, Corp. (HTC)
2997=Vendor ID is 2997: Murata Manufacturing Co., Ltd.
2998=Vendor ID is 2998: Network Alchemy
2999=Vendor ID is 2999: Joytech Computer
3000=Vendor ID is 3000: Renesas Technology Sales Co., Ltd.
3001=Vendor ID is 3001: Eiger M&C
3002=Vendor ID is 3002: ZAccess Systems
3003=Vendor ID is 3003: General Meters
3004=Vendor ID is 3004: Assistive Technology
3005=Vendor ID is 3005: System Connection
3008=Vendor ID is 3008: Knilink Technology
3009=Vendor ID is 3009: Fuw Yng Electronics
3010=Vendor ID is 3010: Seagate RSS LLC
3011=Vendor ID is 3011: IPWireless, Inc.
3012=Vendor ID is 3012: Microcube
3013=Vendor ID is 3013: JCN
3014=Vendor ID is 3014: ExWAY
3015=Vendor ID is 3015: X10 Wireless Technology, Inc.
3016=Vendor ID is 3016: Telmax Communications
3017=Vendor ID is 3017: ECI Telecom
3018=Vendor ID is 3018: Startek Engineering
3019=Vendor ID is 3019: Perfect Technic Enterprise
3034=Vendor ID is 3034: Realtek Semiconductor Corp.
3035=Vendor ID is 3035: Ericsson Mobile Platforms
3036=Vendor ID is 3036: Y Media
3037=Vendor ID is 3037: Orange PCS
3042=Vendor ID is 3042: Kanda Tsushin Kogyo Co., LTD
3043=Vendor ID is 3043: TOYO
3044=Vendor ID is 3044: Elka International Ltd.
3045=Vendor ID is 3045: DOME imaging systems
3046=Vendor ID is 3046: Dong Guan Humen Wonderful Wire Cable Factory
3054=Vendor ID is 3054: LTK Industries Ltd.
3055=Vendor ID is 3055: Way2Call Communications
3056=Vendor ID is 3056: Pace Micro
3057=Vendor ID is 3057: Intracom S.A.
3058=Vendor ID is 3058: Konexx
3062=Vendor ID is 3062: Addonics Technologies, Inc.
3063=Vendor ID is 3063: Sunny Giken
3064=Vendor ID is 3064: Fujitsu Siemens Computers
3076=Vendor ID is 3076: MOTO Development Group
3077=Vendor ID is 3077: Appian Graphics
3078=Vendor ID is 3078: Hasbro Games
3079=Vendor ID is 3079: Infinite Data Storage
3080=Vendor ID is 3080: Agate
3081=Vendor ID is 3081: Comjet Information System
3082=Vendor ID is 3082: Highpoint Technologies
3083=Vendor ID is 3083: Dura Micro, Inc.
3090=Vendor ID is 3090: Zeroplus
3093=Vendor ID is 3093: Iris Graphics
3094=Vendor ID is 3094: Gyration
3095=Vendor ID is 3095: Cyberboard
3096=Vendor ID is 3096: SynerTek Korea
3097=Vendor ID is 3097: cyberPIXIE
3098=Vendor ID is 3098: Silicon Motion
3099=Vendor ID is 3099: MIPS Technologies
3100=Vendor ID is 3100: Hang Zhou Silan
3106=Vendor ID is 3106: Tally
3107=Vendor ID is 3107: Lernout + Hauspie
3108=Vendor ID is 3108: Taiyo Yuden
3109=Vendor ID is 3109: Sampo
3125=Vendor ID is 3125: Eagletron
3126=Vendor ID is 3126: E Ink
3127=Vendor ID is 3127: e.Digital
3128=Vendor ID is 3128: Der An Electric Wire & Cable
3129=Vendor ID is 3129: IFR
3130=Vendor ID is 3130: Furui Precise Component (Kunshan)
3131=Vendor ID is 3131: Komatsu
3132=Vendor ID is 3132: Radius Co., Ltd.
3133=Vendor ID is 3133: Innocom
3134=Vendor ID is 3134: Nextcell
3140=Vendor ID is 3140: Motorola iDEN
3141=Vendor ID is 3141: Sonix Technology Co., Ltd.
3142=Vendor ID is 3142: WaveRider
3154=Vendor ID is 3154: Sealevel Systems
3155=Vendor ID is 3155: ViewPLUS
3156=Vendor ID is 3156: GLORY LTD.
3157=Vendor ID is 3157: Spectrum Digital Inc.
3158=Vendor ID is 3158: Billion Bright Limited
3159=Vendor ID is 3159: Imaginative Design Operation Co. Ltd.
3160=Vendor ID is 3160: Vidar Systems
3161=Vendor ID is 3161: Dong Guan Shinko Wire Co., Ltd.
3162=Vendor ID is 3162: TRS International
3166=Vendor ID is 3166: Xytronix Research & Design
3170=Vendor ID is 3170: Chant Sincere Co., Ltd
3171=Vendor ID is 3171: Toko, Inc.
3172=Vendor ID is 3172: Signality System Engineering Co., Ltd.
3173=Vendor ID is 3173: Eminence Enterprise Co., Ltd.
3174=Vendor ID is 3174: Rexon Electronics
3175=Vendor ID is 3175: Concept Telecom
3184=Vendor ID is 3184: MCT Elektronikladen
3190=Vendor ID is 3190: JMTek, LLC.
3191=Vendor ID is 3191: Sipix Group
3192=Vendor ID is 3192: Detto
3193=Vendor ID is 3193: NuConnex Technologies Pte.
3194=Vendor ID is 3194: Wing-Span Enterprise Co., Ltd.
3206=Vendor ID is 3206: NDA Technologies
3208=Vendor ID is 3208: Kyocera Wireless Corp.
3209=Vendor ID is 3209: Honda Tsushin Kogyo Co., Ltd
3210=Vendor ID is 3210: Pathway Connectivity
3211=Vendor ID is 3211: Wavefly
3212=Vendor ID is 3212: Coactive Networks
3213=Vendor ID is 3213: Tempo
3214=Vendor ID is 3214: Cesscom Co., Ltd.
3215=Vendor ID is 3215: Applied Microsystems
3225=Vendor ID is 3225: Innochips Co., Ltd.
3226=Vendor ID is 3226: Hanwool Robotics Corp.
3227=Vendor ID is 3227: Jobin Yvon
3234=Vendor ID is 3234: Zyfer
3235=Vendor ID is 3235: Sega
3236=Vendor ID is 3236: ST&T Instrument
3237=Vendor ID is 3237: BAE Systems Canada
3238=Vendor ID is 3238: Castles Technology
3239=Vendor ID is 3239: Information Systems Laboratories
3245=Vendor ID is 3245: Motorola CGISS
3246=Vendor ID is 3246: Ascom Business Systems
3247=Vendor ID is 3247: Buslink
3248=Vendor ID is 3248: Flying Pig Systems
3249=Vendor ID is 3249: Innovonics
3254=Vendor ID is 3254: Celestix Networks, Pte.
3255=Vendor ID is 3255: Singatron Enterprise
3256=Vendor ID is 3256: Opticis
3258=Vendor ID is 3258: Trust Electronic (Shanghai)
3259=Vendor ID is 3259: Shanghai Darong Electronics Co., Ltd.
3260=Vendor ID is 3260: Palmax Technology
3261=Vendor ID is 3261: Pentel
3262=Vendor ID is 3262: Keryx Technologies
3263=Vendor ID is 3263: Union Genius Computer Co., Ltd
3264=Vendor ID is 3264: Kuon Yi Industrial Corp.
3265=Vendor ID is 3265: Given Imaging
3266=Vendor ID is 3266: Timex
3267=Vendor ID is 3267: Rimage
3268=Vendor ID is 3268: emsys GmbH
3269=Vendor ID is 3269: Sendo
3270=Vendor ID is 3270: Intermagic
3271=Vendor ID is 3271: Kontron Medical AG
3272=Vendor ID is 3272: Technotools
3273=Vendor ID is 3273: BroadMAX Technologies
3274=Vendor ID is 3274: AMPHENOL
3275=Vendor ID is 3275: SKNet
3276=Vendor ID is 3276: DOMEX TECHNOLOGY CORPORATION
3277=Vendor ID is 3277: TerraTec Electronic GmbH
3282=Vendor ID is 3282: C-Map
3284=Vendor ID is 3284: Bang Olufsen
3287=Vendor ID is 3287: NewChip S.r.l.
3288=Vendor ID is 3288: JS Digitech
3289=Vendor ID is 3289: Hitachi Shin Din Cable Limited
3294=Vendor ID is 3294: Z-Com
3313=Vendor ID is 3313: e-Conn Electronic
3314=Vendor ID is 3314: ENE Technology Inc.
3315=Vendor ID is 3315: Atheros Communications
3316=Vendor ID is 3316: Fomtex
3317=Vendor ID is 3317: Cellink
3318=Vendor ID is 3318: Compucable Corporation
3319=Vendor ID is 3319: ishoni Networks
3320=Vendor ID is 3320: Clarisys
3321=Vendor ID is 3321: Central System Research Co., Ltd.
3322=Vendor ID is 3322: Inviso
3324=Vendor ID is 3324: Minolta-QMS, Inc.
3334=Vendor ID is 3334: telos EDV Systementwicklung GmbH
3339=Vendor ID is 3339: Contemporary Controls
3340=Vendor ID is 3340: Astron Electronics Co., Ltd.
3341=Vendor ID is 3341: MKNet
3342=Vendor ID is 3342: Hybrid Networks
3343=Vendor ID is 3343: Feng Shin Cable Co. Ltd.
3344=Vendor ID is 3344: Elastic Networks
3345=Vendor ID is 3345: Maspro Denkoh
3346=Vendor ID is 3346: Hansol Electronics
3347=Vendor ID is 3347: BMF CORPORATION
3348=Vendor ID is 3348: Array Comm
3349=Vendor ID is 3349: OnStream b.v.
3350=Vendor ID is 3350: Hi-Touch Imaging Technologies Co., Ltd.
3351=Vendor ID is 3351: NALTEC, Inc.
3352=Vendor ID is 3352: coaXmedia
3353=Vendor ID is 3353: Hank Connection Industrial Co., Ltd.
3378=Vendor ID is 3378: Leo Hui Electric Wire & Cable
3379=Vendor ID is 3379: AirSpeak
3380=Vendor ID is 3380: Rearden Steel Technologies
3381=Vendor ID is 3381: Dah Kun Co., Ltd.
3388=Vendor ID is 3388: SRI CABLE TECHNOLOGY LTD.
3389=Vendor ID is 3389: TANGTOP TECHNOLOGY CO., LTD.
3390=Vendor ID is 3390: Fitcom
3391=Vendor ID is 3391: MTS Systems
3392=Vendor ID is 3392: Ascor
3393=Vendor ID is 3393: Ta Yun Terminals Industrial Co., Ltd.
3394=Vendor ID is 3394: FULL DER CO., LTD.
3401=Vendor ID is 3401: Maxtor
3402=Vendor ID is 3402: NF Corporation
3403=Vendor ID is 3403: Grape Systems Inc.
3404=Vendor ID is 3404: Tedas AG
3405=Vendor ID is 3405: Coherent Inc.
3406=Vendor ID is 3406: Agere Systems Netherland BV
3407=Vendor ID is 3407: EADS Airbus France
3408=Vendor ID is 3408: Cleware GmbH
3409=Vendor ID is 3409: Volex (Asia) Pte Ltd
3411=Vendor ID is 3411: HMI
3412=Vendor ID is 3412: Holon
3413=Vendor ID is 3413: ASKA Technologies Inc.
3414=Vendor ID is 3414: AVLAB Technology, Inc.
3415=Vendor ID is 3415: Solomon Microtech
3420=Vendor ID is 3420: Belkin
3422=Vendor ID is 3422: Myacom
3423=Vendor ID is 3423: CSI
3424=Vendor ID is 3424: IVL Technologies
3425=Vendor ID is 3425: MEILU ELECTRONICS (SHENZHEN) CO., LTD.
3426=Vendor ID is 3426: Darfon Electronics Corp.
3427=Vendor ID is 3427: Fritz Gegauf AG
3428=Vendor ID is 3428: DXG Technology
3429=Vendor ID is 3429: KMJP
3430=Vendor ID is 3430: TMT
3431=Vendor ID is 3431: Advanet
3432=Vendor ID is 3432: Super Link Electronics
3433=Vendor ID is 3433: NSI
3434=Vendor ID is 3434: Megapower International Corp.
3435=Vendor ID is 3435: And-Or Logic
3440=Vendor ID is 3440: Try Computer Co. LTD
3441=Vendor ID is 3441: Hirakawa Hewtech
3442=Vendor ID is 3442: Winmate Communication
3443=Vendor ID is 3443: Hit's Communications
3446=Vendor ID is 3446: MFP Korea
3447=Vendor ID is 3447: Power Sentry/Newpoint
3448=Vendor ID is 3448: Japan Distributor
3450=Vendor ID is 3450: MARX Software Security GmbH
3451=Vendor ID is 3451: Wellco Technology
3452=Vendor ID is 3452: Taiwan Line Tek Electronic Co., Ltd.
3453=Vendor ID is 3453: Apacer®
3454=Vendor ID is 3454: American Computer & Digital Components
3455=Vendor ID is 3455: Essential Reality LLC
3456=Vendor ID is 3456: H.R. Silvine Electronics
3457=Vendor ID is 3457: TechnoVision
3459=Vendor ID is 3459: Think Outside
3465=Vendor ID is 3465: Oz Software
3466=Vendor ID is 3466: KING JIM CO., LTD.
3467=Vendor ID is 3467: Ascom Telecommunications
3468=Vendor ID is 3468: C-MEDIA ELECTRONICS INC.
3469=Vendor ID is 3469: Promotion & Display Technology Ltd.
3470=Vendor ID is 3470: Global Sun Technology
3471=Vendor ID is 3471: Pitney Bowes
3472=Vendor ID is 3472: Sure-Fire Electrical Corporation
3478=Vendor ID is 3478: Traveler
3480=Vendor ID is 3480: Mars Semiconductor
3481=Vendor ID is 3481: Trazer Technologies
3482=Vendor ID is 3482: RTX Telecom AS
3483=Vendor ID is 3483: Tat Shing Electrical
3484=Vendor ID is 3484: Chee Chen Hi-Technology Co., Ltd.
3485=Vendor ID is 3485: Sanwa Supply
3486=Vendor ID is 3486: Avaya
3487=Vendor ID is 3487: Powercom
3488=Vendor ID is 3488: Danger Research
3489=Vendor ID is 3489: Suzhou Peter's Precise Industrial Co., Ltd.
3490=Vendor ID is 3490: Land Instruments International
3491=Vendor ID is 3491: Nippon Electro-Sensory Devices
3492=Vendor ID is 3492: Polar Electro OY
3495=Vendor ID is 3495: IOGEAR
3501=Vendor ID is 3501: Westover Scientific
3504=Vendor ID is 3504: Micro Star International
3505=Vendor ID is 3505: Wen Te Electronics
3506=Vendor ID is 3506: Shian Hwi Plug Parts, Plastic Factory
3507=Vendor ID is 3507: Tekram Technology
3508=Vendor ID is 3508: Chung Fu Chen Yeh Enterprise
3518=Vendor ID is 3518: Jiuh Shiuh Precision Industry
3519=Vendor ID is 3519: Quik Tech Solutions
3520=Vendor ID is 3520: Great Notions
3521=Vendor ID is 3521: Tamagawa Seiki
3523=Vendor ID is 3523: Athena Smartcard Solutions Inc.
3524=Vendor ID is 3524: Macpower Peripherals Ltd.
3525=Vendor ID is 3525: SDK Co, Ltd.
3526=Vendor ID is 3526: Precision Squared Technology
3527=Vendor ID is 3527: First Cable Line
3533=Vendor ID is 3533: NetworkFab
3537=Vendor ID is 3537: Contek Electronics Co., Ltd.
3538=Vendor ID is 3538: Power Quotient International Co., Ltd.
3539=Vendor ID is 3539: MediaQ
3540=Vendor ID is 3540: Custom Engineering SPA
3541=Vendor ID is 3541: California Micro Devices
3543=Vendor ID is 3543: KOCOM CO., LTD
3545=Vendor ID is 3545: HighSpeed Surfing
3546=Vendor ID is 3546: Integrated Circuit Solution Inc.
3547=Vendor ID is 3547: Tamarack
3549=Vendor ID is 3549: Datelink Technology Co., Ltd.
3550=Vendor ID is 3550: UBICOM
3552=Vendor ID is 3552: BD Consumer Healthcare
3562=Vendor ID is 3562: UTECH Electronic (D.G.)
3565=Vendor ID is 3565: Novasonics
3566=Vendor ID is 3566: Lifetime Memory Products
3567=Vendor ID is 3567: Full Rise Electronic Co., Ltd.
3574=Vendor ID is 3574: Sitecom Europe B.V.
3575=Vendor ID is 3575: Mobile Action Technology Inc.
3576=Vendor ID is 3576: Hoya Computer Co., Ltd.
3578=Vendor ID is 3578: Toyo Communication Equipment Co., Ltd.
3580=Vendor ID is 3580: GeneralTouch Technology
3586=Vendor ID is 3586: Doowon Co., LTD
3587=Vendor ID is 3587: Nippon Systemware
3592=Vendor ID is 3592: Winbest Technology
3596=Vendor ID is 3596: Gesytec
3604=Vendor ID is 3604: Hunter Engineering Co.
3606=Vendor ID is 3606: JMTEK, LLC
3607=Vendor ID is 3607: Walex Electronic
3611=Vendor ID is 3611: Crewave
3617=Vendor ID is 3617: Cowon Systems
3618=Vendor ID is 3618: Symbian Ltd.
3619=Vendor ID is 3619: Liou Yuane Enterprise Co., Ltd.
3621=Vendor ID is 3621: VinChip Systems Inc.
3622=Vendor ID is 3622: J-Phone East Co., Ltd.
3632=Vendor ID is 3632: HeartMath LLC
3636=Vendor ID is 3636: Micro Computer Control Corp.
3637=Vendor ID is 3637: 3Pea Technologies, Inc.
3638=Vendor ID is 3638: TiePie engineering
3640=Vendor ID is 3640: Stratitec, Inc.
3641=Vendor ID is 3641: Smart Modular Technologies, Inc.
3642=Vendor ID is 3642: Neostar Technology Co., Ltd.
3643=Vendor ID is 3643: Mansella Ltd.
3650=Vendor ID is 3650: Puretek Industrial
3652=Vendor ID is 3652: Sun-Riseful Technology Co., Ltd.
3654=Vendor ID is 3654: Delphi Corporation
3656=Vendor ID is 3656: Julia
3658=Vendor ID is 3658: Shenzhen Bao Hing Electric Wire & Cable Mfr. Co.
3660=Vendor ID is 3660: Radica Games Ltd.
3669=Vendor ID is 3669: Speed Dragon Multimedia Ltd.
3674=Vendor ID is 3674: ACTIVE CO., LTD.
3675=Vendor ID is 3675: Union Power Information Industrial Co., Ltd.
3676=Vendor ID is 3676: Bitland Information Technology Co., Ltd.
3677=Vendor ID is 3677: Neltron Industrial Co., Ltd.
3686=Vendor ID is 3686: Hawking
3687=Vendor ID is 3687: Fossil
3690=Vendor ID is 3690: Megawin Technology Co., Ltd.
3696=Vendor ID is 3696: Tokyo Electronic Industry Co, LTD.
3698=Vendor ID is 3698: Hsi-Chin Electronics Co., Ltd.
3701=Vendor ID is 3701: TVS Electronics
3707=Vendor ID is 3707: On-Tech Industry Co., Ltd.
3710=Vendor ID is 3710: Gmate
3714=Vendor ID is 3714: Ching Tai Electric Wire & Cable Co., Ltd.
3715=Vendor ID is 3715: Shin An Wire & Cable Co.
3723=Vendor ID is 3723: KAO SHIN PRECISION INDUSTRY
3724=Vendor ID is 3724: Well Force Electronic Co., Ltd
3725=Vendor ID is 3725: MediaTek Inc.
3728=Vendor ID is 3728: WiebeTech, LLC
3729=Vendor ID is 3729: VTech Engineering Canada Ltd.
3730=Vendor ID is 3730: C'S GLORY ENTERPRISE CO., LTD.
3731=Vendor ID is 3731: eM Technics
3733=Vendor ID is 3733: Future Technology
3734=Vendor ID is 3734: APLUX  Communications Ltd.
3735=Vendor ID is 3735: Fingerworks
3736=Vendor ID is 3736: Advanced Analogic Technologies
3737=Vendor ID is 3737: Parallel Dice
3738=Vendor ID is 3738: TA HSING Industries
3739=Vendor ID is 3739: ADTEC CORPORATION
3743=Vendor ID is 3743: Tamura
3744=Vendor ID is 3744: Ours Technology Inc.
3750=Vendor ID is 3750: Nihon Computer Co., Ltd.
3751=Vendor ID is 3751: MSL Enterprises Corp.
3752=Vendor ID is 3752: CenDyne, Inc.
3757=Vendor ID is 3757: HUMAX Co., Ltd.
3761=Vendor ID is 3761: WIS Technologies, Inc.
3762=Vendor ID is 3762: Y-S Electronic
3763=Vendor ID is 3763: Saint Technology Corp.
3767=Vendor ID is 3767: Endor AG
3774=Vendor ID is 3774: VWeb
3775=Vendor ID is 3775: Omega Technology of Taiwan Inc.
3776=Vendor ID is 3776: LHI Technology (China)
3777=Vendor ID is 3777: Abit Computer
3778=Vendor ID is 3778: Sweetray Industrial Ltd.
3779=Vendor ID is 3779: AXELL CO., LTD.
3780=Vendor ID is 3780: Ballracing Developments
3781=Vendor ID is 3781: GT Information System
3782=Vendor ID is 3782: InnoVISION Multimedia Limited
3783=Vendor ID is 3783: Theta Link
3789=Vendor ID is 3789: Lite-On IT Corp.
3790=Vendor ID is 3790: TaiSol Electronics Co., Ltd.
3791=Vendor ID is 3791: Phogenix Imaging, LLC
3793=Vendor ID is 3793: WinMaxGroup
3794=Vendor ID is 3794: Kyoto Micro Computer Co., LTD.
3795=Vendor ID is 3795: Wing-Tech Enterprise
3802=Vendor ID is 3802: NORITAKE ITRON CORPORATION
3807=Vendor ID is 3807: e-MDT
3808=Vendor ID is 3808: SHIMA SEIKI MFG., LTD.
3809=Vendor ID is 3809: Sarotech
3810=Vendor ID is 3810: AMI Semiconductor
3811=Vendor ID is 3811: ComTrue Technology
3812=Vendor ID is 3812: Sunrich Technology Ltd.
3822=Vendor ID is 3822: Digital Stream Technology
3823=Vendor ID is 3823: D-WAV Scientific
3824=Vendor ID is 3824: Hitachi Cable
3825=Vendor ID is 3825: Aichi Micro Intelligent
3826=Vendor ID is 3826: I/OMAGIC CORPORATION
3827=Vendor ID is 3827: Lynn Products
3828=Vendor ID is 3828: DSI Datotech
3829=Vendor ID is 3829: PointChips
3830=Vendor ID is 3830: Yield Microelectronics
3831=Vendor ID is 3831: SM Tech Co., Ltd./Tulip Computers International
3837=Vendor ID is 3837: Oasis Semiconductor
3838=Vendor ID is 3838: WEM TECHNOLOGY INC.
3846=Vendor ID is 3846: Visual Frontier Precision Corp.
3848=Vendor ID is 3848: CSL Wire & Plug (Shen Zhen) Company
3852=Vendor ID is 3852: CAS
3853=Vendor ID is 3853: Hori
3854=Vendor ID is 3854: Energy Full Corp.
3858=Vendor ID is 3858: Mars Engineering
3859=Vendor ID is 3859: Acetek Technology
3865=Vendor ID is 3865: Oracom
3867=Vendor ID is 3867: Onset Computer Corporation
3868=Vendor ID is 3868: Funai Electric Co., Ltd.
3869=Vendor ID is 3869: Iwill
3873=Vendor ID is 3873: IOI Technology Corporation
3874=Vendor ID is 3874: SENIOR INDUSTRIES, INC.
3875=Vendor ID is 3875: Leader Tech Manufacturer
3876=Vendor ID is 3876: FLEX-P INDUSTRIES SDN.BHD.
3885=Vendor ID is 3885: ViPower
3886=Vendor ID is 3886: Geniality Maple Technology Co., Ltd.
3887=Vendor ID is 3887: Priva Design Services
3888=Vendor ID is 3888: Jess Technology Co., Ltd.
3889=Vendor ID is 3889: Chrysalis Development
3890=Vendor ID is 3890: YFC-BonEagle Electric Co., Ltd.
3895=Vendor ID is 3895: Kokuyo
3896=Vendor ID is 3896: Nien-Yi Industrial Corp.
3905=Vendor ID is 3905: RDC Semiconductor
3906=Vendor ID is 3906: Nital Consulting Services, Inc.
3915=Vendor ID is 3915: St. John Technology Co., Ltd.
3916=Vendor ID is 3916: WORLDWIDE CABLE OPTO
3917=Vendor ID is 3917: Microtune
3918=Vendor ID is 3918: Freedom Scientific
3922=Vendor ID is 3922: WING KEI ELECTRICAL CO., LTD.
3923=Vendor ID is 3923: Taiyo Cable (Dongguan) Co. Ltd.
3924=Vendor ID is 3924: Kawai Musical Instruments Mfg. Co., Ltd.
3925=Vendor ID is 3925: AmbiCom
3932=Vendor ID is 3932: Prairiecomm
3933=Vendor ID is 3933: NewAge International, LLC
3935=Vendor ID is 3935: Key Technology Corporation
3936=Vendor ID is 3936: NTK (HK) LTD.
3937=Vendor ID is 3937: Varian
3938=Vendor ID is 3938: Acrox Technologies Co., Ltd.
3944=Vendor ID is 3944: Kobe Steel, Ltd.
3945=Vendor ID is 3945: DIONEX CORPORATION
3946=Vendor ID is 3946: Vibren Technologies
3955=Vendor ID is 3955: DFI
3964=Vendor ID is 3964: DQ Technology
3965=Vendor ID is 3965: NetBotz
3966=Vendor ID is 3966: Fluke
3976=Vendor ID is 3976: VTech Holdings Ltd.
3979=Vendor ID is 3979: Yazaki Corporation
3980=Vendor ID is 3980: Young Generation International Corp.
3981=Vendor ID is 3981: Uniwill Computer Corp.
3982=Vendor ID is 3982: Kingnet Technology
3983=Vendor ID is 3983: SOMA NETWORKS
3991=Vendor ID is 3991: CviLux Corporation
3992=Vendor ID is 3992: CYBERBANK CORP.
3998=Vendor ID is 3998: Lucent Technologies
4003=Vendor ID is 4003: Starconn Electronic
4004=Vendor ID is 4004: ATL Technology
4005=Vendor ID is 4005: SOTEC CO., LTD.
4007=Vendor ID is 4007: Epox Computer
4008=Vendor ID is 4008: Logic Controls
4015=Vendor ID is 4015: Winpoint Electronic Corp.
4016=Vendor ID is 4016: Haurtian Wire & Cable Co., Ltd.
4017=Vendor ID is 4017: Inclose Design
4018=Vendor ID is 4018: Juan-Chern Industrial
4024=Vendor ID is 4024: Wistron Corporation
4025=Vendor ID is 4025: AACom
4026=Vendor ID is 4026: SAN SHING ELECTRONICS CO., LTD..
4027=Vendor ID is 4027: Bitwise Systems
4033=Vendor ID is 4033: Mitac Internatinal
4034=Vendor ID is 4034: Plug and Jack Industrial
4037=Vendor ID is 4037: Delcom Engineering
4038=Vendor ID is 4038: Dataplus Supplies, Inc.
4046=Vendor ID is 4046: Sony Ericsson Mobile Communications AB
4047=Vendor ID is 4047: Dynastream Innovations
4048=Vendor ID is 4048: Tulip Computers B.V.
4052=Vendor ID is 4052: Tenovis
4053=Vendor ID is 4053: Direct Access Technology, Inc.
4060=Vendor ID is 4060: Micro Plus
4068=Vendor ID is 4068: IN-Tech Electronics
4069=Vendor ID is 4069: GREENCONN (U.S.A.) INC.
4074=Vendor ID is 4074: United Computer Accessories
4075=Vendor ID is 4075: CRS Electronic
4076=Vendor ID is 4076: UMC Electronics
4077=Vendor ID is 4077: ACCESS CO., LTD.
4078=Vendor ID is 4078: Xsido
4079=Vendor ID is 4079: MJ Research
4086=Vendor ID is 4086: Core Valley
4087=Vendor ID is 4087: CHI SHING COMPUTER ACCESSORIES CO., LTD.
4095=Vendor ID is 4095: Aopen
4096=Vendor ID is 4096: Speed Tech Corp.
4097=Vendor ID is 4097: Ritronics
4099=Vendor ID is 4099: Sigma
4100=Vendor ID is 4100: LG Electronics Inc.
4101=Vendor ID is 4101: Apacer Technology Inc.
4105=Vendor ID is 4105: Emuzed
4106=Vendor ID is 4106: AV Chaseway
4107=Vendor ID is 4107: Chou Chin Industrial
4109=Vendor ID is 4109: NETOPIA, INC.
4112=Vendor ID is 4112: FUKUDA DENSHI CO., LTD.
4113=Vendor ID is 4113: Mobile Media Tech.
4114=Vendor ID is 4114: SDKM Fibres, Wires & Cables Berhad
4115=Vendor ID is 4115: TST-Touchless Sensor Technology AG
4116=Vendor ID is 4116: Densitron Technologies PLC
4117=Vendor ID is 4117: Softronics Pty. Ltd.
4118=Vendor ID is 4118: Xiamen Hung's Enterprise
4119=Vendor ID is 4119: SPEEDY INDUSTRIAL SUPPLIES PTE. LTD.
4121=Vendor ID is 4121: I-Buddie
4130=Vendor ID is 4130: Shinko Shoji Co., Ltd.
4133=Vendor ID is 4133: Hyper-Paltek
4134=Vendor ID is 4134: Newly Corporation
4135=Vendor ID is 4135: Time Domain
4136=Vendor ID is 4136: Inovys
4137=Vendor ID is 4137: Atlantic Coast Telesys
4138=Vendor ID is 4138: RAMOS Technology Co., Ltd.
4139=Vendor ID is 4139: Infotronic America, Inc.
4140=Vendor ID is 4140: Etoms Electronics Corp.
4141=Vendor ID is 4141: Winic Corporation
4145=Vendor ID is 4145: Comax Technology Inc.
4146=Vendor ID is 4146: C-One Technology Corp.
4147=Vendor ID is 4147: Nucam Corporation
4158=Vendor ID is 4158: TTi
4163=Vendor ID is 4163: iCreate Technologies
4164=Vendor ID is 4164: Chu Yuen Enterprise
4166=Vendor ID is 4166: Winbond Electronics
4172=Vendor ID is 4172: AMCO TEC International Inc.
4179=Vendor ID is 4179: Immanuel Electronics
4180=Vendor ID is 4180: BMS International Beheer N.V.
4181=Vendor ID is 4181: Complex Micro Interconnection
4182=Vendor ID is 4182: Hsin Chen Ent Co., Ltd.
4183=Vendor ID is 4183: ON Semiconductor
4184=Vendor ID is 4184: Western Digital Technologies, Inc.
4185=Vendor ID is 4185: Giesecke & Devrient GmbH
4188=Vendor ID is 4188: Hong Ji Electric Wire & Cable (Dongguan)
4189=Vendor ID is 4189: Delkin Devices, Inc.
4190=Vendor ID is 4190: Valence Semiconductor Design Limited
4191=Vendor ID is 4191: Chin Shong Enterprise Co., Ltd.
4192=Vendor ID is 4192: Easthome Industrial Co., Ltd.
4195=Vendor ID is 4195: Motorola Electronics Taiwan
4197=Vendor ID is 4197: CCYU Technology
4202=Vendor ID is 4202: Loyal Legend Limited
4204=Vendor ID is 4204: Curitel Communications
4205=Vendor ID is 4205: San Chieh Manufacturing
4206=Vendor ID is 4206: ConectL
4207=Vendor ID is 4207: Money Controls
4214=Vendor ID is 4214: GCT Semiconductor, Inc.
4221=Vendor ID is 4221: Arlec Australia
4222=Vendor ID is 4222: MIDORIYA ELECTRIC
4223=Vendor ID is 4223: KidzMouse
4226=Vendor ID is 4226: Shin-Etsukaken
4227=Vendor ID is 4227: CANON ELECTRONICS INC.
4228=Vendor ID is 4228: PANTECH CO., LTD.
4234=Vendor ID is 4234: Chloride Power Protection
4235=Vendor ID is 4235: Grand-tek Technology Co., Ltd.
4236=Vendor ID is 4236: Robert Bosch GmbH
4249=Vendor ID is 4249: Surface Optics Corporation
4250=Vendor ID is 4250: DATASOFT Systems GmbH
4255=Vendor ID is 4255: eSOL Co., Ltd.
4256=Vendor ID is 4256: HIROTECH, INC.
4259=Vendor ID is 4259: MITSUBISHI MATERIALS CORPORATION
4265=Vendor ID is 4265: SK Teletech Co., Ltd.
4266=Vendor ID is 4266: Cables To Go
4267=Vendor ID is 4267: USI Co., Ltd.
4268=Vendor ID is 4268: Honeywell
4270=Vendor ID is 4270: Princeton Technology Corp.
4277=Vendor ID is 4277: Comodo
4283=Vendor ID is 4283: TM Technology Inc.
4284=Vendor ID is 4284: Dinging Technology Co., Ltd.
4285=Vendor ID is 4285: TMT TECHNOLOGY, INC.
4292=Vendor ID is 4292: Cygnal Integrated Products, Inc.
4293=Vendor ID is 4293: Sanei Electric Inc.
4294=Vendor ID is 4294: Intec, Inc.
4299=Vendor ID is 4299: eratech
4300=Vendor ID is 4300: GBM Connector Co., Ltd.
4301=Vendor ID is 4301: Kycon Inc.
4305=Vendor ID is 4305: Hottinger Baldwin Measurement
4308=Vendor ID is 4308: Man Boon Manufactory Ltd.
4309=Vendor ID is 4309: Uni Class Technology Co., Ltd.
4310=Vendor ID is 4310: Actions Semiconductor Co., Ltd.
4318=Vendor ID is 4318: Authenex, Inc.
4319=Vendor ID is 4319: In-Win Development Inc.
4320=Vendor ID is 4320: Bella Corporation
4321=Vendor ID is 4321: CABLEPLUS LTD.
4322=Vendor ID is 4322: Nada Electronics, Ltd.
4332=Vendor ID is 4332: Vast Technologies Inc.
4347=Vendor ID is 4347: Pictos Technologies
4352=Vendor ID is 4352: VirTouch Ltd.
4353=Vendor ID is 4353: EASYPASS INDUSTRIAL CO., LTD.
4360=Vendor ID is 4360: BRIGHTCOM TECHNOLOGIES LTD.
4362=Vendor ID is 4362: MOXA Technologies Co., Ltd.
4368=Vendor ID is 4368: Analog Devices Canada
4370=Vendor ID is 4370: YM ELECTRIC CO., LTD.
4371=Vendor ID is 4371: Medion AG
4382=Vendor ID is 4382: VSO Electric Co., Ltd.
4398=Vendor ID is 4398: Master Hill Electric Wire and Cable Co., Ltd.
4399=Vendor ID is 4399: Cellon International
4400=Vendor ID is 4400: Tenx Technology, Inc.
4401=Vendor ID is 4401: Integrated System Solution Corp.
4402=Vendor ID is 4402: Toshiba
4412=Vendor ID is 4412: Arin Tech Co., Ltd.
4413=Vendor ID is 4413: Mapower Electronics Co. Ltd.
4415=Vendor ID is 4415: Testech
4417=Vendor ID is 4417: V ONE MULTIMEDIA PTE LTD
4418=Vendor ID is 4418: CYBERSCAN TECH. INC.
4423=Vendor ID is 4423: Ever Great Electric Wire and Cable Co., Ltd.
4428=Vendor ID is 4428: Tinius Olsen Testing Machine Co., Inc.
4429=Vendor ID is 4429: Alpha Imaging Technology Corp.
4450=Vendor ID is 4450: Secugen Corporation
4451=Vendor ID is 4451: DeLorme Publishing Inc.
4452=Vendor ID is 4452: YUAN High-Tech Development Co., Ltd.
4453=Vendor ID is 4453: Telson Electronics Co., Ltd.
4454=Vendor ID is 4454: Bantam Interactive Technologies
4455=Vendor ID is 4455: Salient Systems Corporation
4456=Vendor ID is 4456: BizConn International Corp.
4462=Vendor ID is 4462: Gigastorage Corp.
4463=Vendor ID is 4463: Silicon 10 Technology Corp.
4469=Vendor ID is 4469: Shengyih Steel Mold Co., Ltd.
4477=Vendor ID is 4477: Santa Electronic Inc.
4478=Vendor ID is 4478: JNC, Inc.
4482=Vendor ID is 4482: Venture Corporation Limited
4483=Vendor ID is 4483: Digital Dream Co. Europe Ltd.
4484=Vendor ID is 4484: Kyocera Elco Corporation
4489=Vendor ID is 4489: Trisat Industrial Co., Ltd.
4495=Vendor ID is 4495: You Yang Technology Co., Ltd.
4496=Vendor ID is 4496: Tripace
4497=Vendor ID is 4497: Loyalty Founder Enterprise Co., Ltd.
4503=Vendor ID is 4503: Technoimagia Co., Ltd.
4504=Vendor ID is 4504: StarShine Technology Corp.
4505=Vendor ID is 4505: Sierra Wireless Inc.
4506=Vendor ID is 4506: ZHAN QI Technology Co., Ltd.
4515=Vendor ID is 4515: Technovas Co., Ltd.
4522=Vendor ID is 4522: GlobalMedia Group, LLC
4523=Vendor ID is 4523: Exito Electronics Co., Ltd.
4527=Vendor ID is 4527: Valence Semiconductor
4528=Vendor ID is 4528: ATECH FLASH TECHNOLOGY
4529=Vendor ID is 4529: New Motion Tec. Corp.
4544=Vendor ID is 4544: Sanmos Microelectronics Corp.
4552=Vendor ID is 4552: Fullcom Technology Corp.
4553=Vendor ID is 4553: Monster Cable Products, Inc.
4559=Vendor ID is 4559: Nemoto Kyorindo Co., Ltd.
4566=Vendor ID is 4566: FUJIFILM AXIA CO., LTD.
4571=Vendor ID is 4571: Topfield Co., Ltd.
4581=Vendor ID is 4581: CHUFON Technology Co., Ltd.
4582=Vendor ID is 4582: K.I. Technology Co. Ltd.
4583=Vendor ID is 4583: Rockford Corporation
4584=Vendor ID is 4584: NAAT Technology Corp.
4585=Vendor ID is 4585: Wincan Technology Co., Ltd.
4586=Vendor ID is 4586: PAN RAM International Corp.
4587=Vendor ID is 4587: VTech Innovation L.P. dba Advanced American Telephones
4588=Vendor ID is 4588: Hitachi Computer Peripherals Co., Ltd.
4591=Vendor ID is 4591: Cableplus Industrial Co., Ltd.
4597=Vendor ID is 4597: Siemens Mobile Phones
4610=Vendor ID is 4610: KUK JE TONG SHIN CO., LTD.
4617=Vendor ID is 4617: InterBiometrics
4622=Vendor ID is 4622: HUDSON SOFT CO., LTD.
4631=Vendor ID is 4631: Goyatek Technology Inc.
4632=Vendor ID is 4632: Geutebrueck GmbH
4638=Vendor ID is 4638: Jungsoft
4643=Vendor ID is 4643: SKYCABLE ENTERPRISE. CO., LTD.
4649=Vendor ID is 4649: EPO Science & Technology Inc.
4655=Vendor ID is 4655: Takasic
4656=Vendor ID is 4656: Chipidea-Microelectronica, S.A.
4657=Vendor ID is 4657: CHI MEI COMMUNICATION SYSTEMS, INC.
4667=Vendor ID is 4667: De La Rue Systems Automatizacao
4668=Vendor ID is 4668: K-Won C & C Co., Ltd.
4673=Vendor ID is 4673: Packard Bell
4674=Vendor ID is 4674: MAC SYSTEM CO., LTD.
4682=Vendor ID is 4682: AirVast Technology Inc.
4683=Vendor ID is 4683: NYKO Technologies, Inc.
4689=Vendor ID is 4689: Iwaya Corporation
4690=Vendor ID is 4690: Nextway Co., Ltd.
4691=Vendor ID is 4691: Erebus Limited
4698=Vendor ID is 4698: Shintake Sangyo Co., Ltd.
4705=Vendor ID is 4705: All Ring Tech Co., Ltd.
4706=Vendor ID is 4706: MICRO VISION CO., LTD.
4707=Vendor ID is 4707: Opti Japan Corporation
4715=Vendor ID is 4715: Veridian Systems
4716=Vendor ID is 4716: Aristocrat Technologies
4717=Vendor ID is 4717: Bel Stewart
4718=Vendor ID is 4718: Strobe Data, Inc.
4719=Vendor ID is 4719: TwinMOS Technologies Inc.
4720=Vendor ID is 4720: Procomp Informatics Ltd.
4721=Vendor ID is 4721: Foxda Technology Industrial (Shenzhen) Co., Ltd.
4722=Vendor ID is 4722: Linear Technology Corporation
4725=Vendor ID is 4725: Xaxero Marine Software Engineering
4736=Vendor ID is 4736: Animeta Systems Inc.
4737=Vendor ID is 4737: Gean Sen Electronic Co., Ltd.
4742=Vendor ID is 4742: MARVELL SEMICONDUCTOR, INC.
4753=Vendor ID is 4753: Flarion Technologies
4754=Vendor ID is 4754: Fire International Ltd.
4755=Vendor ID is 4755: Belkin
4763=Vendor ID is 4763: CyberTAN Technology Inc.
4764=Vendor ID is 4764: Min Aik Technology Co., Ltd.
4765=Vendor ID is 4765: Yueqing Longhua Electronics Factory
4771=Vendor ID is 4771: KENT WORLD CO., LTD.
4772=Vendor ID is 4772: Guangdong Matsunichi Communications Technology Co., Ltd
4779=Vendor ID is 4779: Honey Bee Electronic International Ltd.
4781=Vendor ID is 4781: Asahi Seiko Co., Ltd.
4786=Vendor ID is 4786: DICKSON Company
4787=Vendor ID is 4787: Megaforce Company Ltd.
4792=Vendor ID is 4792: Zhejiang Xinya Electronic Technology Co., Ltd.
4793=Vendor ID is 4793: Freehand Systems, Inc.
4794=Vendor ID is 4794: Sony Computer Entertainment America
4797=Vendor ID is 4797: Sun Light Application Co., Ltd.
4809=Vendor ID is 4809: Newmen Technology Corp. Ltd.
4817=Vendor ID is 4817: Huawei Technologies Co., Ltd.
4818=Vendor ID is 4818: LINE TECH INDUSTRIAL CO., LTD.
4823=Vendor ID is 4823: BETTER WIRE FACTORY CO., LTD.
4824=Vendor ID is 4824: Araneus Information Systems Oy
4825=Vendor ID is 4825: DIGITFAB INTERNATIONAL CO., LTD.
4829=Vendor ID is 4829: Alec Electronics Co.,Ltd.
4830=Vendor ID is 4830: National Display Systems
4836=Vendor ID is 4836: Bruel & Kjaer Sound & Vibration Meas. A/S
4841=Vendor ID is 4841: Mindspeed Technologies
4852=Vendor ID is 4852: Glovic Electronics Corp.
4853=Vendor ID is 4853: Dynamic System Electronics Corp.
4855=Vendor ID is 4855: Memorex Products, Inc.
4857=Vendor ID is 4857: RF-LINK SYSTEMS, INC.
4858=Vendor ID is 4858: RF Micro Devices
4862=Vendor ID is 4862: E.U CONNECTOR(M) SDN BHD.
4870=Vendor ID is 4870: Torcon Instruments Inc.
4871=Vendor ID is 4871: USBest Technology Inc.
4882=Vendor ID is 4882: ICS Electronics
4887=Vendor ID is 4887: PC-CRAFT Co., Ltd.
4888=Vendor ID is 4888: O'RITE TECHNOLOGY Co., Ltd.
4895=Vendor ID is 4895: Ayuttha Technology Corp.
4899=Vendor ID is 4899: Zeustech Company Limited
4900=Vendor ID is 4900: H-Mod, Inc.
4905=Vendor ID is 4905: Appairent Technologies, Inc.
4906=Vendor ID is 4906: Envara
4907=Vendor ID is 4907: Konica Minolta Holdings, Inc.
4908=Vendor ID is 4908: Le Prestique International (H.K.) Ltd.
4923=Vendor ID is 4923: FLASH SUPPORT GROUP, INC.
4924=Vendor ID is 4924: G-Design Technology
4930=Vendor ID is 4930: Sutter Instrument Company
4933=Vendor ID is 4933: Sino Lite Technology Corp.
4936=Vendor ID is 4936: Katsuragawa Electric Co., Ltd.
4950=Vendor ID is 4950: Techpoint Electric Wire & Cable Co., Ltd.
4955=Vendor ID is 4955: M-System Co., Ltd.
4970=Vendor ID is 4970: Pelco
4971=Vendor ID is 4971: SimpleTech
4972=Vendor ID is 4972: Datastor Technology Co., Ltd.
4980=Vendor ID is 4980: American Anko Co.
4981=Vendor ID is 4981: TCL MOBILE COMMUNICATION CO., LTD.
4982=Vendor ID is 4982: Vimtron Electronics Co., Ltd.
4988=Vendor ID is 4988: Yaskawa Electric Corporation
4989=Vendor ID is 4989: Pericom Taiwan Limited
4990=Vendor ID is 4990: XL Microwave, Inc.
5001=Vendor ID is 5001: Coolnection Technology Co., Ltd.
5008=Vendor ID is 5008: TOMTOM B.V.
5013=Vendor ID is 5013: Sennheiser Communications A/S
5014=Vendor ID is 5014: Silicon Storage Technology, Inc.
5028=Vendor ID is 5028: Equipment Systems & Devices
5029=Vendor ID is 5029: Sammy Corporation
5030=Vendor ID is 5030: Jeppesen Sanderson Inc.
5032=Vendor ID is 5032: Grandtec Electronic Corp
5040=Vendor ID is 5040: PerkinElmer Optoelectronics
5041=Vendor ID is 5041: Cisco-Linksys, LLC
5042=Vendor ID is 5042: ALESIS
5043=Vendor ID is 5043: Nippon Dics Co., Ltd.
5048=Vendor ID is 5048: PDM Electronic
5054=Vendor ID is 5054: Hitachi Printing Solutions
5055=Vendor ID is 5055: Accusys
5056=Vendor ID is 5056: Stream Labs
5057=Vendor ID is 5057: Vivitar
5065=Vendor ID is 5065: LinearX Systems
5066=Vendor ID is 5066: Suzhou Jye Tai Precision Industrial
5067=Vendor ID is 5067: JTEK Technology
5068=Vendor ID is 5068: Cellvic
5071=Vendor ID is 5071: Wisair
5073=Vendor ID is 5073: A-MAX Technology
5074=Vendor ID is 5074: Shark Multimedia
5075=Vendor ID is 5075: TwinHan Technology
5084=Vendor ID is 5084: ALEREON
5085=Vendor ID is 5085: i.Tech Dynamic
5086=Vendor ID is 5086: LANKOM ELECTRONICS
5087=Vendor ID is 5087: Good Fancy Enterprise
5088=Vendor ID is 5088: Taiwan Silicon Electronics
5089=Vendor ID is 5089: Kaibo Wire & Cable (Shenzhen)
5094=Vendor ID is 5094: TechnoScope
5098=Vendor ID is 5098: I/F - COM A/S
5108=Vendor ID is 5108: Verisity Design
5110=Vendor ID is 5110: Aspen Touch Solutions
5111=Vendor ID is 5111: Corevalley
5112=Vendor ID is 5112: EZPnP Technologies
5118=Vendor ID is 5118: Phison Electronics
5119=Vendor ID is 5119: VIEWCON ELECTRONIC
5120=Vendor ID is 5120: Axxion Group
5121=Vendor ID is 5121: Fulhua Microelectronics
5122=Vendor ID is 5122: Bowe Bell & Howell
5123=Vendor ID is 5123: Sitronix Technology
5134=Vendor ID is 5134: Telechips
5141=Vendor ID is 5141: Sony Computer Entertainment Europe
5145=Vendor ID is 5145: ABILITY ENTERPRISE
5146=Vendor ID is 5146: Realm Systems
5147=Vendor ID is 5147: METRAWARE
5148=Vendor ID is 5148: Leviton Manufacturing
5153=Vendor ID is 5153: Sensor Technologies America
5161=Vendor ID is 5161: Vega Technologies Industrial (Austria)
5168=Vendor ID is 5168: RedOctane
5172=Vendor ID is 5172: Comart System
5173=Vendor ID is 5173: Wistron NeWeb
5174=Vendor ID is 5174: Denali Software
5176=Vendor ID is 5176: My3ia (Beijing) Technology
5177=Vendor ID is 5177: Wind River Systems
5178=Vendor ID is 5178: CP Technologies
5186=Vendor ID is 5186: Canadian Bank Note Company
5189=Vendor ID is 5189: JUSTER
5203=Vendor ID is 5203: RadioShack
5205=Vendor ID is 5205: Georgia Technology
5206=Vendor ID is 5206: Extending Wire & Cable
5209=Vendor ID is 5209: Shanghai Simax Micro-electronics
5211=Vendor ID is 5211: Lead-Type Precision Electronics
5214=Vendor ID is 5214: Forschungszentrum Karlsruhe GmbH
5217=Vendor ID is 5217: Staccato Communications
5218=Vendor ID is 5218: Bright Computech
5219=Vendor ID is 5219: BBWM
5220=Vendor ID is 5220: Asiamajor
5229=Vendor ID is 5229: Progeny
5230=Vendor ID is 5230: ClearOne Communications
5231=Vendor ID is 5231: Unity Electrical Ind.
5232=Vendor ID is 5232: STARRIVER TECHNOLOGY
5234=Vendor ID is 5234: Hangzhou Huawei-3Com Tech.
5235=Vendor ID is 5235: Dingo
5242=Vendor ID is 5242: Formosa Industrial Computing
5247=Vendor ID is 5247: Hama
5252=Vendor ID is 5252: Elsa AG 
5253=Vendor ID is 5253: OrangeWare
5255=Vendor ID is 5255: DSP Group
5256=Vendor ID is 5256: Orion Technology
5261=Vendor ID is 5261: DESMA
5262=Vendor ID is 5262: EVATRONIX SA
5263=Vendor ID is 5263: Ralink Technology,
5271=Vendor ID is 5271: Panstrong Company
5272=Vendor ID is 5272: ULi Electronics
5273=Vendor ID is 5273: G-STAR Communications
5274=Vendor ID is 5274: Imagination Technologies
5278=Vendor ID is 5278: Amkor Technology
5279=Vendor ID is 5279: Wits Technologies Pte.
5285=Vendor ID is 5285: I-ROCKS TECHNOLOGY
5293=Vendor ID is 5293: CTK
5294=Vendor ID is 5294: Printronix
5295=Vendor ID is 5295: ATP Electronics
5296=Vendor ID is 5296: Startech.com
5300=Vendor ID is 5300: Inventec Appliances
5305=Vendor ID is 5305: BP Microsystems
5306=Vendor ID is 5306: FLOVEL
5307=Vendor ID is 5307: Assembly Tech.
5314=Vendor ID is 5314: Gemlight Computer Ltd.
5349=Vendor ID is 5349: SAIN Information & Communications
5375=Vendor ID is 5375: Twinhead International Corp.
5408=Vendor ID is 5408: Bitwire Corp.
5460=Vendor ID is 5460: Prolink Microsystems Corporation
5480=Vendor ID is 5480: Sunf Pu Technology Co., Ltd
5608=Vendor ID is 5608: SohoWare
5609=Vendor ID is 5609: Pacific Digital
5636=Vendor ID is 5636: Tascam
5638=Vendor ID is 5638: Umax
5640=Vendor ID is 5640: Inside Out Networks
5701=Vendor ID is 5701: Entrega
5736=Vendor ID is 5736: Actiontec Electronics
5776=Vendor ID is 5776: Askey Computer
5782=Vendor ID is 5782: Hitachi Advanced Digital, Inc.
5783=Vendor ID is 5783: VTEC TEST, INC.
6292=Vendor ID is 6292: Topseed
6800=Vendor ID is 6800: Mentor Graphics
7867=Vendor ID is 7867: NuCORE Technology, Inc.
8193=Vendor ID is 8193: D-Link
8256=Vendor ID is 8256: Hauppauge Computer Works, Inc.
8449=Vendor ID is 8449: ActionStar
8546=Vendor ID is 8546: Creative (?)
8738=Vendor ID is 8738: MacAlly
8888=Vendor ID is 8888: Motorola PCS
8889=Vendor ID is 8889: eTurboTouch Technology Inc.
8890=Vendor ID is 8890: Technology Innovation Holdings
8964=Vendor ID is 8964: Pinnacle Systems, Inc.
8984=Vendor ID is 8984: Shining Technologies
9077=Vendor ID is 9077: Digit@lway
9778=Vendor ID is 9778: TwinMOS
9797=Vendor ID is 9797: Lead Data Inc.
9808=Vendor ID is 9808: Electronics For Imaging, Inc.
10096=Vendor ID is 10096: NHJ
10393=Vendor ID is 10393: Toptronic Industrial
12581=Vendor ID is 12581: Eagletron
12662=Vendor ID is 12662: WHANAM ELECTRONICS CO., Ltd. MS division
13108=Vendor ID is 13108: AEI
13572=Vendor ID is 13572: Micro Star
13624=Vendor ID is 13624: Power Quotient International
13689=Vendor ID is 13689: DIVA
13878=Vendor ID is 13878: InVibro
14392=Vendor ID is 14392: WEM
14627=Vendor ID is 14627: National Instruments
16700=Vendor ID is 16700: Dell Computer Corp.
16962=Vendor ID is 16962: USB Design By Example
21581=Vendor ID is 21581: Transmeta
21827=Vendor ID is 21827: UC-Logic Technology
21930=Vendor ID is 21930: OnSpec Electronic Inc.
25452=Vendor ID is 25452: CoreLogic, Inc.
25600=Vendor ID is 25600: Springer Design
26214=Vendor ID is 26214: Prototype product Vendor ID
27253=Vendor ID is 27253: Shanghai Jujo Electronics Co., Ltd.
32902=Vendor ID is 32902: Intel Corporation
38672=Vendor ID is 38672: Moschip Semiconductor Technology
49745=Vendor ID is 49745: Keil Software
60186=Vendor ID is 60186: Empia Technology , Inc.

      
   }
   FormatValue=The Vendor ID is 0x%04X

}

; idProduct  description
Offset(10)={

   Size=2   
   FormatValue=The Product ID is 0x%04X

}

; bcdDevice  description
Offset(12)={

   Size=2  
   BCD=TRUE
   FormatValue=The device release number is %X.%02X
   
}

; iManufacturer  description
Offset(14)={
  WordValue={
     0x00=The device doesn't have the string descriptor describing the manufacturer
  }
  FormatValue=The index of the string descriptor describing the manufacturer is %d
}

; iProduct  description
Offset(15)={

  WordValue={
     0x00=The device doesn't have the string descriptor describing the product
  }
  FormatValue=The index of the string descriptor describing the product is %d
}

; iSerialNumber  description
Offset(16)={

  WordValue={
     0x00=The device doesn't have the string descriptor describing the serial number
  }
  FormatValue=The index of the string descriptor describing the serial number is %d
}

; bNumConfigurations  description
Offset(17)={

  FormatValue=The device has %d possible configurations

}


*******************************************************************************
* CONFIGURATION Descriptor definitions
*******************************************************************************
DescriptorName=CONFIGURATION
DescriptorType=0x02

AllOffsets={
 2=wTotalLength
 4=bNumInterfaces
 5=bConfigurationValue
 6=iConfiguration
 7=bmAttributes
 8=MaxPower
}

; wTotalLength  description
Offset(2)={
   Size=2
   FormatValue=The total length of data for this configuration is %i. This includes the combined length of all the descriptors returned
}

; bNumInterfaces  description
Offset(4)={
   FormatValue=This configuration supports %i interfaces
}

; bConfigurationValue  description
Offset(5)={
   FormatValue=The value %i should be used to select this configuration
}

; iConfiguration  description
Offset(6)={
   WordValue={
      0x00=The device doesn't have the string descriptor describing this configuration
   }
   FormatValue=The index of the string descriptor describing this configuration is %d
}

; bmAttributes  description
Offset(7)={
   Name=Configuration characteristics
   Bitmap={
      7=Reserved (set to one)
      6=Self-powered
      5=Remote Wakeup
   }   
}

; MaxPower  description
Offset(8)={
   Units=2
   FormatValue=Maximum power consumption of the device in this configuration is %i mA
}


*******************************************************************************
* INTERFACE Descriptor definitions
*******************************************************************************
DescriptorName=INTERFACE
DescriptorType=0x04

AllOffsets={
 2=bInterfaceNumber
 3=bAlternateSetting
 4=bNumEndpoints
 5=bInterfaceClass
 6=bInterfaceSubClass
 7=bInterfaceProtocol
 8=iInterface
}

; bInterfaceNumber  description
Offset(2)={
   FormatValue=The number of this interface is %i
}

; bAlternateSetting  description
Offset(3)={
   FormatValue=The value used to select alternate setting for this interface is %i
}

; bNumEndpoints  description
Offset(4)={
   FormatValue=The number of endpoints used by this interface is %i (excluding endpoint zero)
}

; bInterfaceClass  description
Offset(5)={

   WordValue={
      0xFF=The interface class is vendor-specific
      0x00=This value is reserved for future standartization
      0x01=The interface implements Audio Interface class
      0x03=The interface implements HID class
      0x06=The interface implements Still Image class
      0x07=The interface implements Printer class
      0x08=The interface implements Mass Storage class
      0x09=The interface implements HUB class
      0x0E=The interface implements Video class
   }
   FormatValue=The class code is 0x%02X

}

; bInterfaceSubClass  description
Offset(6)={

   WordValue={
      0xFF=The interface subclass is vendor-specific
   }
   FormatValue=The subclass code is 0x%02X

}

; bInterfaceProtocol  description
Offset(7)={

   WordValue={
      0xFF=The interface protocol is vendor-specific
      0x00=The interface doesn't use any class-specific protocols
   }
   FormatValue=The protocol code is 0x%02X

}

; iInterface  description
Offset(8)={
   WordValue={
      0x00=The device doesn't have the string descriptor describing this interface
   }
   FormatValue=The index of the string descriptor describing this interface is %d  
}


*******************************************************************************
* ENDPOINT Descriptor definitions
*******************************************************************************
DescriptorName=ENDPOINT
DescriptorType=0x05

AllOffsets={
 2=bEndpointAddress
 3=bmAttributes
 4=wMaxPacketSize
 6=bInterval
}

; bEndpointAddress  description
Offset(2)={
   WordValue={
      0x01=This is an OUT endpoint with address (endpoint number) 1
      0x02=This is an OUT endpoint with address (endpoint number) 2
      0x03=This is an OUT endpoint with address (endpoint number) 3
      0x04=This is an OUT endpoint with address (endpoint number) 4
      0x05=This is an OUT endpoint with address (endpoint number) 5
      0x06=This is an OUT endpoint with address (endpoint number) 6
      0x07=This is an OUT endpoint with address (endpoint number) 7
      0x08=This is an OUT endpoint with address (endpoint number) 8
      0x09=This is an OUT endpoint with address (endpoint number) 9
      0x0A=This is an OUT endpoint with address (endpoint number) 10
      0x0B=This is an OUT endpoint with address (endpoint number) 11
      0x0C=This is an OUT endpoint with address (endpoint number) 12
      0x0D=This is an OUT endpoint with address (endpoint number) 13
      0x0E=This is an OUT endpoint with address (endpoint number) 14
      0x0F=This is an OUT endpoint with address (endpoint number) 15

      0x81=This is an IN endpoint with address (endpoint number) 1
      0x82=This is an IN endpoint with address (endpoint number) 2
      0x83=This is an IN endpoint with address (endpoint number) 3
      0x84=This is an IN endpoint with address (endpoint number) 4
      0x85=This is an IN endpoint with address (endpoint number) 5
      0x86=This is an IN endpoint with address (endpoint number) 6
      0x87=This is an IN endpoint with address (endpoint number) 7
      0x88=This is an IN endpoint with address (endpoint number) 8
      0x89=This is an IN endpoint with address (endpoint number) 9
      0x8A=This is an IN endpoint with address (endpoint number) 10
      0x8B=This is an IN endpoint with address (endpoint number) 11
      0x8C=This is an IN endpoint with address (endpoint number) 12
      0x8D=This is an IN endpoint with address (endpoint number) 13
      0x8E=This is an IN endpoint with address (endpoint number) 14
      0x8F=This is an IN endpoint with address (endpoint number) 15
   }
   FormatValue=Invalid endpoint address (reserved bits are set to one)!
}

; bmAttributes
Offset(3)={
   WordValue={
      0x00=Types - Transfer:CONTROL Sync:No Sync Usage:Data EP
      0x01=Types - Transfer:ISOCHRONOUS Sync:No Sync Usage:Data EP   
      0x02=Types - Transfer:BULK Sync:No Sync Usage:Data EP
      0x03=Types - Transfer:INTERRUPT Sync:No Sync Usage:Data EP
      0x04=Types - Transfer:CONTROL Sync:Async Usage:Data EP
      0x05=Types - Transfer:ISOCHRONOUS Sync:Async Usage:Data EP
      0x06=Types - Transfer:BULK Sync:Async Usage:Data EP
      0x07=Types - Transfer:INTERRUPT Sync:Async Usage:Data EP
      0x08=Types - Transfer:CONTROL Sync:Adaptive Usage:Data EP
      0x09=Types - Transfer:ISOCHRONOUS Sync:Adaptive Usage:Data EP
      0x0A=Types - Transfer:BULK Sync:Adaptive Usage:Data EP
      0x0B=Types - Transfer:INTERRUPT Sync:Adaptive Usage:Data EP
      0x0C=Types - Transfer:CONTROL Sync:Sync Usage:Data EP
      0x0D=Types - Transfer:ISOCHRONOUS Sync:Sync Usage:Data EP
      0x0E=Types - Transfer:BULK Sync:Sync Usage:Data EP
      0x0F=Types - Transfer:INTERRUPT Sync:Sync Usage:Data EP
      0x10=Types - Transfer:CONTROL Sync:No Sync Usage:Feedback EP
      0x11=Types - Transfer:ISOCHRONOUS Sync:No Sync Usage:Feedback EP
      0x12=Types - Transfer:BULK Sync:No Sync Usage:Feedback EP
      0x13=Types - Transfer:INTERRUPT Sync:No Sync Usage:Feedback EP
      0x14=Types - Transfer:CONTROL Sync:Async Usage:Feedback EP
      0x15=Types - Transfer:ISOCHRONOUS Sync:Async Usage:Feedback EP
      0x16=Types - Transfer:BULK Sync:Async Usage:Feedback EP
      0x17=Types - Transfer:INTERRUPT Sync:Async Usage:Feedback EP
      0x18=Types - Transfer:CONTROL Sync:Adaptive Usage:Feedback EP
      0x19=Types - Transfer:ISOCHRONOUS Sync:Adaptive Usage:Feedback EP
      0x1A=Types - Transfer:BULK Sync:Adaptive Usage:Feedback EP
      0x1B=Types - Transfer:INTERRUPT Sync:Adaptive Usage:Feedback EP
      0x1C=Types - Transfer:CONTROL Sync:Sync Usage:Feedback EP
      0x1D=Types - Transfer:ISOCHRONOUS Sync:Sync Usage:Feedback EP
      0x1E=Types - Transfer:BULK Sync:Sync Usage:Feedback EP
      0x1F=Types - Transfer:INTERRUPT Sync:Sync Usage:Feedback EP
      0x20=Types - Transfer:CONTROL Sync:No Sync Usage:Implicit Feedback EP
      0x21=Types - Transfer:ISOCHRONOUS Sync:No Sync Usage:Implicit Feedback EP
      0x22=Types - Transfer:BULK Sync:No Sync Usage:Implicit Feedback EP
      0x23=Types - Transfer:INTERRUPT Sync:No Sync Usage:Implicit Feedback EP
      0x24=Types - Transfer:CONTROL Sync:Async Usage:Implicit Feedback EP
      0x25=Types - Transfer:ISOCHRONOUS Sync:Async Usage:Implicit Feedback EP
      0x26=Types - Transfer:BULK Sync:Async Usage:Implicit Feedback EP
      0x27=Types - Transfer:INTERRUPT Sync:Async Usage:Implicit Feedback EP
      0x28=Types - Transfer:CONTROL Sync:Adaptive Usage:Implicit Feedback EP
      0x29=Types - Transfer:ISOCHRONOUS Sync:Adaptive Usage:Implicit Feedback EP
      0x2A=Types - Transfer:BULK Sync:Adaptive Usage:Implicit Feedback EP
      0x2B=Types - Transfer:INTERRUPT Sync:Adaptive Usage:Implicit Feedback EP
      0x2C=Types - Transfer:CONTROL Sync:Sync Usage:Implicit Feedback EP
      0x2D=Types - Transfer:ISOCHRONOUS Sync:Sync Usage:Implicit Feedback EP
      0x2E=Types - Transfer:BULK Sync:Sync Usage:Implicit Feedback EP
      0x2F=Types - Transfer:INTERRUPT Sync:Sync Usage:Implicit Feedback EP
      0x30=Types - Transfer:CONTROL Sync:No Sync Usage:RESERVED
      0x31=Types - Transfer:ISOCHRONOUS Sync:No Sync Usage:RESERVED
      0x32=Types - Transfer:BULK Sync:No Sync Usage:RESERVED
      0x33=Types - Transfer:INTERRUPT Sync:No Sync Usage:RESERVED
      0x34=Types - Transfer:CONTROL Sync:Async Usage:RESERVED
      0x35=Types - Transfer:ISOCHRONOUS Sync:Async Usage:RESERVED
      0x36=Types - Transfer:BULK Sync:Async Usage:RESERVED
      0x37=Types - Transfer:INTERRUPT Sync:Async Usage:RESERVED
      0x38=Types - Transfer:CONTROL Sync:Adaptive Usage:RESERVED
      0x39=Types - Transfer:ISOCHRONOUS Sync:Adaptive Usage:RESERVED
      0x3A=Types - Transfer:BULK Sync:Adaptive Usage:RESERVED
      0x3B=Types - Transfer:INTERRUPT Sync:Adaptive Usage:RESERVED
      0x3C=Types - Transfer:CONTROL Sync:Sync Usage:RESERVED
      0x3D=Types - Transfer:ISOCHRONOUS Sync:Sync Usage:RESERVED
      0x3E=Types - Transfer:BULK Sync:Sync Usage:RESERVED
      0x3F=Types - Transfer:INTERRUPT Sync:Sync Usage:RESERVED
   }
   FormatValue=Invalid Attributes value: 0x%X

}

; wMaxPacketSize  description
Offset(4)={
   Size=2
   FormatValue=Maximum packet size value for this endpoint is 0x%X (Bits 12-11: Addtl. Transactions/frame)
}

; bInterval  description
Offset(6)={
   FormatValue=bInterval:%d. The polling interval value is bInterval or 2**(bInterval-1)
}



*******************************************************************************
* DEVICE_QUALIFIER Descriptor definitions
*******************************************************************************
DescriptorName=DEVICE_QUALIFIER
DescriptorType=0x06

AllOffsets={
 2=bcdUSB
 4=bDeviceClass
 5=bDeviceSubClass
 6=bDeviceProtocol
 7=bMaxPacketSize0
 8=bNumConfigurations
 9=Reserved
}

; bcdUSB  description
Offset(2)={

   Size=2  
   BCD=TRUE
   FormatValue=Device compliant to the USB specification version %X.%02X   
}

; bDeviceClass  description
Offset(4)={

   WordValue={
      0xFF=The device class is vendor-specific
      0x00=Each interface specifies its own class information
      0x01=The device belongs to Audio Interface class
      0x03=The device belongs to HID class
      0x06=The device belongs to Still Image class
      0x07=The device belongs to Printer class
      0x08=The device belongs to Mass Storage class
      0x09=The device belongs to the HUB class
   }
   FormatValue=The class code is 0x%02X

}

; bDeviceSubClass  description
Offset(5)={

   WordValue={
      0xFF=The device subclass is vendor-specific
      0x00=Each interface specifies its own subclass information
   }
   FormatValue=The subclass code is 0x%02X

}

; bDeviceProtocol  description
Offset(6)={

   WordValue={
      0xFF=The device protocol is vendor-specific
      0x00=No protocols on the device basis
   }
   FormatValue=The protocol code is 0x%02X

}

; bMaxPacketSize0  description
Offset(7)={

   WordValue={
      0x08=Maximum packet size for endpoint zero is 8
      0x10=Maximum packet size for endpoint zero is 16
      0x20=Maximum packet size for endpoint zero is 32
      0x40=Maximum packet size for endpoint zero is 64
   }
   FormatValue=Maximum packet size for endpoint zero is %d (invalid size)!

}


; bNumConfigurations  description
Offset(8)={

  FormatValue=The device has %d possible other-speed configurations

}

 
 
*******************************************************************************
* OTHER_SPEED_CONFIGURATION Descriptor definitions
*******************************************************************************
DescriptorName=OTHER_SPEED_CONFIGURATION
DescriptorType=0x07

AllOffsets={
 2=wTotalLength
 4=bNumInterfaces
 5=bConfigurationValue
 6=iConfiguration
 7=bmAttributes
 8=MaxPower
}

; wTotalLength  description
Offset(2)={
   Size=2
   FormatValue=The total length of data for this configuration is %i. This includes the combined length of all the descriptors returned
}

; bNumInterfaces  description
Offset(4)={
   FormatValue=This configuration supports %i interfaces
}

; bConfigurationValue  description
Offset(5)={
   FormatValue=The value %i should be used to select this configuration
}

; iConfiguration  description
Offset(6)={
   WordValue={
      0x00=The device doesn't have the string descriptor describing this configuration
   }
   FormatValue=The index of the string descriptor describing this configuration is %d
}

; bmAttributes  description
Offset(7)={
   Name=Configuration characteristics
   Bitmap={
      7=Reserved (set to one)
      6=Self-powered
      5=Remote Wakeup
   }   
}

; MaxPower  description
Offset(8)={
   Units=2
   FormatValue=Maximum power consumption of the device in this configuration is %i mA
}

 
 
*******************************************************************************
* OTG Descriptor definitions
*******************************************************************************
DescriptorName=OTG
DescriptorType=0x09

AllOffsets={
 2=bmAttributes
}

; bmAttributes  description
Offset(2)={
   Name=OTG Device Characteristics
   Bitmap={
      0=SRP Support
      1=HNP Support
   }   
}

 
*******************************************************************************
* INTERFACE_ASSOCIATION  Descriptor definitions
*******************************************************************************
DescriptorName=INTERFACE_ASSOCIATION
DescriptorType=0x11

AllOffsets={
 0=bLength
 1=bDescriptorType
 2=bFirstInterface
 3=bInterfaceCount
 4=bFunctionClass
 5=bFunctionSubClass
 6=bFunctionProtocol
 7=iFunction
}

; bLength  description
Offset(0)={
   FormatValue=The length of this descriptor is %i bytes.
}

; bDescriptorType  description
Offset(1)={
   WordValue={
      0xEF=INTERFACE ASSOCIATION
   }   
   FormatValue=Error: The descriptor type is 0x%02X, expected 0xEF (INTERFACE_ASSOCIATION)
}

; bFirstInterface  description
Offset(2)={
   FormatValue=The first interface number associated with this function is %i
}

; bInterfaceCount  description
Offset(3)={
   FormatValue=The number of contiguous interfaces associated with this function is %i
}

; bFunctionClass  description
Offset(4)={
   WordValue={
      0xFF=The function class is vendor-specific
      0x00=VALUE NOT ALLOWED (0x00)
      0x01=The function class is Audio Interface class
      0x03=The function class is HID class
      0x06=The function class is Still Image class
      0x07=The function class is Printer class
      0x08=The function class is Mass Storage class
      0x09=The function class is the HUB class
      0x0E=The function class is the Video class
      0xEF=The function class is the Miscellaneous Device Class

   }
   FormatValue=The function class code is 0x%02X
}

; bFunctionSubClass  description
Offset(5)={
   FormatValue=The function subclass code is 0x%02X
}

; bFunctionProtocol  description
Offset(6)={
   FormatValue=The function protocol code is 0x%02X
}

; iFunction  description
Offset(7)={
   FormatValue=The index of the string descriptor describing this function is %i
}











































































































































































































































































































































































































































































































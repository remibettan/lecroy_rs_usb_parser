
#
#  Internet Protocol Class Out Endpoint
#

%include "IP_Common.inc"
%include "CATCScriptAPI.inc"
%include "UsbCommon.inc"


# Please see "View Settings" commnet in "CataLyst_Common.inc"
#					[collapsed, expanded]
const IP_Protocol		= [1, 1];

#-----------------------------------------------------------------------------

const Tabular_Def_Table = Map( 
[   
    #-----------------------------------------------------------------------------------------------------
    #       id                  ,      colId                          , 		containerCellId
    #-----------------------------------------------------------------------------------------------------
    [ CELL_IP_PROTOCOL          , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE    , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ CELL_IP_VERSION           , TABULAR_SCRIPT_COLUMN_ID_NONE       , TABULAR_SCRIPT_CONTAINER_CELL_ID_MISC ]

] );


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Version (4 bits): Specifies the format of the IP packet header.
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set IPVersion_FieldDecodeTable =
[
	# Value   Decode
	[ 1		, "Undefined Value" ], # 1, 2, 3, 10~14 are undefined.
	[ 0		, "Reserved" ],
	[ 4		, "IP, Internet Protocol" ],
	[ 5		, "ST, ST Datagram Mode" ],
	[ 6		, "SIP, Simple Internet Protocol. SIPP, Simple Internet Protocol Plus. IPv6, Internet Protocol." ],
	[ 7		, "TP/IX, The Next Internet" ],
	[ 8		, "PIP, The P Internet Protocol" ],
	[ 9		, "TUBA" ],
	[ 15	, "Reserved" ]
];
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Protocol (8 bits): This field specifies the next encapsulated protocol.
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set IPProtocol_FieldDecodeTable =
[
	# Value   Decode
	[ 252	, "Undefined Value" ], # 138~252 are undefined.
	[ 0		, "HOPOPT, IPv6 Hop-by-Hop Option." ],
	[ 1		, "ICMP, Internet Control Message Protocol." ],
	[ 2		, "IGAP, IGMP for user Authentication Protocol. IGMP, Internet Group Management Protocol. RGMP, Router-port Group Management Protocol." ],
	[ 3		, "GGP, Gateway to Gateway Protocol." ],
	[ 4		, "IP in IP encapsulation." ],
	[ 5		, "ST, Internet Stream Protocol." ],
	[ 6		, "TCP, Transmission Control Protocol." ],
	[ 7		, "UCL, CBT." ],
	[ 8		, "EGP, Exterior Gateway Protocol." ],
	[ 9		, "IGRP, Interior Gateway Routing Protocol." ],
	[ 10	, "BBN RCC Monitoring." ],
	[ 11	, "NVP, Network Voice Protocol." ],
	[ 12	, "PUP." ],
	[ 13	, "ARGUS." ],
	[ 14	, "EMCON, Emission Control Protocol." ],
	[ 15	, "XNET, Cross Net Debugger." ],
	[ 16	, "Chaos." ],
	[ 17	, "UDP, User Datagram Protocol." ],
	[ 18	, "TMux, Transport Multiplexing Protocol." ],
	[ 19	, "DCN Measurement Subsystems." ],
	[ 20	, "HMP, Host Monitoring Protocol." ],
	[ 21	, "Packet Radio Measurement." ],
	[ 22	, "XEROX NS IDP." ],
	[ 23	, "Trunk-1." ],
	[ 24	, "Trunk-2." ],
	[ 25	, "Leaf-1." ],
	[ 26	, "Leaf-2." ],
	[ 27	, "RDP, Reliable Data Protocol." ],
	[ 28	, "IRTP, Internet Reliable Transaction Protocol." ],
	[ 29	, "ISO Transport Protocol Class 4." ],
	[ 30	, "NETBLT, Network Block Transfer." ],
	[ 31	, "MFE Network Services Protocol." ],
	[ 32	, "MERIT Internodal Protocol." ],
	[ 33	, "SEP, Sequential Exchange Protocol. DCCP, Datagram Congestion Control Protocol." ],
	[ 34	, "Third Party Connect Protocol." ],
	[ 35	, "IDPR, Inter-Domain Policy Routing Protocol." ],
	[ 36	, "XTP, Xpress Transfer Protocol." ],
	[ 37	, "Datagram Delivery Protocol." ],
	[ 38	, "IDPR, Control Message Transport Protocol." ],
	[ 39	, "TP++ Transport Protocol." ],
	[ 40	, "IL Transport Protocol." ],
	[ 41	, "IPv6 over IPv4." ],
	[ 42	, "SDRP, Source Demand Routing Protocol." ],
	[ 43	, "IPv6 Routing header." ],
	[ 44	, "IPv6 Fragment header." ],
	[ 45	, "IDRP, Inter-Domain Routing Protocol." ],
	[ 46	, "RSVP, Reservation Protocol." ],
	[ 47	, "GRE, General Routing Encapsulation." ],
	[ 48	, "MHRP, Mobile Host Routing Protocol." ],
	[ 49	, "BNA." ],
	[ 50	, "ESP, Encapsulating Security Payload." ],
	[ 51	, "AH, Authentication Header." ],
	[ 52	, "Integrated Net Layer Security TUBA." ],
	[ 53	, "IP with Encryption." ],
	[ 54	, "NARP, NBMA Address Resolution Protocol." ],
	[ 55	, "Minimal Encapsulation Protocol." ],
	[ 56	, "TLSP, Transport Layer Security Protocol using Kryptonet key management." ],
	[ 57	, "SKIP." ],
	[ 58	, "ICMPv6, Internet Control Message Protocol for IPv6. MLD, Multicast Listener Discovery." ],
	[ 59	, "IPv6 No Next Header." ],
	[ 60	, "Destination Options for IPv6." ],
	[ 61	, "Any host internal protocol." ],
	[ 62	, "CFTP." ],
	[ 63	, "Any local network." ],
	[ 64	, "SATNET and Backroom EXPAK." ],
	[ 65	, "Kryptolan." ],
	[ 66	, "MIT Remote Virtual Disk Protocol." ],
	[ 67	, "Internet Pluribus Packet Core." ],
	[ 68	, "Any distributed file system." ],
	[ 69	, "SATNET Monitoring." ],
	[ 70	, "VISA Protocol." ],
	[ 71	, "Internet Packet Core Utility." ],
	[ 72	, "Computer Protocol Network Executive." ],
	[ 73	, "Computer Protocol Heart Beat." ],
	[ 74	, "Wang Span Network." ],
	[ 75	, "Packet Video Protocol." ],
	[ 76	, "Backroom SATNET Monitoring." ],
	[ 77	, "SUN ND PROTOCOL-Temporary." ],
	[ 78	, "WIDEBAND Monitoring." ],
	[ 79	, "WIDEBAND EXPAK." ],
	[ 80	, "ISO-IP." ],
	[ 81	, "VMTP, Versatile Message Transaction Protocol." ],
	[ 82	, "SECURE-VMTP" ],
	[ 83	, "VINES." ],
	[ 84	, "TTP." ],
	[ 85	, "NSFNET-IGP." ],
	[ 86	, "Dissimilar Gateway Protocol." ],
	[ 87	, "TCF." ],
	[ 88	, "EIGRP." ],
	[ 89	, "OSPF, Open Shortest Path First Routing Protocol. MOSPF, Multicast Open Shortest Path First." ],
	[ 90	, "Sprite RPC Protocol." ],
	[ 91	, "Locus Address Resolution Protocol." ],
	[ 92	, "MTP, Multicast Transport Protocol." ],
	[ 93	, "AX.25." ],
	[ 94	, "IP-within-IP Encapsulation Protocol." ],
	[ 95	, "Mobile Internetworking Control Protocol." ],
	[ 96	, "Semaphore Communications Sec. Pro." ],
	[ 97	, "EtherIP." ],
	[ 98	, "Encapsulation Header." ],
	[ 99	, "Any private encryption scheme." ],
	[ 100	, "GMTP." ],
	[ 101	, "IFMP, Ipsilon Flow Management Protocol." ],
	[ 102	, "PNNI over IP." ],
	[ 103	, "PIM, Protocol Independent Multicast." ],
	[ 104	, "ARIS." ],
	[ 105	, "SCPS." ],
	[ 106	, "QNX." ],
	[ 107	, "Active Networks." ],
	[ 108	, "IPPCP, IP Payload Compression Protocol." ],
	[ 109	, "SNP, Sitara Networks Protocol." ],
	[ 110	, "Compaq Peer Protocol." ],
	[ 111	, "IPX in IP." ],
	[ 112	, "VRRP, Virtual Router Redundancy Protocol." ],
	[ 113	, "PGM, Pragmatic General Multicast." ],
	[ 114	, "any 0-hop protocol." ],
	[ 115	, "L2TP, Level 2 Tunneling Protocol." ],
	[ 116	, "DDX, D-II Data Exchange." ],
	[ 117	, "IATP, Interactive Agent Transfer Protocol." ],
	[ 118	, "ST, Schedule Transfer." ],
	[ 119	, "SRP, SpectraLink Radio Protocol." ],
	[ 120	, "UTI." ],
	[ 121	, "SMP, Simple Message Protocol." ],
	[ 122	, "SM." ],
	[ 123	, "PTP, Performance Transparency Protocol." ],
	[ 124	, "ISIS over IPv4." ],
	[ 125	, "FIRE." ],
	[ 126	, "CRTP, Combat Radio Transport Protocol." ],
	[ 127	, "CRUDP, Combat Radio User Datagram." ],
	[ 128	, "SSCOPMCE." ],
	[ 129	, "IPLT." ],
	[ 130	, "SPS, Secure Packet Shield." ],
	[ 131	, "PIPE, Private IP Encapsulation within IP." ],
	[ 132	, "SCTP, Stream Control Transmission Protocol." ],
	[ 133	, "Fibre Channel." ],
	[ 134	, "RSVP-E2E-IGNORE." ],
	[ 135	, "Mobility Header." ],
	[ 136	, "UDP-Lite, Lightweight User Datagram Protocol." ],
	[ 137	, "MPLS-in-IP." ],
	[ 253	, "Experimentation and testing." ],
	[ 254	, "Experimentation and testing." ],
	[ 255	, "reserved." ]
];
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# IP Header
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set IP_HeaderFields =
[
	#	FieldName			, Length,	Tooltip,	FieldDecodeTable    , tabular info
	["Version"				, 4		, "Specifies the format of the IP packet header." , IPVersion_FieldDecodeTable, [_TABULARCELL, CELL_IP_VERSION, "TEXT_CAPTION" ]],
	["IHL"					, 4		, "Internet Header Length" ],
	["TOS"					, 8		, "Type of Service" ],
	["Total length"			, 16	, "Contains the length of the datagram" ],
	["Identification"		, 16	],
	["Flags"				, 3		],
	["Fragment offset"		, 13	],
	["TTL"					, 8,	"Time to Live" ],
	["Protocol"				, 8,	"This field specifies the next encapsulated protocol.", IPProtocol_FieldDecodeTable, [_TABULARCELL, CELL_IP_PROTOCOL ]],
	["Header checksum"		, 16	],
	["Source IP address"	, 32	],
	["Destination IP address", 32	],
	["Options"				, 1		]
];


InternetProtocolPayloadWrapper()
{
    AddDecSeparator();
    FieldColor = IP_CaptionColor;
    AddCaptionCell("Internet Protocol", "IP_ET0800", "This data payload represents a Internet Protocol Payload.");

	ShowArrowFields(IP_HeaderFields);

    out.Decoded = in.DataLength;
}

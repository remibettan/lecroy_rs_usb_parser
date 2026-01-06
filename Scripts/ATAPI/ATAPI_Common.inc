
%include "CataLyst_Common.inc"

#----  Input
# in.Data       - Data_block to decode
# in.DataLength - Length of Data_block
#
#----  Output
# out.Decoded   - amount of data has been decoded
#
#------------------------  Common Globals -----------------------------------
set UsbDecodeType = "Endpoint";
set UsbEndpType   = "Bulk";
set UsbMaxXferSize = 0x7FFFFFFF;  #try largest possible positive value
set UsbMaxXferDecodeSize   = 36;  # Max bytes that we will be decoding
set UsbMaxPktSize          = 512;
set UsbScriptDecodeType    = 2; # Combined decoding for Cells and Text decoding
set UsbDecHdrType = 2; # This type references decoder byte containing the SCSI Opcode
set UsbDecHdrLen  = 1; # This 1 byte is passed in to this via the in context
set UsbDecExtraInfoBytePos = 15; # Position of Additional Info byte
set UsbXferCompleteClue = 4;     # this Xfer ends if Bulk In seen during decoding

# User can select the colors for the fields he chooses
#-------------------------------------------------------------------------------


const ATAPI_CaptionColor	= 0x008080FF;
const ATAPI_PayLoadColor	= 0x0028B928; 
const ATAPI_OpCodeColor		= 0x00189918; 

set PACKET_COMMAND		= 0xA0;		# OK: 0xA0
set opartionCode		= 0xFF;

set ATAPI_CBW_SIGNATURE		= 0x43425355;	# OK: 0x43425355
set ATAPI_CSW_SIGNATURE		= 0x53425355;	# OK: 0x53425355


const Tabular_Def_Table = Map( 
[   
    #-----------------------------------------------------------------------------------------------------
    #       id                      ,      colId                          , 		containerCellId
    #-----------------------------------------------------------------------------------------------------
    [ CELL_ATAPI_OPERATION_CODE    , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE   , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ CELL_ATAPI_STATUS            , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE   , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ]
] );


# Please see "View Settings" commnet in "CataLyst_Common.inc"
#					[collapsed, expanded]
const ATAPI_Operation_Code	= [1, 1];
const ATAPI_bCSWStatus		= [1, 1];
# const ATAPI_dCBWTag		= [1, 1];


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ATAPI CBW (Commnad Block Wrapper) Fields
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set ATAPI_CBW_FieldsTable =
[
	#	FieldName				, Length,	Tooltip,	FieldDecodeTable
	["dCBWSignature"			, 32],
	["dCBWTag"					, 32],
	["dCBWDataTransferLength"	, 32],
	["bmCBWFlags"				, 8 ],
	["bCBWLUN"					, 4 ],
	["Reserved"					, 4 ],
	["bCBWCBLength"				, 5 ],
	["Reserved"					, 3 ]
	# ["CBWCB"					, 128] <-- This is used as ATAPI fields.
];

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# bCSWStatus of CSW (Commnad Status Wrapper): Indicates the success or failure of the commnad.
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set CSWStatus_FieldDecodeTable =
[
	# Value   Decode
	[ 0x05	, "Reserved"				], # 0x05 ~ 0xFF are Reserved.
	[ 0x00	, "Command Passed (good)"	],
	[ 0x01	, "Command Fsiled"			],
	[ 0x02	, "Phase Error"				],
	[ 0x03	, "Reserved (Obsolote)"		],
	[ 0x04	, "Reserved (Obsolote)"		]
];
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ATAPI CSW (Commnad Status Wrapper) Fields
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set ATAPI_CSW_FieldsTable =
[
	#	FieldName				, Length,	Tooltip,	FieldDecodeTable,       tabular info
	["dCSWSignature"			, 32],
	["dCSWTag"					, 32],
	["dCSWDataResidue"			, 32],
	["bCSWStatus"				, 8		, "Indicates the success or failure of the commnad.", CSWStatus_FieldDecodeTable, [_TABULARCELL, CELL_ATAPI_STATUS]]
];



#~~~~~~~~~~~~~~~~~~~~~~
ProcessData_ATAPI(strSpec, strSpecDesc)
{
    InitType2Decoder();
    Prefix =  "ATAPI";

    length = in.DataLength;
    if (length < 4)
        return (0);

    # BitCurrentFieldOffset must be zero
	#AddPayLoadCell("BitCurrentFieldOffset", Format("0x%02X", BitCurrentFieldOffset), "For Debug", _ERROR);

    signature = GetDataLong(0);
	if (signature == ATAPI_CBW_SIGNATURE )
	{
		Show_ATAPI_CBW_Fields();
		return Show_ATAPI_Fields(strSpec, strSpecDesc);
	}
	else
	if (signature == ATAPI_CSW_SIGNATURE )
	{
        return Show_ATAPI_CSW_Fields();
	}

   return 0;
}


Show_ATAPI_CBW_Fields()
{
	return 0;
	FieldColor = ATAPI_CaptionColor;
	AddCaptionCell("  ATAPI  ", "CBW", "CBW: Commnad Block Wrapper");

	BitCurrentFieldOffset = 0;
	ShowArrowFields( ATAPI_CBW_FieldsTable );
}

Show_ATAPI_CSW_Fields()
{
	FieldColor = ATAPI_CaptionColor;
	AddDecSeparator();

	AddCaptionCell("  ATAPI  ", "CSW", "ATAPI CSW (Commnad Status Wrapper)");

	BitCurrentFieldOffset = 0;
	ShowArrowFields( ATAPI_CSW_FieldsTable );

	out.Decoded = in.DataLength;
}


Show_ATAPI_Fields(strSpec, strSpecDesc)
{

	#~~~~~~~~~~~~~~~~~~~~~~
	# CBWCB starts at byte 15
	BitCurrentFieldOffset = 8 * 15;
	#~~~~~~~~~~~~~~~~~~~~~~

	opartionCode = GetDataByte(BitCurrentFieldOffset / 8);

	# Find correspoding embedded SCSI table and show it
	atapiSpecTable = Resolve( "ATAPI_" + strSpec + "_CommandsTable" );
	commandsTable = Find(atapiSpecTable, opartionCode);

	fieldAttr = commandsTable[1][0];

	FieldColor = ATAPI_CaptionColor;
	AddDecSeparator();
	captionTooltip = "This data payload represents a ATAPI " + strSpec + " (" + strSpecDesc + ") Payload.";

	AddCaptionCell("  ATAPI  ", strSpec, captionTooltip);


	if(commandsTable[0] == 0xFF)
	{
		# AddPayLoadCell("  ATAPI  ", strSpec, captionTooltip, _MONOCOLOR);
		AddPayLoadCell("Operation Code", Format ("0x%02X: Unknown!", opartionCode ), "Operation Code", _ERROR, [_TABULARCELL, CELL_ATAPI_OPERATION_CODE]);
	}
	else
	{
		Show_SCSI_Fields(strSpec, commandsTable[1]);
	}

	out.Decoded = in.DataLength;
}


#~~~~~~~~~~~~~~~~~~~~~~
# Gets and shows field that placed in passed table
#~~~~~~~~~~~~~~~~~~~~~~
Show_SCSI_Fields(strCategory, SCSIFieldsTable)
{
	# ----------\/-----------\/-----------\/----------
	# Show first field of SCSIFieldsTable (It is 'Operation Code')
	#------------------------------------------------------------
	FieldColor = ATAPI_OpCodeColor;
	fieldAttr = SCSIFieldsTable[0];
	AddPayLoadCell(fieldAttr[0], Format("0x%02X: ", opartionCode) + fieldAttr[2], strCategory + ": " + fieldAttr[2], FieldColor, [_TABULARCELL, CELL_ATAPI_OPERATION_CODE]);
	# ----------/\-----------/\-----------/\----------


	# ----------\/-----------\/-----------\/----------
	# Copy all fileds except first field ('Operation Code') in new array,
	# then show new array using global ShowArrowFields(...) function.
	#------------------------------------------------------------
	for( nIndex = 1; nIndex < sizeof(SCSIFieldsTable); nIndex = nIndex + 1 )
	{
		SCSIFieldsTable_Except0[nIndex-1] = SCSIFieldsTable[nIndex];
	}

	ShowArrowFields( SCSIFieldsTable_Except0 );
	# ----------/\-----------/\-----------/\----------
}

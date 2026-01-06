set ModuleType     = "DataBlock Decoder";

const MassStorageColor = 0x80B0D0;
const Bulk_CBWCellColor     = 0x641A1A; 
const Bulk_CSWCellColor     = 0xA45A5A;

const CBI_ADSC_CellColor    = 0x641A1A;
const CBI_IntBlkColor       = 0xA45A5A;

const ErrorColor       = 0x0000FF;

const UFI_CmdColor     = 0x965478;

const MaxShowDataBlockSize = 512;

set SCSILevel = 0;

const Tabular_Def_Table = Map( 
[   
    #-----------------------------------------------------------------------------------------------------
    #       id              ,      colId                          , 		containerCellId
    #-----------------------------------------------------------------------------------------------------
    [ SCSI_CELL_CDB_SCSI    , TABULAR_SCRIPT_COLUMN_ID_TYPE       , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ SCSI_CELL_CDB         , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE    , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ SCSI_CELL_LBA         , TABULAR_SCRIPT_COLUMN_ID_NONE       , TABULAR_SCRIPT_CONTAINER_CELL_ID_MISC ],
    [ SCSI_CELL_LBA_SCSI    , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE    , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ SCSI_CELL_LENGTH      , TABULAR_SCRIPT_COLUMN_ID_NONE       , TABULAR_SCRIPT_CONTAINER_CELL_ID_MISC ],
    [ MS_CELL_STATUS        , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE    , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ MS_UASP_IDENTIFIER    , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE    , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ MS_UASP_TSK_MGM       , TABULAR_SCRIPT_COLUMN_ID_TYPE       , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ MS_UASP_RESPONSE_CODE , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE    , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ MS_UASP_STATUS        , TABULAR_SCRIPT_COLUMN_ID_NONE       , TABULAR_SCRIPT_CONTAINER_CELL_ID_MISC ],
    [ MS_UFI_SENSE          , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE    , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ MS_GET_MAX_LUN        , TABULAR_SCRIPT_COLUMN_ID_SUBTYPE    , TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE ],
    [ MS_MAX_LUN            , TABULAR_SCRIPT_COLUMN_ID_NONE       , TABULAR_SCRIPT_CONTAINER_CELL_ID_MISC ]
] );

####################################################################################
#                       USBTracer specific caption cell                            #
####################################################################################

AddSpecCaptionCell(caption, text, tooltip, FieldColor, addparam, addparam1, addparam2 )
{   
    AddCell(caption, text, tooltip, FieldColor, _USBBULK_HEADER, addparam, addparam1, addparam2 );        
    return 1;        
}

 

AddLBASpecCell( caption, str, tooltip, addparam, addparam1, addparam2 )
{
    if (SCSILevel == 1) # SCSI Level
    {    
        AddDecSeparator();
        AddCell( caption, str, tooltip, SCSI_Color, addparam1, [_TABULARCELL, SCSI_CELL_LBA_SCSI, "TEXT_CAPTION"] );
    }
    else
        AddBlockPLCell( caption, str, tooltip, addparam, addparam1, [_TABULARCELL, SCSI_CELL_LBA, "TEXT_CAPTION"] ); # the same as in ShowLBA() in SCSI_CDB.inc
        
    return 1;    
}

AddSCSICDBSpecCell( caption, str, tooltip, addparam, addparam1, addparam2 )
{
    if (SCSILevel == 1) # SCSI Level
        AddPLCellMonoStr( caption, str , tooltip, addparam, [_TABULARCELL, SCSI_CELL_CDB_SCSI] );
    else
        AddPLCellMonoStr( caption, str , tooltip, addparam, [_TABULARCELL, SCSI_CELL_CDB] );
        
    return 1;    
}

AddSpecDataBlockVS( len, view_setting )
{
	if( view_setting == null ) view_setting = VS;  
    ShowDataBlockReOrder( len, !ShowItem( view_setting ), view_setting[COLLAPSED] );
}

AddTag( tag_len )
{   
    save_endian = LittleEndian;
    LittleEndian = 0;

    tag = NextNBits_(tag_len);
    if (in.Expanded || in.PrepareFldsForDlg)
    {
        AddSimplePLCell("Tag", Format ("0x%04X", tag), "INITIATOR PORT TRANSFER TAG");
    }
    else
    {
        AddPayLoadCell("Tag", Format ("0x%04X", tag ), "INITIATOR PORT TRANSFER TAG");
    }
    
    LittleEndian = save_endian;
}

ProcessCDBs()
{
	CDBType = NextNBits_(8);

	select 
	{
		CDBType == 1 : { str = "For 6-Byte Command";
						tooltip = "For 6-Byte Command"; }
	        
		CDBType == 2 : { str = "For 10-Byte Command";
						tooltip = "For 10-Byte Command"; }
						
		CDBType == 3 : { str = "For 12-Byte Command";
						tooltip = "For 12-Byte Command"; }
						
		CDBType == 4 : { str = "For 16-Byte Command";
						tooltip = "For 16-Byte Command"; }
						
		CDBType == 5 : { str = "Long LBA 16-Byte Command";
						tooltip = "Long LBA 16-Byte Command"; }
						
		CDBType == 6 : { str = "Variable Length";
						tooltip = "Variable Length"; }
						
		CDBType == 7 : { str = "Variable Length For long LBA 32-Byte Command";
						tooltip = "Variable Length For long LBA 32-Byte Command"; }
						
		default :      { str = "Any CDB Type"; tooltip = "Any CDB Type";
                        error = _ERROR; }                            
	        
	};
    
	options = [ ["For 6-Byte Command", 1], ["For 10-Byte Command", 2], ["For 12-Byte Command", 3], ["For 16-Byte Command", 4], 
				["Long LBA 16-Byte Command", 5], ["Variable Length", 6], ["Variable Length For long LBA 32-Byte Command", 7] ];
				
	AddPayLoadCell( "CDB Type", str, tooltip, FieldColor, [_CELLINFO, 0, options] );
    
	if ( CDBType == 0x01 ) #6BYTE
		CDBType6Bytes();
	else if ( CDBType == 0x02 ) #10BYTE
		CDBType10Bytes();
	else if ( CDBType == 0x03 ) #12BYTE
		CDBType12Bytes();
	else if ( CDBType == 0x04 ) #16BYTE
		CDBType16Bytes();
	else if ( CDBType == 0x05 ) #Long LBA 16-Byte
		CDBTypeLongLBA16Bytes();
	else if ( CDBType == 0x06 ) #Variable Length
		CDBTypeVariableLength();
	else if ( CDBType == 0x07 ) #Variable Length For long LBA
		CDBTypeLongLBAVariableLength();
}

CDBType6Bytes()
{
	ShowOperCode();
    ShowLBA(24);    
	ShowTransferLen(8);
	ShowControlByte();	
}

CDBType10Bytes()
{
	ShowOperCode();
    PLReservedCheck( 3 );

    serv_action = NextNBits_(5);
    AddPayLoadCell( "SERVICE ACTION", Format ("0x%0X", serv_action), "SERVICE ACTION");
     
	ShowLBA(32);    
    PLReservedCheck( 8 );
	ShowTransferLen(16);
	ShowControlByte();	
}

CDBType12Bytes()
{
	ShowOperCode();
    PLReservedCheck( 3 );
    
    serv_action = NextNBits_(5);
    AddPayLoadCell( "SERVICE ACTION", Format ("0x%0X", serv_action), "SERVICE ACTION");
     
	ShowLBA(32);    
    ShowTransferLen(32);
    PLReservedCheck( 8 );
	ShowControlByte();	
}

CDBType16Bytes()
{
	ShowOperCode();
    PLReservedCheck( 3 );
    
    serv_action = NextNBits_(5);
    AddPayLoadCell( "SERVICE ACTION", Format ("0x%0X", serv_action), "SERVICE ACTION");
     
	ShowLBA(32); 
       
	add_cdb_data = NextNBits_(32);
    AddPayLoadCell( "Additional CDB Data", Format ("0x%08X", add_cdb_data), "Additional CDB Length");
    
    ShowTransferLen(32);
    PLReservedCheck( 8 );
	ShowControlByte();	
}

CDBTypeLongLBA16Bytes()
{
	ShowOperCode();
    PLReservedCheck( 3 );
    
    serv_action = NextNBits_(5);
    AddPayLoadCell( "SERVICE ACTION", Format ("0x%0X", serv_action), "SERVICE ACTION");
     
    ShowLBA(64); 
    ShowTransferLen(32);
    PLReservedCheck( 8 );
	ShowControlByte();	
}

CDBTypeVariableLength()
{
	ShowOperCode();
	ShowControlByte();	
    PLReservedCheck( 8 );
    PLReservedCheck( 8 );
    PLReservedCheck( 8 );
    PLReservedCheck( 8 );
    PLReservedCheck( 8 );	
    
    add_cdb_length = NextNBits_(8);
    AddPayLoadCell( "Additional CDB Length", Format ("0x%02X", add_cdb_length), "Additional CDB Length");
    
    serv_action = NextNBits_(16);
    AddPayLoadCell( "SERVICE ACTION", Format ("0x%04X", serv_action), "SERVICE ACTION");
    
    # based on STX software SERVICE ACTION Specific Field is in 22 bytes length
    str = Format("0x%08X", NextNBits(32));    
    str += Format(" %08X", NextNBits(32));
    str += Format(" %08X", NextNBits(32));
    str += Format(" %08X", NextNBits(32));
    str += Format(" %08X", NextNBits(32));
    str += Format(" %04X", NextNBits(16));
    IncFieldOffset( 22*8 );
    AddPayLoadCell( "SERVICE ACTION Specific Field", str, "SERVICE ACTION Specific Field");
}

CDBTypeLongLBAVariableLength()
{
	ShowOperCode();
    ShowControlByte();	
    PLReservedCheck( 24 );
    PLReservedCheck( 8 );
    PLReservedCheck( 8 );
    	
    
    add_cdb_length = NextNBits_(8);
    AddPayLoadCell( "Additional CDB Length", Format ("0x%02X", add_cdb_length), "Additional CDB Length");
    
    serv_action = NextNBits_(16);
    AddPayLoadCell( "SERVICE ACTION", Format ("0x%04X", serv_action), "SERVICE ACTION");
    
    PLReservedCheck( 3 );
    ShowDPO();
    ShowFUA();
    PLReservedCheck( 3 );
    PLReservedCheck( 8 );
	ShowLBA(64);    
	
	str = Format("0x%08X", NextNBits(32));    
    str += Format(" %08X", NextNBits(32));
    IncFieldOffset( 64 );
    AddPayLoadCell( "Additional CDB Data", str, "Additional CDB Length");
    
    ShowTransferLen(32);
}

ShowOperCode()
{
	op_code = NextNBits_(8);
    AddSimplePLCell("OperCode", Format ("0x%02X", op_code), "This field specifies format of SCSI command.\n\n");
}

Read_SCSILevel()
{
    param_second_byte = GetNBits(in.DecodeParams, 8, 8);
    
    SCSILevel = param_second_byte >> 7;
}
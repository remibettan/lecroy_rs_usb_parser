#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB.inc
#
#  SCSI CDB decoder functions
################################################################################


#---------------------  SCSI CDB Common Globals ---------------------------------
const CDB_EXTENDED = 0x7F;

set Opcode        = 0;
set ServiceAction = 0;


set CDB_Name    = "";
set CDB_Decoder = "";
set CDB_Color   =  0;
set CDB_Tooltip = "";

set CDB_CmndSetDesc = "";

#--------------------------------------------------------------------------------


ShowCDB( cdb_len)
{   
    AddDecSeparator();    
    Opcode = NextNBits_(8);
    
    SetupCDBDecoder( );
    
    #  set color for CDB cells   
    SetCellColor ( CDB_Color );
    
    
    # get view setting for CDB
    cdb_vs = Resolve( Prefix + "_CDB" );
    
    
    if( CDB_Tooltip && ( IsExpanded() || cdb_vs[COLLAPSED] ) ) 
    {
        if( !AddSCSICDBSpecCell( "SCSI CDB", CDB_Name , CDB_Tooltip, FieldColor ))  # Check if some project-specific AddSCSICDBSpecCell hook handled call
            AddPLCellMonoStr( "SCSI CDB", CDB_Name , CDB_Tooltip, FieldColor, [_TABULARCELL, SCSI_CELL_CDB] );
    }
    else
    {
        SetCellColor ( SCSI_Color );
        
        AddCell ("SCSI CDB", null, "SCSI Command Descriptor Block field.\n" +
        "This field specifies CDB to be interpreted\n" + 
        "by the addressed logical unit.", FieldColor, _MONOFIELD);
        
        RestoreCellColor();
        
        
    }
    
    # set view settings for block of cells
    VS = cdb_vs;
        
    
     # Special cell for OPERATION CODE in collapsed state 
     if( !IsExpanded() && !VS[COLLAPSED] )
     {
        tooltip =     "SCSI command     : " + CDB_Name + 
        Format("\nSCSI CDB opcode  : 0x%02X\n", Opcode );
        
        if( Opcode == CDB_EXTENDED )
            tooltip += Format("\nService Action  : 0x%04X", ServiceAction );
        else
            tooltip += "SCSI Command Set : " + CDB_CmndSetDesc;    
         
        tooltip += "\n\n"; 
         
        AddCell( CDB_Name, null, tooltip + CDB_Tooltip, CDB_Color , _MONOFIELD ); 
     }
    
    # special call for dialog view 
    AddStringToDlg("SCSI CDB", CDB_Name, tooltip + CDB_Tooltip );
    
    #-------------------------- Decoding CDB ----------------------------------
    cdb_real_len = ShowOperationCode();
    if( !cdb_real_len ) cdb_real_len = cdb_len;    
    
    if( Opcode == CDB_EXTENDED  )   ShowExtCDBCommonPart( cdb_real_len );    
    Call( CDB_Decoder, [cdb_real_len] );    
    if( Opcode != CDB_EXTENDED  )   ShowControlByte();    
        
    NextNBits_( (cdb_len - cdb_real_len) * 8  );
    #---------------------------------------------------------------------------
    
    AddDecSeparator();    
    
    # get current cell color back
    RestoreCellColor();
}


#####################################################################################
#                                Working functions                                  #
#####################################################################################

SetupCDBDecoder( )
{
    # if a command set to use first is specified in in.CommandSet
    # we use this value if not we use the default value specified
    # in CommandSet global variable.
    #
    if( in.CommandSet != null ) command_set = in.CommandSet;
    else                        command_set = CommandSet;
          
    
    if( Opcode == CDB_EXTENDED  )  #  Extended CDB
    {
        val = GetBitOffset();      # store offset
        NextNBits(7*8);
        
        ServiceAction = NextNBits(16);
        
        GetNBits(in.Data, val, 0); # restore offset   
        
        
        # set up Extended CDB definition table to look for service action...
        cdb_table = ExCDB_Tables[command_set];
        
        # look for opcode... 
        if( cdb_table )     
            cdb_dec = Find( cdb_table, ServiceAction );
        
        # if the extended cdb definition for the ServiceAction is not found let's search
        # the other Extended CDB definition tables for this ServiceAction.
        #        
                               
        if( cdb_dec == null )
        {            
            for ( table = ExCDB_Tables ; table && !cdb_dec; table = tail( table ) )
            {              
                item = head(table);
                
                if( item && ( item != cdb_table ) ) # skip null-s and the table we looked first                
                    cdb_dec = Find( item, ServiceAction );         
            } 
            
            if( cdb_dec == null ) # unable to find definition for the Opcode
            {             
                CDB_Name    = "EXTENDED"; 
                CDB_Decoder = "ShowExtCDBUnknown"; 
                CDB_Color   = EXTCDB_Common_Color;
                
                CDB_Tooltip = "EXTENDED SCSI command.\n" + 
                    "Operation code 7Fh means extended CDB\n" + 
                    "with a variable length. The functionality\n" + 
                    "is defined by SERVICE ACTION code.";
                
                return 0;
            }                           
        }        
            
        
        #cdb_dec = Find( EXT_CDB_DecTable, ServiceAction );
    }
    else
    {        
        # set up CDB definition table to look for opcode...
        cdb_table = CDB_Tables[command_set]; 
        
        # look for opcode...       
        cdb_dec = Find( cdb_table, Opcode );        
        
        
        # if the cdb definition for the opcode is not found let's search
        # the other CDB definition tables for this opcode.
        #        
                               
        if( cdb_dec == null )
        {            
            for ( table = CDB_Tables ; table && !cdb_dec; table = tail( table ) )
            {              
                item = head(table);
                
                if( item && ( item != cdb_table ) ) # skip null-s and the table we looked first                
                    cdb_dec = Find( item, Opcode );         
            } 
            
            if( cdb_dec == null ) # unable to find definition for the Opcode
            {
                CDB_Name    = Format("OPER CODE: %02Xh", Opcode); 
                CDB_Decoder = "ShowUnknownCDB"; 
                if (SCSILevel == 0)
                    CDB_Color   = SCSI_Color;   # XFer level
                else
                    CDB_Color   = RED;          # SCSI level
                CDB_Tooltip = "Invalid operation code";
                CDB_CmndSetDesc = "Unknown";
                
                return 0;     
            }
            
            cdb_table = item;                                    
        }
        
        # store SCSI command set brief description...
        CDB_CmndSetDesc = cdb_table[2];           
    }    
    
    
    CDB_Name    = cdb_dec[1];
    CDB_Decoder = cdb_dec[2];
    CDB_Color   = cdb_dec[3];
    CDB_Tooltip = cdb_dec[4];
}



FindCDBDefinition( opcode )
{
    # we look for CDB definitions for regular CDB not for extended ones...
    if( opcode == CDB_EXTENDED ) return null;
    
    
    # if a command set to use first is specified in in.CommandSet
    # we use this value if not we use the default value specified
    # in CommandSet global variable.
    #        
    if( in.CommandSet != null ) command_set = in.CommandSet;
    else                        command_set = CommandSet;
    
    
    # set up CDB definition table to look for opcode...
    cdb_table = CDB_Tables[command_set]; 
    
    # look for opcode...       
    cdb_dec = Find( cdb_table, opcode );
    
    # if the cdb definition for the opcode is not found let's search
    # the other CDB definition tables for this opcode.
    #        
                           
    if( cdb_dec == null )
    {            
        for ( table = CDB_Tables ; table && !cdb_dec; table = tail( table ) )
        {              
            item = head(table);
            
            if( item && ( item != cdb_table ) ) # skip null-s and the table we looked first                
                cdb_dec = Find( item, opcode );         
        }                                 
    }
    
    return cdb_dec;        
}




#################################################
#   Decoder for unknown or obsolete CDB         #
#################################################
ShowUnknownCDB( cdb_len )
{   
	if( !AddSpecDataBlockVS( cdb_len - 2, VS ))  # Check if some project-specific ShowSpecDataBlockVS hook handled call        
		ShowDataBlockVS( cdb_len - 2, VS );
}



ShowOperationCode( )
{      
    grp_code  = Opcode >> 5 ;   # last 3 bits
    cmd_code  = Opcode & 0x1F;  # first  5 bits
    
    str = " byte CDB)";    
    cdb_real_len = 0;
    
    error = null;    
    select{
        grp_code == 0b000 : { str = "000b (6"  + str ; cdb_real_len = 6 ; }
        grp_code == 0b001 : { str = "001b (10" + str ; cdb_real_len = 10; }
        grp_code == 0b010 : { str = "010b (10" + str ; cdb_real_len = 10; }     
        grp_code == 0b100 : { str = "100b (16" + str ; cdb_real_len = 16; }
        grp_code == 0b101 : { str = "101b (12" + str ; cdb_real_len = 12; }
        grp_code == 0b110 : { str = "110b (Vendor)"  ; }
        grp_code == 0b111 : { str = "111b (Vendor)"  ; }
        
        ( grp_code == 0b011 ) && ( cmd_code == 0b11111 )
                     : { str = "011b (Extended)" ; cdb_real_len = 32;} # all extended commands (0x7F) are 32 bytes except 
																	   # XDWriteExtended64
        
        default      : { str = "011b (Reserved)" ; error = _ERROR; }
    };
    
    str =  Format("GROUP CODE   : %s.\n",   str      );
    str += Format("COMMAND CODE : 0x%02X.", cmd_code );
    
	
	if ( !AddSpecOpCodeCell("OperCode", Format("0x%02X", Opcode ),
		"OPERATION CODE field.\n" + 
		"This field specifies format of SCSI command.\n\n" + str, error, [_CELLINFO, 1]) )
	{
		AddBlockPLCell("OperCode", CDB_Name + "( " + Format("0x%02X", Opcode ) + " )",
			"OPERATION CODE field.\n" + 
			"This field specifies format of SCSI command.\n\n" + str, error, [_CELLINFO, 1] );
	}
	
    return cdb_real_len;
}


ShowControlByte()
{
	control_byte = PeekNBits_(8);
	
    tooltip  = "The CONTROL byte field.\n\n";
    tooltip += Format("Vendor   : 0x%01X.\n", NextNBits(2));
    tooltip += Format("Reserved : 0x%01X.\n", NextNBits(3));
    
    tooltip += "NACA     : ";
    if ( NextNBits(1) ) tooltip += "set";
    else                tooltip += "Not set"; 
    
    tooltip += ".\n";
    
    tooltip += "Obsolete : ";
    if ( NextNBits(1) ) tooltip += "set";
    else                tooltip += "Not set";
    
    tooltip += ".\n";
    
    tooltip += "LINK     : ";
    if ( NextNBits(1) ) tooltip += "set.";
    else                tooltip += "Not set.";
    
	if (!AddSpecControlByteCell("CONTROL", control_byte, tooltip) )
	{
		str = Format("0x%02X", control_byte );
		AddBlockPLCell("CONTROL", str, tooltip );
	}
}



ShowParamListLen( len, check_value )
{
    if( !len ) len = 32;
    
    val = NextNBits_(len);
    
    error   = null;
    tooltip = "";
    if( (check_value != null) && ( check_value != val ) )
    {
        error = _ERROR;
        tooltip = Format("The PARAMETER LIST LENGTH(%u) is not equal to\n" , val) + 
                  Format("the expected value(%d)." , check_value);
    }
    

     AddBlockPLCell("ParamList Len", Format("%u", val ),
         "The PARAMETER LIST LENGTH field specifies\n" + 
         "the length in bytes of the parameter data that shall\n" + 
         "be contained in the Data-Out Buffer." + AddWarningTooltip(tooltip),
         error);
}


ShowAllocLen( len )
{
    if( !len ) len = 32;

    AddBlockPLCell("AllocLen", Format("%u", NextNBits_(len)), 
    "The ALLOCATION LENGTH field in the CDB indicates\n" + 
    "how much space has been allocated for the returned\n" + 
    "parameter list.");
}



ShowTransferLen( len, transfer_entity )
{
    if( !len ) len = 32;
    if( !transfer_entity ) transfer_entity = "bytes";
    
	if ( !AddSpecTransferLenCell(len, transfer_entity) )
	{
		AddBlockPLCell("Transfer Len", Format("%u", NextNBits_(len)), 
		"The TRANSFER LENGTH field specifies the length\n" + 
		"in " + transfer_entity + " of data that shall be transferred from\n" + 
		"the Data-Out Buffer.");
	}
}


ShowLBA( lba_len, addparam, add_tooltip )
{
    
    len = lba_len;
    if( !lba_len || lba_len > 32 ) len = 32;    
    
    
    str = Format("0x%08X", NextNBits(len));    
    if( lba_len > 32 ) str += Format(" %08X", NextNBits(lba_len - len));
    
    if( !lba_len ) lba_len = 32;
    IncFieldOffset( lba_len );
    
    caption = "Logical Block Addr";
    
    tooltip = "The LOGICAL BLOCK ADDRESS field specifies\n" + 
              "the logical block where the operation shall\n" + 
               "begin." + add_tooltip;    

    if( !AddLBASpecCell( caption, str, tooltip, FieldColor, addparam ))  # Check if some project-specific AddLBASpecCell hook handled call        
        AddBlockPLCell( caption, str, tooltip, FieldColor, addparam , [_TABULARCELL, SCSI_CELL_LBA, "TEXT_CAPTION"]);    
}





ShowRELADR()
{
	options = [ ["set", 1], ["Not set", 0] ];

    AddBlockPLCell("RELADR", GetBitStr(), 
    "A relative address (RELADR) bit of zero indicates that the\n" + 
    "LOGICAL BLOCK ADDRESS field specifies the first logical\n" + 
    "block of the range of logical blocks for this command.\n" + 
    "A RELADR bit of one indicates that the LOGICAL BLOCK ADDRESS\n" + 
    "field is a two's complement displacement.", FieldColor, [_CELLINFO, 0, options ]);
}


ShowPortControl()
{
    #-------------------------------- PORT CONTROL -----------------------------
    val = NextNBits_(2);      
    
    select{
        val == 0b00 : { text = "Same As Rcvd"; str = "00b"; tooltip = "The target transfers the data using the\n" + 
                                                            "same port that received the command" ; }

        val == 0b01 : { text = "Dffr From Rcvd"; str = "01b"; tooltip = "The target transfers the data using a\n" + 
                                                            "different port than the one that received\n" + 
                                                            "the command"; }
                                                            

        val == 0b10 : { text = "One TRGT choice"; str = "10b"; tooltip = "The target transfers the data using one\n" + 
                                                             "port of the target“s choice" ; }
        
        val == 0b11 : { text = "One/More TRGT choice"; str = "11b"; tooltip = "The target transfers the data using one\n" + 
                                                             "or more ports of the target“s choice"; }
    };
    
    tooltip = "PORT CONTROL field.\n\n" + 
    Format("Value   : %s.\n", str) + Format("Meaning : %s.", tooltip);
    
    options = [ ["Same As Rcvd", 0], ["Dffr From Rcvd", 1], ["One TRGT choice", 2], ["One/More TRGT choice", 3] ];
    
    AddBlockPLCell("PORT CONTROL", text, tooltip, FieldColor, [_CELLINFO, 0, options ]);
    #---------------------------------------------------------------------------------
}


# -----------------------------------------------------------------------------------

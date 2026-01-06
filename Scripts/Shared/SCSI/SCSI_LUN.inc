#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_LUN.inc
#
#  SCSI LUN decoder functions
################################################################################



ShowLUN()
{    
    #  set SCSI color for cells    
    SetCellColor ( SCSI_Color );
        
    AddDecSeparator();
    
    #------------------------------ LUN ----------------------------------------
    val = GetBitOffset();        # save offset    
    
    str = "";
    for( i = 0; i < 4; i++ )
        str += Format(" %04X", NextNBits(16));
        
    GetNBits( in.Data, val, 0 ); # restore offset    
    #---------------------------------------------------------------------------
    
    tooltip = "LUN (hex) : " + str + ".\n\n" + 
    "The LOGICAL UNIT NUMBER field specifies the address \n" + 
    "of the logical unit component of the nexus for the\n" + 
    "task request.";
    
      
    # Special cell for LUN in collapsed state
    if( !IsExpanded() )
    {
        AddCell( "SCSI LUN", str, tooltip, SCSI_Color, [_LOWERCOLOR, SCSI_LUN_Color] );   
    }
        
    
    VS = Resolve( Prefix + "_LUN" );
    
    
    AddBlockPLCellMonoStr("SCSI LUN", "", tooltip, _MONOFIELD );
    
    
    break = 0;
    for( i = 1; (i <= 4) && !break ; i++ )
    {  
        i_str = Format("%d", i);
        AddBlockPLCellMonoCap("Level", i_str, "Logical Unit Number Level " + i_str );
          
        adr_mthd = NextNBits_(2);
        
        tooltip = "ADDRESS METHOD field.\nCode : ";        
        
        select {
            adr_mthd == 0b00 : { str = "Peripheral"; tooltip += "00b - Peripheral device addressing method"; }
            adr_mthd == 0b10 : { str = "LUN"       ; tooltip += "10b - Logical unit addressing method"; }            
            
            adr_mthd == 0b01 : { str = "Flat"      ; tooltip += "01b - Flat space addressing method"; }
                        
            adr_mthd == 0b11 :
            { 
                str = "Extended"  ; tooltip += "11b - Extended logical unit addressing method";                
                #if( PeekNBits(2) != 0b00 )
                 break = 1; # extended LUN more than two bytes long
            }
        };
                
        
        AddBlockPLCell("ADDR_MTHD", str, tooltip );        
        ShowMethodSpecific( adr_mthd, i );
        
        # look at the next level structure -
        # if it is empty stop processing.
        if( (i != 4) &&  !break && !PeekNBits(16) )
        {
            break = 1;
            NextNBits_( 64 - i*16 );
        }
    }
    
    AddDecSeparator();
    
    # get current cell color back
    RestoreCellColor();
}



ShowMethodSpecific( adr_mthd, level )
{
    select {
        adr_mthd == 0b10 :
        {
            AddBlockPLCell("TARGET", Format("0x%02X", NextNBits_(6)),
            "The target information in the TARGET field may be a target\n" + 
            "identifier or it may be a mapped representation of a target\n" + 
            "identifier, when the range of possible target identifiers is too\n" + 
            "large to fit in the TARGET field." );
            
             AddBlockPLCell("BUS NUMBER", Format("%d", NextNBits_(3)), "BUS NUMBER field." );
             AddBlockPLCell("LUN"       , Format("0x%02X", NextNBits_(5)), "LUN field value."  );
        }
        
        adr_mthd == 0b00 :
        {
             AddBlockPLCell("BUS ID", Format("%d", NextNBits_(6)),
            "The BUS IDENTIFIER field identifies the bus or path\n" + 
            "that the SCSI device shall use to relay the received command.\n" + 
            "Bus identifier zero shall indicate that the command is\n" + 
            "to be relayed to a logical unit within the SCSI device at\nthe current level." );            
             
             AddBlockPLCell("TARGET/LUN", Format("0x%02X", NextNBits_(8)),
             "The TARGET/LUN field indicates the address of\n" + 
             "the peripheral device to which the SCSI device\n" + 
             "shall relay the received command." );
        }
        
        
        adr_mthd == 0b01 :
             AddBlockPLCell("LUN" , Format("0x%04X", NextNBits_(14)), "LUN field value."  );        
        
        
        
        adr_mthd == 0b11 :
        {
            val   = NextNBits_(2);            
            
            select  {
                val == 0b00 : { str = "1 byte" ; ext_len = 1;}
                val == 0b01 : { str = "3 bytes"; ext_len = 3;}
                val == 0b10 : { str = "5 bytes"; ext_len = 5;}
                val == 0b11 : { str = "7 bytes"; ext_len = 7;}
            };
            
            
            byte_rest = (4 - level) * 2 + 1 - ext_len;
            
            error = null;
            tooltip = "";
            
            
            # check if the length of EXTENDED ADDRESS METHOD SPECIFIC field
            # fits remaining space of LUN structure. 
            #
            if( byte_rest < 0 )
            {
                error = _ERROR;
                tooltip = Format("The LENGTH value(%d bytes)", ext_len) + " is too large to fit\nremaining space in LUN structure.";
                                
                byte_rest = 0;
                ext_len = (4 - level) * 2 + 1;                
            }
        
            AddBlockPLCell("LENGTH", str,
            Format("The LENGTH field -(0x%01X)", val) + " specifies the length of\n" + 
            "the EXTENDED ADDRESS METHOD SPECIFIC field." + AddWarningTooltip(tooltip), error );
            
            #------------------------- EXTENDED ADDRESS METHOD SPECIFIC --------------------------
            val = NextNBits_(4);
            
            tooltip =  "EXTENDED ADDRESS METHOD field.\n\n" + 
            "This field combined with the LENGTH field specifies\n" +
            "the type and size of extended logical unit address\n" +
            "found in the EXTENDED ADDRESS METHOD SPECIFIC field.";
                        
            if( (ext_len == 1) && (val == 0x1) ) # Well-known Logical Unit
                str = "Well-known LU(1h)";
            else
                str = Format("0x%01X", val);
            
            AddBlockPLCell("EXT_ADDR_MTHD", str, tooltip );
            #-------------------------------------------------------------------------------------
             
             
            #------------------------- EXTENDED ADDRESS METHOD SPECIFIC --------------------------
            caption = "EXT_ADDR_MTHD_SPEC";
            tooltip = "EXTENDED ADDRESS METHOD SPECIFIC field.";
            
            select {
                ext_len == 1 : 
                {
                    str = Format("0x%02X", NextNBits(8)) ;
                    if( val == 0x1 ) {caption = "W-LUN"; tooltip = "W-LUN field.";}
                }
                
                
                ext_len == 3 : { str = Format("0x%06X", NextNBits(24)); }
                
                ext_len == 5 : 
                {
                    str =  Format("0x%08X", NextNBits(32));
                    str += Format("%02X"  , NextNBits( 8));              
                }
                
                ext_len == 7 : 
                { 
                    str =  Format("0x%08X", NextNBits(32));
                    str += Format("%06X"  , NextNBits(24));
                }
            };
                        
                       
            IncFieldOffset( ext_len * 8  );             
            AddBlockPLCell( caption, str, tooltip );
            
            
            NextNBits_( byte_rest * 8 ); # shift to the end of LUN structure
            #-------------------------------------------------------------------------------------            
        }        
        
     };
}



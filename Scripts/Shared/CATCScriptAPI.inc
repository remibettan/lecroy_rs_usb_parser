#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  CATCScriptAPI.inc
#
#  CATC Display Decoder Tools
#


##############################################################
#                    RGB function                            #
##############################################################



#------------------- Constants ----------------------------
const COLLAPSED = 0;
const EXPANDED  = 1;

const NOT_USE_COLON_AS_DVDR = 0xAA;


##############################################################
# The next constant is supposed to be used in cell tooltips  #
# as delimiter of "normal" part of tooltip and the part      #
# containing a message about protocol specification errors   #
# in the subfield.                                           #
#                                                            #
# It is used like                                            #
# ...                                                        #
# tooltip = normal_tooltip + WARNING_SIGN + error_tooltip;   #
# Add...Cell( caption , value, tooltip, _ERROR );            #
# ...                                                        #
##############################################################

const WARNING_SIGN = "\n\n!!! WARNING !!!\n";
#----------------------------------------------------------



#------------------- Colors -------------------------------
const RED          = RGB(255,   0,   0);
const WarningColor = RGB(255, 255,   0);  # yellow
const ERROR_COLOR  = RGB(255,   0,   0);  # red
# ---------------------------------------------------------


#---------------- Bit order constants ---------------------
const BIG_ENDIAN    = 0;
const LITTLE_ENDIAN = 1;
# ---------------------------------------------------------



#------------------- Decoder globals  ---------------------

# setting globals
set NotShowRsrvWrngCells = 0;
set CheckBadDataLength   = 0;
set EndCellBlockInNewCaptionCell = 1;
set UseCaptionAsCellBlockName    = 0;


# This variable contains the length of data payload passed to script in bits.
set PayloadLenBits = 0;

# current operational globals (used in Add..Cell functions)

set VS = [];            # View setting list for the current field
set Prefix = "";        # current "prefix". Prefix uniquely defines the some decoding part of the whole decoding
set FieldColor = 0;     # represents the current field color
set CellBlockName = ""; # The current name for the group of cell in the trace that can be expanded or collapsed.



# working globals storing some intermediate information

set val = 0;
set bit = 0;
set str = "";
set tooltip = "";

set error       = null;
set err_tooltip = "";


set Global_BitField_offset = 0;
set BitCurrentFieldOffset  = 0;
set BitCurrentFieldLength  = 0;


set ViewAll = 0;
set HideAll = 0;

set Cur_color  = 0;

set B_Prefix = "";

set B_ViewAll = 0;
set B_HideAll = 0;

set B_GBitFld_offset   = 0;
set B_BitCurFldOffset  = 0;

set B_offset = 0;

# globals for non-primitive helper functions

set WrapStringWidth = 80;

#----------------------------------------------------------



#########################################################################
#                           Working functions                           #
#########################################################################


#################################################################
# Set current color for cells as defined in color               #
#################################################################
SetCellColor( color )
{
   Cur_color  = FieldColor;
   FieldColor = color;
}


#################################################################
# Restore current color for cells from Cur_color                #
#################################################################
RestoreCellColor()
{
    FieldColor = Cur_color;
}
############################################################




#################################################################
#    Initialization of SRP common global variables              #
#################################################################

CommonDecoderInit()
{
  out.Decoded = 0;

  FieldColor = RGB(125, 125, 125); # grey -

  Global_BitField_offset = 0;

  BitCurrentFieldOffset  = 0;
  BitCurrentFieldLength  = 0;

  GetNBits( in.Data, 0, 0 );

  # Set this global variable to 1 if you don't care that
  # reserved fields are not zeros. Set to 0 to switch on
  # showing warning cells for non-zero reserved fields.
  NotShowRsrvWrngCells = 0;

  CheckBadDataLength = 1; # Turn-on checking if we don't step out of payload
  PayloadLenBits = in.DataLength * 8;
}





#################################################################
#  This function performes necessary initialization routine     #
#  for field to be decoded. it must be called before starting   #
#  field decoding.                                              #
#################################################################

CurrentFldInit( )
{
     BitCurrentFieldOffset = 0;
     BitCurrentFieldLength = 0;

     PrepareFieldForDlgExt("FIELD_INIT", 0,
        Global_BitField_offset, "", "", null, 1 );
}




#################################################################
#  This function performes necessary initialization routine     #
#  for "unit" decoder.                                          #
#                                                               #
#  "Unit" means here a bunch of subfields having common logical #
#  sense. Unit decoder is a function which decodes a bunch of   #
#  subfields considered as a "unit".                            #
#                                                               #
#  Unit has its own prefix, view settings and may have its own  #
#  color.                                                       #
#                                                               #
#  This function must be called before starting unit decoding.  #
#################################################################

UnitDecoderInit( prefix )
{
    Prefix =  prefix;

    # setting global view settings to local ones
    ViewAll = Resolve( Prefix + "_ViewAll" );
    HideAll = Resolve( Prefix + "_HideAll" );

    CurrentFldInit();

    # Call decoder-specific hook here
    # define it somewhere in your decoder if you need to add
    # some specific initialization.
    UnitDecoderInitHook();
}



#################################################################
#   This function sets values for field (or subfield) length    #
#   and offset from beginning of field structure                #
#################################################################

SetFieldOffsetLen( offset, len )
{
    BitCurrentFieldOffset = offset;
    BitCurrentFieldLength = len;
}


################################################################################
#  Increments field offset by and set field length variable equal to len.      #
#  Useful when being not able to obtain a field value using only one           #
#  GetNBits_ or NextNBits_  command.                                           #
################################################################################

IncFieldOffset( len )
{
    if( in.PrepareFldsForDlg )
    {
	BitCurrentFieldOffset += len;
        BitCurrentFieldLength  = len;
    }

    CheckBadDataLength();
}


#####################################################################
# The next two function are very useful when we should  show        #
# one attribute inside of other.                                    #
#                                                                   #
# We could do that writing code like this:                          #
#   ...                                                             #
#   ...  # pre-decoding of container attribute                      #
#   SaveFieldSettings();                                            #
#   Global_BitField_offset = MAD_HEADER_LEN_BITS +                  #
#                               amount_of_bits_before_attribute;    #
#                                                                   #
#   ShowSomeAttribute();                                            #
#   RestoreFieldSettings( );                                        #
#   ...  # post-decoding of container attribute                     #
#   ...                                                             #
#####################################################################

SaveFieldSettings()
{
    B_Prefix  = Prefix;

    B_ViewAll = ViewAll;
    B_HideAll = HideAll;

    B_GBitFld_offset   = Global_BitField_offset;
    B_BitCurFldOffset  = BitCurrentFieldOffset;

    # set global field offset for contained attribute
    Global_BitField_offset = Global_BitField_offset + BitCurrentFieldOffset;
}


RestoreFieldSettings( )
{
    Prefix = B_Prefix;

    ViewAll = B_ViewAll;
    HideAll = B_HideAll;

    Global_BitField_offset  = B_GBitFld_offset;

    PrepareFieldForDlgExt("FIELD_INIT", 0, Global_BitField_offset );

    BitCurrentFieldOffset   = B_BitCurFldOffset + BitCurrentFieldOffset;
}

#####################################################################




#####################################################################
#               Saving offset of current data source                #
#####################################################################

SaveOffset()
{
   B_offset = GetBitOffset();
}


#####################################################################
#               Restoring offset for data source                    #
# (in.Data is used by default if some other specific source has not #
# been specified)                                                   #
#####################################################################

RestoreOffset( source )
{
    if( source == null ) source = in.Data;
    GetNBits( source, B_offset, 0 );
}




#============================================================================================
#=                                  'Get field' functions.                                  =
#=                                                                                          =
#= This group of functions allows to get string representations of fields of different      =
#= lengths.                                                                                 =
#============================================================================================


GetGUID()
{
        IncFieldOffset(64);

        guid  = Format("0x%04X",  NextNBits(16));
        guid += Format("-%04X", NextNBits(16));
        guid += Format("-%04X", NextNBits(16));
        guid += Format("-%04X", NextNBits(16));

        return guid;
}


GetGIID()
{
        IncFieldOffset(128);

        giid =  Format("0x%08X", NextNBits(32));
	giid += Format("-%04X" , NextNBits(16));
	giid += Format("-%04X" , NextNBits(16));
	giid += Format("-%04X" , NextNBits(16));
	giid += Format("-%08X" , NextNBits(32));
	giid += Format("%04X"  , NextNBits(16));

	return giid;
}




# get string representations of fields of any length ( given in bits from 1 to 32)
# postfix "D" means decimal format, "H" - hexadecimal.
#
GetFldD( len ) { return Format("%u"  , NextNBits_(len) ); }
GetFldH( len ) { return Format("0x%X", NextNBits_(len) ); }


# get string representations of fields of various lengths
# postfix "D" means decimal format, "H" - hexadecimal.
#

GetFld4D()  {  return Format("%u"    , NextNBits_(4)  ); }
GetFld4H()  {  return Format("0x%01X", NextNBits_(4)  ); }

GetFld8D()  {  return Format("%u"    , NextNBits_(8)  ); }
GetFld8H()  {  return Format("0x%02X", NextNBits_(8)  ); }

GetFld12D() {  return Format("%u"    , NextNBits_(12) ); }
GetFld12H() {  return Format("0x%03X", NextNBits_(12) ); }

GetFld16D() {  return Format("%u"    , NextNBits_(16) ); }
GetFld16H() {  return Format("0x%04X", NextNBits_(16) ); }

GetFld24D() {  return Format("%u"    , NextNBits_(24) ); }
GetFld24H() {  return Format("0x%06X", NextNBits_(24) ); }

GetFld32D() {  return Format("%u"    , NextNBits_(32) ); }
GetFld32H() {  return Format("0x%08X", NextNBits_(32) ); }


GetFld64()
{
    IncFieldOffset(64);

    fld  = Format("0x%08X ", NextNBits(32));
    fld += Format("%08X "  , NextNBits(32));
    return fld;
}




############################################################
#       Get string field of len_in_bytes bytes long        #
############################################################

GetStrFld( len_in_bytes )
{
    IncFieldOffset( len_in_bytes * 8 );

    tmp = "";
    for(i = 0; i < len_in_bytes; i++)
        tmp += Format("%c", NextNBits(8));

    return tmp;
}



GetBitStr( bit_fld )
{
    if( bit_fld == null ) bit_fld = NextNBits_(1);

    if( bit_fld ) return "set";
    else      return "Not set";
}


###############################################################
# This function returns the string with binary representation #
# of the 'value' having the length 'len' bits in 'msb' order. #
###############################################################

GetBinaryString( value, len, msb )
{
    str = "b";

    if( msb == 0 )
    {
        for( i = 0; i < len; i++ )
        {
            if( value & (0x1 << i) ) str += "1";
            else                     str += "0";
        }
    }
    else
    {
        for( i = len; i > 0; i-- )
        {
            if( value & (0x1 << i) ) str += "1";
            else                     str += "0";
        }
    }

    return str;
}


###########################################################
# finds a string in the table by a key value -
# if the key is not found the first string is returned
###########################################################
Find(table, table_key)
{
    if( IsMap( table ) )
    {
        item = table[table_key];

        if( item == null ) item = table[0xFFFFFFFF];  # Legacy script support - when first list item was returned if key isn't found.
        if( item == null ) item = table[0xFFFF];      # Legacy script support - when first list item was returned if key isn't found.
        if( item == null ) item = table[0xFF];        # Legacy script support - when first list item was returned if key isn't found.

        return item;
    }


    if( IsList( table ) )
    {
        not_found = table[0];

        for( item = first( table ); more( table ); item = next( table ) )
        {
           if( head( item ) == table_key ) return item;
        }

        return not_found;
    }

    if( IsArray( table ) )
    {
        not_found = table[0];

        for( i = 0; i < sizeof( table ); i++ )
        {
            item = table[i];
            if( head( item ) == table_key ) return item;
        }

        return not_found;
    }

    return not_found;
}




###########################################################
#  This function is intended for presentation DataBlock   #
#  len - length of DataBlock,                             #
#                                                         #
#  no_cell - define that no Cells will be drawn.          #
#            (useful for View Settings)                   #
#                                                         #
#  show_in_collapsed - define that datablock is shown     #
#                      in collapsed state                 #
###########################################################

ShowDataBlock( len, no_cells, show_in_collapsed )
{
   # no need to do anything if len = 0 or len < 0
   if( !len )    return 0;
   if( len < 0 ) return 0;

  if( in.PrepareFldsForDlg )
  {
        lenbits = len * 8;
        BitCurrentFieldOffset = BitCurrentFieldOffset + lenbits;
        BitCurrentFieldLength = lenbits;


        str = Format("%d bytes", len);
        PrepareFieldForDlg( "DATA_BLOCK", str,
        "Data Block containing " + str, !no_cells, show_in_collapsed );

        NextNBits( lenbits );
  }
  else
  {
        if( !no_cells )
        {
              select
              {
                    len == 1 :  AddDataCell( [NextNBits(8)], _BYTES );
                    len == 2 :  AddDataCell( [NextNBits(8), NextNBits(8)], _BYTES );
                    len == 3 :  AddDataCell( [NextNBits(8), NextNBits(8), NextNBits(8)], _BYTES );
                    len == 4 :  AddDataCell( [NextNBits(8), NextNBits(8), NextNBits(8), NextNBits(8)], _BYTES );
                    default	 :  AddDataCell( NextNBits(8*len), _BYTES );
              };
        }
        else
            NextNBits(8*len);
  }

  out.Decoded += len;
}


###########################################################
# Show DataBlock using information about showing in       #
# collapsed or in expanded states contained in            #
# view_setting.                                           ##
###########################################################

ShowDataBlockVS( len, view_setting )
{
     if( view_setting == null ) view_setting = VS;
     ShowDataBlock( len, !ShowItem( view_setting ), view_setting[COLLAPSED] );
}



# ------------------------ Adds separator Cell ---------------------------
AddDecSeparator()
{
    if( !in.PrepareFldsForDlg )
	    AddSeparator();
	else
	    PrepareZeroFieldForDlg( "SEPARATOR" );
}




#===========================================================================================
#=                         Warning and error handling functions                            =
#===========================================================================================


Warning(text, tooltip)
{
    if( !in.PrepareFldsForDlg )
    {
       AddCell("!!! WARNING !!!", text, tooltip, WarningColor, _WARNING );
    }
    else
        PrepareZeroFieldForDlg( "WARNING", text, tooltip );

}


#########################################################################
#   This function prepares warning for Dialog-view not showing          #
#   warning on the screen                                               #
#########################################################################
WarningForDlg(text, tooltip)
{
    if( in.PrepareFldsForDlg )  PrepareZeroFieldForDlg( "WARNING", text, tooltip );
}



#########################################################################
#  This function allows to add a special warning or error description   #
#  part to tooltip string.                                              #
#  For instance, let's have a piece of code:                            #
#                                                                       #
#  ...                                                                  #
#  LID_number = 2345;                                                   #
#  tooltip = "LID block number.";                                       #
#                                                                       #
#  error = null;                                                        #
#  error_tooltip = "";                                                  #
#  if( LID_number > UPPER_BOUND ) {  error = _ERROR;                    #
#    error_tooltip = "LID number is out of range"; }                    #
#                                                                       #
#  AddSimplePLCell("LID", Format("%d", LID_number ),                    #
#  tooltip + GetWarningTooltip(error_tooltip), error);                  #
#  ...                                                                  #
#                                                                       #
#  On the tooltip to this cell in case of error you will see            #
#  -----------------------------------------                            #
#  | LID block number.                     |                            #
#  |                                       |                            #
#  | !!! WARNING !!!                       |                            #
#  | LID number is out of range            |                            #
#  -----------------------------------------                            #
#  and the warning part will be shown dark red in dialog view.          #
#                                                                       #
#  The other opportunity to add warning part properly is to use         #
#  WARNING_SIGN - constant like:                                        #
#  ...                                                                  #
#  if( error_tooltip != "" )                                            #
#        error_tooltip = WARNING_SIGN + error_tooltip;                  #
#########################################################################

AddWarningTooltip( error_tooltip )
{
    if( error_tooltip != "" ) error_tooltip = WARNING_SIGN + error_tooltip;
    return error_tooltip;
}


###############################################################################
#   This function clears global variables containing information about        #
#   last error happened during decodeing.                                     #
###############################################################################

ClearError()
{
    error       = null;
    err_tooltip = "";
}



###############################################################################
#   This function sets global variables containing information about          #
#   last error.                                                               #
###############################################################################

SetError( error_tip )
{
    error = _ERROR;
    err_tooltip = error_tip;
}




###############################################################################
#   This function returns the last decoding error set and clear global        #
#   variables containing information about this error.                        #
###############################################################################

GetError()
{
    err = error;  ClearError();
    return err;
}



##########################################################################
#  This function allows to add a special warning or error description    #
#  part to tooltip string.                                               #
#                                                                        #
#  The difference between this function and AddWarningTooltip() is that  #
#  this function works with global variables whereas AddWarningTooltip() #
#  with local ones.                                                      #
##########################################################################

AddErrorTooltip()
{
    if( err_tooltip != "" ) error_tooltip = WARNING_SIGN + err_tooltip;
    return error_tooltip;
}


SetReservedError()
{
    str = "Reserved";
    error = _ERROR;
    err_tooltip = "This value is reserved and shouldn't be used.";
}





#===================================================================================================



##########################################################################
#       This function makes check of next bits_reserved bits             #
#       that are reserved and should be set to zero                      #
##########################################################################

ReservedCheck( bits_reserved )
{
    res_val = NextNBits_(bits_reserved); # Reserved, should be zero


    # We don't show reserved check warnings in collapsed state
    # when no preparing data for Dialog-view.
    if( !IsExpanded()  && !in.PrepareFldsForDlg ) return 0;


    if( res_val )
    {
        str = "";
        if( in.PrepareFldsForDlg ) str = Format(" at offset : %d bit(s)", BitCurrentFieldOffset - bits_reserved );

        if( !NotShowRsrvWrngCells )
            Warning( Format("0x%X - not 0!", res_val),
            Format("These %d bits" , bits_reserved ) + str + "\nare reserved and should be 0." );

        tooltip = WARNING_SIGN + " Not zero!";
    }
    else
    {
        tooltip = "Reserved, should be set to zero.";
    }

    if( bits_reserved <= 4)
        name = Format("0x%01X", res_val);
    else if( bits_reserved <= 8)
        name = Format("0x%02X", res_val);
    else if( bits_reserved <= 12)
        name = Format("0x%03X", res_val);
    else if( bits_reserved <= 16)
        name = Format("0x%04X", res_val);
    else if( bits_reserved <= 24)
        name = Format("0x%06X", res_val);
    else if( bits_reserved <= 32)
        name = Format("0x%08X", res_val);
    else
        name = "0";

    PrepareFieldForDlg( "RESERVED", name, tooltip );
}




# -------------------- Prepares field for dialog View ---------------------

###############################################################################
#  This function writes passed data to out.FieldList, using current           #
#  values of field offset and field length.                                   #
#                                                                             #
#  addparam = _ERROR could inform the application about an error in the field #
###############################################################################

PrepareFieldForDlg( field_name, str_value, tooltip, addparam, show_in_collapsed, addparam1, addparam2 )
{
    if( !in.PrepareFldsForDlg ) return 0;

    # Handling erroneous field
    if( (addparam == _ERROR) || (FieldColor == ERROR_COLOR) ) str_value = "e#" + str_value;

    if( !show_in_collapsed ) show_in_collapsed = 0;
    else                     show_in_collapsed = 1;


    if(  BitCurrentFieldOffset >= BitCurrentFieldLength )
        AddViewFieldEntry( field_name, BitCurrentFieldLength, BitCurrentFieldOffset - BitCurrentFieldLength,
            str_value, tooltip, show_in_collapsed, FieldColor, addparam1, addparam2);
    else
        AddViewFieldEntry( field_name, BitCurrentFieldLength, BitCurrentFieldOffset, str_value,
            tooltip, show_in_collapsed, FieldColor, addparam1, addparam2);
}


###########################################################################
#   ZeroField means that field to be added to out.FieldsList is not       #
#   a data field but rather a kind of an additional fields (captions,     #
#   separators, ...)                                                      #
#                                                                         #
#  addparam = _ERROR could inform the application about an error in the   #
#  field                                                                  #
###########################################################################

PrepareZeroFieldForDlg( field_name, str_value, tooltip, addparam, show_in_collapsed )
{
    if( !in.PrepareFldsForDlg ) return 0;

    # Handling erroneous field
    if( (addparam == _ERROR) || (FieldColor == ERROR_COLOR) ) str_value = "e#" + str_value;

    if( !show_in_collapsed ) show_in_collapsed = 0;
    else                     show_in_collapsed = 1;

   AddViewFieldEntry( field_name, 0, 0, str_value, tooltip, show_in_collapsed, FieldColor );
}



###############################################################################
#  This function writes passed data to out.FieldList, using passed            #
#  values of field offset and field length.                                   #
#                                                                             #
#  addparam = _ERROR could inform the application about an error in the field #
#                                                                             #
#  addparam = NOT_USE_COLON_AS_DVDR( or + _ERROR ) specify that caption       #
#             and text should not be divided by colon in Dialog View.         #
###############################################################################

PrepareFieldForDlgExt(field_name, len, offset, str_value, tooltip, addparam, show_in_collapsed )
{
    if( !in.PrepareFldsForDlg ) return 0;

    # Handling erroneous field
    if( (addparam == _ERROR) || (FieldColor == ERROR_COLOR) ) str_value = "e#" + str_value;

    if( !show_in_collapsed ) show_in_collapsed = 0;
    else                     show_in_collapsed = 1;

    AddViewFieldEntry( field_name, len, offset, str_value, tooltip, show_in_collapsed, FieldColor);
}




###############################################################################
#       This function writes passed data to out.FieldList                     #
#       as special field called 'CAPTION'.                                    #
#                                                                             #
#       addparam = _ERROR could inform the application about an error in      #
#       the field.                                                            #
#                                                                             #
#       addparam = NOT_USE_COLON_AS_DVDR( or + _ERROR ) specify that caption  #
#       and text should not be divided by colon in Dialog View.               #
###############################################################################

AddCaptionToDlg( caption, text, tooltip, addparam, show_in_collapsed )
{
    # if show_in_collapsed = null by default we set it to 1
    #
    if( show_in_collapsed != 0 ) show_in_collapsed = 1;


    select{
        addparam == NOT_USE_COLON_AS_DVDR          : {  caption = caption + " " + text; }
        addparam == NOT_USE_COLON_AS_DVDR + _ERROR : {  caption = caption + " " + text; addparam = _ERROR; }
        default                                    :    caption = caption + " : " + text;
    };

    PrepareZeroFieldForDlg("CAPTION", caption, tooltip,
     addparam, show_in_collapsed );
}



###############################################################################
#       This function writes passed data to out.FieldList                     #
#       as special field called 'STRING'.                                     #
#                                                                             #
#       addparam = _ERROR could inform the application about an error in      #
#       the field                                                             #
###############################################################################

AddStringToDlg( caption, text, tooltip, addparam, show_in_collapsed )
{
    # if show_in_collapsed = null by default we set it to 1
    #
    if( show_in_collapsed != 0 ) show_in_collapsed = 1;

    select{
        addparam == NOT_USE_COLON_AS_DVDR          : {  caption = caption + " " + text; }
        addparam == NOT_USE_COLON_AS_DVDR + _ERROR : {  caption = caption + " " + text; addparam = _ERROR; }
        default                                    :    caption = caption + " : " + text;
    };

    PrepareZeroFieldForDlg("STRING", caption , tooltip, addparam,
     show_in_collapsed );
}

###############################################################################
# WrapString( input_str, str_width ):                                         #
#   This function returns a "width-formatted" string. It takes the supplied   #
#   input_str (should not have any line breaks), and formats it into a string #
#   of length str_width, which is WrapStringWidth (80) characters by default. #
#   The default can be redefined by calling the SetWrapString( width )        #
#   function. An effort is made to not break words by only breaking lines at  #
#   spaces, i.e. if the line limit is in a word, the line will be broken at   #
#   the beginning of that word. fmt_input_str it the returned formatted       #
#   string.                                                                   #
#                                                                             #
#   <Usage>                                                                   #
#       WrapString( "ABC..." )     --> uses width WrapStringWidth             #
#       WrapString( "123...", 40 ) --> uses width 40                          #
###############################################################################

WrapString( input_str, str_width )
{
    DEBUG_wrapstring = 0;

    if( str_width == null )
        str_width = WrapStringWidth;

    str_len = sizeof(input_str);        #get the length of the tool tip string

    # Return the input_str if str_width is negative or the input_str length is less than the wrap width
    if( ( str_width < 0 ) || ( str_width > str_len ) )
        return input_str;

    fmt_input_str = "";                 #initialize variables
    copy_index = 0;
    copied_index = 0;
    prev_end_at_space = 0;              #flag to determine if a line break is necessary (doing post-process line breaks)

    /*DEBUG*/ if( DEBUG_wrapstring ) Trace( input_str + "\n" );

    # Parse the input string input_str and break into lines of width str_width.
    for( index = 0; index < str_len; index = copied_index )
    {
        end_at_space = 0;               #flag to determine if copy_index is at a space
        copy_increment = str_width;     #initialize/reinitialize copy_increment (width)

        /*DEBUG*/ if( DEBUG_wrapstring ) dbg_trc_str = "";

        # If the remaining line to be parsed is smaller than the copy_increment, no need to parse, just copy the remaining string
        if( ( str_len - index - 1 ) < copy_increment )
            copy_index = str_len;
        # Else, parse the string
        else
        {
            # Find where to break the string. Search for a space or null within the range [index to copy_index].
            for( copy_index = copy_increment + index; ( end_at_space == 0 ) && ( copy_index > index ); copy_index-- )
            {
                if( ( input_str[ copy_index ] == " " ) || ( input_str[ copy_index ] == null ) )
                {
                    end_at_space = 1;   #set flag to true
                    /*DEBUG*/ if( DEBUG_wrapstring ) dbg_trc_str = Format( "copy_index<in>for = %d; ", copy_index);
                }
            }

            copy_index++;               #correcting an extra decrement ( the above 'for loop' exits with an extra decrement )

            # If a space or null wasn't found within the range, it's an 80+ character 'word', don't add a line break.
            if( !end_at_space )
            {
                /*DEBUG*/ if( DEBUG_wrapstring ) Trace( "Debug: Full line w/ no spaces\n" );
                copy_index = copy_increment + index;
            }
        }

        /*DEBUG*/ if( DEBUG_wrapstring ) dbg_trc_str += FormatEx( "copy_index<out>for = %d; index<out> = %d; @index = \'%s\'\n", copy_index, index, input_str[index] );
        /*DEBUG*/ if( DEBUG_wrapstring ) Trace( dbg_trc_str );

        # Add a line break if not the first line. [ Do post new-line appending to avoid an extra line break at the end of the tool tip string ]
        if( ( index != 0 ) && prev_end_at_space )
            fmt_input_str += "\n";

        # Copy a "line" of data from the input_str to the fmt_input_str.
        for( copied_index = index; copied_index < copy_index; copied_index++ )
        {
            fmt_input_str += input_str[ copied_index ];
        }

        # If a space/null was found, skipping over the space [ (copy_index+1) is a space, and copied_index is equal to copy_index here ]
        if( end_at_space )
            copied_index++;

        prev_end_at_space = end_at_space;   #keeping track of end_at_space in current line to decide wheter to add a line break or not before concatenating next line
    }

    return fmt_input_str;
}

###############################################################################
# SetWrapStringWidth( width ):                                                #
#   Sets the default value for the WrapString(...) function.                  #
###############################################################################

SetWrapStringWidth( width )
{
    if( width )
        WrapStringWidth = width;
}


###############################################################################
#   Makes a special record about DataBlock of length len for Dialog-View.     #
###############################################################################

AddDataBlockToDlg( len, show_in_collapsed )
{
    BitCurrentFieldLength = len * 8;

    PrepareFieldForDlg( "DATA_BLOCK", Format("%d bytes", len),
    Format("Data Block containing %d bytes", len), show_in_collapsed );
}


###############################################################################
#   This function checks offset from beginnig of Data Payload                 #
#   for packet with bad data length and set the current color of field to     #
#   error color when the offset exceeds the length of Data PayLoad.           #
###############################################################################

CheckBadDataLength()
{
    if ( CheckBadDataLength )
    {
         if( GetBitOffset() >= PayloadLenBits ) FieldColor = ERROR_COLOR;
    }
}


###############################################################################
#   Redefined  NextNBits function which increments field offset and           #
#   field length.                                                             #
###############################################################################

NextNBits_( next_n_bits )
{
   if(in.PrepareFldsForDlg)
   {
        BitCurrentFieldOffset += next_n_bits;
        BitCurrentFieldLength  = next_n_bits;
   }


   CheckBadDataLength();

   return NextNBits( next_n_bits );
}



###############################################################################
#   Redefined  PeekNBits function which increments field offset and           #
#   field length.                                                             #
###############################################################################

PeekNBits_( next_n_bits )
{
   if(in.PrepareFldsForDlg)
   {
        BitCurrentFieldOffset += next_n_bits;
        BitCurrentFieldLength  = next_n_bits;
   }

   return PeekNBits( next_n_bits );
}



###############################################################################
#   Redefined  GetNBits function which increments field offset and            #
#   field length.                                                             #
###############################################################################

GetNBits_( offset , len)
{
   if(in.PrepareFldsForDlg)
   {
        BitCurrentFieldOffset = offset + len;
        BitCurrentFieldLength = len;
   }

   CheckBadDataLength();

   return GetNBits(in.Data, offset, len);
}


###############################################################################
#   This function extracts bit field from source starting from start_bit      #
#   and ending end_bit (MSB->LSB order is used here)                          #
###############################################################################

GetRangeBits(start_bit, end_bit, source)
{
    source = source >> start_bit;

    temp = 0;
    for(i = 1; i <= (end_bit - start_bit + 1); i++ )
    {
        temp = (temp << 1) + 0x01;
    }

    return (source & temp);
}


###############################################################################
#   This function extracts bit - 'bit_needed' from source.                    #
###############################################################################

GetBit( bit_needed, source )
{
    return ( (source >> bit_needed) & 0x01 );
}


#################################################################
#  This function draws a special "caption" cell.                #
#################################################################

AddCaptionCell( caption, text, tooltip, addparam, addparam1, addparam2 )
{
    if( !in.PrepareFldsForDlg )
    {
        if ( !AddSpecCaptionCell(caption, text, tooltip, FieldColor, addparam, addparam1, addparam2 ) )    # Check if some specific AddCaptionCell hook handled call
        {
            if( EndCellBlockInNewCaptionCell ) EndCellBlock();

            if( UseCaptionAsCellBlockName )
            {
                BeginCellBlock(caption, text, tooltip, FieldColor, addparam, addparam1 );
            }
            else
            {
                BeginCellBlock(caption, text, tooltip, FieldColor, addparam, addparam1, [_BLOCKNAME, CellBlockName] );
            }
        }
    }
    else
        AddStringToDlg(caption, text, tooltip, addparam, 1);
}



###############################################################################
#                       Usual PayLoad add-Cell functions                      #
###############################################################################

AddPayLoadCell( caption , text, tooltip, addparam, addparam1, addparam2)
{
    if( ShowItemByCaptn( caption ) )
    {
        if( !in.PrepareFldsForDlg )
        {
            if ( !AddSpecPayLoadCell(caption, text, tooltip, FieldColor, addparam, addparam1, addparam2) )   # Check if some specific AddPayLoadCell hook handled call
                AddCell(caption, text, tooltip, FieldColor, addparam, addparam1, addparam2);
        }
        else
            PrepareFieldForDlg(caption , text, tooltip, addparam, VS[COLLAPSED], addparam1, addparam2 );
    }
}




AddPayLoadCellMono( caption , text, tooltip, addparam, addparam1, addparam2)
{
    if( ShowItemByCaptn( caption ) )
    {
        if( !in.PrepareFldsForDlg )
        {
            if ( !AddSpecPayLoadCellMono(caption, text, tooltip, FieldColor, addparam, addparam1, addparam2 ) )  # Check if some specific AddPayLoadCellMono hook handled call
                AddCell(caption, text, tooltip, FieldColor, _MONOCOLOR, addparam, addparam1, addparam2 );
        }
        else
            PrepareFieldForDlg(caption , text, tooltip, addparam, VS[COLLAPSED], addparam1, addparam2 );
    }
}




AddPLCellMonoStr( caption , text, tooltip, addparam, addparam1, addparam2 )
{
       if( ShowItemByCaptn( caption ) )
       {
            if( !in.PrepareFldsForDlg )
            {
                if ( !AddSpecPLCellMonoStr(caption, text, tooltip, FieldColor, addparam, addparam1, addparam2 ) )  # Check if some specific AddPLCellMonoStr hook handled call
                    AddCell(caption, text, tooltip, FieldColor, _MONOCOLOR, addparam, addparam1, addparam2 );
            }
            else
                AddStringToDlg(caption, text, tooltip, addparam, VS[COLLAPSED]);
       }
}




AddPLCellMonoCap( caption , text, tooltip, addparam, addparam1, addparam2 )
{
       if( ShowItemByCaptn( caption ) )
       {
            if( !in.PrepareFldsForDlg )
            {
                if ( !AddSpecPLCellMonoCap(caption, text, tooltip, FieldColor, addparam, addparam1, addparam2 ) )  # Check if some specific AddPLCellMonoCap hook handled call
                    AddCell(caption, text, tooltip, FieldColor, _MONOCOLOR, addparam, addparam1, addparam2 );
            }
            else
                AddCaptionToDlg(caption, text, tooltip, addparam, VS[COLLAPSED]);
       }
}




AddPLCellMonoNoDlg( caption , text, tooltip, addparam, addparam1, addparam2 )
{
   if( SimpleShowItem() )
        if( !in.PrepareFldsForDlg )
            if ( !AddSpecPLCellMonoNoDlg(caption, text, tooltip, FieldColor, addparam, addparam1, addparam2 ) )  # Check if some specific AddPLCellMonoNoDlg hook handled call
                AddCell(caption, text, tooltip, FieldColor, _MONOCOLOR, addparam, addparam1, addparam2 );
}


AddPLCellNoDlg( caption , text, tooltip, addparam, addparam1, addparam2)
{
    if( ShowItemByCaptn( caption ) )
    {
        if(!in.PrepareFldsForDlg)
        {
            if ( !AddSpecPayLoadCell(caption, text, tooltip, FieldColor, addparam, addparam1, addparam2) )   # Check if some specific AddPLCellNoDlg hook handled call
                AddCell(caption, text, tooltip, FieldColor, addparam, addparam1, addparam2);
        }
    }
}

AddPLCellInDlg( caption , text, tooltip, addparam, addparam1, addparam2 )
{
   if( in.PrepareFldsForDlg )
		PrepareFieldForDlg(caption , text, tooltip, addparam, VS[COLLAPSED], addparam1, addparam2 );  # Show in Dialog View only
}

AddStrCellInDlg( caption , text, tooltip, addparam, addparam1, addparam2 )
{
	if( in.PrepareFldsForDlg )
		AddStringToDlg(caption, text, tooltip, addparam, VS[COLLAPSED]);
}

###############################################################################
#                       "Simple" PayLoad add-Cell functions                   #
# "Simple" payload cells pay no attention to view settings - they are not     #
#  seen in COLLAPSED state and are in EXPANDED state                          #
###############################################################################


AddSimplePLCell( caption , text, tooltip, addparam, addparam1, addparam2 )
{
   if( in.PrepareFldsForDlg )
        PrepareFieldForDlg(caption , text, tooltip, addparam, 0, addparam1, addparam2 );
   else
       if( SimpleShowItem() )
            if ( !AddSpecSimplePLCell(caption, text, tooltip, FieldColor, addparam, addparam1, addparam2 ) )  # Check if some specific AddSimplePLCell hook handled call
                AddCell(caption, text, tooltip, FieldColor, addparam, addparam1, addparam2 );
}




AddSimpleCellMonoCap( caption , text, tooltip, addparam, addparam1, addparam2 )
{
   if( in.PrepareFldsForDlg )
        AddCaptionToDlg( caption, text, tooltip, addparam, 0 );
   else
       if( SimpleShowItem() )
            if ( !AddSpecSimpleCellMonoCap(caption, text, tooltip, FieldColor, addparam, addparam1, addparam2 ) )  # Check if some specific AddSimpleCellMonoCap hook handled call
                AddCell(caption, text, tooltip, FieldColor, _MONOCOLOR, addparam, addparam1, addparam2 );
}



AddSimpleCellMonoStr( caption , text, tooltip, addparam, addparam1, addparam2 )
{
   if( in.PrepareFldsForDlg )
        AddStringToDlg( caption, text, tooltip, addparam, 0 );
   else
       if( SimpleShowItem() )
            if ( !AddSpecSimpleCellMonoStr(caption, text, tooltip, FieldColor, addparam, addparam1, addparam2) )  # Check if some specific AddSimpleCellMonoStr hook handled call
                AddCell(caption, text, tooltip, FieldColor, _MONOCOLOR, addparam, addparam1, addparam2 );
}



###############################################################################
#                       "Block" PayLoad add-Cell functions                    #
# "Block" payload cells use view settings contained in global view setting    #
# variable VS. This allow to apply one view setting to many cells - block     #
###############################################################################


AddBlockPLCell( caption , text, tooltip, addparam, addparam1, addparam2 )
{
   if( in.PrepareFldsForDlg )
        PrepareFieldForDlg(caption , text, tooltip, addparam, VS[COLLAPSED], addparam1, addparam2 );
   else
       if( ShowItem(VS) )
            if ( !AddSpecBlockPLCell(caption, text, tooltip, FieldColor, addparam, addparam1, addparam2) )  # Check if some specific AddBlockPLCell hook handled call
                AddCell(caption, text, tooltip, FieldColor, addparam, addparam1, addparam2 );
}



AddBlockPLCellMonoStr( caption , text, tooltip, addparam, addparam1, addparam2 )
{
   if( in.PrepareFldsForDlg )
        AddStringToDlg(caption, text, tooltip, addparam, VS[COLLAPSED] );
   else
       if( ShowItem(VS) )
            if ( !AddSpecBlockPLCellMonoStr(caption, text, tooltip, FieldColor, addparam, addparam1, addparam2 ) )  # Check if some specific AddBlockPLCellMonoStr hook handled call
                AddCell(caption, text, tooltip, FieldColor, _MONOCOLOR, addparam, addparam1, addparam2 );
}


AddBlockPLCellMonoCap( caption , text, tooltip, addparam, addparam1, addparam2 )
{
   if( in.PrepareFldsForDlg )
        AddCaptionToDlg(caption, text, tooltip, addparam, VS[COLLAPSED] );
   else
       if( ShowItem(VS) )
            if ( !AddSpecBlockPLCellMonoCap(caption, text, tooltip, FieldColor, addparam, addparam1, addparam2 ) )  # Check if some specific AddBlockPLCellMonoCap hook handled call
                AddCell(caption, text, tooltip, FieldColor, _MONOCOLOR, addparam, addparam1, addparam2 );
}




###############################################################################
#   This funciton add cell presenting decoder errors of some kinds.           #
#   Usually, it is added as the last cell of decoding illustrating that       #
#   a very serious decoding error occured.                                    #
###############################################################################

AddErrorMonoCell( caption, text, tooltip )
{
    AddCell( caption , text, tooltip , ERROR_COLOR, _MONOCOLOR);

    if( FieldColor != ERROR_COLOR ) caption = "e#" + caption;
	AddStringToDlg( caption, text, "e#" + tooltip );
}


IsExpanded()
{
   return ( in.Expanded || IsCellBlockExpanded() );
}



##############################################################################
#     Function defining if we should show item defined with view_setting     #
##############################################################################

ShowItem( view_setting )
{
    # always show if we prepare data for dialog-view
    if( in.PrepareFldsForDlg ) return 1;

    expanded = IsExpanded();

    if( expanded )
    {
        if( ViewAll ) return 1;
        if( HideAll ) return 0;
    }

    # show item anyway if view setting for it not valid
    if( view_setting == null ) return 1;

    return ( view_setting[expanded] );
}





##############################################################################
#     Function defining if we should show item having caption 'caption'      #
##############################################################################

ShowItemByCaptn( caption )
{
    VS = Resolve( Prefix + " " + caption );
    return ShowItem( VS );
}



##############################################################################
#     Function defining that we should show item in expanded state and not   #
#     in collapsed one. Function has prefix 'Simple' because of item's       #
#     view settings being ignored.                                           #
##############################################################################

SimpleShowItem( )
{
    # always show if we prepare data for dialog-view
    if( in.PrepareFldsForDlg ) return 1;

    if( IsExpanded() )
    {
        if( ViewAll ) return 1;
        if( HideAll ) return 0;
        return 1;
    }

    return 0;
}



IsHideAll()
{
    if( in.PrepareFldsForDlg || !IsExpanded() ) return 0;
    if( (ViewAll == 0) && (HideAll != 0) )      return 1;

    return 0;
}





###############################################################################
#  This function is used to make common check of reserved bits taking into    #
#  account view settings.                                                     #
###############################################################################

PLReservedCheck( reserved_bits )
{
    if( !in.PrepareFldsForDlg )
    {
        if( !HideAll || ViewAll )
            ReservedCheck( reserved_bits );
        else
            NextNBits(reserved_bits);
    }
    else
        ReservedCheck( reserved_bits );
}



###############################################################################
#   This function returns difference between integer values considering them  #
#   as unsigned values. So value - 0xFFFFFFFF is -1 and less than 0 in        #
#   logical conditions, but as unsigned integer it is so much bigger than 0.  #
#   Use this function in places where you want integer values to be           #
#   thought of as unsigned.                                                   #
###############################################################################

UnsignedCompare( op1, op2 )
{
    if( op1 >= 0 && op2 >= 0 ) return (op1 - op2);
    if( op1 <  0 && op2 <  0 ) return (op1 - op2);

    return (op2 - op1);
}




CheckOffset()
{
    AddCell( Format ("GetBitOffset()   =  %u", GetBitOffset()),
    Format("PayloadLenBits = %u", PayloadLenBits), "", 0, _WARNING );
}



SetDecodedFully()
{
    out.Decoded = in.DataLength;
    SetSpecDecodedFully(); # try to call decoder-specific hook
}


set OldByteOrder = BIG_ENDIAN;

########################################################################
# This function instructs the application that hexadecimal             #
# values for multi-byte fields(<= 32 bits only) in byte payloads       #
# should be retrieved using the specified format.                      #
#                                                                      #
# This function returns previously used format.                        #
#                                                                      #
# Ignored when building cells in trace view and for DWORD payloads.    #
########################################################################

SetByteOrder( little_endian )
{
    OldByteOrder = GetFieldByteOrder(); # save the previous field byte order


    # Instructs the application to use the specified bit order in
    # NextNBits, GetNBits, PeekNBits functions.
    SetFieldByteOrder( little_endian );

    if( in.PrepareFldsForDlg )
    {
        if( little_endian ) str = "LSB_MSB";
        else                str = "MSB_LSB";

        AddViewFieldEntry( "BYTE_ORDER", 0, 0, str, "", 0, FieldColor );
    }

    return OldBitOrder;
}

########################################################################
# This function Forces to use full descrption strings when building    #
# HTML source for View Fields Dialog.                                  #
########################################################################
ForceFullDescriptions()    
{   
    if( in.PrepareFldsForDlg )
        AddViewFieldEntry( "DESCRIPTION_MODE", 0, 0, "FullDescription", "", 0, FieldColor );
}

########################################################################
# This function Doesn't Forces to use full descrption strings when     #
# building HTML source for View Fields Dialog.                         #
########################################################################
DontForceFullDescriptions()
{
    if( in.PrepareFldsForDlg )
          AddViewFieldEntry( "DESCRIPTION_MODE", 0, 0, "", "", 0, FieldColor );
}



########################################################################
# This function restores field bit order changed by the SetByteOrder() #
# function.                                                            #
#                                                                      #
# The 'prev_byte_order' parameter specifies a previously used byte     #
# order.                                                               #
# If it is 'null' then OldByteOrder global variable will be used.      #
########################################################################

RestoreByteOrder( prev_byte_order )
{
    if( prev_byte_order != null )
        SetFieldByteOrder( prev_byte_order );
    else
        SetFieldByteOrder( OldByteOrder );
}



set OldPrefix = "";

#######################################################################
# This function saves the current field prefix and set it to          #
# a new value.                                                        #
#######################################################################

SetPrefix( prefix )
{
    OldPrefix = Prefix;
    Prefix = prefix;
}


#######################################################################
# This function restores the field prefix from the saved value.       #
#######################################################################

RestorePrefix()
{
    Prefix = OldPrefix;
}


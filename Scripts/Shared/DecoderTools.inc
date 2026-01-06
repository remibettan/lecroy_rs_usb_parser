#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  DecoderTools.inc
#
#  Display Decoder Tools
#

const RED          = 0x0000FF;




Find(table, table_key)
{
  i = 0;
  while( table[i][0] != null )  
  {
    if (table[i][0] == table_key) return table[i];
    i = i + 1;
  }
  return table[0];
}


DataBlock( len )
{
  select
  {
    len == 0 :  ;
    len == 1 :  AddDataCell( [ NextNBits(8)] );
    len == 2 :  AddDataCell( [ NextNBits(8), NextNBits(8)] );
    len == 3 :  AddDataCell( [ NextNBits(8), NextNBits(8), NextNBits(8)] );
    len == 4 :  AddDataCell( [ NextNBits(8), NextNBits(8), NextNBits(8), NextNBits(8)] );
    default  :  AddDataCell(   NextNBits(8*len) );
  };
#  if (len > 0) AddDataCell( NextNBits(8*len) );
}


ShowDataBlock( len )
{
  DataBlock( len );
  out.Decoded = out.Decoded + len;
}



CopyToOutData( len )
{
  select
  {
    len == 0 :  ;
    len == 1 :  out.Data = [ NextNBits(8) ];
    len == 2 :  out.Data = [ NextNBits(8), NextNBits(8)];
    len == 3 :  out.Data = [ NextNBits(8), NextNBits(8), NextNBits(8)];
    len == 4 :  out.Data = [ NextNBits(8), NextNBits(8), NextNBits(8), NextNBits(8)];
    default  :  out.Data =   NextNBits(len * 8);
  };
}

CopyAddToOutData( len )
{
  select
  {
    len == 0 :  ;
    len == 1 :  out.Data[sizeof(out.Data)] = NextNBits(8);
    len == 2 :  
    { 
      out.Data[sizeof(out.Data)] = NextNBits(8); 
      out.Data[sizeof(out.Data)] = NextNBits(8); 
    }
    len == 3 :  
    { 
      out.Data[sizeof(out.Data)] = NextNBits(8); 
      out.Data[sizeof(out.Data)] = NextNBits(8); 
      out.Data[sizeof(out.Data)] = NextNBits(8);
    }
    len == 4 :  
    {
      out.Data[sizeof(out.Data)] = NextNBits(8); 
      out.Data[sizeof(out.Data)] = NextNBits(8); 
      out.Data[sizeof(out.Data)] = NextNBits(8);
      out.Data[sizeof(out.Data)] = NextNBits(8);
    }
    default  :  out.Data += NextNBits(len * 8);
  };
}




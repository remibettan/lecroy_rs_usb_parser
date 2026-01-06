#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  DecoderTools.inc
#
#  Display Decoder Tools
#

%include "DecoderTools.inc"


set M_color   = 0x6295ff;             #RGB(255,149,98);
set S_color   = 0x80ff00;
set Ch1_color = 0x800000;
set Ch2_color = 0x000080;

ShowAmAddrSlave()
{
  if(in.AmAddr != null)
  {

    if (in.Channel == null)
    {
      if (in.Slave == 0)
        AddCell("T", "M" ,"Master", M_color, _MONOCOLOR);
      else
        AddCell("T", "S" ,"Slave" , S_color, _MONOCOLOR);
    }
    else if (in.Channel == 0)
    {
      if (in.Slave == 0)
        AddCell("C1", "M" ,"Master on channel 1 transmitting", Ch1_color, [_LOWERCOLOR , M_color] );
      else
        AddCell("C1", "S" ,"Slave on channel 1 transmitting", Ch1_color, [_LOWERCOLOR , S_color] );
    }
    else if (in.Channel == 1)
    {
      if (in.Slave == 0)
        AddCell("C2", "M" ,"Master on channel 2 transmitting", Ch2_color, [_LOWERCOLOR , M_color] );
      else
        AddCell("C2", "S" ,"Slave on channel 2 transmitting", Ch2_color, [_LOWERCOLOR , S_color] );
    }
  }
  else if(in.ConnectionHandle != null)
  {
    if (in.Slave == 0)
      AddCell("T", "H" ,"Host to Host Controller", M_color, _MONOCOLOR);
    else
      AddCell("T", "C" ,"Host Controller to Host" , S_color, _MONOCOLOR);
  }
  
  AddSeparator();
}

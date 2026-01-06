#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
# Midi Payload data decoder
set _MIDIColor=0x7700aa;
set _MIDICellCOLOR = 0x7700aa;
set CIN_Table = 
[
	[0x0, "MidiMisc"     ,3 ,0x7700aa ,"Miscellaneous function codes. Reserved for future extensions."],
	[0x1, "CableEvent"   ,3 ,0x7700aa ,"Cable events. Reserved for future expansion."],
	[0x2, "Message2"     ,2 ,0x7700aa ,"Two-byte System Common messages like MTC, SongSelect, etc."],
	[0x3, "Message3"     ,3 ,0x7700aa ,"Three-byte System Common messages like SPP, etc."],
	[0x4, "SysEx"        ,3 ,0x7700aa ,"SysEx starts or continues"],
	[0x5, "Message1"     ,1 ,0x7700aa ,"Single-byte System Common Message or SysEx ends with following single byte."],
	[0x6, "SysExEnd2"    ,2 ,0x7700aa ,"SysEx ends with following two bytes."],
	[0x7, "SysExEnd3"    ,3 ,0x7700aa ,"SysEx ends with following three bytes."],
	[0x8, "NoteOff"      ,3 ,0xA750aa ,"Note-off"],
	[0x9, "NoteOn"       ,3 ,0xB780aa ,"Note-on"],
	[0xA, "PolyKeyPress" ,3 ,0x7700aa ,"Poly-KeyPress"],
	[0xB, "CtrlChange"   ,3 ,0x7700aa ,"Control Change"],
	[0xC, "PgmChange"    ,2 ,0x7700aa ,"Program Change"],
	[0xD, "ChanPressure" ,2 ,0x7700aa ,"Channel Pressure"],
	[0xE, "PitchBend"    ,3 ,0x7700aa ,"PitchBend Change"],
	[0xF, "SysMsg"     ,1 ,0x7700aa ,"Single Byte"]
];

DecodeMidiPacket()
{
    
    CblNum=NextNBits(4);
	CIN=NextNBits(4);
	CINDcde=Find(CIN_Table,CIN);
	numByteDecded=1;
	AddCell("Chan",CblNum,"Cable Number",_MIDIColor+(CblNum<<2));
	AddCell("CIN",CINDcde[1],FormatEx("%d = %s:",CIN,CINDcde[4]),_MIDIColor+(CIN<<3));
	
	numByteDecded += DecodeMidiMessage();
	#AddCell("Decoded",numByteDecded);
    return numByteDecded;
}

DecodeMidiMessage()
{
	
	msgStatus= NextNBits(8);
	dcdn=1;
	Mchan= (msgStatus & 0x0F) +1;
	Mstatus = (msgStatus >>4) ;
	if (Mstatus != 0xf) {
		_row =Find(CIN_Table,Mstatus);
		
		if (Mstatus<8) {
			AddCell("MidiMessage", FormatEx("0x%X : %s",Mstatus,_row[1]), "Warning: Message status should be >128",_MIDIColor,_WARNING);
		} else {
			AddCell("MidiMessage", FormatEx("0x%X : %s",Mstatus,_row[1]), FormatEx("Message status code=%d\n%s",Mstatus,_row[4]),_row[3]);
		
		
		
		
		}
		AddCell("MidiChan", Mchan, FormatEx("Message Midi Channel =%d",Mchan),_MIDIColor+(Mchan<<6));
		_MIDICellCOLOR = _row[3];
		Call(_row[1]);
		dcdn+=_row[2];
	} else {
		_row = Find(sysMessageTable,msgStatus);
		if (msgStatus>0xF7) 
		{
			AddCell("SysRealTimeMessage", FormatEx("0x%X : %s",msgStatus,_row[1]), FormatEx("System Real Time Message: %s",_row[2]),_MIDIColor);

			# dcdn+=decodeManufacturer();
			# dcdn+=dumpMessageData();
		
		} else {
			
			AddCell("SysCommonMessage", FormatEx("0x%X : %s",msgStatus,_row[1]), FormatEx("System Common Message: %s",_row[2]),_MIDIColor);
				# vendor specific message ending in f7?
			if (msgStatus == 0xF0) {
				dcdn+=decodeManufacturer();
				dcdn+=dumpMessageData();
				tInt = (dcdn+1)/4; 
				
				if ((dcdn+1) != tInt*4) {
					pads=((tInt+1) * 4)-(dcdn+1);
					
					while (pads>0) {
						if (dcdn<in.DataLength) {
							Pad1Byte(4-pads);
							dcdn++;
						}
						pads--	;				
					}
				
				}
			}
		
		}
	
	}
	return dcdn;
}

set sysMessageTable = [
[ 0xF0, "SysEx","System Exclusive Message"],
[ 0xF1, "MTCQuarterFrm", "MIDI Time Code Quarter Frame"],
[ 0xF2, "SongPosPtr","Song Position Pointer"],
[ 0xF3, "SongSelect", "Song Select"],
[ 0xF4, "RsvdFutureUse","Reserved for Future Use"],
[ 0xF5, "RsvdFutureUse","Reserved for Future Use"],
[ 0xF6, "TuneRequest", "Tune Request"],
[ 0xF7, "EOX", "EOX (End of Exclusive)"],
[ 0xF8, "SysRTM_TimingClk", "Timing Clock"],
[ 0xFA, "SysRTM_Start", "Start"],
[ 0xFB, "SysRTM_Continue", "Continue"],
[ 0xFC, "SysRTM_Stop", "Stop"],
[ 0xF4, "RsvdFutureUse","Reserved for Future Use"],
[ 0xFE, "SysRTM_ActiveSensing", "Active Sensing"],
[ 0xFF, "SysReset", "System Reset"]
];

CheckDataByte(cellValue,cellName,cellText,cellTooltip,celColor)
{
#databytes should be in the range 0-127 only
if (cellValue<128) 
	AddCell(cellName,cellText,cellTooltip,celColor);
else
	AddCell(cellName,cellText,FormatEx("Error: Databyte value %d >127!\n%s",cellValue,cellTooltip),celColor,_ERROR);
}

dumpMessageData()
{
	dmpMsgStr="";
	j=0;
     for (i=2;i<in.DataLength; i++)
	 {
		b1=PeekNBits(8);
		if (b1<128) 
		{
			b1=NextNBits(8);
			dmpMsgStr+= Format("%02X ",b1);
			j++;
		} else {
			i=in.DataLength;
		}
	 }
	 #if (IsExpanded()) {
	 AddCell("MessageData",dmpMsgStr, "Message Data bytes",0x001052);
	 #} else {
	 #AddCell("MessageData",j + "bytes" , "Message Data bytes",0x001052);
	 
	 
	 #}
	if (b1==0xF7) {
		b1=NextNBits(8);
		AddCell("MsgTerm","0xF7", "Message Termination byte correctly sent",0x00AA00);
		j++;
	} else {
		AddCell("MsgTerm",FormatEx("Message Abort: 0x%02X",b1),"Message aborted next byte is >127 = new status message",0x00AAAA,_WARNING);	
	}
	return j;
}
Pad1Byte(bnum)
{
	b1=NextNBits(8);
    CheckDataByte(b1,"Pad#"+bnum,Format("0x%02X",b1),Format("Padding Byte=%d",b1),0xaaaaaa);
	return 1;
}



MidiMisc() #Miscellaneous function codes. Reserved for future extensions
{
	b1=NextNBits(8);
	CheckDataByte(b1,"b1",Format("0x%02X",b1),Format(" b1=%d",b1),_MIDICellCOLOR);
	b1=NextNBits(8);
    CheckDataByte(b1,"b2",Format("0x%02X",b1),Format(" b1=%d",b1),_MIDICellCOLOR);

}

CableEvent() #Cable events. Reserved for future expansion.
{
	b1=NextNBits(8);
    CheckDataByte(b1,"b1",Format("0x%02X",b1),Format(" b1=%d",b1),_MIDICellCOLOR);
	PadByte(2);

}

Message2() #Two-byte System Common messages like MTC, SongSelect, etc.
{
	b1=NextNBits(8);
    CheckDataByte(b1,"b1",Format("0x%02X",b1),Format(" b1=%d",b1),_MIDICellCOLOR);
	b1=NextNBits(8);
    CheckDataByte(b1,"b2",Format("0x%02X",b1),Format(" b1=%d",b1),_MIDICellCOLOR);

}
Message3() #Three-byte System Common messages like SPP, etc."],
{
	b1=NextNBits(8);
    CheckDataByte(b1,"b1",Format("0x%02X",b1),Format(" b1=%d",b1),_MIDICellCOLOR);
	b1=NextNBits(8);
    CheckDataByte(b1,"b2",Format("0x%02X",b1),Format(" b1=%d",b1),_MIDICellCOLOR);

}
SysEx() #SysEx starts or continues"],
{
	b1=NextNBits(8);
    CheckDataByte(b1,"b1",Format("0x%02X",b1),Format(" b1=%d",b1),_MIDICellCOLOR);
	PadByte(2);

}

Message1() #Single-byte System Common Message or SysEx ends with following single byte."],
{
	b1=NextNBits(8);
    CheckDataByte(b1,"b1",Format("0x%02X",b1),Format(" b1=%d",b1),_MIDICellCOLOR);
	PadByte(2);

}

SysExEnd2() #SysEx ends with following two bytes."],
{
	b1=NextNBits(8);
    CheckDataByte(b1,"b1",Format("0x%02X",b1),Format(" b1=%d",b1),_MIDICellCOLOR);
	b1=NextNBits(8);
    CheckDataByte(b1,"b2",Format("0x%02X",b1),Format(" b1=%d",b1),_MIDICellCOLOR);

}

SysExEnd3() #SysEx ends with following three bytes."],
{
	b1=NextNBits(8);
    CheckDataByte(b1,"b1",Format("0x%02X",b1),Format(" b1=%d",b1),_MIDICellCOLOR);
	b1=NextNBits(8);
    CheckDataByte(b1,"b2",Format("0x%02X",b1),Format(" b1=%d",b1),_MIDICellCOLOR);

}

NoteOff()
{
	b1=NextNBits(8);
    CheckDataByte(b1,"KeyCode",Format("0x%02X",b1),Format("Note or Key value=%d",b1),_MIDIColor+(b1<<5));
 	b2=NextNBits(8);
    CheckDataByte(b1,"Velocity",Format("0x%02X",b2),Format("Key Press Velocity/Pressure=%d",b2),_MIDIColor-(b2<<4));

}
NoteOn()
{
	b1=NextNBits(8);
    CheckDataByte(b1,"KeyCode",Format("0x%02X",b1),Format("Note or Key value=%d",b1),_MIDIColor+(b1<<5));
 	b2=NextNBits(8);
    CheckDataByte(b1,"Velocity",Format("0x%02X",b2),Format("Key Press Velocity/Pressure=%d",b2),_MIDIColor-(b2<<4));

}

PolyKeyPress() 
{ #Poly-KeyPress
	b1=NextNBits(8);
    CheckDataByte(b1,"b1",Format("0x%02X",b1),Format("PolyKeyPress b1=%d",b1),_MIDICellCOLOR);
	PadByte(2);

}

CtrlChange() #Control Change
{
	b1=NextNBits(8);
	_row = Find(ControlChangeMsg_Table3,b1);
    CheckDataByte(b1,"CtrlChangeMsg",_row[1],FormatEx("%d : %s",b1,_row[2]),_MIDICellCOLOR);
	b2=NextNBits(8);
    CheckDataByte(b1,"CtrlValue",Format("0x%02X",b2),FormatEx("%s valus=%d",_row[2],b2),_MIDICellCOLOR);
	

}

PgmChange() #Program Change
{
	b1=NextNBits(8);
    CheckDataByte(b1,"b1",Format("0x%02X",b1),Format(" b1=%d",b1),_MIDICellCOLOR);
	PadByte(2);

}

ChanPressure() #Channel Pressure"],
{
	b1=NextNBits(8);
    CheckDataByte(b1,"b1",Format("0x%02X",b1),Format(" b1=%d",b1),_MIDICellCOLOR);
	PadByte(2);

}

PitchBend() #PitchBend Change"],
{
	b1=NextNBits(8);
    CheckDataByte(b1,"b1",Format("0x%02X",b1),Format(" b1=%d",b1),_MIDICellCOLOR);
	PadByte(2);

}	
MidiByte()
{ # 1byte midi message
	b1=NextNBits(8);
    CheckDataByte(b1,"RawByte",Format("0x%02X",b1),Format("Single raw byte sent%d",b1),_MIDICellCOLOR);
    PadByte(2);

}

set ControlChangeMsg_Table3= [
[0,"MSB_0_Bank_Select","LSB for Control 0 (Bank Select)"],
[ 1 ,"ModWheel","Modulation Wheel or Lever"],
[ 2 ,"BreathCntrl","Breath Controller"],
[ 3 ,"Undefined","Undefined"],
[ 4 ,"FootCntrl","Foot Controller"],
[ 5 ,"PortamentoTime","Portamento Time"],
[ 6 ,"Data_Entry_","Data Entry MSB"],
[ 7 ,"ChanVol","Channel Volume (formerly Main Volume)"],
[ 8 ,"Balance","Balance"],
[ 9 ,"Undefined","Undefined"],
[ 10 ,"Pan","Pan"],
[ 11 ,"Expression_","Expression Controller"],
[ 12 ,"Effect_1","Effect Control 1"],
[ 13 ,"Effect2","Effect Control 2"],
[ 14 ,"Undefined","Undefined"],
[ 15 ,"Undefined","Undefined"],
[ 16 ,"General_Purpose_Cntrl1","General Purpose Controller 1"],
[ 17 ,"General_Purpose_Cntrl2","General Purpose Controller 2"],
[ 18 ,"General_Purpose_Cntrl3","General Purpose Controller 3"],
[ 19 ,"General_Purpose_Cntrl4","General Purpose Controller 4"],
[ 20 ,"Undefined","Undefined"],
[ 21 ,"Undefined","Undefined"],
[ 22 ,"Undefined","Undefined"],
[ 23 ,"Undefined","Undefined"],
[ 24 ,"Undefined","Undefined"],
[ 25 ,"Undefined","Undefined"],
[ 26 ,"Undefined","Undefined"],
[ 27 ,"Undefined","Undefined"],
[ 28 ,"Undefined","Undefined"],
[ 29 ,"Undefined","Undefined"],
[ 30 ,"Undefined","Undefined"],
[ 31 ,"Undefined","Undefined"],
[ 32 ,"LSB_0_Bank_Select","LSB for Control 0 (Bank Select)"],
[ 33 ,"LSB_1Modulation_Wheel_or_Lever","LSB for Control 1 (Modulation Wheel or Lever)"],
[ 34 ,"LSB_2_Breath_Cntrller","LSB for Control 2 (Breath Controller)"],
[ 35 ,"LSB_3_Undefined","LSB for Control 3 (Undefined)"],
[ 36 ,"LSB_4_Foot_Cntrller","LSB for Control 4 (Foot Controller)"],
[ 37 ,"LSB_5_Portamento_Time","LSB for Control 5 (Portamento Time)"],
[ 38 ,"LSB_6_Data_Entry","LSB for Control 6 (Data Entry)"],
[ 39 ,"LSB_7_ChanVolume","LSB for Control 7 (Channel Volume, formerly Main Volume)"],
[ 40 ,"LSB_8_Balance","LSB for Control 8 (Balance)"],
[ 41 ,"LSB_9_Undefined","LSB for Control 9 (Undefined)"],
[ 42 ,"LSB_10_Pan","LSB for Control 10 (Pan)"],
[ 43 ,"LSB_11Expression_Cntrller","LSB for Control 11 (Expression Controller)"],
[ 44 ,"LSB_12_Effect_Cntrl_1","LSB for Control 12 (Effect control 1)"],
[ 45 ,"LSB_13_Effect_Cntrl_2","LSB for Control 13 (Effect control 2)"],
[ 46 ,"LSB_14_Undefined","LSB for Control 14 (Undefined)"],
[ 47 ,"LSB_15_Undefined","LSB for Control 15 (Undefined)"],
[ 48 ,"LSB_16_General_Purpose_Cntrl1","LSB for Control 16 (General Purpose Controller 1)"],
[ 49 ,"LSB_17_General_Purpose_Cntrl2","LSB for Control 17 (General Purpose Controller 2)"],
[ 50 ,"LSB_18_General_Purpose_Cntrl3","LSB for Control 18 (General Purpose Controller 3)"],
[ 51 ,"LSB_19_General_Purpose_Cntrl4","LSB for Control 19 (General Purpose Controller 4)"],
[ 52 ,"LSB_20_Undefined","LSB for Control 20 (Undefined)"],
[ 53 ,"LSB_21Undefined","LSB for Control 21 (Undefined)"],
[ 54 ,"LSB_22_Undefined","LSB for Control 22 (Undefined)"],
[ 55 ,"LSB_23_Undefined","LSB for Control 23 (Undefined)"],
[ 56 ,"LSB_24_Undefined","LSB for Control 24 (Undefined)"],
[ 57 ,"LSB_25_Undefined","LSB for Control 25 (Undefined)"],
[ 58 ,"LSB_26_Undefined","LSB for Control 26 (Undefined)"],
[ 59 ,"LSB_27_Undefined","LSB for Control 27 (Undefined)"],
[ 60 ,"LSB_28_Undefined","LSB for Control 28 (Undefined)"],
[ 61 ,"LSB_29_Undefined","LSB for Control 29 (Undefined)"],
[ 62 ,"LSB_30_Undefined","LSB for Control 30 (Undefined)"],
[ 63 ,"LSB_31Undefined","LSB for Control 31 (Undefined)"],
[ 64 ,"Damper_Pedal_","Damper Pedal onoff (Sustain)"],
[ 65 ,"Portamento_On","Portamento OnOff"],
[ 66 ,"Sostenuto_On","Sostenuto OnOff"],
[ 67 ,"Soft_Pedal_On","Soft Pedal OnOff"],
[ 68 ,"Legato_Footswitch","Legato Footswitch"],
[ 69 ,"Hold_2","Hold 2"],
[ 70 ,"SndCntrl1SndVariation","Sound Controller 1 (default: Sound Variation)"],
[ 71 ,"SndCntrl2_TimbreHarmonic_Intens.","Sound Controller 2 (default: TimbreHarmonic Intens.)"],
[ 72 ,"SndCntrl3_Release_Time","Sound Controller 3 (default: Release Time)"],
[ 73 ,"SndCntrl4_Attack_Time","Sound Controller 4 (default: Attack Time)"],
[ 74 ,"SndCntrl5_Brightness","Sound Controller 5 (default: Brightness)"],
[ 75 ,"SndCntrl6_Decay_Time","Sound Controller 6 (default: Decay Time - see MMA RP-021)"],
[ 76 ,"SndCntrl7_Vibrato_Rate","Sound Controller 7 (default: Vibrato Rate - see MMA RP-021)"],
[ 77 ,"SndCntrl8_Vibrato_Depth","Sound Controller 8 (default: Vibrato Depth - see MMA RP-021)"],
[ 78 ,"SndCntrl9_Vibrato_Delay","Sound Controller 9 (default: Vibrato Delay - see MMA RP-021)"],
[ 79 ,"SndCntrl10_default_undefined","Sound Controller 10 (default undefined - see MMA RP-021)"],
[ 80 ,"General_Purpose_Cntrl5","General Purpose Controller 5"],
[ 81 ,"General_Purpose_Cntrl6","General Purpose Controller 6"],
[ 82 ,"General_Purpose_Cntrl7","General Purpose Controller 7"],
[ 83 ,"General_Purpose_Cntrl8","General Purpose Controller 8"],
[ 84 ,"Portamento_Cntrl","Portamento Control"],
[ 85 ,"Undefined","Undefined"],
[ 86 ,"Undefined","Undefined"],
[ 87 ,"Undefined","Undefined"],
[ 88 ,"High_Resolution_Velocity_Prefix","High Resolution Velocity Prefix"],
[ 89 ,"Undefined","Undefined"],
[ 90 ,"Undefined","Undefined"],
[ 91 ,"Effects_1Depth","Effects 1 Depth (default: Reverb Send Level - see MMA RP-023) (formerly External Effects Depth)"],
[ 92 ,"Effects_2_Depth_formerly_Tremolo_Depth","Effects 2 Depth (formerly Tremolo Depth)"],
[ 93 ,"Effects_3_Depth","Effects 3 Depth (default: Chorus Send Level - see MMA RP-023)(formerly Chorus Depth)"],
[ 94 ,"Effects_4_Depth_formerly_Celeste_Detune_Depth","Effects 4 Depth (formerly Celeste [Detune] Depth)"],
[ 95 ,"Effects_5_Depth_formerly_Phaser_Depth","Effects 5 Depth (formerly Phaser Depth)"],
[ 96 ,"Data_Increment_Data_Entry_P1","Data Increment (Data Entry +1) (see MMA RP-018)"],
[ 97 ,"Data_Decrement_Data_Entry_M1","Data Decrement (Data Entry -1) (see MMA RP-018)"],
[ 98 ,"NRPN_LSB","Non-Registered Parameter Number (NRPN) - LSB"],
[ 99 ,"NRPN_MSB","Non-Registered Parameter Number (NRPN) - MSB"],
[ 100 ,"RPN_lsb","Registered Parameter Number (RPN) - LSB*"],
[ 101 ,"RPN_msb","Registered Parameter Number (RPN) - MSB*"],
[ 102 ,"Undefined","Undefined"],
[ 103 ,"Undefined","Undefined"],
[ 104 ,"Undefined","Undefined"],
[ 105 ,"Undefined","Undefined"],
[ 106 ,"Undefined","Undefined"],
[ 107 ,"Undefined","Undefined"],
[ 108 ,"Undefined","Undefined"],
[ 109 ,"Undefined","Undefined"],
[ 110 ,"Undefined","Undefined"],
[ 111 ,"Undefined","Undefined"],
[ 112 ,"Undefined","Undefined"],
[ 113 ,"Undefined","Undefined"],
[ 114 ,"Undefined","Undefined"],
[ 115 ,"Undefined","Undefined"],
[ 116 ,"Undefined","Undefined"],
[ 117 ,"Undefined","Undefined"],
[ 118 ,"Undefined","Undefined"],
[ 119 ,"Undefined","Undefined"],
[ 120 ,"Chan_Mode_Msg_All_SndOff","[Channel Mode Message] All Sound Off"],
[ 121 ,"Chan_Mode_Msg_Reset_All_Cntrllers","[Channel Mode Message] Reset All Controllers (See MMA RP-015)"],
[ 122 ,"Chan_Mode_Msg_Local_Cntrl_OnOff","[Channel Mode Message] Local Control OnOff"],
[ 123 ,"Chan_Mode_Msg_All_Notes_Off","[Channel Mode Message] All Notes Off"],
[ 124 ,"Chan_Mode_Msg_Omni_Mode_Off","[Channel Mode Message] Omni Mode Off (+ all notes off)"],
[ 125 ,"Chan_Mode_Msg_Omni_Mode_On","[Channel Mode Message] Omni Mode On (+ all notes off)"],
[ 126 ,"Chan_Mode_Msg_Mono_Mode_On","[Channel Mode Message] Mono Mode On (+ poly off, + all notes off)"],
[ 127 ,"Chan_Mode_Msg_Poly_Mode_On","[Channel Mode Message] Poly Mode On (+ mono off, +all notes off)"]
];


decodeManufacturer()
{
  mId = NextNBits(8);
  nBytes=1;
  if (mID!=0) {
		# older 1 byte manufactuerID
		mIDData = Find(midiManufactureId1Byte,mId);
  } else {
	# newer 3 byte manufactuerID
     mID = NextNBits(16);
	 mIDData = Find(midiManufactureId2Byte,mId);
	 nBytes=3;
  }
   AddCell("Manufacturer ID", FormatEx("0x%02X : %s", mId, mIDData[1]),FormatEx("Manufacturer ID is 0x%02X : %s", mId, mIDData[1]),0xD92299);

   return nBytes;
}
   
   
   
set midiManufactureId1Byte = [
[ 0xFF, "Unknown"],
[ 0x00, "ExtendedFormat"],
[ 0x01, "Sequential Circuits*/Dave Smith Instruments"],
[ 0x02, "IDP"],
[ 0x03, "Voyetra/Octave Plateau"],
[ 0x04, "Moog Music*"],
[ 0x05, "Passport Designs*"],
[ 0x06, "Lexicon"],
[ 0x07, "Kurzweil"],
[ 0x08, "Fender"],
[ 0x09, "Gulbransen"],
[ 0x0A, "AKG Acoustics"],
[ 0x0B, "Voyce Music"],
[ 0x0C, "Waveframe*"],
[ 0x0D, "ADA"],
[ 0x0E, "Garfield Electronics*"],
[ 0x0F, "Ensoniq"],
[ 0x10, "Oberheim"],
[ 0x11, "Apple Computer"],
[ 0x12, "Grey Matter*"],
[ 0x13, "Digidesign"],
[ 0x14, "Palm Tree Instruments"],
[ 0x15, "JL Cooper"],
[ 0x16, "Lowrey"],
[ 0x17, "Adams-Smith"],
[ 0x18, "E-mu Systems"],
[ 0x19, "Harmony Systems"],
[ 0x1A, "ART"],
[ 0x1B, "Baldwin"],
[ 0x1C, "Eventide"],
[ 0x1D, "Inventronics"],
[ 0x1E, "Key Concepts"],
[ 0x1F, "Clarity"],
[ 0x20, "Passac"],
[ 0x21, "SIEL"],
[ 0x22, "Synthaxe*"],
[ 0x23, "Stepp*"],
[ 0x24, "Hohner"],
[ 0x25, "Twister"],
[ 0x26, "Solton"],
[ 0x27, "Jellinghaus*"],
[ 0x28, "Southworth"],
[ 0x29, "PPG*"],
[ 0x2A, "JEN"],
[ 0x2B, "Solid State Logic"],
[ 0x2C, "Audio Veritrieb"],
[ 0x2D, "Hinton Instruments"],
[ 0x2E, "Soundtracs"],
[ 0x2F, "Elka"],
[ 0x30, "Dynacord"],
[ 0x33, "Clavia Digital Instruments"],
[ 0x34, "Audio Architecture*"],
[ 0x39, "Soundcraft Electronics"],
[ 0x3B, "Wersi"],
[ 0x3C, "Avab Electronik"],
[ 0x3D, "Digigram"],
[ 0x3E, "Waldorf Electronics"],
[ 0x3F, "Quasimidi*"],
[ 0x40, "Kawai"],
[ 0x41, "Roland UK | Roland US"],
[ 0x42, "Korg"],
[ 0x43, "Yamaha UK | Yamaha Japan"],
[ 0x44, "Casio"],
[ 0x45, "Moridaira"],
[ 0x46, "Kamiya"],
[ 0x47, "Akai"],
[ 0x48, "Japan Victor"],
[ 0x49, "Meisosha"],
[ 0x4A, "Hoshino Gakki"],
[ 0x4B, "Fujitsu Electric"],
[ 0x4C, "Sony"],
[ 0x4D, "Nishin Onpa"],
[ 0x4E, "TEAC"],
[ 0x50, "Matsushita Electric"],
[ 0x51, "Fostex"],
[ 0x52, "Zoom"],
[ 0x53, "Midori Electronics"],
[ 0x54, "Matsushita Communication Industrial"],
[ 0x55, "Suzuki Musical Instrument Mfg."],
[ 0x56, "Fuji Sound Corporation Ltd."],
[ 0x57, "Acoustic Technical Laboratory, Inc."],
[ 0x59, "Faith, Inc."],
[ 0x5A, "Internet Corporation"],
[ 0x5C, "Seekers Co. Ltd."],
[ 0x5F, "SD Card Association"],
[ 0x7D, "Non-commercial"],
[ 0x7E, "Non Real Time"],
[ 0x7F, "Real Time"]
];

set midiManufactureId2Byte = [
[ 0x0001, "Warner New Media"],
[ 0x0007, "Digital Music Corporation"],
[ 0x0008, "IOTA Systems"],
[ 0x0009, "New England Digital*"],
[ 0x000A, "Artisyn"],
[ 0x000B, "IVL Technologies"],
[ 0x000C, "Southern Music Systems"],
[ 0x000D, "Lake Butler Sound Company*"],
[ 0x000E, "Alesis"],
[ 0x0010, "DOD Electronics"],
[ 0x0011, "Studer"],
[ 0x0014, "Perfect Fretworks"],
[ 0x0015, "KAT"],
[ 0x0016, "Opcode*"],
[ 0x0017, "Rane Corporation"],
[ 0x0018, "Spatial Sound/Anadi Inc"],
[ 0x0019, "KMX"],
[ 0x001A, "Allen & Heath Brenell"],
[ 0x001B, "Peavey Electronics"],
[ 0x001C, "360 Systems"],
[ 0x001D, "Spectrum Design & Development"],
[ 0x001E, "Marquis Musi"],
[ 0x001F, "Zeta Systems"],
[ 0x0020, "Axxes"],
[ 0x0021, "Orban"],
[ 0x0024, "KTI"],
[ 0x0025, "Breakaway Technologies"],
[ 0x0026, "CAE"],
[ 0x0029, "Rocktron Corp."],
[ 0x002A, "PianoDisc"],
[ 0x002B, "Cannon Research Corporation"],
[ 0x002D, "Rogers Instrument Corp."],
[ 0x002E, "Blue Sky Logic"],
[ 0x002F, "Encore Electronics"],
[ 0x0030, "Uptown"],
[ 0x0031, "Voce"],
[ 0x0032, "CTI Audio"],
[ 0x0033, "S&S Research"],
[ 0x0034, "Broderbund Software"],
[ 0x0035, "Allen Organ Co."],
[ 0x0037, "Music Quest"],
[ 0x0038, "Aphex"],
[ 0x0039, "Gallien Krueger"],
[ 0x003A, "IBM"],
[ 0x003C, "Hotz Instruments Technologies"],
[ 0x003D, "ETA Lighting"],
[ 0x003E, "NSI Corporation"],
[ 0x003F, "Ad Lib"],
[ 0x0040, "Richmond Sound Design"],
[ 0x0041, "Microsoft"],
[ 0x0042, "The Software Toolworks"],
[ 0x0043, "RJMG/Niche"],
[ 0x0044, "Intone"],
[ 0x0047, "GT Electronics/Groove Tubes"],
[ 0x004E, "Euphonix"],
[ 0x004F, "InterMIDI"],
[ 0x0055, "Lone Wolf*"],
[ 0x0064, "Musonix"],
[ 0x0074, "Ta Horng Musical Inst."],
[ 0x0075, "eTek (formerly Forte)"],
[ 0x0076, "Electrovoice"],
[ 0x0077, "Midisoft"],
[ 0x0078, "Q-Sound Labs"],
[ 0x0079, "Westrex"],
[ 0x007A, "NVidia"],
[ 0x007B, "ESS Technology"],
[ 0x007C, "MediaTrix Peripherals"],
[ 0x007D, "Brooktree"],
[ 0x007E, "Otari"],
[ 0x007F, "Key Electronics"],
[ 0x0101, "Crystalake Multimedia"],
[ 0x0102, "Crystal Semiconductor"],
[ 0x0103, "Rockwell Semiconductor"],
[ 0x0104, "Silicon Graphics"],
[ 0x0105, "Midiman"],
[ 0x0106, "PreSonus"],
[ 0x0108, "Topaz Enterprises"],
[ 0x0109, "Cast Lighting"],
[ 0x010A, "Microsoft Consumer Division"],
[ 0x010C, "Fast Forward Designs"],
[ 0x010D, "Headspace (Igor's Labs)"],
[ 0x010E, "Van Koevering Company"],
[ 0x010F, "Altech Systems"],
[ 0x0110, "S & S Research"],
[ 0x0111, "VLSI Technology"],
[ 0x0112, "Chromatic Research"],
[ 0x0113, "Sapphire"],
[ 0x0114, "IDRC"],
[ 0x0115, "Justonic Tuning"],
[ 0x0116, "TorComp Research, Inc."],
[ 0x0117, "Newtek Inc."],
[ 0x0118, "Sound Sculpture"],
[ 0x0119, "Walker Technical"],
[ 0x011A, "PAVO"],
[ 0x011B, "InVision Interactive"],
[ 0x011C, "T-Square Design"],
[ 0x011D, "Nemesys Music Technology"],
[ 0x011E, "DBX Professional"],
[ 0x011F, "Syndyne Corporation"],
[ 0x0120, "Bitheadz"],
[ 0x0121, "Cakewalk Music Software"],
[ 0x0122, "Staccato Systems"],
[ 0x0123, "National Semiconductor"],
[ 0x0124, "Boom Theory / Adinolfi Alternative Percussion"],
[ 0x0125, "Virtual DSP Corporation"],
[ 0x0126, "Antares Systems"],
[ 0x0127, "Angel Software"],
[ 0x0128, "St. Louis Music"],
[ 0x0129, "Lyrrus, d.b.a. G-VOX"],
[ 0x012A, "Ashley Audio, Inc."],
[ 0x012B, "Vari-Lite, Inc."],
[ 0x012C, "Summit Audio, Inc."],
[ 0x012D, "Aureal Semiconductor, Inc."],
[ 0x012E, "SeaSound, LLC"],
[ 0x012F, "U. S. Robotics"],
[ 0x0130, "Aurisis Research"],
[ 0x0131, "Nearfield Multimedia"],
[ 0x0132, "FM7, Inc."],
[ 0x0133, "Swivel Systems"],
[ 0x0134, "Hyperactive Audio Systems"],
[ 0x0135, "MidiLite (Castle Studios Productions)"],
[ 0x0136, "Radikal Technologies"],
[ 0x0137, "Roger Linn Design"],
[ 0x0138, "TC-Helicon Vocal Technologies"],
[ 0x0139, "Event Electronics"],
[ 0x013A, "Sonic Network, Inc."],
[ 0x013B, "Realtime Music Solutions"],
[ 0x013C, "Apogee Digital"],
[ 0x013D, "Classical Organs, Inc."],
[ 0x013E, "Microtools, Inc."],
[ 0x013F, "Numark Industries"],
[ 0x0140, "Frontier Design Group, LLC"],
[ 0x0141, "Recordare, LLC"],
[ 0x0142, "Starr Labs"],
[ 0x0143, "Voyager Sound, Inc."],
[ 0x0144, "Manifold Labs"],
[ 0x0145, "Aviom, Inc."],
[ 0x0146, "Mixmeister Technology"],
[ 0x0147, "Notation Software"],
[ 0x0148, "Mercurial Communications"],
[ 0x0149, "Wave Arts"],
[ 0x014A, "Logic Sequencing Devices"],
[ 0x014B, "Axess Electronics"],
[ 0x014C, "Muse Research"],
[ 0x014D, "Open Labs"],
[ 0x014E, "Guillemot R&D, Inc."],
[ 0x014F, "Samson Technologies"],
[ 0x0150, "Electronic Theatre Controls, Inc."],
[ 0x2000, "Dream"],
[ 0x2001, "Strand Lighting"],
[ 0x2002, "AMEK Systems & Controls"],
[ 0x2004, "Dr.Bohm/Musician International"],
[ 0x2006, "Trident"],
[ 0x2007, "Real World Design*"],
[ 0x2009, "Yes Technology"],
[ 0x200A, "Audiomatica"],
[ 0x200B, "Bontempi/Farfisa"],
[ 0x200C, "F.B.T. Electronica"],
[ 0x200D, "MIDITEMP"],
[ 0x200E, "Larking Audio"],
[ 0x200F, "Zero 88 Lighting"],
[ 0x2010, "Micon Audio Electronics"],
[ 0x2011, "Forefront Technology"],
[ 0x2013, "Kenton Electronics"],
[ 0x2015, "ADB"],
[ 0x2016, "Jim Marshall Products"],
[ 0x2017, "DDA"],
[ 0x2018, "BSS Audio"],
[ 0x201F, "TC Electronic"],
[ 0x202B, "Medeli Electronics Co."],
[ 0x202C, "Charlie Lab SRL"],
[ 0x202D, "Blue Chip Music Technology"],
[ 0x202E, "BEE OH"],
[ 0x202F, "LG Semiconductor"],
[ 0x2030, "TESI"],
[ 0x2031, "Emagic"],
[ 0x2032, "Behringer"],
[ 0x2033, "Access"],
[ 0x2034, "Synoptic"],
[ 0x2035, "Hanmesoft"],
[ 0x2036, "Terratec Electronic"],
[ 0x2037, "Proel SpA"],
[ 0x2038, "IBK MIDI"],
[ 0x2039, "IRCAM"],
[ 0x203A, "Propellerhead Software"],
[ 0x203B, "Red Sound Systems, Ltd."],
[ 0x203C, "Elektron ESI AB"],
[ 0x203D, "Sintefex Audio"],
[ 0x203E, "MAM (Music and More)"],
[ 0x203F, "Amsaro GmbH"],
[ 0x2040, "CDS Advanced Technology BV"],
[ 0x2041, "Touched By Sound GmbH"],
[ 0x2042, "DSP Arts"],
[ 0x2043, "Phil Rees Music Tech"],
[ 0x2044, "Stamer Musikanlagen GmbH"],
[ 0x2045, "Musical Muntaner S.A., d.b.a. Soundart"],
[ 0x2046, "C-Mexx Software"],
[ 0x2047, "Klavis Technologies"],
[ 0x2048, "Noteheads AB"],
[ 0x2049, "Algorithmix"],
[ 0x204A, "Skrydstrup R&D"],
[ 0x204B, "Professional Audio Company"],
[ 0x204C, "DBTECH/MadWaves"],
[ 0x204D, "Vermona"],
[ 0x204E, "Nokia"],
[ 0x204F, "Wave Idea"],
[ 0x2050, "Hartmann GmbH"],
[ 0x2051, "Lion's Tracs"],
[ 0x2052, "Analogue Systems"],
[ 0x2053, "Focal-JMlab"],
[ 0x2054, "Ringway Electronics (Chang-Zhou) Co. Ltd."],
[ 0x2055, "Digiplug (Faith)"],
[ 0x2056, "Showworks"],
[ 0x2057, "Manikin Electronic"],
[ 0x2058, "1Come Tech"],
[ 0x2059, "Phonic Corp"],
[ 0x205A, "Lake Technology"],
[ 0x205B, "Silansys Technologies"],
[ 0x205C, "Winbond Electronics"],
[ 0x205D, "Cinetix Medien und Interface GmbH"],
[ 0x205E, "A&G Soluzioni Digitali"],
[ 0x205F, "Sequentix Music Systems"],
[ 0x2060, "Oram Pro Audio"],
[ 0x4000, "Crimson Technology Inc."]
];
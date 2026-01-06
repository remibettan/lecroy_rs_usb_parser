#########################################################################################
#########################################################################################
#  Copyright (c) 2004, Computer Access Technology Corp. - All Rights Reserved           #
#                                                                                       #
#  VFTools.inc                                                                          #
#                                                                                       #
#  Verification Script Tools                                                            #
#  version 1.0                                                                          #
#                                                                                       #
#  NOTE: This file contains important script functions and is a supplement to the       #
#        Verification Script Engine API provided by the application.                    #
#                                                                                       #
#        This file SHOULD be included in all verification scripts.                      #
#########################################################################################


%include "VS_constants.inc"


#########################################################################################
#                                   Common Globals                                      #
#########################################################################################

set State       = 0;  # Main state machine input.
                      # This variable may be used for implementation of different kinds of
                      # state machines.
                      
set StartScript = 1;  # indicates that it first run

set str         = ""; # global buffer supposedly for string  values
set val         = 0;  # global buffer supposedly for integer or other values



########################################################################################
#                                   FUNCTIONS                                          #
########################################################################################


####################################################################
#    Common reset actions which should be performed for any        #
#    verification script preparing it for consecutive runs.        # 
#                                                                  #
#  The VSE will call this function for any script after it         #
#  has finished running.                                           #
####################################################################

OnResetScript()
{
    State = 0;
    StartScript = 1;
  
    #ResetScript();
}



########################################################################
#  This function specifies that the verification is passed and the     # 
#  script should complete its work.                                    #
########################################################################

ScriptPassed()
{
    out.Result = _VERIFICATION_PASSED;  
}



########################################################################
#  This function specifies that the verification is failed and the     # 
#  script should complete its work.                                    #
########################################################################

ScriptFailed()
{
    out.Result = _VERIFICATION_FAILED;  
}



########################################################################
#  This function specifies that the verification is done and the       # 
#  script should complete its work.                                    #
########################################################################

ScriptDone()
{
    out.Result = _VERIFICATION_PASSED;  
}


########################################################################
#  This function specifies that the verification is passed and the     # 
#  script should complete its work and it's also has a warning message.#
########################################################################

ScriptPassWithWarning()
{
    out.Result = _VERIFICATION_PASSED_WARNING;  
}


##########################################################################
#  This function specifies that the verification is passed and the       #  
#  script should complete its work and it's also has a message to notice.#
##########################################################################

ScriptPassWithNote()
{
    out.Result = _VERIFICATION_PASSED_WITH_NOTE;
}


########################################################################
#  This function specifies that the verification is Not Applicable (NA)# 
#  and the script should complete its work.                            #
########################################################################

ScriptNotApplicable()
{
    out.Result = _VERIFICATION_NOT_APPLICABLE;  
}


########################################################################
#  This function returns the name of the channel where the current     #
#  event occurred.                                                     #
########################################################################

GetChannelName()
{
    channel_name = 
        select
        {
            in.Channel ==  _USB2     : "_USB2"  ;
            in.Channel ==  _USB2_1   : "_USB2_1";
            in.Channel ==  _USB2_2   : "_USB2_2";
            in.Channel ==  _USB2_3   : "_USB2_3";
            
            in.Channel ==  _USB3_RX  : "_USB3_RX"  ;
            in.Channel ==  _USB3_TX  : "_USB3_TX"  ;
            in.Channel ==  _USB3_RX_1: "_USB3_RX_1";
            in.Channel ==  _USB3_TX_1: "_USB3_TX_1";
                        
            default                  : Format("%d", in.Channel);  #"Unknown";
        };           
        
    return channel_name;    
}




########################################################################
#  This function returns the name of the current event.                #
########################################################################

GetEventName()
{
    event = in.TraceEvent;
        
    event_name = 
    select
    {
        # frame level events...
        event == _USB2_BUS_CONDITION : "_USB2_BUS_CONDITION";
        
        event == _USB2_PACKET        : "_USB2_PACKET";
        event == _USB2_TOKEN         : "_USB2_TOKEN" ;
        event == _USB2_SOF           : "_USB2_SOFS"  ;
        event == _USB2_DATA          : "_USB2_DATA"  ;
        event == _USB2_HSK           : "_USB2_HSK"   ;
        event == _USB2_PRE           : "_USB2_PRE"   ;
        event == _USB2_SPLIT         : "_USB2_SPLIT" ;
        event == _USB2_LPM           : "_USB2_LPM"   ;
        event == _USB2_OTHER         : "_USB2_OTHER" ; 

        
        event == _USB3_PACKET        : "_USB3_PACKET" ;         
                
        event == _USB3_TSEQ          : "_USB3_TSEQ"  ;
        event == _USB3_TS1           : "_USB3_TS1"   ;
        event == _USB3_TS2           : "_USB3_TS2"   ;
        event == _USB3_LFPS          : "_USB3_LFPS"  ;
        event == _USB3_IPS           : "_USB3_IPS"   ;
        event == _USB3_LINK_CMD      : "_USB3_LINK_CMD";
        event == _USB3_SKP_SEQ       : "_USB3_SKP_SEQ";
        event == _USB3_SYMBOL_IDLE   : "_USB3_SYMBOL_IDLE";
        event == _USB3_E_IDLE        : "_USB3_E_IDLE";       
        
        event == _USB3_LMP_PKT       : "_USB3_LMP_PKT";
        event == _USB3_TP_PKT        : "_USB3_TP_PKT";
        event == _USB3_ITP_PKT       : "_USB3_ITP_PKT";
        event == _USB3_DP_PKT        : "_USB3_DP_PKT";
        
        event == _USB3_OTHER_PKT     : "_USB3_OTHER_PKT";
        event == _USB3_BRST	         : "_USB3_BRST"  ;
        event == _USB3_BERC			 : "_USB3_BERC"  ;
        event == _USB3_BCNT			 : "_USB3_BCNT"  ;
        event == _USB3_TERM_STATE	 : "_USB3_TERM_STATE"  ;
        event == _USB3_LTSSM_STATE	 : "_USB3_LTSSM_STATE"  ;
        event == _USB3_CP			 : "_USB3_CP"  ;
        event == _USB3_VBUS_STATE	 : "_USB3_VBUS_STATE"  ;
        event == _USB3_SYNC          : "_USB3_SYNC";
        event == _USB3_SDS           : "_USB3_SDS";

        # SSIC Bus Conditions 
        event == _SSIC_BC            : "SSIC_BUS_CONDITION";
        
        # SSIC LS Packets
        event == _SSIC_LS_UNDEFINED      : "SSIC_UNDEFINED";
        event == _SSIC_LS_FILLER         : "SSIC_FILLER";
        event == _SSIC_LS_RRAP_WR_CMD    : "SSIC_RRAP_WRITE_CMD";
        event == _SSIC_LS_RRAP_WR_RSP    : "SSIC_RRAP_WRITE_RSP";
        event == _SSIC_LS_RRAP_RD_CMD    : "SSIC_RRAP_READ_CMD";
        event == _SSIC_LS_RRAP_RD_RSP    : "SSIC_RRAP_READ_RSP";
        
        # The separate DPH/DPP events are reported only for traces 
        # recorded before USB Suite software version 3.71
        event == _USB3_DPH_PKT       : "_USB3_DPH_PKT";
        event == _USB3_DPP_PKT       : "_USB3_DPP_PKT";
        
        event == _T_SETUP            : "_T_SETUP"    ;
        event == _T_IN               : "_T_IN"       ;
        event == _T_OUT              : "_T_OUT"      ;
        event == _T_OTHER            : "_T_OTHER"    ;        
        
        event == _SPLIT_TRA          : "_SPLIT_TRA"  ;      
        
        event == _X_CONTROL          : "_X_CONTROL"  ;
        event == _X_ISO              : "_X_ISO"      ;
        event == _X_BULK             : "_X_BULK"     ;
        event == _X_INTERRUPT        : "_X_INTERRUPT";
        event == _X_OTHER            : "_X_OTHER"    ;
        
        event == _SCSI_OPR          : "_SCSI_OPR"  ;      
        
        # Add more event descriptions...
        #event == _            : "_";  

        default                : Format( "Unknown(%d)", event );    
    };
    
    return event_name;
}




########################################################################
#  This function outputs the information of the current event.         #
########################################################################

ReportEventInfo()
{
    if(in.Level != _SCSI)
    {  
        report = FormatEx( "TraceEvent:# %04u, Level: %d, Channel: %s, Event: %s, Speed: %s, Dir: %s, Time: %s, Duration: %s",
             in.Index, in.Level, GetChannelName(), GetEventName(), GetSpeedDesc( in.Speed ), 
             GetDirectionDesc( in.Direction ), TimeToText( in.Time ), TimeToText( in.Duration ) );
    }
    else # direction and speed is not reported in SCSI operations
    {
        report = FormatEx( "TraceEvent:# %04u, Level: %d, Channel: %s, Event: %s, Time: %s, Duration: %s",
             in.Index, in.Level, GetChannelName(), GetEventName(), TimeToText( in.Time ), TimeToText( in.Duration ) );
    }
    
    ReportText( report );
    
    if( in.Errors )
        ReportText( Format( "Errors: 0x%08X", in.Errors )  );
}



ReportBusConditionEventInfo()
{
   if( in.TraceEvent == _USB2_BUS_CONDITION )
    {
        bus_condition = 
            select 
            {
                in.BusCondition == _CHIRP_K             : "CHIRP_K";
                in.BusCondition == _CHIRP_J             : "CHIRP_J";
                in.BusCondition == _FS_K_ON_HS          : "FS_K_ON_HS";
                in.BusCondition == _FS_J_ON_HS          : "FS_J_ON_HS";
                in.BusCondition == _SUSPEND             : "SUSPEND";
                in.BusCondition == _RESUME              : "RESUME";
                in.BusCondition == _SE1                 : "SE1";
                in.BusCondition == _SE0                 : "SE0";
                in.BusCondition == _VBUS_VOLTAGE_CHANGE : "VBUS_VOLTAGE_CHANGE";
                                
                default                                 : Format( "Unknown(%d)", in.BusState );                   
            };        
        
        report  = FormatEx( "USB 2 Bus Condition : %s, duration: %u ns", bus_condition, in.BusCondDuration );
        ReportText( report );
    }
}


ReportTraEventInfo()
{
    if( in.Level != _TRA )
        return 0;
        
    # report common Transaction stuff   
    report = FormatEx( "\t*** USB Transaction ***\n" +            
             "\tTraToken  = 0x%02X (%s)\n" +
             "\tAddr      = %d\n" +
             "\tEndp      = %d\n" +
             "\tErrors    = %d (%s)\n" +
             "\tComplete  = %d\n" +
             "\tComplFlag = 0x%02X (%s)\n" +
             "\tXferType  = %d (%s)\n" +
             "\tFrstInXfer= %d\n" +
             "\tLastInXfer= %d\n" +
             "\tSplit     = %d\n",
                     
             in.TraToken, GetPidDesc( in.TraToken ), in.Addr, in.Endp, in.Errors, GetTraErrorDescr( in.Errors ),
             in.Complete, in.TraCompletionFlg, GetPidDesc( in.TraCompletionFlg ), in.XferType, GetXferTypeDescr( in.XferType ),
             in.FirstInXfer, in.LastInXfer, in.Split );
                
    ReportText( report );       
    
    
    if( in.TraceEvent == _T_SETUP )
    {
        report = FormatEx( "\t*** Setup Transaction ***\n" +            
               "\tReqType      = %d\n"      +
               "\tReqRecipient = %d (%s)\n" +
               "\tbRequest     = 0x%02X\n"  +
               "\twValue       = 0x%04X\n"  +
               "\twIndex       = 0x%04X\n"  +
               "\twLength      = %d\n",        
                        
               in.ReqType, in.ReqRecipient, GetReqRecipientDesc( in.ReqRecipient ),
               in.bRequest, in.wValue, in.wIndex, in.wLength );
            
        ReportText( report );
    }
    
    if( in.Split )
    {
        report = FormatEx( "\t*** Split Transaction ***\n" +            
               "\tHubAddr      = %d\n" +
               "\tSC           = %d\n" +
               "\tPort         = %d\n" +
               "\tS            = %d\n" +
               "\tE            = %d\n" +
               "\tET           = %d (%s)\n",
                                            
               in.HubAddr, in.SC, in.Port, in.S, in.E, in.ET, GetSplitETDesc( in.ET ) );
        
        ReportText( report );       
    }       

    
    if( in.XferType == _X_CONTROL )
    {
        # Show Control Transfer-specific information
        if( in.CtrlDirection == 0 ) report = "\tCtrlDirection = 0 (Host->Device)\n";
        else                        report = "\tCtrlDirection = 1 (Device->Host)\n";
                    
        ReportText( report );
    }
    
    if( ( in.Speed != _SS ) && ( in.DataPid != 0 ) )     # USB 2.0              
        ReportText( FormatEx( "\tDataPid   = 0x%02X (%s)\n", in.DataPid, GetPidDesc( in.DataPid ) ) );
    
    if( in.PayloadLength ) # have some data
    {
        ReportText( "----- USB Transaction Data -----\n" );                     
        ShowPayload();
    }       
}


ReportSplitTraEventInfo()
{
    if( in.Level != _SPL_TRA )
        return 0;
        
    # report common Transaction stuff   
    report = FormatEx( "\t*** USB Split Transaction ***\n" +            
                   "\tTraToken   = 0x%02X (%s)\n" +
                   "\tAddr       = %d\n" +
                   "\tEndp       = %d\n" +
                   "\tErrors     = %d (%s)\n" +            
                   "\tXferType   = %d (%s)\n" +
                   "\tFrstInXfer = %d\n" +
                   "\tLastInXfer = %d\n" +            
                   "\tHubAddr    = %d\n" +
                   "\tPort       = %d\n" +
                   "\tTraStalled = %d\n" +
                   "\tTraHalted  = %d\n" +            
                   "\tSplit      = %d\n",
                                
                   in.TraToken, GetPidDesc( in.TraToken ), in.Addr, in.Endp, in.Errors, GetTraErrorDescr( in.Errors ),
                   in.XferType, GetXferTypeDescr( in.XferType ),
                   in.FirstInXfer, in.LastInXfer, in.HubAddr, in.Port, in.TraStalled, in.TraHalted, in.Split );
                
    ReportText( report );
    
    
    if( in.TraceEvent == _T_SETUP )
    {
        report = FormatEx( "\t*** Setup Transaction ***\n" +            
               "\tReqType      = %d\n"      +
               "\tReqRecipient = %d (%s)\n" +
               "\tbRequest     = 0x%02X\n"  +
               "\twValue       = 0x%04X\n"  +
               "\twIndex       = 0x%04X\n"  +
               "\twLength      = %d\n",        
                        
               in.ReqType, in.ReqRecipient, GetReqRecipientDesc( in.ReqRecipient ),
               in.bRequest, in.wValue, in.wIndex, in.wLength );
        
        ReportText( report );
    }    
    
    if( in.XferType == _X_CONTROL )
    {
        # Show Control Transfer-specific information
        if( in.CtrlDirection == 0 ) report = "\tCtrlDirection = 0 (Host->Device)\n";
        else                        report = "\tCtrlDirection = 1 (Device->Host)\n";
                    
        ReportText( report );
    }
    
    if( ( in.Speed != _SS ) && ( in.DataPid != 0 ) )     # USB 2.0              
        ReportText( FormatEx( "\tDataPid   = 0x%02X (%s)\n", in.DataPid, GetPidDesc( in.DataPid ) ) );
    
    if( in.PayloadLength ) # have some data
    {
        ReportText( "----- USB Transaction Data -----\n" );                     
        ShowPayload();
    }       
}

ReportXferEventInfo()
{
    if( in.Level != _XFER )
        return 0;
        
    # report common Transaction stuff   
    report = FormatEx( "\t*** USB Transfer ***\n" +            
                   "\tXferType  = %d (%s)\n" +
                   "\tAddr      = %d\n" +
                   "\tEndp      = %d\n" +
                   "\tError     = %d\n" +
                   "\tCompleted = %d\n" +
                   "\tHalted    = %d\n",  
                                      
                   in.XferType, GetXferTypeDescr( in.XferType ),                   
                   in.Addr, in.Endp, in.Error, in.Completed, in.Halted );
                
    ReportText( report );      
    
    if( in.XferType == _X_CONTROL )
    {
        # Show Control Transfer-specific information            
        ReportText ( "\t*** Control Transfer ***" );        
        
        if( in.CtrlDirection == 0 ) report = "\tCtrlDirection = 0 (Host->Device)\n";
        else                        report = "\tCtrlDirection = 1 (Device->Host)\n";
        
        ReportText( report );
        
        report = FormatEx(
               "\tReqType      = %d\n"      +
               "\tReqRecipient = %d (%s)\n" +
               "\tbRequest     = 0x%02X\n"  +
               "\twValue       = 0x%04X\n"  +
               "\twIndex       = 0x%04X\n"  +
               "\twLength      = %d\n",
                
               in.ReqType, in.ReqRecipient, GetReqRecipientDesc( in.ReqRecipient ),
               in.bRequest, in.wValue, in.wIndex, in.wLength );
                    
        ReportText( report );
    }       
    
    if( in.PayloadLength ) # have some data
    {
        ReportText( "----- USB Transfer Data -----\n" );                    
        ShowPayload();
    }       
}

ReportSCSIEventInfo()
{
    if( in.Level != _SCSI )
        return 0;
        
    # report common Transaction stuff   
    report = FormatEx( "\t*** SCSI Operation ***\n" +            
                   "\tAddr            = %d\n" +
                   "\tTag             = 0x%08X\n" +
                   "\tOperCode        = %d\n" +
                   "\tStatus          = %d\n" +
                   "\t#Xfers          = %d\n" +            
                   "\tResp. time      = %s\n" +
                   "\tLatency         = %s\n" +
                   "\tData-Stat. time = %s\n" +
                   "\tThrpt KB/s      = %d\n" +
                   "\tPld. Bytes      = %d\n",
                                
                   in.Addr, in.Tag, in.OperCode, in.Status, in.XferCount, TimeToText(in.ResponseTime),
                   TimeToText(in.LatencyTime), TimeToText(in.DataToStatusTime), in.Throughput, in.PldBytes );
                
    ReportText( report );           
}

ReportSSICLSPktEventInfo()
{
    if( in.TraceEvent == _SSIC_LS_UNDEFINED )
    {
        report = FormatEx( "{\n\t*** SSIC Low Speed Packet ***\n \tType = Undefined\n \tSymbols Count = %d\n", in.SymbolCount );
    }
    else if( in.TraceEvent == _SSIC_LS_FILLER )
    {
        report = FormatEx( "{\n\t*** SSIC Low Speed Packet ***\n \tType = Filler\n \tSymbols Count = %d\n", in.SymbolCount );
    }
    else if( in.TraceEvent == _SSIC_LS_RRAP_WR_CMD )        
    {
        report = FormatEx( "{\n\t*** SSIC Low Speed Packet ***\n \tType = RRAP Write Command\n" +
        "\tReserve0 = %d\n \tUpper Addres = %d\n \tLower Address = %d\n \tData = %d\n \tReserve1 = %d\n \tParity = %d\n",
        in.Reserve0, in.UpperAddress, in.LowerAddress, in.Data, in.Reserve1, in.Parity );
    }
    else if( in.TraceEvent == _SSIC_LS_RRAP_WR_RSP )
    {
        report = FormatEx( "{\n\t*** SSIC Low Speed Packet ***\n \tType = RRAP Write Response\n" +
        "\tReserve0 = %d\n \tParity = %d\n",
        in.Reserve0, in.Parity );    
    }
    else if( in.TraceEvent == _SSIC_LS_RRAP_RD_CMD )
    {
        report = FormatEx( "{\n\t*** SSIC Low Speed Packet ***\n \tType = RRAP Read Command\n" +
        "\tReserve0 = %d\n \tUpper Addres = %d\n \tLower Address = %d\n \tReserve1 = %d\n \tParity = %d\n",
        in.Reserve0, in.UpperAddress, in.LowerAddress, in.Reserve1, in.Parity );    
    }
    else if( in.TraceEvent == _SSIC_LS_RRAP_RD_RSP )
    {
        report = FormatEx( "{\n\t*** SSIC Low Speed Packet ***\n \tType = RRAP Read Response\n" +
        "\tReserve0 = %d\n \tData = %d\n \tReserve1 = %d\n \tParity = %d\n",
        in.Reserve0, in.Data, in.Reserve1, in.Parity );    
    }
    
    ReportText( report );    

    return 0;
}

ReportUSB2PktEventInfo()
{    
    if( ( in.Channel != _USB2 ) || ( in.Level != _PKT ) || ( in.TraceEvent == _USB2_BUS_CONDITION ) )
        return 0;     
    
    if( in.TraceEvent == _USB2_TOKEN )
    {
        report = FormatEx( "{\n\t*** USB 2 Token Packet ***\n" +
               "\tPid    = 0x%02X (%s)\n" +
               "\tAddr   = %d\n" +
               "\tEndp   = %d\n" +
               "\tCRC5   = 0x%02X\n}",
               in.Pid, GetPidDesc( in.Pid ), in.Addr, in.Endp, in.CRC5 );
                
        ReportText( report );
        return 0;
    }
    
    if( in.TraceEvent == _USB2_SOF )
    {
        report = FormatEx( "*** USB SOF Packet ***, Pid = 0x%02X (%s), Frame: %d, micro_frame: %d,  CRC5   = 0x%02X\n",
                in.Pid, GetPidDesc( in.Pid ), in.FrmNum, in.MicroFrmNum, in.CRC5 );
                
        ReportText( report );
        return 0;
    }
    
    if( in.TraceEvent == _USB2_DATA )
    {
        report  = FormatEx( "*** USB Data Packet ***, Pid = 0x%02X (%s), CRC16 = 0x%04X\n", in.Pid, GetPidDesc( in.Pid ), in.CRC16 );
        ReportText( report );
        
        ShowPayload();          
        return 0;
    }
    
    if( in.TraceEvent == _USB2_HSK )
    {
        report  = FormatEx( "*** USB Handshake Packet ***, Pid = 0x%02X (%s)\n", in.Pid, GetPidDesc( in.Pid ) );
        ReportText( report );
        return 0;
    }
    
    if( in.TraceEvent == _USB2_SPLIT )
    {
        report = FormatEx( "{\n\t*** USB 2 Split Packet ***\n" +
               "\tPid     = 0x%02X (%s)\n" +
               "\tHubAddr = %d\n" +
               "\tSC      = %d\n" +
               "\tPort    = %d\n" +
               "\tS       = %d\n" +
               "\tE       = %d\n" +
               "\tET      = %d\n" +
               "\tCRC5   = 0x%02X\n}",
               in.Pid, GetPidDesc( in.Pid ), in.HubAddr, in.SC, in.Port, in.S, in.E, in.ET, in.CRC5 );
                
        ReportText( report );
        return 0;
    }
    
    if( in.TraceEvent == _USB2_LPM )
    {
        report = FormatEx( "{\n\t*** USB 2 LPM Packet ***\n" +
               "\tPid         = 0x%02X (%s)\n" +
               "\tBESL        = %d\n" +
               "\tbLinkState  = %d\n" +
               "\tbRemoteWake = %d\n" +
               "\tReserved    = %d\n" +            
               "\tCRC5        = 0x%02X\n}",
               in.Pid, GetPidDesc( in.Pid ), in.BESL, in.bLinkState, in.bRemoteWake, in.Reserved, in.CRC5 );
                
        ReportText( report );
        return 0;
    }
}    
        
    
    
GetPidDesc( pid )
{
    if( in.SubPidPacket )
        return GetSubPidDesc( pid );
    
    pid = select
    {        
         pid == PID_OUT   : "OUT";
         pid == PID_IN    : "IN ";
         pid == PID_SOF   : "SOF";
         pid == PID_SETUP : "SETUP";
         pid == PID_DATA0 : "DATA0";
         pid == PID_DATA1 : "DATA1";
         pid == PID_DATA2 : "DATA2";
         pid == PID_MDATA : "MDATA";
         pid == PID_ACK   : "ACK";
         pid == PID_NAK   : "NAK";
         pid == PID_STALL : "STALL";
         pid == PID_NYET  : "NYET";
         pid == PID_PRE   : "PRE";
         pid == PID_ERR   : "ERR";
         pid == PID_SPLIT : "SPLIT";
         pid == PID_PING  : "PING";
         pid == PID_EXT   : "EXT";
         
         default          : Format( "Pid(0x%02X)", pid );
    };
    
    return pid;
}


GetSubPidDesc( pid )
{
    pid = select
    {        
         pid == SUB_PID_LPM : "LPM";
         default            : Format( "Pid(0x%02X)", pid );
    };
    
    return pid;
}


GetSpeedDesc( speed )
{   
    speed_desc = select
    {
        speed == _FS : "_FS";
        speed == _LS : "_LS";
        speed == _HS : "_HS";
        speed == _SS : "_SS";
        speed == _SSP: "_SSP";
        speed == _SSIC_LS: "_SSIC_LS";        
        speed == _SSIC_HS: "_SSIC_HS";        
        
        
        default      : Format( "UNK(%d)", speed );
    };
    
    return speed_desc;
}


GetDirectionDesc( dir )
{   
    dir_desc = select
    {
        dir == _IN   : "_IN"  ;
        dir == _OUT  : "_OUT" ;
        dir == _BOTH : "_BOTH";
        default     : Format( "UNK(%d)", dir );
    };
    
    return dir_desc;
}


GetSplitETDesc( et )
{
    desc = select
    {
        et == SET_CTRL : "CTRL";
        et == SET_ISO  : "ISO";
        et == SET_BULK : "BULK";
        et == SET_INT  : "INT";
        default     : Format( "UNK(%d)", et );
    };  
}


GetTraErrorDescr( error )
{
    err_desc = select
    {
        error == EC_NO_ERROR          : "EC_NO_ERROR"          ;
        error == EC_ERROR_BITSTUFF    : "EC_ERROR_BITSTUFF"    ;
        error == EC_ERROR_CRC5        : "EC_ERROR_CRC5"        ;
        error == EC_ERROR_CRC16       : "EC_ERROR_CRC16"       ;
        error == EC_ERROR_BAD_PKT_LEN : "EC_ERROR_BAD_PKT_LEN" ;
        error == EC_ERROR_TOGGLE      : "EC_ERROR_TOGGLE"      ;
        error == EC_ERROR_TURNAROUND  : "EC_ERROR_TURNAROUND"  ;
        error == EC_ERROR_MOD_8       : "EC_ERROR_MOD_8"       ;
        error == EC_ERROR_OTG         : "EC_ERROR_OTG"         ;
        default                       : Format( "UNK(%d)", error );
    };
    
    return err_desc;
}


GetXferTypeDescr( xfer_type )
{
    xfer_desc = select
    {
        xfer_type == _X_CONTROL  : "_X_CONTROL"  ;
        xfer_type == _X_ISO      : "_X_ISO"      ;
        xfer_type == _X_BULK     : "_X_BULK"     ;
        xfer_type == _X_INTERRUPT: "_X_INTERRUPT";
        xfer_type == _X_OTHER    : "_X_OTHER"    ;
        default                  : Format( "UNK(%d)", xfer_type );
    };
    
    return xfer_desc;
}


GetReqRecipientDesc( recipient )
{
    desc = select
    {
        recipient == RCP_DEVICE    : "RCP_DEVICE   ";
        recipient == RCP_INTERFACE : "RCP_INTERFACE";
        recipient == RCP_ENDPOINT  : "RCP_ENDPOINT ";
        recipient == RCP_OTHER     : "RCP_OTHER    ";
        recipient == RCP_PORT      : "RCP_PORT     ";
        recipient == RCP_RPIPE     : "RCP_RPIPE    ";
            
        default                    : Format( "UNK(%d)", recipient );
    };
    
    return desc;
    
}

###############################################################################
#                        SSIC Bus Condition report functions                  #
###############################################################################

GetMPHYStateName( state )
{
    if( state == _MPHY_DIF_N )
        return "DIF-N";
    else if( state == _MPHY_DIF_P )
        return "DIF-P";        
    else if( state == _MPHY_DIF_Z )
        return "DIF-Z";        

    return "Unknown";
}

ReportSSICBCEventInfo()
{
    if( in.TraceEvent == _SSIC_BC )
    {
        report  = FormatEx( "\n\t*** SSIC Bus Condition Packet ***\n" + 
                            "\tSSIC Event Type   = %d\n" +
                            "\tTotal Duration    = %d\n"  +
                            "\tMPHY States Count = %d\n"  +
                            "\tLane Index        = %d\n"  +
                            "\tMPHY State0 Type     = %s\n"  +
                            "\tMPHY State0 Duration = %d\n"  ,
                            in.SSICEventType, in.TotalDuration, in.MPHYStateCount, in.LaneIndex, GetMPHYStateName( in.MPHYStateType0 ), in.MPHYStateDuration0 );
        
        if( in.MPHYStateCount > 1 )
        {
            report1  = FormatEx( "\tMPHY State1 Type     = %s\n"  +
                                 "\tMPHY State1 Duration = %d\n"  ,
                                 GetMPHYStateName( in.MPHYStateType1 ), in.MPHYStateDuration1 );                    
                    
            report = report + report1;
        }
   
        ReportText( report );
    }
}

###############################################################################
#                        USB 3.0 report functions                             #
###############################################################################

ReportUsb3TSEventInfo()
{
    if( in.TraceEvent == _USB3_TSEQ )
    {
        if( in.Speed == _SSP )
        {
            report  = FormatEx( "{\n\t*** USB 3 TSEQ Packet ***\n" + 
                                "\tCount             = %d\n}" +
                                "\tHasDCBalance      = %d\n"  +
                                "\tIsByte14DCBalance = %d\n"  +
                                "\tIsByte15DCBalance = %d\n",
                                in.Count, in.HasDCBalance, in.IsByte14DCBalance, in.IsByte15DCBalance );                    
        }
        else
        {
            report  = FormatEx( "{\n\t*** USB 3 TSEQ Packet ***\n" + 
                    "\tCount        = %d\n}", 
                    in.Count );
        }
        
        ReportText( report );
    }    
    else if( in.TraceEvent == _USB3_TS1 )
    {
        if( in.Speed == _SSP )
        {
            report  = FormatEx( "{\n\t*** USB 3 TS1 Packet ***\n" +
                "\tCount      = %d\n" +
                "\tReset      = %d\n" +
                "\tSSDisable  = %d\n" +
                "\tLoopback   = %d\n" +
                "\tScrDisable = %d\n" +
                "\tRsvd       = %d\n" +            
                "\tLnkFunctionality  = 0x%02X\n}"   +
                "\tHasDCBalance      = %d\n"        +
                "\tIsByte14DCBalance = %d\n"        + 
                "\tIsByte15DCBalance = %d\n",                
                in.Count, in.Reset, in.SSDisable, in.Loopback, in.ScrDisable, in.Rsvd, in.LnkFunctionality, in.HasDCBalance, in.IsByte14DCBalance, in.IsByte15DCBalance );
        }
        else
        {
            report  = FormatEx( "{\n\t*** USB 3 TS1 Packet ***\n" +
                "\tCount      = %d\n" +
                "\tReset      = %d\n" +
                "\tSSDisable  = %d\n" +
                "\tLoopback   = %d\n" +
                "\tScrDisable = %d\n" +
                "\tRsvd       = %d\n" +            
                "\tLnkFunctionality = 0x%02X\n}",
                
                    in.Count, in.Reset, in.SSDisable, in.Loopback, in.ScrDisable, in.Rsvd, in.LnkFunctionality );            
        }
        
        ReportText( report );   
    }
    else if( in.TraceEvent == _USB3_TS2 )
    {
        if( in.Speed == _SSP )
        {
            report  = FormatEx( "{\n\t*** USB 3 TS2 Packet ***\n" +
                "\tCount      = %d\n" +
                "\tReset      = %d\n" +
                "\tSSDisable  = %d\n" +
                "\tLoopback   = %d\n" +
                "\tScrDisable = %d\n" +
                "\tRsvd       = %d\n" +            
                "\tLnkFunctionality  = 0x%02X\n}"   +
                "\tHasDCBalance      = %d\n"        +
                "\tIsByte14DCBalance = %d\n"        + 
                "\tIsByte15DCBalance = %d\n",                
                in.Count, in.Reset, in.SSDisable, in.Loopback, in.ScrDisable, in.Rsvd, in.LnkFunctionality, in.HasDCBalance, in.IsByte14DCBalance, in.IsByte15DCBalance );
        }
        else
        {    
            report  = FormatEx( "{\n\t*** USB 3 TS2 Packet ***\n" +
                "\tCount      = %d\n" +
                "\tReset      = %d\n" +
                "\tSSDisable  = %d\n" +
                "\tLoopback   = %d\n" +
                "\tScrDisable = %d\n" +
                "\tRsvd       = %d\n" +            
                "\tLnkFunctionality = 0x%02X\n}",
                    in.Count, in.Reset, in.SSDisable, in.Loopback, in.ScrDisable, in.Rsvd, in.LnkFunctionality );
        }
        
        ReportText( report );   
    }    
}


ReportLFPSEventInfo()
{
     if( in.TraceEvent == _USB3_LFPS )  
     {
        report  = FormatEx( "{\n\t*** USB 3 LFPS Packet ***\n" +
            "\tType       = 0x%02X (%s)\n" +
            "\tDuration   = %u ns\n}",
                 in.Type, GetLfpsDesc( in.Type ), in.Duration );
                
        ReportText( report );           
     }   
}

ReportEIdleEventInfo()
{
     if( in.TraceEvent == _USB3_E_IDLE )  
     {
        report  = FormatEx( "{\n\t*** USB 3 Electrical Idle Packet ***\n" +     
            "\tDuration   = %u ns\n}", in.Duration );
                
        ReportText( report );
     }   
}


# Returns text representation of running disparity value:
# 0 - negative, 1 - positive
GetRDDescription( rd )
{
   if( rd == 0 ) return "Negative";
   if( rd == 1 ) return "Positive";
   return "Unknown";
}

GetLfpsDesc( type )
{   
    lfps_desc = select
    {
        type == _LFPS_ILLEGAL           : "LFPS_ILLEGAL";
        type == _LFPS_RESET             : "LFPS_RESET";
        type == _LFPS_PING              : "LFPS_PING";
        type == _LFPS_POLLING           : "LFPS_POLLING";
        type == _LFPS_EXIT_U1           : "LFPS_EXIT_U1";
        type == _LFPS_EXIT_U2_LB        : "LFPS_EXIT_U2_LB";
        type == _LFPS_WAKE_U3           : "LFPS_WAKE_U3";
        type == _LFPS_LBPM_LFPS0        : "LFPS_LBPM_LFPS0";
        type == _LFPS_LBPM_LFPS1        : "LFPS_LBPM_LFPS1";
        type == _LFPS_LBPM_DELIMITER    : "LFPS_LBPM_DELIMITER";
                
        default      : Format( "UNK(%d)", type );
    };
    
    return lfps_desc;
}

ReportIPSEventInfo( index )
{
    if( in.TraceEvent == _USB3_IPS )
    {
        if( index == null )
            index = 0;
        
        report  = FormatEx( "{\n\t*** USB 3 IPS Packet ***\n" +
                             "\tNumOfSymbols = %u\n}", in.NumOfSymbols );
                  
        ReportText( report );
      
        if( in.Speed == _SS )
        {
             report = FormatEx( "\n\tSymbol info (index: %u)\n" +
                 "\tSymbol     = 0x%03X\n" +
                 "\tHasRDError = %u\n" +
                 "\tIsInvalid  = %u\n" +
                 "\tRDisparity = %u(%s)\n",
                 index, GetSymbol(index), SymbolHasRDError( index ), IsInvalidSymbol( index ), 
                 GetSymbolRD( index ), GetRDDescription( index ) );
                
             ReportText( report );       
        }
    }
}

GetUsb3LnkCmdDesc( lnk_cmd )
{
    if( in.Speed == _SS )
    {
        lnk_cmd_desc = select
        { 
            lnk_cmd == LGOOD_0 : "LGOOD_0";
            lnk_cmd == LGOOD_1 : "LGOOD_1";
            lnk_cmd == LGOOD_2 : "LGOOD_2";
            lnk_cmd == LGOOD_3 : "LGOOD_3";
            lnk_cmd == LGOOD_4 : "LGOOD_4";
            lnk_cmd == LGOOD_5 : "LGOOD_5";
            lnk_cmd == LGOOD_6 : "LGOOD_6";
            lnk_cmd == LGOOD_7 : "LGOOD_7";
            lnk_cmd == LBAD    : "LBAD"   ;
            lnk_cmd == LCRD_A  : "LCRD_A" ;
            lnk_cmd == LCRD_B  : "LCRD_B" ;
            lnk_cmd == LCRD_C  : "LCRD_C" ;
            lnk_cmd == LCRD_D  : "LCRD_D" ;
            lnk_cmd == LRTY    : "LRTY"   ;
            lnk_cmd == LGO_U1  : "LGO_U1" ;
            lnk_cmd == LGO_U2  : "LGO_U2" ;
            lnk_cmd == LGO_U3  : "LGO_U3" ;
            lnk_cmd == LAU     : "LAU"    ;
            lnk_cmd == LXU     : "LXU"    ;
            lnk_cmd == LPMA    : "LPMA"   ;
            lnk_cmd == LUP     : "LUP"    ;
            lnk_cmd == LDN     : "LDN"    ; 
                  
            default            : Format( "UNK(%d)", lnk_cmd );
        };        
    }          
    else
    {
        lnk_cmd_desc = select
        { 
            lnk_cmd == LGOOD_0 : "LGOOD_0";
            lnk_cmd == LGOOD_1 : "LGOOD_1";
            lnk_cmd == LGOOD_2 : "LGOOD_2";
            lnk_cmd == LGOOD_3 : "LGOOD_3";
            lnk_cmd == LGOOD_4 : "LGOOD_4";
            lnk_cmd == LGOOD_5 : "LGOOD_5";
            lnk_cmd == LGOOD_6 : "LGOOD_6";
            lnk_cmd == LGOOD_7 : "LGOOD_7";
            lnk_cmd == LGOOD_8 : "LGOOD_8";
            lnk_cmd == LGOOD_9 : "LGOOD_9";
            lnk_cmd == LGOOD_10: "LGOOD_10";
            lnk_cmd == LGOOD_11: "LGOOD_11";
            lnk_cmd == LGOOD_12: "LGOOD_12";
            lnk_cmd == LGOOD_13: "LGOOD_13";
            lnk_cmd == LGOOD_14: "LGOOD_14";
            lnk_cmd == LGOOD_15: "LGOOD_15";
            lnk_cmd == LBAD    : "LBAD";
            lnk_cmd == LCRD_A  : "LCRD1_A";
            lnk_cmd == LCRD_B  : "LCRD1_B";
            lnk_cmd == LCRD_C  : "LCRD1_C";
            lnk_cmd == LCRD_D  : "LCRD1_D";
            lnk_cmd == LRTY    : "LRTY"   ;
            lnk_cmd == LGO_U1  : "LGO_U1" ;
            lnk_cmd == LGO_U2  : "LGO_U2" ;
            lnk_cmd == LGO_U3  : "LGO_U3" ;
            lnk_cmd == LAU     : "LAU"    ;
            lnk_cmd == LXU     : "LXU"    ;
            lnk_cmd == LPMA    : "LPMA"   ;
            lnk_cmd == LUP     : "LUP"    ;
            lnk_cmd == LDN     : "LDN"    ; 
            lnk_cmd == LCRD2_A : "LCRD2_A";
            lnk_cmd == LCRD2_B : "LCRD2_B";
            lnk_cmd == LCRD2_C : "LCRD2_C";
            lnk_cmd == LCRD2_D : "LCRD2_D";
                  
            default            : Format( "UNK(%d)", lnk_cmd );
        };            
    }
    
    return lnk_cmd_desc;
}         

ReportLnkCmdEventInfo()
{
    if( in.TraceEvent == _USB3_LINK_CMD )  
    {
        report = FormatEx( "{\tLink Command = %u (%s) }\n",
               in.LnkCmd, GetUsb3LnkCmdDesc( in.LnkCmd ) );
               
        ReportText( report );
    }   
}

GetUsb3LmpSubTypeDesc( subtype )
{
    st_desc = select
    { 
        subtype == LMP_SET_LNK_FUNC      : "LMP_SET_LNK_FUNC"     ;
        subtype == LMP_U2_INACTIVITY_TMT : "LMP_U2_INACTIVITY_TMT";
        subtype == LMP_VNDR_DEV_TST      : "LMP_VNDR_DEV_TST"     ;
        subtype == LMP_PRT_CAPABILITY    : "LMP_PRT_CAPABILITY"   ;
        subtype == LMP_PRT_CFG           : "LMP_PRT_CFG"          ;
        subtype == LMP_PRT_CFG_ACK       : "LMP_PRT_CFG_ACK"      ;
        subtype == USB3_LMP_LDM          : "LMP_LDM"              ;
      
        default                          : Format( "RSVD(%d)", subtype );
    };        
          
    return st_desc;
  
}

ReportLMPEventInfo()
{
    if( in.TraceEvent == _USB3_LMP_PKT )    
    {
        report  = FormatEx( "{\tSubType  = %u (%s) }\n",
                in.SubType, GetUsb3LmpSubTypeDesc( in.SubType ) );
               
        ReportText( report );
    }   
}


GetUsb3TpSubTypeDesc( subtype )
{
    st_desc = select
    {         
        subtype == TP_ACK              : "TP_ACK"             ;
        subtype == TP_NRDY             : "TP_NRDY"            ;
        subtype == TP_ERDY             : "TP_ERDY"            ;
        subtype == TP_STATUS           : "TP_STATUS"          ;
        subtype == TP_STALL            : "TP_STALL "          ;
        subtype == TP_DEV_NOTIFICATION : "TP_DEV_NOTIFICATION";
        subtype == TP_PING             : "TP_PING"            ;
        subtype == TP_PING_RESPONSE    : "TP_PING_RESPONSE"   ;
      
        default                        : Format( "RSVD(%d)", subtype );
    };        
          
    return st_desc;  
}

GetTPDirDesc( dir )
{
    if( dir == 1 ) 
        return "IN";
  
    return "OUT";
}


ReportTPEventInfo()
{
    if( in.TraceEvent == _USB3_TP_PKT )  
    {
        report  = FormatEx( "\tSubType  = %u (%s)\n" +
                            "\tAddr     = %u\n" +
                            "\tEndp     = %u\n" +
                            "\tDir      = %u (%s)\n" +
                            "\tStreamID = 0x%04X\n",                                      
                            in.SubType, GetUsb3TpSubTypeDesc( in.SubType ),
                            in.Addr, in.Endp, in.Dir, GetTPDirDesc( in.Dir ), in.StreamID );     
                
        ReportText( report );
    }   
}

ReportDPEventInfo()
{
    if( in.TraceEvent == _USB3_DP_PKT )
    {
        report = FormatEx( "\tAddr       = %u\n" +
                           "\tEndp       = %u\n" +
                           "\tDir        = %u (%s)\n" +
                           "\tSeqN       = %u\n" +
                           "\tDataLength = %u\n" +
                           "\tStreamID   = 0x%04X\n",
                           in.Addr, in.Endp, in.Dir, GetTPDirDesc( in.Dir ), in.SeqN, in.DataLength, in.StreamID );    
               
        ReportText( report );
        
        report = FormatEx( "\tCRC32 = 0x%08X\n", in.CRC32 );
        ReportText( report );
      
        ShowPayload();   
    }
}

# The separate DPH/DPP events are reported only for traces 
# recorded before USB Suite software version 3.71
ReportDPHEventInfo()
{
    if( in.TraceEvent == _USB3_DPH_PKT )
    {
        report = FormatEx( "\tAddr       = %u\n" +
                           "\tEndp       = %u\n" +
                           "\tDir        = %u (%s)\n" +
                           "\tSeqN       = %u\n" +
                           "\tDataLength = %u\n" +
                           "\tStreamID   = 0x%04X\n",
                           in.Addr, in.Endp, in.Dir, GetTPDirDesc( in.Dir ), in.SeqN, in.DataLength, in.StreamID );    
               
        ReportText( report );
    }
}

# The separate DPH/DPP events are reported only for traces 
# recorded before USB Suite software version 3.71
ReportDPPEventInfo()
{
    if( in.TraceEvent == _USB3_DPP_PKT )
    {
        report = FormatEx( "\tCRC32 = 0x%08X\n", in.CRC32 );
        ReportText( report );
      
        ShowPayload();   
    }
}


ReportITPEventInfo()
{
    if( in.TraceEvent == _USB3_ITP_PKT ) 
    {
        report = FormatEx( "\tBusICounter = %u\n" +
                           "\tDelta       = %u\n" +
                           "\tBusIAdjCtrl = %u\n",                                                           
                           in.BusICounter, in.Delta, in.BusIAdjCtrl );      
               
        ReportText( report );
    }   
}


ReportSKPSeqEventInfo()
{
    if( in.TraceEvent == _USB3_SKP_SEQ )   
    {
        if( in.Speed == _SS )
        {
            report  = FormatEx( "{\tSKP Count = %u }\n", in.Count );                
        }
        else
        {
            report  = FormatEx( "{\tSKP Count = %u }\n" +
                                "\tLFSR       = %u\n",
                                in.Count, in.Lfsr );                
        }
        
        ReportText( report );
    }   
}


ReportBRSTEventInfo()
{
    if ( in.TraceEvent == _USB3_BRST )
    {
        report = FormatEx( "{\n\t*** USB 3 BRST Packet ***\n}" );
        
        ReportText( report );
        return 0;
    }
}


ReportBERCEventInfo()
{
    if ( in.TraceEvent == _USB3_BERC )
    {
        report = FormatEx( "{\n\t*** USB 3 BERC Packet ***\n}" );
        
        ReportText( report );
        return 0;
    }
}


ReportBCNTEventInfo()
{
    if ( in.TraceEvent == _USB3_BCNT )
    {
        report = FormatEx( "{\n\t*** USB 3 BCNT Packet ***\n" + 
                            "\tErrorCount = %d\n}", in.ErrorCount );
        
        ReportText( report );
        return 0;
    }
}

ReportSYNCEventInfo()
{
    if ( in.TraceEvent == _USB3_SYNC )
    {
        report = FormatEx( "{\n\t*** USB 3 SYNC Packet ***\n}" );
        
        ReportText( report );
        return 0;
    }
}

ReportSDSEventInfo()
{
    if ( in.TraceEvent == _USB3_SDS )
    {
        report = FormatEx( "{\n\t*** USB 3 SDS Packet ***\n}" );
        
        ReportText( report );
        return 0;
    }
}

ShowPayload()
{            
    GetNBits( in.Payload, 0, 0 );
    str = "Payload";        
    str += Format( "( %d byte(s) ):\n", in.PayloadLength );
    
    
    for( i = 0; i < in.PayloadLength; i++ )
    {
        val = NextNBits(8);
        str += Format( "%02X ", val );
        
        if( ((i + 1) % 20) == 0 )
            str += "\n";
    }  
    
    str += "\n";
    
    ReportText( str ); 
}

###############################################################################
#   This function extracts a bit - the 'bit_needed' from source.              #
#     --> Function copied from CATCScriptAPI.inc [GetBit()]                   #
###############################################################################

GetOneBit( bit_needed, source )
{   
    return ( (source >> bit_needed) & 0x01 );
}


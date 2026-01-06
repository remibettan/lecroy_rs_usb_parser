#
#  Copyright (c) 1998 - 2009, Computer Access Technology Corp. - All Rights Reserved
#
#   VS_constants.inc
#
#   This file contains common Verificatiton Script constants.
#
#
#   Add your own additional definitions if you need.
#
#######################################################################################

%include "VSUser_globals.inc"

# Time constants
const MICRO_SECS    = 1000;    # nanosecs per microsecond
const MILLI_SECS    = 1000000; # nanosecs per millisecond


# USB 2.0 PID values
const PID_OUT   = 0x87;
const PID_IN    = 0x96;
const PID_SOF   = 0xA5;
const PID_SETUP = 0xB4;
const PID_DATA0 = 0xC3;
const PID_DATA1 = 0xD2;
const PID_DATA2 = 0xE1;
const PID_MDATA = 0xF0;
const PID_ACK   = 0x4B;
const PID_NAK   = 0x5A;
const PID_STALL = 0x78;
const PID_NYET  = 0x69;
const PID_PRE   = 0x3C;
const PID_ERR   = 0x3C;
const PID_SPLIT = 0x1E;
const PID_PING  = 0x2D;
const PID_EXT   = 0x0F;

# USB 2.0 Sub PID values
const SUB_PID_LPM = 0xC3;

#USB Packet errors flags
#
# USB 2 packet error
const USB_PID_ERROR               = 0x00000002;
const USB_CRC5_ERROR              = 0x00000004;
const USB_CRC16_ERROR             = 0x00000008;
const USB_PACKETLEN_ERROR         = 0x00000010;
const USB_BIT_STUFF_ERROR         = 0x00000020;
const USB_EOP_ERROR               = 0x00000040;
const USB_BABBLE_START_ERROR      = 0x00000080;
const USB_BABBLE_END_ERROR        = 0x00000100;
const USB_FRAME_LENGTH_ERROR      = 0x00000200;
const USB_HANDSHAKE_TIMEOUT_ERROR = 0x00000400;
const USB_INTERNAL_ERROR          = 0x00000800;
const USB_DATA_TOGGLE_ERROR       = 0x00001000;
const USB_MICROFRAME_ERROR        = 0x00002000;
const USB_MOD_8_ERROR             = 0x00004000;
const USB_OTG_ERROR               = 0x00008000;
                                  
# USB 3 packet error flags                                            
const USB3_CRC5_ERROR		          = 0x00010000; 
const USB3_CRC16_ERROR		        = 0x00020000;
const USB3_CRC32_ERROR		        = 0x00040000;
const USB3_DISPARITY_ERROR        = 0x00080000;
const USB3_10BIT_SYMBOL_ERROR     = 0x00100000;
const USB3_UNKNOWN_PACKET_IPS     = 0x00200000;
const USB3_FRAMING_SYMBOL_ERROR   = 0x00400000;
const USB3_LC_DATA_SYMBOL_ERROR   = 0x00800000;
const USB3_BAD_HEADER_PKT_LENGTH  = 0x01000000;
const USB3_BAD_DATA_LENGTH_FIELD  = 0x02000000;
const USB3_SKP_SYMBOL_ERROR       = 0x04000000;
const USB3_DIR_CTRL_ENDP          = 0x08000000;


										 
#USB Transaction Error codes
const EC_NO_ERROR           = 0;
const EC_ERROR_BITSTUFF     = 1;
const EC_ERROR_CRC5         = 2;
const EC_ERROR_CRC16        = 3;
const EC_ERROR_BAD_PKT_LEN  = 4;
const EC_ERROR_TOGGLE       = 5;
const EC_ERROR_TURNAROUND   = 6;
const EC_ERROR_MOD_8        = 7;
const EC_ERROR_OTG          = 8;

#USB 3.0 Link Command indexes
const LGOOD_0 = 0;
const LGOOD_1 = 1;
const LGOOD_2 = 2;
const LGOOD_3 = 3;
const LGOOD_4 = 4;
const LGOOD_5 = 5;
const LGOOD_6 = 6;
const LGOOD_7 = 7;
const LBAD    = 8;
const LCRD_A  = 9;
const LCRD_B  = 10;
const LCRD_C  = 11;
const LCRD_D  = 12;
const LRTY    = 13;
const LGO_U1  = 14;
const LGO_U2  = 15;
const LGO_U3  = 16;
const LAU     = 17;
const LXU     = 18;
const LPMA    = 19;
const LUP     = 20;
const LDN     = 23;
const LGOOD_8  = 24;
const LGOOD_9  = 25;
const LGOOD_10 = 26;
const LGOOD_11 = 27;
const LGOOD_12 = 28;
const LGOOD_13 = 29;
const LGOOD_14 = 30;
const LGOOD_15 = 31;
const LCRD2_A  = 32;
const LCRD2_B  = 33;
const LCRD2_C  = 34;
const LCRD2_D  = 35;


# USB 3.0 LMP subtype constants
const LMP_SET_LNK_FUNC      = 0b001;
const LMP_U2_INACTIVITY_TMT = 0b010;
const LMP_VNDR_DEV_TST      = 0b011;
const LMP_PRT_CAPABILITY    = 0b100;
const LMP_PRT_CFG           = 0b101;
const LMP_PRT_CFG_ACK       = 0b110;
const USB3_LMP_LDM          = 0b111;

# USB 3.0 TP subtype constants
const TP_ACK                = 0b0001;
const TP_NRDY               = 0b0010;
const TP_ERDY               = 0b0011;
const TP_STATUS             = 0b0100;
const TP_STALL              = 0b0101;
const TP_DEV_NOTIFICATION   = 0b0110;
const TP_PING               = 0b0111;
const TP_PING_RESPONSE      = 0b1000;

const TP_OUT = 0;
const TP_IN  = 1;



# USB Setup Transaction Recipients
const RCP_DEVICE    = 0;
const RCP_INTERFACE = 1;
const RCP_ENDPOINT  = 2;
const RCP_OTHER     = 3;
const RCP_PORT      = 4;
const RCP_RPIPE     = 5;

# Split Transfer types
const SET_CTRL = 0;
const SET_ISO  = 1;
const SET_BULK = 2;
const SET_INT  = 3;
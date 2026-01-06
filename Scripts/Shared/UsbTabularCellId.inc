#
#  Copyright (C) 2009 LeCroy Corporation
#
#  TabularColId.inc
#
#  Usb Tabular Column Id Definition Constants
################################################################################

const TABULAR_SCRIPT_COLUMN_ID_NONE             =  0;
const TABULAR_SCRIPT_COLUMN_ID_TYPE             =  100;
const TABULAR_SCRIPT_COLUMN_ID_SUBTYPE          =  101;

const TABULAR_SCRIPT_CONTAINER_CELL_ID_NONE     =  0;
const TABULAR_SCRIPT_CONTAINER_CELL_ID_MISC     =  1001;





#------------------------------------------------------------------------------
#                               Cell Ids
#------------------------------------------------------------------------------


################################################################################
# Range 1000-1100                  Standard Descriptor Cell ids   
################################################################################
const CELL_REQUEST   = 1000;
const CELL_WVALUE    = 1001;
const CELL_HBWVALUE  = 1002;
const CELL_LBWVALUE  = 1003;


################################################################################
# Range 1100-1200                  AssociationFrameworks Cell ids   
################################################################################
const CELL_CBAF_REQUEST                     = 1100;
const CELL_CBAF_WVALUE                      = 1101;

################################################################################
# Range 1200-1300                  ATAPI Cell ids   
################################################################################
const CELL_ATAPI_OPERATION_CODE             = 1200;
const CELL_ATAPI_STATUS                     = 1201;


################################################################################
# Range 1300-1400                  AudioClass Cell ids   
################################################################################
const CELL_AUDIO_CONTROL_SELECTOR           = 1300;
const CELL_AUDIO_ORIGINATOR                 = 1301;

################################################################################
# Range 1400-1500                  Communications Cell ids   
################################################################################
const CELL_COMM_BMTYPE                      = 1400;
const CELL_COMM_LENGTH                      = 1401;
const CELL_COMM_COMMAND                     = 1402;    
const CELL_COMM_WRAPPER_SIZE                = 1403;    
const CELL_COMM_CMD_TYPE                    = 1404;    

################################################################################
# Range 1500-1600                  ContentSecurity Cell ids   
################################################################################
const CELL_CSDC_NOTIFICATION                = 1500;
const CELL_CSDC_BDATA                       = 1501;

################################################################################
# Range 1600-1700                  HID Cell ids   
################################################################################
const CELL_HID_KEYBOARD                     = 1600;   
const CELL_HID_MOUSE                        = 1601;   

################################################################################
# Range 1700-1800                  HTTP Cell ids   
################################################################################
const CELL_TCP_SEQUENCE_NUMBER              = 1700;   
const CELL_TCP_SORT_PORT                    = 1701;  
const CELL_HTTP_PROTOCOL                    = 1702;   
const CELL_HTTP_VERSION                     = 1703;    


################################################################################
# Range 1800-1900                  HubClass Cell ids   
################################################################################
const CELL_HUB_CHANGE_ENDPOINT              = 1800;   


################################################################################
# Range 1900-2000                  IP Cell ids   
################################################################################
const CELL_IP_PROTOCOL                      = 1900;   
const CELL_IP_VERSION                       = 1901;   

################################################################################
# Range 2000-2100                  MassStorageClass Cell ids   
################################################################################
const MS_CELL_STATUS                        = 2000;
const MS_UASP_IDENTIFIER                    = 2001;
const MS_UASP_TSK_MGM                       = 2002;
const MS_UASP_RESPONSE_CODE                 = 2003;
const MS_UASP_STATUS                        = 2004;
const MS_UFI_SENSE                          = 2005;
const MS_GET_MAX_LUN                        = 2006;
const MS_MAX_LUN                            = 2007;

################################################################################
# Range 2100-2200                  IrDA_Bridge Cell ids   
################################################################################
# ----

################################################################################
# Range 2200-2300                  PersonalHealthcare Cell ids   
################################################################################
const CELL_PHC_A_SIGNATURE  = 2200;


################################################################################
# Range 2300-2400                  Printer Cell ids   
################################################################################
# ----

################################################################################
# Range 2400-2500                  RNDIS Cell ids   
################################################################################
const CELL_RNDIS_MSG_TYPE  = 2400;



################################################################################
# Range 2500-2600                  SmartCard Cell ids   
################################################################################
const CELL_SMART_CARD_MESSAGE_TYPE          = 2500;
const CELL_SMART_CARD_SEQ                   = 2501;

################################################################################
# Range 2600-2700                  StillImageClass Cell ids   
################################################################################
const CELL_STILL_IMAGE_CON_TYPE             = 2600;
const CELL_STILL_IMAGE_CODE                 = 2601;   
const CELL_STILL_IMAGE_STANDARD_VERSION     = 2602;   
const CELL_STILL_IMAGE_STORAGE_ID           = 2603;   
const CELL_STILL_IMAGE_STORAGE_TYPE         = 2604;   
const CELL_STILL_IMAGE_OBJ_HAN_TOT          = 2605;   
const CELL_STILL_IMAGE_DEVICE_PROP_CODE     = 2606;   
const CELL_STILL_IMAGE_OBJ_PROP_VALUE       = 2607;   
const CELL_STILL_IMAGE_NUM_ELEMENTS         = 2608;   
const CELL_STILL_IMAGE_REQUEST              = 2609;   


################################################################################
# Range 2700-2800                  VideoClass Cell ids   
################################################################################
const CELL_VIDEO_REQUEST                    = 2700;   
const CELL_VIDEO_CONTROLL_SELECTOR          = 2701;   
const CELL_VIDEO_STATUS_TYPE                = 2702; 
const CELL_VIDEO_EVENT                      = 2703;   


################################################################################
# Range 2800-2900                  Virtual Cell ids   
################################################################################
const CELL_UART_COMMAND_IN                  = 2800;   
const CELL_UART_COMMAND_OUT                 = 2801;   


################################################################################
# Range 2900-3000                  WireAdapter Cell ids   
################################################################################
const CELL_WA_XFER_REQ_TYPE                  = 2900;   
const CELL_WA_TRANSFER_RESULT                = 2901;   
const CELL_WA_NOTIFY_TYPE                    = 2902;   
const CELL_WA_NOTIFY_TYPE_VALUE              = 2903;   
const CELL_WA_RESULT_TYPE_VALUE              = 2904;   

################################################################################
# Range 3000-3100                  TJBC Cell ids   
################################################################################
const CELL_TJBC_B_EVENT						= 3000;   
const CELL_TJBC_B_PROFILE					= 3001;   
const CELL_TJBC_STATUS						= 3002;   
const CELL_TJBC_MSG_TYPE    				= 3003;   
const CELL_TJBC_OPCODE    					= 3004;   
const CELL_TJBC_TARGET_TYPE 				= 3005;   
const CELL_TJBC_OBEX_OPCODE 				= 3006;   
const CELL_TJBC_OBEX_RESPCODE 				= 3007;   
const CELL_TJBC_OBEX_LENGTH 				= 3008;   



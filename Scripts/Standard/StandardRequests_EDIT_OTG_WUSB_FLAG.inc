#*******************************************************************************
#*
#*  FILENAME: StandardRequests_EDIT_OTG_WUSB_FLAG.inc
#*
#*  Copyright (C) 2007 Lecroy Corporation
#*
#*  DESCRIPTION
#*    This is an include file for the standard device requests file and is meant to be
#*    EDITED BY THE USER for decoding WUSB Devices versus OTG Devices.
#*
#*    OTG Devices and WUSB Devices use the same Feature Selector for the Standard
#*    Request SET_FEATURE(). The flag in this file allows the application to determine
#*    which type of Device is being decoded. It should be modified by the user as
#*    necessary to decode the appropriate type of device.
#*
#*
#*  REVISION HISTORY
#*      06/05/07 File Created -RK
#*
#*******************************************************************************

#---------CONSTANTS-------------#
#DO NOT MODIFY THESE CONSTANTS --> Use to set StdReqDeviceTypeFLAG to appropriate value.

const OTG_Device  = 0;
const WUSB_Device = 1;

#---------DEVICE TYPE FLAG---------#
#MODIFY THIS FLAG AS NECESSARY --> Use above constants to set to appropriate device.

set StdReqDeviceTypeFLAG =0;# WUSB_Device;


#Global variable to decide on the USB specification with which the device is compliant
const UNKNOWN_VALUE  = 0xFFF;
const USB2_Spec      = 0x200;
const USB3_Spec      = 0x300;

set gDeviceCompliantSpec = USB3_Spec;


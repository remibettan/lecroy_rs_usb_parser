*******************************************************************************
*
*  FILENAME: Audio.dsc
*
*  Copyright (C) 1999 Computer Access Technology Corporation
*
*  DESCRIPTION
*    This descriptor definition file is supplied by CATC.
*    This file defines Audio class USB descriptors.
*    File version is 1.0.
*
*    At this moment the class-specific Format Type descriptors are not
*    defined in this file.
*
*******************************************************************************

*******************************************************************************
* Standard INTERFACE Descriptor definitions.
* The Interfcase descriptor is redefined here in order to decode and present
* the Audio Interface Subclass codes.
*******************************************************************************
DescriptorName=INTERFACE
DescriptorType=0x04
ClassCode=0x01

AllOffsets={
 2=bInterfaceNumber
 3=bAlternateSetting
 4=bNumEndpoints
 5=bInterfaceClass
 6=bInterfaceSubClass
 7=bInterfaceProtocol
 8=iInterface
}

; bInterfaceNumber  description
Offset(2)={
   FormatValue=The number of this interface is %i
}

; bAlternateSetting  description
Offset(3)={
   FormatValue=The value used to select alternate setting for this interface is %i
}

; bNumEndpoints  description
Offset(4)={
   FormatValue=The number of endpoints used by this interface is %i (excluding endpoint zero)
}

; bInterfaceClass  description
Offset(5)={

   WordValue={
      0x01=The interface implements Audio Interface class
   }
   FormatValue=The class code is 0x%02X

}

; bInterfaceSubClass  description
Offset(6)={
   WordValue={
      0x01=The interface subclass is AudioControl
      0x02=The interface subclass is AudioStreaming
      0x03=The interface subclass is MIDIStreaming
   }
   FormatValue=The subclass code is 0x%02X
}

; bInterfaceProtocol  description
Offset(7)={

   WordValue={
      0xFF=The interface protocol is vendor-specific
      0x00=The interface doesn't use any class-specific protocols
   }
   FormatValue=The protocol code is 0x%02X

}

; iInterface  description
Offset(8)={
   WordValue={
      0x00=The device doesn't have the string descriptor describing this interface
   }
   FormatValue=The index of the string descriptor describing this interface is %d  
}


*******************************************************************************
* Class-specific AC Interface Header Descriptor definitions.
* This descriptor is being decoded up to baInterfaceNr(1) location. The rest
* of the descriptor (additional interface numbers) will be displayed as 
* raw data.
*******************************************************************************
DescriptorName=AC Interface Header
DescriptorType=0x24
DescriptorSubtype=0x01
ClassCode=0x01
SubclassCode=0x01

AllOffsets={
 1=bDescriptorType
 2=bDescriptorSubtype
 3=bcdADC
 5=wTotalLength
 7=bInCollection
 8=baInterfaceNr(1)
}

Offset(1)={
  WordValue={
    0x24=CS_INTERFACE type
  }
}

Offset(2)={
  WordValue={
    0x01=HEADER subtype
  }
}

Offset(3)={
   Size=2  
   BCD=TRUE
   FormatValue=Device compliant to the Audio Device Class specification version %X.%02X   
}

Offset(5)={
   Size=2
   FormatValue=The combined length for this descriptor, including all Unit and Terminal descriptors is %d
}

Offset(7)={
   FormatValue=There are %d AudioStreaming and MIDIStreaming interfaces in this collection
}

Offset(8)={
   FormatValue=Interface number of the first Audio/MIDI Streaming interface in the Collection
}


*******************************************************************************
* Input Terminal Descriptor definitions.
*******************************************************************************
DescriptorName=Input Terminal
DescriptorType=0x24
DescriptorSubtype=0x02
ClassCode=0x01
SubclassCode=0x01

AllOffsets={
 1=bDescriptorType
 2=bDescriptorSubtype
 3=bTerminalID
 4=wTerminalType
 6=bAssocTerminal
 7=bNbrChannels
 8=wChannelConfig
10=iChannelNames
11=iTerminal
}

Offset(1)={
  WordValue={
    0x24=CS_INTERFACE type
  }
}

Offset(2)={
  WordValue={
    0x02=INPUT_TERMINAL subtype
  }
}

Offset(3)={
  FormatValue=Value of %d uniquely identifies this terminal
}

Offset(4)={
  Size=2
  WordValue={
     ;USB Terminal Types
     0x0101=USB streaming
     0x01FF=USB vendor specific

     ;Input Terminal Types
     0x0201=Microphone
     0x0202=Desktop microphone
     0x0203=Personal microphone
     0x0204=Omni-directional microphone
     0x0205=Microphone array
     0x0206=Processing microphone array

     ;Bi-directional Terminal Types
     0x0401=Handset
     0x0402=Headset
     0x0403=Speakerphone, no echo reduction
     0x0404=Echo-suppressing speakerphone
     0x0405=Echo-canceling speakerphone

     ;Telephony Terminal Types
     0x0501=Phone line
     0x0502=Telephone
     0x0503=Down Line Phone

     ;External Terminal Types
     0x0601=Analog connector
     0x0602=Digital audio interface
     0x0603=Line connector
     0x0604=Legacy audio connector
     0x0605=S/PDIF
     
     ;Embedded function Terminal Types
     0x0703=CD player
     0x0704=Digital Audio Tape
     0x0705=Digital Compact Cassette
     0x0706=MiniDisk player
     0x0707=Analog Tape
     0x0708=Phonograph
     0x0709=VCR Audio
     0x070A=Video Disc Audio
     0x070B=DVD Audio
     0x070C=TV Tuner Audio
     0x070D=Satellite Reciever Audio
     0x070E=Cable Tuner Audio
     0x070F=DSS Audio
     0x0710=Radio Receiver
     0x0712=Multi-track Recorder
     0x0713=Synthesizer
  }
  FormatValue=Undefined Input Terminal Type 0x%04X
}

Offset(6)={
   FormatValue=This Input Terminal is associated with Output Terminal %d
}

Offset(7)={
   FormatValue=This Terminal's output audio channel cluster has %d logical output channels
}

Offset(8)={
   Size=2
   Name=Spatial locations present in the cluster:
   Bitmap={
      0= Left Front
      1= Right Front
      2= Center Front
      3= Low Freq Enh
      4= Left Surround
      5= Right Surround
      6= Left of Center
      7= Right of Center
      8= Surround
      9= Side Left
      10=Side Right
      11=Top
   }
}

Offset(10)={
  WordValue={
     0x00=There is no string descriptor describing the first logical channel
  }
  FormatValue=The index of the string descriptor describing the first logical channel is %d
}

Offset(11)={
  WordValue={
     0x00=There is no string descriptor describing the Input Terminal
  }
  FormatValue=The index of the string descriptor describing the Input Terminal is %d
}


*******************************************************************************
* Output Terminal Descriptor definitions.
*******************************************************************************
DescriptorName=Output Terminal
DescriptorType=0x24
DescriptorSubtype=0x03
ClassCode=0x01
SubclassCode=0x01

AllOffsets={
 1=bDescriptorType
 2=bDescriptorSubtype
 3=bTerminalID
 4=wTerminalType
 6=bAssocTerminal
 7=bSourceID
 8=iTerminal
}

Offset(1)={
  WordValue={
    0x24=CS_INTERFACE type
  }
}

Offset(2)={
  WordValue={
    0x03=OUTPUT_TERMINAL subtype
  }
}

Offset(3)={
  FormatValue=Value of %d uniquely identifies this terminal
}

Offset(4)={
  Size=2
  WordValue={

     ;USB Terminal Types
     0x0101=USB streaming Terminal Type
     0x01FF=USB vendor specific Terminal Type

     ;Output Terminal Types
     0x0301=Speaker
     0x0302=Headphones
     0x0303=Head Mounted Display Audio
     0x0304=Desktop speaker
     0x0305=Room speaker
     0x0306=Communication speaker
     0x0307=Low frequency effects speaker

     ;Bi-directional Terminal Types
     0x0401=Handset
     0x0402=Headset
     0x0403=Speakerphone, no echo reduction
     0x0404=Echo-suppressing speakerphone
     0x0405=Echo-canceling speakerphone

     ;Telephony Terminal Types
     0x0501=Phone line
     0x0502=Telephone
     0x0503=Down Line Phone

     ;External Terminal Types
     0x0601=Analog connector
     0x0602=Digital audio interface
     0x0603=Line connector
     0x0604=Legacy audio connector
     0x0605=S/PDIF

     ;Embedded function Terminal Types
     0x0701=Level Calibration Noise Source
     0x0702=Equalization Noise
     0x0704=Digital Audio Tape
     0x0705=Digital Compact Cassette
     0x0706=MiniDisk player
     0x0707=Analog Tape
     0x0712=Radio Transmitter
     0x0712=Multi-track Recorder

  }
  FormatValue=Undefined Output Terminal Type 0x%04X

}

Offset(6)={
   FormatValue=This Output Terminal is associated with Input Terminal %d
}

Offset(7)={
   FormatValue=This Terminal is connected to Unit or Terminal with ID %d
}

Offset(8)={
   WordValue={
      0x00=There is no string descriptor describing this Output Terminal
   }
   FormatValue=The index of the string descriptor describing this Output Terminal is %d  
}


*******************************************************************************
* Mixer Unit Descriptor definitions.
* This descriptor is being decoded up to baSourceID(1) location. The rest
* of the descriptor will be displayed as raw data.
*******************************************************************************
DescriptorName=Mixer Unit
DescriptorType=0x24
DescriptorSubtype=0x04
ClassCode=0x01
SubclassCode=0x01

AllOffsets={
 1=bDescriptorType
 2=bDescriptorSubtype
 3=bUnitID
 4=bNrInPins
 5=baSourceID(1)
}

Offset(1)={
  WordValue={
    0x24=CS_INTERFACE type
  }
}

Offset(2)={
  WordValue={
    0x04=MIXER_UNIT subtype
  }
}

Offset(3)={
  FormatValue=Constant %d uniquely identifies this unit
}

Offset(4)={
  FormatValue=This unit has %d Input Pins
}

Offset(5)={
  FormatValue=The first Input Pin is connected to Unit or Terminal %d
}

*******************************************************************************
* Selector Unit Descriptor definitions.
* This descriptor is being decoded up to baSourceID(1) location. The rest
* of the descriptor will be displayed as raw data.
*******************************************************************************
DescriptorName=Selector Unit
DescriptorType=0x24
DescriptorSubtype=0x05
ClassCode=0x01
SubclassCode=0x01

AllOffsets={
 1=bDescriptorType
 2=bDescriptorSubtype
 3=bUnitID
 4=bNrInPins
 5=baSourceID(1)
}

Offset(1)={
  WordValue={
    0x24=CS_INTERFACE type
  }
}

Offset(2)={
  WordValue={
    0x05=SELECTOR_UNIT subtype
  }
}

Offset(3)={
  FormatValue=Constant %d uniquely identifies this unit
}

Offset(4)={
  FormatValue=This unit has %d Input Pins
}

Offset(5)={
  FormatValue=The first Input Pin is connected to Unit or Terminal %d
}


*******************************************************************************
* Feature Unit Descriptor definitions.
* This descriptor is being decoded up to bmaControls(0) location. The rest
* of the descriptor will be displayed as raw data.
*******************************************************************************
DescriptorName=Feature Unit
DescriptorType=0x24
DescriptorSubtype=0x06
ClassCode=0x01
SubclassCode=0x01

AllOffsets={
 1=bDescriptorType
 2=bDescriptorSubtype
 3=bUnitID
 4=bSourceID
 5=bControlSize
 6=bmaControls(0)
}

Offset(1)={
  WordValue={
    0x24=CS_INTERFACE type
  }
}

Offset(2)={
  WordValue={
    0x06=FEATURE_UNIT subtype
  }
}

Offset(3)={
  FormatValue=Constant %d uniquely identifies this unit
}

Offset(4)={
  FormatValue=This unit is connected to Unit or Terminal %d
}

Offset(5)={
  FormatValue=The size of the element of bmaControls() is %d bytes
}

Offset(6)={
  Size=2
  Name=Supported controls for master channel 0 (size 2 assumed)
  Bitmap={
     0=Mute
     1=Volume
     2=Bass
     3=Mid
     4=Treble
     5=Graphic Equalizer
     6=Automatic Gain
     7=Delay
     8=Bass Boost
     9=Loudness
  }
}


*******************************************************************************
* Processing Unit Descriptor definitions.
* Only the common part of this descriptor is being decoded at this moment
* (up to baSourceID(1) location). The wProcessType field identifies the
* type of processing performed. The rest of the descriptor will be 
* displayed as raw data.
*******************************************************************************
DescriptorName=Processing Unit
DescriptorType=0x24
DescriptorSubtype=0x07
ClassCode=0x01
SubclassCode=0x01

AllOffsets={
 1=bDescriptorType
 2=bDescriptorSubtype
 3=bUnitID
 4=wProcessType
 6=bNrInPins
 6=baSourceID(1)
}

Offset(1)={
  WordValue={
    0x24=CS_INTERFACE type
  }
}

Offset(2)={
  WordValue={
    0x07=PROCESSING_UNIT subtype
  }
}

Offset(3)={
  FormatValue=Constant %d uniquely identifies this unit
}

Offset(4)={
  WordValue={
     0x0001=UP/DOWNMIX_PROCESS type
     0x0002=DOLBY_PROLOGIC_PROCESS type
     0x0003=3D_STEREO_EXTENDER_PROCESS type
     0x0004=REVERBERATION_PROCESS type
     0x0005=CHORUS_PROCESS type
     0x0006=DYN_RANGE_COMP_PROCESS type
  }
  FormatValue=Process type 0x%04X
}

Offset(6)={
  FormatValue=This unit has %d Input Pins
}

Offset(7)={
  FormatValue=The first Input Pin is connected to Unit or Terminal %d
}


*******************************************************************************
* Extension Unit Descriptor definitions.
* This descriptor is being decoded up to baSourceID(1) location. The rest
* of the descriptor will be displayed as raw data.
*******************************************************************************
DescriptorName=Extension Unit
DescriptorType=0x24
DescriptorSubtype=0x08
ClassCode=0x01
SubclassCode=0x01

AllOffsets={
 1=bDescriptorType
 2=bDescriptorSubtype
 3=bUnitID
 4=wExtensionCode
 6=bNrInPins
 7=baSourceID(1)
}

Offset(1)={
  WordValue={
    0x24=CS_INTERFACE type
  }
}

Offset(2)={
  WordValue={
    0x08=EXTENSION_UNIT subtype
  }
}

Offset(3)={
  FormatValue=Constant %d uniquely identifies this unit
}

Offset(5)={
  Size=2
  Format=Vendor-specific code of 0x%04X identifies this Extension Unit
}

Offset(6)={
  FormatValue=This unit has %d Input Pins
}

Offset(7)={
  FormatValue=The first Input Pin is connected to Unit or Terminal %d
}


*******************************************************************************
* Standard AC Interrupt Edpoint Descriptor definitions.
*******************************************************************************
DescriptorName=AC Interrupt Endpoit
DescriptorType=0x05
ClassCode=0x01
SubclassCode=0x01

AllOffsets={
 1=bDescriptorType
 2=bEndpointAddress
 3=bmAttributes
 4=wMaxPacketSize
 6=bInterval
 7=bRefresh
 8=bSyncAddress
}

Offset(1)={
  WordValue={
    0x05=ENDPOINT type
  }
}

Offset(2)={
   WordValue={
      0x01=This is an OUT endpoint with number 1
      0x02=This is an OUT endpoint with number 2
      0x03=This is an OUT endpoint with number 3
      0x04=This is an OUT endpoint with number 4
      0x05=This is an OUT endpoint with number 5
      0x06=This is an OUT endpoint with number 6
      0x07=This is an OUT endpoint with number 7
      0x08=This is an OUT endpoint with number 8
      0x09=This is an OUT endpoint with number 9
      0x0A=This is an OUT endpoint with number 10
      0x0B=This is an OUT endpoint with number 11
      0x0C=This is an OUT endpoint with number 12
      0x0D=This is an OUT endpoint with number 13
      0x0E=This is an OUT endpoint with number 14
      0x0F=This is an OUT endpoint with number 15

      0x81=This is an IN endpoint with number 1
      0x82=This is an IN endpoint with number 2
      0x83=This is an IN endpoint with number 3
      0x84=This is an IN endpoint with number 4
      0x85=This is an IN endpoint with number 5
      0x86=This is an IN endpoint with number 6
      0x87=This is an IN endpoint with number 7
      0x88=This is an IN endpoint with number 8
      0x89=This is an IN endpoint with number 9
      0x8A=This is an IN endpoint with number 10
      0x8B=This is an IN endpoint with number 11
      0x8C=This is an IN endpoint with number 12
      0x8D=This is an IN endpoint with number 13
      0x8E=This is an IN endpoint with number 14
      0x8F=This is an IN endpoint with number 15
   }
   FormatValue=Invalid endpoint address (reserved bits are set to one)!
}

Offset(3)={
   WordValue={
      0x03=INTERRUPT Transfer Type, no synchronization
   }
}

Offset(4)={
   Size=2
   WordValue={
      0x0002=Maximum packet size 2 (endpoint not shared)
   }
   FormatValue=Maximum packet size for this endpoint is %i in this configuration
}

Offset(6)={
   FormatValue=The polling interval for this endpoint is %d milliseconds
}

Offset(7)={
   WordValue={
      0x00=Reset to zero
   }
   FormatValue=Non-default value 0x%02X
}

Offset(8)={
   WordValue={
      0x00=Reset to zero
   }
   FormatValue=Non-default value 0x%02X
}


*******************************************************************************
* AudioStreaming Descriptors start here.
*******************************************************************************

*******************************************************************************
* Class-Specific AS Interface Descriptor definitions.
*******************************************************************************
DescriptorName=Class-Specific AS Interface
DescriptorType=0x24
DescriptorSubtype=0x01
ClassCode=0x01
SubclassCode=0x02

AllOffsets={
 1=bDescriptorType
 2=bDescriptorSubtype
 3=bTerminalLink
 4=bDelay
 5=wFormatTag
}

Offset(1)={
  WordValue={
    0x24=CS_INTERFACE type
  }
}

Offset(2)={
  WordValue={
    0x01=AS_GENERAL subtype
  }
}

Offset(3)={
   FormatValue=Terminal ID of connected Terminal %d   
}

Offset(4)={
   FormatValue=Delay introduced by the data path is %d frames   
}


Offset(5)={
   Size=2  
   WordValue={
      ; TYPE I codes
      0x0001=PCM Data Format
      0x0002=PCM8 Data Format
      0x0003=IEEE_FLOAT Data Format
      0x0004=ALAW Data Format
      0x0005=MULAW Data Format

      ; TYPE II codes
      0x1001=MPEG Data Format
      0x1002=AC-3 Data Format

      ; TYPE III codes
      0x2001=IEC1937_AC-3 Data Format
      0x2002=IEC1937_MPEG-1_Layer1 Data Format
      0x2003=IEC1937_MPEG-1_Layer2/3 or IEC1937_MPEG-2_NOEXT
      0x2004=IEC1937_MPEG-2_EXT
      0x2005=IEC1937_MPEG-2_Layer1_LS
      0x2006=IEC1937_MPEG-2_Layer2/3_LS

   }
   FormatValue=Undefined 0x%04X Audio Data Format   
}


*******************************************************************************
* Standard AC Isochronous Audio Data or Synch Edpoint Descriptor definitions.
*******************************************************************************
DescriptorName=Standard AS Iso Audio Data/Synch Endpoit
DescriptorType=0x05
ClassCode=0x01
SubclassCode=0x02

AllOffsets={
 1=bDescriptorType
 2=bEndpointAddress
 3=bmAttributes
 4=wMaxPacketSize
 6=bInterval
 7=bRefresh
 8=bSyncAddress
}

Offset(1)={
  WordValue={
    0x05=ENDPOINT type
  }
}

; bEndpointAddress  description
Offset(2)={
   WordValue={
      0x01=This is an OUT endpoint with number 1
      0x02=This is an OUT endpoint with number 2
      0x03=This is an OUT endpoint with number 3
      0x04=This is an OUT endpoint with number 4
      0x05=This is an OUT endpoint with number 5
      0x06=This is an OUT endpoint with number 6
      0x07=This is an OUT endpoint with number 7
      0x08=This is an OUT endpoint with number 8
      0x09=This is an OUT endpoint with number 9
      0x0A=This is an OUT endpoint with number 10
      0x0B=This is an OUT endpoint with number 11
      0x0C=This is an OUT endpoint with number 12
      0x0D=This is an OUT endpoint with number 13
      0x0E=This is an OUT endpoint with number 14
      0x0F=This is an OUT endpoint with number 15

      0x81=This is an IN endpoint with number 1
      0x82=This is an IN endpoint with number 2
      0x83=This is an IN endpoint with number 3
      0x84=This is an IN endpoint with number 4
      0x85=This is an IN endpoint with number 5
      0x86=This is an IN endpoint with number 6
      0x87=This is an IN endpoint with number 7
      0x88=This is an IN endpoint with number 8
      0x89=This is an IN endpoint with number 9
      0x8A=This is an IN endpoint with number 10
      0x8B=This is an IN endpoint with number 11
      0x8C=This is an IN endpoint with number 12
      0x8D=This is an IN endpoint with number 13
      0x8E=This is an IN endpoint with number 14
      0x8F=This is an IN endpoint with number 15
   }
   FormatValue=Invalid endpoint address (reserved bits are set to one)!
}

; bmAttributes
Offset(3)={
   WordValue={
      0x01=ISOCHRONOUS Transfer Type, No synchronization (this is the Synch Endpoint)
      0x05=ISOCHRONOUS Transfer Type, Asynchronous synchronization
      0x09=ISOCHRONOUS Transfer Type, Adaptive synchronization
      0x0D=ISOCHRONOUS Transfer Type, Synchronous synchronization
   }
}

; wMaxPacketSize  description
Offset(4)={
   Size=2
   FormatValue=Maximum packet size for this endpoint is %i in this configuration
}

; bInterval  description
Offset(6)={   
   FormatValue=The polling interval for this endpoint is %d milliseconds
}

Offset(7)={
   WordValue={
      0x00=Reset to zero
   }
   FormatValue=The rate of synchronization feedback data is 2^%d ms
}

Offset(8)={
   WordValue={
      0x00=No synchronization pipe is used
   }
   FormatValue=Endpoint 0x%02X is used to communicate synchronization information
}


*******************************************************************************
* Class-specific AS Isochronous Audio Data Edpoint Descriptor definitions.
*******************************************************************************
DescriptorName=Class-specific AS Isochronous Audio Data Endpoit
DescriptorType=0x25
DescriptorSubtype=0x01
ClassCode=0x01
SubclassCode=0x02

AllOffsets={
 1=bDescriptorType
 2=bDescriptorSubtype
 3=bmAttributes
 4=bLockDelayUnits
 5=wLockDelay
}

Offset(1)={
  WordValue={
    0x25=CS_ENDPOINT type
  }
}

Offset(2)={
  WordValue={
    0x01=EP_GENERAL subtype
  }
}

Offset(3)={
   Name=Control and max packet requirement
   Bitmap={
     0=Sampling Frequency
     1=Pitch
     7=MaxPacketsOnly
   }
}

Offset(4)={
   WordValue={
      0x00=Undefined delay units
      0x01=Lock Delay in milliseconds
      0x02=Lock Delay in decoded PCM samples
   }
   FormatValue=Resedved Units value 0x%02X
}

Offset(5)={
   Size=2
   FormatValue=Clock recovery circuitry locked in %d units
}

; bInterval  description
Offset(6)={   
   FormatValue=The polling interval for this endpoint is %d milliseconds
}

Offset(7)={
   WordValue={
      0x00=Reset to zero
   }
   FormatValue=Non-default value 0x%02X
}

Offset(8)={
   WordValue={
      0x00=No synchronization pipe is used
   }
   FormatValue=Endpoint 0x%02X is used to communicate synchronization information
}

# You neeed to edit this to match the Id's shown in the Descriptor Decoding.
# Replace the first number with the one you get from the descriptor.
# If there are more than one of the same type, repeate the line but change the
# first entry to match the unique Id.  The 3rd column tells the script decoder
# how to decode it, so leave that alone.

# Example: if I see in the Descriptor Decoding that
# a Audio Control Interface is assigned EntiyId 0x02,
# I enter a 0x02 in the first column  in the
# row that has "Terminal Control Selectors" in it
# if there were 2 Audio control Interfaces, and the second one
# had the EntityId of 0x04, I would add the row
# and enter a 0x04 in the first column.  If a unit does not
# exist, you can enter 0xFF in the first column so it will be ignored.
# (That assumes 0xFF is never a valid EntityId)
# Here is a sample where there is no Extension Unit.
# (This one is not referenced by the decoding software)
 

set SAMPLE_CurrentEntityIdMap = 
[
    #-----------------------------------------------------------------------------------------------
    #  EntityID , Corresponding control selectors                               , Internal Key 
    #                                                                             for this CS
    #-----------------------------------------------------------------------------------------------
    [   0xFF    , "NotFound"                                                    ,0xFF],
    [   0x10    , "Clock Source Control Selectors"                              ,0x01],           
    [   0x20    , "Clock Selector Control Selectors"                            ,0x02],
    #----------------------------------------------------------------------------------
    # if one does not exist, you can comment it out
    #[   0x30    , "Clock Multiplier Control Selectors"                          ,0x03],
    # or set it to 0xFF so that it is ignored
    [   0xFF    , "Terminal Control Selectors"                                  ,0x04],
    # or just delete the whole row
    #-----------------------------------------------------------------------------------    
    # if we have two "Mixer Control Selectors", you can do as following
    [   0x50    , "Mixer Control Selectors"                                     ,0x05],
    [   0x60    , "Mixer Control Selectors"                                     ,0x05],
    #-----------------------------------------------------------------------------------    
    # you can change the second text as a remark to yourself, but keep Internal Keys so that
    # we can correctly decode them
    [   0x70    , "This is the one I want to change name"                       ,0x07],
    #------------------------------------------------------------------------------------
    # the following is illegal, which applies one entity ID to two different type of CS
    # only the first one will be used
    [   0xB0    , "Dynamic Range Compressor Effect Unit Control Selectors"      ,0x0B],  
    [   0xB0    , "Up/Down-mix Processing Unit Control Selectors"               ,0x0C], 
    #-------------------------------------------------------------------------------------
    # last one in the table does not have ','
    [   0xC0    , "Dolby Prologic Processing Unit Control Selectors"            ,0x0D] 
];

# note that the syntax must be as above, with no comma after the
# last entry's right bracket.

# Here is a copy of the default entries so you dont lose the format.
# (This one is not referenced by the decoding software)

set DEFAULT_CurrentEntityIdMap = 
[
    #-----------------------------------------------------------------------------------------------
    #  EntityID , Corresponding control selectors                               , Internal Key 
    #                                                                             for this CS
    #-----------------------------------------------------------------------------------------------
    [   0xFF    , "NotFound"                                                    ,0xFF],
    [   0x01    , "Clock Source Control Selectors"                              ,0x01],           
    [   0x02    , "Clock Selector Control Selectors"                            ,0x02],
    [   0x03    , "Clock Multiplier Control Selectors"                          ,0x03],
    [   0x04    , "Terminal Control Selectors"                                  ,0x04],
    [   0x05    , "Mixer Control Selectors"                                     ,0x05],
    [   0x06    , "Selector Control Selectors"                                  ,0x06],
    [   0x07    , "Feature Unit Control Selectors"                              ,0x07],
    [   0x08    , "Parametric Equalizer Section Effect Unit Control Selectors"  ,0x08],
    [   0x09    , "Reverberation Effect Unit Control Selectors"                 ,0x09],
    [   0x0A    , "Modulation Delay Effect Unit Control Selectors"              ,0x0A],         
    [   0x0B    , "Dynamic Range Compressor Effect Unit Control Selectors"      ,0x0B],  
    [   0x0C    , "Up/Down-mix Processing Unit Control Selectors"               ,0x0C], 
    [   0x0D    , "Dolby Prologic Processing Unit Control Selectors"            ,0x0D], 
    [   0x0E    , "Stereo Extender Processing Unit Control Selectors"           ,0x0E], 
    [   0x0F    , "Extension Unit Control Selectors"                            ,0x0F], 
    [   0x10    , "AudioStreaming Interface Control Selectors"                  ,0x10], 
    [   0x11    , "Encoder Control Selectors"                                   ,0x11], 
    [   0x12    , "MPEG Decoder Control Selectors"                              ,0x12], 
    [   0x13    , "AC-3 Decoder Control Selectors"                              ,0x13],  
    [   0x14    , "WMA Decoder Control Selectors"                               ,0x14],  
    [   0x15    , "DTS Decoder Control Selectors"                               ,0x15]
];


# HERE IS THE REAL MAP (THE ONE YOU MUST EDIT):
# set this value to 1 to use custom map, otherwise software extract values automatically from descriptors in trace
set UseCurrentEntityIdMap = 0;
set CurrentEntityIdMap = 
[
    #-----------------------------------------------------------------------------------------------
    #  EntityID , Corresponding control selectors                               , Internal Key 
    #                                                                             for this CS
    #-----------------------------------------------------------------------------------------------
    [   0xFF    , "NotFound"                                                    ,0xFF],
    [   0x01    , "Clock Source Control Selectors"                              ,0x01],           
    [   0x02    , "Clock Selector Control Selectors"                            ,0x02],
    [   0x03    , "Clock Multiplier Control Selectors"                          ,0x03],
    [   0x04    , "Terminal Control Selectors"                                  ,0x04],
    [   0x05    , "Mixer Control Selectors"                                     ,0x05],
    [   0x06    , "Selector Control Selectors"                                  ,0x06],
    [   0x07    , "Feature Unit Control Selectors"                              ,0x07],
    [   0x08    , "Parametric Equalizer Section Effect Unit Control Selectors"  ,0x08],
    [   0x09    , "Reverberation Effect Unit Control Selectors"                 ,0x09],
    [   0x0A    , "Modulation Delay Effect Unit Control Selectors"              ,0x0A],         
    [   0x0B    , "Dynamic Range Compressor Effect Unit Control Selectors"      ,0x0B],  
    [   0x0C    , "Up/Down-mix Processing Unit Control Selectors"               ,0x0C], 
    [   0x0D    , "Dolby Prologic Processing Unit Control Selectors"            ,0x0D], 
    [   0x0E    , "Stereo Extender Processing Unit Control Selectors"           ,0x0E], 
    [   0x0F    , "Extension Unit Control Selectors"                            ,0x0F], 
    [   0x10    , "AudioStreaming Interface Control Selectors"                  ,0x10], 
    [   0x11    , "Encoder Control Selectors"                                   ,0x11], 
    [   0x12    , "MPEG Decoder Control Selectors"                              ,0x12], 
    [   0x13    , "AC-3 Decoder Control Selectors"                              ,0x13],  
    [   0x14    , "WMA Decoder Control Selectors"                               ,0x14],  
    [   0x15    , "DTS Decoder Control Selectors"                               ,0x15]
];
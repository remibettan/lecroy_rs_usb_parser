# You neeed to edit this to match the Id's shown in the Descriptor Decoding.
# Replace the first number with the one you get from the descriptor.
# If there are more than one of the same type, repeate the line but change the
# first entry to match the unique Id.  The 3rd column tells the script decoder
# how to decode it, so leave that alone.

# Example: if I see in the Descriptor Decoding that
# a Audio Control Interface is assigned EntiyId 0x02,
# I enter a 02 in the first column  in the
# row that has "Terminal" in it
# if there were 2 Audio control Interfaces, and the second one
# had the EntityId of 0x04, I would add the row
# and enter a 0x04 in the first column.  If a unit does not
# exist, you can enter 0xFF in the first column so it will be ignored.
# (That assumes 0xFF is never a valid EntityId)
# Here is a sample where there is no Extension Unit.
# (This one is not referenced by the decoding software)
 

set SAMPLE_CurrentEntityIdMap = 
[
    [   0xFF, "NotFound",                0 ],
    [   0x02, "Terminal",                1 ],
    [   0x10, "Terminal",                1 ],           
    [   0x20, "MixerUnit",               2 ],
    [   0x30, "SelectorUnit",            3 ],
    [   0x40, "FeatureUnit",             4 ],
    [   0x50, "ProcessingUnit",          5 ],
    [   0xFF, "ExtensionUnit",           6 ]
];

# note that the syntax must be as above, with no comma after the
# last entry's right bracket.

# Here is a copy of the default entries so you dont lose the format.
# (This one is not referenced by the decoding software)

set DEFAULT_CurrentEntityIdMap = 
[
    [   0xFF, "NotFound",                                0 ],
    [   0x10, "Terminal",                                1 ],           
    [   0x20, "MixerUnit",                               2 ],
    [   0x30, "SelectorUnit",                            3 ],
    [   0x40, "FeatureUnit",                             4 ],
    [   0x50, "ProcessingUnit_UP_DOWNMIX",               5 ],
    [   0x60, "ProcessingUnit_DOLBY_PROLOGIC",           6 ],
    [   0x70, "ProcessingUnit_AUDIO_3D_STEREO_EXTENDER", 7 ],
    [   0x80, "ProcessingUnit_REVERBERATION",            8 ],
    [   0x90, "ProcessingUnit_CHORUS",                   9 ],
    [   0xA0, "ProcessingUnit_DYN_RANGE_COMP",           10],         
    [   0xB0, "ExtensionUnit",                           11]      
];


# HERE IS THE REAL MAP (THE ONE YOU MUST EDIT):
# set this value to 1 to use custom map, otherwise software extract values automatically from descriptors in trace
set UseCurrentEntityIdMap = 0;
set CurrentEntityIdMap = 
[
    [   0xFF, "NotFound",                                0 ],
    [   0x10, "Terminal",                                1 ],           
    [   0x20, "MixerUnit",                               2 ],
    [   0x30, "SelectorUnit",                            3 ],
    [   0x40, "FeatureUnit",                             4 ],
    [   0x50, "ProcessingUnit_UP_DOWNMIX",               5 ],
    [   0x60, "ProcessingUnit_DOLBY_PROLOGIC",           6 ],
    [   0x70, "ProcessingUnit_AUDIO_3D_STEREO_EXTENDER", 7 ],
    [   0x80, "ProcessingUnit_REVERBERATION",            8 ],
    [   0x90, "ProcessingUnit_CHORUS",                   9 ],
    [   0xA0, "ProcessingUnit_DYN_RANGE_COMP",           10],         
    [   0xB0, "ExtensionUnit",                           11]      
];

# set this value to 1 will let the endpoint request decoding following th AudioStreaming Requests
# set this value to 2 will let the endpoint request decoding following th MIDIStreaming Requests
set EndpointRequestDecodingSubclass = 1;



# You neeed to edit this to match the Id's shown in the Descriptor Decoding.
# Replace the first number with the one you get from the descriptor.
# If there are more than one of the same type, repeate the line but change the
# first entry to match the unique Id.  The 3rd column tells the script decoder
# how to decode it, so leave that alone.

# Example: if I see in the Descriptor Decoding that
# a Video Control Interface is assigned EntiyId 0x02,
# I enter a 02 in the first column  in the
# row that has "VideoControlInterface" in it
# if there were 2 Video control Interfaces, and the second one
# had the EntityId of 0x04, I would add the row
# and enter a 0x04 in the first column.  If a unit does not
# exist, you can enter 0xFF in the first column so it will be ignored.
# (That assumes 0xFF is never a valid EntityId)
# Here is a sample where there is no Extension Unit.
# (This one is not referenced by the decoding software)
 

set SAMPLE_CurrentEntityIdMap = 
[
    [   0xFF, "NotFound",                0 ],                
    [   0x02, "VideoControlInterface",   1 ],
    [   0x04, "VideoControlInterface",   1 ],
    [   0x10, "Terminal",                2 ],           
    [   0x83, "SelectorUnit",            3 ],
    [   0x82, "Camera",                  4 ],
    [   0x99, "ProcessingUnit",          5 ],         
    [   0xFF, "ExtensionUnit",           6 ],
    [   0x60, "VideoStreaming",          7 ]        
];

# note that the syntax must be as above, with no comma after the
# last entry's right bracket.

# Here is a copy of the default entries so you dont lose the format.
# (This one is not referenced by the decoding software)

set DEFAULT_CurrentEntityIdMap = 
[
    [   0xFF, "NotFound",                0 ],                
    [   0x10, "VideoControlInterface",   1 ],
    [   0x20, "Terminal",                2 ],           
    [   0x30, "SelectorUnit",            3 ],
    [   0x40, "Camera",                  4 ],
    [   0x50, "ProcessingUnit",          5 ],         
    [   0x60, "ExtensionUnit",           6 ],
    [   0x70, "VideoStreaming",          7 ]        
];


# HERE IS THE REAL MAP (THE ONE YOU MUST EDIT):

set CurrentEntityIdMap = 
[
    [   0xFF, "NotFound",                0 ],
	[   0x00, " VideoControlInterface ",   1 ],
	[   0x01, " TerminalInputDepth ",      4 ],
    [   0x06, " TerminalInputRGB ",        4 ],
	[   0xff, " TerminalInputFishEye ",    0 ],
    [   0x02, " ProcessingUnitDepth ",     5 ],
    [   0x07, " ProcessingUnitRGB ",       5 ],
    [   0x0b, " ProcessingUnitFishEye ",   5 ], 
	[   0x03, " ExtensionUnitDepth ",      6 ],
	[   0x08, " ExtensionUnitRGB ",        0 ],
	[   0x0c, " ExtensionUnitFishEye ",    8 ],
	[   0xff, " OutputDepth ",             0 ],
	[   0xff, " OutputRGB ",    	       0 ],
	[   0xff, " OutputFishEye ",           0 ]
];

set CurrentStreamInterfacesMap = 
[
    [   0xFF, "NotFound",                0 ],
	[   0x0, " VideoControlInterface ",   1 ],	
	[   0x1, " VideoStreamInterface ",   9 ],
	[   0x2, " VideoStreamInterface ",   9 ],
	[   0x3, " VideoControlInterface ",   1 ],
	[   0x4, " VideoStreamInterface ",   9 ]
];

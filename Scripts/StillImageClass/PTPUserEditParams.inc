########################################################################################
##      USB/UWB Tracer Script        Copyright 2006 LeCroy PSG
#       PTPUserEditParams.inc
#       Contains critical variables for user to adjust
#
########################################################################################

########################################################################################
# This is the variable that determine how many cells to display in the software for 
#each display unit. default : 
# set MAX_CELLS_TO_DISPLAY = 80;
# We suggest users not to set the number larger than 100, which could cause the whole
# screen overflow.
########################################################################################
set MAX_CELLS_TO_DISPLAY = 80;

########################################################################################
# This is the variable that determine if user want to continue processing the data that
# reach the MAX_CELLS_TO_DISPLAY value.
# If you set the IF_CONTINUE_ON_PROCESSING_DATA = 1 , you will be able to see any errors
# that occurs after the MAX_CELLS_TO_DISPLAY value is reached, but please be aware that 
# if the data payload is large, you could experience significant lag on viewing this
# display unit with extreme large data payload. (The majority PTP/MTP commands we saw that
# causing this problem is GetObjectPropList)
# The defualt value for IF_CONTINUE_ON_PROCESSING_DATA is 0, set the variable to this value
# will trigger the script dump all the rest of payload after MAX_CELLS_TO_DISPLAY value is
# reached. In collaps view case, the total cells may not reach MAX_CELLS_TO_DISPLAY value, 
# but data still get dumped at the same point as under expanded view
##########################################################################################
set IF_CONTINUE_ON_PROCESSING_DATA = 0;


###########################################################################################
#InterdependentPropDescDatasetSizeBytes = 2;                                              #
#According to the MTP Specification Revision 0.83 by Microsoft Corp.,                     #
#The NumberOfInterdependencies and NumberOfPropDescs in InterdependentPropDescDataset     #
#are UINT16 value with size of 2 bytes. If you are following this, please leave this      #
#value as it is (2). However, we realized that some products on the market are using      #
#UINT32 instead for unknown reasons, which could mess up the whole InterdependentPropDesc #
#Dataset decoding. So if your company has decoding problem with the                       #
#GetInterdependentPropDesc operation, try to change this value to 4                       #
###########################################################################################
set InterdependentPropDescDatasetSizeBytes = 2;


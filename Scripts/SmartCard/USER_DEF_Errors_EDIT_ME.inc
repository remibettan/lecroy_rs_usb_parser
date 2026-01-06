#*******************************************************************************
#
#  FILENAME: USER_DEF_Errors_EDIT_ME.inc
#
#  Copyright (c) 2007, LeCroy - All Rights Reserved
#
#  DESCRIPTION
#    This is the file for USER DEFINED ERRORS for the Smart-Card Class 
#      (CCIDs & ICCDs) 
#
#  REVISION HISTORY
#    02/08/2007
#
#*******************************************************************************   


#The error code table is a list type (defined in the "USBTracer Script Decoding Manual".

/*
Lists:
A list can hold zero or more pieces of data. A list that contains zero pieces of data
is called an empty list. An empty list evaluates to false when used in an expression,
whereas a non-empty list evaluates to true. List literals are expressed using the
square bracket ([]) delimiters. List elements can be of any type, including lists.
    [1, 2, 3, 4]
    []
    ["one", 2, "three", [4, [5, [6]]]]
*/

#Each element in the error code table is a list of 3 pieces of data. (i.e. a list of lists)
#The format for an element/entry in the ErrorCodeTable is as follows:
#     [  Error   ,    Name   ,   Possible Causes / Description ]
#
#  Example: An error with the following attributes -
#
#             Error = 0x81  
#             Name = "OVERHEATING"  
#             PossibleCauses/Description = "\nThe device is over heating"
#
#           is entered as shown in the Sample USER_ErrorCodeTable below
#
# Sample USER_ErrorCodeTable
#  
# set USER_ErrorCodeTable=[
#   [ 0x81, "OVERHEATING"  , "\nThe device is over heating"  ],
#   [ 0xB3, "BAD_PIN"      , "\nThe PIN was In-correct" ],
#   [ 0xB4, "XFR_TIMEOUT"  , "\nTransfer took too long" ]
# ];
#
# Each error should be separated by a comma, except the last element, otherwise a parse
# error will occur. Before editing this file, it recommended to make a back-up file, 
# just in case.


#CCID USER DEFINED Bulk-IN Message ErrorCode Table (Range = 0x81 - 0xC0)
#Do not remove  [ 0, "",""] it is necessary for the decode scripts.
#When adding a new error, make sure that the previous element/error has a comma after it.
#If adding a possiblecause/description, add a "\n" in front of the text (formating for display

set CCID_USER_ErrorCodeTable=[
 [  0, "",""]
];


#ICCD USER DEFINED Bulk-IN Message ErrorCode Table  (Range = 0x81 - 0xC0)
#Do not remove  [ 0, "",""] it is necessary for the decode scripts.
#When adding a new error, make sure that the previous element/error has a comma after it.
#If adding a possiblecause/description, add a "\n" in front of the text (formating for display

set ICCD_USER_ErrorCodeTable=[
 [  0, "",""]
];


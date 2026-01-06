#
#  Copyright (c) 2001, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_CDB_defs.inc
#
#  SCSI CDB definitions.
################################################################################


#
# This global variable specifies the default command set to start search for 
# CDB deinition with. This value will be used if the input context variable
# in.CommandSet is null (not specified)
#
set CommandSet = 0;


#
# Table containing CDB definition tables.
#
# NOTE: The order of tables in the table below defines the order how
#       CDB definition will be searched by default. 
#
#       if in.CommandSet contains a valid index of some CDB table then
#       CDB definition will be searched for in that table first.
#

const CDB_Tables =
[
  # CDB definition table 
  #------------------------------------------------ 
  
    SPC_CDB_Table, # - 0 
    SBC_CDB_Table, # - 1
    SMC_CDB_Table, # - 2
    SSC_CDB_Table, # - 3
    MMC_CDB_Table, # - 4
    SCC_CDB_Table, # - 5
    SES_CDB_Table, # - 6
    SAT_CDB_Table  # - 7
    # OSD           We should add this category based on STX software
    # ADS           We should add this category based on STX software
];




#
# Table containing Extended CDB definition tables.
#
# NOTE: The order of tables in the table below defines the order how
#       Extended CDB definition will be searched for by default.
#
#       if in.CommandSet contains a valid index of some CDBEx table then
#       Extended CDB definition will be searched for in that table first.
#

const ExCDB_Tables =
[
  # Extended CDB definition table 
  #------------------------------------------------ 
  
    null,            # - 0 
    SBC_ExCDB_Table, # - 1, Currently only SBC command set( of the command sets that we decode ) provides extended CDB.
    null,            # - 2
    null             # - 3
];


#
#  Copyright (c) 2003, Computer Access Technology Corp. - All Rights Reserved
#
#  SCSI_ExCDB_SBC.inc
#
#  SCSI Extended CDB definitions for SBC command set.
# 
################################################################################

const SBC_ExCDB_Table = 
[
# Service actn, CDB_Name  , Extended CDB_Decoder  , CDB_Color,   CDB_Tooltip #
#---------------------------------------------------------
    null,
    
    [0x0001 , "REBUILD(32)" , "ShowRebuild32" , CDB_Rebuild_Color , 
        "The REBUILD (32) command requests that the\n" + 
        "target write to the medium the XOR data\n" + 
        "generated from the specified source devices."],
    
    [0x0002 , "REGENERATE(32)", "ShowUnknownCDB" , SCSI_Color ,
        "The REGENERATE (32) command requests that the\n" + 
        "target write to the buffer the XOR data generated\n" + 
        "from its own medium and the specified source\n" + 
        "devices."],
    
    [0x0003 , "XDREAD(32)", "ShowXDRead32" , CDB_XDRead_Color ,
        "The XDREAD (32) command requests that the target\n" + 
        "transfer to the initiator the XOR data generated\n" + 
        "by an XDWRITE or REGENERATE command."],
    
    [0x0004 , "XDWRITE(32)", "ShowXDWrite32" , CDB_XDWrite_Color ,
        "The XDWRITE (32) command requests that the target\n" + 
        "XOR the data transferred with the data on the\n" + 
        "medium."],
    
    [0x0005 , "XDWRITE EXTENDED(32)", "ShowXDWriteExtended32" , CDB_XDWrite_Color,
        "The XDWRITE EXTENDED (32) command requests\n" + 
        "that the target XOR the data transferred\n" + 
        "with the data on the medium."],
    
    
    [0x0006 , "XPWRITE(32)", "ShowXPWrite32" , CDB_XPWrite_Color,
        "The XPWRITE(32) command requests that the\n" + 
        "target XOR the data transferred with the\n" + 
        "data on the medium and then write the XOR\n" + 
        "data to the medium."],
    
    
    [0x0007 , "XDWRITEREAD(32)", "ShowXDWriteRead32" , CDB_XDWriteRead_Color ,
        "The XDWRITEREAD (32) command requests that the\n" + 
        "target XOR the data transferred (data-out) with\n" + 
        "the data on the medium and return the resulting\n" + 
        "XOR data (data-in)."],
    
    [0x0008 , "XDWRITE EXTENDED(64)", "ShowXDWriteExtended64" , CDB_XDWrite_Color,
        "The XDWRITE EXTENDED (64) command requests\n" + 
        "that the target XOR the data transferred\n" + 
        "with the data on the medium."],

    [0x0009 , "READ(32)", "ShowRead32" , CDB_Read_Color ,
        "The READ (32) command requests that the device\n" + 
        "server reads the specified logical block(s)\n" +
        " and transfer them to the data-in buffer."],

    [0x000A , "VERIFY(32)", "ShowVerify32" , CDB_Verify_Color ,
        "The VERIFY (32) command requests that the device\n" + 
        "server verify the specified logical block(s)\n" +
        " on the medium."],

    [0x000B , "WRITE (32)", "ShowWrite32" , CDB_Write_Color ,
        "The WRITE (32) command requests that the device\n" + 
        "server  transfer the specified logical block(s)\n" +
        "from the data-out buffer and write them."],

    [0x000C , "WRITE AND VERIFY(32)", "ShowWriteVerify32" , CDB_WriteVerify_Color ,
        "The WRITE AND VERIFY (32) command requests that the device\n" + 
        "server transfer the specified logical block(s)\n" +
        "from the data-out buffer, write them and verify\n" +
        "that they are correctly written."],

    [0x000D , "WRITE SAME(32)", "ShowWriteSame32" , CDB_WriteSame_Color ,
        "The WRITE SAME(32) command requests that the device\n" + 
        "server transfer a single logical block\n" +
        "from the data-out buffer and write the\n" +
        "contents of that logical block"]

]; 
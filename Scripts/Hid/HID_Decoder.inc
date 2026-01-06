#*******************************************************************************
#
#  FILENAME: Hid_Decoder.inc
#
#  Copyright (c) 2016, Teledyne-LeCroy - All Rights Reserved
#
#  DESCRIPTION
#    This is the HID Decoder file
#
#  FILE HISTORY:
#         June 2016 Created - SM
#         Dec  2016 Edit    - FJ
#      
#*******************************************************************************

%include "..\Standard\Hid_descr.inc"
%include "HIDReportDescriptor_EditMe.inc"
%include "HIDCommon.inc"

set ByteOffset = 0;
set BitOffset = 0;
set UsageMinimum = 0;
set UsageMaximum = 0;
set ReportCount = 0;
set ReportSize = 0;
set ReportTagData = 0;
set ReportID = 0;
set UsageIndex = 0;
set LastUsage = 0; # This is the index of usage names stored in following usage name list, this index has a one to one relationship with usage input/output data
set UsageName = []; # Usage names are stored in this list to be used when adding usage input/output data
set UsageNameCaption = [0xFFFF, ""]; # UsageId, UsageName
set UsagePageId = 0;
set UsagePageName = "";
set UsagePageIdChanged = 0;

ProcessHIDReportDescriptor(UsbEndpType, UsbEndpDir)
{
    ByteOffset = 0;
    BitOffset = 0;
    UsageIndex = 0;
    UsageMinimum = 0;
    UsageMaximum = 0;
    UsagePageIdChanged = 0;
    ReportTagData = 0;
    ReportID = 0;
        
    item_tag = 0;
    item_tag_data = 0;
    
    for(index = 0; index < sizeof (HIDReportDescriptorItems); index++)
    {
        item_tag = (HIDReportDescriptorItems[index][0]) & 0xFC; #remove first two bitss, which identify the size
        item_tag_data = HIDReportDescriptorItems[index][1];
                              
        _rowHIDReportTags = Find(HIDReportTags, item_tag);
        if(_rowHIDReportTags != null)
        {
           CreateFields(item_tag, item_tag_data);
        }
    }        
}

DecodeGlobalItems(item_tag, item_tag_data)
{
    select
    {
        item_tag == REPORT_TAG_USAGE_MIN : UsageMinimum = item_tag_data;
        item_tag == REPORT_TAG_USAGE_MAX : UsageMaximum = item_tag_data;
        item_tag == REPORT_TAG_REPORT_COUNT : ReportCount = item_tag_data;
        item_tag == REPORT_TAG_REPORT_SIZE : ReportSize = item_tag_data;        
    };
}

CreateFields(item_tag, item_tag_data)
{
    if(item_tag == REPORT_TAG_USAGE_PAGE)
    {
        _row = Find(HIDUsageTable, item_tag_data);
        UsagePageId = _row[0];
        UsagePageName = _row[1];               
        UsagePageIdChanged = 1; 
                       
        # When a Usage Page is encountered Usage list has to be emptied, as the UsageNames stored in the list are not meant to be used as input/output tags
        LastUsage = 0;
        UsageName = [];
    }
    else if(item_tag == REPORT_TAG_USAGE)
    {
        # Queue Usages to be added later when corresponding input/output tags are added        
        UsageId = item_tag_data;
        ReportData = UsageId;
        _row = Find(HIDUsageTable, UsagePageId);
        UsageName += Call (_row[2] );
        last_index = sizeof(UsageNameCaption);
        UsageNameCaption[last_index][0] = item_tag_data;
        UsageNameCaption[last_index][1] = Call (_row[2] );
        LastUsage++;
        
        UsageMinimum = 0;
        UsageMaximum = 0;             
    }
    else if(item_tag == REPORT_TAG_REPORT_ID && item_tag_data > 0)
    {
        AddSeparator();      
        ReportTagData = item_tag_data;
        
        ReportID = GetDataByte(ByteOffset);        
        if(ReportID == ReportTagData)
        {
            SetCellColor(HIDCaptionColor);        
            AddHIDField(ByteOffset, 1, 0, 0, "Report ID", "Report ID", HIDCaptionColor, 0, UsagePageId);
            ByteOffset++;
                    
            RestoreCellColor();
            AddSeparator();                           
        }        
    }       
    else if(item_tag == REPORT_TAG_FEATURE)
    {
        # When a Usage Page is encountered Usage list has to be emptied, as the UsageNames stored in the list are not meant to be used as input/output tags
        LastUsage = 0;
        UsageName = [];
        
        AddCaptionCell("Feature", Format(" (0x%02X) ", item_tag_data), Format(" (0x%02X) ", item_tag_data), _MONOCOLOR);        
    }
    else if( UsbEndpType == "Interrupt" && ReportTagData == ReportID &&
            ((UsbEndpDir == "In" && item_tag == REPORT_TAG_INPUT) || (UsbEndpDir == "Out" && item_tag == REPORT_TAG_OUTPUT))
           )
    {                 
        if(UsagePageIdChanged)
        {
            AddSeparator();
            SetCellColor(HIDCaptionColor);
            AddCaptionCell("Usage Page ", UsagePageName + Format(" (0x%02X)", UsagePageId    ), UsagePageName + Format(" (0x%02X)", UsagePageId), _MONOCOLOR);
            RestoreCellColor();
            UsagePageIdChanged = 0;
        }
               
        # Add relevant queued Usages
        #for(usage_caption_index = 2; usage_caption_index < sizeof(UsageNameCaption); usage_caption_index++)
        #{
        #    AddSeparator();
        #    SetCellColor(HIDCaptionColor);
        #    _row = UsageNameCaption[usage_caption_index];
        #    AddCaptionCell("Usage ", UsageNameCaption[usage_caption_index][1] + Format(" (0x%02X)", UsageNameCaption[usage_caption_index][0]), UsageNameCaption[usage_caption_index][1] + Format(" (0x%02X)", UsageNameCaption[usage_caption_index][0]), _MONOCOLOR);
        #    RestoreCellColor();
        #}
        AddSeparator();
       
        UsageNameCaption = [0xFFFF, ""];
         
        # Add HID fields
        for(field_index = 0; field_index < ReportCount; field_index++)
        {
            # make field captions
            is_variable_field = (item_tag_data & 0x2);        
            if(UsagePageId && is_variable_field)
            {
                if(UsageMinimum > 0)
                {
                    _row = Find(HIDUsageTable, UsagePageId);
                    ReportData = UsageMinimum + field_index; 
                    field_name = Call (_row[2] );
                }                
                else
                {
                    if(field_index < LastUsage)
                    {
                        if((LastUsage > ReportCount))
                            usage_name_index = (LastUsage - ReportCount) + field_index;
                        else
                            usage_name_index = field_index;
                    }
                    else
                        usage_name_index = LastUsage - 1;
                
                    field_name = UsageName[usage_name_index];
                }
            }
            else if(UsagePageId) # Retrieve field names from corresponding Usage Page
            {
                usage_index_txt = "";
                if(UsageMinimum > 0)
                {
                    usage_index_txt = Format(" %d", field_index + 1);
                }
                field_name = UsagePageName;
                field_name += usage_index_txt;
            }                   
                        
            #extract field values            
            if(ReportSize % 8 == 0) # If field size is interger multiple of a byte
            {
                byte_len = ReportSize / 8;
                AddHIDField(ByteOffset, byte_len, 0, 0, field_name, field_name, HIDCellColor, !is_variable_field, UsagePageId);
                ByteOffset += byte_len;
                BitOffset = 0;
            }
            else    # If field size is not interger multiple of a byte
            {
                AddHIDField(ByteOffset, 0, BitOffset, ReportSize, field_name, field_name, HIDCellColor, !is_variable_field, UsagePageId);
                BitOffset += ReportSize;
                if(BitOffset >= 8)
                {
                    ByteOffset += (BitOffset / 8);
                    BitOffset  = BitOffset % 8;                    
                }
            }
        }                        
              
        # When a Usage Page is encountered Usage list has to be emptied, as the UsageNames stored in the list are not meant to be used as input/output tags
        LastUsage = 0;
        UsageName = [];
    }
    else
    {   
        DecodeGlobalItems(item_tag, item_tag_data);    
    }
}

####################################################################################
#                       USBTracer specific caption cell                            #
####################################################################################

AddSpecCaptionCell(caption, text, tooltip, FieldColor, addparam, addparam1, addparam2 )
{
    AddCell(caption, text, tooltip, FieldColor, _USBBULK_HEADER, addparam, addparam1, addparam2 );
    return 1;
}
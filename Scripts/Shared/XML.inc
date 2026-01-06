#  Copyright (c) 2006, LeCroy Corp. PSG - All Rights Reserved
#
#  XML.inc
#
#  XML supporting functions
#


#################################################################
#                     XML functions                             #
#################################################################

const XML_CELL_COLOR  = RGB( 0, 0, 125 );
const MAX_NODE_NUMBER = 15; # specifies the maximum number of XML nodes to process
set SpecificationCommandTable = null;


ShowXMLCells( source )
{  
   FieldColor = XML_CELL_COLOR;
   
    # just for testing - let's hardcode XML source
#     source  = "<?xml version=\"1.0\"?>\n";
#     source += "<dps xmlns=\"http://www.cipa.jp/dps/schema/\">\n";
#     source += "   <input>\n";
#     source += "    <startJob>\n";
#     source += "      <jobConfig>\n";
#     source += "          <fileType>53180000</fileType> <!-- fileType: 53180000 (DPOF) -->\n";
#     source += "      </jobConfig>\n";
#     source += "\n";      
#     source += "      <printInfo>\n";
#     source += "          <fileID>00000002</fileID>\n";
#     source += "      </printInfo>\n";
#     source += "    </startJob>\n";
#     source += "   </input>\n";
#     source  += "</dps>\n";
   
   
   # parse the source and get XML node list...
   node_list = GetXMLEndNodes( source );
   
   # error checking...
   # if the first entry is null then the second one contains error description
   #
   if( node_list[0] == null && node_list[1] != null)
   {
        error_message = node_list[1];
        
        # TBD: show somehow error message and return... 
        # like below:
        AddXMLCaptionCell( "XML Parsing", "Error", error_message, source, _ERROR );
        
        return 0; 
   }
   
   #
   # at this point we parsed XML source without errors
   #
   
   
   # show caption cell
   AddXMLCaptionCell( "XML", "Nodes", GetXMLTooltip( node_list ), source );
   
      
   # process XML nodes...
   
   node_count = 0;
   
   for( item = first(node_list); more(node_list) && (node_count < MAX_NODE_NUMBER); item = next(node_list) )
   {
        node_name = item[0];
        node_text = item[1];        
        
        AddXMLCell( node_name, node_text, GetNodeTooltip( node_name, node_text ), source );
        
        node_count++;
   }   
}


AddXMLCaptionCell( caption , text, tooltip, xml_source, addparam )
{
    AddCell( caption, text, tooltip, FieldColor, _USB_XML_CELL, xml_source, _MONOCOLOR, addparam ); 
}



AddXMLCell( caption , text, tooltip, xml_source, addparam )
{
    if( SimpleShowItem() ) # show in expanded state only                  
          AddCell( caption, text, tooltip, FieldColor, _USB_XML_CELL, xml_source, addparam );    
}



GetNodeTooltip( node_name, node_text )
{

    tooltip  = "<HTML>";
    
    tooltip += "<TABLE width=\"200\">";
    
    tooltip += "<TR align=center><TD><B>Type</B></TD><TD><B>Value</B></TD><TD><B>Description</B></TD></TR>";
    result = Find(SpecificationCommandTable, node_name);
    if (result[0] == null) # we did not find the corresponding command, 
    {
	  	# use generic tooltip
        tooltip += "<TR><TD><B>Node Name</B></TD><TD>" + node_name + "</TD><TD>N/A</TD></TR>";
        tooltip += "<TR><TD><B>Node Text</B></TD><TD>" + node_text + "</TD><TD>N/A</TD></TR>";
    }
    else
    {
        # To insert line break if the description is too long

        desc_length = sizeof(result[1]);
        tempString = result[1];
        description = "";
        while (desc_length > 50)
        {
            # now we need to find the next space or the end of description
            found = 0;
            for (i = 50 ; i <= desc_length && found == 0; i++)
            {
                stringChar = Mid(tempString, i, 1);
                if (stringChar == " ")
                    found = 1;
            }
            if (found == 1)
            {
                # if we find a space, just replace it with "\n"
                description += Left(tempString, i - 1); # i got an extra of ++
                description += "\n";
                tempString = Right(tempString, desc_length - i);
                desc_length -= i;
            }
            else
            {
                # we just exit the loop and add the whole thing
                desc_length = 0;
            }
        }
        description += tempString;

        tooltip += "<TR><TD><B>Node Name</B></TD><TD>" + node_name + "</TD><TD>" + description + "</TD></TR>";
        if (result[2] != null)
        {
            tooltip += "<TR><TD><B>Node Text</B></TD><TD>" + Call(result[2], [node_text]) + "</TD>";
        }
        else
        {
            tooltip +="<TR><TD><B>Node Text</B></TD><TD>" + node_text + "</TD>";
        }
        if (result[3] != null)
        {
            tooltip +="<TD>" + Call(result[3], [node_text]) + "</TD></TR>";
        }
        else
        {
            tooltip += "<TD>" + node_text + "</TD></TR>";
        }
    }
    tooltip += "</TABLE>";
    tooltip += "</HTML>";
    return tooltip;
}



GetXMLTooltip( node_list )
{    
    # here should be the code that build HTML table based on node list like below :
    if (node_list[0] == null)
        return "The XML file does not contain values for any elements";
    
    tooltip  = "<HTML>";
    tooltip += "<b>XML elements:\n</b>";
    
    tooltip += "<TABLE>";
    
    tooltip += "<TR align=center><TD><B>Element</B></TD><TD><B>Value</B></TD></TR>";
    
    node_count = 0;
    
    for( item = first(node_list); more(node_list) && (node_count < MAX_NODE_NUMBER); item = next(node_list) )
    {
        node_name = item[0];
        node_text = item[1];        
        
        tooltip += "<TR><TD><font color=#0000FF><B>" + node_name + "</B></font></TD><TD>" + node_text + "</TD></TR>";        
        node_count++; 
    }    
    
    tooltip += "</TABLE>";
    tooltip += "</HTML>";    
    
    return tooltip;
}

#################################################################

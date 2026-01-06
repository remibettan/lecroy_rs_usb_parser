#########################################################################################
#                                                                                       #
#  Copyright (c) 1998 - 2010, LeCroy Corporation - All Rights Reserved                  #
#                                                                                       #
#  html.inc                                                                             #
#                                                                                       #
#   Verification script header                                                          #
#                                                                                       #
#   Brief Description: This header provides helper functions and variables              #
#   used by sample scripts utilizing output to HTML files.                              #
#                                                                                       #
#########################################################################################



###########################################################################
#                            Global Variables                             #
###########################################################################

# HTML file handle
set HTMLFile = 0;

###########################################################################



################################################################
#                   HTML file functions                        #
################################################################


H_OpenFile( path, title )
{
    HTMLFile = OpenFile( path );    
    WriteString( HTMLFile, "<html><head><title>" + title + "</title></head><body>" );    
}



H_CloseFile()
{
   WriteString( HTMLFile, "</body></html>" );
   CloseFile( HTMLFile );
}



H_Line      ( line    )         {  WriteString( HTMLFile, line + "<br>" );                   }
H_Table     ( options )         {  WriteString( HTMLFile, "<table " + options +  " >" );     }
H_EndTable  ()                  {  WriteString( HTMLFile, "</table>" );                      }

H_Row       ( options )         {  WriteString( HTMLFile, "<tr " + options +  " >" );        }
H_EndRow    ( )                 {  WriteString( HTMLFile, "</tr>" );                         }

H_Cell      ( text, options )   {  WriteString( HTMLFile, "<td " + options +  " >" + text ); }
H_EndCell   ()                  {  WriteString( HTMLFile, "</td>" );                         }





%{ 
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <iostream>
  #include "parser.h"
%} 
%option case-insensitive
%option noyywrap

/* Extras */
numero   [0-9]+







/****************************** Rule Section ******************************/
%% 
{numero}             {return(numero); } 
"="                  {return(igual);}

"mkdisk"             {return(mkdisk);}
"-size"    	     {return(size);}
"-f"     	     {return(fit);}
"-u"     	     {printf("Caracter %s jiji\n ", yytext);return(units);}
"-path"   	     {return(path);}




"quit"               {yyterminate();}
.                    {printf("Caracter %s no admitido\n ", yytext);}
%%













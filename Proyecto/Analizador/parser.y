%{ 
   #include<iostream>
   #include <stdio.h>
   using namespace std;

   #include "mkdisk.h"

   mkdisk *mkdisco = new mkdisk();

   int yylex();
   int yyerror(const char* msg){
        cout<< "Syntax Error: " << msg << endl;
        return 0;
   }
%} 
  
%define parse.error verbose

/*
%union{
   char TEXT[500];
   class mkdisk *mkdisk;
}
*/


/******************************* TOKENS *******************************/
%token numero igual mkdisk size fit units path
  

  
%start line
/******************************* PRODUCCIONES *******************************/
%% 
  

line: mkdisk MKDISK { cout << "entro al mkdisk "<< endl;}
;

MKDISK:size igual numero  { cout << ">1 "<<$1<< endl;}
      |fit 	{ cout << ">2 "<<$1<< endl;}
      |units 	{ cout << ">3 "<<$1<< endl;}
      |path 	{ cout << ">4 "<<$1<< endl;}
;	






  
%%

preprocessor #.*
identifier [_a-zA-Z][_a-zA-Z0-9]*
keyword int|float|char|double|while\(.*\)|for\(.*\)|do|if\(.*\)|break|continue|void|switch\(.*\)|case|long|struct|const|typedef|return|else|goto
comment "/*".*"*/"
asmnt_op "="|"+="|"-="|"/=""*="
relop "=="|"!="|"<"|"<="|">"|">="
arith_op [+\-*/%]
integer [-+]?([0-9]*)
string \".*\"
punct [;\.,]
%%
{string} {printf("\n String:\t%s",yytext);}
{keyword} {printf("\n Keyword:\t%s",yytext);}
{preprocessor} {printf("\n Preprocessor directive:\t%s",yytext);}
{comment} {printf("\n Comment:\t%s",yytext);}
{identifier}\( {printf("\n Function:\t%s",yytext);}
\{  {printf("\n begin block");}
\}  {printf("\n end block");}
{relop} {printf("\nRelational Operator:\t%s",yytext);}
{asmnt_op} {printf("\nAssignment Operator:\t%s",yytext);}
{arith_op} {printf("\nArithmetic Operator:\t%s",yytext);}
{identifier}: {printf("\nLabel:\t%s",yytext);}
{identifier} {printf("\nvariable:\t%s",yytext);}
{integer} {printf("\nInteger number:\t%s",yytext);}
\) {printf("\n End of function\t%s",yytext);}
{punct} {("\n Punctuation:\t%s",yytext);}
%%
int main(int argc,char **argv)
{
        FILE *file;
        file=fopen(argv[1],"r");
        if(!file)
        {
                printf("file open error");
                exit(0);
        }
        yyin=file;
        yylex();
        printf("\n");
        return 0;
}
int yywrap()
{
        return 1;
}

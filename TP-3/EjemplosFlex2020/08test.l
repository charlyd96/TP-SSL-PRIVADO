%top{
#include "tokens_08.h"
}
%option outfile="08scanner.c"
%option header-file="08scanner.h"
%option nodefault

L  [[:alpha:]]
D  [0-9]
LD [[:alnum:]]
S  [[:space:]]
O  [[:^alnum:]]{-}[[:space:]#]

%%
{L}{LD}*     return ID;
{D}+         return CTE;
#            return NUMERAL;
{O}+         return ERROR;
{S}+         /*ignorar*/


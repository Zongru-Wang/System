// Implement a working parser in this file that splits text into individual tokens.
/* strtok example */

#include <stdio.h>
#include <string.h>

int main ()
{
    char str[20];
    char * pch;
    scanf("%[^\n]s", &str);

    pch = strtok (str," ");
    while (pch != NULL)
    {
        printf ("%s\n",pch);
        pch = strtok (NULL, " ");
    }
    return 0;
}
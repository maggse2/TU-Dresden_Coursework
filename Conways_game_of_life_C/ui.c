#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>
#include <string.h>
int UserInput1()
{
    char eingabe1[2];
    char str1[2]= "q";
    int ret[6];
    fgets(eingabe1,2,stdin);
    ret[0] = strcmp(eingabe1, str1);
    if (ret[0] == 0)
    {
        printf("q wurde eingegeben: %s", eingabe1);
        exit(0);                                       	 
    }
    return 0;
}
int UserInput2()
{
    char eingabe2[2];
    char pausieren[2];
    char str2[2] = ".";
    char str3[2] = " ";
    int ret[6];
    fgets(eingabe2, 2, stdin);
    ret[2] = strcmp(eingabe2, str2);
    if (ret[2] == 0)
    {
        printf(". wurde eingegeben: %s", eingabe2);

        do
        {
            fgets(pausieren,2,stdin);
            ret[3] = strcmp(pausieren, str3);
        }
        while (ret[3]!= 0);
    }
    return 0;
}

int UserInput3()
{
    char eingabe3[2];
    char pausieren[2];
    char str3[2] = " ";
    int ret[6];
    fgets(eingabe3, 2, stdin);
    ret[3] = strcmp(eingabe3, str3);
    if(ret[3]== 0)
    {
        printf("Leerzeichen wurde eingegeben: %s", eingabe3);

        do
        {
            fgets(pausieren,2,stdin);
            ret[4] = strcmp(pausieren, str3);


        }
        while (ret[4]!= 0);

    }
    return 0;
}

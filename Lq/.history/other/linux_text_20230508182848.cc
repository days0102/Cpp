#include <stdlib.h>

#include <stdio.h>

#include <string.h>

char *upcase(char *string, int length);

int main(void)

{
    char *buf, *newstr;

    /*
    1. 这里初始化字符数组错误
    */
    char oldstr1[] = {“abcdefg”};
    char oldstr2[] = {“xyz”};

    int counter;

    buf = malloc(15);

    strcpy(buf, ”CHANGE STRINGS.”);

    fprintf(stdout, “% s\n”, buf);

    free(buf);

    for (counter = 0; counter < sizeof(oldstr1); counter++)

    {
        putchar(oldstr1[counter]);

        putchar(oldstr2[counter]);
    }

    newstr = upcase(oldstr1, sizeof(oldstr1));

    fprintf(stdout, "NEW STRING 1 : % s.\n", newstr);

    newstr = upcase(oldstr2, sizeof(oldstr2));

    fprintf(stdout,"NEW STRING 2 : % s.\n", newstr);

    free(newstr);

    strcpy(buf, “THE END.”);

    fprintf(stdout, “% s\n”, buf);

    free(buf);
}

char *upcase(char *string, int length)

{
    char *newstring;

    char temp;

    int counter;

    newstring = calloc(length, sizeof(char));

    for (counter = 0; counter < length; counter++)

    {
        temp = *(string + counter);

        if (temp >= 97 && temp <= 122)

            *(newstring + counter) = temp - 32;

        else

            *(newstring + counter) = temp;
    }

    return newstring;
}
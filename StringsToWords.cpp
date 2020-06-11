//
// Created by mby on 11/06/2020.
//
#include "StringsToWords.h"
#include <stdio.h>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <iostream>

/* A function that prints given number in words */
std::string convert_to_words(std::string c,std::size_t start ,std::size_t end)
{
    if(end==0){
        end=c.size();
    }
    char* num=new char[end-start];
    for (unsigned int j = start; j < end; ++j) {
        num[j-start]=c[j];
    }
    int len = strlen(num); // Get number of digits in given number

    /* Base cases */
    if (len == 0) {
        throw ;
    }
    if (len > 4) {
        throw ;
    }

    /* The first string is not used, it is to make
        array indexing simple */
    char* single_digits[] = { (char*)"zero", (char*)"one", (char*)"two",
                              (char*)"three", (char*)"four",(char*)"five",
                              (char*)"six", (char*)"seven", (char*)"eight", (char*)"nine" };

    /* The first string is not used, it is to make
        array indexing simple */
    char* two_digits[] = { (char*)"", (char*)"ten", (char*)"eleven",(char*) "twelve",
                           (char*)"thirteen", (char*)"fourteen",
                           (char*)"fifteen", (char*)"sixteen",
                           (char*)"seventeen", (char*)"eighteen", (char*)"nineteen" };

    /* The first two string are not used, they are to make
        array indexing simple*/
    char* tens_multiple[] = { (char*)"", (char*)"", (char*)"twenty", (char*)"thirty", (char*)"forty", (char*)"fifty",
                              (char*)"sixty", (char*)"seventy", (char*)"eighty", (char*)"ninety" };

    char* tens_power[] = { (char*)"hundred", (char*)"thousand" };

    /* Used for debugging purpose only */
//    printf("\n%s: ", num);

    /* For single digit number */
    if (len == 1) {
        printf("%s\n", single_digits[*num - '0']);
        return num;
    }

    /* Iterate while num is not '\0' */
    while (*num != '\0') {

        /* Code path for first 2 digits */
        if (len >= 3) {
            if (*num - '0' != 0) {
                printf("%s ", single_digits[*num - '0']);
                printf("%s ", tens_power[len - 3]); // here len can be 3 or 4
            }
            --len;
        }

            /* Code path for last 2 digits */
        else {
            /* Need to explicitly handle 10-19. Sum of the two digits is
            used as index of "two_digits" array of strings */
            if (*num == '1') {
                int sum = *num - '0' + *(num + 1) - '0';
                printf("%s\n", two_digits[sum]);
                return num;
            }

                /* Need to explicitely handle 20 */
            else if (*num == '2' && *(num + 1) == '0') {
                printf("twenty\n");
                return num;
            }

                /* Rest of the two digit numbers i.e., 21 to 99 */
            else {
                int i = *num - '0';
                printf("%s ", i ? tens_multiple[i] : "");
                ++num;
                if (*num != '0')
                    printf("%s ", single_digits[*num - '0']);
            }
        }
        ++num;
    }
    return num;
}




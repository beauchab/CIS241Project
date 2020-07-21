/**********************************************************************
Name: fileHelper.h
Description: This is a library of file functions to help the
             file Separator program.
@author - Green Team SS20 CIS241
@updated - 6/25/2020
**********************************************************************/
#ifndef FILESEPERATOR_FILEHELPER_H
#define FILESEPERATOR_FILEHELPER_H
//Includes
#include <stdio.h>
#include <string.h>
#include "dataHelper.h"
//Function Prototypes
void readFileData(FILE *fp, dat d);

/**********************************************************************
Name: readFileData
Description: This program takes an input of a file pointer to the
             classData.csv file and a multidimensional array. It
             parses through this file and separates the file into its
             constituent elements.
@author - Brendan P. Beauchamp
@author - Kendra Haan
@updated - 6/25/2020
@param - FILE *fp
                                This is a pointer  to the
                                classData.csv file which contains the
                                input data for the project.
@param - char arP[2330][5][20]
                                This is an array which contains the
                                file data after it has been read.
@return - void
**********************************************************************/
void readFileData(FILE *fp, dat d)
{
    char buff[200];
    char delim[2] = ",";
    int n = 0, m = 0;

    //Read Header
    fgets(buff, sizeof(buff), fp);

    //read in a line
    while (fgets(buff, sizeof(buff), fp) != NULL)
    {
        //Tokenize line into array elements
        //Tokenize user input as stated in midterm file
        strcpy(&d.arIn[m][n][0], strtok(buff, delim));
        parseData(n, d.arIn[m][n], d.parsedData[m]);

        n++;
        while (n < 5)
        {
            strcpy(&d.arIn[m][n][0], strtok(NULL, delim));
            parseData(n, d.arIn[m][n], d.parsedData[m]);

            n++;
        }
        n = 0;
        m++;
    }
}

#endif //FILESEPERATOR_FILEHELPER_H

/**********************************************************************
Name: printHelper.h
Description: This is a library of print functions to help the
             file Separator program.
@author - Green Team SS20 CIS241
@updated - 6/25/2020
**********************************************************************/
#ifndef FILESEPERATOR_PRINTHELPER_H
#define FILESEPERATOR_PRINTHELPER_H
//Includes
#include <stdio.h>
#include <string.h>
//Function Prototypes
void printData(char arP[2330][5][20]);
int printTab(void);
int printNewLine(void);
void printIntro();
void printGoodBye();

/**********************************************************************
Name: printData
Description: This is a function used to print the input data to the
             screen
@author - Brendan P. Beauchamp
@author - Kendra Haan
@updated - 6/25/2020
@param - char arP[2330][5][20]
                                This is an array which contains the
                                file data after it has been read.
@return - void
**********************************************************************/
void printData(char arP[2330][5][20])
{
    int i,j;
    int (*pT)(void) = &printTab;
    int (*pN)(void) = &printNewLine;

    for(i=0; i<2330; i++)
    {
        for(j=0; j<5; j++)
        {
            printf("%s", &arP[i][j][0]);
            (j==4) ? pN() : pT();
        }
    }
}

/**********************************************************************
Name: printTab
Description: This is a helper function to print a tab.
@author - Brendan P. Beauchamp
@updated - 6/24/2020
@param - void
@return - void
**********************************************************************/
int printTab(void)
{
    printf("\t");
    return 0;
}

/**********************************************************************
Name: printNewLine
Description: This is a helper function to print a new line.
@author - Brendan P. Beauchamp
@updated - 6/24/2020
@param - void
@return - void
**********************************************************************/
int printNewLine(void)
{
    printf("\n");
    return 0;
}

/**********************************************************************
Name:printIntro
Description: This function prints an introduction message to the user
@author - Brendan P. Beauchamp
@updated - 5/20/2020
@param - void
@return - void
**********************************************************************/
void printIntro()
{
    printf("Welcome to the Green Team file separator. This \n");
    printf("program separates classData and allows for modification\n");
    printf("CIS-241 taught by Dr. Vijay Bhuse\n\n");
}

/**********************************************************************
Name:printGoodBye
Description: This function prints a good bye message to the user
@author - Brendan P. Beauchamp
@updated - 5/20/2020
@param - void
@return - void
**********************************************************************/
void printGoodBye()
{
    printf("\nThank you for using File Separator!\n");
    printf("Have a nice day!\n");
}
#endif //FILESEPERATOR_PRINTHELPER_H
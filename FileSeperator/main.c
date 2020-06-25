/**********************************************************************
Name: File Sperator
Description: This Program opens the data given to us by the professor,
             and ...
@author - Green Team SS20 CIS241
@updated - 6/25/2020
@param - classData.csv
@return -
**********************************************************************/
//Included Libraries
#include <stdio.h>
#include <string.h>
#include "printHelper.h"
#include "fileHelper.h"
#include <stdlib.h>

//Function Prototypes
void stateMachine(struct stateControl *u, struct theData *d, struct files *f);
void exitProgram(struct stateControl *u, struct files *f);
int userContinue();

//Structs
struct stateControl {
    int state;
    int flags[5];
    int userContinue = 1;
};
struct outData {
    char ***arOut;
    int length;
    int width;
    int depth;
};
struct theData {
    char arIn[2330][5][20];
    struct outData oD;
};
struct files{
    FILE *inFileP;
    FILE *outFileP;
};

//State Definitions
#define READ_INPUT 0
#define PRINT_DATA 1
#define EXIT  2

//choose the two element rows as args
int main()
{
    struct stateControl sC;
    struct theData d;
    struct files f;

    //char* arOut[2330][]


    f.inFileP = fopen("classData.csv", "r");

    // CLion is giving me a hard time with printing this fixed it for me, you may comment it out.
    //setbuf(stdout, NULL);
    do
    {
        stateMachine(&sC, &d, &f);
    }
    while(sC.userContinue);



    //readFileData(f.inFileP, d.arIn);
    //printData(d.arIn);

    printf("Hello, World!\n");
    return 0;
}

/**********************************************************************
Name:userContinue
Description: This function checks if the user would like to continue
             running the program
@author - Brendan P. Beauchamp
@updated - 5/20/2020
@param - void
@return - int ans
                This is a value which states 1 if the user would like
                to continue running the program or 0 if the would not.
**********************************************************************/
int userContinue()
{
    int ans = 0;

    printf("Would you like to run the program again?\n");
    printf("Type 1 for yes, 0 for no:");
    scanf("%d", &ans);

    if(ans != 1)
    {
        ans = 0;
    }

    return ans;
}

/**********************************************************************
Name:userContinue
Description: This function checks if the user would like to continue
             running the program
@author - Brendan P. Beauchamp
@updated - 5/20/2020
@param - void
@return - int ans
                This is a value which states 1 if the user would like
                to continue running the program or 0 if the would not.
**********************************************************************/
int receiveInput()
{
    int ans = 0;

    printf("What would you like to do?\n");
    printf("Options:");

    //FIXME
    //Function for Displaying Options

    scanf("%d", &ans);

    if(ans != 1)
    {
        ans = 0;
    }

    return ans;
}

/**********************************************************************
Name: stateMachine
Description: This is the state machine for the program.
@author - Brendan P. Beauchamp
@updated - 6/25/2020
@param - struct stateControl *u
                            This is a structure which contains
                            variables used in state control
@param - struct theData *d
                            This is a structure containing data for
                            the main program, and parsed data
@param - struct files *f
                            This is a structure containing data for
                            open files in the program
@return - void
**********************************************************************/
void stateMachine(struct stateControl *u, struct theData *d, struct files *f)
{

    switch(u->state) {

        case READ_INPUT  :
            readFileData(f->inFileP,d->arIn);
            break;

        case PRINT_DATA  :
            printData(d->arIn);
            break;

        case EXIT       :
            //Function for closing files and setting the control structure to exit
            exitProgram(u, f);
            break;

        /* you can have any number of case statements */

        default :
            //FIXME
            //Function for stating improper input

            break;
    }
}

/**********************************************************************
Name:
Description:
@author - Brendan P. Beauchamp
@updated - 6/25/2020
@param - struct stateControl *u
                            This is a structure which contains
                            variables used in state control
@param - struct files *f
                            This is a structure containing data for
                            open files in the program
@return - void
**********************************************************************/
void exitProgram(struct stateControl *u, struct files *f)
{
    u->userContinue = 0;
    fclose(f->inFileP);
}
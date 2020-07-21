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
#include "pythagoreanMeans.h"
#include <stdlib.h>
#include "linearRegression.h"
#include "usefulStats.h"
#include "dataHelper.h"

//MAIN State Machine Definitions
#define READ_INPUT        0
#define PRINT_DATA        1//FIXME THIS SHOULD LAUNCH A SECONDARY STATE MACHINE (i.e. What data you want to print?)
#define LINEAR_REGRESSION 2
#define KMEANS            3
#define OUTLIER_DETECTION 4
#define EXIT              5

//Structs
struct stateControl {
    int state;
    int flags[5];
    int userContinue;
};
struct files{
    FILE *inFileP;
    FILE *outFileP;
};

//Function Prototypes
void stateMachine(struct stateControl *u, dat *d, struct files *f);
void exitProgram(struct stateControl *u, struct files *f);
int userContinue();
int receiveInput(struct stateControl *u);

//choose the two element rows as args
int main()
{
    struct stateControl sC;
    dat d = { .arIn = {0}, .parsedData = {0} };
    struct files f;
    sC.userContinue = 1;
    sC.state = READ_INPUT;

    //char* arOut[2330][]


    f.inFileP = fopen("classData.csv", "r");

    // CLion is giving me a hard time with printing this fixed it for me, you may comment it out.
//    setbuf(stdout, NULL);
//    do
//    {
//        stateMachine(&sC, &d, &f);
//    }
//    while(receiveInput(&sC));



    readFileData(f.inFileP, &d);
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
Name:recieveInput
Description: This function is used to determine what the user would
             like to do in the main menu
@author - Brendan P. Beauchamp
@updated - 7/17/2020
@param - struct stateControl *u
                This is a structure which contains variables useful to
                maintaining the state of the program.
@return - int ans
                This is a value which states 1 if the user would like
                to continue running the program or 0 if the would not.
**********************************************************************/
int receiveInput(struct stateControl *u)
{
    int ans;
    int invalid = 1;
    do {
        printf("MAIN: STATE MACHINE\n");
        printf("What would you like to do?\n");
        printf("Options:\n");

        //FIXME INCLUDE NEW OPTION EVERY TIME ONE IS MADE
        printf("0:\tRead Data\n");
        printf("1:\tPrint Data\n");
        printf("2:\tLinear Regression\n");
        printf("3:\tKMeans\n");
        printf("4:\tOutlier Detection\n");
        printf("5:\tEXIT\n");

        scanf("%d", &ans);

        //Answer is incorrect
        if(ans < 0 || ans > 5 )
        {
            printf("\nINVALID INPUT!\n");
        } else{
            invalid = 0;
        }
    }while(invalid);

    //Set State
    u->state = ans;

    return u->state == EXIT ? 0 : 1;
}

/**********************************************************************
Name: stateMachine
Description: This is the state machine for the main menu.
@author - Brendan P. Beauchamp
@updated - 6/25/2020
@param - struct stateControl *u
                            This is a structure which contains
                            variables used in state control
@param - dat *d
                            This is a structure containing data for
                            the main program, and parsed data
@param - struct files *f
                            This is a structure containing data for
                            open files in the program
@return - void
**********************************************************************/
void stateMachine(struct stateControl *u, dat *d, struct files *f)
{
    switch(u->state) {

        case READ_INPUT  :
            //State Machine for Reading Input
            readFileData(f->inFileP, d);
            break;

        case PRINT_DATA  :
            //State Machine for Printing Data
            printData(d->arIn);
            break;

        case LINEAR_REGRESSION  :
            //State Machine for Linear Regression

            break;

        case KMEANS  :
            //State Machine for KMEANS

            break;

        case OUTLIER_DETECTION  :
            //State Machine for Outlier Detection

            break;

        case EXIT       :
            //Function for closing files and setting the control structure to exit
            exitProgram(u, f);
            break;

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

/*
int* dataLinerization(struct Data data[])
{
	int i = 0, j=0, date[foo(data)], month[foo(data)];
	static int newArray[][];
	while( i < foo(data))
	{
		month = strtok(data.date[i], "/");
		date[i] = strtok(NULL, "/");
		i++;
	}
	i=0;
	while(j < date[i])
	{
		newArray[j] = j + 1;
		j++;
	}
	return newArray;
}
 */
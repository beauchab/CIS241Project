/**********************************************************************
Name: SUBMENU_OutlierDetection.h
Description: This is a library which controls the Outlier Detection
             Sub Menu. It allows the user to perform a linear
             regression, analyze the regression based on selected
             input data, and exit.
@author - Green Team SS20 CIS241
@updated - 7/8/2020
**********************************************************************/
#ifndef FILESEPERATOR_SUBMENU_OUTLIERDETECTION_H
#define FILESEPERATOR_SUBMENU_OUTLIERDETECTION_H
//Included Libraries
#include <stdio.h>
#include <string.h>
#include "outlierDetection.h"
#include "globalDefinitions.h"
#include "usefulStats.h"
#include "dataHelper.h"
#include "globalDefinitions.h"

//State Definitions
#define OUTLIER_PRINT       0
#define OUTLIER_EXIT        1
//Structs
typedef struct Outlier_StateControl {
    int state;
    int userContinue;
}outlierSC;
typedef struct Outlier_DataPoints {
    char nameXY[40];
    lrCo *lrP;
    int xData;
    void *xDatVec[2330];
    int yData;
    void *yDatVec[2330];
}outlierDP;

//Function Prototypes
int outlierSub_receiveInput(outlierSC *u);
void outlierSub_exit(outlierSC *u);
int outlierSub_stateMachine(outlierSC *u, lrDP data);
/**********************************************************************
Name: outlierDetectionSubMenu
Description: This function is the main driver for the outlier detection
             submenu
@author - Nicholas Bernhardt, Brendan P. Beauchamp
@updated - 7/22/2020
@param - parDTok *dat[2330]
                This is the dataset read from Dr. Bhuse's input file
@return - void
**********************************************************************/
void outlierDetectionSubMenu(lrDP data)
{
    outlierSC session;
    session.userContinue = 1;
    while(outlierSub_receiveInput(&session))
    {
        outlierSub_stateMachine(&session, data);
    }
}
/**********************************************************************
Name:outlierSub_receiveInput
Description: This function is used to determine what the user would
             like to do in the linear regression sub menu
@author - Nicholas Bernhardt, Brendan P. Beauchamp
@updated - 7/17/2020
@param - outlierSC *u
                This is a structure which contains variables useful to
                maintaining the state of the outlier detection sub menu.
@return - int {1,0}
                This is a value which states 1 if the user would like
                to continue running the program or 0 if the would not.
**********************************************************************/
int outlierSub_receiveInput(outlierSC *u)
{
    int ans;
    int invalid = 1;
    do {
        printf("-_-_-_/ OUTLIER DETECTION /-_-_-_\n");
        printf("Options:\n");
        printf("0 -\tPrint Outliers\n");
        printf("1 -\tEXIT\n");
        printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");
        printf("What would you like to do?\n\n\t-> ");

        scanf("%d", &ans);
        printf("\n");

        //Answer is incorrect
        if(ans < 0 || ans > 2 )
            printf("\nINVALID INPUT!\n");
        else
            invalid = 0;
    }while(invalid);

    //Set State
    u->state = ans;

    return u->state == OUTLIER_EXIT ? 0 : 1;
}
/**********************************************************************
Name: outlierSub_stateMachine
Description: This is the state machine for the linear regression sub menu.
@author - Nicholas Bernhardt, Brendan P. Beauchamp
@updated - 7/22/2020
@param - outlierSC *u
                This is a structure which controls the state of the
                outlier detection sub menu state machine
@param - char dataSet[2330][5][20]
                This is the dataset read from Dr. Bhuse's input file
@return - int u->userContinue
                This variable states whether the user would like to
                continue running
**********************************************************************/
int outlierSub_stateMachine(outlierSC *u, lrDP data)
{
    switch(u->state) {

        case OUTLIER_PRINT  :
            //State Machine for printing the outliers
            outlierDetection(data);
            break;

        case OUTLIER_EXIT       :
            //Function for setting control structure to exit
            outlierSub_exit(u);
            break;

        default :
            //ERROR -> Exit state machine
            printf("\nERROR: EXITING LINEAR REGRESSION\n");
            u->state = OUTLIER_EXIT;
            break;
    }
    return u->userContinue;
}
/**********************************************************************
Name: outlierSub_exit
Description: This is a function which sets parameters to exit the
             outlier detection sub menu
@author - Nicholas Bernhardt, Brendan P. Beauchamp
@updated - 7/22/2020
@param - outlierSC *u
            This is a structure which controls the state of the
            outlier detection sub menu state machine
@return - void
**********************************************************************/
void outlierSub_exit(outlierSC *u)
{
    u->state = OUTLIER_EXIT;
    u->userContinue = 0;
}
#endif //FILESEPERATOR_SUBMENU_OUTLIERDETECTION_H

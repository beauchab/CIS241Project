//TODO
//FIXME CLEAN UP STATE MACHINE
//We can skip these if we run out of time
//FIXME IMPLEMENT LINKED LIST TO PASS DATA TO ANALYZE REGRESSION
//FIXME IMPLEMENT ANALYZE REGRESSION
/**********************************************************************
Name: SUBMENU_LinearRegression.h
Description: This is a library which controls the Linear Regression
             Sub Menu. It allows the user to perform a linear
             regression, analyze the regression based on selected
             input data, and exit.
@author - Green Team SS20 CIS241
@updated - 7/8/2020
**********************************************************************/
#ifndef FILESEPERATOR_SUBMENU_LINEARREGRESSION_H
#define FILESEPERATOR_SUBMENU_LINEARREGRESSION_H
//Included Libraries
#include <stdio.h>
#include <string.h>
#include "linearRegression.h"
#include "globalDefinitions.h"
#include "usefulStats.h"
#include "dataHelper.h"

//Function Prototypes
int lrSub_receiveInput(lrSC *u);
void lrSub_exit(lrSC *u);
int lrSub_stateMachine(lrSC *u, parDTok *dat[2330]);
void lrSub_performRegression(parDTok *dat[2330]);
char *lrSub_dataName(int i);
int lrSub_selectData(char* var);
void linearRegressionSubMenu(parDTok *dat[2330]);
lrCo castToRegression(int xTyp, int yTyp, void *xDat[2330], void *yDat[2330]);

/**********************************************************************
Name: linearRegressionSubMenu
Description: This function is the main driver for the linear regression
             submenu
@author - Brendan P. Beauchamp
@updated - 7/17/2020
@param - parDTok *dat[2330]
                This is the dataset read from Dr. Bhuse's input file
@return - void
**********************************************************************/
void linearRegressionSubMenu(parDTok *dat[2330])
{
    lrSC session;
    session.userContinue = 1;
    while(lrSub_receiveInput(&session))
    {
        lrSub_stateMachine(&session, dat);
    }
}
/**********************************************************************
Name:lrSub_receiveInput
Description: This function is used to determine what the user would
             like to do in the linear regression sub menu
@author - Brendan P. Beauchamp
@updated - 7/17/2020
@param - lrSC *u
                This is a structure which contains variables useful to
                maintaining the state of the linear regression sub menu.
@return - int {1,0}
                This is a value which states 1 if the user would like
                to continue running the program or 0 if the would not.
**********************************************************************/
int lrSub_receiveInput(lrSC *u)
{
    int ans;
    int invalid = 1;
    do {
        printf("Linear Regression: STATE MACHINE\n");
        printf("What would you like to do?\n");
        printf("Options:\n");
        printf("0:\tPerform Regression\n");
        printf("1:\tAnalyze Regression\n");
        printf("2:\tEXIT\n");

        printf("Answer:\t");
        scanf("%d", &ans);
        printf("\n");

        //Answer is incorrect
        if(ans < 0 || ans > 2 )
        {
            printf("\nINVALID INPUT!\n");
        } else{
            invalid = 0;
        }
    }while(invalid);

    //Set State
    u->state = ans;

    return u->state == LR_EXIT ? 0 : 1;
}
/**********************************************************************
Name: lrSub_stateMachine
Description: This is the state machine for the linear regression sub menu.
@author - Brendan P. Beauchamp
@updated - 7/17/2020
@param - lrSC *u
                This is a structure which controls the state of the
                linear regression sub menu state machine
@param - char dataSet[2330][5][20]
                This is the dataset read from Dr. Bhuse's input file
@return - int u->userContinue
                This variable states whether the user would like to
                continue running
**********************************************************************/
int lrSub_stateMachine(lrSC *u, parDTok *dat[2330])
{
    switch(u->state) {

        case LR_PERFORM_REGRESSION  :
            //State Machine for choosing what to regress
            lrSub_performRegression(dat);
            break;

        case LR_ANALYZE_REGRESSION  :
            //State Machine for doing analysis on a member of the linked list
            //FIXME
            break;

        case LR_EXIT       :
            //Function for setting control structure to exit
            lrSub_exit(u);
            break;

        default :
            //ERROR -> Exit state machine
            printf("\nERROR: EXITING LINEAR REGRESSION\n");
            u->state = LR_EXIT;
            break;
    }
    return u->userContinue;
}
/**********************************************************************
Name: lrSub_exit
Description: This is a function which sets parameters to exit the
             linear regression sub menu
@author - Brendan P. Beauchamp
@updated - 7/17/2020
@param - lrSC *u
            This is a structure which controls the state of the
            linear regression sub menu state machine
@return - void
**********************************************************************/
void lrSub_exit(lrSC *u)
{
    u->state = LR_EXIT;
    u->userContinue = 0;
}
/**********************************************************************
Name: lrSub_performRegression
Description: This function asks the user which columns of Dr. Bhuse's
             file they would like to perform a regression on, and then
             performs a linear regression on those two data sets.
             After the regression is complete, its data is printed back
             to the user.
@author - Brendan P. Beauchamp
@updated - 7/17/2020
@param - char dataSet[2330][5][20]
                This is the dataset read from Dr. Bhuse's input file
@return - void
**********************************************************************/
void lrSub_performRegression(parDTok *dat[2330])
{
    lrDP data;
    char xDataType[20], yDataType[20];

    printf("Performing Linear Regression\n");
    printf("Y = aX + b\n");

    //DataSet Options
    printf("Options:\n");
    printf("0:\tDate\n");
    printf("1:\tSPY Put/Call Ratio\n");
    printf("2:\tSPY Put Volume\n");
    printf("3:\tSPY Call Volume\n");
    printf("4:\tTotal SPY Options Volume\n");

    //Select X Data Set
    data.xData = lrSub_selectData('X');
    strcpy(xDataType, lrSub_dataName(data.xData));

    //Select Y Data Set
    data.yData = lrSub_selectData('Y');
    strcpy(yDataType, lrSub_dataName(data.yData));

    //Concatenate Name of Data Structure "xDataType,yDataType"
    strcpy(data.nameXY, xDataType);
    strcat(data.nameXY, " and ");
    strcat(data.nameXY, yDataType);

    //Select Columns to Regress
    selectColumn(dat, data.xData, data.xDatVec);
    selectColumn(dat, data.yData, data.yDatVec);

    //Perform Regression
    data.lrP = castToRegression(data.xData, data.yData, data.xDatVec, data.yDatVec);

    //Print Vars
    lrSub_printRegression(data);

    //Analyze for Outliers
    //FIXME IMPLEMENT LIST
}
/**********************************************************************
Name:lrSub_dataName
Description: This function takes an input of an integer representing
             a column in the input dataset, and returns a string which
             represents that column's title.
@author - Brendan P. Beauchamp
@updated - 7/17/2020
@param - int i
                This is an integer representing which of the columns of
                the data set has been selected
@return - char* ans
                This represents the character format of the input value
**********************************************************************/
char *lrSub_dataName(int i)
{
    char* ans;

    switch(i) {

        case DATE  :
            ans = "Date";
            break;

        case SPY_PUT_CALL_RATIO            :
            ans = "SPY Put Call Ratio";
            break;

        case SPY_PUT_VOLUME                :
            ans = "Spy Put Volume";
            break;

        case SPY_CALL_VOLUME                :
            ans = "SPY Call Volume";
            break;

        case TOTAL_SPY_OPTIONS_VOLUME       :
            ans = "Total SPY Options Volume";
            break;

        default :
            ans = "Error";
            break;
    }
    return ans;
}
/**********************************************************************
Name: lrSub_selectData
Description: This is a helper function for scanning in the datasets for
             X and Y.
@author - Brendan P. Beauchamp
@updated - 7/17/2020
@param - char* var
                This is a character either X or Y depending on which
                variable in the regression is currently being scanned
@return - int ans
                This is the user's choice for the column of the input
                dataset to be selected.
**********************************************************************/
int lrSub_selectData(char* var)
{
    int ans;
    int invalid = 1;

    do {
        printf("Select Data Set for %c\n", var);

        printf("Answer:\t");
        scanf("%d", &ans);
        printf("\n");

        //Answer is incorrect
        if(ans < 0 || ans > 4 )
        {
            printf("\nINVALID INPUT!\n");
        } else{
            invalid = 0;
        }
    }while(invalid);

    return ans;
}

/**********************************************************************
Name:
Description:
@author - Brendan P. Beauchamp
@updated - 7/21/2020
@param -
@return -
**********************************************************************/
lrCo castToRegression(int xTyp, int yTyp, void *xDat[2330], void *yDat[2330])
{
    lrCo ret;
    Type xT, yT;

    xT = ((xTyp == 0)||(xTyp == 2)||(xTyp == 3)) ? tInt : tDouble;
    yT = ((yTyp == 0)||(yTyp == 2)||(yTyp == 3)) ? tInt : tDouble;

    ret = linearRegression(xDat, xT, yDat, yT);

    return ret;
}
#endif //FILESEPERATOR_SUBMENU_LINEARREGRESSION_H
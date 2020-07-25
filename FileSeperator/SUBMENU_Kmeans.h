/************************************************************
Name: SUBMENU_Kmeans.h
Description: This is a library which controls the kmeans Sub Menu.
         It allows the user to perform kmeans clustering based
         on selected input data and then exits.
@author - Green Team SS20 CIS241
@updated - 7/21/2020
*************************************************************/
#ifndef FILESEPARATOR_SUBMENU_KMEANS_H
#define FILESEPARATOR_SUBMENU_KMEANS_H
//Included Libraries
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "kmeans.h"
#include "globalDefinitions.h"
#include "dataHelper.h"

//Function Prototypes
void kmeansSubMenu(parDTok *dat[2330]);
int kmeansSub_receiveInput(kmSC *u);
int kmeansSub_receiveInput(kmSC *u);
int kmeansSub_stateMachine(kmSC *u, parDTok *dat[2330]);
void kmSub_exit(kmSC *u);
void kmeansSub_performKmeans(parDTok *dat[2330]);
int kmSub_selectData(char* var);
int createDim(int dim);
/**********************************************************************
Name: kmeansSubMenu
Description: This function is the main driver for the kmeans
             submenu.
@author - Taylor A. Rieger
@updated - 7/22/2020
@param - char dataSet[2330][5][20]
                This is the dataset read from Dr. Bhuse's input file
@return - void
**********************************************************************/
void kmeansSubMenu(parDTok *dat[2330])
{
    kmSC session;
    session.userContinue = 1;
    while(kmeansSub_receiveInput(&session))
    {
        kmeansSub_stateMachine(&session, dataSet);
    }
}

/**********************************************************************
Name:kmeansSub_receiveInput
Description: This function is utilized to determine what the user will
         pass into the kmeans function.
@author - Taylor A. Rieger
@updated - 7/17/2020
@param - lrSC *u
                This is a structure which contains variables useful to
                maintaining the state of the linear regression sub menu.
@return - int {1,0}
                This is a value which states 1 if the user would like
                to continue running the program or 0 if the would not.
**********************************************************************/
int kmeansSub_receiveInput(kmSC *u)
{
    int ans;
    int invalid = 1;
    do {
        printf("KMEANS: STATE MACHINE\n");
        printf("What would you like to do?\n");
        printf("Options:\n");
        printf("0:\tPerform Kmeans\n");
        printf("1:\tEXIT\n");

        printf("Answer:\t");
        scanf("%d", &ans);
        printf("\n");

        //Answer is incorrect
        if(ans < 0 || ans > 1 )
        {
            printf("\nINVALID INPUT!\n");
        } else{
            invalid = 0;
        }
    }while(invalid);

    //Set State
    u->state = ans;

    return u->state == KMEANS_EXIT ? 0 : 1;
}

int kmeansSub_stateMachine(kmSC *u, parDTok *dat[2330])
{
    switch(u->state) {

        case PERFORM_KMEANS  :
            //State Machine for choosing what to regress
            kmeansSub_performKmeans(dat);
            break;

        case KMEANS_EXIT       :
            //Function for setting control structure to exit
            kmSub_exit(u);
            break;

        default :
            //ERROR -> Exit state machine
            printf("\nERROR: EXITING KMEANS\n");
            u->state = KMEANS_EXIT;
            break;
    }
    return u->userContinue;
}

void kmSub_exit(kmSC *u)
{
    u->state = KMEANS_EXIT;
    u->userContinue = 0;
}

void kmeansSub_performKmeans(parDTok *dat[2330])
{
    kmDP data;
    char xDataType[40], yDataType[40];
    int dim, clusters;

    printf("Performing K Means:\n\n");
    printf("Please choose single or double dimension:\n");
    printf("0:\tSingle\n");
    printf("1:\tDouble\n");
    scanf("%d", &dim);



    //DataSet Options
    if(dim == 1) {
        printf("Options:\n");
        printf("0:\tDate\n");
        printf("1:\tSPY Put/Call Ratio\n");
        printf("2:\tSPY Put Volume\n");
        printf("3:\tSPY Call Volume\n");
        printf("4:\tTotal SPY Options Volume\n");

        //Select X Data Set
        data.xData = kmSub_selectData('X');
        strcpy(xDataType, lrSub_dataName(data.xData));

        //Select Y Data Set
        data.yData = kmSub_selectData('Y');
        strcpy(yDataType, lrSub_dataName(data.yData));

        //Select Columns to Regress
        selectColumn(dat, data.xData, data.xDatVec);
        selectColumn(dat, data.yData, data.yDatVec);

        //Concatenate Name of Data Structure "xDataType,yDataType"
        strcpy(data.nameXY, xDataType);
        strcat(data.nameXY, " and \0");
        strcat(data.nameXY, yDataType);

    }
    else{
        printf("Options:\n");
        printf("1:\tSPY Put/Call Ratio\n");
        printf("2:\tSPY Put Volume\n");
        printf("3:\tSPY Call Volume\n");
        printf("4:\tTotal SPY Options Volume\n");

        //Select X Data Set
        data.xData = kmSub_selectData("Data");
        strcpy(xDataType, lrSub_dataName(data.xData));

        selectColumn(dat, data.xData, data.xDatVec);
        strcpy(data.nameXY, xDataType);

        do {
            printf("How many clusters would you like to perform k means on? (1-10):\n");
            scanf("%d", &clusters);
        }while(clusters < 1 && clusters > 10);
    }

        printf("Clusters of ");
        printf(data.nameXY);
        printf("\n\n");
        int outputCluster[clusters];
        double initialCentroids[] = {100000, 200000, 300000};
        dim = createDim(dim);
        kmeans(dim, (double*) data.xDatVec , 2330, clusters, initialCentroids, outputCluster);
}

int kmSub_selectData(char* var)
{
    int ans;
    int invalid = 1;

    do {
        printf("Select Data Set to Cluster: %c\n", var);

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

double* createInitCluster(parDTok *dat[2330])
{

}

int createDim(int dim){
    int newDim;
    if (dim == 0){
        newDim = 1;
    }
    else if(dim == 1){
        newDim = 2;
    }
    return newDim;
}
#endif //FILESEPERATOR_SUBMENU_KMEANS_H

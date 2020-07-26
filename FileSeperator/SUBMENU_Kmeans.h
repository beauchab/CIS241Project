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
#include "math.h"
#include "kmeans.h"
#include "globalDefinitions.h"
#include "dataHelper.h"

//Function Prototypes
void kmeansSubMenu(parDTok *dat);
int kmeansSub_receiveInput(kmSC *u);
int kmeansSub_stateMachine(kmSC *u, parDTok *dat);
void kmSub_exit(kmSC *u);
void kmeansSub_performKmeans(parDTok *dat);
int kmSub_selectData(parDTok *dat, kmDP *data);
int createDim(int dim);
void createInitCentroid(double* dataVector, int n, int numClusters, double* initialCentroids);
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
void kmeansSubMenu(parDTok *dat)
{
    kmSC session;
    session.userContinue = 1;
    while(kmeansSub_receiveInput(&session))
    {
        kmeansSub_stateMachine(&session, dat);
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

int kmeansSub_stateMachine(kmSC *u, parDTok *dat)
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

void kmeansSub_performKmeans(parDTok *dat)
{
    kmDP data;
    int dim=1, clusters=1, i=0;

    printf("Performing K Means:\n\n");

    //DataSet Options
    do {
        printf("Options:\n");
        printf("1:\tSPY Put/Call Ratio\n");
        printf("2:\tSPY Put Volume\n");
        printf("3:\tSPY Call Volume\n");
        printf("4:\tTotal SPY Options Volume\n");

        //Select X Data Set
        data.Data = kmSub_selectData(dat, &data);

    } while (data.Data < 1 || data.Data > 4);

    //seeing if data is correct
//    for (i=0; i < 2330; i++){
//        printf("%lf\n",  data.input[i]);
//    }

    do {
        printf("How many clusters would you like to perform k means on? (1-4):\n");
        scanf("%d", &clusters);
    }while(clusters < 1 || clusters > 4;


    int outputCluster[clusters];
    double initialCentroids[clusters];

    createInitCentroid(data.input, DATA_SIZE, clusters, initialCentroids);

    kmeans(dim, (double*)&data.input, DATA_SIZE, clusters, initialCentroids, outputCluster);
}

int kmSub_selectData(parDTok *dat, kmDP *data)
{
    int ans, i;
    int invalid = 1;

    do {
        printf("Select Data Set to Cluster: \n");

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

    switch(ans) {
        case SPY_PUT_CALL_RATIO:
            for (i = 0; i < DATA_SIZE; i++) {
                data->input[i] = (double) dat[i].spyPutCallRatio;
            } break;
        case SPY_PUT_VOLUME:
            for (i = 0; i < DATA_SIZE; i++) {
                data->input[i] = (double) dat[i].spyPutVolume;
            } break;
        case SPY_CALL_VOLUME:
            for (i = 0; i < DATA_SIZE; i++) {
                data->input[i] = (double) dat[i].spyCallVolume;
            } break;
        case TOTAL_SPY_OPTIONS_VOLUME:
            for (i = 0; i < DATA_SIZE; i++) {
                data->input[i] = (double) dat[i].spyTotalOptionsVolume;
            } break;
    }

    return ans;
}

void createInitCentroid(double* dataVector, int n, int numClusters, double* initialCentroids)
{
    double min,max, range=0, gap;
    int i;
    min=max=dataVector[0];

    for(i=1; i<n; i++)
    {
        if(min>dataVector[i])
            min=dataVector[i];
        if(max<dataVector[i])
            max=dataVector[i];
    }

    range = max - min;
    initialCentroids[0] = min;
    initialCentroids[numClusters-1] = max;
    gap = range/numClusters;
    for(i=1; i<numClusters-1; i++){
        initialCentroids[i] += (min + gap*i);
    }
}

int createDim(int dim){
    int newDim=1;
    if (dim == 0){
        newDim = 1;
    }
    else if(dim == 1){
        newDim = 2;
    }
    return newDim;
}

#endif //FILESEPERATOR_SUBMENU_KMEANS_H
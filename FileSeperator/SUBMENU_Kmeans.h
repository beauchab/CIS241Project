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
int kmSub_selectData1D(parDTok *dat, kmDP *data);
int kmSub_selectData2D(parDTok *dat, kmDP *data);
void createInitCentroid1D(double* dataVector, int n, int numClusters, double* initialCentroids);
void createInitCentroid2D(double dataVector[][DATA_SIZE], int n, int numClusters, double initialCentroids[0][MAX_CLUSTERS]);
/**********************************************************************
Name: kmeansSubMenu
Description: This function is the main driver for the kmeans
             submenu.
@author - Taylor A. Rieger, Brendan P. Beauchamp
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
@author - Taylor A. Rieger, Brendan P. Beauchamp
@updated - 7/17/2020
@param - kmSC *u
                This is a structure which contains variables useful to
                maintaining the state of the kmeans sub menu.
@return - int {1,0}
                This is a value which states 1 if the user would like
                to continue running the program or 0 if the would not.
**********************************************************************/
int kmeansSub_receiveInput(kmSC *u)
{
    int ans;
    int invalid = 1;
    do {
        printf("-_-_-_-_-_/ K MEANS MENU /-_-_-_-_-_\n");
        printf("Options:\n");
        printf("0 -\tPerform Kmeans\n");
        printf("1 -\tEXIT\n");
        printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");
        printf("What would you like to do?\n\n\t-> ");

        scanf("%d", &ans);
        printf("\n");

        //Answer is incorrect
        if(ans < 0 || ans > 1 )
        {
            printf("\t*INVALID INPUT!*\n\n");
        } else{
            invalid = 0;
        }
    }while(invalid);

    //Set State
    u->state = ans;

    return u->state == KMEANS_EXIT ? 0 : 1;
}
/************************************************************
Name: kmeansSub_stateMachine
Description: This is a function that controls the flow of the
             kmeans submenu state machine.
@author - Taylor A. Rieger, Brendan P. Beauchamp
@updated - 7/21/2020
@param - kmSC *u
                This is a structure which contains variables
                useful to maintaining the state of the kmeans
                sub menu.
@param - char dataSet[2330][5][20]
                This is the dataset read from Dr. Bhuse's input
                file.
@return - int u->userContinue
                This variable states whether the user would like
                to continue running.
*************************************************************/
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
            printf("\n\t*ERROR: EXITING KMEANS*\n\n");
            u->state = KMEANS_EXIT;
            break;
    }
    return u->userContinue;
}
/**********************************************************************
Name: kmSub_exit
Description: This is a function which sets parameters to exit the
             linear regression sub menu.
@author - Taylor A. Rieger, Brendan P. Beauchamp
@updated - 7/17/2020
@param - kmSC *u
            This is a structure which controls the state of the
            kmeans sub menu state machine
@return - void
**********************************************************************/
void kmSub_exit(kmSC *u)
{
    u->state = KMEANS_EXIT;
    u->userContinue = 0;
}
/**********************************************************************
Name: kmeansSub_performKmeans
Description: This function asks the user which column of Dr. Bhuse's
             file they would like to perform kmeans on, and then
             performs kmeans on that single column with the inputted
             number of centroids and clusters.
             After kmeans is complete, its data is printed back
             to the user.
@author - Taylor A. Rieger, Kendra Haan
@updated - 7/26/2020
@param - char dataSet[2330][5][20]
                This is the dataset read from Dr. Bhuse's input file
@return - void
**********************************************************************/
void kmeansSub_performKmeans(parDTok *dat)
{
    kmDP data;
    int dim=0, clusters=1, i=0;

    printf("-_-_-_/ Performing K Means: /-_-_-_\n");

    //DataSet Options
    do {
        printf("Please indicate dimension: \n");
        printf("1 -\t1-D Analysis\n");
        printf("2 -\t2-D Analysis\n");
        printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");
        printf("What would you like to do?\n\n\t-> ");

        scanf("%d", &dim);
        printf("\n");

        //Select X Data Set
        printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");
        printf("%d-D Analysis Chosen\n", dim);
        printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n\n");

    } while (dim < 1 || dim > 2);

    //DataSet Options
    do {
        printf("-_-_-_/ Dataset Options: /-_-_-_\n");
        printf("1 -\tSPY Put/Call Ratio\n");
        printf("2 -\tSPY Put Volume\n");
        printf("3 -\tSPY Call Volume\n");
        printf("4 -\tTotal SPY Options Volume\n");
        printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n");
        if(dim == 1)
        {
            //Select X Data Set
            data.Data = kmSub_selectData1D(dat, &data);
        }
        else if(dim == 2)
        {
            //Select XY Data Set
            data.Data = kmSub_selectData2D(dat, &data);
        }
    } while (data.Data < 1 || data.Data > 4);


    do {
        printf("How many clusters would you like to perform k means on? (1-4):\n\n\t->");

        scanf("%d", &clusters);
    }while(clusters < 1 || clusters > 4);


    int outputCluster[clusters];


    if(dim == 1)
    {
        double initialCentroids[clusters];
        createInitCentroid1D(data.input1D, DATA_SIZE, clusters, initialCentroids);
        kmeans(dim, (double *)&data.input1D, DATA_SIZE, clusters, initialCentroids, outputCluster);
    }
    else if(dim == 2)
    {
        double initialCentroids[2][MAX_CLUSTERS];
        createInitCentroid2D(data.input2D, DATA_SIZE, clusters, initialCentroids);
        kmeans(dim, (double *)&data.input2D, DATA_SIZE, clusters, (double *)initialCentroids, outputCluster);
    }

}
/**********************************************************************
Name: kmSub_selectData1D
Description: This is a helper function for scanning in the datasets for
             K means in 1 Dimensional analysis.
@author - Taylor A. Rieger, Kendra Haan
@updated - 7/26/2020
@param - char dataSet[2330][5][20]
                This is the dataset read from Dr. Bhuse's input file
@param - kmDP *data
                This is a structure containing the kmeans data and
                data points.
@return - int ans
                This is the user's choice for the column of the input
                dataset to be selected.
**********************************************************************/
int kmSub_selectData1D(parDTok *dat, kmDP *data)
{
    int ans, i;
    int invalid = 1;

    do {
        printf("What data set would you like to cluster?\n\n\t->");
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
                data->input1D[i] = (double) dat[i].spyPutCallRatio;
            } break;
        case SPY_PUT_VOLUME:
            for (i = 0; i < DATA_SIZE; i++) {
                data->input1D[i] = (double) dat[i].spyPutVolume;
            } break;
        case SPY_CALL_VOLUME:
            for (i = 0; i < DATA_SIZE; i++) {
                data->input1D[i] = (double) dat[i].spyCallVolume;
            } break;
        case TOTAL_SPY_OPTIONS_VOLUME:
            for (i = 0; i < DATA_SIZE; i++) {
                data->input1D[i] = (double) dat[i].spyTotalOptionsVolume;
            } break;
    }

    return ans;
}
/**********************************************************************
Name: kmSub_selectData2D
Description: This is a helper function for scanning in the datasets for
             K means in 2 Dimensional analysis.
@author - Kendra Haan
@updated - 7/26/2020
@param - char dataSet[2330][5][20]
                This is the dataset read from Dr. Bhuse's input file
@param - kmDP *data
                This is a structure containing the kmeans data and
                data points.
@return - int ans
                This is the user's choice for the column of the input
                dataset to be selected.
**********************************************************************/
int kmSub_selectData2D(parDTok *dat, kmDP *data)
{
    int ans, i;
    int invalid = 1;

    do {
        printf("What data set would you like to cluster first?\n\n\t->");

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
                data->input2D[0][i] = (double) dat[i].spyPutCallRatio;
            } break;
        case SPY_PUT_VOLUME:
            for (i = 0; i < DATA_SIZE; i++) {
                data->input2D[0][i] = (double) dat[i].spyPutVolume;
            } break;
        case SPY_CALL_VOLUME:
            for (i = 0; i < DATA_SIZE; i++) {
                data->input2D[0][i] = (double) dat[i].spyCallVolume;
            } break;
        case TOTAL_SPY_OPTIONS_VOLUME:
            for (i = 0; i < DATA_SIZE; i++) {
                data->input2D[0][i] = (double) dat[i].spyTotalOptionsVolume;
            } break;
    }

    invalid = 1;

    do {
        printf("What data set would you like to cluster second?\n\n\t->");

        scanf("%d", &ans);
        printf("\n");

        //Answer is incorrect
        if(ans < 0 || ans > 4 )
        {
            printf("\n\t*INVALID INPUT!*\n\n");
        } else{
            invalid = 0;
        }
    }while(invalid);

    switch(ans) {
        case SPY_PUT_CALL_RATIO:
            for (i = 0; i < DATA_SIZE; i++) {
                data->input2D[1][i] = (double) dat[i].spyPutCallRatio;
            } break;
        case SPY_PUT_VOLUME:
            for (i = 0; i < DATA_SIZE; i++) {
                data->input2D[1][i] = (double) dat[i].spyPutVolume;
            } break;
        case SPY_CALL_VOLUME:
            for (i = 0; i < DATA_SIZE; i++) {
                data->input2D[1][i] = (double) dat[i].spyCallVolume;
            } break;
        case TOTAL_SPY_OPTIONS_VOLUME:
            for (i = 0; i < DATA_SIZE; i++) {
                data->input2D[1][i] = (double) dat[i].spyTotalOptionsVolume;
            } break;
    }

    return ans;
}
/**********************************************************************
Name: createInitCentroid1D
Description: This is a helper function that creates initial centroids
             to be passed into the kmeans function.
@author - Taylor A. Rieger, Kendra Haan
@updated - 7/26/2020
@param - double* dataVector
                This is a the data in the column selected by the user
                in order to determine initial centroids.
@param - int n
                This is the number of rows/datapoints in the column.
@param - int numClusters
                This is the number of clusters the user wants to
                create from the data.
@return - double* initialCentroids
                This is the initial array of centroids that are
                doubles and to be passed to kmeans.
**********************************************************************/
void createInitCentroid1D(double* dataVector, int n, int numClusters, double* initialCentroids)
{
    double min,max, range=0, gap;
    int i;
    min= max = dataVector[0];

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
/**********************************************************************
Name: createInitCentroid2D
Description: This is a helper function that creates initial centroids to
             be passed into the kmeans function.
@author - Kendra Haan
@updated - 7/25/2020
@param - double* dataVector[][DATA_SIZE]
                This is the data in the column selected by the user
                in order to determine initial centroids.
@param - int n
                This is the number of rows/datapoints in the column.
@param - int numClusters
                This is the number of clusters the user wants to
                create from the data.
@return - double* initialCentroids[0][MAX_CLUSTERS]
                This is the initial array of centroids that are
                doubles and to be passed to kmeans. It is a 2-D
                array.
**********************************************************************/
void createInitCentroid2D(double dataVector[][DATA_SIZE], int n, int numClusters, double initialCentroids[0][MAX_CLUSTERS])
{
    double min,max, range=0, gap;
    int i;
    min = max = dataVector[0][0];

    for(i=1; i<n; i++)
    {
        if(min>dataVector[0][i])
            min=dataVector[0][i];
        if(max<dataVector[0][i])
            max=dataVector[0][i];
    }

    range = max - min;
    initialCentroids[0][0] = min;
    initialCentroids[0][numClusters-1] = max;
    gap = range/numClusters;
    for(i=1; i<numClusters-1; i++){
        initialCentroids[0][i] += (min + gap*i);
    }

    min = max = dataVector[1][0];

    for(i=1; i<n; i++)
    {
        if(min>dataVector[1][i])
            min=dataVector[1][i];
        if(max<dataVector[1][i])
            max=dataVector[1][i];
    }

    range = max - min;
    initialCentroids[1][0] = min;
    initialCentroids[1][numClusters-1] = max;
    gap = range/numClusters;
    for(i=1; i<numClusters-1; i++){
        initialCentroids[1][i] += (min + gap*i);
    }
}
#endif //FILESEPERATOR_SUBMENU_KMEANS_H

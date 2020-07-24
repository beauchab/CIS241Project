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

//State Definitions
#define

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
void kmeansSubMenu(char dataSet[2330][5][20])
{
    kmeans session;
    session.userContinue = 1;
    while(lrSub_receiveInput(&session))
    {
        lrSub_stateMachine(&session, dataSet);
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
int kmeansSub_receiveInput(kmeansSC *u)
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




#endif //FILESEPERATOR_SUBMENU_KMEANS_H

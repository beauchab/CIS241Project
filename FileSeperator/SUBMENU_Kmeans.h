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
#define KM_

/**********************************************************************
Name: kmeansSubMenu
Description: This function is the main driver for the kmeans
             submenu
@author - Taylor A. Rieger
@updated - 7/22/2020
@param - char dataSet[2330][5][20]
                This is the dataset read from Dr. Bhuse's input file
@return - void
**********************************************************************/
void linearRegressionSubMenu(char dataSet[2330][5][20])
{
    lrSC session;
    session.userContinue = 1;
    while(lrSub_receiveInput(&session))
    {
        lrSub_stateMachine(&session, dataSet);
    }
}





#endif //FILESEPERATOR_SUBMENU_KMEANS_H

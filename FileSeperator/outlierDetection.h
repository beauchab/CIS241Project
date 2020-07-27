/**********************************************************************
Name: outlierDetection.h
Description: This program integrates logic for outlier detection
@author - Green Team SS20 CIS241
@updated - 7/16/2020
**********************************************************************/
#ifndef FILESEPERATOR_OUTLIERDETECTION_H
#define FILESEPERATOR_OUTLIERDETECTION_H

#include "pythagoreanMeans.h"
#include "usefulStats.h"
#include "globalDefinitions.h"

void castVector(void *x[2330], double yHat[2330]);

/*
     * Outlier Detection Submenu
     * 1. Perform outlier detection
     *  -> choose number of std dev
     *      -> perform logic
     *          -> count number of outliers
     *          -> print lin regression eq
     *          -> print upper bound
     *          -> print lower bound
     *          -> divide count by 2330 for percentage of outliers
     * 2. EXIT
     */
void outlierDetection(lrDP data)
{
    int stdDev, i;
    double yUpper[2330];
    double yBottom[2330];
    void *outliers[2330];
    int outlierIndex = 0;
    double outlierPercent = 0.0;
    int invalid = 1;

    do{
        printf("Enter a Standard Deviation to calculate outliers with\n");
        printf("Number of standard deviations must be between 1 and 10: ");
        scanf("%d", &stdDev);

        if(stdDev < 1 || stdDev > 10 )
            printf("\n\t*ERROR*\n\nChoose number between 1 and 10.\n\n");
        else
            invalid = 0;

    }while(invalid);

    printf("\nPerforming Outlier Detection based on Standard Deviation of %d:\n", stdDev);


    Type xT = ((data.xData != 1)) ? tInt : tDouble;
    Type yT = ((data.yData != 1)) ? tInt : tDouble;

    calcYHat(data.xDatVec, xT, yUpper, data.lrP.alpha, (data.lrP.beta + (stdDev * data.lrP.stdDevY)));
    calcYHat(data.xDatVec, xT, yBottom, data.lrP.alpha, (data.lrP.beta - (stdDev * data.lrP.stdDevY)));

    switch(yT) {

        case tInt:
            for (i = 0; i < 2330; i++)
            {
                if ((*(int*)data.yDatVec[i] > yUpper[i] || *(int*)data.yDatVec[i] < yBottom[i]))
                {
                    outliers[outlierIndex] = (int*)data.yDatVec[i];
                    outlierIndex++;
                }
            }
            break;

        case tDouble:
            for (i = 0; i < 2330; i++)
            {
                if ((*(double*)data.yDatVec[i] > yUpper[i] || *(double*)data.yDatVec[i] < yBottom[i]))
                {
                    outliers[outlierIndex] = (double*)data.yDatVec[i];
                    outlierIndex++;
                }
            }
            break;
    }
    outlierPercent = outlierIndex / 2330.0;
    printf(" Upper Bound Equation:");
    printf("\ty = %.02lfx + %.02lf\n",data.lrP.alpha,data.lrP.beta + (stdDev * data.lrP.stdDevY));
    printf(" Regression Equation:");
    printf("\ty = %.02lfx + %.02lf\n",data.lrP.alpha,data.lrP.beta);
    printf(" Lower Bound Equation:");
    printf("\ty = %.02lfx + %.02lf\n",data.lrP.alpha,data.lrP.beta - (stdDev * data.lrP.stdDevY));
    printf("\n\t> Number of Outliers -  \t%d\n", outlierIndex);
    printf("\t> Percentage of Outliers -\t%2.2g %%\n\n", outlierPercent * 100);
}

/**********************************************************************
Name: castVector
Description: This function takes an input of array x, its type,
             and an array of doubles to write the void vector casted as
             a double vector to.

@author - Nicholas Bernhardt, Brendan Beauchamp
@updated - 7/24/2020
@param - double x[]
                    This is an array which contains all of the x values
                    for the linear regression.
@param - double yHat[]
                    This is an array of predicted values for y using
                    the linear regression coefficients.
@return - void
**********************************************************************/
void castVector(void *x[2330], double yHat[2330])
{
    int i;
    for( i = 0; i < 2330; i++)
    {
        yHat[i] = (*(double*)x[i]); //Yhat = aX +b
    }
//    switch(xT) {
//
//        case tInt:
//            for( i = 0; i < 2330; i++)
//            {
//                yHat[i] = (double)(*(int*)x[i]); //Yhat = aX +b
//            }
//            break;

//        case tDouble:

//            break;
//    }
}

#endif //FILESEPERATOR_OUTLIERDETECTION_H

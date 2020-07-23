//FIXME THESE FUNTIONS SHOULD BE IMPLEMENTED FOR BOTH MULTIPLE DATA TYPES
//FIXME THE FUNCTIONS DO NOT NEED TO PASS SIZE, CAN USE SIZEOF OPERATOR
/**********************************************************************
Name: means.h
Description: This library implements the three means functions
@author - Green Team SS20 CIS241
@updated - 7/4/2020
@param -
@return -
**********************************************************************/
#ifndef FILESEPERATOR_PYTHAGOREANMEANS_H
#define FILESEPERATOR_PYTHAGOREANMEANS_H
//Included Libraries
#include <math.h>
#include "dataHelper.h"
//Structs
typedef struct pythagoreanMeans
{
    double arithmeticM;
    double geometricM;
    double harmonicM;
}means;
//Function Prototypes
double arithmeticMean(void *array[2330], Type arT);
double geometricMean(void *array[2330], Type arT);
double harmonicMean(void *array[2330], Type arT);
means calcMeans(void *array[2330], Type arT);
/**********************************************************************
Name: arithmeticMean
Description: This function calculates the arithmetic mean of a
             data set. A = additiveSum(array)/size
@author - Brendan P. Beauchamp
@updated - 7/4/2020
@param -
@return -
**********************************************************************/
double arithmeticMean(void *array[], Type arT)
{
    int i;
    double arithSum = 0;
    switch(arT)
    {
        case tInt:
            for(i = 0; i < 2330; i++)
            {
                arithSum = arithSum + *(int*)array[i];
            }
            break;

        case tDouble:
            for(i = 0; i < 2330; i++)
            {
                arithSum = arithSum + *(double*)array[i];
            }
            break;
    }

    return arithSum/2330;
}
/**********************************************************************
Name: geometricMean
Description: This function calculates the geometric mean of a
             data set. G= (multiplicitiveSum(array))^(1/size)
@author - Brendan P. Beauchamp
@updated - 7/4/2020
@param -
@return -
**********************************************************************/
double geometricMean(void *array[], Type arT)
{
    int i;
    double geoSum = 1;
    switch(arT) {

        case tInt:
            for(i = 0; i < 2330; i++)
            {
                geoSum = geoSum * *(int*)array[i];
            }
            break;

        case tDouble:
            for(i = 0; i < 2330; i++)
            {
                geoSum = geoSum * *(double*)array[i];
            }
            break;

    }
    return pow(geoSum, 1.0/2330.0);
}
/**********************************************************************
Name: geometricMean
Description: This function calculates the harmonic mean of a
             data set. H= size/inverseSum(array)
@author - Brendan P. Beauchamp
@updated - 7/4/2020
@param -
@return -
**********************************************************************/
double harmonicMean(void *array[], Type arT)
{
    int i;
    double arithSumInv = 0;
    double invX = 0.0;
    switch(arT) {

        case tInt:
            for (i = 0; i < 2330; i++) {
                invX = 1 / (*(int*) array[i]);
                arithSumInv = arithSumInv + invX;
            }
            break;

        case tDouble:
            for (i = 0; i < 2330; i++) {
                invX = 1 / (*(double*) array[i]);
                arithSumInv = arithSumInv + invX;
            }
            break;

    }
    return (2330.0 / arithSumInv);
}
/**********************************************************************
Name: calcMeans
Description: This function calculates all of the means. It returns
             these means in a structure.
@author - Brendan P. Beauchamp
@updated - 7/4/2020
@param -
@return -
**********************************************************************/
means calcMeans(void *array[], Type arT)
{
    means mS;

    mS.arithmeticM =  arithmeticMean(array, arT);
    mS.geometricM = geometricMean(array, arT);
    mS.harmonicM = harmonicMean(array, arT);

    return mS;
}
#endif //FILESEPERATOR_PYTHAGOREANMEANS_H
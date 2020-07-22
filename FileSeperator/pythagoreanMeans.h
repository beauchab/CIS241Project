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
//Structs
typedef struct pythagoreanMeans
{
    double arithmeticM;
    double geometricM;
    double harmonicM;
}means;
//Function Prototypes
double arithmeticMean(void *array[], int size);
double geometricMean(void *array[], int size);
double harmonicMean(void *array[], int size);
means calcMeans(void *array[], int size);
/**********************************************************************
Name: arithmeticMean
Description: This function calculates the arithmetic mean of a
             data set. A = additiveSum(array)/size
@author - Brendan P. Beauchamp
@updated - 7/4/2020
@param -
@return -
**********************************************************************/
double arithmeticMean(void *array[], int size)
{
    int i;
    double arithSum = 0;
    for(i = 0; i < size; i++)
    {
        arithSum = arithSum + *(int*)array[i];
    }
    return arithSum/size;
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
double geometricMean(void *array[], int size)
{
    int i;
    double geoSum = 1;

    for(i = 0; i < size; i++)
    {
        geoSum = geoSum * *(int*)array[i];
    }
    return pow(geoSum, 1.0/(double)size);
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
double harmonicMean(void *array[], int size)
{
    int i;
    double arithSumInv = 0;
    double invX = 0.0;

    for (i = 0; i < size; i++) {
        invX = 1 / (*(double*) array[i]);
        arithSumInv = arithSumInv + invX;
    }
    return ((double) size / arithSumInv);
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
means calcMeans(void *array[], int size)
{
    means mS;

    mS.arithmeticM =  arithmeticMean(array,size);
    mS.geometricM = geometricMean(array,size);
    mS.harmonicM = harmonicMean(array,size);

    return mS;
}
#endif //FILESEPERATOR_PYTHAGOREANMEANS_H
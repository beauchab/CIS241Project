/**********************************************************************
Name: linearRegression.h
Description: This is a library of functions which implement linear
             regression. Linear regression extrapolates a function of
             the form y = ax + b, this library's main function call
             will return the coefficients a & b in a structure to the
             caller.
@author - Green Team SS20 CIS241
@updated - 7/8/2020
**********************************************************************/
#ifndef FILESEPERATOR_USEFULSTATS_H
#define FILESEPERATOR_USEFULSTATS_H
//Included Libraries
#include "pythagoreanMeans.h"
//Function Prototypes
double calcVar(double x[], double xBar, int n);
double calcStdDev(double Var);
double calcCovXY(double x[], double xBar, double y[], double yBar, int n);
double calcCorXY(double covXY, double varX, double varY);
/**********************************************************************
Name: calcVar
Description: This function calculates the variance of a dataset that
             is input to the function. The formula for variance is:

                    var = sum((x-xBar)^2)/(n-1)

@author - Brendan P. Beauchamp
@updated - 7/8/2020
@param - double x[]
                    This is an array which contains the dataset to
                    calculate the variance of
@param - double xBar
                    This is the mean of the dataset to calculate the
                    variance of
@param -  int n
                    This is the size of the dataset
@return - double var
                    This is the variance of the dataset
**********************************************************************/
double calcVar(double x[], double xBar, int n)
{
    double var,num;
    int i;

    //sum the numerator
    for( i = 0; i < n; i++)
    {
        num += pow((x[i] - xBar),2);
    }

    var = num/(n-1);
    return var;
}
/**********************************************************************
Name: calcStdDev
Description: This function calculates the standard deviation of a
             dataset given its variance
@author - Brendan P. Beauchamp
@updated - 7/8/2020
@param - double var
                    This is the variance of the dataset
@return - double stdDev
                    This is the standard deviation of the dataset
**********************************************************************/
double calcStdDev(double var)
{
    double stdDev;
    stdDev = sqrt(var);
    return stdDev;
}
/**********************************************************************
Name: calcCovXY
Description: This function calculates the covariance between two
             data sets.
@author - Brendan P. Beauchamp
@updated - 7/8/2020
@param - double x[]
                    This is an array which contains all of the x values
                    for the linear regression
@param - double xBar
                    This is a double value which represents the
                    arithmetic mean of the data set x
@param - double y[]
                    This is an array which contains all of the y values
                    for the linear regression
@param - double yBar
                    This is a double value which represents the
                    arithmetic mean of the data set y
@param - double n
                    This is an integer which represents the size of the
                    data sets x and y
@return - double cov
                    This is the covariance of the two datasets
**********************************************************************/
double calcCovXY(double x[], double xBar, double y[], double yBar, int n)
{
    double cov, num;
    int i;

    for( i = 0; i < n; i++)
    {
        num += ((x[i] - xBar)*(y[i] - yBar));
    }

    cov = num/(n-1);
    return cov;
}
/**********************************************************************
Name: calcCorXY
Description: This function calculates the Correlation coefficient
             between two data sets.
@author - Brendan P. Beauchamp
@updated - 7/8/2020
@param - double covXY
                        This is the covariance between the datasets
                        X and Y
@param - double varX
                        This is the variance of the dataset X
@param - double varY
                        This is the variance of the dataset Y
@return - double cor
                        This is the correlation coefficient between
                        the datasets X and Y
**********************************************************************/
double calcCorXY(double covXY, double varX, double varY)
{
    double cor;
    cor = covXY/(sqrt(varX*varY));
    return cor;
}
#endif //FILESEPERATOR_USEFULSTATS_H

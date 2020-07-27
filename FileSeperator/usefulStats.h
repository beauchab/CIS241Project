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
#include "globalDefinitions.h"
//Function Prototypes
double calcVar(void *x[], Type xT, double xBar);
double calcStdDev(double Var);
double calcCovXY(void *x[2330], Type xT, void *y[2330], Type yT, double xBar, double yBar);
double calcCorXY(double covXY, double varX, double varY);
void analyzeRSquared(double r);
void analyzeCovXY(double c);
void analyzeCorXY(double c);
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
double calcVar(void *x[], Type xT, double xBar)
{
    double var=0,num=0;
    int i;

    //sum the numerator
    switch(xT) {

        case tInt:
            for( i = 0; i < 2330; i++)
            {
                num += pow((*(int*)x[i] - xBar),2);
            }
            break;

        case tDouble:
            for( i = 0; i < 2330; i++)
            {
                num += pow((*(double*)x[i] - xBar),2);
            }
            break;
    }

    var = num/2329;
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
double calcCovXY(void *x[2330], Type xT, void *y[2330], Type yT, double xBar, double yBar)
{
    double cov=0, num=0;
    int i, cTp = 0;

    cTp = (xT<<1) + yT;

    switch(cTp) {
        //x -> int, y -> int
        case 0:
            for( i = 0; i < 2330; i++)
            {
                num += ((*(int*)x[i] - xBar)*(*(int*)y[i] - yBar));
            }
        break;

        //x -> int, y -> double
        case 1:
            for( i = 0; i < 2330; i++)
            {
                num += ((double)(*(int*)x[i] - xBar)*(*(double*)y[i] - yBar));
            }
        break;

        //x -> double, y -> int
        case 2:
            for( i = 0; i < 2330; i++)
            {
                num += ((*(double*)x[i] - xBar)*((double)*(int*)y[i] - yBar));
            }
        break;

        //x -> double, y -> double
        case 3:
            for( i = 0; i < 2330; i++)
            {
                num += ((*(double*)x[i] - xBar)*(*(double*)y[i] - yBar));
            }
        break;
    }

    cov = num/2329;
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
    double cor=0;
    cor = covXY/(sqrt(varX*varY));
    return cor;
}
/**********************************************************************
Name: analyzeRSquared
Description: This function takes an input of the r squared value of
             the linear regression and prints a statement describing
             the accuracy of the regression.
@author - Brendan P. Beauchamp
@updated - 7/17/2020
@param - double r
            This is a double which represents the value of r squared.
@return - void
**********************************************************************/
void analyzeRSquared(double r)
{
    if      (r>0.999)
    {
        printf("\t Regression is exact");
    }
    else if (r>0.85)
    {
        printf("\t Regression is a very precise");
    }
    else if (r>0.50)
    {
        printf("\t Regression is a loose");
    }
    else
    {
        printf("\t Regression is not an accurate");
    }
    printf(" representation of data.\n\n");
}
/**********************************************************************
Name: analyzeCovXY
Description: This function takes an input of the covariance value of
             the linear regression and prints a statement describing
             the relationship exhibited within the two data sets.
@author - Brendan P. Beauchamp
@updated - 7/17/2020
@param - double c
            This value represents the covariance between the two data
            sets in the linear regression.
@return - void
**********************************************************************/
void analyzeCovXY(double c)
{
    if      (c>0.0)
    {
        printf("\t Data sets exhibit positive relationship.\n\n");
    }
    else if (c<0.0)
    {
        printf("\t Data sets exhibit negative relationship.\n\n");
    }
    else
    {
        printf("\t Data sets exhibit no relationship.\n\n");
    }
}
/**********************************************************************
Name: analyzeCorXY
Description: This function takes an input of a double representing the
             correlation coefficient, and prints a statement which
             describes the correlation between the two data sets in the
             regression.
@author - Brendan P. Beauchamp
@updated - 7/17/2020
@param - double c
        This is a double representing the correlation coefficient
        between the two data sets in the linear regression.
@return - void
**********************************************************************/
void analyzeCorXY(double c)
{
    if      (c>0.80)
    {
        printf("\t Significant positive");
    }
    else if (c>0.0)
    {
        printf("\t Insignificant positive");
    }
    else if (c<-0.80)
    {
        printf("\t Significant negative");
    }
    else
    {
        printf("\t Insignificant negative");
    }
    printf(" relationship between data sets.\n\n");
}
#endif //FILESEPERATOR_USEFULSTATS_H

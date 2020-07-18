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
        printf("Regression is exact");
    }
    else if (r>0.85)
    {
        printf("Regression is a very precise");
    }
    else if (r>0.50)
    {
        printf("Regression is a loose");
    }
    else
    {
        printf("Regression is not an accurate");
    }
    printf(" representation of data\n\n");
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
        printf("Data sets exhibit positive relationship\n\n");
    }
    else if (c<0.0)
    {
        printf("Data sets exhibit negative relationship\n\n");
    }
    else
    {
        printf("Data sets exhibit no relationship\n\n");
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
        printf("Significant positive");
    }
    else if (c>0.0)
    {
        printf("Insignificant positive");
    }
    else if (c<-0.80)
    {
        printf("Significant negative");
    }
    else
    {
        printf("Insignificant negative");
    }
    printf(" relationship between data sets\n\n");
}
#endif //FILESEPERATOR_USEFULSTATS_H

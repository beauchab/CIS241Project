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
#ifndef FILESEPERATOR_LINEARREGRESSION_H
#define FILESEPERATOR_LINEARREGRESSION_H
//Included Libraries
#include "pythagoreanMeans.h"
#include "usefulStats.h"
//Structs
typedef struct linearRegressionCoefficients
{
    double alpha;
    double beta;
    double R_2;
    double stdDevX;
    double stdDevY;
    double covXY;
    double corXY;
}lrCo;
//Function Prototypes
lrCo linearRegression(double x[], double y[], int size);
double calcAlpha(double x[], double xBar, double y[], double yBar, int n);
double calcBeta(double yBar, double xBar, double alpha);
void calcYHat(double x[], double yHat[], double alpha, double beta, int n);
double calcR_2(double y[], double yHat[], double yBar, int n);
/**********************************************************************
Name:linearRegression
Description: This function maps the data of arrays x and y to a function
             of the form y = ax + b. It then uses this mapping to
             determine the coefficients a and b. It returns these in a
             structure.
@author - Brendan P. Beauchamp
@updated - 7/8/2020
@param - double x[]
                    This is an array which contains all of the x values
                    for the linear regression
@param - double y[]
                    This is an array which contains all of the y values
                    for the linear regression
@param - int size
                    This is the size of arrays x and y
@return - struct linearRegressionCoefficients (lrco) lRegC
                This is a structure which contains the coefficients
                of the linear regression of x and y. These coefficients
                are labeled alpha for a and beta for b.
**********************************************************************/
lrCo linearRegression(double x[], double y[], int size)
{
    lrCo lRegC;
    double yBar,xBar,varX,varY;

    //FIXME yHAT MUST BE CONVERTED INTO A POINTER pYHAT TO DYNAMICALLY ALLOCATE SPACE
    double *yHat =(double*) malloc(size * sizeof(double));  //memory allocated

    //xBar and yBar using arithmetic mean
    xBar = arithmeticMean(x, size);
    yBar = arithmeticMean(y, size);

    //calculates coefficients {a,b} for y= ax + b
    lRegC.alpha = calcAlpha(x, xBar, y, yBar, size);
    lRegC.beta = calcBeta( yBar, xBar, lRegC.alpha);

    //determines Rsquared value
    calcYHat(x, yHat, lRegC.alpha, lRegC.beta, size);
    lRegC.R_2 = calcR_2(y, yHat, yBar, size);

    //calculate variances and standard deviations
    varX = calcVar(x, xBar, size);
    varY = calcVar(y, yBar, size);
    lRegC.stdDevX = calcStdDev(varX);
    lRegC.stdDevY = calcStdDev(varY);

    //calculate covariance and correlation coefficient of X and Y
    lRegC.covXY = calcCovXY(x, xBar, y, yBar, size);
    lRegC.corXY = calcCorXY(lRegC.covXY, varX, varY);

    return lRegC;
}
/**********************************************************************
Name: calcAlpha
Description: This program calculates the linear regression coefficient
             a (alpha) in the equation y = ax + b. This coefficient is
             found using the equation below

                 a = sum((x_i - xbar)(y_i - ybar))/sum((x_i - xbar)^2)

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
@return - double alpha
                    This is the linear regression coefficient which
                    represents the slope of the linear regression.
**********************************************************************/
double calcAlpha(double x[], double xBar, double y[], double yBar, int n)
{
    double den = 0;//bottom of alpha formula
    double num = 0;//top of alpha formula
    double alpha;
    int i;//iterator

    for(i = 0; i < n; ++i){
        num += ((x[i] - xBar)*(y[i] - yBar));//calculates the top of the alpha formula and sums values
    }
    for(i = 0; i < n; ++i){
        den += pow((x[i] - xBar),2);//calculates the bottom of the alpha formula
    }
    alpha = (num/den);//divides top by bottom to get alpha

    return alpha;
}
/**********************************************************************
Name: calcBeta
Description: This program calculates the linear regression coefficient
             b (beta) in the equation y = ax + b. This coefficient is
             found using the equation below

                b = ybar - (a * xbar)

@author - Brendan P. Beauchamp
@updated - 7/8/2020
@param - double yBar
                    This is a double value which represents the
                    arithmetic mean of the data set y
@param - double xBar
                    This is a double value which represents the
                    arithmetic mean of the data set x
@param - double alpha
                    This is the linear regression coefficient which
                    represents the slope of the linear regression.
@return - double beta
                    This is the linear regression coefficient which
                    represents the y intercept of the linear
                    regression.
**********************************************************************/
double calcBeta(double yBar, double xBar, double alpha)
{
    double beta;
    beta = yBar - (alpha * xBar);//calculates value for Beta
    return beta;
}
/**********************************************************************
Name: calcYHat
Description: This function takes an input of array x, its size, and the
             coefficients of linear regression to calculate a predicted
             value for y at that measurement (i.e. yHat). This is done
             using the equation:

                yHat[i] = a*x[i] + b

@author - Brendan P. Beauchamp
@updated - 7/8/2020
@param - double x[]
                    This is an array which contains all of the x values
                    for the linear regression
@param - double yHat[]
                    This is an array of predicted values for y using
                    the linear regression coefficients
@param - double alpha
                    This is the linear regression coefficient which
                    represents the slope of the linear regression.
@param - double beta
                    This is the linear regression coefficient which
                    represents the y intercept of the linear
                    regression.
@param - int n
                    This is an integer which represents the size of the
                    data sets
@return - void
**********************************************************************/
void calcYHat(double x[], double yHat[], double alpha, double beta, int n)
{
    int i;

    for( i = 0; i < n; i++)
    {
        yHat[i] = (alpha * x[i]) + beta;
    }
}
/**********************************************************************
Name: calcR_2
Description: This function calculates the R squared value of the linear
             regression. This scalar is a measure of how closely the
             data points in y fit to the regression y = ax + b.
@author - Brendan P. Beauchamp
@updated - 7/8/2020
@param - double y[]
                    This is an array which contains all of the y values
                    for the linear regression
@param - double yHat[]
                    This is an array of predicted values for y using
                    the linear regression coefficients
@param - double yBar
                    This is a double value which represents the
                    arithmetic mean of the data set y
@param - int n
                    This is an integer which represents the size of the
                    data sets
@return - double R_2
                    This scalar is a measure of how closely the
                    data points in y fit to the regression y = ax + b.
**********************************************************************/
double calcR_2(double y[], double yHat[], double yBar, int n)
{
    double R_2 = 0.0, num = 0.0, den = 0.0;
    int i;

    for( i = 0; i < n; i++)
    {
        num += pow((y[i] - yHat[i]),2);
         den += pow((y[i] - yBar),2);
    }

    R_2 = 1 - (num/den);
    return R_2;
}
#endif //FILESEPERATOR_LINEARREGRESSION_H

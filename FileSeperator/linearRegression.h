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
#include "globalDefinitions.h"

//Function Prototypes
lrCo linearRegression(void *x[2330], Type xT, void *y[2330], Type yT);
double calcAlpha(void *x[2330], Type xT, void *y[2330], Type yT, double xBar, double yBar);
double calcBeta(double yBar, double xBar, double alpha);
void calcYHat(void *x[2330], Type xT, double yHat[2330], double alpha, double beta);
double calcR_2(void *y[2330], Type yT, double yHat[2330], double yBar);
void lrSub_printRegression(lrDP d);
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
@param - double y[]
                    This is an array which contains all of the y values
                    for the linear regression.
@param - int size
                    This is the size of arrays x and y
@return - struct linearRegressionCoefficients (lrco) lRegC
                This is a structure which contains the coefficients
                of the linear regression of x and y. These coefficients
                are labeled alpha for a and beta for b.
**********************************************************************/
lrCo linearRegression(void *x[2330], Type xT, void *y[2330], Type yT)
{
    lrCo lRegC;
    double yBar,xBar,varX,varY;
    double yHat[2330];

    //xBar and yBar using arithmetic mean
    xBar = arithmeticMean(x,xT);
    yBar = arithmeticMean(y,yT);

    //calculates coefficients {a,b} for y= ax + b
    lRegC.alpha = calcAlpha(x, xT, y, yT, xBar, yBar);
    lRegC.beta = calcBeta( yBar, xBar, lRegC.alpha);

    //determines Rsquared value
    calcYHat(x, xT, &yHat, lRegC.alpha, lRegC.beta);
    lRegC.R_2 = calcR_2(y, yT, yHat, yBar);

    //calculate variances and standard deviations
    varX = calcVar(x, xT, xBar);
    varY = calcVar(y, yT, yBar);
    lRegC.stdDevX = calcStdDev(varX);
    lRegC.stdDevY = calcStdDev(varY);

    //calculate covariance and correlation coefficient of X and Y
    lRegC.covXY = calcCovXY(x, xT, y, yT, xBar, yBar);
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
                    for the linear regression.
@param - double xBar
                    This is a double value which represents the
                    arithmetic mean of the data set x.
@param - double y[]
                    This is an array which contains all of the y values
                    for the linear regression.
@param - double yBar
                    This is a double value which represents the
                    arithmetic mean of the data set y.
@param - double n
                    This is an integer which represents the size of the
                    data sets x and y.
@return - double alpha
                    This is the linear regression coefficient which
                    represents the slope of the linear regression.
**********************************************************************/
double calcAlpha(void *x[2330], Type xT, void *y[2330], Type yT, double xBar, double yBar)
{
    double den = 0;//bottom of alpha formula
    double num = 0;//top of alpha formula
    double alpha;
    int i, cTp = 0;

    cTp = (xT<<1) + yT;

    switch(cTp) {

        //x -> int, y -> int
        case 0:
            //calculates the top of the alpha formula and sums values
            for(i = 0; i < 2330; ++i){
                num += ((*(int*)x[i] - xBar)*(*(int*)y[i] - yBar));
            }
            //calculates the bottom of the alpha formula
            for(i = 0; i < 2330; ++i){
                den += pow((*(int*)x[i] - xBar),2);
            }
            break;

        //x -> int, y -> double
        case 1:
            //calculates the top of the alpha formula and sums values
            for(i = 0; i < 2330; ++i){
                num += ((*(int*)x[i] - xBar)*(*(double*)y[i] - yBar));
            }
            //calculates the bottom of the alpha formula
            for(i = 0; i < 2330; ++i){
                den += pow((*(int*)x[i] - xBar),2);
            }
            break;

        //x -> double, y -> int
        case 2:
            //calculates the top of the alpha formula and sums values
            for(i = 0; i < 2330; ++i){
                num += ((*(double*)x[i] - xBar)*(*(int*)y[i] - yBar));
            }
            //calculates the bottom of the alpha formula
            for(i = 0; i < 2330; ++i){
                den += pow((*(double*)x[i] - xBar),2);
            }
            break;

        //x -> double, y -> double
        case 3:
            //calculates the top of the alpha formula and sums values
            for(i = 0; i < 2330; ++i){
                num += ((*(double*)x[i] - xBar)*(*(double*)y[i] - yBar));
            }
            //calculates the bottom of the alpha formula
            for(i = 0; i < 2330; ++i){
                den += pow((*(double*)x[i] - xBar),2);
            }
            break;
    }

    alpha = (num/den);//divides top by bottom to get alpha

    return alpha;
}
/**********************************************************************
Name: calcBeta
Description: This program calculates the linear regression coefficient
             b (beta) in the equation y = ax + b. This coefficient is
             found using the equation below.

                b = ybar - (a * xbar)

@author - Brendan P. Beauchamp
@updated - 7/8/2020
@param - double yBar
                    This is a double value which represents the
                    arithmetic mean of the data set y.
@param - double xBar
                    This is a double value which represents the
                    arithmetic mean of the data set x.
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
                    for the linear regression.
@param - double yHat[]
                    This is an array of predicted values for y using
                    the linear regression coefficients.
@param - double alpha
                    This is the linear regression coefficient which
                    represents the slope of the linear regression.
@param - double beta
                    This is the linear regression coefficient which
                    represents the y intercept of the linear
                    regression.
@param - int n
                    This is an integer which represents the size of the
                    data sets.
@return - void
**********************************************************************/
void calcYHat(void *x[2330], Type xT, double yHat[2330], double alpha, double beta)
{
    int i;
    switch(xT) {
        case tInt:
            for( i = 0; i < 2330; i++)
            {
                yHat[i] = (double)(alpha * *(int*)x[i]) + beta; //Yhat = aX +b
            }
            break;

        case tDouble:
            for( i = 0; i < 2330; i++)
            {
                yHat[i] = (alpha * *(double*)x[i]) + beta; //Yhat = aX +b
            }
            break;
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
                    for the linear regression.
@param - double yHat[]
                    This is an array of predicted values for y using
                    the linear regression coefficients.
@param - double yBar
                    This is a double value which represents the
                    arithmetic mean of the data set y.
@param - int n
                    This is an integer which represents the size of the
                    data sets.
@return - double R_2
                    This scalar is a measure of how closely the
                    data points in y fit to the regression y = ax + b.
**********************************************************************/
double calcR_2(void *y[2330], Type yT, double yHat[2330], double yBar)
{
    double R_2, num=0, den=0;
    int i;
    switch(yT) {

        case tInt:
            for( i = 0; i < 2330; i++)
            {
                num += pow((double)(*(int*)y[i] - yHat[i]),2);
                den += pow((*(int*)y[i] - yBar),2);
            }
            break;

        case tDouble:
            for( i = 0; i < 2330; i++)
            {
                num += pow((*(double*)y[i] - yHat[i]),2);
                den += pow((*(double*)y[i] - yBar),2);
            }
            break;
    }

    R_2 = 1 - (num/den);
    return R_2;
}
/**********************************************************************
Name: lrSub_printRegression
Description: This is a function which prints the linear regression
             coefficients for a computed linear regression.
@author - Brendan P. Beauchamp
@updated - 7/17/2020
@param - lrCo c
            This is a structure containing the linear regression
            coefficients to be printed to the user.
@return - void
**********************************************************************/
void lrSub_printRegression(lrDP d)
{
    printf("Regression of %s:\n", d.nameXY);

    //Equation Y = ax + b
    printf(" - Equation:");
    printf("\ty = %.02lfx + %.02lf\n\n",d.lrP.alpha,d.lrP.beta);
    printf("\t> Alpha -\t\t\t%lf\n",d.lrP.alpha);
    printf("\t> Beta  -\t\t\t%lf\n",d.lrP.beta);

    //Standard Deviations
    printf("\t> Standard Deviation (x) -\t%lf\n",d.lrP.stdDevX);
    printf("\t> Standard Deviation (y) -\t%lf\n",d.lrP.stdDevY);

    //Regressional Analysis Correlation
    //R Squared
    printf("\n\t> R Squared -\t\t\t%lf\n",d.lrP.R_2);
    analyzeRSquared(d.lrP.R_2);

    //Covariance
    printf("\t> Covariance XY -\t\t%lf\n",d.lrP.covXY);
    analyzeCovXY(d.lrP.covXY);

    //Correlation Coefficient
    printf("\t> Correlation Coefficent XY -\t%lf\n",d.lrP.corXY);
    analyzeCorXY(d.lrP.corXY);
}
#endif //FILESEPERATOR_LINEARREGRESSION_H

//FIXME CLEANUP ON AISLE 4!!!
//FIXME https://warwick.ac.uk/fac/soc/economics/staff/vetroeger/teaching/po906_week567.pdf
/**********************************************************************
Name: fileHelper.h
Description: This is a library of functions which implement linear
             regression. Linear regression extrapolates a function of
             the form y = ax+b, this library's main function call
             will return the coefficients a & b in a structure to the
             caller.
@author - Green Team SS20 CIS241
@updated - 6/25/2020
**********************************************************************/
#ifndef FILESEPERATOR_LINEARREGRESSION_H
#define FILESEPERATOR_LINEARREGRESSION_H
//Included Libraries
#include "pythagoreanMeans.h"
//Structs
typedef struct linearRegressionCoefficients
{
    double alpha;
    double beta;
}coeffs;
//Function Prototypes
coeffs linearRegression(double x[], double y[], int size);
double calcAlpha(double x[], double xBar, double y[], double yBar, double n);
double calcBeta(double yBar, double xBar, double alpha);
/**********************************************************************
Name:
Description:
@author - Brendan P. Beauchamp
@updated - 7/4/2020
@param -
@return -
**********************************************************************/
coeffs linearRegression(double x[], double y[], int size)
{
    coeffs lRegC;
    double yBar,xBar;

    //xBar and yBar using arithmetic mean
    xBar = arithmeticMean(x, size);
    yBar = arithmeticMean(y, size);

    //calculates coefficients {a,b} for y= ax + b
    lRegC.alpha = calcAlpha(x, xBar, y, yBar, size);
    lRegC.beta = calcBeta( yBar, xBar, lRegC.alpha);

    return lRegC;
}
/**********************************************************************
Name:
Description:
@author - Brendan P. Beauchamp
@updated - 7/4/2020
@param -
@return -
**********************************************************************/
double calcAlpha(double x[], double xBar, double y[], double yBar, double n)
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
Name:
Description:
@author - Brendan P. Beauchamp
@updated - 7/4/2020
@param -
@return -
**********************************************************************/
double calcBeta(double yBar, double xBar, double alpha)
{
    double beta;
    beta = yBar - (alpha * xBar);//calculates value for Beta
    return beta;
}
#endif //FILESEPERATOR_LINEARREGRESSION_H

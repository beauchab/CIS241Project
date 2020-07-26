/**********************************************************************
Name:globalDefinitions
Description: This is a file which contains useful definitions for the
             whole file seperator program
@author - Brendan P. Beauchamp
@updated - 7/17/2020
**********************************************************************/
#ifndef FILESEPERATOR_GLOBALDEFINITIONS_H
#define FILESEPERATOR_GLOBALDEFINITIONS_H
//Data Field Definitions
#define DATE                     0
#define SPY_PUT_CALL_RATIO       1
#define SPY_PUT_VOLUME           2
#define SPY_CALL_VOLUME          3
#define TOTAL_SPY_OPTIONS_VOLUME 4

//State Machine Definitions
//MAIN
#define READ_INPUT        0
//FIXME THIS SHOULD LAUNCH A SECONDARY STATE MACHINE (i.e. What data you want to print?)
#define PRINT_DATA        1
#define LINEAR_REGRESSION 2
#define KMEANS            3
#define EXIT              4
//Linear Regression
#define LR_PERFORM_REGRESSION       0
#define LR_EXIT                     1
//K Means
#define PERFORM_KMEANS              0
#define KMEANS_EXIT                 1


//Enums
typedef enum Type{tInt, tDouble}Type;

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
typedef struct LR_StateControl {
    int state;
    int userContinue;
}lrSC;
typedef struct LR_DataPoints {
    char nameXY[100];
    lrCo lrP;
    int xData;
    void *xDatVec[2330];
    int yData;
    void *yDatVec[2330];
}lrDP;

//Structs
struct stateControl {
    int state;
    int flags[5];
    int userContinue;
};
struct files{
    FILE *inFileP;
    FILE *outFileP;
};
//Structures
typedef struct numericDate{
    int day;
    int month;
    int year;
}nDate;
typedef struct parsedDataToken{
    nDate date;
    int linDate;
    double spyPutCallRatio;
    int spyPutVolume;
    int spyCallVolume;
    int spyTotalOptionsVolume;
}parDTok;
typedef struct theData {
    char arIn[2330][5][20];
    parDTok parsedData[2330];
}dat;
typedef struct Kmeans_StateControl {
    int state;
    int userContinue;
}kmSC;
typedef struct KM_DataPoints {
    char nameXY[100];
    int Data;
    void *DatVec[2330];
}kmDP;
#endif //FILESEPERATOR_GLOBALDEFINITIONS_H
/**********************************************************************
Name:dataHelper.h
Description: This is a collection of functions which aids in the
             parsing of data.
@author - Brendan P. Beauchamp
@updated - 7/21/2020
**********************************************************************/
#ifndef FILESEPERATOR_DATAHELPER_H
#define FILESEPERATOR_DATAHELPER_H
//Included Libraries
#include "globalDefinitions.h"
#include <stdlib.h>

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

//Function Prototypes
void selectColumn(parDTok pDat[2330], int colChoice, void *cDat[2330]);
void parseData(int dTyp, char *tok, parDTok *pDat);
nDate parseDate(char *tok);
double parseDub(char tok[20]);
int parseInt(char tok[20]);
void selectColumn(parDTok pDat[2330], int colChoice, void *cDat[2330]);

/**********************************************************************
Name: selectColumn
Description: This is a function which allows the user to select a column
             of the input data set.
@author - Brendan P. Beauchamp
@updated - 7/21/2020
@param - parDTok pDat[2330]
                This is an array of parDTok structures which represents
                the parsedData member of the dat structure. This is
                passed to select a column (i.e. member) of the structure.
@param - int colChoice
                This is an integer value which represents the member
                or column of the parDTok structure which is to be
                returned to the caller.
@param - void *cDat[2330]
                This is a column of data type void pointer which
                represents the column (i.e. member) of pDat that has
                been selected.
@return - void
**********************************************************************/
void selectColumn(parDTok pDat[2330], int colChoice, void *cDat[2330])
{
    int i;

    for(i = 0; i < 2330; i++)
    {
        switch (colChoice)
        {
            //FIXME DO WE NEED A CASE FOR THE DATE STRUCTURE???
            //FIXME I DO NOT SEE A CASE WHERE THE USER WOULD LIKE TO REGRESS
            //FIXME THE DATE STRUCTURE
            //FIXME THE MALLOC MAY NEED TO BE INSTANTIATED EARLIER THAN THIS DEPENDING ON HOW C REALLOCATES MEMORY

            //Selected linear date {int}
            case DATE  :
                //Allocate Space for Type
                cDat[i] = malloc(sizeof(int));
                //Cast Member to Array Location
                *((int*)cDat[i]) = pDat->linDate;
                break;

                //Selected SPY Put Call Ratio {double}
            case SPY_PUT_CALL_RATIO  :
                //Allocate Space for Type
                cDat[i] = malloc(sizeof(double));
                //Cast Member to Array Location
                *((double*)cDat[i]) = pDat->spyPutCallRatio;
                break;

                //Selected SPY Put Volume {int}
            case SPY_PUT_VOLUME   :
                //Allocate Space for Type
                cDat[i] = malloc(sizeof(int));
                //Cast Member to Array Location
                *((int*)cDat[i]) = pDat->spyPutVolume;
                break;

                //Selected SPY Call Volume {int}
            case SPY_CALL_VOLUME  :
                //Allocate Space for Type
                cDat[i] = malloc(sizeof(int));
                //Cast Member to Array Location
                *((int*)cDat[i]) = pDat->spyCallVolume;
                break;

                //Parsing SPY Total Options Volume {int}
            case TOTAL_SPY_OPTIONS_VOLUME  :
                //Allocate Space for Type
                cDat[i] = malloc(sizeof(int));
                //Cast Member to Array Location
                *((int*)cDat[i]) = pDat->spyTotalOptionsVolume;
                break;

            default :
                //ERROR
                cDat[i] = NULL;
                break;
        }
    }
}

/**********************************************************************
Name:parseData
Description: This function is a state machine which controls the
             parsing of data read in by the readFileData function in
             the fileHelper.h file. The function uses the dTyp int as
             a switch, because readFileData naturally increments an int
             in order to tokenize the input file.
@author - Brendan P. Beauchamp
@updated - 7/21/2020
@param - int dTyp
                This is an integer value which represents the column
                names of the input csv file. These names are defined
                in the globalDefinitions.h file.
@param - char tok[20]
                This is a single parsed member of a row in the arIn
                member of the dat structure. This single member value
                along with dTyp are used to determine the type (4cols)
                and value of a member of the parDTok structure.
@param - parDTok *pDat
                This is a parameterized data token which contains
                parsed members of the .csv input file. The structure
                contains these values in their numeric, manipulable
                data types.
@return - void
**********************************************************************/
//FIXME FUNCTION DOES NOT PROPERLY TRANSFER D.ARIN CHAR ARRAY
void parseData(int dTyp, char *tok, parDTok *pDat)
{
    switch(dTyp) {

        case DATE  :
            //Parsing date structure {int,int,int}
            pDat->date = parseDate(tok);
            break;

        case SPY_PUT_CALL_RATIO  :
            //Parsing SPY Put Call Ratio {double}
            pDat->spyPutCallRatio = parseDub(tok);
            break;

        case SPY_PUT_VOLUME   :
            //Parsing SPY Put Volume {int}
            pDat->spyPutVolume = parseInt(tok);
            break;

        case SPY_CALL_VOLUME  :
            //Parsing SPY Call Volume {int}
            pDat->spyCallVolume = parseInt(tok);
            break;

        case TOTAL_SPY_OPTIONS_VOLUME  :
            //Parsing SPY Total Options Volume {int}
            pDat->spyTotalOptionsVolume = parseInt(tok);
            break;

        default :
            //FIXME
            //Function for stating improper input

            break;
    }
}

/**********************************************************************
Name: parseDate
Description: This function takes an input of a string which is a member
             of the arIn character array into a dat stucture. It knows
             that this string is a date as delegated by the parseData
             function, and converts it into a nDate structure.
@author - Brendan P. Beauchamp
@updated - 7/21/2020
@param - char tok[20]
                This is a single parsed member of a row in the arIn
                member of the dat structure. This single member value
                along with dTyp are used to determine the type (4cols)
                and value of a member of the parDTok structure. This
                determination is done in the parseData state machine,
                and then delegated to a helper parse function.
@return - nDate
                This is a member type of the structure parDTok which
                represents a date.
**********************************************************************/
nDate parseDate(char *tok)
{
    nDate ret;
    char day[5], month[5], year[5];
    char delim[2] = "/";

    //Tokenize input
    strcpy(day, strtok(tok, delim));
    strcpy(month, strtok(NULL, delim));
    strcpy(year, strtok(NULL, delim));

    //Convert input to date structure
    ret.day = parseInt(day);
    ret.month = parseInt(month);
    ret.year = parseInt(year);

    return ret;
}

/**********************************************************************
Name: parseDub
Description: This function takes an input of a string which is a member
             of the arIn character array into a double. It knows that
             this string is a double as delegated by the parseData
             function.
@author - Brendan P. Beauchamp
@updated - 7/21/2020
@param - char tok[20]
                This is a single parsed member of a row in the arIn
                member of the dat structure. This single member value
                along with dTyp are used to determine the type (4cols)
                and value of a member of the parDTok structure. This
                determination is done in the parseData state machine,
                and then delegated to a helper parse function.
@return - double
                This is a double value which represents the SPY put
                call ratio.
**********************************************************************/
double parseDub(char tok[20])
{
    char *ptr;
    double ret;
    ret = strtod(tok,&ptr);
    return ret;
}

/**********************************************************************
Name: parseInt
Description: This function takes an input of a string which is a member
             of the arIn character array into a integer. It knows that
             this string is a integer as delegated by the parseData
             function.
@author - Brendan P. Beauchamp
@updated - 7/21/2020
@param - char tok[20]
                This is a single parsed member of a row in the arIn
                member of the dat structure. This single member value
                along with dTyp are used to determine the type (4cols)
                and value of a member of the parDTok structure. This
                determination is done in the parseData state machine,
                and then delegated to a helper parse function.
@return - int
                This is an integer which can represent either a
                SPY Put volume, SPY Call Volume, or Total SPY Options
                Volume.
**********************************************************************/
int parseInt(char tok[20])
{
    return atoi(tok);
}

#endif //FILESEPERATOR_DATAHELPER_H
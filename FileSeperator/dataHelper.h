/**********************************************************************
Name:
Description:
@author -
@updated -
**********************************************************************/
#ifndef FILESEPERATOR_DATAHELPER_H
#define FILESEPERATOR_DATAHELPER_H
//Included Libraries

//Structures
typedef struct numericDate{
    int day;
    int month;
    int year;
}date;
typedef struct parsedDataToken{
    date d;
    int linDate;
    double spyPutCallRatio;
    int spyPutVolume;
    int spyCallVolume;
    int spyTotalOptionsVolume;
}parDTok;
struct theData {
    char arIn[2330][5][20];
    parDTok parsedData[2330];
};

//Function Prototypes


#endif //FILESEPERATOR_DATAHELPER_H

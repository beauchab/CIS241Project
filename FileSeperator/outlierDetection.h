/**********************************************************************
Name: outlierDetection.h
Description:
@author - Green Team SS20 CIS241
@updated - 7/16/2020
**********************************************************************/
#ifndef FILESEPERATOR_OUTLIERDETECTION_H
#define FILESEPERATOR_OUTLIERDETECTION_H

void outlierDetection() {
    int standDev, menuOption;
    int a = 0;
    int b = 0;

    printf("\nOUTLIER DETECTION\n\n");

    while(a == 0) {
        printf("How many standard deviations will be used to detect outliers?\n\t");
        scanf("%d", &standDev);

        if(standDev > 1 && standDev < 10) a++;
        else printf("\n*ERROR*\nPlease enter a valid number.\n\n");
    }
    while(b == 0) {
        printf("\n\nWhat would you like to do?\nOptions:\n");
        printf("0\tPrint the outliers of %d standard deviations.\n", standDev);
        printf("1\tRemove the outliers from the current set of data.\n");
        printf("2\tEXIT\n\n");
        scanf("%d", &menuOption);

        if (menuOption == 0){
            printOutliers(standDev);
        }
        else if (menuOption == 1){
            removeOutliers(standDev);
        }
        else b++;
    }

}

void printOutliers(int StandardDeviations){

    printf("This will print the outliers of %d standard deviations\n\n", StandardDeviations);

    //LOOP through all the data ...
    //IF an outlier, print

    //ELSE nothing

}

void removeOutliers(int StandardDeviations){

    printf("This will remove the outliers from the data of %d standard deviations\n\n", StandardDeviations);

    //LOOP through all the data ...
    //IF an outlier, nothing

    //ELSE add to new array

    //then add this new array everywhere else in the code...yikes
}

#endif //FILESEPERATOR_OUTLIERDETECTION_H
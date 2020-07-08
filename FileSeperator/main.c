#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Function Prototypes
int printTab(void);
int printNewLine(void);
void readFileData(FILE *fp, char arP[2330][5][20]);
void printData(char arP[2330][5][20]);

//choose the two element rows as args
int main()
{
    char* arIn[2330][5];
    FILE *fp;

    //char* arOut[2330][]


    // CLion is giving me a hard time with printing this fixed it for me, you may comment it out.
    setbuf(stdout, NULL);

    fp = fopen("classData.csv", "r");

    readFileData(fp, arIn);
    printData(arIn);

    printf("Hello, World!\n");
    return 0;
}



void readFileData(FILE *fp, char arP[2330][5][20])
{
    char buff[200] = "";
    char *delim = ",";
    int n = 0, m = 0;

    //Read Header
    fgets(buff, sizeof(buff), fp);

    //read in a line
    while (fgets(buff, sizeof(buff), fp) != NULL)
    {
        //Tokenize line into array elements
        //Tokenize user input as stated in midterm file
        strcpy(arP[m][n++], strtok(buff, delim));
        while (n < 5)
        {
            strcpy(arP[m][n], strtok(NULL, delim));
            n++;
        }
        n = 0;
        m++;
    }
}

void printData(char arP[2330][5][20])
{
    int i,j;
    int (*pT)(void) = &printTab;
    int (*pN)(void) = &printNewLine;

    for(i=0; i<2330; i++)
    {
        for(j=0; j<5; j++)
        {
            printf("%s", arP[j][i]);
            (i==5) ? (*pN) : (*pT);

        }
    }
}

int printTab(void)
{
    printf("\t");
    return 0;
}

int printNewLine(void)
{
    printf("\n");
    return 0;
}


int* dataLinerization(struct Data data[]) 
{
	int i = 0, j=0, date[foo(data)], month[foo(data)];
	static int newArray[][];

	while( i < foo(data))
	{
		month = strtok(data.date[i], "/");
		date[i] = strtok(NULL, "/");
		i++;
	}
	i=0;
	
	while(j < date[i])
	{
		newArray[j] = j + 1;
		j++;
		
	}
	return newArray;
}
	

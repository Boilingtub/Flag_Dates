#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define YEAR 2024

typedef enum bool{false, true} bool;
int count_lines(char* filepath); 


int days_in_month[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
char *months[]=
{
	" ",
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December"
};

char *months_short[]=
{
	" ",
	"Jan",
	"Feb",
	"Mar",
	"Apr",
	"May",
	"Jun",
	"Jul",
	"Aug",
	"Sep",
	"Oct",
	"Nov",
	"Dec"
};

char** textfile_To_Arr(char* filepath)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    int linecount = count_lines(filepath);
    char** arr = malloc(sizeof(char*)*linecount); 

    fp = fopen(filepath, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    int i = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        arr[i] = malloc(len*sizeof(char)+1);
        strcpy(arr[i],line);
        //printf("%s", value);
        i++;
    }

    fclose(fp);
    if (line)
        free(line);

    return arr;

}

int determinedaycode(int year)
{
	int daycode;
	int d1, d2, d3;
	
	d1 = (year - 1.)/ 4.0;
	d2 = (year - 1.)/ 100.;
	d3 = (year - 1.)/ 400.;
	daycode = (year + d1 - d2 + d3) %7;
	return daycode;
}


bool determineleapyear(int year)
{
	if(year% 4 == false && year%100 != false || year%400 == false)
	{
		days_in_month[2] = 29;
		return true;
	}
	else
	{
		days_in_month[2] = 28;
		return false;
	}
}

int count_lines(char* filepath); 

int count_lines(char* filepath) {
    FILE* fp;
    int lines = 0;
    char ch;
    fp = fopen(filepath, "r");

    while(!feof(fp)) {
        ch = fgetc(fp);
        if(ch == '\n'){
            lines++;
        }
    }
    return lines;
}

void write_text_file(char* file_path, char* buffer) {
    FILE *file_pointer = fopen(file_path,"w");
    fprintf(file_pointer,"%s\n",buffer);
    fclose(file_pointer);
}
    
void append_text_file(char* file_path, char* buffer) {
    /* File pointer to hold reference of input file */
    FILE *fPtr = fopen(file_path,"a");
    fputs(buffer, fPtr);
    fclose(fPtr);

}

int main() {
    #define InFilePath "volunteers.txt"
    #define OutFilePath "flag_dates.txt"
    //printf("FLAG TIMES:\n");
    int year = YEAR;
    int daycode = determinedaycode(year);
    bool leapyear = determineleapyear(year);
    int month , day;

    char** volunteers = textfile_To_Arr(InFilePath);
    int arr_len = count_lines(InFilePath);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
   
    write_text_file(OutFilePath,"FLAG DATES:\n");
	for ( month = 1; month <= 12; month++ )
	{		
		// Print all the dates for one month 
        append_text_file(OutFilePath,"\n----------\n");
        append_text_file(OutFilePath,months[month]);
        append_text_file(OutFilePath,"\n----------\n");

        int i = 0;
		for ( day = 1; day <= days_in_month[month]; day++ )
		{
            char mon_name[5];
            sprintf(mon_name,"%s,",months_short[month]);
            char day_num[6];
			sprintf(day_num, "%2d - ",day);
           
            char fin_date[strlen(mon_name)+strlen(day_num)+strlen(volunteers[i])+2];
            strcpy(fin_date,mon_name);
            strcat(fin_date,day_num);
            strcat(fin_date,volunteers[i]);
            
            //printf("%s",fin_date);
            append_text_file(OutFilePath,fin_date);
            i++;
            if(i >= arr_len)
                i = 0;
		}
    
	}
}

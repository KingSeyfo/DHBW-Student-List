#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct datum Datum;
typedef struct student Student;



void readFile(FILE* file);
void addStudent(Student* stud, FILE* file);
void combine(char* fname, char* lname, int* id, Datum* geb, Datum* start, Datum* end, Student* final);
void inputStudent(char* fname, char* lname, int* id, Datum* geb, Datum* start, Datum* end);
void inputData(char msg[30], char* ptr);
void inputMatrikel(char msg[30], int* ptr);
void inputDatum(char msg[50], Datum* var);
bool checkDatumisValid(int tag, int monat, int jahr);

struct datum{
	int day;
	int month;
	int year;
};


struct student{
	char firstName[20];
	char lastName[20];
	int matrikelNr;
	struct datum geb;
	struct datum start;
	struct datum ende;
};


int main(){
	Student* result = malloc(sizeof(Student));

	char (*firstname)[20] = malloc(sizeof(char[20]));
	char (*lastname)[20] = malloc(sizeof(char[20]));
	int* matrikel = malloc(sizeof(int));
	Datum* birth = malloc(sizeof(Datum));
	Datum* startdate = malloc(sizeof(Datum));
	Datum* enddate = malloc(sizeof(Datum));


	FILE* file = fopen("C:\\Users\\Seyfu\\Desktop\\students.txt", "w");

	inputStudent(firstname, lastname, matrikel, birth, startdate, enddate);
	combine(firstname, lastname, matrikel, birth, startdate, enddate, result);


	addStudent(result, file);
	printf("Nun lesen\n");
	readFile(file);

	printf("Normaler Print\n");

	printf("%s\n",result->firstName);
	printf("%s\n",result->lastName);
	printf("%d\n",result->matrikelNr);
	printf("%d/%d/%d\n",result->geb.day, result->geb.month, result->geb.year);
	printf("%d/%d/%d\n",result->start.day, result->start.month, result->start.year);
	printf("%d/%d/%d\n",result->ende.day, result->ende.month, result->ende.year);


	free(result);
	free(firstname);
	free(matrikel);
	free(birth);
	free(startdate);
	free(enddate);
    return 0;
}


void readFile(FILE* file){
	Student* a = malloc(sizeof(Student));
	fread(a,sizeof(Student),1,file);


	printf("%s\n",a->firstName);
	printf("%s\n",a->lastName);
	printf("%d\n",a->matrikelNr);
	printf("%d/%d/%d\n",a->geb.day, a->geb.month, a->geb.year);
	printf("%d/%d/%d\n",a->start.day, a->start.month, a->start.year);
	printf("%d/%d/%d\n",a->ende.day, a->ende.month, a->ende.year);


	fclose(file);
}


void addStudent(Student* stud, FILE* file){
		if(file == NULL){
			printf("Error beim erstellen der Datei");
			return;
		}
		fwrite(stud, sizeof(Student),1,file);
		fclose(file);
}


void combine(char* fname, char* lname, int* id, Datum* geb, Datum* start, Datum* end, Student* final){
	strcpy(final->firstName, fname);
	strcpy(final->lastName, lname);
	final->matrikelNr = *id;
	final->geb = *geb;
	final->start = *start;
	final->ende = *end;
}


void inputStudent(char* fname, char* lname, int* id, Datum* geb, Datum* start, Datum* end){
	inputData("Bitte Vornamen angeben: \n",fname);
	fflush(stdin);
	inputData("Bitte Nachnamen angeben: \n",lname);
	fflush(stdin);
	inputMatrikel("Bitte Matrikelnummer angeben: \n",id);
	fflush(stdin);
	inputDatum("Bitte Geburtsdatum(tt/mm/jjjj) angeben: \n",geb);
	fflush(stdin);
	inputDatum("Bitte Startdatum(tt/mm/jjjj) angeben: \n",start);
	fflush(stdin);
	inputDatum("Bitte Enddatum(tt/mm/jjjj) angeben: \n",end);
}


void inputData(char msg[30], char* ptr){
	printf(msg);
	scanf("%s",ptr);
}


void inputMatrikel(char msg[30], int* ptr){
	printf(msg);
	scanf("%d",ptr);
}


void inputDatum(char msg[50], Datum* var){
	int tag,monat,jahr;
	printf(msg);
	scanf("%d/%d/%d",&tag,&monat,&jahr);
	if(!checkDatumisValid(tag, monat, jahr)){
		inputDatum(msg,var);
	}else{
		Datum a;
		a.day = tag;
		a.month = monat;
		a.year = jahr;
		*var = a;
	}
}


bool checkDatumisValid(int tag, int monat, int jahr){
	if(jahr>=1900 && jahr<=9999){
		if(monat>=1 && monat<=12){
			if((tag>=1 && tag<=31) && (monat==1 || monat==3 || monat==5 || monat==7 || monat==8 || monat==10 || monat==12)){
				return true;
			}else if((tag>=1 && tag<=30) && (monat==4 || monat==6 || monat==9 || monat==11)){
				return true;
			}else if((tag>=1 && tag<=28) && (monat==2)){
				return true;
			}else if(tag==29 && monat==2 && (jahr%400==0 ||(jahr%4==0 && jahr%100!=0))){
				return true;
			}else{
				printf("Ungültiger Tag.\n");
				return false;
			}
		}else{
			printf("Ungültiger Monat.\n");
			return false;
		}
	}else{
		printf("Ungültiges Jahr.\n");
		return false;
	}
}

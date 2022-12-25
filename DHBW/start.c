#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct datum Datum;
typedef struct student Student;

void inputDatum(char msg[50],Datum* var);
bool checkDatumisValid();
void inputStudent(char* fname, char* lname, int* id, Datum* geb, Datum* start, Datum* end);
void combine(char* fname, char* lname, int* id, Datum* geb, Datum* start, Datum* end, Student* final);
void inputData(char msg[30], char* ptr);
void inputMatrikel(char msg[30], int* ptr);
void addStudent(Student* stud, FILE* file);

char firstname[20];
char lastname[20];
int matrikel;
struct datum birth_date;
struct datum start_date;
struct datum end_date;

struct student subject;


struct datum{
	int day;
	int month;
	int year;
};


struct student{
	char firstName;
	char lastName;
	int matrikelNr;
	struct datum geb;
	struct datum start;
	struct datum ende;
};

int main(){

	char* pfirstname = &firstname;
	char* plastname = &lastname;
	int* pmatrikel = &matrikel;
	Datum* pbirth = &birth_date;
	Datum* pstartdate = &start_date;
	Datum* penddate = &end_date;

	Student* result = &subject;

	FILE* file = fopen("C:\\Users\\Seyfu\\Desktop\\students.txt", "w");
	inputStudent(pfirstname,plastname,pmatrikel,pbirth,pstartdate,penddate);
	combine(pfirstname,plastname,pmatrikel,pbirth,pstartdate,penddate, result);
	addStudent(result, file);
	readFile(file);
    return 0;
}

void readFile(FILE* file){
	Student* a = malloc(sizeof(Student));

	fread(a,sizeof(Student),1,file);
	fclose(file);
	printf("%d",a->matrikelNr);
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
	Student *a = malloc(sizeof(Student));
	a->firstName = *fname;
	a->lastName = *lname;
	a->matrikelNr = *id;
	a->geb = *geb;
	a->start = *start;
	a->ende = *end;
	final = a;
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
	scanf("%c ",ptr);
}
void inputMatrikel(char msg[30], int* ptr){
	printf(msg);
	scanf("%d ",ptr);
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

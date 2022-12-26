#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct datum Datum;
typedef struct student Student;


void chooseMode();
void addStudent(FILE* file);
void delete(FILE* file);
void deleteStudent(FILE* file, int matrikel);
void scanLinesforArray(FILE* file,char search[],int* ptr);
void combine(char (*fname)[20], char (*lname)[20], int* id, Datum* geb, Datum* start, Datum* end, Student* final);
void inputStudent(char (*fname)[20], char (*lname)[20], int* id, Datum* geb, Datum* start, Datum* end);
void inputData(char msg[30], char (*ptr)[20]);
void inputMatrikel(char msg[30], int* ptr);
void inputDatum(char msg[50], Datum* var);
void menue();
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
	FILE* file = fopen("C:\\Users\\Seyfu\\Desktop\\students.txt", "r");
	if(file == NULL){
		file = fopen("C:\\Users\\Seyfu\\Desktop\\students.txt", "w");
	}
	fclose(file);

	chooseMode();

	return 0;
}


void chooseMode(){
	int mode;
	menue();
	scanf("%d",&mode);
	if(mode>7){
		printf("ERROR");
		exit(0);
	}
	FILE* file;
	switch(mode){
	case 0:
		exit(0);
		break;
	case 1:
		chooseMode();
		break;
	case 2:
		file = fopen("C:\\Users\\Seyfu\\Desktop\\students.txt", "r+");
		addStudent(file);
		fclose(file);
		chooseMode();
		break;
	case 3:
		file = fopen("C:\\Users\\Seyfu\\Desktop\\students.txt", "r+");
		delete(file);
		fclose(file);
		chooseMode();
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	default:
		chooseMode();
		break;
	}
}


void delete(FILE* file){
	char matrikel[7],*ptr;
	ptr = &matrikel;
	printf("Wen möchtest du Löschen?\n");
	printf("Bitte Matrikelnummer angeben:\n");
	scanf("%s",ptr);
	deleteStudent(file, matrikel);
}


void deleteStudent(FILE* file, int matrikel){
	 int line,*lineptr;
	 lineptr = &line;
	 scanLinesforArray(file, ((char)matrikel), lineptr);
}


void scanLinesforArray(FILE* file, char search[], int* lineNr){
	char line[1024];
	int line_count = 0;
	while(fgets(line, sizeof(line),file) !=NULL){
		++line_count;
		printf(line);
//		if(strstr(line,search) != NULL){
//			printf("SUCCESS WITH LINE %d\n",(char)line_count);
//		}
	}
}


void addStudent(FILE* file){
		Student* stud = malloc(sizeof(Student));

		char (*firstname)[20] = malloc(sizeof(char[20]));
		char (*lastname)[20] = malloc(sizeof(char[20]));
		int* matrikel = malloc(sizeof(int));
		Datum* birth = malloc(sizeof(Datum));
		Datum* startdate = malloc(sizeof(Datum));
		Datum* enddate = malloc(sizeof(Datum));


		inputData("Bitte Vornamen angeben: \n",firstname);
		fflush(stdin);
		inputData("Bitte Nachnamen angeben: \n",lastname);
		fflush(stdin);
		inputMatrikel("Bitte Matrikelnummer angeben: \n",matrikel);
		fflush(stdin);
		inputDatum("Bitte Geburtsdatum(tt/mm/jjjj) angeben: \n",birth);
		fflush(stdin);
		inputDatum("Bitte Startdatum(tt/mm/jjjj) angeben: \n",startdate);
		fflush(stdin);
		inputDatum("Bitte Enddatum(tt/mm/jjjj) angeben: \n",enddate);

		combine(firstname, lastname, matrikel, birth, startdate, enddate, stud);

		if(file == NULL){
			printf("Error beim öffnen der Datei");
			return;
		}
		fseek(file,0,SEEK_END);

		fprintf(file,"%s\n%s\n%d\n%d/%d/%d\n%d/%d/%d\n%d/%d/%d\n"
				,stud->firstName,stud->lastName,stud->matrikelNr
				,stud->geb.day, stud->geb.month, stud->geb.year
				,stud->start.day, stud->start.month, stud->start.year
				,stud->ende.day, stud->ende.month, stud->ende.year);

		free(stud);
		free(firstname);
		free(lastname);
		free(matrikel);
		free(birth);
		free(startdate);
		free(enddate);
		printf("Schüler hinzugefügt!\n");
}


void combine(char (*fname)[20], char (*lname)[20], int* id, Datum* geb, Datum* start, Datum* end, Student* final){
	strcpy(final->firstName, fname);
	strcpy(final->lastName, lname);
	final->matrikelNr = *id;
	final->geb = *geb;
	final->start = *start;
	final->ende = *end;
}


void inputStudent(char (*fname)[20], char (*lname)[20], int* id, Datum* geb, Datum* start, Datum* end){
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


void inputData(char msg[30], char (*ptr)[20]){
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


void menue(){
    printf("Auflistung moeglicher Funktionen:\n----------------------------------\n");
    printf("0: exit(0); 						Diese Funktion verlässt das Programm.\n");
    printf("1: menue();                         Diese Funktion listet alle moeglichen Funktionen auf.\n");
    printf("2: addStudent();                    Diese Funktion erstellt einen neuen Studenten mit den eingetragenen Werten.\n");
    printf("3: inputStudent();                  Diese Funktion aendert die Daten eines Studenten.\n");
    printf("4: printStudent(Matrikelnummer);    Diese Funktion gibt alle Daten eines Studenten aus.\n");
    printf("5: studentCount();                  Diese Funktion gibt die Anzahl aller Stundenten aus.\n");
    printf("6: printAllStudents();              Diese Funktion gibt sortiert die Daten aller Studenten aus.\n");
    printf("7: deleteStundent(Matrikelnummer);  Diese Funktion löscht einen Studenten und seine Daten.\n");
    printf("Geben Sie die Nummer der gewünschten Funktion ein\n");
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

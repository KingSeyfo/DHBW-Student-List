#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct datum Datum;
typedef struct student Student;
typedef struct vliste Liste;


void vergleich();
void chooseMode();
void append(Liste** lst, Student* value);
void combineStruct(FILE* file);
void addStudent(FILE* file);
void delete(FILE* file);
void searchStudent(int* MatrikelNR);
void printStudent();
void deleteStudent(FILE* file, char* ptr);
void scanLinesforArray(FILE* file, char* search, int* ptr);
void combine(char(*fname)[20], char(*lname)[20], int* id, Datum* geb, Datum* start, Datum* end, Student* final);
void inputStudent(char(*fname)[20], char(*lname)[20], int* id, Datum* geb, Datum* start, Datum* end);
void inputData(char msg[30], char(*ptr)[20]);
void inputMatrikel(char msg[30], int* ptr);
void inputDatum(char msg[50], Datum* var);
void menue();
void SaveSingleStudent(FILE* file, Student* stud);
void saveToFile(FILE* file);
bool checkDatumisValid(int tag, int monat, int jahr);

struct datum {
	int day;
	int month;
	int year;
};


struct student {
	char firstName[20];
	char lastName[20];
	int matrikelNr;
	struct datum geb;
	struct datum start;
	struct datum ende;
};

struct vliste {
	Student s;
	struct vliste* next;
};


const char filepath[] = "students.txt";
Liste* liste;

int main() {
	FILE* file = fopen(filepath, "r+");
	if (file == NULL) {
		file = fopen(filepath, "w");
		file = fopen(filepath, "r+");
	}
	
	combineStruct(file);
	fclose(file);
//	printf(liste);
	chooseMode();
	//	vergleich();
	return 0;
}



void chooseMode() {
	int mode;
	menue();
	scanf("%d", &mode);
	if (mode > 7) {
		printf("ERROR");
		exit(0);
	}
	FILE* file;
	switch (mode) {
	case 0:
		file = fopen(filepath, "w");
		saveToFile(file);
		fclose(file);
		exit(0);
		break;
	case 1:
		chooseMode();
		break;
	case 2:
		//file = fopen(filepath, "r+");
		//addStudent(file);
		//fclose(file);
		//chooseMode();
		break;
	case 3:
		file = fopen(filepath, "r+");
		delete(file);
		fclose(file);
		chooseMode();
		break;
	case 4:
		printStudent();
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

void printStudent() {
	int* ma = malloc(sizeof(int));
	if (ma == NULL) {
		return -1;
	}
	
	printf("Bitte Matrikelnummer angeben:\n");
	scanf("%d", ma);
	searchStudent(ma);
	
}

void searchStudent(int *MatrikelNR) {
	while (liste->s.matrikelNr != MatrikelNR && liste->next != NULL) {
		liste = liste->next;
	}
	printf(liste->s.firstName);

}

void append(Liste** lst, Student* value) {
	Liste* neuesElement;

	while (*lst != NULL) {
		lst = &(*lst)->next;
	}

	neuesElement = malloc(sizeof(*neuesElement)); /* erzeuge ein neues Element */
	neuesElement->s = *value;
	neuesElement->next = NULL; /* Wichtig f�r das Erkennen des Listenendes     */

	*lst = neuesElement;
}

void saveToFile(FILE *file) {
	while (liste->next != NULL) {
		SaveSingleStudent(file, &liste->s);
		liste = liste->next;
	}
	SaveSingleStudent(file, &liste->s);

}

void combineStruct(FILE* file) {
	int linecnt = 0;
	char line[60];
	if (line == NULL) {
		printf("ERROR");
		return;
	}
	Student* sss = NULL;

	while (fgets(line, sizeof(line), file) != NULL) {
		line[strcspn(line, "\n")] = 0;
		char* test = line;
		//char* test = line;
		char* ohne = malloc(sizeof(test));
		strcpy(ohne, test);

		++linecnt;
		char* date[3];
		switch (linecnt) {
		case 1:
			sss = malloc(sizeof(Student));
			if (sss == NULL) {
				printf("ERROR");
				return;
			}
			strcpy(sss->firstName, ohne);
			break;
		case 2:
			strcpy(sss->lastName, ohne);
			break;
		case 3:
			sss->matrikelNr = atoi(line);
			break;
		case 4:
			date[0] = strtok(line, "/");
			date[1] = strtok(NULL, "/");
			date[2] = strtok(NULL, "/");
			sss->geb.day = atoi(date[0]);
			sss->geb.month = atoi(date[1]);
			sss->geb.year = atoi(date[2]);
			break;
		case 5:
			date[0] = strtok(line, "/");
			date[1] = strtok(NULL, "/");
			date[2] = strtok(NULL, "/");
			sss->start.day = atoi(date[0]);
			sss->start.month = atoi(date[1]);
			sss->start.year = atoi(date[2]);
			break;
		case 6:
			date[0] = strtok(line, "/");
			date[1] = strtok(NULL, "/");
			date[2] = strtok(NULL, "/");
			sss->ende.day = atoi(date[0]);
			sss->ende.month = atoi(date[1]);
			sss->ende.year = atoi(date[2]);

			linecnt = 0;

			append(&liste, sss);
			free(sss);
			break;

		default:
			break;
		}
	}
	fclose(file);
}


void delete(FILE* file) {
	char* ma = malloc(sizeof(char[7]));
	printf("Wen m�chtest du L�schen?\n");
	printf("Bitte Matrikelnummer angeben:\n");
	scanf("%s", ma);
	deleteStudent(file, ma);
	free(ma);
}


void deleteStudent(FILE* file, char* ptr) {
	int line, * lineptr;
	lineptr = &line;
	scanLinesforArray(file, ptr, lineptr);
	//Unfertig
}


void scanLinesforArray(FILE* file, char* search, int* lineNr) {
	//	char line[1024];
	char* line = malloc(sizeof(char) * 1024);
	int line_count = 0;

	printf("STRING: %s\n", search);

	while (fgets(line, sizeof(line), file) != NULL) {
		++line_count;
		printf(line);


		//		char *temp = malloc(strlen(line));
		//		strncpy(temp,line,strlen(line));

		char* found_string = strstr(line, search);

		if (found_string == NULL) {
			//	        printf ("Substring not found in the string\n");
		}
		else {
			printf("Substring located -> %d\n", line_count);
		}

		//		free(temp);
	}
}


void vergleich() {
	char main_string[50] = "this is a testing string for testing";
	char search_string[30] = "test";

	char* found_string = strstr(main_string, search_string);

	if (found_string == NULL)
	{
		printf("Substring not found in the string");
	}
	else
	{
		printf("Substring located -> %s", found_string);
	}
}


void SaveSingleStudent(FILE* file, Student *stud) {

	if (file == NULL) {
		printf("Error beim �ffnen der Datei");
		return;
	}
	fseek(file, 0, SEEK_END);

	fprintf(file, "%s\n%s\n%d\n%d/%d/%d\n%d/%d/%d\n%d/%d/%d\n"
		, stud->firstName, stud->lastName, stud->matrikelNr
		, stud->geb.day, stud->geb.month, stud->geb.year
		, stud->start.day, stud->start.month, stud->start.year
		, stud->ende.day, stud->ende.month, stud->ende.year);
}


void combine(char(*fname)[20], char(*lname)[20], int* id, Datum* geb, Datum* start, Datum* end, Student* final) {
	strcpy(final->firstName, fname);
	strcpy(final->lastName, lname);
	final->matrikelNr = *id;
	final->geb = *geb;
	final->start = *start;
	final->ende = *end;
}


void inputStudent(char(*fname)[20], char(*lname)[20], int* id, Datum* geb, Datum* start, Datum* end) {
	inputData("Bitte Vornamen angeben: \n", fname);
	fflush(stdin);
	inputData("Bitte Nachnamen angeben: \n", lname);
	fflush(stdin);
	inputMatrikel("Bitte Matrikelnummer angeben: \n", id);
	fflush(stdin);
	inputDatum("Bitte Geburtsdatum(tt/mm/jjjj) angeben: \n", geb);
	fflush(stdin);
	inputDatum("Bitte Startdatum(tt/mm/jjjj) angeben: \n", start);
	fflush(stdin);
	inputDatum("Bitte Enddatum(tt/mm/jjjj) angeben: \n", end);
}


void inputData(char msg[30], char(*ptr)[20]) {
	printf(msg);
	scanf("%s", ptr);
}


void inputMatrikel(char msg[30], int* ptr) {
	printf(msg);
	scanf("%d", ptr);
}


void inputDatum(char msg[50], Datum* var) {
	int tag, monat, jahr;
	printf(msg);
	scanf("%d/%d/%d", &tag, &monat, &jahr);
	if (!checkDatumisValid(tag, monat, jahr)) {
		inputDatum(msg, var);
	}
	else {
		Datum a;
		a.day = tag;
		a.month = monat;
		a.year = jahr;
		*var = a;
	}
}


void menue() {
	printf("Auflistung moeglicher Funktionen:\n----------------------------------\n");
	printf("0: exit(0); 						Diese Funktion verl�sst das Programm.\n");
	printf("1: menue();                         Diese Funktion listet alle moeglichen Funktionen auf.\n");
	printf("2: addStudent();                    Diese Funktion erstellt einen neuen Studenten mit den eingetragenen Werten.\n");
	printf("3: inputStudent();                  Diese Funktion aendert die Daten eines Studenten.\n");
	printf("4: printStudent(Matrikelnummer);    Diese Funktion gibt alle Daten eines Studenten aus.\n");
	printf("5: studentCount();                  Diese Funktion gibt die Anzahl aller Stundenten aus.\n");
	printf("6: printAllStudents();              Diese Funktion gibt sortiert die Daten aller Studenten aus.\n");
	printf("7: deleteStundent(Matrikelnummer);  Diese Funktion l�scht einen Studenten und seine Daten.\n");
	printf("Geben Sie die Nummer der gew�nschten Funktion ein\n");
}


bool checkDatumisValid(int tag, int monat, int jahr) {
	if (jahr >= 1900 && jahr <= 9999) {
		if (monat >= 1 && monat <= 12) {
			if ((tag >= 1 && tag <= 31) && (monat == 1 || monat == 3 || monat == 5 || monat == 7 || monat == 8 || monat == 10 || monat == 12)) {
				return true;
			}
			else if ((tag >= 1 && tag <= 30) && (monat == 4 || monat == 6 || monat == 9 || monat == 11)) {
				return true;
			}
			else if ((tag >= 1 && tag <= 28) && (monat == 2)) {
				return true;
			}
			else if (tag == 29 && monat == 2 && (jahr % 400 == 0 || (jahr % 4 == 0 && jahr % 100 != 0))) {
				return true;
			}
			else {
				printf("Ung�ltiger Tag.\n");
				return false;
			}
		}
		else {
			printf("Ung�ltiger Monat.\n");
			return false;
		}
	}
	else {
		printf("Ung�ltiges Jahr.\n");
		return false;
	}
}

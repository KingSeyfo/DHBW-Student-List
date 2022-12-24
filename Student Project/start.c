#include <stdio.h>

//Ausflistung aller Funktionen, kann selbstständig oder bei falschem Input aufgerufen werden.
menue(){
    printf("Auflistung moeglicher Funktionen:\n----------------------------------\n");
    printf("menue();                         Diese Funktion listet alle moeglichen Funktionen auf.\n");
    printf("addStudent();                    Diese Funktion erstellt einen neuen Studenten mit den eingetragenen Werten.\n");
    printf("inputStudent();                  Diese Funktion aendert die Daten eines Studenten.\n");
    printf("printStudent(Matrikelnummer);    Diese Funktion gibt alle Daten eines Studenten aus.\n");
    printf("studentCount();                  Diese Funktion gibt die Anzahl aller Stundenten aus.\n");
    printf("printAllStudents();              Diese Funktion gibt sortiert die Daten aller Studenten aus.\n");
    printf("deleteStundent(Matrikelnummer);  Diese Funktion löscht einen Studenten und seine Daten.\n");
}

addStudent(){
    // student new Student
}

//Abändern der Daten eines Studenten
inputStudent(){
    char pNachname[50];
    printf("Enter new Nachname");
    scanf("%c",&pNachname);
    //student.nachname = pNachname;

    int pMatrikelnummer;
    printf("Enter new Matrikelnummer");
    scanf("%d",&pMatrikelnummer);
    //student.matrikelnummer = pMatrikelnummer;

    //datum pStartdatum;
    printf("Enter new Startdatum (Format:dd/mm/yy)");
    //scanf("%d/%d/%d",&),&pStartdatum.day,&pStartdatum.month,&pStartdatum.year); // mit Datumscheck
    //student.startdatum = pStartdatum;

    //datum pEnddatum;
    printf("Enter new Enddatum (Format:dd/mm/yy)");
    //scanf("%d/%d/%d",&),&pEnddatum.day,&pEnddatum.month,&pEnddatum.year); // mit Datumscheck
    //student.enddatum = pEnddatum;

    //datum pGeburtsdatum;
    printf("Enter new Geburtsdatum (Format:dd/mm/yy)");
    //scanf("%d/%d/%d",&),&pGeburtsdatum.day,&pGeburtsdatum.month,&pGeburtsdatum.year); // mit Datumscheck
    //student.geburtsdatum = pGeburtsdatum;
}

printStudent(int pMatrikelnummer){
    //suche nach student.matrikelnummer == pMatrikelnummer, falls nicht existiert error ausspucken
    printf("Nachname:%c\nMatrikelnummer:%d\nStartdatum:%d/%d/%d");
    //printf("Matrikelnummer:%d\n",&student.matrikelnummer);
    //printf("Startdatum:%\n", );
    //printf("Enddatum:%\n", );
    //printf("Geburtsdatum:%\n", );
}

studentCount(){
    int i = 0;
    // while (student.next != NULL){
    //    student = student.next;
    //    i++;
    //}
    printf("Die Anzahl der Stundenten betraegt:%d\n",&i);
}

printAllStundents(){
    printf("Daten aller Stundenten:\n");
    //spätestens jetzt die Studentenliste sortieren
    //while(student.next != NULL){
    //    student = student.next;
    //    printf("%c, %d, %, % ,%\n"student.nachname,student.matrikelnummer,student.startdatum,student.enddatum,student.geburtstag);
    //}
}

deleteStudent(int pMatrikelnummer){
    //suche nach student.matrikelnummer == pMatrikelnummer
    //zeiger des studentenvorher zeigt auf student.next
    //danach element student löschen
}

/*save(){
    bei beendung des Programms soll eine Datei erzeugt werden
    in der alle Studenten gespeichert werden sollen 
}

  read(){
    bei start des Programms soll die Datei ausgelesen werden 
    und aus den Daten eine neue Liste erstellt werden.
  }
*/

checkDate(){
    int dd,mm,yy;
     
    printf("Enter date (DD/MM/YYYY format): ");
    scanf("%d/%d/%d",&dd,&mm,&yy);
     
    //check year
    if(yy < 1900 || yy > 9999){
        printf("Year ist not valid.\n");
        return 0;
    }
    //check month
    if(mm < 1 || mm > 12){
        printf("Month is not valid.\n");
        return 0;
    }
    //check days
    if((dd>=1 && dd<=31) && (mm==1 || mm==3 || mm==5 || mm==7 || mm==8 || mm==10 || mm==12)){
        printf("Date is valid.\n");}
    else if((dd>=1 && dd<=30) && (mm==4 || mm==6 || mm==9 || mm==11)){
        printf("Date is valid.\n");}
    else if((dd>=1 && dd<=28) && (mm==2)){
        printf("Date is valid.\n");}
    else if(dd==29 && mm==2 && (yy%400==0 ||(yy%4==0 && yy%100!=0))){
        printf("Date is valid.\n");}
    else{
        printf("Day is invalid.\n");}
    return 0;    
}


int main(){
    struct date{
        int day;
        int month;
        int year;
    };
    struct student{
        char nachname[50];
        int matrikelnummer;
        //date startdatum;
        //date enddatum;
        //date geburtsdatum;
    };

}

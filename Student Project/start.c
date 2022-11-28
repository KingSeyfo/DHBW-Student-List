#include <stdio.h>
#include <stdbool.h>

void inputDatum();
bool checkDatum();
int main(){
	inputDatum();
    return 0;
}


struct datum{
        int day;
        int month;
        int year;
};


struct student{
	char firtName[50];
	char lastName[50];
	int matrikelNr;
	struct datum geb;
	struct datum start;
	struct datum ende;
};


void inputDatum(){
	int tag,monat,jahr;
	printf("Bitte Datum eingeben (tt/mm/jjjj Format): ");
	scanf("%d/%d/%d",&tag,&monat,&jahr);
	checkDatum(tag, monat, jahr);
}


bool checkDatum(int tag, int monat, int jahr){
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

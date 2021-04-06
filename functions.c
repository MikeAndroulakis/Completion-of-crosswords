#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int function1(char *tempfile)//synartisi poy metraei tis lekseis toy leksikoy
{	
	FILE *fp;
	int arithmosleksewn;
	fp = fopen(tempfile,"r");
	arithmosleksewn=0;
	char ch='t';//diabazei xaraktires
	if(fp == NULL)
		return 1;
	while(ch!=EOF){
		ch = fgetc(fp);//diabasma xaraktirwn
		if(ch == '\n')//an brethike allagh grammhs shmainei oti exoyme mia leksh
			arithmosleksewn++;//ayksanoyme to metriti twn leksewn
			
	}
	fclose(fp);
	return arithmosleksewn;
}

int *function2(int arithmosleksewn,char *tempfile)//synarthsh poy diavazei ta mhkh twn leksewn toy leksikoy kai ta apothikeyei se pinaka
{
	FILE *fp;
	int j,g=0;
	char ch='l';
	int *mikileksikoy = malloc(arithmosleksewn*sizeof(int));//pinakas me mhkh twn leksewn toy leksikoy
	fp = fopen(tempfile,"r");//ksananoigoyme to file gia dhmioyrgia katalliloy pinaka analoga me ta grammata kathe leksis
	for(j=0; j<arithmosleksewn; j++)//briskoyme ta mhkh gia kathe leksh
	{
		ch='0';//arxikopoihsh gia epomenh epanalipsi
		while(ch!='\n')//mexri na ginei allagh grammhs(allagh lekshs)
		{
			ch = fgetc(fp);
			g++;//aykshsh toy metriti analoga me ta grammata ths lekshs toy leksikoy
		}
		mikileksikoy[j]=g-1;//fylassetai to mhkos kathe lekshs toy leksikoy
		g=0;
	}
	fclose(fp);
	return mikileksikoy;
}
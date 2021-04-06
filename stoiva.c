#include <stdio.h>
#include <stdlib.h>
#include "stoiva.h"


struct node *firstsetstack(struct node *temptop,int arithmosleksewn)//dimioyrgia stack
{
	struct node *neos;
	neos=malloc(sizeof(struct node));//Dhmiourgoume kainoyrio komvo
	if(neos==NULL){
		printf("There is no memory\n");
	}
	if(temptop==NULL){//an einai o prwtos komvos poy fimioyrghsame tote deixnei se NULL to beforestack
		neos->beforestack=NULL;
	}
	else{//alliws
		neos->beforestack=temptop;//deixnei sto proigoymeno
	}
	int i,j;
	neos->deadlist=(char **)malloc((arithmosleksewn)*sizeof(char *));//desmeysh pinaka gia tis lekseis poy exoyn idi mpei
	if(neos->deadlist==NULL){
		printf("There is no memory\n");
	}
	for(i=0;i<arithmosleksewn;i++)//desmeyoyme xwro gia kathe leksi toy pinaka toy deadlist
	{
		neos->deadlist[i]=(char *)malloc((128)*sizeof(char));//me max orio 128(de mporei n mpei leksi me panw apo 128 grammata
		if(neos->deadlist[i]==NULL){
			printf("There is no memory\n");
		}
		for(j=0;j<128;j++)
		{
			neos->deadlist[i][j]='0';
		}
	}
	neos->metrdeadlist=0;
	neos->metrsyntet=0;
	return neos;
}

void setinfosgrst(struct node *top,int arithmos,int grst){
	top->arithmosgrst=arithmos;
	top->orikathe=grst;
}

void setprwththesh(struct node *top,int prwththesh){//arxikopoieitai h metablhth wste na deixnei se poia thesh toy stayroleksoy arxizei h leksh
	top->prwththesh=prwththesh;
}


void setdeadlistword(struct node *top,char character,int metritisgrammatwn){		
	top->deadlist[top->metrdeadlist][metritisgrammatwn]=character;
}


void auksisimetrdeadlist(struct node *top,int arithmosleksewn){
	top->metrdeadlist++;
	if(top->metrdeadlist>(arithmosleksewn-1)){
		top->metrdeadlist=arithmosleksewn-1;
	}
}

void dhmiourgiapinakasyntetagmenwn(struct node *top,int mhkoslekshs){
	int i;
	top->mhkosleksis=mhkoslekshs;
	top->syntetagmenes=(int *)malloc((mhkoslekshs)*sizeof(int));//dhmioyrgia pinaka me tis syntetagmenes twn stoixeiwn poy yparxoyn prin baloyme thn leksi
	for(i=0;i<mhkoslekshs;i++){
		top->syntetagmenes[i]=0;//sthn arxh gemizei me mhdenika
	}
}

void beforestep(struct node *top,int thesixaraktira){//elegxos an einai orizontia h katheta kai arithmos=o arithmos ths sthlhs h ths grammhs 
	top->syntetagmenes[top->metrsyntet]=thesixaraktira;//apothikeyontai sto pinaka oi theseis twn grammatwn poy proyphrxan
	top->metrsyntet++;
}

struct node *back(int arithmosleksewn,int *mikileksikoy,struct node *top,char **pinalex , char **staurolex)
{
	int j,i,k,l;
	j=0;
	int apothikeysiprwtisthesis;
	int apothikeysimhkousleksis;
	int apothikeysigrst;
	int elegxos1=0;
	int elegxos2=0;
	int metritis=0;
	int koinagrammata=0;
	top=deletestructs(top,arithmosleksewn);
	if(top==NULL){
		return NULL;
	}
	apothikeysiprwtisthesis=top->prwththesh;
	apothikeysimhkousleksis=top->mhkosleksis;
	apothikeysigrst=top->arithmosgrst;
	int diaxwrismos;
	if(top->orikathe==0){//an exoyme grammh
		diaxwrismos=0;
	}
	else{//an exoyme sthlh
		diaxwrismos=1;
	}
	for(i=(top->prwththesh);i<(top->mhkosleksis+top->prwththesh);i++){//anazhtame gia kathe gramma
		for(l=0;l<(top->mhkosleksis);l++){//an h syntetagmeni toy yparxei sto pinaka twn syntetagmenwn
			if(i==top->syntetagmenes[l]){//an den yparxei tote sth sygkekrimeni thesi sto stayrolekso mpainei '0'
				elegxos1=1;
			}
		}
		if(elegxos1==1){
			elegxos1=0;
		}
		else{//an den proyphrxe to gramma tote sbhnetai
			if(top->orikathe==0){//an exoyme grammh
				staurolex[top->arithmosgrst][i]='0';
			}
			else{//an exoyme sthlh
				staurolex[i][top->arithmosgrst]='0';
			}
		}
	}
	for(j=0;j<arithmosleksewn;j++){//gia oles tis lekseis toy stayroleksoy
		elegxos2=0;
		if(top->mhkosleksis==mikileksikoy[j]){//an h sygkekrimeni leksi exei idio mhkos me ti leksi poy anazhtame
			k=0;
			metritis=0;
			for(i=top->prwththesh;i<(top->mhkosleksis+top->prwththesh);i++){//gia oles tis theseis
				if(top->orikathe==0){//elegxetai an tairiazei ena ena gramma
					if((staurolex[top->arithmosgrst][i]==pinalex[j][k])||(staurolex[top->arithmosgrst][i]=='0')){
						metritis++;
					}
				}
				else{
					if((staurolex[i][top->arithmosgrst]==pinalex[j][k])||(staurolex[i][top->arithmosgrst]=='0')){
						metritis++;
					}
				}
				k++;
			}	
			k=0;
			if(metritis==top->mhkosleksis){//an ola tairiazoyne
				for(i=0;i<arithmosleksewn;i++){//tote
					if(top->deadlist[i][0]=='0'){
						break;
					}
					for(l=0;l<top->mhkosleksis;l++){
						if(top->deadlist[i][l]!='0'){//elegxoyme an h leksi ayth yparxei sto deadlist
							if(top->deadlist[i][l]==pinalex[j][l]){
								koinagrammata++;
							}
						}
						else{
							break;
						}
					}
					if((koinagrammata==top->mhkosleksis)&&(top->deadlist[i][l]=='0')){//paizei na einai ta prwta grammata idia kai meta na einai diaforetikh h leksi
						koinagrammata=0;
						elegxos2=1;
						break;//an ola ta grammata einai idia tote termatismos
					}
					koinagrammata=0;
				}
				if(elegxos2==1){//an h leksi brethike sto deadlist synexise gia thn epomenh leksi
					elegxos2=0;
					continue;
				}
				k=0;
				for(i=top->prwththesh;i<(top->prwththesh+top->mhkosleksis);i++){//an i leksi den yparxe sto deadlist
					if(top->orikathe==0){//an exoyme grammh
						staurolex[top->arithmosgrst][i]=pinalex[j][k];//mpainoyn ta grammata sto stayrolekso
					}
					else{//an exoyme sthlh
						staurolex[i][top->arithmosgrst]=pinalex[j][k];
					}
					top->deadlist[top->metrdeadlist][k]=pinalex[j][k];//h leksi mpainei sto deadlist
					k++;
				}
				auksisimetrdeadlist(top,arithmosleksewn);//kaleitai h synarthsh ayksisis toy metrdeadlist
								       //wste thn epomenh fora h allh leksi na mpei sthn epomenh thesi
				k=0;
				break;
			}
			
		}
		if(j==(arithmosleksewn-1)){//an de brethike leksi
			top=back(arithmosleksewn,mikileksikoy,top,pinalex,staurolex);//tote opisthodromisi
			if(top==NULL){
				return NULL;
			}	
			top=firstsetstack(top,arithmosleksewn);//otan epistrepsoyme apo thn opisthodromisi ksanaftiaxnoyme th stack
								//poy eixame
			setinfosgrst(top,apothikeysigrst,diaxwrismos);
			setprwththesh(top,apothikeysiprwtisthesis);
			dhmiourgiapinakasyntetagmenwn(top,apothikeysimhkousleksis);
			for(i=apothikeysiprwtisthesis;i<(apothikeysimhkousleksis+apothikeysiprwtisthesis);i++){
				if(diaxwrismos==0){
					if(staurolex[apothikeysigrst][i]!='0'){
						beforestep(top,i);//gemizoyme enan enan xaraktira toys pinakes
					}
				}
				else{
					if(staurolex[i][apothikeysigrst]!='0'){
						beforestep(top,i);
					}
				}
			}
			j=-1;//to j ginetai -1 gia na ksanapsaksei leksi
		}
	}
	return top;
}


struct node *deletestructs(struct node *top,int arithmosleksewn){
	int i;
	struct node *temp;
	if(top->beforestack!=NULL)//an yparxei proigoymenos komvos
	{
		temp=top->beforestack;
		free(top->syntetagmenes);//kane apodesmeyseis mnimis
		for(i=0;i<arithmosleksewn;i++){
			free(top->deadlist[i]);
		}
		free(top->deadlist);
		free(top);
		return temp;
	}
	else//ama ftasame sth prwth stoiva shmainei oti to stayrolekso den exei lysh
	{
		printf("The staurolex has no solution\n");
		return NULL;
	}
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stoiva.h"
#include "functions.h"

int main(int argc , char *argv[]){
	int i,l;
	int elegxos=0,mhkos,flag=0;//mhkos=diastaseis stayroleksoy,flag=gia kapoion elegxo
	//int eisodos=0;
	int draw=0;
	//int checker=0;
	int arithmosleksewn;//arithmos twn leksewn toy leksikoy
	char *tempfile="Words.txt",*crosstempfile =argv[1];
	for(i=0; i<argc; i++)
	{
		if(strcmp(argv[i],"-dict")==0){//an brethike orisma dict shmainei oti kaloyme allo leksiko opote
			tempfile=argv[i+1];
		}
		if(strcmp(argv[i],"-check")==0){//an yparxei -check kane thn eisodo 1
			//checker=1;
		}
		if(strcmp(argv[i],"-draw")==0){//an sthn grammh entolwn yparxei -draw kane th metabliti 1
			draw=1;
		}
	}
	FILE *fp;
	int j,metr=0;//metr=posa black boxes exoyme(gia dhmioyrgia katallhloy pinaka)
	arithmosleksewn = function1(tempfile);
	int *mikileksikoy;
	mikileksikoy = function2(arithmosleksewn,tempfile);
	char **pinalex;
	pinalex	= malloc((arithmosleksewn) * sizeof(char *));//pinakas poy fyllaei tis lekseis toy leksikoy px toy word.txt
	if(pinalex==NULL){
		printf("No memory");
	}
	for(j=0; j<(arithmosleksewn); j++)
	{
		pinalex[j] = (char *)malloc(mikileksikoy[j]*sizeof(char));//dhmioyrgia pinaka gia kathe leksh toy leksikoy
		if(pinalex[j]==NULL){
			printf("NO memory\n");
			return 1;
		}
	}
	int takis=0;//otan xreiazetai na ayksiseis ena metriti takis is there
	char ch;
	ch='t';
	/*int eleg=0;
	if(eisodos==1){
		int metreisodou=0;
		fp = fopen("eisodos.txt", "ab+");
		while(ch!=EOF){
				//printf("troll");
				ch=fgetc(stdin);
				if(ch==EOF){
					break;
				}
				fprintf(fp,"%c",ch);
				if(ch=='\n'){
					eleg++;
				}
			
		}
		fclose(fp);
		printf("eleg=%d",eleg);
		ch='t';
		int *mikipinaka;
		mikipinaka=malloc(eleg*sizeof(int));
		fp=fopen("eisodos.txt","r");
		ch=fgetc(fp);
		for(i=0;i<eleg;i++){
			ch='t';
			while(ch!='\n'){
				ch=fgetc(fp);
				if(ch=='\n'){
					mikipinaka[i]=metreisodou;
					printf("eisod=%d ",metreisodou);
					metreisodou=0;
					break;
				}
				metreisodou++;
			}
				
		}
		fclose(fp);
		for(i=0;i<eleg;i++){
		
		}
	}*/
	fp=fopen(tempfile,"r");//anoigma toy arxeioy twn leksewn toy leksikoy gia apothikeysh toys sto pinaka poy dhmioyrgisame
	for(j=0;j<(arithmosleksewn);j++)
	{//gia oles tis lekseis
		ch='0';
		while(ch!='\n')//an eimaste sthn idia leksh
		{
			ch=fgetc(fp);//diabazoyme gramma
			if(ch=='\n')//an brethike allagh grammhs tote bale sto pinaka kai to \n wste na exoyme strings
			{
				pinalex[j][takis]='\0';
			}
			else
			{
				pinalex[j][takis]=ch;//to apothikeyoume sto pinaka
			}
			takis++;//ayksanoyme ton taki gia to epomeno  gramma
		}
		if(ch=='\n')
		{//an brethike allh leksh
			takis=0;//mhdenismoi
			ch='0';
		}
	}
	fclose(fp);//kleisimo arxeio leksikoy
	elegxos=0;
	ch='0';
	int metabliti=0;
	int t=0;
	fp = fopen(crosstempfile,"r");//anoigma arxeio stayroleksoy gia na metrisoume ta mayra koutia
	while(ch!=EOF)//an de teliwse to arxeio
	{	
		ch = fgetc(fp);//diabasma xaraktiras
		if(ch == '\n'){//an brethike allo mayro kouti
			elegxos=1;
			metr++;//metritis poy deixnei posa mayra koutakia exoyme
		}
		if(elegxos==0)//edw apothikeyei th diastash
		{
			if(t==0){//an exoyme diastaseis pinaka<10
				mhkos=ch-'0';
			}
			if(t==1){//an exoyme diastaseis pinaka>10
				mhkos=mhkos*10;
				metabliti=ch-'0';
				mhkos=mhkos+metabliti;
			}
		}
		t++;
	}
	fclose(fp);//kleismo
	char **stayrolekso;//ppinakas gia tis theseis toy stayroleksoy
	stayrolekso=(char **)malloc((mhkos+1)*sizeof(char *));//desmeyetai xwros gia tis grammes kai tis stiles toy stayroleksoy
	for(i=1;i<=mhkos;i++)
	{
		stayrolekso[i]=(char *)malloc((mhkos+1)*sizeof(char));//(1parapanw thesi kathws to stayrolekso arxizei apo arithmisi0)
	}
	if(metr>1)
	{
		int **blackbox =(int **) malloc((metr-1)*sizeof(int *));//dysdiastatos pinakas gia thn apothikeysi twn mayrwn koytiwn
		if(blackbox==NULL){
			printf("NO memory");
		}
		for(i=0; i<metr-1; i++)//gia ola ta mayra koytia poy diabastikan
		{
			blackbox[i]=(int *)malloc(2*sizeof(int));//dhmioyrgoyme dysdiasto pinaka gia thn apothikeysh twn syntetagmenwn
			if(blackbox[i]==NULL){
				printf("NO memory");
			}
		}
		elegxos = 0;
		fp = fopen(crosstempfile,"r");//anoigma toy arxeiou toy stayroleksoy gia na gemisoyme to pinaka twn blackboxes
		int metritis=0;
		while(flag!=1)
		{
			if(elegxos==0)//sth prwth epanalipsi apla diabazetai h diastash toy stayroleksoy
			{
				int lel;
				fscanf(fp,"%d",&lel);
				//printf("%d",lel);
				elegxos=1;//o elegxos ginetai 1 wste n mh ksanampei
			}
			fscanf(fp,"%d",&blackbox[metritis][0]);//oi times mpainoyn sto pinaka
			fscanf(fp,"%d",&blackbox[metritis][1]);
			metritis++;//se poio mauro koyti briskomaste
			if(metritis==(metr-1)){//an diabasthkan ola ta mayra koutia
				flag=1;//termatismos
			}
		}
		fclose(fp);
		int a,b;
		for(i=0;i<(metr-1);i++)//sto pinaka toy stayroleksoy pernioyntai ta mayra koytia
		{
			a=blackbox[i][0];
			b=blackbox[i][1];
			stayrolekso[a][b]='#';//kai oi theseis gemizoyn me #
		}


	}
	for(i=1; i <=mhkos; i++)//ola ta ypoloipa koutakia gemizoyn me 0
	{
		for(j=1; j<=mhkos; j++)
		{
			if(stayrolekso[i][j]!='#'){
				stayrolekso[i][j]='0';
			}
		}
	}
/* MEXRI EDW exoyme gemisei to stayrolekos me mhdenika h me '#' , exoyme ena polydiastato pinaka poy na krataei olo to words.txt */
	int mikosleksis=0;
	int metritis=1;
	int k,katallilithesi=1;
	int prwtithesi=1;//elegxos wste na mpoyme sth katallili thesh toy stayroleksoy
	int katallili=0;//elegxos gia to an einai katallhli mia leksh na mpei sto stayrolexo
	struct node *top;
	top=NULL;
	elegxos=0;
	int dead=0;
	int elegxosdead=0;
	int olikoselegxos=0;
	int kathorismos=0;//metabliti poy mas deixnei an briskomaste se grammh h sthlh(an einai artios se grammh kai perittos se sthlh
	while(metritis<=mhkos){//metriti poy deixnei se poia sthlh-grammh briskomaste
		while(katallilithesi<mhkos){//me th katallilithesi diabazoyme olokliri th grammh h th sthlh
			elegxos=0;
			mikosleksis=0;
			if((kathorismos%2)!=0){//an o kathorismos einai perittos(diladi eimaste se sthlh)
				while(stayrolekso[katallilithesi][metritis] == '#'){//prosperna ta prwta #
					if (katallilithesi == mhkos ){//an ftasame sto telos ths sthlhs
						elegxos=1;//o elegxos ginetai 1 gia n bgei kai apo thn ekswterikh while
						break;//termatismos
					}
					katallilithesi++;//h thesi poy briskomaste gia diabasma ayksanetai(proxwrame mia thesi)
				}
			}
			else{//an eimaste gia grammh
				while(stayrolekso[metritis][katallilithesi] == '#'){//prospername ta mhdenika
					if (katallilithesi == mhkos ){//an ftasame sto telos ths grammhs
						elegxos=1;//termatismos
						break;
					}
					katallilithesi++;//ayksisi ths theshs sthn opoia briskomaste
				}
			}
			prwtithesi=katallilithesi;//se ayth thn thesi ksekinane oi mh # theseis toy stayroleksoy
			if(elegxos==1){//an exoyme ftasei sto telos grammhs h sthlh break
				break;
			}
			if((kathorismos%2)!=0){//an eimaste gia sthlh
				while((katallilithesi<=mhkos)&&(stayrolekso[katallilithesi][metritis] != '#')){//an de ftasame sto 
					//telos kai an de synantisame #
					mikosleksis++;//posa grammata yparxoyn sth grammh
					katallilithesi++;//ayksisi ths katallilisthesis gia na deixnei ston epomeno
					if(katallilithesi>mhkos){//an bghkame ektos oriwn termatismos
						break;
					}
				}
			}
			else{//an eimaste se grammh
				while((katallilithesi<=mhkos)&&(stayrolekso[metritis][katallilithesi] != '#')){
					mikosleksis++;//posa grammata yparxoyn sth grammh
					katallilithesi++;
					if(katallilithesi>mhkos){
						break;
					}
				}
			}
			/*if(elegxos==1){
				break;
			}*/
			if(mikosleksis==1){//an yparxei ena gramma anamesa se 2 diesh apla synexizoyme thn epomenh epanalipsi
				continue;
			}
			else{//alliws
				if(olikoselegxos==0){//an eimaste sth prwth dimioyrgia stoibas kanoyme to beforestoiva NULL(ths stoiv)
					top=firstsetstack(NULL,arithmosleksewn);
					olikoselegxos=1;//o elegxos ginetai 1 gia n mh ksnampei
				}
				else{
					top=firstsetstack(top,arithmosleksewn);
				}
			}
			if((kathorismos%2)!=0){//an eimaste gia sthlh
				setinfosgrst(top,metritis,1);//to orikathe ginetai 1(ths synarthshs)
			}
			else{
				setinfosgrst(top,metritis,0);//to orikathe ginetai 0(ths synarthshs)
			}
			setprwththesh(top,prwtithesi);//arxikopoieitai h prwth thesh poy arxizei h leksi
			dhmiourgiapinakasyntetagmenwn(top,mikosleksis);//dimioyrgia pinaka gia fylagma syntetagmenwn
			katallilithesi=prwtithesi;//h katallilithesi ksanadeixnei ekei poy arxizei h leksi
			for(k=0;k<mikosleksis;k++){//h epanalipsi ginetai oses fores to mikosleksis
				if((kathorismos%2)!=0){//an eimaste se sthlh
					if(stayrolekso[katallilithesi][metritis]!='0'){//an sth sygkekrimenh thesh den exoyme 0
										       //diladi exoyme gramma
						beforestep(top,katallilithesi);//gemizoyme mia mia syntetagmenh toys pinakes
					}
				}
				else{//an eimaste se grammh
					if(stayrolekso[metritis][katallilithesi]!='0'){
						beforestep(top,katallilithesi);//gemizoyme mia mia syntetagmenh toys pinakes
					}
				}
				katallilithesi++;//se poio gramma briskomaste
				if(katallilithesi==mhkos){//an ftasame sto telos ths grammhs o elegxos ginetai 1
					elegxos=1;
				}
			}
			for(j=0;j<arithmosleksewn;j++){//gia oles tis lekseis toy leksikoy
				katallilithesi=prwtithesi;//h katallilithesi ksanadeixnei sth prwti
				if(mikosleksis==mikileksikoy[j]){//an h sygkekrimeni leksi toy leksikoy exei idio mhkos me ayto poy
							         //psaxnoyme
					k=0;
					for(i=top->prwththesh;i<(top->prwththesh+top->mhkosleksis);i++){//gia oles tis theseis
						if((kathorismos%2)!=0){//an exoyme sthlh
							if((stayrolekso[i][metritis]==pinalex[j][k])||(stayrolekso[i][metritis]=='0')){
							//an to gramma einai idio stoys dyo pinakes h sto stayrolekso sth sygkekrimeni
							//thesi yparxei 0(diladi mporei na mpei otidhpote)
								katallili++;//ayksisi toy metriti katallili
							}
						}
						else{//an exoyme grammh
							if((stayrolekso[metritis][i]==pinalex[j][k])||(stayrolekso[metritis][i]=='0')){
								katallili++;
							}							
						}
						k++;//to k ayksanetai gia n mpoyme sthn epomenh thesi toy pinaka twn leksewn toy leks
					}
					if(katallili==mikosleksis){//an ola ta grammata htan idia(h kapoia 0)
						katallilithesi=prwtithesi;
						dead=0;
						for(l=0;l<arithmosleksewn;l++){//elegxoyme an h leksi yparxei sto deadlist
							if(top->deadlist[l][0]=='0'){//an den yparxoyn alles lekseis sto deadlist
										//(dilade h leksi den yparxei sto deadlist tote break
								break;
							}
							for(i=0;i<mikosleksis;i++){//gia ola ta grammata
								if(top->deadlist[l][i]==pinalex[j][i]){//an brethike koino ayksisi
									dead++;
								}
							}
							if((dead==mikosleksis)&&(top->deadlist[l][i]=='0')){//an ola ta grammata 
											//einai koina break
								elegxosdead=1;
								break;
							}
							dead=0;
						}
						if(elegxosdead==1){
							elegxosdead=0;
							continue;
						}
						katallilithesi=prwtithesi;
						for(i=0;i<mikosleksis;i++){//gia ola ta grammata
							setdeadlistword(top,pinalex[j][i],i);//h leksi mpainei sto deadlist
							if((kathorismos%2)!=0){
								stayrolekso[katallilithesi][metritis]=pinalex[j][i];//kai mpainei kai
								//sto stayrolekso
							}
							else{
								stayrolekso[metritis][katallilithesi]=pinalex[j][i];
							}
							
							katallilithesi++;//ayksanetai h katallilithesi gia n mpoyme sth katallili 
									//thesi toy pinaka toy stayroleksoy
								
						}
						auksisimetrdeadlist(top,arithmosleksewn);//ayksanetai o metr deadlist wste
								//h epomenh leksi na mpei sto pinaka deadlist sthn epomenh thesh  
						break;
					}


				}
				katallili=0;
				if(j==(arithmosleksewn-1)){//an de brethike swsth leksi (diabasame oles tis lekseis)
					top=back(arithmosleksewn,mikileksikoy,top,pinalex,stayrolekso);//kane opisthodromisi
					if(top==NULL){//an epestrepse NULL shmainei oti to stayrolekso den exei lysh
						return 0;
					}
					top=firstsetstack(top,arithmosleksewn);//meta apo thn epistrofh ths opisthodromisis 
									//ksanaftiaxnoyme th stoiba poy diagrapsame me ta idia data
					if((kathorismos%2)!=0){//an eimaste se sthlh
						setinfosgrst(top,metritis,1);
					}
					else{//an eimaste se grammh
						setinfosgrst(top,metritis,0);
					}
					setprwththesh(top,prwtithesi);//kaloyntai oles oi katalliles synarthseis gia dhmioyrgia stack
					dhmiourgiapinakasyntetagmenwn(top,mikosleksis);
					katallilithesi=prwtithesi;
					for(k=0;k<mikosleksis;k++){//ksanampainoyn oi syntetagmenes sto pinaka syntetagmenwn
						if((kathorismos%2)!=0){
							if(stayrolekso[katallilithesi][metritis]!='0'){
								beforestep(top,katallilithesi);
							}
						}
						else{
							if(stayrolekso[metritis][katallilithesi]!='0'){
								beforestep(top,katallilithesi);
							}
						}
						katallilithesi++;
					}
					j=-1;//to j ginetai -1 kathws sto telos tha ayksithei kai tha ginei 0 opote tha ksanarxisei 
															//to psaksimo
					continue;
				}
			
			}
			katallili=0;//ginontai mhdenismoi gia tis epomenes epanalipseis
			mikosleksis=0;
			if(elegxos==1){
				break;
			}
			
		}
		kathorismos++;//an teliwse mia grammh h mia sthlh ginetai ayksisi
		if((kathorismos%2)==0){//an o kathorismos einai artios shmainei oti diabastike mia grammh kai mia sthlh opote 
					//ayksanetai o metritis
			metritis++;
		}
		katallilithesi=1;
		elegxos=0;
	}
	if(draw==0){//an de theloyme parastatiko tropo 
		for(i=1;i<=mhkos;i++){//gia oles tis grammes ektypwnontai oi lekseis
			flag=1;
			for(j=1;j<=mhkos;j++){
				if(stayrolekso[i][j]!='#'){//an de synanthsame # kai de ftasame sto telos ths gram
					printf("%c",stayrolekso[i][j]);
					flag=0;
				}
				if((j!=mhkos)&&(stayrolekso[i][j]=='#')&&(flag==0)){
					flag=1;
					printf("\n");
				}
			}
			printf("\n");
		}
		for(i=1;i<=mhkos;i++){//gia oles tis sthles ektypwnontai oi lekseis
			flag=1;
			for(j=1;j<=mhkos;j++){
				if(stayrolekso[j][i]!='#'){
					printf("%c",stayrolekso[j][i]);
					flag=0;
				}
				if((j!=mhkos)&&(stayrolekso[j][i]=='#')&&(flag==0)){
					flag=1;
					printf("\n");
				}
			}
			printf("\n");
		}
	}
	else{//an epilexthike parastatikos tropos
		for(i=1;i<=mhkos;i++){//gia oles tis grammes
			for(j=1;j<=mhkos;j++){//gia oles tis sthles
				if(stayrolekso[i][j]=='#'){//an synanthsame #
					printf("###");
				}
				else{//alliws apla ektypwsh toy grammatos
					printf(" %c ",stayrolekso[i][j]);
				}
			}
			printf("\n");
		}
	}
	return 0;

}

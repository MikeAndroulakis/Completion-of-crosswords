#include <stdio.h>

struct node{
	int orikathe;//an einai mhden einai grammh an einai 1 einai sthlh
	int arithmosgrst;//o arithmos ths grammhs h ths sthlhs
	int *syntetagmenes;//pinakas poy fylassontai oi syntetagmenes twn grammatwn poy ipirxan apo prin
	char **deadlist;//pinaka gia tis lekseis poy idi exoyn mpei kai de ksanampainoyn
	int prwththesh; //apo poia syntetagmenh arxizei h leksh sto pinaka toy stayroleksou
	struct node *beforestack;//deiktis poy fyllaei th dieythinsi toy proigoymnoy stack
	int mhkosleksis;
	int metrdeadlist;//metritis poy mas deixnei se poia thesi toy pinaka deadlist tha baloyme th leksi
	int metrsyntet;//metritis gia tis syntetagmenes
};
struct node *firstsetstack(struct node *temptop,int arithmosleksewn);

void setinfosgrst(struct node *top,int arithmos,int grst);

void setprwththesh(struct node *top,int prwththesh);

void dhmiourgiapinakasyntetagmenwn(struct node *top,int mhkoslekshs);

void beforestep(struct node *top,int thesixaraktira);

void setdeadlistword(struct node *top,char character,int metritisgrammatwn);

void auksisimetrdeadlist(struct node *top,int arithmosleksewn);

struct node *back(int arithmosleksewn,int *mikileksikoy,struct node *top,char **pinalex , char **staurolex);

struct node *deletestructs(struct node *top,int arithmosleksewn);

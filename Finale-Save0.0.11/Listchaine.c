
item * allouer(){
return (item *)malloc(sizeof (item));
}
void inverser_liste2(item **p){

item  *t=*p,*k=NULL,*p_suivant;

while(t!=NULL)
{
    p_suivant=t->next;
    t->next=k;
    k=t;
    t=p_suivant;
}

*p=k;
}


// question 3  tete sera modifier => passage par adresse de tete
void inserer_tete(item ** tete,int x,int y,int med){  // supporte une tete non initialisé
item * nv=allouer();
nv->x=x;
nv->color=BY_DEFAULT_COLOR;
nv->y=y;
nv->is_a_medoid=0; // c pas un medoid
if(*tete!=NULL){
nv->next=*tete;
*tete=nv;
}else{
*tete=nv;
(*tete)->next=NULL;
}
}

void afficher(item * tete)
{
    printf(" ****************************:\n");
while(tete!=NULL){
printf(" x=%d y=%d is_medoid=%d \n",tete->x,tete->y,tete->is_a_medoid);
tete=tete->next;

}
printf(" ****************************:\n");
}

//question 4
void inserer_fin(item * tete,int x,int y,int is_a_medoid){


while(tete->next!=NULL){tete=tete->next;}
item * nv=allouer();
nv->x=x;
nv->y=y;
nv->color=BY_DEFAULT_COLOR;   // Attribuer une couleur Par default
nv->is_a_medoid=0; // c pas un medoid
nv->next=NULL;
tete->next=nv;
}


item * vider_liste(item * t){
item *save=t;
while(save!=NULL){
save=(t)->next;
free(t);
t=save;
}
return NULL;
}


//question 5   {liste vide == liste avec une tete NULL}
int test_vide(item *tete){
if(tete==NULL){
 //printf("La liste est vide\n");
return 0;
}else{
  //  printf("La liste est Non vide\n");
return 1;
}
}

// question 6  taille de la liste
int calcule_taille(item *tete){
int size=0;

if (test_vide(tete)==1){

while(tete!=NULL){
tete=tete->next;
size++;
}
}
return size;
}



#include <math.h>
#include <conio.h>
#include <process.h>
//void Rebuil_my_points(HWND hwnd);



cluster * Init_K_Medoid(){

int size=calcule_taille(List_tt_point);

if(k_med<=size){
int rnd; // rnd number
cluster * cls=(cluster * )malloc(k_med*(sizeof(cluster))); // Les tetes des clusters
item *p;

for(int i=0;i<k_med;i++){  // Compteur des K-Medoid

p=List_tt_point; // Save the main List
rnd=rand();
rnd=((rnd*rand())%size); // Indice Aléatoire dans [0 , Size-1]
rnd++; // pour indice [1,Size]
while(rnd!=1){  // positionner P sur l'élément  d'indice aléatroire rnd
p=p->next;rnd--;
}
 // Enregistrer l'element comme Cluster
 // SI c'est pas déja un Cluster
 if(p->is_a_medoid==0){
 (cls+i)->pts=p;     // Enregistrer le point medoid
  p->is_a_medoid=1; // fixer l element comme un cluster
 rnd=(rand()%30000)*(i*i+3)+(rand()%999000);   // Générer Couleur Spectre RGB
    printf("Color = %d\n",rnd);
    p->color=rnd; // Attribuer la couleur au point
 (cls+i)->next=NULL; // Initialiser Next a Null

 }else{
 printf("\nRedondance Cluster\n");
 i--; // Ressayer une autre fois pour le meme medoid
 }


}
return cls; // Return les nouveaux clusters
}else{
printf("Le nombre de medoid >au nombre de points\n");
return NULL;
}
 }

float  Distance_Point_Medoid(item * medoid , item * not_medoid ){
float dist=sqrt(  (    (medoid->x - not_medoid->x)*(medoid->x - not_medoid->x)/*(Xi-Xj)²*/ )   +
                (  (medoid->y - not_medoid->y)*(medoid->y - not_medoid->y)/*(Yi-Yj)²*/ )   );
return(dist);
}

cluster *ye;
void Ajout_pts_cluster_fin(cluster * t , item *p){  // Ajout à la findu cluster

while(t->next)t=t->next;    // position t sur le tout derneir element

ye=(cluster *)malloc(sizeof(cluster));
ye->next=NULL;  // Delimiter la chaine
ye->pts=p; // Initialiser le champ address point
t->next=ye;  // Assurer l'enchainement
}


void Set_same_color(cluster * t){ // Parcours totale du tableau des clusters

for(int j=0;j<k_med;j++){  // parcours  des clusters

ye=(t+j)->next; // point sauivant dans le cluster(le non medoid)

while(ye){
ye->pts->color=(t+j)->pts->color; // Attribuer la meme couleur au meme point d'un medoid
ye=ye->next;
}

}


}


void  Detruire_Cluster(cluster * t){

cluster *p,*r;

for(int j=0;j<k_med;j++){
p=(t+j)->next;

while(p){
r=p->next;
free(p);
p=r;
}

}




free(t); // Liberer le tableau

}



 void Affecter(cluster * CLS, item * tmp_medoid ){ // affectation Temporaire + Affectation initiale
item * p=List_tt_point; // List de tout les point
int i,indice_min,k;
float dist_min;

if(tmp_medoid==NULL){  // Affectation toute initiale


while(p){  // parcours des points

if(p->is_a_medoid==0){ // Affectation si point non_medoid
      i=0;
 dist_min=Distance_Point_Medoid((CLS+i)->pts,p); // Min = Distance entre 1 er medoid dans les clusters et le point suivant
 indice_min=0; // Supposons que c le 1 er medoid qui va affecter ce point
   for(i=1;i<k_med;i++){ // parcours des clusters
if(Distance_Point_Medoid((CLS+i)->pts,p)<dist_min){  // Si le point est  plus proche au medoid (CLS+i)->pts
dist_min=Distance_Point_Medoid((CLS+i)->pts,p);
indice_min=i; // Indice du cluster qui minimise la distance avec le point
}
                       }
              /* Ajout de ce point dans le  cluster d'indice min  */
Ajout_pts_cluster_fin(CLS+indice_min,p);
}
p=p->next; // point suivant
}
Set_same_color(CLS); // Fixer les memes couleurs au meme point du medoid
// Faire appel au dessinateur de Toile
}else{   // Affectation temporaire

while(p){  // parcours des points

if(p->is_a_medoid==0 || p==tmp_medoid){ // Affectation si point non_medoid ou meme si point est l'ancien medoid

  i=0;

 dist_min=Distance_Point_Medoid((CLS+i)->pts,p); // Min = Distance entre 1 er medoid dans les clusters et le point suivant
 indice_min=0; // Supposons que c le 1 er medoid qui va affecter ce point

   for(i=1;i<k_med;i++){ // parcours des clusters

if(Distance_Point_Medoid((CLS+i)->pts,p)<dist_min){  // Si le point est  plus proche au medoid (CLS+i)->pts
dist_min=Distance_Point_Medoid((CLS+i)->pts,p);
indice_min=i;
}
                       }
              /* Ajout de ce point dans le  cluster d'indice i  */
Ajout_pts_cluster_fin(CLS+indice_min,p);
}
p=p->next; // point suivant
}

// Faire appel au dessinateur de toile Si on gagne du coup dans ces foutu Nvs_Clusters ==> See K_medoid Func
 }




 }


double Calculer_Score(cluster * t){  // Calcule le Score des Clusters

double somme=0,dist=0;
cluster *medoid,*not_medoid;

for(int i=0;i<k_med;i++){

 medoid= (t+i); // Premier element ==  medoid
 not_medoid=medoid->next; // Apartir du deuxième c'est les non medoids

  while(   not_medoid!=NULL    ){

     dist=Distance_Point_Medoid(medoid->pts , not_medoid->pts ); // claculer la distance entre le medoid et le point
    //  dist est positive  ==> pas la paine de calculer l'absolue ou carre
     somme=somme+dist;

     not_medoid=not_medoid->next;

        }

}

return somme;
}


int Nb_item_by_Cluster(cluster * Ci /*  Ghir Cluster 1 Machi Tableau Kamal*/  ){ // Medoid Included
int nb=0;

while(Ci){
nb++;
Ci=Ci->next;
}

return nb;
}

void Dessiner_Toile(cluster * cls,HWND hwnd){

int i;
cluster *p ;

   hdc = GetDC(hwnd);
for(i=0;i<k_med;i++){

p=(cls+i);

if(Nb_item_by_Cluster(p)>1){




            //  SetBkMode(hdc, TRANSPARENT);
              hp2px = CreatePen(PS_SOLID, 1, p->pts->color);   // Configurer les bordures
              hpOld =(HPEN) SelectObject(hdc,hp2px);      // appliquer les bordures au pinceau
               hbRed = CreateSolidBrush(p->pts->color);       // configurer le bk
              hbrOld =(HBRUSH) SelectObject(hdc,hbRed);   // appliquer la texture au pinceau


            //  TextOut(hdc, 199, 346, st , lstrlen(st));
             // Position du Medoid
             p=p->next;
           while(p){
                MoveToEx(hdc, (cls+i)->pts->x+PADDING, (cls+i)->pts->y+PADDING, NULL);
                LineTo(hdc, p->pts->x+PADDING, p->pts->y+PADDING);
                p=p->next;
           }


DeleteObject (hp2px) ;
DeleteObject (hpOld) ;
DeleteObject (hbRed) ;
}


}
 ReleaseDC(hwnd, hdc);

}

VOID Thread3 (PVOID pvoid)
{
 Detruire_Cluster((cluster *)pvoid);
//InvalidateRgn(handle_Fenetre,NULL,TRUE);
//UpdateWindow(handle_Fenetre);

}


cluster * Build_News_Clusters(cluster * ancien,item * nv_medoid,int indice_cluster){  // Doit Retourner un nouveau Cluster Temporaire à base du premier cluster

cluster * nv=(cluster * )malloc(k_med*(sizeof(cluster))); // creation Nouveau TMP Clusters

 // Copier Coller tout Sauf Le cluster courant d'indice indice_cluster
for(int j=0;j<k_med;j++){

if(j==indice_cluster){   // C'est le cluster à changer
(nv+j)->pts=nv_medoid;  // Le nouveau medoid tmp(is medoid ==0 )
}else{
(nv+j)->pts=(ancien+j)->pts; // Affecter
}
(nv+j)->next=NULL;
}
            /* nv : Nouveau Clusters contenant Juste les medoids                             */

/*    Début réaffectation des points  : Attention cas ou le nouveau medoid est temporaire (is_medoid==0)
  Attention dans le parcours des points ==> comparrer les address par nv_medoid */

Affecter(nv ,(ancien+indice_cluster)->pts ); //Affectation Temporaire; Att (ancien+indice_cluster)->pts == Medoid pourtant doit etre affecter à un nouveau cluster

return nv ;
}

void K_Medoid(HWND hwnd){

double Ei=0,Ef=0;
int i,j,k;
cluster *Tmp;
cluster *p;


score_final=0;
iter=0; // Initialiser le compteur

 Affecter(MDS,NULL); // Affectation Initial
PostMessage(hwnd, WM_PAINT,0,0);

score_initiale=Calculer_Score(MDS);

      for(i=0;i<k_med;i++){  // parcours des clusters
        Ei=Calculer_Score(MDS); // Score Global
       // Size_cluster=Nb_item_by_Cluster(MDS+i); // le Medoid est aussi compté  : Nombre/Cluster
    printf("\nScore Totale = %f\n",Ei);
        // Choix element Nn Medoid => Debut à partir du deuxieme Element dans la structure cluster
    p=(MDS+i)->next;  // Parcours des elements à partir du 2ème elements
  while(p){     // Remplcement des point non medoid par les point medoid c a d Rebuild new Tmps clusters


        Tmp= Build_News_Clusters(MDS,p->pts ,i); // Doit Returner les nouveaux cluster Temporaire
        Ef=Calculer_Score(Tmp); // Calculer le nouveaux Score Globale
 //printf("\n Cout Finale = %0.3f \n",Ef);
                     if(Ei>Ef){   // Si on va gagner en distance ==> Garder les nouveaux Cluster

                      (MDS+i)->pts->is_a_medoid=0;
                      (Tmp+i)->pts->is_a_medoid=1;
             _beginthread (Thread3, 0, MDS) ;
                       // Libérer les ressources
                        MDS=Tmp;  // Garder les nouveaux clusters
                      printf("Changemenet\n");
                      iter++;
                      score_final=Ef;// Le nouveau score
                   Set_same_color(MDS);
 Refresh_counter(hwnd);

                       //Supprimer(0);

//if(iter%2==0){  // Fréquence de Rafraichissement

 i=0;
//}
                     // PostMessage(hwnd, WM_PAINT,0,0);
                     // pour reparourir les cluster depuis le début
                        break;   // Sortir boucle des elements


                    }else{
                        Detruire_Cluster(Tmp); // Libérer les ressources
                         }
                             p=p->next;
                                }
if(iter%2==0){
  Supprimer(0);
                           Rebuil_my_points(hwnd); // Recolorer Les Points Medoids
                           Dessiner_Toile(MDS,hwnd);
}


                          }  // Fin parcours des cluster
printf("\n**************Fin***************\n");

  Supprimer(0);
                           Rebuil_my_points(hwnd); // Recolorer Les Points Medoids
                           Dessiner_Toile(MDS,hwnd);
}


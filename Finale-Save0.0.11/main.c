#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "vars&const.h"
#include "Functions.c"
#include "Listchaine.c"
#include "K-Medoids.c"
#include <time.h>


VOID Thread (PVOID pvoid)
{

  K_Medoid(handle_Fenetre);



                                        Supprimer(0);        // Supprimer le client Area
                                        Rebuil_my_points(handle_Fenetre); // Recolorer Les Points Medoids
                           Dessiner_Toile(MDS,handle_Fenetre);
}


void Generer_aleatoir(HWND hwnd){

int i=0,x,y;
couleur=BY_DEFAULT_COLOR;

for(i=0;i<Nb_elm;i++){

 x=rand()%700;
 y=rand()%320;
                          //   Buil_Point(hwnd,x,y);
                                if(List_tt_point==NULL){ // si la liste est encore vide
                                    inserer_tete(&List_tt_point,x,y,0);
                                }else{
                                    inserer_fin(List_tt_point,x,y,0);
                                     }

}
Rebuil_my_points(hwnd);
}






int WINAPI WinMain (HINSTANCE hThisInstance,HINSTANCE hPrevInstance,LPSTR lpszArgument,int nCmdShow){
// le faire une seule fois

Buil_Frame(hThisInstance); //Créer ma Fenetre
ShowWindow (handle_Fenetre, nCmdShow); // Afficher ma fenetre
Recv_Trans_Message(); // Traitement des messages du S.E

    return 0;
}


/*  Cette fonction est appellée par la fonction DispatchMessage()-Recv_Trans-Message  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {


        case WM_CREATE :


                     Build_Menu(hwnd);

                      return 0 ;

        case WM_PAINT :
                        printf("\n***************REPAINT************\n");
                            // InvalidateRect (hwnd, NULL, TRUE) ;
                         Refresh_counter(hwnd);
                         Build_Help(hwnd);
                       //  hdc = GetDC(handle_Fenetre);
                        // Supprimer(0);        // Supprimer le client Area
                        // Rebuil_my_points(hwnd); // Recolorer Les Points Medoids
                        // Dessiner_Toile(MDS,hwnd);
                         return 0;

         case WM_COMMAND:   // click sur les  button


                 switch (wParam)
                      {


                              case BTN_EXIT :
                                     PostMessage(hwnd, WM_CLOSE,0,0);  // envoyer le message de fermeture dans la queue des messages
                                         break ;

                              case BTN_RENEW :
                                      printf("\nRafraichissement\n");

                                      Supprimer(0);
                                     Rebuil_my_points(hwnd); // Recolorer Les Points Medoids
                                     Dessiner_Toile(MDS,hwnd);
                                          break;


                           case BTN_RANDOM :

                                      char tmp[15];
                                      GetWindowTextA(edit_gen,tmp,13);
                                      Nb_elm=atoi(tmp);

                                     Generer_aleatoir(hwnd);
                                       printf("\Random : %d \n",Nb_elm);
                                        Refresh_counter(hwnd);
                                     // Supprimer(0);
                                      //Rebuil_my_points(hwnd);
                                          break;


                              case BTN_PLAY :
                                     if(initialised==false){
                                         set_k();
                                         MDS=Init_K_Medoid(); // Choix Medoid Aléatoirement + Change color of medoid
                                         initialised=true;     // flag d'initialisation
                                       //    Affecter(MDS,NULL);
                                        _beginthread (Thread, 0, NULL) ;

                                        //  Rebuil_my_points(hwnd); // Recolorer Les Points Medoids

                                     }else{
                                     printf("\n***Deja Initialiser***\n");
                                     }

                                         afficher(List_tt_point);
                                              break;

                              case BTN_RESET :
                              printf("Rset");
                               couleur=BY_DEFAULT_COLOR;
                                            reset=true;
                                            initialised=false;
                                             List_tt_point=vider_liste(List_tt_point); // Libérer les ressources
                                            Supprimer(0);  // affacer les points de l'ecran

                                             Refresh_counter(hwnd);
                                            Detruire_Cluster(MDS);
                                            MDS=NULL;


                                            //  PostMessage(hwnd, WM_CREATE,0,0);
                                             // PostMessage(hwnd, WM_PAINT,0,0);
                                             break ;

                              default :

                                              break;

                                        }  // FIN SWITCH BTN TYPE

                        return 0;

            case WM_LBUTTONDOWN:   // Click Souris sur la zone de travail



                         x=LOWORD(lParam);
                         y=HIWORD(lParam);



                         if(y<330-CRCL_WIDTH && x<700-CRCL_WIDTH){   // si les coordonner  sont  dans la zone menuy
                            hdc = GetDC(handle_Fenetre);

                             hp2px = CreatePen(PS_SOLID, 1, 0x00ABABAB);   // Configurer les bordures
                             hpOld =(HPEN) SelectObject(hdc,hp2px);      // appliquer les bordures au pinceau

                             hbRed = CreateSolidBrush(BY_DEFAULT_COLOR);       // configurer le bk
                             hbrOld =(HBRUSH) SelectObject(hdc,hbRed);   // appliquer la texture au pinceau

                              Buil_Point(hwnd,x,y);


                               DeleteObject (hp2px) ;
                               DeleteObject (hpOld) ;
                               DeleteObject (hbRed) ;


                                if(List_tt_point==NULL){ // si la liste est encore vide
                                    inserer_tete(&List_tt_point,x,y,0);
                                }else{
                                    inserer_fin(List_tt_point,x,y,0);
                                     }
                           ReleaseDC(hwnd,hdc);
                             afficher(List_tt_point);
   Refresh_counter(hwnd);

}


                       break;   // FIN SWITCH EVENTMS


        default:                      /* for messages that we don't deal with */
              return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

/*

*/

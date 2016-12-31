
int calcule_taille(item *tete);


void Buil_Frame(HINSTANCE hThisInstance){

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS|CS_GLOBALCLASS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDI_EXCLAMATION);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_INACTIVEBORDER;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        exit (-1);
handle_Fenetre = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "K Medoide Project",       /* Title Text */
           WS_EX_TRANSPARENT, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           FRM_WIDTH,                 /* The programs width */
           FRM_HEIGHT,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );
}

void Recv_Trans_Message(){
   /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0)){
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }
}

void Build_Menu(HWND hwnd){

// Create the owner−draw pushbuttons
button[0] = CreateWindow (TEXT ("button"), TEXT ("Classifier"),
WS_CHILD | WS_VISIBLE,
10, 260 -100, 140, 30,
hwnd, (HMENU) BTN_PLAY, Handle_instance_prog, NULL) ;

button[0] = CreateWindow (TEXT ("button"), TEXT ("Arreter"),
WS_CHILD | WS_VISIBLE,
10, 200 -100, 140, 30,
hwnd, (HMENU) BTN_EXIT, Handle_instance_prog, NULL) ;

button[0] = CreateWindow (TEXT ("button"), TEXT ("Reinitialiser"),
WS_CHILD | WS_VISIBLE,
10, 300 -100, 140, 30,
hwnd, (HMENU) BTN_RESET, Handle_instance_prog, NULL) ;

button[3] = CreateWindow (TEXT ("button"), TEXT ("Rafraichir"),
WS_CHILD | WS_VISIBLE,
10, 320+10 -100, 140, 30,
hwnd, (HMENU) BTN_RENEW, Handle_instance_prog, NULL) ;

button[4] = CreateWindow (TEXT ("button"), TEXT ("Generer"),
WS_CHILD | WS_VISIBLE,
10, 360+20 -100, 140, 30,
hwnd, (HMENU) BTN_RANDOM, Handle_instance_prog, NULL) ;


edit_text =CreateWindow("edit", "5",
              WS_CHILD | WS_VISIBLE ,
                                          10, 400-50, 60, 20, hwnd, (HMENU) EDIT_K, Handle_instance_prog, NULL);
edit_gen=  CreateWindow("edit", "180000",
              WS_CHILD | WS_VISIBLE ,
                                          10, 430-100, 60, 20, hwnd, (HMENU) EDIT_GENERATOR, Handle_instance_prog, NULL);

}

void Build_Help(HWND hwnd){

 PAINTSTRUCT ps;

              HDC hdc = BeginPaint(handle_Fenetre, &ps);
              SetBkMode(hdc, TRANSPARENT);
              TextOut(hdc, 199, 346, st , lstrlen(st));  // Specifier Nb Medoid
               TextOut(hdc, 10, 346, st2 , lstrlen(st2)); // Nb Generer

              MoveToEx(hdc, 0, 400-70, NULL);
              LineTo(hdc, 700, 330);

              EndPaint(hwnd, &ps);
}

void Buil_Point(HWND hwnd,int x,int y){
// TRY SET ONE HDC
         //    hdc = GetDC(handle_Fenetre); // obtenir le contexte du périphérique



              Ellipse(hdc, x, y, x+CRCL_WIDTH, y+CRCL_WIDTH); // Dessiner un cercle de rayon 15
             // ReleaseDC(hwnd, hdc); // libérer le contexte
}

 void set_k(){
   char tmp[10];
GetWindowTextA(edit_text,tmp,5);

      k_med=atoi(tmp);
      printf("%d\n",k_med);
 }

void Supprimer(int i){
   hdc = GetDC(handle_Fenetre); // obtenir le contexte du périphérique
  hp2px = CreatePen(PS_SOLID, 0, 0x00FFFFFF);   // Configurer les bordures
              hpOld =(HPEN) SelectObject(hdc,hp2px);

              hbRed = CreateSolidBrush(0x00FFFFFF);       // configurer le bk
              hbrOld =(HBRUSH) SelectObject(hdc,hbRed);   // appliquer la texture au pinceau

         if(i==0) // Supprimer Just le client Area
         {

             Rectangle(hdc, 0, 0, 700, 330);
         }else{
         Rectangle(hdc, 0, 0, 700, 450); // Supprimer toute l'interface
         }


             ReleaseDC(handle_Fenetre, hdc); // libérer le contexte
}

 item *List_tt_point=NULL; // liste de tout les points


void Rebuil_my_points(HWND hwnd){
printf("\nRebuild All Points\n");
if(List_tt_point){  // si la liste contient des points faut les redissiner
item * p=List_tt_point;
 hdc = GetDC(handle_Fenetre);
while(p!=NULL){
//couleur=p->color; // prendre en considartion  la couleur du medoid

 hp2px = CreatePen(PS_SOLID, 0, p->color);   // Configurer les bordures
              hpOld =(HPEN) SelectObject(hdc,hp2px);      // appliquer les bordures au pinceau

              hbRed = CreateSolidBrush(p->color);       // configurer le bk
              hbrOld =(HBRUSH) SelectObject(hdc,hbRed);   // appliquer la texture au pinceau

Buil_Point(hwnd,p->x,p->y);
p=p->next;

DeleteObject (hp2px) ;
DeleteObject (hpOld) ;
DeleteObject (hbRed) ;
}

}
ReleaseDC(hwnd,hdc);
}

cluster * MDS=NULL;
int PAINT=0;


int Get_number_of_a_number(int r){  // Retourne le nombre de chiffre d'un nombre
int f=1;
r=r/(int)10;
while(r!=0){
r=r/(int)10;
f++;
}
return f;
}

void Refresh_counter(HWND hwnd){
 hdc = GetDC(handle_Fenetre);

     TextOut(hdc, 330+10+20+10, 346, MSG_NB_ELEMENT , lstrlen(MSG_NB_ELEMENT)); // Message : Nombre Actual d'élément
     TextOut(hdc, 330+20+8+20+10+20+40, 346, it , lstrlen(it)); // Iteration

     TextOut(hdc, 330+20+8+20+10+20+40+30+30+5+15, 330+1, scor_init , lstrlen(scor_init)); // MSG Score Initiale

     TextOut(hdc, 330+20+8+20+10+20+40+30+30+5+15, 360, scor_finale , lstrlen(scor_finale)); // MSG Score Finale

              int nbr_apres_virgule=0;
              int signe=1;// passage => Longeur de la chaine  && retour ==> Indice du Signe
              Nb_elm=calcule_taille(List_tt_point);

 //  330+20+8+20+10+20+40


if(Nb_elm==0){  // Reset


              TextOut(hdc, 330+20+8+20+10, 346, TEXT("0      ") , lstrlen(TEXT("0      ")));  // Ecraser le Nb element
                   nbr_apres_virgule=0;
                   signe=1;
                   iter=0;
   // NB_ELEMENT= ecvt(iter, signe,&nbr_apres_virgule,&signe);  // Conversion Integer => chaine
    TextOut(hdc, 330+20+8+20+10+20+40+30+30+5, 346, TEXT("0      ") , lstrlen(TEXT("0      ")));  // Ecraser l'ietrator
         score_final=0;
         score_initiale=0;
           TextOut(hdc, 330+20+8+20+10+20+40+30+30+5+40+40, 330+1, TEXT("0          ") , lstrlen(TEXT("0          ")));  // Ecraser le scores

                TextOut(hdc, 330+20+8+20+10+20+40+30+30+5+40+40, 360, TEXT("0          ") , lstrlen(TEXT("0          ")));  // Ecraser le scores

}else{ // Refresh

/*               if(Nb_elm>9&& Nb_elm<100)signe=2;
 *               if(Nb_elm<=999 && Nb_elm>=100)signe=3;
 *                if(  Nb_elm<=9999 && Nb_elm>=1000)signe=4;
 */
    signe=Get_number_of_a_number(Nb_elm);
              NB_ELEMENT= ecvt(Nb_elm, signe,&nbr_apres_virgule,&signe);  // Conversion Integer => chaine

             // printf("Mon Nb : %s \n",NB_ELEMENT);
              TextOut(hdc, 330+20+8+20+10, 346, NB_ELEMENT , lstrlen(NB_ELEMENT));  // Nombre d'élément

              signe=Get_number_of_a_number(iter);
              NB_ELEMENT= ecvt(iter, signe,&nbr_apres_virgule,&signe);  // Conversion Integer => chaine
              TextOut(hdc, 330+20+8+20+10+20+40+30+30+5, 346, NB_ELEMENT , lstrlen(NB_ELEMENT));


              signe=Get_number_of_a_number(score_initiale);
              NB_ELEMENT= ecvt(score_initiale, signe,&nbr_apres_virgule,&signe);  // Conversion Integer => chaine

               TextOut(hdc, 330+20+8+20+10+20+40+30+30+5+40+40, 330+1, NB_ELEMENT, lstrlen(NB_ELEMENT));  // Ecraser le scores

              signe=Get_number_of_a_number(score_final);
              NB_ELEMENT= ecvt(score_final, signe,&nbr_apres_virgule,&signe);  // Conversion Integer => chaine

                TextOut(hdc, 330+20+8+20+10+20+40+30+30+5+40+40, 360, NB_ELEMENT , lstrlen(NB_ELEMENT));  // Ecraser le scores

}

ReleaseDC(hwnd,hdc);
}









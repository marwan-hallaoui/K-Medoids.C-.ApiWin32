#define FRM_WIDTH  700                /* Mes Constantes */
#define FRM_HEIGHT  450
#define CRCL_WIDTH 8
#define BTN_EXIT 0
#define BTN_RESET 2
#define BTN_RENEW 3
#define BTN_PLAY 1
#define BTN_RANDOM 4
#define EDIT_K 3
#define EDIT_GENERATOR 4
#define BY_DEFAULT_COLOR  0x00000000
#define PADDING 3

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
void Buil_Frame(HINSTANCE hThisInstance);
void Recv_Trans_Message();



char * st2 ="Nb. Generer :" ;
char st[]="Nb Medoids :"; //   Message Label
char szClassName[ ] = "K-Medoids Project"; // Message Frame
char * MSG_NB_ELEMENT="N=";
char * NB_ELEMENT;   // Pointeur pour chaine Contenant le nombre
char * it="Iteration :";
char * scor_init="Scor/Init:";
char * scor_finale="Scor/fin:";


HWND handle_Fenetre,button[5],edit_text,edit_gen;               /* This is the handle for our window */
MSG messages;            /* Pour stocker les messages de l'application*/
WNDCLASSEX wincl;        /* Strcuture de données d'une Frame */
HINSTANCE Handle_instance_prog; // Sauvegarde du Handle d'instance
bool reset;
int x,y,couleur; // position mouse
int k_med,Nb_elm=0; // le nombre de medoids
HBRUSH hbRed, hbrOld; // Zwa9
HPEN hp2px, hpOld;// Zwa9
HDC hdc; // Handle du contexte du périphérique encours
bool initialised=false;
/*Structure de données d'un point */

double score_final=0,score_initiale=0;;

int iter=0;

struct item{
int x,y; // coordonées
item *next;
int is_a_medoid;  // Medoid or not
int color; // coleur spécifique au point
};

/*Structure de données d'un cluster*/
struct cluster{

item *pts;  // les points du cluster sans le medoid
cluster *next;
};





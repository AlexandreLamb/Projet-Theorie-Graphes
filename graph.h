#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

/**************************************************************
    Ici sont propos�es 3 classes fondamentales
            Vertex (=Sommet)
            Edge (=Ar�te ou Arc)
            Graph (=Graphe)

    Les ar�tes et les sommets et le graphe qu'ils constituent
    "travaillent" �troitement ensemble : pour cette raison les
    Vertex et Edge se d�clarent amis (friend) de Graph pour que
    ce dernier puisse librement acc�der aux membres (y compris
    protected ou private) de Vertex et Edge.

    Ces Classes peuvent �tres compl�t�es. Il est �galement possible
    de les d�river mais il est malheureusement assez difficile
    de d�river le "triplet" des 3 classes en maintenant des relations
    coh�rentes ( rechercher "c++ class covariance" et "c++ parallel inheritance"
    pour commencer .. ). Il est donc sans doute pr�f�rable, si possible,
    de "customiser" ces classes de base directement, sans h�ritage.

    Le mod�le propos� permet de repr�senter un graphe orient� �ventuellement
    pond�r�, les arcs portent une ou des informations suppl�mentaire(s).
    Les relations/navigations Arcs -> Sommets et Sommets -> Arcs se font
    dans les 2 sens et utilisent des INDICES et NON PAS DES ADRESSES (pointeurs)
    de telle sorte que la topologie du graphe puisse �tre assez facilement
    lue et �crite en fichier, et b�n�ficie d'une bonne lisibilit� en cas de bugs...

    Chaque arc poss�de 2 attributs principaux (en plus de son �ventuelle pond�ration)
        -> m_from (indice du sommet de d�part de l'arc )
        -> m_to (indice du sommet d'arriv�e de l'arc )

    Chaque sommet poss�de 2 liste d'arcs (en plus de ses attributs "internes", marquages...)
        -> m_in (liste des indices des arcs arrivant au sommet : acc�s aux pr�d�cesseurs)
        -> m_out (liste des indices des arcs partant du sommet : acc�s aux successeurs)

    Cependant le probl�me des indices (par rapport aux pointeurs) et qu'en cas
    de destruction d'une entit� (un arc et/ou un sommet sont enlev�s du graphe) alors :

    - Soit il faut reprendre toute la num�rotation pour "boucher le trou"
      (par exemple on a supprim� le sommet n�4, le sommet n�5 devient le 4, 6 devient 5 etc...)
      ce qui pose des probl�mes de stabilit� et de coh�rence, et une difficult� � r�-introduire
      le(s) m�me(s) �l�ment supprim� (au m�me indice)

    - Soit on admet que la num�rotation des sommets et arcs n'est pas contigue, c�d qu'il
      peut y avoir des "trous" : sommets 0 1 5 7 8, pas de sommets 2 ni 3 ni 4 ni 6. La num�rotation
      est stable mais on ne peut plus utiliser un simple vecteur pour ranger la liste de tous
      les arcs et tous les sommets aux indices correspondants, on peut utiliser une map
      qui associe un objet arc ou sommet � des indices arbitraires (pas forc�ment contigus)

    C'est cette 2�me approche qui est propos�e ici : dans la classe graphe vous trouverez
        -> map<int, Edge>   m_edges
        -> map<int, Vertex> m_vertices    (le pluriel de vertex est vertices)

    Il faudra �tre attentif au fait que par rapport � un simple vecteur, le parcours des �l�ments
    ne pourra PAS se faire avec un simple for (int i=0; i<m_edges.size(); ++i) ...m_edges[i]...
    et que les parcours � it�rateur ne donneront pas directement des Edge ou des Vertex
    mais des pairs, l'objet d'int�r�t se trouvant dans "second" ("first" contenant l'indice)
                for (auto &it = m_edges.begin(); it!=m_edges.end(); ++it) ...it->second...
    ou bien     for (auto &e : m_edges) ...e.second...

    Il n'est pas obligatoire d'utiliser ces classes pour le projet, vous pouvez faire les votres

    Au niveau de l'interface, on dissocie une classe interface associ�e � chaque classe fondamentale
    de telle sorte qu'il soit possible de travailler avec des graphes non repr�sent�s � l'�cran
    Imaginons par exemple qu'on doive g�n�rer 1000 permutations de graphes pour tester des
    combinaisons, on ne souhaite pas repr�senter graphiquement ces 1000 graphes, et les
    interfaces p�sent lourd en ressource, avec cette organisation on est libre de r�server ou
    pas une interface de pr�sentation associ�e aux datas (d�couplage donn�es/interface)

***********************************************************************************************/

#include <vector>
#include <map>
#include <string>
#include <memory>
#include "fstream"
#include "tools_bar.h"

#include "grman/grman.h"



/***************************************************
                    VERTEX
****************************************************/

class VertexInterface
{
    // Les (methodes des) classes amies pourront acc�der
    // directement aux attributs (y compris priv�s)
    friend class Vertex;
    friend class EdgeInterface;
    friend class Graph;
    friend class Edge;

    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de d�clarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le param�trer ( voir l'impl�mentation du constructeur dans le .cpp )

        // La boite qui contient toute l'interface d'un sommet
        grman::WidgetBox m_top_box;

        // Un slider de visualisation/modification de la valeur du sommet
        grman::WidgetVSlider m_slider_value;

        // Un label de visualisation de la valeur du sommet
        grman::WidgetText m_label_value;

        // Une image de "remplissage"
        grman::WidgetImage m_img;
        grman::WidgetImage m_img_Dead;


        // Un label indiquant l'index du sommet
        grman::WidgetText m_label_idx;

        // Une boite pour le label pr�c�dent
        grman::WidgetText m_box_label_idx;

        grman::WidgetBox m_tools_box;

        grman::WidgetButton m_button_cacher;

        grman::WidgetButton m_button_edit;

        grman::WidgetButton m_tools_button;

        grman::WidgetText m_tools_label;

        grman::WidgetText m_label_cacher;

        grman::WidgetText m_label_edit;

        grman::WidgetText m_tools_text;

        grman::WidgetText m_label_name;


    public :

        // Le constructeur met en place les �l�ments de l'interface
        // voir l'impl�mentation dans le .cpp
        VertexInterface(int idx, int x, int y, std::string pic_name="", int pic_idx=0);
};


class Vertex
{
    // Les (methodes des) classes amies pourront acc�der
    // directement aux attributs (y compris priv�s)
    friend class Graph;
    friend class VertexInterface;
    friend class Edge;
    friend class EdgeInterface;

    private :
        /// liste des indices des arcs arrivant au sommet : acc�s aux pr�d�cesseurs
        std::vector<int> m_in;
        std::vector<int> m_in2;

        /// liste des indices des arcs partant du sommet : acc�s aux successeurs
        std::vector<int> m_out;
        std::vector<int> m_out2;


        /// pourcentage de la population
        double m_value;


        /// Variable K qui nous permet de calculer la populataion a t+1
        double m_K;

        /// Varible r qui est le rythme d ecroissance
        int m_r;

        /// variable d erefrence pour le nb de la pop
        double m_val_ref;


        /// indice du sommet pour savoir ou il est dans la map
        int m_indx_V;

        /// vector des predecesseurs
        std::vector<int> m_pred;

        /// vector des successeurs
        std::vector<int> m_succ;

        std::string m_name;


        /// le POINTEUR sur l'interface associ�e, nullptr -> pas d'interface
        std::shared_ptr<VertexInterface> m_interface = nullptr;

        // Docu shared_ptr : https://msdn.microsoft.com/fr-fr/library/hh279669.aspx
        // La ligne pr�c�dente est en gros �quivalent � la ligne suivante :
        // VertexInterface * m_interface = nullptr;

        bool IsHide=false;
       ///marquage

        bool m_ismarqued=false;
        bool m_ismarqued_connexeout=false;
        bool m_ismarqued_connexein=false;
        bool m_isin_cmpconnexeout=false;
        bool m_isin_cmpconnexein=false;

      ///indice du vertex dans la map de graph
        int m_idx;



        bool IsMarque=false;

    public:

        /// Les constructeurs sont � compl�ter selon vos besoin...
        /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
        Vertex (double value=0, int r=0, double val_ref=0, std::string name=" ", VertexInterface *interface=nullptr) :
            m_value(value), m_r(r), m_val_ref(val_ref), m_name(name), m_interface(interface)  {  }

       // Vertex (Vertex &v): m_value(v.m_value), m_interface(new std::shared_ptr <VertexInterface>(v.m_interface)),
            //   m_idx(v.m_idx) , m_in(v.m_in), m_out(v.m_out){  }

        /// Vertex �tant g�r� par Graph ce sera la m�thode update de graph qui appellera
        /// le pre_update et post_update de Vertex (pas directement la boucle de jeu)
        /// Voir l'impl�mentation Graph::update dans le .cpp
        void pre_update();
        void post_update();


        void Afficher_option();

        void Toggle_Sommet();

        void Cacher_Sommet();

        void Afficher_Somet();

        void Cacher_Arretes();

        void Deco();

        void Cacher_option();


        void set_idx_V(int id);
        int get_idx_V();


        ///marquage accseceur

        void set_marque(bool x);
        bool get_marque();
        void set_connexeout(bool x);
        bool get_connexeout();
        void set_connexein(bool x);
        bool get_connexein();
        void set_marque_connexeout(bool x);
        bool get_marque_connexeout();
        void set_marque_connexein(bool x);
        bool get_marque_connexein();

        std::string get_name(){return m_name ;}



        int get_idx();
        void set_idx(int x);

        bool islinked(Vertex x,int param);

        int get_value();


};



/***************************************************
                    EDGE
****************************************************/

class EdgeInterface
{
    // Les (methodes des) classes amies pourront acc�der
    // directement aux attributs (y compris priv�s)
    friend class Edge;
    friend class Graph;


    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de d�clarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le param�trer ( voir l'impl�mentation du constructeur dans le .cpp )

        // Le WidgetEdge qui "contient" toute l'interface d'un arc
        grman::WidgetEdge m_top_edge;

        // Une boite pour englober les widgets de r�glage associ�s
        grman::WidgetBox m_box_edge;

        // Un slider de visualisation/modification du poids valeur de l'arc
        grman::WidgetVSlider m_slider_weight;

        // Un label de visualisation du poids de l'arc
        grman::WidgetText m_label_weight;

    public :

        // Le constructeur met en place les �l�ments de l'interface
        // voir l'impl�mentation dans le .cpp
        EdgeInterface(Vertex& from, Vertex& to);


};


class Edge
{
    // Les (methodes des) classes amies pourront acc�der
    // directement aux attributs (y compris priv�s)
    friend class Graph;
    friend class EdgeInterface;

    private :
        /// indice du sommet de d�part de l'arc
        int m_from;

        /// indice du sommet d'arriv�e de l'arc
        int m_to;

        /// Variable coefficient qui permet de savoir combien sont mang�
        double m_weight;

        /// indice du sommet pour savoir ou il est dans la map

        int m_indx_E;

        /// le POINTEUR sur l'interface associ�e, nullptr -> pas d'interface
        std::shared_ptr<EdgeInterface> m_interface = nullptr;



        std::vector<int> v_from;


        std::vector<int> v_to;

        double get_weight();


    public:

        /// Les constructeurs sont � compl�ter selon vos besoin...
        /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
        Edge (double weight=0, EdgeInterface *interface=nullptr) :
            m_weight(weight), m_interface(interface)  {  }

        /// Edge �tant g�r� par Graph ce sera la m�thode update de graph qui appellera
        /// le pre_update et post_update de Edge (pas directement la boucle de jeu)
        /// Voir l'impl�mentation Graph::update dans le .cpp
        void pre_update();
        void post_update();


        void Afficher_Edges(Vertex& from , Vertex& to);
        void hide_edge_out();
        void hide_edge_in();


        void set_idx_E(int id);
        int get_idx_E();

};



/***************************************************
                    GRAPH
****************************************************/

class GraphInterface
{
    friend class Graph;

    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de d�clarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le param�trer ( voir l'impl�mentation du constructeur dans le .cpp )

        /// La boite qui contient toute l'interface d'un graphe
        grman::WidgetBox m_top_box;

        /// Dans cette boite seront ajout�s les (interfaces des) sommets et des arcs...
        grman::WidgetBox m_main_box;

        /// Dans cette boite seront ajout�s des boutons de contr�le etc...
        grman::WidgetBox m_tool_box;

        grman::WidgetButton m_savebutton;
        grman::WidgetText m_savebutton_text;

        grman::WidgetText m_tool_text;



        grman::WidgetButton m_afficher_sommet;
        grman::WidgetText m_afficher_sommet_text;

        grman::WidgetButton m_retour;
        grman::WidgetImage m_retour_img;
        grman::WidgetText m_text_flux;

        grman::WidgetButton m_button_flux;
        grman::WidgetText m_text1_flux;
        grman::WidgetText m_text2_flux;


        grman::WidgetButton m_button_play;

        grman::WidgetText m_text_play;


        grman::WidgetButton m_cmp_fconnexe;
        grman::WidgetText m_cmp_fconnexe_text1;
        grman::WidgetText m_cmp_fconnexe_text2;
        grman::WidgetText m_cmp_fconnexe_text3;
        //bouton pour afficher le graphe r�duit
        grman::WidgetButton m_afficher_graphreduit;
        grman::WidgetText m_afficher_graphreduit_text1;
        grman::WidgetText m_afficher_graphreduit_text2;
        //bouton pour d�sactiver l'affichage des cmpconnexe
        grman::WidgetButton m_cmp_fconnexe_off;
        grman::WidgetText m_cmp_fconnexe_off_text1;
        grman::WidgetText m_nb_cmpfc;

        grman::WidgetText m_ordre_graph;


        grman::WidgetText m_text1_play;
        grman::WidgetText m_text2_play;

        grman::WidgetButton m_button_pause;
        grman::WidgetText m_text1_pause;
        grman::WidgetText m_text2_pause;

        std::vector<grman::WidgetBox*> m_tab_cmp_GraphReduit;
        std::vector<grman::WidgetEdge*> m_tab_edge_GraphReduit;
        std::vector<grman::WidgetText*> m_tab_texte_GraphReduit;

        grman::WidgetButton m_button_K_co;
        grman::WidgetText m_label_K_co;


        grman::WidgetButton m_temp;




    public :

        // Le constructeur met en place les �l�ments de l'interface
        // voir l'impl�mentation dans le .cpp
        GraphInterface(int x, int y, int w, int h);
};


class Graph
{
    private :

        /// La "liste" des ar�tes
        std::map<int, Edge> m_edges;

        /// La liste des sommets
        std::map<int, Vertex> m_vertices;

        /// Matrice adjacence pour avoir le numero arete a partir des deuw sommets

        /// le POINTEUR sur l'interface associ�e, nullptr -> pas d'interface
        std::shared_ptr<GraphInterface> m_interface = nullptr;

        bool play=false;
        int ordre;
        int p=0;
        int nbrEdge;
        std::string m_nomgraph;


        std::vector<int> Sommet_suite_in;
        std::vector<int> Sommet_suite_out;

        bool m_quitter=false;

        std::vector<std::vector<Vertex*>> m_tabcmpfc;






    public:

        /// Les constructeurs sont � compl�ter selon vos besoin...
        /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
        Graph (GraphInterface *interface=nullptr) :
            m_interface(interface)  {  }
                                 //int idx, double value, int r, double val_ref, int x, int y, std::string pic_name, int pic_idx
        void add_interfaced_vertex(int idx, double value,int r, double val_ref, int x, int y, std::string pic_name="", int pic_idx=0 );
        void add_interfaced_edge(int idx, int vert1, int vert2, double weight=0);

        /// M�thode sp�ciale qui construit un graphe arbitraire (d�mo)
        /// Voir impl�mentation dans le .cpp
        /// Cette m�thode est � enlever et remplacer par un syst�me
        /// de chargement de fichiers par exemple.
        void make_example();
        void make_graph_1();

        void make_graph_3();

        void make_graph_2();

        long int** find_K_connex();

        bool IsConnex();

        int* marquage(int** adja , int _ordre , int s );

        int KparmisN(int k,int n);

        std::vector<int> allouer_k_uplet();

        void fonctionnel();

        float findEdgeWeight(int s1, int s2);


        void remplirPred();

        void remplirSucc();

        void calculK();

        void calculN();


        void charger(std::string graphName);
        void sauvgarder(std::string graphName);
        void addVertex();
        void Temporise();
        void supprimerVertex();
        int menugraph();


        /// Reset des diff�ntes marquage n�cessaire pout la forte connexit�
        void Reset_marquage_vertex();
        void Reset_marquage_marqued_connexeinout();
        void Reset_marquage_isincompf_connexeinout();

        ///methode qui renvoit l'indice de l'arete qui relie les deux sommets en parametre
        int findEdge(int sfrom, int sto);


      /// Fonctions de recherche de forte connexit�
        std::vector<Vertex*> Cmp_fort_connexe_serach(Vertex s);
         std::vector<std::vector<Vertex*>> search_all_cmpfc();

    /// Mise en valeurs visuel de la forte connexit�

        void visuelle_forte_connexite(bool activate);
        void Afficher_graphReduit(bool activate);

    ///permet de revenir au menu


        /// La m�thode update � appeler dans la boucle de jeu pour les graphes avec interface
        void update();


        bool get_quitter();
        void set_quitter(bool x);
        void destroy_graph();
};


#endif // GRAPH_H_INCLUDED

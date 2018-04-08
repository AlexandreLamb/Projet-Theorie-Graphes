#include "graph.h"
#include <string>
#include <map>

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les éléments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{


    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0 , 100.0); // Valeurs arbitraires, à adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );

    m_top_box.add_child(m_tools_button);
    m_tools_button.add_child(m_tools_text);

    m_tools_button.set_pos(90,0);
    m_tools_text.set_pos(4,3);

    m_tools_text.set_message("Option");

    m_tools_text.set_dim(30,10);
    m_tools_button.set_dim(30,10);



}

void Vertex::Cacher_option() {

    m_interface->m_top_box.remove_child(m_interface->m_tools_box);
    m_interface->m_top_box.set_border(2);
}

void Vertex::Afficher_option(){

        if(grman::mouse_click && m_interface->m_tools_button.is_mouse_over())
    {
        m_interface->m_top_box.add_child(m_interface->m_tools_box);

    m_interface->m_tools_box.add_child(m_interface->m_tools_label);
    m_interface->m_tools_box.add_child(m_interface->m_button_cacher);
    m_interface-> m_tools_box.add_child(m_interface->m_label_cacher);
    m_interface->m_tools_box.add_child(m_interface->m_button_edit);
    m_interface->m_tools_box.add_child(m_interface->m_label_edit);

        m_interface->m_top_box.set_border(0);

        m_interface->m_tools_box.set_pos(-10,-10);
        m_interface->m_tools_box.set_gravity_xy(grman::GravityX::Right,grman::GravityY::Up);
        m_interface->m_tools_box.set_dim(120,120);
        m_interface->m_tools_box.set_border(1);
        m_interface->m_tools_box.set_bg_color(CYAN);

         m_interface-> m_tools_label.set_message("Option Sommet");
         m_interface-> m_label_cacher.set_message("Cacher");
         m_interface-> m_label_edit.set_message("Editer");

         m_interface-> m_tools_label.set_pos(0,0);

         m_interface->m_button_cacher.set_pos(0,20);
         m_interface->m_button_edit.set_pos(0,40);

         m_interface->m_label_cacher.set_pos(40,20);
         m_interface->m_label_edit.set_pos(40,40);

         m_interface->  m_button_cacher.set_bg_color(JAUNE);
         m_interface-> m_button_edit.set_bg_color(JAUNE);

         m_interface->m_button_cacher.set_dim(30,10);
         m_interface->m_button_edit.set_dim(30,10);

    }
   /* else {

        m_interface->m_tools_box.remove_child(m_interface->m_tools_label);
       m_interface-> m_tools_box.remove_child(m_interface->m_button_cacher);
       m_interface-> m_tools_box.remove_child(m_interface->m_label_cacher);
       m_interface-> m_tools_box.remove_child(m_interface->m_button_edit);
       m_interface-> m_tools_box.remove_child(m_interface->m_label_edit);

    }*/

}

void Vertex::Toggle_Sommet(){

    if(grman::mouse_click && m_interface->m_button_cacher.is_mouse_over()){
        Vertex::IsHide = !Vertex::IsHide;

        if(IsHide==true){
            //Cacher_Sommet();

        }
    }

    if(grman::mouse_click && m_interface->m_button_edit.is_mouse_over()){
        Cacher_option();

    }

}

void Vertex::Afficher_Somet(){
        m_interface->m_top_box.add_child( m_interface->m_img );

        m_interface->m_top_box.add_child(m_interface->m_slider_value);

        m_interface->m_top_box.add_child(m_interface->m_label_value);




        m_interface->m_top_box.add_child(m_interface->m_tools_box);

       m_interface->m_top_box.add_child(m_interface-> m_box_label_idx );

       m_interface->m_box_label_idx.set_pos(115,90);
        m_interface->m_img.set_pos(30,0);
         m_interface->m_top_box.set_dim(130, 100);

         m_interface->m_top_box.set_border(2);

    m_interface->m_top_box.add_child(m_interface->m_tools_button);

        m_interface->m_top_box.remove_child(m_interface->m_tools_box);
        m_interface->m_tools_box.remove_child(m_interface->m_tools_label);
       m_interface-> m_tools_box.remove_child(m_interface->m_button_cacher);
       m_interface-> m_tools_box.remove_child(m_interface->m_label_cacher);
       m_interface-> m_tools_box.remove_child(m_interface->m_button_edit);
       m_interface-> m_tools_box.remove_child(m_interface->m_label_edit);


}

void Vertex::Cacher_Sommet(){

    m_interface->m_top_box.remove_child(m_interface->m_img);
    m_interface->m_top_box.remove_child(m_interface->m_tools_box);
    m_interface->m_top_box.remove_child(m_interface->m_slider_value);
    m_interface->m_top_box.remove_child(m_interface->m_box_label_idx);
    m_interface->m_top_box.remove_child(m_interface->m_label_value);
    m_interface->m_top_box.remove_child(m_interface->m_tools_button);
    m_interface->m_top_box.set_dim(0,0);


}

void Vertex::Cacher_Arretes(){



}

/// Gestion du Vertex avant l'appel à l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_value vers le slider associé
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donnée m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex après l'appel à l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_value locale
    m_value = m_interface->m_slider_value.get_value();

    Toggle_Sommet();
    Afficher_option();

}

void Vertex::set_idx_V(int id)
{
    m_indx_V=id;
}

int Vertex::get_idx_V()
{
    return m_indx_V;
}



/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les éléments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de réglage associés
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de réglage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0 , 1000.0); // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}


void Edge::hide_edge_in(Vertex& v){

m_interface->m_top_edge.remove_child(m_interface->m_box_edge);
m_interface->m_top_edge.detach_from();


}
void Edge::hide_edge_out(Vertex& v){

m_interface->m_top_edge.remove_child(m_interface->m_box_edge);
m_interface->m_top_edge.detach_to();

}
void Edge::Afficher_Edges(Vertex& from , Vertex& to){

    m_interface->m_top_edge.attach_from(from.m_interface->m_top_box);
    m_interface->m_top_edge.attach_to(to.m_interface->m_top_box);
    m_interface-> m_top_edge.reset_arrow_with_bullet();

    m_interface->m_top_edge.add_child(m_interface->m_box_edge);

}


/// accesseurs
double Edge::get_weight()
{
    return m_weight;
}


/// Gestion du Edge avant l'appel à l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_weight vers le slider associé
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donnée m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge après l'appel à l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();

    //hide_edge();
}

void Edge::set_idx_E(int id)
{
    m_indx_E=id;
}
int Edge::get_idx_E()
{
    return m_indx_E;
}


/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(800,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_top_box.set_bg_color(VERTFLUO);

    m_top_box.add_child(m_main_box);

    m_main_box.set_dim(708,720);


    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);

    m_top_box.add_child(m_tool_box);


    m_tool_box.set_dim(80,720);

    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_tool_box.add_child(m_savebutton);

    m_tool_box.add_child(m_tool_text);
    m_tool_text.set_message("Options");
    m_tool_text.set_pos(10,20);

    m_savebutton.set_dim(45,30);
    m_savebutton.set_pos(10,40);

    m_savebutton.set_bg_color(ROUGE);
    m_savebutton.add_child(m_savebutton_text);
    m_savebutton_text.set_message("save");
    m_savebutton_text.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);

    m_tool_box.add_child(m_afficher_sommet);
    m_afficher_sommet.add_child(m_afficher_sommet_text);

    m_afficher_sommet.set_dim(45,30);
    m_afficher_sommet.set_bg_color(ROUGE);
    m_afficher_sommet.set_pos(10,120);

    m_afficher_sommet_text.set_message("show");
    m_afficher_sommet_text.set_gravity_xy(grman::GravityX::Center,grman::GravityY::Center);

    m_tool_box.add_child(m_retour);
    m_retour.set_dim(50,50);
    m_retour.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Down);
    m_retour.set_border(0);
    m_retour.add_child(m_retour_img);
    m_retour_img.set_pic_name("retour.bmp");
    m_retour_img.set_pic_idx(0);
    m_retour_img.set_border(0);
    m_retour_img.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Down);


    m_tool_box.add_child(m_button_flux);

    m_button_flux.set_pos(10,200);
    m_button_flux.set_dim(45,30);
    m_button_flux.set_bg_color(ROUGE);

    m_button_flux.add_child(m_text_flux);
    m_text_flux.set_message("ModeF");
    m_text_flux.set_gravity_xy(grman::GravityX::Center,grman::GravityY::Center);

    m_tool_box.add_child(m_button_play);
    m_button_play.set_dim(70,30);
    m_button_play.set_gravity_x(grman::GravityX::Center);
    m_button_play.set_posy(300);
    m_button_play.set_bg_color(ROUGE);
    m_button_play.add_child(m_text_play);
     m_text_play.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);
     m_text_play.set_message("Play");

    m_tool_box.add_child(m_button_pause);
    m_button_pause.set_dim(70,30);
    m_button_pause.set_gravity_x(grman::GravityX::Center);
    m_button_pause.set_posy(332);
    m_button_pause.set_bg_color(ROUGE);
    m_button_pause.add_child(m_text_pause);
     m_text_pause.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);
     m_text_pause.set_message("Pause");

/// Méthode spéciale qui construit un graphe arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de chargement de fichiers par exemple.
/// Bien sûr on ne veut pas que vos graphes soient construits
/// "à la main" dans le code comme ça.



}
void Graph::make_example()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    /// Les sommets doivent être définis avant les arcs
    // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...
    add_interfaced_vertex(0, 29, 0, 0, 2, 4, "clown2.jpg");
    add_interfaced_vertex(1, 60.0, 400, 100,2,4, "clown2.jpg");
    add_interfaced_vertex(2,  50.0, 200, 300, 2,4, "clown3.jpg");
    add_interfaced_vertex(3,  0.0, 400, 300, 2,4, "clown4.jpg");
    add_interfaced_vertex(4,  100.0, 600, 300,2,4, "clown5.jpg");
    add_interfaced_vertex(5,  0.0, 100, 500,2,4, "bad_clowns_xx3xx.jpg", 0);
    add_interfaced_vertex(6,  0.0, 300, 500,2,4, "bad_clowns_xx3xx.jpg", 1);
    add_interfaced_vertex(7,  0.0, 500, 500,2, 4,"bad_clowns_xx3xx.jpg", 2);

    /// Les arcs doivent être définis entre des sommets qui existent !
    // AJouter l'arc d'indice 0, allant du sommet 1 au sommet 2 de poids 50 etc...
    add_interfaced_edge(0, 1, 2, 50.0);
    add_interfaced_edge(1, 0, 1, 50.0);
    add_interfaced_edge(2, 1, 3, 75.0);
    add_interfaced_edge(3, 4, 1, 25.0);
    add_interfaced_edge(4, 6, 3, 25.0);
    add_interfaced_edge(5, 7, 3, 25.0);
    add_interfaced_edge(6, 3, 4, 0.0);
    add_interfaced_edge(7, 2, 0, 100.0);
    add_interfaced_edge(8, 5, 2, 20.0);
    add_interfaced_edge(9, 3, 7, 80.0);
}


void Graph::make_graph_1(){
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);

    Graph::charger("graph1");
    m_nomgraph ="graph1";

}

void Graph::make_graph_2(){

    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    Graph::charger("graph2");
    m_nomgraph ="graph2";
}

void Graph::find_K_connex(){
    int kmin;
    int cmp1=0;
    int cmp2=1;
    int cmp3=0;
    int kParmisN;
    bool IsKmin =false;
    int** pyra=Graph::allouer_k_uplet();

        for(int j = 0 ; j < ordre-1 ;j++){

            for(int i = cmp3 ; i< ordre; i++){
                std::cout<<i<<" "<<pyra[cmp1][i]<<std::endl;

            }
            cmp1++;
            cmp3++;


        }

}

int Graph::KparmisN(int k,int n){

int result=0;
int nFacto=1;
int kFacto=1;
int kMoinNFacto=1;
int tmp =(n-k)+1;


if( n != 0 && k != 0 ){

    for(int i=1 ; i < n+1 ; i++){
        nFacto=i*nFacto;
    }

    for(int i=1 ; i < k+1 ; i++){
        kFacto=i*kFacto;
    }
    for(int i=1 ; i < tmp ; i++){
        kMoinNFacto=i*kMoinNFacto;
    }
    result=(nFacto)/(kFacto*kMoinNFacto);

    return result;
}


return result;
}




int** Graph::allouer_k_uplet(){
    int** mat;
    int cmp=0;
    mat = new int*[ordre];
    for(int i = 0 ; i < ordre ; i++ ){
        mat[i]=new int [ordre-i];
    }
        for(int i = 0 ; i <ordre ; i++){
            //mat[i][0]=i;
            for(int j =0 ; j<ordre-i;j++){
              mat[i][j]=cmp;
              if(i!=mat[i][j]){
               std::cout<<i<<" "<< mat[i][j]<<std::endl;
              }
                cmp++;
            }
            cmp=i+1;

        }

}


///zoe : sous prgramme qui gère partie fonctinnel sans affichage
void Graph::fonctionnel()
{
    /// variables

    float N=0;
    double coeff=0;

     /*/
    std::cout << " TEST VALEUR FIC";
    for(int k=0; k<ordre; k++)
    {
        std::cout <<" " <<m_vertices[k].m_value<<" " <<m_vertices[k].m_r <<" " <<m_vertices[k].m_val_ref;
    }
    /*/

    /// condition: si l'utilisateur appuie sur play et tant qu'il n'appuie pas sur pause ou rappuie sur play

           if(play)
            {

                      std::cout << " " <<std::endl;
                      std::cout << " ----- TEST FLUX -----"  <<std::endl;
                      std::cout << " " <<std::endl;
                /// montee en memoire des valeures sur les curseurs ou sur fichier si curseur pas modi


                /// remplit pour chaque sommet vecteur de pred
                remplirPred();
                /*/ TEST PREDECESSEURS QUI EST MANGE PAR QUI
                for(int i=0; i<ordre;i++)
                {  std::cout << "S"<<i <<" "<<m_vertices[i].m_name<<" ";
                    std::cout << "a "<<m_vertices[i].m_pred.size() <<" predecesseurs, il est mange par: ";
                    for(int j=0; j<m_vertices[i].m_pred.size(); j++) { std::cout << " S"<<m_vertices[i].m_pred[j] <<" "<<m_vertices[m_vertices[i].m_pred[j]].m_name<<" ";}
                    std::cout << " "<<std::endl;
                }
                /*/
                  /// remplit pour chaque sommet vecteur de pred
                remplirSucc();
                /*/
                for(int i=0; i<ordre;i++)
                {  std::cout << "S"<<i <<" "<<m_vertices[i].m_name<<" ";
                    std::cout << "a "<<m_vertices[i].m_succ.size() <<" successeurs, il mange: ";
                    for(int j=0; j<m_vertices[i].m_succ.size(); j++) { std::cout << " S"<<m_vertices[i].m_succ[j] <<" "<<m_vertices[m_vertices[i].m_succ[j]].m_name<<" ";}
                    std::cout << " "<<std::endl;
                }
                /*/



                    std::cout << "  ---- Boucle ---- " <<std::endl;

                /// on calcul et met à jour le K de chaque sommet
                calculK();


                for(int i=0; i<ordre;i++)
                {
                    for(int j=0; j<m_vertices[i].m_succ.size(); j++)
                    {
                    coeff=findEdgeWeight(i,m_vertices[i].m_succ[j]);
                    //std::cout << " "<<m_vertices[m_vertices[i].m_succ[j]].m_value <<"  "<<m_vertices[m_vertices[i].m_succ[j]].m_name<<" * "<<coeff<<" + ";
                    }
                    std::cout << "K= "<< m_vertices[i].m_K<<std::endl;
                }


                /// on calcul et met à jour le N de chaque somme
                calculN();
/*/
                for(int i=0; i<ordre;i++)
                {
                    for(int j=0; j<m_vertices[i].m_succ.size(); j++)
                    {
                      std::cout <<"N = "<<(m_vertices[i].m_value) <<"+ "<<(m_vertices[i].m_r)<<" * " <<(m_vertices[i].m_value)<<" * (1-( " ;
                     std::cout << m_vertices[i].m_value<<" / "<<m_vertices[i].m_K <<")"<<std::endl;
                    }
                    std::cout << "N = "<< m_vertices[i].m_value<<std::endl;
                    std::cout << "N+1 = "<< m_vertices[i].m_valuePlus1<<std::endl;
                    std::cout << " "<<std::endl;
                }


/*/

                /// anomations du mort quand la population est morte
                for(int i=0; i<ordre; i++)
                 {
                     if(m_vertices[i].m_value==0)
                     {
                         rest(40);
                         m_vertices[i].m_interface->m_img.set_pic_name("Dead.png");

                     }
                 }
                std::cout << " "<<std::endl;

            }
}

/*
void Graph::update(){

    for ( int i = 0 ; i < Graph::m_vertices ; i++ ){
       Graph::m_vertices[i] Graph::m_vertices[i].m_interface->m_slider_value.get_value()
    }

}
*/


/// methode qui calcul et remplit le N des sommets
void Graph::calculN()
{
    double N_save=0;
    double N=0;
    double N_pourc=0;
    int K=0;
    int nb;
    int id_pred;
    double Npred=0;
    double val_ref=0;
    double coeff=0;
    std::vector<float> liste_N;


    /// parcours des sommets
    for(int k=0; k<ordre; k++)
    {
        /// Nsave = N | N=Nplus1 | ici on calcul Nplu1 avec le Nsave

        N=m_vertices[k].m_interface->m_slider_value.get_value();


        /// conversion de valeur à pourcentage  avec la valeure de reference
        N=N*m_vertices[k].m_val_ref/1000;

        /// on fait monter dans les attributs cette valeure pour le calcul du K
        m_vertices[k].m_value=N;

        /// sauvegarde du N+1 que l'on ecrase
        N_save=m_vertices[k].m_value;

        /// recupere le K
        K=m_vertices[k].m_K;

        if(K!=0) // si K=0 pas de succ don on peut pas se reproduire et manger
        {
            //std::cout << "N+1.1 = N + r * N * (1 - ( N / K )) "<<std::endl;
            //std::cout<< "N+1.1 = ("<< N_save << ") + ("<<m_vertices[k].m_r << ") * (" <<N_save<<") * (1-(" <<N_save<<" / "<<K << ") = "<<std::endl;
            N= (N_save) + (m_vertices[k].m_r)*(N_save)*(1-(N_save)/K);

        }
        else {//std::cout<< " K=0 -> N+1.1 = N = "<< N <<std::endl;
            N= N_save;

        }

        /// on recupere le nombre de ses predecesseurs
        nb=m_vertices[k].m_pred.size();
        //std::cout<< "N+1 = N ";
        if(nb!=0) // si nb=0 pas de predecesseurs
        {
            for(int i=0; i<nb; i++)
            {
                id_pred=m_vertices[k].m_pred[i];

                coeff=findEdgeWeight(id_pred, k);

                /// N inchange encore
                Npred=m_vertices[id_pred].m_value;

                N=N-(coeff*Npred);
               // std::cout<< "- ( "<<coeff<<" * "<<Npred<< " ) " ;
                if(N<=0) /// pas de pop negative possible
                {
                    N=0;
                }

            }

            //std::cout<< " = " << N<<std::endl;
            /// sauvegarde des valeurs de N dans des vecteurs
            liste_N.push_back(N);
            //std::cout<< " " <<std::endl;

        }
        else
        {
           // std::cout<< " = " << N;
           // std::cout<< "  car pas de pred  "<<std::endl;
            liste_N.push_back(N);

         }
       // std::cout<< " " <<std::endl;
    }


    /// parcours des sommets pour montee en memoir les vecteurs dans les attributs
    for(int k=0; k<ordre; k++)
    {
        m_vertices[k].m_value=liste_N[k];
        std::cout << m_vertices[k].m_name<<" N = "<< m_vertices[k].m_value<<std::endl;

        /// conversion de valeur à pourcentage  avec la valeure de reference
        val_ref=m_vertices[k].m_val_ref;
        N_pourc= 1000*N/val_ref;

        /// afichage de cette valeur sur les curseurs
        m_vertices[k].m_interface->m_slider_value.set_value(N_pourc);
        rest(90);


    }

}

/// methode qui calcul et remplit le K des sommets
void Graph::calculK()
{
     int nb=0;
     int id_succ=0, id_arc=0;
     double N=0;
     double coeff=0;
     double K=0;

    /// parcours sommet
    for(int k=0; k<ordre; k++)
    {
        K=0;
        /// on recupere le nombre de ses predecesseurs = le nombre d'arc
        nb=m_vertices[k].m_succ.size();

        /// pour tous ces succ on cherche le sommet predecesseur relié a cette arete
        for(int i=0; i<nb; i++)
        {
            /// on recupere l'indice du succ
            id_succ=m_vertices[k].m_succ[i];

            /// on recupere son coeff = poids
            coeff=findEdgeWeight(k,id_succ);

            ///on recupere le nombre de pop du succ
            N=m_vertices[id_succ].m_interface->m_slider_value.get_value();


            /// on calcul K
            K=K+(coeff*N);


        }
        /// sauvegarde dans attributs
        m_vertices[k].m_K=K;
       // std::cout << "K= "<< m_vertices[k].m_K<<std::endl;
    }
}

/// methode qui remplit le vecteur des pred de tous les sommets
void Graph::remplirPred()
{
    int id_arc, id_sfrom, nb;
   /// on parcourt sommets
    for(int k=0; k<ordre; k++)
    {
        /// on recupere le nombre de ses predecesseurs = le nombre d'arc
        nb=m_vertices[k].m_out.size();

        /// pour tous ces pred on cherche le sommet predecesseur relié a cette arete
        for(int i=0; i<nb; i++)
        {
            /// on recupere l'index d'un arc du pred
            id_arc=m_vertices[k].m_out[i];

            /// on recupere le sommet m_to qu'elle relie au sommet [k]
            id_sfrom= m_edges[id_arc].m_from;
            ///montee en memoire
            m_vertices[k].m_pred.push_back(id_sfrom);

        }
    }
}

/// methode qui remplit le vecteur des succ de tous les sommets
void Graph::remplirSucc()
{
    int id_arc, id_sto, nb;
   /// on parcourt sommets
    for(int k=0; k<ordre; k++)
    {
        /// on recupere le nombre de ses succ = le nombre d'arc
        nb=m_vertices[k].m_in.size();

        /// pour tous ces succ on cherche le sommet succ relié a cette arete
        for(int i=0; i<nb; i++)
        {
            /// on recupere l'index d'un arc du succ
            id_arc=m_vertices[k].m_in[i];

            /// on recupere le sommet m_from qu'elle relie au sommet [k]
            id_sto= m_edges[id_arc].m_to;

            ///montee en memoire
            m_vertices[k].m_succ.push_back(id_sto);

        }
    }
}

/// methode qui renvoit le poids de l'arete des deux sommets en parametre
float Graph::findEdgeWeight(int sfrom, int sto)
{
    int s1=0;
    int s2=0;

    double poids=0;

    /// parcourt la map d'arete
    for(auto &elt : m_edges)
    {
        /// accede à m-from et m_to
       s1= elt.second.m_from;
       s2= elt.second.m_to;

       /// si les sommets s1 et s2 sont les meme que les sommets en parametres on retourne la valeur de l'arete (coeff)
       if(s1==sfrom && s2==sto)
       {
           poids= elt.second.m_interface->m_slider_weight.get_value();

           return poids;
       }
    }
}

void Graph::addVertex()
{

    int indxVertex,posX, posY, indxEdge, vertexIn, vertexOut;

    double poidEdge,poidVertex;

}

void Graph::supprimerVertex(){

    std::map<int,Vertex>::iterator it1;
    std::map<int,Edge>::iterator it2;

    for ( auto &elmt : m_vertices){
        if(elmt.second.IsHide==true){
            elmt.second.Cacher_Sommet();

            //std::cout<<elmt.second.m_out.size();
            for(int i =0 ; i < elmt.second.m_in.size();i++){
            m_edges[elmt.second.m_in[i]].hide_edge_in(elmt.second);

            }

            for(int i =0 ; i < elmt.second.m_out.size();i++){
                m_edges[elmt.second.m_out[i]].hide_edge_out(elmt.second);


            }
        }
    }
}



void Graph::charger(std::string graphName){

    std::ifstream fichier (graphName+".txt",std::ios::in);
    int indxVertex,posX, posY, r,indxEdge, vertexIn, vertexOut;
    double poidEdge,poidVertex, val_ref;
    std::string picName;
    bool bo=false;


            if (fichier){

        fichier >> Graph::ordre;
        fichier >> Graph::nbrEdge;

        for(int i=0 ; i <ordre  ; i++){
        fichier >> poidVertex;
        fichier >> posX;
        fichier >> posY;
        fichier >> r;
        fichier >> val_ref;
        fichier >> picName;

        add_interfaced_vertex(i,poidVertex,r, val_ref,posX,posY,picName+".jpg");
        }
        for(int j=0 ; j < nbrEdge ; j++){

        /// montee en memoire des attributs pour interface
            fichier >> vertexIn;
            fichier >> vertexOut;
            fichier >> poidEdge;
            add_interfaced_edge(j,vertexIn,vertexOut,poidEdge);
        }
        fichier.close();

    }
}

void Graph::sauvgarder(std::string graphName){

    std::ofstream fichier(graphName+".txt",std::ios::out | std::ios::trunc);
    std::string picName;
        if(fichier){
            fichier << Graph::ordre <<std::endl;
            fichier << Graph::nbrEdge<<std::endl;

            for(auto &elt : m_vertices){
         fichier << elt.second.m_value<<" ";
         fichier <<elt.second.m_interface->m_top_box.get_frame_pos().x<<" ";
         fichier <<elt.second.m_interface->m_top_box.get_frame_pos().y<<" ";
         fichier <<elt.second.m_r<<" ";
         fichier <<elt.second.m_val_ref<<" ";
        picName=elt.second.m_interface->m_img.get_pic_name();
        picName.erase(picName.size()-4,4);
         fichier <<picName<<std::endl;
    }
        for(auto &elt : m_edges){
            std::cout<<elt.second.m_from;
            fichier << elt.second.m_from<<" ";
            fichier << elt.second.m_to<<" ";
            fichier << elt.second.m_weight<<std::endl;

        }
        fichier.close();
        std::cout<<"Sauvgarde done";
        }

}

int Graph::menugraph()
{
    int i=0;

    if(grman::mouse_click && m_interface->m_afficher_sommet.is_mouse_over())
    {



        for ( auto &elmt : m_vertices ){
            elmt.second.IsHide=false;
           elmt.second.Afficher_Somet();
        }
        for ( auto & elmt : m_edges ) {

           elmt.second.Afficher_Edges(m_vertices[Sommet_suite_in[i]],m_vertices[Sommet_suite_out[i]]);
           i++;
        //std::cout<<"l'arrete "<< i <<"est composé des sommet " << Sommet_suite_in[i]<<" et "<< Sommet_suite_out[i]<<std::endl;
            if(Sommet_suite_in[i]==0 && Sommet_suite_out[i]==1){
                std::cout<<i<<"t";
            }
        }


    }
    if(grman::mouse_click && m_interface->m_savebutton.is_mouse_over()){

       sauvgarder(m_nomgraph);

    }

    if(grman::mouse_click && m_interface->m_retour.is_mouse_over())
    {
        return 1;
    }

    if(grman::mouse_click&1 && m_interface->m_button_flux.is_mouse_over())
    {
        fonctionnel();
       std::cout<<"1";
    }




    if(grman::mouse_click && m_interface->m_button_play.is_mouse_over())
        {
                play=true;


        }if
        (grman::mouse_click && m_interface->m_button_pause.is_mouse_over())
        {
                play=false;


        }

    return 0;
}


void Graph::destroy_graph()
{

    for(std::map<int,Vertex>::iterator it= m_vertices.begin(); it!=m_vertices.end();it++)
    {
        m_interface->m_main_box.remove_child(it->second.m_interface->m_top_box);

    }

    m_vertices.clear();

    for(std::map<int,Edge>::iterator et= m_edges.begin(); et!=m_edges.end();et++)
    {
        m_interface->m_main_box.remove_child(et->second.m_interface->m_top_edge);


    }
    m_edges.clear();

    m_interface.reset();
    m_interface=nullptr;

}

/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();
    menugraph();
    supprimerVertex();
    if(play)
    fonctionnel();

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();

}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value, int r, double val_ref, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Création d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(value,r, val_ref, pic_name, vi);

}

/// Aide à l'ajout d'arcs interfacés
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
{

    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_edges[idx] = Edge(weight, ei);
    m_edges[idx].m_from=id_vert1;
    m_edges[idx].m_to=id_vert2;

    //m_vertices[id_vert1].m_in.push_back(idx);
    //m_vertices[id_vert2].m_out.push_back(idx);


   // std::cout<<"les sommet "<<id_vert1<<" et "<<id_vert2<<" sont relié par l'arrete " <<idx <<std::endl;
    Sommet_suite_in.push_back(id_vert1);
    Sommet_suite_out.push_back(id_vert2);

/*****************************************
    je laisse pour l'instant c'est 2 ligne
    et mets les deux du haut en commentaire
    juste que je verifie que ca pose pas de
    problmes quand je les utilise

******************************************/
    if((idx!=id_vert1) ||(idx!=id_vert2))
    {
        m_vertices[id_vert1].m_in.push_back(idx);
        m_vertices[id_vert2].m_out.push_back(idx);

    }
}

/// methode qui renvoit indice de l'arete entre deux sommets en parametre
int Graph::findEdge(int sfrom, int sto)
{
    int s1=0;
    int s2=0;

    double idx=0;


    /// parcourt la map d'arete
    for(auto &elt : m_edges)
    {
        /// accede à m-from et m_to
       s1= elt.second.m_from;
       s2= elt.second.m_to;

       /// si les sommets s1 et s2 sont les meme que les sommets en parametres on retourne la valeur de l'arete (coeff)
       if(s1==sfrom && s2==sto)
       {
          idx= elt.first;

           return idx;
       }
    }
}

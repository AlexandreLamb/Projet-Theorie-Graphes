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
         m_interface-> m_label_edit.set_message("Retour");

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
    m_slider_weight.set_range(0.0 , 100.0); // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}


void Edge::hide_edge_in(){

m_interface->m_top_edge.remove_child(m_interface->m_box_edge);
m_interface->m_top_edge.detach_from();


}
void Edge::hide_edge_out(){

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

    m_tool_box.add_child(m_button_K_co);

    m_button_K_co.set_pos(10,280);
    m_button_K_co.set_dim(45,30);
    m_button_K_co.set_bg_color(ROUGE);

    m_button_K_co.add_child(m_label_K_co);
    m_label_K_co.set_message("K-Co");
    m_label_K_co.set_gravity_xy(grman::GravityX::Center,grman::GravityY::Center);

    m_tool_box.set_bg_color(BLANCBLEU);


}

void Graph::make_example()
{

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

long int** Graph::find_K_connex(){

long int* tab;
long int** liste;

long int i,j;
long int n= ordre;

int cmp = 0;
int k =0;
tab=(long int*)malloc(n*sizeof(long int));
liste = (long int**)malloc((long int) pow((double)n,(double)p) * sizeof(long int*));
for(i=0;i<(long int )pow((double)n,(double)p);i++){
    liste[i] = (long int*)malloc(p*sizeof(long int));
}
for(i=0;i<n;i++){
    tab[i]=i;
}
for(i=0;i<(long int )pow((double)n,(double)p);i++){
    for(j=0;j<p;j++){


        liste[i][j] = tab[(i/(long int)pow((double)n,(double)(p-(j+1))))%n];




    }
}
for(k;k<p;k++){
    for(i=0;i<(long int )pow((double)n,(double)p);i++){
        for(j=0;j<p;j++){
            if(liste[i][k]==liste[i][j] && k!=j ){
                liste[i][0]=-1;
        }
    }
}

}
return liste;
}

 bool Graph::IsConnex(){



int n = ordre;

long int** tab ;


std::vector<int> SomemtMarque;

int* marque;

int ** adja = new int* [ordre];
int tmp1=0,tmp2=0;
for(int i =0 ; i < ordre;i++){
    adja[i] = new int [ordre];
}

std::cout<<"Choisir quelle k-connexité vous voulez tester ? ...";
std::cin>>Graph::p;

tab= find_K_connex();



for(int i=0;i<(long int )pow((double)n,(double)p);i++){
   if(tab[i][0] != -1 ){

    for(int j=0;j<p;j++){


              m_vertices[tab[i][j]].IsMarque=true;  ///on marque toute la ligne
            m_vertices[tab[i][j]].Cacher_Sommet();
            SomemtMarque.push_back(tab[i][j]);


    }

    for(int a =0 ; a < ordre;a++){
        for(int b = 0 ; b < ordre ; b ++){
            adja[a][b]=0;
        }
    }



    for(int a = 0 ; a < nbrEdge ; a++ ){
        if(!m_vertices[m_edges[a].m_from].IsMarque && !m_vertices[m_edges[a].m_to].IsMarque )
        {
            adja[m_edges[a].m_from][m_edges[a].m_to] = 1;
            adja[m_edges[a].m_to][m_edges[a].m_from] = 1;
            tmp1=m_edges[a].m_to;
        }
    }



     marque =  marquage(adja,ordre-p,tmp1);
     tmp2=0;

     for(int x =0 ;x< ordre ;x++){

        tmp2=marque[x]+tmp2; ///nbr sommet marqué
     }

    if(tmp2 == ordre-p){
            std::cout<<"les sommet : "<<std::endl;
        for(int i = 0 ; i<SomemtMarque.size();i++){
                std::cout<<"- "<<SomemtMarque[i]<<std::endl;
        }
    std::cout<<"lorsqu'il sont deconnecte ne rende pas le graph non connexe"<<std::endl;
    }
    else{
        std::cout<<"les sommet marque on deconnecte le graph"<<std::endl;
    }

    SomemtMarque.clear();

    for(int a=0;a<p;a++){

              m_vertices[tab[i][a]].IsMarque=false;  ///on marque toute la ligne
                m_vertices[tab[i][a]].Afficher_Somet();
    }



   }
}




}
void Graph::Temporise(){
    bool isTemp=false;
        m_interface->m_tool_box.add_child(m_interface->m_temp);
        m_interface->m_temp.set_pos(10,400);
        m_interface->m_temp.set_dim(35,40);
        m_interface->m_temp.set_bg_color(ROUGE);


        do{
        if(grman::mouse_click && m_interface->m_temp.is_mouse_over()){

        isTemp=true;

        }

        }
        while(isTemp==false);
}

int* Graph::marquage(int** adja , int _ordre , int s ){

    int* marques = new int[ordre];
    int x,y;
    int cmp=0;
    /*int* tab = new int[_ordre];
    for(int i = 0 ; i< ordre ; i++ ){
            std::cout<<"s = " <<s<<std::endl;
        if((s<ordre)&&(!m_vertices[s].IsMarque)){
        tab[cmp]=s;
        std::cout<<"tab de " <<cmp <<" = "<< tab[cmp]<<std::endl;
        cmp++;

        }
        if(s>=ordre) {
            s = 0;
        }
s++;

    }*/
    for(x=0;x<ordre;x++){
        marques[x]= 0;
    }
    marques[s]=1;

   for(x=0;x<ordre;x++){
        if(marques[x]){
            for(y=0;y<ordre;y++){
                    if(adja[x][y]&&!marques[y]){
                            marques[y]=1;
                    }
            }
        }
    }

    for(x=s;x>0;x--){

        if(marques[x]){
            for(y=0;y<ordre;y++){
                    if(adja[x][y]&&!marques[y]){
                            marques[y]=1;
                    }
            }
        }
    }
return marques;
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





std::vector<int> Graph::allouer_k_uplet(){

    std::vector<int> vec;
    int** mat;
    int cmp=0;

    mat = new int*[ordre];
    for(int i = 0 ; i < ordre ; i++ ){
        mat[i]=new int [ordre-i];
    }

        for(int i = 0 ; i <ordre ; i++){
            //mat[i][0]=i;
            //vec.push_back( mat[i][0]);
            for(int j =0; j<ordre-i;j++){
                mat[i][j]=cmp;
                vec.push_back( mat[i][j]);
                cmp++;
              }
            cmp=i+1;
        }
        return vec;
}


///zoe : sous prgramme qui gère partie fonctinnel sans affichage
void Graph::fonctionnel()
{
    /// variables
    float K=0;
    int id_arc=0;
    int id_sto=0;
    int N=0;
    bool play = false; // savoir quand c'est play ou non
    bool mode_flux=false; // savoir si bouton mode flux est actif
    double coeff=0.00;
    int nb=0;

    mode_flux = true; // savoir si appuyer sur bouton mode flux

    if(mode_flux){

    /// condition: si l'utilisateur appuie sur play et tant qu'il n'appuie pas sur pause
    play = true; /// trouver : quand il clique sur play dans toolbar

        if(play)
        {
                      std::cout << " " <<nb <<std::endl;
                      std::cout << " ----- TEST FLUX -----" <<nb <<std::endl;
                      std::cout << " " <<nb <<std::endl;
            do
            {
                /// on parcourt sommets et on calcul leur K
                for(int k=0; k<ordre; k++)
                {
                    K=0;
                    /// on recupere le nombre de ses predecesseurs = le nombre d'arc
                    nb=m_vertices[k].m_in.size();

                    /// pour tous ces pred on cherche le sommet predecesseur relié a cette arete
                    for(int i=0; i<nb; i++)
                    {
                        /// on recupere l'index d'un arc du pred
                        id_arc=m_vertices[k].m_in[i];

                       /// on recupère le coeff de cette arete
                        coeff=m_edges[id_arc].m_weight;

                        /// on recupere le sommet m_to qu'elle relie au sommet [k]
                        id_sto= m_edges[id_arc].m_to;

                        ///on recupere le nombre de pop dans sommet to
                        N=m_vertices[id_sto].m_value;

                        /// on calcul K
                        K=K+(coeff*m_vertices[id_sto].m_value);

                        std::cout << "S" << k  <<" mange "<< coeff << "S"<< id_sto << " du nb de "<<N <<std::endl;
                    }

                    ///montee en memoire
                    m_vertices[k].m_K=K;
                    std::cout << " le K est: " << K << std::endl;
                }
            }
            while(!play);
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
            m_edges[elmt.second.m_in[i]].hide_edge_in();

            }

            for(int i =0 ; i < elmt.second.m_out.size();i++){
                m_edges[elmt.second.m_out[i]].hide_edge_out();


            }
            }
        }
    }






void Graph::charger(std::string graphName){

    std::ifstream fichier (graphName+".txt",std::ios::in);
    int indxVertex,posX, posY, indxEdge, vertexIn, vertexOut;
    double poidEdge,poidVertex;
    std::string picName;


    if (fichier){

        fichier >> Graph::ordre;

        fichier >> Graph::nbrEdge;

        for(int i=0 ; i < ordre ; i++){

        fichier >> poidVertex;
        fichier >> posX;
        fichier >> posY;
        fichier >> picName;

        add_interfaced_vertex(i,poidVertex,posX,posY,picName+".jpg");
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
    if(grman::mouse_click && m_interface->m_button_flux.is_mouse_over()){



    }
    if(grman::mouse_click && m_interface->m_button_K_co.is_mouse_over()){
        IsConnex();


    }

    if(grman::mouse_click && m_interface->m_retour.is_mouse_over())
    {
        return 1;
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

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();



}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
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
    m_vertices[idx] = Vertex(value, vi);


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

    m_vertices[id_vert1].m_out.push_back(idx);
    m_vertices[id_vert2].m_in.push_back(idx);


    std::cout<<"les sommet "<<id_vert1<<" et "<<id_vert2<<" sont relié par l'arrete " <<idx <<std::endl;
    Sommet_suite_in.push_back(id_vert1);
    Sommet_suite_out.push_back(id_vert2);

/*****************************************
    je laisse pour l'instant c'est 2 ligne
    et mets les deux du haut en commentaire
    juste que je verifie que ca pose pas de
    problmes quand je les utilise

******************************************/
   /* if((idx!=id_vert1) ||(idx!=id_vert2) )
    {
        m_vertices[id_vert1].m_in.push_back(idx);
        m_vertices[id_vert2].m_out.push_back(idx);

    }
*/

}

/// methode qui rencoit l'indice de l'arete qui relie les deux sommets en parametre
double Graph::PredSucc(int sfrom, int sto)
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
       if((s1==sfrom && s2==sto))
       {
           poids= elt.second.m_weight;

           return poids;
       }
    }
}

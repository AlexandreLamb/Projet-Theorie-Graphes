#include "graph.h"
#include <string>

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les �l�ments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{


    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de r�glage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0 , 100.0); // Valeurs arbitraires, � adapter...
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

    m_tools_button.set_pos(0,0);
    m_tools_text.set_pos(4,3);

    m_tools_text.set_message("Option");

    m_tools_text.set_dim(30,10);
    m_tools_button.set_dim(30,10);



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

/// Gestion du Vertex avant l'appel � l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donn�e m_value vers le slider associ�
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donn�e m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex apr�s l'appel � l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donn�e m_value locale
    m_value = m_interface->m_slider_value.get_value();

    Toggle_Sommet();
    Afficher_option();

}



/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les �l�ments de l'interface
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

    // Une boite pour englober les widgets de r�glage associ�s
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de r�glage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0 , 100.0); // Valeurs arbitraires, � adapter...
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

}


/// Gestion du Edge avant l'appel � l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donn�e m_weight vers le slider associ�
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donn�e m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge apr�s l'appel � l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donn�e m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();

    //hide_edge();
}



/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de pr�parer un cadre d'accueil des
/// �l�ments qui seront ensuite ajout�s lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(800,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_top_box.set_bg_color(VERTFLUO);

    m_top_box.add_child(m_main_box);
<<<<<<< HEAD
    m_main_box.set_dim(708,720);
=======
    m_main_box.set_dim(908,730);
>>>>>>> Menu/Flo
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);

    m_top_box.add_child(m_tool_box);
<<<<<<< HEAD

    m_tool_box.set_dim(80,720);
=======
    m_tool_box.set_dim(80,730);
>>>>>>> Menu/Flo
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_tool_box.add_child(m_savebutton);
<<<<<<< HEAD
    m_tool_box.add_child(m_afficher_sommet);

    m_savebutton.set_dim(35,20);
    m_savebutton.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
=======
    m_savebutton.set_dim(45,30);
    m_savebutton.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Up);
>>>>>>> Menu/Flo
    m_savebutton.set_bg_color(ROUGE);
    m_savebutton.add_child(m_savebutton_text);
    m_savebutton_text.set_message("save");
    m_savebutton_text.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);

<<<<<<< HEAD
    m_afficher_sommet.set_dim(35,20);
    m_afficher_sommet.set_bg_color(ROUGE);
    m_afficher_sommet.set_pos(10,50);
=======
    m_tool_box.add_child(m_retour);
    m_retour.set_dim(50,50);
    m_retour.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Down);
    m_retour.set_border(0);
    m_retour.add_child(m_retour_img);
    m_retour_img.set_pic_name("retour.bmp");
    m_retour_img.set_pic_idx(0);
    m_retour_img.set_border(0);
    m_retour_img.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Down);
>>>>>>> Menu/Flo


    m_tool_box.set_bg_color(BLANCBLEU);


}


/// M�thode sp�ciale qui construit un graphe arbitraire (d�mo)
/// Cette m�thode est � enlever et remplacer par un syst�me
/// de chargement de fichiers par exemple.
/// Bien s�r on ne veut pas que vos graphes soient construits
/// "� la main" dans le code comme �a.
void Graph::make_example()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne pr�c�dente est en gros �quivalente � :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    /// Les sommets doivent �tre d�finis avant les arcs
    // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...
    add_interfaced_vertex(0, 29, 0, 0, "clown2.jpg");
    add_interfaced_vertex(1, 60.0, 400, 100, "clown2.jpg");
    add_interfaced_vertex(2,  50.0, 200, 300, "clown3.jpg");
    add_interfaced_vertex(3,  0.0, 400, 300, "clown4.jpg");
    add_interfaced_vertex(4,  100.0, 600, 300, "clown5.jpg");
    add_interfaced_vertex(5,  0.0, 100, 500, "bad_clowns_xx3xx.jpg", 0);
    add_interfaced_vertex(6,  0.0, 300, 500, "bad_clowns_xx3xx.jpg", 1);
    add_interfaced_vertex(7,  0.0, 500, 500, "bad_clowns_xx3xx.jpg", 2);

    /// Les arcs doivent �tre d�finis entre des sommets qui existent !
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

}

///zoe : sous prgramme qui g�re partie fonctinnel sans affichage
void Graph::fonctionnel()
{
    /// affichage du nombre de la population
    for(int i= 0; i<ordre; i++)
    {
        std::cout << "la population est de" <<m_vertices[i].m_value <<std::endl;
        std::cout << "son coeff est de" <<m_edges[i].m_weight <<std::endl;
    }

    /// variables
    float K=0;
    int indx=0;
    bool play = false; // savoir quand c'est play ou non
    bool pause =false;
    bool mode_flux=false; // savoir si bouton mode flux est actif

    if(mode_flux){

    /// condition: si l'utilisateur appuie sur play et tant qu'il n'appuie pas sur pause
    play = true; /// trouver : quand il clique sur play dans toolbar

        if(play)
        {
            do
            {
                /// on parcourt sommets et on calcul leur K
                for(int k=0; k<ordre; k++)
                {
                    int nb=m_vertices[k].m_out.size();

                    for(int i=0; i<nb; i++)
                    {
                      indx=m_vertices[k].m_out[i];
                    }

                }

            }
            while(pause);
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
    int indxVertex,posX, posY, indxEdge, vertexIn, vertexOut;
    double poidEdge,poidVertex;
    std::string picName;


    if (fichier){

        fichier >> Graph::ordre;

        fichier >> Graph::nbrEdge;
        std::cout<< nbrEdge;
        for(int i=0 ; i < ordre ; i++){

        fichier >> poidVertex;
        fichier >> posX;
        fichier >> posY;
        fichier >> picName;

        add_interfaced_vertex(i,poidVertex,posX,posY,picName+".jpg");
        }
        for(int j=0 ; j < nbrEdge ; j++){

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
    if(grman::mouse_click && m_interface->m_savebutton.is_mouse_over())
    {
        sauvgarder("graph1");
    }
<<<<<<< HEAD
    if(grman::mouse_click && m_interface->m_afficher_sommet.is_mouse_over())
    {
        for ( auto &elmt : m_vertices ){
            elmt.second.IsHide=false;
           elmt.second.Afficher_Somet();
        }
        for ( auto & elmt : m_edges ) {

           elmt.second.Afficher_Edges(m_vertices[Sommet_suite_in[i]],m_vertices[Sommet_suite_out[i]]);
           i++;
        }


    }

=======
    if(grman::mouse_click && m_interface->m_retour.is_mouse_over())
    {
        return 1;
    }

    return 0;
>>>>>>> Menu/Flo

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
/// La m�thode update � appeler dans la boucle de jeu pour les graphes avec interface
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

/// Aide � l'ajout de sommets interfac�s
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Cr�ation d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(value, vi);

}

/// Aide � l'ajout d'arcs interfac�s
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
    m_vertices[id_vert1].m_in.push_back(idx);
    m_vertices[id_vert2].m_out.push_back(idx);
    std::cout<<"les sommet "<<id_vert1<<" et "<<id_vert2<<" sont reli� par l'arrete " <<idx <<std::endl;
    Sommet_suite_in.push_back(id_vert1);
    Sommet_suite_out.push_back(id_vert2);
}


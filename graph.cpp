#include "graph.h"
#include <string>

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
    m_slider_value.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
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
}


void Vertex::set_marque(bool x)
{
    m_ismarqued=x;
}

bool Vertex:: get_marque()
{
    return m_ismarqued;
}

void Vertex::set_connexeout(bool x)
{
    m_isin_cmpconnexeout=x;
}

bool Vertex :: get_connexeout()
{
    return m_isin_cmpconnexeout;
}

void Vertex::set_connexein(bool x)
{
    m_isin_cmpconnexein=x;
}

bool Vertex :: get_connexein()
{
    return m_isin_cmpconnexein;
}



int Vertex::get_idx()
{
    return m_idx;
}

void Vertex::set_idx(int x)
{
    m_idx=x;
}


void Vertex:: set_marque_connexeout(bool x)
{
    m_ismarqued_connexeout=x;
}
bool Vertex::get_marque_connexeout()
{
    return m_ismarqued_connexeout;
}
void Vertex:: set_marque_connexein(bool x)
{
    m_ismarqued_connexein=x;
}
bool Vertex:: get_marque_connexein()
{
    return m_ismarqued_connexein;
}






bool Vertex::islinked(Vertex x, int param)
{
    bool linked;
    /// est liée pour les sommets partant de this
    if(param==1)
    {

        for(int i=0; i<m_out.size(); i++)
       {
            for(int j=0; j<x.m_in.size(); j++)
            {
                if(m_out[i]==x.m_in[j])
                {
                    return true;
                }


                else
                    linked= false;
            }
        }
    }
    /// est liée pour les sommets arrivant sur this
    if(param==0)
    {

        for(int i=0; i<m_in.size(); i++)
        {
            for(int j=0; j<x.m_out.size(); j++)
            {
                if(m_in[i]==x.m_out[j])
                {
                    return true;

                }

                else
                    linked= false;
            }
        }
    }

    return linked;
}

void Vertex::Cacher_Sommet()
{

    m_interface->m_top_box.remove_child(m_interface->m_img);
//    m_interface->m_top_box.remove_child(m_interface->m_tools_box);
    m_interface->m_top_box.remove_child(m_interface->m_slider_value);
    m_interface->m_top_box.remove_child(m_interface->m_box_label_idx);
    m_interface->m_top_box.remove_child(m_interface->m_label_value);
    // m_interface->m_top_box.remove_child(m_interface->m_tools_button);
    m_interface->m_top_box.set_dim(0,0);


}


void Vertex::Afficher_Somet()
{
    m_interface->m_top_box.add_child( m_interface->m_img );

    m_interface->m_top_box.add_child(m_interface->m_slider_value);

    m_interface->m_top_box.add_child(m_interface->m_label_value);




    //   m_interface->m_top_box.add_child(m_interface->m_tools_box);

    m_interface->m_top_box.add_child(m_interface-> m_box_label_idx );

    m_interface->m_box_label_idx.set_pos(115,90);
    m_interface->m_img.set_pos(30,0);
    m_interface->m_top_box.set_dim(130, 100);

    m_interface->m_top_box.set_border(2);

    /* m_interface->m_top_box.add_child(m_interface->m_tools_button);

         m_interface->m_top_box.remove_child(m_interface->m_tools_box);
         m_interface->m_tools_box.remove_child(m_interface->m_tools_label);
        m_interface-> m_tools_box.remove_child(m_interface->m_button_cacher);
        m_interface-> m_tools_box.remove_child(m_interface->m_label_cacher);
      m_interface-> m_tools_box.remove_child(m_interface->m_button_edit);
        m_interface-> m_tools_box.remove_child(m_interface->m_label_edit);*/
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
    m_slider_weight.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

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
}


/// afficher ou masquer des arretes

void Edge::hide_edge_out()
{

    m_interface->m_top_edge.remove_child(m_interface->m_box_edge);
    m_interface->m_top_edge.detach_to();

}

void Edge::hide_edge_in()
{

    m_interface->m_top_edge.remove_child(m_interface->m_box_edge);
    m_interface->m_top_edge.detach_from();
}
void Edge::Afficher_Edges(Vertex& from, Vertex& to)
{

    m_interface->m_top_edge.attach_from(from.m_interface->m_top_box);
    m_interface->m_top_edge.attach_to(to.m_interface->m_top_box);
    m_interface-> m_top_edge.reset_arrow_with_bullet();

    m_interface->m_top_edge.add_child(m_interface->m_box_edge);

}

/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_top_box.set_bg_color(VERTFLUO);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,730);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);
    m_main_box.add_child(m_ordre_graph);
    m_ordre_graph.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);


    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,730);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_tool_box.add_child(m_savebutton);
    m_savebutton.set_dim(45,30);
    m_savebutton.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Up);
    m_savebutton.set_bg_color(ROUGE);
    m_savebutton.add_child(m_savebutton_text);
    m_savebutton_text.set_message("save");
    m_savebutton_text.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);

    m_tool_box.add_child(m_retour);
    m_retour.set_dim(50,50);
    m_retour.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Down);
    m_retour.set_border(0);
    m_retour.add_child(m_retour_img);
    m_retour_img.set_pic_name("retour.bmp");
    m_retour_img.set_pic_idx(0);
    m_retour_img.set_border(0);
    m_retour_img.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Down);


    m_tool_box.add_child(m_cmp_fconnexe);
    m_cmp_fconnexe.set_dim(70,30);
    m_cmp_fconnexe.set_gravity_x(grman::GravityX::Center);
    m_cmp_fconnexe.set_posy(40);
    m_cmp_fconnexe.set_bg_color(ROUGE);
    m_cmp_fconnexe.add_child(m_cmp_fconnexe_text1);
    m_cmp_fconnexe.add_child(m_cmp_fconnexe_text2);
    m_cmp_fconnexe.add_child(m_cmp_fconnexe_text3);
    m_cmp_fconnexe_text1.set_message("cmp");
    m_cmp_fconnexe_text2.set_message("fortement");
    m_cmp_fconnexe_text3.set_message("connexe");
    m_cmp_fconnexe_text1.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Up);
    m_cmp_fconnexe_text2.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);
    m_cmp_fconnexe_text3.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Down);
    //

    m_tool_box.set_bg_color(BLANCBLEU);


}


/// Méthode spéciale qui construit un graphe arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de chargement de fichiers par exemple.
/// Bien sûr on ne veut pas que vos graphes soient construits
/// "à la main" dans le code comme ça.
void Graph::make_example()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    /// Les sommets doivent être définis avant les arcs
    // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...
    add_interfaced_vertex(0, 29, 0, 0, "clown2.jpg");
    add_interfaced_vertex(1, 60.0, 400, 100, "clown2.jpg");
    add_interfaced_vertex(2,  50.0, 200, 300, "clown3.jpg");
    add_interfaced_vertex(3,  0.0, 400, 300, "clown4.jpg");
    add_interfaced_vertex(4,  100.0, 600, 300, "clown5.jpg");
    add_interfaced_vertex(5,  0.0, 100, 500, "bad_clowns_xx3xx.jpg", 0);
    add_interfaced_vertex(6,  0.0, 300, 500, "bad_clowns_xx3xx.jpg", 1);
    add_interfaced_vertex(7,  0.0, 500, 500, "bad_clowns_xx3xx.jpg", 2);

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


void Graph::make_graph_1()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);

    Graph::charger("graph1");
    m_nomgraph ="graph1";

    //affichage de l'ordre du graph dans la main box
    m_interface->m_ordre_graph.set_message("ordre graph: " + std::to_string(ordre));

    /*add_interfaced_vertex(0,50.0,100,100,"requin.jpg");
     add_interfaced_vertex(1, 60.0, 100, 200, "thon.jpg");
     add_interfaced_vertex(2, 60.0, 100, 300, "maquerau.jpg");
     add_interfaced_vertex(3, 60.0, 100, 400, "petit_poisson.jpg");
     add_interfaced_vertex(4, 60.0, 100, 500, "langoustine.jpg");
     add_interfaced_vertex(5, 60.0, 100, 350, "orga_uni.jpg");



     add_interfaced_edge(0, 0, 1, 50.0);
     add_interfaced_edge(1, 1, 2, 20.0);
     add_interfaced_edge(2, 1, 3, 20.0);
     add_interfaced_edge(3, 2, 4, 20.0);
     add_interfaced_edge(4, 3, 4, 20.0);
     add_interfaced_edge(5, 4, 5, 20.0);
    */

}

void Graph::addVertex()
{
    int indxVertex,posX, posY, indxEdge, vertexIn, vertexOut;
    double poidEdge,poidVertex;




}

void Graph::supprimerVertex()
{

    std::map<int,Vertex>::iterator it;

}

void Graph::charger(std::string graphName)
{

    std::ifstream fichier (graphName+".txt",std::ios::in);
    int indxVertex,posX, posY, indxEdge, vertexIn, vertexOut;
    double poidEdge,poidVertex;
    std::string picName;


    if (fichier)
    {

        fichier >> Graph::ordre;

        fichier >> Graph::nbrEdge;
        std::cout<< nbrEdge;
        for(int i=0 ; i < ordre ; i++)
        {

            fichier >> poidVertex;
            fichier >> posX;
            fichier >> posY;
            fichier >> picName;

            add_interfaced_vertex(i,poidVertex,posX,posY,picName+".jpg");
        }
        for(int j=0 ; j < nbrEdge ; j++)
        {

            fichier >> vertexIn;
            fichier >> vertexOut;
            fichier >> poidEdge;
            add_interfaced_edge(j,vertexIn,vertexOut,poidEdge);


        }


        fichier.close();
    }

}

void Graph::sauvgarder(std::string graphName)
{

    std::ofstream fichier(graphName+".txt",std::ios::out | std::ios::trunc);
    std::string picName;
    if(fichier)
    {
        fichier << Graph::ordre <<std::endl;
        fichier << Graph::nbrEdge<<std::endl;

        for(auto &elt : m_vertices)
        {
            fichier << elt.second.m_value<<" ";
            fichier <<elt.second.m_interface->m_top_box.get_frame_pos().x<<" ";
            fichier <<elt.second.m_interface->m_top_box.get_frame_pos().y<<" ";
            picName=elt.second.m_interface->m_img.get_pic_name();
            picName.erase(picName.size()-4,4);
            fichier <<picName<<std::endl;
        }
        for(auto &elt : m_edges)
        {

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
    if(grman::mouse_click && m_interface->m_savebutton.is_mouse_over())
    {
        sauvgarder(m_nomgraph) ;
        visuelle_forte_connexite(0);

    }
    if(grman::mouse_click && m_interface->m_retour.is_mouse_over())
    {
        m_quitter= 1;

    }
    ///partie qui gère l'affichege des composantes fortement connexe
    if(grman::mouse_unclick&1 && m_interface->m_cmp_fconnexe.is_mouse_over())
    {

        if(m_interface->m_cmp_fconnexe.get_value())
        {

            search_all_cmpfc();
            visuelle_forte_connexite(1);


            //l'interface est initialisé ici car on veur qu'il disparaisse.

            m_interface->m_tool_box.add_child(m_interface->m_afficher_graphreduit);
            m_interface->m_afficher_graphreduit.set_dim(70,30);
            m_interface->m_afficher_graphreduit.set_gravity_x(grman::GravityX::Center);
            m_interface->m_afficher_graphreduit.set_posy(74);
            m_interface->m_afficher_graphreduit.set_bg_color(ROUGECLAIR);
            m_interface->m_afficher_graphreduit.add_child(m_interface->m_afficher_graphreduit_text1);
            m_interface->m_afficher_graphreduit.add_child(m_interface->m_afficher_graphreduit_text2);
            m_interface->m_afficher_graphreduit_text1.set_gravity_xy(grman::GravityX::Center,grman::GravityY::Up);
            m_interface->m_afficher_graphreduit_text2.set_gravity_xy(grman::GravityX::Center,grman::GravityY::Center);
            m_interface->m_afficher_graphreduit_text1.set_message("Graph");
            m_interface->m_afficher_graphreduit_text2.set_message("réduit");
            m_interface->m_afficher_graphreduit_text1.set_posy(m_interface->m_afficher_graphreduit_text1.get_posy()+4);
            m_interface->m_afficher_graphreduit_text2.set_posy(m_interface->m_afficher_graphreduit_text2.get_posy()+4);


            m_interface->m_tool_box.add_child(m_interface->m_cmp_fconnexe_off);
            m_interface-> m_cmp_fconnexe_off.set_dim(70,30);
            m_interface-> m_cmp_fconnexe_off.set_gravity_x(grman::GravityX::Center);
            m_interface-> m_cmp_fconnexe_off.set_posy(110);
            m_interface-> m_cmp_fconnexe_off.set_bg_color(ROUGECLAIR);
            m_interface-> m_cmp_fconnexe_off.add_child(m_interface->m_cmp_fconnexe_off_text1);
            m_interface-> m_cmp_fconnexe_off_text1.set_message("Off");
            m_interface->m_tool_box.add_child(m_interface->m_nb_cmpfc);
            m_interface->m_nb_cmpfc.set_dim(70,30);
            m_interface->m_nb_cmpfc.set_posy(150);
            m_interface->m_nb_cmpfc.set_message("nb cmp:" + std::to_string(m_tabcmpfc.size()));





        }
m_interface->m_cmp_fconnexe.set_value(!m_interface->m_cmp_fconnexe.get_value());

    }

    if(grman::mouse_unclick&1 && m_interface->m_afficher_graphreduit.is_mouse_over())
    {
         Afficher_graphReduit(1);
    }

    if(grman::mouse_unclick&1 && m_interface->m_cmp_fconnexe_off.is_mouse_over())
    {
        visuelle_forte_connexite(0);
        Afficher_graphReduit(0);
        m_interface->m_tool_box.remove_child(m_interface->m_cmp_fconnexe_off);
        m_interface->m_tool_box.remove_child(m_interface->m_nb_cmpfc);
        m_interface->m_tool_box.remove_child(m_interface->m_afficher_graphreduit);

    }


    return 0;

}

int Graph::get_quitter()
{
    return m_quitter;
}

void Graph::set_quitter(bool x)
{
    m_quitter=x;
}

void Graph::destroy_graph()
{

    for(std::map<int,Vertex>::iterator it= m_vertices.begin(); it!=m_vertices.end(); it++)
    {
        m_interface->m_main_box.remove_child(it->second.m_interface->m_top_box);

    }

    m_vertices.clear();

    for(std::map<int,Edge>::iterator et= m_edges.begin(); et!=m_edges.end(); et++)
    {
        m_interface->m_main_box.remove_child(et->second.m_interface->m_top_edge);


    }
    m_edges.clear();

    m_interface.reset();
    m_interface=nullptr;


}

/// permet de démarquer tout les vertex

void Graph::Reset_marquage_vertex()
{
    for(std::map<int,Vertex>::iterator it=m_vertices.begin(); it!=m_vertices.end(); it++)
    {
        it->second.set_marque(0);
    }
}


void Graph :: Reset_marquage_marqued_connexeinout()
{
    for(std::map<int,Vertex>::iterator it=m_vertices.begin(); it!=m_vertices.end(); it++)
    {
        it->second.set_marque_connexeout(0);
        it->second.set_marque_connexein(0);
    }
}

void Graph:: Reset_marquage_isincompf_connexeinout()
{
    for(std::map<int,Vertex>::iterator it=m_vertices.begin(); it!=m_vertices.end(); it++)
    {
        it->second.set_connexein(0);
        it->second.set_connexeout(0);
    }
}


/// methode qui renvoit l'indice de l'arete qui relie les deux sommets en parametre
int Graph::findEdge(int sfrom, int sto)
{
    int s1=0;
    int s2=0;

    int idx=0;

    /// parcourt la map d'arete
    for(auto &elt : m_edges)
    {
        /// accede à m-from et m_to
        s1= elt.second.m_from;
        s2= elt.second.m_to;

        /// si les sommets s1 et s2 sont les meme que les sommets en parametres on retourne la valeur de l'arete (coeff)
        if((s1==sfrom && s2==sto))
        {
            idx= elt.first;

            return idx;
        }
        else
        {
            return INFINI;
        }
    }
}




/// Recherche d'une composante fortement connexe


std::vector<Vertex*> Graph:: Cmp_fort_connexe_serach(Vertex s)
{


    std::vector<Vertex*> c ; // la composante fortement connexe

    bool add=true;


    m_vertices[s.get_idx()].set_connexeout(true);
    m_vertices[s.get_idx()].set_connexein(true);

    for(int i=0; i<m_vertices[1].m_in.size();i++)
    {
        //std::cout << m_vertices[1].m_out[i];




    }



    while(add)
    {
        add=0;
        for(int i=0; i<ordre; i++)
        {
            if(!m_vertices[i].get_marque_connexeout() && m_vertices[i].get_connexeout())
            {
                m_vertices[i].set_marque_connexeout(true);

                for(int k=0; k<ordre; k++)
                {
                    if(m_vertices[i].islinked(m_vertices[k],1)&& !m_vertices[k].get_marque_connexeout())
                    {

                        m_vertices[k].set_connexeout(true);
                        add=1;


                    }
                }
            }
        }
    }



    add=true;
    while(add)
    {
        add=0;
        for(int i=0; i<ordre; i++)
        {
            if(!m_vertices[i].get_marque_connexein() && m_vertices[i].get_connexein() )
            {
                m_vertices[i].set_marque_connexein(true);

                for(int k=0; k<ordre; k++)
                {
                    if(m_vertices[i].islinked(m_vertices[k],0) && !m_vertices[k].get_marque_connexein())
                    {

                        m_vertices[k].set_connexein(true);
                        add=1;

                    }
                }
            }
        }
    }

    for (int z=0 ; z<ordre; z++)
    {
        if(m_vertices[z].get_connexein() && m_vertices[z].get_connexeout() && !m_vertices[z].get_marque())
        {
            c.push_back(new Vertex(m_vertices[z]));
            m_vertices[z].set_marque(true);



        }
    }
//std::cout << c.size();
    return c;
}

std::vector<std::vector<Vertex*>> Graph::search_all_cmpfc()
{
    Reset_marquage_vertex();
    Reset_marquage_marqued_connexeinout();
    Reset_marquage_isincompf_connexeinout();
    m_tabcmpfc.clear();



    bool* marquage= new bool [m_vertices.size()];
    for (int i =0; i<m_vertices.size(); i++)
    {
        marquage[i]=false;
    }

    for(int i=0; i<ordre; i++)
    {
        if(!marquage[i])
        {
            m_tabcmpfc.push_back( Cmp_fort_connexe_serach(m_vertices[i]));
            marquage[i]=true;

            for(int k=0; k<m_tabcmpfc.back().size(); k++)
            {


                marquage[m_tabcmpfc.back()[k]->get_idx()] = true;

            }
        }

    }


    for(int i=0; i<m_tabcmpfc.size(); i++)
    {
        for(int k=0; k<m_tabcmpfc[i].size(); k++)
        {
            std::cout << m_tabcmpfc[i][k]->get_idx();
        }
        std::cout << std::endl;
    }

    return m_tabcmpfc;
}






void Graph:: visuelle_forte_connexite(bool activate)
{
    int color;
    if(activate)
    {

        for(int i=0; i<m_tabcmpfc.size(); i++)
        {
            color= COULEURALEATOIRECLAIR;

            for(int k=0; k<m_tabcmpfc[i].size(); k++)
            {
                m_tabcmpfc[i][k]->m_interface->m_top_box.set_border_color(color);
                m_tabcmpfc[i][k]->m_interface->m_top_box.m_isincmpf=true;  // paramètre qui permet de sélectioner quel get_color_bg() utiliser.

               /* if(k<m_tabcmpfc[i].size()-1)
                {
                   // if(findEdge(m_tabcmpfc[i][k]->get_idx(),m_tabcmpfc[i][k+1]->get_idx())< INFINI)
                    {
                      std::cout << findEdge(m_tabcmpfc[i][k]->get_idx(),m_tabcmpfc[i][k+1]->get_idx());
                     m_edges[findEdge(m_tabcmpfc[i][k]->get_idx(),m_tabcmpfc[i][k+1]->get_idx())].m_interface->m_top_edge.set_colorEdge(color);
                     m_edges[findEdge(m_tabcmpfc[i][k]->get_idx(),m_tabcmpfc[i][k+1]->get_idx())].m_interface->m_box_edge.set_bg_color(color);

                    }
                 //   else
                    {
                    // m_edges[findEdge(m_tabcmpfc[i][k+1]->get_idx(),m_tabcmpfc[i][k]->get_idx())].m_interface->m_top_edge.set_colorEdge(color);
                    // m_edges[findEdge(m_tabcmpfc[i][k+1]->get_idx(),m_tabcmpfc[i][k]->get_idx())].m_interface->m_box_edge.set_bg_color(color);

                    }


                    // std::cout<< findEdge(m_tabcmpfc[i][k]->get_idx(),m_tabcmpfc[i][k+1]->get_idx());
                }





            }
                  // on sort de la boucle pour la dernière arrete afin de ne pas faire de dépassement mémoire

                    /*if(findEdge(m_tabcmpfc[i][m_tabcmpfc[i].size()-1]->get_idx(),m_tabcmpfc[i][0]->get_idx())!=INFINI)
                    {
                     m_edges[findEdge(m_tabcmpfc[i][m_tabcmpfc[i].size()-1]->get_idx(),m_tabcmpfc[i][0]->get_idx())].m_interface->m_top_edge.set_colorEdge(color);
                     m_edges[findEdge(m_tabcmpfc[i][m_tabcmpfc[i].size()-1]->get_idx(),m_tabcmpfc[i][0]->get_idx())].m_interface->m_box_edge.set_bg_color(color);
                    }
                    else
                    {
                     m_edges[findEdge(m_tabcmpfc[i][0]->get_idx(),m_tabcmpfc[i][m_tabcmpfc[i].size()-1]->get_idx())].m_interface->m_top_edge.set_colorEdge(color);
                     m_edges[findEdge(m_tabcmpfc[i][0]->get_idx(),m_tabcmpfc[i][m_tabcmpfc[i].size()-1]->get_idx())].m_interface->m_box_edge.set_bg_color(color);
                    }*/
                    //  std::cout<< findEdge(2,0);*/


        }






    }
}

    else
    {
        for(int i=0; i<m_tabcmpfc.size(); i++)
        {

            for(int k=0; k<m_tabcmpfc[i].size(); k++)
            {

                m_tabcmpfc[i][k]->m_interface->m_top_box.m_isincmpf=false;

            }

        }
    }




}



void Graph::Afficher_graphReduit(bool activate)
{

    if(activate)
    {
        for(int k=0; k<m_tabcmpfc.size(); k++)
        {
            m_interface->m_tab_cmp_GraphReduit.push_back(new grman::WidgetBox);
            m_interface->m_tab_texte_GraphReduit.push_back(new grman::WidgetText);

            if(k<m_tabcmpfc.size()-1)
            {
                m_interface->m_tab_edge_GraphReduit.push_back(new grman::WidgetEdge);
            }



        }





        for(int i=0; i<m_interface->m_tab_cmp_GraphReduit.size(); i++)
        {

            m_interface->m_main_box.add_child(*m_interface->m_tab_cmp_GraphReduit[i]);
            m_interface->m_tab_cmp_GraphReduit[i]->set_pos(m_tabcmpfc[i][0]->m_interface->m_top_box.get_posx(),m_tabcmpfc[i][0]->m_interface->m_top_box.get_posy());
            m_interface->m_tab_cmp_GraphReduit[i]->set_dim(130,100);
            m_interface->m_tab_cmp_GraphReduit[i]->set_bg_color(ROUGESOMBRE);
            m_interface->m_tab_cmp_GraphReduit[i]->add_child(*m_interface->m_tab_texte_GraphReduit[i]);
            m_interface->m_tab_texte_GraphReduit[i]->set_gravity_xy(grman::GravityX::Center,grman::GravityY::Center);
            m_interface->m_tab_texte_GraphReduit[i]->set_message("cmpfconexe n°" + std::to_string(i));


            if(i< m_interface->m_tab_edge_GraphReduit.size())
            {
                m_interface->m_main_box.add_child(*m_interface->m_tab_edge_GraphReduit[i]);
                m_interface->m_tab_edge_GraphReduit[i]->attach_from(m_tabcmpfc[i][0]->m_interface->m_top_box);
                m_interface->m_tab_edge_GraphReduit[i]->attach_to(m_tabcmpfc[i+1][0]->m_interface->m_top_box);
                m_interface->m_tab_edge_GraphReduit[i]->reset_arrow_with_bullet();

            }








            /* for(int k=0; k<m_tabcmpfc[i].size(); k++)
             {
                 if(i<m_tabcmpfc[i].size()-1)
                 {
                     if (m_tabcmpfc[i][k]->islinked(*m_tabcmpfc[i+1][k],1))
                     {
                         m_interface->m_main_box.add_child(*m_interface->m_tab_cmp_GraphReduit[i]);
                         m_interface->m_tab_cmp_GraphReduit[i]->set_pos(m_tabcmpfc[i][k]->m_interface->m_top_box.get_posx(),m_tabcmpfc[i][k]->m_interface->m_top_box.get_posy());
                         m_interface->m_tab_cmp_GraphReduit[i]->set_dim(130,100);
                         m_interface->m_tab_cmp_GraphReduit[i]->set_bg_color(ROUGESOMBRE);
                         break;
                     }


                 }


                /* else
                 {
                     if (m_tabcmpfc[i][k]->islinked(*m_tabcmpfc[0][k],1))
                     {
                         m_interface->m_main_box.add_child(*m_interface->m_tab_cmp_GraphReduit[i]);
                         m_interface->m_tab_cmp_GraphReduit[i]->set_pos(m_tabcmpfc[i][k]->m_interface->m_top_box.get_posx(),m_tabcmpfc[i][k]->m_interface->m_top_box.get_posy());
                         m_interface->m_tab_cmp_GraphReduit[i]->set_dim(130,100);
                         m_interface->m_tab_cmp_GraphReduit[i]->set_bg_color(ROUGESOMBRE);
                         break;
                     }


                 }*/





        }


        for(int i=0; i<m_tabcmpfc.size(); i++)
        {
            for(int k=0; k<m_tabcmpfc[i].size(); k++)
            {

                {
                    m_tabcmpfc[i][k]->Cacher_Sommet();
                    for(int z=0; z<m_tabcmpfc[i][k]->m_in.size(); z++)
                    {
                        m_edges[m_tabcmpfc[i][k]->m_in[z]].hide_edge_in();
                    }
                    for(int z=0; z<m_tabcmpfc[i][k]->m_out.size(); z++)
                    {
                        m_edges[m_tabcmpfc[i][k]->m_out[z]].hide_edge_out();
                    }


                }

            }
        }
    }


    else
    {

        for(int i=0; i<m_vertices.size(); i++)
        {
           m_vertices[i].Afficher_Somet();
        }

        for(int l=0; l<m_edges.size(); l++)
        {
             m_edges[l].Afficher_Edges(m_vertices[m_edges[l].m_from],m_vertices[m_edges[l].m_to]);
        }



        for(int k=0; k<m_interface->m_tab_cmp_GraphReduit.size(); k++)
        {

            m_interface->m_main_box.remove_child(*m_interface->m_tab_cmp_GraphReduit[k]);

            delete m_interface->m_tab_cmp_GraphReduit[k];
            delete m_interface->m_tab_texte_GraphReduit[k];

            if(k<m_interface->m_tab_cmp_GraphReduit.size()-1)
            {

              m_interface->m_main_box.remove_child(*m_interface->m_tab_edge_GraphReduit[k]);
            delete m_interface->m_tab_edge_GraphReduit[k];
            }



        }
            m_interface->m_tab_cmp_GraphReduit.clear();
            m_interface->m_tab_texte_GraphReduit.clear();
            m_interface->m_tab_edge_GraphReduit.clear();
    }




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
    menugraph();
    m_interface->m_top_box.update();


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

    m_vertices[idx].set_idx(idx);
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
}


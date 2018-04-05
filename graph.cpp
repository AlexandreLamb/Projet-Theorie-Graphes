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
    m_slider_value.set_range(0.0, 100.0);  // Valeurs arbitraires, � adapter...
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
    /// est li�e pour les sommets partant de this
    if(param==1)
    {

        for(int i=0; i<m_out.size(); i++)
        {
            for(int j=0; j<x.m_in.size(); j++)
            {
                if(m_out[i]==x.m_in[j])
                {
                    linked=true;
                }


                else
                    linked= false;
            }
        }
    }
    /// est li�e pour les sommets arrivant sur this
    if(param==0)
    {

        for(int i=0; i<m_out.size(); i++)
        {
            for(int j=0; j<x.m_in.size(); j++)
            {
                if(m_out[i]==x.m_in[j])
                {
                    linked=true;

                }

                else
                    linked= false;
            }
        }
    }

    return linked;
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
    m_slider_weight.set_range(0.0, 100.0);  // Valeurs arbitraires, � adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

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
}



/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de pr�parer un cadre d'accueil des
/// �l�ments qui seront ensuite ajout�s lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_top_box.set_bg_color(VERTFLUO);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,730);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);

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


void Graph::make_graph_1()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);

    Graph::charger("graph1");
    m_nomgraph ="graph1";


    /* add_interfaced_vertex(0,50.0,100,100,"requin.jpg");
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
        sauvgarder(m_nomgraph);
    }
    if(grman::mouse_click && m_interface->m_retour.is_mouse_over())
    {
        return 1;
    }

    if(grman::mouse_unclick&1 && m_vertices[1].m_interface->m_top_box.is_mouse_over())
    {


       search_all_cmpfc();


    }
    return 0;

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

/// permet de d�marquer tout les vertex

void Graph::Reset_marquage_vertex()
{
    for(std::map<int,Vertex>::iterator it=m_vertices.begin(); it!=m_vertices.end(); it++)
    {
        it->second.set_marque(0);
    }
}


 void Graph :: Reset_marquage_connexe_inout()
 {
     for(std::map<int,Vertex>::iterator it=m_vertices.begin(); it!=m_vertices.end(); it++)
    {
        it->second.set_marque_connexeout(0);
        it->second.set_marque_connexein(0);
    }
 }



/// Recherche d'une composante fortement connexe


std::vector<Vertex*> Graph:: Cmp_fort_connexe_serach(Vertex s)
{


    std::vector<Vertex*> c ; // la composante fortement connexe

    bool add=true;


    m_vertices[s.get_idx()].set_connexeout(true);
    m_vertices[s.get_idx()].set_connexein(true);

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
                    if(m_vertices[i].islinked(m_vertices[k],1) && !m_vertices[k].get_marque_connexeout())
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
                        add=1;//std::cout << m_vertices[k].get_idx();
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

   /* for(int i=0; i<c.size(); i++)
    {
          std::cout << c[i]->get_idx();

    }
    std::cout << std::endl;*/

    return c;
}

void Graph::search_all_cmpfc()
{
   // Reset_marquage_vertex();
   // Reset_marquage_connexe_inout();
    std::vector<std::vector<Vertex*>> tabcmpfc;


    bool* marquage= new bool [m_vertices.size()];
    for (int i =0; i<m_vertices.size(); i++)
    {
        marquage[i]=false;
    }

    for(int i=0; i<ordre; i++)
    {
        if(!marquage[i])
        {
            tabcmpfc.push_back( Cmp_fort_connexe_serach(m_vertices[i]));
            marquage[i]=true;

            for(int k=0; k<tabcmpfc.back().size(); k++)
            {
                /*if(tabcmpfc.back()[k]->get_connexein() && tabcmpfc.back()[k]->get_connexeout() && !marquage[k])
                {
                    marquage[k]=true;

                }*/

                marquage[tabcmpfc.back()[k]->get_idx()] = true;

            }
        }

    }


    for(int i=0; i<tabcmpfc.size(); i++)
    {
        for(int k=0; k<tabcmpfc[i].size(); k++)
        {
            std::cout << tabcmpfc[i][k]->get_idx();
        }
        std::cout << std::endl;
    }
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

    m_vertices[idx].set_idx(idx);
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
}


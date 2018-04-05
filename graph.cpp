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
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_top_box.set_bg_color(VERTFLUO);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);

    m_main_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);
    m_tool_box.add_child(m_savebutton);
    m_savebutton.set_dim(35,20);
    m_savebutton.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_savebutton.set_bg_color(ROUGE);
    m_savebutton.add_child(m_savebutton_text);
    m_savebutton_text.set_message("save");
    m_savebutton_text.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);

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


void Graph::make_graph_1(){
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);

    Graph::charger("graph1");


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

///zoe : sous prgramme qui gère partie fonctinnel sans affichage
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
    bool mode_flux=false; // savoir si bouton mode flux est actif
    int nb=0;
    int a = 0;

    mode_flux = true; // savoir si appuyer sur bouton mode flux

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
                    /// on recupere le nombre de ses predecesseurs
                    nb=m_vertices[k].m_out.size();

                    std::cout << "nb de pred est: "<< nb <<std::endl;

                    /// pour tous ces pred on cherche l'arete qui le relie avec el sommet
                    for(int i=0; i<nb; i++)
                    {
                        std::cout << "rentree "<< indx <<std::endl;
                      indx=m_vertices[k].m_out[i];
                      std::cout << "l'index du sommet est: "<< indx <<std::endl;

                      /// on cherche arete de ce sommet à ce pred
                        a=PredSucc(k, i);
                      ///coeff=
                     /// K=K+(coeff*nb);
                    }

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

    std::map<int,Vertex>::iterator it;

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

            fichier << elt.second.m_from<<" ";
            fichier << elt.second.m_to<<" ";
            fichier << elt.second.m_weight<<std::endl;

        }
        fichier.close();
        std::cout<<"Sauvgarde done";
        }

}

void Graph::menugraph()
{
    if(grman::mouse_click && m_interface->m_savebutton.is_mouse_over())
    {
        sauvgarder("graph1");
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

    m_interface->m_top_box.update();
    menugraph();

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

    m_vertices[id_vert1].m_in.push_back(idx);
    m_vertices[id_vert2].m_in.push_back(idx);

}

/// methode qui rencoit l'indice de l'arete qui relie les deux sommets en parametre
int Graph::PredSucc(int sfrom, int sto)
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
       if((s1==sfrom && s2==sto) || (s1==sto && s2==sfrom) )
       {
           poids= elt.second.m_weight;
           return poids;
       }
    }
}

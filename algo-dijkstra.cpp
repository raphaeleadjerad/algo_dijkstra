////////////////////////////////////////////////////////////////
//   Programmme de l'algorithme de Dijkstra utilisant la STL  //
///////////////////////////////////////////////////////////////

#include<bits/stdc++.h> // Includes every standard library
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <cmath>
#include "projet-R2.hpp"
using namespace std;
# define INF 0x3f3f3f3f //donne une adresse a la variable infini

///////////////////////////////
//     TRACE GRAPHE          //
///////////////////////////////
vector<R2> WriteCoordinates(int nx,int ny,double delta)
{
  vector<R2> noeuds;
  for(double x=0;x<=nx;x+=delta)
    {
      for (double y=0; y<=ny;y+=delta)
	{
	  R2 noeud;
	  noeud.x = x;
	  noeud.y = y;
	  noeuds.push_back(noeud);
        }	  
    }
  return noeuds;
}
double height(double a, double b)
{
  double height;
  double x=a*2 - 1;
  double y = b*2 - 1;
  height = sin(x)*sin(y)*exp(-x*x-y*y+x*y)*100;
  return height;
}
// Cette fonction va creer un tableau avec les noms des noeuds qui communiquent et le cout qui les separe
map<pair<int,int>,double> MakeGraph(vector<R2> noeuds,double distanceNoeud)
{
  map<pair<int,int>,double> graphe;
  for(int i=0;i<noeuds.size();++i)
    {
      for(int j=i;j< noeuds.size();++j)
	{
	   if(abs((noeuds[i]-noeuds[j]).norm())< distanceNoeud)
	     {
	       double disi = height(noeuds[i].x,noeuds[i].y);
	       double disj= height(noeuds[j].x,noeuds[j].y);
	       double distance1 =abs(floor(disi)-floor(disj));
	       double distance2 = abs(floor((noeuds[i]-noeuds[j]).norm()*1000));
	       double cost = distance1 +distance2;
	       graphe.insert({{i,j},cost});
	     }	   
	}
    }
  return graphe;
}


  
///////////////////////////////
//        CLASS GRAPHE       //
///////////////////////////////

class Graph
{

  int V;    // Nombre de noeuds
 
  /** Stockage des couts et les noeuds du graphe dans une liste **/
  
  list< pair<int, int> > *adj;
  // Pointeur sur une liste chainee de paires d'entiers, attention le premier est le numero du noeud avec lequel il est relie et le deuxieme est le poids de ce noeud par rapport a l'indice
public:
  Graph(int V);  // Constructeur du graphe
  
 
  // Fonction permettant d'ajouter une arrete entre deux noeuds u et v
  void addEdge(int u, int v, int w);
 
  // Imprime le cout du chemin le plus court depuis s jusqu'au noeud d'arrivee
  vector<int> shortestPath(int s, int noeudarrivee);

};
 
// Definition du constructeur :
// Allocation dynamique de  memoire pour la liste d'adjacence
Graph::Graph(int V) 
{
    this->V = V;
    adj = new list< pair<int, int> >[V];
}

// Fonction membre permettant d'ajouter des arretes
// On ajoute la paire (v,w) a la liste chainee ainsi que la paire (u,w)
void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w)); 
}
 
// Fonction membre permettant d'afficher le plus court chemin

vector<int> Graph::shortestPath(int src, int noeudarrivee)
{
  /* On cree un set (STL) permettant de stocker les noeuds par lesquelles on est 
     deja passe. Le set est un conteneur qui stocke des elements uniques, la valeur 
     d'un element est elle meme, sa clef. Les valeurs du set ne peuvent pas etre
     modifiees une fois dans le conteneur. Les set sont ordonnees, et ici grace 
     au fait que la distance est le premier element de la paire, c'est la distance
     qui ordonne les noeuds.*/
  
  set< pair<int, int> > setds; // la paire represente une distance, un noeud
 
    // Cree un vecteur de distance et initialise toutes les distances a l'infini
    vector<int> dist(V, INF);// V est le nombre d'arretes et INF est la valeur d'initialisation
    vector<int> antec(V,0);// Vector qui va stocker les antecedents dans le plus court chemin que l'on trouve
 
    // Insere la source (le point de depart) dans le set et initialise sa distance a 0
    setds.insert(make_pair(0, src));
    dist[src] = 0;
    
 
    /*La boucle continue tant que la plus courte distance 
      au point de depart n'a pas encore ete trouvee i.e. jusqu'a 
      ce que le set soit vide */
    while (!setds.empty())
    {
        
        // Le premier noeud  dans le set est le noeud situee a la distance minimum, on l'extrait alors du set
      pair<int, int> tmp = *(setds.begin()); //pointeur temporaire sur le debut du set
      setds.erase(setds.begin()); // on enleve le debut car il est a la plus courte distance de la ou l'on se trouve
 
        
      /* Le nom du noeud est stocke (on a enleve le debut du set et on stocke ce debut
	 dans une variable temporaire). Cela doit etre realise ainsi afin d'avoir 
	 les noeuds ranges dans un ordre croissant (ordre selon le premier element
	 de la paire, a savoir la distance).*/
      
      int u = tmp.second;//On cree un int qui contient le numero du noeud de depart
 
        // 'i' est utilise pour parcourir tous les noeuds de la liste chainee initiale 
      list< pair<int, int> >::iterator i; // Iterateur de mon conteneur liste
      for (i = adj[u].begin(); i != adj[u].end(); ++i) // On parcourt la liste chainee des noeuds du graphe, on parcourt sur un seul entier (on se souvient que chaque element de liste est une paire d'entier
        {
	  // On obtient le numero du noeud et le poids de l'element suivant dans la liste chainee 
	  int v = (*i).first; // Premier element de la paire, le numero du noeud
	  int weight = (*i).second; // Deuxieme element de la paire, le poids du noeud
 


	  // S'il existe un chemin plus court jusqu'a v a partir de la ou on est en passant par u :
	  if (dist[v] > dist[u] + weight)
	    /* Cette condition signifie que a partir du point de depart, le cout d'aller 
	     en u, plus le cout d'aller de u en v, est inferieur au cout d'aller du point 
	    de depart a v directement (cf LATEX)*/

            {
	      /* Si la distance jusqu'a v n'est pas INF alors il doit etre 
		 dans notre set, donc on l'enleve et on le remet avec une 
		 distance mise a jour. NOTE :On n'enleve du set que les arretes 
		 dont la distance est finie.*/
	      
                if (dist[v] != INF)
                    setds.erase(setds.find(make_pair(dist[v], v)));
 
                // Mise a jour de la distance a v
                dist[v] = dist[u] + weight;
		antec[v]=u;
                setds.insert(make_pair(dist[v], v));
            }
        }
    }
 
    // Imprimer la plus courte distance stockee dans dist[]


   
    cout << "Le cout total de votre trajet est :" << dist[noeudarrivee] << endl;
    cout << "Vous passez par les noeuds" << endl;
    vector<int> antecedents;
    cout<< "| " << antec[noeudarrivee] << " | ";
    antecedents.push_back(antec[noeudarrivee]);
    while(antec[noeudarrivee]!=0)
      {
	noeudarrivee=antec[noeudarrivee];
	cout << antec[noeudarrivee] << " | ";
	antecedents.push_back(antec[noeudarrivee]);
      }    
    return antecedents;
}

 
// Test de la methode
int main()
{
  // On ecrit le maillage a grapher
  vector<R2> noeuds = WriteCoordinates(1,1,0.25);

  map<pair<int,int>,double> graphe = MakeGraph(noeuds,0.4);

  string const nomFichier2("plot2.txt");
  ofstream monFlux2(nomFichier2.c_str());

   if(monFlux2)    
    {
      for(map<pair<int,int>,double>::iterator it =graphe.begin(); it!=graphe.end(); ++it)
	{
	  monFlux2 << (it->first).first << " " << (it->first).second << " " << it->second  << endl;
	}
    }
   	   else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }

   string const nomFichier3("plot3.txt");
   ofstream monFlux3(nomFichier3.c_str());

   if(monFlux3)    
    {
      for(map<pair<int,int>,double>::iterator it =graphe.begin(); it!=graphe.end(); ++it)
	{
	  double heighti = height(noeuds[(it->first).first].x,noeuds[(it->first).first].y);
	  double heightj = height(noeuds[(it->first).second].x,noeuds[(it->first).second].y);
	  if ((it->first).first!=(it->first).second)
	    {
	   monFlux3 << noeuds[(it->first).first].x << " " <<  noeuds[(it->first).first].y << " " << heighti << " X" << (it->first).first <<  endl;
	    }
	   monFlux3 << noeuds[(it->first).second].x << " " <<  noeuds[(it->first).second].y << " " << heightj << " X" << (it->first).second << endl;
	   monFlux3 << " " << endl;
	    
	}

	
    }
	   else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }
   
   
   
    // Cree un graphe
  int V =25;
  Graph g(V);

    
    ifstream monFlux("plot2.txt");  //Ouverture d'un fichier en lecture

    if(monFlux)
      {
	string ligne; //Une variable pour stocker les lignes lues

	while(getline(monFlux, ligne)) //Tant qu'on n'est pas «¢ la fin, on lit
	  {
	    int u,v;
	    double w;
	    monFlux >> u;
	    monFlux >> v;
	    monFlux >> w;
	    int weight = floor(w);
	    g.addEdge(u,v,weight);
	  }
      }
    else
      {
	cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
	}
    cout << "Nous partons du noeud 0" << endl;

    vector<int> antecedents;
    int noeudarrivee=0;
    cout << "Ou voulez vous aller? Entrez un noeud entre 0 et " << V-1 << endl;
    cin >> noeudarrivee;
    antecedents = g.shortestPath(0,noeudarrivee);
    

    string const nomFichier("plot4.txt");
    ofstream monFlux6(nomFichier.c_str());

    if(monFlux6)    
    {
      monFlux6 << noeudarrivee << endl;
      for(int i=0;i<antecedents.size();++i)
	monFlux6 << antecedents[i] << endl;
      monFlux6.close();
      
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }

    string const nomFichier4("plot4.txt");
   ifstream fichier4(nomFichier4.c_str());
   vector<int> chemin;
   if(fichier4)
   {
      cout << "Votre chemin est le suivant : " << endl;
      string contenu; 
     
      while(getline(fichier4, contenu))
      {
	int n ;
	n = stoi(contenu);
	chemin.push_back(n);
      }
      for(vector<int>::reverse_iterator it = chemin.rbegin(); 
        it != chemin.rend(); ++it)
	{
	  cout << " vous passez par le noeud " << *it << endl;
	}
      cout << "Vous etes arrives" << endl;
   }
   else
   {
      cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
   }
   

    string const nomFichier5("plot5.txt");
   ofstream monFlux5(nomFichier5.c_str());

   if(monFlux5)    
    {
        for(int i=0;i<chemin.size();++i)
	{
	  double heighti = height(noeuds[chemin[i]].x,noeuds[chemin[i]].y);
	  monFlux5 << noeuds[chemin[i]].x << " " << noeuds[chemin[i]].y << " "<< heighti << " X" << chemin[i] << endl;  
	}
    }
	   else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }  
    return 0;
}

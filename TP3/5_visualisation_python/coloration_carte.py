import networkx as nx
import matplotlib.pyplot as plt

class Graph:
    
    # Initialise le graphe avec N sommets
    def __init__(self, vertices):
        self.vertices = vertices
        # Crée une matrice d'adjacence N*N remplie de 0
        self.adjMatrix = [[0] * vertices for _ in range(vertices)]
        # Associe des étiquettes par défaut (0 -> "0", 1 -> "1", etc.)
        self.labels = {i: str(i) for i in range(vertices)} 

    # Ajoute une arête non-orientée entre deux sommets u et v
    def add_edge(self, u, v):
        self.adjMatrix[u][v] = 1
        self.adjMatrix[v][u] = 1

    # Permet de définir des étiquettes (noms) personnalisées pour les sommets
    def set_labels(self, labels_dict):
        """Associe un dictionnaire de noms aux IDs des sommets."""
        self.labels = labels_dict

    # Vérifie si le sommet v peut prendre la couleur c
    def peut_colorer(self, v, c, color):
        for i in range(self.vertices):
            # Si un voisin a déjà cette couleur, on ne peut pas
            if self.adjMatrix[v][i] == 1 and color[i] == c:
                return False
        return True

    # Exécute l'algorithme de coloration de Welsh-Powell
    def welsh_powell(self):
        # Calcule le degré de chaque sommet
        degree = [sum(row) for row in self.adjMatrix]
        vertices_degrees = [(i, degree[i]) for i in range(self.vertices)]
        
        # Trie les sommets par degré décroissant
        sorted_vertices = sorted(vertices_degrees, key=lambda x: x[1], reverse=True)

        # Initialise le tableau des couleurs (0 = non coloré)
        color = [0] * self.vertices
        couleur_actuelle = 1
        sommets_colores = 0

        print("\n--- Ordre de marquage (Welsh-Powell) ---")
        for i, (vertex_id, deg) in enumerate(sorted_vertices):
             print(f"{i+1}. Sommet {self.labels.get(vertex_id, vertex_id)} (ID: {vertex_id}) - Degre: {deg}")
        
        print("\n--- Processus de coloration ---")

        while sommets_colores < self.vertices:
            print(f"Application de la Couleur {couleur_actuelle} sur :")
            
            # Parcourt la liste triée des sommets
            for vertex, _ in sorted_vertices:
                # Si le sommet n'a pas de couleur
                if color[vertex] == 0:
                    # S'il peut prendre la couleur actuelle
                    if self.peut_colorer(vertex, couleur_actuelle, color):
                        color[vertex] = couleur_actuelle
                        sommets_colores += 1
                        print(f"   -> {self.labels.get(vertex, vertex)}")
            
            couleur_actuelle += 1
        
        num_colors = couleur_actuelle - 1

        print("\n--- Resultats de la Coloration ---")
        print(f"Graphe colore (Python) avec {num_colors} couleurs:")
        for c in range(1, num_colors + 1):
            # Regroupe les sommets par couleur pour l'affichage
            nodes_with_color = [self.labels.get(i, i) for i, col in enumerate(color) if col == c]
            print(f"   Couleur {c}: {nodes_with_color}")

        return color, num_colors

    # Dessine le graphe coloré en utilisant networkx et matplotlib
    def draw_colored_graph(self, color_map, num_colors):
        """Dessine le graphe avec les couleurs trouvées."""
        G = nx.Graph()
        G.add_nodes_from(range(self.vertices))
        # Ajoute les arêtes au graphe networkx
        for i in range(self.vertices):
            for j in range(i + 1, self.vertices):
                if self.adjMatrix[i][j] == 1:
                    G.add_edge(i, j)
        
        # Crée une palette de couleurs
        palette = plt.cm.get_cmap('rainbow', num_colors)
        node_colors = [palette(c - 1) for c in color_map]

        plt.figure(figsize=(10, 7))
        nx.draw(G, 
                labels=self.labels, 
                with_labels=True, 
                node_color=node_colors, 
                edge_color='gray',
                font_weight='bold',
                node_size=2000)
        plt.title("Carte d'Europe Coloree (Welsh-Powell)")
        plt.show()

# Données de la carte
labels_pays = {
    0: "Fr", 1: "Es", 2: "Po", 3: "An", 4: "It", 5: "Au",
    6: "Su", 7: "Al", 8: "Lu", 9: "Be", 10: "PB"
}
NB_PAYS = 11

# Liste des arêtes (frontières)
aretes_pays = [
    # France (0)
    (0, 1), (0, 3), (0, 4), (0, 6), (0, 7), (0, 8), (0, 9),
    # Espagne (1)
    (1, 2), (1, 3),
    # Italie (4)
    (4, 5), (4, 6),
    # Autriche (5)
    (5, 6), (5, 7),
    # Suisse (6)
    (6, 7),
    # Allemagne (7)
    (7, 8), (7, 9), (7, 10),
    # Luxembourg (8)
    (8, 9),
    # Belgique (9)
    (9, 10)
]

# Lancement
print("--- Lancement de la coloration de la carte d'Europe ---")
g_europe = Graph(NB_PAYS)
g_europe.set_labels(labels_pays)

# Ajoute toutes les arêtes au graphe
for u, v in aretes_pays:
    g_europe.add_edge(u, v)

# Lance la coloration et le dessin
colors, num_colors = g_europe.welsh_powell()
g_europe.draw_colored_graph(colors, num_colors)
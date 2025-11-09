# Fichier : TP3/coloration_carte.py (Corrigé)

import networkx as nx
import matplotlib.pyplot as plt

# --- PARTIE 1 : La classe Graph (de coloration_corrigee.py) ---
# -----------------------------------------------------------
class Graph:
    def __init__(self, vertices):
        self.vertices = vertices
        self.adjMatrix = [[0] * vertices for _ in range(vertices)]
        self.labels = {i: str(i) for i in range(vertices)} # Labels par défaut

    def add_edge(self, u, v):
        self.adjMatrix[u][v] = 1
        self.adjMatrix[v][u] = 1

    def set_labels(self, labels_dict):
        """Associe un dictionnaire de noms aux IDs des sommets."""
        self.labels = labels_dict

    def peut_colorer(self, v, c, color):
        for i in range(self.vertices):
            if self.adjMatrix[v][i] == 1 and color[i] == c:
                return False
        return True

    def welsh_powell(self):
        degree = [sum(row) for row in self.adjMatrix]
        vertices_degrees = [(i, degree[i]) for i in range(self.vertices)]
        
        sorted_vertices = sorted(vertices_degrees, key=lambda x: x[1], reverse=True)

        color = [0] * self.vertices
        couleur_actuelle = 1
        sommets_colores = 0

        print("\n--- Ordre de marquage (Welsh-Powell) ---")
        for i, (vertex_id, deg) in enumerate(sorted_vertices):
             print(f"{i+1}. Sommet {self.labels.get(vertex_id, vertex_id)} (ID: {vertex_id}) - Degre: {deg}")
        
        print("\n--- Processus de coloration ---")

        while sommets_colores < self.vertices:
            print(f"Application de la Couleur {couleur_actuelle} sur :")
            
            for vertex, _ in sorted_vertices:
                if color[vertex] == 0:
                    if self.peut_colorer(vertex, couleur_actuelle, color):
                        color[vertex] = couleur_actuelle
                        sommets_colores += 1
                        print(f"  -> {self.labels.get(vertex, vertex)}")
            
            couleur_actuelle += 1
        
        num_colors = couleur_actuelle - 1

        print("\n--- Resultats de la Coloration ---")
        print(f"Graphe colore (Python corrige) avec {num_colors} couleurs:")
        for c in range(1, num_colors + 1):
            nodes_with_color = [self.labels.get(i, i) for i, col in enumerate(color) if col == c]
            print(f"  Couleur {c}: {nodes_with_color}")

        return color, num_colors

    def draw_colored_graph(self, color_map, num_colors):
        """Dessine le graphe avec les couleurs trouvées."""
        G = nx.Graph()
        G.add_nodes_from(range(self.vertices))
        for i in range(self.vertices):
            for j in range(i + 1, self.vertices):
                if self.adjMatrix[i][j] == 1:
                    G.add_edge(i, j)
        
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

# --- PARTIE 2 : Les données de la carte (CORRIGEES) ---
# ----------------------------------------------------

labels_pays = {
    0: "Fr", 1: "Es", 2: "Po", 3: "An", 4: "It", 5: "Au",
    6: "Su", 7: "Al", 8: "Lu", 9: "Be", 10: "PB"
}
NB_PAYS = 11

# --- CORRECTION DE LA LISTE D'ARETES ---
# (C'est la liste qui était correcte dans 'visualiser_carte.py'
# mais que j'ai mal copiée dans 'coloration_carte.py')
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
# --- FIN CORRECTION ---


# --- PARTIE 3 : Lancement ! ---
# ------------------------------

print("--- Lancement de la coloration de la carte d'Europe ---")
g_europe = Graph(NB_PAYS)
g_europe.set_labels(labels_pays)

for u, v in aretes_pays:
    g_europe.add_edge(u, v)

colors, num_colors = g_europe.welsh_powell()
g_europe.draw_colored_graph(colors, num_colors)
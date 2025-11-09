import matplotlib.pyplot as plt
import networkx as nx

class Graph:
    def __init__(self, vertices):
        self.vertices = vertices
        # Initialise la matrice à 0
        self.adjMatrix = [[0] * vertices for _ in range(vertices)]

    def add_edge(self, u, v):
        self.adjMatrix[u][v] = 1
        self.adjMatrix[v][u] = 1

    # --- DEBUT DU CODE CORRIGE ---

    # J'ai ajouté une fonction 'peut_colorer' (similaire à 'is_safe'
    # de l'autre script Python) pour plus de clarté
    def peut_colorer(self, v, c, color):
        """Verifie si le sommet 'v' peut prendre la couleur 'c'"""
        for i in range(self.vertices):
            # Si 'i' est un voisin ET 'i' a deja la couleur 'c'
            if self.adjMatrix[v][i] == 1 and color[i] == c:
                return False
        return True

    def welsh_powell(self):
        # 1. Calculer les degrés
        degree = [sum(row) for row in self.adjMatrix]
        vertices_degrees = [(i, degree[i]) for i in range(self.vertices)]
        
        # 2. Trier les sommets par degré décroissant
        sorted_vertices = sorted(vertices_degrees, key=lambda x: x[1], reverse=True)

        # 3. Initialiser les couleurs (0 = non coloré)
        color = [0] * self.vertices
        
        couleur_actuelle = 1
        sommets_colores = 0

        print("\n--- Ordre de marquage (Welsh-Powell) ---")
        for i, (vertex_id, deg) in enumerate(sorted_vertices):
             print(f"{i+1}. Sommet {vertex_id} - Degre: {deg}")
        
        print("\n--- Processus de coloration ---")

        # 4. Boucle principale (logique corrigée)
        while sommets_colores < self.vertices:
            print(f"Application de la Couleur {couleur_actuelle} sur :")
            
            # On parcourt TOUTE la liste triée
            for vertex, _ in sorted_vertices:
                
                # Si le sommet n'est pas coloré
                if color[vertex] == 0:
                    
                    # S'il peut prendre la couleur actuelle
                    if self.peut_colorer(vertex, couleur_actuelle, color):
                        color[vertex] = couleur_actuelle
                        sommets_colores += 1
                        print(f"  -> Sommet {vertex}")
            
            # On passe à la couleur suivante
            couleur_actuelle += 1
        
        # Le nombre de couleurs est couleur_actuelle - 1
        num_colors = couleur_actuelle - 1

        print("\n--- Resultats de la Coloration ---")
        print(f"Graphe colore (Python corrige) avec {num_colors} couleurs:")
        for c in range(1, num_colors + 1):
            nodes_with_color = [i for i, col in enumerate(color) if col == c]
            print(f"  Couleur {c}: {nodes_with_color}")

        return color, num_colors

    # --- FIN DU CODE CORRIGE ---

    def draw_colored_graph(self, color_map, num_colors):
        """Dessine le graphe avec les couleurs trouvées."""
        G = nx.Graph()
        G.add_nodes_from(range(self.vertices))
        for i in range(self.vertices):
            for j in range(i + 1, self.vertices):
                if self.adjMatrix[i][j] == 1:
                    G.add_edge(i, j)
        
        # Crée une palette de couleurs
        palette = plt.cm.get_cmap('rainbow', num_colors)
        node_colors = [palette(c - 1) for c in color_map] # c-1 car les couleurs sont 1-indexées

        plt.figure(figsize=(8, 6))
        nx.draw(G, 
                with_labels=True, 
                node_color=node_colors, 
                edge_color='gray',
                node_size=1000)
        plt.title("Graphe Colore (Welsh-Powell Python)")
        plt.show()

# --- Exemple d'utilisation (le même que dans le fichier C) ---
g = Graph(5)
g.add_edge(0, 1)
g.add_edge(0, 2)
g.add_edge(1, 2)
g.add_edge(1, 3)
g.add_edge(2, 3)
g.add_edge(3, 4)

# Appliquer l'algorithme corrigé
colors, num_colors = g.welsh_powell()

# Dessiner le résultat
g.draw_colored_graph(colors, num_colors)
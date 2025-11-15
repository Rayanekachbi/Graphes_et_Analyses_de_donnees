import networkx as nx
import matplotlib.pyplot as plt

# Définir les sommets (ID et Noms)
# Les noms sont juste pour les étiquettes
labels = {
    0: "Fr", 1: "Es", 2: "Po", 3: "An", 4: "It", 5: "Au",
    6: "Su", 7: "Al", 8: "Lu", 9: "Be", 10: "PB"
}

# Définir les arêtes (frontières) en utilisant les IDs
aretes = [
    (0, 1), (0, 3), (0, 4), (0, 6), (0, 7), (0, 8), (0, 9), # France
    (1, 2), (1, 3),                                          # Espagne
    # (Portugal n'a que l'Espagne)
    # (Andorre n'a que France/Espagne)
    (4, 6), (4, 5),                                          # Italie
    (5, 6), (5, 7),                                          # Autriche
    (6, 7),                                                  # Suisse
    (7, 8), (7, 9), (7, 10),                                 # Allemagne
    (8, 9),                                                  # Luxembourg
    (9, 10)                                                  # Belgique
]

# Créer le graphe
G = nx.Graph()

# --- CORRECTION ICI ---
# Ajouter les nœuds par leur ID (les clés du dictionnaire)
G.add_nodes_from(labels.keys())

# Ajouter les arêtes (qui utilisent maintenant les IDs)
G.add_edges_from(aretes)
# --- FIN CORRECTION ---

# Dessiner le graphe
plt.figure(figsize=(10, 7))
nx.draw(G, 
        labels=labels,       # Affiche nos étiquettes "Fr", "Es"...
        with_labels=True, 
        node_color='lightblue', 
        edge_color='gray',
        font_weight='bold',
        node_size=2000)

# Afficher le graphe
plt.title("Graphe des 11 Pays Europeens")
plt.show()
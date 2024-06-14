import pandas as pd
import matplotlib.pyplot as plt
import os

def fonction_affichage(file_path):
    data = pd.read_csv(file_path, sep=';')

    data.columns = ["nom du fichier", "MatDPvectVect", "MatDPvect", "MatDPtabTab", "MatDPtab",
                     "écart vectvect", "écart vect","écart tabtab", "écart tab", "unused"]

    mean_ecarts = {
        'vectVect': data['écart vectvect'].mean(),
        'vect': data['écart vect'].mean(),
        'tabTab': data['écart tabtab'].mean(),
        'tab': data['écart tab'].mean()
    }

    min_mean_ecart = min(mean_ecarts.values())
    normalization_factor = 1.0 / min_mean_ecart
    normalized_means = {key: value * normalization_factor for key, value in mean_ecarts.items()}

    plt.figure(figsize=(10, 6))
    bars = plt.bar(normalized_means.keys(), normalized_means.values(), color='blue', alpha=0.7)
    plt.xlabel('type matrices')
    plt.ylabel('moyenne des écarts normalisées')
    plt.grid(True)

    for bar in bars:
        height = bar.get_height()
        plt.text(bar.get_x() + bar.get_width() / 2, height, f'{height:.2f}', ha='center', va='bottom')

    plt.title(f'Analyse des écarts pour {os.path.basename(file_path)}')
    plt.show()

# liste des fichiers CSV à traiter
file_list = ['testV0.csv', 'testV1.csv','testV2.csv']

for file in file_list:
    fonction_affichage(file)

import csv
import os

def process_file(filename):
    count_v0_better = 0
    count_v1_better = 0
    ratios = []

    with open(filename, newline='') as csvfile:
        reader = csv.reader(csvfile, delimiter=';')
        next(reader)  # Pour sauter l'en-tête s'il y en a un

        for row in reader:
            if len(row) == 4:
                vi = float(row[0])
                vi1 = float(row[1])
                ratio = float(row[2])

                if vi < vi1:
                    count_v0_better += 1
                elif vi1 < vi:
                    count_v1_better += 1

                ratios.append(ratio)

    avg_ratio = sum(ratios) / len(ratios) if ratios else 0
    min_ratio = min(ratios) if ratios else float('inf')
    max_ratio = max(ratios) if ratios else float('-inf')

    #attribution des label
    base_filename = os.path.splitext(os.path.basename(filename))[0]
    v0_label = base_filename[:2]
    v1_label = base_filename[2:].split('_')[0]

    print(f"Fichier: {filename}")
    print(f"Nombre de fois où {v0_label} est meilleure: {count_v0_better}")
    print(f"Nombre de fois où {v1_label} est meilleure: {count_v1_better}")
    print(f"Analyse des ratios ti/tmin: Moyenne = {avg_ratio}, Min = {min_ratio}, Max = {max_ratio}")
    print()

# liste des fichiers CSV à traiter
file_list = ['v0V1_a.csv', 'v0V1_b.csv', 'v1Vbis.csv', 'v1Vbis_b.csv', 'v1V2_a.csv', 'v1V2_b.csv']

for file in file_list:
    process_file(file)

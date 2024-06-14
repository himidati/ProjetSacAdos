import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("temps_calcul.csv", delimiter=';')

df['Ratio Temps/N*M'] = df['Temps-calculs(s)'] / df['N*M']

group1 = df.nsmallest(20, 'Ratio Temps/N*M')  # groupe 1 les plus petits
group2 = df.nlargest(20, 'Ratio Temps/N*M')   # groupe 2 les plus grands

plt.figure(figsize=(10, 6))

# Plot des instances du groupe 1
plt.scatter(group1['filename'], group1['Ratio Temps/N*M'], c='blue', label='Groupe 1')

# Plot des instances du groupe 2
plt.scatter(group2['filename'], group2['Ratio Temps/N*M'], c='red', label='Groupe 2')

plt.xlabel('Instances')
plt.ylabel('Temps de calcul total / N*M')
plt.title('Ratio Temps de calcul total / N*M pour chaque instance')
plt.xticks(rotation=90)
plt.legend()
plt.grid(True)
plt.tight_layout()

plt.show()

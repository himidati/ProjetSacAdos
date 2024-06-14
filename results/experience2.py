import pandas as pd
import matplotlib.pyplot as plt


df = pd.read_csv("temps_calcul.csv", delimiter=';', names=['filename', 'Temps-calculs(s)', 'optimum', 'N', 'M', 'N*M'], header=0)

plt.figure(figsize=(10, 6))
plt.scatter(df['N*M'], df['Temps-calculs(s)'], c='blue', label='Temps de calcul')

plt.xlabel('N*M')
plt.ylabel('Temps de calcul total (s)')
plt.title('Temps de calcul total vs N*M')
plt.legend()

plt.show()

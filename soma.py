import pandas as pd

# Ler o arquivo CSV
df = pd.read_csv('dados.csv', sep=';')
for i in range(200, 2200, 200):
    df[f'{i}'][3] = df[f'{i}'][0] / (df[f'{i}'][1] - df[f'{i}'][2])

# Salvar o DataFrame atualizado de volta no arquivo CSV
df.to_csv('dados.csv', sep=';', index=False)
print(df)

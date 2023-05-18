from random import randint

n_linhas = 2
n_produtos = 14

# Array de custos 
custos = [randint(1, 8) for i in range(n_produtos)]

# Gera a matriz de distâncias
matriz_distancias = []
for i in range(n_produtos):
    linha = []
    for j in range(n_produtos):
        if i == j:
            linha.append(0)
        else:
            linha.append(randint(1, 100))
    matriz_distancias.append(linha)


path = f".\\instancias\\instancia_custom_{n_linhas}_{n_produtos}.txt"


with open(path, 'w+') as file:
    file.write(f"{n_linhas}\n{n_produtos}\n\n")
    file.write(" ".join(str(custo) for custo in custos))
    file.write("\n\n")
    for linha in matriz_distancias:
        file.write(" ".join(str(distancia) for distancia in linha))
        file.write("\n")

print(f"Arquivo gravado em {path}")

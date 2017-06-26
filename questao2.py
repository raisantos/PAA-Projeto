npeso = 100000 + 1

def inicia_matriz(valor, nitens, mochila):
    for i in range(nitens+1):
        linha = []
        for j in range(npeso + 1):
            linha.append(valor)
        mochila.append(linha)

def mochila(nitens, codigo, valores, porcentagem):
    
    mochila = []
    inicia_matriz(0, nitens, mochila)
    
    for i in range(1, nitens+1):
        for j in range(1, npeso+1):
            if(valores[i-1] <= j):
                if(porcentagem[i-1] + mochila[i-1][j - valores[i-1]] > mochila[i-1][j]):
                    mochila[i][j] = porcentagem[i-1] + mochila[i-1][j - valores[i-1]]
                else:
                    mochila[i][j] = mochila[i-1][j]
            else:
                mochila[i][j] = mochila[i-1][j]
                
    mostra_mochila(nitens, mochila, codigo, valores, porcentagem)

def mostra_mochila(nitens, mochila, codigo, valores, porcentagem):
    i = nitens
    j = npeso

    lista = []
    
    while( (i > 0) and (j > 0) ):
        if(mochila[i][j] != mochila[i-1][j]):
            lista.append(codigo[i-1])
            j = j - valores[i-1]
            i = i - 1
        else:
            i = i - 1

    lista.sort()
    for i in lista:
        print(i)
                    

def processa():
    nitens = int(input())

    codigo = []
    porcentagem = []
    valores = []    
    
    for i in range(0, nitens):
        acoes = input()
        lista = acoes.split(" ")
        codigo.append(lista[0])
        valores.append(int(lista[1]))
        porcentagem.append(float(lista[2]))

    mochila(nitens, codigo, valores, porcentagem)


processa()

    


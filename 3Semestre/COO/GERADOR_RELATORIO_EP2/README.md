
# 📝 Gerador de Relatórios - EP2COO

Este projeto gera um relatório em HTML a partir de uma lista de produtos contida em um arquivo CSV. É possível escolher o critério de ordenação, a direção, filtros e formatações no relatório.

---

## ✅ Como Executar

1. Abra o terminal dentro da pasta `src` do projeto:

```powershell
cd caminho/para/EP2COO/src
```

2. Compile o código:

```powershell
javac Gerador_de_Relatorio/GeradorDeRelatorios.java
```

3. Execute o programa:

```powershell
java Gerador_de_Relatorio.GeradorDeRelatorios <algoritmo> <critério de ordenação> <critério de ordem> <critério de filtragem> <parâmetro de filtragem> <opções de formatação>
```

### Exemplo:

```powershell
java Gerador_de_Relatorio.GeradorDeRelatorios quick preco_c crescente todos x negrito
```

---

## 📁 Requisitos

- O arquivo `produtos.csv` deve estar no diretório correto (data), conforme especificado no código.
- Ter o Java instalado (JDK 11 ou superior).

---

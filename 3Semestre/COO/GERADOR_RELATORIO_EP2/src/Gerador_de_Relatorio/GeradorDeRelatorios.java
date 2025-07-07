package Gerador_de_Relatorio;

import java.io.PrintWriter;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

import Criterio_Ordenacao.*;
import Direcao_Ordenacao.*;
import Estrategia_Ordenacao.*;
import Filtragem.*;
import Formatadores.*;
import Produto.*;

public class GeradorDeRelatorios {

	// operador bit a bit "ou" pode ser usado para combinar mais de  
    // um estilo de formatacao simultaneamente (veja como no main)
    public static final int FORMATO_PADRAO  = 0b0000;
    public static final int FORMATO_NEGRITO = 0b0001;
    public static final int FORMATO_ITALICO = 0b0010;

	private SortStrategy sortStrategy;
    private Comparator<Produto> comparator; 
	private List<Produto> produtos;
	private Filtros filtro;

	public GeradorDeRelatorios(List<Produto> produtos, SortStrategy sortStrategy, Comparator<Produto> comparator, 
								OrdemStrategy ordemStrategy, Filtros filtro){
		this.produtos = new ArrayList<>(produtos);
		this.filtro = filtro;
		this.sortStrategy = sortStrategy;
        this.comparator = ordemStrategy.aplicar(comparator);
	}

    public void setSortStrategy(SortStrategy sortStrategy) {
        this.sortStrategy = sortStrategy;
    }

    public void setComparator(Comparator<Produto> comparator) {
        this.comparator = comparator;
    }

    public void Ordenar(List<Produto> produtos) {
        sortStrategy.sort(produtos, comparator);
    }
	
	public void debug(){

		System.out.println("Gerando relatório para array contendo " + produtos.size() + " produto(s)");
	}

	public void geraRelatorio(String arquivoSaida) throws IOException {

		debug();

		Ordenar(produtos);

		PrintWriter out = new PrintWriter(arquivoSaida);

		out.println("<!DOCTYPE html><html>");
		out.println("<head><title>Relatorio de produtos</title></head>");
		out.println("<body>");
		out.println("Relatorio de Produtos:");
		out.println("<ul>");

		int count = 0;

		for (Produto p : produtos) {
			if (filtro.selecionar(p)) {
				out.print("<li>");
				out.print(p.formataParaImpressao());
				out.println("</li>");
				count++;
			}
		}

		out.println("</ul>");
		out.println(count + " produtos listados, de um total de " + produtos.size() + ".");
		out.println("</body>");
		out.println("</html>");

		out.close();
	}


public static List<Produto> carregaProdutos() {
    List<Produto> listaDeProdutos = new ArrayList<>();
    String caminhoArquivo = "../data/produtos.csv";  // Ajuste conforme onde está o arquivo

    try (BufferedReader br = new BufferedReader(new FileReader(caminhoArquivo))) {
        String linha;
        boolean primeiraLinha = true;

        while ((linha = br.readLine()) != null) {
            // Remove possíveis espaços e caracteres invisíveis
            linha = linha.trim();

            // Ignora cabeçalho ou linhas vazias
            if (primeiraLinha || linha.isEmpty()) {
                primeiraLinha = false;
                continue;
            }

            // Split robusto: separa por vírgula e remove espaços
            String[] campos = linha.split(",");

            if (campos.length < 8) {
                System.out.println("Linha ignorada (dados incompletos): " + linha);
                continue;
            }

            try {
                int id = Integer.parseInt(campos[0].trim());
                String descricao = campos[1].trim();
                String categoria = campos[2].trim();
                int qtdEstoque = Integer.parseInt(campos[3].trim());
                double preco = Double.parseDouble(campos[4].trim());
                boolean negrito = Boolean.parseBoolean(campos[5].trim());
                boolean italico = Boolean.parseBoolean(campos[6].trim());
                String cor = campos[7].trim();

                Produto produto = new ProdutoPadrao(id, descricao, categoria, qtdEstoque, preco);
                if (negrito) produto = new Negrito(produto);
                if (italico) produto = new Italico(produto);
                if (!cor.equalsIgnoreCase("#000000")) produto = new Cor(produto, cor);

                listaDeProdutos.add(produto);
            } catch (Exception e) {
                System.out.println("Erro ao processar linha: " + linha);
                e.printStackTrace();
            }
        }
    } catch (IOException e) {
        e.printStackTrace();
    }

    System.out.println("Total de produtos carregados: " + listaDeProdutos.size());
    return listaDeProdutos;
}



	public static void main(String [] args) {

		if(args.length < 5){

			System.out.println("Uso:");
			System.out.println("\tjava " + GeradorDeRelatorios.class.getName() + " <algoritmo> <critério de ordenação> <critério de ordem> <critério de filtragem> <parâmetro de filtragem> <opções de formatação>");
			System.out.println("Onde:");
			System.out.println("\talgoritmo: 'quick' ou 'insertion'");
			System.out.println("\tcriterio de ordenação: 'preco_c' ou 'descricao_c' ou 'estoque_c'");
			System.out.println("\tcriterio de ordem: 'crescente' ou 'decrescente'");
			System.out.println("\tcriterio de filtragem: 'todos' ou 'estoque_menor_igual' ou 'categoria_igual' ou 'preco_intervalo' ou 'descricao_contem'"); 
			System.out.println("\tparâmetro de filtragem: argumentos adicionais necessários para a filtragem (se for intervalo, digite '0.1,1.0' por exemplo)"); 
			System.out.println("\topções de formatação: 'negrito' e/ou 'italico'");
			System.out.println();
			System.exit(1);
		}

		String opcao_algoritmo = args[0]; 
		String opcao_criterio_ord = args[1];
		String opcao_ordem = args[2]; 
		String opcao_criterio_filtro = args[3]; 
		String opcao_parametro_filtro = args[4];
		
		Filtros criterio_filtragem;
		switch (opcao_criterio_filtro) {
			case "todos":
				criterio_filtragem = new Todos();
				break;
			case "estoque_menor_igual":
				criterio_filtragem = new EstoqueMenorOuIgual(Integer.parseInt(opcao_parametro_filtro));
				break;
			case "categoria_igual":
				criterio_filtragem = new CategoriaIgual(opcao_parametro_filtro);
				break;
			case "preco_intervalo":
				criterio_filtragem = new PrecoIntervalo(opcao_parametro_filtro);
				break;
			case "descricao_contem":
				criterio_filtragem = new DescricaoContem(opcao_parametro_filtro);
				break;
			default:
				throw new RuntimeException("Critério de filtragem inválido!");
		}

		SortStrategy estrategia_ordenacao;
		switch (opcao_algoritmo) {
			case "quick":
				estrategia_ordenacao = new QuickSort();
				break;
			case "insertion":
				estrategia_ordenacao = new InsertionSort();
				break;
			default:
				throw new RuntimeException("Opção de estrategia de ordenação inválido!");
		}	

		OrdemStrategy estrategia_ordem;
		switch (opcao_ordem) {
			case "crescente":
				estrategia_ordem = new OrdemCrescente();
				break;
			case "decrescente":
				estrategia_ordem = new OrdemDecrescente();
				break;
			default:
				throw new RuntimeException("Opção de estrategia de ordem inválido!");
		}	

		Comparator<Produto> criterio_ordenacao;
		switch (opcao_criterio_ord) {
			case "preco_c":
				criterio_ordenacao = new PrecoComparator();
				break;
			case "descricao_c":
				criterio_ordenacao = new DescricaoComparator();
				break;
			case "estoque_c":
				criterio_ordenacao = new QuantidadeComparator();
				break;
			default:
				throw new RuntimeException("Opção de critério de ordenação inválido!");
		}	

		List<Produto> Lista_Produtos;
		Lista_Produtos = carregaProdutos();

		GeradorDeRelatorios gdr = new GeradorDeRelatorios(Lista_Produtos, estrategia_ordenacao, criterio_ordenacao, estrategia_ordem, criterio_filtragem);

		try{
			gdr.geraRelatorio("saida.html");
		}
		catch(IOException e){
			
			e.printStackTrace();
		}
	}
}
package Exercícios.ninja;

// Importanto a coleção de listas e Array Lists
import java.util.ArrayList;
import java.util.List;

// Criando uma classe que recebe um tipo genérico
public class BolsaNinja<T> {

    // Inicializando a array
    private List<T> ferramentas;

    // Construtor
    public BolsaNinja() {
        this.ferramentas = new ArrayList<>();
    }

    // Colocar ferramentas na lista
    public void AdicionarFerramenta(T item_ninja) {
        ferramentas.add(item_ninja);
    }

    // Mostrar a lista de ferramentas
    public void AbrirBolsa() {
        for(T item_ninja : ferramentas){
            System.out.println(item_ninja);
        }
    }
}
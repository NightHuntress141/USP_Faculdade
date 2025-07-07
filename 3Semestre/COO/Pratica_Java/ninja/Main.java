package Exercícios.ninja;

public class Main {
    public static void main(String[] args) {
        
        // Inicializando uma nova instância da classe de Bolsa Ninja
        // Perceba que essa declaração se utiliza de uma superclasse chamada Object,
        // dessa maneira, é possível adicionar qualquer outra classe derivada dessa mesma (Shuriken e Kunai)
        BolsaNinja<Object> NovaBolsa = new BolsaNinja<>();

        NovaBolsa.AdicionarFerramenta(new Kunai("Kunai Explosiva"));
        NovaBolsa.AdicionarFerramenta(new Shuriken(10));

        NovaBolsa.AbrirBolsa();
    }
}

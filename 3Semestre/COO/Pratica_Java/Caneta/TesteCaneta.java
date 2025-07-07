package Exercícios.Caneta;

public class TesteCaneta {
    //Método principal para execusão e teste da classe Caneta
    public static void main(String[] args){

        // Exibindo informações do objeto usando um construtor com parâmetros
        Caneta minhaCaneta_1 = new Caneta("Pilot", "Preta", 2, true, 10);
        minhaCaneta_1.status();
        System.out.println("");

        // Trocando os valores
        minhaCaneta_1.cor = "rosa";
        minhaCaneta_1.status();
        System.out.println("");
        
        // Criando um objeto usando um construtor sem parâmetros
        Caneta canetaPadrao = new Caneta();
        canetaPadrao.status();
        System.out.println("");

        // Utilizando um método
        canetaPadrao.AbrirCaneta();
        canetaPadrao.status();
        System.out.println("");

        // Tentando mudar manualmente um valor privado (carga) -> Dará um erro
        // canetaPadrao.carga = 15;

        // Tentando mudar através de um método público o valor de um atributo privado (carga)
        canetaPadrao.MudarCarga(15);
        canetaPadrao.status();
        System.out.println("");
    }
}

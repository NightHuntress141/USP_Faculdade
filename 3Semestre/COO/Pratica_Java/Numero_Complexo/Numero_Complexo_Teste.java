package Exercícios.Numero_Complexo;

public class Numero_Complexo_Teste {
    public static void main(String[] args) {
        Numero_Complexo c1 = new Numero_Complexo(2,1); // Cria número complexo 2 + i
        Numero_Complexo c2 = new Numero_Complexo(3, -1); // Cria número complexo 3 - i

        // Três formas diferentes de somar números complexos:
        Numero_Complexo S1 = Numero_Complexo.soma(c1, c2); // Usando método estático
        Numero_Complexo S2 = c1.soma2(c2);                 // Usando método de instância
        Numero_Complexo S3 = c2.soma3(c2);                 // Usando método que chama o estático

    }
}

package Exercícios.Numero_Complexo;

public class Numero_Complexo {

    // Atributos
    private double r; // parte real
    private double i; // parte imaginária


    // Construtor
    public Numero_Complexo(double r, double i){
        this.r = r;
        this.i = i;
    }

    // Método estático que retorna a soma de dois números complexos
    public static Numero_Complexo soma(Numero_Complexo S1, Numero_Complexo S2){
            return(new Numero_Complexo(S1.r + S2.r, S1.i + S2.i));
    }

    // Método de instância que soma este número complexo com outro
    public Numero_Complexo soma2(Numero_Complexo O){
        return(new Numero_Complexo(O.r + this.r, O.i + this.i));
    }

    // Método de instância que usa o método estático para somar
    public Numero_Complexo soma3(Numero_Complexo o) {
        return Numero_Complexo.soma(o, this);  
    }

}

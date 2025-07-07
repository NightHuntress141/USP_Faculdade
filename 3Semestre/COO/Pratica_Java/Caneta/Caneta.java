package Exercícios.Caneta;

// Public -> Faz referencia a visibilidade dessa classe, podendo ser privada ou pública
public class Caneta{

    // Criando os campos (variáveis de instâncias) de uma classe -> Armazenam valores 
    // para o objeto utilizar
    public String modelo;
    public String cor;
    public int ponta;
    public boolean tampada;
    private int carga; // Varíavel privada

    // Construtor parametrizado -> responsável por inicializar os objetos com os valores recebidos
    public Caneta(String modelo, String cor, int ponta, boolean tampada, int carga){
        // Aqui podemos podemos fazer com que os objetos inicializem com valores já definidos
        this.modelo = modelo;
        this.cor = cor;
        this.ponta = ponta;
        this.tampada = tampada;
        this.carga = carga;
        // No código apresentado, a palavra-chave this é usada para referenciar os atributos da 
        // própria instância do objeto. Como os parâmetros do construtor têm os mesmos nomes que 
        // os atributos da classe, o this. é necessário para diferenciar entre eles. 
    }

    // Construtor não parametrizado -> responsável por inicializar os objetos com os valores já pré-definidos
    public Caneta() {
        this.modelo = "Bic";
        this.cor = "Azul";
        this.ponta = 1;
        this.tampada = true;
        this.carga = 10;
    }

    // Construtor parametrizado que ainda pode colocar valores pré-definidos
    /*public Caneta(String modelo, String cor, int ponta, boolean tampada) {
        this.modelo = (modelo != null) ? modelo : "Bic";
        this.cor = (cor != null) ? cor : "Azul";
        this.ponta = (ponta > 0) ? ponta : 1;
        this.tampada = tampada;
    }*/
    
    // Criando os métodos
    public void status(){
        System.out.println("Modelo: " + modelo);
        System.out.println("Cor: " + cor);
        System.out.println("Ponta: " + ponta);
        System.out.println("Está tampada? " + tampada);
        System.out.println("Carga: " + carga);
    }
    public boolean AbrirCaneta(){
        return tampada = false;
    }
    public boolean FecharCaneta(){
        return tampada = true;
    }
    public int MudarCarga(int NovaCarga){
        return carga = NovaCarga;
    }
}


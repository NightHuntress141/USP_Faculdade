package Exercícios;
class Animal {
    int peso;
    
    // Construtor não parametrizado -> Aqui peso será 0
    Animal() {
        System.out.println("Eu respiro e me mexo.");
    }
    
    // Construtor parametrizado -> Aqui peso será igual ao parametro passado na chamada
    Animal(int peso) {
        this.peso = peso;
        System.out.println("Eu respiro e me mexo e peso " + peso + " gramas");
    }
}

class Cachorro extends Animal {

    // Construtor não parametrizado -> Aqui peso será 0
    Cachorro() {
        super();
        System.out.println("Eu tenho coluna vertebral e lato.");
    }
    
    // Construtor parametrizado -> Aqui peso será igual ao parametro passado na chamada
    Cachorro(int peso) {
        super(peso); // Chama o construtor da superclasse (de cima estritamente)
        System.out.println("Eu tenho coluna vertebral e lato.");
    }
    
    public static void main(String args[]) {
        Animal totó = new Cachorro(); // Todo cachorro é um animal
        // Cachorro totó = new Animal(); Mas animal não é um cachorro
        Cachorro rex = new Cachorro(12000);
    }
}
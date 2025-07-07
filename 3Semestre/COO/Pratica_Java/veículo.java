package Exercícios;
// 1 - O método movimente() está sobrescrito em todas as subclasses, demonstrando polimorfismo.
// 2 - As chamadas super.movimente() são opcionais e servem para invocar o comportamento da classe 
// pai antes de adicionar o comportamento específico da classe filha.

class Veiculo {
    void movimente() {
        System.out.println("Eu me movimento por aí.");
    }
}

class Carro extends Veiculo {
    void movimente() {
        super.movimente(); // opcional
        System.out.println("Eu gasto combustível, gero trânsito e poluo o ar.");
    }
}

class Ferrari extends Carro {
    void movimente() {
        super.movimente(); // opcional
        System.out.println("Sou vermelha, super-da-hora mas faço um barulhão.");
    }
}

class Bicicleta extends Veiculo {
    void movimente() {
        super.movimente(); // opcional
        System.out.println("Faço bem para a saúde física e mental e não poluo.");
    }
}
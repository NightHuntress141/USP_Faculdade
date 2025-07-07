package Exercícios.Collections;

import java.util.Set;
import java.util.TreeSet;
import java.util.HashSet;
import java.util.LinkedHashSet;

public class SetEHashSet_teste {
    public static void main(String[] args) {
        // Assim como no caso de List e Map e Queue, Set é apenas uma interface, não havendo nenhuma implementação
        // Dessa maneira, devemos decidir qual classe que implementa a interface Set devemos utilizar:
        // HashSet, TreeSet ou LinkedHashSet
        // Lembrando que Set imita um conjunto matemático
        
        System.out.println("Criando um HashSet: Ordem Aleatória e é mais rápido");
        Set<String> names = new HashSet<>();

        names.add("Ana");
        names.add("Ana"); // Nesse caso, ele não irá duplicar, pois imita um conjunto matemático
        names.add("Mike");
        names.add("Jon");
        System.out.println(names);
        names.remove("Ana");
        System.out.println(names);
        
        System.out.println("Tamanho do HashSet: ");
        System.out.println(names.size());
        System.out.println("Possui o nome Saul? ");
        System.out.println(names.contains("Saul"));

        names.clear();
        System.out.println("Está vazio? ");
        System.out.println(names.isEmpty());

        System.out.println("Criando um TreeSet: Ordem Alfabetica, não é mais tão rápido");
        Set<String> names_alfabeto = new TreeSet<>();
        names_alfabeto.add("Julia"); 
        names_alfabeto.add("Mike");
        names_alfabeto.add("Ana");
        System.out.println(names_alfabeto);
        names_alfabeto.clear();
        System.out.println("Está vazio? ");
        System.out.println(names_alfabeto.isEmpty());

        System.out.println("Criando um LinkedHashSet: Ordem de inserção pelo usuário, é mais rápido");
        Set<String> names_inserção = new LinkedHashSet<>();
        names_inserção.add("Julia"); 
        names_inserção.add("Mike");
        names_inserção.add("Ana");
        System.out.println(names_inserção);
        names_inserção.clear();
        System.out.println("Está vazio? ");
        System.out.println(names_inserção.isEmpty());
    }
}

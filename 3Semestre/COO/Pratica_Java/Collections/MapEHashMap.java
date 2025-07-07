package Exercícios.Collections;

import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.TreeMap;
import java.util.SortedMap;

public class MapEHashMap {
    public static void main(String[] args){ 
        // Assim como no caso de List e Set e Queue, map é apenas uma interface, não havendo nenhuma implementação
        // Dessa maneira, devemos decidir qual classe que implementa a interface Map devemos utilizar:
        // HashMap, TreeMap ou LinkedHashMap

        System.out.println("Criando um HashMap: Ordem Aleatória e é mais rápido");
        Map<String, Integer> reg = new HashMap<>();

        reg.put("John", 123);
        reg.put("Ana", 345);
        reg.put("Luke", 897);
        reg.put("Peter", 123); // Perceba que podemos ter chaves diferentes com o mesmo valor, mas não podemos possuir chaves iguais com valores diferentes!
        reg.put("Peter", 489); // Nesse caso, a chave de Peter será a última declarada pelo usuário, isto é, Peter=489
        reg.replace("John", 564); // Troca o valor da chave "John", mas apenas se essa já existir
        System.out.println(reg);

        System.out.println("ID de John: " + reg.get("John"));
        System.out.println("Ana está na lista: " + (reg.containsKey("Ana") ? "Sim, Ana está na lista" : "Não, Ana não está na lista"));
        System.out.println("ID '123' está na lista: ': " + (reg.containsValue(123) ? "Sim" : "Não"));

        reg.clear();

        // TreeMap é uma implementação da Interface SortedMap, que é derivada da interface Map em si
        System.out.println("Criando um TreeMap: Ordem definida pelas chaves, não é mais tão rápido");
        SortedMap<String, Integer> reg_2 = new TreeMap<>();

        reg_2.put("John", 123);
        reg_2.put("Ana", 345);
        reg_2.put("Peter", 123); 
        reg_2.put("Luke", 897);
        System.out.println(reg_2);

        reg_2.clear();

        System.out.println("Criando um LinkedHashMap: Ordem de inserção pelo usuário, é mais rápido");
        Map<String, Integer> reg_3 = new LinkedHashMap<>();

        reg_3.put("John", 123);
        reg_3.put("Ana", 345);
        reg_3.put("Peter", 123); 
        reg_3.put("Luke", 897);
        System.out.println(reg_3);

        reg_3.clear();

    }
}

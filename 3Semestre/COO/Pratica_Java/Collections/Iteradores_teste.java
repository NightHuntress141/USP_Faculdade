package Exercícios.Collections;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Iterator;

public class Iteradores_teste {
    public static void main(String[] args) {

        List<Integer> nums = new ArrayList<>(Arrays.asList(1, 2, 3, 4, 5));

        // Utilizando a classe "Iteradores" que possui métodos com iterator
        Iteradores.filter(nums); // nums agora contém [2, 4]

        // Utilizando for-each para printar os valores da ArrayList
        System.out.println("Interando com for-each");
        for (Integer number : nums) {
            System.out.println(number);
        }

        // Utilizando iterator para printar os valores da ArrayList e removendo valores especificos
        Iterator<Integer> it = nums.iterator();
        System.out.println("Interando por iterator");
        while (it.hasNext()) {
            Integer atual = it.next();
            if(atual == 4) it.remove();
            System.out.println(it.next());
        }

    }
    
}

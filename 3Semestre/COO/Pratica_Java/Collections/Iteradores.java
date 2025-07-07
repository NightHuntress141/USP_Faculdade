package Exercícios.Collections;

import java.util.Collection;
import java.util.Iterator;

public class Iteradores {

    // Condição para ser um número par
    static boolean isEven (Object elemento){
        Integer number = (Integer) elemento;
        return number % 2 == 0;
    }

    // Método de filtragem
    static void filter(Collection<?> c) {
    for (Iterator<?> it = c.iterator(); it.hasNext();)
        if (!isEven(it.next()))
            it.remove();
    }
}

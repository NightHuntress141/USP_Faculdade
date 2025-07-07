package Estrategia_Ordenacao;

import java.util.Comparator;
import java.util.List;
import Produto.*;

public class InsertionSort implements SortStrategy {
    @Override
    public void sort(List<Produto> produtos, Comparator<Produto> comparator) {
        for (int i = 1; i < produtos.size(); i++) {
            Produto chave = produtos.get(i);
            int j = i - 1;
            while (j >= 0 && comparator.compare(produtos.get(j), chave) > 0) {
                produtos.set(j + 1, produtos.get(j));
                j--;
            }
            produtos.set(j + 1, chave);
        }
    }
}

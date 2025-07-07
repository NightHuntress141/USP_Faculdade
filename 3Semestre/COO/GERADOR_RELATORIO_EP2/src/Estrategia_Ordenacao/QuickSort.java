package Estrategia_Ordenacao;

import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import Produto.*;

public class QuickSort implements SortStrategy {
    @Override
    public void sort(List<Produto> produtos, Comparator<Produto> comparator) {
        quicksort(produtos, 0, produtos.size() - 1, comparator);
    }

    private void quicksort(List<Produto> a, int lo, int hi, Comparator<Produto> cmp) {
        if (lo >= hi) return;
        Produto pivot = a.get((lo + hi) / 2);
        int i = lo, j = hi;
        while (i <= j) {
            while (cmp.compare(a.get(i), pivot) < 0) i++;
            while (cmp.compare(a.get(j), pivot) > 0) j--;
            if (i <= j) {
                Collections.swap(a, i++, j--);
            }
        }
        if (lo < j) quicksort(a, lo, j, cmp);
        if (i < hi) quicksort(a, i, hi, cmp);
    }
}

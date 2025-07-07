package Estrategia_Ordenacao;

import java.util.Comparator;
import java.util.List;
import Produto.*;

public interface SortStrategy {

    void sort(List<Produto> produtos, Comparator<Produto> comparator);
}

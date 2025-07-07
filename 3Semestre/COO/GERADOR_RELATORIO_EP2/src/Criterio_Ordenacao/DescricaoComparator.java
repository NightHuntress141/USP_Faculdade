package Criterio_Ordenacao;

import java.util.Comparator;
import Produto.*;

public class DescricaoComparator implements Comparator<Produto> {
    @Override
    public int compare(Produto p1, Produto p2) {
        return p1.getDescricao().compareToIgnoreCase(p2.getDescricao());
    }
}
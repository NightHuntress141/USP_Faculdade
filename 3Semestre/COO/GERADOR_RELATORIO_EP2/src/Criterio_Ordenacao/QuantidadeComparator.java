package Criterio_Ordenacao;

import java.util.Comparator;
import Produto.*;

public class QuantidadeComparator implements Comparator<Produto> {
    @Override
    public int compare(Produto p1, Produto p2) {
        return Integer.compare(p1.getQtdEstoque(), p2.getQtdEstoque());
    }
}

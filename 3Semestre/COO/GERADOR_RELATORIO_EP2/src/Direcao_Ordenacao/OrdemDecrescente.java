package Direcao_Ordenacao;

import java.util.Comparator;

public class OrdemDecrescente implements OrdemStrategy {
    @Override
    public <T> Comparator<T> aplicar(Comparator<T> comparatorBase) {
        return comparatorBase.reversed(); // invertemos a ordem
    }
}

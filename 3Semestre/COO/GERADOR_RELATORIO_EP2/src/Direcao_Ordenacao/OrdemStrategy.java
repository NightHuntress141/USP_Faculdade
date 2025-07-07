package Direcao_Ordenacao;

import java.util.Comparator;

public interface OrdemStrategy {
    <T> Comparator<T> aplicar(Comparator<T> comparatorBase);
}

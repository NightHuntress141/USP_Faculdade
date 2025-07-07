package Direcao_Ordenacao;

import java.util.Comparator;

public class OrdemCrescente implements OrdemStrategy {
    @Override
    public <T> Comparator<T> aplicar(Comparator<T> comparatorBase) {
        return comparatorBase; // mantemos a ordem natural
    }
}

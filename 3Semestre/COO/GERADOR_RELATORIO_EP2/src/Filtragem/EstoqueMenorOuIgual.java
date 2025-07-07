package Filtragem;

import Produto.*;

public class EstoqueMenorOuIgual implements Filtros {
    private int limite;

    public EstoqueMenorOuIgual(int limite) {
        this.limite = limite;
    }

    public boolean selecionar(Produto p) {
        return p.getQtdEstoque() <= limite;
    }
}
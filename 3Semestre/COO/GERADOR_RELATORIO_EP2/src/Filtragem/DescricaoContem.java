package Filtragem;

import Produto.Produto;

public class DescricaoContem implements Filtros {
    private String valor;

    public DescricaoContem(String valor) {
        this.valor = valor;
    }

    public boolean selecionar(Produto p) {
        return p.getDescricao().contains(valor);
    }
}

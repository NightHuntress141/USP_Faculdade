package Filtragem;

import Produto.*;

public class CategoriaIgual implements Filtros {
    private String categoria;

    public CategoriaIgual(String categoria) {
        this.categoria = categoria;
    }

    public boolean selecionar(Produto p) {
        return p.getCategoria().equalsIgnoreCase(categoria);
    }
}

package Filtragem;

import Produto.*;

public class Todos implements Filtros {
    public boolean selecionar(Produto p) {
        return true;
    }
}
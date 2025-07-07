package Filtragem;

import Produto.*;

public class PrecoIntervalo implements Filtros {
    private double inferior;
    private double superior;

    public PrecoIntervalo(String conteudo) {
        String[] limites = conteudo.split(",");
        this.inferior = Double.parseDouble(limites[0]);
        this.superior = Double.parseDouble(limites[1]);
    }

    public boolean selecionar(Produto p) {
        return (p.getPreco() >= inferior && p.getPreco() <= superior);
    }
}

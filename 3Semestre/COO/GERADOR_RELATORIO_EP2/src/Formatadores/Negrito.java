package Formatadores;

import Produto.*;

public class Negrito extends ProdutoDecorator {

    public Negrito(Produto produtoDecorado) {
        super(produtoDecorado, 
              getCor(produtoDecorado), 
              true, 
              getItalico(produtoDecorado));
    }

    private static String getCor(Produto produto) {
        if (produto instanceof ProdutoDecorator) {
            return ((ProdutoDecorator) produto).getCor();
        }
        return "#000000";
    }

    private static boolean getItalico(Produto produto) {
        if (produto instanceof ProdutoDecorator) {
            return ((ProdutoDecorator) produto).getItalico();
        }
        return false;
    }

    public String formataParaImpressao() {
        return "<span style=\"font-weight:bold\">" + super.produtoDecorado.formataParaImpressao() + "</span>";
    }
}
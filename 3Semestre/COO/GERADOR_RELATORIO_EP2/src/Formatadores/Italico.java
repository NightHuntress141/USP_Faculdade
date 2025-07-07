package Formatadores;

import Produto.*;

public class Italico extends ProdutoDecorator {

    public Italico(Produto produtoDecorado) {
        super(produtoDecorado, 
              getCor(produtoDecorado), 
              getNegrito(produtoDecorado), 
              true);
    }

    private static String getCor(Produto produto) {
        if (produto instanceof ProdutoDecorator) {
            return ((ProdutoDecorator) produto).getCor();
        }
        return "#000000";
    }

    private static boolean getNegrito(Produto produto) {
        if (produto instanceof ProdutoDecorator) {
            return ((ProdutoDecorator) produto).getNegrito();
        }
        return false;
    }

    public String formataParaImpressao() {
        return "<span style=\"font-style:italic\">" + super.produtoDecorado.formataParaImpressao() + "</span>";
    }
}
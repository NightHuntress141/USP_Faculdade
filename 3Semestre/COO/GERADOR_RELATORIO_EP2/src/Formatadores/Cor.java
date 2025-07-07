package Formatadores;

import Produto.*;

public class Cor extends ProdutoDecorator {

    public Cor(Produto produtoDecorado, String cor) {
        super(produtoDecorado, 
              cor, 
              getNegrito(produtoDecorado), 
              getItalico(produtoDecorado));
    }

    private static boolean getNegrito(Produto produto) {
        if (produto instanceof ProdutoDecorator) {
            return ((ProdutoDecorator) produto).getNegrito();
        }
        return false;
    }

    private static boolean getItalico(Produto produto) {
        if (produto instanceof ProdutoDecorator) {
            return ((ProdutoDecorator) produto).getItalico();
        }
        return false;
    }

    public String formataParaImpressao() {
        return "<span style=\"color:" + super.getCor() + "\">" + super.produtoDecorado.formataParaImpressao() + "</span>";
    }
}
package Produto;

public abstract class ProdutoDecorator implements Produto {
    protected Produto produtoDecorado;
    private String cor;
    private boolean negrito;
    private boolean italico;

    public ProdutoDecorator(Produto produtoDecorado, String cor, boolean negrito, boolean italico) {
        this.produtoDecorado = produtoDecorado;
        this.cor = cor;
        this.negrito = negrito;
        this.italico = italico;
    }

    public void setQtdEstoque(int qtdEstoque) {
        this.produtoDecorado.setQtdEstoque(qtdEstoque);
    }

    public void setPreco(double preco) {
        this.produtoDecorado.setPreco(preco);
    }

    public int getId() {
        return this.produtoDecorado.getId();
    }

    public String getDescricao() {
        return this.produtoDecorado.getDescricao();
    }

    public String getCategoria() {
        return this.produtoDecorado.getCategoria();
    }

    public int getQtdEstoque() {
        return this.produtoDecorado.getQtdEstoque();
    }

    public double getPreco() {
        return this.produtoDecorado.getPreco();
    }

    public String getCor() {
        return this.cor;
    }

    public boolean getNegrito() {
        return this.negrito;
    }

    public boolean getItalico() {
        return this.italico;
    }

    public abstract String formataParaImpressao();
}

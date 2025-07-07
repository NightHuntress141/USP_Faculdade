package Exercícios.Controle_Remoto;

public class Controle_Samsung implements Controle_Remoto {

    // Atributos
    private int volume;
    private boolean ligando;
    private boolean tocando;

    // Construtor
    public Controle_Samsung() {
        this.volume = 50;
        this.ligando = false;
        this.tocando = false;
    }

    // Métodos padrões Getters e Setters
    public int getVolume() {
        return volume;
    }
    public boolean isLigando() {
        return ligando;
    }
    public boolean isTocando() {
        return tocando;
    }
    public void setVolume(int novoVolume) {
        this.volume = novoVolume;
    }
    public void setLigando(boolean ligado) {
        this.ligando = ligado;
    }
    public void setTocando(boolean tocando) {
        this.tocando = tocando;
    }

    // Implementação dos métodos da interface
    @Override
    public void Ligar() {
        this.setLigando(true);
        System.out.println("Dispositivo Samsung ligado");
    }

    @Override
    public void desligar() {
        this.setLigando(false);
        System.out.println("Dispositivo Samsung desligado");
    }

    @Override
    public void abrirMenu() {
        if (this.isLigando()) {
            System.out.println("----- MENU SAMSUNG -----");
            System.out.println("Está ligado? " + this.isLigando());
            System.out.println("Está tocando? " + this.isTocando());
            System.out.println("Volume: " + this.getVolume());
            for (int i = 0; i < this.getVolume(); i += 10) {
                System.out.print("|");
            }
            System.out.println();
        } else {
            System.out.println("Não é possível abrir o menu - dispositivo desligado");
        }
    }

    @Override
    public void fecharMenu() {
        if (this.isLigando()) {
            System.out.println("Fechando menu...");
        }
    }

    @Override
    public void maisVolume() {
        if (this.isLigando()) {
            this.setVolume(this.getVolume() + 5);
            System.out.println("Volume aumentado para: " + this.getVolume());
        } else {
            System.out.println("Não é possível aumentar volume - dispositivo desligado");
        }
    }

    @Override
    public void menosVolume() {
        if (this.isLigando()) {
            this.setVolume(this.getVolume() - 5);
            System.out.println("Volume diminuído para: " + this.getVolume());
        } else {
            System.out.println("Não é possível diminuir volume - dispositivo desligado");
        }
    }

    @Override
    public void ligarMudo() {
        if (this.isLigando() && this.getVolume() > 0) {
            this.setVolume(0);
            System.out.println("Mudo ativado");
        }
    }

    @Override
    public void desligarMudo() {
        if (this.isLigando() && this.getVolume() == 0) {
            this.setVolume(50);
            System.out.println("Mudo desativado");
        }
    }

    @Override
    public void play() {
        if (this.isLigando() && !this.isTocando()) {
            this.setTocando(true);
            System.out.println("Reproduzindo...");
        }
    }

    @Override
    public void pause() {
        if (this.isLigando() && this.isTocando()) {
            this.setTocando(false);
            System.out.println("Pausado...");
        }
    }
}

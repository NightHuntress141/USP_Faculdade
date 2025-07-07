package Exercícios.Bicycle;

public class Bicycle {
    // variáveis de instância da classe Bicycle
    public int cadence, gear, speed;
    
    // construtor da classe Bicycle
    public Bicycle(int startCadence, int startGear, int startSpeed) {
        cadence = startCadence;
        gear = startGear;
        speed = startSpeed;
    }
    
    // métodos da classe Bicycle
    public void setCadence(int newValue) {
        cadence = newValue;
    }
    
    public void setGear(int newValue) {
        gear = newValue;
    }
    
    public void applyBrake(int decrement) {
        speed -= decrement;
    }
    
    public void speedUp(int increment) {
        speed += increment;
    }
}

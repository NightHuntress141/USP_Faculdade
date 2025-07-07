package Exercícios.Bicycle;

public class MountainBike extends Bicycle {

    // a subclasse MountainBike adiciona um campo
    public int seatHeight;

    // construtor da subclasse MountainBike
    public MountainBike(int startHeight,
                        int startCadence,
                        int startSpeed,
                        int startGear) {
        super(startCadence, startSpeed, startGear);
        seatHeight = startHeight;
    }

    // a subclasse MountainBike adiciona um método
    public void setHeight(int newValue) {
        seatHeight = newValue;
    }
}
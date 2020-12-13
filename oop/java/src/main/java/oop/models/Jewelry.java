package oop.models;

public class Jewelry {
    private int id;
    private String name;
    private int jewelryCost;
    private int makingCost;

    public void setId(int id) {
        this.id = id;
    }

    public int getId() {
        return id;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setJewelryCost(int jewelryCost) {
        this.jewelryCost = jewelryCost;
    }

    public int getJewelryCost() {
        return jewelryCost;
    }

    public void setMakingCost(int makingCost) {
        this.makingCost = makingCost;
    }

    public int getMakingCost() {
        return makingCost;
    }
}

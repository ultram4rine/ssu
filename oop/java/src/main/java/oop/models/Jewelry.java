package oop.models;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;

public class Jewelry {
    private int id;
    private String name;
    private int jewelryCost;
    private int makingCost;

    public Jewelry(int id, String name, int jewelryCost, int makingCost) {
        setId(id);
        setName(name);
        setJewelryCost(jewelryCost);
        setMakingCost(makingCost);
    }

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

    public String toJSON() throws JsonProcessingException {
        return new ObjectMapper().writeValueAsString(this);
    }
}

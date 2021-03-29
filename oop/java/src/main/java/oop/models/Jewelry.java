package oop.models;

import java.sql.Connection;
import java.sql.SQLException;
import java.sql.Statement;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;

public class Jewelry {
    private int id;
    private String name;
    private int jewelryCost;
    private int makingCost;

    public Jewelry() {
    }

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

    public void saveToDB(Connection connection) {
        try {
            Statement statement = connection.createStatement();
            statement.setQueryTimeout(30);
            statement.executeUpdate("INSERT INTO jewelries(id, name, jewelry_cost, making_cost) VALUES (" + getId()
                    + ", '" + getName() + "', " + getJewelryCost() + ", " + getMakingCost() + ")");
        } catch (SQLException e) {
            System.err.println("Error inserting jewelry: " + e.getMessage());
        }
    }
}

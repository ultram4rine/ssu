package oop.models;

import java.sql.Connection;
import java.sql.SQLException;
import java.sql.Statement;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;

public class Sale {
    private int id;
    private Jewelry jewelry;
    private Customer customer;

    public Sale() {
    }

    public Sale(int id, Jewelry jewelry, Customer customer) {
        setId(id);
        setJewelry(jewelry);
        setCustomer(customer);
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getId() {
        return id;
    }

    public void setJewelry(Jewelry jewelry) {
        this.jewelry = jewelry;
    }

    public Jewelry getJewelry() {
        return jewelry;
    }

    public void setCustomer(Customer customer) {
        this.customer = customer;
    }

    public Customer getCustomer() {
        return customer;
    }

    public String toJSON() throws JsonProcessingException {
        return new ObjectMapper().writeValueAsString(this);
    }

    public void saveToDB(Connection connection) {
        try {
            Statement statement = connection.createStatement();
            statement.setQueryTimeout(30);
            statement.executeUpdate("INSERT INTO sales(id, jewelry_id, customer_id) VALUES (" + getId() + ", "
                    + getJewelry().getId() + ", " + getCustomer().getId() + ")");
        } catch (SQLException e) {
            System.err.println("Error inserting sale: " + e.getMessage());
        }
    }
}

package oop.models;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.List;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;

// JewelryStore is singleton.
public class JewelryStore {
    public List<Jewelry> jewelries;
    public List<Customer> customers;
    public List<Sale> sales;

    private static JewelryStore instance;

    private JewelryStore() {
    }

    public static JewelryStore getInstance() {
        if (instance == null) {
            instance = new JewelryStore();
        }
        return instance;
    }

    public String toJSON() throws JsonProcessingException {
        return new ObjectMapper().writeValueAsString(this);
    }

    public void writeJSON(String fileName) throws IOException {
        try {
            String json = toJSON();

            BufferedWriter writer = new BufferedWriter(new FileWriter(fileName));
            writer.write(json);

            writer.close();
        } catch (JsonProcessingException e) {
            System.err.println(e.getMessage());
        }
    }
}

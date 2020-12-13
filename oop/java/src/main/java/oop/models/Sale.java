package oop.models;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;

public class Sale {
    private int id;
    private int jewelryId;
    private int customerId;

    public Sale(int id, int jewelryId, int customerId) {
        setId(id);
        setJewelryId(jewelryId);
        setCustomerId(customerId);
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getId() {
        return id;
    }

    public void setJewelryId(int jewelryId) {
        this.jewelryId = jewelryId;
    }

    public int getJewelryId() {
        return jewelryId;
    }

    public void setCustomerId(int customerId) {
        this.customerId = customerId;
    }

    public int getCustomerId() {
        return customerId;
    }

    public String toJSON() throws JsonProcessingException {
        return new ObjectMapper().writeValueAsString(this);
    }
}

package oop.models;

import java.util.regex.Pattern;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;

public class Customer {
    private int id;
    private String name;
    private String surname;
    private String phone;
    private String address;

    private Pattern phoneRegex = Pattern.compile("^(\\d{3}[- .]?){2}\\d{4}$");

    public Customer(int id, String name, String surname, String phone, String address) {
        setId(id);
        setName(name);
        setSurname(surname);
        setPhone(phone);
        setAddress(address);
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

    public void setSurname(String surname) {
        this.surname = surname;
    }

    public String getSurname() {
        return surname;
    }

    public void setPhone(String phone) throws IllegalArgumentException {
        if (phoneRegex.matcher(phone).matches()) {
            this.phone = phone;
        } else {
            throw new IllegalArgumentException("Wrong phone number.");
        }
    }

    public String getPhone() {
        return phone;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    public String getAddress() {
        return address;
    }

    public String toJSON() throws JsonProcessingException {
        return new ObjectMapper().writeValueAsString(this);
    }
}

package oop;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;

import oop.models.Customer;
import oop.models.Jewelry;
import oop.models.JewelryStore;
import oop.models.Sale;

public class App {
    public static void main(String[] args) {
        Connection connection = null;
        try {
            connection = DriverManager.getConnection("jdbc:sqlite:sqlite.db");

            Statement statement = connection.createStatement();
            statement.setQueryTimeout(30);

            try {
                String schema = new String(Files.readAllBytes(Paths.get("src/main/sql/schema.sql")));
                statement.execute(schema);
            } catch (IOException e) {
                System.err.println(e.getMessage());
            }
        } catch (SQLException e) {
            System.err.println(e.getMessage());
        } finally {
            try {
                if (connection != null)
                    connection.close();
            } catch (SQLException e) {
                System.err.println(e.getMessage());
            }
        }

        Jewelry goldRing = new Jewelry(1, "Gold Ring", 800, 600);
        Jewelry silverRingWithDiamond = new Jewelry(2, "Silver Ring with Diamond", 1500, 1300);

        Customer AlexGoldman = new Customer(1, "Alex", "Goldman", "202-555-0125", "West Avenue");

        Sale sale1 = new Sale(1, 1, 1);
        Sale sale2 = new Sale(1, 2, 1);

        JewelryStore store = JewelryStore.getInstance();

        store.jewelries = new ArrayList<Jewelry>();
        store.jewelries.add(goldRing);
        store.jewelries.add(silverRingWithDiamond);

        store.customers = new ArrayList<Customer>();
        store.customers.add(AlexGoldman);

        store.sales = new ArrayList<Sale>();
        store.sales.add(sale1);
        store.sales.add(sale2);

        try {
            store.writeJSON("store.json");
        } catch (IOException e) {
            System.err.println(e.getMessage());
        }
    }
}

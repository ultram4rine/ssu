package oop;

import java.io.IOException;
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

            statement.execute(
                    "CREATE TABLE IF NOT EXISTS jewelries ('id' INTEGER PRIMARY KEY, 'name' VARCHAR (190) NOT NULL, 'jewelry_cost' INTEGER NOT NULL, 'making_cost' INTEGER NOT NULL, UNIQUE(name))");

            statement.execute(
                    "CREATE TABLE IF NOT EXISTS customers ('id' INTEGER PRIMARY KEY, 'name' VARCHAR (30) NOT NULL, 'surname' VARCHAR (30) NOT NULL, 'phone' VARCHAR(11) NOT NULL, 'address' VARCHAR(50) NOT NULL, UNIQUE(name, surname, phone))");

            statement.execute(
                    "CREATE TABLE IF NOT EXISTS sales ('id' INTEGER PRIMARY KEY, 'jewelry_id' INTEGER, 'customer_id' INTEGER, FOREIGN KEY (jewelry_id) REFERENCES jewelries (id) ON DELETE NO ACTION, FOREIGN KEY (customer_id) REFERENCES customers (id) ON DELETE NO ACTION)");

            Jewelry goldRing = new Jewelry(1, "Gold Ring", 800, 600);

            Customer AlexGoldman = new Customer(1, "Alex", "Goldman", "202-555-0125", "West Avenue");

            Sale sale1 = new Sale(1, goldRing, AlexGoldman);

            JewelryStore store = new JewelryStore(new ArrayList<Jewelry>(), new ArrayList<Customer>(),
                    new ArrayList<Sale>());

            store.addJewelry(goldRing);
            store.addCustomer(AlexGoldman);
            store.addSale(sale1);

            try {
                store.writeJSON("store.json");
            } catch (IOException e) {
                System.err.println(e.getMessage());
            }

            store.writeJewelriesToDB(connection);
            store.writeCustomersToDB(connection);
            store.writeSalesToDB(connection);

            Jewelry silverRingWithDiamond = new Jewelry(2, "Silver_Ring_with_Diamond", 1500, 1300);
            Sale sale2 = new Sale(1, silverRingWithDiamond, AlexGoldman);

            store.addJewelry(silverRingWithDiamond);
            store.addSale(sale2);

            store.readJewelriesFromDB(connection);
            store.readCustomersFromDB(connection);
            store.readSalesFromDB(connection);

            System.out.println(store.getSales().get(0).getId());
        } catch (SQLException e) {
            System.err.println(e.getMessage());
        } finally {
            try {
                if (connection != null) {
                    Statement dropStmt = connection.createStatement();

                    dropStmt.execute("DROP TABLE jewelries");
                    dropStmt.execute("DROP TABLE customers");
                    dropStmt.execute("DROP TABLE sales");

                    connection.close();
                }
            } catch (SQLException e) {
                System.err.println(e.getMessage());
            }
        }
    }
}

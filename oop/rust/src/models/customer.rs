extern crate serde;

use crate::db::db::DB;
use crate::lists::lists::List;
use rusqlite::{params, Connection, Result, NO_PARAMS};
use serde::{Deserialize, Serialize};

#[derive(Clone, Debug, Serialize, Deserialize, PartialEq)]
pub struct Customer {
    pub id: i32,
    pub name: String,
    pub phone: String,
}

impl Customer {
    pub fn new(id: i32, name: String, phone: String) -> Customer {
        Customer {
            id: id,
            name: name,
            phone: phone,
        }
    }
}

pub type CustomersList = Vec<Customer>;

impl DB<Customer> for CustomersList {
    fn to_db(&self, conn: &Connection) -> Result<()> {
        for c in self {
            conn.execute(
                "INSERT INTO customers (id, name, phone) VALUES (?1, ?2, ?3)",
                params![c.id, c.name, c.phone],
            )?;
        }
        Ok(())
    }

    fn from_db(&self, conn: &Connection) -> Result<CustomersList> {
        let mut stmt = conn.prepare("SELECT id, name, phone FROM customers")?;
        let iter = stmt.query_map(NO_PARAMS, |row| {
            Ok(Customer::new(row.get(0)?, row.get(1)?, row.get(2)?))
        })?;

        let mut customers = Vec::new();
        for c in iter {
            customers.push(c?)
        }

        Ok(CustomersList::new_list(customers))
    }
}

impl List<Customer> for CustomersList {
    fn new_list(customers: Vec<Customer>) -> CustomersList {
        customers
    }

    fn add_item(&mut self, customer: Customer) {
        let item = self.to_vec().into_iter().find(|x| x == &customer);
        match item {
            Some(c) => println!("Customers list already contains customer with {} id", c.id),
            None => self.push(customer),
        }
    }

    fn remove_item(&mut self, customer: Customer) {
        let item = self.to_vec().into_iter().find(|x| x == &customer);
        match item {
            Some(_) => {
                let index = self.iter().position(|x| *x == customer).unwrap();
                self.remove(index);
            }
            None => println!(
                "Customers list doesn't contains customer with {} id",
                customer.id
            ),
        }
    }
}

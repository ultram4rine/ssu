extern crate serde;

use crate::lists::lists::List;
use serde::{Deserialize, Serialize};

#[derive(Clone, Debug, Serialize, Deserialize, PartialEq)]
pub struct Customer {
    pub id: u64,
    pub name: String,
    pub phone: String,
}

impl Customer {
    pub fn new(id: u64, name: String, phone: String) -> Customer {
        Customer {
            id: id,
            name: name,
            phone: phone,
        }
    }
}

pub type CustomersList = Vec<Customer>;

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

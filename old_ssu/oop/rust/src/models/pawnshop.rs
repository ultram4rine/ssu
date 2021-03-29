extern crate serde;

use crate::db::db::DB;
use crate::lists::lists::List;
use crate::models::contract::{Contract, ContractsList};
use crate::models::customer::{Customer, CustomersList};
use crate::models::product::{Product, ProductsList};
use serde::{Deserialize, Serialize};
use serde_json::{from_str, to_string_pretty};
use std::fs;
use std::io::Write;

#[derive(Debug, Serialize, Deserialize, PartialEq)]
pub struct Pawnshop {
    pub contracts: ContractsList,
    pub customers: CustomersList,
    pub products: ProductsList,
}

impl Pawnshop {
    pub fn new(
        contracts: ContractsList,
        customers: CustomersList,
        products: ProductsList,
    ) -> Pawnshop {
        Pawnshop {
            contracts: contracts,
            customers: customers,
            products: products,
        }
    }

    pub fn from_json(path: String) -> Option<Pawnshop> {
        let content = fs::read_to_string(path);
        match content {
            Ok(v) => match from_str(&v) {
                Ok(v) => v,
                Err(e) => {
                    println!("cant't transform XML to pawnshop: {}", e);
                    None
                }
            },
            Err(e) => {
                println!("can't read file: {}", e);
                None
            }
        }
    }

    pub fn to_json(&self, path: String) {
        let mut file = match fs::File::create(&path) {
            Ok(file) => file,
            Err(e) => {
                println!("couldn't create XML file: {}", e);
                return;
            }
        };

        let xml = match to_string_pretty(self) {
            Ok(xml) => xml,
            Err(e) => {
                println!("couldn't serialize XML: {}", e);
                return;
            }
        };

        match file.write_all(xml.as_bytes()) {
            Ok(_) => (),
            Err(e) => println!("couldn't write to XML file: {}", e),
        }
    }

    pub fn add_product(&mut self, product: Product) {
        self.products.add_item(product);
    }
    pub fn remove_product(&mut self, product: Product) {
        self.products.remove_item(product);
    }

    pub fn add_customer(&mut self, customer: Customer) {
        self.customers.add_item(customer);
    }
    pub fn remove_customer(&mut self, customer: Customer) {
        self.customers.remove_item(customer);
    }

    pub fn add_contract(&mut self, contract: Contract) {
        self.contracts.add_item(contract);
    }
    pub fn remove_contract(&mut self, contract: Contract) {
        self.contracts.remove_item(contract);
    }
}

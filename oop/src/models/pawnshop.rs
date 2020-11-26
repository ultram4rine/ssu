extern crate quick_xml;
extern crate serde;

use serde::{Deserialize, Serialize};

use quick_xml::de::from_str;
use quick_xml::se::to_string;
use std::fs;
use std::io::Write;

use crate::models::contract::{Contract, ContractsList};
use crate::models::customer::{Customer, CustomersList};
use crate::models::product::{Product, ProductsList};

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

    pub fn from_xml(path: String) -> Option<Pawnshop> {
        let content = fs::read_to_string(path);
        match content {
            Ok(v) => from_str(&v).unwrap(),
            Err(_) => None,
        }
    }
    pub fn to_xml(&self, path: String) {
        let mut file = match fs::File::create(&path) {
            Err(e) => panic!("couldn't create XML file: {}", e),
            Ok(file) => file,
        };

        let mut xml = match to_string(self) {
            Err(e) => panic!("couldn't serialize XML: {}", e),
            Ok(xml) => xml,
        };

        match file.write_all(xml.as_bytes()) {
            Err(e) => panic!("couldn't write to XML file: {}", e),
            Ok(_) => (),
        }
    }

    pub fn add_product(&mut self, product: Product) {
        self.products.add(product);
    }
    pub fn remove_product(&mut self, product: Product) {
        self.products.remove(product);
    }

    pub fn add_customer(&mut self, customer: Customer) {
        self.customers.add(customer);
    }
    pub fn remove_customer(&mut self, customer: Customer) {
        self.customers.remove(customer);
    }

    pub fn add_contract(&mut self, contract: Contract) {
        self.contracts.add(contract);
    }
    pub fn remove_contract(&mut self, contract: Contract) {
        self.contracts.remove(contract);
    }
}

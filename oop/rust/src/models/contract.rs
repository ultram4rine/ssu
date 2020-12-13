extern crate serde;

use serde::{Deserialize, Serialize};

use crate::lists::lists::ListMethods;
use crate::models::customer::Customer;
use crate::models::product::Product;

#[derive(Clone, Debug, Serialize, Deserialize, PartialEq)]
pub struct Contract {
    pub id: u64,
    pub customer: Customer,
    pub products: Vec<Product>,
    pub return_date: String,
    pub factual_return_date: String,
    pub start_cost: u64,
    pub buyback_cost: u64,
    pub closed: bool,
}

impl Contract {
    pub fn new(
        id: u64,
        customer: Customer,
        products: Vec<Product>,
        return_date: String,
        factual_return_date: String,
        start_cost: u64,
        buyback_cost: u64,
        closed: bool,
    ) -> Contract {
        Contract {
            id: id,
            customer: customer,
            products: products,
            return_date: return_date,
            factual_return_date: factual_return_date,
            start_cost: start_cost,
            buyback_cost: buyback_cost,
            closed: closed,
        }
    }
}

pub type ContractsList = Vec<Contract>;

impl ListMethods<Contract> for ContractsList {
    fn new_list(contracts: Vec<Contract>) -> Self {
        contracts
    }

    fn add_item(&mut self, contract: Contract) {
        let item = self.to_vec().into_iter().find(|x| x == &contract);
        match item {
            Some(c) => println!("Contracts list already contains contract with {} id", c.id),
            None => self.push(contract),
        }
    }

    fn remove_item(&mut self, contract: Contract) {
        let item = self.to_vec().into_iter().find(|x| x == &contract);
        match item {
            Some(_) => {
                let index = self.iter().position(|x| *x == contract).unwrap();
                self.remove(index);
            }
            None => println!(
                "Contracts list doesn't contains contract with {} id",
                contract.id
            ),
        }
    }
}

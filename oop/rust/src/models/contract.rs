extern crate serde;

use serde::{Deserialize, Serialize};

use crate::db::db::DB;
use crate::lists::lists::List;
use crate::models::customer::Customer;
use crate::models::product::Product;
use rusqlite::{params, Connection, Result, NO_PARAMS};

#[derive(Clone, Debug, Serialize, Deserialize, PartialEq)]
pub struct Contract {
    pub id: i32,
    pub customer: Customer,
    pub products: Vec<Product>,
    pub return_date: String,
    pub factual_return_date: String,
    pub start_cost: i32,
    pub buyback_cost: i32,
    pub closed: bool,
}

impl Contract {
    pub fn new(
        id: i32,
        customer: Customer,
        products: Vec<Product>,
        return_date: String,
        factual_return_date: String,
        start_cost: i32,
        buyback_cost: i32,
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

impl DB<Contract> for ContractsList {
    fn to_db(&self, conn: &Connection) -> Result<()> {
        for c in self {
            conn.execute(
                "INSERT INTO contracts (id, customer_id, return_date, factual_return_date, start_cost, buyback_cost, closed) VALUES(?1, ?2, ?3, ?4, ?5, ?6, ?7)",
                params![c.id, c.customer.id, c.return_date,c.factual_return_date,c.start_cost,c.buyback_cost,c.closed]
            )?;
            for p in c.products.clone() {
                conn.execute(
                    "INSERT INTO contracts_products (contract_id, product_id) VALUES (?1, ?2)",
                    params![c.id, p.id],
                )?;
            }
        }
        Ok(())
    }

    fn from_db(conn: &Connection) -> Result<ContractsList> {
        let mut stmt = conn.prepare("SELECT id, customer_id, return_date, factual_return_date, start_cost, buyback_cost, closed FROM contracts")?;
        let iter = stmt.query_map(NO_PARAMS, |row| {
            let mut stmt_c = conn.prepare("SELECT name, phone FROM customers WHERE id = ?1")?;
            let customer_id:i32 = row.get(1)?;
            let iter_c = stmt_c.query_map(params![customer_id], |c| {
                Ok(Customer::new(row.get(1)?, c.get(0)?, c.get(1)?))
            })?;

            let mut customer=Customer{id:0,name:"".to_string(),phone:"".to_string()};
            for c in iter_c {
                customer=c?;
            };

            let mut stmt_p =
                conn.prepare("SELECT id, name, cost FROM products WHERE id = (SELECT product_id FROM contracts_products WHERE contract_id = ?1)")?;
            let contract_id:i32=row.get(0)?;
            let iter_p = stmt_p.query_map(params![contract_id], |p| {
                Ok(Product::new(p.get(0)?, p.get(1)?, p.get(2)?))
            })?;

            let mut products = Vec::new();
            for p in iter_p {
                products.push(p?);
            };

            Ok(Contract::new(row.get(0)?, customer, products, row.get(2)?, row.get(3)?, row.get(4)?, row.get(5)?, row.get(6)?))
        })?;

        let mut contracts = Vec::new();
        for contract in iter {
            contracts.push(contract?)
        }

        Ok(ContractsList::new_list(contracts))
    }
}

impl List<Contract> for ContractsList {
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

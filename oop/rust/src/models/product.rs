extern crate serde;

use crate::lists::lists::ListMethods;
use serde::{Deserialize, Serialize};

#[derive(Clone, Debug, Serialize, Deserialize, PartialEq)]
pub struct Product {
    pub id: u64,
    pub name: String,
    pub cost: u64,
}

impl Product {
    pub fn new(id: u64, name: String, cost: u64) -> Product {
        Product {
            id: id,
            name: name,
            cost: cost,
        }
    }
}

pub type ProductsList = Vec<Product>;

impl ListMethods<Product> for ProductsList {
    fn new_list(products: Vec<Product>) -> ProductsList {
        products
    }

    fn add_item(&mut self, product: Product) {
        let item = self.to_vec().into_iter().find(|x| x == &product);
        match item {
            Some(p) => println!("Products list already contains customer with {} id", p.id),
            None => self.push(product),
        }
    }

    fn remove_item(&mut self, product: Product) {
        let item = self.to_vec().into_iter().find(|x| x == &product);
        match item {
            Some(_) => {
                let index = self.iter().position(|x| *x == product).unwrap();
                self.remove(index);
            }
            None => println!(
                "Products list doesn't contains product with {} id",
                product.id
            ),
        }
    }
}

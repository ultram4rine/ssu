extern crate serde;

use crate::db::db::DB;
use crate::lists::lists::List;
use rusqlite::{params, Connection, Result, NO_PARAMS};
use serde::{Deserialize, Serialize};

#[derive(Clone, Debug, Serialize, Deserialize, PartialEq)]
pub struct Product {
    pub id: i32,
    pub name: String,
    pub cost: i32,
}

impl Product {
    pub fn new(id: i32, name: String, cost: i32) -> Product {
        Product {
            id: id,
            name: name,
            cost: cost,
        }
    }

    pub fn to_db(&self, conn: Connection) -> Result<()> {
        conn.execute(
            "INSERT INTO products (id, name, cost) VALUES(?1, ?2, ?3)",
            params![self.id, self.name, self.cost],
        )?;
        Ok(())
    }
}

pub type ProductsList = Vec<Product>;

impl DB<Product> for ProductsList {
    fn to_db(&self, conn: &Connection) -> Result<()> {
        for p in self {
            conn.execute(
                "INSERT INTO products (id, name, cost) VALUES (?1, ?2, ?3)",
                params![p.id, p.name, p.cost],
            )?;
        }
        Ok(())
    }

    fn from_db(conn: &Connection) -> Result<ProductsList> {
        let mut stmt = conn.prepare("SELECT id, name, cost FROM products")?;
        let iter = stmt.query_map(NO_PARAMS, |row| {
            Ok(Product::new(row.get(0)?, row.get(1)?, row.get(2)?))
        })?;

        let mut products = Vec::new();
        for p in iter {
            products.push(p?)
        }

        Ok(ProductsList::new_list(products))
    }
}

impl List<Product> for ProductsList {
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

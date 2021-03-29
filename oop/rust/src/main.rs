mod db;
mod lists;
mod models;

use chrono::prelude::*;
use db::db::DB;
use lists::lists::List;
use models::contract::{Contract, ContractsList};
use models::customer::{Customer, CustomersList};
use models::pawnshop::Pawnshop;
use models::product::{Product, ProductsList};

use rusqlite::{Connection, Result, NO_PARAMS};

fn main() -> Result<()> {
    let conn = Connection::open("sqlite.db")?;

    conn.execute(
        "CREATE TABLE IF NOT EXISTS products (
            id              INTEGER PRIMARY KEY,
            name            TEXT NOT NULL,
            cost            INTEGER
        )",
        NO_PARAMS,
    )?;
    conn.execute(
        "   CREATE TABLE IF NOT EXISTS customers (
            id              INTEGER PRIMARY KEY,
            name            TEXT NOT NULL,
            phone           TEXT NOT NULL
        )",
        NO_PARAMS,
    )?;
    conn.execute(
            " CREATE TABLE IF NOT EXISTS contracts (
            id INT              INTEGER PRIMARY KEY,
            customer_id         INT,
            return_date         TEXT,
            factual_return_date TEXT,
            start_cost          INT,
            buyback_cost        INT,
            closed              INT,
            FOREIGN KEY (customer_id) REFERENCES customers (id) ON DELETE NO ACTION ON UPDATE CASCADE
        )",
        NO_PARAMS,)?;
    conn.execute(
        "
        CREATE TABLE IF NOT EXISTS contracts_products (
            contract_id INT,
            product_id  INT,
            FOREIGN KEY (contract_id) REFERENCES contracts (id) ON DELETE CASCADE ON UPDATE CASCADE,
            FOREIGN KEY (product_id) REFERENCES products (id) ON DELETE NO ACTION ON UPDATE CASCADE
        );",
        NO_PARAMS,
    )?;

    let p = Product::new(1, "Gold Ring".to_string(), 600);
    let cust = Customer::new(1, "John Johnson".to_string(), "89990000000".to_string());
    let cont = Contract::new(
        1,
        cust.clone(),
        vec![p.clone()],
        Utc.ymd(2020, 11, 28).to_string(),
        Utc.ymd(2020, 11, 30).to_string(),
        600,
        700,
        true,
    );

    let mut pawnshop = Pawnshop::new(
        ContractsList::new_list(vec![cont.clone()]),
        CustomersList::new_list(vec![cust.clone()]),
        ProductsList::new_list(vec![p.clone()]),
    );
    pawnshop.to_json("pawnshop.json".to_string());

    pawnshop.add_product(Product::new(2, "Silver Ring".to_string(), 400));
    pawnshop.to_json("pawnshop.json".to_string());
    pawnshop.customers.to_db(&conn)?;
    pawnshop.products.to_db(&conn)?;
    pawnshop.contracts.to_db(&conn)?;

    // proof that something exists in db.
    let contracts_from_db = pawnshop.contracts.from_db(&conn)?;
    for c in contracts_from_db {
        println!(
            "id: {}, customer: {}, closed: {}",
            c.id, c.customer.name, c.closed
        );
        println!("products in contract:");
        for p in c.products {
            println!("{}", p.name);
        }
    }

    // Drop tables to correctly rerun program.
    conn.execute(
        "DROP TABLE IF EXISTS products;
        DROP TABLE IF EXISTS customers;
        DROP TABLE IF EXISTS contracts;
        DROP TABLE IF EXISTS contracts_products;",
        NO_PARAMS,
    )?;

    Ok(())
}

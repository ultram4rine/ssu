mod models;

use models::contract::{Contract, ContractsList};
use models::customer::{Customer, CustomersList};
use models::pawnshop::Pawnshop;
use models::product::{Product, ProductsList};

use rusqlite::{Connection, Result, NO_PARAMS};

fn main() -> Result<()> {
    let conn = Connection::open("sqlite.db")?;

    conn.execute(
        "CREATE TABLE IF NOT EXISTS product (
            id              INTEGER PRIMARY KEY,
            name            TEXT NOT NULL,
            cost            INTEGER
        );
        CREATE TABLE IF NOT EXISTS customer (
            id              INTEGER PRIMARY KEY,
            name            TEXT NOT NULL,
            phone           TEXT NOT NULL
        );
        CREATE TABLE IF NOT EXISTS contracts (
            id INT              INTEGER PRIMARY KEY,
            customer_id         INT,
            return_date         TEXT,
            factual_return_date TEXT,
            start_cost          INT,
            buyback_cost        INT,
            closed              INT,
            FOREIGN KEY (customer_id) REFERENCES customers (id) ON DELETE NO ACTION ON UPDATE CASCADE
        );
        CREATE TABLE IF NOT EXISTS contracts_products (
            contract_id INT,
            product_id  INT,
            FOREIGN KEY (contract_id) REFERENCES contracts (id) ON DELETE CASCADE ON UPDATE CASCADE,
            FOREIGN KEY (product_id) REFERENCES products (id) ON DELETE NO ACTION ON UPDATE CASCADE
        );",
        NO_PARAMS,
    )?;

    let p = Product::new(1, "Gold Ring".to_string(), 600);
    let cust = Customer::new(1, "Some name".to_string(), "89990000000".to_string());
    let cont = Contract::new(
        1,
        cust.clone(),
        vec![p.clone()],
        "rdate".to_string(),
        "frdate".to_string(),
        600,
        700,
        false,
    );

    let pawnshop = Pawnshop::new(
        ContractsList::new(vec![cont.clone()]),
        CustomersList::new(vec![cust.clone()]),
        ProductsList::new(vec![p.clone()]),
    );
    pawnshop.to_xml("pawnshop.xml".to_string());

    Ok(())
}

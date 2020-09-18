CREATE TABLE IF NOT EXISTS products (id INT PRIMARY KEY, name TEXT, cost INT);
CREATE TABLE IF NOT EXISTS customers (id INT PRIMARY KEY, name TEXT, phone TEXT);
CREATE TABLE IF NOT EXISTS contracts (
    id INT PRIMARY KEY,
    customer_id INT,
    return_date TEXT,
    factual_return_date TEXT,
    start_cost INT,
    buyback_cost INT,
    closed INT,
    FOREIGN KEY (customer_id) REFERENCES customers (id) ON DELETE NO ACTION ON UPDATE CASCADE
);
CREATE TABLE IF NOT EXISTS contracts_products (
    contract_id INT,
    product_id INT,
    FOREIGN KEY (contract_id) REFERENCES contracts (id) ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (product_id) REFERENCES products (id) ON DELETE NO ACTION ON UPDATE CASCADE
);
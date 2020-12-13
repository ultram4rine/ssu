CREATE TABLE IF NOT EXISTS jewelries (
    id INTEGER PRIMARY KEY,
    name VARCHAR (190) NOT NULL,
    jewelry_cost VARCHAR(15) NOT NULL,
    making_cost VARCHAR(15) NOT NULL,
    UNIQUE(name)
);
CREATE TABLE IF NOT EXISTS customer (
    id INTEGER PRIMARY KEY,
    name VARCHAR (30) NOT NULL,
    surname VARCHAR (30) NOT NULL,
    phone VARCHAR(11) NOT NULL,
    address VARCHAR(50) NOT NULL,
    UNIQUE(name, surname, phone)
);
CREATE TABLE IF NOT EXISTS sales (
    id INTEGER PRIMARY KEY,
    jewerly_id INTEGER,
    customer_id INTEGER,
    FOREIGN KEY (jewerly_id) REFERENCES jewelries (id) ON DELETE NO ACTION,
    FOREIGN KEY (customer_id) REFERENCES customers (id) ON DELETE NO ACTION,
);
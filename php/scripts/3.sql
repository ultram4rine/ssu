CREATE TABLE IF NOT EXISTS bill (
    bid INT PRIMARY KEY AUTO_INCREMENT,
    num INT,
    bdate DATE,
    name VARCHAR(255)
);
CREATE TABLE IF NOT EXISTS payment (
    id INT PRIMARY KEY AUTO_INCREMENT,
    bid INT,
    pdate DATE,
    summa FLOAT,
    FOREIGN KEY (bid) REFERENCES bill (bid)
);
CREATE TABLE IF NOT EXISTS bill_content (
    id INT PRIMARY KEY AUTO_INCREMENT,
    goods VARCHAR(255),
    price FLOAT,
    quantity FLOAT,
    bid INT,
    FOREIGN KEY (bid) REFERENCES bill (bid)
);
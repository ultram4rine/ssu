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
INSERT INTO bill
VALUES(1, 1, "2010-01-12", "Oracle"),
    (2, 2, "2010-03-12", "Oracle"),
    (3, 3, "2010-02-12", "Microsoft");
INSERT INTO bill_content
VALUES(1, "computers", 1000, 3, 3),
    (2, "network adapters", 400, 3, 3),
    (3, "licenses", 500, 4, 1),
    (4, "software", 100, 4, 2),
    (5, "licenses", 600, 5, 1),
    (6, "software", 200, 5, 2),
    (7, "hardware", 800, 2, 3),
    (8, "hardware", 200, 3, 1),
    (9, "hardware", 300, 7, 2),
    (10, "hardware", 400, 1, 3);
INSERT INTO payment
VALUES(1, 1, "2010-02-12", 3000),
    (2, 1, "2010-04-12", 600),
    (3, 2, "2010-03-12", 2700),
    (4, 2, "2010-05-12", 100);
CREATE TABLE users (
    id INT PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(50) NOT NULL UNIQUE,
    password_hash VARCHAR(255) NOT NULL,
    root BOOLEAN NOT NULL,
    full_name VARCHAR(100) NOT NULL,
    last_accessed_at DATETIME NOT NULL
);
CREATE TABLE tasks (
    id INT PRIMARY KEY AUTO_INCREMENT,
    created_at DATETIME NOT NULL,
    user_id INT NOT NULL,
    planned_closed_at DATE NOT NULL,
    closed_at DATE NULL,
    name VARCHAR(50) NOT NULL UNIQUE,
    description TEXT NOT NULL,
    FOREIGN KEY (user_id) REFERENCES users (id) ON DELETE CASCADE ON UPDATE CASCADE
);
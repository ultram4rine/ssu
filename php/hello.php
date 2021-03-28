<?php
require_once 'conn.php';

$mysqli = new mysqli($host, $user, $password, $database);

if ($mysqli->connect_errno) {
    printf("Соединение не удалось: %s\n", $mysqli->connect_error);
    exit();
}

$result = $mysqli->query("SELECT * FROM users"); 
if (!$result)
{
    printf("Сообщение ошибки: %s\n", $mysqli->error);
} else {
    echo "Выполнение запроса прошло успешно";
}

$mysqli->close();
?>
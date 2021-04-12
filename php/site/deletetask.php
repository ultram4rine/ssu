<?php
    if ($_SERVER["REQUEST_METHOD"] == "DELETE") {
        $id = htmlspecialchars($_GET["id"]);
        if (!empty($id)) {
            require_once 'conn.php';

            $mysqli = new mysqli($host, $user, $password, $database);
            if ($mysqli->connect_errno) {
                printf("Соединение не удалось: %s\n", $mysqli->connect_error);
                exit();
            }

            $result = $mysqli->query("DELETE FROM tasks WHERE id = $id");

            $mysqli->close();
        }
        header('Location: gantt.php');
    }
?>
<!DOCTYPE html>
<html>

<head>
    <meta charset="UTF-8">
    <link type="text/css" rel="stylesheet" href="public/css/global.css">
    <link type="text/css" rel="stylesheet" href="public/css/header.css">
    <link type="text/css" rel="stylesheet"
        href="https://cdn.jsdelivr.net/npm/select2@4.1.0-rc.0/dist/css/select2.min.css" />
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"
        integrity="sha256-/xUj+3OJU5yExlq6GSYGSHk7tPXikynS7ogEvDej/m4=" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/select2@4.1.0-rc.0/dist/js/select2.min.js"></script>
    <style>
        input,
        textarea,
        select {
            width: 150px;
            margin: 0;

            -webkit-box-sizing: border-box;
            -moz-box-sizing: border-box;
            box-sizing: border-box;
        }
    </style>
</head>

<body>
    <?php echo file_get_contents("public/html/header.html"); ?>
    <form action="adduser.php" method="POST">
        <label for="username">Логин: </label>
        <input id="username" name="username" type="text" required="required" maxlength="50" /> <br />

        <label for="password">Пароль: </label>
        <input id="password" name="password" type="password" required="required" maxlength="20" /> <br />

        <label for="fullname">Полное имя: </label>
        <input id="fullname" name="fullname" type="text" required="required" maxlength="100" /> <br />

        <label for="root">Права администратора: </label>
        <input id="root" name="root" type="checkbox" /> <br />

        <input type="submit" value="Добавить пользователя" />
    </form>
</body>

</html>

<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    require_once 'conn.php';

    $mysqli = new mysqli($host, $user, $password, $database);

    if ($mysqli->connect_errno) {
        printf("Соединение не удалось: %s\n", $mysqli->connect_error);
        exit();
    }

    $username = htmlentities($mysqli->real_escape_string($_POST['username']));
    $password_hash = password_hash(htmlentities($mysqli->real_escape_string($_POST['password'])), PASSWORD_DEFAULT);
    $root = isset($_POST['root']);
    $fullname = htmlentities($mysqli->real_escape_string($_POST['fullname']));

    $result = $mysqli->query("SELECT username FROM users WHERE username == '$username'");
    if (!$result) {
        $res = $mysqli->query("INSERT INTO users VALUES(NULL, '$username', '$password_hash', '$root', '$fullname', NOW())");
        if ($res) {
            echo "<span style='color:blue;'>Данные добавлены</span>";
        } else {
            echo "<span style='color:blue;'>Пиздец '$mysqli->error'</span>";
        }
    } else {
        print("<script>alert('Пользователь уже зарегистрирован');</script>");
    }

    $mysqli->close();
}
?>
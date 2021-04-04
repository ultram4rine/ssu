<!DOCTYPE html>
<html>

<head>
    <meta charset="UTF-8">
    <link type="text/css" rel="stylesheet" href="public/css/global.css">
    <link type="text/css" rel="stylesheet" href="public/css/header.css">
    <link type="text/css" rel="stylesheet" href="public/css/form.css">
</head>

<body>
    <div class="box">
        <?php echo file_get_contents("public/html/header.html"); ?>
        <main>
            <div class="container">
                <form action="adduser.php" method="POST">
                    <div class="row">
                        <div class="col-25">
                            <label for="username">Логин</label>
                        </div>
                        <div class="col-75">
                            <input id="username" name="username" type="text" required="required" maxlength="50" />
                        </div>
                    </div>

                    <div class="row">
                        <div class="col-25">
                            <label for="password">Пароль</label>
                        </div>
                        <div class="col-75">
                            <input id="password" name="password" type="password" required="required" maxlength="20" />
                        </div>
                    </div>

                    <div class="row">
                        <div class="col-25">
                            <label for="fullname">Полное имя</label>
                        </div>
                        <div class="col-75">
                            <input id="fullname" name="fullname" type="text" required="required" maxlength="100" />
                        </div>
                    </div>

                    <div class="row">
                        <div class="col-25">
                            <label for="root">Права администратора</label>
                        </div>
                        <div class="col-75">
                            <input id="root" name="root" type="checkbox" />
                        </div>
                    </div>

                    <div class="row">
                        <input type="submit" value="Добавить пользователя" />
                    </div>
                </form>
            </div>
        </main>
    </div>
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
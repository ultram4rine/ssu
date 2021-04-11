<!DOCTYPE html>
<html>

<head>
    <meta charset="UTF-8">
    <title>Вход</title>
    <link type="text/css" rel="stylesheet" href="public/css/global.css">
    <link type="text/css" rel="stylesheet" href="public/css/login.css">
</head>

<?php
    session_start();
    if($_SESSION['user_id']){
        header("location: user.php?id=" . $_SESSION['user_id']);
    }
?>

<body>
    <div class="box">
        <div class="container">
            <div class="wrap">
                <form action="login.php" method="POST">
                    <div class="input-wrap">
                        <input id="username" name="username" type="text" required="required" maxlength="50"
                            placeholder="Логин" />
                    </div>

                    <div class="input-wrap">
                        <input id="password" name="password" type="password" required="required"
                            placeholder="Пароль"></input>
                    </div>

                    <div class="input-wrap">
                        <button type="submit">Войти</button>
                    </div>
                </form>
            </div>
        </div>
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

    session_start();

    $username = htmlentities($mysqli->real_escape_string($_POST['username']));
    $password = htmlentities($mysqli->real_escape_string($_POST['password']));

    $result = $mysqli->query("SELECT id, username, password_hash, root, full_name FROM users WHERE username = '$username'");
    if (!$result) {
        print("<script>alert('Invalid username');</script>");
    } else {
        while($row = $result->fetch_array()){
            if (password_verify($password, $row["password_hash"])) {
                $id = $row["id"];
                $_SESSION['user_id'] = $id;
                $_SESSION['user_name'] = $row["name"];
                $_SESSION['user_is_root'] = $row["root"];
                $_SESSION['user_fullname'] = $row["full_name"];
                $mysqli->query("UPDATE users SET last_accessed_at = NOW() WHERE id = $id");
                header("location: user.php?id=" . $row["id"]);
            } else {
                print("<script>alert('Incorrect password');</script>");
            }
        }
    }

    $mysqli->close();
}
?>
<!DOCTYPE html>
<html>

<head>
    <meta charset="UTF-8">
    <title>Вход</title>
    <link type="text/css" rel="stylesheet" href="public/css/global.css">
    <link type="text/css" rel="stylesheet" href="public/css/form.css">
</head>

<?php
    session_start();
    if($_SESSION['user_id']){
        header("location: usertasks.php?id=" . $_SESSION['user_id']);
    }
?>

<body>
    <div class="box">
        <main>
            <div class="container">
                <form action="login.php" method="POST">
                    <label for="username"><b>Логин</b></label>
                    <input id="username" name="username" type="text" required="required" maxlength="50"
                        placeholder="Enter username" />

                    <label for="desc"><b>Пароль</b></label>
                    <input id="password" name="password" type="password" required="required"
                        placeholder="Enter password"></input>

                    <button type="submit">Войти</button>
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

    session_start();

    $username = htmlentities($mysqli->real_escape_string($_POST['username']));
    $password = htmlentities($mysqli->real_escape_string($_POST['password']));

    $result = $mysqli->query("SELECT id, username, password_hash, root, full_name FROM users WHERE username = '$username'");
    if (!$result) {
        print("<script>alert('Invalid username');</script>");
    } else {
        while($row = $result->fetch_array()){
            if (password_verify($password, $row["password_hash"])) {
                $_SESSION['user_id'] = $row["id"];
                $_SESSION['user_name'] = $row["name"];
                $_SESSION['user_is_root'] = $row["root"];
                $_SESSION['user_fullname'] = $row["full_name"];
                header("location: usertasks.php?id=" . $row["id"]);
            } else {
                print("<script>alert('Incorrect password');</script>");
            }
        }
    }

    $mysqli->close();
}
?>
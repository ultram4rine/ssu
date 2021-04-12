<!DOCTYPE html>
<html>

<head>
    <meta charset="UTF-8">
    <title>Задачи</title>
    <link type="text/css" rel="stylesheet" href="public/css/global.css">
    <link type="text/css" rel="stylesheet" href="public/css/header.css">
    <link type="text/css" rel="stylesheet" href="public/css/form.css">
</head>

<?php
    session_start();
    if($_SESSION['user_id']) {
        if ($_SESSION['user_is_root']) {} else {
            header("location: gantt.php");
        }
    } else {
        header("location: login.php");
    }
    $s_user_id = $_SESSION['user_id'];
?>

<body>
    <div class="box">
        <?php include("header.php"); ?>
        <main>
            <div class="container">
                <form action="user.php" method="POST">
                    <?php
                        $id = htmlspecialchars($_GET["id"]);
                        if(!empty($id)) {
                            require_once 'conn.php';

                            $mysqli = new mysqli($host, $user, $password, $database);
                            if ($mysqli->connect_errno) {
                                printf("Соединение не удалось: %s\n", $mysqli->connect_error);
                                exit();
                            }

                            $username;
                            $root;
                            $full_name;

                            $result = $mysqli->query("SELECT username, root, full_name FROM users WHERE id = $id");
                            if (!$result){
                                print("No content");
                            } else {
                                foreach ($result as $row) {
                                    $username = $row["username"];
                                    $root = $row["root"];
                                    $full_name = $row["full_name"];
                                    $last_access = $row["last_accessed_at"];
                                }
                            }

                            $mysqli->close();
                        } else {
                            print("No content");
                        }
                    ?>

                    <?php printf('<input id="id" name="id" type="hidden" required="required" value="%s" />', $id); ?>

                    <div class="row">
                        <div class="col-25">
                            <label for="username">Логин</label>
                        </div>
                        <div class="col-75">
                            <?php printf('<input id="username" name="username" type="text" required="required" maxlength="50" value="%s" />', $username); ?>
                        </div>
                    </div>

                    <div class="row">
                        <div class="col-25">
                            <label for="password">Пароль</label>
                        </div>
                        <div class="col-75">
                            <input id="password" name="password" type="password" maxlength="20" />
                        </div>
                    </div>

                    <div class="row">
                        <div class="col-25">
                            <label for="fullname">Полное имя</label>
                        </div>
                        <div class="col-75">
                            <?php printf('<input id="fullname" name="fullname" type="text" required="required" maxlength="100" value="%s" />', $full_name); ?>
                        </div>
                    </div>

                    <div class="row">
                        <div class="col-25">
                            <label for="root">Права администратора</label>
                        </div>
                        <div class="col-75">
                            <input id="root" name="root" type="checkbox" <?php if ($root) { print("checked"); } ?> />
                        </div>
                    </div>

                    <div class="row">
                        <?php printf('<input type="submit" onclick="window.location.href=\'changeuser.php?id=%s\';" value="Изменить" />', $id) ?>
                    </div>
                </form>
            </div>
        </main>
    </div>
</body>

</html>
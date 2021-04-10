<!DOCTYPE html>
<html>

<head>
    <meta charset="UTF-8">
    <title>Задачи</title>
    <link type="text/css" rel="stylesheet" href="public/css/global.css">
    <link type="text/css" rel="stylesheet" href="public/css/header.css">
    <link type="text/css" rel="stylesheet" href="public/css/form.css">
    <link type="text/css" rel="stylesheet" href="public/css/table.css">
    <link type="text/css" rel="stylesheet" href="https://use.fontawesome.com/releases/v5.15.3/css/all.css">
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"
        integrity="sha256-/xUj+3OJU5yExlq6GSYGSHk7tPXikynS7ogEvDej/m4=" crossorigin="anonymous"></script>
</head>

<?php
    session_start();
    if($_SESSION['user_id']) {}
    else {
        header("location: login.php");
    }
    $user_id = $_SESSION['user_id'];
?>

<body>
    <div class="box">
        <?php include("header.php"); ?>
        <main>
            <div class="container">
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
                        $last_access;

                        $u_result = $mysqli->query("SELECT username, root, full_name, last_accessed_at FROM users WHERE id = $id");
                        if (!$u_result){
                            print("No content");
                        } else {
                            foreach ($u_result as $row) {
                                $username = $row["username"];
                                $root = $row["root"];
                                $full_name = $row["full_name"];
                                $last_access = $row["last_accessed_at"];
                            }
                        }

                        $t_result = $mysqli->query("SELECT id, created_at, planned_closed_at, closed_at, name FROM tasks WHERE user_id = $id ORDER BY closed_at IS NOT NULL, closed_at, created_at DESC");

                        $mysqli->close();
                    } else {
                        print("No content");
                    }
                ?>

                <form>
                    <div class="row">
                        <div class="col-25">
                            <label for="username">Логин</label>
                        </div>
                        <div class="col-75">
                            <?php printf('<input id="username" name="username" type="text" required="required" maxlength="50" readonly value="%s" />', $username); ?>
                        </div>
                    </div>

                    <div class="row">
                        <div class="col-25">
                            <label for="fullname">Полное имя</label>
                        </div>
                        <div class="col-75">
                            <?php printf('<input id="fullname" name="fullname" type="text" required="required" maxlength="100" readonly value="%s" />', $full_name); ?>
                        </div>
                    </div>

                    <div class="row">
                        <div class="col-25">
                            <label for="root">Права администратора</label>
                        </div>
                        <div class="col-75">
                            <?php printf('<input id="root" name="root" type="text" required="required" readonly value="%s" />', $root ? 'Да' : 'Нет'); ?>
                        </div>
                    </div>
                </form>

                <div class="row">
                    <?php printf('<input type="submit" onclick="window.location.href=\'changeuser.php?id=%s\';" value="Изменить" />', $id) ?>
                </div>

                <div class="col-25">
                    <label for="name">Задачи</label>
                </div>
                <table id="tasks">
                    <tr>
                        <th>Идентификатор <i id="sort-icon" class="fas fa-sort"></i></th>
                        <th>Заголовок <i id="sort-icon" class="fas fa-sort"></i></th>
                        <th>Время добавления <i id="sort-icon" class="fas fa-sort-up"></i></th>
                        <th>Планируемая дата завершения <i id="sort-icon" class="fas fa-sort"></i></th>
                        <th>Завершена <i id="sort-icon" class="fas fa-sort"></i></th>
                    </tr>
                    <?php
                        foreach ($t_result as $row) {
                            printf("<tr>");
                            printf("<td>%s</td>", $row["id"]);
                            printf("<td>%s</td>", $row["name"]);
                            printf("<td>%s</td>", $row["created_at"]);
                            printf("<td>%s</td>", $row["planned_closed_at"]);
                            printf("<td>%s</td>", empty($row["closed_at"]) ? 'Нет' : $row["closed_at"]);
                            printf("</tr>");
                        }
                    ?>
                </table>
            </div>
        </main>
    </div>

    <script src="public/js/sort.js"></script>
    <?php
    if ($id == $user_id) {
        print('
            <script>
                $(document).ready(function () {
                    $("#profile").addClass("active");
                });
            </script>
        ');
    }
    ?>
</body>

</html>
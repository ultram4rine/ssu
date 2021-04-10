<!DOCTYPE html>
<html>

<head>
    <meta charset="UTF-8">
    <title>Задачи</title>
    <link type="text/css" rel="stylesheet" href="public/css/global.css">
    <link type="text/css" rel="stylesheet" href="public/css/header.css">
    <link type="text/css" rel="stylesheet" href="public/css/table.css">
    <link type="text/css" rel="stylesheet" href="https://use.fontawesome.com/releases/v5.15.3/css/all.css">
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"
        integrity="sha256-/xUj+3OJU5yExlq6GSYGSHk7tPXikynS7ogEvDej/m4=" crossorigin="anonymous"></script>
</head>

<?php
    session_start();
    if ($_SESSION['user_id']) {
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
                <table id="users">
                    <tr>
                        <th>Идентификатор <i id="sort-icon" class="fas fa-sort-up"></i></th>
                        <th>Логин <i id="sort-icon" class="fas fa-sort"></i></th>
                        <th>Полное имя <i id="sort-icon" class="fas fa-sort"></th>
                        <th>Администратор <i id="sort-icon" class="fas fa-sort"></i></th>
                        <th>Заходил последний раз <i id="sort-icon" class="fas fa-sort"></i></th>
                        <th>Действия</th>
                    </tr>
                    <?php
                        require_once 'conn.php';

                        $mysqli = new mysqli($host, $user, $password, $database);
                        if ($mysqli->connect_errno) {
                            printf("Соединение не удалось: %s\n", $mysqli->connect_error);
                            exit();
                        }

                        $result = $mysqli->query("SELECT id, username, root, full_name, last_accessed_at FROM users");
                        if (!$result){
                            print("No content");
                            exit();
                        } else {
                            while ($row = $result->fetch_array(MYSQLI_ASSOC)) {
                                printf("<tr>");
                                printf("<td><a href='user.php?id=%s'>%s</a></td>", $row["id"], $row["id"]);
                                printf("<td><a href='user.php?id=%s'>%s</a></td>", $row["id"], $row["username"]);
                                printf("<td>%s</td>", $row["full_name"]);
                                printf("<td>%s</td>", $row["root"] ? 'Да' : 'Нет');
                                printf("<td>%s</td>", $row["last_accessed_at"]);
                                printf("<td><a href='changeuser.php?id=%s'><i class='fas fa-edit'></i></a> <a href='deleteuser.php?id=%s'><i class='fas fa-trash'></i></a></td>", $row["tid"], $row["tid"]);
                                printf("</tr>");
                            }
                        }

                        $mysqli->close();
                    ?>
                </table>
            </div>
        </main>
    </div>

    <script src="public/js/sort.js"></script>
    <script>
        $(document).ready(function () {
            $("#users").addClass("active");
        });
    </script>
</body>

</html>
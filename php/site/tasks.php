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
                <table id="tasks">
                    <tr>
                        <th>Идентификатор <i id="sort-icon" class="fas fa-sort-up"></i></th>
                        <th>Заголовок <i id="sort-icon" class="fas fa-sort"></i></th>
                        <th>Исполнитель <i id="sort-icon" class="fas fa-sort"></th>
                        <th>Время добавления <i id="sort-icon" class="fas fa-sort"></i></th>
                        <th>Планируемая дата завершения <i id="sort-icon" class="fas fa-sort"></i></th>
                        <th>Завершена <i id="sort-icon" class="fas fa-sort"></i></th>
                        <th>Действия</th>
                    </tr>
                    <?php
                        require_once 'conn.php';

                        $mysqli = new mysqli($host, $user, $password, $database);
                        if ($mysqli->connect_errno) {
                            printf("Соединение не удалось: %s\n", $mysqli->connect_error);
                            exit();
                        }

                        $result = $mysqli->query("SELECT t.id AS tid, t.created_at, t.user_id, t.planned_closed_at, t.closed_at, t.name, t.description, u.id AS uid, u.full_name FROM tasks AS t JOIN users AS u ON u.id = t.user_id");
                        if (!$result){
                            print("No content");
                            exit();
                        } else {
                            while ($row = $result->fetch_array(MYSQLI_ASSOC)) {
                                printf("<tr>");
                                printf("<td><a href='task.php?id=%s'>%s</a></td>", $row["tid"], $row["tid"]);
                                printf("<td><a href='task.php?id=%s'>%s</a></td>", $row["tid"], $row["name"]);
                                printf("<td><a href='user.php?id=%s'>%s</a></td>", $row["uid"], $row["full_name"]);
                                printf("<td>%s</td>", $row["created_at"]);
                                printf("<td>%s</td>", $row["planned_closed_at"]);
                                printf("<td>%s</td>", empty($row["closed_at"]) ? 'Нет' : $row["closed_at"]);
                                printf("<td><a href='changetask.php?id=%s'><i class='fas fa-edit'></i></a> <a href='deletetask.php?id=%s'><i class='fas fa-trash'></i></a></td>", $row["tid"], $row["tid"]);
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
            $("#tasks").addClass("active");
        });
    </script>
</body>

</html>
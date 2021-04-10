<!DOCTYPE html>
<html>

<head>
    <meta charset="UTF-8">
    <title>Новая задача</title>
    <link type="text/css" rel="stylesheet" href="public/css/global.css">
    <link type="text/css" rel="stylesheet" href="public/css/header.css">
    <link type="text/css" rel="stylesheet" href="public/css/form.css">
    <link type="text/css" rel="stylesheet" href="https://code.jquery.com/ui/1.12.1/themes/base/jquery-ui.css">
    <link type="text/css" rel="stylesheet"
        href="https://cdn.jsdelivr.net/npm/select2@4.1.0-rc.0/dist/css/select2.min.css" />
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"
        integrity="sha256-/xUj+3OJU5yExlq6GSYGSHk7tPXikynS7ogEvDej/m4=" crossorigin="anonymous"></script>
    <script src="https://code.jquery.com/ui/1.12.1/jquery-ui.min.js"
        integrity="sha256-VazP97ZCwtekAsvgPBSUwPFKdrwD3unUfSGVYrahUqU=" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/select2@4.1.0-rc.0/dist/js/select2.min.js"></script>
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
                <form action="addtask.php" method="POST">
                    <div class="row">
                        <div class="col-25">
                            <label for="name">Заголовок</label>
                        </div>
                        <div class="col-75">
                            <input id="name" name="name" type="text" required="required" maxlength="50" />
                        </div>
                    </div>

                    <div class="row">
                        <div class="col-25">
                            <label for="desc">Описание</label>
                        </div>
                        <div class="col-75">
                            <textarea id="desc" name="desc" required="required" maxlength="65535"></textarea>
                        </div>
                    </div>

                    <div class="row">
                        <div class="col-25">
                            <label for="empl">Сотрудник</label>
                        </div>
                        <div class="col-75">
                            <select id="empl" name="empl">
                                <?php
                                    require_once 'conn.php';

                                    $mysqli = new mysqli($host, $user, $password, $database);

                                    if ($mysqli->connect_errno) {
                                        printf("Соединение не удалось: %s\n", $mysqli->connect_error);
                                        exit();
                                    }

                                    $result = $mysqli->query("SELECT id, full_name FROM users");
                                    while ($row = $result->fetch_array(MYSQLI_ASSOC)) {
                                        printf("<option value='%s'>%s</option>\n", $row["id"], $row["full_name"]);
                                    }

                                    $mysqli->close();
                                ?>
                            </select>
                        </div>
                    </div>

                    <div class="row">
                        <div class="col-25">
                            <label for="closing">Планируемая дата завершения</label>
                        </div>
                        <div class="col-75">
                            <input id="closing" name="closing" type="text" required="required" />
                        </div>
                    </div>

                    <div class="row">
                        <input type="submit" value="Добавить задачу" />
                    </div>
                </form>
            </div>
        </main>
    </div>
    <script>
        $(document).ready(function () {
            $("#addtask").addClass("active");
            $("#empl").select2();
            $("#closing").datepicker({
                dateFormat: "yy-mm-dd"
            });
        });
    </script>
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

    $name = htmlentities($mysqli->real_escape_string($_POST['name']));
    $desc = htmlentities($mysqli->real_escape_string($_POST['desc']));
    $empl = htmlentities($mysqli->real_escape_string($_POST['empl']));
    $closing = htmlentities($mysqli->real_escape_string($_POST['closing']));

    $res = $mysqli->query("INSERT INTO tasks VALUES(NULL, NOW(), '$empl', '$closing', NULL, '$name', '$desc')");
    if ($res) {
        echo "<script>alert('Задача добавлена');</script>";
    } else {
        echo "<script>alert('Ошибка');</script>";
    }

    $mysqli->close();
}
?>
<!DOCTYPE html>
<html>

<head>
    <meta charset="UTF-8">
    <link type="text/css" rel="stylesheet" href="public/css/global.css">
    <link type="text/css" rel="stylesheet" href="public/css/header.css">
    <link type="text/css" rel="stylesheet" href="https://cdn.jsdelivr.net/npm/select2@4.1.0-rc.0/dist/css/select2.min.css" />
    <script src="https://code.jquery.com/jquery-3.6.0.min.js" integrity="sha256-/xUj+3OJU5yExlq6GSYGSHk7tPXikynS7ogEvDej/m4=" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/select2@4.1.0-rc.0/dist/js/select2.min.js"></script>
    <style>
        input, textarea, select {
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
    <main>
        <form action="addtask.php" method="POST">
            <label for="name">Заголовок: </label>
            <input id="name" name="name" type="text" required="required" maxlength="50" /> <br/>
            <label for="desc">Описание: </label>
            <textarea style="resize: none;" id="desc" name="desc" rows="10" cols="30" required="required" maxlength="65535"></textarea> <br/>
            <label for="empl">Сотрудник: </label>
            <select class="empl-select" id="empl" name="empl">
<?php
require_once 'conn.php';

$mysqli = new mysqli($host, $user, $password, $database);

if ($mysqli->connect_errno) {
    printf("Соединение не удалось: %s\n", $mysqli->connect_error);
    exit();
}

$result = $mysqli->query("SELECT * FROM users");
while ($row = $result->fetch_array(MYSQLI_ASSOC)) {
    printf("<option>%s</option>\n", $row["full_name"]);
}
$result = $mysqli->query();
if (!$result) {
    printf("Сообщение ошибки: %s\n", $mysqli->error);
} else {
    echo "Выполнение запроса прошло успешно";
}

$mysqli->close();
?>
            </select> <br/>
            <input type="submit" value="Добавить задачу"/>
        </form>
    </main>
    <script>
        $(document).ready(function() {
            $('.empl-select').select2();
        });
    </script>
</body>

</html>
<!DOCTYPE html>
<html>

<head>
    <meta charset="UTF-8">
    <link type="text/css" rel="stylesheet" href="public/css/global.css">
    <link type="text/css" rel="stylesheet" href="public/css/header.css">
    <link type="text/css" rel="stylesheet" href="public/css/form.css">
    <link type="text/css" rel="stylesheet"
        href="https://cdn.jsdelivr.net/npm/select2@4.1.0-rc.0/dist/css/select2.min.css" />
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"
        integrity="sha256-/xUj+3OJU5yExlq6GSYGSHk7tPXikynS7ogEvDej/m4=" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/select2@4.1.0-rc.0/dist/js/select2.min.js"></script>
</head>

<body>
    <div class="box">
        <?php echo file_get_contents("public/html/header.html"); ?>
        <main>
            <div class="container">
                <form action="addtask.php" method="POST">
                    <div class="row">
                        <div class="col-25">
                            <label for="name">Заголовок </label>
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
                            <select class="empl-select" id="empl" name="empl">
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
                                $result = $mysqli->query();
                                if (!$result) {
                                    printf("Сообщение ошибки: %s\n", $mysqli->error);
                                } else {
                                    echo "Выполнение запроса прошло успешно";
                                }

                                $mysqli->close();
                            ?>
                            </select>
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
            $('.empl-select').select2();
        });
    </script>
</body>

</html>
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
    if ($_SESSION['user_id']) {}
    else {
        header("location: login.php");
    }
    $s_user_id = $_SESSION['user_id'];
?>

<body>
    <div class="box">
        <?php include("header.php"); ?>
        <main>
            <div class="container">
                <form>
                    <?php
                        $id = htmlspecialchars($_GET["id"]);
                        if(!empty($id)) {
                            require_once 'conn.php';

                            $mysqli = new mysqli($host, $user, $password, $database);
                            if ($mysqli->connect_errno) {
                                printf("Соединение не удалось: %s\n", $mysqli->connect_error);
                                exit();
                            }

                            $created_at;
                            $user_full_name;
                            $planned_closed_at;
                            $closed_at;
                            $name;
                            $description;

                            $result = $mysqli->query("SELECT t.created_at, t.planned_closed_at, t.closed_at, t.name, t.description, u.full_name FROM tasks AS t JOIN users AS u ON t.user_id = u.id WHERE t.id = $id");
                            if (!$result){
                                print("No content");
                            } else {
                                while ($row = $result->fetch_array(MYSQLI_ASSOC)) {
                                    $created_at = $row['created_at'];
                                    $user_full_name = $row['full_name'];
                                    $planned_closed_at = $row['planned_closed_at'];
                                    $closed_at = $row['closed_at'];
                                    $name = $row['name'];
                                    $description = $row['description'];
                                }
                            }

                            $mysqli->close();
                        } else {
                            print("No content");
                        }
                    ?>
                    <div class="row">
                        <div class="col-25">
                            <label for="name">Заголовок</label>
                        </div>
                        <div class="col-75">
                            <?php printf('<input id="name" name="name" type="text" required="required" maxlength="50" readonly value="%s" />', $name); ?>
                        </div>
                    </div>

                    <div class="row">
                        <div class="col-25">
                            <label for="desc">Описание</label>
                        </div>
                        <div class="col-75">
                            <?php printf('<textarea id="desc" name="desc" required="required" maxlength="65535" readonly>%s</textarea>', $description); ?>
                        </div>
                    </div>

                    <div class="row">
                        <div class="col-25">
                            <label for="empl">Сотрудник</label>
                        </div>
                        <div class="col-75">
                            <?php printf('<input id="empl" name="empl" type="text" required="required" maxlength="50" readonly value="%s" />', $user_full_name); ?>
                        </div>
                    </div>

                    <div class="row">
                        <div class="col-25">
                            <label for="open">Открыта</label>
                        </div>
                        <div class="col-75">
                            <?php printf('<input id="open" name="open" type="text" required="required" readonly value="%s" />', $created_at); ?>
                        </div>
                    </div>

                    <div class="row">
                        <div class="col-25">
                            <label for="closing">Планируемая дата завершения</label>
                        </div>
                        <div class="col-75">
                            <?php printf('<input id="closing" name="closing" type="text" required="required" readonly value="%s" />', $planned_closed_at); ?>
                        </div>
                    </div>

                    <?php
                        if ($closed_at != '') {
                            printf('<div class="row">
                                <div class="col-25">
                                    <label for="closed">Завершена</label>
                                </div>
                                <div class="col-75">
                                    <input id="closed" name="closed" type="text" required="required" readonly value="%s" />
                                </div>
                            </div>', $closed_at);
                        }
                    ?>

                </form>
                <div class="row">
                    <?php printf('<input type="submit" onclick="window.location.href=\'changetask.php?id=%s\';" value="Изменить" />', $id) ?>
                </div>
            </div>
        </main>
    </div>
</body>

</html>
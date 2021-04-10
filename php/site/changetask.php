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
                <form action="task.php" method="POST">
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
                            $user_id;
                            $user_full_name;
                            $planned_closed_at;
                            $closed_at;
                            $name;
                            $description;

                            $result = $mysqli->query("SELECT t.created_at, t.planned_closed_at, t.closed_at, t.name, t.description, u.id, u.full_name FROM tasks AS t JOIN users AS u ON t.user_id = u.id WHERE t.id = $id");
                            if (!$result){
                                print("No content");
                            } else {
                                while ($row = $result->fetch_array(MYSQLI_ASSOC)) {
                                    $created_at = $row['created_at'];
                                    $user_id = $row['id'];
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

                    <?php printf('<input id="id" name="id" type="hidden" required="required" value="%s" />', $id); ?>

                    <div class="row">
                        <div class="col-25">
                            <label for="name">Заголовок</label>
                        </div>
                        <div class="col-75">
                            <?php printf('<input id="name" name="name" type="text" required="required" maxlength="50" value="%s" />', $name); ?>
                        </div>
                    </div>

                    <div class="row">
                        <div class="col-25">
                            <label for="desc">Описание</label>
                        </div>
                        <div class="col-75">
                            <?php printf('<textarea id="desc" name="desc" required="required" maxlength="65535">%s</textarea>', $description); ?>
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
                            <?php printf('<input id="closing" name="closing" type="text" required="required" value="%s" />', $planned_closed_at); ?>
                        </div>
                    </div>

                    <?php
                        if ($closed_at != '') {
                            printf('<div class="row">
                                <div class="col-25">
                                    <label for="closed">Завершена</label>
                                </div>
                                <div class="col-75">
                                    <input id="closed" name="closed" type="text" required="required" value="%s" />
                                </div>
                            </div>', $closed_at);
                        }
                    ?>

                    <?php
                        if ($_SESSION['user_is_root'] || $s_user_id == $user_id) {
                        echo '<div class="row">
                                <input type="submit" value="Изменить задачу" name="change" />
                                <input style="margin-right: 10px;" type="submit" value="Завершить задачу" name="close" />
                            </div>';
                        }
                    ?>
                </form>
            </div>
        </main>
    </div>
</body>

</html>
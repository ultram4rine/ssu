<!DOCTYPE html>
<html>

<head>
    <meta charset="UTF-8">
    <title>Задачи</title>
    <link type="text/css" rel="stylesheet" href="public/css/global.css">
    <link type="text/css" rel="stylesheet" href="public/css/header.css">
    <link type="text/css" rel="stylesheet" href="public/css/table.css">
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"
        integrity="sha256-/xUj+3OJU5yExlq6GSYGSHk7tPXikynS7ogEvDej/m4=" crossorigin="anonymous"></script>
</head>

<?php
    session_start();
    if($_SESSION['user_id']){}
    else{
        header("location: login.php");
    }
    $user = $_SESSION['user_id'];
?>

<body>
    <div class="box">
        <?php include("header.php"); ?>
        <main>
            <div class="container">
                <table id="gantt" style="overflow-y: auto;">
                    <?php
                        require_once 'conn.php';

                        $mysqli = new mysqli($host, $user, $password, $database);
                        if ($mysqli->connect_errno) {
                            printf("Соединение не удалось: %s\n", $mysqli->connect_error);
                            exit();
                        }

                        $result = $mysqli->query("SELECT t.id AS tid, t.created_at, t.planned_closed_at, t.name, u.id AS uid, u.full_name FROM tasks AS t JOIN users AS u ON t.user_id = u.id WHERE closed_at IS NULL ORDER BY t.planned_closed_at ASC, t.created_at");
                        if (!$result){
                            print("No content");
                        } else {
                            $dates;
                            $i = 0;
                            foreach ($result as $row) {
                                $dates[$i] = substr($row["created_at"], 0, -9);
                                $i++;
                                $dates[$i] = $row["planned_closed_at"];
                                $i++;
                            }

                            $dates = array_unique($dates);

                            function date_sort($a, $b) {
                                return strtotime($a) - strtotime($b);
                            }
                            usort($dates, "date_sort");

                            print("<tr>");
                            print("<th style='cursor: default; background-color: #f2f2f2; color: black;'></th>");
                            foreach ($dates as $date) {
                                printf("<th style='cursor: default; background-color: #f2f2f2; color: black; font-weight: normal;'>%s</th>", $date);
                            }
                            print("</tr>");

                            foreach ($result as $row) {
                                print("<tr>");
                                printf("<td>%s</td>", "<a href='user.php?id=" . $row["uid"] . "'>" . $row["full_name"] . "</a>" . " -> " . "<a href='task.php?id=" . $row["tid"] . "'>" . $row["name"] . "</a>");
                                $paint = false;
                                foreach ($dates as $date) {
                                    if ($date == substr($row["created_at"], 0, -9)) {
                                        $paint = true;
                                        if (substr($row["created_at"], 0, -9) == $row["planned_closed_at"]) {
                                            $paint = false;
                                            print("<td style='background-color: red;'></td>");
                                            continue;
                                        }
                                    } else if ($date == $row["planned_closed_at"]) {
                                        $paint = false;
                                        print("<td style='background-color: red;'></td>");
                                        continue;
                                    }

                                    if (!$paint) {
                                        print("<td></td>");
                                    } else {
                                        print("<td style='background-color: red;'></td>");
                                    }
                                }
                                print("</tr>");
                            }
                        }

                        $mysqli->close();
                    ?>
                </table>
            </div>
        </main>
    </div>
    <script>
        $(document).ready(function () {
            $("#chart").addClass("active");
        });
    </script>
</body>

</html>
<!DOCTYPE html>
<html>

<head>
    <meta charset="UTF-8">
    <title>Задачи</title>
    <link type="text/css" rel="stylesheet" href="public/css/global.css">
    <link type="text/css" rel="stylesheet" href="public/css/header.css">
    <link type="text/css" rel="stylesheet" href="public/css/table.css">
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
        <?php echo file_get_contents("public/html/header.html"); ?>
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

                        $result = $mysqli->query("SELECT t.created_at, t.planned_closed_at, t.name, u.full_name FROM tasks AS t JOIN users AS u ON t.user_id = u.id WHERE closed_at IS NULL ORDER BY t.planned_closed_at ASC, t.created_at");
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
                            print("<td></td>");
                            foreach ($dates as $date) {
                                printf("<td>%s</td>", $date);
                            }
                            print("</tr>");

                            foreach ($result as $row) {
                                print("<tr>");
                                printf("<td>%s</td>", $row["full_name"] . " -> " . $row["name"]);
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
</body>

</html>
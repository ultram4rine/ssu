<!DOCTYPE html>
<html>

<head>
    <meta charset="UTF-8">
    <title>Задачи</title>
    <link type="text/css" rel="stylesheet" href="public/css/global.css">
    <link type="text/css" rel="stylesheet" href="public/css/header.css">
    <link type="text/css" rel="stylesheet" href="public/css/table.css">
</head>

<body>
    <div class="box">
        <?php echo file_get_contents("public/html/header.html"); ?>
        <main>
            <div class="container">
                <table>
                    <thead>
                        <tr>
                            <th>Идентификатор</th>
                            <th>Заголовок</th>
                            <th>Время добавления</th>
                            <th>Планируемая дата завершения</th>
                            <th>Закрыта</th>
                        </tr>
                    </thead>
                    <tbody>
                        <?php
                        $id = htmlspecialchars($_GET["id"]);
                        if(!empty($id)) {
                            require_once 'conn.php';

                            $mysqli = new mysqli($host, $user, $password, $database);
                            if ($mysqli->connect_errno) {
                                printf("Соединение не удалось: %s\n", $mysqli->connect_error);
                                exit();
                            }

                            $result = $mysqli->query("SELECT id, created_at, planned_closed_at, closed_at, name FROM tasks WHERE user_id = $id ORDER BY closed_at IS NOT NULL, closed_at, created_at DESC");
                            if (!$result){
                                print("No content");
                            } else {
                                while ($row = $result->fetch_array(MYSQLI_ASSOC)) {
                                    printf("<tr>");
                                    printf("<td>%s</td>", $row["id"]);
                                    printf("<td>%s</td>", $row["name"]);
                                    printf("<td>%s</td>", $row["created_at"]);
                                    printf("<td>%s</td>", $row["planned_closed_at"]);
                                    printf("<td>%s</td>", empty($row["closed_at"]) ? 'Нет' : $row["closed_at"]);
                                    printf("</tr>");
                                }
                            }
                            
                            $mysqli->close();
                        } else {
                            print("No content");
                        }
                    ?>
                    </tbody>
                </table>
            </div>
        </main>
    </div>
</body>

</html>
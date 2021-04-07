<!DOCTYPE html>
<html>

<head>
    <meta charset="UTF-8">
    <title>Calculator</title>
    <style>
        th,
        td {
            border: 1px solid #ddd;
            padding: 8px;
        }
    </style>
</head>

<body>
    <table>
        <tr>
            <td>Товар</td>
            <td>Цена</td>
            <td>Количество</td>
            <td>Стоимость</td>
        </tr>
        <?php
            $mysqli = new mysqli("localhost", "root", "parol", "exercise_3");

            if ($mysqli->connect_errno) {
                printf("Соединение не удалось: %s\n", $mysqli->connect_error);
                exit();
            }

            $result = $mysqli->query("SELECT goods, price, quantity, price * quantity AS total FROM bill_content");
            while ($row = $result->fetch_array(MYSQLI_ASSOC)) {
                print("<tr>");
                printf("<td>%s</td>", $row["goods"]);
                printf("<td>%s</td>", $row["price"]);
                printf("<td>%s</td>", $row["quantity"]);
                printf("<td>%s</td>", $row["total"]);
                print("</tr>");
            }

            $mysqli->close();
        ?>
    </table>

    <table>
        <tr>
            <td>№ счёта</td>
            <td>Дата</td>
            <td>Организация</td>
            <td>Сумма</td>
        </tr>
        <?php
            $mysqli = new mysqli("localhost", "root", "parol", "exercise_3");

            if ($mysqli->connect_errno) {
                printf("Соединение не удалось: %s\n", $mysqli->connect_error);
                exit();
            }

            $result = $mysqli->query("SELECT bid, num, bdate, name FROM bill");
            while ($row = $result->fetch_array(MYSQLI_ASSOC)) {
                print("<tr>");
                printf("<td>%s</td>", $row["num"]);
                printf("<td>%s</td>", $row["bdate"]);
                printf("<td>%s</td>", $row["name"]);
                $bid = $row["bid"];
                $total = 0;
                $res = $mysqli->query("SELECT price * quantity AS total FROM bill_content WHERE bid = '$bid'");
                while ($r = $res->fetch_array(MYSQLI_ASSOC)) {
                    $total += $r['total'];
                }
                printf("<td>%s</td>", $total);
                print("</tr>");
            }

            $mysqli->close();
        ?>
    </table>

    <table>
        <tr>
            <td>№ счёта</td>
            <td>Организация</td>
            <td>Задолженность</td>
        </tr>
        <?php
            $mysqli = new mysqli("localhost", "root", "parol", "exercise_3");

            if ($mysqli->connect_errno) {
                printf("Соединение не удалось: %s\n", $mysqli->connect_error);
                exit();
            }

            $result = $mysqli->query("SELECT bid, num, name FROM bill");
            while ($row = $result->fetch_array(MYSQLI_ASSOC)) {
                print("<tr>");
                printf("<td>%s</td>", $row["num"]);
                printf("<td>%s</td>", $row["name"]);
                
                $bid = $row["bid"];
                $total = 0;

                $res1 = $mysqli->query("SELECT price * quantity AS total FROM bill_content WHERE bid = '$bid'");
                while ($r = $res1->fetch_array(MYSQLI_ASSOC)) {
                    $total += $r['total'];
                }

                $res3 = $mysqli->query("SELECT summa FROM payment WHERE bid = '$bid'");
                while ($r = $res3->fetch_array(MYSQLI_ASSOC)) {
                    $total -= $r['summa'];
                }

                printf("<td>%s</td>", $total);
                print("</tr>");
            }

            $mysqli->close();
        ?>
    </table>
</body>

</html>
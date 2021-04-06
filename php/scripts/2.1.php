<!DOCTYPE html>
<html>

<head>
    <meta charset="UTF-8">
    <title>Calculator</title>
</head>

<body>
    <form action="2.1.php" method="POST">
        <label for="a">a</label>
        <input name="a" type="text" required="required" /> <br />

        <label for="b">b</label>
        <input name="b" type="text" required="required" /> <br />

        <label for="op">operation</label>
        <select name="op">
            <option>add</option>
            <option>sub</option>
            <option>mul</option>
            <option>div</option>
        </select> <br />

        <input type="submit" value="calculate" />
    </form>
</body>

</html>

<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $a = $_POST['a'];
    $b = $_POST['b'];
    $op = $_POST['op'];

    if (!is_numeric($a) || !is_numeric($b)) {
        print('<script>alert("not a number")</script>');
        exit();
    }

    switch ($op) {
        case 'add':
            printf('%s + %s = %s', $a, $b, $a+$b);
            break;
        case 'sub':
            printf('%s - %s = %s', $a, $b, $a-$b);
            break;
        case 'mul':
            printf('%s * %s = %s', $a, $b, $a*$b);
            break;
        case 'div':
            if ($b != '0') {
                printf('%s / %s = %s', $a, $b, $a/$b);
            } else {
                print('<script>alert("division by zero!")</script>');
                exit();
            }
            break;
        default:
            print('<script>alert("invalid operation")</script>');
            exit();
            break;
    }
}
?>
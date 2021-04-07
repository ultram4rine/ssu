<!DOCTYPE html>
<html>

<head>
    <meta charset="UTF-8">
</head>

<body>
    <?php
        $n = $_GET["n"];
        if (!isset($n)) {$n = 0;}
        if (!is_numeric($n)) {print('<script>alert("not an integer")</script>'); exit();}
        if ($n < 0) {print('<script>alert("negative")</script>'); exit();}

        if ($n > 0) {
            printf('<a href="2.2.php?n=%s"><<</a>', $n-1);
        }
        for ($i = 1; $i <= 10; $i++) {
            if ($n == $n*10 + $i) {
                printf(' %s ', $n*10 + $i);
            }
            printf(' <a href="2.2.php?n=%s">%s</a> ', $n*10 + $i, $n*10 + $i);
        }
        printf('<a href="2.2.php?n=%s">>></a>', $n+1);
    ?>
</body>

</html>
<?php
    $m = 99; // 10 < $m < 100
    $p = 3; // 1 < $p < 20
    $c = 3; // 1 < $c < 10

    print('<table border="1" cellpadding="2" cellspacing="2"><tr>');
    for ($i = 1; $i < $m; $i++) {
        if ($i % $c == 0) {
            if ($i == $m-1) {
                printf('<td colspan="%s" style="color: red;">%s</td>', $p - (($m-1) % $p) + 1, $i);
            } else {
                printf('<td style="color: red;">%s</td>', $i);
            }
        } else {
            if ($i == $m-1) {
                printf('<td colspan="%s">%s</td>', $p - (($m-1) % $p) + 1, $i);
            } else {
                printf('<td>%s</td>', $i);
            }
        }
        if ($i % $p == 0) {
            print('</tr><tr>');
        }
    }
    print('</table>')
?>
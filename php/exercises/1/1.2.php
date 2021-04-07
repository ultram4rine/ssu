<?php
    $n_max = 10;
    $m_max = 10;

    $n_min = 1;
    $m_min = 1;

    $p;
    for ($i = $m_min; $i <= $m_max; $i++) {
        for ($j = $n_min-1; $j <= $n_max; $j++) {
            $p[$i][$j] = 2;
        }
    }

    print('<table border="1" cellpadding="2" cellspacing="2"><tr>');
    for ($i = $n_min-1; $i <= $n_max; $i++) {
        if ($i == $n_min-1) {
            print('<td style="color: red;"></td>');
        } else {
            printf('<td style="color: red;">%s</td>', $i);
        }
    }
    print('</tr>');
    for ($i = $m_min; $i <= $m_max; $i++) {
        print('<tr>');
        for ($j = $n_min-1; $j <= $n_max; $j++) {
            if ($j == $n_min-1) {
                printf('<td style="color: red;">%s</td>', $i);
            } else {
                printf('<td>%s</td>', ($i*$j)**$p[$i][$j]);
            }
        }
        print('</tr>');
    }
    print('</table>')
?>
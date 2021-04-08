<?php
    session_start();

    $user = $_SESSION['user_id'];
    $is_root = $_SESSION['user_is_root'];

    print('
        <header>
            <a id="chart" class="logo" href="/gantt.php">Распределение задач</a>
                <div class="header-right">');

        if ($is_root) {
        print('
            <a id="addtask" href="/addtask.php">Добавить задачу</a>
            <a id="adduser" href="/adduser.php">Добавить пользователя</a>
        ');
    }

    printf('
                <a id="profile" href="/user.php?id=%s">Профиль</a>
            </div>
        </header>', $user);
?>
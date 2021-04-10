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
            <div class="dropdown">
                <div class="dropbtn">Управление</div>
                <div class="dropdown-content">
                    <a id="tasks" class="droplnk" href="/tasks.php">Задачи</a>
                    <a id="users" class="droplnk" href="/users.php">Пользователи</a>
                    <a id="addtask" class="droplnk" href="/addtask.php">Добавить задачу</a>
                    <a id="adduser" class="droplnk" href="/adduser.php">Добавить пользователя</a>
                </div>
            </div>
        ');
    }

    printf('
                <a id="profile" href="/user.php?id=%s">Профиль</a>
                <a id="logout" href="/logout.php">Выйти</a>
            </div>
        </header>', $user);
?>
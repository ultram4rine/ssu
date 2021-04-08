<?php
    session_start();
    if($_SESSION['user_id']){}
    else{
        header("location: login.php");
    }
    $user = $_SESSION['user_id'];

    printf('
    <header>
        <a href="/gantt.php" class="logo">Распределение задач</a>
        <div class="header-right">
            <a id="addtask" href="/addtask.php">Добавить задачу</a>
            <a id="adduser" href="/adduser.php">Добавить пользователя</a>
            <a id="profile" href="/user.php?id=%s">Профиль</a>
        </div>
    </header>', $user);
?>
<?php
session_start();
if ($_SESSION["user_id"]) {
        header("location: user.php?id=" . $_SESSION["user_id"]);
} else {
        header("location: login.php");
}
?>
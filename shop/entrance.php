<?
session_start();

$allow = false;

if (isset($_GET['logout'])) {
    session_destroy();
    setcookie("hash");
    header("Location: /");
}

if (is_auth()) {
    $allow = true;
    $user = get_user();
}


if (isset($_POST['send'])) {
    $login = $_POST['login'];
    $pass = $_POST['password'];

    if (!auth($login, $pass)) {
        Die('Не верный логин пароль');
    } else {
        if (isset($_POST['save'])) {
            $hash = uniqid(rand(), true);
            $db = get_db();
            $id = mysqli_real_escape_string($db, strip_tags(stripslashes($_SESSION['id'])));
            $sql = "UPDATE `users` SET `hash` = '{$hash}' WHERE `users`.`id` = {$id}";
            $result = mysqli_query($db, $sql);
            setcookie("hash", $hash, time() + 3600);

        }
        $allow = true;
        $user = get_user();


    }
}

function get_db() {
    static $db = '';
    if (empty($db)) {
        $db = mysqli_connect('localhost', 'root', '', 'products');
    }
    return $db;
}

function auth($login, $pass)
{
    $db = get_db();
    $login = mysqli_real_escape_string($db, strip_tags(stripslashes($login)));
    $result = mysqli_query($db, "SELECT * FROM users WHERE login = '{$login}'");
    $row = mysqli_fetch_assoc($result);

    if (password_verify($pass, $row['password'])) {
        $_SESSION['login'] = $login;
        $_SESSION['id'] = $row['id'];
        return true;
    }
    return false;
}

function is_auth()
{
    if (isset($_COOKIE["hash"])) {
        $hash = $_COOKIE["hash"];
        $db = get_db();
        $sql = "SELECT * FROM `users` WHERE `hash`='{$hash}'";
        $result = mysqli_query($db, $sql);
        $row = mysqli_fetch_assoc($result);
        $user = $row['login'];
        if (!empty($user)) {
            $_SESSION['login'] = $user;
        }
    }
    return isset($_SESSION['login']) ? true : false;
}

function get_user()
{
    return $_SESSION['login'];
}
?>
<?php
include "menu.php";
if (!$allow) :?>

<form method="post">
        <input type='text' name='login' placeholder='Логин'>
        <input type='password' name='password' placeholder='Пароль'>
        Save? <input type='checkbox' name='save'>
        <input type='submit' name='send'>
    </form>

<? else: ?>
    Добро пожаловать! <?=$user?> <a href="/?logout">Выход</a><br>
<? endif; ?>
<br>
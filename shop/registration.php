<?php
include "db.php";
$row=[];
if($_GET['action']=='registr'){
    $login=strip_tags(htmlspecialchars(mysqli_real_escape_string($db,$_POST['login'])));
    $pass=strip_tags(htmlspecialchars(mysqli_real_escape_string($db,$_POST['pass'])));
    $sql="INSERT INTO users(login,password) VALUES ('{$login}','{$pass}')";
    mysqli_query($db,$sql);
    header('Location: registration.php');
    die();
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <link rel="stylesheet" href="form.css">
</head>
<body>
  <?php  include "menu.php" ?>
  <h1>Регистрация</h1>
<form  name="forms" class="form" action="?action=registr" method="post">
        <label class="label " for="login" >Логин</label>
        <input class="input" type="text" name="login" value="<?=$row['login']?>" required >
        <label class="label" for="pass">Пароль</label>
        <input class="input" type="text"  name="pass" value="<?=$row['pass']?>" required>
        <button class="input btn" value="submit">Зарегистрироваться</button>
         
    </form>
</body>
</html>
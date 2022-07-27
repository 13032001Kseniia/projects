<?php
include "db.php";
$row=[];

if($_GET['action']=='order'){
    // $id=(int)$_GET['id'];
    // var_dump($id);
    // die();
    $session=session_id();
    $name=strip_tags(htmlspecialchars(mysqli_real_escape_string($db,$_POST['name'])));
    $phone=strip_tags(htmlspecialchars(mysqli_real_escape_string($db,$_POST['phone'])));
    $email=strip_tags(htmlspecialchars(mysqli_real_escape_string($db,$_POST['email'])));
    // $w=mysqli_query($db,"SELECT session_id as session_basket FROM orders,basket WHERE orders.session_id_basket = basket.{$session} ");
    // var_dump($w);
    // die();
    $sql="INSERT INTO orders(name,phone,session_id_backet,email) VALUES ('{$name}','{$phone}','{$session}','{$email}')";
    mysqli_query($db,$sql);
    header('Location: order.php');
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
    <?php include "menu.php"?>
    <h1>Оформление заказа</h1>
<script defer src="form.js"></script>
    <form  name="forms" class="form" action="?action=order"  method="post">
        <label class="label " for="name" >Name</label>
        <input class="input" type="text" name="name" value="<?=$row['name']?>" >
        <label class="label" for="Phone" >Phone</label>
        <input class="input"  type="tel" name="phone" value="<?=$row['phone']?>">
        <label class="label" for="email">E-mail</label>
        <input class="input" type="email"  name="email" value="<?=$row['email']?>">
        <!-- <button onclick="submitForm()" class="input btn" value="submit"><a href="?action=order&id=<?$row['id']?>">Оформить</a></button> -->
        <button onclick="submitForm()" class="input btn" value="submit">Оформить</button> 
    </form>
</body>
</html>
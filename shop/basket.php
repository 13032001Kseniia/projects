<?php
session_start();
include "db.php";
$session=session_id();
$basket = mysqli_query($db, "SELECT basket.id basket_id ,products.title,products.price FROM basket,products WHERE basket.goods_id = products.id AND session_id = '{$session}'");
// var_dump($basket);
$c=mysqli_fetch_assoc($basket);
// var_dump($c);
// die();
$res=mysqli_query($db,"SELECT count(id) as count FROM `basket` WHERE `session_id`='{$session}'");
$sum=mysqli_query($db,"SELECT SUM(price) FROM products,basket WHERE basket.goods_id=products.id");
// var_dump($sum);
// die();
$count=mysqli_fetch_assoc($res)['count'];
if($_GET['action']=='delete'){
    $id=(int)$_GET['id'];
    var_dump($id);
//    die();
    $sql="DELETE FROM `basket` WHERE basket.id={$id} ";
    mysqli_query($db,$sql);
    header('Location:basket.php?message=delete');
    die();
  }
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
   <link rel="stylesheet" href="style.css">
    <title>Document</title>
</head>
<body>
    <?php include "menu.php";?>
    <h1>Корзина</h1>
   <?php foreach($basket as $row):?> 
       
        <div class="product">
           <p class="text"><?=$row['title']?></p> 
           <p class="text"><?=$row['price']?></p>
            <!-- <?php $sum+=$row['price']?> -->
            <button><a href="?action=delete&id=<?=$row['basket_id']?>">Удалить</a></button>
        </div>
          <?php endforeach;?>
     
        <p>Итого:<?=$sum-1?></p>
        <button class="input btn" ><a href="/order.php">Оформить</a></button>
</body>
</html>
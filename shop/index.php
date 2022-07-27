<?php
session_start();
include "db.php";
$session=session_id();
if($_GET['action']=='buy'){
  $id=(int)$_GET['id'];
  mysqli_query($db,"INSERT INTO `basket`(`session_id`,`goods_id`) VALUES('{$session}','{$id}')");
  header("Location: /");
  die();
}
$res=mysqli_query($db,"SELECT count(id) as count FROM `basket` WHERE `session_id`='{$session}'");
$count=mysqli_fetch_assoc($res)['count'];
// include "comment.php";
$result=mysqli_query($db,"SELECT * FROM `products`");
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>

    <header class="heading">Shop<?php include "menu.php";?></header>
    <div class="wrap">
<?php while($row=mysqli_fetch_assoc($result)):?> 
        <div class="product">
       <h1><?= $row['title']?></h1>
       <a href="product.php?id=<?= $row['id'] ?>"><img src="/img/img_small/<?= $row['filename'] ?>" alt="" width="100"></a>
       <br>
       <button class="btn"><a href="/?action=buy&id=<?=$row['id']?>">Купить</a></button>
       <img src="eye.png" alt="" width="20"><?=$row['view']?>
       <p>цена:<?=$row['price']?></p>
       </div>
      
      <?php endwhile;?> 
      </div>
     
</body>
</html>
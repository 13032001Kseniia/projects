<?php
include "db.php";
// $dbc=mysqli_connect('localhost','root','','products');
// $message=[
//     'ok'=>'Сообщение отправлено',
//     'delete'=>'Сообщение удалено',
//     'error'=>'Error'
//  ];
$id = $_GET['id'];
$views = mysqli_query($db, "UPDATE `products` SET `view`=`view`+1 WHERE id ={$id}");
$result = mysqli_query($db, "SELECT * FROM `products` WHERE id ={$id} ");
var_dump($id);

// if($_GET['action']=='add'){
//     $nameUser=strip_tags(htmlspecialchars(mysqli_real_escape_string($dbc,$_POST['nameUser'])));
//     $commentUser=strip_tags(htmlspecialchars(mysqli_real_escape_string($dbc,$_POST['comment'])));
//     $sql="INSERT INTO comments(name,comment,id_product) VALUES ('{$nameUser}','{$commentUser}','{$id}')";
//     mysqli_query($dbc,$sql);
//      header('Location: /?product.php?id={$id}');
//     die();
// }
$name = mysqli_fetch_assoc($result);
// $comments=mysqli_query($dbc,"SELECT * FROM comments ORDER BY id DESC ");
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

        <div>
       <h1 class="title"><?= $name['title']?></h1>
       <img src="/img/img_big/<?=$name['filename']?>" alt="" width="300">
       <p class="text"><?= $name['description']?></p>
       <img src="eye.png" alt="" width="20"><?=$name['view']?>
       </div>
       <!-- <form action="?action=add" method="post">
           <input type="text" placeholder="name" name="nameUser">
           <input type="text" placeholder="review" name="comment">
           <input type="submit" value="submit">
       </form>
       <p><?=$message?></p> -->
       <!-- <h2>Отзывы</h2>
      <?php foreach($comments as $comment):?>
        <p><?=$comment['name']?></p>
        <p><?=$comment['comment']?></p>
      <?php endforeach;?> -->
</body>
</html>
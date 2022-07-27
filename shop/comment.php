<?php
include "db.php";
$messages=[
    'ok'=>'Сообщение отправлено',
    'delete'=>'Сообщение удалено',
    'edit'=>'Сообщение изменено',
    'error'=>'Error'
 ];
 $message='';
 $row=[];
$btn="submit";
$action="add";
 if($_GET['action']=='add'){
    $nameUser=strip_tags(htmlspecialchars(mysqli_real_escape_string($db,$_POST['nameUser'])));
    $commentUser=strip_tags(htmlspecialchars(mysqli_real_escape_string($db,$_POST['comment'])));
    $sql="INSERT INTO comments(name,comment) VALUES ('{$nameUser}','{$commentUser}')";
    mysqli_query($db,$sql);
    header('Location: comment.php?message=ok');
    die();
}
if($_GET['action']=='remove'){
  $id=(int)$_GET['id'];
  $sql="DELETE FROM comments WHERE id={$id}";
  mysqli_query($db,$sql);
  header('Location: comment.php?message=delete');
  die();
}
if ($_GET['action'] == 'edit') {
  $id = (int)$_GET['id'];
  $result = mysqli_query($db, "SELECT * FROM comments WHERE id = {$id}");
  if ($result) $row = mysqli_fetch_assoc($result);
  $btn = "Изменить";
  $action = "save";
}

if ($_GET['action'] == 'save') {
  $id = (int)$_POST['id'];
  $name = strip_tags(htmlspecialchars(mysqli_real_escape_string($db, $_POST['name'])));
  $comment = strip_tags(htmlspecialchars(mysqli_real_escape_string($db, $_POST['comment'])));
  $sql = "UPDATE comments SET name='{$name}', comment='{$comment}' WHERE id = {$id}";
  mysqli_query($db, $sql);

  header('Location: comment.php?message=edit');
  die();
}
$comments=mysqli_query($db,"SELECT * FROM comments ORDER BY id DESC ");
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
<?php include "menu.php";?>
<?=$message?><br>
      <h2 class="title2">Отзывы</h2>
         <form class="form" action="?action=<?=$action?>" method="post">
         <input type="text" name="id" value="<?=$row['id']?>" hidden>
           <input class="input" type="text" placeholder="name" name="nameUser" value="<?=$row['name']?>">
           <input class="input" type="text" placeholder="review" name="comment" value="<?=$row['comment']?>">
           <input class="input" type="submit" value="<?=$btn?>">
       </form>
      
     
     
       <?php foreach($comments as $comment):?>
        <p class="text_comment"><?=$comment['name']?>:<?=$comment['comment']?><a href="?action=remove&id=<?=$comment['id']?>">X</a>
       <a href="?action=edit&id=<?=$comment['id']?>"> <img src="edit.png" width="20"></a></p>
       
      <?php endforeach;?>
</body>
</html>
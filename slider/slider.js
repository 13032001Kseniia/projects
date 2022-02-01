var imagesArr=["1img.jpg","2img.jpg","3img.jpg","4img.jpg"];

var count = 0;

function next(id){
var img = document.getElementById(id);

if(count ==(imagesArr.length-1)) 
{
     count = 0 
}
else count++;

img.src = "img\\" +imagesArr[count]; 
}

function back(id){
    var img = document.getElementById(id);
    
   if(count == 0) {
         count = imagesArr.length-1;
      }
   else count--;
    
    img.src = "img\\" + imagesArr[count]; 
    }
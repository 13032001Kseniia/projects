function submitForm(){
  regexp_name=/^[a-zA-Zа-яА-ЯёЁ'][a-zA-Z-а-яА-ЯёЁ' ]+[a-zA-Zа-яА-ЯёЁ']?$/;
  regexp_phone=/(?:\+|\d)[\d\-\(\) ]{9,}\d/g;
  regexp_mail= /[-.\w]+@([\w-]+\.)+[\w-]+/g;
  let reg=[];
  reg.push(regexp_name);
  reg.push(regexp_phone);
  reg.push(regexp_mail);
  console.log(reg);
  let input=document.querySelectorAll(".input");
  console.log(input);
  // event.preventDefault();
  let value=valueInput(input);
  console.log(value);
  regInp(value,reg,input);
}
function valueInput(input){
  let value=[];
  for(let i=0;i<input.length-1;i++){
   value.push(input[i].value);
  }
  console.log(value);
  return value;
}
 function regInp(value,reg,input){
   for(let i=0;i<value.length;i++){
     if(!value[i].match(reg[i])){
      event.preventDefault();
      console.log("error");
      error(input[i]);
     }
     else{
       removeError(input[i]);
     }
   }
 }
 function error(input){
   input.classList.add("error");
 }
 function removeError(input){
  input.classList.remove("error");
 }

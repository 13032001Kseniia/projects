class Components_Hamburger{
   constructor(components){
      this.name=components.value;
      this.price=+components.dataset['price'];
      this.calories=+components.dataset['calories'];
   }
}
class Hamburger {
    constructor(size, stuffing,topping) { 
        this.size=new Components_Hamburger(this.getSize(size));
        this.stuffing=this.getToppings(stuffing);
        this.topping=this.getToppings(topping);
     }
    
    getToppings(name){
      let result=[];
      this.getStuffing(name).forEach(element=>{
      let obj=new Components_Hamburger(element);
      result.push(obj);
     });
     return result;

    } 
        
    getSize(name) {       
       return document.querySelector(`input[name=${name}]:checked`);

           }
    getStuffing(name) {   
      return [...document.querySelectorAll(`input[name=${name}]:checked`)];
          }
    calculatePrice() {  
           let  total_price=this.size.price;
           this.stuffing.forEach(element =>{total_price+=element.price});
          this.topping.forEach(element=> {total_price+=element.price});
           return total_price;
          }
    calculateCalories() {  
      let  total_calories=this.size.calories;
     this.stuffing.forEach(element =>total_calories+=element.calories);
     this.topping.forEach(element=> total_calories+=element.calories);
      return total_calories;
       }
       OutputTotal(price,calories){
          document.querySelector(price).innerHTML=this.calculatePrice();
         document.querySelector(calories).innerHTML=this.calculateCalories();
       }
  }
  
 
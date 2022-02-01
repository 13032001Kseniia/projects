// const app=new Vue({
//     el:"#app",
//     data:{
//         products:[],
//         backets:[],
//         backet_show:false,
//         search:'',
//         arr_search:[],
//     },
//     methods:{
//        getJSON(url){
//            return fetch(url)
//            .then(data=>data.json());
//        },
//        filter(){
//         let regexp = new RegExp(this.search, 'i');
//         this.arr_search =  this.products.filter(el => regexp.test(el.product_name));
//     },
//     deleteProduct(item){
//         this.getJSON(`https://raw.githubusercontent.com/GeekBrainsTutorial/online-store-api/master/responses/addToBasket.json`)
//         .then(data=>{
//             if(data.result===1){
//                 if(item.quantity>1){
//                     item.quantity--;
//                 }
//                 else{
//                    this.backet.splice(this.backet.indexOf(item),1);
//                 }
//             }
//         })
//     },
//     addProduct(item){
//         this.getJSON(`https://raw.githubusercontent.com/GeekBrainsTutorial/online-store-api/master/responses/addToBasket.json`)
//         .then(data=>{
//             if(data.result===1){
//                 let find= this.backet.find(el=>{el.product_name ===item.product_name });
//                 if(find){
//                     backet.quantity++;
//                 }
//                 else{
//                     const obj=Object.assign({quantity:1},item);
//                     this.backet.push(obj);
//                 }
//             }
//         })
//     }
//     },
//     mounted(){
//         this.getJSON(`https://raw.githubusercontent.com/GeekBrainsTutorial/online-store-api/master/responses/catalogData.json`)
//         .then(data=>{
//             for(let el of data){
//                 this.$data.products.push(el);
//                 this.$data.arr_search.push(el);
//             }
//         });
//         this.getJSON(`https://raw.githubusercontent.com/GeekBrainsTutorial/online-store-api/master/responses/getBasket.json`)
//         .then(res=>{
//             for(let el of res.contents){
//                 this.backets.push(el);
//             }
//         })
      
//     }
// })
const app=new Vue({
    el:"#app",
    data:{
        products:[],
        backet:[],
        backet_show:false,
        search:'',
        arr_search:[],
    },
    methods:{
       getJSON(url){
           return fetch(url)
           .then(data=>data.json());
       },
       filter(){
        let regexp = new RegExp(this.search, 'i');
        this.arr_search =  this.products.filter(el => regexp.test(el.product_name));
    },
    deleteProduct(item){
        this.getJSON(`https://raw.githubusercontent.com/GeekBrainsTutorial/online-store-api/master/responses/addToBasket.json`)
        .then(data=>{
            if(data.result===1){
                if(item.quantity>1){
                    item.quantity--;
                }
                else{
                   this.backet.splice(this.backet.indexOf(item),1);
                }
            }
        })
    },
    addProduct(item){
        this.getJSON(`https://raw.githubusercontent.com/GeekBrainsTutorial/online-store-api/master/responses/addToBasket.json`)
        .then(data=>{
            if(data.result===1){
                let find= this.backet.find(el=>{el.product_name ===item.product_name });
                if(find){
                    backet.quantity++;
                }
                else{
                    const obj=Object.assign({quantity:1},item);
                    this.backet.push(obj);
                }
            }
        })
    }
    },
    mounted(){
        this.getJSON(`https://raw.githubusercontent.com/GeekBrainsTutorial/online-store-api/master/responses/catalogData.json`)
        .then(data=>{
            for(let el of data){
                this.$data.products.push(el);
                this.$data.arr_search.push(el);
            }
        });
        this.getJSON(`https://raw.githubusercontent.com/GeekBrainsTutorial/online-store-api/master/responses/getBasket.json`)
        .then(res=>{
            for(let el of res.contents){
                this.backet.push(el);
            }
        })
      
    }
})
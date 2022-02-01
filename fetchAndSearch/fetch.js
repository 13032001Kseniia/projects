const app=new Vue({
    el:'#app',
    data:{
        search:'',
        arr_search:[],
        goods:[],
        arr_before:[],
    },
    methods:{
       getJson(url){
           return fetch(url)
           .then(data=>data.json())
           .catch(error=>console.log(error))
       },
        filter(){
            let regexp=new RegExp(this.search,'i');
            this.goods=this.arr_before.filter(el=>regexp.test(el.Name ));
        }
    
    },
    mounted(){
        this.getJson(`https://www.cbr-xml-daily.ru/daily_json.js`)
        .then(res=>{
            // for(let el in res.Valute){
               
            //     //this.$data.goods.push(el);
            //    this.arr_search.push(el);
            //    console.log(el);
             this.arr_search=res.Valute;
             console.log(this.arr_search);
             for(let el in this.arr_search)
             {
                this.arr_before.push(this.arr_search[el]);
                this.goods.push(this.arr_search[el]);

                console.log(this.goods);
            }
        })
    }
})

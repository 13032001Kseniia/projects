let q=-1,h=1,EI=1000,n=19;
arr_h=[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16];
arr_h1=[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16];
let arr_w=[];
let arr_a=[[0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],[1,-2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],[1,	-4,	6,	-4,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0],
[0,	1,	-4,	6,	-4,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0],[0,	0,	1,	-4,	6,	-4,	1,	0,	0,	0,	0,	0,	0	,0,	0,	0,	0,	0,	0],
[0,	0	,0,	1,	-4,	6,	-4,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0],[0,	0,	0,	0,	1,	-4,	6,	-4,	1,	0,	0,	0,	0	,0	,0,	0,	0,	0,	0],
[0,	0,	0,	0,	0,	1,	-4,	6,	-4,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0],[0,	0,	0,	0,	0,	0,	1,	-4,	6,	-4,	1,	0,	0,	0	,0,	0,	0,	0,	0],
[0,	0,	0,	0,	0,	0,	0,	0	,0,	1,	0,	0,	0,	0,	0,	0	,0,	0,	0],[0,	0,	0,	0,	0	,0,	0,	0	,1,	-4,	6,	-4,	1,	0,	0,	0,	0,	0,	0],
[0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	-4,	6,	-4,	1,	0,	0,	0,	0,	0],[0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	-4,	6,	-4,	1,	0,	0,	0,	0],
[0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	-4,	6,	-4,	1,	0,	0,	0],[0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	-4,	6,	-4,	1,	0,	0],
[0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	-4,	6,	-4,	1,	0],[0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	-4,	6,	-4,	1],
[0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0],[0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	-1,	0,	1]],
arr_m=[[1,	-2,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,0,	0,	0],[0,	1,	-2,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0],
[0,	0,	1,	-2,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0],[0,	0,	0,	1,	-2,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0],
[0,	0,	0,	0,	1,	-2,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0],[0,	0,	0,	0,	0,	1,	-2,	1,	0,	0	,0,	0,	0,	0,	0,	0,	0,	0,	0],
[0,	0,	0,	0,	0,	0,	1,	-2,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0],[0,	0,	0,	0,	0,	0	,0,	1,	-2,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0],
[0,	0,	0,	0,	0,	0,	0,	0,	1,	-2,	1,	0,	0	,0,	0,	0,	0,	0,	0],[0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	-2,	1,	0,	0,	0	,0,	0,	0,	0],
[0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	-2,	1,	0,	0,	0,	0,	0,	0],[0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	-2,	1,	0,	0,	0,	0,	0],
[0,	0,	0,	0,	0,	0,	0,	0	,0,	0,	0,	0,	1,	-2,	1,	0,	0,	0,	0],[0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	-2,	1,	0,	0,	0],
[0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	-2,	1,	0,	0],[0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	-2,	1,	0],
[0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	-2,	1]],
arr_f=[[-1,	0,	1,	0	,0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0],[0,	-1,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0	,0,	0,	0,	0,	0,	0,	0],
[0,	0,	-1,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0],[0,	0,	0,	-1,	0,	1,	0,	0,	0,	0,	0	,0,	0,	0,	0,	0,	0,	0,	0],
[0,	0,	0,	0,	-1,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0],[0,	0,	0,	0,	0,	-1,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0],
[0,	0,	0,	0,	0,	0,	-1,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0],[0,	0,	0,	0,	0,	0,	0,	-1,	0,	1,	0,	0,	0,	0,	0,	0	,0,	0,	0],
[0,	0,	0,	0,	0,	0,	0,	0,	-1,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0],[0,	0,	0,	0,	0,	0,	0,	0,	0,	-1,	0,	1,	0,	0,	0,	0,	0,	0,	0],
[0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	-1,	0,	1,	0,	0,	0,	0	,0,	0],[0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	-1,	0,	1,	0,	0,	0,	0,	0],
[0,	0,	0,	0,	0,	0,	0,	0,	0	,0,	0,	0,	-1,	0,	1,	0,	0	,0,	0],[0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	-1,	0,	1,	0,	0,	0],
[0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	-1,	0,	1,	0,	0],[0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	-1,	0,	1,	0],
[0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	-1,	0,	1]],
arr_right=[[0],[0],[q*Math.pow(h,4)/EI],[q*Math.pow(h,4)/EI],[q*Math.pow(h,4)/EI],[q*Math.pow(h,4)/EI],[q*Math.pow(h,4)/EI],[q*Math.pow(h,4)/EI],[q*Math.pow(h,4)/EI],[0],[q*Math.pow(h,4)/EI],[q*Math.pow(h,4)/EI],[q*Math.pow(h,4)/EI],[q*Math.pow(h,4)/EI],[q*Math.pow(h,4)/EI],[q*Math.pow(h,4)/EI],[q*Math.pow(h,4)/EI],[0],[0]],
arr_v=[],v_m=[],v_f=[];

function direct_way(arr1,arr2,n){
    let max,k=0,index,eps = 0.00001,temp,x=[];
    while(k<n){
      max=Math.abs(arr1[k][k]);
      index=k;
      for(let i=k+1;i<n;i++){
        if(Math.abs(arr1[i][k])>max)
        {
          max=Math.abs(arr1[i][k]);
          index=i;
        }
      }
      if(max<eps){
        document.write("Решение нет");
        document.write(index,"матрица А");
      }
      for(let j=0;j<n;j++){
        temp=arr1[k][j];
        arr1[k][j]=arr1[index][j];
        arr1[index][j]=temp;
      }
      temp=arr2[k];
      arr2[k]=arr2[index];
      arr2[index]=temp;
    
    for(let i=k;i<n;i++){
      temp=arr1[i][k];
      
      if(Math.abs(temp)<eps)
      continue;
      for(let j=0; j<n;j++)
      arr1[i][j]=arr1[i][j]/temp;
      arr2[i]=arr2[i]/temp;    
      if(i==k) continue;
      for(let j=0;j<n;j++)
      arr1[i][j]=arr1[i][j]-arr1[k][j];
      arr2[i]=arr2[i]-arr2[k]; 
    }
    k++;
   }
   for(let k=n-1;k>=0;k--){
      
      x[k]= (arr2[k]);
     
  for(let i=0;i<k;i++)
      arr2[i]=arr2[i]-arr1[i][k]*x[k];
     
   }
   document.write("Решение матрицы Гаусса:","<p>")
   for(let i=0;i<n;i++){
   document.write("<p>");   
   document.write(x[i]);
   }
return arr2;
  }
  
  function multi_Matrix(H,B)
{
var rowsH = H.length, colsH = H[0].length,
  rowsB = B.length, colsB = B[0].length,
  C = [];

if (colsH != rowsB)
return false;

for (var i = 0; i < rowsH; i++) C[i] = [];

for (var k = 0; k < colsB; k++)
{ for (var i = 0; i < rowsH; i++)
  { var temp = 0;
    for (var j = 0; j < rowsB; j++) temp += H[i][j]*B[j][k];
    C[i][k] = temp;
  }
}


document.write("<table border='1'>");
for(let i=0;i<n;i++){
  document.write("<tr>");
  
      document.write("<td>" +C[i] + "</td>");
   
    document.write("</tr>");
   }
document.write("</table>");

return C;
}
function listToMatrix(list, elements) {
  var matrix = [], i, k;

  for (i = 0, k = -1; i < list.length; i++) {
      if (i % elements === 0) {
          k++;
          matrix[k] = [];
      }

      matrix[k].push(list[i]);
  }

  return matrix;
}
document.write("<p>"); 
arr_v=direct_way(arr_a,arr_right,n);
document.write("<p>");

arr_w=listToMatrix(arr_v,1);
document.write("<p>"); 
document.write("Вектор моментов");
document.write("<p>"); 
v_m=multi_Matrix(arr_m,arr_w);
document.write("Вектор углов поворота");
v_f=multi_Matrix(arr_f,arr_w);
const tags = arr_h;
const dataSales2020 = {
    label: "Вектор перемещений",
    data:arr_v.splice(1) , 
    backgroundColor: 'rgba(255, 255, 0,0.2)', 
    borderColor: 'rgba(54, 162, 235, 1)', 
    borderWidth: 1,
};
const $grafica = document.querySelector("#grafica");
new Chart($grafica, {
    type: 'line',
    data: {
        labels: tags,
        datasets: [
            dataSales2020,
            
        ]
    },
    options: {
        scales: {
            yAxes: [{
                ticks: {
                    max:0.005,
                    min:-0.03
                }
            }],
        },
    }
});
const x_h = arr_h1;
const dataSales = {
    label: "Моменты",
    data:v_m , 
    backgroundColor: 'rgba(255, 0, 0,0.2)', 
    borderColor: 'rgba(54, 162, 235, 1)', 
    borderWidth: 1,
};
const $grafica2 = document.querySelector("#grafica2");


new Chart($grafica2, {
    type: 'line',
    data: {
        labels: x_h,
        datasets: [
            dataSales,
            
        ]
    },
    options: {
        scales: {
            yAxes: [{
                ticks: {
                    max:0.006,
                    min:-0.007
                }
            }],
        },
    }
});
const a_h = arr_h1;
const data = {
    label: "Углы поворота",
    data:v_f , 
    backgroundColor: 'rgba(0, 255, 0,0.2)', 
    borderColor: 'rgba(54, 162, 235, 1)', 
    borderWidth: 1,
};
const $grafica3 = document.querySelector("#grafica3");


new Chart($grafica3, {
    type: 'line',
    data: {
        labels: a_h,
        datasets: [
            data,
            
        ]
    },
    options: {
        scales: {
            yAxes: [{
                ticks: {
                    max:0.02,
                    min:-0.03
                }
            }],
        },
    }
});

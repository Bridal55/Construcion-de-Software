"use strict";


const latteValue = document.getElementById("Late");
const americanoValue = document.getElementById("Americano");

const change_title_btn = document.getElementById("Change title");


latteValue.addEventListener("click", () => {    

    if (latteValue.textContent === "4$") {
        latteValue.textContent = "8$";
    } 

});


americanoValue.addEventListener("click", () => {    

    if (americanoValue.textContent === "2.50$") {
        americanoValue.textContent = "5$";
    } else {
        americanoValue.textContent = "2.50$";
    }

});


change_title_btn.addEventListener("click", () => {
    document.querySelector("h1").textContent = "CAT CAT CAT CAFE";
});



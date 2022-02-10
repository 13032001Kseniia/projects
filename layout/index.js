btn = document.querySelectorAll('#click');
block = document.querySelectorAll('.click')
for (let i = 0; i < btn.length; i++)
    btn[i].addEventListener("click", () => {
        block[i].classList.toggle('visibility');
    });
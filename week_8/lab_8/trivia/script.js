document.addEventListener('DOMContentLoaded', function() {
    const answer = document.querySelectorAll("#femur, #tibia, #stapes, #radius");
    const rightAnswer = document.getElementById("stapes");
    const correctness = document.getElementById("correctness");

answer.forEach(answer => {
    if(answer == rightAnswer) {
        answer.addEventListener("click", function() {
            changeColor(this);
        })
        correctness.textContent = "Correct!";
    }
    else {
        answer.addEventListener("click", function(){
            changeColorRed(this);
        })
        correctness.textContent = "Incorrect!";
    }

});

function changeColor(element) {
    element.className = "color1";
}

function changeColorRed(element) {
    element.className = "color2";
}
});


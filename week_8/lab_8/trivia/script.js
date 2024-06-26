document.addEventListener('DOMContentLoaded', function() {
    const answer = document.querySelectorAll("#femur, #tibia, #stapes, #radius");
    const rightAnswer = document.getElementById("stapes");
    const correctness = document.getElementById("correctness");

    const freeResponse = document.getElementById("free-response");
    //const submitAnswer = document.getaElementById("submit-answer");
    //const correctAnswer = "Vatican City";

    
    // Multiple selecttype="submit"ion quiestion
    answer.forEach(answer => {
        if(answer == rightAnswer) {
            answer.addEventListener("click", function() {
                changeColor(this);
                correctness.textContent = "Correct!";
            })
            
        }
        else {
            answer.addEventListener("click", function(){
                changeColorRed(this);
                correctness.textContent = "Incorrect!";
            })
            
        }

    });

    function changeColor(element) {
        element.className = "color1";
    }

    function changeColorRed(element) {
        element.className = "color2";
    }

    // Free answer quiestion
    document.querySelector('#check').addEventListener('click', function() {
        let input = document.querySelector('input');
        if (input.value === 'Vatican City') {
            input.style.backgroundColor = "green";
            document.querySelector('#feedback').innerHTML = "Correct!";
        } else {
            input.style.backgroundColor = "red";
            document.querySelector('#feedback').innerHTML = "Incorrect!";
        }
    });
});


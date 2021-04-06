var SLIDE = [
    { src: "assets/img1.png", alt: "img1", text: "lorem" },
    { src: "assets/img2.png", alt: "img2", text: "ipsum" },
    { src: "assets/img3.jpg", alt: "img3", text: "dolores" },
    { src: "assets/img4.jpg", alt: "img4", text: "mozzarella" },
];
var SLIDING_INTERVAL = 3000; //in milliseconds

function setAttribute(element, attribute, value) {
    element.attr(attribute, value);
}

function initializeSlides() {
    for (let i = 0; i < SLIDE.length; i += 1) {
        var currentSlide = "#slide" + (i + 1);
        var slideImg = $(currentSlide).children("img");
        setAttribute(slideImg, "src", SLIDE[i].src);
        setAttribute(slideImg, "alt", SLIDE[i].alt);
        $(currentSlide).children("p")[0].innerHTML = SLIDE[i].text;
    }
}

function slideLeft() {
    var first = SLIDE[0];
    for (var i = 0; i < SLIDE.length - 1; i += 1) {
        SLIDE[i] = SLIDE[i + 1];
    }
    SLIDE[SLIDE.length - 1] = first;
    initializeSlides();
}

function slideRight() {
    var last = SLIDE[SLIDE.length - 1];
    for (var i = SLIDE.length - 1; i > 0; i -= 1) {
        SLIDE[i] = SLIDE[i - 1];
    }
    SLIDE[0] = last;
    initializeSlides();
}

function maximize(slideId) {
    var modalImg = $("#modal div").children("img");
    setAttribute(modalImg, "src", SLIDE[slideId].src);
    setAttribute(modalImg, "alt", SLIDE[slideId].alt);
    $("#modal").css("display", "block")
    window.clearInterval(window.intervalId);
}

(() => {
    initializeSlides();

    window.intervalId = window.setInterval(slideRight, SLIDING_INTERVAL);

    $("#leftButton").click(slideLeft);
    $("#rightButton").click(slideRight);
    window.onclick = function(event) {
        if (event.target == $("#modal")[0]){
                modal.style.display = "none";
                window.intervalId = window.setInterval(slideRight, SLIDING_INTERVAL);
        }
    }
    for(let i = 0; i < SLIDE.length; i += 1){
        var currentSlideId = "#slide" + (i + 1);
        $(currentSlideId).click(() => maximize(i));
    }
})()
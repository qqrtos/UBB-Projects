var TILES_IDS = ["A", "B", "C", "D", "E", "F", "G", "H"]
var COMPLETE_STATUS = [
    ["A", "B", "C"],
    ["D", "E", "F"],
    ["G", "H", ""]
]

function isGameFinished(){
    return TILES_IDS
        .map(id => document.getElementById(id))
        .filter(e => e.id != e.textContent)
        .length == 0;
}

function handleTileClick(target) {
    console.log(target.id);
}

(() => {
    TILES_IDS.forEach(e => {
        var target = document.getElementById(e);
        target.addEventListener('click', () => handleTileClick(target));
    });
})();
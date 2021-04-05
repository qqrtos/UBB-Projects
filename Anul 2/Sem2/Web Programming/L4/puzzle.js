var TILES_IDS = ["A", "B", "C", "D", "E", "F", "G", "H", "empty"]
var STATUS = [
    ["A", "B", "C"],
    ["D", "E", "F"],
    ["G", "empty", "H"]
]

function isGameFinished(){
    return TILES_IDS
        .map(id => document.getElementById(id))
        .filter(e => e.id != e.textContent && e.id !== "empty")
        .length == 0;
}

function moveToEmptyTile(target){
    var position = target.getAttribute("pos")
                         .split(',')
                         .map(a => parseInt(a));

    var x = position[0];
    var y = position[1];

    function updateTiles(targetX, targetY){
        let targetTile = document.querySelectorAll(`[pos="${targetX},${targetY}"]`)[0];
        targetTile.classList.remove("empty");
        targetTile.innerHTML = STATUS[x][y];
        document.querySelectorAll(`[pos="${x},${y}"]`)[0].classList.add("empty");

        let aux = STATUS[x][y];
        STATUS[x][y] = STATUS[targetX][targetY];
        STATUS[targetX][targetY] = aux;
    }

    if(x - 1 >= 0 && STATUS[x - 1][y] === "empty") {
        updateTiles(x - 1, y);
    }
    else if(x + 1 < 3 && STATUS[x + 1][y] === "empty") {
        updateTiles(x + 1, y);
    }
    else if(y - 1 >= 0 && STATUS[x][y - 1] === "empty") {
        updateTiles(x, y - 1);
    }
    else if(y + 1 > 0 && STATUS[x][y + 1] === "empty") {
        updateTiles(x, y + 1);
    }
}

function handleTileClick(target) {
    if (isGameFinished()) {
        alert("WINNER WINNER!");
        return;
    }
    
    moveToEmptyTile(target);
}

(() => {
    TILES_IDS.forEach(e => {
        var target = document.getElementById(e);
        target.addEventListener('click', () => handleTileClick(target));
    });
})();
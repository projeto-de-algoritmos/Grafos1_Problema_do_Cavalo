create_board();

function squareEvent(element) {
	element.addEventListener("click", () => {
		const n = parseInt(element.getAttribute("id"));
		const arr = knight_tour(n);	
		console.log(arr);
		let count = 1;
		for(let i in arr) {
			const square = document.getElementById(arr[i]);
			square.innerHTML = count;
			count++;
		}
	})
}

function cleanBoard() {
	let squares = document.getElementsByTagName("td");
	for(let s in squares) {
		squares[s].innerHTML = "x";
	}
}

function create_board(){
	const board = document.createElement("table");
	let color = true;	
	let count = 0;

	for(let i = 0; i < 8; i++) {
		let row = document.createElement("tr");
		for(let j = 0; j < 8; j++) {
			col = document.createElement("td");	
			squareEvent(col);
			col.setAttribute("id", count);
			if(color)
				col.setAttribute("class", "white_square");
			else
				col.setAttribute("class", "black_square");

			color = !color
			row.appendChild(col);
			count++;
		}
		color = !color
		board.append(row);
	}
	document.getElementById("board").appendChild(board);
}



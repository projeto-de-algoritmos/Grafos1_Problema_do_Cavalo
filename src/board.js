create_board();

function create_board(){
	const board = document.createElement("table");
	let color = true;	
	let count = 1;

	for(let i = 0; i < 8; i++) {
		let row = document.createElement("tr");
		for(let j = 0; j < 8; j++) {
			col = document.createElement("td");	
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

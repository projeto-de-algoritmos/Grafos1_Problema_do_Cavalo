#include <stdlib.h>
#include <emscripten.h>

typedef struct
{
	int x;
	int y;
} coor;

typedef struct
{
	int x[8][8];
} Board;

Board board;
int w = 0;

coor * gen_knight_moves(coor N)
{
	coor off_sets[8] = {{-1, -2}, {-1, 2}, {-2, -1}, {-2, 1},
							{1, -2}, {1, 2}, {2, -1}, {2,1}};

	coor *moves = malloc(sizeof(coor) * 8);

	for (int i = 0; i < 8; i++)
	{
		coor aux = {N.x + off_sets[i].x, N.y + off_sets[i].y};
		moves[i] = aux;
	}

	return moves;
}

int is_valid_move(coor N)
{
	return N.x >= 0 && N.x < 8 && N.y >= 0 && N.y < 8;
}

void dfs_visited(coor N, Board visited, int count, char * res)
{
	if (visited.x[N.x][N.y]) return;

	visited.x[N.x][N.y] = 1;

	res[count++] = board.x[N.x][N.y];

	if (count == 64)
	{
		w = 1;
		return;
	}
	coor *moves = gen_knight_moves(N);

	for (int i = 0; i < 8; i++)
	{
		if (is_valid_move(moves[i]))
			dfs_visited(moves[i], visited, count, res);	

		if(w) break;
	}

	free(moves);
}

EMSCRIPTEN_KEEPALIVE
char * dfs(int x, int y)
{
	int c = 1;
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			board.x[i][j] = c++;
		}
	}
	coor N = {x, y};
	Board visited;
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			visited.x[i][j] = 0;

	char * res = malloc(sizeof(char) * 64);
	dfs_visited(N, visited, 0, res);	
	return res;
}

EMSCRIPTEN_KEEPALIVE
void wfree(void *ptr)
{
	free(ptr);
}

int main() { return 0; }

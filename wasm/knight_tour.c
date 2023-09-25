#include <stdlib.h>
#include <stdio.h>
//#include <emscripten.h>

typedef struct
{
	int x;
	int y;
} coor;

typedef struct
{
	int x[8][8];
} Board;

typedef struct
{
	coor moves[8];
	int i;
} stack;


coor pop(stack *s)
{
	s->i--;
	return s->moves[s->i];
}

void push(coor c, stack *s)
{
	s->moves[s->i] = c;
	s->i++;
}

Board board;

int is_valid_move(coor N)
{
	return N.x >= 0 && N.x < 8 && N.y >= 0 && N.y < 8;
}

int was_visited(coor N, Board v)
{
	return v.x[N.x][N.y];
}

stack * gen_knight_moves(coor N, Board visited)
{
	coor off_sets[8] = {{-1, -2}, {-1, 2}, {-2, -1}, {-2, 1},
							{1, -2}, {1, 2}, {2, -1}, {2,1}};

	stack *moves = malloc(sizeof(stack));
	moves->i = 0;

	for (int i = 0; i < 8; i++)
	{
		coor aux = {N.x + off_sets[i].x, N.y + off_sets[i].y};
		if(is_valid_move(aux) && !was_visited(aux, visited)) push(aux, moves);
	}

	return moves;
}

int count_valid(coor N, Board visited)
{
	stack *s = gen_knight_moves(N, visited);
	int c = s->i;	
	free(s);
	return c;
}

void order(stack *s, Board visited)
{
	for(int i=0; i<s->i; i++)
	{
		for(int j=i+1; j<s->i; j++)
		{
			int x = count_valid(s->moves[i], visited);
			int y = count_valid(s->moves[j], visited);

			if(x < y)
			{
				coor tmp = s->moves[i];
				s->moves[i] = s->moves[j];
				s->moves[j] = tmp;
			}
		}
	}
}

int dfs_visited(coor N, Board visited, int count, char * res)
{
	if (was_visited(N, visited)) return 0;

	visited.x[N.x][N.y] = 1;

	res[count] = board.x[N.x][N.y];
	count++;


	if (count == 64)
	{
		return 1;
	}

	stack *m = gen_knight_moves(N, visited);
	order(m, visited);

	int done = 0;

	while(m->i > 0)
	{
		done = dfs_visited(pop(m), visited, count, res);	

		if(done) return 1;
	}
	free(m);
	return 0;
}

//EMSCRIPTEN_KEEPALIVE
char * dfs(int x, int y)
{
	int c = 0;
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

//EMSCRIPTEN_KEEPALIVE
void wfree(void *ptr)
{
	free(ptr);
}

//int is_valid(char *arr) {
//	int c[64] = {0};
//	for(int i= 0; i<64; i++){
//		if(c[i]) return 0;
//		c[i]++;
//	}
//	return 1;
//}

int main() { 
	
	
	for(int i= 0; i<5; i++)
	{
		int x = i/8;
		int y = i%8;
		char *arr = dfs(x, y);
		for(int i= 0; i<64; i++)
			printf("%d ", arr[i]);	
		printf("\n");
		free(arr);
	}
	return 0;
}

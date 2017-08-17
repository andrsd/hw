#include <iostream>

// Number of rows
static const unsigned int M = 8;
// number of columns
static const unsigned int N = 8;

// The chess board
struct Board {
	int pos[M][N];
};

unsigned int solutions_tried = 0;

/**
 * Initialize an empty board
 */
void init_board(Board & b) {
	for (unsigned int i = 0; i < M; i++)
		for (unsigned int j = 0; j < N; j++)
			b.pos[i][j] = 0;
}

void print_board(Board & b) {
	for (unsigned int i = 0; i < M; i++) {
		for (unsigned int j = 0; j < N; j++)
			std::cout << " " << b.pos[i][j];
		std::cout << std::endl;
	}
}

/**
 * Checks if the board is a solution
 */
bool check_solution(Board & b) {
	// number of queens in a row, a column or a diagonals
	unsigned int num_q;

	// check rows
	for (unsigned int i = 0; i < M; i++) {
		num_q = 0;
		for (unsigned int j = 0; j < N; j++)
			if (b.pos[i][j])
				num_q++;
		if (num_q > 1)
			return false;
	}

	// check columns
	for (unsigned int j = 0; j < N; j++) {
		num_q = 0;
		for (unsigned int i = 0; i < M; i++)
			if (b.pos[i][j])
				num_q++;
		if (num_q > 1)
			return false;
	}

	// check main diagonals
	const unsigned int N_DIAGS = 15;
	unsigned int diag_len[]  = { 1, 2, 3, 4, 5, 6, 7, 8, 7, 6, 5, 4, 3, 2, 1 };
	{
		unsigned int start_i[] = { 7, 6, 5, 4, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
		unsigned int start_j[] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7 };
		for (unsigned int k = 0; k < N_DIAGS; k++) {
			num_q = 0;
			for (unsigned int i = start_i[k], j = start_j[k], l = 0; l < diag_len[k]; i++, j++, l++) {
				if (b.pos[i][j])
					num_q++;
			}
			if (num_q > 1)
				return false;
		}
	}
	// check minor diagonals
	{
		// inside a block so I can reuse the name
		unsigned int start_i[] = { 0, 1, 2, 3, 4, 5, 6, 7, 7, 7, 7, 7, 7, 7, 7 };
		unsigned int start_j[] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7 };
		for (unsigned int k = 0; k < N_DIAGS; k++) {
			num_q = 0;
			for (unsigned int i = start_i[k], j = start_j[k], l = 0; l < diag_len[k]; i--, j++, l++) {
				if (b.pos[i][j])
					num_q++;
			}
			if (num_q > 1)
				return false;
		}
	}

	return true;
}

// brute force

bool brute_force(Board & b, int q_left) {
	if (q_left == 0) {
		solutions_tried++;
		if (check_solution(b)) {
			print_board(b);
			return true;
		}
		return false;
	}

	for (unsigned int i = 0; i < M; i++)
		for (unsigned int j = 0; j < N; j++) {
			if (b.pos[i][j] == 0) {
				// place a queen
				b.pos[i][j] = 1;
				// place another one
				if (brute_force(b, q_left - 1))
					return true;
				// remove the queen
				b.pos[i][j] = 0;
			}
		}

	return false;
}

//

bool pruning(Board & b, int q_left) {
	if (q_left == 0) {
		solutions_tried++;
		if (check_solution(b)) {
			print_board(b);
			std::cout << std::endl;
			return true;
		}
		return false;
	}

	// create a mask of impossible positions
	Board mask;
	init_board(mask);
	for (unsigned int i = 0; i < M; i++) {
		for (unsigned int j = 0; j < N; j++) {
			if (b.pos[i][j] == 1) {
				// mask the row
				for (unsigned int k = 0; k < N; k++)
					mask.pos[i][k] = 1;
				// mask the column
				for (unsigned int k = 0; k < M; k++)
					mask.pos[k][j] = 1;

				for (int k = i, l = j; (k >= 0) && (l < N); k--, l++)
					mask.pos[k][l] = 1;

				for (int k = i, l = j; (k < M) && (l < N); k++, l++)
					mask.pos[k][l] = 1;

				for (int k = i, l = j; (k >= 0) && (l >= 0); k--, l--)
					mask.pos[k][l] = 1;

				for (int k = i, l = j; (k < M) && (l >= 0); k++, l--)
					mask.pos[k][l] = 1;
			}
		}
	}

	for (unsigned int i = 0; i < M; i++)
		for (unsigned int j = 0; j < N; j++) {
			if (b.pos[i][j] == 0 && mask.pos[i][j] == 0) {
				// place a queen
				b.pos[i][j] = 1;
				// place another one
				if (pruning(b, q_left - 1))
					return true;
				// remove the queen
				b.pos[i][j] = 0;
			}
		}

	return false;
}

int main() {
	Board b;

	init_board(b);

	//brute_force(b, 8);
	pruning(b, 8);

	return 0;
}

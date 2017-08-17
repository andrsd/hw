#include <iostream>

/**
 * The chess board
 *
 * The OOP does not really buy us anything here.  But it shows how one can go about
 * solving this kind of a problem. We define data - the chess board - and we implement
 * operations on them. Operations like: initialize, print the board (when we find a
 * solution), check that placed queens satisfy the solurion to our puzzle, and of
 * course methods for finding the solution.
 *
 * Another thing we demonstrate here is recursion.
 *
 * The obvious downside of this code is that it finds one solution and then it quits.
 * We do not have to terminate the search though. The recursion would give us all the
 * possible solutions, but since the code distinguish between queens it will print
 * more than just the uniques solutions. What we mean by that is that in any given
 * solutions, if we swapped queen one and two our code considers that as a different
 * solution, while we as humans treat that as the same solution.
 */
class Board
{
public:
	/**
	 * Initialize an empty board
	 */
	Board() {
		for (unsigned int i = 0; i < M; i++)
			for (unsigned int j = 0; j < N; j++)
				_pos[i][j] = 0;
	}

	void print() {
		for (unsigned int i = 0; i < M; i++) {
			for (unsigned int j = 0; j < N; j++)
				std::cout << " " << _pos[i][j];
			std::cout << std::endl;
		}
	}

	/**
	 * Checks if the board is a solution
	 */
	bool check_solution() {
		// number of queens in a row, a column or a diagonals
		unsigned int num_q;

		// check rows
		for (unsigned int i = 0; i < M; i++) {
			num_q = 0;
			for (unsigned int j = 0; j < N; j++)
				if (_pos[i][j])
					num_q++;
			if (num_q > 1)
				return false;
		}

		// check columns
		for (unsigned int j = 0; j < N; j++) {
			num_q = 0;
			for (unsigned int i = 0; i < M; i++)
				if (_pos[i][j])
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
					if (_pos[i][j])
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
					if (_pos[i][j])
						num_q++;
				}
				if (num_q > 1)
					return false;
			}
		}

		return true;
	}

	/**
	 * Use brute force to find the solution
	 */
	bool brute_force(int q_left) {
		if (q_left == 0) {
			_solutions_tried++;
			if (check_solution()) {
				print();
				return true;
			}
			return false;
		}

		for (unsigned int i = 0; i < M; i++)
			for (unsigned int j = 0; j < N; j++) {
				if (_pos[i][j] == 0) {
					// place a queen
					_pos[i][j] = 1;
					// place another one
					if (brute_force(q_left - 1))
						return true;
					// remove the queen
					_pos[i][j] = 0;
				}
			}

		return false;
	}

	//
	bool pruning(int q_left) {
		if (q_left == 0) {
			_solutions_tried++;
			if (check_solution()) {
				print();
				std::cout << std::endl;
				return true;
			}
			return false;
		}

		// create a mask of impossible positions
		int mask[M][N];
		for (unsigned int i = 0; i < M; i++)
			for (unsigned int j = 0; j < N; j++)
				mask[i][j] = 0;

		for (unsigned int i = 0; i < M; i++) {
			for (unsigned int j = 0; j < N; j++) {
				if (_pos[i][j] == 1) {
					// mask the row
					for (unsigned int k = 0; k < N; k++)
						mask[i][k] = 1;
					// mask the column
					for (unsigned int k = 0; k < M; k++)
						mask[k][j] = 1;

					for (int k = i, l = j; (k >= 0) && (l < N); k--, l++)
						mask[k][l] = 1;

					for (int k = i, l = j; (k < M) && (l < N); k++, l++)
						mask[k][l] = 1;

					for (int k = i, l = j; (k >= 0) && (l >= 0); k--, l--)
						mask[k][l] = 1;

					for (int k = i, l = j; (k < M) && (l >= 0); k++, l--)
						mask[k][l] = 1;
				}
			}
		}

		for (unsigned int i = 0; i < M; i++)
			for (unsigned int j = 0; j < N; j++) {
				if (_pos[i][j] == 0 && mask[i][j] == 0) {
					// place a queen
					_pos[i][j] = 1;
					// place another one
					if (pruning(q_left - 1))
						return true;
					// remove the queen
					_pos[i][j] = 0;
				}
			}

		return false;
	}

protected:
	/// Number of rows
	static const unsigned int M = 8;
	/// number of columns
	static const unsigned int N = 8;

	/// The board itself
	int _pos[M][N];

	/// Number of solurions we tried
	unsigned int _solutions_tried = 0;
};


int main() {
	Board b;

	//b.brute_force(8);
	b.pruning(8);

	return 0;
}

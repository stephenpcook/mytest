/* Program for calculating the n-th fibonacci number with matrices 
 * Stephen Cook, Bath. */

/* Given the matrix
 *   M = [[1,1],[1,0]], 
 * the n-th and (n+1)-th fibonacci numbers are given by
 *   [F(n+1),F(n)]' = (M^n)*[1,0]'.
 * We want to do this by taking the binary representation of n and moving
 * through the digits from right to left, each time finding M^(2^i) and adding
 * to a running product. For example with n=13,
 *   bin(13) = 1101,
 *   M^13 = 1*M^1 * 0*M^2 * 1*M^4 * 1*M^8,
 * each M^(2^i) we can find iteratively with one symmetric matrix
 * multiplication, 
 * M^(2n) = (M^n)^2.
 *
 *  Since all matrices are Symmetric 2-by-2, they shall be stored as
 *  Marray = {M(1,1), M(1,2)(=M(2,1)), M(2,2)};
 *
 *  Not quite good enough to do inline assignments to arrays so the code is
 *  longer than I hoped for. It shold be a lot fewer lines. 
 *  Probably slower than a raw iteration, such as
 *   for (i=1;i<n;i++) {fn1 = fn+fn_old, fn_old=fn, fn=fn1;}
 *  but for large n this should scale like log(n) instead of n.
 */

#include <stdio.h>


long fib(int n){
	/* Initialise */
	long M[] = {1L,1L,0L};		// M is [[1,1],[1,0]]^(2^i)
	long A[3];			// A will be M^n.
	long M2[3];			// Temporary variable for M*M
	long MA[3];			// Temporary variable for M*A

	if (n&1) { 			// If n is odd.
		A[0] = M[0];		// Then A starts off as M.
		A[1] = M[1];
		A[2] = M[2];
	} 
	else {				// So n is even
		A[0] = 1L;		// So start A as the identity matrix
		A[1] = 0L;
		A[2] = 1L;
	}

	/* Main loop iterating through the digits of biary n, right to left. */
	n>>=1; // Already taken care of the "units" above, move onto "tens".
	while (n) {
		// While we haven't got to the end of the binary rep. of n.

		// i++ (not needed)
		// M = M*M = [[1,1],[1,0]]^(2^i)
		//
		// This is supposed to be M = mmult(M,M), but can't figure out
		// how to return arrays from functions.
		M2[0] = M[0]*M[0] + M[1]*M[1];
		M2[1] = M[0]*M[1] + M[1]*M[2]; 
		M2[2] = M[1]*M[1] + M[2]*M[2];
		M[0] = M2[0];
		M[1] = M2[1];
		M[2] = M2[2];
		if (n&1){ // If the current digit of bin(n) is 1 then
			// Again, A = M*A
			MA[0] = A[0]*M[0] + A[1]*M[1];
			MA[1] = A[0]*M[1] + A[1]*M[2];
			MA[2] = A[1]*M[1] + A[2]*M[2];
			A[0] = MA[0];
			A[1] = MA[1];
			A[2] = MA[2];
		}

		n>>=1; 	// Move onto the next digit
	}
	return A[1]; // A[1]=F(n). Also have A[0]=F(n+1), but seems less neat.
}

int main(void){
	int n;		// User input

	printf("Give integer n: ");
	scanf("%d", &n);
	printf("%ld \n", fib(n));
}

/*  Did not work at all, not got to grips with arrays quite yet.
int mmult(int A[3],int B[3]){
	int C[3];

	C[0] = A[0]*B[0] + A[1]*B[1];
	C[1] = A[0]*B[1] + A[1]*B[2]; 	// This could also be A1B0 + A2B1
					// but all our matrices are M or I, so
					// commutativity is free.
	C[2] = A[1]*B[1] + A[2]*B[2];

	return C[];
}
*/

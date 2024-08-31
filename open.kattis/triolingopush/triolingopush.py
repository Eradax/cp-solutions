from copy import deepcopy

def matMul(A, B):
	rowsA = len(A)
	colsA = len(A[0])
	rowsB = len(B)
	colsB = len(B[0])

	result = [[0 for row in range(colsB)] for col in range(rowsA)]
	for i in range(rowsA):
		for j in range(colsB):
			for k in range(colsA):
				result[i][j] += (A[i][k] * B[k][j])%(1000000007)
	return result

def exp(mult, a, n):
	if n == 1:
		return a 
	if n == 2:
		return mult(a, a)
	
	t = deepcopy(a)
	n-=1
	while n>1:
		if n%2 == 1:
			t = mult(a, t)
			n-=1
		a = mult(a, a)
		n>>=1
	return mult(a, t)

def main():
	n = int(input())
	mod = int(1e9)+7

	F = [[0], [1], [1]]
	T = [[0, 1, 0], [1, 1, 1], [0, 0, 1]]
	
	nT = exp(matMul, T, n)

	print(matMul(nT, F)[0][0]%mod)
main()


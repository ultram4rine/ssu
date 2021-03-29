#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <string>
#include <vector>
#include <complex>
#include <windows.h>

using namespace std;

double random(double min, double max) //Function for get random numbers with type double from min to max
{
	return (double)(rand()) / RAND_MAX * (max - min) + min;
}

bool isEqual(double a, double b)
{
	return fabs(a - b) < DBL_EPSILON;
}

int sign(double a)
{
	if (a > 0)
	{
		return 1;
	}
	else if (isEqual(a, 0))
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

class RotrMatr
{
public:
	int i, j;
	double angle;

	RotrMatr(int k, int l, double theta)
	{
		i = k;
		j = l;
		angle = theta;
	}

	RotrMatr Transpose()
	{
		RotrMatr transposedMatrix(i, j, angle);

		transposedMatrix.i = j;
		transposedMatrix.j = i;

		return transposedMatrix;
	}
};

class Matrix
{
public:
	double** matrix;
	int size;
	string id;

	Matrix(int n, string name)
	{
		size = n;
		id = name;
		matrix = new double *[size];
		for (int i = 0; i < size; i++)
		{
			matrix[i] = new double[size];
			for (int j = 0; j < size; j++)
			{
				matrix[i][j] = 0;
			}
		}
	}

	Matrix(int n)
	{
		size = n;
		id = "E";
		matrix = new double *[size];
		for (int i = 0; i < size; i++)
		{
			matrix[i] = new double[size];
			for (int j = 0; j < size; j++)
			{
				matrix[i][j] = 0;
			}
		}

		for (int i = 0; i < size; i++)
		{
			matrix[i][i] = 1;
		}
	}

	Matrix(int n, int k, int l, double c, double s)
	{
		size = n;
		id = "RotationMatr";
		matrix = new double*[size];
		for (int i = 0; i < size; i++)
		{
			matrix[i] = new double[size];
		}

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (i == j)
				{
					matrix[i][j] = 1;
				}
				else
				{
					matrix[i][j] = 0;
				}
			}
		}
		matrix[k][k] = matrix[l][l] = c;
		matrix[k][l] = -s;
		matrix[l][k] = s;
	}

	Matrix(Matrix &toCopy)
	{
		size = toCopy.size;
		id = toCopy.id + "Copy";
		matrix = new double *[size];
		for (int i = 0; i < size; i++)
		{
			matrix[i] = new double[size];
			for (int j = 0; j < size; j++)
			{
				matrix[i][j] = toCopy.matrix[i][j];
			}
		}
	}

	~Matrix()
	{
		for (int i = 0; i < size; i++)
		{
			delete[] matrix[i];
		}
		delete[] matrix;
		//cout << "Matrix with id " << id << " deleted" << '\n' << '\n';
	}

	double FrobeniusNorm()
	{
		double FrobNorm = 0;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				FrobNorm += matrix[i][j] * matrix[i][j];
			}
		}
		return sqrt(FrobNorm);
	}

	void RandomFill(double min, double max)
	{
		srand((unsigned int)time(0));

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				matrix[i][j] = random(min, max);
			}
		}
	}

	double DeterminantForTriangle()
	{
		double determinant = 1;

		for (int i = 0; i < size; i++)
		{
			determinant *= matrix[i][i];
		}

		return determinant;
	}

	Matrix Transpose()
	{
		Matrix transposedMatrix(size, id + "Transposed");

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				transposedMatrix.matrix[i][j] = matrix[j][i];
			}
		}

		return transposedMatrix;
	}

	Matrix MakeSymmetric()
	{
		Matrix SymMatr(*this);

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (i != j)
				{
					SymMatr.matrix[j][i] = SymMatr.matrix[i][j];
				}
			}
		}

		return SymMatr;
	}

	Matrix MakeLowTriangle()
	{
		Matrix LowTriangleMatr(*this);

		for (int j = 0; j < size; j++)
		{
			for (int i = 0; i < j; i++)
			{
				LowTriangleMatr.matrix[i][j] = 0;
			}
		}

		return LowTriangleMatr;
	}

	bool isDiagonal()
	{
		double max = 0;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (i != j)
				{
					if (abs(matrix[i][j]) > max)
						max = matrix[i][j];
				}
			}
		}

		if (isEqual(max, 0))
			return true;
		else
			return false;
	}

	complex<double> detbyCholeskyDecomposition()
	{
		complex<double>** lowerTriangleMatrix = new complex<double>* [size];
		for (int i = 0; i < size; i++)
		{
			lowerTriangleMatrix[i] = new complex<double>[size];
		}

		//Lower triangle matrix elements counting and filling
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < i + 1; j++)
			{
				complex<double> sum = 0;
				lowerTriangleMatrix[i][j] = 0;
				if (j == i)
				{
					for (int k = 0; k < j; k++)
					{
						sum += (lowerTriangleMatrix[j][k] * lowerTriangleMatrix[j][k]);
					}
					lowerTriangleMatrix[j][j] = sqrt(matrix[j][j] - sum);
				}
				else
				{
					for (int k = 0; k < j; k++)
					{
						sum += (lowerTriangleMatrix[i][k] * lowerTriangleMatrix[j][k]);
					}
					lowerTriangleMatrix[i][j] = (matrix[i][j] - sum) / lowerTriangleMatrix[j][j];
				}
			}
		}

		complex<double> determinant = 1.0;
		for (int i = 0; i < size; i++)
		{
			determinant *= lowerTriangleMatrix[i][i];
		}

		for (int i = 0; i < size; i++)
			delete[] lowerTriangleMatrix[i];
		delete[] lowerTriangleMatrix;

		return determinant * determinant;
	}

	std::vector<double> JacobiRotation();

	bool operator == (Matrix toCompare)
	{
		if (size != toCompare.size) return false;
		else
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					if (!isEqual(matrix[i][j], toCompare.matrix[i][j])) return false;
				}
			}
			return true;
		}
	}

	bool operator != (Matrix toCompare)
	{
		if (size != toCompare.size) return true;
		else return !(*this == toCompare);
	}

	Matrix &operator = (const Matrix &toAssign)
	{
		if (this == &toAssign)
		{
			cout << "Self assignment" << '\n';
			return *this;
		}

		if (size != toAssign.size)
		{
			cout << "For assignment matrices sizes must be equal" << '\n'
				<< "Your sizes is: " << size << " and " << toAssign.size << '\n' << '\n';
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				delete[] matrix[i];
			}
			delete[] matrix;

			id = toAssign.id;
			size = toAssign.size;

			matrix = new double*[size];
			for (int i = 0; i < size; i++)
			{
				matrix[i] = new double[size];
				for (int j = 0; j < size; j++)
				{
					matrix[i][j] = toAssign.matrix[i][j];
				}
			}

			return *this;
		}
	}

	Matrix operator + (Matrix toAdd)
	{
		if (size != toAdd.size)
		{
			cout << "For adding matrices sizes must be equal" << '\n'
				<< "Your sizes is: " << size << " and " << toAdd.size << '\n' << '\n';
		}
		else
		{
			Matrix resultofAddition(size, "AdditionRes");

			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					resultofAddition.matrix[i][j] = matrix[i][j] + toAdd.matrix[i][j];
				}
			}

			return resultofAddition;
		}
	}

	Matrix operator - (Matrix toSubtract)
	{
		if (size != toSubtract.size)
		{
			cout << "For subtracking matrices sizes must be equal" << '\n'
				<< "Your sizes is: " << size << " and " << toSubtract.size << '\n' << '\n';
		}
		else
		{
			Matrix resultofSubtraction(size, "SubtractionRes");

			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					resultofSubtraction.matrix[i][j] = matrix[i][j] - toSubtract.matrix[i][j];
				}
			}

			return resultofSubtraction;
		}
	}

	Matrix operator * (double c)
	{
		Matrix resultofMultiplication(*this);

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				resultofMultiplication.matrix[i][j] *= c;
			}
		}

		return resultofMultiplication;
	}

	Matrix operator * (Matrix toMult)
	{
		if (size != toMult.size)
		{
			cout << "For multiplying matrices sizes must be equal" << '\n'
				<< "Your sizes is: " << size << " and " << toMult.size << '\n' << '\n';
		}
		else
		{
			Matrix resultofMultiplication(size, "MultiplicationRes");

			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					resultofMultiplication.matrix[i][j] = 0;
					for (int k = 0; k < size; k++)
					{
						resultofMultiplication.matrix[i][j] += matrix[i][k] * toMult.matrix[k][j];
					}
				}
			}

			return resultofMultiplication;
		}
	}
};

Matrix operator * (Matrix M, RotrMatr R)
{
	Matrix resultofMultiplication(M);

	for (int k = 0; k < M.size; k++)
	{
		resultofMultiplication.matrix[k][R.i] = 0;
		resultofMultiplication.matrix[k][R.j] = 0;
		resultofMultiplication.matrix[k][R.i] += M.matrix[k][R.i] * cos(R.angle) + M.matrix[k][R.j] * sin(R.angle);
		resultofMultiplication.matrix[k][R.j] += M.matrix[k][R.i] * (-sin(R.angle)) + M.matrix[k][R.j] * cos(R.angle);
	}

	return resultofMultiplication;
}

Matrix operator * (RotrMatr R, Matrix M)
{
	Matrix resultofMultiplication(M);

	for (int k = 0; k < M.size; k++)
	{
		resultofMultiplication.matrix[R.i][k] = 0;
		resultofMultiplication.matrix[R.j][k] = 0;
		resultofMultiplication.matrix[R.i][k] += cos(R.angle) * M.matrix[R.i][k] + (-sin(R.angle)) * M.matrix[R.j][k];
		resultofMultiplication.matrix[R.j][k] += sin(R.angle) * M.matrix[R.i][k] + cos(R.angle) * M.matrix[R.j][k];
	}

	return resultofMultiplication;
}

std::vector<double> Matrix::JacobiRotation()
{
	SYSTEMTIME st1, st2;
	Matrix A(*this);
	int h = 0, ri = 0, rj = 0;
	while (!A.isDiagonal())
	{
		double theta, tau, t, c, s, max = 0;
		const double pi = atan(1) * 4;

		//cout << "Frobenius Norm on " << h << " iteration: " << A.FrobeniusNorm() << '\n';
		GetLocalTime(&st1);
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (abs(A.matrix[i][j]) > max)
				{
					max = abs(A.matrix[i][j]);
					ri = i;
					rj = j;
				}
			}
		}
		if (isEqual(A.matrix[ri][ri], A.matrix[rj][rj]))
		{
			theta = pi / 4;
			RotrMatr R(ri, rj, theta);
			A = R.Transpose() * A;
			A = A * R;
		}
		else
		{
			//tau = (A.matrix[ri][ri] - A.matrix[rj][rj]) / (2 * A.matrix[ri][rj]);
			//t = sign(tau) / (abs(tau) + sqrt(1 + tau * tau));
			//c = 1 / sqrt(1 + t * t);
			//s = t * c;
			double tg2 = (2 * A.matrix[ri][rj]) / (A.matrix[ri][ri] - A.matrix[rj][rj]);
			theta = atan(tg2) / 2;
			//cout << "acos(c): " << acos(c) << " theta: " << theta << '\n';
			RotrMatr R(ri, rj, theta);
			A = R.Transpose() * A;
			A = A * R;
		}
		GetLocalTime(&st2);
		double T1 = (double)(st1.wMinute * 60 * 1000 + st1.wSecond * 1000 + st1.wMilliseconds);
		double T2 = (double)(st2.wMinute * 60 * 1000 + st2.wSecond * 1000 + st2.wMilliseconds);
		cout << "Time to rotate matrix on " << h << " iteration: " << T2 - T1 << " milliseconds" << '\n';

		h++;
	}

	std::vector<double> eigenvalues(size);
	for (int i = 0; i < size; i++)
		eigenvalues[i] = A.matrix[i][i];

	cout << "Count of iterations: " << h << '\n' << '\n';
	return eigenvalues;
}

int main()
{
	srand(time(NULL));
	SYSTEMTIME st1, st2;
	int n;
	string goon = "y";
	cout.precision(15);

	while (goon == "y")
	{
		cout << "Size of matrix: ";
		cin >> n;
		cout << '\n';

		Matrix A(n, "A");
		srand(time(NULL));
		cout << "Our Matrix A" << '\n' << '\n';
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				A.matrix[i][j] = rand() % 5 + 1;
			}
		}
		A.RandomFill(1.9, 2.1);
		A = A.MakeSymmetric();

		Matrix JacRot(A);
		std::vector<double> EigenValues(A.size);
		int h = 0;
		
		GetLocalTime(&st1);
		EigenValues = JacRot.JacobiRotation();
		GetLocalTime(&st2);

		cout << "Eigenvalues of Matrix A" << '\n' << '\n';
		for (int i = 0; i < n; i++)
		{
			if (sign(EigenValues[i] < 0))
			{
				cout << EigenValues[i] << '\n';
			}
			else
			{
				cout << " " << EigenValues[i] << '\n';
			}
		}
		cout << '\n';

		double T1 = (double)(st1.wMinute * 60 * 1000 + st1.wSecond * 1000 + st1.wMilliseconds);
		double T2 = (double)(st2.wMinute * 60 * 1000 + st2.wSecond * 1000 + st2.wMilliseconds);
		cout << "Time to found Eigenvalues by Jacobi Rotation method: " << T2 - T1 << " milliseconds" << '\n';

		double mineigenvalue = DBL_MAX;
		for (int i = 0; i < n; i++)
		{
			if (EigenValues[i] < mineigenvalue)
			{
				mineigenvalue = EigenValues[i];
			}
		}

		Matrix E(n);
		E = E * mineigenvalue;

		Matrix Check(n, "check");
		Check = A - E;

		GetLocalTime(&st1);
		cout << "Determinant of A - (v * E): " << Check.detbyCholeskyDecomposition() << '\n';
		GetLocalTime(&st2);

		T1 = (double)(st1.wMinute * 60 * 1000 + st1.wSecond * 1000 + st1.wMilliseconds);
		T2 = (double)(st2.wMinute * 60 * 1000 + st2.wSecond * 1000 + st2.wMilliseconds);
		cout << "Time to count Determinant by Cholesky Decomposition Method: " << T2 - T1 << " milliseconds" << '\n';
		
		cout << '\n' << "Continue(y/n)?: ";
		cin >> goon;
	}

	return 0;
}
#include <iostream>
#include <string>

using namespace std;

class vect
{
	int dim;    //�����������
	double* v;  //����������

public:
	int num;           //����� �������
	static int count;  //���������� ��������

	vect();
	vect(vect& x);
	vect(int n);
	vect(int n, double* x);
	~vect();
	void print();
	vect& operator + (vect& right);
	friend vect operator - (vect e, vect r);
	vect operator = (const vect& r);
	vect operator - ();
	double operator * (vect& r);
	friend vect operator * (double k, vect& r);

	friend class matr;
};

int vect::count = 0;

vect::vect()
{
	dim = 0;
	v = new double[dim];
	num = ++count;

	cout << "�������� �����������" << endl;
}

vect::vect(int n)
{
	dim = n;
	v = new double[n];
	for (int i = 0; i < n; i++)
	{
		v[i] = 0;
	}
	num = ++count;

	cout << "�������� �����������" << endl;
}

vect::vect(int n, double* x)
{
	dim = n;
	v = new double[n];
	for (int i = 0; i < n; i++)
	{
		v[i] = x[i];
	}
	num = ++count;

	cout << "�������� �����������" << endl;
}

vect::vect(vect& x)
{
	dim = x.dim;
	v = new double[dim];
	for (int i = 0; i < dim; i++)
	{
		v[i] = x.v[i];
	}
	num = ++count;

	cout << "�������� ����������� �����������" << endl;
}

vect::~vect()
{
	delete[] v;

	cout << "�������� ����������" << endl;
}

void vect::print()
{
	cout << "������: ";
	for (int i = 0; i < dim; i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
}

vect& vect::operator + (vect& r)
{
	if (dim != r.dim)
	{
		cout << "����������� �������� �� ���������. �������� ����������." << endl;
		return *this;
	}

	vect* result = new vect(dim);
	for (int i = 0; i < dim; i++)
	{
		result->v[i] = v[i] + r.v[i];
	}
	cout << "��������� �������� ��������" << endl;

	return *result;
}

vect operator - (vect e, vect r)
{
	if (e.dim != r.dim)
	{
		cout << "����������� �������� �� ���������. �������� ����������." << endl;
		return 0;
	}

	vect result(e.dim);
	for (int i = 0; i < e.dim; i++)
	{
		result.v[i] = e.v[i] - r.v[i];
	}
	cout << "��������� ��������� ��������" << endl;

	return result;
}

vect vect::operator - ()
{
	vect result(dim);
	for (int i = 0; i < dim; i++)
	{
		result.v[i] = -v[i];
	}
	cout << "��������� �������� � ������� �������" << endl;

	return result;
}

vect vect::operator = (const vect& r)
{
	if (this == &r)
	{
		return *this;
	}

	delete[] v;
	dim = r.dim;
	v = new double[dim];
	for (int i = 0; i < dim; i++)
	{
		v[i] = r.v[i];
	}
	cout << "��������� ������������" << endl;

	return *this;
}

double vect::operator * (vect& r)
{
	if (dim != r.dim)
	{
		cout << "����������� �������� �� ���������. �������� ����������." << endl;
		return 0;
	}

	double result = 0.0;
	for (int i = 0; i < dim; i++)
	{
		result += v[i] * r.v[i];
	}
	cout << "��������� ��������� ������������ ��������" << endl;

	return result;
}

vect operator * (double k, vect& r)
{
	for (int i = 0; i < r.dim; i++)
	{
		r.v[i] = k * r.v[i];
	}
	cout << "��������� ��������� ������� �� �����" << endl;

	return r;
}


class matr
{
	int dim;   //�����������
	double* a;  //����������

public:
	matr()
	{
		dim = 0;
		a = NULL;
	}

	matr(int n)
	{
		dim = n;
		a = new double[n * n];
		for (int i = 0; i < n * n; i++)
		{
			a[i] = 0;
		}
	}

	matr(int n, double* x)
	{
		dim = n;
		a = new double[n * n];
		for (int i = 0; i < n * n; i++)
		{
			a[i] = x[i];
		}
	}

	matr(matr& x)
	{
		dim = x.dim;
		a = new double[dim * dim];
		for (int i = 0; i < dim * dim; i++)
		{
			a[i] = x.a[i];
		}
	}

	~matr()
	{
		delete[] a;
	}

	void print()
	{
		for (int i = 0; i < dim; i++)
		{
			for (int j = 0; j < dim; j++)
			{
				cout << a[i * dim + j] << " ";
			}
			cout << endl;
		}
	}

	matr operator + (matr& r)
	{
		if (dim != r.dim)
		{
			cout << "����������� ������ �� ���������. �������� ����������." << endl;
			return 0;
		}

		matr result(r.dim);
		for (int i = 0; i < dim * dim; i++)
		{
			result.a[i] = a[i] + r.a[i];
		}

		return result;
	}

	matr operator - (matr& r)
	{
		if (dim != r.dim)
		{
			cout << "����������� ������ �� ���������. �������� ����������." << endl;
			return 0;
		}

		matr result(r.dim);
		for (int i = 0; i < dim * dim; i++)
		{
			result.a[i] = a[i] - r.a[i];
		}

		return result;
	}

	matr operator - ()
	{
		matr result(dim);
		for (int i = 0; i < dim * dim; i++)
		{
			result.a[i] = -a[i];
		}

		return result;
	}

	matr operator = (const matr& r)
	{
		if (this == &r)
		{
			return *this;
		}

		delete[] a;
		dim = r.dim;
		a = new double[dim * dim];
		for (int i = 0; i < dim * dim; i++)
		{
			a[i] = r.a[i];
		}
		cout << "��������� ������������" << endl;

		return *this;
	}

	matr operator * (matr& r)
	{
		if (dim != r.dim)
		{
			cout << "����������� ������ �� ���������. �������� ����������." << endl;
			return 0;
		}

		matr result(r.dim);
		for (int i = 0; i < dim; i++)
		{
			for (int j = 0; j < dim; j++)
			{
				double sum = 0.0;
				for (int k = 0; k < dim; k++)
				{
					sum += a[i * dim + k] * r.a[k * dim + j];
				}
				result.a[i * dim + j] = sum;
			}
		}

		return result;
	}

	friend matr operator * (double k, matr& r)
	{
		matr result(r.dim);
		for (int i = 0; i < r.dim * r.dim; i++)
		{
			result.a[i] = k * r.a[i];
		}

		return result;
	}

	vect operator * (vect& r)
	{
		vect result(dim);
		for (int i = 0; i < dim; ++i)
		{
			double sum = 0.0;
			for (int j = 0; j < dim; ++j)
			{
				sum += a[i * dim + j] * r.v[j];
			}

			result.v[i] = sum;
		}

		return result;
	}
};

int main()
{
	setlocale(LC_ALL, "RU");

	double scalar;

	// �������� ��������
	double arr1[] = { 1, 2, 3 };
	double arr2[] = { 4, 5, 6 };
	vect v1(3, arr1);
	vect v2(3, arr2);
	vect v6, v7, v8, v9, v10, v11;

	// ������������ ���������� ������������� ������ vect
	vect v3();
	vect v4(v1);
	vect v5(10);

	// ���������� �������� � ���������
	cout << endl;
	v6 = v1 + v2;
	cout << "����� ���� ��������: ";
	v6.print();
	cout << endl;

	v7 = v2 - v1;
	cout << "�������� ���� ��������: ";
	v7.print();
	cout << endl;

	v8 = -v1;
	cout << "��������� �������� ������: ";
	v8.print();
	cout << endl;

	scalar = v1 * v2;
	cout << "��������� ����������� ���� ��������: " << scalar << endl;;
	cout << endl;

	v10 = 5 * v2;
	cout << "������������ ����� �� ������: ";
	v10.print();
	cout << endl;

	// �������� ������
	double matArr1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	double matArr2[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	matr m1(3, matArr1);
	matr m2(3, matArr2);
	matr m6, m7, m8, m9, m10;

	// ������������ ���������� ������������� ������ matr
	matr m3();
	matr m4(m1);
	matr m5(10);

	// ���������� �������� � ���������
	m6 = m1 + m2;
	cout << "����� ���� ������: " << endl;
	m6.print();
	cout << endl;

	m7 = m1 - m2;
	cout << "�������� ���� ������: " << endl;
	m7.print();
	cout << endl;

	m8 = -m1;
	cout << "��������� �������� ������: " << endl;
	m8.print();
	cout << endl;

	m9 = m1 * m2;
	cout << "������������ ���� ������: " << endl;
	m9.print();
	cout << endl;

	m10 = 5 * m2;
	cout << "������������ ����� �� �������: " << endl;
	m10.print();
	cout << endl;

	// ������������ ������� �� ������
	v11 = m1 * v1;
	cout << "������������ ������� �� ������: " << endl;
	v11.print();
	cout << endl;

	return 0;
};
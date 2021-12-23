#ifndef MATRIX_H_
#define MATRIX_H_

#include<iostream>
#include<math.h>
using namespace std;
class matrix
{
	private:
	int m,n;
	public:
	double array[100][100] = {0};
	matrix(int x, int y)
	{
		m=x;n=y;
	}
	
	void matrix_in()
	{
		for (int i = 0; i < m; i++)
    	{
        	for (int j = 0; j < n; j++)
        	{
            	cin >> array[i][j];
        	}
    	}
	}
	
	int row()
	{
		return m;
	}
	int column()
	{
		return n;
	}
	
	void matrix_out()
	{
		for (int i = 0; i < m; i++)
    	{
        	for (int j = 0; j < n; j++)
        	{
            	cout << array[i][j] << "  ";
        	}
        	cout << endl;
    	}
    	cout << endl;
	}
	
	void print_dimension()
	{
		cout <<"["<<to_string(m)<<","<<to_string(n)<<"]"<<endl;
	}
	
	matrix multiply(matrix brray)
	{
		matrix crray(m,brray.n);
		
		for(int i=0;i<m;i++)
		{
  			for(int j=0;j<brray.n;j++)
			{
  				crray.array[i][j]=0;
  				for(int k=0;k<n;k++)
  				crray.array[i][j]=crray.array[i][j]+(array[i][k]*brray.array[k][j]);
			}
  		}
  		return crray;
	}
	
	matrix upper_traingle()
	{
		matrix urray = *this;
		double t;
		for(int k = 0;k<m;k++)
		{
			for(int i = k+1;i<m;i++)
			{
				t = urray.array[i][k]/urray.array[k][k];
				for(int j = 0; j<n; j++)
				{
					urray.array[i][j] = urray.array[i][j] - t * urray.array[k][j];
				}
			}
		}
		return urray;
	}
	
	double determinant()
	{
		matrix trray = this->upper_traingle();
		double det = 1;
		for(int i =0; i < m;i++)
		{
			det = det * trray.array[i][i];
		}
		return det;
	}
	
	matrix transpose()
	{
		matrix trans(n,m);
		for(int i = 0;i<m;i++)
		{
			for(int j = 0;j<n;j++)
			{
				trans.array[j][i] = this->array[i][j];
			}
		}
		return trans;
	}
	
	matrix truncate(int rs,int cs,int re = -1,int ce = -1)
	{
		if(re == -1)
			re = rs;
		if(ce == -1)
			ce = cs;
		int m1 = re-rs+1;
		int n1 = ce-cs+1;
		matrix t(m1,n1);
		for(int i = 0;i < m1;i++)
		{
			for(int j = 0;j<n1;j++)
			{
				t.array[i][j] = this->array[rs-1+i][cs-1+j];
			}
		}
		return t;
	}
	
	matrix diagonal()
	{
		matrix d = this->upper_traingle();
		d = d.transpose();
		d = d.upper_traingle();
		return d;
	}
	
	matrix minor(int a, int b)
	{
		a--; b--;
		matrix c(m-1,n-1);
		for(int i=0; i<m; i++)
		{
			for(int j=0; j<n; j++)
			{
				if((i<a)&&(j<b))
				{
					c.array[i][j] = this->array[i][j];
				}
				if((i>=a)&&(j<b))
				{
					c.array[i][j] = this->array[i+1][j];
				}
				if((i<a)&&(j>=b))
				{
					c.array[i][j] = this->array[i][j+1];
				}
				if((i>=a)&&(j>=b))
				{
					c.array[i][j] = this->array[i+1][j+1];
				}
			}
		}
		return c;
	}
	
	matrix cofactor()
	{
		matrix c(m,n);
		for(int i=0; i< m; i++)
		for(int j=0; j< n; j++)
		{
			c.array[i][j] = (pow(-1,i+j))*this->minor(i+1,j+1).determinant();
		}
		return c;
	}
	
	matrix adjoint()
	{
		return this->cofactor().transpose();
	}
	
	matrix inverse()
	{
		if(this->determinant()!=0)
		{
			double d = this->determinant();
			matrix inv(m,n);
			matrix adj = this->adjoint();
			for(int i=0; i<m; i++)
			for(int j=0; j<n; j++)
			{
				inv.array[i][j] = (1/d)*adj.array[i][j];
			}
			return inv;
		}
		else
		{
			cout << "Inverse does not exist" << endl;
			matrix x(m,n);
			return x;
		}
	}
};

#endif
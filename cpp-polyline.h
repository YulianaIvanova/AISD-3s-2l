#pragma once
#include <iostream>
#include <exception>
#include <math.h>
#include <complex>
#include <string>

using namespace std;
namespace cpp
{
	struct int_point2
	{
		int _x;
		int _y;

		bool operator==(const int_point2& p_i) const
		{
			if ((_x == p_i._x) && (_y == p_i._y)) return true;
			else return false;
		}

		float distance(const int_point2& p_i) const
		{
			return static_cast<float>(sqrt(pow(_x - p_i._x, 2) + pow(_y - p_i._y, 2)));
		}
	};


	ostream& operator<<(ostream& out, const int_point2& p_i)//vertex output
	{
		out << "X: " << p_i._x << '\n';
		out << "Y: " << p_i._y << '\n';
		out << '\n';
		return out;
	}

	istream& operator>>(istream& in, int_point2& p_i)//entering a vertex
	{
		char data[32] = { 0 };
		char* pointer = data;
		in.getline(pointer, 32);
		pointer = pointer + 1;
		char* tmp = strchr(pointer, ';');
		size_t len_data = (tmp - pointer) / sizeof(char);
		char data_x[32] = { 0 };
		for (size_t j = 0; j < len_data; j++)
		{
			data_x[j] = pointer[j];
		}
		p_i._x = atoi(data_x);

		pointer = tmp + 1;

		tmp = strchr(pointer, ')');
		len_data = (tmp - pointer) / sizeof(char);
		char data_y[32] = { 0 };
		for (size_t j = 0; j < len_data; j++)
		{
			data_y[j] = pointer[j];
		}
		p_i._y = atoi(data_y);
		return in;
	}


	struct double_point3
	{
		double _x;
		double _y;
		double _z;

		bool operator==(const double_point3& p_i) const
		{
			if ((_x == p_i._x) && (_y == p_i._y) && (_z == p_i._z)) return true;
			else return false;
		}

		float distance(const double_point3& p_i) const
		{
			return sqrt(pow(_x - p_i._x, 2) + pow(_y - p_i._y, 2) + pow(_z - p_i._z, 2));
		}
	};

	ostream& operator<<(ostream& out, const double_point3& p_i)//vertex output
	{
		out << "X: " << p_i._x << '\n';
		out << "Y: " << p_i._y << '\n';
		out << "Z: " << p_i._z << '\n';
		out << '\n';
		return out;
	}

	istream& operator>>(istream& in, double_point3& p_i)//entering a vertex
	{
		char data[64] = { 0 };
		char* pointer = data;
		in.getline(pointer, 64);
		pointer = pointer + 1;
		char* tmp = strchr(pointer, ';');
		size_t len_data = (tmp - pointer) / sizeof(char);
		char data_x[32] = { 0 };
		for (size_t i = 0; i < len_data; i++)
		{
			data_x[i] = pointer[i];
		}
		p_i._x = atof(data_x);

		pointer = tmp + 1;

		tmp = strchr(pointer, ';');
		len_data = (tmp - pointer) / sizeof(char);
		char data_y[32] = { 0 };
		for (size_t j = 0; j < len_data; j++)
		{
			data_y[j] = pointer[j];
		}
		p_i._y = atof(data_y);

		pointer = tmp + 1;

		tmp = strchr(pointer, ')');
		len_data = (tmp - pointer) / sizeof(char);
		char data_z[32] = { 0 };
		for (size_t k = 0; k < len_data; k++)
		{
			data_z[k] = pointer[k];
		}
		p_i._y = atof(data_y);
		return in;
	}

	istream& operator>>(istream& in, std::complex<double>& p_i)
	{
		double _re = 0;
		double _im = 0;
		char data[32] = { 0 };
		char* pointer = data;
		in.getline(pointer, 32);
		pointer = pointer + 1;
		char* tmp = strchr(pointer, ';');
		size_t len_data = (tmp - pointer) / sizeof(char);
		char data_real[32] = { 0 };
		for (size_t j = 0; j < len_data; j++)
		{
			data_real[j] = pointer[j];
		}
		_re = stod(data_real);
		pointer = tmp + 1;

		tmp = strchr(pointer, ')');
		len_data = (tmp - pointer) / sizeof(char);
		char data_image[32] = { 0 };
		for (size_t j = 0; j < len_data; j++)
		{
			data_image[j] = pointer[j];
		}
		_im = stod(data_image);

		std::complex<double> temp(_re, _im);
		p_i = temp;
		return in;
	}

	ostream& operator<<(ostream& out, const complex<double>& p_i)//vertex output
	{
		out << "Real: " << p_i.real() << '\n';
		out << "Image: " << p_i.imag() << '\n';
		out << '\n';
		return out;
	}

	template <class T>
	class polyline
	{
	private:
		T* _vertices;
		size_t _n; //number of vertices
	public:
		polyline();//default constructor
		polyline(size_t n);//with the parameter
		polyline(const polyline& rhs);//copy
		void swap(polyline&);
		size_t get_n() const;
		~polyline();
		T& operator[](const int index);
		T operator[](const int index) const;
		polyline& operator=(const polyline& rhs);
		polyline operator+(const polyline& s);
		bool operator==(polyline& rhs) const;
		bool operator != (const polyline<T>& p) const;
		polyline& operator<(T t);//adding a vertex to the beginning of a polyline
		polyline& operator>(T t);//adding a vertex to the end of a polyline
		auto get_distance() const;
	};


	template <class T>
	ostream& operator<<(ostream& out, const polyline<T>& p);
	template <class T>
	istream& operator>>(istream& in, polyline<T>& p);


	template <class T>
	polyline<T>::polyline() : _n(0), _vertices(NULL) {};

	template <class T>
	polyline<T>::polyline(size_t n) :_n(n)
	{
		_vertices = new  T[_n];
	}

	template <class T>
	void polyline<T>::swap(polyline<T>& rhs)
	{
		std::swap(_n, rhs._n);
		std::swap(_vertices, rhs._vertices);
	}

	template <class T>
	polyline<T>::polyline(const polyline<T>& rhs) : _n(rhs._n)
	{
		_vertices = new  T[_n];
		for (size_t i = 0; i < _n; i++)
		{
			_vertices[i] = rhs._vertices[i];
		}
	}

	template <class T>
	size_t polyline<T>::get_n() const
	{
		return _n;
	}

	template <class T>
	polyline<T>::~polyline()
	{
		delete[] _vertices;
	}

	template <class T>
	T& polyline<T>::operator[](int index)
	{
		if (index > _n || index < 0)
			throw logic_error("out_of_bounds");
		else
			return _vertices[index];
	}

	template <class T>
	T polyline<T>::operator[](int index) const
	{
		if (index > _n || index < 0)
			throw logic_error("out_of_bounds");
		else
			return _vertices[index];
	}

	template <class T>
	polyline<T>& polyline<T>::operator=(const polyline<T>& rhs)
	{
		polyline copy(rhs);
		swap(copy);
		return *this;
	}

	template <class T>
	polyline<T> polyline<T>::operator + (const polyline<T>& s)
	{
		polyline res(_n + s._n);
		for (size_t i = 0; i < _n; i++)
		{
			res._vertices[i] = _vertices[i];
		}
		for (size_t i = 0; i < s._n; i++)
		{
			res._vertices[_n + i] = s._vertices[i];
		}
		return res;
	}


	template <class T>
	bool polyline<T>::operator==(polyline<T>& rhs) const
	{
		if (_n != rhs._n) return false;
		for (size_t i = 0; i < _n; i++)
		{
			if (!(_vertices[i] == rhs._vertices[i])) return false;
		}
		return true;
	}

	template <class T>
	bool polyline<T>::operator != (const polyline<T>& p) const
	{
		if (_n != p.get_n) return true;
		for (size_t i = 0; i < _n; i++)
		{
			if (!(_vertices[i] == p._vertices[i])) return true;
		}
		return false;
	}

	//adding to the beginning
	template <class T>
	polyline<T>& polyline<T>::operator<(T t)
	{
		T* tmp = new T[_n + 1];
		tmp[0] = t;

		for (size_t i = 0; i < _n; i++)
		{
			tmp[i + 1] = _vertices[i];
		}
		delete[] _vertices;
		_vertices = tmp;
		_n++;
		return *this;
	}

	template <class T>
	//adding to the end
	polyline<T>& polyline<T>::operator>(T t)
	{
		T* tmp = new T[_n + 1];
		tmp[_n] = t;
		for (size_t i = 0; i < _n; i++)
		{
			tmp[i] = _vertices[i];
		}
		delete[] _vertices;
		_vertices = tmp;
		_n++;
		return *this;
	}

	template <class T>
	auto polyline<T>::get_distance() const
	{
		auto len = _vertices[0].distance(_vertices[1]);
		for (size_t i = 1; i < _n - 1; i++)
		{
			len += _vertices[i].distance(_vertices[i + 1]);
		}
		return len;
	}

	auto polyline<complex<double>>::get_distance() const
	{
		double len = 0;
		for (size_t i = 0; i < _n - 1; i++)
		{
			len += abs(_vertices[i + 1] - _vertices[i]);
		}
		return len;
	}

	template <class T>
	istream& operator>>(istream& in, polyline<T>& p)//entering a polyline
	{
		int n;
		in >> n;
		in.get();
		polyline<T> _p(n);
		for (size_t i = 0; i < n; i++)
		{
			T v;
			in >> v;
			_p[i] = v;
		}
		p = _p;
		return in;
	}

	template <class T>
	ostream& operator<<(ostream& out, const polyline<T>& p)//polyline output
	{
		for (size_t i = 0; i < p.get_n(); i++)
		{
			out << p[i];
		}
		out << '\n';
		return out;
	}
}
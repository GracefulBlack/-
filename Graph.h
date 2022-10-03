#pragma once
#include<iostream>
#include<cstdio>
#include<vector>
#include<map>

using namespace std;

template<class V,class W ,W MAX_W = INT_MAX,bool Direction = false> // vertex,edge,�Ƿ����򣬶���Ȩֵ
class Graph {
public:
	Graph() = default;
	Graph(const V* vertexs ,size_t n) //���붥��͸���
	{
		_vertexs.reserve(n);//���ռ�
		for (int i = 0; i < n; ++i)
		{
			_vertexs.push_back(vertexs[i]);
			_vIndexMap[vertexs[i]] = i;//����������±�
		}

		_matrix.resize(n);//�ȿ�n�пռ�
		for (auto& e : _matrix)
		{
			e.resize(n, MAX_W);
		}
	}

	size_t GetVertexIndex(const V& v)
	{
		auto ret = _vIndexMap.find(v);
		if (ret != _vIndexMap.end())
		{
			//�ҵ���
			return ret->second;
		}
		else
		{
			throw invalid_argument("�����ڵĶ���");
			return -1;
		}
	}

	void AddEdge(const V& sec, const V& des,const W& w)
	{
		size_t sec_index = GetVertexIndex(sec);
		size_t des_index = GetVertexIndex(des);

		_matrix[sec_index][des_index] = w;
		//���������ͼ�����ڶԽ��߶��������ͬ��Ȩֵ
		if (Direction == false)
		{
			_matrix[des_index][sec_index] = w;
		}
	}

	void Print()
	{
		for (int i = 0; i < _vertexs.size(); i++)
		{
			cout << _vertexs[i] << "-" << i << endl;
		}
		cout << endl;

		cout << " ";
		for (size_t i = 0; i < _vertexs.size(); ++i)
		{
			cout << i << " ";
		}
		cout << endl;

		// ��ӡ����
		for (size_t i = 0; i < _matrix.size(); ++i)
		{
			cout << i << " ";
			for (size_t j = 0; j < _matrix[i].size(); ++j)
			{
				if (_matrix[i][j] != MAX_W)
					cout << _matrix[i][j] << " ";
				else
					cout << "*" << " ";
			}
			cout << endl;
		}
		cout << endl << endl;

		// ��ӡ���еı�
		for (size_t i = 0; i < _matrix.size(); ++i)
		{
			for (size_t j = 0; j < _matrix[i].size(); ++j)
			{
				if (i < j && _matrix[i][j] != MAX_W)
				{
					cout << _vertexs[i] << "-" << _vertexs[j] << ":" <<
						_matrix[i][j] << endl;
				}
			}
		}
	
	}

private:
	map<V, size_t> _vIndexMap;//����ĳ��������ڵ��±�
	vector<V> _vertexs;//һάvector�洢����
	vector<vector<W>> _matrix;//��άvector�洢�ڽӾ���Ȩֵ
};

void TestGraph()
{
	Graph<char, int, INT_MAX, true> g("0123", 4);
	g.AddEdge('0', '1', 1);
	g.AddEdge('0', '3', 4);
	g.AddEdge('1', '3', 2);
	g.AddEdge('1', '2', 9);
	g.AddEdge('2', '3', 8);
	g.AddEdge('2', '1', 5);
	g.AddEdge('2', '0', 3);
	g.AddEdge('3', '2', 6);
	g.Print();
}
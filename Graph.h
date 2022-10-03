#pragma once
#include<iostream>
#include<cstdio>
#include<vector>
#include<map>

using namespace std;

template<class V,class W ,W MAX_W = INT_MAX,bool Direction = false> // vertex,edge,是否有向，定义权值
class Graph {
public:
	Graph() = default;
	Graph(const V* vertexs ,size_t n) //传入顶点和个数
	{
		_vertexs.reserve(n);//开空间
		for (int i = 0; i < n; ++i)
		{
			_vertexs.push_back(vertexs[i]);
			_vIndexMap[vertexs[i]] = i;//给定点给与下标
		}

		_matrix.resize(n);//先开n行空间
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
			//找到了
			return ret->second;
		}
		else
		{
			throw invalid_argument("不存在的顶点");
			return -1;
		}
	}

	void AddEdge(const V& sec, const V& des,const W& w)
	{
		size_t sec_index = GetVertexIndex(sec);
		size_t des_index = GetVertexIndex(des);

		_matrix[sec_index][des_index] = w;
		//如果是无向图，就在对角线对面添加相同的权值
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

		// 打印矩阵
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

		// 打印所有的边
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
	map<V, size_t> _vIndexMap;//查找某个顶点对于的下标
	vector<V> _vertexs;//一维vector存储顶点
	vector<vector<W>> _matrix;//二维vector存储邻接矩阵权值
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
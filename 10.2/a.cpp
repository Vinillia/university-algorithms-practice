#include <iostream>
#include <vector>

class UnionFind
{
public:
    explicit UnionFind(int n) : parent(n), rank(n, 0)
    {
        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (x != parent[x])
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY)
        {
            if (rank[rootX] > rank[rootY])
            {
                parent[rootY] = rootX;
            }
            else if (rank[rootX] < rank[rootY])
            {
                parent[rootX] = rootY;
            }
            else
            {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

private:
    std::vector<int> parent;
    std::vector<int> rank;
};

int main()
{
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> adjacency_matrix1(n, std::vector<int>(n, 0));
    std::vector<std::vector<int>> adjacency_matrix2(n, std::vector<int>(n, 0));

    UnionFind uf(n);

    for (int route = 0; route < m; route++)
    {
        int k;
        std::cin >> k;

        std::vector<int> stops(k);
        for (int i = 0; i < k; i++)
        {
            std::cin >> stops[i];
            stops[i]--;
        }

        for (int i = 0; i < k - 1; i++)
        {
            int u = stops[i];
            int v = stops[i + 1];
            adjacency_matrix1[u][v] = 1;
            adjacency_matrix1[v][u] = 1;
        }

        for (int i = 0; i < k; i++)
        {
            for (int j = i + 1; j < k; j++)
            {
                uf.unite(stops[i], stops[j]);
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (uf.find(i) == uf.find(j))
            {
                adjacency_matrix2[i][j] = 1;
                adjacency_matrix2[j][i] = 1;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << adjacency_matrix1[i][j] << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << adjacency_matrix2[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

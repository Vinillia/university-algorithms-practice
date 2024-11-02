#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

struct Cell 
{
    int x, y;
    string path;
};

int main() 
{
    int n, m;
    cin >> n >> m;

    vector<string> maze(n);
    for (int i = 0; i < n; ++i) 
    {
        cin >> maze[i];
    }

    int startX, startY, endX, endY;
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < m; ++j) 
        {
            if (maze[i][j] == 'S') 
            {
                startX = i;
                startY = j;
            }
            else if (maze[i][j] == 'F') 
            {
                endX = i;
                endY = j;
            }
        }
    }

    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };
    char dir[] = { 'U', 'D', 'L', 'R' };

    queue<Cell> q;
    q.push({ startX, startY, "" });
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    visited[startX][startY] = true;

    while (!q.empty()) 
    {
        Cell current = q.front();
        q.pop();

        if (current.x == endX && current.y == endY) 
        {
            cout << current.path.size() << endl;
            cout << current.path << endl;
            return 0;
        }

        for (int i = 0; i < 4; ++i)
        {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (nx >= 0 && nx < n && ny >= 0 && ny < m && maze[nx][ny] != '#' && !visited[nx][ny])
            {
                visited[nx][ny] = true;
                q.push({ nx, ny, current.path + dir[i] });
            }
        }
    }

    cout << -1 << endl;
    return 0;
}
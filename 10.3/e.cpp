#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <ranges>

using namespace std;

struct State
{
	int x, y;
	int keys;
	string path;
};

bool is_valid(int x, int y, int n, int m)
{
	return x >= 0 && x < n && y >= 0 && y < m;
}

int key_bit(char key)
{
	return 1 << (key - 'a');
}

pair<int, string> solve_labyrinth(int n, int m, const vector<string>& labyrinth, int k, const vector<pair<char, char>>& door_key_pairs, bool consider_keys)
{
	unordered_map<char, char> door_to_key;
	for (const auto& [door, key] : door_key_pairs)
	{
		door_to_key[door] = key;
	}

	pair<int, int> start, end;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			char cell = labyrinth[i][j];
			if (cell == 'S')
				start = { i, j };
			else if (cell == 'F')
				end = { i, j };
		}
	}

	vector<pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
	vector<char> moves = { 'U', 'D', 'L', 'R' };

	auto hash = [](const std::pair<string, bool>& data)
		{
			return std::hash<std::string>()(data.first) ^ (std::hash<bool>()(data.second) << 1);
		};

	auto equal = [](const std::pair<string, bool>& a, const std::pair<string, bool>& b)
		{
			return a.first == b.first && a.second == b.second;
		};

	queue<State> q;
	q.push({ start.first, start.second, 0, "" });
	unordered_set<std::pair<string, bool>, decltype(hash), decltype(equal)> visited;

	auto encode_state = [](int x, int y, int keys) {
		return to_string(x) + "," + to_string(y) + "," + to_string(keys);
		};

	visited.insert({ encode_state(start.first, start.second, 0), false });

	while (!q.empty())
	{
		State cur = q.front();
		q.pop();

		if (cur.x == end.first && cur.y == end.second)
			return { cur.path.length(), cur.path };

		char ca = labyrinth[cur.x][cur.y];

		for (int i = 0; i < 4; ++i)
		{
			int nx = cur.x + directions[i].first;
			int ny = cur.y + directions[i].second;

			if (is_valid(nx, ny, n, m))
			{
				char cell = labyrinth[nx][ny];
				int new_keys = cur.keys;

				if (cell == '.' || cell == 'F' || cell == 'S')
				{
				consider_key:
					string state_key = encode_state(nx, ny, new_keys);
					if (!visited.count({ state_key, false }))
					{
						visited.insert({ state_key, false });
						q.push({ nx, ny, new_keys, cur.path + moves[i] });
					}
				}
				else if ('a' <= cell && cell <= 'k')
				{
					if (!consider_keys)
					{
						goto consider_key;
					}

					new_keys |= key_bit(cell);
					string state_key = encode_state(nx, ny, new_keys);
					if (!visited.count({ state_key, true }))
					{
						visited.insert({ state_key, true });
						std::erase_if(visited, [](auto& cell)
							{
								return !cell.second;
							});

						const_cast<std::vector<std::string>&>(labyrinth)[nx][ny] = '.';
						q.push({ nx, ny, new_keys, cur.path + moves[i] + 'P' });
					}
				}
				else if ('A' <= cell && cell <= 'J')
				{
					if ((new_keys & key_bit(door_to_key[cell])) != 0)
					{
						string state_key = encode_state(nx, ny, new_keys);
						if (!visited.count({ state_key, false }))
						{
							visited.insert({ state_key, false });
							q.push({ nx, ny, new_keys, cur.path + moves[i] });
						}
					}
				}
			}
		}
	}

	return { -1, "" };
}

int main()
{
	int n, m, k;
	cin >> n >> m;
	vector<string> labyrinth(n);
	for (int i = 0; i < n; ++i)
		cin >> labyrinth[i];

	cin >> k;
	vector<pair<char, char>> door_key_pairs(k);
	for (int i = 0; i < k; ++i)
		cin >> door_key_pairs[i].first >> door_key_pairs[i].second;

	auto result = solve_labyrinth(n, m, labyrinth, k, door_key_pairs, false);
	if (result.first == -1)
	{
		result = solve_labyrinth(n, m, labyrinth, k, door_key_pairs, true);

		if (result.first == -1)
		{
			cout << -1 << endl;
			return 0;
		}
	}

	cout << result.first << endl;
	cout << result.second << endl;
	return 0;
}
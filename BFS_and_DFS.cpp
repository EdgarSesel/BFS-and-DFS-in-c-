#include<bits/stdc++.h>
#include<windows.h>
using namespace std;

class Graph {
    int V;
    list<int> *adj;

public:
    Graph(int V);
    void addEdge(int v, int w);
    void BFS(int s);
    void DFS(int s);
    void DFSUtil(int v, bool visited[]);
};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
}

void Graph::BFS(int s) {
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;

    list<int> queue;
    visited[s] = true;
    queue.push_back(s);

    while(!queue.empty()) {
        s = queue.front();
        cout << s << " ";
        queue.pop_front();

        for (auto i = adj[s].begin(); i != adj[s].end(); ++i) {
            if (!visited[*i]) {
                queue.push_back(*i);
                visited[*i] = true;
            }
        }
    }
}

void Graph::DFSUtil(int v, bool visited[]) {
    visited[v] = true;
    cout << v << " ";

    list<int>::iterator i;
    for(i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);
}

void Graph::DFS(int v) {
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    DFSUtil(v, visited);
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void print_maze(vector<vector<char>> &maze, list<pair<int, int>> path) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[i].size(); j++) {
            if (find(path.begin(), path.end(), make_pair(i, j)) != path.end()) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                gotoxy(j, i);
                cout << "X";
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            } else {
                gotoxy(j, i);
                cout << maze[i][j];
            }
        }
        cout << "\n";
    }
}

list<pair<int, int>> BFS(vector<vector<char>> &maze, pair<int, int> start, pair<int, int> end, bool printMaze = true) {
    int rows = maze.size();
    int cols = maze[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, {-1, -1}));
    queue<pair<int, int>> q;
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    q.push(start);
    visited[start.first][start.second] = true;

    bool pathExists = false;

    while (!q.empty()) {
        pair<int, int> current = q.front();
        q.pop();

        if (current == end) {
            pathExists = true;
            break;
        }

        for (pair<int, int> dir : directions) {
            int newRow = current.first + dir.first;
            int newCol = current.second + dir.second;

            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && maze[newRow][newCol] != '#' && !visited[newRow][newCol]) {
                q.push({newRow, newCol});
                visited[newRow][newCol] = true;
                parent[newRow][newCol] = current;

                list<pair<int, int>> path;
                pair<int, int> currentPos = {newRow, newCol};
                while (currentPos != start) {
                    path.push_front(currentPos);
                    currentPos = parent[currentPos.first][currentPos.second];
                }
                path.push_front(start);

                if (printMaze) {
                    system("CLS");
                    print_maze(maze, path);
                    Sleep(250);
            }

                if (make_pair(newRow, newCol) == end) {
                    return path;
                }
            }
        }
    }

    return list<pair<int, int>>();
}


list<pair<int, int>> DFS(vector<vector<char>> &maze, pair<int, int> start, pair<int, int> end, bool printMaze = true) {
    int rows = maze.size();
    int cols = maze[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, {-1, -1}));
    stack<pair<int, int>> s;
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    s.push(start);
    visited[start.first][start.second] = true;

    bool pathExists = false;

    while (!s.empty()) {
        pair<int, int> current = s.top();
        s.pop();

        if (current == end) {
            pathExists = true;
            break;
        }

        for (pair<int, int> dir : directions) {
            int newRow = current.first + dir.first;
            int newCol = current.second + dir.second;

            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && maze[newRow][newCol] != '#' && !visited[newRow][newCol]) {
                s.push({newRow, newCol});
                visited[newRow][newCol] = true;
                parent[newRow][newCol] = current;

                list<pair<int, int>> path;
                pair<int, int> currentPos = {newRow, newCol};
                while (currentPos != start) {
                    path.push_front(currentPos);
                    currentPos = parent[currentPos.first][currentPos.second];
                }
                path.push_front(start);

                if (printMaze) {
                    system("CLS");
                    print_maze(maze, path);
                    Sleep(250);
                }

                if (make_pair(newRow, newCol) == end) {
                    cout << endl;
                    break;
                }
            }
        }
    }
list<pair<int, int>> path;
    if (pathExists) {
        pair<int, int> currentPos = end;
        while (currentPos != start) {
            path.push_front(currentPos);
            currentPos = parent[currentPos.first][currentPos.second];
        }
        path.push_front(start);
    }

    return path;
}

void comparePaths(vector<vector<char>> &maze, pair<int, int> start, pair<int, int> end, bool option) {
    list<pair<int, int>> pathBFS = BFS(maze, start, end, option);
    list<pair<int, int>> pathDFS = DFS(maze, start, end, option);

    int lengthDFS = pathDFS.size();
    int lengthBFS = pathBFS.size();

    cout << "BFS path length: " << lengthBFS << "\n";
    cout << "DFS path length: " << lengthDFS << "\n";

    if (lengthDFS < lengthBFS) {
        cout << "DFS found a faster path by " << lengthBFS - lengthDFS << " moves.\n\n";
    } else if (lengthBFS < lengthDFS) {
        cout << "BFS found a faster path by " << lengthDFS - lengthBFS << " moves.\n\n";
    } else {
        cout << "Both DFS and BFS found a path of the same length.\n\n";
    }
}




int main() {
    vector<vector<char>> maze = {
        {'#', '#', '#', '#', '#', 'O', '#', '#', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', '#', ' ', '#', '#', ' ', '#'},
        {'#', ' ', '#', '#', ' ', '#', '#', ' ', '#'},
        {'#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
        {'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
        {'#', '#', '#', ' ', '#', '#', '#', ' ', '#'},
        {'#', ' ', '#', '#', '#', ' ', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
        {'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
        {'#', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
        {'#', ' ', '#', ' ', '#', ' ', '#', '#', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', 'X', '#'}
    };

    pair<int, int> start = {0, 5};
    pair<int, int> end = {14, 7};

    bool option, temp;
    int choice;
    bool quit=true;
    while(quit){
    cout << "Welcome back, Colleagues!" << endl <<endl;
    cout << "Please choose from options below: " << "\n1) BFS (Breadth-First Search) algorithm" << "\n2) DFS (Depth-First Search) algorithm" << "\n3) Comparison of BFS and DFS algorithms" << "\n4) Quit" << endl;
    cout << "Confirm your choice: ";
    cin >> choice;
    switch(choice)
    {
    case 1:
        BFS(maze, start, end);
        break;

    case 2:
        DFS(maze, start, end);
        break;

    case 3:
        temp=true;
        char check;
        while(temp){
        cout << "\n\nDo you want to see path of BFS and DFS ('y' and 'Y' - yes, 'n' and 'N' - no)?" << endl;
        cout << "Confirm your choice: ";
        cin >> check;
        if (check == 'n' || check == 'N'){
            option = false;
            temp = false;
        }

        else if (check == 'y' || check == 'Y'){
            option = true;
            temp = false;
        }

        else{
            cout<<"\nWrong option, try again!";
        }
        }


        comparePaths(maze, start, end, option);
        break;

    case 4:
        quit = false;
        break;

    default:
        cout << "\nInvalid option, try one more time!\n\n";
        break;
    }
    }

    cout<<"\nSee you next time, my friend!\n";
    return 0;
}

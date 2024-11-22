#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <queue>
#include <utility>
#include "bingo.h"

using namespace std;


void Matrix::display() const
{
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            cout << setfill('0') << setw(2) << grid[i][j] << " ";
        }
        cout << endl;
    }
}

bool Matrix::select(int _n)
{
    bool fl{0};
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(grid[i][j] == _n)
            {
                fl = 1;
                grid[i][j] = 0;
            }
        }
    }
    return fl ? 1 : 0;
}


bool Matrix::win() const
{

    int res = 0;
    bool fl{1};

    for(int i = 1; i <= n; i++)
    {
        fl = 1;
        for(int j = 1; j <= n; j++)
        {
            if(grid[i][j])
            {
                fl = 0;
                break;
            }
        }
        if(fl)
            res++;
    }

    for(int i = 1; i <= n; i++)
    {
        fl = 1;
        for(int j = 1; j <= n; j++)
        {
            if(grid[j][i])
            {
                fl = 0;
                break;
            }
        }
        if(fl)
            res++;
    }

    fl = 1;
    for(int i = 1; i <= n; i++)
    {
        if(grid[i][i])
            fl = 0;
    }
    if(fl)
        res++;

    fl = 1;
    for(int i = 1, j = n; i <= n, j >= 1; i++, j--)
    {
        if(grid[i][j])
            fl = 0;
    }

    if(fl)
        res++;
    return res >= n ? 1 : 0;
}

void Matrix::init(int l, int r)
{
    vector<int> nums;

    for (int i = l; i <= r; i++)
        nums.push_back(i);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(nums.begin(), nums.end(), default_random_engine(seed));

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            grid[i][j] = nums[n * (i - 1) + (j - 1)];
        }
    }
}


pair<int, int> Machine::bfs(pair<int, int> point, pair<int, int> dxy) const
{
    bool vis[11][11] {};
    queue<pair<int, int>> q;
    pair<int, int> last = point;
    vis[point.first][point.second] = 1;
    q.push(point);

    while(!q.empty())
    {
        pair<int,int> u = q.front();
        q.pop();

        pair<int, int> v = make_pair(u.first + dxy.first, u.second + dxy.second);
        if(v.first <= 0 || v.first > n || v.second <= 0 || v.second > n || grid[v.first][v.second] || vis[v.first][v.second])
            continue;

        last = v;
        vis[v.first][v.second] = 1;
        q.push(v);

    }

    return last;
}

Machine::pointw Machine::movee() const
{
    int rss = 0;
    pointw mxx[n * n] {};

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            /// 3 3
            /// 3-0 3-1
            /// 3 2
            pair<int, int> left{0, -1};
            pair<int, int> right{0, 1};
            pair<int, int> down{-1, 0};
            pair<int, int> up{1, 0};
            pair<int, int> upleft{-1, -1};
            pair<int, int> upright{-1, 1};
            pair<int, int> downleft{1, -1};
            pair<int, int> downright{1, 1};


            if(!grid[i][j])
            {
                pair<int, int> point = bfs({i, j}, left);
                pair<int, int> point1 = bfs({i, j}, right);
                pair<int, int> point2 = bfs({i, j}, down);
                pair<int, int> point3 = bfs({i, j}, up);
                pair<int, int> point4 = bfs({i, j}, upleft);
                pair<int, int> point5 = bfs({i, j}, upright);
                pair<int, int> point6 = bfs({i, j}, downleft);
                pair<int, int> point7 = bfs({i, j}, downright);

                int weight = abs(j - point.second);
                int weight1 = abs(j - point1.second);
                int weight2 = abs(i - point2.first);
                int weight3 = abs(i - point3.first);
                int weight4 = abs(i - point4.first);
                int weight5 = abs(i - point5.first);
                int weight6 = abs(i - point6.first);
                int weight7 = abs(i - point7.first);

                int mx = max({weight, weight1, weight2, weight3, weight4, weight5, weight6, weight7}) + 1;


                if(mx == weight + 1 && point.second + left.second >= 1)
                    mxx[rss] = {point.first, point.second + left.second, weight + 1};
                else if(mx == weight1 + 1 && point1.second + right.second <= n)
                    mxx[rss] = {point1.first, point1.second + right.second, weight1 + 1};
                else if(mx == weight2 + 1 && point2.first + down.first >= 1)
                    mxx[rss] = {point2.first + down.first, point2.second, weight2 + 1};
                else if(mx == weight3 + 1 && point3.first + up.first <= n)
                    mxx[rss] = {point3.first + up.first, point3.second, weight3 + 1};
                else if(mx == weight4 + 1 && point4.first + upleft.first >= 1 && i == j)
                    mxx[rss] = {point4.first + upleft.first, point4.second + upleft.second, weight4 + 1};
                else if(mx == weight5 + 1 && point5.first + upright.first >= 1 && n - i == j - 1)
                    mxx[rss] = {point5.first + upright.first, point5.second + upright.second, weight5 + 1};
                else if(mx == weight6 + 1 && point6.first + downleft.first <= n && n - i == j - 1)
                    mxx[rss] = {point6.first + downleft.first, point6.second + downleft.second, weight6 + 1};
                else if(mx == weight7 + 1 && point7.first + downright.first <= n && i == j)
                    mxx[rss] = {point7.first + downright.first, point7.second + downright.second, weight7 + 1};

                rss++;
            }

        }
    }

    pointw fin{};
    for(int i = 0; i < rss; i++)
    {
        if(fin.w < mxx[i].w)
            fin = mxx[i];
    }

    return fin;
}
int Machine::choose() const
{
    pointw point = movee();
    return grid[point.x][point.y];
}

void Player::input_matrix()
{
    cout << "Nhap ma tran cua ban: " << endl;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
            cin >> grid[i][j];
    }
}

void Bingo::play()
{
    bool player_win{0}, machine_win{0};
    while(1)
    {
        int num{};

        cout << "Chon so: ";
        cin >> num;
        if(!player.select(num))
        {
            cout << "\nO da duoc chon!\n";
            do
            {
                cout << "Chon so: ";
                cin >> num;
            }
            while(!player.select(num));
        }

        machine.select(num);
        if(player.win())
        {
            player_win = 1;
            break;
        }

        int num_m = machine.choose();
        machine.select(num_m);
        player.select(num_m);
        cout << "May chon: " << num_m << endl;
        if(machine.win())
        {
            machine_win = 1;
            break;
        }

        cout << "Ma tran cua ban: " << endl;
        player.display();
         cout << "Ma tran cua may: " << endl;
        machine.display();
        cout << "----------------\n\n";
    }

    if(player_win)
    {
        cout << "Ban thang";
    }
    else
    {
        cout << "May thang";
    }
}

// #include "bits/stdc++.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#include <unordered_set>
#include <list>
#include <iterator>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <bitset>
#include <random>
#include <map>
#include <unordered_map>
#include <stdio.h>
#include <complex>
#include <math.h>
#include <cstring>
#include <chrono>
#include <string>
// ########################################################################################################################################################
using namespace std;
using namespace std::chrono;

#define ll long long
#define pb push_back
#define pob pop_back()
#define pf push_front
#define pof pop_front()
#define mod 1000000007
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL)

/*
We wish to produce an optimum matching
*/
class assignment_matching
{
private:
    int n;
    vector<vector<int>> cost_matrix;
    int recursive_dp_visited_states, iteratve_dp_visited_states;

    void __permute_recursive__(vector<int> &curr_permutation, int idx, ll &curr_cost, ll &min_cost)
    {
        if (idx == n)
        {
            min_cost = min(min_cost, curr_cost);
            return;
        }
        for (int j = idx; j < n; j++)
        {
            swap(curr_permutation[idx], curr_permutation[j]);
            curr_cost += cost_matrix[idx][curr_permutation[idx]];
            __permute_recursive__(curr_permutation, idx + 1, curr_cost, min_cost);
            curr_cost -= cost_matrix[idx][curr_permutation[idx]];
            swap(curr_permutation[idx], curr_permutation[j]);
        }
    }

    inline int clearbit(int mask, int index)
    {
        return mask & (~(1 << index));
    }
    ll __mincost_dp_iteratve__()
    {

        vector<vector<ll>> dp(2, vector<ll>(1 << n, INT64_MAX));

        for (int task = 0; task < n; task++)
            dp[0][1 << task] = cost_matrix[0][task]; // single assignemnt single student

        for (int person = 1; person < n; person++)
        {
            for (int mask = 0; mask < (1 << n); mask++)
            {
                dp[person % 2][mask] = INT64_MAX;
                if (__builtin_popcount(mask) != person + 1) // not a size valid dubset
                    continue;
                for (int task_to_curr = 0; task_to_curr < n; task_to_curr++)
                {
                    if (!((mask >> task_to_curr) & 1))
                        continue;
                    int subset = clearbit(mask, task_to_curr);

                    dp[person % 2][mask] = min(dp[person % 2][mask], dp[person % 2 ^ 1][subset] + 1ll * cost_matrix[person][task_to_curr]);
                }
            }
        }

        return dp[(n - 1) % 2][(1 << n) - 1];
    }

    ll __mincost_dp_recursive__(vector<vector<ll>> &dp, int mask, int person)
    {
        if (mask == 0)
            return 0;
        if (dp[person][mask] != -1)
            return dp[person][mask];
        dp[person][mask] = INT64_MAX;
        for (int task_to_curr = 0; task_to_curr < n; task_to_curr++)
        {
            if (!((mask >> task_to_curr) & 1))
                continue;
            int subset = clearbit(mask, task_to_curr);
            dp[person][mask] = min(dp[person][mask], __mincost_dp_recursive__(dp, subset, person - 1) + 1ll * cost_matrix[person][task_to_curr]);
        }
        ++recursive_dp_visited_states;
        return dp[person][mask];
    }

public:
    assignment_matching(vector<vector<int>> &cost)
    {
        n = cost.size();
        cost_matrix = cost;
    }

    ll optimum_brute_recursive()
    {

        vector<int> curr_permutation(n);
        for (int i = 0; i < n; i++)
            curr_permutation[i] = i;

        ll min_cost = INT64_MAX, curr_cost = 0;
        __permute_recursive__(curr_permutation, 0, curr_cost, min_cost);
        return min_cost;
    }
    ll optimum_dp_iterative()
    {
        iteratve_dp_visited_states = n * (1 << n);
        return __mincost_dp_iteratve__();
    }
    ll optimum_dp_recursive()
    {
        vector<vector<ll>> dp(n, vector<ll>(1 << n, -1));
        recursive_dp_visited_states = 0;
        return __mincost_dp_recursive__(dp, (1 << n) - 1, n - 1);
    }

    void show_input()
    {
        cout << "Priniting input cost matirx!\n";
        cout << "Input matrix size: " << n << "\n";
        for (vector<int> row : cost_matrix)
        {
            for (int cost : row)
                cout << cost << ' ';
            cout << "\n";
        }
        cout << "\n";
    }
    void show_used_states()
    {
        cout << "States used in iterative dp: " << iteratve_dp_visited_states << " and in recursive dp: " << recursive_dp_visited_states << '\n';
    }
};
/*
  dp[i][mask] ==> minimum cost alloting the Assignmnets represented by subset 'mask'
  to students 0,1....i
  dp[i][mask] == ll 64_MAX if Assignment Subset size (== set bits in mask) != Student subset sixe (== i+1 )
  Since each dp[i][mask] depends on only dp[i-1][mask'], we can use space optimized dp[][]
  */
void take_input(vector<vector<int>> &vec)
{
    for (int i = 0; i < vec.size(); i++)
        for (int j = 0; j < vec.size(); j++)
            cin >> vec[i][j];
}

void show_error(ll ans_brute, ll ans_dp_it, ll ans_dp_rec)
{
    cout << "Result of brute force solution: " << ans_brute << "\n";
    cout << "Result of iterative dp solution: " << ans_dp_it << "\n";
    cout << "Result of recursive dp solution: " << ans_dp_rec << "\n";
    cout << "Terminating Program\n";
}
void print_times(vector<duration<double, std::milli>> &time_brute, vector<duration<double, std::milli>> &time_dp_it, vector<duration<double, std::milli>> &time_dp_rec)
{
    cout << "\n\nAll Test Cases Passed! Printing Runtimes:\n ";
    cout << "T_Brute force | T_iterative_dp | T_recursive_dp\n";
    cout << setprecision(6);
    for (int i = 0; i < time_brute.size(); i++)
        cout << time_brute[i].count() << ' ' << time_dp_it[i].count() << ' ' << time_dp_rec[i].count() << '\n';
}

int main()
{
    fastio;
    freopen("output.txt", "w", stdout);
    freopen("input.txt", "r", stdin);

    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;
    using std::chrono::milliseconds;
    int TESTCASE_CNT;
    cin >> TESTCASE_CNT;

    vector<duration<double, std::milli>> time_dp_it(TESTCASE_CNT), time_brute(TESTCASE_CNT), time_dp_rec(TESTCASE_CNT);

    for (int test = 0; test < TESTCASE_CNT; test++)
    {
        int ASSIGNMENT_CNT;
        cin >> ASSIGNMENT_CNT;
        vector<vector<int>> cost_matrix(ASSIGNMENT_CNT, vector<int>(ASSIGNMENT_CNT));
        take_input(cost_matrix);
        assignment_matching model(cost_matrix);
        auto T_START = high_resolution_clock::now();
        ll ans_brute = model.optimum_brute_recursive();
        auto T_BRUTE_END = high_resolution_clock::now();
        ll ans_dp_it = model.optimum_dp_iterative();
        auto T_itDP_END = high_resolution_clock::now();
        ll ans_dp_rec = model.optimum_dp_recursive();
        auto T_recDP_END = high_resolution_clock::now();
        if (ans_dp_it != ans_brute || ans_brute != ans_dp_rec)
        {
            cout << "Test Falied! Printing Details\n";
            model.show_input();
            show_error(ans_brute, ans_dp_it, ans_dp_rec);
            return 0;
        }
        time_brute[test] = T_BRUTE_END - T_START;
        time_dp_it[test] = T_itDP_END - T_BRUTE_END;
        time_dp_rec[test] = T_recDP_END - T_itDP_END;
        model.show_used_states();
    }
    print_times(time_brute, time_dp_it, time_dp_rec);

    fclose(stdout);
    fclose(stdin);
    return 0;
}
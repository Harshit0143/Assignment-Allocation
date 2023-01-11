#include "bits/stdc++.h"
using namespace std;
using namespace std::chrono;

#define ll long long
#define pb push_back
#define pob pop_back()
#define pf push_front
#define pof pop_front()
#define mod 1000000007
#define add_m(a, b) (((a % mod) + (b % mod)) % mod)
#define sub_m(a, b) (((a % mod) - (b % mod) + mod) % mod)
#define mul_m(a, b) (((a % mod) * (b % mod)) % mod)
/*
We wish to produce an optimum matching
*/





void permute_rec(const vector<vector<ll> > &effort, vector<ll> &perm, ll i, ll &cst, ll &min_cst)
{
    ll n = effort.size();
    if (i == n)
    {
        min_cst = min(min_cst, cst);
        return;
    }
    for (ll j = i; j < n; j++)
    {
        swap(perm[i], perm[j]);
        cst += effort[i][perm[i]];
        rec(effort, perm, i + 1, cst, min_cst);
        cst -= effort[i][perm[i]];
        swap(perm[i], perm[j]);
    }
}

ll minimum_effort_permute(vector<vector<ll> > &effort)
{
    ll n = effort.size();
    ll min_cst = INT64_MAX, cst = 0;
    vector<ll> perm(n);
    for (ll i = 0; i < n; i++)
        perm[i] = i;
    permute_rec(effort, perm, 0, cst, min_cst);
    return min_cst;
}



ll clearbit(ll n, ll pos)
{
  return n & (~((1ll) << pos));
}

ll minimum_effort_dp(vector<vector<ll> > &effort)
{

  ll n = effort.size();

  vector<vector<ll> > dp(2, vector<ll>((1ll) << n, INT64_MAX));
  for (ll j = 0; j < n; j++)
    dp[0][(1ll) << j] = effort[0][j]; // single assignemnt single student

  for (ll i = 1; i < n; i++)
  {
    for (ll j = 0; j < ((1ll) << n); j++)
    {
      if (__builtin_popcount(j) != i + 1) // not a size valid dubset
        continue;
      for (ll x = 0; x < n; x++)
      {
        if ((j & ((1ll) << x)) == 0)
          continue;
        ll sub = clearbit(j, x);

        dp[i % 2][j] = min(dp[i % 2][j], dp[(i - 1) % 2][sub] + effort[i][x]);
      }
    }
  }

  return dp[(n - 1) % 2][((1ll) << n) - 1];
}
/*
dp[i][mask] ==> minimum cost alloting the Assignmnets represented by subset 'mask'
to students 0,1....i
dp[i][mask] == ll 64_MAX if Assignment Subset size (== set bits in mask) != Student subset sixe (== i+1 )
Since each dp[i][mask] depends on only dp[i-1][mask'], we can use space optimized dp[][]
*/

void take_input(vector<vector<ll> > &vec)
{
  ll n = vec.size();
  for (ll i = 0; i < n; i++)
    for (ll j = 0; j < n; j++)
      scanf("%lld", &vec[i][j]);
}

int main()
{ cout<<"hi\n";
  ll n;
  scanf("%lld", &n);
  vector<vector<ll> > vec(n, vector<ll>(n));
  take_input(vec);
  ll test_case;
 
  for (ll i  )
  auto start = high_resolution_clock::now();
  cout << minimum_effort_dp(vec) << "\n";
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  stop = start;
   cout << minimum_effort_permute(vec) << "\n";
  auto stop = high_resolution_clock::now();
   auto duration = duration_cast<microseconds>(stop - start);

 
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;

  return 0;
}
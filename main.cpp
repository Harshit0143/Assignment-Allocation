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
    permute_rec(effort, perm, i + 1, cst, min_cst);
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
void print(const vector <vector <ll > >&vec)
{for (vector <ll > c: vec) 
{ for (ll  d:c) {cout<< d<<" ";} cout<<"\n";}cout<<"\n";
}

int main()
{
  freopen ("output.txt","w",stdout);
  freopen("input.txt","r", stdin);
                                   
 
  using std::chrono::duration;
  using std::chrono::duration_cast;
  using std::chrono::high_resolution_clock;
  using std::chrono::milliseconds;

  ll num,n;
  scanf("%lld", &num);
  vector<duration<double, std::milli> > time_dp(num), time_pern(num);

  for (ll i = 0; i < num; i++)
  {
    scanf("%lld", &n);
    vector<vector<ll> > vec(n, vector<ll>(n));
    take_input(vec);
    auto t1 = high_resolution_clock::now();
    ll ans_dp = minimum_effort_dp(vec);
    auto t2 = high_resolution_clock::now();
    ll ans_brute = minimum_effort_permute(vec);
    auto t3 = high_resolution_clock::now();
    if (ans_dp != ans_brute)
    {
      cout << "Test Falied! Printing Details\n";
      cout << "Input matrix size: " << n << "\n";
      print(vec);
      cout << "Result of dp[] solution: " << ans_dp << "\n";
      cout << "Result of brute force solution: " << ans_brute << "\n";
      cout<<"Terminating Program\n";
      return 0;
    }
    time_dp[i] = t2 - t1;
    time_pern[i] = t3 - t2;
  }
  cout<<"All Test Cases Passed! Printing Runtimes:\n ";
  for (ll i = 0; i < num; i++)
    cout << time_dp[i].count() << "         " << time_pern[i].count() << "\n";
    fclose (stdout);
  fclose(stdin);
  return 0;
}
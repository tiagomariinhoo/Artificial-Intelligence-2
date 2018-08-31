#include <bits/stdc++.h>
using namespace std;
 
#define DEBUG if(1)
#define MAX INT_MAX
#define MAXLL LLONG_MAX
#define MAXU ULLONG_MAX
#define MIN -2000000
#define endl "\n"
#define INF 99999999
#define MOD 1000000007
#define s(n) scanf("%d", &n)
#define ss(a,b) scanf("%d %d",&a,&b)
#define pb push_back
#define mp make_pair
#define M_PI 3.14159265358979323846
#define sz(a) int(a.size())
#define lli long long int
#define rep(i,a,n) for (int i=a;i<n;i++)
#define ler(a,n,vec) for(int i=0;i<n;i++)s(a), vec.pb(a)
typedef vector<lli> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef pair<string, pair<int, char> > ps;
#define DEBUG if(1)
#define F first
#define S second
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
int ddx[] = {1, 0};
int ddy[] = {1, 1};

const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();

//Casos base
string t1  = "1111011001";
string t2  = "1111110100";
string t3  = "1001011111";
string t4  = "1100110111";

vector<pair<string, int> > cases;
vector<string> base;
vector<double> weights;


double cError = 0;
double vCoef = 0.0;
double peso = -30;

void generate(){

  srand(RANDOM);

  for(int j=0;j<10;j++){
  string aux = "";
    for(int i=0;i<10;i++){
      int atual = rand()%2;

      aux += atual + '0';
    }

    int at = 0;
    for(int i=0;i<sz(base);i++){
      if(base[i] == aux) at = 1;
    }

    cases.pb({aux, at});
  }
  
  for(int i=0;i<sz(base);i++) cases.pb({base[i], 1});

  // for(int i=0;i<sz(cases);i++) cout << cases[i].F << " " << cases[i].S << endl;
}

void setWeights(){
  weights.clear();
  for(int i=0;i<10;i++) weights.pb(peso);

  // cout << "Pesos atuais " << endl;
  // for(int i=0;i<sz(weights);i++) cout << weights[i] << " ";
  //   cout << endl;

}

void adjWeight(double error, string aux){

  for(int i=0;i<10;i++){
    weights[i] = weights[i] + vCoef * error * (aux[i] - '0');
  }
}

void train(){
  setWeights();

  int c = 0, eCounter = 0;
  while(1){
    c += 1;

    for(int i=0;i<sz(cases);i++){
      double sum = 0;
      string auxString = cases[i].F;
        for(int j=0;j<10;j++){
          sum += ((auxString[j] - '0') * weights[j]);
        }

      int at = 0;
      if(sum >= 0) at = 1;

      //Obtido - esperado
      double error = cases[i].S - at;

      if(error != 0){
        eCounter++;
        adjWeight(error, auxString);
      }


    }

    if(c == 5000 or !eCounter) break;
    else eCounter = 0;
  }

  // for(int i=0;i<sz(weights);i++) cout << weights[i] << " ";
  //   cout << endl;
}

int isTri(string atual){
  int sum = 0;
  for(int i=0;i<10;i++) sum += ((atual[i] - '0') * weights[i]);
  
  // for(int i=0;i<sz(weights);i++) cout << weights[i] << " ";
  //   cout << endl;

  // printf("%d\n",sum);
    // cout << atual << " - " << sum << endl;
  return (sum >= 0);
}

int main(){
  // ios_base::sync_with_stdio(false);
  // cin.tie(NULL);

  base.pb(t1), base.pb(t2), base.pb(t3), base.pb(t4);

  for(int i=0;i<30;i++){
    for(int j=0;j<10;j++){
      cases.clear();
      generate();
      train();

      string tri = "1111011001";
      string nTri = "1010101010";

      int aa = isTri(tri);
      int bb = isTri(nTri);
      // printf("%d %d \n", aa, bb);

      if(aa != 1 or bb != 0) cError++;

    }

    printf("Coef Variation : %lf \n", vCoef);
    vCoef += 0.02;
    printf("Peso Inicial : %lf \n", peso);
    peso += 1;
    double div = (double)cError / (double)10;
    printf("Taxa de erro : %.2lf \n \n", div);
    cError = 0;
  }


  return 0;
}

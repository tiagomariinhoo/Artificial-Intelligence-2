#include <bits/stdc++.h>
using namespace std;
 
#define DEBUG if(1)
#define MAX INT_MAX
#define MAXLL INT_MAX
#define MAXU ULLONG_MAX
#define MIN -2000000
#define endl "\n"
#define INF INT_MAX
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
#define DEBUG if(1)
#define F first
#define S second
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
int ddx[] = {1, 0};
int ddy[] = {1, 1};
#define MAXN 100001
#define MAXL 20
#define EPS 1e-9

double input[2] = {5, 1};
double output1[2], output2[2];

double sigmoide(double n){
	return 1 / (1 + exp(-n));
}

int main(){ 
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  double w[2][2];
  for(int i=0;i<2;i++){
  	for(int j=0;j<2;j++){
  		if(i == j) w[i][j] = 0;
  		else{
  			double atual = (double)rand()/(double)RAND_MAX;
  			while(atual == 0 or atual == 1) atual = (double)rand()/(double)RAND_MAX;
  			w[i][j] = atual;
  		}
  	}
  }

  // for(int i=1;i<=100;i++){
  // 	printf("%d : %lf\n", i, sigmoide(i));
  // }

  printf("Pesos: \n");
  for(int i=0;i<2;i++){
  	for(int j=0;j<2;j++) printf("%.2f ", w[i][j]);
  	printf("\n");
  }

  bool parada = true;

  double soma = 0;

  while(parada){
  	for(int i=0;i<2;i++){
  		soma = input[i] * 0.5 - 0.01;
  		for(int j=0;j<2;j++){
  			soma += output1[j] * w[i][j];
  		}
  		output2[i] = sigmoide(soma);

  	}
  	soma = 0;
  	for(int i=0;i<2;i++){
  		if(abs(output1[i] - output2[i]) < EPS) soma++;
  	}

  	if(soma == 2) parada = false;

  	for(int i=0;i<2;i++) output1[i] = output2[i];

  	int c = 0;
  	for(int i=0;i<2;i++){
  		for(int j=0;j<2;j++){
  			w[i][j] = sigmoide(output2[i] * output2[j]);
  		}
  		printf("Entrada %d: %lf - ", i, input[i]);
  		printf("Saida 1: %lf - ", output1[i]);
  		printf("Saida 2 : %lf\n", output2[i]);
  		// if(abs(output1[i] - output2[i]) < EPS) c++;
  	}

  	// if(c == 2) break;
  }



  return 0;
}

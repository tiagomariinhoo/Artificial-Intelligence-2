#include <bits/stdc++.h>
using namespace std;
 
#define DEBUG if(1)
#define MAXN 100
#define MAX INT_MAX
#define MAXLL INT_MAX
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
typedef vector<int> vi;
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

struct Car{
	int x;
	int y;
	char dir;
	int temp;
	int espera;

};

struct Sinal{
	int x;
	int y;
	char dir;
	int temp;
};

vector < vector< pair< ii , int > >  > congestionamento;
vector<string> vec;
vector<Car> carro;
vector<Sinal> sinal(30);
int vis[21];
int vis2[21];
map<ii, int> qt;
int c;
bool VertHori = false;
int tempo = 5;
int qtCarros;
int haveCar;
map<ii, char> direcao;
int iteracoes;

/*
v<<<<<!<<<<<!<<<<<< 
v*****v*****^*****^
v*****v*****^*****^
v*****v*****^*****^
v*****v*****^*****^
v*****v*****^*****^
!>>>>>!>>>>>!>>>>>!
v*****v*****^*****^
v*****v*****^*****^
v*****v*****^*****^
v*****v*****^*****^
v*****v*****^*****^
!<<<<<!<<<<<!<<<<<!
v*****v*****^*****^
v*****v*****^*****^
v*****v*****^*****^
v*****v*****^*****^
v*****v*****^*****^
>>>>>>!>>>>>!>>>>>^
*/

void init(int qtCarros){
	for(int i=0;i<19;i++){
		string s;
		cin >> s;
		vec.pb(s);
	}

	for(int i=0;i<19;i++){
		for(int j=0;j<sz(vec[i]);j++){
			if(vec[i][j] == '!'){
				sinal[c].x = i, sinal[c].y = j;
				sinal[c].temp = 5;
				c++;
			}
		}
	}



	for(int i=0;i<qtCarros;i++){
		Car carroAux;
		carroAux.x = i+1, carroAux.y = 6, carroAux.dir = vec[i+1][6];
		qt[{i+1,6}]++;
		carro.pb(carroAux);
	}
}

void openHori(){
	for(int i=0;i<12;i++){
		int x = sinal[i].x, y = sinal[i].y;
		if(x == 0 and y == 6){
			sinal[i].dir = '<';
		} else if(x == 0 and y == 12){
			sinal[i].dir = '<';
		} else if(x == 6 and y == 0){
			sinal[i].dir = '>';
		} else if(x == 6 and y == 6){
			sinal[i].dir = '>';
		} else if(x == 6 and y == 12){
			sinal[i].dir = '>';
		} else if(x == 6 and y == 18){
			sinal[i].dir = '>';
		} else if(x == 12 and y == 0){
			sinal[i].dir = '<';
		} else if(x == 12 and y == 6){
			sinal[i].dir = '<';
		} else if(x == 12 and y == 12){
			sinal[i].dir = '<';
		} else if(x == 12 and y == 18){
			sinal[i].dir = '<';
		} else if(x == 18 and y == 6){
			sinal[i].dir = '>';
		} else if(x == 18 and y == 12){
			sinal[i].dir = '>';
		}
	}
}

void openVert(){
	for(int i=0;i<12;i++){
		int x = sinal[i].x, y = sinal[i].y;
		if(x == 0 and y == 6){
			sinal[i].dir = 'v';
		} else if(x == 0 and y == 12){
			sinal[i].dir = '^';
		} else if(x == 6 and y == 0){
			sinal[i].dir = 'v';
		} else if(x == 6 and y == 6){
			sinal[i].dir = 'v';
		} else if(x == 6 and y == 12){
			sinal[i].dir = '^';
		} else if(x == 6 and y == 18){
			sinal[i].dir = '^';
		} else if(x == 12 and y == 0){
			sinal[i].dir = 'v';
		} else if(x == 12 and y == 6){
			sinal[i].dir = 'v';
		} else if(x == 12 and y == 12){
			sinal[i].dir = '^';
		} else if(x == 12 and y == 18){
			sinal[i].dir = '^';
		} else if(x == 18 and y == 6){
			sinal[i].dir = 'v';
		} else if(x == 18 and y == 12){
			sinal[i].dir = '^';
		}
	}
}

ii nextPosSinal(int x, int y){
	vector<ii> aux;
	if(x == 0 and y == 6){
		aux = {{x, y-1}, {x+1, y}};
	} else if(x == 0 and y == 12){
		aux = {{x, y-1}, {-1, -1}};
	} else if(x == 6 and y == 0){
		aux = {{x, y+1}, {x+1, y}};
	} else if(x == 6 and y == 6){
		aux = {{x, y+1}, {x+1, y}};
	} else if(x == 6 and y == 12){
		aux = {{x-1, y}, {x,y+1}};
	} else if(x == 6 and y == 18){
		return {x-1, y};
	} else if(x == 12 and y == 0){
		return {x+1, y};
	} else if(x == 12 and y == 6){
		aux = {{x+1, y}, {x, y-1}};
	} else if(x == 12 and y == 12){
		aux = {{x,y-1}, {x-1,y}};
	} else if(x == 12 and y == 18){
		aux = {{x,y-1}, {x-1,y}};
	} else if(x == 18 and y == 6){
		return {x, y+1};
	} else if(x == 18 and y == 12){
		aux = {{x-1, y}, {x,y+1}};
	}
	int atual = rand()%2;

	// cout << "atual : " << atual << endl;
	// cout << aux[0].F << " - " << aux[0].S << endl;
	// cout << aux[1].F << " - " << aux[1].S << endl;
	return aux[atual];
}
ii verNext(int x, int y){
	if(vec[x][y] == '>') return {x, y+1};
	else if(vec[x][y] == '<') return {x, y-1};
	else if(vec[x][y] == '^') return {x-1, y};
	else if(vec[x][y] == 'v')return{x+1, y};
	else return nextPosSinal(x, y);
}

void nextTime(){

	int atual = haveCar;
	memset(vis2, 0, sizeof vis2);
	int count = 0;

	while(atual and count <= 20){
		for(int i=0;i<qtCarros;i++){
			if(vis[i] or vis2[i]) continue;
			ii aux = verNext(carro[i].x, carro[i].y);
			int x = aux.F, y = aux.S;
			
			if(x == -1 and y == -1){
				vis[i] = 1, vis2[i] = 1;
				qt[{carro[i].x, carro[i].y}]--;
				haveCar--;
				continue;
			}

			if(!qt[{x,y}]){
				if(vec[x][y] == '!'){
					for(int j=0;j<12;j++){
						if(sinal[j].x == x and sinal[j].y == y){
							if(sinal[j].dir == carro[i].dir){
								qt[{carro[i].x, carro[i].y}]--;
								carro[i].x = x, carro[i].y = y;
								qt[{carro[i].x, carro[i].y}]++;
							}
						
							break;
						}
					}
					
					continue;
				}

				qt[{carro[i].x, carro[i].y}]--;
				carro[i].x = x, carro[i].y = y;
				qt[{carro[i].x, carro[i].y}]++;
				carro[i].dir = vec[x][y];
				vis2[i] = 1;
				atual--;
			}
		}

		count++;
	}

	tempo--;

	if(!tempo){
		if(VertHori) openVert(), VertHori = false;
		else openHori(), VertHori = true;
		tempo = 5;
	}

}

bool have(int x, int y){
		for(int i=0;i<qtCarros;i++){
			if(vis[i]) continue;
			if(carro[i].x == x and carro[i].y == y) return true;
		}
		return false;
}

bool isSinal(int x, int y){
	if(x == 0 and y == 6){
		return true;
	} else if(x == 0 and y == 12){
		return true;
	} else if(x == 6 and y == 0){
		return true;
	} else if(x == 6 and y == 6){
		return true;
	} else if(x == 6 and y == 12){
		return true;
	} else if(x == 6 and y == 18){
		return true;
	} else if(x == 12 and y == 0){
		return true;
	} else if(x == 12 and y == 6){
		return true;
	} else if(x == 12 and y == 12){
		return true;
	} else if(x == 12 and y == 18){
		return true;
	} else if(x == 18 and y == 6){
		return true;
	} else if(x == 18 and y == 12){
		return true;
	}
	return false;
}

int valueCong(int x, int y, char atual){
		if(!have(x, y)) return 0;
	int aa = 0, bb = 0;
	if(atual == '^'){
		while(have(x - aa, y)) aa++;
	} else if(atual == '>'){
		while(have(x, y + aa)) aa++;
	} else if(atual == '<'){
		while(have(x, y - aa)) aa++;
	} else {
		while(have(x + aa, y)) aa++;
	}
	return aa;
}

void congestionamentoCount(){
	//VertHori = false, vertical aberto, = true, horizontal aberto
	vector< pair< ii , int > > congAtual;
		for(int i=0;i<19;i++){
			for(int j=0;j<19;j++){
				int conta = -1;
				if(i == 0 and j== 6){
					if(!VertHori) conta = valueCong(i, j+1, '>');
				} else if(i == 0 and  j== 12){
					if(!VertHori) conta = valueCong(i, j+1, '>');
				} else if(i == 6 and  j== 0){
					if(VertHori) conta = valueCong(i-1, j, '^');
				} else if(i == 6 and  j== 6){
					if(VertHori) conta = valueCong(i-1, j, '^');
					else conta = valueCong(i, j-1, '<');
				} else if(i == 6 and  j== 12){
					if(VertHori) conta = valueCong(i+1, j, 'v');
					else conta = valueCong(i, j-1, '<');					
				} else if(i == 6 and  j== 18){
					if(VertHori) conta = valueCong(i+1, j, 'v');
					else conta = valueCong(i, j-1, '<');
				} else if(i == 12 and j == 0){
					if(VertHori) conta = valueCong(i-1, j, '^');
					else conta = valueCong(i, j+1, '>');
				} else if(i == 12 and j == 6){
					if(VertHori) conta = valueCong(i-1, j, '^');
					else conta = valueCong(i, j+1, '>');
				} else if(i == 12 and j == 12){
					if(VertHori) conta = valueCong(i+1, j, 'v');
					else conta = valueCong(i, j+1, '>');
				} else if(i == 12 and j == 18){
					if(VertHori) conta = valueCong(i+1, j, 'v');
				} else if(i == 18 and j == 6){
					if(VertHori) conta = valueCong(i-1, j, '^');
					else conta = valueCong(i, j-1, '<');
				} else if(i == 18 and j == 12){
					if(!VertHori) conta = valueCong(i, j-1, '<');
				} 

				if(conta != -1){
					congAtual.pb({{i, j}, conta});
				}
			}
		}

		congestionamento.pb(congAtual);
}

void checkCongestionamento(){
	congestionamentoCount();
	if(sz(congestionamento[sz(congestionamento)-1]) != 0){
		cout << " ---- " << endl;
		cout << "Sinal - Quantidade de Carros" << endl;
		for(int i=0;i<sz(congestionamento[sz(congestionamento)- 1]);i++){
			cout << congestionamento[sz(congestionamento) - 1][i].F.F
			<< " - " << congestionamento[sz(congestionamento) - 1][i].F.S << " : "
			<<  congestionamento[sz(congestionamento) - 1][i].S << endl;
		}
	}
}

int main(){	
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	qtCarros = 5;
	haveCar = qtCarros;

	init(haveCar);
	cout << "Count : " << c << endl;
	cout << "Mapa : " << endl;
	for(int i=0;i<19;i++) cout << vec[i] << endl;
	VertHori = false;
	openVert();

	while(haveCar and iteracoes <= 1000){
		nextTime();
		cout << "Tempo : " << tempo << endl;
		cout << "HaveCar : " << haveCar << endl;
		cout << "Sinal : " << (VertHori == false ? "Vertical" : "Horizontal") << endl;

		checkCongestionamento();

		for(int i=0;i<19;i++){
			for(int j=0;j<19;j++){
				if(have(i, j)) cout << 'a';
				else cout << vec[i][j];
			} cout << endl;
		}
		cout << endl;
		iteracoes++;
	}

	return 0;
}

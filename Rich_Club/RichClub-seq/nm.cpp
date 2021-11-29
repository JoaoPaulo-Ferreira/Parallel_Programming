#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <sys/time.h>
#include <vector>
#include <list>
using namespace std;

double coefficient_richClub(int, int );

int main(int argc, char const **argv){
	if(argc < 2){
		fprintf(stderr, "\tMissing filename\n %s <filename>\n", argv[0]);
		exit(1);
	}

	// LENDO ARQUIVO E CRIANDO MATRIZ DE ADJACÊNCIA
	ifstream infile(argv[1]);
	string input;
	int vertex, edge, node_A, node_B,  k_max=0, nEdges, rc_size;
	double rc_coef;
	struct timeval t1, t2;
	infile >> vertex >> edge;
	vector<vector<int>> graph(vertex);
	vector<int> rich_club;

	// REPRESENTACAO DE LISTA DE ADJACENCIA
	/*
		Eu gosto da ideia do indice do vetor representar o vertice pois para verificar se existe uma aresta entre o nó i e o nó j
		posso verificar na lista de adjacencia do indice i (procurar j) ou na lista de adjacencia de j (procurar por i). Sem falar
		que o acesso ao vetor é imediato.
	
	*/


	// Lendo arquivo e preenchendo grafo
	while (infile >> node_A >> node_B){
		graph[node_A].push_back(node_B);
		graph[node_B].push_back(node_A);
	}
    gettimeofday(&t1, 0);
	
	// Calculo do Kmax
	for(int i = 0; i < vertex; i++){
		if((int ) graph[i].size() > k_max)
			k_max = graph[i].size();
	}


	vector<double> coefficients(k_max);
	// // CÁLCULO DO COEFICIENTE
	// /*
	// 	O clube dos ricos é novamente expresso por um vector que armazena os indices dos verticies do grafo.
	// 	Para cada k = 0  até kmax
	// 		percorre o clube dos ricos verificando quais dos números na sua lista de adjacencias também estão no clube dos ricos
	// */
	for (int k = 0; k < k_max; k++){
		nEdges = 0;
		rc_size = 0;

	// 	// Criando o rich club para o valor atual de k
		for(int j = 0; j < vertex; j++){ 
			if( (int) graph[j].size() > k)
				rich_club.push_back(j);
		}

		
		rc_size = rich_club.size(); // tamanho do rich club
		if(rc_size > 1){
			for (auto i = rich_club.begin(); i != rich_club.end(); i++){ // para cada elemento i no clube dos ricos 
				for(auto i_neigh = graph[*i].begin(); i_neigh != graph[*i].end(); i_neigh++){ // verifique quantas arestas i possui
					for(auto j = rich_club.begin(); j != rich_club.end(); j ++){ // com os demais membros do clube dos ricos
						if(*i_neigh == *j)
							nEdges++;
					}
				}
			}
			rc_coef = coefficient_richClub(nEdges, rc_size);
		}else{
			rc_coef = 1;
		}
		coefficients[k] = rc_coef;
		rich_club.resize(0);		
	}
	gettimeofday(&t2, 0);
	printf("It took %f milliseconds.\n",(t2.tv_sec - t1.tv_sec) + (t2.tv_usec - t1.tv_usec) / 1e6);

	// ESCREVENDO ARQUIVO DE SAIDA
	string filename = argv[1];
	filename = filename.substr(0, filename.find('.'));
	filename = filename + ".rcb";
	ofstream outfile;
	outfile.open(filename);
	outfile << fixed << setprecision(5);
	for (auto it = coefficients.begin(); it != coefficients.end(); it++)
		outfile <<" " << *it << endl;
	
	infile.close();
	outfile.close();

	return 0;
}

double coefficient_richClub(int nEdges, int nk){
	return (((double)1/(double)(nk*(nk-1))) * (double)nEdges);
}

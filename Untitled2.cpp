#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#define MAX 5
#define EMB 3

using namespace std;

typedef struct{

	string nome;
	int numeroJogadas = 0;
	int numeroEmbarcacoes = EMB;

} Jogador;

//O que faz: exibe o tabuleiro
//Parametros: matriz de char (por referencia)
//Retorno: nenhum
void mostrarTabuleiro(char tabuleiro[MAX][MAX]){
	cout << setw(43) << endl;
	for(int i = 0; i < MAX; i++){
		for(int j = 0; j < MAX; j++){
			cout << tabuleiro[i][j] << " ";
		}
		cout << setw(43) << endl;
	}
	cout << setw(30) << endl;
}

//O que faz: preenche o tabuleiro
//Parametros: matriz de char (por referencia)
//Retorno: nenhum
void preencheTabuleiro(char tabuleiro[MAX][MAX]){
	for(int i = 0; i < MAX; i++ ){
		for(int j = 0; j < MAX; j++ ){
			tabuleiro[i][j] = '#';
		}
	}
}

//O que faz: insere a embarcação no tabuleiro
//Parametros: matriz de char (por referencia), inteiros i e j (por valor)
//Retorno: nenhum
void inserirEmbarcacoes(char tabuleiro [MAX][MAX], int i, int j){
	tabuleiro[i][j] = 's';
}

//O que faz: Verifica se a posição que o usuário digitou é valida
//Parametros: matriz de char (por referencia), inteiros i e j (por valor)
//Retorno: retorna 0 caso a posicao esteja disponivel e 1 caso nao
int checarPosicao(char tabuleiro [MAX][MAX], int i, int j){
	if((i < MAX) && (j < MAX )){
		if (tabuleiro[i][j] != '#'){
			cout << setw(60) << "Posiçao já ocupada" << endl;
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		system("clear");
		cout << setw(60) << "Insira valores entre 0 e " << MAX << endl;
		return 1;
	}

}

//O que faz: avalia se o disparo  acertou alguma embarcação, marca nas matriz a coordenada do disparo
//de acordo com a efetividade do disparo, marca na matriz auxiliar a coordenada do disparo, incrementa
//o numero de jogadas e caso o disparo tenha sido certeiro decrementa o numero de embarcacoes do adversario.
//Parametros: 2 matrizes de char (por referencia), inteiros i e j (por valor) e
//duas variaveis do tipo jogador (por referencia usando ponteiros)
//Retorno: sem retorno
void atirar(char tabuleiro [MAX][MAX], char tabuleiro1 [MAX][MAX], Jogador *jogador1, Jogador *jogador2, int i, int j){
	if(tabuleiro[i][j] == 's'){
		tabuleiro1[i][j] = '$';
		jogador2->numeroEmbarcacoes--;
		jogador1->numeroJogadas++;
	}
	else{
		tabuleiro1[i][j] = '*';
		jogador1->numeroJogadas++;
	}

}

//O que faz: verifica se a partida acabou de acordo com o numero de embarcações do jogador
//Parametros: jogador do tipo Jogador (por referencia)
//Retorno: retorna 0 caso não restem mais embarcações, retorna 1 caso ainda restem embarcações.
int checarVitoria(Jogador jogador){
	if(jogador.numeroEmbarcacoes == 0){
		return 0;
	}
	else
		return 1;
}

//O que faz: atualiza o ranking de acordo com o numero de jogadas efetuadas, quanto menas jogadas
//mais alta a posição no ranking
//Parametros: struct ranking do tipo jogador (por referencia usando ponteiros), inteiros i (por valor)
//Retorno: nenhum
void AtualizaRanking(Jogador *ranking, int i){
	Jogador aux;
	for(int j = 0; j < i; j++){
		for(int k = j+1; k < i; k++){
			if(ranking[j].numeroJogadas > ranking[k].numeroJogadas){
				aux = ranking[j];
				ranking[j] = ranking[k];
				ranking[k] = aux;
			}
		}
	}
}

//O que faz: exibe o ranking
//Parametros: struct ranking do tipo jogador (por referencia usando ponteiros) e indice (por valor)
//Retorno: nenhum
void MostraRanking(Jogador *ranking, int indice){
	if(indice > 0){
		cout << "Posição" << setw(20) << "Nome do jogador" << setw(30) << "Numero de jogadas " << endl;
		for(int i = 0; i < indice; i++){
			cout << i + 1 << "º " << setw(20) << ranking[i].nome << setw(20) << ranking[i].numeroJogadas << endl;
		}
	}
	else{
		cout << setw(53) << "Ranking Vazio" << endl;
	}
	cout << endl;
}

//O que faz: preenche o ranking
//Parametros: struct jogador do tipo Jogador (por referencia)  e struct ranking do tipo jogador
//(por referencia usando ponteiro)
//Retorno: nenhum
void PreencheRanking(Jogador jogador, Jogador *ranking){
	ranking->nome = jogador.nome;
	ranking->numeroJogadas = jogador.numeroJogadas;
}

//O que faz: reseta os valores dos paramentros para que uma nova partida possa ser iniciada
//Parametros: 2 structs jogador do tipo Jogador (por referencia usando ponteiro) e os elementos inteiros
// i , j, k, col, lin e menu (por referencia usando ponteiro)
//Retorno: nenhum
void Reset(Jogador *jogador1, Jogador *jogador2, int *i, int *j, int *k, int *l, int *col, int *lin, int *menu){
	jogador1->nome = "";
	jogador1->numeroEmbarcacoes = EMB;
	jogador1->numeroJogadas = 0;
	jogador2->nome = "";
	jogador2->numeroEmbarcacoes = EMB;
	jogador2->numeroJogadas = 0;
	*i = 0;
	*j = 0;
	*k = 1;
	*l = 1;
	*col = 0;
	*lin = 0;
}

//O que faz: verifica a coordenada inserida pelo computador para evitar disparos sucessivos na mesma posição
//Parametros: tabuleiro do tipo matriz de char (por referencia) e lin e col do tipo inteiro (por valor)
//Retorno: retorna 1 caso ja tenha sido disparado na respectiva coordenada e retorna 0 caso não
int ChecarPosComputador(char tabuleiro[MAX][MAX], int lin, int col){
	if(tabuleiro[lin][col] == '*'){
		return 1;
	}
	else
		return 0;

}

//O que faz: reseta os valores dos paramentros para evitar lixo de memoria nas proximas jogadas
//Parametros: os elementos inteiros
// i , j, k, col, lin (por referencia usando ponteiro)
//Retorno: nenhum
void Reset2(int *i, int *j, int *k, int *l, int *col, int *lin){
	*i = 0;
	*j = 0;
	*k = 1;
	*l = 1;
	*col = 0;
	*lin = 0;
}

int main(){
	Jogador jogador1;
	Jogador jogador2;
	Jogador ranking [100];
	char tabuleiro[MAX][MAX];
	char tabuleiro2[MAX][MAX];
	char tabuleiroaux[MAX][MAX];
	char tabuleiroaux2[MAX][MAX];
	char confirmacao;
	int i = 0, j = 0, k = 1, l = 1, lin = 0, col = 0, menu = 0, indice = 0;

	do{
		cout << setw(60)<<"Selecione uma opção: "<< endl;
		cout << endl;
		cout << setw(50)<<"1 Player x Player" << endl;
		cout << endl;
		cout << endl;
		cout << setw(42)<<"2 Ranking" << endl;
		cout << endl;
		cout << endl;
		cout << setw(48)<<"3 Player x Comp" << endl;
		cout << endl;
		cout << endl;
		cout << setw(45)<<"4 Instrucoes" << endl;
		cout << endl;
		cout << endl;
		cout << setw(39)<<"5 Sair" << endl;
		cin >> menu;
		system("clear");

		switch(menu){

		case 1:

			cout << setw(60) << "JOGADOR 1 INSIRA SEU NOME: " << setw(52) << endl;
			cin >> jogador1.nome;
			cout << "Tabuleiro de " << jogador1.nome << setw(43) << endl;

			preencheTabuleiro(tabuleiro);
			preencheTabuleiro(tabuleiroaux);
			mostrarTabuleiro(tabuleiro);

			for(int n = 0; n < EMB; n++){
				do {
					Reset2(&i, &j, &k, &l, &lin, &col);
					cout << setw(30) << jogador1.nome << " insira as coordenadas da embarcação " << setw(43) << endl;
					cin >> i;
					cin >> j;
					k = checarPosicao(tabuleiro, i, j);
				}while (k != 0);

				inserirEmbarcacoes(tabuleiro, i, j);
				mostrarTabuleiro(tabuleiro);
			}

			system("clear");

			cout << setw(60)<<"JOGADOR 2 INSIRA SEU NOME: " << endl;
			cin >> jogador2.nome;
			cout << setw(50) << "Tabuleiro de " << jogador2.nome << setw(50) << endl;

			preencheTabuleiro(tabuleiro2);
			preencheTabuleiro(tabuleiroaux2);
			mostrarTabuleiro(tabuleiro2);

			for(int n = 0; n < EMB; n++){
				do {
					Reset2(&i, &j, &k, &l, &lin, &col);
					cout << setw(30) << jogador2.nome << " insira as coordenadas da embarcação " << endl;
					cin >> i;
					cin >> j;
					k = checarPosicao(tabuleiro2, i, j) ;
				}while (k != 0);

				inserirEmbarcacoes(tabuleiro2, i, j);
				mostrarTabuleiro(tabuleiro2);
			}
			system("clear");
			Reset2(&i, &j, &k, &l, &lin, &col);
			do{
				cout << jogador1.nome << " insira as coordenadas do seu disparo " << endl;
				cin >> lin >> col;
				atirar(tabuleiro2, tabuleiroaux2, &jogador1, &jogador2 , lin, col);
				cout << setw(50) << " Tabuleiro auxiliar de " << jogador1.nome << endl;
				mostrarTabuleiro(tabuleiroaux2);
				cout << endl;
				cout << endl;
				if(checarVitoria(jogador2) == 0){
					do{
						system("clear");
						cout << endl;
						cout << endl;
						cout << endl;
						cout << endl;
						cout << setw(45) << jogador1.nome << " Venceu" << endl;
						cout << endl;
						cout << endl;
						cout << endl;
						cout << endl;
						PreencheRanking(jogador1, &ranking[indice]);
						indice++;
						Reset(&jogador1, &jogador2, &i, &j, &k, &l, &lin, &col, &menu);
						cout << "Digite Q para voltar ao menu " << endl;
						cin >> confirmacao;
					}while(confirmacao != 'Q');
					confirmacao = 0;
					system("clear");
					break;
				}
				Reset2(&i, &j, &k, &l, &lin, &col);

				cout << jogador2.nome << " insira as coordenadas do seu disparo " << endl;
				cin >> lin >> col;
				atirar(tabuleiro, tabuleiroaux, &jogador2, &jogador1, lin, col);
				cout << setw(50) << " Tabuleiro auxiliar de " << jogador2.nome << endl;
				mostrarTabuleiro(tabuleiroaux);
				cout << endl;
				cout << endl;
				if(checarVitoria(jogador1) == 0){
					do{
						system("clear");
						cout << endl;
						cout << endl;
						cout << endl;
						cout << endl;
						cout << jogador2.nome << " Venceu" << endl;
						cout << endl;
						cout << endl;
						cout << endl;
						cout << endl;
						PreencheRanking(jogador2, &ranking[indice]);
						indice++;
						Reset(&jogador1, &jogador2, &i, &j, &k, &l, &lin, &col, &menu);
						cout << jogador2.nome << " Venceu" << endl;
						cout << "Digite Q para voltar ao menu " << endl;
						cin >> confirmacao;
					}while(confirmacao != 'Q');
					confirmacao = 0;
					system("clear");
					break;
				}
				Reset2(&i, &j, &k, &l, &lin, &col);

			}while((checarVitoria(jogador1) != 0) || (checarVitoria(jogador2) != 0));

			break;

		case 2:
			do{
				system("clear");
				AtualizaRanking(ranking, indice);
				MostraRanking(ranking, indice);
				cout << "Digite Q para voltar ao menu "<<endl;
				cin >> confirmacao;
			}while(confirmacao != 'Q');
			confirmacao = 0;
			system("clear");
			break;

		case 3:
			Reset2(&i, &j, &k, &l, &lin, &col);
			srand(time(NULL));

			cout << setw(60) << "JOGADOR 1 INSIRA SEU NOME: " << setw(52) << endl;
			cin >> jogador1.nome;
			cout << "Tabuleiro de " << jogador1.nome << setw(43) << endl;

			preencheTabuleiro(tabuleiro);
			preencheTabuleiro(tabuleiroaux);
			mostrarTabuleiro(tabuleiro);

			for(int n = 0; n < EMB; n++){
				do {
					cout << setw(40) << jogador1.nome<<" insira as coordenadas da embarcação " << setw(43) << endl;
					cin >> i;
					cin >> j;
					k = checarPosicao(tabuleiro, i, j) ;
				}while (k != 0);
				inserirEmbarcacoes(tabuleiro, i, j);
				mostrarTabuleiro(tabuleiro);
			}
			system("clear");
			jogador2.nome = "Computador";

			preencheTabuleiro(tabuleiro2);
			preencheTabuleiro(tabuleiroaux2);
			Reset2(&i, &j, &k, &l, &lin, &col);

			for(int n = 0; n < EMB; n++){
				do {
					i = rand() % (MAX - 1);
					j = rand() % (MAX - 1);
					k = checarPosicao(tabuleiro2, i, j) ;
				}while (k != 0);
				inserirEmbarcacoes(tabuleiro2, i, j);
			}

			do{
				Reset2(&i, &j, &k, &l, &lin, &col);

				cout << setw(30) << jogador1.nome << " insira as coordenadas do seu disparo " << endl;
				cin >> lin >> col;

				atirar(tabuleiro2, tabuleiroaux2, &jogador1, &jogador2 , lin, col);
				mostrarTabuleiro(tabuleiroaux2);
				cout << endl;
				cout << endl;
				if(checarVitoria(jogador2) == 0){
					do{
						system("clear");
						cout << endl;
						cout << endl;
						cout << endl;
						cout << endl;
						cout << setw(52) << jogador1.nome << " Venceu" << endl;
						cout << endl;
						cout << endl;
						cout << endl;
						cout << endl;
						PreencheRanking(jogador1, &ranking[indice]);
						indice++;
						Reset(&jogador1, &jogador2, &i, &j, &k, &l, &lin, &col, &menu);
						cout << "Digite Q para voltar ao menu "<<endl;
						cin >> confirmacao;
					}while(confirmacao != 'Q');
					confirmacao = 0;
					system("clear");
					break;
				}
				Reset2(&i, &j, &k, &l, &lin, &col);

				cout << setw(50) << "Computador" << endl;

				do{
					lin = rand() % (MAX - 1);
					col = rand() % (MAX - 1);
					l = ChecarPosComputador(tabuleiroaux, lin, col);
				}while( l != 0);

				atirar(tabuleiro, tabuleiroaux, &jogador2, &jogador1, lin, col);
				mostrarTabuleiro(tabuleiroaux);
				cout << endl;
				cout << endl;
				if(checarVitoria(jogador1) == 0){
					do{
						system("clear");
						cout << endl;
						cout << endl;
						cout << endl;
						cout << endl;
						cout << jogador2.nome << " Venceu" << endl;
						cout << endl;
						cout << endl;
						cout << endl;
						cout << endl;
						PreencheRanking(jogador2, &ranking[indice]);
						indice++;
						Reset(&jogador1, &jogador2, &i, &j, &k, &l, &lin, &col, &menu);
						cout << "Digite Q para voltar ao menu " << endl;
						cin >> confirmacao;
					}while(confirmacao != 'Q');
					confirmacao = 0;
					system("clear");
					break;
				}
			}while((checarVitoria(jogador1) != 0) || (checarVitoria(jogador2) != 0));
			break;

		case 4:
			system("clear");
			do{
				cout << setw(60) << "Bem vindo ao Batalha Naval" << endl;
				cout << endl;
				cout << endl;
				cout << setw(48) << "Objetivo: " << endl;
				cout << endl;
				cout << setw(70) << "O objetivo do jogo é afundar as embarcacoes adversarias " << endl;
				cout << endl;
				cout << setw(50) << "Como jogar: " << endl;
				cout << endl;
				cout << "    Comece o jogo escolhendo entre jogar contra o computador ou um amigo" << endl;
				cout << endl;
				cout << "em seguida adote uma estratégia para posicionar as embarcacoes, primeiro" << endl;
				cout << endl;
				cout << "coloque a linha e depois a coluna nas quais deseja posicionar sua embarcacao" << endl;
				cout << endl;
				cout << "o programa nao possibilita a colocacao de duas embarcacoes na mesma " << endl;
				cout << endl;
				cout << "posicao portanto fique atento as posicoes disponiveis. " << endl;
				cout << endl;
				cout << "   Apos isso sera solicitado as coordenadas nas quais voce deseja disparar " << endl;
				cout << endl;
				cout << "segue o mesmo modelodo posicionamento das embarcacoes, primeiro a linha " << endl;
				cout << endl;
				cout << "e depois a coluna, apos cada disparo é disponibilizado um tabuleiro auxiliar " << endl;
				cout << endl;
				cout << "para ajudar na tomada de decisao"<<endl;
				cout << endl;
				cout << "O jogo termina quando um dos jogadores afundar as embarcacoes do adversario " << endl;
				cout << endl;
				cout << "Bom Jogo, e boa sorte " << endl;
				cout << endl;
				cout << "Digite Q para voltar ao menu " << endl;
				cin >> confirmacao;
				system("clear");
			}while(confirmacao != 'Q');
			confirmacao = 0;
			system("clear");
			break;
		}

	}while(menu != 5);
}





#include <iostream>
using namespace std;

class no {
	public:
		string nome;
		int nId;
		int prioridade;
		no* anterior;
		no* proximo;

		no () {
			nome = "";
			nId = -1;
			prioridade = -1;
			anterior = NULL;
			proximo = NULL;

		}

		no (string n, int id, int priori){
			nome = n;
			nId = id;
			prioridade = priori;
			anterior = NULL;
			proximo = NULL;

		}
};

class lista{
	public:
		no* inicio;

		lista () {
			inicio = NULL;
		}

		no* busca (int priori) {
			no* aux; //Nó para percorrer a lista na busca
			no* ultimo = inicio->anterior; //Nó setado no anterior do primeiro, para ser lista circular
			if (priori >= ultimo->prioridade) { //Caso a prioridade do cliente a ser inserido seja maior ou igual do que a do final da fila, faz a busca por um elemento menor, caso não, insere no final da lista automaticamente
				aux = inicio;
				while (aux->prioridade >= priori) {
					aux = aux->proximo;
				}

				return aux;
			}

			else
				return inicio;
		}

		void InsereCliente (string n, int id, int priori) {
			if (inicio == NULL) //Caso não hajam elementos na função na lista, insere diretamente (Evitar segmentation fault na busca)
				inicio = new no(n, id, priori);

			else if (inicio->anterior == NULL) { //Caso só haja um elemento, insere direto na lista, de acordo com a prioridade (também evitar segmentation fault na busca)
				no* aux = new no(n, id, priori);
				aux->anterior = inicio;
				aux->proximo = inicio;
				inicio->anterior = aux;
				inicio->proximo = aux;
				if (priori > inicio->prioridade)
					inicio = aux;
			}

			else {
				no* pontEncontrado = busca(priori); // sucessor do elemento a ser inserido
				no* ant = pontEncontrado->anterior; // anterior do elemento a ser inserido
				no* aux = new no(n, id, priori); //criação do nó do elemento a ser inserido
				aux->anterior = ant; //ponteiro anterior do novo nó setado para seu antecessor
				aux->proximo = pontEncontrado; //ponteiro sucessor do novo nó setado para seu sucessor
				ant->proximo = aux; //ponteiro para o próximo elemento anterior ao nó setado para o nó
				pontEncontrado->anterior = aux; //ponteiro para o elemento anterior ao nó setado para o nó
				if (priori > inicio->prioridade) //se a prioridade do elemento inserido for maior que o do início, seta o início para o novo nó
					inicio = aux;

			}

		}

		void removeElemento () {
			if (inicio == NULL)
				cout << "Fila vazia" << endl;
			else {
				cout << "Próximo a ser atendido: " << inicio->nome << " Identificação: " << inicio->nId << endl;
			
			no* aux = inicio;

				if (inicio->proximo != NULL) {
					no* ant = aux->anterior;
					no* prox = aux -> proximo;

					inicio = prox;
				
					if (ant != prox) { //Caso haja mais de 2 elementos na fila, faz o processo nromal de mudança de referências
						ant->proximo = inicio;
						inicio->anterior = ant;
					}
					else { //Caso haja só 2 elementos na fila, garante que o anterior e o próximo o nó que ficará na fila não apontem para ele mesmo
						inicio->anterior = NULL;
						inicio->proximo = NULL;
					}
					delete aux;
		
				} 

				else { //Caso só haja um nó na fila, faz com que o início seja nulo e não dê segmentation fault
					delete aux;
					inicio = NULL;
				}

			}
			
				

		}

};


int main() {
	lista listaEspera; 
  string nome;
	int id = 0;
	int prioridade;
	bool continuar = true;
	char lerId;
	int escolha;
	char cont;
	while (continuar) {
		cout << "Digite o que deseja fazer: 1 - inserir cliente na fila, 2 - chamar próximo cliente a ser atendido" << endl;
		cin >> escolha;
		if (escolha == 2)
			listaEspera.removeElemento();
		else {
			cout << "Digite o nome do cliente" << endl;
			cin.ignore();
			getline(cin, nome);
			cout << "Deseja digitar o número de identificação do cliente manualmente? [S/N]" << endl;
			cin >> lerId; //Avalia se o número de Id vai ser digitado ou gerado pelo computador
			if (lerId == 'S' || lerId == 's') {
				cout << "Digite o número de identificação do cliente" << endl;
				cin >> id;
			}
			else
				id++; //Caso o Id seja informado pelo sistema, faz com que o número seja o do cliente anterior +1

			cout << "Informe a prioridade do cliente (1 a 3)" << endl;
			cin >> prioridade;
			listaEspera.InsereCliente(nome, id, prioridade);

		}

		cout << "Deseja continuar [S/N]?" << endl;
		cin >> cont;
		if (cont == 'n' || cont == 'N')
			continuar = false;
	}
}
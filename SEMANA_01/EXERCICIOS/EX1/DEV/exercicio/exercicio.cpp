#include <iostream>
#include <string>
using namespace std;
// 1 -  Faça uma função que recebe uma certa medida e ajusta ela percentualmente
// entre dois valores mínimo e máximo e retorna esse valor
double converteSensor(double val, double minVal, double maxVal) {
	double percentual;
	percentual = (val - minVal) / (maxVal - minVal);

	return percentual * 100;
}

// 2 - Faça uma função que simule a leitura de um sensor lendo o
// valor do teclado ao final a função retorna este valor
int lerMedida(string direcao) {
	int numero;
	cout << "Digite uma medida para o sensor " << direcao << ": ";
	cin >> numero;
	return numero;
}

// 3 - Faça uma função que armazena uma #medida inteira# qualquer
// em um #vetor fornecido. Note que como C não possui vetores
// nativos da linguagem, lembre-se que você precisa passar o
// valor máximo do vetor# assim como a última posição# preenchida
// Evite também que, por acidente, um valor seja escrito em
// uma área de memória fora do vetor
int insereEmVetor(int val, int* vetor, int tamanho, int posicao) {
	if (posicao < tamanho) { // verifica se é posivel inserir 
		vetor[posicao] = val;  // enfia no vetor global
		return posicao + 1;      // retorna a proxima posição
	}
	return posicao;          // posicao inaltera
}

// 4 - Faça uma função que recebe um "vetor" com 4 posições que contém
// o valor da distância de um pequeno robô até cada um dos seus 4 lados.
// A função deve retornar duas informações: A primeira é a direção
// de maior distância ("Direita", "Esquerda", "Frente", "Tras") e a
// segunda é esta "maior distância".
const char* direcaoMenorCaminho(int* vetor, int *distancia) {
	int maiorDistancia = 0;
	int sentido = 0;

	const char* sentidos[] = { "Direita", "Esquerda", "Frente", "Tras" };

	for (int i = 0; i < 4; i++) {
		if (vetor[i] > maiorDistancia) {
			maiorDistancia = vetor[i];
			sentido = i;
		}
	}
	*distancia = maiorDistancia;
	return sentidos[sentido];

}


// 5 - Faça uma função que pergunta ao usuário se ele deseja continuar o
// mapeamento e retorna verdadeiro ou falso
bool leComando() {
	char resposta;

	cout << "Quer continuar? (S/N) " << endl;
	cin >> resposta;

	if (toupper(resposta) == 'N') {
		return false;
	}
	return true;
}

// 6 - A função abaixo (que está incompleta) vai "dirigindo" virtualmente um
// robô e através de 4 sensores em cada um dos 4 pontos do robo ("Direita",
// "Esquerda", "Frente", "Tras").
//      A cada passo, ele verifica as distâncias aos objetos e vai mapeando o
//      terreno
// para uma movimentação futura.
//      Ele vai armazenando estas distancias em um vetor fornecido como
//      parâmetro
// e retorna a ultima posicao preenchida do vetor.
//      Esta função deve ir lendo os 4 sensores até que um comando de pare seja
//      enviado
//
//      Para simular os sensores e os comandos de pare, use as funções já
//      construídas
// nos ítens anteriores e em um looping contínuo até que um pedido de parada
// seja enviado pelo usuário.
//
//      Complete a função com a chamada das funções já criadas
int dirige(int* vetor, int tamanho) {
	int posAtualVetor = 0;
	bool dirigindo = true;

	while (dirigindo == true) {

		string sentidos[] = { "Direita", "Esquerda", "Frente", "Tras" };

		// leitura dos sensores
		for (int i = 0; i < 4; i++) { // pra cada sensor que existe:
			int medida = lerMedida(sentidos[i]);         // le o valor
			int medidaConvertida = converteSensor(medida, 0, 830); // converte o valor
			posAtualVetor = insereEmVetor(
				medidaConvertida, vetor, tamanho,
				posAtualVetor); // muda a posição atual E altera o vetorMov
		}

		dirigindo = leComando(); // verifica se quer continaur mapeando
	}
	return posAtualVetor;
}

// O trecho abaixo irá utilizar as funções acima para ler os sensores e o
// movimento do robô e no final percorrer o vetor e mostrar o movimento a cada
// direção baseado na maior distância a cada movimento
void percorre(int* vetor, int tamPercorrido) {
	int maiorDir = 0;

	for (int i = 0; i < tamPercorrido; i += 4) {
		const char* direcao = direcaoMenorCaminho(&(vetor[i]), &maiorDir);
		cout << "Movimento " << maiorDir << " para a direção " << direcao << ". \n";
	}
}

int main(int argc, char** argv) {
	const int maxVetor = 100;         // declara o tamanho do vetor
	int vetorMov[maxVetor * 4]; // cria um vetor com 400 posições (tudo é 0)
	int posAtualVet = 0;

	posAtualVet = dirige(vetorMov, maxVetor); // volto 4
	percorre(vetorMov, posAtualVet);

	return 0;
}
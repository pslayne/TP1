#include <iostream>
#include <iomanip>
#include "cripto.h"
#include "simd.h"
using namespace std;

//função principal
int main() {

	//mudando código de página
	system("chcp 1252 > nul");

	//dados recebidos do usuário
	int a, b, c, d, e, f, g, h;
	char ch;
	cin.ignore();
	cin >> a;
	cin.ignore();
	cin >> b;
	cin.ignore();
	cin >> c;
	cin.ignore();
	cin >> d;
	cin.ignore();
	//ao colocar dois cin.ignore() só um é reconhecido, então um dos colchetes foi armazenado em uma variável char
	cin >> ch;
	cin >> e;
	cin.ignore();
	cin >> f;
	cin.ignore();
	cin >> g;
	cin.ignore();
	cin >> h;
	cin.ignore();

	//foi usado \n em toda a função para separar as saídas
	cout << "\n";

	//usando a função armazena() os 8 valores recebidos do usário foram colocados, em grupos de 4, em blocos de 32 bits 
	int numero_1 = armazena(a, b, c, d);
	int numero_2 = armazena(e, f, g, h);
	//saída dos números de 32 bits
	cout << "Operandos em 32 bits = " << numero_1 << endl;
	cout << "Operandos em 32 bits = " << numero_2 << endl;

	cout << "\n";

	//usando as funções soma() e multiplicacao() foram realizadas as operações dos números recebidos, dois a dois, e armazenadas em blocos de 32 bits
	int som = soma(numero_1, numero_2);
	int mult = multiplicacao(numero_1, numero_2);
	//saída dos resultados
	cout << "Soma em 32 bits = " << som << endl;
	cout << "Multiplicação em 32 bits = " << mult << endl;

	cout << "\n";
	
	//usando as funções de separação, foram separados os resultados da operação individuais
	int som_1 = primeiro(som), som_2 = segundo(som), som_3 = terceiro(som), som_4 = quarto(som);
	int mult_1 = primeiro(mult), mult_2 = segundo(mult), mult_3 = terceiro(mult), mult_4 = quarto(mult);

	//saída dos resultados
	cout << "[";
	//para que as saídas seja no padrão '000', foram usadas as funções setw(), define quantos caracteres deve ter a saída, e setfill(), 
	//define como preencher os espaços em branco
	cout << setfill('0') << setw(3) << som_1; cout << ",";
	cout << setfill('0') << setw(3) << som_2; cout << ",";
	cout << setfill('0') << setw(3) << som_3; cout << ",";
	cout << setfill('0') << setw(3) << som_4; cout << "] = Somas" << endl;
	cout << "[";
	cout << setfill('0') << setw(3) << mult_1; cout << ",";
	cout << setfill('0') << setw(3) << mult_2; cout << ",";
	cout << setfill('0') << setw(3) << mult_3; cout << ",";
	cout << setfill('0') << setw(3) << mult_4; cout << "] = Multiplicações" << endl;

	cout << "\n";
	
	//codifica os valores de 32 bits da soma e da multiplicação
	long long soma_cripto = codificar(som);
	long long mult_cripto = codificar(mult);
	//saída
	cout << "Soma Cripto 64 bits = " << soma_cripto << endl;
	cout << "Mult Cripto 64 bits = " << mult_cripto << endl;

	cout << "\n";
	
	//decodifica a soma
	int soma_dcripto = decodificar(soma_cripto);

	//separara, do retorno de codificar(), o numero codificado e as posicoes que foram alteradas
	long long mascara = 4294967295;
	int masc = 31, soma_codificada, posicoes_soma, s1, s2, s3, s4, s5, s6;

	posicoes_soma = (soma_cripto & mascara);
	soma_codificada = (soma_cripto >> 32);

	s1 = (posicoes_soma & (masc << 27));
	s1 = (s1 >> 27);
	s2 = (posicoes_soma & (masc << 22));
	s2 = (s2 >> 22);
	s3 = (posicoes_soma & (masc << 17));
	s3 = (s3 >> 17);
	s4 = (posicoes_soma & (masc << 12));
	s4 = (s4 >> 12);
	s5 = (posicoes_soma & (masc << 7));
	s5 = (s5 >> 7);
	s6 = (posicoes_soma & (masc << 2));
	s6 = (s6 >> 2);

	//saída dos resultados
	cout << "Valor Codificado = " << soma_codificada << " (" << s1 << " " << s2 << " " << s3 << " " << s4 << " " << s5 << " " << s6 << ")" << endl;
	cout << "Soma Decodificada = " << soma_dcripto << endl;

	cout << "\n";

	//decodifica a multiplicação
	int mult_dcripto = decodificar(mult_cripto);

	//separara, do retorno de codificar(), o numero codificado e as posicoes que foram alteradas
	int mult_codificada, posicoes_mult, m1, m2, m3, m4, m5, m6;

	posicoes_mult = (mult_cripto & mascara);
	mult_codificada = (mult_cripto >> 32);

	m1 = (posicoes_mult & (masc << 27));
	m1 = (m1 >> 27);
	m2 = (posicoes_mult & (masc << 22));
	m2 = (m2 >> 22);
	m3 = (posicoes_mult & (masc << 17));
	m3 = (m3 >> 17);
	m4 = (posicoes_mult & (masc << 12));
	m4 = (m4 >> 12);
	m5 = (posicoes_mult & (masc << 7));
	m5 = (m5 >> 7);
	m6 = (posicoes_mult & (masc << 2));
	m6 = (m6 >> 2);

	//saída dos resultados
	cout << "Valor Codificado = " << mult_codificada << " (" << m1 << " " << m2 << " " << m3 << " " << m4 << " " << m5 << " " << m6 << ")" << endl;
	cout << "Multiplicação Decodificada = " << mult_dcripto << endl;
}
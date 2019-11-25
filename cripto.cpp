#include <random>
#include <iostream>
using namespace std;

//função que transforma determinado bit de valor 0 em 1
int ligarBit(int estado, int i) {
	int mascara = 1 << i;
	return (estado | mascara);
}

//função que transforma determinado bit de valor 1 em 0
int desligarBit(int estado, int i) {
	int mascara = ~(1 << i);
	return (estado & mascara);
}

//função que descobre se o bit é 1 ou 0
bool testarBit(int estado, int i) {
	int mascara = 1 << i;
	if (estado & mascara) {
		return true;
	}
	else {
		return false;
	}
}

//função que codifica um valor transformando 6 bits em posições aleatórias e guardando essas posições.
long long codificar(int x) {

	//gera número pseudo-aleatório
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> dist(0, 31);
	
	bool escolha;
	int position_1, position_2, position_3, position_4, position_5, position_6;
	
	//usa os números pseudo-aleatórios para gerar as posições
	position_1 = dist(mt);
	//testa o bit
	escolha = testarBit(x, position_1);
	if (escolha == true) {
		//desliga se for 1
		x = desligarBit(x, position_1);
	}
	else {
		//liga se for 0
		x = ligarBit(x, position_1);
	}
	//se repete para as 6 posições

	position_2 = dist(mt);
	escolha = testarBit(x, position_2);
	if (escolha == true) {
		x = desligarBit(x, position_2);
	}
	else {
		x = ligarBit(x, position_2);
	}

	position_3 = dist(mt);
	escolha = testarBit(x, position_3);
	if (escolha == true) {
		x = desligarBit(x, position_3);
	}
	else {
		x = ligarBit(x, position_3);
	}

	position_4 = dist(mt);
	escolha = testarBit(x, position_4);
	if (escolha == true) {
		x = desligarBit(x, position_4);
	}
	else {
		x = ligarBit(x, position_4);
	}

	position_5 = dist(mt);
	escolha = testarBit(x, position_5);
	if (escolha == true) {
		x = desligarBit(x, position_5);
	}
	else {
		x = ligarBit(x, position_5);
	}

	position_6 = dist(mt);
	escolha = testarBit(x, position_6);
	if (escolha == true) {
		x = desligarBit(x, position_6);
	}
	else {
		x = ligarBit(x, position_6);
	}

	//insere o valor codificado e as posições em um valor de 64 bit
	long long resultado;

	resultado = 0;
	resultado = (resultado | x);
	resultado = (resultado << 32);
	resultado = (resultado | ((long long)position_1 << 27));
	resultado = (resultado | ((long long)position_2 << 22));
	resultado = (resultado | ((long long)position_3 << 17));
	resultado = (resultado | ((long long)position_4 << 12));
	resultado = (resultado | ((long long)position_5 << 7));
	resultado = (resultado | ((long long)position_6 << 2));
	
	//retorna o valor de 64 bits codificado
	return resultado;
}

int decodificar(long long x) {

	//valor correspondente ao número binário com 32 zeros e 32 uns
	long long mascara = 4294967295;
	int numero, posicoes, p1, p2, p3, p4, p5, p6;

	//separa o bloco que contém as posições
	posicoes = (x & mascara);

	//separa o bloco que contém o número codificado
	numero = (x >> 32);
	
	//valor correspondente á 11111
	int masc = 31;
	bool escolha;

	//separa a primeira posição
	p1 = (posicoes & (masc << 27));

	//ajusta a posição dos bits para o valor correto
	p1 = (p1 >> 27);
	
	//testa o bit nesta posição
	escolha = testarBit(numero, p1);
	if (escolha == true) {
		//desligar se for 1
		numero = desligarBit(numero, p1);
	}
	else {
		//liga se for 0
		numero = ligarBit(numero, p1);
	}
	//se repete para as demais posições

	p2 = (posicoes & (masc << 22));
	p2 = (p2 >> 22);

	escolha = testarBit(numero, p2);
	if (escolha == true) {
		numero = desligarBit(numero, p2);
	}
	else {
		numero = ligarBit(numero, p2);
	}

	p3 = (posicoes & (masc << 17));
	p3 = (p3 >> 17);
	
	escolha = testarBit(numero, p3);
	if (escolha == true) {
		numero = desligarBit(numero, p3);
	}
	else {
		numero = ligarBit(numero, p3);
	}

	p4 = (posicoes & (masc << 12));
	p4 = (p4 >> 12);
	
	escolha = testarBit(numero, p4);
	if (escolha == true) {
		numero = desligarBit(numero, p4);
	}
	else {
		numero = ligarBit(numero, p4);
	}

	p5 = (posicoes & (masc << 7));
	p5 = (p5 >> 7);
	
	escolha = testarBit(numero, p5);
	if (escolha == true) {
		numero = desligarBit(numero, p5);
	}
	else {
		numero = ligarBit(numero, p5);
	}

	p6 = (posicoes & (masc << 2));
	p6 = (p6 >> 2);
	
	escolha = testarBit(numero, p6);
	if (escolha == true) {
		numero = desligarBit(numero, p6);
	}
	else {
		numero = ligarBit(numero, p6);
	}

	//retorna o valor de 32 bits decodificado
	return numero;
}

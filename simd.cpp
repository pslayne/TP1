//função que armazena 4 valores de 8 bits em um bloco de 32 bits
int armazena(int n_1, int n_2, int n_3, int n_4) {
	
	//variável com todos os bits iguais a 0
	int a = 0;
	
	//utiliza-se a operação OR para armazenar os valores, deslocando os bits para que ele ocupem os espaços certos.
	a = (a | (n_1 << 24));
	a = (a | (n_2 << 16));
	a = (a | (n_3 << 8));
	a = (a | n_4);
	return a;
}

//função que retira o valor armazenado no primeiro bloco de 8 bits do bloco de 32 bits
int primeiro(int n) {
	int a = 255;
	int first;
	//utiliza-se a operação AND para que se percam os demais valores, zerando todos os outros bits a não ser os primeiros 8
	first = (n & (a << 24));
	return (first >> 24);
}

//função que retira o valor armazenado no segundo bloco de 8 bits do bloco de 32 bits
int segundo(int n) {
	int a = 255;
	int second;
	second = (n & (a << 16));
	return (second >> 16);
}

//função que retira o valor armazenado no terceiro bloco de 8 bits do blocos de 32 bits
int terceiro(int n) {
	int a = 255;
	int third;
	third = (n & (a << 8));
	return (third >> 8);
}

//função que retira o valor armazenado no quarto bloco de 8 bits do blocos de 32 bits
int quarto(int n) {
	int a = 255;
	int fourth;
	fourth = (n & a);
	return fourth;
}
//função que soma separadamente os valores de 8 bits e retorna um valor de 32 bits.
int soma(int x, int y) {

	//separa os valores através das funções já definidadas acima.
	int x_first = primeiro(x);
	int x_second = segundo(x);
	int x_third = terceiro(x);
	int x_fourth = quarto(x);

	int y_first = primeiro(y);
	int y_second = segundo(y);
	int y_third = terceiro(y);
	int y_fourth = quarto(y);

	int soma_first = (x_first + y_first);
	int soma_second = (x_second + y_second);
	int soma_third = (x_third + y_third);
	int soma_fourth = (x_fourth + y_fourth);

	//armazena utilizando a função existente.
	return armazena(soma_first, soma_second, soma_third, soma_fourth);
}

//função que multiplica separadamente os valores de 8 bits e retorna um valor de 32 bits.
int multiplicacao(int x, int y) {

	//separa os valores através das funções já definidadas acima.
	int x_first = primeiro(x);
	int x_second = segundo(x);
	int x_third = terceiro(x);
	int x_fourth = quarto(x);

	int y_first = primeiro(y);
	int y_second = segundo(y);
	int y_third = terceiro(y);
	int y_fourth = quarto(y);

	int mult_first = (x_first * y_first);
	int mult_second = (x_second * y_second);
	int mult_third = (x_third * y_third);
	int mult_fourth = (x_fourth * y_fourth);

	//armazena utilizando a função existente.
	return armazena(mult_first, mult_second, mult_third, mult_fourth);
}
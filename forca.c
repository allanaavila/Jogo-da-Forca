#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>

#define TAMANHO_PALAVRA 20

//assinatura das funcoes 
void abertura();
void chuta();
int jachutou(char letra);
void desenhaforca();
void escolhepalavra();
int acertou();
int enforcou();
void adicionapalavra();
void escolhepalavra();
int chuteserrados();
int letraexiste(char letra);


//variaveis globais
char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;

void abertura(){
	printf("******************************** \n");
	printf("**      Jogo de Forca         **\n");
	printf("******************************** \n\n");
}

void chuta() {
    char chute;
    printf("Qual letra? ");
    scanf(" %c", &chute);

    if(letraexiste(chute)) {
        printf("Você acertou: a palavra tem a letra %c\n\n", chute);
    } else {
        printf("\nVocê errou: a palavra NÃO tem a letra %c\n\n", chute);
    }

    chutes[chutesdados] = chute;
    chutesdados++;
}

int jachutou(char letra){

	int achou = 0;

	for(int j = 0; j < chutesdados; j++){
					
		if(chutes[j] == letra){
			achou = 1;
			break;
		}
	}
	return achou;
 }

int letraexiste(char letra) {

    for(int j = 0; j < strlen(palavrasecreta); j++) {
        if(letra == palavrasecreta[j]) {
            return 1;
        }
    }

    return 0;
}


void desenhaforca(){


	int erros = chuteserrados();

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
    printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
    printf(" |       %c     \n", (erros>=2?'|':' '));
    printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

    for(int i = 0; i < strlen(palavrasecreta); i++) {

        if(jachutou(palavrasecreta[i])) {
            printf("%c ", palavrasecreta[i]);
        } else {
            printf("_ ");
        }

    }
    printf("\n");
}

void adicionapalavra(){
	char quer;
	printf("Voce deseja adicionar uma nova palavra no jogo? (S/N): ");
	scanf(" %c", &quer);

	if(quer == 'S'){

		char novopalavra[TAMANHO_PALAVRA];
		printf("Qual a nova palavra: ");
		scanf("%s", novopalavra);

		FILE* f;
		f = fopen("palavras.txt", "r+"); //leitura e escrita

		if(f == 0){
			printf("Desculpe, banco de dados nao disponivel \n\n");
			exit(1);
		}

		int qtd;
		fscanf(f, "%d", &qtd);
		qtd++;

		fseek(f, 0, SEEK_SET);//posiciona inicio do arquivo
		fprintf(f, "%d", qtd);

		fseek(f, 0, SEEK_END); //posicionar no fim do arquivo

		fprintf(f, "\n%s", novopalavra);

		fclose(f);
	}
}

void escolhepalavra(){
	FILE* f; //ponteiro de arquivo

	f = fopen("palavras.txt", "r"); // abrir arquivo

	if(f == 0){
		printf("Desculpe, banco de dados nao disponivel \n\n");
		exit(1);
	}


	int qtddepalavras;

	fscanf(f, "%d", &qtddepalavras); //pegar quantidade de letras no arquivo

	srand(time(0));
	int randomico = rand() % qtddepalavras;

	for(int i = 0; i <= randomico; i++){
		fscanf(f, "%s", palavrasecreta);
	}
	fclose(f);
}


int acertou(){
	for(int i = 0; i < strlen(palavrasecreta); i++){
		if(!jachutou(palavrasecreta[i])) {
			return 0;
		}
	}
	return 1;
}
 
int chuteserrados() {
    int erros = 0;

    for(int i = 0; i < chutesdados; i++) {

        if(!letraexiste(chutes[i])) {
            erros++;
        }
    }

    return erros;
}

int enforcou(){

	return chuteserrados() >= 5;
}



int main(){
	abertura();
	escolhepalavra();

	do{

		desenhaforca();
		chuta();

	}while(!acertou() && !enforcou());

	if(acertou()){
		printf("\n Parabens, voce ganhou! \n");

		printf("		---------------------------------------- \n");
		printf("		             ___________				 \n");	
		printf("		            '._==_==_=_.'                \n");
		printf("		            .-\\:      /-.               \n");
		printf("		           | (|:.     |) |               \n");
		printf("		            '-|:.     |-'                \n");
		printf("		              \\::.    /                 \n");
		printf("		               '::. .'                   \n");
		printf("		                 ) (                     \n");
		printf("		               _.' '._                   \n");
		printf("		---------------------------------------- \n");


	}else{
		printf("Puxa, voce foi enforcado! \n");
		printf("A palavra era **%s**\n\n", palavrasecreta);



			printf("		  +---+          \n");
			printf("		  |   |          \n");
			printf("		  O   |          \n");
			printf("		 /|\\  |         \n");
			printf("		 / \\  |         \n");
			printf("		      |          \n");
			printf("		========='''     \n");
	}
}
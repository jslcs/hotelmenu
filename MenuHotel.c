#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50
#define TOTAL 100
#define ANOATUAL 2020

typedef struct 
{
	int diac, mesc, anoc;
	int dias, mess, anos;
	int ndias;
	char cpf[50];
	char nome[30];
	int numeroDoQuarto;
	float valorDiaria;
	int presente;
} registro;

int i = 1, j;
int contador = 1;
char totaldepessoas[TOTAL][TOTAL];
registro Hospede[MAX];

registro *pt = Hospede;

void menu();
void checkin();
void checkout();
void mostraHospPresentes();
void mostraHospTotais();
void verificaQuarto();

int main(void)
{	
	int a;

	pt -> diac = 30;

	printf("%d\n", Hospede[0].diac);

	for(a = 0; a < MAX; a++)
	{
		Hospede[a].presente = 0;
	}

	menu();

return 0;
}

void menu()
{
	int op;

	for(; i < MAX; i++)
	{
		system("cls");
		printf("\n\n");
		printf("Checkin (1): \n");
		printf("Checkout(2): \n");
		printf("Mostrar hospedes presentes (3): \n");
		printf("Mostrar hospedes totais (4): \n");
		printf("Verificar se o quarto esta vago (5): \n");
		printf("Sair (6): \n");
		printf("\n\n");
		
		fflush(stdin);
		scanf("%d", &op);

		switch(op)
		{
			case 1:
				checkin();
			break;

			case 2:
				checkout();
			break;

			case 3:
				mostraHospPresentes();
			break;

			case 4:
				mostraHospTotais();
			break;

			case 5:
				verificaQuarto();
			break;

			case 6:
				system("cls");
				exit(1);
			break;

			default:
				system("cls");
				printf("numero invalido\n");
				system("pause");
				menu();
	    }
	}
}

void checkin()
{	
	int a;
	int num;

	system("cls");
	
	for(a = 0; a < MAX ; a++)
	{
		printf("Digite o numero do quarto em que o hospede ficara hospedado: ");	
		scanf("%d", &num);

		if(num > 50 || num <= 0)
		{	
			printf("\n");
			printf("O numero digitado eh invalido\n\n");
			system("pause");
			menu();
		}
		else if(Hospede[num].presente == 0)
		{
			Hospede[num].presente = 1;
			break;
		}
		else
		{
			printf("\nO quarto digitado esta ocupado, tente outro quarto.\n");
		}
	}

	printf("\nDigite o nome do hospede: ");
	fflush(stdin);
	scanf("%[^\n]", &Hospede[num].nome);
	printf("\n");

	printf("Digite os dez digitos do CPF do hospede: ");
	scanf("%s", Hospede[num].cpf);
	printf("\n");

	printf("Digite a data de chegada no formato DD/MM/AAAA: ");
	scanf("%d/%d/%d", &Hospede[num].diac, &Hospede[num].mesc, &Hospede[num].anoc);	

	if(Hospede[num].diac > 31 || Hospede[num].mesc > 12 || Hospede[num].anoc > ANOATUAL
	   || Hospede[num].diac <= 0 || Hospede[num].mesc <= 0 || Hospede[num].anoc < 0)
	{
		system("cls");
		printf("Data invalida!\n");
		Hospede[num].presente = 0;
		system("pause");
		menu();
	}

	printf("\n");
	printf("Digite o valor da diaria: ");
	scanf("%f", &Hospede[num].valorDiaria);
	printf("\n");

	Hospede[num].numeroDoQuarto = num;

	Hospede[num].dias = 0;
	Hospede[num].mess = 0;
	Hospede[num].anos = 0;
	Hospede[num].ndias = 0;

	//passa uma string pra outra
	strcpy(totaldepessoas[contador], Hospede[num].nome);
	contador++;

	printf("\n");
	printf("O numero do quarto eh: %d", Hospede[num].numeroDoQuarto);
	printf("\n\n");
	system("pause");
}

void checkout()
{
	int numero;
	int a, conta = 0;
	int diaA, diaB, diaT;
	float valor;

	for(a = 0; a < MAX; a++)
	{
		if(Hospede[a].presente == 1)
			conta++;
	}
	
	if(conta == 0)
	{	
		system("cls");
		printf("Nao ha hospedes para fazer chekout\n");
		system("pause");
		menu();
	}

	system("cls");
	printf("Digite o numero do quarto do hospede que ira fazer o checkout: ");
	scanf("%d", &numero);
	printf("\n");

	if(Hospede[numero].presente == 0)
	{
		printf("\nNao existem hospedes no quarto %d\n\n", numero);
		system("pause");
		menu();
	}

	printf("Digite a data de saida no formato DD/MM/AAAA: ");
	scanf("%d/%d/%d", &Hospede[numero].dias, &Hospede[numero].mess, &Hospede[numero].anos);
	printf("\n");

	if(Hospede[numero].dias > 31 || Hospede[numero].mess > 12 || Hospede[numero].anos > 2020
	   || Hospede[numero].dias <= 0 || Hospede[numero].mess <= 0 || Hospede[numero].anos < 0)
	{
		system("cls");
		printf("Data invalida!\n");
		system("pause");
		menu();
	}

	diaA = Hospede[numero].anos * 365 + Hospede[numero].mess * 30 + Hospede[numero].dias;
	diaB = Hospede[numero].anoc * 365 + Hospede[numero].mesc * 30 + Hospede[numero].diac;

	diaT = diaA - diaB;

	if(diaT < 0)
	{
		printf("\nData invalida!\n");
		system("pause");
		menu();
	}

	valor = diaT * Hospede[numero].valorDiaria;

	Hospede[numero].presente = 0;


	printf("O Hospede ficou hospedado %d dia(s)\n\n", diaT);
	printf("O valor a ser pago eh: R$ %.2f\n", valor);
	printf("\n");
	system("pause");
	i = i - 1;
	menu();
}

void mostraHospPresentes()
{
	int a;
	int conta = 0;

	system("cls");

	for(a = 0; a < MAX; a++)
	{
		if(Hospede[a].presente == 1)
		{
			printf("Quarto %d: %s\n",  Hospede[a].numeroDoQuarto, Hospede[a].nome);
			conta++;
		}
	}

	if(conta == 0)
			printf("Nao ha ninguem hospedado no momento\n\n");

	system("pause");
	menu();
}

void mostraHospTotais()
{
	int a;
	int cont = 0;

	system("cls");

	if(contador == 1)
	{
		system("cls");
		printf("Nao ha hospedes para serem mostrados\n\n");
		system("pause");
		menu();
	}

	for(a = 1; a < contador; a++)
	{
		printf("%s\n", totaldepessoas[a]);
	}
	
	system("pause");
	menu();
}

void verificaQuarto()
{
	int n;

	system("cls");

	printf("Digite o numero do quarto: ");
	scanf("%d", &n);

	if(n > 50 || n <= 0)
	{
		system("cls");
		printf("O numero do quarto digitado nao existe\n");
		system("pause");
	}
	else
	{
		if(Hospede[n].presente == 0)
		{	

			system("cls");
			printf("O quarto numero %d esta vago\n\n", n);
			system("pause");
		}
		else if(Hospede[n].presente == 1)
		{
			system("cls");

			printf("O quarto numero %d esta ocupado\n\n", n);
			printf("Nome do Hospede: %s\n", Hospede[n].nome);
			printf("CPF: %s\n", Hospede[n].cpf);
			printf("Data de chegada: %d/%d/%d\n", Hospede[n].diac, Hospede[n].mesc, Hospede[n].anoc);
			printf("Valor da diaria: %.2f\n\n", Hospede[n].valorDiaria);
			system("pause");
		}
	}

	menu();
}
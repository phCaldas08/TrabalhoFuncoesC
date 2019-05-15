#include<stdio.h>
#include<string.h>

#define N_CLIENTES 500
#define TAM_CNPJ 14
#define TAM_STRING 11
#define LIMPA_TELA system("cls")

struct Cliente{
	char CNPJ[TAM_CNPJ], atividade_economica[TAM_STRING];
	int consumoGB;
};
typedef struct Cliente TipoCliente;

void Le_Registros(TipoCliente clientes[], int *num){
	char op;
	short ae;	
	*num = 0;
	
	do{
		LIMPA_TELA;
		printf("Digite o CNPJ do cliente:\n");
		fflush(stdin);
		gets(clientes[*num].CNPJ);
		
		do{			
			LIMPA_TELA;
			printf("Digite o codigo da atividade economica do cliente: \n1 - Agronegocio\n2 - Industria\n3 - Tecnologia\n4 - comercio\n");
			scanf("%hd", &ae);
			switch(ae){
				case 1:
					strcpy(clientes[*num].atividade_economica, "Agronegocio");
					break;
				case 2:
					strcpy(clientes[*num].atividade_economica, "Industria");
					break;
				case 3:
					strcpy(clientes[*num].atividade_economica, "Tecnologia");
					break;
				case 4:
					strcpy(clientes[*num].atividade_economica, "comercio");
					break;
				default:
					ae = -1;
					break;		
			}			
		}while(ae == -1);
		
		LIMPA_TELA;
		printf("Digite o consumo do cliente em GB:\n");
		scanf("%d", &clientes[*num].consumoGB);	
		
		LIMPA_TELA;
		fflush(stdin);
		printf("Deseja cadastrar outro cliente? [s/n]\n");
		scanf("%c", &op);
		*num = *num + 1;	
			
	}while(op == 's' || op == 'S' && *num < 500);
	LIMPA_TELA;	
}

void Consumo_Superior_500(TipoCliente clientes[], int num, char CNPJ_500[][14], int *cont){
	int i;
	*cont = 0;
	
	for(i = 0; i < num; i++){
		if(clientes[i].consumoGB > 500 && strcmp(clientes[i].atividade_economica, "Agronegocio") == 0){
			strcpy(CNPJ_500[*cont], clientes[i].CNPJ);
			*cont = *cont + 1;
		}		
	}	
}

void Maior_Menor_Consumo(TipoCliente clientes[], int num, int *pos_maior, int *pos_menor){
	int i, consumoMax, consumoMin;
	for(i = 0; i < num; i++){
		if(i == 0){
			consumoMax = consumoMin = clientes[i].consumoGB;
			*pos_maior = *pos_menor = 0;
		}
		
		if(consumoMax < clientes[i].consumoGB){
			*pos_maior = i;
			consumoMax = clientes[i].consumoGB;
		}
		
		if(consumoMin > clientes[i].consumoGB){
			*pos_menor = i;
			consumoMin = clientes[i].consumoGB;
		}
	}
}

void Exibe_CNPJ(char CNPJ_500[][14], int cont){
	int i;
	LIMPA_TELA;
	if(cont == 0){
		printf("Nenhum cliente encontrado!\n");
		return;		
	}
	
	printf("CNPJs com consumo maior que 500Gb e atividade tecnica em agronegocio: \n");
	for(i = 0; i < cont; i++){
		printf("%d - %s\n", cont + 1, CNPJ_500[i]);
	}
}

int main(){
	TipoCliente clientes[N_CLIENTES];
	char CNPJ_500[500][14];
	int num, op, cont = 0, pos_maior = -1, pos_menor = -1;
	
	do{			
		printf("Digite a operacao desejada: \n1 - Ler clientes\n2 - Consumo superior a 500\n3 - Maior e menor consumo\n4 - Exibir CNPJs com consumo maior que 500\n5 - Sair\n");
		scanf("%d", &op);
		
		switch(op){
			case 1:
				cont = 0;
				pos_maior = pos_menor = -1;				
				Le_Registros(clientes, &num);
				printf("Foram lidos %d clientes!\n", num);
				break;
			case 2:
				Consumo_Superior_500(clientes, num, CNPJ_500, &cont);
				break;
			case 3:
				LIMPA_TELA;
				Maior_Menor_Consumo(clientes, num, &pos_maior, &pos_menor);				
				if(pos_maior != -1 && pos_menor != -1)
					printf("Maior:\nCNPJ: %s\nAtividade Economica: %s\n\nMenor:\nCNPJ: %s\nAtividade Economica: %s\n"
								, clientes[pos_maior].CNPJ
								, clientes[pos_maior].atividade_economica
								, clientes[pos_menor].CNPJ
								, clientes[pos_menor].atividade_economica);
				else
					printf("Nenhum cliente encontrado!\n");
				break;
			case 4:
				Exibe_CNPJ(CNPJ_500, cont);
				break;
			case 5:
				break;
			default:
				LIMPA_TELA;
				printf("Opcao nao encotrada, tente novamente!\n");
				break;
		}
		system("pause");
		LIMPA_TELA;
		
	}while(op != 5);
	
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>

#define euro 2.5

struct parking{
	char matricula[7];
	char nome[50];

	time_t t_entrada;
	time_t t_saida;
};

struct pInfo{
	int piso;
	int coluna;
	int linha;
};

typedef struct pInfo pInfo;

typedef struct parking park;

void welcome(){
	int f,g,h,j,k;
	for(f = 1; f < 50; f++){
		if(f % 2 == 0){
			printf("=");
			
		}
		else{
			printf("*");
		}
		usleep(2000);
	}
	
	printf("\n");
	printf("         ");
	printf("         ");
	printf("\n");
	usleep(80000);
	printf("         ");
	printf("        __-------__ \n");
	usleep(80000);
	printf("         ");
	printf("      / _---------_ \\ \n" );
	usleep(80000);
	printf("         ");
	printf("     | |           | | \n");
	usleep(80000);
	printf("         ");
	printf("     | |           | | \n");
	usleep(80000);
	printf("         ");
	printf("     |_|___________|_| \n");
	usleep(80000);
	printf("         ");
	printf(" /-||                |/-| \n");
	usleep(80000);
	printf("         ");
	printf("| _ |\       0       /| _ | \n");
	usleep(80000);
	printf("         ");
	printf("|(_)| \      !      / |(_)| \n");
	usleep(80000);
	printf("         ");
	printf("|___|__\_____!_____/__|___| \n");
	usleep(80000);
	printf("         ");
	printf("[_________|AEDP2|_________] \n");
	usleep(80000);
	printf("         ");
	printf(" ||||    ~~~~~~~~     |||| \n");
	usleep(80000);
	printf("         ");
	printf(" `--'                 `--' \n");
	usleep(80000);
	
	for(g = 1; g < 50; g++){
		if(g % 2 == 0){
			printf("=");
			
		}
		else{
			printf("*");
		}
		usleep(2000);
	}
	
	printf("\n\n\n");
	
		
	printf("              ");
	
	
	char start[13] = "A INICIAR...";
	
	for(h = 0; h < 16; h++){
		printf("%c", start[h]);
		usleep(80000);
	}
	
	printf("\n\n");
	
	printf("           ");
	
	
	char welc[20] = "  SEJA BEM VINDO!";
	
	for(j = 0; j < 16; j++){
		printf("%c", welc[j]);
		usleep(80000);
	}
	
	printf("\n\n\n");
	
	
	for(k = 1; k < 50; k++){
		if(k % 2 == 0){
			printf("=");
			
		}
		else{
			printf("*");
		}
		usleep(2000);
	}
	
	system("cls");
}

//Funcao que verifica se uma determinada matricula existe
int searchMat(park ***prk, pInfo *info, char mat[7]){
	int p = info->piso;
	int c = info->coluna;
	int l = info->linha;
	int exist = 0;
	int f,j,u;
	
	//Percorrer a struct do parque (por piso, seguido da coluna e, por fim, da linha)
	for(f = 0; f < p; f++){
		for(j = 0; j < c; j++){
			for(u = 0; u < l; u++){
				//Verifica a sua existencia
				if(strcmp(prk[f][j][u].matricula,mat) == 0){
					exist = 1;
					f=p;
					j=c;
					u=l;
				}
			}
		}
	}
	return exist;
}

//Funcao que adiciona um veiculo (matricula e nome) ao parque previamente criado
add(park ***prk, pInfo *info, char mat[7], char nom[50]){
	int p = info->piso;
	int c = info->coluna;
	int l = info->linha;
	
	int found = 0;
	int exist = searchMat(prk,info,mat);
	
	int f,j,u;
	
	//Apenas adiciona se a matricula nao existir
	time_t entrada;
	if(exist == 0){
		//Percorrer a struct do parque (por piso, seguido da coluna e, por fim, da linha)
		for(f = 0; f < p; f++){
			for(j = 0; j < c; j++){
				for(u = 0; u < l; u++){
					//Se a matricula estiver como "LIVRE" quer dizer que nao se encontra nenhum veiculo naquela determinada posicao (piso=f, coluna=j e piso=u)
					if(strcmp(prk[f][j][u].matricula,"LIVRE") == 0){
						//Adiciona o veiculo nessa posicao (matricula e nome)
						strcpy(prk[f][j][u].matricula , mat);
						strcpy(prk[f][j][u].nome , nom);
					
						//Atribui ao tempo de entrada do veiculo a hora, consoante a hora da maquina
						prk[f][j][u].t_entrada = time(&entrada);
					
						found = 1;
						f=p;
						j=c;
						u=l;
					}
				}
			}
		}
	}else{
		printf("\nO carro com a matricula %s ja existe no parque!",mat);
		sleep(2);
		found = 2;
	}
	if(found == 0){
		printf("Parque Ocupado!\n");
		sleep(2);
	}
}

//Funcao que permite ao utilizador remover um veiculo segundo a sua matricula
remover(park ***prk, pInfo *info, char mat[7]){
	int p = info->piso;
	int c = info->coluna;
	int l = info->linha;
	int found = 0;
	int i,j,u;
	
	time_t saida;
	int tempo;
	
	//Percorrer a struct do parque (por piso, seguido da coluna e, por fim, da linha)
	for(i = 0; i < p; i++){
		for(j = 0; j < c; j++){
			for(u = 0; u < l; u++){
				if(strcmp(prk[i][j][u].matricula,mat) == 0){
					//Assim que for eliminado um veiculo a matricula e o nome que esta presente naquela posicao e alterada para "LIVRE" e "None", consequentemente
					strcpy(prk[i][j][u].matricula , "LIVRE");
					strcpy(prk[i][j][u].nome , "None");
					
					//Busca as horas da maquina e atribui essas horas ao tempo de saida do veiculo
					prk[i][j][u].t_saida = time(&saida);
					
					//Calcula a diferenca dos tempos (segundos)
					tempo = difftime(saida, prk[i][j][u].t_entrada);
					
					sleep(1);
					
					printf("\n\n\n\n\n");
					
					printf("A diferenca de tempo foi: %d segundos", tempo);
					
					printf("\n\n\n\n\n");
					
					float fatura;
					
					fatura = tempo*(euro/3600);
					
					float rounded_up = ceilf(fatura * 100) / 100;
					
					printf("O cliente necessita de pagar %.2f euros", rounded_up);
					
					sleep(5);
					
					found = 1;
					i=p;
					j=c;
					u=l;
				}
			}
		}
	}
	if(found == 0){
		printf("O carro que procura não existe no Parque!\n");
		
	}
		printf("\nHELP: Pressione ENTER para sair");
}

//Apresenta as caracteristicas de um determinado carro (piso, coluna e linda que esta estacionado e, ainda, o tempo de entrada do mesmo)
carInfo(park ***prk, pInfo *info, char mat[7]){
	int p = info->piso;
	int c = info->coluna;
	int l = info->linha;
	int found = 0;
	int i,j,u;
	
	//Percorrer a struct do parque (por piso, seguido da coluna e, por fim, da linha)
	for(i = 0; i < p; i++){
		for(j = 0; j < c; j++){
			for(u = 0; u < l; u++){
				if(strcmp(prk[i][j][u].matricula,mat) == 0){
					
					printf("\n");
					
					printf("O teu carro esta no piso %d na coluna %d e na linha %d!", i,j,u);
					
					printf("\n\n");
					
					struct tm *newtime;
					
					newtime = localtime(&prk[i][j][u].t_entrada);
					
					printf("O teu carro entrou no parque %s", asctime(newtime));

					found = 1;
					i=p;
					j=c;
					u=l;
				}
			}
		}
	}
	if(found == 0){
		printf("Nao existe o veiculo no Parque!");
	}
	printf("\n\nHELP: Pressione ENTER para sair");
}

//Apresenta as caracteristicas do parque em matriz
parkInfo(park ***prk,pInfo *info){
	int p = info->piso;
	int c = info->coluna;
	int l = info->linha;
	int tamanho = p*c*l;
	int livre = 0;
	int i,u,j;
	
	//Percorrer a struct do parque (por piso, seguido da coluna e, por fim, da linha)
	for(i = 0; i < p; i++){
		for(j = 0; j < c; j++){
			for(u = 0; u < l; u++){
				if(strcmp(prk[i][j][u].matricula,"LIVRE") == 0){
					livre++;	
				}
			}
		}
	}

	int ocupado = tamanho - livre;
	int perc = (livre * 100) / tamanho;

	//Mini dashboard, com caracteristicas de lotacao do parque
	printf("Tamanho do Parque: %d \n", tamanho);
	printf("Lugares Livres: %d     Lugares Ocupados: %d\n", livre, ocupado);
	printf("Percentagem Livres: %d %% \n", perc);

	int f,g,h;
	for(f = 0; f < p; f++){
		printf("\nPiso %d", f);
		for(g = 0; g < c; g++){
			printf("\n");
			for(h = 0; h < l; h++){
				printf("%s ", prk[f][g][h].matricula);
			}
		}
		printf("\n");
	}
	
	printf("\nHELP: Pressione ENTER para sair");
}

void arrowHere(int realPosition, int arrowPosition) {
    if (realPosition == arrowPosition) { 
        printf(" ---->> ");
    }
    else{
        printf (" ");
    }     
}

int backupw(park ***prk ,pInfo *info){
	
    int r,u,w;
	int p = info->piso;
	int c = info->coluna;
	int l = info->linha;
	
	//Ficheiro com a constituicao do veiculo, num determinado parque
    FILE *fp;
    fp = fopen("./backupwr.dat", "w");
    //Ficheiro com a constituicao do parque de estacionamento
	FILE *fp1;
    fp1 = fopen("./backupw1r.dat", "w");
    
    if (fp == NULL)
    {
        printf("Ficheiro nao existe \n");
        return 0 ;
    }
	 if (fp1 == NULL)
    {
        printf("Ficheiro nao existe \n");
        return 0 ;
    }
    fprintf(fp1,"%d ", p);
    fprintf(fp1,"%d ", c);
    fprintf(fp1,"%d ", l);
    
	for(r=0;r<p;r++){
    	for(u=0;u<c;u++){
			for(w=0;w<l;w++){

				//Escreve os dados que foram criados no programa
	            fprintf(fp,"\n");
	            fprintf(fp,"%s",prk[r][u][w].matricula);
	            fprintf(fp," %s",prk[r][u][w].nome);
	            fprintf(fp," %lld",prk[r][u][w].t_entrada);
	            fprintf(fp," %lld",prk[r][u][w].t_saida);
            }
		}
	}
			
    fclose(fp);
    fclose(fp1);
}


int backupr(){

    int r,u,w;
	int p;
	int c;
	int l;
	
	//Ficheiro com a constituicao do veiculo, num determinado parque
	FILE *fp;
    fp = fopen("./backupwr.dat", "r");
    //Ficheiro com a constituicao do parque de estacionamento
    FILE *fp1;
    fp1 = fopen("./backupw1r.dat", "r");

	if (fp1 == NULL)
    {
        printf("Parque não existe!\n");
        novo();
    }
    fscanf(fp1,"%d ",&p);
    fscanf(fp1,"%d ",&c);
	fscanf(fp1,"%d ",&l);

	park ***prk = (park ***)malloc(p*(sizeof(park)));
	
	for(r=0;r<p;r++){
		prk[r]=(park **)malloc(c*(sizeof(park)));
		for(u=0;u<c;u++){
			prk[r][u]=(park *)malloc(l*(sizeof(park)));
		}
	}

    for(r=0;r<p;r++){
    	for(u=0;u<c;u++){
			for(w=0;w<l;w++){
				
				//Le do ficheiro os dados que se encontram no mesmo
	            fscanf(fp,"\n");
	            fscanf(fp," %s", prk[r][u][w].matricula);
	            fscanf(fp," %s", prk[r][u][w].nome);
	            fscanf(fp," %lld", &prk[r][u][w].t_entrada);
	            fscanf(fp," %lld", &prk[r][u][w].t_saida);
			}
		}
	}
		
    fclose(fp);
	fclose(fp1);
	principal(prk,p,c,l);
		
} 
 
void getMenu(int i,park ***prk, pInfo *info){
	char mat[7];
	char nom[50];
	switch(i){
		case 1:
			system("cls");
			printf("=*=*=*=*=*=*=*=|ADICIONAR|=*=*=*=*=*=*=*=\n");
			printf("Insira a matricula de um veiculo por favor: ");
			scanf(" %s", &mat);
			printf("\nInsira a nome do Proprietario por favor: ");
			scanf(" %s", &nom);
			add(prk, info, mat, nom);
			usleep(50000);
			break;
		case 2:
			system("cls");
			printf("=*=*=*=*=*=*=*=|REMOVER|=*=*=*=*=*=*=*=\n");
			printf("Insira a matricula de um veiculo por favor: ");
			scanf(" %s", &mat);
			remover(prk,info,mat);
			usleep(50000);
			break;
		case 3: 
			system("cls");
			printf("=*=*=*=*=*=*=|INFORMACAO|=*=*=*=*=*=*=\n");
			printf("Insira a matricula de um veiculo por favor: ");
			scanf(" %s", &mat);
			carInfo(prk,info,mat);
			getch();
			break;
		case 4:
			system("cls");
			printf("=*=*=*=*=*=*=|INFORMACAO|=*=*=*=*=*=*=\n");
			parkInfo(prk,info);
			getch();
			break;
		case 5:
			system("cls");
			printf("A SAIR!");
			backupw(prk,info);	
			usleep(500000);
			exit(0);
	}
}

void menu(park ***prk,pInfo *info){
	system("cls");
	int position = 1;
	int keyPressed = 0;
	
	#define MAX 5
	#define MIN 1
	
	while (keyPressed != 13){
		system("cls");
		printf("=*=*=*=*=*=*=*=*=|MENU|=*=*=*=*=*=*=*=*=\n");
		arrowHere(1, position); printf(" Estacionar Carro \n");
		arrowHere(2, position); printf(" Remover Carro \n");
		arrowHere(3, position); printf(" Mostrar Informacao sobre Carro \n");
		arrowHere(4, position); printf(" Mostrar Informacao sobre o Parque \n");
		arrowHere(5, position); printf(" Sair \n\n");
		printf("HELP: Use as setas do teclado para navegar o menu!\n");
		printf("HELP: Para gravar selecione a opcao 5!!\n");
		printf("=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=\n");
		keyPressed = getch();
		if (keyPressed == 80 && position != MAX) {
 			position++;
		}
		else if (keyPressed	== 72 && position != MIN){
 			position--;
		}
 		else{
    		position = position;
		}
	}

	getMenu(position, prk, info);
}

//Se existir um parque executa este metodo
principal(park ***prk, int piso,int col, int lin){
	
	struct pInfo *info;
	info = (struct pInfo*) malloc (sizeof (pInfo));
	info->piso = piso;
	info->coluna = col;
	info->linha = lin;		
	
	int chaveta = 0;
	while(chaveta == 0){
		menu(prk,info);
	}
	free(info);
	free(prk);
}	

//Se nao existir um parque executa este metodo
novo(){
	int p;
	int c;
	int l;
	system("cls");
	printf("=*=*=*=*=*=*=|CRIAR PARQUE|=*=*=*=*=*=*=\n");
	printf("Quantos pisos tem o parque: ");
	scanf("%d",&p);
	
	printf("Quantas colunas tem cada piso: ");
	scanf("%d",&c);
	
	printf("Quantos linhas tem cada piso: ");
	scanf("%d",&l);

	struct pInfo *info;
	info = (struct pInfo*) malloc (sizeof (pInfo));
	info->piso = p;
	info->coluna = c;
	info->linha = l;
	
	int i,j,u;
	park ***prk; 
	prk = (park ***)malloc(p*(sizeof(park)));
	for(i=0;i<p;i++){
		prk[i]=(park **)malloc(c*(sizeof(park)));
			for(j=0;j<c;j++){
				prk[i][j]=(park *)malloc(l*(sizeof(park)));
			}
		}
	
	for(i = 0; i < p; i++){
		printf("\n\n");
		for(j = 0; j < c; j++){
			printf("\n");
			for(u = 0; u < l; u++){
				strcpy(prk[i][j][u].matricula , "LIVRE");
				strcpy(prk[i][j][u].nome , "None");
				prk[i][j][u].t_entrada = 0;
				prk[i][j][u].t_saida = 0;
			}
		}
	}
	
	int chaveta = 0;
	while(chaveta == 0){
		menu(prk,info);
	}
	free(prk);
}

main(){
	welcome();
	backupr();
	
}

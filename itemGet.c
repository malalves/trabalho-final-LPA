#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char nome[25];
 	char categoria;
 	int value;
}item;

int itemGet(int num,item *it){
	FILE*arq;

	arq=fopen("item.dat","rb");
	fseek(arq,(num*sizeof(item)),0);
	fread(it,sizeof(item),1,arq);
	if(feof(arq))return 1;
	fclose(arq);

	return 0;
}

int itemFind(char nome[25],item *it){
	FILE*arq;

	arq=fopen("item.dat","rb");
	do{
		fread(it,sizeof(item),1,arq);
		if(feof(arq)) return 1;
	}while(strcmp(nome,(*it).nome));
	fclose(arq);

	return 0;
}

int main(){
	item it;
	char test;

	printf("voce deseja encontrar um item pelo nome(c) ou pelo numero(n):");
	scanf("%c",&test);

	if(test=='c'){
		char nome[25];
		scanf("%*c");
		printf("digite o nome do item:");
		gets(nome);
		if(itemFind(nome,&it)) return 1;
	}
	else{
		if(test=='n'){
			printf("digite o numero do item:");
			scanf("%i",&test);
			if(itemGet(test,&it)) return 1;
		}
		else return 0;
	}

	printf("%s\ncategoria:%c\nbonus:%i\n",it.nome,it.categoria,it.value);
	system("pause");
	return 0;
}

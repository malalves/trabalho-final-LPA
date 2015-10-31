#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char inv[10];

typedef struct{
	char nome[25];
 	char categoria;
 	int value;
}item;

int itemFind(char nome[25],item *it){
	FILE*arq;

	arq=fopen("item.dat","rb");
	do{
		fread(it,sizeof(item),1,arq);
		if(feof(arq)) return 1;
	}while(strcmp(nome,(*it).nome));
	fclose(arq);

	return 0;
}//emcontra um item no banco de dados pelo nome

int itemGet(int num,item *it){
	FILE*arq;

	arq=fopen("item.dat","rb");
	fseek(arq,(num*sizeof(item)),0);//pula para a struct numero num

	fread(it,sizeof(item),1,arq);

	if(feof(arq))return 1;//não existe o numero
	fclose(arq);

	return 0;//encontrou o item
}//encontra um item no banco de dados pelo numero

int invFind(char nome[25],item *it){
	FILE*arq;

	arq=fopen(inv,"rb");
	do{
		fread(it,sizeof(item),1,arq);
		if(feof(arq)) return 1;//não encontrou o item com o nome
	}while(strcmp(nome,(*it).nome));
	fclose(arq);

	return 0;//encontrou o item
}//encontra um item no inventario pelo nome

int invSet(int slot){
	switch(slot){
		case 0:
			strcpy(inv,"inv0.dat");
			break;
		case 1:
			strcpy(inv,"inv1.dat");
			break;
		case 2:
			strcpy(inv,"inv2.dat");
			break;
		case 3:
			strcpy(inv,"inv3.dat");
			break;
		default:
			printf("slot invalido\n");
			return 1;
	}
	return 0;
}//seleciona o inventario

int store(item *it){
	FILE* arq;
	item i2;

	if(!invFind((*it).nome,&i2)){
		printf("este item ja existe no inventario\n");
		return 1;
	}
	
	arq=fopen(inv,"ab");
	fwrite(it,sizeof(item),1,arq);
	fclose(arq);

	return 0;
}//adiciona um item no inventario

int invType(char type){
	FILE* arq;
	item it;
	int i=0;
	
	arq=fopen(inv,"rb");

	fread(&it,sizeof(item),1,arq);
	do{
		if(it.categoria==type){
			printf("%s--%i\n",it.nome,it.value);
		}
		i++;
		fread(&it,sizeof(item),1,arq);
	}while(!feof(arq));
	fclose(arq);

	return 0;
}//inprime o nome e o bonus de todos os items de u certo tipo

int invGet(int num,item *it){
	FILE*arq;

	arq=fopen(inv,"rb");
	fseek(arq,(num*sizeof(item)),0);//pula para a struct numero num

	fread(it,sizeof(item),1,arq);

	if(feof(arq))return 1;//não existe o numero
	fclose(arq);

	return 0;//encontrou o item
}//seleciona um item do inventario pelo nome

int invRemove(char nome[25]){
	FILE* arq;
	item it;
	int i=0;

	arq=fopen("aux.dat","wb");

	while(!invGet(i,&it)){
		if(strcmp(it.nome,nome)){
			fwrite(&it,sizeof(item),1,arq);
		}
		i++;
	}

	fclose(arq);

	remove(inv);
	rename("aux.dat",inv);

	return 0;
}//remove um item do inventario

int main(){
	printf("blar\n");
	return 0;
}

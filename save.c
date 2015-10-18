#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char nome[25];
 	char categoria;
 	int value;
}item;

typedef struct{
	unsigned int hp, xp;
	unsigned char lvl,
	     wis,
	     str,
	     dex,
	     pos,
	     slot;
	char nome[30];
	item equip[6];
}personagem;

int save(personagem per){
	FILE* arq;
	char str[10];
	
	switch(per.slot){
		case 0:
			strcpy(str,"slot0.dat");
			break;
		case 1:
			strcpy(str,"slot1.dat");
			break;
		case 2:
			strcpy(str,"slot2.dat");
			break;
		case 3:
			strcpy(str,"slot3.dat");
			break;
		default:
			printf("slot invalido\n");
			return 1;

	}

	arq=fopen(str,"wb");
	fseek(arq,per.slot*sizeof(personagem),0);
	fwrite(&per,sizeof(personagem),1,arq);
	fclose(arq);

	return 0;
}

void equip(personagem *per,item it){
	switch (it.categoria){
		case 'f':
			(*per).equip[0]=it;
			break;
		case 'm':
			(*per).equip[1]=it;
			break;
		case 'd':
			(*per).equip[2]=it;
			break;
		case 'c':
			(*per).equip[3]=it;
			break;
		case 'a':
			(*per).equip[4]=it;
			break;
		case 'b':
			(*per).equip[5]=it;
			break;
	}
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

int itemGet(int num,item *it){
	FILE*arq;

	arq=fopen("item.dat","rb");
	fseek(arq,(num*sizeof(item)),0);
	fread(it,sizeof(item),1,arq);
	if(feof(arq))return 1;
	fclose(arq);

	return 0;
}

int main(){
	personagem per;
	char test;
	item it;

	printf("\ndigite o level:");
	scanf("%i",&per.lvl);
	printf("%i\ndigite o valor de wis:",per.lvl);
	scanf("%i",&per.wis);
	printf("%i\ndigite o valor de str:",per.wis);
	scanf("%i",&per.str);
	printf("%i\ndigite o valor de dex:",per.str);
	scanf("%hhu",&per.dex);
	printf("%i\ndigite o valor de pos:",per.dex);
	scanf("%hhu",&per.pos);
	printf("%i\ndigite o valor de hp:",per.pos);
	scanf("%i",&per.hp);
	printf("%i\ndigite o valor de xp:",per.hp);
	scanf("%i",&per.xp);
	printf("%i\ndigite o slot(de 0 a 3):",per.xp);
	scanf("%i",&per.slot);
	printf("%i\n",per.slot);
	scanf("%*c");
	printf("digite o nome do personagem:");
	gets(per.nome);

	printf("yo:%s\n",per.nome);

	for(test=0;test<6;test++){
		(per.equip[test]).nome[0]='\0';
	}

	printf("deseja equipar um item(s/n):");
	scanf("%c",&test);

	while(test=='s'){
		scanf("%*c");
		printf("voce deseja encontrar um item pelo nome(c) ou pelo numero(n):");
		scanf("%c",&test);

		if(test=='c'){
			char nome[25];
			scanf("%*c");
			printf("digite o nome do item:");
			gets(nome);
			if(itemFind(nome,&it)) printf("item não encontrado\n");
			else equip(&per,it);
		}
		else{
			if(test=='n'){
				printf("digite o numero do item:");
				scanf("%i",&test);
				scanf("%*c");
				if(itemGet(test,&it))printf("item não encontrado\n");
				else equip(&per,it);
			}
			else printf("comando invalido\n");
		}

		printf("deseja equipar outro item(s/n):");
		scanf("%c",&test);
	}

	system("pause");
	save(per);

	return 0;
}

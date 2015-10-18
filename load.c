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

int load(personagem *per,unsigned char slot){
	FILE*arq;
	char str[10];
	
	switch(slot){
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

	arq=fopen(str,"rb");
	fseek(arq,slot*sizeof(personagem),0);
	fread(per,sizeof(personagem),1,arq);
	fclose(arq);

	if((*per).lvl==0)return 1;
	return 0;
}

int main(){
	personagem per;
	unsigned char slot;
	int i;

	printf("digite o numero do save slot:");
	scanf("%i",&slot);

	if(load(&per,slot)){
		printf("slot vazio");
		system("pause");
		return 1;
	}

	printf("%s\n",per.nome);
	printf("lvl:%i\n",per.lvl);
	printf("wis:%i\n",per.wis);
	printf("str:%i\n",per.str);
	printf("dex:%i\n",per.dex);
	printf("pos:%i\n",per.pos);
	printf("hp:%i\n",per.hp);
	printf("xp:%i\n",per.xp);
	printf("slot:%i\n",per.slot);
	printf("equips:");
	for(i=0;i<6;i++){
		printf("%s\n",(per.equip[i]).nome);
	}


	system("pause");
	return 0;
}

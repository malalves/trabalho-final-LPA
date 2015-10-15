#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int magicD;
	int fisicalD;
	int distD;
	char atkType;
	int atk;
	char nome[25];
	char drop[25];
	int HP, XP;
}monstro;

int main(){
	monstro mon;
	FILE *arq;
	int num;

	printf("digite o numero do monstro (iniciando por 0):");
	scanf("%i",&num);

	arq=fopen("mostros.dat","rb");
	fseek(arq,(num*sizeof(monstro)),0);
	fread(&mon,sizeof(monstro),1,arq);
	
	
	printf("%s\n",mon.nome );
	printf("tipo de ataque:%c\n",mon.atkType );
	printf("valor do ataque:%i\n",mon.atk);
	printf("defesa magica:%i\n",mon.magicD );
	printf("defesa fisica:%i\n",mon.fisicalD );
	printf("defesa a distancia:%i\n",mon.distD);
	printf("HP:%i\n",mon.HP );
	printf("XP:%i\n",mon.XP );
	printf("drop:%s\n",mon.drop );
	printf("\n\n\n");
	

	system("pause");
	return 0;
}

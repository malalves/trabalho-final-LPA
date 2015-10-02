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

int main() {
	monstro mon;
	FILE*arq;
	char test;

	do{
		printf("digite o nome do mostro:");
		gets(mon.nome);
		printf("%s\ndigite o tipo de ataque do montro:(m-magico,f-fisico,d-distancia):",mon.nome);
		scanf("%c",&mon.atkType);
		printf("%c\ndigite o valor de magicD:",mon.atkType);
		scanf("%i",&mon.magicD);
		printf("%i\ndigite o valor de fisicalD:",mon.magicD);
		scanf("%i",&mon.fisicalD);
		printf("%i\ndigite o valor de distD:",mon.fisicalD);
		scanf("%i",&mon.distD);
		printf("%i\ndigite o valor de atk:",mon.distD);
		scanf("%i",&mon.atk);
		printf("%i\ndigite o valor de HP:",mon.atk);
		scanf("%i",&mon.HP);
		printf("%i\ndigite o valor de XP:",mon.HP);
		scanf("%i",&mon.XP);
		printf("%i\ndigite o nome do item dropado:",mon.XP);
		test=getchar();
		gets(mon.drop);
		printf("%s\n",mon.drop);

		arq=fopen("mostros.dat","ab");
		fwrite(&mon,sizeof(monstro),1,arq);
		fclose(arq);

		printf("deseja inserir outro monstro:(s/n)");
		scanf("%c",&test);
		scanf("%*c");
	}while(test!='n');

	system("pause");
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct{
	char nome[25];
 	char categoria;
 	int value;
}item;

typedef struct{
	unsigned int HPx,HP,XP;
	unsigned char lvl,
	     wis,
	     str,
	     dex,
	     pos,
	     slot,
	     rooms[3];
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
	fread(per,sizeof(personagem),1,arq);
	fclose(arq);

	if((*per).lvl==0)return 1;
	return 0;
}

monstro monsterGet(int num){
	FILE*arq;
	monstro mon;

	arq=fopen("mostros.dat","rb");
	fseek(arq,(num*sizeof(monstro)),0);
	fread(&mon,sizeof(monstro),1,arq);
	fclose(arq);

	return mon;
}

char combatMenu(personagem per,monstro mon){
	char escolha;

	system("cls");

	printf("%s\n",mon.nome);
	printf("HP:%i\n\n",mon.HP);
	printf("%s - lvl:%i\n",per.nome,per.lvl);
	printf("HP:%i/%i\n",per.HP,per.HPx);
	printf("XP:\n");

	do{
		printf("voce deseja:\na-atacar,f-fugir,d-despistar o monstro");
		scanf("%c",&escolha);
	}while(escolha=='a'
		|| escolha=='f'
		|| escolha=='d');

	system("cls");

	return escolha;
}//imprime os status do combate e o menu principal do combate

int perAtk(personagem *per,monstro * mon){
	char tipo;
	int dano;

	printf("voce deseja realizar um ataque f-fisico, m-magico ou d-a distancia:\n");
	scanf("%c",&tipo);

	switch(tipo){
		case 'f':
			dano=(((*per).lvl+(*per).str+((*per).equip[0]).value)*(rand()%201))/((*mon).fisicalD*100);
			break;
		case 'm':
			dano=(((*per).lvl+(*per).wis+(*per).equip[1].value)*(rand()%201))/((*mon).magicD*100);
			break;
		case 'd':
			dano=(((*per).lvl+(*per).dex+(*per).equip[2].value)*(rand()%201))/((*mon).distD*100);
			break;
	}

	(*mon).HP -= dano;

	if((*mon).HP<=0)return 1;
	else return 0;
}//personagem causa dano no monstro(retorna 1 se mon morre)

int monAtk(personagem *per,monstro * mon){
	int dano;

	switch((*mon).atkType){
		case 'f':
			dano=((*mon).atk*(rand()%201)-((*per).str+(*per).lvl+((*per).equip[3]).value+((*per).equip[4]).value+((*per).equip[5]).value))/100;
			break;
		case 'm':
			dano=((*mon).atk*(rand()%201)-((*per).wis+(*per).lvl+((*per).equip[3]).value+((*per).equip[4]).value+((*per).equip[5]).value))/100;
			break;
		case 'd':
			dano=((*mon).atk*(rand()%201)-((*per).dex+(*per).lvl+((*per).equip[3]).value+((*per).equip[4]).value+((*per).equip[5]).value))/100;
			break;
	}

	if(dano>0){
		(*per).HP -= dano;
	}

	if((*per).HP<=0)return 2;
	else return 0;
}//monstro causa dano no personagem(retorna 2 se per morre)

void heal(personagem *per){
	(*per).HP=(*per).HPx;
}//cura

int fugir(personagem *per){
	if(rand()%2){
		printf("voce usou o amuleto da saida de fininho e retornou para a sala 0.\n");
		(*per).pos=0;
		return 3;
	}

	printf("voce esta muito assustado,por isso nao conseguiu se concentar para usar o amuleto da saida de fininho.\nBoa Sorte!\n");
	return 0;
}//foge para a sala inicial utilizando o "amuleto da saida de fininho"

int despist(){
	char test, try;

	do{
		printf("voce deseja:\n");
		printf("1-correr entre os escombros e se esconder no alcapao nao tao secreto\n");
		printf("2-se ocultar nas sombras e desaparecer\n");
		printf("3-criar uma ilusao que te ocultara ante os olhos de qualquer criatura\n");
		scanf("%c",&test);
	}while(test=='1' || test=='2' || test=='3');

	try=rand()%2;

	switch(test){
		case '1':// alcapao
			if(try){
				printf("o montro eh mais rapido e bloqueia a sua passagem\n");
				return 0;
			}
			printf("voce entra rapidamente no alcapao,e escondido espera ate o monstro deixar a sala\n");
			return 3;

		case '2':
			if(try){
				printf("esta muito sol para isso\n");
				return 0;
			}
			printf("voce fica totalmente oculto ate que o monstro deixe a sala\n");
			return 3;

		case '3':
			if(try){
				printf("o montro usa oculos uma ilusao sua ilusao nao tem efeito\n");
				return 0;
			}
			printf("voce agora eh invisivel para esse monstro, cuidado para nao tropecar\n");
			return 3;

	}
}//tentar despistar um monstro durante o combate pode nao ser a decisao mais sabia a se tomar

void derrotou(personagem *per, monstro *mon){
	char test;

	(*per).XP+=(*mon).XP;
	if((*per).XP/(*per).lvl==100){
		(*per).lvl++;
		printf("voce alcancou o level %i\n",(*per).lvl);
	}

	printf("o monstro dropou:%s\n",(*mon).drop);
	printf("voce deseja guardar o item no inventario?(s/n)\n");
	scanf("%c",&test);

	if (test=='s'){
		//store((*mon).drop); descomentar***************************************************************************************************************************************************
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
}//providencia o xp e drop

int combat(personagem *per,monstro *mon){
	int test;
	char escolha;

	do{
		escolha=combatMenu(*per,*mon);


		switch(escolha){
			case'a'://test(0-os dois estao vivos,1-mon morre,2-per morre)
				test=perAtk(per,mon);
				if(!test)test=monAtk(per,mon);
				break;
			case'f'://test(0-os dois vivos,2-per morre,3-per foge)
				test=fugir(per);
				if(test)break;
				test=monAtk(per,mon);
				break;
			case 'd'://test(0-os dois vivos,4-per se esconde)
				test=despist();
				if(test) break;
				test=monAtk(per,mon);
				break;
		}

		switch(test){
			case 0:
				continue;
			case 1:
				printf("voce venceu a luta");
				derrotou(per,mon);
				//vai para o mapa
				return 0;
			case 2:
				printf("voce morreu\nGAME OVER");
				//vai para tela inicial
				return 1;
			case 3:
				//vai para o mapa
				return 0;
		}
		
	}while(!test);
}

int main(){
	return 0;
}

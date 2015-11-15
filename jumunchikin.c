#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define monsterNum 15
#define itemNum 20
#define side 6
#define HPinit 70
#define atributeInit 20

char inv[10];

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

//////////////////////save e load

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
	fwrite(&per,sizeof(personagem),1,arq);
	fclose(arq);

	return 0;
}//salva o jogo

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
}//equipa um item no personagem

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
}//carrega o jogo

/////////////////////itens e inventario

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

void store(item it){
	FILE* arq;
	item i2;

	if(!invFind(it.nome,&i2)){
		printf("este item ja existe no inventario\n");
		return;
	}
	
	arq=fopen(inv,"ab");
	fwrite(&it,sizeof(item),1,arq);
	fclose(arq);

	return;
}//adiciona um item no inventario

void invType(char type){
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
}//inprime o nome e o bonus de todos os items de um certo tipo

int invGet(int num,item *it){
	FILE*arq;

	arq=fopen(inv,"rb");
	fseek(arq,(num*sizeof(item)),0);//pula para a struct numero num

	fread(it,sizeof(item),1,arq);

	if(feof(arq))return 1;//não existe o numero
	fclose(arq);

	return 0;//encontrou o item
}//seleciona um item do inventario pelo numero

void invRemove(char nome[25]){
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
}//remove um item do inventario

void invMenu(personagem *per){
	char test,nome[25];
	item it;

	while(1){
		system("cls");
		printf("voce deseja:\n");
		printf("a - mostrar todas as armaduras;\n");
		printf("b - mostrar todas as botas;\n");
		printf("c - mostrar todos os capacetes;\n");
		printf("d - mostrar todas as armas a distancia;\n");
		printf("f - mostrar todas as armas fisicas;\n");
		printf("m - mostrar todas as armas magicas;\n");
		printf("0 - sair.\n");
		printf("Digite a sua escolha:");
		scanf("%c",&test);
		if(test=='0'){
			return;
		}
		if(test!='a' && test!='b' && test!='c' && test!='d' && test!='f' && test!='m'){
			continue;
		}

		invType(test);

		printf("voce deseja:");
		printf("e - equipar um item;\n");
		printf("d - descartar um item;\n");
		printf("0 - sair.\n");
		scanf("%c",&test);
		switch(test){
			case '0':
				return;
			case 'e':
				printf("digite o nome do item:");
				gets(nome);
				itemFind(nome,&it);
				equip(per,it);
				break;
			case 'd':
				printf("digite o nome do item:");
				gets(nome);
				invRemove(nome);
				break;
			default:
				continue;
		}
	}
}

///////////////////////combate

monstro monsterGet(int num){
	FILE*arq;
	monstro mon;

	arq=fopen("mostros.dat","rb");
	fseek(arq,(num*sizeof(monstro)),0);
	fread(&mon,sizeof(monstro),1,arq);
	fclose(arq);

	return mon;
}//encontra um monstro pelo numero

char combatMenu(personagem per,monstro mon){
	char escolha;

	system("cls");

	printf("%s\n",mon.nome);
	printf("HP:%i\n\n",mon.HP);
	printf("%s - lvl:%i\n",per.nome,per.lvl);
	printf("HP:%i/%i\n",per.HP,per.HPx);
	printf("XP:\n");

	do{
		printf("voce deseja:\na-atacar,f-fugir,d-despistar o monstro:");
		scanf("%*c");
		scanf("%c",&escolha);
	}while(escolha!='a'
		&& escolha!='f'
		&& escolha!='d');

	system("cls");

	return escolha;
}//imprime os status do combate e o menu principal do combate

int perAtk(personagem *per,monstro * mon){
	char tipo;
	int dano=0;

	do{
		printf("voce deseja realizar um ataque f-fisico, m-magico ou d-a distancia:\n");
		scanf("%*c");
		scanf("%c",&tipo);
	}while(tipo!='f' && tipo!='m' && tipo!='d');

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
	if(rand()%21){
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

	try=rand()%3;

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
				printf("o montro usa oculos, sua ilusao nao tem efeito\n");
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
		item it;
		itemFind((*mon).drop,&it);
		store(it);
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
			case 'd'://test(0-os dois vivos,3-per se esconde)
				test=despist();
				if(test) break;
				test=monAtk(per,mon);
				break;
		}

		switch(test){
			case 0://os dois vivos
				continue;
			case 1:
				printf("voce venceu a luta");
				derrotou(per,mon);
				//vai para o mapa
				return 1;
			case 2:
				printf("voce morreu\nGAME OVER");
				//vai para tela inicial
				return 0;
			case 3://voce fugiu
				//vai para o mapa
				return 2;
		}
		
	}while(1);
}//mecanica do combate

/////////////////////////mapa e movimentação

int allocar (char **map,personagem per){
	unsigned char i;

	*map=(char*)calloc(side*side,sizeof(char));
	if(*map==NULL)return 1;

	*map[0]=1;//coloca estado na sala 0 para diferenciá-la
	for(i=0;i<3;i++){
		if(per.rooms[i]!=0){
			(*map)[per.rooms[i]] = i+2;
		}
	}

	return 0;
}//aloca o mapa com o tamanho desejado e estabelece as salas chave

void move(char dir, unsigned char *pos){
	switch (dir){
		case 'a':
			if((*pos)%side==0){
				*pos=*pos+(side-1);
				break;
			}
			*pos=*pos-1;
			break;
		case 'd':
			if((*pos)%side==(side-1)){
				*pos=*pos-(side-1);
				break;
			}
			*pos=*pos+1;
			break;
		case 's':
			if(*pos<side){
				*pos=side*side-*pos-1;
				break;
			}
			*pos=*pos-side;
			break;
		case 'w':
			if(*pos>=side*(side-1)){
				*pos=side*side-*pos-1;
				break;
			}
			*pos=*pos+side;
			break;			
	}
}//move o personagem na direção desejada

//////////////////////////////////inicialização

void newGame(personagem *per){
	int i;
	for(i=0;i<3;i++){
		do{
			(*per).rooms[i-2]=rand()%(side*side);
		}while((*per).rooms==0);
	}

	(*per).lvl=1;
	(*per).HPx=HPinit;
	(*per).HP=HPinit;
	(*per).wis=atributeInit;
	(*per).dex=atributeInit;
	(*per).str=atributeInit;
	(*per).pos=0;
	(*per).XP=0;

	for(i=0;i<6;i++){
		((*per).equip[i]).value=0;
		printf("ok\n");
		strcpy(((*per).equip[i]).nome,"\0");
		printf("ok\n");
		((*per).equip[i]).categoria='\0';
		printf("ok\n");
	}
	printf("ok\n");
	do{
		printf("digite o slot em que seu personagem deve ser salvo:(entre 0 e 3)\n");
		scanf("%i",&((*per).slot));
	}while((*per).slot>3 || (*per).slot<0);
	system("cls");

	printf("Voce caminha tranquilamente, quase saltitando, pelas ruas de sua cidade, quando de repente repara em uma estranha loja de antiguidades.");
	printf(" Achando estranho nunca te-la visto apesar de morar nas redondezas voce decide entrar para dar uma olhada.\n Ao entar uma estranha caixa chama a sua atencao.");
	printf(" Nela estava escrito 'jumunchkin, um jogo muito realista'. Voce pergunta a dona da loja quanto custa e ela responde 'se voce gostou pode levar, considere um presente pela");
	printf("inauguracao da loja' voce muito feliz agradece e compra tambem algumas coisas para sua mae.\nChegando em casa voce abre a caixa para ver o que ha dentro e neste momento...");
	system("pause");
	system("cls");
	printf("\n\nVoce ve tudo rodar e o cenario ao seu redor se transformar em algo como uma ruina medieval, voce percebe que algo de errado nao esta certo e acredita que esse nao eh ");
	printf("mais o seu quarto. voce ve uma inscricao escrito SALA ZERO e ouve uma voz dizendo 'bem vindo a ruina dos herois sobreviva se puder HAHAHAHAHAHA.'\n");
	printf("Voce sente um vento frio na espinha e percebe que esta sem roupas, olha ao redor para procura-las, mas nem sinal delas. Voce entao grita e esmurra o ar. Neste instante um ");
	printf("raio de luz sai de seu punho e cria uma explosao ao atingir a parede. Voila agora voce tem poderes magicos");
	system("pause");
	system("cls");
	printf("Voce esta em uma sala ampla com paredes e chao de pedra, ao seu redor existem varios destrocos pedacos de madeira e pedra, provavelmente vindos do telhado, ");
	printf("ja partido com frestas que permitem observar um o azul do ceu, e da decoracao, que antes imponente e bela agora nao passa de escombros\n\n");
	printf("mas voce eh capaz de identificar no meio disso um pedestal de pedra e sobre ele apenas os pes do que um dia ja foi uma estatua e uma inscricao que diz:\n");
	printf("'voce esta agora em um local seguro jovem aventureiro ou aventureira, aproveite este lugar para se preparar para as aventuras que estao a seguir.'");
	printf("\n o resto estva ilegivel apagado pelo tempo. Voce aproveita a seguranca temporaria para se preparar para o que ha a seguir");
}

int start(personagem *per,char **map){
	char test,test2;
	int slot,i;

	do{
	printf("BEM VINDO AO JUMUNCHIKIN\nNOVO JOGO(n)/CARREGAR JOGO(c):");
	scanf("%c",&test);
	}while(test!='c' && test!='n');

	if(test=='c'){
		do{
			printf("digite o slot que sera carregado:\n");
			scanf("%i",&slot);
		}while(slot<0 || slot>3);
		if(load(per,slot)){
			printf("slot invalido.\n");
			return 2;
		}
		system("pause");
	}//carrega um jogo

	if(test=='n'){
		printf("digite o nome do seu personagem:");
		scanf("%*c");
		gets((*per).nome);
		newGame(per);
		test2=save(*per);
		system("pause");
	}//cria um novo personagem

	test=allocar(map,*per);
		if(test){
			printf("erro na alocacao do mapa\n");
			return 1;
	}//aloca mapa

	test2=invSet((*per).slot);//seleciona inventario
	if(test2){
		return 1;
	}
	return 0;
}//inicializa o jogo e o personagem com new game ou load game

int main(){
	personagem per;
	monstro mon;
	char *map;
	char tEnd=1,tQuit=1,tRoom, test,test2;
	
	item it;
	strcpy(it.nome,"Capa Vampirica\0");
	it.categoria='a';
	it.value=80;

	monstro blair;
	blair.magicD = 160;
	blair.fisicalD = 160;
	blair.distD = 160;
	blair.atkType = 'm';
	blair.atk = 250;
	strcpy(blair.nome,"Bruxa Blair\0");
	strcpy(blair.drop,"Camiseta do TUSCA\0");
	blair.HP = 120;
	blair.XP = 0;

	srand(time(NULL));

	do{
		test=start(&per,&map);
		if(test==2)continue;
		if(test==1)break;
		scanf("%*c");
		do{
			system("cls");
			printf("SALA %i\n",per.pos);

			printf("deseja mexer em seu inventario?(s/n):");
			scanf("%c",&test);
			if(test=='s'){
				invMenu(&per);///cuidado olhar argumentos
			}			

			do{
				printf("Digite a direcao que dejeja seguir:norte-w; sul-s; leste-d; oeste-a; quit game-q:");
				scanf("%c",&test);
			}while(test!='w' && test!='a' && test!='s' && test!='d' && test!='q');

			if(test=='q'){
				printf("deseja salvar o seu progresso?(s/n)");
				scanf("%*c");
				scanf("%*c");
				scanf("%c",&test);
				if(test=='s'){
					test2=save(per);
				}
				tQuit=0;
				break;
			}
			else{
				move(test,&(per.pos));
			}

			printf("SALA %i\n",per.pos);

			switch(map[per.pos]){
				case 0://sala qualquer sem importancia
					tRoom=rand()%100;

					if(tRoom>=35){
						mon=monsterGet(rand()%monsterNum);
						tQuit=combat(&per,&mon);
						break;
					}

					if(tRoom>=15){
						printf("nao ha nada na sala\n");
						break;
					}

					if(tRoom>=5){
						printf("voce encontrou uma fonte de cura, e aproveitou para relaxar e tomar um banho, afinal ate os herois ficam cansados(as).");
						printf(" Alem de especialmente fedidos(as) afinal de contas um covil de monstros nao cheiram tao bem assim (na maioria dos casos)\n");
						heal(&per);
						break;
					}

					item it;
					test2=itemGet(rand()%itemNum,&it);
					printf("voce encontrou um '%s' deseja guardar no seu inventario?(s/n)\n",it.nome);
					scanf("%*c");
					scanf("%c",&test);
					if(test=='s'){
						store(it);
					}

					break;
				case 1://sala 0
					printf("SALA ZERO\n\n");
					printf("Voce esta em uma sala ampla com paredes e chao de pedra, ao seu redor existem varios destrocos pedacos de madeira e pedra, provavelmente vindos do telhado, ");
					printf("ja partido com frestas que permitem observar um o azul do ceu, e da decoracao, que antes imponente e bela agora nao passa de escombros\n\n");
					printf("mas voce eh capaz de identificar no meio disso um pedestal de pedra e sobre ele apenas os pes do que um dia ja foi uma estatua e uma inscricao que diz:\n");
					printf("'voce esta agora em um local seguro jovem aventureiro ou aventureira, aproveite este lugar para se preparar para as aventuras que estao a seguir.'");
					printf("\n o resto estva ilegivel apagado pelo tempo. Voce aproveita a seguranca temporaria para se preparar para o que ha a seguir");
					heal(&per);
					break;
				case 2://sala com primeiro boss Alucard
					printf("voce sente seu corpo ser transportado para um local difente das ruinas em que voce estava anteriormnte, voce agora esta em uma sala nao muito grande,mas");
					printf(" muito bem decorada com itens de beleza rara, apesar de ja ser noite a sala esta bem iluminada e ao olhar na direcao da janela voce ve um homem.\n");
					printf("Ele esta vestindo um longo sobretudo preto com detalhes em vermelho por cima da camisa e calca tambem de coras escuras e logo se vira para voce e diz:\n");
					printf("'seja bem vindo ao meu humilde castelo %s,eu estava lhe esperando. Meu nome eh Alucard sou um dos gurdioes das ruinas dos herois, por favor sente-se",per.nome);
					printf(", vou lhe contar a triste historia deste lugar:\n");
					system("pause");
					system("cls");
					printf("Ha muitos anos este lugar era um reduto de aventureiros que que reuniam nos arredores para desafiar as salas e conquistar as recompensas ");
					printf("que aqui existem, ate que um dia a bruxa Blair, que era uma guardia, assasinou o antigo mestre, tomou seu lugar e comecou a enviar os desafiantes para ");
					printf("a morte certa ate que certa vez os aventureiros se revoltaram contra ela. Uma grande batalha foi travada e o resultado foi um massacre. Eles nao puderam ");
					printf("conta as forcas de Blair e tudo o que restou sao os destrocos da sala zero. Apos isso os poucos que fugiram no inicio da batalha lacraram a entada para que " );
					printf("nenhum desavisado caisse em suas garas. Desde entao Blair tem trazido pessoas aqui atravez de armadilhas para que lutem aqui ate a morte certa, destruindo ");
					printf("os ideais do primeiro mestre. Eu nunca pude fazer nada contra o seu poder, mas agora com voce aqui eh diferente, voce tem potencial para mudar isto.");
					system("pause");
					system("cls");
					printf("Torne-se mais forte para poder derrota-la, eu orei lhe ajudar quando a hora chegar.\nComo prova de minha lealdade lhe dou isto:'\n");
					printf("Voce recebeu a 'capa vampirica' e guardou em seu inventario.");
					store(it);
					printf("'um ultimo aviso cuidado com o proximo guardiao ele pode parecer inofensivo mas eh uma fera selvagem e mortal.'");
					system("pause");
					system("cls");
					printf("voce entao retorna para as ruinas");
					per.rooms[0]=0;
					map[per.pos]=0;
					break;
				case 3://sala com segundo boss galinha
					if(per.rooms[0]!=0){
						printf("nao ha nada na sala\n");
						break;
					}
					printf("Ao entrar na sala voce se ve em meio a um palheiro e bem ao centro voce ve uma galinha.\no que voce deseja fazer:");
					printf("1 - matar a galinha e assar sua carne (ela parece suculenta);");
					printf("2 - andar de fininho e passar tentando nao chamar a atencao;");
					printf("outro - gritar por socoro;");
					scanf("%c",&test);
					switch(test){
						case '1':
							printf("A galinha eh mais poderosa que voce e te mata.");
							tQuit=0;
							break;
						case '2':
							printf("voce passa sem cahmar a atencao e se salva");
							per.rooms[1]=0;
							map[per.pos]=0;
							break;
						default:
							printf("Voce chamou a atencao da galinha, sair vivo nao eh mais uma opcao.");
							tQuit=0;
							break;						
					}
					break;				
				case 4:
					if(per.rooms[1]!=0){
						printf("nao ha nada na sala\n");
						break;
					}
					printf("Voce se encontra agora num lugar que aparenta ser uma arena de combate medieval. Blair se encontra a sua frente com seu cajado em posicao de combate");
					printf("Blair diz: 'me surpreende muito que voce tenha chegado ate aqui, achei que fosse apenas mais um idiota, mas voce tem algum valor.'");
					system("pause");
					test=combat(&per,&blair);
					switch(test){
						case 0:
							tQuit = 0;
							break;
						case 1:
							printf("Com a morte de Blair, Alucard assume o comendo das Ruina dos Herois e voce eh nomeado um dos Guardioes da Ruina. \n");
							printf("Novamente, aventureiros se reunem para desafiar as salas e conquistar suas recompensas.\n");
							printf(" Voce jamais volta para casa, afinal, para que voltar para casa?!");
							printf("\n\nFIM.");
							break;
						case 2:
							printf("Voce foi transportado para a SALA ZERO");
							per.pos = 0;
							break;
					}
			}

			if(tQuit==0)break;

			printf("deseja salvar o seu progresso?(s/n)");
			scanf("%c",&test);
			if(test=='s'){
				save(per);
			}

		}while(tQuit);

		printf("deseja voltar ao menu inicial?(s/n)");
		scanf("%*c");
		scanf("%c",&tEnd);
		system("cls");

	}while(tEnd!='n');
	system("pause");
	return 0;
}

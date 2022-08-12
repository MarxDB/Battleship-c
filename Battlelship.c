#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void intestazione(void);
void area_player(int val[][8]);
void area(int val[][8], int valg[][8]);
void inserimento(int val[][8]);
void aut_ins(int valg[][8]);
int main(void)
{
	srand(time(NULL));
	char command[10];
	int ctrl, win1 = 0, win2 = 0;
	int r, c, m = 0, p = 0;
	int val[8][8] = {
			  {3,3,3,3,3,3,3,3},
		          {3,3,3,3,3,3,3,3},
			  {3,3,3,3,3,3,3,3},
			  {3,3,3,3,3,3,3,3},
		          {3,3,3,3,3,3,3,3},
			  {3,3,3,3,3,3,3,3},
			  {3,3,3,3,3,3,3,3},
			  {3,3,3,3,3,3,3,3}
		      };
	int valg[8][8] = {
			  {3,3,3,3,3,3,3,3},
		          {3,3,3,3,3,3,3,3},
			  {3,3,3,3,3,3,3,3},
			  {3,3,3,3,3,3,3,3},
		          {3,3,3,3,3,3,3,3},
			  {3,3,3,3,3,3,3,3},
			  {3,3,3,3,3,3,3,3},
			  {3,3,3,3,3,3,3,3}
		      };
	strcpy( command, "clear" );
	ctrl = system(command);	
	intestazione();
	inserimento(val);
	aut_ins(valg);
	do
	{
		if(m == 0)
		{
			printf("Player: ");
			ctrl = scanf("%d%d", &r, &c);
			while(getchar() != '\n');
			if(valg[r-1][c-1] == 3)
				valg[r-1][c-1] = 4;
			else if(valg[r-1][c-1] == 1)
			{
				valg[r-1][c-1] = 2;
				win1++;
				p = 1;
			}
		}
		m = 0;
		if(p == 0)
		{
			r = rand()%8;
			c = rand()%8;
			if(val[r][c] == 3)
				val[r][c] = 4;
			else if(val[r][c] == 1)
			{
				val[r][c] = 2;
				win2++;
				m = 1;
			}
			ctrl = system(command);
			intestazione();
			area(val, valg);
		}
	}while(win1 < 11 || win2 < 11);

	return(0);
}

void area(int val[8][8], int valg[8][8])
{
	char pp[] = {"XO"};
	int i, j;

	printf("\n\t      CPU:           \t\t   ->PLAYER:");
	printf("\n\t      _ _ _ _ _ _ _ _\t\t     _ _ _ _ _ _ _ _");
	printf("\n\t   1 |");
	
	for(j = 0; (j < 8); j++)
	{
		for(i = 0; (i < 8); i++)
		{
			if(valg[j][i] == 3 || valg[j][i] == 1)
				printf(" |");
			else
			{
				if(valg[j][i] == 2)
					printf("%c|", pp[0]);
				else 
					printf("%c|", pp[1]);
			}
		}
		printf("\t\t  %d |", j+1);
		for(i = 0; (i < 8); i++)
		{
			if(val[j][i] == 3)
				printf(" |");
			else
			{
				if(val[j][i] == 1)
					printf("%c|", pp[0]);
				else 
					printf("%c|", pp[1]);
			}
		}
		if(j != 7)
			printf("\n\t   %d |", j+2); 
	}
	printf("\n\t      1 2 3 4 5 6 7 8\t\t     1 2 3 4 5 6 7 8\n\n"); 
}

void inserimento(int val[8][8])
{
	int r, c, c1, c2, ctrl, err, sup, i, j;
	int casa[2];
	char command[10];
	strcpy( command, "clear" );

	printf("Hai da disposizione 4 navi:\n\t-Una portaerei (5 case)\n\t-Un incrociatore (3 case)");
	printf("\n\t-Un Cacciatorpediniere (2 case)\n\t-Un sommergibile (1 casa)");
	area_player(val);
	printf("\nPosiziona la portaerei sulla casa  d'origine");
	printf("\n(es. 1 1 posiziona nella casella della prima riga sulla prima colonna): ");

	do
	{
		err = 0;
		do
		{
			ctrl = scanf("%d %d", &casa[0], &casa[1]);

			while(getchar() != '\n');
			if(ctrl != 2 && casa[0] < 1 && casa[1] < 1 && casa[0] > 8 && casa[1] > 8)
				printf("\nLa casella selezionata non esiste, reinserire: ");
		}while(ctrl != 2 && casa[0] < 1 && casa[1] < 1 && casa[0] > 8 && casa[1] > 8);
		
		printf("Vuoi posizionarla in verticale (1) o orizzontale(2)? ");

		do
		{
			ctrl = scanf("%d", &sup);
			while(getchar() != '\n');
			if(sup != 1 && sup != 2)
				printf("\nInserisci '1' o '2':");
		}while(sup != 1 && sup != 2);

		if(sup == 1 && casa[0] > 4)
		{
			printf("\nLa portaerei non puo' essere posizionata qui, reinserire: ");
			err++;
		}
		else if(sup == 2 && casa[1] > 4)
		{
			printf("\nLa portaerei non puo' essere posizionata qui, reinserire: ");
			err++;
		}
	}while(err > 0);
	
	r = casa[0] - 1;
	c = casa[1] - 1;
	
	for(i = 0; (i < 5); i++)
	{
		val[r][c] = 1;
		if (sup == 1)
			r++;
		else
			c++;
	}
	ctrl = system(command);	
	area_player(val);

	printf("\nPosiziona l'incrociatore sulla casa  d'origine: ");
	do
	{
		err = 0;
		do
		{
			ctrl = scanf("%d %d", &casa[0], &casa[1]);

			while(getchar() != '\n');
			if(ctrl != 2 && casa[0] < 1 && casa[1] < 1 && casa[0] > 8 && casa[1] > 8)
				printf("\nLa casella selezionata non esiste, reinserire: ");
		}while(ctrl != 2 && casa[0] < 1 && casa[1] < 1 && casa[0] > 8 && casa[1] > 8);
		
		printf("Vuoi posizionarla in verticale (1) o orizzontale(2)? ");

		do
		{
			ctrl = scanf("%d", &sup);
			while(getchar() != '\n');
			if(sup != 1 && sup != 2)
				printf("\nInserisci '1' o '2':");
		}while(sup != 1 && sup != 2);

		if(sup == 1 && casa[0] > 6)
		{
			printf("\nL'incrociatore non puo' essere posizionato qui, reinserire: ");
			err++;
		}
		else if(sup == 2 && casa[1] > 6)
		{
			printf("\nL'incrociatore non puo' essere posizionato qui, reinserire: ");
			err++;
		}
	
		r = casa[0] - 1;
		c = casa[1] - 1;
		c1 = r;
		c2 = c;
			
		for(j = 0; (j < 3); j++)
		{
			if(val[c1][c2] != 3)
			{
				err++;
			}				
			if (sup == 1)
				c1++;
			else
				c2++;
		}

		for(i = 0; (i < 3); i++)
		{
			
			if(err == 0)
			{
				val[r][c] = 1;
				if (sup == 1)
					r++;
				else
					c++;
			}
			else
				printf("\nUna o piu' caselle sono gia' occupate, reinserire: ");			
		}

	}while(err > 0);
	ctrl = system(command);	
	area_player(val);

	printf("\nPosiziona il cacciatorpediniere sulla casa  d'origine: ");
	do
	{
		err = 0;
		do
		{
			ctrl = scanf("%d %d", &casa[0], &casa[1]);

			while(getchar() != '\n');
			if(ctrl != 2 && casa[0] < 1 && casa[1] < 1 && casa[0] > 8 && casa[1] > 8)
				printf("\nLa casella selezionata non esiste, reinserire: ");
		}while(ctrl != 2 && casa[0] < 1 && casa[1] < 1 && casa[0] > 8 && casa[1] > 8);
		
		printf("Vuoi posizionarla in verticale (1) o orizzontale(2)? ");

		do
		{
			ctrl = scanf("%d", &sup);
			while(getchar() != '\n');
			if(sup != 1 && sup != 2)
				printf("\nInserisci '1' o '2':");
		}while(sup != 1 && sup != 2);

		if(sup == 1 && casa[0] > 7)
		{
			printf("\nIl cacciatorpediniere non puo' essere posizionato qui, reinserire: ");
			err++;
		}
		else if(sup == 2 && casa[1] > 7)
		{
			printf("\nIl cacciatorpediniere non puo' essere posizionato qui, reinserire: ");
			err++;
		}
	
		r = casa[0] - 1;
		c = casa[1] - 1;
		c1 = r;
		c2 = c;
			
		for(j = 0; (j < 2); j++)
		{
			if(val[c1][c2] != 3)
			{
				err++;
			}				
			if (sup == 1)
				c1++;
			else
				c2++;
		}

		for(i = 0; (i < 2); i++)
		{
			
			if(err == 0)
			{
				val[r][c] = 1;
				if (sup == 1)
					r++;
				else
					c++;
			}
			else
				printf("\nUna o piu' caselle sono gia' occupate, reinserire: ");			
		}

	}while(err > 0);
	ctrl = system(command);	
	area_player(val);

	printf("\nPosiziona il sommergibile sulla casa  d'origine: ");
	do
	{
		err = 0;
		do
		{
			ctrl = scanf("%d %d", &casa[0], &casa[1]);

			while(getchar() != '\n');
			if(ctrl != 2 && casa[0] < 1 && casa[1] < 1 && casa[0] > 8 && casa[1] > 8)
				printf("\nLa casella selezionata non esiste, reinserire: ");
		}while(ctrl != 2 && casa[0] < 1 && casa[1] < 1 && casa[0] > 8 && casa[1] > 8);

		r = casa[0] - 1;
		c = casa[1] - 1;

		if(val[r][c] != 3)
		{
			printf("\nLa casella e' già occupata, reinserire: ");
			err++;
		}
		else
			val[r][c] = 1;
	}while(err > 0);
	ctrl = system(command);	
	area_player(val);

}

void aut_ins(int val[8][8])
{
	int r, c, sup, err, i, j;

	do
	{
		err = 0;
		sup = rand()%2;
		r = rand()%8;
		c = rand()%8;
		
		if(sup == 0 && r > 3)
			err++;
		else if(sup == 1 && c > 3)
			err++;
	}while(err > 0);

	for(i = 0; (i < 5); i++)
	{
		val[r][c] = 1;
		if (sup == 1)
			r++;
		else
			c++;
	}

	do
	{
		err = 0;
		sup = rand()%2;
		r = rand()%8;
		c = rand()%8;
		
		if(sup == 0 && r > 5)
			err++;
		else if(sup == 1 && c > 5)
			err++;
		
		for(j = 0; (j < 3); j++)
		{
			if(val[r][c] != 3)
			{
				err++;
			}				
			if (sup == 0)
				r++;
			else
				c++;
		}
		if(err == 0)
		{
			for(i = 0; (i < 3); i++)
			{
				val[r][c] = 1;
				if (sup == 1)
					r++;
				else
					c++;
			}
		}

	}while(err > 0);
	
	do
	{
		err = 0;
		sup = rand()%2;
		r = rand()%8;
		c = rand()%8;
		
		if(sup == 0 && r > 6)
			err++;
		else if(sup == 1 && c > 6)
			err++;
		
		for(j = 0; (j < 2); j++)
		{
			if(val[r][c] != 3)
			{
				err++;
			}				
			if (sup == 0)
				r++;
			else
				c++;
		}
		if(err == 0)
		{
			for(i = 0; (i < 2); i++)
			{
				val[r][c] = 1;
				if (sup == 1)
					r++;
				else
					c++;
			}
		}

	}while(err > 0);

	do
	{
		err = 0;
		r = rand()%8;
		c = rand()%8;
		if(val[r][c] != 3)
			err++;
		else
			val[r][c] = 1;

	}while(err > 0);
}

void area_player(int val[8][8])
{
	char pp[] = {"XO"};
	int i, j;
	
	printf("\n\t\t\t      _ _ _ _ _ _ _ _");
	printf("\n\t\t\t   1 |");
	
	for(j = 0; (j < 8); j++)
	{
		for(i = 0; (i < 8); i++)
		{
			if(val[j][i] == 3)
				printf(" |");
			else
			{
				if(val[j][i] == 1)
					printf("%c|", pp[0]);
				else 
					printf("%c|", pp[1]);
			}
		}
		if(j != 7)
			printf("\n\t\t\t   %d |", j+2); 
	}
	printf("\n\t\t\t      1 2 3 4 5 6 7 8\n\n"); 
}

void intestazione(void)
{
	printf("\n\t***********************************************************");
	printf("\n\t********************  BATTLESHIP!  ************************");
	printf("\n\t***********************************************************");
	printf("\n\n");
}





		








	
		     

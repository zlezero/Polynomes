/******************************************************************************/
/* POLYNOMES_C                                                                */
/******************************************************************************/

//toutes déclarations dans le fichier .h
#include "polynomes.h"

/******************************************************************************/
/* main                                                                       */
/******************************************************************************/
int main(void)
{
	system("clear");

	//Test affichage
	Polynome p;
	initPolynome(&p);

	//str2Polynome("5x7-x^6-x5  +-2- 12x^5+2x-3", &p);
	str2Polynome("3X^2-X+5", &p);

	affichePolynome(p); 
	printf("\n");
	
	//Test de la mutiplication
	Polynome p_mult;
	Monome m_mult = {-2, 2};

	initPolynome(&p_mult);
	str2Polynome("X^5-3X+2", &p_mult);

	multiplieMonomePolynome(&p_mult, m_mult);

	printf("Multiplication de : -2X²x(X⁵-3X+2) = ");

	affichePolynome(p_mult);
	printf("\n");

	//Test ajout monôme à un polynôme

	Polynome p_Ajout0;
	Monome m_Ajout = {-2, 3};

	initPolynome(&p_Ajout0);
	str2Polynome("X^5-3X^2+2", &p_Ajout0);

	printf("Ajout de : -2X³+(");
	affichePolynome(p_Ajout0);
	printf(") = ");

	ajouteMonomePolynome(&p_Ajout0, m_Ajout);
	affichePolynome(p_Ajout0);
	printf("\n");

	//Test ajout polynôme à un autre polynôme

	Polynome p_Ajout1, p_Ajout2;
	initPolynome(&p_Ajout1);
	initPolynome(&p_Ajout2);

	str2Polynome("X^5-3X+2", &p_Ajout1);
	str2Polynome("X^5-3X+2", &p_Ajout2);

	printf("Ajout de : ");
	affichePolynome(p_Ajout1);
	printf(" avec : ");
	affichePolynome(p_Ajout2);
	printf(" = ");

	ajoutePolynomePolynome1(&p_Ajout1, &p_Ajout2);

	affichePolynome(p_Ajout1);
	printf("\n");

	//Test ajout polynôme à un autre polynôme 2

	str2Polynome("X^5-3X+2", &p_Ajout1);

	printf("Ajout de : ");
	affichePolynome(p_Ajout1);
	printf(" avec : ");
	affichePolynome(p_Ajout2);
	printf(" = ");

	ajoutePolynomePolynome2(&p_Ajout1, &p_Ajout2);

	affichePolynome(p_Ajout1);
	printf("\n");
	
	//Test multiplication polynôme à un autre polynôme

	Polynome p_Mult1, p_Mult2;
	initPolynome(&p_Mult1);
	initPolynome(&p_Mult2);

	str2Polynome("X^5-3X+2", &p_Mult1);
	str2Polynome("X^5-3X+2", &p_Mult2);

	printf("Multiplication de : ");
	affichePolynome(p_Ajout1);
	printf(" avec : ");
	affichePolynome(p_Ajout2);
	printf(" = ");

	multipliePolynomePolynome(&p_Mult1, &p_Mult2);

	affichePolynome(p_Mult1);

	//Fin
	printf("\n");
	return 0;
}

/******************************************************************************/
/* initPolynomes - initialise le polynome fourni                              */
/*                                                                            */
/* INPUT  : polynome (pointeur) à initialiser                                 */
/* OUTPUT : néant                                                             */
/******************************************************************************/
void initPolynome(Polynome *p)
{
	p->nb_monomes = 0;
}

/******************************************************************************/
/* affichePolynome - self explained                                           */
/*                                                                            */
/* INPUT  : polynome à afficher                                               */
/* OUTPUT : néant                                                             */
/******************************************************************************/
void affichePolynome(Polynome p)
{
	int i;

	for (i=0;i<p.nb_monomes;i++) //On boucle sur tout les différents polynômes
	{
		if (p.tab_monomes[i].coeff == 1) // Cas où c'est X¹
			printf("X^%d", p.tab_monomes[i].degre);
		else if (p.tab_monomes[i].coeff < 0) //Sinon si on obtient nX avec n négatif
		{
			if (p.tab_monomes[i].degre > 1 && p.tab_monomes[i].coeff == -1) //Dans le cas où on a -X^n avec n > 1
				printf("-X^%d", p.tab_monomes[i].degre);
			else if (p.tab_monomes[i].degre > 1 && p.tab_monomes[i].coeff < -1) //Sinon si le monôme est nX^m avec n < -1 et m > 1
				printf("%dX^%d", p.tab_monomes[i].coeff, p.tab_monomes[i].degre);
			else if (p.tab_monomes[i].coeff == -1) //Sinon si nous avons -X (degré égal à 1 et coeff égal à -1)
				printf("-X");
			else //Sinon si le coeff est < -1 et un degré 1
				printf("%dX", p.tab_monomes[i].coeff);
		}	
		else if (p.tab_monomes[i].degre == 1) //Si nX¹ avec n > 1
			printf("%dX", p.tab_monomes[i].coeff);
		else if (!p.tab_monomes[i].degre) // Si nX⁰ ce qui veut dire que nous avons juste n
			printf("%d", p.tab_monomes[i].coeff);
		else //Si nX^m avec n > 1 et m > 1
			printf("%dX^%d", p.tab_monomes[i].coeff, p.tab_monomes[i].degre); 
		
		if ((i + 1) < p.nb_monomes && p.tab_monomes[i+1].coeff >= 0) //Pour ajouter un + entre chaque monôme et enlever le + en fin de chaîne 
			printf("+");
		
	}
}

/******************************************************************************/
/* multiplieMonomePolynome - Multiplie un polynôme donné par un monôme        */
/*                                                                            */
/* INPUT  : polynome à multiplier + monôme                                    */
/* OUTPUT : néant                                                             */
/******************************************************************************/

void multiplieMonomePolynome(Polynome *p, Monome m)
{
	int i;

	for (i=0;i<p->nb_monomes;i++) //Pour chaque monôme du polynôme
	{
		p->tab_monomes[i].coeff *= m.coeff; //On le multiplie par le coeff donné du monôme
		p->tab_monomes[i].degre += m.degre; //On additionne les dégrés avec le monôme donné
	}
}

/******************************************************************************/
/* ajouteMonomePolynome - Ajoute un monôme à un polynôme                      */
/*                                                                            */
/* INPUT  : Monôme à ajouter + polynôme                                       */
/* OUTPUT : néant                                                             */
/******************************************************************************/

void ajouteMonomePolynome(Polynome *p, Monome m)
{
	int i, l;

	
	for (i=0;i<p->nb_monomes;i++)
	{
		if (p->tab_monomes[i].degre == m.degre)
		{
			p->tab_monomes[i].coeff += m.coeff;
			return;
		}
	}

	for (l=0;l<p->nb_monomes;l++)
	{
		if (p->tab_monomes[l].degre < m.degre)
		{
			p->nb_monomes += 1;

			for (i=p->nb_monomes;i>l;i--)
			{
				p->tab_monomes[i] = p->tab_monomes[i-1];
			}

			p->tab_monomes[l] = m;

			break;
		} 


	}

}

/******************************************************************************/
/* ajoutePolynomePolynome1 - Ajoute un polynôme à un autre polynôme           */
/*                                                                            */
/* INPUT  : Les 2 polynômes à multiplier                                      */
/* OUTPUT : néant                                                             */
/******************************************************************************/

void ajoutePolynomePolynome1(Polynome *p1, Polynome *p2)
{
	int i;

	for (i=0;i<p2->nb_monomes;i++)
	{
		ajouteMonomePolynome(p1, p2->tab_monomes[i]);
	}

}

/******************************************************************************/
/* ajoutePolynomePolynome2 - Ajoute un polynôme à un autre polynôme           */
/*                                                                            */
/* INPUT  : Les 2 polynômes à ajouter                                         */
/* OUTPUT : néant                                                             */
/******************************************************************************/

void ajoutePolynomePolynome2(Polynome *p1, Polynome *p2)
{

}

/******************************************************************************/
/* multipliePolynomePolynome - Multiplie un polynôme à un autre polynôme      */
/*                                                                            */
/* INPUT  : Les 2 polynômes à multiplier                                      */
/* OUTPUT : néant                                                             */
/******************************************************************************/

void multipliePolynomePolynome(Polynome *p1, Polynome *p2)
{

}

/******************************************************************************/
/* standardiseDescription - ajoute des + devant les -, vire les char étranges */
/* et change 'x' en 'X', remplace X par 1X                                    */
/*                                                                            */
/* INPUT : s est la chaîne source (celle qui contient une description         */
/* réduite du polynôme                                                        */
/*         d est la chaîne de destination dans laquelle on ecrit              */
/* une description standardisée                                               */
/* OUPUT : néant                                                              */
/******************************************************************************/
void standardiseDescription(char *s, char *d)
{
	char *l = s, *e = d;
	//l pointeur qui lit la chaîne source
	//e pointeur qui écrit la chaîne destination

	while (*l != '\0')
	{
		if (*l == '-') //remplacer - par +-
		{
			*e = '+';
			e++;
			*e = '-';
		}
		else
		{
			if (*l == 'x' || *l == 'X') // X ou x
			{
				if (*(l - 1) < '0' || *(l - 1) > '9') // ...non précédé d'un chiffre
				{
					*e = '1';
					e++;
					*e = 'X';
				}
				else
					*e = 'X';
			}
			// autre cas on recopie
			else if ((*l >= '0' && *l <= '9') || *l == '+' || *l == '^')
				*e = *l;
			else // caractères erronés
			{
				e--;           // on recule
				if (*l != ' ') // et on signale (sauf si espace)
					fprintf(stderr, "Err: caractère '%c' ignoré\n", *l);
			}
		}

		e++;
		l++;
	}
	*e = '\0'; // fin de chaîne
}

/******************************************************************************/
/* str2Polynome - lit un polynome dans une string et charge un Polynome       */
/* format pour écrire les polynômes                                           */
/*     X^3 - X - 1, 1X^3 - 1X^1 - 1 sont acceptés                             */
/*                                                                            */
/* INPUT  : str chaîne de caractères qui décrit le polynôme                   */
/*          p   polynôme dans lequel écrire le résultat                       */
/* OUTPUT : néant                                                             */
/******************************************************************************/
void str2Polynome(char *str, Polynome *p)
{
	char *tok, *ptr;
	int coeff, degre;
	int nb_monomes = 0;

	//on commence par standardiser la description
	//dans une chaîne assez longue pur la contenir
	char *str2 = (char *)malloc(strlen(str) + 50);

	//la nouvelle description
	standardiseDescription(str, str2); // Nettoie et normalise

	tok = strtok(str2, "+"); // Récupération d'un "token" grâce au séparateur +

	while (tok != NULL)
	{
		ptr = strchr(tok, 'X'); // Y a-t-il un X dans le token?
		if (ptr)                // Oui, il y a un X
		{
			//Y a-t'il un '^nombre' derriere le X
			if (sscanf(tok, "%dX^%d", &coeff, &degre) != 2) // Cas 5X^2
			{
				if (sscanf(tok, "%dX%d", &coeff, &degre) != 2) // Cas 5X2
				{
					if ((sscanf(tok, "X%d", &degre) == 1) || (sscanf(tok, "X^%d", &degre) == 1)) // Cas X2 ou X^2
						coeff = 1;
					else if (sscanf(tok, "%dX", &coeff) == 1) // Cas 5X
						degre = 1;
					else // ...sinon on considère qu'il s'agit de X
					{
						coeff = 1;
						degre = 1;
					}
				}
			}
		}
		else // Pas de X
		{
			sscanf(tok, "%d", &coeff);
			degre = 0;
		}
		p->tab_monomes[nb_monomes].coeff = coeff;
		p->tab_monomes[nb_monomes].degre = degre;
		nb_monomes++;

		tok = strtok(NULL, "+");
	}

	p->nb_monomes = nb_monomes;
	free(str2);
}
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
	Polynome p, p_res;
	initPolynome(&p);
	initPolynome(&p_res);

	//str2Polynome("5x7-x^6-x5  +-2- 12x^5+2x-3", &p);
	str2Polynome("3X^2-X+5", &p);

	printf("Affichage du polynôme : ");
	affichePolynome(p); 
	printf("\n \n"); 
	
	//Test de la mutiplication
	Polynome p_mult;
	Monome m_mult = {-2, 2};

	initPolynome(&p_mult);
	str2Polynome("X^5-3X+2", &p_mult);

	multiplieMonomePolynome(p_mult, m_mult, &p_res);

	printf("Multiplication de : -2X²x(X⁵-3X+2) = ");

	affichePolynome(p_res);
	printf("\n \n"); 

	//Test ajout monôme à un polynôme

	Polynome p_Ajout0;
	Monome m_Ajout = {-2, 3};

	initPolynome(&p_Ajout0);
	str2Polynome("X^5-3X^3", &p_Ajout0);

	printf("Ajout de monôme : -2X³+(");
	affichePolynome(p_Ajout0);
	printf(") = ");

	ajouteMonomePolynome(p_Ajout0, m_Ajout, &p_res);
	affichePolynome(p_res);
	printf("\n \n");

	//Test ajout polynôme à un autre polynôme

	Polynome p_Ajout1, p_Ajout2;
	initPolynome(&p_Ajout1);
	initPolynome(&p_Ajout2);

	//str2Polynome("X^5-3X^2+2", &p_Ajout1);
	//str2Polynome("X^6-3X^3+2", &p_Ajout2);
	str2Polynome("2X^7+X^5-3X^2-3X-3", &p_Ajout1);
	str2Polynome("X^7+2X^6", &p_Ajout2);

	printf("Ajout de polynôme à polynôme 1 : ");
	affichePolynome(p_Ajout1);
	printf(" avec : ");
	affichePolynome(p_Ajout2);
	printf(" = ");

	ajoutePolynomePolynome1(p_Ajout1, p_Ajout2, &p_res);

	affichePolynome(p_res);
	printf("\n");

	//Test ajout polynôme à un autre polynôme 2

	printf("Ajout de polynôme à polynôme 2 : ");
	affichePolynome(p_Ajout1);
	printf(" avec : ");
	affichePolynome(p_Ajout2);
	printf(" = ");

	ajoutePolynomePolynome2(p_Ajout1, p_Ajout2, &p_res);

	affichePolynome(p_res);
	printf("\n \n");

	//Test multiplication polynôme à un autre polynôme

	Polynome p_Mult1, p_Mult2;
	initPolynome(&p_Mult1);
	initPolynome(&p_Mult2);

	str2Polynome("-3x^2+4x-2", &p_Mult1);
	str2Polynome("x^3-x+1", &p_Mult2);

	initPolynome(&p_res);

	printf("Multiplication de : ");
	affichePolynome(p_Mult1);
	printf(" avec : ");
	affichePolynome(p_Mult2);
	printf(" = ");

	multipliePolynomePolynome(p_Mult1, p_Mult2, &p_res);

	affichePolynome(p_res);

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

	if (!p.nb_monomes)
		printf("0");

	for (i = 0; i < p.nb_monomes; i++) //On boucle sur tout les différents polynômes
	{
		if (p.tab_monomes[i].coeff == 1 && p.tab_monomes[i].degre == 1)
			printf("X");
		else if (p.tab_monomes[i].coeff == 1 && p.tab_monomes[i].degre != 0) // Cas où c'est 1X
			printf("X^%d", p.tab_monomes[i].degre);
		else if (!p.tab_monomes[i].degre) // Si nX⁰ ce qui veut dire que nous avons juste n
			printf("%d", p.tab_monomes[i].coeff);
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
		else if (p.tab_monomes[i].coeff != 0)//Si nX^m avec n > 1 et m > 1
			printf("%dX^%d", p.tab_monomes[i].coeff, p.tab_monomes[i].degre);

		if ((i + 1) < p.nb_monomes && p.tab_monomes[i + 1].coeff >= 1) //Pour ajouter un + entre chaque monôme et enlever le + en fin de chaîne
			printf("+");
	}
}

/******************************************************************************/
/* multiplieMonomePolynome - Multiplie un polynôme donné par un monôme        */
/*                                                                            */
/* INPUT  : polynome à multiplier + monôme                                    */
/* OUTPUT : néant                                                             */
/******************************************************************************/

void multiplieMonomePolynome(Polynome p, Monome m, Polynome *resultat)
{
	int i;
	Polynome Resultat;

	initPolynome(&Resultat);

	Resultat = p;

	for (i = 0; i < p.nb_monomes; i++) //Pour chaque monôme du polynôme
	{
		Resultat.tab_monomes[i].coeff *= m.coeff; //On le multiplie par le coeff donné du monôme
		Resultat.tab_monomes[i].degre += m.degre; //On additionne les dégrés avec le monôme donné
	}

	*resultat = Resultat;
}

/******************************************************************************/
/* ajouteMonomePolynome - Ajoute un monôme à un polynôme                      */
/*                                                                            */
/* INPUT  : Monôme à ajouter + polynôme                                       */
/* OUTPUT : néant                                                             */
/******************************************************************************/

void ajouteMonomePolynome(Polynome p, Monome m, Polynome *resultat)
{
	int i, l=0;

	Polynome Resultat;
	Resultat = p;

	for (i = 0; i < Resultat.nb_monomes; i++) //Pour chaque monôme du polynôme
	{
		if (Resultat.tab_monomes[i].degre == m.degre) //On vérifie si le dégré du monôme donné est le même
		{
			Resultat.tab_monomes[i].coeff += m.coeff; //Alors on ajoute les 2 coefficients
			*resultat = Resultat;
			return;	//Et on quitte la fonction
		}
		else if (Resultat.tab_monomes[i].degre < m.degre || (Resultat.tab_monomes[i].degre > m.degre && i == Resultat.nb_monomes - 1)) //On vérifie pour placer le monôme donné au bon endroit
		{
			Resultat.nb_monomes += 1; //On ajoute un monôme au compte total

			if (Resultat.tab_monomes[i].degre > m.degre)
				i += 1;

			for (l = Resultat.nb_monomes; l > i; l--) //On décale tous les monômes qui ont un degré inférieur au monôme donné
			{
				Resultat.tab_monomes[l] = Resultat.tab_monomes[l - 1];
			}

			Resultat.tab_monomes[i] = m; //On insère le monôme donné au bon endroit

			break; //On quitte la boucle puisqu'on a fini le travail
		}


	}

	*resultat = Resultat;
}

/******************************************************************************/
/* ajoutePolynomePolynome1 - Ajoute un polynôme à un autre polynôme           */
/* Compléxité : O(n³) dans le pire des cas sinon O(n²) dans le meilleur       */
/* INPUT  : Les 2 polynômes à multiplier                                      */
/* OUTPUT : néant                                                             */
/******************************************************************************/

void ajoutePolynomePolynome1(Polynome p1, Polynome p2, Polynome *resultat)
{
	int i;

	Polynome Resultat, Max;

	if (p2.nb_monomes > p1.nb_monomes)
	{
		Resultat = p1;
		Max = p2;
	}
	else
	{
		Resultat = p2;
		Max = p1;
	}

	for (i = 0; i < Max.nb_monomes; i++) //Pour chaque monôme du polynôme donné
		ajouteMonomePolynome(Resultat, Max.tab_monomes[i], &Resultat); //On ajoute le ième monôme du polynôme

	*resultat = Resultat;
}

/******************************************************************************/
/* ajoutePolynomePolynome2 - Ajoute un polynôme à un autre polynôme           */
/* Compléxité : linéaire donc O(n*m)                                          */
/* INPUT  : Les 2 polynômes à ajouter                                         */
/* OUTPUT : néant                                                             */
/******************************************************************************/

void ajoutePolynomePolynome2(Polynome p1, Polynome p2, Polynome *resultat)
{
	int i1 = 0, i2 = 0, j=0; //On initialise les compteurs afin de lire dans chaque polynôme le monôme que l'on souhaite

	Polynome Resultat;
	initPolynome(&Resultat);
	initPolynome(resultat);

	while(i1 < p1.nb_monomes || i2 < p2.nb_monomes) //On boucle tant qu'un des compteurs n'a pas atteint la taille du nb_monome des polynômes donnés 
	{
		if (p1.tab_monomes[i1].degre > p2.tab_monomes[i2].degre) //Si le degré du monôme i1 du premier polynôme est supérieur au dégré du monôme i2 du second
		{
			Resultat.tab_monomes[j] = p1.tab_monomes[i1]; //Alors le polynôme résultat aura comme monôme max le monôme de i1 du polynôme 1
			i1++;
		}
		else if(p1.tab_monomes[i1].degre < p2.tab_monomes[i2].degre) //Sinon s'il s'agit de l'inverse (sans l'égalité)
		{
			Resultat.tab_monomes[j] = p2.tab_monomes[i2]; //Alors le polynôme résultat aura comme monôme max le monôme de i2 du polynôme 2
			i2++;
		}
		else //Sinon les monômes ont le même degré
		{
			Resultat.tab_monomes[j].coeff = p1.tab_monomes[i1].coeff + p2.tab_monomes[i2].coeff; //On ajoute alors leurs coéfficients
			Resultat.tab_monomes[j].degre = p1.tab_monomes[i1].degre; //Comme les degrés sont les mêmes on met le même
			i2++;
			i1++;
		}

		printf("I1 : %d\n", i1);
		printf("I2 : %d\n", i2);

		//On incrémente les compteurs
		j++;
		Resultat.nb_monomes++;
	 }

	 *resultat = Resultat;
}

/******************************************************************************/
/* multipliePolynomePolynome - Multiplie un polynôme à un autre polynôme      */
/*                                                                            */
/* INPUT  : Les 2 polynômes à multiplier                                      */
/* OUTPUT : néant                                                             */
/******************************************************************************/

void multipliePolynomePolynome(Polynome p1, Polynome p2, Polynome *resultat)
{
	Polynome stock;
	initPolynome(&stock);
	//int i;

	/*stock = p1;
	multiplieMonomePolynome(stock, p2.tab_monomes[0], resultat);
	ajoutePolynomePolynome1(*resultat, stock, resultat);
	*resultat = stock;
	multiplieMonomePolynome(p1, p2.tab_monomes[1], &stock);
	printf("\n Affichage stock : ");
	affichePolynome(stock)


	printf("\n Affichage résultat : ");
	ajoutePolynomePolynome1(*resultat, stock, resultat);
	affichePolynome(*resultat);
	printf("\n Affichage fin : "); */

	stock = p2;
	multiplieMonomePolynome(stock, p1.tab_monomes[0], resultat);
	ajoutePolynomePolynome1(*resultat, stock, resultat);
	multiplieMonomePolynome(stock, p1.tab_monomes[1], resultat);
	ajoutePolynomePolynome1(*resultat, stock, resultat);
	multiplieMonomePolynome(stock, p1.tab_monomes[2], resultat);
	ajoutePolynomePolynome1(*resultat, stock, resultat);
	
	/*for(i = 0; i< p1.nb_monomes;i++)
	{
		//initPolynome(&stock);
		stock = p2;
		multiplieMonomePolynome(stock, p1.tab_monomes[i], &stock);
		ajoutePolynomePolynome1(*resultat, stock, resultat);
	}*/

	/*for (i=1; i<0;i++)
	{	
		printf("boucle");
		multiplieMonomePolynome(p1, p2->tab_monomes[i], &stock);
		affichePolynome(stock);
		printf("\n resultat :");
		ajoutePolynomePolynome1(&stock, resultat, resultat);
		affichePolynome(*resultat);
		printf("\n stock : ");
	}
*/
	//resultat->nb_monomes=7;
	
}

/******************************************************************************/
/* puissancePolynome - Multiplie un polynôme à un autre polynôme              */
/*                                                                            */
/* INPUT  : Les 2 polynômes à multiplier                                      */
/* OUTPUT : néant                                                             */
/******************************************************************************/

void puissancePolynome(Polynome p1, int puissance, Polynome *resultat)
{
	int i;
	
	for(i=0;i<puissance;i++)
	{
		multipliePolynomePolynome(p1, p1, resultat);
		
		if (p1.nb_monomes > 50)
		{
			printf("Bouchon = trop loin !");
			break;
		}
	}
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
				e--;		   // on recule
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
		if (ptr)				// Oui, il y a un X
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

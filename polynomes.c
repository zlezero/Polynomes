/******************************************************************************/
/* POLYNOMES_C                                                                */
/******************************************************************************/

//toutes déclarations dans le fichier .h
#include "polynomes.h"

/******************************************************************************/
/* Main                                                                       */
/******************************************************************************/
int main(void)
{

	Main_Menu(); //On lance le menu principal

	//Fin du programme

	system("clear");

	printf("Merci d'avoir utilisé notre programme !");
	printf("\n");
	
	return 0;
}

/******************************************************************************/
/*                                                                            */
/*                        Fonctions des polynômes                             */
/*                        (tous réduits et triés)                             */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* initPolynomes - initialise le polynome fourni                              */
/*                                                                            */
/* INPUT  : Polynôme (pointeur) à initialiser                                 */
/* OUTPUT : néant                                                             */
/******************************************************************************/

void initPolynome(Polynome *p)
{
	p->nb_monomes = 0;
}

/******************************************************************************/
/* affichePolynome - Affiche un polynôme                                      */
/* Compléxité : O(n) avec n la taille du tableau                              */
/* INPUT  : Polynôme à afficher                                               */
/* OUTPUT : néant                                                             */
/******************************************************************************/

void affichePolynome(Polynome p)
{
	int i;

	if (!p.nb_monomes)
		printf("0");

	for (i = 0; i < p.nb_monomes; i++) //On boucle sur tout les différents polynômes
	{
		if (p.tab_monomes[i].coeff == 1 && p.tab_monomes[i].degre == 1) // Si on a X
			printf("X");
		else if (p.tab_monomes[i].coeff == 1 && p.tab_monomes[i].degre != 0) // Cas où c'est 1X^n
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
		else if (p.tab_monomes[i].coeff != 0) //Si nX^m avec n > 1 et m > 1
			printf("%dX^%d", p.tab_monomes[i].coeff, p.tab_monomes[i].degre);

		if ((i + 1) < p.nb_monomes && p.tab_monomes[i + 1].coeff >= 1) //Pour ajouter un + entre chaque monôme et enlever le + en fin de chaîne
			printf("+");
	}
}

/******************************************************************************/
/* multiplieMonomePolynome - Multiplie un polynôme donné par un monôme        */
/* Compléxité :          n = taille du tableau           O(n)                 */
/* INPUT  : Polynôme à multiplier + Monôme + Polynôme résultat                */
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
/* Compléxité : n = taille du tableau. dans le pire des cas O(n²)             */
/* INPUT  : Monôme à ajouter + Polynôme à ajouter  + Polynôme résultat        */
/* OUTPUT : néant                                                             */
/******************************************************************************/

void ajouteMonomePolynome(Polynome p, Monome m, Polynome *resultat)
{
	int i, l = 0;

	Polynome Resultat;
	Resultat = p;

	for (i = 0; i < Resultat.nb_monomes; i++) //Pour chaque monôme du polynôme
	{
		if (Resultat.tab_monomes[i].degre == m.degre) //On vérifie si le dégré du monôme donné est le même
		{
			Resultat.tab_monomes[i].coeff += m.coeff; //Alors on ajoute les 2 coefficients
			*resultat = Resultat;
			return; //Et on quitte la fonction
		}
		else if (Resultat.tab_monomes[i].degre < m.degre || (Resultat.tab_monomes[i].degre > m.degre && i == Resultat.nb_monomes - 1)) //On vérifie pour placer le monôme donné au bon endroit
		{
			Resultat.nb_monomes += 1; //On ajoute un monôme au compte total

			if (Resultat.tab_monomes[i].degre > m.degre) //Si le degre du monome est inférieur 
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
/* INPUT  : Les 2 polynômes à ajouter + Polynôme résultat                     */
/* OUTPUT : néant                                                             */
/******************************************************************************/

void ajoutePolynomePolynome1(Polynome p1, Polynome p2, Polynome *resultat)
{
	int i;

	Polynome Resultat, Max;

	if (p1.nb_monomes == 0) //Le cas où un p1 est vide alors on retourne p2
	{
		*resultat = p2;
		return;
	}
	else if (p2.nb_monomes == 0) //Le cas où un p2 est vide alors on retourne p1
	{
		*resultat = p1;
		return; 
	}
	
	if (p2.nb_monomes > p1.nb_monomes) //On regarde quel est le plus grand des deux polynômes
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

/**********************************************************************************/
/* ajoutePolynomePolynome2 - Ajoute un polynôme à un autre polynôme               */
/* Compléxité : linéaire donc O(m+n)  (m & n sont les tailles des deux polynomes) */
/* INPUT  : Les 2 polynômes à ajouter + Polynôme résultat                         */
/* OUTPUT : néant                                                                 */
/**********************************************************************************/

void ajoutePolynomePolynome2(Polynome p1, Polynome p2, Polynome *resultat)
{
	int i1 = 0, i2 = 0, j = 0, k; //On initialise les compteurs afin de lire dans chaque polynôme le monôme que l'on souhaite

	Polynome Resultat;
	initPolynome(&Resultat);
	initPolynome(resultat);

	while (i1 < p1.nb_monomes && i2 < p2.nb_monomes) //On boucle tant qu'un des compteurs n'a pas atteint la taille du nb_monome des polynômes donnés
	{
		if (p1.tab_monomes[i1].degre > p2.tab_monomes[i2].degre) //Si le degré du monôme i1 du premier polynôme est supérieur au dégré du monôme i2 du second
		{
			Resultat.tab_monomes[j] = p1.tab_monomes[i1]; //Alors le polynôme résultat aura comme monôme max le monôme de i1 du polynôme 1
			i1++;
		}
		else if (p1.tab_monomes[i1].degre < p2.tab_monomes[i2].degre) //Sinon s'il s'agit de l'inverse (sans l'égalité)
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

		//On incrémente les compteurs
		j++;
		Resultat.nb_monomes++;
	}

	if (i1 == p1.nb_monomes)
	{
		k = Resultat.nb_monomes;

		while (i2 < p2.nb_monomes)
		{
			Resultat.tab_monomes[k] = p2.tab_monomes[i2];
			i2++;
			k++;
			Resultat.nb_monomes++;
		}
	}
	else if (i2 == p2.nb_monomes)
	{
		k = Resultat.nb_monomes;

		while (i1 < p1.nb_monomes)
		{
			Resultat.tab_monomes[k] = p1.tab_monomes[i1];
			i1++;
			k++;
			Resultat.nb_monomes++;
		}
	}

	*resultat = Resultat;
}

/******************************************************************************/
/* multipliePolynomePolynome - Multiplie un polynôme à un autre polynôme      */
/* Compléxité :     O(n*(n+(n+m))                                             */
/* INPUT  : Les 2 polynômes à multiplier + Polynôme résultat                  */
/* OUTPUT : néant                                                             */
/******************************************************************************/

void multipliePolynomePolynome(Polynome p1, Polynome p2, Polynome *resultat)
{
	int i;
	Polynome tampon;

	initPolynome(&tampon);
	initPolynome(resultat);

	for (i=0;i<p1.nb_monomes;i++)
	{
		multiplieMonomePolynome(p2, p1.tab_monomes[i], &tampon);
		ajoutePolynomePolynome2(*resultat, tampon, resultat);
	}

}

/******************************************************************************/
/* puissancePolynome - Met à la puissance un polynôme                         */
/* Compléxité :            O(n*complexité de multipliePolPol))                */
/* INPUT  : Le polynôme à multiplier + La puissance + Polynôme résultat       */
/* OUTPUT : néant                                                             */
/******************************************************************************/

void puissancePolynome(Polynome p1, int puissance, Polynome *resultat)
{
	int i;
	Polynome Tampon;

	Tampon = p1;

	if (puissance == 1)
	{
		*resultat = p1;
		return;
	}

	for (i = 1; i < puissance; i++)
	{
		multipliePolynomePolynome(Tampon, p1, &Tampon);

		if (Tampon.nb_monomes > 50)
		{
			printf("Ce polynôme à la puissance %d dépasse les 50 monômes ! Il nous est impossible de le calculer.", puissance);
			break;
		}
	}

	*resultat = Tampon;

}

/******************************************************************************/
/* triPolynome - Tri un polynôme donné                                        */
/* Compléxité :                 dans le pire des cas : O(n²)                  */
/* INPUT  : Le polynôme à trier + Le polynôme résultat                        */
/* OUTPUT : néant                                                             */
/******************************************************************************/

void triPolynome(Polynome p1, Polynome *resultat)
{
	int i, l, indice_mini;
	Monome tampon;

	*resultat = p1;

	for (i=0;i<resultat->nb_monomes;i++)
	{
		indice_mini = i;

		for (l=indice_mini; l<resultat->nb_monomes;l++)
		{
			if (resultat->tab_monomes[l].degre > resultat->tab_monomes[indice_mini].degre)
				indice_mini = l;
		}

		tampon = resultat->tab_monomes[indice_mini];
		resultat->tab_monomes[indice_mini] = resultat->tab_monomes[i];
		resultat->tab_monomes[i] = tampon;

	}
}

/******************************************************************************/
/* reduitPolynomeTrie - Réduit un polynôme trié                               */
/* Compléxité :        O(n)                                                   */
/* INPUT  : Le polynôme à réduire (doit être trié) + Le polynôme résultat     */
/* OUTPUT : néant                                                             */
/******************************************************************************/

void reduitPolynomeTrie(Polynome p1, Polynome *resultat)
{
	int i, k = 0, compteur = 0, somme = 0;
	
	initPolynome(resultat);

	for (i=0;i<p1.nb_monomes;i++)
	{

		if (i < p1.nb_monomes -1 && p1.tab_monomes[i+1].degre == p1.tab_monomes[i].degre)
		{
			compteur = i;
			somme = p1.tab_monomes[i].coeff;

			while(compteur <= p1.nb_monomes && p1.tab_monomes[i].degre == p1.tab_monomes[i+1].degre)
			{
				somme += p1.tab_monomes[i + 1].coeff;
				i++;
				compteur++;
			}

			resultat->tab_monomes[k].coeff = somme;
			resultat->tab_monomes[k].degre = p1.tab_monomes[i].degre;

		}
		else
		{
			resultat->tab_monomes[k] = p1.tab_monomes[i];
		}

		resultat->nb_monomes++;
		compteur++;
		k++;
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


/******************************************************************************/
/*                                                                            */
/*                        Fonctions de l'interface                            */
/*                                                                            */
/******************************************************************************/


/******************************************************************************/
/* Main_Menu - Menu principal                                                 */
/* INPUT : Rien                                                               */
/* OUTPUT : Rien                                                              */
/******************************************************************************/

void Main_Menu()
{
	int i = -1;

	while (i <= 0 || i > 3)
	{
		system("clear");

		printf("== Ultra Polynômes Calculator == \n");
		printf("1 - Démonstrations\n");
		printf("2 - Calculatrice\n");
		printf("3 - Quitter\n\n");

		printf("Entrez votre proposition (1/2/3) : ");
		scanf("%d", &i);

		switch (i)
		{
			case 1:
				Demonstrations();
				i = -1;
				break;
			case 2:
				Calculatrice_Menu();
				i = -1;
				break;
			case 3:
				break;
			default:
				viderBuffer();
		}

	}
}

/******************************************************************************/
/* Demonstrations - Affiche les démonstrations pour tous les fonctions des    */
/*                  polynômes                                                 */
/* INPUT : Rien                                                               */
/* OUTPUT : Rien                                                              */
/******************************************************************************/

void Demonstrations()
{
	system("clear");

	//Test affichage
	Polynome p, p_res;
	initPolynome(&p);
	initPolynome(&p_res);

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

	str2Polynome("", &p_Ajout1);
	str2Polynome("2X^7+X^5", &p_Ajout2);

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

	str2Polynome("-3X^2+4X-2", &p_Mult1);
	str2Polynome("X^3-X+1", &p_Mult2);

	initPolynome(&p_res);

	printf("Multiplication de : ");
	affichePolynome(p_Mult1);
	printf(" avec : ");
	affichePolynome(p_Mult2);
	printf(" = ");

	multipliePolynomePolynome(p_Mult1, p_Mult2, &p_res);

	affichePolynome(p_res);

	printf("\n \n");

	//Test puissance polynôme

	int puissance = 2;
	str2Polynome("X^3+2", &p_Mult1);

	printf("Puissance de : ");
	affichePolynome(p_Mult1);
	printf(" par : %d = ", puissance);

	puissancePolynome(p_Mult1, puissance, &p_res);

	affichePolynome(p_res);

	printf("\n");

	//Test tri polynôme

	str2Polynome("3X^5+2X^6+3-X^7", &p_Mult1);
	printf("Tri de : ");
	affichePolynome(p_Mult1);
	printf(" = ");

	triPolynome(p_Mult1, &p_res);
	
	affichePolynome(p_res);

	printf("\n");

	//Test reduire polynôme trié

	str2Polynome("5X^7+3X^5+2X^5+3X^5+3X^4+3X^4+4", &p_Mult1);
	printf("Réduction de : ");
	affichePolynome(p_Mult1);
	printf(" = ");

	reduitPolynomeTrie(p_Mult1, &p_res);

	affichePolynome(p_res);

	printf("\n \n");

	Wait_For_Enter();

}

/******************************************************************************/
/* Calculatrice_Menu - Menu pour la calculatrice des polynômes                */
/* INPUT : Rien                                                               */
/* OUTPUT : Rien                                                              */
/******************************************************************************/

void Calculatrice_Menu()
{
	int i = -1, puissance = 0;
	Polynome resultat, p1, p2;
	Monome mon;

	initPolynome(&resultat);
	initPolynome(&p1);
	initPolynome(&p2);

	while (i <= 0 || i > 10)
	{
		system("clear");

		printf("== Ultra Polynômes Calculator == \n");
		printf("1 - Afficher un polynôme\n");
		printf("2 - Multiplication d'un monôme avec un polynôme\n");
		printf("3 - Ajouter un monôme à un polynôme\n");
		printf("4 - Ajouter un polynôme à un autre polynôme (Algorithme 1)\n");		
		printf("5 - Ajouter un polynôme à un autre polynôme (Algorithme 2)\n");
		printf("6 - Multiplier un polynôme à un autre polynôme\n");
		printf("7 - Mettre un polynôme à une puissance\n");
		printf("8 - Trier un polynôme\n");
		printf("9 - Réduire un polynôme\n");
		printf("10 - Retourner au menu principal\n\n");

		printf("Entrez votre proposition (1/2/3/4/5/6/7/8/9/10) : ");
		scanf("%d", &i);

		switch (i)
		{
			case 1:
				Entree_Polynome(1, &resultat, 1);
				printf("Affichage du polynôme : ");
				affichePolynome(resultat);
				Calcul_Fin(&i);
				break;
			case 2:
				Entree_Monome(&mon);
				Entree_Polynome(1, &p1, 1);
				printf("Multiplication de %dX^%d avec ", mon.coeff, mon.degre);
				affichePolynome(p1);
				printf(" = ");
				multiplieMonomePolynome(p1, mon, &resultat);
				affichePolynome(resultat);
				Calcul_Fin(&i);
				break;
			case 3:
				Entree_Monome(&mon);
				Entree_Polynome(1, &p1, 1);
				printf("Ajout de %dX^%d avec ", mon.coeff, mon.degre);
				affichePolynome(p1);
				printf(" = ");
				ajouteMonomePolynome(p1, mon, &resultat);
				affichePolynome(resultat);
				Calcul_Fin(&i);
				break;
			case 4:
				Entree_Polynome(1, &p1, 1);
				Entree_Polynome(2, &p2, 1);
				printf("Ajout de ");
				affichePolynome(p1);
				printf(" avec ");
				affichePolynome(p2);
				printf(" = ");
				ajoutePolynomePolynome1(p1, p2, &resultat);
				affichePolynome(resultat);
				Calcul_Fin(&i);
				break;
			case 5:
				Entree_Polynome(1, &p1, 1);
				Entree_Polynome(2, &p2, 1);
				printf("Ajout de ");
				affichePolynome(p1);
				printf(" avec ");
				affichePolynome(p2);
				printf(" = ");
				ajoutePolynomePolynome2(p1, p2, &resultat);
				affichePolynome(resultat);
				Calcul_Fin(&i);
				break;
			case 6:
				Entree_Polynome(1, &p1, 1);
				Entree_Polynome(2, &p2, 1);
				printf("Multiplication de ");
				affichePolynome(p1);
				printf(" avec ");
				affichePolynome(p2);
				printf(" = ");
				multipliePolynomePolynome(p1, p2, &resultat);
				affichePolynome(resultat);
				Calcul_Fin(&i);
				break;
			case 7:
				Entree_Polynome(1, &p1, 1);
				do
				{
					system("clear");
					printf("Entrez une puissance : ");
					scanf("%d", &puissance);
				} while (puissance <= 0);
				system("clear");
				printf("Multiplication de ");
				affichePolynome(p1);
				printf(" à la puissance %d = ", puissance);
				puissancePolynome(p1, puissance, &resultat);
				affichePolynome(resultat);
				Calcul_Fin(&i);
				break;
			case 8:
				Entree_Polynome(1, &p1, 0);
				printf("Tri de ");
				affichePolynome(p1);
				printf(" = ");
				triPolynome(p1, &resultat);
				affichePolynome(resultat);
				Calcul_Fin(&i);
				break;
			case 9:
				Entree_Polynome(1, &p1, 2);
				printf("Réduction de ");
				affichePolynome(p1);
				printf(" = ");
				reduitPolynomeTrie(p1, &resultat);
				affichePolynome(resultat);
				Calcul_Fin(&i);
				break;
			case 10:
				break;
			default:
				viderBuffer();
		}

	}
}

/******************************************************************************/
/* Calcul_Fin - Exécute la séquence de fin des calculs                        */
/* INPUT : i de la boucle afin de permettre à la boucle de ne pas quitter     */
/* OUTPUT : Rien                                                              */
/******************************************************************************/

void Calcul_Fin(int *i)
{
	printf("\n");
	Wait_For_Enter();
	*i = -1;
}

/******************************************************************************/
/* Entree_Polynome - Fait entrer un polynôme à l'utilisateur                  */
/* INPUT : i le ième polynôme à être entré + res le polynôme résultat + tri   */
/*    tri = 0 pas de tri / tri = 1 tri + réduction / tri = 2 Pas de réduction */
/* OUTPUT : Rien                                                              */
/******************************************************************************/

void Entree_Polynome(int i, Polynome *res, int tri) //
{
	char polynome_entre_str[50] = "";
	Polynome polynome_entre;
	
	system("clear");

	printf("Entrez le polynôme %d : ", i);
	scanf("%s", polynome_entre_str);
	
	if (tri)
	{
		//On traite le polynôme
		str2Polynome(polynome_entre_str, &polynome_entre);
		triPolynome(polynome_entre, &polynome_entre);
		reduitPolynomeTrie(polynome_entre, &polynome_entre);
	}
	else if (tri == 2)
	{
		str2Polynome(polynome_entre_str, &polynome_entre);
		triPolynome(polynome_entre, &polynome_entre);
	}
	else
		str2Polynome(polynome_entre_str, &polynome_entre);

	*res = polynome_entre;

	system("clear");

}

/******************************************************************************/
/* Entree_Monome - Fait entrer un monôme à l'utilisateur                      */
/* INPUT : mon le monôme résultat                                             */
/* OUTPUT : Rien                                                              */
/******************************************************************************/

void Entree_Monome(Monome *mon)
{
	int coeff_monome = 0, degre_monome = 0;
	Monome monome_res;

	while (degre_monome <= 0)
	{
		system("clear");

		printf("Entrez le coefficient du monôme : ");
		scanf("%d", &coeff_monome);
		printf("\nEntrez le degré du monôme : ");
		scanf("%d", &degre_monome);
	}

	monome_res.coeff = coeff_monome;
	monome_res.degre = degre_monome;

	*mon = monome_res;

	system("clear");
}

/******************************************************************************/
/* Wait_For_Enter - Attend que l'utilisateur valide avec la touche entrée     */
/* INPUT : Rien                                                               */
/* OUTPUT : Rien                                                              */
/******************************************************************************/

void Wait_For_Enter()
{
	printf("Appuyez sur Entrée pour continuer !");
	viderBuffer();
	getchar();
}

/******************************************************************************/
/* viderBuffer - Vide le buffer pour ne pas causer de problèmes avec scanf    */
/* INPUT : Rien                                                               */
/* OUTPUT : Rien                                                              */
/******************************************************************************/

void viderBuffer()
{
	int c = 0;
	while (c != '\n' && c != EOF)
	{
		c = getchar();
	}
}

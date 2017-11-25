/******************************************************************************/
/* POLYNOMES_C                                                                */
/******************************************************************************/

//toutes déclarations dans le fichier .h
#include"polynomes.h"

/******************************************************************************/
/* main                                                                       */
/******************************************************************************/
int main(void)
{
    Polynome p;

    initPolynome(&p);
    str2Polynome("5x7-x^6-x5  +-2- 12x^5+2x-3",&p);
    affichePolynome(p);  // NE FAIT RIEN TANT QUE VOUS N'AUREZ PAS ECRIT LA FX!
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
    // A COMPLETER PAR VOS SOINS
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
    char *l=s, *e=d;
    //l pointeur qui lit la chaîne source
    //e pointeur qui écrit la chaîne destination

    while(*l!='\0')
    {
        if(*l=='-')  //remplacer - par +-
        {
            *e = '+';
            e++;
            *e = '-';
        }
        else
        {
            if(*l=='x' || *l=='X')  // X ou x
            {
                if(*(l-1)<'0' || *(l-1)>'9') // ...non précédé d'un chiffre
                {
                    *e='1';
                    e++;
                    *e='X';
                }
                else
                    *e = 'X';
            }
            // autre cas on recopie
            else if((*l>='0' && *l<='9') || *l=='+' || *l=='^')
                *e = *l;
            else // caractères erronés
            {
                e--; // on recule
                if (*l!=' ') // et on signale (sauf si espace)
                    fprintf(stderr,"Err: caractère '%c' ignoré\n",*l);
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
void str2Polynome(char *str,Polynome *p)
{
    char *tok, *ptr;
    int coeff, degre;
    int nb_monomes = 0;


    //on commence par standardiser la description
    //dans une chaîne assez longue pur la contenir
    char *str2 = (char *) malloc(strlen(str)+50);

    //la nouvelle description
    standardiseDescription(str,str2); // Nettoie et normalise

    tok = strtok(str2,"+"); // Récupération d'un "token" grâce au séparateur +

    while(tok!=NULL)
        {
        ptr=strchr(tok,'X'); // Y a-t-il un X dans le token?
        if(ptr) // Oui, il y a un X
            {
            //Y a-t'il un '^nombre' derriere le X
            if(sscanf(tok,"%dX^%d",&coeff,&degre)!=2) // Cas 5X^2
                {
                if(sscanf(tok,"%dX%d",&coeff,&degre) != 2) // Cas 5X2
                    {
                    if((sscanf(tok,"X%d",&degre) == 1) || (sscanf(tok,"X^%d",&degre) == 1)) // Cas X2 ou X^2
                        coeff = 1;
                    else if (sscanf(tok,"%dX",&coeff)==1) // Cas 5X
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
            sscanf(tok,"%d",&coeff);
            degre = 0;
            }
        p->tab_monomes[nb_monomes].coeff = coeff;
        p->tab_monomes[nb_monomes].degre = degre;
        nb_monomes++;

        tok = strtok(NULL,"+");
    }

    p->nb_monomes = nb_monomes;
    free(str2);
}

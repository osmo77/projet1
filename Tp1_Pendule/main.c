#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "main.h"
#include <string.h> // pour strcmp
#include <time.h>


char* motAleatoire();
int nombreAleatoire(int maximum);

int main (int argc, char* argv[])
{
    srand(time(NULL)); //Rend aléatoire le seed de rand()
    int compteurCoups = 15;
    char lettre = 0;
    char *motSecret;

    motSecret= motAleatoire();

    int longueurChaine = strlen(motSecret); //On crée le mot trouver en fonction de la taille du mot secret
    char motTrouve[longueurChaine];
    for (int x = 0; x < longueurChaine; x++) 
    {
        motTrouve[x] = '*';
    }

    printf("\nBienvenue dans le Pendu !\n");
    int reussite = 0;

    while (compteurCoups > 0)
    {
        printf("\nIl vous reste %d coups a jouer \n", compteurCoups);
        printf("Quel est le mot secret ?  %s\n", motTrouve);
        printf("Proposez une lettre : ");
        lettre = lireCaractere();

        for (int y = 0 ; y < longueurChaine ; y++)
        {
            if (motSecret[y] == lettre)
            {
                motTrouve[y] = lettre;
                reussite = 1;
            }
        }
        
        if (reussite == 0)
        {
            compteurCoups--;
        }

        if (strcmp(motTrouve, motSecret) == 0)
        {
            printf("\nGagne ! Le mot secret etait bien : %s\n", motSecret);
            break;
        }
    }

    if (compteurCoups == 00)
    {
        printf("Dommage vous avez perdu ... Le mot secret était %s\n", motSecret);
    }

    free(motSecret); //On libère la mémoire demandé dans la fonction motAleatoire
}

char* motAleatoire()
{
        FILE *dico = NULL;
        int nombreLigne = 0, caractereActuel = 0, positionLigne = 0;
        char *chaine = malloc(10 * sizeof(char));

        dico =fopen("dico.txt", "r");

        if (dico != NULL)
        {
            while (caractereActuel != EOF)  // Calcul le nombre de lignes dans le dico
            {
                caractereActuel = fgetc(dico);
                if (caractereActuel == '\n')
                {
                    nombreLigne++;
                }
            }

            positionLigne = nombreAleatoire(nombreLigne); //La ligne max est 12 est pas 13 car on commence à 0
            rewind(dico); //remet à O la position du curseur
            caractereActuel = 0, nombreLigne = 0; //On réintialise les variables pour la prochaine boucle
            while (caractereActuel != EOF && nombreLigne != positionLigne) // Se place à la bonne ligne
            {
                caractereActuel = fgetc(dico);
                if (caractereActuel == '\n') 
                {
                    nombreLigne++;
                }
            }
            
            caractereActuel = 0; //Encore une fois on réinitialise le caractere actuelle
            caractereActuel = fgetc(dico);
            int x = 0;
            while (caractereActuel != EOF && caractereActuel != '\n') // Lit le mot sans le '\n' de fin
            {
                chaine[x++] = caractereActuel;
                caractereActuel = fgetc(dico);
            }

            fclose(dico);
        }

        return chaine;
}


int nombreAleatoire(int maximum)
{

   int resultat = rand() % maximum;

   return resultat;
}

char lireCaractere() 
{ 
    char caractere = 0;
 
    caractere = getchar(); // On lit le premier caractère
    caractere = toupper(caractere); // On met la lettre en majuscule si elle ne l'est pas déjà
 
    while (getchar() != '\n') ; // On lit les autres caractères mémorisés un à un jusqu'au \n (pour les effacer) 
 
    return caractere; // On retourne le premier caractère qu'on a lu 
}
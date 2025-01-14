#include <stdio.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_INTRO_LENGTH 256

typedef struct
{
    char name[MAX_NAME];
    int force;
    int intelligence;
    int endurance;
    char language[3]; // "fr" ou "en"
} Player;

void setLanguage(Player *player)
{
    int valid = 0;

    do
    {
        printf("Choisissez une langue (fr/en) : ");
        scanf("%2s", player->language);

        if (strcmp(player->language, "fr") == 0 || strcmp(player->language, "en") == 0)
        {
            valid = 1;
        }
        else
        {
            printf("Langue non supportée. Veuillez réessayer.\n");
        }
    } while (!valid);
}

void setPlayerName(Player *player)
{
    if (strcmp(player->language, "fr") == 0)
    {
        printf("Entrez votre prénom : ");
    }
    else
    {
        printf("Enter your name: ");
    }

    getchar(); // Nettoie le tampon pour éviter les problèmes avec fgets
    fgets(player->name, MAX_NAME, stdin);
    player->name[strcspn(player->name, "\n")] = '\0'; // Supprime le saut de ligne
}

void assignSkillPoints(Player *player)
{
    int totalPoints = 10;
    int points;

    if (strcmp(player->language, "fr") == 0)
    {
        printf("\nVous avez %d points de compétence à répartir entre Force, Intelligence et Endurance.\n", totalPoints);
    }
    else
    {
        printf("\nYou have %d skill points to distribute among Strength, Intelligence, and Endurance.\n", totalPoints);
    }

    // Force
    do
    {
        if (strcmp(player->language, "fr") == 0)
        {
            printf("Combien de points voulez-vous attribuer à Force ? ");
        }
        else
        {
            printf("How many points do you want to assign to Strength? ");
        }
        scanf("%d", &points);
        if (points < 0 || points > totalPoints)
        {
            if (strcmp(player->language, "fr") == 0)
            {
                printf("Valeur invalide. Vous avez %d points restants.\n", totalPoints);
            }
            else
            {
                printf("Invalid value. You have %d points remaining.\n", totalPoints);
            }
        }
        else
        {
            player->force = points;
            totalPoints -= points;
            break;
        }
    } while (1);

    // Intelligence
    do
    {
        if (strcmp(player->language, "fr") == 0)
        {
            printf("Combien de points voulez-vous attribuer à Intelligence ? ");
        }
        else
        {
            printf("How many points do you want to assign to Intelligence? ");
        }
        scanf("%d", &points);
        if (points < 0 || points > totalPoints)
        {
            if (strcmp(player->language, "fr") == 0)
            {
                printf("Valeur invalide. Vous avez %d points restants.\n", totalPoints);
            }
            else
            {
                printf("Invalid value. You have %d points remaining.\n", totalPoints);
            }
        }
        else
        {
            player->intelligence = points;
            totalPoints -= points;
            break;
        }
    } while (1);

    // Endurance
    player->endurance = totalPoints;
    if (strcmp(player->language, "fr") == 0)
    {
        printf("Les %d points restants sont attribués à Endurance.\n", totalPoints);
    }
    else
    {
        printf("The remaining %d points are assigned to Endurance.\n", totalPoints);
    }
}

void displayPlayerInfo(const Player *player)
{
    if (strcmp(player->language, "fr") == 0)
    {
        printf("\n--- Profil du joueur ---\n");
        printf("Prénom      : %s\n", player->name);
        printf("Force       : %d\n", player->force);
        printf("Intelligence: %d\n", player->intelligence);
        printf("Endurance   : %d\n", player->endurance);
        printf("------------------------\n");
    }
    else
    {
        printf("\n--- Player Profile ---\n");
        printf("Name        : %s\n", player->name);
        printf("Strength    : %d\n", player->force);
        printf("Intelligence: %d\n", player->intelligence);
        printf("Endurance   : %d\n", player->endurance);
        printf("------------------------\n");
    }
}

void displayIntroduction(const Player *player)
{
    char introText[MAX_INTRO_LENGTH];
    FILE *file;
    char filename[50];

    // Sélectionner le fichier en fonction de la langue
    if (strcmp(player->language, "fr") == 0)
    {
        strcpy(filename, "text_fr/introduction.txt");
    }
    else
    {
        strcpy(filename, "en/intro.txt");
    }

    // Ouvrir le fichier
    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Erreur: Impossible de lire le fichier d'introduction.\n");
        return;
    }

    // Lire le contenu du fichier
    fgets(introText, sizeof(introText), file);
    fclose(file);

    // Afficher l'introduction
    printf("\n--- Introduction ---\n");
    printf("%s\n", introText);
    printf("---------------------\n");
}

int main()
{
    Player player = {"", 0, 0, 0, ""};

    // Choix de la langue
    setLanguage(&player);

    // Afficher l'introduction
    displayIntroduction(&player);

    // Saisie du prénom
    setPlayerName(&player);

    // Attribution des points de compétence
    assignSkillPoints(&player);

    // Affichage du profil du joueur
    displayPlayerInfo(&player);

    return 0;
}

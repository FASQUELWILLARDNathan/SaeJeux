#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME 50
#define MAX_INTRO_LENGTH 256
#define MAX_TEXT_LENGTH 1024

typedef struct
{
    char name[MAX_NAME];
    int force;
    int intelligence;
    int endurance;
    char language[3]; // "fr" ou "en"
    char chapter1Choice; // Le choix effectué au chapitre 1
} Player;

// Lire les lignes d'un intervalle donné (de `start_line` à `end_line`) d'un fichier ouvert
void lire_intervalle_lignes(FILE *file, int start_line, int end_line)
{
    char line[MAX_TEXT_LENGTH];
    int current_line = 1;

    // Revenir au début du fichier
    rewind(file);

    while (fgets(line, sizeof(line), file))
    {
        if (current_line >= start_line && current_line <= end_line)
        {
            printf("%s", line);
        }
        current_line++;
        if (current_line > end_line)
        {
            break;
        }
    }
}

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
        FILE *file = fopen("text_fr/lancement.txt", "r");
        if (file == NULL)
        {
            printf("Erreur: Impossible de lire le fichier.\n");
        }

        int start = 1, end = 1;
        lire_intervalle_lignes(file, start, end);

        getchar(); // Nettoie le tampon pour éviter les problèmes avec fgets
        scanf("%s", player->name);

        start = 2;
        end = 2;
        lire_intervalle_lignes(file, start, end);
        printf("%s", player->name);

        fclose(file);
    }
    else
    {
        FILE *file = fopen("text_en/launch.txt", "r");
        if (file == NULL)
        {
            printf("Erreur: Impossible de lire le fichier.\n");
        }

        int start = 1, end = 1;
        lire_intervalle_lignes(file, start, end);

        getchar(); // Nettoie le tampon pour éviter les problèmes avec fgets
        scanf("%s", player->name);

        start = 2;
        end = 2;
        lire_intervalle_lignes(file, start, end);
        printf(" %s", player->name);

        fclose(file);
    }
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
        strcpy(filename, "text_en/introduction.txt");
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

void displayChapter1(Player *player)
{
    char choice;
    int valid = 0;

    if (strcmp(player->language, "fr") == 0)
    {
        FILE *file = fopen("text_fr/chapitre1.txt", "r");
        if (file == NULL)
        {
            printf("Erreur: Impossible de lire le fichier.\n");
        }

        int start = 1, end = 5; // Lire de la ligne 1 à la ligne 5
        lire_intervalle_lignes(file, start, end);

        fclose(file);
    }
    else
    {
        FILE *file = fopen("text_en/chapter1.txt", "r");
        if (file == NULL)
        {
            printf("Error: Impossible to read this file.\n");
        }

        int start = 1, end = 5; // Lire de la ligne 1 à la ligne 5
        lire_intervalle_lignes(file, start, end);

        fclose(file);
    }

    do
    {
        printf("Votre choix (A/B/C): ");
        getchar(); // Nettoyer le tampon
        scanf("%c", &choice);
        choice = toupper(choice);

        if (choice == 'A')
        {
            valid = 1;
            player->chapter1Choice = 'A';
            if (strcmp(player->language, "fr") == 0)
            {
                FILE *file = fopen("text_fr/chapitre1.txt", "r");
                if (file == NULL)
                {
                    printf("Erreur: Impossible de lire le fichier.\n");
                }

                int start = 6, end = 6; // Lire de la ligne 5 à la ligne 10
                lire_intervalle_lignes(file, start, end);

                fclose(file);
            }
            else
            {
                FILE *file = fopen("text_en/chapter1.txt", "r");
                if (file == NULL)
                {
                    printf("Error: Impossible to read this file.\n");
                }

                int start = 6, end = 6;
                lire_intervalle_lignes(file, start, end);

                fclose(file);
            }
        }
        else if (choice == 'B')
        {
            if (player->endurance >= 3)
            {
                valid = 1;
                player->chapter1Choice = 'B';
                if (strcmp(player->language, "fr") == 0)
                {
                    FILE *file = fopen("text_fr/chapitre1.txt", "r");
                    if (file == NULL)
                    {
                        printf("Erreur: Impossible de lire le fichier.\n");
                    }

                    int start = 7, end = 7;
                    lire_intervalle_lignes(file, start, end);

                    fclose(file);
                }
                else
                {
                    FILE *file = fopen("text_en/chapter1.txt", "r");
                    if (file == NULL)
                    {
                        printf("Error: Impossible to read this file.\n");
                    }

                    int start = 7, end = 7;
                    lire_intervalle_lignes(file, start, end);

                    fclose(file);
                }
            }
            else
            {
                if (strcmp(player->language, "fr") == 0)
                {
                    printf("Vous n'avez pas assez d'endurance");
                }
                else
                {
                    printf("You don't have enough endurance");
                }
            }
        }
        else if (choice == 'C')
        {
            valid = 1;
            player->chapter1Choice = 'C';
            if (strcmp(player->language, "fr") == 0)
            {
                FILE *file = fopen("text_fr/chapitre1.txt", "r");
                if (file == NULL)
                {
                    printf("Erreur: Impossible de lire le fichier.\n");
                }

                int start = 8, end = 8;
                lire_intervalle_lignes(file, start, end);

                fclose(file);
            }
            else
            {
                FILE *file = fopen("text_en/chapter1.txt", "r");
                if (file == NULL)
                {
                    printf("Erreur: Impossible de lire le fichier.\n");
                }

                int start = 8, end = 8;
                lire_intervalle_lignes(file, start, end);

                fclose(file);
            }
        }
        else
        {
            if (strcmp(player->language, "fr") == 0)
            {
                printf("Choix invalide. Veuillez choisir une option disponible.\n");
            }
            else
            {
                printf("Invalid choice. Please select an available option.\n");
            }
        }
    } while (!valid);
}

void displayChapter2(Player *player)
{
    char choice;
    int valid = 0;

    do
    {
        // Affichage des options selon le choix du chapitre 1
        if (strcmp(player->language, "fr") == 0)
        {
            printf("\n--- Chapitre 2 ---\n");
            printf("Après votre décision, que souhaitez-vous faire par la suite ?\n");

            if (player->chapter1Choice == 'A')
            {
                printf("A. Suivre le passage des sous-sols découvert plus tôt. (Intelligence requise : 4)\n");
                printf("B. Remonter et sortir par l’entrée principale pour rejoindre les rues.\n");
            }
            else if (player->chapter1Choice == 'B')
            {
                printf("A. Descendre pour trouver un chemin sûr vers le bâtiment avec les hélicoptères. (Intelligence requise : 2)\n");
                printf("B. Utiliser la corde pour descendre directement dans une zone moins exposée. (Force requise : 3)\n");
            }
            else if (player->chapter1Choice == 'C')
            {
                printf("A. Suivre le plan donné par la personne blessée. (Intelligence requise : 3)\n");
                printf("B. Fouiller les environs à la recherche de provisions.\n");
            }
        }
        else
        {
            printf("\n--- Chapter 2 ---\n");
            printf("After your decision, what do you want to do next?\n");

            if (player->chapter1Choice == 'A')
            {
                printf("A. Follow the underground passage discovered earlier. (Intelligence required: 4)\n");
                printf("B. Go back up and exit through the main entrance to the streets.\n");
            }
            else if (player->chapter1Choice == 'B')
            {
                printf("A. Go down to find a safe path to the building with helicopters. (Intelligence required: 2)\n");
                printf("B. Use the rope to descend directly to a less exposed area. (Strength required: 3)\n");
            }
            else if (player->chapter1Choice == 'C')
            {
                printf("A. Follow the plan given by the injured person. (Intelligence required: 3)\n");
                printf("B. Search the surroundings for supplies.\n");
            }
        }

        // Lecture du choix de l'utilisateur
        printf("Votre choix (A/B): ");
        getchar(); // Nettoyer le tampon
        scanf("%c", &choice);
        choice = toupper(choice);

        // Traitement des choix
        if (player->chapter1Choice == 'A' && choice == 'A' && player->intelligence >= 4)
        {
            valid = 1;
            if (strcmp(player->language, "fr") == 0)
            {
                printf("\nVous explorez les sous-sols et découvrez une sortie secrète menant à un abri sécurisé.\n");
            }
            else
            {
                printf("\nYou explore the underground passage and find a secret exit leading to a safe shelter.\n");
            }
        }
        else if (player->chapter1Choice == 'A' && choice == 'B')
        {
            // Retour au chapitre 1
            if (strcmp(player->language, "fr") == 0)
            {
                printf("\nVous avez choisi de revenir à votre point de départ...\n");
            }
            else
            {
                printf("\nYou have chosen to go back to your starting point...\n");
            }

            // Réinitialiser le choix du chapitre 1
            player->chapter1Choice = '\0'; // Réinitialisation du choix du chapitre 1

            // Rejouer le chapitre 1 sans quitter le programme
            valid = 0; // Pour continuer à entrer dans la boucle de `displayChapter1()`
            while (!valid)
            {
                displayChapter1(player); // Rejouer le chapitre 1
                if (player->chapter1Choice != '\0')
                {
                    valid = 1; // Si un choix valide est fait, sortir de la boucle
                }
            }
            return;
        }
        else if (player->chapter1Choice == 'B' && choice == 'A' && player->intelligence >= 2)
        {
            valid = 1;
            if (strcmp(player->language, "fr") == 0)
            {
                printf("\nVous descendez prudemment et trouvez un chemin menant au bâtiment avec les hélicoptères.\n");
            }
            else
            {
                printf("\nYou carefully go down and find a path leading to the building with helicopters.\n");
            }
        }
        else if (player->chapter1Choice == 'B' && choice == 'B' && player->force >= 3)
        {
            valid = 1;
            if (strcmp(player->language, "fr") == 0)
            {
                printf("\nAvec la corde, vous descendez rapidement et atterrissez dans une zone protégée.\n");
            }
            else
            {
                printf("\nUsing the rope, you quickly descend and land in a protected area.\n");
            }
        }
        else if (player->chapter1Choice == 'C' && choice == 'A' && player->intelligence >= 3)
        {
            valid = 1;
            if (strcmp(player->language, "fr") == 0)
            {
                printf("\nEn suivant le plan, vous découvrez une route sûre mais complexe vers un lieu sûr.\n");
            }
            else
            {
                printf("\nFollowing the map, you find a safe but complex route to a secure location.\n");
            }
        }
        else if (player->chapter1Choice == 'C' && choice == 'B')
        {
            valid = 1;
            if (strcmp(player->language, "fr") == 0)
            {
                printf("\nVous trouvez des provisions : eau, nourriture et quelques outils utiles.\n");
            }
            else
            {
                printf("\nYou find supplies: water, food, and some useful tools.\n");
            }
        }
        else
        {
            if (strcmp(player->language, "fr") == 0)
            {
                printf("\nChoix invalide ou compétence insuffisante. Veuillez réessayer.\n");
            }
            else
            {
                printf("\nInvalid choice or insufficient skill. Please try again.\n");
            }
        }
    } while (!valid);
}

void displayChapter3(Player *player)
{
    char choice;
    int valid = 0;

    // Vérifier que le joueur a fait le bon choix dans le chapitre 1 et chapitre 2 pour accéder au chapitre 3
    if (player->chapter1Choice == 'A' && player->chapter1Choice == 'A')
    {
        if (strcmp(player->language, "fr") == 0)
        {
            printf("\n--- Chapitre 3 ---\n");
            printf("Vous entendez des bruits inquiétants derrière vous. Une créature étrange semble vous suivre.\n");
            printf("Que souhaitez-vous faire ?\n");
            printf("A. Courir pour échapper à la créature. (Endurance requise : 5)\n");
            printf("B. Tendre un piège avec votre corde et votre cutter. (Armement requis : 5)\n");
            printf("C. Trouver un endroit pour vous cacher et observer. (Intelligence requise : 4)\n");
        }
        else
        {
            printf("\n--- Chapter 3 ---\n");
            printf("You hear strange noises behind you. An odd creature seems to be following you.\n");
            printf("What do you want to do?\n");
            printf("A. Run to escape the creature. (Endurance required: 5)\n");
            printf("B. Set a trap using your rope and cutter. (Weaponry required: 5)\n");
            printf("C. Find a place to hide and observe. (Intelligence required: 4)\n");
        }

        do
        {
            printf("Votre choix (A/B/C): ");
            getchar(); // Nettoyer le tampon
            scanf("%c", &choice);
            choice = toupper(choice);

            if (choice == 'A' && player->endurance >= 5)
            {
                valid = 1;
                if (strcmp(player->language, "fr") == 0)
                {
                    printf("\nRésultat : Vous courez à toute vitesse, mais la créature vous rattrape et vous devez vous défendre.\n");
                }
                else
                {
                    printf("\nResult: You run as fast as you can, but the creature catches up with you and you must defend yourself.\n");
                }
            }
            else if (choice == 'B' && player->force >= 5)
            {
                valid = 1;
                if (strcmp(player->language, "fr") == 0)
                {
                    printf("\nRésultat : Vous tendez un piège avec la corde et le cutter. La créature tombe dans le piège et vous êtes en sécurité.\n");
                }
                else
                {
                    printf("\nResult: You set a trap using the rope and cutter. The creature falls into the trap and you're safe.\n");
                }
            }
            else if (choice == 'C' && player->intelligence >= 4)
            {
                valid = 1;
                if (strcmp(player->language, "fr") == 0)
                {
                    printf("\nRésultat : Vous trouvez un endroit pour vous cacher et observer la créature à distance.\n");
                }
                else
                {
                    printf("\nResult: You find a place to hide and observe the creature from a distance.\n");
                }
            }
            else
            {
                if (strcmp(player->language, "fr") == 0)
                {
                    printf("\nChoix invalide ou compétence insuffisante. Veuillez réessayer.\n");
                }
                else
                {
                    printf("\nInvalid choice or insufficient skill. Please try again.\n");
                }
            }
        } while (!valid);
    }
    else
    {
        if (strcmp(player->language, "fr") == 0)
        {
            printf("\nVous ne pouvez pas accéder au chapitre 3 car vous n'avez pas fait les bons choix dans les chapitres précédents.\n");
        }
        else
        {
            printf("\nYou cannot access Chapter 3 because you didn't make the right choices in the previous chapters.\n");
        }
    }
}

int main()
{
    Player player = {"", 0, 0, 0, ""};
    int gameRunning = 1; // Flag pour contrôler la boucle du jeu

    // Choix de la langue
    setLanguage(&player);

    // Saisie du prénom
    setPlayerName(&player);

    // Attribution des points de compétence
    assignSkillPoints(&player);

    // Affichage du profil du joueur
    displayPlayerInfo(&player);

    // Afficher l'introduction
    displayIntroduction(&player);

    // Boucle principale du jeu
    while (gameRunning)
    {
        // Afficher le chapitre 1
        displayChapter1(&player);

        // Si un choix valide est fait dans le chapitre 1, on passe au chapitre 2
        if (player.chapter1Choice != '\0')
        {
            // Afficher le chapitre 2
            displayChapter2(&player);
        }

        // Vérifier si on peut accéder au chapitre 3 après le chapitre 2
        if (player.chapter1Choice == 'A' && player.chapter1Choice == 'A')
        {
            // Afficher le chapitre 3
            displayChapter3(&player);
        }

        // Logique pour continuer ou quitter le jeu
        char continueGame;
        if (strcmp(player.language, "fr") == 0)
        {
            printf("\nVoulez-vous continuer à jouer ? (O/N) : ");
        }
        else
        {
            printf("\nDo you want to continue playing? (Y/N) : ");
        }

        getchar(); // Nettoyer le tampon
        scanf("%c", &continueGame);
        continueGame = toupper(continueGame);

        if (continueGame == 'N')
        {
            gameRunning = 0; // Quitter la boucle et terminer le jeu
        }
        else
        {
            player.chapter1Choice = '\0'; // Réinitialiser le choix du chapitre 1 pour recommencer
        }
    }

    printf("\nMerci d'avoir joué !\n"); // Message de fin du jeu
    return 0;
}

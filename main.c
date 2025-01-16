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
    char chapter2Choice; // Le choix effectué au chapitre 2
    char chapter4Choice; // Le choix effectué au chapitre 4
    char chapter5Choice; // Le choix effectué au chapitre 5
    char chapter5bisChoice; // Le choix effectué au chapitre 5_bis
    char chapter6Choice; // Le choix effectué au chapitre 6
    char chapter6bisChoice; // Le choix effectué au chapitre 6_bis
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

// Fonction de lecture rapide
void lecture_rapide(const char *path, int debut, int fin)
{
    FILE *file = fopen(path, "r");

    // Appeler la fonction pour lire l'intervalle de lignes
    lire_intervalle_lignes(file, debut, fin);

    // Fermer le fichier après usage
    fclose(file);
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
        printf(" %s", player->name);

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

    // Sélectionner le fichier en fonction de la langue
    if (strcmp(player->language, "fr") == 0)
    {
        lecture_rapide("text_fr/introduction.txt", 1, 2);
    }
    else
    {
        lecture_rapide("text_en/introduction.txt", 1, 2);
    }
}

void displayChapter1(Player *player)
{
    char choice;
    int valid = 0;

    if (strcmp(player->language, "fr") == 0)
    {
        lecture_rapide("text_fr/chapitre1.txt", 1, 5);
    }
    else
    {
        lecture_rapide("text_en/chapter.txt", 1, 5);
    }

    do
    {
        printf("\nVotre choix (A/B/C): ");
        getchar(); // Nettoyer le tampon
        scanf("%c", &choice);
        choice = toupper(choice);

        if (choice == 'A')
        {
            valid = 1;
            player->chapter1Choice = 'A';
            if (strcmp(player->language, "fr") == 0)
            {
                lecture_rapide("text_fr/chapitre1.txt", 6, 6);
            }
            else
            {
                lecture_rapide("text_en/chapter1.txt", 6, 6);
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
                    lecture_rapide("text_fr/chapitre1.txt", 7, 7);
                }
                else
                {
                    lecture_rapide("text_en/chapter1.txt", 7, 7);
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
                lecture_rapide("text_fr/chapitre1.txt", 8, 8);
            }
            else
            {
                lecture_rapide("text_en/chapter1.txt", 8, 8);
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
            lecture_rapide("text_fr/chapitre2.txt", 1, 2);

            if (player->chapter1Choice == 'A')
            {
                lecture_rapide("text_fr/chapitre2.txt", 3, 4);
            }
            else if (player->chapter1Choice == 'B')
            {
                lecture_rapide("text_fr/chapitre2.txt", 6, 7);
            }
            else if (player->chapter1Choice == 'C')
            {
                lecture_rapide("text_fr/chapitre2.txt", 9, 10);
            }
        }
        else
        {
            lecture_rapide("text_en/chapter2.txt", 1, 2);

            if (player->chapter1Choice == 'A')
            {
                lecture_rapide("text_en/chapter2.txt", 3, 4);
            }
            else if (player->chapter1Choice == 'B')
            {
                lecture_rapide("text_en/chapter2.txt", 6, 7);
            }
            else if (player->chapter1Choice == 'C')
            {
                lecture_rapide("text_en/chapter2.txt", 6, 7);
            }
        }

        // Lecture du choix de l'utilisateur
        printf("\nVotre choix (A/B): ");
        getchar(); // Nettoyer le tampon
        scanf("%c", &choice);
        choice = toupper(choice);

        // Traitement des choix
        if (player->chapter1Choice == 'A' && choice == 'A' && player->intelligence >= 4)
        {
            valid = 1;
            player->chapter2Choice = 'A'; // Enregistrer le choix
        }
        else if (player->chapter1Choice == 'A' && choice == 'B')
        {
            player->chapter2Choice = 'B'; // Enregistrer le choix

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
            player->chapter2Choice = 'A'; // Enregistrer le choix
        }
        else if (player->chapter1Choice == 'B' && choice == 'B' && player->force >= 3)
        {
            valid = 1;
            player->chapter2Choice = 'b'; // Enregistrer le choix
        }
        else if (player->chapter1Choice == 'C' && choice == 'A' && player->intelligence >= 3)
        {
            valid = 1;
            player->chapter2Choice = 'A'; // Enregistrer le choix
        }
        else if (player->chapter1Choice == 'C' && choice == 'B')
        {
            valid = 1;
            player->chapter2Choice = 'B'; // Enregistrer le choix
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
            lecture_rapide("text_fr/chapitre3_A.txt", 1, 5);
        }
        else
        {
            lecture_rapide("text_en/chapter3_A.txt", 1, 5);
        }

        do
        {
            printf("\nVotre choix (A/B/C): ");
            getchar(); // Nettoyer le tampon
            scanf("%c", &choice);
            choice = toupper(choice);

            if (choice == 'A' && player->endurance >= 5)
            {
                valid = 1;
            }
            else if (choice == 'B' && player->force >= 5)
            {
                valid = 1;
            }
            else if (choice == 'C' && player->intelligence >= 4)
            {
                valid = 1;
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
}

void displayChapter3_bis(Player *player)
{
    char choice;
    int valid = 0;

    // Conditions pour accéder au chapitre 3
    if (!((player->chapter1Choice == 'B' || player->chapter1Choice == 'C') && 
         (player->chapter2Choice == 'A' || player->chapter2Choice == 'B')))

    do
    {
        // Affichage des options du chapitre 3
        if (strcmp(player->language, "fr") == 0)
        {
            lecture_rapide("text_fr/chapitre3_B.txt", 1, 5);
        }
        else
        {
            lecture_rapide("text_en/chapter3_B.txt", 1, 5);
        }

        // Lecture du choix de l'utilisateur
        printf("\nVotre choix (A/B/C): ");
        getchar(); // Nettoyer le tampon
        scanf("%c", &choice);
        choice = toupper(choice);

        // Traitement des choix
        if (choice == 'A' && player->endurance >= 3)
        {
            valid = 1;
        }
        else if (choice == 'B' && player->force >= 2)
        {
            valid = 1;
        }
        else if (choice == 'C')
        {
            valid = 1;
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

void displayChapter4(Player *player)
{
    char choice;
    int valid = 0;

    do
    {
        if (strcmp(player->language, "fr") == 0)
        {
            lecture_rapide("text_fr/chapitre4.txt", 1, 4);
        }
        else
        {
            lecture_rapide("text_en/chapter4.txt", 1, 4);
        }

        // Lecture du choix du joueur
        printf("\nVotre choix (A/B): ");
        getchar(); // Nettoyer le tampon
        scanf("%c", &choice);
        choice = toupper(choice);

        // Traitement des choix
        if (choice == 'A' && player->force >= 4)
        {
            valid = 1;
            player->chapter4Choice = 'A'; // Enregistrer le choix du joueur
        }
        else if (choice == 'B' && player->intelligence >= 2)
        {
            valid = 1;
            player->chapter4Choice = 'B'; // Enregistrer le choix du joueur
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


void displayChapter5(Player *player)
{
    char choice;
    int valid = 0;

    // Affichage des options pour le Chapitre 5
    do
    {
        if (strcmp(player->language, "fr") == 0)
        {
            lecture_rapide("text_fr/chapitre5_A.txt", 1, 4);
        }
        else
        {
            lecture_rapide("text_en/chapter5_A.txt", 1, 4);
        }

        // Lecture du choix du joueur
        printf("\nYour choice (A/B): ");
        getchar(); // Nettoyer le tampon
        scanf("%c", &choice);
        choice = toupper(choice);

        // Traitement des choix
        if (choice == 'A' && player->force >= 4)
        {
            valid = 1;
            player->chapter5Choice = 'A'; // Enregistrer le choix
        }
        else if (choice == 'B')
        {
            valid = 1;
            player->chapter5Choice = 'B'; // Enregistrer le choix
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

void displayChapter5_bis(Player *player)
{
    char choice;
    int valid = 0;

    // Affichage des options pour le Chapitre 5 bis
    do
    {
        if (strcmp(player->language, "fr") == 0)
        {
            lecture_rapide("text_fr/chapitre5_B.txt", 1, 4);
        }
        else
        {
            lecture_rapide("text_en/chapter5_B.txt", 1, 4);
        }

        // Lecture du choix du joueur
        printf("\nYour choice (A/B): ");
        getchar(); // Nettoyer le tampon
        scanf("%c", &choice);
        choice = toupper(choice);

        // Traitement des choix
        if (choice == 'A')
        {
            valid = 1;
            player->chapter5bisChoice = 'A'; // Enregistrer le choix
        }
        else if (choice == 'B')
        {
            valid = 1;
            player->chapter5bisChoice = 'B'; // Enregistrer le choix
        }
        else
        {
            if (strcmp(player->language, "fr") == 0)
            {
                printf("\nChoix invalide. Veuillez réessayer.\n");
            }
            else
            {
                printf("\nInvalid choice. Please try again.\n");
            }
        }
    } while (!valid);
}

void displayChapter6_bis2(Player *player)
{
    // Afficher le texte du chapitre 6_bis2
    if (strcmp(player->language, "fr") == 0)
    {
        lecture_rapide("text_fr/chapitre6_B.txt", 1, 1);
        lecture_rapide("text_fr/chapitre6_B.txt", 2, 2);
    }
    else
    {
        lecture_rapide("text_en/chapter6_B.txt", 1, 1);
        lecture_rapide("text_en/chapter6_B.txt", 2, 2);
    }
}


// Fonction pour afficher le Chapitre 6
void displayChapter6(Player *player)
{
    char choice;
    int valid = 0;

    // Affichage des options pour le Chapitre 6
    do
    {
        if (strcmp(player->language, "fr") == 0)
        {
            lecture_rapide("text_fr/chapitre6_A.txt", 1, 4);
        }
        else
        {
            lecture_rapide("text_en/chapter6_A.txt", 1, 4);
        }

        // Lecture du choix du joueur
        printf("\nVotre choix (A/B): ");
        getchar(); // Nettoyer le tampon
        scanf("%c", &choice);
        choice = toupper(choice);

        // Traitement des choix
        if (choice == 'A')
        {
            valid = 1;
            player->chapter6Choice = 'A'; // Enregistrer le choix
            if (strcmp(player->language, "fr") == 0)
            {
                lecture_rapide("text_fr/chapitre6_A.txt", 5, 5);
            }
            else
            {
                lecture_rapide("text_en/chapter6_A.txt", 5, 5);
            }
        }
        else if (choice == 'B')
        {
            valid = 1;
            player->chapter6Choice = 'B'; // Enregistrer le choix
            if (strcmp(player->language, "fr") == 0)
            {
                lecture_rapide("text_fr/chapitre6_A.txt", 6, 6);
            }
            else
            {
                lecture_rapide("text_en/chapter6_A.txt", 6, 6);
            }
        }
        else
        {
            if (strcmp(player->language, "fr") == 0)
            {
                printf("\nChoix invalide. Veuillez réessayer.\n");
            }
            else
            {
                printf("\nInvalid choice. Please try again.\n");
            }
        }
    } while (!valid);
}

void displayChapter6_bis(Player *player)
{
    // Vérification des conditions pour afficher le chapitre 6_bis :
    if ((player->chapter4Choice == 'B' && player->chapter5Choice == 'B') || 
        (player->chapter4Choice == 'A' && player->chapter5Choice == 'B'))
    {
        // Affichage du texte du chapitre 6_bis
        lecture_rapide("text_fr/chapitre6_B.txt", 1, 1);
        if (strcmp(player->language, "fr") == 0)
        {
            lecture_rapide("text_fr/chapitre6_B.txt", 3, 3);
        }
        else
        {
            lecture_rapide("text_en/chapter6_B.txt", 3, 3);
        }
    }
    else
    {
        // Si les conditions ne sont pas remplies, afficher un message
        if (strcmp(player->language, "fr") == 0)
        {
            printf("\nVous ne pouvez pas accéder à ce chapitre car les conditions de choix au Chapitre 4 et Chapitre 5 ne sont pas remplies.\n");
        }
        else
        {
            printf("\nYou cannot access this chapter because the required choices in Chapter 4 and Chapter 5 have not been made.\n");
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

        // Vérifier si on peut accéder au chapitre 3 principal
        if (player.chapter1Choice == 'A' && player.chapter2Choice == 'A')
        {
            // Afficher le chapitre 3 principal
            displayChapter3(&player);
            // Passer au chapitre 4
            displayChapter4(&player);
        }
        // Vérifier si on peut accéder au chapitre 3 alternatif
        else if ((player.chapter1Choice == 'B' || player.chapter1Choice == 'C') &&
                 (player.chapter2Choice == 'A' || player.chapter2Choice == 'B'))
        {
            // Afficher le chapitre 3 alternatif
            displayChapter3_bis(&player);
            // Passer au chapitre 4
            displayChapter4(&player);
        }

        // Vérifier si on peut accéder au Chapitre 5_A
        if (player.chapter4Choice == 'A')
        {
            // Afficher le chapitre 5_A
            displayChapter5(&player);
        }

        // Vérifier si on peut accéder au Chapitre 5_bis (pour le choix B au chapitre 5)
        if (player.chapter4Choice == 'A' && player.chapter5Choice == 'B')
        {
            // Afficher le chapitre 5_bis
            displayChapter5_bis(&player);
        }

        // Vérifier si on peut accéder au Chapitre 6
        if (player.chapter4Choice == 'A' && player.chapter5Choice == 'A')
        {
            // Afficher le chapitre 6
            displayChapter6(&player);
            // Afficher le message de fin et sortir de la boucle
            printf("\nVous avez atteint la fin du jeu !\n");
            break; // Quitter la boucle
        }

        // Vérifier si on peut accéder au Chapitre 6_bis
        if (player.chapter4Choice == 'B' && player.chapter5Choice == 'B')
        {
            // Afficher le chapitre 6_bis
            displayChapter6_bis(&player);
            // Afficher le message de fin et sortir de la boucle
            printf("\nVous avez atteint la fin du jeu !\n");
            break; // Quitter la boucle
        }

        // Vérifier si on peut accéder au Chapitre 6_bis2 (conditions spécifiques pour B au Chapitre 4 et A au Chapitre 5_bis)
        if (player.chapter4Choice == 'A' && player.chapter5Choice == 'B' && player.chapter5bisChoice == 'A')
        {
            // Afficher le chapitre 6_bis2
            displayChapter6_bis2(&player);
            // Afficher le message de fin et sortir de la boucle
            printf("\nVous avez atteint la fin du jeu !\n");
            break; // Quitter la boucle
        }

        // Vérifier si on peut accéder au Chapitre 6_bis2 (conditions spécifiques pour A au Chapitre 5_bis)
        if (player.chapter4Choice == 'B' && player.chapter5Choice == 'A')
        {
            // Afficher le chapitre 6_bis2
            displayChapter6_bis2(&player);
            // Afficher le message de fin et sortir de la boucle
            printf("\nVous avez atteint la fin du jeu !\n");
            break; // Quitter la boucle
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
            player.chapter2Choice = '\0'; // Réinitialiser le choix du chapitre 2
            player.chapter4Choice = '\0'; // Réinitialiser le choix du chapitre 4
        }
    }

    printf("\nMerci d'avoir joué !\n"); // Message de fin du jeu
    return 0;
}






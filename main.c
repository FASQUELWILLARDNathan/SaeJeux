// FASQUEL WILLARD Nathan | DRIEUX Luc

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define MAX_NAME 50
#define MAX_INTRO_LENGTH 256
#define MAX_TEXT_LENGTH 1024
#define TOTAL_CHAPTERS 6

typedef struct
{
    char name[MAX_NAME];
    int force;
    int intelligence;
    int endurance;
    char language[3]; // fr or en
    char chapter1Choice; // Choice done on the chapter 1
    char chapter2Choice; // Choice done on the chapter 2
    char chapter3bisChoice; // Choice done on the chapter 3_bis
    char chapter4Choice; // Choice done on the chapter 4
    char chapter5Choice; // Choice done on the chapter 5
    char chapter5bisChoice; // Choice done on the chapter 5_bis
    char chapter6Choice; // Choice done on the chapter 6
    char chapter6bisChoice; // Choice done on the chapter 6_bis
} Player;

void smoothPrint(const char *message, int delay) {
    while (*message) {
        printf("%c", *message); // afficher un caractère
        fflush(stdout);        // forcer l'affichage immédiat
        usleep(delay * 1000);  // délai en millisecondes
        message++;
    }
} 

// Read the lines of a given range (from start_line to end_line) from an opened file.
void lire_intervalle_lignes(FILE *file, int start_line, int end_line)
{
    char line[MAX_TEXT_LENGTH];
    int current_line = 1;

    // Back to the beginning of the file
    rewind(file);

    // Read each line from the file until the end
    while (fgets(line, sizeof(line), file))
    {
        // Check if the current line number is within the specified range (start_line to end_line)
        if (current_line >= start_line && current_line <= end_line)
        {

            smoothPrint(line, 15);
            if (line[strlen(line) - 1] != '\n') {
                 // garantir une nouvelle ligne si nécessaire
            }
        }
        current_line++;
        // Stop reading if we have passed the end_line
        if (current_line > end_line)
        {
            break;
        }
    }
}


// Progression bar
void afficherBarreProgression(int chapitreActuel, int totalChapitres) {
    int pourcentage = (chapitreActuel * 100) / totalChapitres;
    printf("\nProgression : [");

    for (int i = 0; i < 50; i++) {
        if (i < (pourcentage / 2)) {
            printf("=");
        } else {
            printf(" ");
        }
    }
    printf("] %d%%\n", pourcentage);
}

// read files between a beginning and a end lines
void lecture_rapide(const char *path, int debut, int fin)
{
    FILE *file = fopen(path, "r");

    lire_intervalle_lignes(file, debut, fin);

    fclose(file);
}


// Set language of the game
void setLanguage(Player *player)
{
    int valid = 0;

    do
    {
        lecture_rapide("text_fr/console.txt", 8, 8);
        scanf("%2s", player->language);

        if (strcmp(player->language, "fr") == 0 || strcmp(player->language, "en") == 0)
        {
            valid = 1;
        }
        else
        {
            lecture_rapide("text_fr/console.txt", 9, 9);
        }
    } while (!valid);
}


// We ask the player a name
void setPlayerName(Player *player)
{
    if (strcmp(player->language, "fr") == 0)
    {
        lecture_rapide("text_fr/lancement.txt", 1, 1);
        scanf("%s", player->name);

        lecture_rapide("text_fr/lancement.txt", 2, 2);
        printf(" \033[1;34m%s\033[0m\n", player->name);

    }
    else
    {
        lecture_rapide("text_en/launch.txt", 1, 1);
        scanf("%s", player->name);

        lecture_rapide("text_en/launch.txt", 2, 2);
        printf(" \033[1;34m%s\033[0m\n", player->name);
    }
}


// Skills points for the game
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
            lecture_rapide("text_fr/console.txt", 10, 10);
        }
        else
        {
            lecture_rapide("text_en/console.txt", 8, 8);
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
            lecture_rapide("text_fr/console.txt", 11, 11);
        }
        else
        {
            lecture_rapide("text_en/console.txt", 9, 9);
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


// Print the informations of the player
void displayPlayerInfo(const Player *player)
{
    if (strcmp(player->language, "fr") == 0)
    {
        printf("\n--- Profil du joueur ---\n");
        printf("Prénom      : \033[1;34m%s\033[0m\n", player->name);
        printf("Force       : \033[1;31m%d\033[0m\n", player->force);
        printf("Intelligence: \033[1;32m%d\033[0m\n", player->intelligence);
        printf("Endurance   : \033[1;33m%d\033[0m\n", player->endurance);
        printf("------------------------\n");
    }
    else
    {
        printf("\n--- Player Profile ---\n");
        printf("Name        : \033[1;34m%s\033[0m\n", player->name);
        printf("Strength    : \033[1;31m%d\033[0m\n", player->force);
        printf("Intelligence: \033[1;32m%d\033[0m\n", player->intelligence);
        printf("Endurance   : \033[1;33m%d\033[0m\n", player->endurance);
        printf("------------------------\n");

    }
}


// Print introduction
void displayIntroduction(const Player *player)
{
    if (strcmp(player->language, "fr") == 0)
    {
        lecture_rapide("text_fr/introduction.txt", 1, 2);
    }
    else
    {
        lecture_rapide("text_en/introduction.txt", 1, 2);
    }
}

// Print chapter 1
void displayChapter1(Player *player)
{
    char choice;
    int valid = 0;

    if (strcmp(player->language, "fr") == 0)
    {
        lecture_rapide("text_fr/chapitre1.txt", 1, 5);
        printf("\n");
        lecture_rapide("text_fr/console.txt", 3, 3);
    }
    else
    {
        lecture_rapide("text_en/chapter1.txt", 1, 5);
        printf("\n");
        lecture_rapide("text_en/console.txt", 3, 3);
    }

    do
    {
        
        getchar(); // Erase the memory
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
                    lecture_rapide("text_fr/console.txt", 7, 7);
                }
                else
                {
                    lecture_rapide("text_en/console.txt", 7, 7);
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
        else if (choice == 'I') 
        {

            displayPlayerInfo(player);
            lecture_rapide("text_fr/console.txt", 3, 3);
        }
        else
        {
            if (strcmp(player->language, "fr") == 0)
            {
                lecture_rapide("text_fr/console.txt", 1, 1);
            }
            else
            {
                lecture_rapide("text_en/console.txt", 1, 1);
            }
        }
    } while (!valid);
    afficherBarreProgression(1, TOTAL_CHAPTERS);
}

// Print chapter 2
void displayChapter2(Player *player)
{
    char choice;
    int valid = 0;

    do
    {
        // Print according to the choice in chapter 1
        if (strcmp(player->language, "fr") == 0)
        {
            lecture_rapide("text_fr/chapitre2.txt", 1, 2);

            if (player->chapter1Choice == 'A')
            {
                lecture_rapide("text_fr/chapitre2.txt", 3, 4);
                printf("\n");
                lecture_rapide("text_fr/console.txt", 2, 2);
            }
            else if (player->chapter1Choice == 'B')
            {
                lecture_rapide("text_fr/chapitre2.txt", 6, 7);
                printf("\n");
                lecture_rapide("text_fr/console.txt", 2, 2);
            }
            else if (player->chapter1Choice == 'C')
            {
                lecture_rapide("text_fr/chapitre2.txt", 9, 10);
                printf("\n");
                lecture_rapide("text_fr/console.txt", 2, 2);
            }
        }
        else
        {
            lecture_rapide("text_en/chapter2.txt", 1, 2);

            if (player->chapter1Choice == 'A')
            {
                lecture_rapide("text_en/chapter2.txt", 3, 4);
                printf("\n");
                lecture_rapide("text_en/console.txt", 2, 2);
            }
            else if (player->chapter1Choice == 'B')
            {
                lecture_rapide("text_en/chapter2.txt", 6, 7);
                printf("\n");
                lecture_rapide("text_en/console.txt", 2, 2);
            }
            else if (player->chapter1Choice == 'C')
            {
                lecture_rapide("text_en/chapter2.txt", 6, 7);
                printf("\n");
                lecture_rapide("text_en/console.txt", 2, 2);
            }
        }

        // Read the choice
        getchar();
        scanf("%c", &choice);
        choice = toupper(choice);

        // Treatment
        if (player->chapter1Choice == 'A' && choice == 'A' && player->intelligence >= 4)
        {
            valid = 1;
            player->chapter2Choice = 'A'; // Save the choice
        }
        else if (player->chapter1Choice == 'A' && choice == 'B')
        {
            player->chapter2Choice = 'B'; // Save the choice

            // Reset chapter 1 choice
            player->chapter1Choice = '\0';

            // Play again chapter 1
            valid = 0;
            while (!valid)
            {
                displayChapter1(player); // Replay chapter 1
                if (player->chapter1Choice != '\0')
                {
                    valid = 1; // If choice is done we get out of the loop
                }
            }
            return;
        }
        else if (player->chapter1Choice == 'B' && choice == 'A' && player->intelligence >= 2)
        {
            valid = 1;
            player->chapter2Choice = 'A';
        }
        else if (player->chapter1Choice == 'B' && choice == 'B' && player->force >= 3)
        {
            valid = 1;
            player->chapter2Choice = 'b';
        }
        else if (player->chapter1Choice == 'C' && choice == 'A' && player->intelligence >= 3)
        {
            valid = 1;
            player->chapter2Choice = 'A';
        }
        else if (player->chapter1Choice == 'C' && choice == 'B')
        {
            valid = 1;
            player->chapter2Choice = 'B';
        }
        else if (choice == 'I') 
        {

            displayPlayerInfo(player);
            lecture_rapide("text_fr/console.txt", 2, 2);
        }
        else
        {
            if (strcmp(player->language, "fr") == 0)
            {
                lecture_rapide("text_fr/console.txt", 7, 7);
            }
            else
            {
                lecture_rapide("text_en/console.txt", 7, 7);
            }
        }
    } while (!valid);
    afficherBarreProgression(2, TOTAL_CHAPTERS);
}


// Display Chapter 3
void displayChapter3(Player *player)
{
    char choice;
    int valid = 0;

    // Verify if the chapter 3 is possible according to the chapter 1 and chapter 2 choices
    if (player->chapter1Choice == 'A' && player->chapter1Choice == 'A')
    {
        if (strcmp(player->language, "fr") == 0)
        {
            lecture_rapide("text_fr/chapitre3_A.txt", 1, 5);
            printf("\n");
            lecture_rapide("text_fr/console.txt", 3, 3);
        }
        else
        {
            lecture_rapide("text_en/chapter3_A.txt", 1, 5);
            printf("\n");
            lecture_rapide("text_en/console.txt", 3, 3);
        }

        do
        {
            getchar();
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
            else if (choice == 'I') 
            {
                displayPlayerInfo(player);
            }
            
            else
            {
                if (strcmp(player->language, "fr") == 0)
                {
                    lecture_rapide("text_fr/console.txt", 1, 1);
                }
                else
                {
                    lecture_rapide("text_en/console.txt", 1, 1);
                }
            }
        } while (!valid);
        afficherBarreProgression(3, TOTAL_CHAPTERS);
    }
}


// Chapter 3 bis 
void displayChapter3_bis(Player *player)
{
    char choice;
    int valid = 0;

    do
    {
        if (strcmp(player->language, "fr") == 0)
        {
            lecture_rapide("text_fr/chapitre3_B.txt", 1, 5);
            printf("\n");
            lecture_rapide("text_fr/console.txt", 3, 3);
        }
        else
        {
            lecture_rapide("text_en/chapter3_B.txt", 1, 5);
            printf("\n");
            lecture_rapide("text_en/console.txt", 3, 3);
        }
        
        getchar();
        scanf("%c", &choice);
        choice = toupper(choice);

        if (choice == 'A' && player->endurance >= 3)
        {
            valid = 1;
            player->chapter3bisChoice = 'A';
        }
        else if (choice == 'B' && player->force >= 2)
        {
            valid = 1;
            player->chapter3bisChoice = 'A';
        }
        else if (choice == 'C')
        {
            valid = 1;
            player->chapter3bisChoice = 'A';
        }
        else if (choice == 'I') 
        {
            displayPlayerInfo(player);
            lecture_rapide("text_fr/console.txt", 3, 3);
        }
        else
        {
            if (strcmp(player->language, "fr") == 0)
            {
                lecture_rapide("text_fr/console.txt", 7, 7);
            }
            else
            {
                lecture_rapide("text_en/console.txt", 7, 7);
            }
        }
    } while (!valid);
    afficherBarreProgression(3, TOTAL_CHAPTERS);
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
            printf("\n");
            lecture_rapide("text_fr/console.txt", 2, 2);
        }
        else
        {
            lecture_rapide("text_en/chapter4.txt", 1, 4);
            printf("\n");
            lecture_rapide("text_en/console.txt", 2, 2);
        }

        getchar();
        scanf("%c", &choice);
        choice = toupper(choice);

        if (choice == 'A' && player->force >= 4)
        {
            valid = 1;
            player->chapter4Choice = 'A';
        }
        else if (choice == 'B' && player->intelligence >= 2)
        {
            valid = 1;
            player->chapter4Choice = 'B';
        }
        else if (choice == 'I') 
        {
            displayPlayerInfo(player);
            lecture_rapide("text_fr/console.txt", 2, 2);
        }
        else
        {
            if (strcmp(player->language, "fr") == 0)
            {
                lecture_rapide("text_fr/console.txt", 7, 7);
            }
            else
            {
                lecture_rapide("text_en/console.txt", 7, 7);
            }
        }
    } while (!valid);
    afficherBarreProgression(4, TOTAL_CHAPTERS);
}


void displayChapter5(Player *player)
{
    char choice;
    int valid = 0;

    do
    {
        if (strcmp(player->language, "fr") == 0)
        {
            lecture_rapide("text_fr/chapitre5_A.txt", 1, 4);
            printf("\n");
            lecture_rapide("text_fr/console.txt", 2, 2);
        }
        else
        {
            lecture_rapide("text_en/chapter5_A.txt", 1, 4);
            printf("\n");
            lecture_rapide("text_en/console.txt", 2, 2);
        }

        getchar();
        scanf("%c", &choice);
        choice = toupper(choice);

        if (choice == 'A' && player->force >= 4)
        {
            valid = 1;
            player->chapter5Choice = 'A';
        }
        else if (choice == 'B')
        {
            valid = 1;
            player->chapter5Choice = 'B';
        }
        else if (choice == 'I') 
        {
            displayPlayerInfo(player);
            lecture_rapide("text_fr/console.txt", 2, 2);
        }
        else
        {
            if (strcmp(player->language, "fr") == 0)
            {
                lecture_rapide("text_fr/console.txt", 7, 7);
            }
            else
            {
                lecture_rapide("text_en/console.txt", 7, 7);
            }
        }
    } while (!valid);
    afficherBarreProgression(5, TOTAL_CHAPTERS);
}

void displayChapter5_bis(Player *player)
{
    char choice;
    int valid = 0;

    do
    {
        if (strcmp(player->language, "fr") == 0)
        {
            lecture_rapide("text_fr/chapitre5_B.txt", 1, 4);
            printf("\n");
            lecture_rapide("text_fr/console.txt", 2, 2);
        }
        else
        {
            lecture_rapide("text_en/chapter5_B.txt", 1, 4);
            printf("\n");
            lecture_rapide("text_en/console.txt", 2, 2);
        }

        getchar();
        scanf("%c", &choice);
        choice = toupper(choice);

        if (choice == 'A')
        {
            valid = 1;
            player->chapter5bisChoice = 'A';
        }
        else if (choice == 'B')
        {
            valid = 1;
            player->chapter5bisChoice = 'B';
        }
        else if (choice == 'I') 
        {
            displayPlayerInfo(player);
            lecture_rapide("text_fr/console.txt", 2, 2);
        }
        else
        {
            if (strcmp(player->language, "fr") == 0)
            {
                lecture_rapide("text_fr/console.txt", 1, 1);
            }
            else
            {
                lecture_rapide("text_en/console.txt", 1, 1);
            }
        }
    } while (!valid);
    afficherBarreProgression(5, TOTAL_CHAPTERS);
}

void displayChapter6_bis2(Player *player)
{
    if (strcmp(player->language, "fr") == 0)
    {
        lecture_rapide("text_fr/chapitre6_B.txt", 1, 1);
        printf("\n");
        lecture_rapide("text_fr/chapitre6_B.txt", 2, 2);
    }
    else
    {
        lecture_rapide("text_en/chapter6_B.txt", 1, 1);
        printf("\n");
        lecture_rapide("text_en/chapter6_B.txt", 2, 2);
    }
    afficherBarreProgression(6, TOTAL_CHAPTERS);
}


void displayChapter6(Player *player)
{
    char choice;
    int valid = 0;

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

        lecture_rapide("text_fr/console.txt", 2, 2);
        getchar();
        scanf("%c", &choice);
        choice = toupper(choice);

        if (choice == 'A')
        {
            valid = 1;
            player->chapter6Choice = 'A';
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
            player->chapter6Choice = 'B';
            if (strcmp(player->language, "fr") == 0)
            {
                lecture_rapide("text_fr/chapitre6_A.txt", 6, 6);
            }
            else
            {
                lecture_rapide("text_en/chapter6_A.txt", 6, 6);
            }
        }
        else if (choice == 'I') 
        {
            displayPlayerInfo(player);
            lecture_rapide("text_fr/chapitre6_B.txt", 2, 2);
        }
        else
        {
            if (strcmp(player->language, "fr") == 0)
            {
                lecture_rapide("text_fr/console.txt", 1, 1);
            }
            else
            {
                lecture_rapide("text_en/console.txt", 1, 1);
            }
        }
    } while (!valid);
    afficherBarreProgression(6, TOTAL_CHAPTERS);
}

void displayChapter6_bis(Player *player)
{

    if (strcmp(player->language, "fr") == 0)
    {
        lecture_rapide("text_fr/chapitre6_B.txt", 1, 1);
        printf("\n");
        lecture_rapide("text_fr/chapitre6_B.txt", 3, 3);
    }
    else
    {
        lecture_rapide("text_en/chapter6_B.txt", 1, 1);
        printf("\n");
        lecture_rapide("text_en/chapter6_B.txt", 3, 3);
    afficherBarreProgression(6, TOTAL_CHAPTERS);
    }
}



int main()
{
    Player player = {"", 0, 0, 0, ""};
    int gameRunning = 1; // Continue the game while 1
    // Language choice
    setLanguage(&player);

    // Name set
    setPlayerName(&player);

    // Skills set
    assignSkillPoints(&player);

    // Profil display
    displayPlayerInfo(&player);

    // Print introduction
    displayIntroduction(&player);

    // Loop for the game
    while (gameRunning)
    {
        // Display chapter 1
displayChapter1(&player);

// If a valid choice is made in chapter 1, proceed to chapter 2
if (player.chapter1Choice != '\0')
{
    // Display chapter 2
    displayChapter2(&player);
}

// Check if we can access the main chapter 3
if (player.chapter1Choice == 'A' && player.chapter2Choice == 'A')
{
    // Display the main chapter 3
    displayChapter3(&player);
    // Proceed to chapter 4
    displayChapter4(&player);
}
// Check if we can access the alternative chapter 3
else if ((player.chapter1Choice == 'B' || player.chapter1Choice == 'C') &&
         (player.chapter2Choice == 'A' || player.chapter2Choice == 'B'))
{
    // Display the alternative chapter 3
    displayChapter3_bis(&player);
    displayChapter4(&player);
}

// Check if we can access chapter 5_A
if (player.chapter4Choice == 'A')
{
    // Display chapter 5_A
    displayChapter5(&player);
}

// Check if we can access chapter 5_B
if (player.chapter4Choice == 'B')
{
    // Display chapter 5_B
    displayChapter5_bis(&player);
}

// Check if we can access chapter 5_bis (for choice B in chapter 5)
if (player.chapter4Choice == 'A' && player.chapter5Choice == 'B')
{
    // Display chapter 5_bis
    displayChapter5_bis(&player);
}

// Check if we can access chapter 6_bis2 after chapter 5_bis (specific cases)
if (player.chapter4Choice == 'A' && player.chapter5Choice == 'B' && player.chapter5bisChoice == 'A')
{
    displayChapter6_bis2(&player);
    if (strcmp(player.language, "fr") == 0)
    {
        lecture_rapide("text_fr/console.txt", 4, 4);
    }
    else
    {
        lecture_rapide("text_en/console.txt", 4, 4);
    }
    break;
}

if (player.chapter4Choice == 'A' && player.chapter5Choice == 'B' && player.chapter5bisChoice == 'B')
{
    displayChapter6_bis(&player);
    if (strcmp(player.language, "fr") == 0)
    {
        lecture_rapide("text_fr/console.txt", 4, 4);
    }
    else
    {
        lecture_rapide("text_en/console.txt", 4, 4);
    }
    break;
}

if (player.chapter4Choice == 'B' && player.chapter5bisChoice == 'A')
{
    displayChapter6_bis2(&player);
    if (strcmp(player.language, "fr") == 0)
    {
        lecture_rapide("text_fr/console.txt", 4, 4);
    }
    else
    {
        lecture_rapide("text_en/console.txt", 4, 4);
    }
    break;
}

if (player.chapter4Choice == 'B' && player.chapter5bisChoice == 'B')
{
    displayChapter6_bis(&player);
    if (strcmp(player.language, "fr") == 0)
    {
        lecture_rapide("text_fr/console.txt", 4, 4);
    }
    else
    {
        lecture_rapide("text_en/console.txt", 4, 4);
    }
    break;
}

// Check if we can access the main chapter 6
if (player.chapter4Choice == 'A' && player.chapter5Choice == 'A')
{
    displayChapter6(&player);
    if (strcmp(player.language, "fr") == 0)
    {
        lecture_rapide("text_fr/console.txt", 4, 4);
    }
    else
    {
        lecture_rapide("text_en/console.txt", 4, 4);
    }
    break;
}

// Check if we can access chapter 6_bis
if (player.chapter4Choice == 'B' && player.chapter5bisChoice == 'B')
{
    displayChapter6_bis(&player);
    if (strcmp(player.language, "fr") == 0)
    {
        lecture_rapide("text_fr/console.txt", 5, 5);
    }
    else
    {
        lecture_rapide("text_en/console.txt", 5, 5);
    }
    break;
}

// Check if we can access chapter 6_bis2 (another path)
if (player.chapter4Choice == 'B' && player.chapter5bisChoice == 'A')
{
    displayChapter6_bis2(&player);
    if (strcmp(player.language, "fr") == 0)
    {
        lecture_rapide("text_fr/console.txt", 4, 4);
    }
    else
    {
        lecture_rapide("text_en/console.txt", 4, 4);
    }
    break;
}

// Logic to continue or quit the game
char continueGame;
if (strcmp(player.language, "fr") == 0)
{
    lecture_rapide("text_fr/console.txt", 5, 5);
}
else
{
    lecture_rapide("text_en/console.txt", 5, 5);
}

getchar(); // Clean the input buffer
scanf("%c", &continueGame);
continueGame = toupper(continueGame);

if (continueGame == 'N')
{
    gameRunning = 0; // Exit the loop and end the game
}
else
{
    // Reset choices to start a new game
    player.chapter1Choice = '\0';
    player.chapter2Choice = '\0';
    player.chapter4Choice = '\0';
    player.chapter5Choice = '\0';
    player.chapter5bisChoice = '\0';
}

}

if (strcmp(player.language, "fr") == 0)
{
    lecture_rapide("text_fr/console.txt", 6, 6);
}
else
{
    lecture_rapide("text_en/console.txt", 6, 6);
}
return 0;
}








#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int display_menu(){
    char ch[1];

    printf("\n\tDeal or No Deal\n\n");
    printf("\n\t[1] Start Game");
    printf("\n\t[2] Instructions");
    printf("\n\t[3] High Scores");
    printf("\n\t[4] Exit");
    printf("\n\n\tChoice: ");
    scanf("%s", ch);    

    return atoi(ch);  // Converting string to int
}

void initializeCases(int cases[]) {
    int i, j, temp, count;

    for (count = 0; count < 3; count++) {
        for(i = 0; i < 26; i++){
            srand(time(NULL));
            j = rand() % 25;
            temp = cases[j];
            cases[j] = cases[i];
            cases[i] = temp;
        }
    }
}

void display_cases(int cases[], int caseChoice) {
    int i;

    printf("\n\n\t");
    for (i = 0; i < 26; i++) {
        if ((cases[i] > 0) && (i != (caseChoice - 1))) {
            printf("[%d] ", i + 1);
        } else {
            printf("[ ] ");
        }

        if (i == 6 || i == 13 || i == 20) {
            printf("\n\t");
        }
    }

    printf("\n");
}

void display_amount(int amounts[]) {
    int i;

    printf("\n\n");
    for (i = 0; i < 14; i++) {
        if (amounts[i] > 0 ) {
            printf("\n\t$%d", amounts[i]);
        } else {
            printf("\n\t");
        }

        if (amounts[i + 12] > 0) {
            printf("\t$%d",amounts[i + 12]);
        } else printf(" ");
    }
}

int get_case_choice() {
    int choice;

    do {
        printf("\n\n\tChoose your case: ");
        scanf("%d", &choice);

        if (choice < 1 || choice > 26) {
            printf("\n\tInvalid input!\n");
        }
    } while (choice < 1 || choice > 26);

    return choice;
}

void reveal_case(int cases[], int caseNum) {
    printf("\n\n\tContent of Case #%d", caseNum);
    printf("\n\t$%d\n", cases[caseNum - 1]);
}

void get_cases(int cases[], int amounts[], int turn, int caseChoice, int nChoice) {
    int i, j, choice, n = nChoice;

    for (i = 0; i < n; i++, nChoice--) {
        do {
            printf("\n\n\tRound %d\n", turn);
            printf("\n\tYour Case: %d\n", caseChoice);
            display_amount(amounts);
            display_cases(cases, caseChoice);
            printf("\n\tChoice left: %d\n", nChoice);
            printf("\tChoose a case: ");
            scanf("%d", &choice);

            if (   
                caseChoice == choice ||
                choice < 1 || 
                choice > 26 || 
                cases[choice - 1] == 0
            ) {
                printf("\n\tInvalid input!\n");
            }
        } while (
            choice == caseChoice ||
            choice < 1 || 
            choice > 26 || 
            cases[choice - 1] == 0
        );
        
        system("clear");
        reveal_case(cases, choice);

        for (j = 0; j < 26; j++) {
            if (amounts[j] == cases[choice - 1]) {
                amounts[j] = 0;
            }
        }
        cases[choice - 1] = 0;
    }
}

int banker_offer(int cases[], int turn) {
    int i, total = 0, amount = 0, n = 0, offer = 0, average = 0, choice;

    for(i = 0 ;  i < 26; i++){
        if(cases[i] > 0){
            total = amount + cases[i];
            n++;
        }
    }
    
    average = amount + total/ n;
    offer = average * turn / 10;

    printf("\n\n\tBanker's Offer: $%d\n", offer);

    return offer;
}

void end_game(int cases[], int caseChoice) {
    int i, choice, choice2;

    for (i = 0; i < 26; i++) {
        if ((cases[i] > 0) && (i != (caseChoice - 1))) {
           choice2 = i + 1;
        }
    }

    do {
        printf("\n\n\t[%d]  [%d]", caseChoice, choice2);
        printf("\nChoose your case: ");
        scanf("%d", &choice);


        if (choice == caseChoice) {
            system("clear");
            printf("\n\n\tYou have won $%d!\n", cases[caseChoice - 1]);
            break;
        } else {
            system("clear");
            printf("\n\n\tYou have won $%d!\n", cases[choice2 - 1]);
            break;
        }
    } while(choice != caseChoice || choice != choice2);   
}

void start_game() {
    int cases[26] = {1, 5, 10, 15, 25, 50, 75, 100, 200, 300, 400, 500, 750, 1000, 
                        5000, 10000, 25000, 50000, 75000, 100000, 200000, 300000, 
                        400000, 500000, 750000, 1000000};
    int amounts[26] = {1, 5, 10, 15, 25, 50, 75, 100, 200, 300, 400, 500, 750, 1000, 
                        5000, 10000, 25000, 50000, 75000, 100000, 200000, 300000, 
                        400000, 500000, 750000, 1000000};
    int turn = 0, nChoice = 6, caseChoice = 0, choice, offer;

    printf("\n\tDeal or No Deal!\n"); 
    printf("\n\tChoose a suitcase and find out \n\tif you're about to win a virtual fortune.");
    printf("\n\n\tLoading . . .");

    initializeCases(cases);

    display_cases(cases, caseChoice);
    caseChoice = get_case_choice();
    turn++;

    while (1) {
        system("clear");
        get_cases(cases, amounts, turn, caseChoice, nChoice);
        printf("\n\n\tRound %d\n", turn);
        printf("\n\tYour Case: %d\n", caseChoice);
        display_amount(amounts);
        display_cases(cases, caseChoice);
        offer = banker_offer(cases, turn);

        printf("\n\t[1] Deal");
        printf("\n\t[2] No Deal");
        printf("\n\tDeal or No Deal? ");
        scanf("%d", &choice);

        if (choice == 1) {
            system("clear");
            printf("\n\tYou have won $%d\n", offer);
            break;
        }

        if (turn == 9) {
            end_game(cases, caseChoice);
            break;
        }
        
        if (nChoice > 1) {
            nChoice--;    
        } else {
            nChoice = 1;
        }
        turn++;
    }
}

void display_instructions() {
    char y[1];

    printf("\n\n\tINSTRUCTIONS\n");
    printf("\n\t[1] Go back to Menu?\n\tChoice: ");
    scanf("%s", y);
}

void display_high_scores() {
    printf("\n\n\tHIGH SCORES\n");

}

void exit_game() {
    printf("\n\n\n\t\tThanks for playing! See you again!\n");
    printf("\n\t\tExiting game...\n");
    sleep(2);
    system("clear");

    exit(0);
}
#include "../../sdk/dexsdk.h"
#include "../../sdk/time.h"

#define up_key (char) 151 
#define down_key (char) 152
#define left_key (char) 150
#define right_key (char) 153
#define enter '\n'
#define backspace 8
#define quit 27

//Colors
#define ROYAL_BLUE 1
#define DARK_BLUE 8
#define YELLOW 54
#define PALE_YELLOW 62
#define GRAY 56
#define WHITE 63
#define BROWN 20
#define VIOLET 40
#define RED 36
#define GREEN 18
#define BLUE 9
#define ORANGE 38
#define MAROON 4
#define FLESH 55 //46
#define BLACK 70
#define DARK_GREEN 16 //24
#define DARK_BROWN 32

void initializeCases(int cases[]) {
    int i, j, temp, count;

    srand(time(NULL));
    for(i = 0; i < 26; i++){
        j = rand() % 25;

        temp = cases[j];
        cases[j] = cases[i];
        cases[i] = temp;
    }
}

//"Erases" the screen given the starting point and the width & height
void erase(int x, int y, int w, int h, int color){ //basically covers an area with a black rectangle 
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j,i,color);
}

int showBankersOffer(int cases[], int amount, int turn){ //pass amount parameter
    int i, j, currentChoice, total, n, average;
    char keypress;
    char offer[50];

    currentChoice = 0;
    total = 0;
    n = 0;
    average = 0;


    for(i = 0 ;  i < 26; i++){
        if(cases[i] > 0){
            total = total + cases[i];
            n++;
        }
    }
    
    average = (amount + total)/ n;
    total = average * turn / 10;

    /*for(i=58; i<=262; i++){ //vertical show
        for(j=10; j<=155; j++){
            write_pixel(i,j,PALE_YELLOW);
        }
    }*/
    for(i=10; i<=155; i++){ //horizontal show
        for(j=58; j<=262; j++){
            write_pixel(j,i,PALE_YELLOW);
        }
    }

    write_text("BANKER'S OFFER", 101, 31, WHITE, 0);
    write_text("BANKER'S OFFER", 100, 30, BLACK, 0);

    sprintf(offer, "$ %d", total);
    write_text(offer, 120, 50, BLACK, 1);

    do{
        if(currentChoice == 0){
            for(i=168; i<=252; i++){
                for(j=108; j<=132; j++){
                    write_pixel(i,j,PALE_YELLOW);
                }
            }
            for(i=68; i<=132; i++){
                for(j=108; j<=132; j++){
                    write_pixel(i,j,WHITE);
                }
            }

            for(i=170; i<=250; i++){
                for(j=110; j<=130; j++){
                    write_pixel(i,j,BLACK);
                }
            }
        }else{
            for(i=68; i<=132; i++){
                for(j=108; j<=132; j++){
                    write_pixel(i,j,PALE_YELLOW);
                }
            }
            for(i=70; i<=130; i++){
                for(j=110; j<=130; j++){
                    write_pixel(i,j,BLACK);
                }
            }

            for(i=168; i<=252; i++){
                for(j=108; j<=132; j++){
                    write_pixel(i,j,WHITE);
                }
            }
        }
        

        for(i=71; i<=129; i++){
            for(j=111; j<=129; j++){
                write_pixel(i,j,YELLOW);
            }
        }

        for(i=171; i<=249; i++){
            for(j=111; j<=129; j++){
                write_pixel(i,j,YELLOW);
            }
        }


        write_text("DEAL", 82, 118, BLACK, 0);
        write_text("NO DEAL", 180, 118, BLACK, 0);

        keypress=(char)getch();


        if(keypress == left_key || keypress == right_key){
            currentChoice = currentChoice == 0 ? 1 : 0;
        }

    }while(keypress != enter);

    return currentChoice; //0 for deal, 1 for no deal
}

void drawBriefcase(int w, int h, int x, int y, int bNumber, int size, int flag){
    int i, j;
    char num[1];


    for(i=0; i<w; i++){
        for(j=0; j<h; j++){
            write_pixel(i+x, j+y, GRAY);
        }
    }
    sprintf(num, "%d", bNumber);
    if(flag == 0){
        if(bNumber/10 > 0) write_text(num, x+9, y+3, BLACK, size);
        else write_text(num, x+15, y+3, BLACK, size);   
    }else{
        if(bNumber/10 > 0) write_text(num, x+8, y+6, BLACK, size);
        else write_text(num, x+12, y+6, BLACK, size);
    }
    //(bNumber/10 < 0) ? write_text(num, x+15, y+3, BLACK, 1) : write_text(num, x+9, y+3, BLACK, 1);
}

void drawAmount(int x, int y, char amount[10], int flag){ //x=10; //40x16
    int i,j;

    for(i=0; i<50; i++){
        for(j=0; j<13; j++){
            flag == 1? write_pixel(i+x, j+y, YELLOW) : write_pixel(i+x, j+y, GRAY);
        }
    }
    write_text(amount, x+5, y+2, BLACK, 0);
}

void drawBoard(int remainingCases[], int remainingAmounts[]){ //pass array of remaining amts
    int i,j;
    int offset=0;
    int start;

    //left side values
    remainingAmounts[0] == 1 ? drawAmount(5, 3, "$1", 1) : drawAmount(5, 3, "$1", 0);
    remainingAmounts[1] == 1 ? drawAmount(5, 18, "$5", 1) : drawAmount(5, 18, "$5", 0);
    remainingAmounts[2] == 1 ? drawAmount(5, 33, "$10", 1) : drawAmount(5, 33, "$10", 0);
    remainingAmounts[3] == 1 ? drawAmount(5, 48, "$15", 1) : drawAmount(5, 48, "$15", 0);
    remainingAmounts[4] == 1 ? drawAmount(5, 63, "$25", 1) : drawAmount(5, 63, "$25", 0);
    remainingAmounts[5] == 1 ? drawAmount(5, 78, "$50", 1) : drawAmount(5, 78, "$50", 0);
    remainingAmounts[6] == 1 ? drawAmount(5, 93, "$75", 1) : drawAmount(5, 93, "$75", 0);
    remainingAmounts[7] == 1 ? drawAmount(5, 108, "$100", 1) : drawAmount(5, 108, "$100", 0);
    remainingAmounts[8] == 1 ? drawAmount(5, 123, "$200", 1) : drawAmount(5, 123, "$200", 0);
    remainingAmounts[9] == 1 ? drawAmount(5, 138, "$300", 1) : drawAmount(5, 138, "$300", 0);
    remainingAmounts[10] == 1 ? drawAmount(5, 153, "$400", 1) : drawAmount(5, 153, "$400", 0);
    remainingAmounts[11] == 1 ? drawAmount(5, 168, "$500", 1) : drawAmount(5, 168, "$500", 0);
    remainingAmounts[12] == 1 ? drawAmount(5, 183, "$750", 1) : drawAmount(5, 183, "$750", 0);

    //right side values
    remainingAmounts[13] == 1 ? drawAmount(265, 3, "$1K", 1) : drawAmount(265, 3, "$1K", 0);//,000");
    remainingAmounts[14] == 1 ? drawAmount(265, 18, "$5K", 1) : drawAmount(265, 18, "$5K", 0);//,000");
    remainingAmounts[15] == 1 ? drawAmount(265, 33, "$10K", 1) : drawAmount(265, 33, "$10K", 0);//,000");
    remainingAmounts[16] == 1 ? drawAmount(265, 48, "$25K", 1) : drawAmount(265, 48, "$25K", 0);//,000");
    remainingAmounts[17] == 1 ? drawAmount(265, 63, "$50K", 1) : drawAmount(265, 63, "$50K", 0);//,000");
    remainingAmounts[18] == 1 ? drawAmount(265, 78, "$75K", 1) : drawAmount(265, 78, "$75K", 0);//,000");
    remainingAmounts[19] == 1 ? drawAmount(265, 93, "$100K", 1) : drawAmount(265, 93, "$100K", 0);//,000");
    remainingAmounts[20] == 1 ? drawAmount(265, 108, "$200K", 1) : drawAmount(265, 108, "$200K", 0);//,000");
    remainingAmounts[21] == 1 ? drawAmount(265, 123, "$300K", 1) : drawAmount(265, 123, "$300K", 0);//,000");
    remainingAmounts[22] == 1 ? drawAmount(265, 138, "$400K", 1) : drawAmount(265, 138, "$400K", 0);//,000");
    remainingAmounts[23] == 1 ? drawAmount(265, 153, "$500K", 1) : drawAmount(265, 153, "$500K", 0);//,000");
    remainingAmounts[24] == 1 ? drawAmount(265, 168, "$750K", 1) : drawAmount(265, 168, "$750K", 0);//,000");
    remainingAmounts[25] == 1 ? drawAmount(265, 183, "$1M", 1) : drawAmount(265, 183, "$1M", 0);//,000,000");

    for(i=1; i<=26; i++){

        if(i<=5){
            start = 59;
            if(remainingCases[i-1] == 1) drawBriefcase(38, 22, start+offset,3,i, 1, 0);
            offset += 41;
        }else if(i<=9){
            start = 55+14;
            if(i==6) offset = 0;
            if(remainingCases[i-1] == 1) drawBriefcase(38, 22, start+offset,30,i, 1, 0);
            offset += 48;
        }else if(i<=14){
            start = 59;
            if(i==10) offset = 0;
            if(remainingCases[i-1] == 1) drawBriefcase(38, 22, start+offset,57,i, 1, 0);
            offset += 41;
        }else if(i<=18){
            start = 55+14;
            if(i==15) offset = 0;
            if(remainingCases[i-1] == 1) drawBriefcase(38, 22, start+offset,84,i, 1, 0);
            offset += 48;
        }else if(i<=23){
            start = 55+4;
            if(i==19) offset = 0;
            if(remainingCases[i-1] == 1) drawBriefcase(38, 22, start+offset,111,i, 1, 0);
            offset += 41;
        }else{
            start = 55+28;
            if(i==24) offset = 0;
            if(remainingCases[i-1] == 1) drawBriefcase(38, 22, start+offset,138,i, 1, 0);
            offset += 58;
        }

    }

    for(i=57; i<263; i++){
        for(j=163; j<196; j++){
            write_pixel(i, j, YELLOW);
        }
    }

    for(i=58; i<262; i++){
        for(j=164; j<195; j++){
            write_pixel(i, j, BLACK);
        }
    }
}

int getCaseChoice(int remainingCases[]){
    char keypress, bcase[2];
    int i, currentCase, maxCase, minCase;

    for(i=0; i<26; i++){
        if(remainingCases[i] == 1){
            currentCase = i+1;
            break;
        }
    }

    for(i=25; i>=0; i--){
        if(remainingCases[i] == 1){
            maxCase = i+1;
            break;
        }
    }

    minCase = currentCase;


    do{
        erase(135,180,40,8,BLACK);

        sprintf(bcase, "%d", currentCase);
        write_text(bcase, 135, 180, WHITE, 0);

        keypress=(char)getch();

        if(keypress == right_key){
            currentCase++;
            if(currentCase == maxCase+1) currentCase = minCase;
            while(remainingCases[currentCase-1] == 0) currentCase++;
        }else if(keypress == left_key){
            currentCase--;
            if(currentCase == minCase-1) currentCase = maxCase;
            while(remainingCases[currentCase-1] == 0) currentCase--;
        }

    }while(keypress != enter);

    return currentCase;
}

void getCases(int cases[], int amounts[], int nChoice, int remainingCases[], int remainingAmounts[]) {
    int i, j, k, l, ch;
    char chCount[2];

    while(nChoice > 0) {
        erase(58,164,204,30,BLACK);
        sprintf(chCount, "Choose %d cases:", nChoice);
        write_text(chCount,117,168, WHITE,0);
       
        ch = getCaseChoice(remainingCases);
        remainingCases[ch-1] = 0;

        // Displays the player's chosen briefcase
        for(k=57; k<107; k++){
            for(l=163; l<196; l++){
                write_pixel(k, l, YELLOW);
            }
        }
        drawBriefcase(30, 19, 67, 170, ch, 0, 1); //chosen briefcase

        //reveal_case(cases, ch);

        for (j = 0; j < 26; j++) {
            if (amounts[j] == cases[ch - 1]) {
                amounts[j] = 0;
                remainingAmounts[j] = 0;
            }
        }
        
        cases[ch - 1] = 0;

        erase(58,3,204,158,BLACK);
        drawBoard(remainingCases, remainingAmounts);
        nChoice--;
    }   
}

void drawGame(){
    int cases[26] = {1, 5, 10, 15, 25, 50, 75, 100, 200, 300, 400, 500, 750, 1000, 
                        5000, 10000, 25000, 50000, 75000, 100000, 200000, 300000, 
                        400000, 500000, 750000, 1000000};
    int amounts[26] = {1, 5, 10, 15, 25, 50, 75, 100, 200, 300, 400, 500, 750, 1000, 
                        5000, 10000, 25000, 50000, 75000, 100000, 200000, 300000, 
                        400000, 500000, 750000, 1000000};
    int turn = 0, nChoice = 6, caseChoice = 0, amountChoice = 0, choice, decision;          

    int i, j;
    int remainingCases[26], remainingAmounts[26];
    char keypress;

    // Initialize cases and amounts: 0 for omitted cases/amts, 1 for remaining cases/amts
    for(i=0; i<26; i++){ 
        remainingCases[i] = 1;
        remainingAmounts[i] = 1;
    }
    erase(0,0,320,220, BLACK);

    initializeCases(cases);

    drawBoard(remainingCases, remainingAmounts);
    write_text("Choose a briefcase to",65,168, WHITE,0);
    write_text("start:", 70, 180, WHITE, 0);
    caseChoice = getCaseChoice(remainingCases);
    amountChoice = cases[caseChoice - 1];
    cases[caseChoice - 1] = 0;
    remainingCases[caseChoice - 1] = 0;
    erase(58,164,204,30,BLACK);
    drawBriefcase(30, 19, 67, 170, caseChoice, 0, 1); //chosen briefcase
    turn = 1;

    while(keypress != quit){
        drawBoard(remainingCases, remainingAmounts);
        getCases(cases, amounts, nChoice, remainingCases, remainingAmounts);

        decision = showBankersOffer(cases, amountChoice, turn);
        erase(58,3,204,158,BLACK);

        if (decision == 0) {
            //end game
            break;
        }

        if (turn == 9) {
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

void drawInstructions(){
    char keypress;

    erase(0,0,320,220, BLACK);
    write_text("Use up, down, left, and right keys", 10, 50, WHITE, 0);
    write_text("to navigate. Press Esc to exit", 10, 80, WHITE, 0);
    write_text("game", 10, 110, WHITE, 0);
    write_text("<press enter to go back to menu_>", 15, 170, WHITE, 0);
    do keypress=(char)getch();
    while(keypress!=enter);
    erase(0,0,320,220, BLACK);
}

void drawMenu() {        
    int currentChoice = 0;
    char keypress;
    
    //Clear the screen first
    erase(0,0,320,220, BLACK);

    do{
        write_text("DEAL OR NO DEAL",90,50,YELLOW,1);

        if(currentChoice==0) write_text("START GAME",110,100,YELLOW,0);
        else write_text("START GAME",110,100,WHITE,0);
        if(currentChoice==1) write_text("INSTRUCTIONS",100,120, YELLOW,0);  
        else write_text("INSTRUCTIONS",100,120, WHITE,0);
        if(currentChoice==2) write_text("HIGH SCORES",104,140, YELLOW,0);
        else write_text("HIGH SCORES",104,140, WHITE,0);
        if(currentChoice==3) write_text("QUIT",135,160, YELLOW,0);
        else write_text("QUIT",135,160, WHITE,0);

        keypress=(char)getch();
        
        if(keypress == up_key){
            if(currentChoice == 0) currentChoice = 3;
            else currentChoice--;
        }else if(keypress == down_key){
            if(currentChoice == 3) currentChoice = 0;
            else currentChoice++;
        }else if(keypress == enter){
            if(currentChoice == 0){
                drawGame();
                erase(0,0,320,220, BLACK);
            } 
            else if(currentChoice == 1) drawInstructions();
            /*else if(currentChoice == 2) drawHighScores();*/
            else if(currentChoice == 3){
                set_graphics(VGA_TEXT80X25X16);
                clrscr();
                exit(0);
            }
        }

    }while(keypress != quit);   

}

int main() {

    char keypress;

    //Set graphics
    set_graphics(VGA_320X200X256);
    //Clear the screen first
    erase(0,0,320,220, BLACK);
    
    drawMenu();
    
    //Return ICS-OS graphics before exiting
    set_graphics(VGA_TEXT80X25X16);
    clrscr();
    exit(0);
}
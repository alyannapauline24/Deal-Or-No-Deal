#include "dorndfunc.h"


int main() {
	int choice;

	while(1){
		choice = display_menu();

		switch(choice) {
			case 1: start_game();
					break;
			case 2: display_instructions();
					break;
			case 3: display_high_scores();
					break;
			case 4: exit_game();
					break;
			default: printf("\n\n\tInvalid Input!\n");
		}
	}

	return 0;
}
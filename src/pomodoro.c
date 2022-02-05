/*
** main.c for pomodoro timer
** 
** Made by Maxime B. (website : maxime-brgt.me)
** 
** Started on Thu Jul  9 17:12:42 2015 Maxime B.
** Last update Mon Jul 13 17:53:22 2015 Maxime B.
*/

/*
 * Last update Saturday 05 February 2022 by NoirHusky
 */
// TODO: give the user a gracefull way to exit any time. Preferably, add a 'q' option to the yes/no question
#include	<stdio.h>
#include	<stdbool.h>
#include	<stdlib.h>
#include    <string.h>
#include    <unistd.h>

#ifndef TEST
    const int LENGTH_SHORT_BREAK = 5 * 60;
    const int LENGTH_LONG_BREAK  = 15 * 60;
    const int NUM_POMODOROS_BFB  = 4;
    const int LENGTH_POMODORO    = 25 * 60;
#else
    const int LENGTH_SHORT_BREAK = 3;
    const int LENGTH_LONG_BREAK  = 5;
    const int NUM_POMODOROS_BFB  = 4;
    const int LENGTH_POMODORO    = 10;
#endif

const char* LONG_BREAK_MSG  = "Good job, long break time !";
const char* SHORT_BREAK_MSG = "Break time !";
const char*     WORK_MSG    = "Time to work!";

bool bRunning = true;

void __bye()
{
  printf("\nGood Bye !\n");
  exit(0);
}

void POM_countdown(const char* msg, int secs) {
    system("clear");
    printf("%s\n\n", msg);

    while ( secs >= 0 ) {
        int min = (secs / 60) % 60; 
        int sec = (secs % 60);

        printf("\rTime remaining: %02d:%02d...", min, sec);

        fflush(stdout);
        sleep(1);
        secs -= 1;
    }
    putchar('\n');
}

bool pom_yes_no_question(char* question) {
    puts(question);
    char answer = 0;
    do {
       answer = getchar(); 
       if ( answer == 'n' ) return false;
    } while ( answer != 'y' && answer != 'n' );
    return true;
}

int	main()
{
    int nums_poms = 1;
    while (bRunning) {
        POM_countdown(WORK_MSG, LENGTH_POMODORO);
        nums_poms++;

        bool yes = pom_yes_no_question("Do you want to take a break? (y/n) ");
        if ( ! yes ) continue; 
        if ( nums_poms % LENGTH_LONG_BREAK == 0 ) { 
            POM_countdown(LONG_BREAK_MSG, LENGTH_LONG_BREAK);
        } else {
            POM_countdown(SHORT_BREAK_MSG, LENGTH_SHORT_BREAK);
        }
        yes = pom_yes_no_question("Break has ended!\nDo you want to go back to work? (y/n) ");
        if ( ! yes ) bRunning = false; 
    }
#ifdef BEEP
    system("beep -l 100 -f 400 -D 200 -n -l 100 -f 400");
#endif
    __bye();
    return (EXIT_SUCCESS);
}

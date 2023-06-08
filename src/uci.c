/*
RobboLito is a UCI chess playing engine by
Yakov Petrovich Golyadkin, Igor Igorovich Igoronov, Roberto Pescatore
copyright: (C) 2009 Yakov Petrovich Golyadkin
date: 92th and 93rd year from Revolution
owners: PUBLICDOMAIN (workers)
dedication: To Vladimir Ilyich

RobboLito is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published
by the Free Software Foundation, either version 3 of the License,
or (at your option) any later version.

RobboLito is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see http://www.gnu.org/licenses/.
*/

#include "robbolito.h"
#include "monitor.h"
#include "search.h"

void uci()
    {
    numCPU = check_num_CPU();
    PONDER = FALSE;
    MPH = 2;
    printf("id name " NAME "\n");
    printf("id author Yakov Petrovich Golyadkin, Igor Igorovich Igoronov, Roberto Pescatore\n");
    printf("id copyright Yakov Petrovich Golyadkin\n");
    printf("id date 92th and 93rd year from Revolution\n");
    printf("id owners PUBLICDOMAIN (workers)\n");
    printf("id dedication To Vladimir Ilyich\n");
    printf("option name Hash type spin default 128 min 4 max 16384\n");
    printf("option name Ponder type check default false\n");
    printf("option name Move on Ponderhit type combo var Never var Sometimes var Always default Sometimes\n");
    printf("uciok\n");
    fflush(stdout);
    }

void readyok()
    {
    printf("readyok\n");
    fflush(stdout);
    }

static void quit()
    {
    exit(0);
    }

static void parse( char *string )
    {
    char *name, *value;
    int size;

	if (!strcmp(string, "ponderhit"))
        {
        PONDERING = FALSE;
        if (MPH == 3)
            search_halt(5);
        else if (MPH == 2 && EASY)
            search_halt(6);
        else if (MPH == 1)
            CLOCK = clock_() - 10000;
        }

    if( !strcmp(string, "quit") )
        quit();

    if( !strcmp(string, "stop") )
        search_halt(0);

    if( !strcmp(string, "isready") )
        readyok();

    if( !strcmp(string, "ucinewgame") )
        {
        search_halt(0);
        game_new(TRUE);
        }

    if( jump_ok )
        return;

    if( !memcmp(string, "setoption", 9) )
        {
        search_halt(0);
        name = strstr(string, "name ");
        value = strstr(string, "value ");

        if( name == NULL || value == NULL || name >= value )
            return;
        value[-1] = 0;
        name += 5;
        value += 6;

        if( !strcmp(name, "Ponder") )
            {
            if( !strcmp(value, "true") || !strcmp(value, "yes") || !strcmp(value, "1") )
                PONDER = TRUE;
            else if( !strcmp(value, "false") || !strcmp(value, "no") || !strcmp(value, "0") )
                PONDER = FALSE;
            }

        if( !strcmp(name, "Move on Ponderhit") )
            {
            if( !strcmp(value, "Never") )
                MPH = 1;
            else if( !strcmp(value, "Sometimes") )
                MPH = 2;
            else if( !strcmp(value, "Always") )
                MPH = 3;

            }

        if( !strcmp(name, "Hash") )
            {
            size = _atoi64(value);

            if( size >= 4 && size <= 16384 )
                size = initialization_zobrist(size);
            }
        }


    if( !memcmp(string, "go", 2) )
        {
        search_initialization(string);

        if( border_legitimate )
            search();
        }

    if( !memcmp(string, "position", 8) )
        positional_initialization(string + 9);

    if( !strcmp(string, "uci") )
        uci();
    }

void input_console()
    {
    char string[65536];
    fgets(string, 65536, stdin);
    string[strlen(string) - 1] = 0;
    parse(string);
    }

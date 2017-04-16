/*
    Dungeoneer simulator - symulator bohatera budz¹cego siê w dziwnej przestrzeni zbudowanej jedynie z pustych pól i niemo¿liwych do przejœcia #.
    Nasz bohater uporczywie szuka wyjœcia, jednak na swojej drodze trafia jedynie na hordy przeciwników a ka¿de wyjœcie prowadzi jedynie do kolejnego poziomu z którego nie ma powrotu.
    Program sk³ada siê z klas:
    level - odpowiedzialna za, proceduralne generowanie poziomów, informowanie o obecnoœci w poz x,y œciany lub drogi, wyrysowywanie samej siebie oraz postaci znajdujaych sie na mapie(dodawane w postaci literki poprzez funkcje, po smierci usuwane)
    character - klasa bazowa dla klas enemy/player, zawiera wspolne dane i funkcje takie jak pozycje, cechy niezbedne do walki, informujace o stanie postaci oraz odpowiedzialne za zmiane pozycji
    enemy - dziediczy po character + zawiera informacje charakterystyczne dla wroga
    player - dziedziczy po character + zawiera informacje charakterystyczne dla gracza

    Z grubsza taki jest zamys³, g³ównym celem projektu jest przyswojenie oraz zaimplementowanie algorytmu generowanie proceduralnego labiryntu perfekcyjnego nastepnie wrzucenie do niego bohatera którego celem jest znalezienie wyjœcia.
    Wp³yw u¿ytkownika na symulacje to nadanie imienia oraz podanie wstêpnych porz¹danych statystyk.

    Plan podstawowy: j.w.
    Dodatki zbedne, aczkolwiek mo¿liwe (w kolejnosci prawdopodobienstwa wprowadzenia): pu³apki, głód/jedzenie, przedmioty na ziemi, mozliwosc wyboru klasy bohatera, druzyna bohaterow

*/
#include "level.h"
#include "enemy.h"
#include "player.h"
#include "treasure.h"
#include "journal.h"
#include <string>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <sstream>
using namespace std;

inline void printLegend();

template <typename T>
string toString ( T Number )
{
	stringstream ss;
	ss << Number;
	return ss.str();
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int sleepValue = argc == 2 ? atoi(argv[1]) : 100;

// ***
// Main menu for starting the simulation/player creation
// ***
    string name;
    system("cls");
    int strVal, dexVal, conVal;
    do
    {
        cout << "########################################\n"
             << "######### Dungeoneer simulator #########\n"
             << "########################################\n\n"
             << "## Enter your name: ";
        cin >> name;
        cout << "## \n"
             << "## Choose attributes value: \n"
             << "## 15 points to spend on STR/CON/DEX:\n"
             << "## STR: ";
        cin >> strVal;
        cout << "## CON: ";
        cin >> conVal;
        cout << "## DEX: ";
        cin >> dexVal;
        system("cls");
        if(strVal + conVal + dexVal > 15 or strVal <= 0 or conVal <= 0 or dexVal <= 0) {
                                           cout << "##################################\n"
                                                << "## \n"
                                                << "## !STR+CON+DEX higher than 15!\n"
                                                << "## !Or one of them is less or equal to 0!\n"
                                                << "## \n"
                                                << "##################################\n";
                                           Sleep(sleepValue * 15);
                                           system("cls");}

    }while(strVal + conVal + dexVal > 15 or strVal <= 0 or conVal <= 0 or dexVal <= 0);


    player player1(name);
    journal journal1(5);
    journal1.addEntry(name + " was born!\n");

    player1.generateStats(strVal + rand() % 4 - 1, conVal + rand() % 4 - 1, dexVal + rand() % 4 - 1);

    encounters encounter = space;

    bool firstSetup = true;
    int width, height, enemiesCount, treasureCount;

    level * level1 = NULL;
    enemy * enemies = NULL;
    treasure * treasures = NULL;
    int currentDepth = 0;


// ***
// Main simulation logic
// ***
    while(player1.isAlive())
    {
        // **
        // Setting up level and encounters for the first time and after moving to next floor
        // ***
        if(firstSetup or encounter == leave)
        {
            // ***
            // Setting up level, player map, enemies stats
            // ***
            system("cls");
            if(!firstSetup)
            {
                delete level1;
                delete [] enemies;
                delete [] treasures;
            }else firstSetup = false;

            width = rand() % 15 + 16, height = rand() % 10 + 11;
            enemiesCount = (width * height)/15;
            treasureCount = enemiesCount/3.5;
            level1 = new level(width, height);
            currentDepth++;
            enemies = new enemy[enemiesCount];
            treasures = new treasure[treasureCount];
            for(int i = 0 ; i < enemiesCount ; i++)
                enemies[i].enemySetup(currentDepth);

            player1.mapPrepare(width, height);

            // ***
            // Setting up positions, player - start from level, enemies at random
            // ***
            player1.setPosition(level1->fieldPosX(level1->getStart()), level1->fieldPosY(level1->getStart()));
            player1.mapAround(level1->fieldMap());
            level1->addChar(player1.posX(), player1.posY(), 'P');

            for(int x = 1, y = 1, i = 0 ; i < enemiesCount ; x++)
            {
                x = rand() % width;
                y = rand() % height;
                if(level1->isValidSpace(x, y))
                {
                    enemies[i].setPosition(x, y);
                    level1->addChar(enemies[i].posX(), enemies[i].posY(), 'E');
                    i++;
                }
            }

            for(int x = 1, y = 1, i = 0 ; i < treasureCount ; x++)
            {
                x = rand() % width;
                y = rand() % height;
                if(level1->isValidSpace(x, y))
                {
                    treasures[i].setPosition(x, y);
                    level1->addChar(treasures[i].posX(), treasures[i].posY(), 'T');
                    i++;
                }
            }
            journal1.addEntry("Entered " + toString(currentDepth) + " dungeon floor!\n");
        }


        // **
        // Player Movement Section
        // ***
        level1->removeChar(player1.posX(), player1.posY(), 'P');
        encounter = player1.bestMove();
        level1->addChar(player1.posX(), player1.posY(), 'P');
        player1.mapAround(level1->fieldMap());


        // **
        // Main Encounters Section
        // ***
        if(encounter == item)
        {
            string info;
            info += "##################################\n";
            info += "## \n";
            int i = 0;
            for( ; i < treasureCount ; i++) // finding which chest player opened
            {
                if(treasures[i].posX() == player1.posX() and treasures[i].posY() == player1.posY()) break;
            }
            int found = static_cast<int>(treasures[i].content());
            switch(found)
            {
                case 1:
                    player1.addXp(player1.level()*8);
                    info += "## " + player1.name() + " found XP potion!\n";
                    info += "## It gave him " + toString(player1.level()*8) + " XP points!\n";
                    journal1.addEntry("Found XP potion!\n");
                    break;
                case 2:
                    player1.heal(player1.maxHp()/5);
                    info += "## " + player1.name() + " found HP potion!\n";
                    info += "## It heald him for " + toString(player1.maxHp()/5) + "!\n";
                    journal1.addEntry("Found HP potion!\n");
                    break;
                case 3:
                    player1.strUp();
                    info += "## " + player1.name() + " found STR potion!\n";
                    info += "## His strength is growing!\n";
                    journal1.addEntry("Found STR potion!\n");
                    break;
                case 4:
                    player1.conUp();
                    info += "## " + player1.name() + " found CON potion!\n";
                    info += "## His constitution is growing!\n";
                    journal1.addEntry("Found CON potion!\n");
                    break;
                case 5:
                    player1.dexUp();
                    info += "## " + player1.name() + " found DEX potion!\n";
                    info += "## His dexterity is growing!\n";
                    journal1.addEntry("Found DEX potion!\n");
                    break;
            }
            info += "## \n";
            info += "##################################\n";

            system("cls");
            cout << info;
            Sleep(sleepValue*15);
            system("cls");
        }

        if(encounter == combat)
        {
            int i = 0;
            for( ; i < enemiesCount ; i++) // finding which enemy player encountered
            {
                if(enemies[i].posX() == player1.posX() and enemies[i].posY() == player1.posY()) break;
            }
            system("cls");
            string eDesc = enemies[i].description();
            string pDesc = player1.description();
            bool descripting = false; // false player / true enemy
            int start = 0, finish = 0;
            for(unsigned int i = 0, j = 0 ; j < eDesc.length() ; )
            {
                if(!descripting)
                {
                    if(pDesc[i] != '\n') cout << pDesc[i];
                    else{finish = i; cout << string((20 - (finish - start)), ' '); descripting = true; start = i + 1;}
                    i++;
                }
                else
                {
                    cout << eDesc[j];
                    if(eDesc[j] == '\n') descripting = false;
                    j++;
                }
            }
            cout << endl;
            Sleep(sleepValue*2.5);

            while(player1.isAlive() and enemies[i].isAlive())
            {
                int hitE = ((double)enemies[i].dex()/(double)player1.dex())*100;
                int hitP = ((double)player1.dex()/(double)enemies[i].dex())*100;
                int hitCh = hitP + hitE;
                int randHit = rand() % hitCh;
                if(randHit <= hitP) // player hits
                {
                    int dmg = ((double)player1.str()/(double)enemies[i].con())*10;
                    dmg = rand() % dmg + 1;
                    enemies[i].damage(dmg);
                    cout << player1.name() << " dealt " << dmg << "!\n";
                }
                else    // enemy hits
                {
                    int dmg = ((double)enemies[i].str()/(double)player1.con())*10;
                    dmg = rand() % dmg + 1;
                    player1.damage(dmg);
                    cout << enemies[i].name() << " dealt " << dmg << "!\n";
                }
                Sleep(sleepValue*4);
            }
            system("cls");
            if(!enemies[i].isAlive()) // if enemy died
            {
                cout << "##################################\n"
                     << "## \n"
                     << "## " << player1.name() << " killed\n"
                     << "## " << enemies[i].name() << "\n"
                     << "## Earning " << enemies[i].xpValue() << " xp points!\n"
                     << "## \n"
                     << "##################################\n";
                Sleep(sleepValue*15);
                player1.addXp(enemies[i].xpValue());
                journal1.addEntry("Killed " + enemies[i].name() + "!\n");
            }
            else // if player died
            {
                cout << "##################################\n"
                     << "## \n"
                     << "## " << player1.name() << "'s \n"
                     << "## miserable life has ended! \n"
                     << "## He died at " << currentDepth << " dungeon floor!\n"
                     << "## Let's try again some other time!\n"
                     << "## \n"
                     << "##################################\n";
                Sleep(sleepValue * 40);
                level1->removeChar(player1.posX(), player1.posY(), 'P');
                level1->addChar(player1.posX(), player1.posY(), 'X');
                journal1.addEntry("!!!Died killed by " + enemies[i].name() + "!!!\n");
            }
            system("cls");
        }

        if(int newLevel = player1.levelUp())
        {
            system("cls");
            cout << "##################################\n"
                 << "## \n"
                 << "## " << player1.name() << " Leveled up!\n"
                 << "## You are now level: " << newLevel << "!\n"
                 << "## Your  base stats have grown!\n"
                 << "## \n"
                 << "##################################\n";
            Sleep(sleepValue*15);
            system("cls");
            journal1.addEntry("Leveld up!\n");
        }
        // ***
        // Drawing
        // ***

        cout << "Current Level: " << currentDepth << endl;
        level1->draw();
        cout << "++++++++++++++++++++++++++++++++" << endl;
        cout << journal1.entries();
        cout << "++++++++++++++++++++++++++++++++" << endl;
        printLegend();
        cout << "++++++++++++++++++++++++++++++++" << endl;
        Sleep(sleepValue * 2.5);
    }
}

inline void printLegend()
{
    cout << "[P] - Player [E] - Enemy\n"
         << "[T] - Treasure\n"
         << "[#] - Wall   [L] - Exit\n";
}

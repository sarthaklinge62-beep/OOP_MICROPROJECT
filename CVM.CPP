#include <iostream.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <fstream.h>
#include <graphics.h>

#define MAX_PLAYERS 50
#define MAX_TEAM_PLAYERS 15

#define PLAYER_FILE "players.dat"
#define MATCH_FILE  "match.dat"


// ==========================================================
//              GRAPHICS FUNCTION PROTOTYPES
// ==========================================================

void drawGraphicsHeader(char heading[]);
void drawBox(int x1, int y1, int x2, int y2);
void drawLine(int y);

void aboutPage1();
void aboutPage2();
void aboutPage3();
void aboutPage4();
void aboutProject();


// ==========================================================
//                     PASSWORD INPUT
// ==========================================================

void getPassword(char password[])
{
    int i;
    char ch;

    i = 0;

    while(1)
    {
        ch = getch();

        if(ch == 13)
        {
            password[i] = '\0';
            cout << "\n";
            break;
        }

        if(ch == 8)
        {
            if(i > 0)
            {
                i--;
                cout << "\b \b";
            }
        }
        else
        {
            if(i < 19)
            {
                password[i] = ch;
                i++;

                cout << "*";
            }
        }
    }
}


// ==========================================================
//                         LOGIN PAGE
// ==========================================================

int login()
{
    char username[30];
    char password[20];

    int attempts;

    attempts = 3;

    while(attempts > 0)
    {
        clrscr();

        cout << "\n\n";
        cout << "**************************************************";
        cout << "\n*                                                *";
        cout << "\n*           CRICKET MANAGEMENT SYSTEM            *";
        cout << "\n*                                                *";
        cout << "\n*                    LOGIN                       *";
        cout << "\n*                                                *";
        cout << "\n**************************************************";

        cout << "\n\nUsername : ";
        cin >> username;

        cout << "Password : ";
        getPassword(password);

        if(strcmp(username, "SARTHAK") == 0 &&
           strcmp(password, "27313235") == 0)
        {
            cout << "\nLogin Successful!";
            cout << "\nWelcome " << username << "!";

            getch();

            return 1;
        }
        else
        {
            attempts--;

            cout << "\n\nInvalid Username or Password!";

            cout << "\nAttempts Remaining : "
                 << attempts;

            if(attempts > 0)
            {
                cout << "\n\nPlease try again.";

                getch();
            }
        }
    }

    cout << "\n\nToo many failed login attempts!";

    cout << "\nProgram will exit.";

    getch();

    return 0;
}


// ==========================================================
//                         PLAYER CLASS
// ==========================================================

class Player
{
    int id;

    char name[30];
    char team[20];
    char role[20];

    int age;
    int matches;
    int runs;
    int wickets;

public:

    // ------------------------------------------------------
    // ADD PLAYER
    // ------------------------------------------------------

    void addPlayer()
    {
        int teamChoice;

        cout << "\n\nEnter Player ID       : ";
        cin >> id;

        cout << "Enter Player Name     : ";
        cin >> name;

        cout << "\nSelect Team";

        cout << "\n1. India";
        cout << "\n2. Australia";
        cout << "\n3. Pakistan";
        cout << "\n4. England";
        cout << "\n5. SouthAfrica";
        cout << "\n6. NewZealand";
        cout << "\n7. Other";

        cout << "\n\nEnter Team Number     : ";
        cin >> teamChoice;

        if(teamChoice == 1)
            strcpy(team, "India");

        else if(teamChoice == 2)
            strcpy(team, "Australia");

        else if(teamChoice == 3)
            strcpy(team, "Pakistan");

        else if(teamChoice == 4)
            strcpy(team, "England");

        else if(teamChoice == 5)
            strcpy(team, "SouthAfrica");

        else if(teamChoice == 6)
            strcpy(team, "NewZealand");

        else if(teamChoice == 7)
        {
            cout << "Enter Team Name       : ";
            cin >> team;
        }
        else
        {
            strcpy(team, "Invalid");
        }

        cout << "Enter Role            : ";
        cin >> role;

        cout << "Enter Age             : ";
        cin >> age;

        cout << "Enter Matches Played  : ";
        cin >> matches;

        cout << "Enter Total Runs      : ";
        cin >> runs;

        cout << "Enter Total Wickets   : ";
        cin >> wickets;
    }


    // ------------------------------------------------------
    // DISPLAY PLAYER
    // ------------------------------------------------------

    void displayPlayer()
    {
        cout << "\n+------------------------------------------+";

        cout << "\n| Player ID       : " << id;

        cout << "\n| Player Name     : " << name;

        cout << "\n| Team            : " << team;

        cout << "\n| Role            : " << role;

        cout << "\n| Age             : " << age;

        cout << "\n| Matches Played  : " << matches;

        cout << "\n| Total Runs      : " << runs;

        cout << "\n| Total Wickets   : " << wickets;

        cout << "\n+------------------------------------------+";
    }


    // ------------------------------------------------------
    // GET ID
    // ------------------------------------------------------

    int getID()
    {
        return id;
    }


    // ------------------------------------------------------
    // GET RUNS
    // ------------------------------------------------------

    int getRuns()
    {
        return runs;
    }


    // ------------------------------------------------------
    // GET WICKETS
    // ------------------------------------------------------

    int getWickets()
    {
        return wickets;
    }


    // ------------------------------------------------------
    // GET TEAM
    // ------------------------------------------------------

    char *getTeam()
    {
        return team;
    }


    // ------------------------------------------------------
    // SHORT DISPLAY
    // ------------------------------------------------------

    void shortDisplay()
    {
        cout << "\n"
             << id << "\t"
             << name << "\t"
             << team << "\t"
             << role << "\t"
             << runs << "\t"
             << wickets;
    }


    // ------------------------------------------------------
    // TEAM DISPLAY
    // ------------------------------------------------------

    void teamDisplay()
    {
        cout << "\n"
             << id << "\t"
             << name << "\t"
             << role << "\t"
             << age << "\t"
             << matches << "\t"
             << runs << "\t"
             << wickets;
    }


    // ------------------------------------------------------
    // PERFORMANCE
    // ------------------------------------------------------

    int getPerformance()
    {
        return runs + (wickets * 20);
    }


    // ------------------------------------------------------
    // SAVE PLAYER
    // ------------------------------------------------------

    void saveToFile(ofstream &file)
    {
        file.write((char *)this, sizeof(Player));
    }


    // ------------------------------------------------------
    // LOAD PLAYER
    // ------------------------------------------------------

    int loadFromFile(ifstream &file)
    {
        file.read((char *)this, sizeof(Player));

        if(file)
            return 1;

        return 0;
    }
};


// ==========================================================
//                         MATCH CLASS
// ==========================================================

class Match
{
    char matchID[20];

    char team1[30];
    char team2[30];

    char venue[40];
    char date[20];

    int score1;
    int score2;

    int wickets1;
    int wickets2;

    int matchEntered;

public:

    // ------------------------------------------------------
    // CONSTRUCTOR
    // ------------------------------------------------------

    Match()
    {
        matchEntered = 0;

        score1 = 0;
        score2 = 0;

        wickets1 = 0;
        wickets2 = 0;
    }


    // ------------------------------------------------------
    // ENTER MATCH
    // ------------------------------------------------------

    void enterMatch()
    {
        cout << "\n\nEnter Match ID       : ";
        cin >> matchID;

        cout << "Enter Team 1         : ";
        cin >> team1;

        cout << "Enter Team 2         : ";
        cin >> team2;

        cout << "Enter Venue          : ";
        cin >> venue;

        cout << "Enter Date           : ";
        cin >> date;

        cout << "\nEnter " << team1 << " Runs   : ";
        cin >> score1;

        cout << "Enter " << team1 << " Wickets: ";
        cin >> wickets1;

        cout << "\nEnter " << team2 << " Runs   : ";
        cin >> score2;

        cout << "Enter " << team2 << " Wickets: ";
        cin >> wickets2;

        matchEntered = 1;
    }


    // ------------------------------------------------------
    // DISPLAY MATCH
    // ------------------------------------------------------

    void displayMatch()
    {
        if(matchEntered == 0)
        {
            cout << "\n\nNo match information available!";

            cout << "\nPlease enter match details first.";

            return;
        }

        cout << "\n\n==============================================";

        cout << "\n             MATCH SCORECARD";

        cout << "\n==============================================";

        cout << "\n\nMatch ID : " << matchID;

        cout << "\nVenue    : " << venue;

        cout << "\nDate     : " << date;

        cout << "\n\n----------------------------------------------";

        cout << "\nTeam\t\tRuns\tWickets";

        cout << "\n----------------------------------------------";

        cout << "\n" << team1 << "\t\t"
             << score1 << "\t"
             << wickets1;

        cout << "\n" << team2 << "\t\t"
             << score2 << "\t"
             << wickets2;

        cout << "\n----------------------------------------------";

        cout << "\n\nMATCH RESULT : ";

        if(score1 > score2)
            cout << team1 << " WON THE MATCH!";

        else if(score2 > score1)
            cout << team2 << " WON THE MATCH!";

        else
            cout << "MATCH DRAW!";

        cout << "\n==============================================";
    }


    // ------------------------------------------------------
    // SAVE MATCH
    // ------------------------------------------------------

    void saveToFile()
    {
        ofstream file;

        file.open(MATCH_FILE, ios::binary);

        if(!file)
        {
            cout << "\nUnable to open match file!";
            return;
        }

        file.write((char *)this, sizeof(Match));

        file.close();
    }


    // ------------------------------------------------------
    // LOAD MATCH
    // ------------------------------------------------------

    void loadFromFile()
    {
        ifstream file;

        file.open(MATCH_FILE, ios::binary);

        if(!file)
            return;

        file.read((char *)this, sizeof(Match));

        file.close();
    }
};


// ==========================================================
//                           TITLE
// ==========================================================

void title()
{
    cout << "\n\n";

    cout << "**************************************************";

    cout << "\n*                                                *";

    cout << "\n*        CRICKET MANAGEMENT SYSTEM               *";

    cout << "\n*                                                *";

    cout << "\n*             C++ MICRO PROJECT                  *";

    cout << "\n*                                                *";

    cout << "\n**************************************************";
}


// ==========================================================
//                  SAVE PLAYER DATA
// ==========================================================

void savePlayers(Player players[], int playerCount)
{
    ofstream file;

    int i;

    file.open(PLAYER_FILE, ios::binary);

    if(!file)
    {
        cout << "\nUnable to open player data file!";
        return;
    }

    file.write((char *)&playerCount,
               sizeof(playerCount));

    for(i = 0; i < playerCount; i++)
    {
        players[i].saveToFile(file);
    }

    file.close();
}


// ==========================================================
//                  LOAD PLAYER DATA
// ==========================================================

int loadPlayers(Player players[])
{
    ifstream file;

    int playerCount;
    int i;

    playerCount = 0;

    file.open(PLAYER_FILE, ios::binary);

    if(!file)
        return 0;

    file.read((char *)&playerCount,
              sizeof(playerCount));

    if(playerCount < 0 ||
       playerCount > MAX_PLAYERS)
    {
        playerCount = 0;

        file.close();

        return 0;
    }

    for(i = 0; i < playerCount; i++)
    {
        if(!players[i].loadFromFile(file))
        {
            playerCount = i;
            break;
        }
    }

    file.close();

    return playerCount;
}


// ==========================================================
//                GRAPHICS HEADER
// ==========================================================

void drawGraphicsHeader(char heading[])
{
    setcolor(LIGHTBLUE);

    rectangle(20, 20, 620, 55);

    setfillstyle(SOLID_FILL, BLUE);

    floodfill(25, 25, LIGHTBLUE);

    setcolor(WHITE);

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);

    outtextxy(180, 30, heading);
}


// ==========================================================
//                     GRAPHICS BOX
// ==========================================================

void drawBox(int x1, int y1, int x2, int y2)
{
    setcolor(CYAN);

    rectangle(x1, y1, x2, y2);

    setcolor(BLUE);

    rectangle(x1 + 4,
              y1 + 4,
              x2 - 4,
              y2 - 4);
}


// ==========================================================
//                     GRAPHICS LINE
// ==========================================================

void drawLine(int y)
{
    setcolor(LIGHTCYAN);

    line(40, y, 600, y);
}


// ==========================================================
//                 ABOUT PROJECT PAGE 1
// ==========================================================

void aboutPage1()
{
    cleardevice();

    setbkcolor(BLACK);

    drawGraphicsHeader("PROJECT INTRODUCTION");

    drawBox(35, 80, 605, 400);

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

    setcolor(YELLOW);

    outtextxy(60, 105,
              "CRICKET MANAGEMENT SYSTEM");

    setcolor(WHITE);

    outtextxy(60, 135,
              "A C++ project for managing cricket data.");

    outtextxy(60, 160,
              "It stores player, team and match information.");

    drawLine(190);

    setcolor(LIGHTGREEN);

    outtextxy(60, 215,
              "MAIN FEATURES");

    setcolor(WHITE);

    outtextxy(70, 245,
              "1. Add / Delete Player");

    outtextxy(70, 270,
              "2. Search Player");

    outtextxy(70, 295,
              "3. Team-wise Players");

    outtextxy(70, 320,
              "4. Player Statistics");

    outtextxy(330, 245,
              "5. Highest Run Scorer");

    outtextxy(330, 270,
              "6. Highest Wicket Taker");

    outtextxy(330, 295,
              "7. Match Scorecard");

    outtextxy(330, 320,
              "8. File Handling");

    setcolor(LIGHTCYAN);

    outtextxy(235, 350,
              "LOGIN SYSTEM");

    outtextxy(190, 430,
              "PAGE 1 / 4");

    outtextxy(155, 455,
              "Press any key for next page");

    getch();
}


// ==========================================================
//                 ABOUT PROJECT PAGE 2
// ==========================================================

void aboutPage2()
{
    cleardevice();

    setbkcolor(BLACK);

    drawGraphicsHeader("OOP CONCEPTS 1 - 3");

    drawBox(35, 80, 605, 400);

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

    setcolor(YELLOW);

    outtextxy(60, 110,
              "1. CLASS");

    setcolor(WHITE);

    outtextxy(70, 140,
              "Player and Match are classes.");

    outtextxy(70, 165,
              "They contain data and functions.");

    drawLine(190);

    setcolor(YELLOW);

    outtextxy(60, 220,
              "2. OBJECT");

    setcolor(WHITE);

    outtextxy(70, 250,
              "players[] and match are objects.");

    outtextxy(70, 275,
              "They represent project entities.");

    drawLine(300);

    setcolor(YELLOW);

    outtextxy(60, 330,
              "3. ENCAPSULATION");

    setcolor(WHITE);

    outtextxy(70, 360,
              "Data and functions are grouped");

    outtextxy(70, 385,
              "inside the class.");

    setcolor(LIGHTCYAN);

    outtextxy(235, 430,
              "PAGE 2 / 4");

    outtextxy(155, 455,
              "Press any key for next page");

    getch();
}


// ==========================================================
//                 ABOUT PROJECT PAGE 3
// ==========================================================

void aboutPage3()
{
    cleardevice();

    setbkcolor(BLACK);

    drawGraphicsHeader("OOP CONCEPTS 4 - 6");

    drawBox(35, 80, 605, 400);

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

    setcolor(YELLOW);

    outtextxy(60, 110,
              "4. ABSTRACTION");

    setcolor(WHITE);

    outtextxy(70, 140,
              "Complex operations are hidden.");

    outtextxy(70, 165,
              "Simple functions are provided.");

    drawLine(190);

    setcolor(YELLOW);

    outtextxy(60, 220,
              "5. CONSTRUCTOR");

    setcolor(WHITE);

    outtextxy(70, 250,
              "Match() initializes match data.");

    outtextxy(70, 275,
              "It runs automatically.");

    drawLine(300);

    setcolor(YELLOW);

    outtextxy(60, 330,
              "6. MEMBER FUNCTIONS");

    setcolor(WHITE);

    outtextxy(70, 360,
              "Functions such as addPlayer(),");

    outtextxy(70, 385,
              "displayPlayer() work on class data.");

    setcolor(LIGHTCYAN);

    outtextxy(235, 430,
              "PAGE 3 / 4");

    outtextxy(155, 455,
              "Press any key for next page");

    getch();
}


// ==========================================================
//                 ABOUT PROJECT PAGE 4
// ==========================================================

void aboutPage4()
{
    cleardevice();

    setbkcolor(BLACK);

    drawGraphicsHeader("TECHNOLOGY & TEAM");

    drawBox(35, 80, 605, 400);

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

    setcolor(LIGHTGREEN);

    outtextxy(60, 110,
              "TECHNOLOGY");

    setcolor(WHITE);

    outtextxy(70, 140,
              "Language : C++");

    outtextxy(70, 165,
              "Platform : Turbo C++");

    outtextxy(70, 190,
              "Graphics : graphics.h");

    outtextxy(70, 215,
              "Storage  : Binary Files");

    drawLine(240);

    setcolor(LIGHTGREEN);

    outtextxy(60, 270,
              "PROJECT TEAM");

    setcolor(WHITE);

    outtextxy(70, 300,
              "1. PRANAV KHADTARE");

    outtextxy(70, 325,
              "2. RAHUL KOLI");

    outtextxy(70, 350,
              "3. VIRAJ KORE");

    outtextxy(70, 375,
              "4. SARTHAK LINGE");

    setcolor(YELLOW);

    outtextxy(250, 410,
              "GROUP G15");

    setcolor(LIGHTCYAN);

    outtextxy(235, 440,
              "PAGE 4 / 4");

    outtextxy(135, 465,
              "Press any key to return Main Menu");

    getch();
}


// ==========================================================
//                    ABOUT PROJECT
// ==========================================================

void aboutProject()
{
    int gd;
    int gm;

    gd = DETECT;
    gm = 0;

    initgraph(&gd, &gm, "C://TC//BGI");

    setbkcolor(BLACK);

    aboutPage1();
    aboutPage2();
    aboutPage3();
    aboutPage4();

    closegraph();

    clrscr();
}


// ==========================================================
//                           MAIN
// ==========================================================

void main()
{
    Player players[MAX_PLAYERS];

    Match match;

    int playerCount;
    int choice;
    int i;
    int searchID;
    int found;

    playerCount = 0;
    choice = 0;
    i = 0;
    searchID = 0;
    found = 0;

    clrscr();


    // ======================================================
    // LOGIN
    // ======================================================

    if(login() == 0)
    {
        return;
    }


    // ======================================================
    // LOAD DATA
    // ======================================================

    playerCount = loadPlayers(players);

    match.loadFromFile();


    // ======================================================
    // MAIN MENU
    // ======================================================

    do
    {
        clrscr();

        title();

        cout << "\n\n                MAIN MENU";

        cout << "\n";

        cout << "\n   [1]  Add New Player";

        cout << "\n   [2]  Display All Players";

        cout << "\n   [3]  Search Player";

        cout << "\n   [4]  Display Team Players";

        cout << "\n   [5]  Player Statistics";

        cout << "\n   [6]  Highest Run Scorer";

        cout << "\n   [7]  Highest Wicket Taker";

        cout << "\n   [8]  Enter Match Details";

        cout << "\n   [9]  Display Match Scorecard";

        cout << "\n   [10] About Project";

        cout << "\n   [11] Man of the Match";

        cout << "\n   [12] Save Data";

        cout << "\n   [13] Delete Player";

        cout << "\n   [14] Logout";

        cout << "\n   [0]  Exit";

        cout << "\n\n----------------------------------------------";

        cout << "\nEnter Your Choice : ";

        cin >> choice;


        switch(choice)
        {

        // ==================================================
        // ADD NEW PLAYER
        // ==================================================

        case 1:
        {
            Player temp;

            int duplicateID;
            int teamCount;

            duplicateID = 0;
            teamCount = 0;

            clrscr();

            title();

            cout << "\n\n              ADD NEW PLAYER";

            cout << "\n----------------------------------------------";

            if(playerCount < MAX_PLAYERS)
            {
                temp.addPlayer();

                for(i = 0; i < playerCount; i++)
                {
                    if(players[i].getID() ==
                       temp.getID())
                    {
                        duplicateID = 1;
                        break;
                    }
                }

                if(duplicateID == 1)
                {
                    cout << "\n\nPlayer ID already exists!";

                    cout << "\nPlease enter a different Player ID.";
                }
                else
                {
                    for(i = 0; i < playerCount; i++)
                    {
                        if(strcmp(players[i].getTeam(),
                                  temp.getTeam()) == 0)
                        {
                            teamCount++;
                        }
                    }

                    if(teamCount < MAX_TEAM_PLAYERS)
                    {
                        players[playerCount] = temp;

                        playerCount++;

                        savePlayers(players,
                                    playerCount);

                        cout << "\n\nPlayer added successfully!";

                        cout << "\nPlayer data saved to file.";

                        cout << "\nTeam : "
                             << temp.getTeam();

                        cout << "\nPlayers in "
                             << temp.getTeam()
                             << " : "
                             << teamCount + 1
                             << "/15";
                    }
                    else
                    {
                        cout << "\n\nTeam "
                             << temp.getTeam()
                             << " already has 15 players!";

                        cout << "\nCannot add more players.";
                    }
                }
            }
            else
            {
                cout << "\nPlayer limit reached!";

                cout << "\nMaximum players allowed : 50";
            }

            getch();

            break;
        }


        // ==================================================
        // DISPLAY ALL PLAYERS
        // ==================================================

        case 2:
        {
            clrscr();

            title();

            cout << "\n\n              PLAYER LIST";

            if(playerCount == 0)
            {
                cout << "\nNo player records available!";
            }
            else
            {
                cout << "\nID\tName\tTeam\tRole\tRuns\tWickets";

                cout << "\n----------------------------------------------------------";

                for(i = 0; i < playerCount; i++)
                {
                    players[i].shortDisplay();
                }
            }

            getch();

            break;
        }


        // ==================================================
        // SEARCH PLAYER
        // ==================================================

        case 3:
        {
            clrscr();

            title();

            cout << "\n\n              SEARCH PLAYER";

            cout << "\n----------------------------------------------";

            if(playerCount == 0)
            {
                cout << "\nNo player records available!";
            }
            else
            {
                cout << "\nEnter Player ID : ";

                cin >> searchID;

                found = 0;

                for(i = 0; i < playerCount; i++)
                {
                    if(players[i].getID() ==
                       searchID)
                    {
                        players[i].displayPlayer();

                        found = 1;

                        break;
                    }
                }

                if(found == 0)
                {
                    cout << "\n\nPlayer not found!";
                }
            }

            getch();

            break;
        }


        // ==================================================
        // DISPLAY TEAM PLAYERS
        // ==================================================

        case 4:
        {
            char searchTeam[20];

            int teamChoice;
            int teamCount;

            teamChoice = 0;
            teamCount = 0;

            clrscr();

            title();

            cout << "\n\n             TEAM PLAYER LIST";

            if(playerCount == 0)
            {
                cout << "\nNo player records available!";
            }
            else
            {
                cout << "\n\nSELECT TEAM";

                cout << "\n1. India";
                cout << "\n2. Australia";
                cout << "\n3. Pakistan";
                cout << "\n4. England";
                cout << "\n5. SouthAfrica";
                cout << "\n6. NewZealand";
                cout << "\n7. Other";

                cout << "\n\nEnter Team Number : ";

                cin >> teamChoice;

                if(teamChoice == 1)
                    strcpy(searchTeam, "India");

                else if(teamChoice == 2)
                    strcpy(searchTeam, "Australia");

                else if(teamChoice == 3)
                    strcpy(searchTeam, "Pakistan");

                else if(teamChoice == 4)
                    strcpy(searchTeam, "England");

                else if(teamChoice == 5)
                    strcpy(searchTeam, "SouthAfrica");

                else if(teamChoice == 6)
                    strcpy(searchTeam, "NewZealand");

                else if(teamChoice == 7)
                {
                    cout << "\nEnter Team Name : ";
                    cin >> searchTeam;
                }
                else
                {
                    cout << "\nInvalid Team Choice!";

                    getch();

                    break;
                }

                cout << "\n\n==============================================";

                cout << "\n              TEAM : "
                     << searchTeam;

                cout << "\n==============================================";

                cout << "\nID\tName\tRole\tAge\tMatches\tRuns\tWickets";

                cout << "\n--------------------------------------------------------------";

                for(i = 0; i < playerCount; i++)
                {
                    if(strcmp(players[i].getTeam(),
                              searchTeam) == 0)
                    {
                        players[i].teamDisplay();

                        teamCount++;
                    }
                }

                if(teamCount == 0)
                {
                    cout << "\n\nNo players found for "
                         << searchTeam
                         << "!";
                }
                else
                {
                    cout << "\n\n----------------------------------------------";

                    cout << "\nTotal Players in "
                         << searchTeam
                         << " : "
                         << teamCount;

                    cout << "\nMaximum Players Allowed : 15";

                    cout << "\nRemaining Places        : "
                         << 15 - teamCount;
                }
            }

            getch();

            break;
        }


        // ==================================================
        // PLAYER STATISTICS
        // ==================================================

        case 5:
        {
            int totalRuns;
            int totalWickets;

            float averageRuns;
            float averageWickets;

            totalRuns = 0;
            totalWickets = 0;

            clrscr();

            title();

            cout << "\n\n             PLAYER STATISTICS";

            if(playerCount == 0)
            {
                cout << "\nNo statistics available!";
            }
            else
            {
                cout << "\n\nID\tName\tTeam\tRole\tRuns\tWickets";

                cout << "\n----------------------------------------------------------";

                for(i = 0; i < playerCount; i++)
                {
                    players[i].shortDisplay();

                    totalRuns =
                        totalRuns + players[i].getRuns();

                    totalWickets =
                        totalWickets + players[i].getWickets();
                }

                averageRuns =
                    (float)totalRuns / playerCount;

                averageWickets =
                    (float)totalWickets / playerCount;

                cout << "\n\n==============================================";

                cout << "\n             STATISTICS SUMMARY";

                cout << "\n==============================================";

                cout << "\n\nTotal Runs       : "
                     << totalRuns;

                cout << "\nTotal Wickets    : "
                     << totalWickets;

                cout << "\nAverage Runs     : "
                     << averageRuns;

                cout << "\nAverage Wickets  : "
                     << averageWickets;

                cout << "\n==============================================";
            }

            getch();

            break;
        }


        // ==================================================
        // HIGHEST RUN SCORER
        // ==================================================

        case 6:
        {
            int maxRuns;
            int index;

            maxRuns = 0;
            index = 0;

            clrscr();

            title();

            cout << "\n\n             HIGHEST RUN SCORER";

            if(playerCount == 0)
            {
                cout << "\nNo player records available!";
            }
            else
            {
                maxRuns = players[0].getRuns();

                index = 0;

                for(i = 1; i < playerCount; i++)
                {
                    if(players[i].getRuns() > maxRuns)
                    {
                        maxRuns = players[i].getRuns();

                        index = i;
                    }
                }

                players[index].displayPlayer();
            }

            getch();

            break;
        }


        // ==================================================
        // HIGHEST WICKET TAKER
        // ==================================================

        case 7:
        {
            int maxWickets;
            int index2;

            maxWickets = 0;
            index2 = 0;

            clrscr();

            title();

            cout << "\n\n             HIGHEST WICKET TAKER";

            if(playerCount == 0)
            {
                cout << "\nNo player records available!";
            }
            else
            {
                maxWickets = players[0].getWickets();

                index2 = 0;

                for(i = 1; i < playerCount; i++)
                {
                    if(players[i].getWickets() > maxWickets)
                    {
                        maxWickets = players[i].getWickets();

                        index2 = i;
                    }
                }

                players[index2].displayPlayer();
            }

            getch();

            break;
        }


        // ==================================================
        // ENTER MATCH DETAILS
        // ==================================================

        case 8:
        {
            clrscr();

            title();

            cout << "\n\n              MATCH MANAGEMENT";

            match.enterMatch();

            match.saveToFile();

            cout << "\n\nMatch information saved successfully!";

            getch();

            break;
        }


        // ==================================================
        // DISPLAY MATCH
        // ==================================================

        case 9:
        {
            clrscr();

            title();

            match.displayMatch();

            getch();

            break;
        }


        // ==================================================
        // ABOUT PROJECT - GRAPHICS ONLY
        // ==================================================

        case 10:
        {
            aboutProject();

            break;
        }


        // ==================================================
        // MAN OF THE MATCH
        // ==================================================

        case 11:
        {
            int maxPerformance;
            int manIndex;

            maxPerformance = 0;
            manIndex = 0;

            clrscr();

            title();

            cout << "\n\n              MAN OF THE MATCH";

            if(playerCount == 0)
            {
                cout << "\nNo player records available!";

                cout << "\nPlease add players first.";
            }
            else
            {
                maxPerformance =
                    players[0].getPerformance();

                manIndex = 0;

                for(i = 1; i < playerCount; i++)
                {
                    if(players[i].getPerformance()
                       > maxPerformance)
                    {
                        maxPerformance =
                            players[i].getPerformance();

                        manIndex = i;
                    }
                }

                players[manIndex].displayPlayer();

                cout << "\n\nPerformance Score : "
                     << maxPerformance;

                cout << "\n\nCalculation:";

                cout << "\nRuns + (Wickets x 20)";

                cout << "\n\nRuns : "
                     << players[manIndex].getRuns();

                cout << "\nWickets : "
                     << players[manIndex].getWickets();
            }

            getch();

            break;
        }


        // ==================================================
        // SAVE DATA
        // ==================================================

        case 12:
        {
            clrscr();

            title();

            cout << "\n\n              SAVE DATA";

            cout << "\n----------------------------------------------";

            savePlayers(players, playerCount);

            match.saveToFile();

            cout << "\n\nPlayer data saved successfully!";

            cout << "\nMatch data saved successfully!";

            cout << "\n\nFiles used:";

            cout << "\n1. players.dat";

            cout << "\n2. match.dat";

            getch();

            break;
        }


        // ==================================================
        // DELETE PLAYER
        // ==================================================

        case 13:
        {
            int deleteID;
            int deleteIndex;
            char confirm;

            deleteID = 0;
            deleteIndex = -1;
            confirm = 'N';

            clrscr();

            title();

            cout << "\n\n              DELETE PLAYER";

            cout << "\n----------------------------------------------";

            if(playerCount == 0)
            {
                cout << "\nNo player records available!";
            }
            else
            {
                cout << "\n\nEnter Player ID to Delete : ";

                cin >> deleteID;

                for(i = 0; i < playerCount; i++)
                {
                    if(players[i].getID() ==
                       deleteID)
                    {
                        deleteIndex = i;

                        break;
                    }
                }

                if(deleteIndex == -1)
                {
                    cout << "\n\nPlayer with ID "
                         << deleteID
                         << " not found!";
                }
                else
                {
                    cout << "\n\nPlayer found!";

                    players[deleteIndex].displayPlayer();

                    cout << "\n\nAre you sure you want to delete this player?";

                    cout << "\nEnter Y to confirm or N to cancel : ";

                    cin >> confirm;

                    if(confirm == 'Y' ||
                       confirm == 'y')
                    {
                        for(i = deleteIndex;
                            i < playerCount - 1;
                            i++)
                        {
                            players[i] =
                                players[i + 1];
                        }

                        playerCount--;

                        savePlayers(players,
                                    playerCount);

                        cout << "\n\nPlayer deleted successfully!";

                        cout << "\nRemaining Players : "
                             << playerCount;
                    }
                    else
                    {
                        cout << "\n\nDelete operation cancelled.";
                    }
                }
            }

            getch();

            break;
        }


        // ==================================================
        // LOGOUT
        // ==================================================

        case 14:
        {
            clrscr();

            savePlayers(players, playerCount);

            match.saveToFile();

            cout << "\n\n";

            cout << "********************************************";

            cout << "\n*                                          *";

            cout << "\n*             LOGOUT SUCCESSFUL            *";

            cout << "\n*                                          *";

            cout << "\n********************************************";

            getch();

            if(login() == 0)
            {
                return;
            }

            break;
        }


        // ==================================================
        // EXIT
        // ==================================================

        case 0:
        {
            savePlayers(players, playerCount);

            match.saveToFile();

            clrscr();

            cout << "\n\n";

            cout << "********************************************";

            cout << "\n*                                          *";

            cout << "\n*       THANK YOU FOR USING THE SYSTEM     *";

            cout << "\n*                                          *";

            cout << "\n********************************************";

            cout << "\n\nAll data has been saved.";

            getch();

            break;
        }


        // ==================================================
        // INVALID CHOICE
        // ==================================================

        default:
        {
            cout << "\n\nInvalid choice!";

            cout << "\nPlease enter a valid option.";

            getch();

            break;
        }

        }

    } while(choice != 0);
}

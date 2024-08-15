#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#pragma comment(lib, "Winmm.lib")

using namespace std;

struct Tail                                                                 //Структура "Хвост"
{
    int vr, hr;
    Tail* next,* prev;
};

Tail* Movement(Tail* head, int vr, int hr, int* len)                        //Функция передвижения головы (Заполнение новой клетки впереди головы)
{
    Tail* s = new Tail;
    s->prev = NULL;
    head->prev = s;
    s->next = head;
    head = s;
    s->vr = vr;
    s->hr = hr;
    len++;
    return head;
}

Tail* Delete(Tail* tail, int* ver, int* hor)                                 //Функция передвижения хвоста (Удаление последней заполненной клектки)
{
    Tail* s;
    s = tail;
    *ver = s->vr; *hor = s->hr;
    tail = tail->prev;
    delete s;
    tail->next = NULL;
    return tail;
}

void Settings(int f, int sp)                                                  //Вывод настроек
{
    cout << "(Settings: field size: ";
    if (f == 0) cout << "small";
    if (f == 1) cout << "medium";
    if (f == 2) cout << "large";
    cout << "; difficulty: ";
    if (sp == 0) cout << "easy";
    if (sp == 1) cout << "medium";
    if (sp == 2) cout << "hard";
    cout << "; goal: ";
    if (f == 0) cout << "75 points)";
    if (f == 1) cout << "150 points)";
    if (f == 2) cout << "300 points)";
}

int main()
{
    srand(time(0));
    setlocale(LC_ALL, "ru");

    Tail* head, * tail;                                                         //Двунаправленный список - хвост змейки

    int** field;                                                                //Массив клеток поля                                                              

    bool up = 0, down = 0, left = 0, right = 0, treat = 0;                      //Направление движения змейки
                                                                                //Только одна из переменных может быть равна 1 в определенный момент времени

    int spd = 200;                                                              //Задержка (скорость) передвижения змейки

    char s[2];                                                                  //Введнный символ (W, A, S, D) определяет направление движения

    int m = 0, f = 0, e = 1, sp = 1; char mm;                                   //Переменные для работы меню

    int ver, ver_lim, ver_mem, ver_treat, hor, hor_lim, hor_mem, hor_treat, len, len_lim;

    ver_lim = hor_lim = 10;

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);


    cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t" << "   -=:PRESS ANY BUTTON TO START:=-";
    s[0] = _getch();

    SetConsoleTextAttribute(handle, FOREGROUND_GREEN);

    system("cls");

    PlaySound(TEXT("LDNGSCR.wav"), NULL, SND_ASYNC);

    Sleep(1000);

    //"Заставка"
    cout << endl << endl << endl << endl << endl << endl << endl;
    cout << "\t\t\t\t\t\t\t" << "   SSSSSSS       NNN          NNN         AAAAAA         KKK          KKK    EEEEEEEEEEEEEEEE" << endl; Sleep(100);     
    cout << "\t\t\t\t\t\t\t" << "  SSSSSSSSS      NNN          NNN         AAAAAA         KKK         KKKK    EEEEEEEEEEEEEEEE" << endl; Sleep(100);
    cout << "\t\t\t\t\t\t\t" << " SSSSSSSSSSS     NNNNN        NNN         AAAAAA         KKK        KKKKK    EEEEEEEEEEEEEEEE" << endl; Sleep(100);
    cout << "\t\t\t\t\t\t\t" << "SSSSS   SSSSS    NNNNN        NNN         AAAAAA         KKK       KKKKK     EEE             " << endl; Sleep(100);
    cout << "\t\t\t\t\t\t\t" << "SSSS     SSSS    NNNNNN       NNN        AAA  AAA        KKK      KKKKK      EEE             " << endl; Sleep(100);
    cout << "\t\t\t\t\t\t\t" << "SSS       SSS    NNNNNN       NNN        AAA  AAA        KKK     KKKKK       EEE             " << endl; Sleep(100);    
    cout << "\t\t\t\t\t\t\t" << "SSS              NNNNNNN      NNN        AAA  AAA        KKK    KKKKK        EEE             " << endl; Sleep(100);
    cout << "\t\t\t\t\t\t\t" << "SSSS             NNN NNN      NNN        AAA  AAA        KKK   KKKKK         EEE             " << endl; Sleep(100);
    cout << "\t\t\t\t\t\t\t" << "SSSSS            NNN NNNN     NNN       AAAA  AAAA       KKK  KKKKK          EEE             " << endl; Sleep(100);
    cout << "\t\t\t\t\t\t\t" << " SSSSS           NNN  NNNN    NNN       AAA    AAA       KKK KKKKK           EEE             " << endl; Sleep(100);
    cout << "\t\t\t\t\t\t\t" << "  SSSSS          NNN  NNNN    NNN       AAA    AAA       KKKKKKKK            EEE             " << endl; Sleep(100);
    cout << "\t\t\t\t\t\t\t" << "   SSSSS         NNN   NNNN   NNN       AAA    AAA       KKKKKKK             EEE             " << endl; Sleep(100);    
    cout << "\t\t\t\t\t\t\t" << "    SSSSS        NNN   NNNN   NNN      AAAAAAAAAAAA      KKKKKKK             EEEEEEEEEEEE    " << endl; Sleep(100);
    cout << "\t\t\t\t\t\t\t" << "     SSSSS       NNN    NNNN  NNN      AAAAAAAAAAAA      KKKKKKK             EEEEEEEEEEEE    " << endl; Sleep(100);
    cout << "\t\t\t\t\t\t\t" << "      SSSSS      NNN    NNNN  NNN      AAAAAAAAAAAA      KKKKKKKK            EEEEEEEEEEEE    " << endl; Sleep(100);
    cout << "\t\t\t\t\t\t\t" << "       SSSSS     NNN     NNNN NNN      AAAA    AAAA      KKK KKKKK           EEE             " << endl; Sleep(100);
    cout << "\t\t\t\t\t\t\t" << "        SSSSS    NNN      NNN NNN     AAAA      AAAA     KKK  KKKKK          EEE             " << endl; Sleep(100);    
    cout << "\t\t\t\t\t\t\t" << "         SSSS    NNN      NNNNNNN     AAA        AAA     KKK   KKKKK         EEE             " << endl; Sleep(100);
    cout << "\t\t\t\t\t\t\t" << "SSS       SSS    NNN       NNNNNN     AAA        AAA     KKK    KKKKK        EEE             " << endl; Sleep(100);
    cout << "\t\t\t\t\t\t\t" << "SSSS     SSSS    NNN       NNNNNN     AAA        AAA     KKK     KKKKK       EEE             " << endl; Sleep(100);
    cout << "\t\t\t\t\t\t\t" << "SSSSS   SSSSS    NNN        NNNNN    AAAA        AAAA    KKK      KKKKK      EEE             " << endl; Sleep(100);
    cout << "\t\t\t\t\t\t\t" << " SSSSSSSSSSS     NNN          NNN    AAA          AAA    KKK       KKKKK     EEEEEEEEEEEEEEEE" << endl; Sleep(100);
    cout << "\t\t\t\t\t\t\t" << "  SSSSSSSSS      NNN          NNN    AAA          AAA    KKK        KKKKK    EEEEEEEEEEEEEEEE" << endl; Sleep(100);
    cout << "\t\t\t\t\t\t\t" << "   SSSSSSS       NNN          NNN    AAA          AAA    KKK         KKKKK   EEEEEEEEEEEEEEEE" << endl; Sleep(100);    
    cout << endl << endl << endl; Sleep(4000);     
    cout << "\t\t\t\t\t\t\t" << "                    TTTTT  H   H  EEEEE      GGGGG  AAAAA  M   M  EEEEE" << endl; Sleep(100);
    cout << "\t\t\t\t\t\t\t" << "                      T    H   H  E          G   G  A   A  MM MM  E    " << endl; Sleep(100); 
    cout << "\t\t\t\t\t\t\t" << "                      T    H   H  E          G      A   A  MM MM  E    " << endl; Sleep(100);
    cout << "\t\t\t\t\t\t\t" << "                      T    HHHHH  EEE        G      AAAAA  M M M  EEE  " << endl; Sleep(100); 
    cout << "\t\t\t\t\t\t\t" << "                      T    H   H  E          G GGG  A   A  M M M  E    " << endl; Sleep(100); 
    cout << "\t\t\t\t\t\t\t" << "                      T    H   H  E          G   G  A   A  M   M  E    " << endl; Sleep(100); 
    cout << "\t\t\t\t\t\t\t" << "                      T    H   H  EEEEE      GGGGG  A   A  M   M  EEEEE" << endl;

    Sleep(3500);
    system("cls");

    bool menu = 1, f1eld = 1, speed = 1, exit = 1, loss = 1, win = 0;                                               //Работа с меню
    while (1)
    {
        system("color 7");
        while (menu)
        {
            f1eld = exit = speed = 1; e = 1;

            if (m == 0)
            {
                cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "   -=PLAY=-" << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "  field size" << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "  difficulty" << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "   controls" << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "     exit" << endl << endl << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "      "; Settings(f, sp); cout << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "use W/S to move" << endl << endl;
            }
            if (m == 1)
            {
                cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "     play  " << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "-=FIELD SIZE=-" << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "  difficulty" << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "   controls" << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "     exit" << endl << endl << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "      "; Settings(f, sp); cout << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "use W/S to move" << endl << endl;
            }
            if (m == 2)
            {
                cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "     play  " << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "  field size" << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "-=DIFFICULTY=-" << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "   controls" << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "     exit" << endl << endl << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "      "; Settings(f, sp); cout << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "use W/S to move" << endl << endl;
            }
            if (m == 3)
            {
                cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "     play  " << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "  field size" << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "  difficulty" << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << " -=CONTROLS=-" << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "     exit" << endl << endl << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "      "; Settings(f, sp); cout << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "use W/S to move" << endl << endl;
            }
            if (m == 4)
            {
                cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "     play  " << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "  field size" << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "  difficulty" << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "   controls" << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "   -=EXIT=-" << endl << endl << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "      "; Settings(f, sp); cout << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "use W/S to move" << endl << endl;
            }

            mm = _getch();
            system("cls");

            if ((mm == 's' or mm == 'S') and m != 4)
            {
                PlaySound(TEXT("STEP.wav"), NULL, SND_ASYNC);
                m++;
            }
            if ((mm == 'w' or mm == 'W') and m != 0)
            {
                PlaySound(TEXT("STEP.wav"), NULL, SND_ASYNC);
                m--;
            }

            if (mm == 13 and m == 0)
            {
                PlaySound(TEXT("PLSND.wav"), NULL, SND_ASYNC);
                menu = 0;
            }

            if (mm == 13 and m == 1)
            {
                PlaySound(TEXT("SWTCH.wav"), NULL, SND_ASYNC);
                while (f1eld)
                {
                    cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
                    cout << "\t\t\t\t\t\t\t\t\t\t\t" << "       CHOOSE THE FIELD SIZE" << endl << endl;
                    if (f == 0)
                    {
                        cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "  -=SMALL (9x9)=-" << endl << endl;
                        cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "  medium  (13x13)" << endl << endl;
                        cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "   large (19x19)" << endl << endl;
                    }
                    if (f == 1)
                    {
                        cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "    small (9x9)" << endl << endl;
                        cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "-=MEDIUM  (13x13)=-" << endl << endl;
                        cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "   large (19x19)" << endl << endl;
                    }
                    if (f == 2)
                    {
                        cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "    small (9x9)" << endl << endl;
                        cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "  medium  (13x13)" << endl << endl;
                        cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << " -=LARGE (19x19)=-" << endl << endl;
                    }

                    cout << endl << "\t\t\t\t\t\t\t\t\t\t\t\t" << "(goal: ";
                    if (f == 0) cout << " 75";
                    else if (f == 1) cout << "150";
                    else cout << "300";
                    cout << " points)" << endl << endl;

                    mm = _getch();
                    system("cls");
                    PlaySound(TEXT("STEP.wav"), NULL, SND_ASYNC);

                    if ((mm == 's' or mm == 'S') and f != 2) f++;
                    if ((mm == 'w' or mm == 'W') and f != 0) f--;
                    if (mm == 13 and f == 0)
                    {
                        ver_lim = hor_lim = 10;
                        f1eld = 0;
                    }
                    if (mm == 13 and f == 1)
                    {
                        ver_lim = hor_lim = 14;
                        f1eld = 0;
                    }
                    if (mm == 13 and f == 2)
                    {
                        ver_lim = hor_lim = 20;
                        f1eld = 0;
                    }
                }
                PlaySound(TEXT("SWTCH.wav"), NULL, SND_ASYNC);
            }

            if (mm == 13 and m == 2)
            {
                PlaySound(TEXT("SWTCH.wav"), NULL, SND_ASYNC);
                while (speed)
                {
                    cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
                    cout << "\t\t\t\t\t\t\t\t\t\t\t" << "       CHOOSE THE DIFFICULTY" << endl << endl;
                    if (sp == 0)
                    {
                        cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "     -=EASY=-" << endl << endl;
                        cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "      medium" << endl << endl;
                        cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "       hard" << endl << endl;
                    }
                    if (sp == 1)
                    {
                        cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "       easy" << endl << endl;
                        cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "    -=MEDIUM=-" << endl << endl;
                        cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "       hard" << endl << endl;
                    }
                    if (sp == 2)
                    {
                        cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "       easy" << endl << endl;
                        cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "      medium" << endl << endl;
                        cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "     -=HARD=-" << endl << endl;
                    }

                    cout << endl << "\t\t\t\t\t\t\t\t\t\t\t" << "       (";
                    if (sp == 0) cout << "3";
                    else if (sp == 1) cout << "5";
                    else cout << "8";
                    cout << " steps per second)" << endl << endl;

                    mm = _getch();
                    system("cls");
                    PlaySound(TEXT("STEP.wav"), NULL, SND_ASYNC);

                    if ((mm == 's' or mm == 'S') and sp != 2) sp++;
                    if ((mm == 'w' or mm == 'W') and sp != 0) sp--;

                    if (mm == 13 and sp == 0)
                    {
                        spd = 333;
                        speed = 0;
                    }
                    if (mm == 13 and sp == 1)
                    {
                        spd = 200;
                        speed = 0;
                    }
                    if (mm == 13 and sp == 2)
                    {
                        spd = 125;
                        speed = 0;
                    }
                }
                PlaySound(TEXT("SWTCH.wav"), NULL, SND_ASYNC);
            }

            if (mm == 13 and m == 3)
            {
                PlaySound(TEXT("SWTCH.wav"), NULL, SND_ASYNC);
                cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
                cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "    W - up" << endl << endl;
                cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "    A - left" << endl << endl;
                cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "    S - down" << endl << endl;
                cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "    D - right" << endl << endl;
                cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "    Enter - OK" << endl << endl;

                while (1)
                {
                    mm = _getch();
                    if (mm == 13 or mm == 27)
                    {
                       
                        mm = 13;
                        break;
                    }
                }
                PlaySound(TEXT("SWTCH.wav"), NULL, SND_ASYNC);
                system("cls");
            }

            if ((mm == 13 and m == 4) or mm == 27)
            {
                PlaySound(TEXT("SWTCH.wav"), NULL, SND_ASYNC);
                while (exit)
                {
                    cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
                    cout << "\t\t\t\t\t\t\t\t\t\t\t" << "-=:ARE YOU SURE YOU WANT TO EXIT?:=-" << endl << endl << endl;
                    if (e == 1)
                    {
                        cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "       yeah" << endl << endl;
                        cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "      -=NO=-" << endl << endl;
                    }
                    if (e == 0)
                    {
                        cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "     -=YEAH=-" << endl << endl;
                        cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "        no" << endl << endl;
                    }

                    mm = _getch();
                    system("cls");
                    PlaySound(TEXT("STEP.wav"), NULL, SND_ASYNC);

                    if ((mm == 's' or mm == 'S') and e != 1) e++;
                    if ((mm == 'w' or mm == 'W') and e != 0) e--;
                    if (mm == 13 and e == 1)
                    {
                        PlaySound(TEXT("SWTCH.wav"), NULL, SND_ASYNC);
                        exit = 0;
                    }
                    if (mm == 13 and e == 0)
                    {
                        cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
                        cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "   -=:GOOD BYE:=-" << endl << endl << endl;
                        cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
                        return 0;
                    }
                }
            }
        }
        m = 0;

        field = new int* [ver_lim];                                                             //Формирование массива клеток поля
        for (ver = 0; ver < ver_lim; ++ver)
            field[ver] = new int[hor_lim];
        for (ver = 1; ver < ver_lim; ver++)                                                     //Заполенение всех клеток как "пустые"
            for (hor = 1; hor < hor_lim; hor++)
                field[ver][hor] = 0;

        ver_mem = hor_mem = (ver_lim + 1) / 2.;                                                 //Установка "головы" на центр поля
        field[ver_mem][hor_mem] = 1;

        Tail* sn = new Tail;                                                                    //Запись "головы" в очередь
        sn->vr = ver_mem; sn->hr = hor_mem;
        sn->next = sn->prev = NULL;
        head = tail = sn;

        treat = 0;
        len = 1;
        len_lim = 4;

        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);

        for (int i = 0; i < 24 - ver_lim / 2; i++) cout << endl;                                //Вывод игрового поля на экран
        if (ver_lim == 10)
            for (int i = 0; i < 12; i++) cout << '\t';
        if (ver_lim == 14)
        {
            for (int i = 0; i < 11; i++) cout << '\t';
            cout << "    ";
        }
        if (ver_lim == 20)
        {
            for (int i = 0; i < 10; i++) cout << '\t';
            cout << "      ";
        }
        for (int i = 0; i < ver_lim - 1; i++) cout << " _";
        cout << endl;
        for (ver = 1; ver < ver_lim; ver++)                                               
        {
            if (ver_lim == 10)
                for (int i = 0; i < 12; i++) cout << '\t';
            if (ver_lim == 14)
            {
                for (int i = 0; i < 11; i++) cout << '\t';
                cout << "    ";
            }
            if (ver_lim == 20)
            {
                for (int i = 0; i < 10; i++) cout << '\t';
                cout << "      ";
            }
            cout << "|";
            for (hor = 1; hor < hor_lim; hor++)
            {
                if (field[ver][hor] == 0)
                    cout << "_|";
                else
                {
                    SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
                    cout << "O";
                    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
                    cout << "|";
                }
            }
            cout << endl;
        }

        cout << endl << "\t\t\t\t\t\t\t\t\t\t\t\t";                                             //Вывод длины хвоста, настроек
        cout << "  -= ";
        SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
        cout << "SCORE - " << len;                                                     
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
        cout << " = -" << endl << endl;                                                     
        cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "      "; Settings(f, sp); cout << endl;
        cout << endl << "\t\t\t\t\t\t\t\t\t\t";
        cout << "      Press ESC if you want to return to menu" << endl;

        while (1)                                                    //Ввод направления движения с клавиатуры
        {
            s[0] = _getch();

            if (s[0] == 's')                                         //Движение вниз
            {
                down = 1;
                up = left = right = 0;
                break;
            }
            else if (s[0] == 'w')                                    //Движение вверх
            {
                up = 1;
                down = left = right = 0;
                break;
            }
            else if (s[0] == 'a')                                    //Движение влево
            {
                left = 1;
                up = down = right = 0;
                break;
            }
            else if (s[0] == 'd')                                     //Движение вправо
            {
                right = 1;
                up = down = left = 0;
                break;
            }
            else if (s[0] == 27)                                      //Выход в меню
            {
                menu = 1;
                system("cls");
                break;
            }
            else continue;
        }

        if (s[0] != 27)
        {
            while (1)
            {
                system("cls");                                                         //Очищение поля

                ver = ver_mem; hor = hor_mem;
                if (up == 1) ver--;
                if (down == 1) ver++;
                if (left == 1) hor--;
                if (right == 1) hor++;

                if (ver == ver_lim or ver == 0 or hor == hor_lim or hor == 0)          //Условие поражения
                {
                    loss = 1;
                    break;
                }

                ver_mem = ver; hor_mem = hor;                                          //Переменные памяти

                if (len < len_lim + 1)                                                 //Передвижение змеи (Если длина змеи меньше предельной)
                {
                    head = Movement(head, ver, hor, &len);
                    len++;
                }

                if (field[ver][hor] == 1)
                {
                    loss = 1;
                    break;                                                             
                } 
                else if (field[ver][hor] == 2)
                {
                    PlaySound(TEXT("SCORE.wav"), NULL, SND_ASYNC);
                    field[ver][hor] = 1;
                    len_lim++;
                    treat = 0;
                }
                else field[ver][hor] = 1;                                              //Заполнение клетки

                if (ver_lim == 10)
                    if (len == 75)
                    {
                        win = 1; loss = 0;
                        break;
                    }
                if (ver_lim == 14)
                    if (len == 150)
                    {
                        win = 1; loss = 0;
                        break;
                    }
                if (ver_lim == 20)
                    if (len == 300)
                    {
                        win = 1; loss = 0;
                        break;
                    }

                while (treat == 0)                                                 //Появление "еды" в случайной клетке поля
                {
                    ver_treat = rand() % (ver_lim - 1) + 1;
                    hor_treat = rand() % (ver_lim - 1) + 1;
                    if (field[ver_treat][hor_treat] == 1)                          //Если клетка занята хвостом змеи - continue
                        continue;
                    else field[ver_treat][hor_treat] = 2;                          //Иначе "еда" помещается в клетку
                    treat = 1;
                }

                if (len == len_lim)                                                  //Передвижение хвоста (Если длина достигла предельной)
                {
                    tail = Delete(tail, &ver, &hor);
                    field[ver][hor] = 0;
                    len--;
                }

                for (int i = 0; i < 24 - ver_lim / 2; i++) cout << endl;             //Вывод текущей ситуации на игровом поле
                if (ver_lim == 10)
                    for (int i = 0; i < 12; i++) cout << '\t';
                if (ver_lim == 14)
                {
                    for (int i = 0; i < 11; i++) cout << '\t';
                    cout << "    ";
                }
                if (ver_lim == 20)
                {
                    for (int i = 0; i < 10; i++) cout << '\t';
                    cout << "      ";
                }
                for (int i = 0; i < ver_lim - 1; i++) cout << " _";
                cout << endl;
                for (ver = 1; ver < ver_lim; ver++)                                  
                {
                    if (ver_lim == 10)
                        for (int i = 0; i < 12; i++) cout << '\t';
                    if (ver_lim == 14)
                    {
                        for (int i = 0; i < 11; i++) cout << '\t';
                        cout << "    ";
                    }
                    if (ver_lim == 20)
                    {
                        for (int i = 0; i < 10; i++) cout << '\t';
                        cout << "      ";
                    }
                    cout << "|";
                    for (hor = 1; hor < hor_lim; hor++)
                    {
                        if (field[ver][hor] == 0)
                            cout << "_|";
                        else if (field[ver][hor] == 1)
                        {
                            SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
                            cout << "O";
                            SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
                            cout << "|";
                        }
                        else if (field[ver][hor] == 2)
                        {
                            SetConsoleTextAttribute(handle, FOREGROUND_RED);
                            cout << "*";
                            SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
                            cout << "|";
                        }
                    }
                    cout << endl;
                }

                cout << endl << "\t\t\t\t\t\t\t\t\t\t\t\t";                                             //Вывод длины хвоста, настроек
                cout << "  -= ";
                SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
                cout << "SCORE - " << len;                                                
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
                cout << " = -" << endl << endl;
                cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << "      "; Settings(f, sp); cout << endl;
                cout << endl << "\t\t\t\t\t\t\t\t\t\t";
                cout << "      Press ESC if you want to return to menu" << endl;

                Sleep(spd);

                if (_kbhit())
                {
                    s[0] = _getch();                                                           //Ввод направления движения с клавиатуры

                    if (s[0] == 's' and up != 1)                                               //Движение вниз
                    {
                        down = 1;
                        up = left = right = 0;
                    }
                    else if (s[0] == 'w' and down != 1)                                        //Движение вверх
                    {
                        up = 1;
                        down = left = right = 0;
                    }
                    else if (s[0] == 'a' and right != 1)                                       //Движение влево
                    {
                        left = 1;
                        up = down = right = 0;
                    }
                    else if (s[0] == 'd' and left != 1)                                        //Движение вправо
                    {
                        right = 1;
                        up = down = left = 0;
                    }
                    else if (s[0] == 'L')                                                      //Комбинация клавиш для увеличения длины на 1
                    {
                        len_lim++;
                    }
                    else if (s[0] == 'B')                                                      //Комбинация клавиш для остановки игры
                    {
                        system("cls");
                        loss = 1;
                        break;
                    }
                    else if (s[0] == 27)                                                        //Вернуться в меню
                    {
                        system("cls");
                        loss = win = 0;
                        menu = 1;
                        break;
                    }
                    else continue;
                }
            }

            if (loss)
            {
                PlaySound(TEXT("LOSE1.wav"), NULL, SND_ASYNC);
                win = 0;
                cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
                SetConsoleTextAttribute(handle, FOREGROUND_RED);
                cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "   -=:GAME  OVER:=-" << endl << endl;
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
                cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << " Enter – back to menu" << endl << endl;
                cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
            }
            else if (win)
            {
                PlaySound(TEXT("WIN.wav"), NULL, SND_ASYNC);
                loss = 0;
                cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
                SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
                cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "   -=: YOU WON! :=-" << endl << endl;
                SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
                cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << " Enter – back to menu" << endl << endl;
                cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
            }
            if (loss or win) while (1)
            {
                mm = _getch();
                if (mm == 13)
                {
                    system("cls");
                    menu = 1;
                    break;
                }
                else if (mm == 27)
                {
                    system("cls");
                    cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
                    cout << "\t\t\t\t\t\t\t\t\t\t\t\t" << "   -=:GOOD BYE:=-" << endl << endl << endl;
                    cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
                    return 0;
                }
                else continue;
            }

            for (ver = 0; ver < ver_lim; ++ver)
                delete[]field[ver];
            delete[]field;
        }
    }
}
#include <iostream>
#include<fstream>
#include<cstring>
#include<windows.h>
#include<mmsystem.h>
#include <graphics.h>
#include <conio.h>
#include<stdio.h>
#include<time.h>
#pragma comment(lib,"winmm.lib")
using namespace std;
int mode = 0;
int x = 0, y = 0, gett, input;
int aa = 2, bb = 2;
char board[7][7],newboard[7][7];
int xx1, yy1, xx, yy;
int newx, newy, newxx, newyy;
string sname,readname;
void copyboard() {
    for (int i = 0; i <= 6; i++)
        for (int j = 0; j <= 6; j++)
            newboard[i][j] = board[i][j];
}
void initialize1() {
    aa = bb = 2;
    for (int i = 0; i < 7; i++) for (int j = 0; j < 7; j++) board[i][j] = '.';
    board[0][0] = board[6][6] = '@';
    board[6][0] = board[0][6] = '#';
}
void initialize2() {
    aa = bb = 2;
    for (int i = 0; i < 7; i++) for (int j = 0; j < 7; j++) board[i][j] = '.';
    board[0][0] = board[6][6] = '#';
    board[6][0] = board[0][6] = '@';
}
void initialize() {
    aa = bb = 2;
    for (int i = 0; i < 7; i++) for (int j = 0; j < 7; j++) board[i][j] = '.';
    board[0][0] = board[6][6] = '@';
    board[6][0] = board[0][6] = '#';
}
void save() {
    ofstream Outfile;
    Outfile.open(sname + ".txt");
    for (int i = 0; i <= 6; i++) {
        for (int j = 0; j <= 6; j++) {
            Outfile << board[i][j];
        }
        Outfile << endl;
    }
    Outfile.close();
}
int eval(int x0, int y0, char s0, char s1) {
    int ans=0;
    for (int i = x0 - 1; i <= x0 + 1; i++)
        for (int j = y0 - 1; j <= y0 + 1; j++)
            if (board[i][j] == s1)ans++;
    return ans;
}
int eval2(char s0, char s1) {
    int aaaa = 0, bbbb = 0;
    for (int i = 0; i < 7; i++) for (int j = 0; j < 7; j++) {
        if (newboard[i][j] == s0)aaaa++;
        if (newboard[i][j] == s1)bbbb++;
    }
    return aaaa - bbbb;
}
int check(int xx1, int yy1, int xx2, int yy2,char s) {
    int xxx = abs(xx1 - xx2), yyy = abs(yy1 - yy2);
    if (xx2 >= 0 && xx2 <= 6 && yy2 >= 0 && yy2 <= 6) {
        if (xxx > 2 || yyy > 2 || xxx + yyy == 0)return 0;
        if (board[xx1][yy1] == s && board[xx2][yy2] == '.') {
            if (xxx == 2 || yyy == 2)return 2;
            if (xxx == 1 || yyy == 1)return 1;
            return 0;
        }
    }
    return 0;
}
int newcheck(int xx1, int yy1, int xx2, int yy2, char s) {
    int xxx = abs(xx1 - xx2), yyy = abs(yy1 - yy2);
    if (xx2 >= 0 && xx2 <= 6 && yy2 >= 0 && yy2 <= 6) {
        if (xxx > 2 || yyy > 2 || xxx + yyy == 0)return 0;
        if (newboard[xx1][yy1] == s && newboard[xx2][yy2] == '.') {
            if (xxx == 2 || yyy == 2)return 2;
            if (xxx == 1 || yyy == 1)return 1;
            return 0;
        }
    }
    return 0;
}
int calc() {
    int a1 = 0, b1 = 0;
    if (aa == 0 || bb == 0)return 1;
    for (int i = 0; i <= 6; i++) 
        for (int j = 0; j <= 6; j++) 
            for (int ii = -2; ii <= 2; ii++) 
                for (int jj = -2; jj <= 2; jj++) {
                    if (check(i, j, i + ii, j + jj, '@') != 0) {
                        a1 = 1;
                        if(b1)return 0;
                    }
                    if (check(i, j, i + ii, j + jj, '#') != 0) {
                        b1 = 1;
                        if(a1)return 0;
                    }
                }
    return 1;
}
void tonghua(int x0, int y0, char s0,char s1) {
    for (int i = x0 - 1; i <= x0 + 1; i++) 
        for (int j = y0 - 1; j <= y0 + 1; j++) 
            if (i >= 0 && i <= 6 && j >= 0 && j <= 6) 
                if (board[i][j] == s1)board[i][j] = s0;
}
void newtonghua(int x0, int y0, char s0, char s1) {
    for (int i = x0 - 1; i <= x0 + 1; i++)
        for (int j = y0 - 1; j <= y0 + 1; j++)
            if (i >= 0 && i <= 6 && j >= 0 && j <= 6)
                if (newboard[i][j] == s1)newboard[i][j] = s0;
}
void move1(int xx1, int yy1, int xx2, int yy2) {
    board[xx2][yy2] = '@';
    tonghua(xx2, yy2, '@','#');
}
void move2(int xx1, int yy1, int xx2, int yy2) {
    board[xx1][yy1] = '.';
    board[xx2][yy2] = '@';
    tonghua(xx2, yy2, '@','#');
}
void aimove1(int xx1, int yy1, int xx2, int yy2) {
    board[xx2][yy2] = '#';
    tonghua(xx2, yy2, '#', '@');
}
void aimove2(int xx1, int yy1, int xx2, int yy2) {
    board[xx1][yy1] = '.';
    board[xx2][yy2] = '#';
    tonghua(xx2, yy2, '#', '@');
}
void newmove1(int xx1, int yy1, int xx2, int yy2) {
    newboard[xx2][yy2] = '@';
    newtonghua(xx2, yy2, '@', '#');
}
void newmove2(int xx1, int yy1, int xx2, int yy2) {
    newboard[xx1][yy1] = '.';
    newboard[xx2][yy2] = '@';
    newtonghua(xx2, yy2, '@', '#');
}
void newaimove1(int xx1, int yy1, int xx2, int yy2) {
    newboard[xx2][yy2] = '#';
    newtonghua(xx2, yy2, '#', '@');
}
void newaimove2(int xx1, int yy1, int xx2, int yy2) {
    newboard[xx1][yy1] = '.';
    newboard[xx2][yy2] = '#';
    newtonghua(xx2, yy2, '#', '@');
}
void moni() {
    int max1 = -2, flag = 0;
    for (int i = 0; i <= 6; i++) {
        for (int j = 0; j <= 6; j++) {
            if (newboard[i][j] == '@') {
                for (int ii = -2; ii <= 2; ii++) {
                    for (int jj = -2; jj <= 2; jj++) {
                        if (ii == 0 && jj == 0)continue;
                        else switch (newcheck(i, j, i + ii, j + jj, '@')) {
                        case 1: {
                            if (max1 <= eval(i + ii, j + jj, '@', '#') * 100) {
                                max1 = eval(i + ii, j + jj, '@', '#') * 100;
                                newx = i;
                                newy = j;
                                newxx = i + ii;
                                newyy = j + jj;
                                flag = 1;
                            }
                            break;
                        }
                        case 2: {
                            if (max1 < eval(i + ii, j + jj, '@', '#')) {
                                max1 = eval(i + ii, j + jj, '@', '#');
                                newx = i;
                                newy = j;
                                newxx = i + ii;
                                newyy = j + jj;
                                flag = 2;
                            }
                            break;
                        }
                        }
                    }
                }
            }
        }
    }
    if (flag == 0)return;
    if (flag == 1) {
        newmove1(newx, newy, newxx, newyy);
    }
    if (flag == 2) {
        newmove1(newx, newy, newxx, newyy);
    }
}
void newai() {
    int max1 = -100, max2 = -100, flag = 0;
    for (int i = 0; i <= 6; i++) {
        for (int j = 0; j <= 6; j++) {
            if (board[i][j] == '#') {
                copyboard();
                for (int ii = -2; ii <= 2; ii++) {
                    for (int jj = -2; jj <= 2; jj++) {
                        copyboard();
                        if (ii == 0 && jj == 0)continue;
                        else switch (newcheck(i, j, i + ii, j + jj, '#')) {
                        case 1: {
                            copyboard();
                            newaimove1(i, j, i + ii, j + jj);
                            moni();
                            if (max1 < eval2('#', '@') * 100 + 10000) {
                                max1 = eval2('#', '@') * 100 + 10000;
                                xx1 = i;
                                yy1 = j;
                                xx = i + ii;
                                yy = j + jj;
                                flag = 1;
                            }
                            break;
                        }
                        case 2: {
                            copyboard();
                            newaimove2(i, j, i + ii, j + jj);
                            moni();
                            if (max2 < eval(i + ii, j + jj, '#', '@') * 100 && max1 < 0) {
                                max2 = eval(i + ii, j + jj, '#', '@') * 100;
                                xx1 = i;
                                yy1 = j;
                                xx = i + ii;
                                yy = j + jj;
                                flag = 2;
                            }
                            break;
                        }
                        }
                    }
                }
            }
        }
    }
    if (flag == 0)return;
    if (flag == 1) {
        aimove1(xx1, yy1, xx, yy);
    }
    if (flag == 2) {
        aimove2(xx1, yy1, xx, yy);
    }
}
void ai() {
    int max = -2, x1,y1,xx, yy, flag = 0;
    for (int i = 0; i <= 6; i++) {
        for (int j = 0; j <= 6; j++) {
            if (board[i][j] == '#') {
                for (int ii = -2; ii <= 2; ii++) {
                    for (int jj = -2; jj <= 2; jj++) {
                        if (ii == 0 && jj == 0)continue;
                        else switch (check(i,j, i+ii, j+jj,'#')) {
                        case 1: {
                            if (max <= eval(i + ii, j + jj, '#', '@')) {
                                max = eval(i + ii, j + jj, '#', '@');
                                x1 = i;
                                y1 = j;
                                xx = i + ii;
                                yy = j + jj;
                                flag = 1;
                            }
                            break;
                        }
                        case 2: {
                            if (max < eval(i + ii, j + jj, '#', '@')) {
                                max = eval(i + ii, j + jj, '#', '@');
                                x1 = i;
                                y1 = j;
                                xx = i + ii;
                                yy = j + jj;
                                flag = 2;
                            }
                            break;
                        }
                        }
                    }
                }
            }
        }
    }
    if (flag == 0)return;
    if (flag == 1)aimove1(x1, y1, xx, yy);
    if (flag == 2)aimove2(x1, y1, xx, yy);
}
void printmenu() {
    initgraph(600, 700);
    setbkcolor(BLACK);
    cleardevice();
    char str[] = { "同化棋！！！" };
    srand((unsigned int)time(NULL));
    int x = 200;
    while (x <= 9000) {
        settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
        settextstyle(x / 100, 0, "楷体");
        outtextxy(10, 10, str);
        x++;
    }
    rectangle(50, 150, 550, 650);
    setfillcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
    fillrectangle(50, 150, 550, 650);
    setfillcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
    settextstyle(25, 0, "宋体");
    outtextxy(60, 160, "规则:初始布置为双方各将两枚棋子放在最外");
    outtextxy(60, 185, "的对角格。玩家必须轮流移动一枚己子到一");
    outtextxy(60, 210, "个空棋位，该棋位可以是邻近8格（包括对角");
    outtextxy(60, 235, "相邻的格）之一，或相隔一格的次邻16格之");
    outtextxy(60, 260, "一。移动的新棋位，会使邻近的所有敌棋如");
    outtextxy(60, 285, "黑白棋一样变成己方。如果棋子移到的是邻");
    outtextxy(60, 310, "接八格，会有一颗新己棋出现在原先棋位。");
    outtextxy(60, 335, "无法行棋需弃权。当两方都无法行棋时，游");
    outtextxy(60, 360, "戏结束，以最多子者胜。");
    int grow[4][4] = { 10,0,0,0,0,10,0,0,0,0,10,0,0,0,0,10 };
    settextstyle(50 + grow[0][y], 0, "楷体");
    outtextxy(60, 400, "新  的  开  始");
    settextstyle(50 + grow[1][y], 0, "楷体");
    outtextxy(60, 460, "存  储  游  戏");
    settextstyle(50 + grow[2][y], 0, "楷体");
    outtextxy(60, 520, "读  取  游  戏");
    settextstyle(50 + grow[3][y], 0, "楷体");
    outtextxy(60, 580, "退  出  游  戏");
    line(0, 100, 600, 100);
    gett = _getch();
    if (gett == 224)gett = _getch();
    closegraph();
}
void win() {
    initgraph(600, 700);
    setbkcolor(BLACK);
    cleardevice();
    char str[] = { "你  赢  了" };
    int x = 500;
    while (x <= 50000) {
        settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
        settextstyle(x / 500, 0, "楷体");
        outtextxy(10, 10, str);
        x++;
    }
    closegraph();
    printmenu();
}
void lose() {
    initgraph(600, 700);
    setbkcolor(BLACK);
    cleardevice();
    char str[] = { "你  输  了" };
    int x = 500;
    while (x <= 50000) {
        settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
        settextstyle(x / 500, 0, "楷体");
        outtextxy(10, 10, str);
        x++;
    }
    closegraph();
    printmenu();
}
void printboard(char currentboard[7][7]) {
    initgraph(600, 700);
    setbkcolor(BLACK);
    cleardevice();
    settextstyle(40, 0, "楷体");
    outtextxy(10, 10, "开始对战");
    settextstyle(25, 0, "楷体");
    outtextxy(220, 10, "悔棋请按“Q”  落子请按空格");
    rectangle(50, 150, 550, 650);
    setfillcolor(GREEN);
    fillrectangle(50, 150, 550, 650);
    line(0, 100, 600, 100);  
    for (int i = 1; i <= 6; i++) {
        line(50, 500 * i / 7 + 150, 550, 500 * i / 7 + 150);
        line(500 * i / 7 + 50, 150, 500 * i / 7 + 50, 650);
    }
    aa = bb = 0;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (board[i][j] == '#') {
                bb++;
                setfillcolor(YELLOW);
                fillrectangle(50 + 500 * j / 7, 150 + 500 * i / 7, 50 + 500 * (j + 1) / 7, 150 + 500 * (i + 1) / 7);
            }
            if (board[i][j] == '@') {
                aa++;
                setfillcolor(RED);
                fillrectangle(50 + 500 * j / 7, 150 + 500 * i / 7, 50 + 500 * (j + 1) / 7, 150 + 500 * (i + 1) / 7);
            }
        }
    }
    char num1[10], num2[10];
    sprintf_s(num1, "%d", aa);
    sprintf_s(num2, "%d", bb);
    outtextxy(220, 50, "己方得分：");
    outtextxy(420, 50, "对方得分：");
    outtextxy(360, 50, num1);
    outtextxy(560, 50, num2);
    int end = calc();
    if (end == 1) {
        closegraph();
        if (aa > bb)win();
        else lose();
    }
    else {
        input = _getch();
        if (input == 'Q') {
            ifstream fileread(sname + ".txt");
            if (!fileread) cout << "发生错误！" << endl;
            else for (int i = 0; i <= 6; i++) fileread >> board[i];
            fileread.close();
        }
        else save();
        closegraph();
    }
}
void play() {
    int x1=0, y1=0, x2=0, y2=0;
    while (1) {
        printboard(board);       
        if (input == 27)break;
        else {
            if (input == 0x20) {
                system("color B4");
                int gg = 1;
                while(gg) {
                    if (gg == 2) {
                        cin.clear();
                        cin.ignore();
                    }
                    cout << "请操作：";
                    cin >> x1 >> y1 >> x2 >> y2;
                    switch (check(x1, y1, x2, y2, '@')) {
                    case 1:move1(x1, y1, x2, y2); gg = 0; break;
                    case 2:move2(x1, y1, x2, y2); gg = 0; break;
                    default: cout << "无效！" << endl; gg = 2; break;
                    }
                }
                if(mode==1)ai();
                if (mode == 2)newai();
                if (aa == 0) {
                    lose();
                    break;
                }
                if (bb == 0) {
                    win();
                    break;
                }
            }
        }
    }
}
void quit() {
    initgraph(600, 700);
    setbkcolor(BLACK);
    cleardevice();
    char str[] = { "欢迎下次再来" };
    int x = 500;
    while (x <= 50000) {
        settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
        settextstyle(x / 500, 0, "楷体");
        outtextxy(10, 10, str);
        x++;
    }
}
int main(){
    initialize();
    PlaySound(TEXT("laser.wav"), NULL, SND_FILENAME | SND_ASYNC);
    while (1) {
        printmenu();
        if (gett == 0x20) {
            if (y == 0) {
                mode = 0;
                cout << "请输入游戏难度：1、简单 2、普通：";
                while (1) {
                    cin >> mode;
                    if (mode == 1 || mode == 2)break;
                    cout << "输入非法，请重试：";
                    cin.clear();
                    cin.ignore();
                }
                cout << "请输入存档名：";
                cin >> sname;
                ofstream Outfile;
                Outfile.open(sname+".txt");
                Outfile.close();
                initialize();
                play();
            }
            else if (y == 1)save();
            else if (y == 2) {
                while (1) {
                    cleardevice();
                    mode = 0;
                    cout << "请重新输入游戏难度：1、简单 2、普通：";
                    while (1) {
                        cin >> mode;
                        if (mode == 1 || mode == 2)break;
                        cout << "输入非法，请重试：";
                        cin.clear();
                        cin.ignore();
                    }
                    cout << "请输入存档名：";
                    cin >> readname;
                    ifstream fileread(readname + ".txt");
                    if (!fileread) {
                        cout << "文件不存在，请重试。" << endl;
                        continue;
                    }
                    else {
                        sname = readname;
                        for (int i = 0; i <= 6; i++) fileread >> board[i];
                        break;
                    }
                    fileread.close();
                }
                play();
            }
            else if (y == 3) {
                quit();
                break;
            }
        }
        else if (gett == 0x48)y--;
        else if (gett == 0x50)y++;
        if (y < 0)y = 3;
        if (y > 3)y = 0;
    }
}
#include "TXLib.h"
#include <fstream>
using namespace std;
struct  Form
{
string question;
string answer1;
string answer2;
string answer3;
string answer4;
int right_answer;
string address;
};
bool click(int y)
{
 return(txMouseButtons() == 1 &&
        txMouseX() > 150 &&
        txMouseY() > y &&
        txMouseX() < 200 &&
        txMouseY() < y+50);
}
void DrawAnswer(int y, string answer, COLORREF color1, COLORREF color2)
{
  txSetFillColor(color1);
  Win32::RoundRect(txDC(), 150, y, 200, y+50, 30, 30);
  txSetFillColor(color2);
  txRectangle(250, y, 500, y+50);
  txDrawText(250, y, 500, y+50, answer.c_str());
}

string getPart(int *pos2, string str)
{
    int pos1 = *pos2 + 1;
    *pos2 = str.find(";", pos1);
    string part = str.substr(pos1, *pos2 - pos1);
    return part;
}

int main()
    {
txCreateWindow (1300, 700);
txTextCursor (false);

HDC menufon = txLoadImage ("Fons/Fon0.bmp");
HDC rezfon = txLoadImage ("Fons/Rezfon.bmp");

int n_queastion = 1;
int point = 0;

string PAGE = "������";

char s[100];
Form form0;
Form form [50];

string str;
int n = 0;
ifstream file("�������.txt");

    while(file.good())
        {
            getline(file, str);
            int pos2 = -1;
            form[n].question = getPart(&pos2, str);
            form[n].answer1 = getPart(&pos2, str);
            form[n].answer2 = getPart(&pos2, str);
            form[n].answer3 = getPart(&pos2, str);
            form[n].answer4 = getPart(&pos2, str);
            form[n].right_answer = atoi(getPart(&pos2, str).c_str());
            form[n].address = getPart(&pos2, str);
            n++;
        }
    file.close();
while(n_queastion <= n)
  {
    if(PAGE=="������")
    {
        txBegin();
        txBitBlt(txDC(), 0, 0, 1300, 700, menufon);
        txSetColor(TX_RED,3);
        txSetFillColor(TX_BLACK);
        //������ ��� ������
        txRectangle(550,100,750,150);
        txDrawText(550,100,750,150, "������");
        //������� �� ������ �����
        if(txMouseX() >= 550 && txMouseY()>=100 &&
           txMouseX() <= 750 && txMouseY()<=150 &&
            txMouseButtons() == 1)
        {
            PAGE="������";
        }
        txEnd();
    }
    if(PAGE=="������")
    {

    txBegin();
    txSetFillColor (TX_BLACK);
    txClear();

    txSetColor (TX_WHITE);
    txSetFillColor (TX_BLACK);
    form0=form[n_queastion - 1];

    txBitBlt(txDC(), 0, 0, 1300, 700, txLoadImage(form0.address.c_str()));
//��������� �������� ����� if
    txSelectFont("Arial", 30);
    txSetFillColor(TX_RED);
    txRectangle(50, 120, 1250, 180);
    txDrawText(50, 120, 1250, 180, form0.question.c_str() );
//��������� ������� ����� if
    DrawAnswer( 250, form0.answer1, TX_RED, TX_RED);
    DrawAnswer( 350, form0.answer2, TX_RED, TX_RED);
    DrawAnswer( 450, form0.answer3, TX_RED, TX_RED);
    DrawAnswer( 550, form0.answer4, TX_RED, TX_RED);

    sprintf(s, "������ � %d �� %d", n_queastion, n);
    txDrawText(550, 0, 750, 100,s);
  if(click(250))
    {
    n_queastion++;
      if(form0.right_answer == 1)
      {
        txSleep(50);
        point++;
      }
    }
  if(click(350))
    {
    n_queastion++;
        if(form0.right_answer == 2)
      {
        txSleep(50);
        point++;
      }
    }
  if(click(450))
    {
    n_queastion++;
        if(form0.right_answer == 3)
      {
        txSleep(50);
        point++;
      }
    }
  if(click(550))
    {
    n_queastion++;
        if(form0.right_answer == 4)
          {
            txSleep(50);
            point++;
          }
    }

        txSleep(100);
        txEnd();
    }
}
    txClear();
    txBitBlt(txDC(), 0, 0, 1300, 700, rezfon);
    sprintf(s, "��� ��������� - %d �� 10\n"
    "���� ��� ��������� ������ 5 �� � ��� ���� ������ ������, ���� ������ �� � ������ ������!", point);
    txSetColor(TX_WHITE);
    txSetFillColor(TX_BLACK);
    txRectangle(150,50,1150,250);
    txDrawText(0, 100, 1300, 300,s);

    return 0;
}

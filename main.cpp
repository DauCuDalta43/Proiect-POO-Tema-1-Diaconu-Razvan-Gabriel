#include "a.h"
#include <bits/stdc++.h>
using namespace std;

ifstream fin("data.txt");

void Init()
{
    string s;
    int x;
    for(int i=1;i<=20;i++)
    {
        getline(fin,s);
        CardName.push_back(s);
    }
    for(int i=1;i<=20;i++)
    {
        getline(fin,s);
        CardDesc.push_back(s);
    }
    for(int i=1;i<=20;i++)
    {
        fin>>x;
        CardCost.push_back(x);
    }
    for(int i=1;i<=5;i++)
    {
        getline(fin,s);
        EnemyName.push_back(s);
    }
    for(int i=1;i<=5;i++)
    {
        getline(fin,s);
        EnemyIntent.push_back(s);
    }
    for(int i=1;i<=5;i++)
    {
        fin>>x;
        EnemyBaseHealth.push_back(x);
    }
    for(int i=1;i<=5;i++)
    {
        fin>>x;
        EnemyBaseDmg.push_back(x);
    }


    for(int i=0;i<=19;i++)
    {
        cout<<i+1<<" "<<CardName[i]<<" "<<CardDesc[i]<<" "<<CardCost[i]<<"\n";
    }



    cout<<"\n\n";
}

void StartGame()
{
    char ch;
    for(int i=1;i<=100;i++)
        cout<<"\n";
    cout<<"Enter any key to start game\n";
    cin>>ch;
}

int main()
{
    srand(time(NULL));
    int stage=1;
    Init();
    StiuSaFacConstructorDeCopiere a(2,3);

    StiuSaFacConstructorDeCopiere b=StiuSaFacConstructorDeCopiere(a);

    Player p;
    StartGame();
    while(Combat(p,stage))
    {
        if(stage%3==0)
            Bonus(p);
        stage++;
    }

    return 0;
}

#ifndef A_H_INCLUDED
#define A_H_INCLUDED
#include <bits/stdc++.h>

using namespace std;

int myrandom (int i) { return std::rand()%i;}

class Player;
class Enemy;
class Hand;

int enemycount[6];
vector<string>CardName,CardDesc;
vector<int>CardCost;
vector<string>EnemyName,EnemyIntent;
vector<int>EnemyBaseHealth,EnemyBaseDmg;

class StiuSaFacConstructorDeCopiere
{
    ///imi pare rau dar am incercat sa fac constructor de copiere la clasa card
    /// si a inceput sa urle la mine functia care da shuffle
    private:
    int a,b;

    public:

    StiuSaFacConstructorDeCopiere(int x,int y):a(x),b(y){}

    StiuSaFacConstructorDeCopiere(const StiuSaFacConstructorDeCopiere& chiarstiu)
    {
        a=chiarstiu.a;
        b=chiarstiu.b;
        cout<<"nu vroiam sa fac asta dar nu vreau mai multe erori in cod ca am fortat asta";
    }

    void SetValue(int x,int y)
    {
        a=x;
        b=y;
    }
    void Afis()
    {
        cout<<a<<" "<<b<<"\n";
    }

    friend ostream & operator << (ostream &out, const StiuSaFacConstructorDeCopiere &t);

};

ostream & operator << (ostream &out, const StiuSaFacConstructorDeCopiere &t)
{
    cout<<t.a<<" "<<t.b;
}

class Card
{
    private:
    int id,cost;
    string name,desc;
    public:
    Card()
    {

    }

    Card(int x):id(x)
    {
        name=CardName[x];
        desc=CardDesc[x];
        cost=CardCost[x];
    }



    int get_Id()
    {
        return id;
    }

    int get_Cost()
    {
        return cost;
    }
    friend ostream & operator << (ostream &out, const Card &c);

};

ostream & operator << (ostream &out, const Card &c)
{
    cout<<c.name<<"("<<c.cost<<"):"<<c.desc<<"\n";
}

class classDeck
{
    private:
    vector<Card>deck;

    public:
    classDeck()
    {
        Card a(0);
        for(int i=1;i<=5;i++)
            deck.push_back(a);
        a=Card(1);
        for(int i=1;i<=5;i++)
            deck.push_back(a);
        deck.push_back(Card(2));
    }

    vector<Card> get_deck()
    {
        return deck;
    }

    AddDeck(Card c)
    {
        deck.push_back(c);
    }


};


class OffHand
{
    private:
    classDeck d;
    vector<Card>draw;
    vector<Card>discard;
    public:
    OffHand()
    {
        ///cout<<"c\n";
    }
    OffHand(classDeck x):d(x)
    {
        //cout<<"c\n";
        discard.clear();
        draw=d.get_deck();
        std::random_shuffle(draw.begin(),draw.end(),myrandom);
        ///cout<<draw.size()<<" "<<discard.size()<<"\n";
//        for(int i=0;i<draw.size();i++)
//            cout<<draw[i].id<<" ";
    }

    void Reshuffle()
    {
        std::random_shuffle(discard.begin(),discard.end());
        draw=discard;
        discard.clear();
        ///cout<<draw.size()<<" "<<discard.size()<<"\n";
    }

    Card Draw()
    {
        if(draw.empty())
            Reshuffle();
        Card a;
        a=draw.back();
        draw.pop_back();
        ////cout<<draw.size()<<" "<<discard.size()<<"\n";
        return a;
    }

    vector<Card> get_draw()
    {
        return draw;
    }

    vector<Card> get_discard()
    {
        return discard;
    }
    friend ostream & operator << (ostream &out, const OffHand &oh);

    void Discard(Card c)
    {
        discard.push_back(c);
    }

    void TempCard(Card c)
    {
        draw.push_back(c);
    }



};

ostream & operator << (ostream &out, const OffHand &oh)
{
    cout<<"Draw:"<<oh.draw.size()<<"   Discard:"<<oh.discard.size()<<"\n";
}

class Hand
{
    private:
    OffHand& deck;
    Player& p;
    Enemy& e;
    int Energy;
    vector<Card>hand;
    public:

    Hand(OffHand& x, Player& y, Enemy& z):deck(x),p(y),e(z)
    {
        ///cout<<this<<"\n";
        for(int i=1;i<=5;i++)
            hand.push_back(deck.Draw());
    }

    void Draw(int n)
    {
        for(int i=1;i<=n;i++)
            hand.push_back(deck.Draw());
    }

    void Endturn()
    {
        while(!hand.empty())
        {
            deck.Discard(hand.back());
            hand.pop_back();
        }
    }
    friend ostream & operator << (ostream &out, const Hand &h);

    Player& get_Player()
    {
        return p;
    }
    OffHand& get_OH()
    {
        return deck;
    }
    Enemy& get_Enemy()
    {
        return e;
    }
    void set_Energy(int x)
    {
        Energy+=x;
    }
    vector<Card> get_Hand()
    {
        return hand;
    }
    int get_Energy()
    {
        return Energy;
    }
    void DiscardN(int nr)
    {
        Card c=hand[nr];
        hand.erase(hand.begin()+nr);
        if(c.get_Id()!=19)deck.Discard(c);
    }
    void turnEnergy(int x)
    {
        Energy=x;
    }
    void AddtoHand(Card c)
    {
        hand.push_back(c);
    }

};

ostream & operator << (ostream &out, const Hand &h)
{
    cout<<"\nEnergy:"<<h.Energy<<"\n";;
    for(int i=1;i<=h.hand.size();i++)
        cout<<i<<": "<<h.hand[i-1];
    cout<<"e: End turn.\n";
}

void AfisReward(Card x, Card y, Card z)
{
    for(int i=1;i<=100;i++)
        cout<<"\n";
    cout<<"Choose card:\n";
    cout<<"1: "<<x;
    cout<<"2: "<<y;
    cout<<"3: "<<z;
    cout<<"s: Skip\n";
}

void AfisBonus()
{
    for(int i=1;i<=100;i++)
        cout<<"\n";
    cout<<"Choose reward:\n";
    cout<<"1: +1 Energy\n";
    cout<<"2: +2 Strenght\n";
    cout<<"3: +2 Dexterity\n";
}



void CardReward(classDeck& p)
{

    int x,y,z;
    x=rand()%8+2;
    y=rand()%17+2;
    z=rand()%14+2;
    Card xc(x);
    Card yc(y);
    Card zc(z);
    char ch;
    AfisReward(xc,yc,zc);
    while(cin>>ch)
    {
        AfisReward(xc,yc,zc);
        if((ch<'1'||ch>'3')&&ch!='s')continue;
        if(ch=='1')p.AddDeck(xc);
        else if(ch=='2')p.AddDeck(yc);
        else if(ch=='3')p.AddDeck(zc);
        return;
    }

}

class Player
{
    public:
    classDeck deck;
    OffHand oh;

    int Hp,Energy;
    int block;
    int weak,frail,vulnerable;
    int str,dex;
    int strBoost,dexBoost;

    Player()
    {
        Hp=50;
        Energy=3;
        block=str=dex=weak=frail=strBoost=dexBoost=0;
        deck=classDeck();
        oh=OffHand(deck);
        ///hand=Hand(oh);

    }

    void Debuff(int type)
    {
        switch(type)
        {
        case 0:
            vulnerable+=2;
            break;
        case 1:
            weak+=2;
            break;
        case 2:
            frail+=2;
        case 3:
            Card c(19);
            oh.TempCard(c);
        }
    }

    void TakeDamage(int dmg)
    {
        if(vulnerable)dmg*=1.5;
        if(dmg<block)block-=dmg;
        else
        {
            dmg-=block;
            block=0;
            Hp-=dmg;
        }
    }

    void Endturn()
    {
        block=0;
        if(weak)weak--;
        if(frail)frail--;
    }

    void EndCombat()
    {
        CardReward(deck);
        weak=frail=strBoost=dexBoost=block=0;
        Hp+=10;
        oh=OffHand(deck);
    }

};

void Bonus(Player& p)
{
    char ch;
    AfisBonus();
    while(cin>>ch)
    {
        AfisBonus();
        if(ch<'1'||ch>'3')continue;
        if(ch=='1')p.Energy++;
        else if(ch=='2')p.str+=2;
        else if(ch=='3')p.dex+=2;
        return;
    }
}

ostream & operator << (ostream &out, const Player &p)
{
    cout<<"Health:"<<p.Hp<<"   Block:"<<p.block<<"\n";
    if(p.dex+p.dexBoost)cout<<"Dexterity:"<<p.dex+p.dexBoost<<"  ";
    if(p.str+p.strBoost)cout<<"Strenght:"<<p.str+p.strBoost<<"  ";
    if(p.weak)cout<<"Weak:"<<p.weak<<"  ";
    if(p.frail)cout<<"Frail:"<<p.frail<<"  ";
    if(p.vulnerable)cout<<"Vulnerable:"<<p.vulnerable<<"  ";
    cout<<"\n\n";
    cout<<p.oh;
}

void EnemyAttack(Player& p, int dmg, int intent, int type)
{
    p.TakeDamage(dmg);
    if(!intent)p.Debuff(type);
    else p.TakeDamage(dmg);
}


class Enemy
{
    public:
    string name,special;
    int Hp,dmg;
    int weak, vulnerable;
    int poison;
    int str;
    int stage,intent,type;

    Enemy()
    {
        name="";
        Hp=dmg=weak=vulnerable=str=poison=0;
    }

    Enemy(int stage):stage(stage)
    {
        type=rand()%5;
        name=EnemyName[type];
        special=EnemyIntent[type];
        Hp=EnemyBaseHealth[type]*(1.0+0.05*(stage-1));
        dmg=EnemyBaseDmg[type]*(1.0+0.05*(stage-1));
        weak=vulnerable=poison=str=0;
    }
    void Intent()
    {
        intent=rand()%2;
        if(type==4)intent=1;
    }

    void Endturn(Player& p)
    {
        if(poison)
        {
            Hp-=poison;
            poison--;
        }
        int dmgVar=dmg+str/(1+intent);
        if(weak)dmgVar*=0.75;
        EnemyAttack(p,dmgVar,intent,type);
        if(type==4)str+=4;
        if(weak)weak--;
        if(vulnerable)vulnerable--;
    }

    ~Enemy()
    {
        enemycount[type]++;
    }

};

ostream & operator << (ostream &out, const Enemy &e)
{
    int dmgVar=e.dmg+e.str/(1+e.intent);
    if(e.weak)dmgVar*=0.75;
    cout<<e.name<<"\n";
    cout<<"Health:"<<e.Hp<<"\n";
    cout<<"Deals "<<dmgVar+dmgVar*e.intent<<" Damage. ";
    if(!e.intent)cout<<e.special;
    cout<<"\n";
    if(e.str)cout<<"Strenght:"<<e.str<<"   ";
    if(e.weak)cout<<"Weak:"<<e.weak<<"   ";
    if(e.vulnerable)cout<<"Vulnerable:"<<e.vulnerable<<"   ";
    if(e.poison)cout<<"Poison:"<<e.poison<<"   ";
    return out;
}

void Afisare(Player& p, Enemy& e, Hand& h)
{
    for(int i=1;i<=100;i++)
        cout<<"\n";
    cout<<e;
    cout<<"\n\n\n";
    cout<<p;
    cout<<h;

}
///Cards

int CalcDmg(Hand& h, int base, int mult=1)
{
    float dmg=base+(h.get_Player().str+h.get_Player().strBoost)*mult;
    if(h.get_Enemy().vulnerable)dmg*=1.5;
    if(h.get_Player().weak)dmg*=0.75;
    return (int)dmg;
}

int CalcBlock(Hand& h, int base)
{
    float block=base+h.get_Player().dex+h.get_Player().dexBoost;
    if(h.get_Player().frail)block*=0.75;
    return (int)block;
}

void Strike(Hand& h)
{
    h.get_Enemy().Hp-=CalcDmg(h,6);
}

void Defend(Hand& h)
{
    h.get_Player().block+=CalcBlock(h,5);
}

void Bash(Hand& h)
{
    h.get_Enemy().Hp-=CalcDmg(h,8);
    h.get_Enemy().vulnerable+=2;
}

void HeavyBlade(Hand& h)
{
    h.get_Enemy().Hp-=CalcDmg(h,14,3);
}

void PommelStrike(Hand& h)
{
    h.get_Enemy().Hp-=CalcDmg(h,8);
    h.Draw(1);

}

void ShruggOff(Hand& h)
{
    h.get_Player().block+=CalcBlock(h,8);
    h.Draw(1);
}

void IronWave(Hand& h)
{
    h.get_Player().block+=CalcBlock(h,5);
    h.get_Enemy().Hp-=CalcDmg(h,5);
}

void PowerThrough(Hand& h)
{
    h.get_Player().block+=CalcBlock(h,15);
    Card c(19);
    h.AddtoHand(c);
}

void SeeingRed(Hand& h)
{
    h.set_Energy(2);
}

void Neutralize(Hand& h)
{
    h.get_Enemy().Hp-=CalcDmg(h,3);
    h.get_Enemy().weak+=1;
}

void Deflect(Hand& h)
{
    h.get_Player().block+=CalcBlock(h,4);
}

void DeadlyPoison(Hand& h)
{
    h.get_Enemy().poison+=5;
}

void PoisonedStab(Hand& h)
{
    h.get_Enemy().poison+=3;
    h.get_Enemy().Hp-=CalcDmg(h,6);
}

void Catalyst(Hand& h)
{
    h.get_Enemy().poison*=2;
}

void Footwork(Hand& h)
{
    h.get_Player().dexBoost+=2;
}

void LegSweep(Hand& h)
{
    h.get_Enemy().weak+=2;
    h.get_Player().block+=CalcBlock(h,11);
}

void Adrenaline(Hand& h)
{
    h.set_Energy(1);
    h.Draw(2);
}

void Offering(Hand& h)
{
    h.set_Energy(2);
    h.Draw(3);
    h.get_Player().Hp-=3;
}

void LimitBreak(Hand& h)
{
    h.get_Player().strBoost+=h.get_Player().str+h.get_Player().strBoost;
}

void Reaper(Hand& h)
{
    h.get_Enemy().Hp-=CalcDmg(h,4);
    h.get_Player().Hp+=CalcDmg(h,4);
}


void PlayCard(Hand& h,int nr)
{
    if(nr>=h.get_Hand().size())
    {
        cout<<"Numar invalid\n";
        return;
    }
    Card c=h.get_Hand()[nr];
    if(h.get_Energy()<c.get_Cost())
    {
        cout<<"Not enough energy\n";
        return;
    }
    h.set_Energy(-c.get_Cost());
    h.DiscardN(nr);
    //n-am chef sa schimb 19 numere
    switch(c.get_Id()+1)
    {
    case 1:
        Strike(h);
        break;
    case 2:
        Defend(h);
        break;
    case 3:
        Bash(h);
        break;
    case 4:
        HeavyBlade(h);
        break;
    case 5:
        PommelStrike(h);
        break;
    case 6:
        ShruggOff(h);
        break;
    case 7:
        IronWave(h);
        break;
    case 8:
        PowerThrough(h);
        break;
    case 9:
        Neutralize(h);
        break;
    case 10:
        DeadlyPoison(h);
        break;
    case 11:
        Deflect(h);
        break;
    case 12:
        PoisonedStab(h);
        break;
    case 13:
        Catalyst(h);
        break;
    case 14:
        Footwork(h);
        break;
    case 15:
        LegSweep(h);
        break;
    case 16:
        Adrenaline(h);
        break;
    case 17:
        Offering(h);
        break;
    case 18:
        Reaper(h);
        break;
    }
}

void Turn(Player& p, Enemy& e)
{
    char ch;
    Hand h=Hand(p.oh,p,e);
    h.turnEnergy(p.Energy);
    e.Intent();
    Afisare(p,e,h);
    while(cin>>ch)
    {
        if(e.Hp<=0)return;

        if(ch=='e')
        {
            h.Endturn();
            e.Endturn(p);
            p.Endturn();
            return;
        }
        if(ch<='9'&&ch>='1')
        {
            //cout<<ch;
            PlayCard(h,int(ch-'1'));
        }
        if(e.Hp<=0)return;
        Afisare(p,e,h);
    }

}

void GameOver(int stage)
{
    for(int i=1;i<=100;i++)
        cout<<"\n";
    cout<<"Game Over. You reached stage "<<stage<<"!\n";
    cout<<"You defeated:\n";
    for(int i=0;i<=4;i++)
    {
        cout<<enemycount[i]<<" "<<EnemyName[i];
        if(enemycount[i]!=1)cout<<"s";
        cout<<"\n";
    }
}

int Combat(Player& p,int stage)
{
    Enemy e=Enemy(stage);
    while(p.Hp>0&&e.Hp>0)
        Turn(p,e);
    if(p.Hp>0)
    {
        p.EndCombat();
        return 1;
    }
    GameOver(stage);
    return 0;
}


#endif // A_H_INCLUDED

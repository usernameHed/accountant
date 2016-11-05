#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <stdio.h>
#include <string.h>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <math.h>
#include <cerrno>
#include <cfenv>
#include <cstring>

using namespace std;

//display list
template <class T>
inline void printList(const T& coll, const char* optcstr=" ")
{
    typename T::const_iterator pos;

    bool start = true;
    for (pos=coll.begin(); pos!=coll.end(); ++pos)
    {
        if (!start)
          std::cerr << optcstr;
        std::cerr << *pos;
        start = false;
    }
    std::cerr << std::endl;
}

/**
 * Shoot enemies before they collect all the incriminating data!
 * The closer you are to an enemy, the more damage you do but don't get too close or you'll get killed.
 **/
int main()
{
    #define PI 3.14159265
    class Enemy
    {
    public:
        int id;
        int x;
        int y;
        int life;
        float distToPlayer;
      Enemy(int idd, int xx, int yy, int lifee)
        : id(idd), x(xx), y(yy), life(lifee)
      {
          
      }
      ~Enemy()
      {
          
      }
      void aff()
      {
        cerr << "enemy[" << id << "]: pos{" << x << ":" << y << "} life: " << life << " | distToPlayer: " << distToPlayer << endl;   
      }
      void setDistToPlayer(int xme, int yme)
      {
          distToPlayer = sqrt(pow(x - xme, 2) + pow(y - yme, 2));
      }
    
      
    };
    class Data
    {
    public:
        int id;
        int x;
        int y;
        int closestEnnemyId;
        int closestEnnemyDist;
      Data(int idd, int xx, int yy)
        : id(x), x(xx), y(yy)
      {
          
      }
      ~Data()
      {
          
      }
    void aff()
      {
        cerr << "Data[" << id << "]: pos{" << x << ":" << y << "}, closest ennemy: " << closestEnnemyId << " (dist: " << closestEnnemyDist << ")" << endl;   
      }
      void setClosestEnnemy(vector<Enemy> &enemy)
      {
          int i = -1;
          int tmpId = 90000000;
          float tmpMaxDist = 9000000;
          while (++i < enemy.size())
          {
              float dist = sqrt(pow(enemy[i].x - x, 2) + pow(enemy[i].y - y, 2));
              if (dist < tmpMaxDist)
              {
                tmpMaxDist = dist;
                tmpId = enemy[i].id;
              }
          }
          closestEnnemyId = tmpId;
          closestEnnemyDist = tmpMaxDist;
      }
      
    };
    
    vector<Enemy> enemy;
    vector<Data> data;
    
    class Me
    {
    public:
        int x;
        int y;
        float Rdist = 2500;
        float Fdist = 7000;
      Me()
      {
          
      }
      ~Me()
      {
          
      }
      void aff()
      {
           cerr << "me, pos{" << x << ":" << y << "}" << endl;   
      }
      
      int getBestAngle(vector<Enemy> &Renemy)
      {
        int angle = 0;
        float xx = 0;
        float yy = 0;
        float nbEnemy = 0;
        int i = -1;
        while (++i < Renemy.size())
        {
            cerr << "enemy[" << Renemy[i].id << "] {" << Renemy[i].x << "," << Renemy[i].y << "}" << endl;
            xx += Renemy[i].x;
            yy += Renemy[i].y;
            nbEnemy += 1;
        }
        xx = xx / nbEnemy;
        yy = yy / nbEnemy;
        AdvanceByPix(xx, yy, -1);
        return (0);
        /*angle = atan2(y - yy, x - xx) * 180 / PI;
        if (angle < 0)
            angle += 360;
        //angle = (angle > 0 ? angle : (2*PI + angle)) * 360 / (2*PI);
        return (angle); */
      }
      
      void Advance(int dist, int angle)
      {
        cerr << "AVANCE !!!: " << angle << endl;
        int xvel = cos(angle * PI / 180) * dist;
        int yvel = 0 - sin(angle * PI / 180) * dist;
        cout << "MOVE " << (x + xvel) << " " << (y + yvel) << endl;
      }
      
      void AdvanceByPix(int xToGo, int yToGo, int dist)
      {
          int tmpX = abs(xToGo - x);
          int tmpY = abs(yToGo - y);
          if (xToGo < x)
            tmpX *= -1;
          if (yToGo < y)
            tmpY *= -1;      
        if (dist == -1)
        {
            tmpX *= -1;
            tmpY *= -1;
        }
          cout << "MOVE " << (x + tmpX) << " " << (y + tmpY) << endl;
      }
      
      void goToMiddleOfData(vector<Enemy> &enemy, int tmpDist)
      {
          cerr << "run to middle of ..." << endl;
          if (enemy.size() == 1)
          {
            //go to ennemy   
            cerr << "ennemy !" << endl;
            AdvanceByPix(enemy[0].x, enemy[0].y, enemy[0].distToPlayer);
            return;
          }
          
          int i = -1;
          int xtmpE = 0;
          int ytmpE = 0;
          int totE = 0;
          while (++i < enemy.size())
          {
               xtmpE += enemy[i].x;
               ytmpE += enemy[i].y;
               totE++;
          }
          xtmpE = xtmpE / totE;
          ytmpE = ytmpE / totE;
          AdvanceByPix(xtmpE, ytmpE, tmpDist);

          /*float convertRadiansToDegrees = 180.0 / 3.14159265359;
          float resultInDegrees = atan2(y - ytmp, x - xtmp) * convertRadiansToDegrees + 180.0; // 0 to 360
          

          int angle = resultInDegrees;
          
          //int angle = atan2(y - ytmp, x - xtmp) * 180 / PI;
          //angle = (angle + 720) % 360;
          //if (angle < 0)
            //angle += 360;
          cerr << "player {" << x << "," << y << "}" << endl;
          cerr << "middleDatas: {" << xtmp << "," << ytmp << "}, angle to go: " << angle << endl;
          Advance(tmpDist, angle);*/
      }
      
      void optiGoForData(vector<Data> &data, int tmpDist, int angle)
      {
          cerr << "opti angle..." << endl;
          //if data evant
          //goToMiddleOfData(data, dist);
          //else
          Advance(tmpDist, angle);
      }
      
      bool runForLife(vector<Enemy> &enemy, vector<Data> &data)
      {    
        vector <Enemy> Renemy;
        
        int i = -1;
        int tmpId = -1;
        int tmpDist = 9000000;
        while (++i < enemy.size()) //save all enemy in R zone
        {
            float dist = enemy[i].distToPlayer;
            if (dist < Rdist)
            {
                Renemy.push_back(enemy[i]);
                if (enemy[i].distToPlayer < tmpDist) //save the nearest enemy
                {
                    tmpId = enemy[i].id;
                    tmpDist = enemy[i].distToPlayer;
                }
            }
        }
        cerr << "tmpId: " << tmpId << ", tmpDist: " << tmpDist << endl;
        if (!Renemy.empty())
        {
            Renemy.clear();
            i = -1;
            while (++i < enemy.size()) //save all enemy in R zone
            {
                float dist = enemy[i].distToPlayer;
                if (dist < Rdist + (Rdist / 2))
                {
                    Renemy.push_back(enemy[i]);
                    if (enemy[i].distToPlayer < tmpDist) //save the nearest enemy
                    {
                        tmpId = enemy[i].id;
                        tmpDist = enemy[i].distToPlayer;
                    }
                }
            }
        
            
            
            cerr << "i have to run !" << endl;
            int angle = getBestAngle(Renemy);
            cerr << "here is the best angle to run: " << angle << endl;
            //optiGoForData(data, tmpDist, angle);
            //cout << "MOVE 8000 4500" << endl; // MOVE x y or SHOOT id            
            return (true);
        }
        return (false);
      }
      
      
      void findTheNearest(vector<Enemy> &enemy, vector<Data> &data)
      {
          int i = -1;
          int tmpId = -1;
          int tmpDist = 9000000;
          while (++i < enemy.size())
          {
               float dist = sqrt(pow(enemy[i].x - x, 2) + pow(enemy[i].y - y, 2));
               if (dist < tmpDist)
               {
                    tmpId = enemy[i].id;   
                    tmpDist = dist;
               }
          }
          //Fdist
          if (tmpDist < Fdist)
          {
            cerr << "enemy are near by, let's kill them !" << endl;
            cout << "SHOOT " << tmpId << endl;
          }
          else
          {
            cerr << "enemy are far away, let's advance to middle of data !" << endl;
            goToMiddleOfData(enemy, tmpDist);
          }
      }
      
      
    };


    
    Me me;
    
    int first = -1;
    
    while (1) {
        /*
        Enemy.clear();
        Data.clear();
        myPos.clear();*/
        
        data.clear();
        enemy.clear();
        
        int x;
        int y;
        cin >> x >> y; cin.ignore();
        me.x = x;
        me.y = y;
        /*myPos.push_back(x);
        myPos.push_back(y);
        cerr << "myPos: "; printList(myPos);*/
        int dataCount;
        cin >> dataCount; cin.ignore();
        for (int i = 0; i < dataCount; i++) {
            int dataId;
            int dataX;
            int dataY;
            cin >> dataId >> dataX >> dataY; cin.ignore();
            
            Data d(dataId, dataX, dataY);
            data.push_back(d);
  
        }
        int enemyCount;
        cin >> enemyCount; cin.ignore();
        for (int i = 0; i < enemyCount; i++) {
            int enemyId;
            int enemyX;
            int enemyY;
            int enemyLife;
            cin >> enemyId >> enemyX >> enemyY >> enemyLife; cin.ignore();
            
            Enemy e(enemyId, enemyX, enemyY, enemyLife);
            e.setDistToPlayer(me.x, me.y);
            enemy.push_back(e);
        }
        int m = -1;
        while (++m < data.size())
        {
            data[m].setClosestEnnemy(enemy);
        }
        me.aff();
        int i = -1;
        while (++i < enemy.size())
            enemy[i].aff();
        i = -1;
        while (++i < data.size())
            data[i].aff();
        

        if (!me.runForLife(enemy, data))
        {
            cerr << "I Don't have to run, do some stuff !" << endl;
            if (enemy.size() == 1)
                me.Fdist = 5000;
            me.findTheNearest(enemy, data);
            //cout << "SHOOT 0" << endl; // MOVE x y or SHOOT id            
                      
        }

        //cout << "SHOOT 0" << endl;
    }
}

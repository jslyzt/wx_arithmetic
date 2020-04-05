#pragma once
#include <vector>
#include <list>
#include <map>
using namespace std;

#include "arithmeticNode.h"

class arithmeticMgr
{
public:
    arithmeticMgr(void);
    ~arithmeticMgr(void);

    void init(int nMax);
    void refresh();
    void random();
    void setShowList(vector<int>& rList);
    void getShowList(vector<int>& rList);

    void start();
    bool getNext();
    void stop();

    int current();

    arithmeticData& getarithmeticData();
private:
    arithmeticData              m_rSortData;
    map<int, arithmeticNode*>   m_rFuncList;
    list<arithmeticNode*>       m_rShowList;
    int                         m_nMax;
    list<arithmeticNode*>::iterator m_iter;
};

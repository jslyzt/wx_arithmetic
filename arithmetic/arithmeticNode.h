#pragma once

#include <map>
#include <vector>
using namespace std;

enum EarithmeticFuncTp
{
    EarithmeticFunc_None = 0,       //≥ı º
    EarithmeticFunc_MaoPao,         //√∞≈›≈≈–Ú
    EarithmeticFunc_2Maopao,        //À´œÚ√∞≈›≈≈–Ú
    EarithmeticFunc_Insert,         //≤Â»Î≈≈–Ú
    EarithmeticFunc_Drum,           //Õ∞≈≈–Ú
    EarithmeticFunc_Tally,          //º∆ ˝≈≈–Ú
    EarithmeticFunc_Merger,         //πÈ≤¢≈≈–Ú
    EarithmeticFunc_MergerLo,       //‘≠µÿπÈ≤¢≈≈–Ú
    EarithmeticFunc_BaseM,          //ª˘ ˝≈≈–ÚMSD
    EarithmeticFunc_BaseL,          //ª˘ ˝≈≈–ÚLSD
    EarithmeticFunc_Choose,         //—°‘Ò≈≈–Ú
    EarithmeticFunc_Quick,          //øÏÀŸ≈≈–Ú
    EarithmeticFunc_Shell,          //œ£∂˚≈≈–Ú
    EarithmeticFunc_Heap,           //∂—≈≈–Ú
    EarithmeticFunc_BinaryTree,     //∂˛≤Ê ˜≈≈–Ú
    EarithmeticFunc_Gnome,          //Gnome≈≈–Ú
    EarithmeticFunc_Library,        //Library≈≈–Ú
    EarithmeticFunc_Comb,           //Comb≈≈–Ú
    EarithmeticFunc_Smooth,         //Smooth≈≈–Ú
    EarithmeticFunc_Intro,          //Intro≈≈–Ú
    EarithmeticFunc_Patience,       //Patience≈≈–Ú
};

////////////////////////////////////////////////////
class arithmeticData
{
public:
    arithmeticData();
    ~arithmeticData();
    void    rondom(int nSize, int nMax);
    int     getDataSize();
    int*    getSortData();
    void    reInit();
    vector<int>* getStepInfo();
    bool    toEnd();
    void    setBegin();
    int     getMaxStep() {return m_nMaxStep;}
    int     getStep();
    void    setMaxStep(int nStep) {m_nMaxStep = nStep;}
    void    saveStep(int nStep);
    void    saveStep(int nStep, int nPos, vector<int>& rList);
    vector<int>& getBaseData() {return m_Base;}

    void    exchange(int nStep, int posA, int posB);
    void    addValue(int nStep, int nPos, int nVaule);
    void    addValue(int nPos, vector<int>& rList);

    void    logOutData();
private:
    void    clear();
private:
    vector<int> m_Base;
    int*        m_pSort;
    map<int, vector<int> > m_rStepList;
    map<int, vector<int> >::iterator m_iter;
    int         m_nMaxStep;
};

class arithmeticNode
{
public:
    arithmeticNode(int nTp);
    ~arithmeticNode(void);
    virtual void sort(arithmeticData& rData);
    int getType() {return m_nType;}
protected:
    int m_nType;    //¿‡–Õ
};

////////////////////////////////////////////////////
//√∞≈›≈≈–Ú
class arithmeticMaoPao: public arithmeticNode
{
public:
    arithmeticMaoPao();
    ~arithmeticMaoPao();
    virtual void sort(arithmeticData& rData);
};

////////////////////////////////////////////////////
//À´œÚ√∞≈›≈≈–Ú
class arithmetic2MaoPao: public arithmeticNode
{
public:
    arithmetic2MaoPao();
    ~arithmetic2MaoPao();

    virtual void sort(arithmeticData& rData);
};

////////////////////////////////////////////////////
//≤Â»Î≈≈–Ú
class arithmeticInsert: public arithmeticNode
{
public:
    arithmeticInsert();
    ~arithmeticInsert();

    virtual void sort(arithmeticData& rData);
};

////////////////////////////////////////////////////
//Õ∞≈≈–Ú
class arithmeticDrum: public arithmeticNode
{
public:
    arithmeticDrum();
    ~arithmeticDrum();

    virtual void sort(arithmeticData& rData);
private:
    void sort(int& nStep, int nSize, vector<int>& rList, arithmeticData& rData);
};

////////////////////////////////////////////////////
//º∆ ˝≈≈–Ú
class arithmeticTally: public arithmeticNode
{
public:
    arithmeticTally();
    ~arithmeticTally();

    virtual void sort(arithmeticData& rData);
};

////////////////////////////////////////////////////
//πÈ≤¢≈≈–Ú
class arithmeticMerger: public arithmeticNode
{
public:
    arithmeticMerger();
    ~arithmeticMerger();

    virtual void sort(arithmeticData& rData);
private:
    void mergearray(int* arr, int first, int mid, int last, vector<int>& rTmp, int& nStep, arithmeticData& rData);
    void mergesort(int* arr, int first, int last, vector<int>& rTmp, int& nStep, arithmeticData& rData);
};

////////////////////////////////////////////////////
//‘≠µÿπÈ≤¢≈≈–Ú
class arithmeticMergerLo: public arithmeticNode
{
public:
    arithmeticMergerLo();
    ~arithmeticMergerLo();

    virtual void sort(arithmeticData& rData);
private:
    void mergearray(int* arr, int first, int mid, int last, int& nStep, arithmeticData& rData);
    void mergesort(int* arr, int first, int last, int& nStep, arithmeticData& rData);
    void exchange(int* arr, int n, int i, int& nStep, arithmeticData& rData);
    void reverse(int* arr, int n, int& nStep, arithmeticData& rData);
};

////////////////////////////////////////////////////
//ª˘ ˝≈≈–ÚMSD
class arithmeticBaseM: public arithmeticNode
{
public:
    arithmeticBaseM();
    ~arithmeticBaseM();

    virtual void sort(arithmeticData& rData);
private:
    int getdigit(int x, int d);
    void msdradix_sort(int* arr, int begin, int end, int dight, int& nStep, arithmeticData& rData);
};

////////////////////////////////////////////////////
//ª˘ ˝≈≈–ÚLSD
class arithmeticBaseL: public arithmeticNode
{
public:
    arithmeticBaseL();
    ~arithmeticBaseL();

    virtual void sort(arithmeticData& rData);
private:
    int getdigit(int x, int d);
    void lsdradix_sort(int* arr, int begin, int end, int dight, int& nStep, arithmeticData& rData);
};

////////////////////////////////////////////////////
//—°‘Ò≈≈–Ú
class arithmeticChoose: public arithmeticNode
{
public:
    arithmeticChoose();
    ~arithmeticChoose();

    virtual void sort(arithmeticData& rData);
private:
    void dataSwap(int* data1, int* data2);
};

////////////////////////////////////////////////////
//øÏÀŸ≈≈–Ú
class arithmeticQuick: public arithmeticNode
{
public:
    arithmeticQuick();
    ~arithmeticQuick();

    virtual void sort(arithmeticData& rData);
private:
    void quickSort(int* arr, int low, int high, int& nStep, arithmeticData& rData);
};

////////////////////////////////////////////////////
//∂˛≤Ê ˜≈≈–Ú
class arithmeticBinaryTree: public arithmeticNode
{
public:
    arithmeticBinaryTree();
    ~arithmeticBinaryTree();

    virtual void sort(arithmeticData& rData);
};

////////////////////////////////////////////////////
//œ£∂˚≈≈–Ú
class arithmeticShell: public arithmeticNode
{
public:
    arithmeticShell();
    ~arithmeticShell();

    virtual void sort(arithmeticData& rData);
};

////////////////////////////////////////////////////
//∂—≈≈–Ú
class arithmeticHeap: public arithmeticNode
{
public:
    arithmeticHeap();
    ~arithmeticHeap();

    virtual void sort(arithmeticData& rData);
};

////////////////////////////////////////////////////
//Gnome≈≈–Ú
class arithmeticGnome: public arithmeticNode
{
public:
    arithmeticGnome();
    ~arithmeticGnome();

    virtual void sort(arithmeticData& rData);
};

////////////////////////////////////////////////////
//Library≈≈–Ú
class arithmeticLibrary: public arithmeticNode
{
public:
    arithmeticLibrary();
    ~arithmeticLibrary();

    virtual void sort(arithmeticData& rData);
};
////////////////////////////////////////////////////
//Comb≈≈–Ú
class arithmeticComb: public arithmeticNode
{
public:
    arithmeticComb();
    ~arithmeticComb();

    virtual void sort(arithmeticData& rData);
};

////////////////////////////////////////////////////
//Smooth≈≈–Ú
class arithmeticSmooth: public arithmeticNode
{
public:
    arithmeticSmooth();
    ~arithmeticSmooth();

    virtual void sort(arithmeticData& rData);
};

////////////////////////////////////////////////////
//Intro≈≈–Ú
class arithmeticIntro: public arithmeticNode
{
public:
    arithmeticIntro();
    ~arithmeticIntro();

    virtual void sort(arithmeticData& rData);
};

////////////////////////////////////////////////////
//Patience≈≈–Ú
class arithmeticPatience: public arithmeticNode
{
public:
    arithmeticPatience();
    ~arithmeticPatience();

    virtual void sort(arithmeticData& rData);
};

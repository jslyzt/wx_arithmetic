#pragma once

#include <map>
#include <vector>
using namespace std;

enum EarithmeticFuncTp
{
    EarithmeticFunc_None = 0,       //��ʼ
    EarithmeticFunc_MaoPao,         //ð������
    EarithmeticFunc_2Maopao,        //˫��ð������
    EarithmeticFunc_Insert,         //��������
    EarithmeticFunc_Drum,           //Ͱ����
    EarithmeticFunc_Tally,          //��������
    EarithmeticFunc_Merger,         //�鲢����
    EarithmeticFunc_MergerLo,       //ԭ�ع鲢����
    EarithmeticFunc_BaseM,          //��������MSD
    EarithmeticFunc_BaseL,          //��������LSD
    EarithmeticFunc_Choose,         //ѡ������
    EarithmeticFunc_Quick,          //��������
    EarithmeticFunc_Shell,          //ϣ������
    EarithmeticFunc_Heap,           //������
    EarithmeticFunc_BinaryTree,     //����������
    EarithmeticFunc_Gnome,          //Gnome����
    EarithmeticFunc_Library,        //Library����
    EarithmeticFunc_Comb,           //Comb����
    EarithmeticFunc_Smooth,         //Smooth����
    EarithmeticFunc_Intro,          //Intro����
    EarithmeticFunc_Patience,       //Patience����
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
    int m_nType;    //����
};

////////////////////////////////////////////////////
//ð������
class arithmeticMaoPao: public arithmeticNode
{
public:
    arithmeticMaoPao();
    ~arithmeticMaoPao();
    virtual void sort(arithmeticData& rData);
};

////////////////////////////////////////////////////
//˫��ð������
class arithmetic2MaoPao: public arithmeticNode
{
public:
    arithmetic2MaoPao();
    ~arithmetic2MaoPao();

    virtual void sort(arithmeticData& rData);
};

////////////////////////////////////////////////////
//��������
class arithmeticInsert: public arithmeticNode
{
public:
    arithmeticInsert();
    ~arithmeticInsert();

    virtual void sort(arithmeticData& rData);
};

////////////////////////////////////////////////////
//Ͱ����
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
//��������
class arithmeticTally: public arithmeticNode
{
public:
    arithmeticTally();
    ~arithmeticTally();

    virtual void sort(arithmeticData& rData);
};

////////////////////////////////////////////////////
//�鲢����
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
//ԭ�ع鲢����
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
//��������MSD
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
//��������LSD
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
//ѡ������
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
//��������
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
//����������
class arithmeticBinaryTree: public arithmeticNode
{
public:
    arithmeticBinaryTree();
    ~arithmeticBinaryTree();

    virtual void sort(arithmeticData& rData);
};

////////////////////////////////////////////////////
//ϣ������
class arithmeticShell: public arithmeticNode
{
public:
    arithmeticShell();
    ~arithmeticShell();

    virtual void sort(arithmeticData& rData);
};

////////////////////////////////////////////////////
//������
class arithmeticHeap: public arithmeticNode
{
public:
    arithmeticHeap();
    ~arithmeticHeap();

    virtual void sort(arithmeticData& rData);
};

////////////////////////////////////////////////////
//Gnome����
class arithmeticGnome: public arithmeticNode
{
public:
    arithmeticGnome();
    ~arithmeticGnome();

    virtual void sort(arithmeticData& rData);
};

////////////////////////////////////////////////////
//Library����
class arithmeticLibrary: public arithmeticNode
{
public:
    arithmeticLibrary();
    ~arithmeticLibrary();

    virtual void sort(arithmeticData& rData);
};
////////////////////////////////////////////////////
//Comb����
class arithmeticComb: public arithmeticNode
{
public:
    arithmeticComb();
    ~arithmeticComb();

    virtual void sort(arithmeticData& rData);
};

////////////////////////////////////////////////////
//Smooth����
class arithmeticSmooth: public arithmeticNode
{
public:
    arithmeticSmooth();
    ~arithmeticSmooth();

    virtual void sort(arithmeticData& rData);
};

////////////////////////////////////////////////////
//Intro����
class arithmeticIntro: public arithmeticNode
{
public:
    arithmeticIntro();
    ~arithmeticIntro();

    virtual void sort(arithmeticData& rData);
};

////////////////////////////////////////////////////
//Patience����
class arithmeticPatience: public arithmeticNode
{
public:
    arithmeticPatience();
    ~arithmeticPatience();

    virtual void sort(arithmeticData& rData);
};

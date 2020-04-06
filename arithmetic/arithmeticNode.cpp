#include "arithmeticNode.h"
#include <time.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

arithmeticData::arithmeticData()
{
    m_Base.clear();
    m_pSort = NULL;
    //����random
    srand((unsigned int)time(NULL));
}

arithmeticData::~arithmeticData()
{
    clear();
}

void	arithmeticData::rondom(int nSize, int nMax)
{
    if (nSize <= 0 || nMax <= 0)
    {
        return;
    }

    clear();
    for (int i = 0; i < nSize; i++)
    {
        int nValue = rand() % nMax;
        if (nValue == 0)
        {
            nValue = 1;
        }
        else if (nValue < 0)
        {
            nValue = abs(nValue);
        }
        m_Base.push_back(nValue);
    }
    reInit();
}

int arithmeticData::getDataSize()
{
    return (int)m_Base.size();
}

int* arithmeticData::getSortData()
{
    return m_pSort;
}

void arithmeticData::clear()
{
    if (m_pSort != NULL)
    {
        delete [] m_pSort;
        m_pSort = NULL;
    }
    m_Base.clear();
    m_rStepList.clear();
    m_iter = m_rStepList.end();
    m_nMaxStep = 0;
}

void arithmeticData::reInit()
{
    size_t nSize = m_Base.size();
    m_pSort = new int[nSize];
    for (size_t i = 0; i < nSize; i++)
    {
        m_pSort[i] = m_Base[i];
    }
    m_rStepList.clear();
    m_iter = m_rStepList.end();
    m_nMaxStep = 0;
}

vector<int>* arithmeticData::getStepInfo()
{
    if (m_iter == m_rStepList.end())
    {
        return NULL;
    }
    vector<int>* ptr = &m_iter->second;
    m_iter ++;
    return ptr;
}

int arithmeticData::getStep()
{
    if (m_iter == m_rStepList.end())
    {
        return 0;
    }
    return m_iter->first;
}

void arithmeticData::exchange(int nStep, int posA, int posB)
{
    auto nSize = (int)m_Base.size();
    if (posA < 0 || posA >= nSize || posB < 0 || posB >= nSize || m_pSort == NULL)
    {
        return;
    }

    int temp = 0;
    temp = m_pSort[posB];
    m_pSort[posB] = m_pSort[posA];
    m_pSort[posA] = temp;

    saveStep(nStep);
}

void arithmeticData::addValue(int nStep, int nPos, int nVaule)
{
    auto nSize = (int)m_Base.size();
    if (nPos < 0 || nPos >= nSize || m_pSort == NULL)
    {
        return;
    }
    m_pSort[nPos] = nVaule;
    saveStep(nStep);
}

void arithmeticData::saveStep(int nStep)
{
    vector<int>& rList = m_rStepList[nStep];
    rList.clear();

    for (int i = 0; i < m_Base.size(); i++)
    {
        rList.push_back(m_pSort[i]);
    }
}

void arithmeticData::saveStep(int nStep, int nPos, vector<int>& rList)
{
    vector<int>& rSetList = m_rStepList[nStep];
    rSetList.clear();
    for (int i = 0; i < m_Base.size(); i++)
    {
        int j = i - nPos;
        if (i < nPos || j >= rList.size())
        {
            rSetList.push_back(m_pSort[i]);
        }
        else
        {
            rSetList.push_back(rList[j]);
        }
    }
}

void arithmeticData::addValue(int nPos, vector<int>& rList)
{
    for (int i = nPos; i < m_Base.size(); i++)
    {
        int j = i - nPos;
        if (j >= 0 && j < rList.size())
        {
            m_pSort[i] = rList[j];
        }
        else
        {
            break;
        }
    }
}

bool arithmeticData::toEnd()
{
    return m_iter == m_rStepList.end();
}

void arithmeticData::setBegin()
{
    m_iter = m_rStepList.begin();
}

void arithmeticData::logOutData()
{
    ofstream ofile;
    ofile.open("out.txt", ios_base::out);

    ofile << "base:" << endl;
    for (size_t i = 0; i < m_Base.size(); i++)
    {
        ofile << m_Base[i] << ",";
    }
    ofile << endl << "arrList" << endl;
    for (map<int, vector<int> >::iterator iter = m_rStepList.begin(); iter != m_rStepList.end(); iter ++)
    {
        vector<int>& rList = iter->second;
        for (size_t i = 0; i < rList.size(); i++)
        {
            ofile << rList[i] << ",";
        }
        ofile << endl;
    }
}
////////////////////////////////////////////////////
arithmeticNode::arithmeticNode(int nTp)
{
    m_nType = nTp;
}

arithmeticNode::~arithmeticNode(void)
{
}

void arithmeticNode::sort(arithmeticData& rData)
{
}

////////////////////////////////////////////////////
//ð������
arithmeticMaoPao::arithmeticMaoPao(): arithmeticNode(EarithmeticFunc_MaoPao)
{
}

arithmeticMaoPao::~arithmeticMaoPao()
{

}

void arithmeticMaoPao::sort(arithmeticData& rData)
{
    int* pSort = rData.getSortData();
    int nSize = rData.getDataSize();
    int nStep = 0;

    for (int i = 0; i < nSize; i ++)
    {
        for (int j = 0; j < nSize - 1 - i; j ++)
        {
            if (pSort[j] > pSort[j + 1])
            {
                rData.exchange(nStep, j, j + 1);
            }
            nStep ++;
        }
    }
    rData.setMaxStep(nStep);
}

////////////////////////////////////////////////////
//˫��ð������
arithmetic2MaoPao::arithmetic2MaoPao(): arithmeticNode(EarithmeticFunc_2Maopao)
{
}
arithmetic2MaoPao::~arithmetic2MaoPao()
{

}

void arithmetic2MaoPao::sort(arithmeticData& rData)
{
    int* pSort = rData.getSortData();
    int nSize = rData.getDataSize();
    int nStep = 0;

    int j = 0;
    for (int i = 0; i < nSize; i ++)
    {
        for (j = 0; j < nSize - 1 - i; j ++)
        {
            if (pSort[j] > pSort[j + 1])
            {
                rData.exchange(nStep, j, j + 1);
            }
            nStep ++;
        }
        for (int k = j; k >= i; k --)
        {
            if (pSort[k] < pSort[k - 1])
            {
                rData.exchange(nStep, k - 1, k);
            }
            nStep ++;
        }
    }
    rData.setMaxStep(nStep);
}

////////////////////////////////////////////////////
//��������
arithmeticInsert::arithmeticInsert(): arithmeticNode(EarithmeticFunc_Insert)
{
}
arithmeticInsert::~arithmeticInsert()
{

}

void arithmeticInsert::sort(arithmeticData& rData)
{
    int* pSort = rData.getSortData();
    int nSize = rData.getDataSize();
    int nStep = 0;

    for (int i = 1; i < nSize; i ++)
    {
        int temp = pSort[i];
        int j = i;
        for (j = i; j > 0 && pSort[j - 1] > temp; j --)
        {
            rData.exchange(nStep, j, j - 1);
            nStep ++;
        }
        rData.addValue(nStep, j, temp);
        nStep ++;
    }
    rData.setMaxStep(nStep);
}
////////////////////////////////////////////////////
//Ͱ����
//ȷ��������Сֵ
//�����ݷ��飬���ն��Ƶ�˳������е������������
arithmeticDrum::arithmeticDrum(): arithmeticNode(EarithmeticFunc_Drum)
{
}
arithmeticDrum::~arithmeticDrum()
{

}

void arithmeticDrum::sort(arithmeticData& rData)
{
    int* pSort = rData.getSortData();
    int nSize = rData.getDataSize();
    int nStep = 0;

    int nMax = 0, nMin = 0x7FFFFFFF;
    for (int i = 0; i < nSize; i++)
    {
        if (nMin > pSort[i])
        {
            nMin = pSort[i];
        }
        if (nMax < pSort[i])
        {
            nMax = pSort[i];
        }
        nStep ++;
    }

    int nless = nMax - nMin;
    if (nless == 0)
    {
        return;
    }

    //�ݶ�Ͱ��Χ10��
    int nNum = (nless + 1) / 10 + 1;

    vector<vector<int> > rDrumList;
    rDrumList.resize(nNum);
    //װͰ
    for (int i = 0; i < nSize; i++)
    {
        int nValue = pSort[i];
        rDrumList[(nValue - nMin) / 10].push_back(nValue);
        nStep ++;
    }

    //��¼
    vector<int> rList;
    for (int i = 0; i < rDrumList.size(); i++)
    {
        vector<int>& rListData = rDrumList[i];
        for (int j = 0; j < rListData.size(); j++)
        {
            rList.push_back(rListData[j]);
        }
        rData.saveStep(nStep, 0, rList);
        nStep ++;
    }
    rData.addValue(0, rList);
    //ÿ��Ͱ����
    nSize = 0;
    for (int i = 0; i < rDrumList.size(); i++)
    {
        vector<int>& rNode = rDrumList[i];
        sort(nStep, nSize, rNode, rData);
        rData.addValue(nSize, rNode);
        nSize += (int)rNode.size();
    }
    rData.setMaxStep(nStep);
}

void arithmeticDrum::sort(int& nStep, int nSize, vector<int>& rList, arithmeticData& rData)
{
    for (int i = 1; i < rList.size(); i ++)
    {
        int temp = rList[i];
        int j = i;
        for (j = i; j > 0 && rList[j - 1] > temp; j --)
        {
            int nTmp = rList[j];
            rList[j] =  rList[j - 1];
            rList[j - 1] = nTmp;
            rData.saveStep(nStep, nSize, rList);
            nStep ++;
        }
        rList[j] = temp;
        rData.saveStep(nStep, nSize, rList);
        nStep ++;
    }
}

////////////////////////////////////////////////////
//��������
//ͳ��һ��������С��Ԫ��a�ĸ���n=>a����n+1��λ����
arithmeticTally::arithmeticTally(): arithmeticNode(EarithmeticFunc_Tally)
{
}
arithmeticTally::~arithmeticTally()
{

}

void arithmeticTally::sort(arithmeticData& rData)
{
    //���������Ҫʹ��2���ڴ濽��
    //���ʹ��map
    int* pSort = rData.getSortData();
    int nSize = rData.getDataSize();
    vector<int>& rBase = rData.getBaseData();
    int nStep = 0;

    map<int, int> rMarkMap;
    for (size_t i = 0; i < rBase.size(); i++)
    {
        rMarkMap[rBase[i]] += 1;
        nStep ++;
    }

    //��map����
    map<int, int> rMarkMap2;
    for (map<int, int>::iterator iter_f = rMarkMap.begin(); iter_f != rMarkMap.end(); iter_f ++)
    {
        int nNum = iter_f->second;
        for (map<int, int>::iterator iter_s = rMarkMap.begin(); iter_s != rMarkMap.end(); iter_s ++)
        {
            if (iter_s->first < iter_f->first)
            {
                nNum += iter_s->second;
            }
            nStep ++;
        }
        rMarkMap2[iter_f->first] = nNum;
    }

    rMarkMap = rMarkMap2;

    for (int i = nSize - 1; i >= 0; i--)
    {
        int nValue = rBase[i];
        int nPos = rMarkMap[nValue];
        pSort[nPos - 1] = nValue;
        rMarkMap[nValue]--;
        rData.saveStep(nStep);
        nStep ++;
    }
    rData.setMaxStep(nStep);
}

////////////////////////////////////////////////////
//�鲢����
//˼���Ǻϲ��������飬����Ϊ22�ϲ�������������������ϲ�
arithmeticMerger::arithmeticMerger(): arithmeticNode(EarithmeticFunc_Merger)
{
}
arithmeticMerger::~arithmeticMerger()
{

}

void arithmeticMerger::sort(arithmeticData& rData)
{
    int* pSort = rData.getSortData();
    int nSize = rData.getDataSize();
    int nStep = 0;

    vector<int> rTemp;
    rTemp.resize(nSize);
    mergesort(pSort, 0, nSize - 1, rTemp, nStep, rData);
    rData.setMaxStep(nStep);
}

void arithmeticMerger::mergearray(int* arr, int first, int mid, int last, vector<int>& rTmp, int& nStep, arithmeticData& rData)
{
    int i = first, j = mid + 1;
    int m = mid,   n = last;
    int k = 0;

    while (i <= m && j <= n)
    {
        if (arr[i] <= arr[j])
        {
            rTmp[k++] = arr[i++];
        }
        else
        {
            rTmp[k++] = arr[j++];
        }
        nStep ++;
    }

    while (i <= m)
    {
        rTmp[k++] = arr[i++];
        nStep ++;
    }

    while (j <= n)
    {
        rTmp[k++] = arr[j++];
        nStep ++;
    }

    for (i = 0; i < k; i++)
    {
        arr[first + i] = rTmp[i];
        rData.saveStep(nStep);
        nStep ++;
    }
}

void arithmeticMerger::mergesort(int* arr, int first, int last, vector<int>& rTmp, int& nStep, arithmeticData& rData)
{
    if (first < last)
    {
        int mid = (first + last) / 2;
        mergesort(arr, first, mid, rTmp, nStep, rData);			//�������
        mergesort(arr, mid + 1, last, rTmp, nStep, rData);		//�ұ�����
        mergearray(arr, first, mid, last, rTmp, nStep, rData);	//�ٽ������������кϲ�
    }
}
////////////////////////////////////////////////////
//ԭ�ع鲢����
//�鲢�������������Ҫʹ�ö�������
arithmeticMergerLo::arithmeticMergerLo(): arithmeticNode(EarithmeticFunc_MergerLo)
{
}
arithmeticMergerLo::~arithmeticMergerLo()
{

}

void arithmeticMergerLo::sort(arithmeticData& rData)
{
    int* pSort = rData.getSortData();
    int nSize = rData.getDataSize();
    int nStep = 0;

    mergesort(pSort, 0, nSize - 1, nStep, rData);
    rData.setMaxStep(nStep);
}


void arithmeticMergerLo::mergearray(int* arr, int first, int mid, int last, int& nStep, arithmeticData& rData)
{
    int i = first, j = mid, k = last;

    while (i < j && j <= k)
    {
        int step = 0;
        while (i < j && arr[i] <= arr[j])
        {
            ++i;
            nStep ++;
        }
        while (j <= k && arr[j] <= arr[i])
        {
            ++j;
            ++step;
            nStep ++;
        }
        exchange(arr + i, j - i, j - i - step, nStep, rData);
        i += step;
        nStep ++;
    }
}

void arithmeticMergerLo::mergesort(int* arr, int first, int last, int& nStep, arithmeticData& rData)
{
    if (first < last)
    {
        int mid = (first + last) / 2;
        mergesort(arr, first, mid, nStep, rData);       //�������
        mergesort(arr, mid + 1, last, nStep, rData);    //�ұ�����
        mergearray(arr, first, mid + 1, last, nStep, rData);    //�ٽ������������кϲ�
    }
}

void arithmeticMergerLo::exchange(int* arr, int n, int i, int& nStep, arithmeticData& rData)
{
    reverse(arr, i, nStep, rData);
    rData.saveStep(nStep);
    reverse(arr + i, n - i, nStep, rData);
    rData.saveStep(nStep);
    reverse(arr, n, nStep, rData);
    rData.saveStep(nStep);
}

void arithmeticMergerLo::reverse(int* arr, int n, int& nStep, arithmeticData& rData)
{
    int i = 0, j = n - 1;
    while (i < j)
    {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;

        i++;
        j--;
        nStep ++;
    }
}

////////////////////////////////////////////////////
//��������MSD
//���αȽϸ�λ���Ĵ�С
arithmeticBaseM::arithmeticBaseM(): arithmeticNode(EarithmeticFunc_BaseM)
{
}
arithmeticBaseM::~arithmeticBaseM()
{

}

void arithmeticBaseM::sort(arithmeticData& rData)
{
    int* pSort = rData.getSortData();
    int nSize = rData.getDataSize();
    int nStep = 0;

    msdradix_sort(pSort, 0, nSize - 1, 2, nStep, rData);    //�����趨���ֻ��99 2λ��
    rData.setMaxStep(nStep);
}

int arithmeticBaseM::getdigit(int x, int d)
{
    int a[] = {1, 1, 10, 100, 1000};    //��Ϊ���������������Ҳֻ����λ���������ڴ�ֻ��Ҫ��ʮλ������
    return ((x / a[d]) % 10);
}

void arithmeticBaseM::msdradix_sort(int* arr, int begin, int end, int dight, int& nStep, arithmeticData& rData)
{
    const int radix = 10;
    int count[radix], i, j;
    for (i = 0; i < radix; ++i)
    {
        count[i] = 0;
        nStep ++;
    }
    for (i = begin; i <= end; ++i)
    {
        count[getdigit(arr[i], dight)]++;
        nStep ++;
    }
    for (i = 1; i < radix; ++i)
    {
        count[i] = count[i] + count[i - 1];
        nStep ++;
    }

    int* bucket = new int[end - begin + 1];
    //����Ҫ��������ɨ�裬��֤�����ȶ���
    for (i = end; i >= begin; --i)
    {
        j = getdigit(arr[i], dight);   //λ��
        bucket[count[j] - 1] = arr[i]; //�ο�Ͱ����
        count[j] = count[j] - 1;
        nStep ++;
    }
    //�ռ�����
    for (i = begin, j = 0; i <= end; ++i, ++j)
    {
        arr[i] = bucket[j];
        rData.saveStep(nStep);
        nStep ++;
    }
    //�ͷſռ�
    delete[] bucket;

    //�Ը�Ͱ�����ݽ���������
    for (i = 0; i < radix; i++)
    {
        int p1 = begin + count[i];         //��i��Ͱ����߽�
        int p2 = end;
        if (i != radix - 1)				  //��i��Ͱ���ұ߽�
        {
            p2 = begin + count[i + 1] - 1;
        }
        if (p1 < p2 && dight > 1)
        {
            msdradix_sort(arr, p1, p2, dight - 1, nStep, rData); //�Ե�i��Ͱ�ݹ���ã����л���������λ�� 1
        }
        nStep ++;
    }
}

////////////////////////////////////////////////////
//��������LSD
//���αȽϸ�λ���Ĵ�С
arithmeticBaseL::arithmeticBaseL(): arithmeticNode(EarithmeticFunc_BaseL)
{
}
arithmeticBaseL::~arithmeticBaseL()
{

}

void arithmeticBaseL::sort(arithmeticData& rData)
{
    int* pSort = rData.getSortData();
    int nSize = rData.getDataSize();
    int nStep = 0;

    lsdradix_sort(pSort, 0, nSize - 1, 2, nStep, rData);    //�����趨���ֻ��99 2λ��
    rData.setMaxStep(nStep);
}

int arithmeticBaseL::getdigit(int x, int d)
{
    int a[] = {1, 1, 10, 100, 1000};    //��Ϊ���������������Ҳֻ����λ���������ڴ�ֻ��Ҫ��ʮλ������
    return ((x / a[d]) % 10);
}

void arithmeticBaseL::lsdradix_sort(int* arr, int begin, int end, int dight, int& nStep, arithmeticData& rData)
{
    const int radix = 10;
    int count[radix], i, j;
    int nsize = end - begin + 1;

    vector<int> bucket;
    bucket.resize(nsize);

    for (int k = 1; k <= dight; ++k)
    {
        j = 0;
        for (i = begin; i <= end; ++i)
        {
            bucket[j++] = arr[i];
        }

        for (i = 0; i < radix; i++)
        {
            count[i] = 0;
            nStep ++;
        }
        for (i = begin; i <= end; i++)
        {
            count[getdigit(arr[i], k)]++;
            nStep ++;
        }
        for (i = 1; i < radix; i++)
        {
            count[i] = count[i] + count[i - 1];
            nStep ++;
        }
        for (i = nsize - 1; i >= 0; --i)    //����Ҫ��������ɨ�裬��֤�����ȶ���
        {
            j = getdigit(bucket[i], k);
            arr[count[j] - 1] = bucket[i];
            count[j] = count[j] - 1;
            rData.saveStep(nStep);
            nStep ++;
        }
    }
}

////////////////////////////////////////////////////
//ѡ������
arithmeticChoose::arithmeticChoose(): arithmeticNode(EarithmeticFunc_Choose)
{
}
arithmeticChoose::~arithmeticChoose()
{

}

void arithmeticChoose::sort(arithmeticData& rData)
{
    int* pSort = rData.getSortData();
    int nSize = rData.getDataSize();
    int nStep = 0;

    for (int i = 0; i < nSize - 1; i++)
    {
        int index = i;
        for (int j = i + 1; j < nSize; j++)    //Ѱ����С����������
        {
            if (pSort[j] < pSort[index])
            {
                index = j;
            }
            nStep ++;
        }
        if (index != i)
        {
            dataSwap(&pSort[index], &pSort[i]);

            rData.saveStep(nStep);
        }
        nStep ++;
    }
    rData.setMaxStep(nStep);
}

void arithmeticChoose::dataSwap(int* data1, int* data2)
{
    int temp = *data1;
    *data1 = *data2;
    *data2 = temp;
}

////////////////////////////////////////////////////
//��������
arithmeticQuick::arithmeticQuick(): arithmeticNode(EarithmeticFunc_Quick)
{
}
arithmeticQuick::~arithmeticQuick()
{

}

void	arithmeticQuick::sort(arithmeticData& rData)
{
    int* pSort = rData.getSortData();
    int nSize = rData.getDataSize();
    int nStep = 0;

    quickSort(pSort, 0, nSize - 1, nStep, rData);
    rData.setMaxStep(nStep);
}

void arithmeticQuick::quickSort(int* arr, int low, int high, int& nStep, arithmeticData& rData)
{
    if (low >= high)
    {
        return;
    }
    int	first	=	low;
    int last	=	high;
    int key		=	arr[first]; //���ֱ�ĵ�һ����¼��Ϊ����
    while (first < last)
    {
        while (first < last && arr[last] >= key)
        {
            --last;
            nStep ++;
        }
        arr[first] = arr[last]; //���ȵ�һ��С���Ƶ��Ͷ�
        rData.saveStep(nStep);
        nStep ++;

        while (first < last && arr[first] <= key)
        {
            ++first;
            nStep ++;
        }
        arr[last] = arr[first]; //���ȵ�һ������Ƶ��߶�
        rData.saveStep(nStep);
        nStep ++;
    }
    arr[first] = key;   //�����¼��λ
    rData.saveStep(nStep);

    quickSort(arr, low, first - 1, nStep, rData);
    quickSort(arr, last + 1, high, nStep, rData);
}

////////////////////////////////////////////////////
//����������
arithmeticBinaryTree::arithmeticBinaryTree(): arithmeticNode(EarithmeticFunc_BinaryTree)
{
}
arithmeticBinaryTree::~arithmeticBinaryTree()
{

}

void arithmeticBinaryTree::sort(arithmeticData& rData)
{

}

////////////////////////////////////////////////////
//ϣ������
arithmeticShell::arithmeticShell(): arithmeticNode(EarithmeticFunc_Shell)
{
}
arithmeticShell::~arithmeticShell()
{

}

void arithmeticShell::sort(arithmeticData& rData)
{

}
////////////////////////////////////////////////////
//������
arithmeticHeap::arithmeticHeap(): arithmeticNode(EarithmeticFunc_Heap)
{
}
arithmeticHeap::~arithmeticHeap()
{

}

void arithmeticHeap::sort(arithmeticData& rData)
{

}

////////////////////////////////////////////////////
//Gnome����
arithmeticGnome::arithmeticGnome(): arithmeticNode(EarithmeticFunc_Gnome)
{
}
arithmeticGnome::~arithmeticGnome()
{

}

void arithmeticGnome::sort(arithmeticData& rData)
{

}

////////////////////////////////////////////////////
//Library����
arithmeticLibrary::arithmeticLibrary(): arithmeticNode(EarithmeticFunc_Library)
{
}
arithmeticLibrary::~arithmeticLibrary()
{

}

void arithmeticLibrary::sort(arithmeticData& rData)
{

}

////////////////////////////////////////////////////
//Comb����
arithmeticComb::arithmeticComb(): arithmeticNode(EarithmeticFunc_Comb)
{
}
arithmeticComb::~arithmeticComb()
{

}

void arithmeticComb::sort(arithmeticData& rData)
{

}
////////////////////////////////////////////////////
//Smooth����
arithmeticSmooth::arithmeticSmooth(): arithmeticNode(EarithmeticFunc_Smooth)
{
}
arithmeticSmooth::~arithmeticSmooth()
{

}

void arithmeticSmooth::sort(arithmeticData& rData)
{

}

////////////////////////////////////////////////////
//Intro����
arithmeticIntro::arithmeticIntro(): arithmeticNode(EarithmeticFunc_Intro)
{
}
arithmeticIntro::~arithmeticIntro()
{

}

void arithmeticIntro::sort(arithmeticData& rData)
{

}

////////////////////////////////////////////////////
//Patience����
arithmeticPatience::arithmeticPatience(): arithmeticNode(EarithmeticFunc_Patience)
{
}
arithmeticPatience::~arithmeticPatience()
{

}

void arithmeticPatience::sort(arithmeticData& rData)
{

}

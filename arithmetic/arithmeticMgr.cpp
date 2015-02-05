#include "arithmeticMgr.h"

arithmeticMgr::arithmeticMgr(void)
{
	m_rFuncList.clear();
	m_rShowList.clear();
	m_nMax = 0;
	m_iter = m_rShowList.end();
}

arithmeticMgr::~arithmeticMgr(void)
{
}


void	arithmeticMgr::init(int nMax)
{
	m_nMax = nMax;
	m_rSortData.rondom(rand()%10 + 20,nMax);

	arithmeticNode* pFunc = new arithmeticMaoPao();	m_rFuncList[pFunc->getType()] = pFunc;
	pFunc = new arithmetic2MaoPao();	m_rFuncList[pFunc->getType()] = pFunc;
	pFunc = new arithmeticInsert();	m_rFuncList[pFunc->getType()] = pFunc;
	pFunc = new arithmeticDrum();	m_rFuncList[pFunc->getType()] = pFunc;
	pFunc = new arithmeticTally();	m_rFuncList[pFunc->getType()] = pFunc;
	pFunc = new arithmeticMerger();	m_rFuncList[pFunc->getType()] = pFunc;
	pFunc = new arithmeticMergerLo();	m_rFuncList[pFunc->getType()] = pFunc;
	pFunc = new arithmeticBaseM();	m_rFuncList[pFunc->getType()] = pFunc;
	pFunc = new arithmeticBaseL();	m_rFuncList[pFunc->getType()] = pFunc;
	pFunc = new arithmeticChoose();	m_rFuncList[pFunc->getType()] = pFunc;
	pFunc = new arithmeticQuick();	m_rFuncList[pFunc->getType()] = pFunc;
	pFunc = new arithmeticShell();	m_rFuncList[pFunc->getType()] = pFunc;
	pFunc = new arithmeticHeap();	m_rFuncList[pFunc->getType()] = pFunc;
	pFunc = new arithmeticBinaryTree();	m_rFuncList[pFunc->getType()] = pFunc;
	pFunc = new arithmeticGnome();	m_rFuncList[pFunc->getType()] = pFunc;
	pFunc = new arithmeticLibrary();	m_rFuncList[pFunc->getType()] = pFunc;
	pFunc = new arithmeticComb();	m_rFuncList[pFunc->getType()] = pFunc;
	pFunc = new arithmeticSmooth();	m_rFuncList[pFunc->getType()] = pFunc;
	pFunc = new arithmeticIntro();	m_rFuncList[pFunc->getType()] = pFunc;
	pFunc = new arithmeticPatience();	m_rFuncList[pFunc->getType()] = pFunc;

	///*
	for(map<int,arithmeticNode*>::iterator iter = m_rFuncList.begin();iter != m_rFuncList.end();iter ++)
	{
		if(iter->first > EarithmeticFunc_Quick)
		{
			break;
		}
		m_rShowList.push_back(iter->second);
	}
	//*/	

	//m_rShowList.push_back(m_rFuncList[EarithmeticFunc_Quick]);
}

void	arithmeticMgr::refresh()
{
	stop();
	random();
	start();
}

void	arithmeticMgr::random()
{
	m_rSortData.rondom(rand()%10 + 20,m_nMax);
}

void	arithmeticMgr::setShowList(vector<int>& rList)
{
	stop();
	m_rShowList.clear();

	for(size_t i=0;i<rList.size();i++)
	{
		m_rShowList.push_back(m_rFuncList[rList[i]]);
	}
	start();
}

void	arithmeticMgr::getShowList(vector<int>& rList)
{
	rList.clear();
	if(m_rShowList.size() != NULL)
	{
		for(list<arithmeticNode*>::iterator iter = m_rShowList.begin();iter != m_rShowList.end();iter ++)
		{
			arithmeticNode* pNode = *iter;
			if(pNode != NULL)
			{
				rList.push_back(pNode->getType());
			}			
		}
	}
	else
	{
		for(map<int,arithmeticNode*>::iterator iter = m_rFuncList.begin();iter != m_rFuncList.end();iter ++)
		{
			rList.push_back(iter->first);
		}
	}
}

void	arithmeticMgr::start()
{
	m_iter = m_rShowList.begin();
	if(m_iter != m_rShowList.end())
	{
		m_rSortData.reInit();
		(*m_iter)->sort(m_rSortData);
		m_rSortData.setBegin();
	}
}

bool	arithmeticMgr::getNext()
{
	if(m_iter != m_rShowList.end())
	{
		m_iter ++;
		if(m_iter != m_rShowList.end())
		{
			m_rSortData.reInit();
			(*m_iter)->sort(m_rSortData);
			m_rSortData.setBegin();
			return true;
		}
	}
	return false;
}

void	arithmeticMgr::stop()
{
	m_iter = m_rShowList.end();
}

int		arithmeticMgr::current()
{
	if(m_iter != m_rShowList.end())
	{
		return (*m_iter)->getType();
	}
	return EarithmeticFunc_None;
}


arithmeticData&		arithmeticMgr::getarithmeticData()
{
	return m_rSortData;
}

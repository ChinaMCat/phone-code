/*************************************************
  Model:             �������
  Author:            ��ѵ��
  Date:              2011-11-15
  Descript:          �ṩһ���ɵȴ�����Ϣ����ʵ��,�����ϲ�Ӧ��
*************************************************/

#ifndef _WEEDONG_CORE_TASKLIST_H_
#define _WEEDONG_CORE_TASKLIST_H_

#include <queue>
#include "../os.h"

namespace wd
{

template<class TypeValue>
class CTaskList
{
public:
	CTaskList(void);
	~CTaskList(void);

    /*************************************************
      Description:    // Ͷ��һ�����񵽶���ǰ��
      Input:          //  v Ͷ�ݵ�����
      Output:         //
      Return:         //
      Others:         //
    *************************************************/
	void		PushFront(TypeValue& v);

    /*************************************************
      Description:    // Ͷ��һ�����񵽶��к���
      Input:          //  v Ͷ�ݵ�����
      Output:         //
      Return:         //
      Others:         //
    *************************************************/
	void		PushBack(TypeValue& v);

    /*************************************************
      Description:    // �Ӷ���ǰ��ȡ��һ������
      Input:          // v Ҫȡ�������� timeout �ȴ��ĺ�����
      Output:         //
      Return:         // ����0��ʾ�����һ������ ����-1��ʾû�л������
      Others:         //
    *************************************************/
	int			PopFront(TypeValue&v , uint32 timeout);

    /*************************************************
      Description:    // �Ӷ��к���ȡ��һ������
      Input:          // v Ҫȡ�������� timeout �ȴ��ĺ�����
      Output:         //
      Return:         // ����0��ʾ�����һ������ ����-1��ʾû�л������
      Others:         //
    *************************************************/
	int			PopBack(TypeValue&v , uint32 timeout);

    /*************************************************
      Description:    // �������У��ṩһ���ֹ��������еķ�ʽ
      Input:          //
      Output:         //
      Return:         //
      Others:         //
    *************************************************/
	void		Lock();

    /*************************************************
      Description:    // �������У��ṩһ���ֹ��������еķ�ʽ
      Input:          //
      Output:         //
      Return:         //
      Others:         //
    *************************************************/
	void		UnLock();

    /*************************************************
      Description:    // ��ö��������������
      Input:          //
      Output:         //
      Return:         //
      Others:         //
    *************************************************/
	int			Size();

    /*************************************************
      Description:    // ����������
      Input:          //
      Output:         //
      Return:         //
      Others:         //
    *************************************************/
	std::deque<TypeValue>&GetDeque(){ return m_deque;}
protected:
	std::deque<TypeValue>	    m_deque;
	semaphore_t				    m_sem;
	mutex_t 					m_mutex;
};


template<class TypeValue>
CTaskList<TypeValue>::CTaskList(void)
{
    mutex_create(&m_mutex);
    semaphore_create(&m_sem,0,0x0FFFFFFF);
}

template<class TypeValue>
CTaskList<TypeValue>::~CTaskList(void)
{
    mutex_destroy(&m_mutex);
    semaphore_destroy(&m_sem);
}

template<class TypeValue>
void		CTaskList<TypeValue>::PushFront(TypeValue& v)
{
    mutex_lock(&m_mutex);
	m_deque.push_front(v);
	mutex_unlock(&m_mutex);
	semaphore_put(&m_sem);
}

template<class TypeValue>
void		CTaskList<TypeValue>::PushBack(TypeValue& v)
{
    mutex_lock(&m_mutex);
	m_deque.push_back(v);
	mutex_unlock(&m_mutex);
	semaphore_put(&m_sem);
}

template<class TypeValue>
int		CTaskList<TypeValue>::PopFront(TypeValue& v , uint32 timeout)
{
    if(semaphore_get(&m_sem,timeout) == 1 )
    {
        mutex_lock(&m_mutex);
        v	=	m_deque.front();
        m_deque.pop_front();
        mutex_unlock(&m_mutex);
        return 0;
    }
    return -1;
}

template<class TypeValue>
int		CTaskList<TypeValue>::PopBack(TypeValue& v , uint32 timeout)
{
    if(semaphore_get(&m_sem,timeout) == 1 )
    {
        mutex_lock(&m_mutex);
        v = m_deque.back();
        m_deque.PopBack();
        mutex_unlock(&m_mutex);
        return 0;
    }
    return -1;
}

template<class TypeValue>
int			CTaskList<TypeValue>::Size()
{
	int size = 0;
	mutex_lock(&m_mutex);
	size	=	(int)m_deque.size();
    mutex_unlock(&m_mutex);
	return size;
}

}

#endif

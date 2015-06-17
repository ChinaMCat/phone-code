#ifndef _WEEDONG_CORE_EVENTMGR_H_
#define _WEEDONG_CORE_EVENTMGR_H_

#include "../os.h"
#include <vector>

namespace wd
{

class CEventMgr
{
public:
    typedef struct _EventBase
    {
        int nEventID;
        int nSource;
        int nTarget;
    } EventBase;

    // �¼��ص�����ԭ��
    typedef void (*EVENT_PROC_T)(EventBase*);

public:
    CEventMgr(int nMaxEvent);
    ~CEventMgr();

    /*************************************************
      Description:    // ע��һ���¼�
      Input:          // nEventID �¼�ID
                      // fn �¼��ص�����
      Output:         // 0 ʧ�� ���� ע��ID
      Return:         // 
      Others:         // 
    *************************************************/
    int Register(int nEventID, EVENT_PROC_T fn);

    /*************************************************
      Description:    // ȡ���¼�ע��
      Input:          // nRegisterID ע��ID
      Output:         // 0 ʧ�� 1 �ɹ�
      Return:         // 
      Others:         // 
    *************************************************/
    int	UnRegister(int nRegisterID);

    /*************************************************
      Description:    // �����¼�
      Input:          // nEventID �¼�ID
                      // pEvent �¼���Ϣָ��
      Output:         // 0 ʧ�� 1 �ɹ�
      Return:         // 
      Others:         // 
    *************************************************/
    int	Dispatch(int nEventID, EventBase* pEvent);

private:
    std::vector< std::vector< std::pair<int, EVENT_PROC_T> > > m_EventList;
};

}

#endif

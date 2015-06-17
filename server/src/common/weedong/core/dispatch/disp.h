/*************************************************
  Model:             ��Ϣ������
  Author:            ��ѵ��
  Date:              2011-11-15
  Descript:          ��Ϣ�������ṩһ��������Ϣ���������Ĺ�ϵ�󶨷��ɹ���
*************************************************/

#ifndef _WEEDONG_CORE_DISP_H_
#define _WEEDONG_CORE_DISP_H_

#include "../os.h"
#include "tasklist.h"
#include <map>
#include <list>

namespace wd
{
	//��������״̬
	enum{
		DISPSTAT_STOP = 0,      //�Ѿ�ֹͣ״̬
		DISPSTAT_STOPING,       //����ֹͣ�е�״̬
		DISPSTAT_START          //��������״̬
	};

	//��������Ԥ����������
	typedef void (*PreCmdHandlerFunc_Ptr)(void* pNetCmd, void* pStatic, void* pDynamic);

	//���������������
	typedef void (*DispHandlerFunc_Ptr)(void* pNetCmd, void* pStatic, void* pDynamic);

    //�����������ٺ�������
    typedef void (*DispCmdDeleteFunc_Ptr)(void* pNetCmd);

    //�����������ص���������
    typedef void (*DispCmdErrorFunc_Ptr)(void* pNetCmd, void*pDynamic );

    //������������Ļص���������
    typedef void (*BusyHandlerFunc_Ptr)(void);

    //����������������ûص���������
    typedef void (*IdleHandlerFunc_Ptr)(void);

	//��¼��Ϣ�������Ͳ������ڲ��ṹ
	class CHandlerInfo{
	public:
		CHandlerInfo()
		{
			m_pFunPtr	=	NULL;
			m_pParam	=	NULL;
		}

		~CHandlerInfo()
		{
		}

		DispHandlerFunc_Ptr	    m_pFunPtr;
		void*                   m_pParam;
	};

	//�����������
	class CCmdDisp{
    public:
        struct SData
        {
            uint32 id;
            void*  data;
            void*  param;
        };
	public:
		CCmdDisp( DispCmdDeleteFunc_Ptr fn_del, DispCmdErrorFunc_Ptr fn_err = NULL );
		virtual ~CCmdDisp();

        /*************************************************
		  Description:    // ���õ�ǰ��Ϣ���д������Ļص�����
		*************************************************/
		void     SetBusyHandlerFunc(BusyHandlerFunc_Ptr pfunc);

        /*************************************************
		  Description:    // ��������Ϣ���ûص�����
		*************************************************/
		void     SetIdleHandlerFunc(IdleHandlerFunc_Ptr pfunc);

		/*************************************************
		  Description:    // ������ϢԤ����ص�����
		  Input:          //
		  Output:         //
		  Return:         //
		  Others:         //
		*************************************************/
		void     SetPreHandlerFunc(PreCmdHandlerFunc_Ptr pfunc,void*pParam);

        /*************************************************
		  Description:    // ���ô�����Ϣ�ص�����
		  Input:          //
		  Output:         //
		  Return:         //
		  Others:         //
		*************************************************/
		void     SetErrorHandlerFunc(DispCmdErrorFunc_Ptr pfunc);

		/*************************************************
		  Description:    // ������������
		  Input:          //
		  Output:         //
		  Return:         // �����ɹ�����1 ��ʧ�ܷ���0
		  Others:         //
		*************************************************/
		int     StartDisp();

		/*************************************************
		  Description:    // ֹͣ��������
		  Input:          //
		  Output:         //
		  Return:         //
		  Others:         //
		*************************************************/
		void    StopDisp();

		/*************************************************
		  Description:    // ע����Ϣ���������ú�����֧�ֶ��̣߳�����Ҫ��StartDisp����֮ǰ����
		  Input:          // cmdid ��ϢID , pFunc ������ , pParam �û��������
		  Output:         //
		  Return:         //
		  Others:         //
		*************************************************/
		void    RegHandler(uint32 cmdid,DispHandlerFunc_Ptr pFunc,void*pParam);

		/*************************************************
		  Description:    // ��ȡע�����Ϣ������
		  Input:          // cmdid ��ϢID
		  Output:         //
		  Return:         // ����ע�ắ��
		  Others:         //
		*************************************************/
		CHandlerInfo    GetHandler( uint32 cmdid );

		/*************************************************
		  Description:    // ��ע����Ϣ���������ú�����֧�ֶ��̣߳�����Ҫ��StartDisp����֮ǰ����
		  Input:          // cmdid ��ϢID
		  Output:         //
		  Return:         //
		  Others:         //
		*************************************************/
		void    UnRegHandler(uint32 cmdid);

		/*************************************************
		  Description:    // ѹ����Ϣ���д���
		  Input:          // cmdid��ϢID �� pNetCmd ��Ϣָ�룬����Ϣ���ᱻ�������ͷ�
		  Output:         //
		  Return:         //
		  Others:         //
		*************************************************/
		void    PushCmd(uint32 cmdid,void* pNetCmd, void* param);
        void    SendCmd(uint32 cmdid,void* pNetCmd, void* param);

        uint32  GetPendCount(void);

	protected:
		static unsigned int WorkerProc(void*param);

	protected:
		int										m_DispStat;				//������״̬
		thread_t								m_WorkerThread;			//�����߳�
		std::map< uint32,CHandlerInfo >			m_HandlerMap;			//�Ѿ�ע��õĴ�����
		CTaskList< SData >	                    m_PendingCmd;			//�����б�
		PreCmdHandlerFunc_Ptr					m_PreCmdHandlerFunc;	//����Ԥ������
		void*									m_PreHandlerParam;		//����Ԥ�������
        DispCmdDeleteFunc_Ptr                   m_FuncDeleteHandler;    //�������ٺ���
        DispCmdErrorFunc_Ptr                    m_FuncErrorHandler;     //���������
        BusyHandlerFunc_Ptr                     m_FuncBusyHandler;      //��ǰ�б���Ϣ�������ص�
        IdleHandlerFunc_Ptr                     m_FuncIdleHandler;      //����Ϣ�������ú�ص�
	};

}

#endif

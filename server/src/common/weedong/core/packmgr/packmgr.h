/*************************************************
  Description:      // ������Ĳ�������������
  Class:            // �з��岿
  Name:             // ��ѵ��
  Date:             // 2011-12-28
*************************************************/

#ifndef _WEEDONG_CORE_PACKMGR_H_INCLUDED
#define _WEEDONG_CORE_PACKMGR_H_INCLUDED
#include "../os.h"
#include <map>
#include <vector>

namespace wd
{

//������Ϣ������������
typedef void (*PackHandlerFunc_Ptr)(uint32 linkid,uint8* ppack , uint32 packlen);

//���ȵĴ���������������
bool	UnPackLen(uint8*&pdata,uint32& datalen,uint32& len);
bool	PackLen(uint8*&pdata,uint32& datalen,uint32 len);

//��������������
class CPackMgr
{
public:
	CPackMgr();
	~CPackMgr(void);

	void		LinkEstablish(uint32 linkid);
	void		LinkRelease(uint32 linkid);
	void		SetPackHandler(PackHandlerFunc_Ptr pfun);
	void		PullData(uint32 linkid , uint8*pdata , uint32 datalen);
protected:
	std::map<uint32,std::vector<uint8>*>		m_streams;
	PackHandlerFunc_Ptr							m_handler;
};

}

#endif	// _WEEDONG_CORE_PACKMGR_H_INCLUDED
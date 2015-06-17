/*************************************************
  Description:      // ������
  Class:            // �з��߲�
  Name:             // �潨ΰ
  Date:             // 2011-10-27
  Descript:
    �ṩ���ݴ���ͽ������
*************************************************/

#ifndef _WEEDONG_CORE_PACKGE_H_INCLUDED
#define _WEEDONG_CORE_PACKGE_H_INCLUDED

#if defined LINUX
#include <unistd.h>
#include <stdarg.h>
#include <stddef.h>
#elif defined WIN32
#include <string.h>
#include <stdlib.h>
#endif

typedef struct _tagpacket_t
{
	char* buf;			// ������ָ��
	size_t write_offset;	// ��ǰ��дλ��
	size_t read_offset;		// ��ǰ�Ѷ���λ��
	size_t max_size;	// ��������С
}packet_t;

// ����ռ�
packet_t* packet_alloc(size_t length);

// �����µİ�������-1��ʾʧ�ܣ�������ʾд������ݳ���
int packet_join(packet_t* p, const void* in_data, size_t in_max_size);

int packet_join_struct(packet_t* p, const void* in_data, size_t in_max_size);

// �Ӱ��л�ȡ���ݣ�����-1��ʾʧ�ܣ�������ʾд������ݳ���
int packet_take(packet_t* p, void* out_data, size_t out_max_size);

int packet_take_struct(packet_t* p, void* out_data, size_t out_max_size);

// ����packet
void packet_dispose(packet_t* p);

// ֱ�Ӵ���ɴ������
packet_t* packet_pack(const void* in_data, size_t in_max_size);

#endif	// _WEEDONG_CORE_PACKGE_H_INCLUDED
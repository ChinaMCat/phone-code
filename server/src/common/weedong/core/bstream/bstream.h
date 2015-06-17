/*************************************************
  Model:            // ������������
  Class:            // �з�����
  Name:             // ������
  Date:             // 2011-10-25
  Descript:
    �ṩ�Զ��������ݵ���ʽ��������
*************************************************/

#ifndef _WEEDONG_CORE_BSTREAM_BSTREAM_H_
#define _WEEDONG_CORE_BSTREAM_BSTREAM_H_

#include <weedong/core/os.h>
#include <algorithm>
#include <vector>
#include <string>
#include <deque>
#include <map>

namespace wd
{

/*************************************************
  Description:    ������������������

  �ṩ������дָ��λ�ã� ͨ��ָ��λ�ÿ����������Ķ�дλ��
*************************************************/
class CStream
{
private:
    std::vector<uint8> m_Buff;
    std::vector<uint8>::iterator m_Pointer;

    std::deque<int32> m_Stack;

public:
    /*************************************************
      Description:    // ���캯��
      Input:          // uiSize ���ݻ���Ԥ�����С
    *************************************************/
    CStream( uint32 uiSize = 1024 );
    CStream( const void *pvData, uint32 uiSize );
    CStream( wd::CStream const& stream );

    /*************************************************
      Description:    // ��������, �����౻����
    *************************************************/
    virtual ~CStream();

    /*************************************************
      Description:    // ��ȡ��������ǰ�����ֽ���
      Return:         // ���ؿ����ֽ���
    *************************************************/
    uint32 available(void);

    /*************************************************
      Description:    // ��ȡ�����������ܳ���
      Return:         // �����������ܳ���
    *************************************************/
    uint32 length(void);

    /*************************************************
      Description:    // ���������
    *************************************************/
    void clear(void);

    /*************************************************
      Description:    // ���û������ߴ�
    *************************************************/
    void resize( uint32 size );

    /*************************************************
      Description:    // ��ȡ��������ǰָ��λ��
      Return:         // ����������ָ��λ������
      Oter:           // �� 0 ��ʼ
    *************************************************/
    uint32 position(void);

    /*************************************************
      Description:    // ����������ָ��λ��
      Oter:           // �� 0 ��ʼ
    *************************************************/
    void position( uint32 uiPosition );

    void posi_push(void);
    void posi_pop(void);
    void posi_clear(void);

    wd::CStream& operator += ( int32 offset );
    wd::CStream& operator -= ( int32 offset );

    /*************************************************
      Description:    // ��������
      Oter:           // ������ 0 ��ʼ����ǰ position λ�õ�����
    *************************************************/
    void erase(void);

    /*************************************************
      Description:    // ��ȡ�������±�����λ��
      Input:          // position : ������ָ��λ��
      Return:         // ���������ݵ�Ԫ����
    *************************************************/
    uint8& operator [] ( int32 position );

    /*************************************************
      Description:    // �ӵ�ǰ����ָ��λ�ö�ȡ�������е�����
      Input:          // pvData : ���ݻ���
                      // uiSize : ��ȡ����
    *************************************************/
    void read( void *pvData, uint32 uiSize );

    /*************************************************
      Description:    // �ӵ�������ָ��λ��д������
      Input:          // pvData : ��Ҫд��Ķ�����ָ�����
      Return:         // uiSize : ��Ҫд������ݳ���
    *************************************************/
    void write( const void *pvData, uint32 uiSize );

    /*************************************************
      Description:    // �ӵ�ǰָ��λ�ö�ȡ�ַ���
      Input:          // strValue : ��ȡ�����ݽ����浽�� std::string ������
                      // uiSize : ��Ҫ��ȡ�����ݳ���
    *************************************************/
    void read( std::string &strValue, uint32 uiSize );

    /*************************************************
      Description:    // �ڵ�ǰָ��λ����д������
      Input:          // strValue : ��Ҫд��� std::string �ַ�������
                      // uiSize : ��Ҫд������ݳ���
    *************************************************/
    void write( std::string &strValue, uint32 uiSize );
};

/*************************************************
Description:    // ���������л�����
 *************************************************/
template< typename T > CStream& operator << ( CStream& stream, T& seq )
{
    seq.write( stream );
    return stream;
}
template< typename T > CStream& operator >> ( CStream& stream, T& seq )
{
    seq.read( stream );
    return stream;
}

/*************************************************
Description:    // �����Ƕ���������
 *************************************************/
template<> CStream& operator >> ( CStream& stream, std::vector<uint8> &vecBuff );
template<> CStream& operator << ( CStream& stream, std::vector<uint8> &vecBuff );
template<> CStream& operator << ( CStream& l, CStream& r );
template<> CStream& operator << ( CStream& stream, const std::string& v );
template<> CStream& operator << ( CStream& stream, std::string& v );

/*************************************************
Description:    // �����ǻ���������
 *************************************************/
template<> CStream& operator << ( CStream& stream, const bool &v );
template<> CStream& operator << ( CStream& stream, bool &v );
template<> CStream& operator >> ( CStream& stream, bool &v );

template<> CStream& operator << ( CStream& stream, const int8 &v );
template<> CStream& operator << ( CStream& stream, int8 &v );
template<> CStream& operator >> ( CStream& stream, int8 &v );

template<> CStream& operator << ( CStream& stream, const uint8 &v );
template<> CStream& operator << ( CStream& stream, uint8 &v );
template<> CStream& operator >> ( CStream& stream, uint8 &v );

template<> CStream& operator << ( CStream& stream, const int16 &v );
template<> CStream& operator << ( CStream& stream, int16 &v );
template<> CStream& operator >> ( CStream& stream, int16 &v );

template<> CStream& operator << ( CStream& stream, const uint16 &v );
template<> CStream& operator << ( CStream& stream, uint16 &v );
template<> CStream& operator >> ( CStream& stream, uint16 &v );

template<> CStream& operator << ( CStream& stream, const int32 &v );
template<> CStream& operator << ( CStream& stream, int32 &v );
template<> CStream& operator >> ( CStream& stream, int32 &v );

template<> CStream& operator << ( CStream& stream, const uint32 &v );
template<> CStream& operator << ( CStream& stream, uint32 &v );
template<> CStream& operator >> ( CStream& stream, uint32 &v );

template<> CStream& operator << ( CStream& stream, const float &v );
template<> CStream& operator << ( CStream& stream, float &v );
template<> CStream& operator >> ( CStream& stream, float &v );

template<> CStream& operator << ( CStream& stream, const double &v );
template<> CStream& operator << ( CStream& stream, double &v );
template<> CStream& operator >> ( CStream& stream, double &v );

/*************************************************
Description:    // ����������������
 *************************************************/

//array
template< typename T >
struct stream_array_process
{
    wd::CStream& stream;
    stream_array_process( wd::CStream& s ) : stream(s){}

    void operator()( T& data )
    {
        stream << data;
    }
};
template< typename T > CStream& operator << ( CStream& stream, std::vector<T>& array )
{
    uint16 size = (uint16)array.size();
    stream << size;

    std::for_each( array.begin(), array.end(), stream_array_process<T>( stream ) );

    return stream;
}
template< typename T > CStream& operator >> ( CStream& stream, std::vector<T>& array )
{
    array.clear();

    uint16 size = 0;
    stream >> size;

    T data;
    for ( int32 i = 0; i < (int32)size; ++i )
    {
        stream >> data;
        array.push_back( data );
    }

    return stream;
}

//map
struct stream_map_process
{
    wd::CStream& stream;
    stream_map_process( wd::CStream& s ) : stream(s){}

    template< typename T >
    void operator()( T& data )
    {
        uint16 length = (uint16)data.first.size();

        stream << length;
        stream << data.first;
        stream << data.second;
    }
};
template< typename T > CStream& operator << ( CStream& stream, std::map< std::string, T >& map )
{
    uint16 size = (uint16)map.size();
    stream << size;

    std::for_each( map.begin(), map.end(), stream_map_process( stream ) );

    return stream;
}
template< typename T > CStream& operator >> ( CStream& stream, std::map< std::string, T >& map )
{
    map.clear();

    uint16 size = 0;
    stream >> size;

    std::string key;
    for ( int32 i = 0; i < (int32)size; ++i )
    {
        uint16 length = 0;
        stream >> length;

        key.resize( length );
        stream.read( &key[0], key.size() );

        stream >> map[ key ];
    }

    return stream;
}

//indices
struct stream_indices_process
{
    wd::CStream& stream;
    stream_indices_process( wd::CStream& s ) : stream(s){}

    template< typename T >
    void operator()( T& data )
    {
        stream << data.first;
        stream << data.second;
    }
};
template< typename T > CStream& operator << ( CStream& stream, std::map< uint32, T >& indices )
{
    uint16 size = (uint16)indices.size();
    stream << size;

    std::for_each( indices.begin(), indices.end(), stream_indices_process( stream ) );

    return stream;
}
template< typename T > CStream& operator >> ( CStream& stream, std::map< uint32, T >& indices )
{
    indices.clear();

    uint16 size = 0;
    stream >> size;

    uint32 key = 0;
    for ( int32 i = 0; i < (int32)size; ++i )
    {
        stream >> key;
        stream >> indices[ key ];
    }

    return stream;
}
}

#endif


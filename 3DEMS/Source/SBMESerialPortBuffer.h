#ifndef SBMESERIALPORTBUFFER_H
#define SBMESERIALPORTBUFFER_H

template <typename T>
class SBMESerialPortBuffer
{
public:
    SBMESerialPortBuffer(int initsize = 10000, T initvalue=0);
    
	bool write(T e);
    T    read(int p);
    int  GetLen();
    void MoveRead(int delta);

private:
    int m_nSize;
	int m_nWrite;
    int m_nRead;
    T   *m_pBase;
};

template <typename T>
SBMESerialPortBuffer<T>::SBMESerialPortBuffer(int initsize, T initvalue)
{
    m_nSize = initsize;
    m_pBase = new T[m_nSize];
    if (!m_pBase)
        exit(1);
    for (int i = 0; i < m_nSize; i++)
    {
        m_pBase[i] = initvalue;
    }
    m_nRead = m_nWrite = 0;
}

template <typename T>
bool SBMESerialPortBuffer<T>::write(T e)
{
    if ((m_nWrite + 1) % m_nSize  == m_nRead)
        return false;
    m_pBase[m_nWrite] = e;
    m_nWrite = (m_nWrite + 1) % m_nSize;
    return true;
}

template <typename T>
T SBMESerialPortBuffer<T>::read(int p)
{
    T e = m_pBase[(m_nRead + p) % m_nSize];
    return e;
}

template <typename T>
int SBMESerialPortBuffer<T>::GetLen()
{
    if (m_nWrite >= m_nRead)
		return (m_nWrite - m_nRead);
	else
		return (m_nWrite - m_nRead + m_nSize);
}

template <typename T>
void SBMESerialPortBuffer<T>::MoveRead(int delta)
{
    m_nRead += delta;
    m_nRead %= m_nSize;    //不考虑delta<0的情况
}

#endif // SBMESERIALPORTBUFFER_H

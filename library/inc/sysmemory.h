#ifndef __PERF_TOOL_SYS_MEM_H__
#define __PERF_TOOL_SYS_MEM_H__

#include <cstdint>
#include <fstream>

class SysMemory
{
public:
    SysMemory();
    virtual ~SysMemory();
    
    bool IsValidate() const { return m_total != 0; }
    
    uint32_t GetTotalSize() const { return m_total; }
    uint32_t GetAvailableSize()  { UpdateData(); return m_available; }
    uint32_t GetFreeSize()  { UpdateData(); return m_free; }
    uint32_t GetCachedSize()  { UpdateData(); return m_cached; }
    
    float GetUsage() { UpdateData(); return ((m_total - m_available) * 1.00 / m_total); }

    const std::string& GetSystemVersion() const { return m_systemVersion; }
    
    uint32_t GetSpeed() const { return m_speed; }
    uint32_t GetChannel() const { return m_channel; }
    uint32_t GetCapacity() const { return m_capacity; }
    uint32_t GetBitWidth() const { return m_bitWidth; }
    const std::string& GetType()  const { return m_type; }

    uint32_t GetIdealBandWidth();

    
    void Dump();
protected:
    void UpdateData();
    void ReadAvailableSize(const std::string& rawString);
    void ReadCachedSize(const std::string& rawString);
    void ReadTotalSize(const std::string& rawString);
    void ReadFreeSize(const std::string& rawString);

    void ReadSystemVersion();

    std::string ReadData(const std::string& rawString, const std::string &prefix);
    void ReadStaticInfo();
    
private:
    static const std::string TOTAL_MEM_PREFIX;
    static const std::string FREE_MEM_PREFIX;
    static const std::string AVAILABLE_MEM_PREFIX;
    static const std::string CACHED_MEM_PREFIX;

    static const std::string SYSTEM_VERSION_FILE;
    
    uint32_t m_total     = 0;
    uint32_t m_available = 0;
    uint32_t m_free      = 0;
    uint32_t m_cached    = 0;

    uint32_t m_speed     = 0;
    uint32_t m_channel   = 0;
    uint32_t m_capacity  = 0;
    uint32_t m_bitWidth  = 0;
    std::string m_type   = "";

    std::string m_systemVersion = "";

    std::ifstream m_ifs;
};

#endif

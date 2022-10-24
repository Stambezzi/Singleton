#include <iostream>
#include <map>

class CLightingDeviceData
{
public:
    CLightingDeviceData() : fNumberOfChannels(0), fDmxAddress("") {};
    CLightingDeviceData(int channels, const std::string& dmxAddress)
    {
        fNumberOfChannels = channels;
        fDmxAddress = dmxAddress;
    }

    friend std::ostream& operator<<(std::ostream& os, const CLightingDeviceData& data)
    {
        return os << "Number of cahnnels: " << data.fNumberOfChannels << " DMX Address: " << data.fDmxAddress << "\n";
    }

private:
    int fNumberOfChannels;
    std::string fDmxAddress;
};

using Uuid = int;

class CSingletonDatabase
{
public:
    CSingletonDatabase(const CSingletonDatabase& other) = delete;
    CSingletonDatabase operator=(const CSingletonDatabase& other) = delete;

    static CSingletonDatabase& GetInstance() 
    {
        static CSingletonDatabase db;
        return db;
    }

    CLightingDeviceData GetDataForDevice(Uuid uuid)
    {
        return fUuidToData[uuid];
    }

private:
    CSingletonDatabase()
    {
        std::cout << "Initialization\n";
        this->InitializeDummyDatabase();
    }

    void InitializeDummyDatabase()
    {
        fUuidToData = {
            {1, CLightingDeviceData(5, "123/1")},
            {2, CLightingDeviceData(5, "128/1")},
            {3, CLightingDeviceData(5, "133/1")},
            {4, CLightingDeviceData(5, "138/1")}
        };
    }

    std::map<Uuid, CLightingDeviceData> fUuidToData;
};

int main()
{
    std::cout << CSingletonDatabase::GetInstance().GetDataForDevice(1);
    std::cout << CSingletonDatabase::GetInstance().GetDataForDevice(2);
    std::cout << CSingletonDatabase::GetInstance().GetDataForDevice(3);
    std::cout << CSingletonDatabase::GetInstance().GetDataForDevice(4);
}


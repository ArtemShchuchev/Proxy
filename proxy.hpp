#include <map>
#include <string>
#include <iostream>

class VeryHeavyDatabase
{
public:
    std::wstring GetData(const std::wstring& key) const noexcept
    {
        //return L"Very Big Data String: " + key;
        return L"value";
    }
};

class CacheProxyDB : VeryHeavyDatabase
{
public:
    explicit CacheProxyDB (VeryHeavyDatabase* real_object) : real_db_(real_object) {}
    std::wstring GetData(const std::wstring& key) noexcept
    {
        if (cache_.find(key) == cache_.end())
        {
            std::wcout << L"Get from real object\n";
            cache_[key] = real_db_->GetData(key);
        }
        else std::wcout << L"Get from cache\n";
        
        return cache_.at(key);
    }

private:
    std::map<std::wstring, std::wstring> cache_;
    VeryHeavyDatabase* real_db_;
};

class TestDB : VeryHeavyDatabase
{
public:
    explicit TestDB(VeryHeavyDatabase* real_object) : real_db_(real_object) {}
    std::wstring GetData(const std::wstring& key) noexcept
    {
        return L"test_data\n";
    }
private:
    VeryHeavyDatabase* real_db_;
};

class OneShotDB : VeryHeavyDatabase
{
public:
    explicit OneShotDB(VeryHeavyDatabase* real_object, size_t shots = 1) : real_db_(real_object), count(shots) {}
    std::wstring GetData(const std::wstring& key) noexcept
    {
        std::wstring data(L"error");
        if (count--)
        {
            data = real_db_->GetData(key);
        }

        return data;
    }
private:
    VeryHeavyDatabase* real_db_;
    size_t count;
};
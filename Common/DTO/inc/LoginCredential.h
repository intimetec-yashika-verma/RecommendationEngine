#include <iostream>
struct LoginCredential
{
    std::string emailId;
    std::string password;

    std::string serialize() const
    {
        return emailId + "," + password;
    }
    void deserialize(const std::string &data)
    {
        size_t pos = data.find(",");
        if (pos != std::string::npos)
        {
            emailId = data.substr(0, pos);
            password = data.substr(pos + 1);
        }
    }
};
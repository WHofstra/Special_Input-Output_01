#include "Controller.h"
#include "Controller.h"

Controller::Controller(std::string* anUrl, std::string* aPath, sf::RenderWindow* aWindow)
{
    request = sf::Http::Request(*aPath, sf::Http::Request::Get);
    http.setHost(*anUrl);
    response = http.sendRequest(request);

    //Check if Http-request is Correct
    if (response.getStatus() == sf::Http::Response::Ok)
    {
        // Check Contents of Response
        std::cout << "Request succeeded." << std::endl;

        //Convert Response to Json-object
        values = GetResponseInObject(&response, &values);
    }
    else
    {
        std::cout << "Request failed." << std::endl;
        EXIT_FAILURE;
        aWindow->close();
    }

    valueNames = AddToValueNames(&valueNames, "AcX");
    valueNames = AddToValueNames(&valueNames, "AcY");
    valueNames = AddToValueNames(&valueNames, "AcZ");
    valueNames = AddToValueNames(&valueNames, "GyX");
    valueNames = AddToValueNames(&valueNames, "GyY");
    valueNames = AddToValueNames(&valueNames, "GyZ");
}

Controller::~Controller()
{

}

void Controller::Update()
{
    response = http.sendRequest(request);
    if (response.getStatus() == sf::Http::Response::Ok)
    {
        //Convert Response to Json-object
        values = GetResponseInObject(&response, &values);
    }
    else
    {
        std::cout << "Request failed." << std::endl;
        EXIT_FAILURE;
        window->close();
    }
}

std::vector<std::string> Controller::AddToValueNames(std::vector<std::string>* aList, std::string aName)
{
    aList->push_back(aName);
    return *aList;
}

std::map<std::string, int> Controller::AddToValueTriggers(std::map<std::string, int>* aList,
    std::map<std::string, int>::iterator anIt, int amount)
{
    //aList->insert(anIt, amount);
    return *aList;
}

nlohmann::json Controller::GetResponseInObject(sf::Http::Response* aResponse, nlohmann::json* val)
{
    //std::cout << aResponse->getBody() << std::endl; //Debug

    val->clear();
    std::stringstream(aResponse->getBody()) >> (*val);

    return *val;
}

nlohmann::json Controller::GetValues()
{
    return values;
}

std::vector<std::string> Controller::GetValueNames()
{
    return valueNames;
}

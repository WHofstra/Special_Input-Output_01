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
        //std::cout << response.getBody() << std::endl;
        std::cout << "Request succeeded." << std::endl;
    }
    else
    {
        std::cout << "Request failed." << std::endl;
        EXIT_FAILURE;
        aWindow->close();
    }
}

Controller::~Controller()
{

}

void Controller::Update()
{
    
}

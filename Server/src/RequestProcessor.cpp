#include "RequestProcessor.h"
#include "Operation.h"
#include "RequestSerializer.h"
#include "AuthenticationController.h"
#include <utility>
#include "UserService.h"
#include "UserDAO.h"
#include "AdminController.h"
#include "MenuDAO.h"
#include "MenuService.h"
#include "RecommendationService.h"
#include "SelectionService.h"
#include "NotificationService.h"
#include "ChefController.h"
#include "SelectedItemsDAO.h"
#include "PublishedMenuDAO.h"
#include "NotificationDAO.h"
#include "EmployeeController.h"
#include "FeedbackDAO.h"
#include "UserProfile.h"
#include "UserActivityDAO.h"

RequestProcessor::RequestProcessor()
{
}

std::string RequestProcessor::processRequest(std::string userResponse)
{
    std::cout << "processRequest" << std::endl;
    std::pair<Operation,std::string> requestData = RequestSerializer::deserializeOperation(userResponse);
    std::cout << requestData.first << " " << requestData.second << std::endl;
    std::string response;
    if (!isUserLoggedIn)
    {
        std::cout << "isUserLoggedIn " << isUserLoggedIn << std::endl;
        UserDAO *userDAO = new UserDAO();
        UserActivityDAO *userActivityDAO = new UserActivityDAO();
        UserService *userService = new UserService(userDAO, userActivityDAO);
        AuthenticationController authenticationController = AuthenticationController(userService);
        userProfile = authenticationController.authenticateUser(requestData.second);
        std::cout << "userAuthenticated " << std::endl;
        isUserLoggedIn = true;
        response.push_back(userProfile.role);
        switch (std::stoi(userProfile.role))
        {
        case Role::admin:
        {
            std::cout << "Admin LoggedIn" << std::endl;
            MenuDAO *menuDao = new MenuDAO();
            MenuService *menuService = new MenuService(menuDao);
            userController = new AdminController(menuService, userProfile);
            break;
        }
        case Role::chef:
        {
            std::cout << "Chef LoggedIn" << std::endl;
            MenuDAO *menuDao = new MenuDAO();
            FeedbackDAO *feedbackDao = new FeedbackDAO();
            PublishedMenuDAO *publishedMenuDAO = new PublishedMenuDAO();
            MenuService *menuService = new MenuService(menuDao);
            SelectedItemsDAO *selectedItemsDAO = new SelectedItemsDAO();
            RecommendationService *recommendationService = new RecommendationService(menuDao, feedbackDao);
            SelectionService *selectionService = new SelectionService(selectedItemsDAO, publishedMenuDAO);
            NotificationDAO *notificationDAO = new NotificationDAO();
            NotificationService *notificationService = new NotificationService(notificationDAO);
            userController = new ChefController(recommendationService, selectionService, notificationService, menuService);
            break;
        }
        case Role::employee:
        {
            std::cout << "Employee logged In" << std::endl;
            PublishedMenuDAO *publishedMenuDAO = new PublishedMenuDAO();
            SelectedItemsDAO *selectedItemsDAO = new SelectedItemsDAO();
            FeedbackDAO *feedbackDAO = new FeedbackDAO();
            NotificationDAO *notificationDAO = new NotificationDAO();
            SelectionService *selectionService = new SelectionService(selectedItemsDAO, publishedMenuDAO);
            NotificationService *notificationService = new NotificationService(notificationDAO);
            FeedbackService *feedbackService = new FeedbackService(feedbackDAO);
            userController = new EmployeeController(notificationService, selectionService, feedbackService, userId);
        }
        }
    }
    else
    {
        std::cout << "userController " << std::endl;
        response = userController->handleRequest(requestData);
        std::cout << "response received" << response[0] << std::endl;
    }
    for (int i = 0; i < response.size(); i++)
    {
        std::cout << response[i] << std::endl;
    }
    return response;
}
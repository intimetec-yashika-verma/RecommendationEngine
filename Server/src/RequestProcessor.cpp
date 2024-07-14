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
#include "PublishMenuService.h"
#include "DiscardItemDAO.h"
#include "DiscardMenuItemService.h"
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
        response = userProfile.role;
        std::cout<<response<<std::endl;
        switch (static_cast<Role>(std::stoi(userProfile.role)))
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
            PublishMenuService *publishMenuService = new PublishMenuService(publishedMenuDAO);
            MenuService *menuService = new MenuService(menuDao);
            SelectedItemsDAO *selectedItemsDAO = new SelectedItemsDAO();
            RecommendationService *recommendationService = new RecommendationService(menuDao, feedbackDao);
            UserActivityDAO *userActivityDAO = new UserActivityDAO();
            DiscardItemDAO *discardItemDAO = new DiscardItemDAO();
            UserActivityService *userActivityService = new UserActivityService(userActivityDAO);
            SelectionService *selectionService = new SelectionService(selectedItemsDAO);
            NotificationDAO *notificationDAO = new NotificationDAO();
            NotificationService *notificationService = new NotificationService(notificationDAO);
            FeedbackService *feedbackService = new FeedbackService(feedbackDao);
            DiscardMenuItemService *discardMenuItemService = new DiscardMenuItemService(discardItemDAO);
            userController = new ChefController(recommendationService, selectionService, notificationService, menuService,feedbackService,publishMenuService,userActivityService,discardMenuItemService,userProfile);
            break;
        }
        case Role::employee:
        {
            std::cout << "Employee logged In" << std::endl;
            MenuDAO *menuDAO = new MenuDAO();
            PublishedMenuDAO *publishedMenuDAO = new PublishedMenuDAO();
            SelectedItemsDAO *selectedItemsDAO = new SelectedItemsDAO();
            FeedbackDAO *feedbackDAO = new FeedbackDAO();
            NotificationDAO *notificationDAO = new NotificationDAO();
            UserActivityDAO *userActivityDAO = new UserActivityDAO();
            MenuService *menuService = new MenuService(menuDAO);
            UserActivityService *userActivityService = new UserActivityService(userActivityDAO);
            SelectionService *selectionService = new SelectionService(selectedItemsDAO);
            NotificationService *notificationService = new NotificationService(notificationDAO);
            FeedbackService *feedbackService = new FeedbackService(feedbackDAO);
            DiscardItemDAO *discardItemDAO = new DiscardItemDAO();
            DiscardMenuItemService *discardMenuItemService = new DiscardMenuItemService(discardItemDAO);
            RecommendationService *recommendationService = new RecommendationService(menuDAO, feedbackDAO);      
            PublishMenuService *publishMenuService = new PublishMenuService(publishedMenuDAO);

            userController = new EmployeeController(notificationService, selectionService, feedbackService,recommendationService,menuService, publishMenuService,discardMenuItemService,userProfile);
        }
        }
    }
    else
    {
        if(requestData.first == Operation::logout)
        {
            isUserLoggedIn = false;
            return "close";
        }
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
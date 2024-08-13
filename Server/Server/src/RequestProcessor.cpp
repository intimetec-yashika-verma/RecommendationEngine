#include "RequestProcessor.h"
#include "Operation.h"

#include "AuthenticationController.h"
#include <utility>
#include "UserService.h"
#include "UserDAO.h"
#include "AdminController.h"
#include "MenuDAO.h"
#include "MenuService.h"
#include "RecommendationEngine.h"
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
    helper = new Helper();
}

std::string RequestProcessor::processRequest(std::string userResponse)
{
    try
    {
        std::pair<Operation, std::string> requestData = helper->deserializeOperation(userResponse);
        std::string response;
        if (!isUserLoggedIn)
        {
            UserDAO *userDAO = new UserDAO();
            UserActivityDAO *userActivityDAO = new UserActivityDAO();
            UserService *userService = new UserService(userDAO);
            AuthenticationController authenticationController = AuthenticationController(userService);
            userProfile = authenticationController.authenticateUser(requestData.second);
            if (userProfile.userId == "")
            {
                return userProfile.role;
            }
            isUserLoggedIn = true;
            response = userProfile.role;
            switch (static_cast<Role>(std::stoi(userProfile.role)))
            {
            case Role::admin:
            {
                adminLogin();
                break;
            }
            case Role::chef:
            {
                chefLogin();
                break;
            }
            case Role::employee:
            {
                employeeLogin();
                break;
            }
            }
        }
        else
        {
            if (requestData.first == Operation::logout)
            {
                isUserLoggedIn = false;
                return "close";
            }
            response = userController->handleRequest(requestData);
        }
        return response;
    }
    catch (const std::exception &e)
    {
        return e.what();
    }
}

void RequestProcessor::employeeLogin()
{
    std::cout << "Employee logged In" << std::endl;
    MenuDAO *menuDAO = new MenuDAO();
    PublishedMenuDAO *publishedMenuDAO = new PublishedMenuDAO();
    SelectedItemsDAO *selectedItemsDAO = new SelectedItemsDAO();
    FeedbackDAO *feedbackDAO = new FeedbackDAO();
    NotificationDAO *notificationDAO = new NotificationDAO();
    UserActivityDAO *userActivityDAO = new UserActivityDAO();
    UserActivityService *userActivityService = new UserActivityService(userActivityDAO);
    NotificationService *notificationService = new NotificationService(notificationDAO,userActivityService);
    MenuService *menuService = new MenuService(menuDAO,notificationService,userActivityService);
    SelectionService *selectionService = new SelectionService(selectedItemsDAO,notificationService,userActivityService);
    FeedbackService *feedbackService = new FeedbackService(feedbackDAO,userActivityService);
    DiscardItemDAO *discardItemDAO = new DiscardItemDAO();
    DiscardMenuItemService *discardMenuItemService = new DiscardMenuItemService(discardItemDAO,userActivityService,notificationService); 
    RecommendationEngine *recommendationEngine = new RecommendationEngine();
    PublishMenuService *publishMenuService = new PublishMenuService(publishedMenuDAO);
    userActivityService->saveUserActivity(userProfile.userId, "Employee Logged In");
    userController = new EmployeeController(notificationService, selectionService, feedbackService, recommendationEngine, menuService, publishMenuService, discardMenuItemService, userActivityService, userProfile);
}

void RequestProcessor::chefLogin()
{
    std::cout << "Chef LoggedIn" << std::endl;
    MenuDAO *menuDAO = new MenuDAO();
    FeedbackDAO *feedbackDao = new FeedbackDAO();
    PublishedMenuDAO *publishedMenuDAO = new PublishedMenuDAO();
    PublishMenuService *publishMenuService = new PublishMenuService(publishedMenuDAO);
    SelectedItemsDAO *selectedItemsDAO = new SelectedItemsDAO();
    RecommendationEngine *recommendationEngine = new RecommendationEngine();
    UserActivityDAO *userActivityDAO = new UserActivityDAO();
    NotificationDAO *notificationDAO = new NotificationDAO();
    DiscardItemDAO *discardItemDAO = new DiscardItemDAO();
    UserActivityService *userActivityService = new UserActivityService(userActivityDAO);
    NotificationService *notificationService = new NotificationService(notificationDAO,userActivityService);
    FeedbackService *feedbackService = new FeedbackService(feedbackDao,userActivityService);
    DiscardMenuItemService *discardMenuItemService = new DiscardMenuItemService(discardItemDAO,userActivityService,notificationService);
    MenuService *menuService = new MenuService(menuDAO,notificationService,userActivityService);
    SelectionService *selectionService = new SelectionService(selectedItemsDAO,notificationService,userActivityService);
    userActivityService->saveUserActivity(userProfile.userId, "Chef Logged In");
    userController = new ChefController(recommendationEngine, selectionService, menuService, feedbackService, publishMenuService, discardMenuItemService, userProfile);
}

void RequestProcessor::adminLogin()
{
    std::cout << "Admin LoggedIn" << std::endl;
    MenuDAO *menuDAO = new MenuDAO();
    UserActivityDAO *userActivityDAO = new UserActivityDAO();
    NotificationDAO *notificationDAO = new NotificationDAO();
    UserActivityService *userActivityService = new UserActivityService(userActivityDAO);
    NotificationService *notificationService = new NotificationService(notificationDAO,userActivityService);
    MenuService *menuService = new MenuService(menuDAO,notificationService,userActivityService);
    userActivityService->saveUserActivity(userProfile.userId, "Admin Logged In");
    userController = new AdminController(menuService,userProfile);
}
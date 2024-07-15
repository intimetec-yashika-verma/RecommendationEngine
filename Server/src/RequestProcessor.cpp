#include "RequestProcessor.h"
#include "Operation.h"

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
    MenuService *menuService = new MenuService(menuDAO);
    UserActivityService *userActivityService = new UserActivityService(userActivityDAO);
    SelectionService *selectionService = new SelectionService(selectedItemsDAO);
    NotificationService *notificationService = new NotificationService(notificationDAO);
    FeedbackService *feedbackService = new FeedbackService(feedbackDAO);
    DiscardItemDAO *discardItemDAO = new DiscardItemDAO();
    DiscardMenuItemService *discardMenuItemService = new DiscardMenuItemService(discardItemDAO);
    RecommendationService *recommendationService = new RecommendationService(menuDAO, feedbackDAO);
    PublishMenuService *publishMenuService = new PublishMenuService(publishedMenuDAO);
    userActivityService->saveUserActivity(userProfile.userId, "Employee Logged In");
    userController = new EmployeeController(notificationService, selectionService, feedbackService, recommendationService, menuService, publishMenuService, discardMenuItemService, userActivityService, userProfile);
}

void RequestProcessor::chefLogin()
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
    userActivityService->saveUserActivity(userProfile.userId, "Chef Logged In");
    userController = new ChefController(recommendationService, selectionService, notificationService, menuService, feedbackService, publishMenuService, userActivityService, discardMenuItemService, userProfile);
}

void RequestProcessor::adminLogin()
{
    std::cout << "Admin LoggedIn" << std::endl;
    MenuDAO *menuDao = new MenuDAO();
    UserActivityDAO *userActivityDAO = new UserActivityDAO();
    MenuService *menuService = new MenuService(menuDao);
    NotificationDAO *notificationDAO = new NotificationDAO();
    NotificationService *notificationService = new NotificationService(notificationDAO);
    UserActivityService *userActivityService = new UserActivityService(userActivityDAO);
    userActivityService->saveUserActivity(userProfile.userId, "Admin Logged In");
    userController = new AdminController(menuService, userActivityService, notificationService, userProfile);
}
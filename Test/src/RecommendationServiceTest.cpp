#include <gtest/gtest.h>
#include "RecommendationService.h"

class RecommendationServiceTest : public ::testing::Test
{
protected:
    void SetUp() override
    {

        recommendationService = new RecommendationService();
    }

    void TearDown() override
    {
        delete recommendationService;
    }

    RecommendationService *recommendationService;
};

TEST_F(RecommendationServiceTest, RecommendTopFoodItemsTest)
{
    std::string mealType = "lunch";
    std::unordered_map<std::string, std::vector<Feedback>> feedbackMap;
    std::vector<MenuItem> menuItems;
    std::vector<ItemReview> recommendedItems = recommendationService->recommendTopFoodItems(mealType, feedbackMap, menuItems);

    ASSERT_FALSE(recommendedItems.empty());
    ASSERT_LE(recommendedItems.size(), 4);
}
TEST_F(RecommendationServiceTest, AnalyzeSentimentTest)
{
    std::string comment = "This dish was delicious and satisfying.";
    std::vector<std::string> foundSentiments;
    double sentimentScore = recommendationService->analyzeSentiment(comment, foundSentiments);
    ASSERT_GT(sentimentScore, 0.0);
    ASSERT_FALSE(foundSentiments.empty());
    ASSERT_EQ(foundSentiments[0], "delicious");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

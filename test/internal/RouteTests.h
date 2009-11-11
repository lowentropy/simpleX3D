#include "internal/Route.h"
#include "internal/Browser.h"

TEST(RouteStorage, NewRouteByNamesShouldBeListedByFields) {
    Node* from = browser()->createNode("TimeSensor");
    Node* to = browser()->createNode("TimeSensor");
    Route* route = browser()->createRoute(from, "loop_changed", to, "set_enabled");
    ASSERT_THAT(route, NotNull());
    EXPECT_EQ(route, from->getField("loop")->getOutgoingRoutes().front());
    EXPECT_EQ(route, from->getField("loop")->getOutgoingRoutes().back());
    EXPECT_EQ(route, to->getField("enabled")->getIncomingRoutes().front());
    EXPECT_EQ(route, to->getField("enabled")->getIncomingRoutes().back());
}

TEST(RouteStorage, NewRouteByPtrsShouldBeListedByFields) {
    Node* from = browser()->createNode("TimeSensor");
    Node* to = browser()->createNode("TimeSensor");
    SAIField* fromField = from->getField("loop_changed");
    SAIField* toField = to->getField("set_enabled");
    ASSERT_THAT(fromField, NotNull());
    ASSERT_THAT(toField, NotNull());
    Route* route = browser()->createRoute(fromField, toField);
    ASSERT_THAT(route, NotNull());
    EXPECT_EQ(route, fromField->getOutgoingRoutes().front());
    EXPECT_EQ(route, fromField->getOutgoingRoutes().back());
    EXPECT_EQ(route, toField->getIncomingRoutes().front());
    EXPECT_EQ(route, toField->getIncomingRoutes().back());
}

TEST(RouteStorage, NewRouteShouldFailIfTypesMismatch) {
    Node* from = browser()->createNode("TimeSensor");
    Node* to = browser()->createNode("TimeSensor");
    EXPECT_ANY_THROW(browser()->createRoute(from, "time", to, "enabled"));
}

TEST(RouteStorage, RemoveRouteShouldUnlistFromFields) {
    Node* from = browser()->createNode("TimeSensor");
    Node* to = browser()->createNode("TimeSensor");
    Route* route = browser()->createRoute(from, "loop_changed", to, "set_enabled");
    ASSERT_THAT(route, NotNull());
    route->remove();
    EXPECT_EQ(0, from->getField("loop")->getOutgoingRoutes().size());
    EXPECT_EQ(0, to->getField("enabled")->getIncomingRoutes().size());
}

TEST(RouteStorage, InsertRouteShouldRelistRoute) {
    Node* from = browser()->createNode("TimeSensor");
    Node* to = browser()->createNode("TimeSensor");
    Route* route = browser()->createRoute(from, "loop_changed", to, "set_enabled");
    ASSERT_THAT(route, NotNull());
    route->remove();
    route->insert();
    EXPECT_EQ(route, from->getField("loop")->getOutgoingRoutes().front());
    EXPECT_EQ(route, from->getField("loop")->getOutgoingRoutes().back());
    EXPECT_EQ(route, to->getField("enabled")->getIncomingRoutes().front());
    EXPECT_EQ(route, to->getField("enabled")->getIncomingRoutes().back());
}

TEST(RouteStorage, InsertShouldFailIfRouteExists) {
    Node* from = browser()->createNode("TimeSensor");
    Node* to = browser()->createNode("TimeSensor");
    Route* route = browser()->createRoute(from, "loop_changed", to, "set_enabled");
    ASSERT_THAT(route, NotNull());
    route->remove();
    Route* other = browser()->createRoute(from, "loop_changed", to, "set_enabled");
    EXPECT_ANY_THROW(route->insert());
}

TEST(RouteStorage, CreateIdenticalRouteShouldReturnOriginalPtr) {
    Node* from = browser()->createNode("TimeSensor");
    Node* to = browser()->createNode("TimeSensor");
    Route* route = browser()->createRoute(from, "loop_changed", to, "set_enabled");
    ASSERT_THAT(route, NotNull());
    EXPECT_EQ(route, browser()->createRoute(from, "loop_changed", to, "set_enabled"));
}


//Tests for checkers program
//Uses catch framework.
//
//In order to add/ modify tests,
//simply write
//		TEST_CASE(" description ", "[ Test Category ]")
//		{
//			//code to be tested
//		}
//
//Inside of test case, use
//			INFO("description");
//to give user description of current subtest. Use
//			REQUIRE( some boolean );
//fo actual condition being tested.

#define CATCH_CONFIG_FAST_COMPILE
# define M_PI  3.14159265358979323846

#include "catch.hpp"
#include "../shape.hpp"

#include <memory>
#include <utility>
#include <initializer_list>

TEST_CASE("Fail construction", "[construction]")
{

}

TEST_CASE("Circle set/get", "[set/get]")
{
	INFO("Constructor creation");
	auto circle = std::make_unique<Circle>(5.0);
	REQUIRE(circle->get_height() == 10.0);
	REQUIRE(circle->get_width() == 10.0);

	INFO("Set height");
	circle->set_height(50.0);
	REQUIRE(circle->get_height() == 50.0);
	REQUIRE(circle->get_width() == 10.0);

	INFO("Set width");
	circle->set_width(100.0);
	REQUIRE(circle->get_height() == 50.0);
	REQUIRE(circle->get_width() == 100.0);
}

TEST_CASE("Rectangle set/get", "[set/get]")
{
	INFO("Constructor creation");
	auto rect = std::make_unique<Rectangle>(10.0, 15.0);
	REQUIRE(rect->get_width() == 10.0);
	REQUIRE(rect->get_height() == 15.0);

	INFO("Set height");
	rect->set_height(50.0);
	REQUIRE(rect->get_width() == 10.0);
	REQUIRE(rect->get_height() == 50.0);

	INFO("Set width");
	rect->set_width(100.0);
	REQUIRE(rect->get_width() == 100.0);
	REQUIRE(rect->get_height() == 50.0);
}

TEST_CASE("Spacer set/get", "[set/get]")
{
	INFO("Constructor creation");
	auto space = std::make_unique<Spacer>(50.0, 50.0);
	REQUIRE(space->get_width() == 50.0);
	REQUIRE(space->get_height() == 50.0);

	INFO("Set height");
	space->set_height(200.0);
	REQUIRE(space->get_width() == 50.0);
	REQUIRE(space->get_height() == 200.0);

	INFO("Set width");
	space->set_width(100.0);
	REQUIRE(space->get_width() == 100.0);
	REQUIRE(space->get_height() == 200.0);
}

TEST_CASE("Square set/get", "[set/get]")
{
	INFO("Constructor creation");
	auto square = std::make_unique<Square>(50.0);
	square->set_width(50.0); //Remove
	square->set_height(50.0); //Remove
	REQUIRE(square->get_width() == 50.0);
	REQUIRE(square->get_height() == 50.0);

	INFO("Set height");
	square->set_height(200.0);
	square->set_width(200.0); //Remove
	REQUIRE(square->get_width() == 200.0);
	REQUIRE(square->get_height() == 200.0);

	INFO("Set width");
	square->set_width(100.0);
	square->set_height(100.0); //Remove
	REQUIRE(square->get_width() == 100.0);
	REQUIRE(square->get_height() == 100.0);
}

TEST_CASE("Triangle set/get", "[set/get]")
{
	const auto side_length = 50.0;
	const auto num_sides = 3;
	const auto cos_part = std::cos(M_PI / double(3));
	const auto sin_part = std::sin(M_PI / double(3));
	const auto height = side_length*(1 + cos_part) / (2 * sin_part);
	const auto width = (side_length * std::sin(M_PI* (num_sides - 1) / double(2 * num_sides))) / (sin_part);

	INFO("Constructor creation");
	auto tri = std::make_unique<Triangle>(50.0);
	REQUIRE(tri->get_width() == width);
	REQUIRE(tri->get_height() == height);

	INFO("Set height");
	tri->set_height(200.0);
	REQUIRE(tri->get_width() == width);
	REQUIRE(tri->get_height() == 200.0);

	INFO("Set width");
	tri->set_width(100.0);
	REQUIRE(tri->get_width() == 100.0);
	REQUIRE(tri->get_height() == 200.0);
}

TEST_CASE("Rotated set/get", "[set/get]")
{
	auto rect = std::make_unique<Rectangle>(100.0, 200.0);

	INFO("Constructor creation");
	auto rot0 = std::make_unique<Rotated>(std::move(rect), Rotated::QUARTER);
	REQUIRE(rot0->get_width() == 200.0);
	REQUIRE(rot0->get_height() == 100.0);

	INFO("Set height");
	rot0->set_height(300.0);
	REQUIRE(rot0->get_width() == 200.0);
	REQUIRE(rot0->get_height() == 300.0);

	INFO("Set width");
	rot0->set_width(40.0);
	REQUIRE(rot0->get_width() == 40.0);
	REQUIRE(rot0->get_height() == 300.0);

	INFO("Rotate after set_height and set_width with constructor");
	auto rot1 = std::make_unique<Rotated>(std::move(rot0), Rotated::QUARTER);
	REQUIRE(rot1->get_width() == 300.0);
	REQUIRE(rot1->get_height() == 40.0);
}

TEST_CASE("Scaled set/get", "[set/get]")
{
	auto rect0 = std::make_unique<Rectangle>(100.0, 200.0);
	auto rect1 = std::make_unique<Rectangle>(100.0, 200.0);

	INFO("Constructor creation 10 times width and height");
	auto scale0 = std::make_unique<Scaled>(std::move(rect0), 10, 10);
	REQUIRE(scale0->get_width() == 1000.0);
	REQUIRE(scale0->get_height() == 2000.0);

	INFO("Constructor creation 0.5 times width and height");
	auto scale1 = std::make_unique<Scaled>(std::move(rect1), 0.5, 0.5);
	REQUIRE(scale1->get_width() == 50.0);
	REQUIRE(scale1->get_height() == 100.0);

	INFO("Set height");
	scale1->set_height(200.0);
	REQUIRE(scale1->get_width() == 50.0);
	REQUIRE(scale1->get_height() == 200.0);

	INFO("Set width");
	scale1->set_width(200.0);
	REQUIRE(scale1->get_width() == 200.0);
	REQUIRE(scale1->get_height() == 200.0);
}

TEST_CASE("Layered set/get", "[set/get]")
{
	auto rect0 = std::make_unique<Rectangle>(100.0, 200.0);
	auto rect1 = std::make_unique<Rectangle>(200.0, 100.0);
	std::initializer_list<std::shared_ptr<Shape>> list0 = { std::move(rect0), std::move(rect1) };

	INFO("Constructor creation with double overlapping rectangles");
	auto lay0 = std::make_unique<Layered>(list0);
	REQUIRE(lay0->get_width() == 200.0);
	REQUIRE(lay0->get_height() == 200.0);

	auto rect2 = std::make_unique<Rectangle>(400.0, 100.0);
	auto circle0 = std::make_unique<Circle>(150.0);
	std::initializer_list<std::shared_ptr<Shape>> list1 = { std::move(rect2), std::move(circle0) };

	INFO("Constructor creation with circle overlapping square");
	auto lay1 = std::make_unique<Layered>(list1);
	REQUIRE(lay1->get_width() == 400.0);
	REQUIRE(lay1->get_height() == 300.0);

	INFO("Set height");
	lay1->set_height(200.0);
	REQUIRE(lay1->get_width() == 400.0);
	REQUIRE(lay1->get_height() == 200.0);

	INFO("Set width");
	lay1->set_width(1200.0);
	REQUIRE(lay1->get_width() == 1200.0);
	REQUIRE(lay1->get_height() == 200.0);
}

TEST_CASE("Vertical set/get", "[set/get]")
{
	auto circle = std::make_unique<Circle>(3.);
	auto rectangle = std::make_unique<Rectangle>(40,50);
	auto spacer = std::make_unique<Spacer>(100,100);
	auto test_verticle = std::make_unique<Virtical>(std::initializer_list<std::shared_ptr<Shape>>{std::move(circle), std::move(spacer), std::move(rectangle)});
	REQUIRE(test_verticle->get_height() == 156.0);
}

TEST_CASE("Horizontal set/get", "[set/get]")
{
	auto circle = std::make_unique<Circle>(3.);
	auto rectangle = std::make_unique<Rectangle>(40,50);
	auto spacer = std::make_unique<Spacer>(100,100);
	auto test_horizontal = std::make_unique<Horizontal>(std::initializer_list<std::shared_ptr<Shape>>{std::move(circle), std::move(spacer), std::move(rectangle)});
	REQUIRE(test_horizontal->get_width() == 146.0);
}

TEST_CASE("Layered Rotated set/get", "[set/get]")
{
	auto rect0 = std::make_unique<Rectangle>(100.0, 200.0);
	auto rect1 = std::make_unique<Rectangle>(200.0, 100.0);
	std::initializer_list<std::shared_ptr<Shape>> list0 = { std::move(rect0), std::move(rect1) };
	auto lay0 = std::make_unique<Layered>(list0);

	auto spacer = std::make_unique<Spacer>(100,100);

	auto square0 = std::make_unique<Square>(100.0);
	auto square1 = std::make_unique<Square>(200.0);
	std::initializer_list<std::shared_ptr<Shape>> list1 = { std::move(square0), std::move(square1) };
	auto lay1 = std::make_unique<Layered>(list0);

	auto test_layered_rot = std::make_unique<Layered>(std::initializer_list<std::shared_ptr<Shape>>{std::move(lay0), std::move(spacer), std::move(lay1)});
	REQUIRE(test_layered_rot->get_width() == 200.0);
	REQUIRE(test_layered_rot->get_height() == 200.0);
}

TEST_CASE("Vertical Rotated set/get", "[set/get]")
{
	auto square = std::make_unique<Square>(50.0);
	auto rectangle = std::make_unique<Rectangle>(40,50);
	auto spacer = std::make_unique<Spacer>(100,100);

	auto rotated_rectangle = std::make_unique<Rotated>(std::move(rectangle), Rotated::QUARTER);
	auto rotated_square = std::make_unique<Rotated>(std::move(square), Rotated::QUARTER);

	auto test_verticle_rotated = std::make_unique<Virtical>(std::initializer_list<std::shared_ptr<Shape>>{std::move(rotated_square), std::move(spacer), std::move(rotated_rectangle)});
	REQUIRE(test_verticle_rotated->get_height() == 190.0);
}

TEST_CASE("Horizontal Rotated set/get", "[set/get]")
{
	auto square = std::make_unique<Square>(50.0);
	auto rectangle = std::make_unique<Rectangle>(40,50);

	auto spacer = std::make_unique<Spacer>(100,100);

	auto rotated_rectangle = std::make_unique<Rotated>(std::move(rectangle), Rotated::QUARTER);
	auto rotated_square = std::make_unique<Rotated>(std::move(square), Rotated::QUARTER);

	auto test_verticle_rotated = std::make_unique<Horizontal>(std::initializer_list<std::shared_ptr<Shape>>{std::move(rotated_square), std::move(spacer), std::move(rotated_rectangle)});
	REQUIRE(test_verticle_rotated->get_width() == 200.0);
}

TEST_CASE("Layered Scaled set/get", "[set/get]")
{
	auto rect0 = std::make_unique<Rectangle>(100.0, 200.0);
	auto rect1 = std::make_unique<Rectangle>(200.0, 100.0);

	auto scale_rect_0 = std::make_unique<Scaled>(std::move(rect0), 10, 10);
	auto scale_rect_1 = std::make_unique<Scaled>(std::move(rect1), 10, 10);

	std::initializer_list<std::shared_ptr<Shape>> list0 = { std::move(scale_rect_0), std::move(scale_rect_1) };
	auto lay0 = std::make_unique<Layered>(list0);

	REQUIRE(lay0->get_width() == 2000.0);
	REQUIRE(lay0->get_height() == 2000.0);
}

TEST_CASE("Vertical Scaled set/get", "[set/get]")
{
	auto rect0 = std::make_unique<Rectangle>(100.0, 200.0);
	auto scale_rect_0 = std::make_unique<Scaled>(std::move(rect0), 10, 10);
	auto rect1 = std::make_unique<Rectangle>(200.0, 100.0);
	auto scale_rect_1 = std::make_unique<Scaled>(std::move(rect1), 10, 10);

	auto test_verticle_scaled = std::make_unique<Virtical>(std::initializer_list<std::shared_ptr<Shape>>{std::move(scale_rect_0), std::move(scale_rect_1)});

	REQUIRE(test_verticle_scaled->get_height() == 3000.0);
}

TEST_CASE("Horizontal Scaled set/get", "[set/get]")
{
	auto rect0 = std::make_unique<Rectangle>(100.0, 200.0);
	auto scale_rect_0 = std::make_unique<Scaled>(std::move(rect0), 10, 10);
	auto rect1 = std::make_unique<Rectangle>(200.0, 100.0);
	auto scale_rect_1 = std::make_unique<Scaled>(std::move(rect1), 10, 10);

	auto test_verticle_scaled = std::make_unique<Horizontal>(std::initializer_list<std::shared_ptr<Shape>>{std::move(scale_rect_0), std::move(scale_rect_1)});

	REQUIRE(test_verticle_scaled->get_height() == 2000.0);
}

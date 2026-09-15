#pragma warning(disable : 4251)

#include <PMMA.hpp>
#include <vector>
#include <random>
#include <chrono>
#include <iostream>
#include <execution>
#include <algorithm>

using namespace std;

int main() {
	string path = "A://GitHub//PMMA//pmma";

	PMMA::Initialize(path);

	PMMA::Display* display = new PMMA::Display();
	uint16_t size[2] = { 1280, 720 };
	display->Create(size, { .Vsync = true });

	std::vector<PMMA::Rendering::TwoD::Shapes::Circle> shapes(100'000);

	// Parallel loop to bypass sequential CPU bottlenecks
	for (int i = 0; i < 100'000; i++) {
		shapes[i].ShapeCenter.GenerateFromRandom();
		shapes[i].Color.GenerateFromRandom();
		shapes[i].ShapeSize.SetRadius(50);
	};

	while (PMMA::General::IsApplicationRunning()) {
		display->Clear();

		for (auto& shape : shapes) {
			shape.Color.GenerateFromRandom();
			shape.Render();
		}

		display->Refresh({ .LimitRefreshRate = false });
	}

	PMMA::Uninitialize();
	return 0;
} // 134 FPS AVG
#include <fstream>
#include <fmt/ostream.h>

#include "integration.hpp"
#include "solution.hpp"
#include "tools.hpp"

int main() {

    const std::string pathToData = "/home/ds/science/2003_302_1/";
    const std::string pathToProcessedData = pathToData + "tec_processed_model/";

    ChepmanLayer chepmanLayer;

    chepmanLayer.add_spot(point(30, 55), 12, pi / 24, 150, 0.5f);
    chepmanLayer.add_spot(point(2.5, 45), 12, pi / 6, 300, 0.2f);
    chepmanLayer.add_spot(point(12, 40), 12, pi / 4, 300, 0.2f);

    chepmanLayer.add_wave(point(10, 40, Re), 32400, 1500, 0.3f); // 25 minutes
    chepmanLayer.add_wave(point(20, 60, Re), 54000, 2100, 0.3f); // 35 minutes
    chepmanLayer.add_wave(point(10, 40, Re), 32400, 1800, 0.3f); // 20 minutes

    const unsigned time_start = 0;
    const unsigned time_finish = 24;

    chepmanLayer.coordinateTransformation = std::make_unique<DecartToGeographic>();
    auto data = get_data(pathToData, time_start, time_finish);
    const auto stations = get_stations(data);

    std::ofstream station_file(pathToProcessedData + "stations_check.txt");
    for (const auto &[lat, lon] : stations) {
        fmt::print(station_file, "{:.2f} {:.2f}\n", radian_to_degree(lat), radian_to_degree(lon));
    }
    station_file.close();

    Rectangle integral;
    for (auto &i : data) {
        for (auto &j : i) {
            j.integral = integral(j, chepmanLayer);
        }
    }

    Sirt solver;
    Solution solution;
    solution.set_limits(-10.0f, 40.0f, 30.0f, 70.0f, time_start, time_finish);
    solution.add_data(std::move(data));
    solution.add_grid(8, 24);
    solution.add_grid(36, 240);
    solution.find(solver);
    solution.print(pathToProcessedData);

    return 0;
}

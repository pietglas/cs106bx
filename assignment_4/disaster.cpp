#include <iostream>
#include <set>
#include <string>
#include <map>

using std::string;
using std::set;
using std::map;
using std::cout;
using std::endl;

using map_network = map<string, set<string>>;

set<string> SafeCities(const map_network& network, set<string>& cities_without_recourses,
                       set<string>& unsafe_cities, int nr_recources) {
    if (nr_recources == 0)
        return safe_cities;
    else {
        // Determine which cities without recourses are connected to the
        // highest number of currently unsafe cities
        map<string, int> network_unsafe;
        for (auto& city : cities_without_recourses) {
            set<string> reachable_cities = network.at(city);
            int unsafe_reachable_cities = 0;
            for (auto& reachable_city : reachable_cities) {
                if (unsafe_cities.find(reachable_city) != unsafe_cities.end())
                    ++unsafe_reachable_cities;
            }
            if (unsafe_reachable_cities == network_unsafe.begin()->second) {
                network_unsafe.emplace(city, unsafe_reachable_cities);
            }
            else if (unsafe_reachable_cities > network_unsafe.begin()->second)
                network_unsafe.clear();
                network_unsafe.emplace(city, unsafe_reachable_cities);
            }
            else
                continue;
        }
        // proceed the recusion with backtracking on the cities determined in the
        // previous part.
        for (auto& city_indexed : network_unsafe) {
            string city = city_indexed.first;
            cities_without_recourses.erase(city);
            for (auto& connected_city : network.at(city)) {
                unsafe_cities.erase(connected_city);
            }
            return SafeCities(network, cities_without_recourses,
                              unsafe_cities, nr_recources - 1);
        }
    }
}

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

int & SafeCities(const map_network & network, set<string> & cities_without_recourses,
                       set<string> & unsafe_cities, int nr_recources, 
                       int & min_unsafe_cities) {
    
    if (nr_recources == 0)
        min_unsafe_cities = unsafe_cities.size();
    else if (nr_recources > 0 && unsafe_cities.size() == 0)
        min_unsafe_cities = 0;
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
            else if (unsafe_reachable_cities > network_unsafe.begin()->second) {
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
            
            set<string> removed_cities;
            for (auto& connected_city : network.at(city)) {
                size_t removed = unsafe_cities.erase(connected_city);
                if (removed)
                   removed_cities.insert(connected_city); 
            }
            SafeCities(network, cities_without_recourses,
                              unsafe_cities, nr_recources - 1);
            
            // do the backtracking
            for (auto& removed_city : removed_cities) 
                unsafe_cities.insert(removed_city);
            cities_without_recourses.insert(city);
        }
    }
    return min_unsafe_cities;
}

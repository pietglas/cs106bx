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


//// returns the minimum number of unsafe cities, given a network of cities and a fixed
//// amount of resources
int SafeCities(const map_network & network, set<string> & cities_without_recourses,
                       set<string> & unsafe_cities, int nr_recources, 
                       set<int> & min_unsafe_cities) {
    
    if (nr_recources == 0)
        min_unsafe_cities.insert(unsafe_cities.size());
    else if (nr_recources > 0 && unsafe_cities.size() == 0)
        return 0;
    else {
        //// Define a map that contains as keys the cities without recourses,
        //// and keys the number of unsafe cities to which they are connected
        map<string, int> network_unsafe;

        for (auto& city : cities_without_recourses) {
            set<string> reachable_cities = network.at(city);
            int unsafe_reachable_cities = 0;
            for (auto& reachable_city : reachable_cities) {
                if (unsafe_cities.find(reachable_city) != unsafe_cities.end())
                    ++unsafe_reachable_cities;
            }
            //   if the city itself isn't safe, it should count too
            if (unsafe_cities.find(city) != unsafe_cities.end())
                ++unsafe_reachable_cities;

            //   only add those cities connected to the highest number of unsafe cities
            if (network_unsafe.size() == 0 || 
                unsafe_reachable_cities == network_unsafe.begin()->second) {
                network_unsafe.emplace(city, unsafe_reachable_cities);
            }
            else if (unsafe_reachable_cities > network_unsafe.begin()->second) {
                network_unsafe.clear();
                network_unsafe.emplace(city, unsafe_reachable_cities);
            }
            else
                continue;
        }

        // cout << "cities connected to highest amount of unsafe cities: " << endl;
        // for (auto& pair : network_unsafe) 
        //     cout << pair.first << " ";
        // cout << endl << endl;

        //// recusively provide resources to the cities connnected to the highest amount
        //// of unsafe cities. Do backtracking, in case there are several cities connected
        //// to an equally high amount. 
        for (auto& city_indexed : network_unsafe) {
            string city = city_indexed.first;
            // cout << city << " is connected to " << city_indexed.second 
            //     << " unsafe cities" << endl;
            cities_without_recourses.erase(city);
            
            //// keep track of the cities that become safe after providing new
            //// resources, in able to do the backtracking
            set<string> removed_cities;
            size_t removed_this_city = unsafe_cities.erase(city);
            if (removed_this_city)
                removed_cities.insert(city);
            for (auto& connected_city : network.at(city)) {
                size_t removed = unsafe_cities.erase(connected_city);
                if (removed)
                   removed_cities.insert(connected_city); 
            }
            //// do the recursion
            SafeCities(network, cities_without_recourses,
                       unsafe_cities, nr_recources - 1, min_unsafe_cities);
            
            //// do the backtracking
            for (auto& removed_city : removed_cities) 
                unsafe_cities.insert(removed_city);
            cities_without_recourses.insert(city);
        }
    }
    return *(min_unsafe_cities.begin());
}

int HowManyRecoursesForSafeNetwork(const map_network & network) {
    set<string> cities_without_recourses, unsafe_cities;
    for (const auto & connected_cities : network) {
        cities_without_recourses.insert(connected_cities.first);
        unsafe_cities.insert(connected_cities.first);
    }
    set<int> min_unsafe_cities;
    int nr_recources = 0;
    while(SafeCities(network, cities_without_recourses, unsafe_cities,
            nr_recources, min_unsafe_cities) != 0)
        ++nr_recources;
    return nr_recources;
}

int main() {
    map_network network = {
        {"groningen", set<string>{"leeuwarden", "assen"}}, 
        {"leeuwarden" , set<string>{"groningen", "zwolle"}},
        {"assen", set<string>{"groningen", "zwolle"}},
        {"zwolle", set<string>{"assen", "leeuwarden"}}
    };

    // set<string> cities_without_recourses{"groningen", "leeuwarden", "assen", "zwolle"};
    // set<string> unsafe_cities = cities_without_recourses;
    // set<int> min_unsafe_cities;

    // int nr_recources = 2;
    // int min_nr_unsafe_cities = SafeCities(network, cities_without_recourses,
    //                                 unsafe_cities, nr_recources, min_unsafe_cities);

    // cout << "Minimum number of unsafe cities with " 
    //     << nr_recources << " recourses: " << min_nr_unsafe_cities << endl;

    int min_nr_resources = HowManyRecoursesForSafeNetwork(network);

    cout << "We need to provide " << min_nr_resources << " cities with resources";

}

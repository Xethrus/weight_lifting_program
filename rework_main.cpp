#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>
#include <fstream>
#include <map>
#include "vendor/nlohmann/json.hpp"
using json = nlohmann::json;

const float TR_FACTOR = 0.75;

std::map<std::string, std::map<std::string, float>> globalMap;
std::map<std::string, std::string> weightTypes;

void fillNameWorkout (json& parsedUserData) {
  std::map<std::string, float> placeHolderMap;
  for(auto& [name, value] : parsedUserData["one_rep_maxes"].items()) {
    placeHolderMap.clear();  
    for(auto& [workout, weight] : value.items()) {
      placeHolderMap.insert({workout, weight});
    }
    globalMap.insert({name, workoutWeight});
  }
}

std::string findWeightType (json& parsedUserData,
      std::string workoutName) {
  return parsedUserData["weight_type"[workoutName]]
}

class config {
  private:

    std::string username;
    
    std::map<std::string, float> workoutWeight;

  public: 

    void fillPersonalInfo(std::string name, std::map<std::string,
        std::map<std::string, float>> fullMap) {
        username = name;         
        for(auto& [workout, weight] : fullMap[name]) {
          workoutWeight.insert({workout, weight});
        }  
      }
    }
};

int main() {

  std::ifstream json("weight_lifting_profile.json"); 
   
}

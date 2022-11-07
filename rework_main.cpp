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

class config {
  private:

    std::map<std::string, std::map<std::string, float>> mapWithNestedMap;
    
    std::string name;
    
    std::map<std::string, float> workoutWeight;

  public: 

    void fillNameWorkout (json& parsedUserData) {
      for(auto& [name, value] : parsedUserData["one_rep_maxes"].items()) {
        workoutWeight.clear();  
        for(auto& [workout, weight] : value.items()) {
          workoutWeight.insert({workout, weight});
        }
        mapWithNestedMap.insert({name, workoutWeight});
      }
    }
    void fillPersonalMap(std::string name) {
      for(auto& [workout weight] : mapWithNestedMap[name]) {
        
      }
    }
};

int main() {

  std::ifstream json("weight_lifting_profile.json"); 
   
}

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
  for(auto& [workout, weightType] : ["weight_type"].items()) {
    weightType.insert({workout, weightType});   
  }
}

std::vector<int> freeWeightPlateSelector(float targetWeight) {
  std::vector<int> usedPlates;
  int currentWeight = 0;
  int platesAvaliable1[] = {45,35,25,10,5};
  
  for (const auto weight : plateWeights) {
    while(currentWeight + weight <= targetWeight) {
      usedPlates.push_back(weight);
      currentWeight += weight;
    }
  } 
  //std::cout << "achievable: " << currentWeight << std::endl;
  return usedPlates;
}

int machineWeightSelector(float targetWeight) {
  int machineWeight[] = {
    10, 20, 30, 40, 50,
    60, 70, 80, 90, 100,
    110, 120, 130, 140, 150,
    160, 170, 180, 190, 200};

  int currentWeight = 0;
 
  for(const auto weight : machineWeight) {
    while(weight <= targetWeight) {
      currentWeight += weight;
    }
  } 
  return currentWeight;
}

void chooseSelector(std::string workoutName) {
  if(weightTypes[workoutName] == "free_weight") {
    //do something

  } else {
    //do something else
  } 
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

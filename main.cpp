#include <string>
#include <iostream>
#include <vector>
#include "vendor/nlohmann/json.hpp"
#include <fstream>
#include <map>
using json = nlohmann::json;

const float TR_FACTOR = .75;

struct UserInfo {
	std::map<std::string, float> userMap;
	float ormBenchPress;
	//float ormLatPullDown;
	//float ormBicepCurl;	
	float tenRepMax(float orm){
		float tenRep =0;
		std::cout << "orm is: " << orm << std::endl;
		tenRep = orm * TR_FACTOR;  
		return tenRep; 
	}
};
class UserProfile {
public:
	std::map<std::string, float> workoutMap;
	std::map<std::string, std::map<std::string, float>> nestingUserMap;	
	std::map<std::string, float> fillWorkoutMap(json& parsedUserData) {
		std::cout << "hello" << std::endl;
		std::cout << parsedUserData["one_rep_maxes"].items() << std::endl;//this is not getting data-not passing in data
		for(auto& [onerepmax, name] : parsedUserData["one_rep_maxes"].items()) {	
			for(auto& [workout, weight] : name.items()) {
				std::cout << "workout: " << workout << ", weight: " << weight << std::endl;
				workoutMap.insert({workout, weight});
			}
			nestingUserMap.insert({name, workoutMap});
		}
		return workoutMap; //not neccessary i dont think lol
	}
	bool testMapForContent(std::map<std::string, std::map<std::string, float>>) {
		for(auto [key, value] : nestingUserMap) {
			std::cout << key << std::endl; 
		}
	}

	//def doesnt work lol
	void displayUserWorkout() {
		std::cout << "function reached- displayUW" << std::endl;//reached
		for(auto& [name, map] : nestingUserMap) {
			std::cout << "reached inside for DUW" << std::endl; //not reached
			std::cout << "for user: " << name << std::endl;
			for(auto& [workout, weight] : workoutMap) {
				std::cout << "The workout is: " << workout << std::endl;
				std::cout << "weight is: " << weight << std::endl;
			}
		}
	};
};
int machineWeightSelector(int targetWeight) {
	int machineWeight[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120,
		130, 140, 150, 160, 170, 180, 190, 200};
	std::cout << "target Weight: " << targetWeight << std::endl;
	int currentWeight = 0;
	for (const auto weight : machineWeight) {
		while(weight <= targetWeight) {
			currentWeight += weight;
		}
	}
	//std::cout << "achievable weight machine weight: " << std::endl;
	return currentWeight;
}
std::vector<int> freePlateSelector(float targetWeight) {
	std::vector<int> usedWeights;	
	int currentWeight = 0;
	std::cout << "targeteWeight: " << targetWeight << std::endl;
	int plateWeights[] = {45, 35, 25, 10, 5};
	for (const auto weight : plateWeights){
		while(currentWeight + weight <= targetWeight){
			usedWeights.push_back(weight);
			currentWeight += weight;
		}
	}
	std::cout << "Achievable Weight Was: " << currentWeight << std::endl;
	float remainderWeight = targetWeight - currentWeight;
	std::cout << "Remainder of Weight Was: " << remainderWeight << std::endl;
	for(auto element : usedWeights) {
		std::cout << "plate: " << element << std::endl;
	}
	return usedWeights;
}

std::vector<float> basicPercGen(float oneRepMax){
	float ninetyPerc = .90;
	float seventyPerc = .70;
	float fiftyPerc = .50;
	std::vector<float> percWeight;
	percWeight.push_back(ninetyPerc*oneRepMax);
	percWeight.push_back(seventyPerc*oneRepMax);
	percWeight.push_back(fiftyPerc*oneRepMax);
	return percWeight;
}
void percReader(float oneRepMax) {
	std::vector<float> readPercWeight;
	for(int i = 0; i < basicPercGen(oneRepMax).size(); i++){
		readPercWeight.push_back(basicPercGen(oneRepMax)[i]);
	}
	for(auto element : readPercWeight) {
		std::cout << "diff percentage weight: " << 
			element << std::endl;
		freePlateSelector(element);
	}

}
std::map<std::string, float> generateUserMap(json userData){
	for(const auto& [key, value] : userData["one_rep_maxes"].items()) {
		std::cout << key << " and value: " << value << std::endl;
		for(const auto& [key2, value2] : value.items()) {
			std::cout << key2 << " and value:" << value2 << std::endl;
		}
	}

	std::cout << "print statement" << std::endl;
	std::map<std::string, float> theMap;
	return theMap;
}
//make map for each person, meaning "Stevie" will have a map with his workouts and weights key - value
int main(int argc, char *argv[]) {

	UserProfile everyone;
	std::ifstream i("weight_lifting_profile.json");
	json j;
	i >> j;
	everyone.fillWorkoutMap(j);
	everyone.displayUserWorkout();
};

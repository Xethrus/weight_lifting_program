#include <typeinfo>
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
	void fillWorkoutMap(json& parsedUserData) {
		for(auto& [name, value] : parsedUserData["one_rep_maxes"].items()) {	
			workoutMap.clear();
			for(auto& [workout, weight] : value.items()) {
				workoutMap.insert({workout, weight});
			}
			nestingUserMap.insert({name, workoutMap}); // tjis doesnt work unmatching pair
		}
		for(auto [key, value] : workoutMap) {
			std::cout << "the value: " << value << std::endl;
		}
	}
	bool testMapForContent(std::map<std::string, std::map<std::string, float>>) {
		for(auto [key, value] : nestingUserMap) {
			std::cout << " the key value: " << key << std::endl; 
		}
	}
	void displayUserWorkout() {
		for(auto& [name, map] : nestingUserMap) {
			std::cout << "for user: " << name << std::endl;
			for(auto& [workout, weight] : map) {
				std::cout << "The workout is: " << workout << std::endl;
				std::cout << "weight is: " << weight << std::endl;
			}
		}
	};
	float tenRepMax(float orm){
		float tenRep =0;
		tenRep = orm * TR_FACTOR;  
		return tenRep; 
	}
	void displayUserTRM(std::string userName) {
		for(auto& [workout, weight] : nestingUserMap[userName]) {
			std::cout << "for workout: " << workout << std::endl;
			tenRepMax(static_cast<float>(weight));
			std::cout << "the ten rep max is: " <<  
			tenRepMax(static_cast<float>(weight)) << std::endl;
				
		}

	}

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

int main(int argc, char *argv[]) {

	UserProfile user1;
	UserProfile user2;
	std::ifstream i("weight_lifting_profile.json");
	json j;
	i >> j;
	user1.fillWorkoutMap(j);
	user1.displayUserWorkout();
	user1.displayUserTRM("Stevie");
	user1.displayUserTRM("Jay");
};

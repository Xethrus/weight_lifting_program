#include <iostream>
#include <vector>
#include "vendor/nlohmann/json.hpp"
#include <fstream>
using json = nlohmann::json;

const float TR_FACTOR = .75;

struct UserInfo {
	float ormBenchPress;
	
	float benchPressTRM(){
		float TenRepBench =0;
		std::cout << "orm is: " << ormBenchPress << std::endl;
		TenRepBench = ormBenchPress * TR_FACTOR;  
		return TenRepBench; 
	}

};
class User {
private:
	float ormBenchPress;
	float ormLatPullDown;
	float ormDumbelCurl;	
public;
//not sure what I want to do with this yet
}
bool testExpected(float trm, float expected) {
	if(trm != expected) {
		std::cerr << "failure: unexpected value for calculation"
			<< std::endl;
		std::cout << "expected, " << expected << ". recieved, " << trm << "." << std::endl; 
		return false;
	}
	return true;
}
bool testExpectedPlates(std::vector<int> usedWeights, std::vector<int> expectedWeights) {
	if (usedWeights.size() != expectedWeights.size()) {
		std::cerr<< "unmatching vector size" << std::endl;
	}	
	for(int i =0; i < usedWeights.size(); i++) {
		if(usedWeights[i] != expectedWeights[i]) {
			std::cerr << "unmatching vector element, expected: " << expectedWeights[i] << ", but recieved:"
				<< usedWeights[i] << std::endl;
			return false;
		}	
	}	
	return true;
}

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
	std::cout << "achievable weight machine weight: " << std::endl;
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
int main(int argc, char *argv[]) {

	std::ifstream f("weight_lifting_profile.json");
	json userData = json::parse(f);
	UserInfo userProfile1;
	userProfile1.ormBenchPress = userData["one_rep_maxes"]["Stevie"]["bench_press"];
	std::cout << userProfile1.ormBenchPress << std::endl;
}

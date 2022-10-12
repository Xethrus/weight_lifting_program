#include <iostream>
#include <vector>
const float TRB_FACTOR = .75;

struct UserInfo {
	float ormBenchPress;
	
	float benchPressTRM(){
		float TenRepBench =0;
		std::cout << "orm is: " << ormBenchPress << std::endl;
		TenRepBench = ormBenchPress * TRB_FACTOR;  
		return TenRepBench; 
	}

};

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
std::vector<int> benchPlateSelector(float targetWeight) {
	std::vector<int> usedWeights;	
	int currentWeight = 0;
	std::cout << "targeteWeight: " << targetWeight << std::endl;
	//std::cout << "currentWeight: " << currentWeight << std::endl;
	int plateWeights[] = {45, 35, 25, 10, 5};
	for (const auto weight : plateWeights){
		while(currentWeight + weight <= targetWeight){
			usedWeights.push_back(weight);
			currentWeight += weight;
			//std::cout << "current weight: " << currentWeight << std::endl;
		}
	}
	std::cout << "Achievable Weight Was: " << currentWeight << std::endl;
	float remainderWeight = targetWeight - currentWeight;
	std::cout << "Remainder of Weight Was: " << remainderWeight << std::endl;
	for(auto element : usedWeights) {
		std::cout << "plate: " << element << std::endl;
	}// Issue with recognzing more than one plate in the plates used!!!!!
	return usedWeights;
}

std::vector<float> basicPercBenchGen(float oneRepMax){
	float ninetyPerc = .90;
	float seventyPerc = .70;
	float fiftyPerc = .50;
	std::vector<float> percWeight;
	percWeight.push_back(ninetyPerc*oneRepMax);
	percWeight.push_back(seventyPerc*oneRepMax);
	percWeight.push_back(fiftyPerc*oneRepMax);
	return percWeight;
}
void percBenchReader(float oneRepMax) {
	std::vector<float> readPercWeight;
	for(int i = 0; i < basicPercBenchGen(oneRepMax).size(); i++){
		readPercWeight.push_back(basicPercBenchGen(oneRepMax)[i]);
	}
	for(auto element : readPercWeight) {

		std::cout << "diff percentage weight: " << 
			element << std::endl;
		benchPlateSelector(element);
	}

}
int main(int argc, char *argv[]) {
	UserInfo userProfile1;
	UserInfo userProfile2;
	userProfile1.ormBenchPress = 185;
	userProfile2.ormBenchPress = 150;
	float expectedForPf2 = 112.5;
	//testExpected(userProfile2.benchPressTRM(),expectedForPf2);
	std::vector<int> expectedPlatesForPf2 = {45,45,45,10,5};
	benchPlateSelector(userProfile2.benchPressTRM());
	percBenchReader(userProfile2.ormBenchPress);
	//testExpectedPlates(benchPlateSelector(userProfile2.ormBenchPress), expectedPlatesForPf2);
}

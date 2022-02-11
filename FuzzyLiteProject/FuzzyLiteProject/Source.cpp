#include<iostream>
#include <fl/Headers.h>

using namespace fl;

int main()
{

	Engine* engine = new Engine();

	InputVariable* obstacle = new InputVariable;
	engine->addInputVariable(obstacle);

	obstacle->setName("obstacle");
	obstacle->setRange(0.000, 1.000);

	obstacle->addTerm(new Ramp("Left", 1.000, 0.000));
	obstacle->addTerm(new Ramp("Right", 0.000, 1.000));

	OutputVariable* msteer = new OutputVariable;
	engine->addOutputVariable(msteer);
	msteer->setName("mSteer");
	msteer->setRange(0.000, 1.000);
	msteer->setAggregation(new Maximum);
	msteer->setDefuzzifier(new Centroid(100));
	msteer->setDefaultValue(fl::nan);
	msteer->addTerm(new Ramp("Left", 1.000, 0.000));
	msteer->addTerm(new Ramp("Right", 0.000, 1.000));

	/*RuleBlock* mamdani = new RuleBlock;
	mamdani->setName("mamdani");
	mamdani->setConjunction(fl::null);
	mamdani->setDisjunction(fl::null);
	mamdani->setImplication(new AlgebraicProduct);
	mamdani->setActivation(new General);
	mamdani->addRule(Rule::parse("if obstacle is Left then mSteer is Right", engine));
	mamdani->addRule(Rule::parse("if obstacle is Right then mSteer is Left", engine));
	engine->addRuleBlock(mamdani);*/

	/*while (1)
	{
		std::string input = "";
		std::cin >> input;
		std::stringstream ss(input);
		float number = 0.f;
		ss >> number;
		obstacle->setValue(number);
		engine->process();
		std::cout << "obstacle.input = " << number <<" => steer.output = " << msteer->getValue() << std::endl;
	}*/
	




	//Week 2 Speed task
	InputVariable* speed = new InputVariable;
	engine->addInputVariable(speed);

	speed->setName("speed");
	speed->setRange(0.000, 1.000);

	speed->addTerm(new Ramp("Left", 1.000, 0.600));
	speed->addTerm(new Ramp("Right", 0.300, 1.000));
	speed->addTerm(new Triangle("none", 0.250, 0.750));

	OutputVariable* mspeedSteer = new OutputVariable;
	engine->addOutputVariable(mspeedSteer);
	mspeedSteer->setName("speedSteer");
	mspeedSteer->setRange(0.000, 1.000);
	mspeedSteer->setAggregation(new Maximum);
	mspeedSteer->setDefuzzifier(new Centroid(100));
	mspeedSteer->setDefaultValue(fl::nan);
	mspeedSteer->addTerm(new Ramp("Left", 1.000, 0.600));
	mspeedSteer->addTerm(new Ramp("Right", 0.300, 1.000));
	mspeedSteer->addTerm(new Triangle("none", 0.250, 0.750));

	RuleBlock* mamdani = new RuleBlock;
	mamdani->setName("mamdani");
	mamdani->setConjunction(new AlgebraicProduct);
	mamdani->setDisjunction(new Maximum);
	mamdani->setImplication(new AlgebraicProduct);
	mamdani->setActivation(new General);
	mamdani->addRule(Rule::parse("if obstacle is Left or speed is Left then mspeedSteer is Right", engine));
	mamdani->addRule(Rule::parse("if obstacle is Right or speed is Right then mspeedSteer is Left", engine));
	mamdani->addRule(Rule::parse("if obstacle is Right then mspeedSteer is Left", engine));
	engine->addRuleBlock(mamdani);

	while (1)
	{
		std::string input = "";
		std::cin >> input;
		std::stringstream ss(input);
		float number = 0.f;
		ss >> number;
		speed->setValue(number);
		engine->process();
		std::cout << "obstacle.input = " << number << " => steer.output = " << mspeedSteer->getValue() << std::endl;
	}

	delete engine;
	return 0;
}
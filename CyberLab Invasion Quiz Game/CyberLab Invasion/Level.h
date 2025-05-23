#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> // For sound effects
#include <vector>
#include <fstream>
#include <string>
#include "QuestionBank.h"
#include "Player.h"
#include "Button.h"
#include "ProgressBar.h"
#include "Loader.h"
#include "MessageBox.h"

//Question node
struct QuestionNode {
	std::string id;
	std::string title;
	std::string narrative;
	std::string question;
	std::string hint;
	std::vector<std::string> options;
	std::vector<std::string> nextIds;
	int correctIndex = -1;
};

//The Abstract Level class
class  Level {
private:
	//NEW
	std::unordered_map<std::string, QuestionNode> questionTree;
	std::string currentQuestionID;
	sf::View scrollView;   // For scrolling

public:
	Level();
	~Level();

    //Attributes of the progress bar
	ProgressBar progressBar;
	int currentLevelIndex = 0;
	static constexpr int TOTAL_LEVELS = 5;

	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;
	sf::Sprite avatar_sprite;

	sf::Texture hintTexture;
	sf::Sprite hintSprite;

	bool addedButton = false;
	bool needButton = true;
	bool moveToNextQuestion = false; //Used in processEvents to check if there is an option that has been selected nefore moving to the next question
	int count = 0; //counts the number of options displayed in the Level render method so we know if it is a true or false question
	int initialSkullColor = 0;  //To set the skull color to green when a level is to be started
	bool corr = true;

	void updateTexture() 
	{
		if (initialSkullColor < 1){ skullTexture.loadFromFile("Green_Skull.png");}
		else {
		
			if (corr) { skullTexture.loadFromFile("Green_Skull.png"); }
			else { skullTexture.loadFromFile("Red_Skull.png"); }
			skullSprite.setTexture(skullTexture);

		}
		initialSkullColor++;
	}

	std::string clickedButtonChar(Button& b)
	{
		return ((b.text).getString().toAnsiString());
	}

	Button exit;
	Button start;
	Button nextButton;
	Button* buttonA, * buttonB, * buttonC, * buttonD , *buttonHint;
	MessageBox hint;
	sf::Font nextFont;  //this is the font for the buttons because I cant't use the font defined in the level header file since my buttons need to be global


	std::string clickedCharAsString;
	bool getHome = false;
	bool nextLevelFeedBack1 = false;
	bool nextLevelFeedBack2 = false;
	bool nextLevelFeedBack3 = false;
	bool nextLevelHome = false;
	bool nextLevelPage = false;
	//bool nextLevelOnePage = false;
	//bool nextLevelTwoPage = false;
	//bool nextLevelThreePage = false;

	//int introLevelNum;
	virtual void handleEvent(const sf::Event& event) = 0; //To pass th
	virtual void setSprites() = 0;
	virtual void render();
	void gameSound(const string& gameSound);
	void update();
	void setAnimation(bool& condition);
	void processEvents();
	void pollEvents();
	void skipAnimation();
	bool displayStory = false;//when animating text to check which to be animated between narrativeStoryText(true) & questionText(false)

	//NEW
	int selectedIndex = -1; // Index of the selected option
	void showCurrentQuestion(); //navigate and show the current question
	void nextQuestionFromChoice(int selectedIndex); //Called when the player selects an option
	//END NEW


	//Function to load questions from a file
	void loadQuestionsFromFile(const std::string& filename, int level);

	//Structure to hold question outcome
	struct QuestionOutcome
	{
		std::string user_answer;
		std::string correct_answer;
		std::string question;

		bool isCorrect() const {
			return user_answer == correct_answer;
		}
	};

	//Function to get question outcome
	QuestionOutcome getQuestionOutcome(std::string ques, std::string user_ans, std::string correct_ans)
	{
		QuestionOutcome q;
		q.user_answer = user_ans;
		q.correct_answer = correct_ans;
		q.question = ques;
		q.isCorrect();

		return q;
	}

	//Question outcomes for each level
	static std::vector<QuestionOutcome> outcomes;

	//level one intro level one page
	std::string level;
	std::string intro1, intro2, intro3;
	//From LEVEL ONE!!!!

	sf::Font font;
	sf::Text narrativeText, text, questionText, option1Text, option2Text, option3Text, option4Text, narrativeStoryText;
	QuestionBank questionBank;
	int currentLevel = 1;
	//sf::RectangleShape rectangle;


	//Game sprite and texture was taken from game.cpp, which represented level three
	sf::Texture skullTexture, homeTexture, introTexture, levelpageTexture, GameTexture, backgroundTexture, textboxTexture, compTexture, serverTexture, avatarTexture;
	sf::Sprite  skullSprite, homeSprite, introSprite, LevelSprite, GameSprite, backgroundSprite, backgroundSprite2, textboxSprite, compSprite, Sprite, avatarSprite;

	std::vector<std::string> messages;
	sf::Vector2f rectangleSize;

	//Typing sound effect functionality
	std::string fullQuestionText;  // Stores the full question
	std::string displayedQuestionText; // Stores text being animated
	sf::Clock typingClock; // Controls the speed of typing effect
	sf::SoundBuffer typingSoundBuffer; // Buffer to store sound data
	sf::Sound typingSound; // Sound effect for typing
	bool isTyping = false; // Flag to check if animation is ongoing

	std::vector<std::string> currentOptions; // Stores options
	bool optionsDisplayed = false; // Flag to track when to display options

	inline void clearOptions(); //Clears the options 

	//Handling timer atributes
	sf::Text timerText;
	sf::Clock gameClock;
	sf::Clock pulseClock;
	float levelTime;
	bool isTimerRunning;

	//void setSprites();
	void setFont();

	sf::Text message(const std::string& my_message);
	sf::Text message(const std::string& my_message, const sf::Font& font, const double& x, const double& y);
	sf::Text message(const std::string& my_message, const sf::Font& font, const double& x, const double& y, const int size);


	//FROM THE LEVEL ONE(PRIVATE)


	//Animated text function
	void animateText(const std::string& text, const std::vector<std::string>& options);

	//Handling timer functions
	void resetTimer();        // Reset the timer for a new level
	void updateTimer();       // Update the timer each frame
	void formatTime(float seconds, char* buffer); // Format seconds into MM:SS
	void handleTimerExpired(); // Handle what happens when time runs out
	// create player
	Player p;

	//NEW
	// **NEW**: return the next Level, owning pointer
  //           or nullptr if this was the last one.
	virtual Level* createNext(sf::RenderWindow* window) = 0;

	virtual bool isFinished() const { return finished; }
protected:
	bool finished = false;
	//END NEW
};

//Homepage class *******************************************************************************
class Home : public Level
{
private:

public:
	//HOME PAGE COSNTRUCTOR
	Home(sf::RenderWindow* win);
	void handleEvent(const sf::Event& event);
	void render() override;


	void setSprites();

	//NEW
	// override isFinished and createNext functions
	bool isFinished() const override;
	Level* createNext(sf::RenderWindow* window) override;
};

//Narrative story Home page**************************************************************************************************
class StoryPage : public Level
{

public:
	//Constructor For STORYPAGE

	StoryPage(sf::RenderWindow* win);
	void handleEvent(const sf::Event& event);
	void setSprites();
	void render() override;

	//NEW
	// override isFinished and createNext functions
	bool isFinished() const override;
	Level* createNext(sf::RenderWindow* window) override;
};

//classes that DISPLAYS NARRATIVE BEFORE LEVEL ONE,TWO,THREE***********************************************************
class LevelOnePage : public Level {

public:
	LevelOnePage(sf::RenderWindow* win);
	void handleEvent(const sf::Event& event);
	void setSprites();
	void render() override;

	//NEW
	// override isFinished and createNext functions
	bool isFinished() const override;
	Level* createNext(sf::RenderWindow* window) override;
};
class LevelTwoPage : public Level {

public:
	LevelTwoPage(sf::RenderWindow* win);
	void handleEvent(const sf::Event& event);
	void setSprites();

	//NEW
	// override isFinished and createNext functions
	bool isFinished() const override;
	Level* createNext(sf::RenderWindow* window) override;
};
class LevelThreePage : public Level {

public:
	LevelThreePage(sf::RenderWindow* win);
	void handleEvent(const sf::Event& event);
	void setSprites();

	//NEW
	// override isFinished and createNext functions
	bool isFinished() const override;
	Level* createNext(sf::RenderWindow* window) override;
};

//Level One, Two, Three classes 
class LevelOne : public Level {

public:
	//Constructor For One Three
	LevelOne(sf::RenderWindow* win);
	void handleEvent(const sf::Event& event);
	void setSprites();

	//NEW
	// override isFinished and createNext functions
	bool isFinished() const override;
	Level* createNext(sf::RenderWindow* window) override;
};
class LevelTwo : public Level {

public:
	//Constructor For level Two
	LevelTwo(sf::RenderWindow* win);
	void handleEvent(const sf::Event& event);
	void setSprites();

	//NEW
	// override isFinished and createNext functions
	bool isFinished() const override;
	Level* createNext(sf::RenderWindow* window) override;
};
class LevelThree : public Level {

public:
	//Constructor For level Three
	LevelThree(sf::RenderWindow* win);
	void handleEvent(const sf::Event& event);
	void setSprites();

	//NEW
	// override isFinished and createNext functions
	bool isFinished() const override;
	Level* createNext(sf::RenderWindow* window) override;
};



//FeedBackPage classes that displays the feedback after every level

class FeedBackPage1 : public Level
{
public:

	sf::View scrollView;   // For scrolling

	// FEEDBACKPAGE1 COSNTRUCTOR
	FeedBackPage1(sf::RenderWindow* win);
	void handleEvent(const sf::Event& event);
	void render();


	void setSprites();

	//NEW
	// override isFinished and createNext functions
	bool isFinished() const override;
	Level* createNext(sf::RenderWindow* window) override;
};
class FeedBackPage2 : public Level
{
public:

	sf::View scrollView;   // For scrolling

	// FEEDBACKPAGE2 COSNTRUCTOR
	FeedBackPage2(sf::RenderWindow* win);
	void handleEvent(const sf::Event& event);
	void render();


	void setSprites();

	//NEW
	// override isFinished and createNext functions
	bool isFinished() const override;
	Level* createNext(sf::RenderWindow* window) override;
};
class FeedBackPage3 : public Level
{
public:

	sf::View scrollView;   // For scrolling

	//HOME FEEDBACKPAGE3 COSNTRUCTOR
	FeedBackPage3(sf::RenderWindow* win);
	void handleEvent(const sf::Event& event);
	void render();


	void setSprites();

	//NEW
	// override isFinished and createNext functions
	bool isFinished() const override;
	Level* createNext(sf::RenderWindow* window) override;
};

//Narrative story Home page**************************************************************************************************
class FinalPage : public Level
{

public:
	//Constructor For STORYPAGE

	FinalPage(sf::RenderWindow* win);
	void handleEvent(const sf::Event& event);
	void setSprites();
	void render() override;

	//NEW
	// override isFinished and createNext functions
	bool isFinished() const override;
	Level* createNext(sf::RenderWindow* window) override;
};


//This is declared outside as a seperate function
template<typename T>
bool loadFile(T& type_of_file, const std::string& file_name)
{
	if (!type_of_file.loadFromFile(file_name))
	{
		std::cerr << "Error loading file: " << file_name << std::endl;
		return false;
	}
	return true;
}
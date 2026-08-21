#ifndef _QUIZ_H_
#define _QUIZ_H_

#include <string>
#include <vector>

//BASE CLASS - Abstract class for all question types
class Question{

    protected:
        std::string questionText;
        int points;

    public:
        //Constructor
        Question(std::string text, int pts);
        //Virtual Destructor
        virtual ~Question();

        //Pure virtual Methods - child classes MUST implement these
        virtual void display() = 0;
        virtual bool checkAnswer(std::string answer) = 0;

        //Points getter
        int get_points();
};


//CHILD CLASS 1 - Multiple Choice Questions
class MultipleChoiceQuestion: public Question{
    private: 
        std::vector<std::string> options;
        char correctAnswer;
    public:
        //Constructor
        MultipleChoiceQuestion(std::string text, int pts, std::vector<std::string> opts, char correct);

        //Destructor
        ~MultipleChoiceQuestion();

        //Implementing the pure virtual Methods
        void display() override;
        bool checkAnswer(std::string answer) override;

};


//CHILD CLASS 2 - True/False Questions
class TrueFalseQuestion: public Question{
    private: 
        bool correctAnswer; //True or False

    public:
        //Constructor
        TrueFalseQuestion(std::string text, int pts, bool correct);
        //Destructor
        ~TrueFalseQuestion();
        //Implementing the pure virtual Methods
        void display() override;
        bool checkAnswer(std::string answer) override;
};

//=============================================
//COLOR THEME CLASS - Handle all visual styling
//=============================================
class ColorTheme{
    public:
        //ANSI Color Codes - static because so they're shared in each instance
        static const char* RESET;
        static const char* RED;
        static const char* GREEN;
        static const char* YELLOW;
        static const char* BLUE;
        static const char* MAGENTA;
        static const char* CYAN;
        static const char* BOLD;
        static const char* DIM;

        //Visual elements - static methods
        static void print_banner();
        static void print_separator();
        static void print_correct_message(int points);
        static void print_wrong_message();
        static void print_question_header(int current, int total);
        static void print_progress_bar(int current, int total);
};




//==================
//GAME MANAGER CLASS
//==================
class QuizGame{
    private:
        Question* parse_question_line(std::string line); //Helper to parse one line into question 
        void display_live_stats(int current, int total); //show stat during quiz
        std::vector<Question*> questions; //Stores all the questions
        int totalScore; //Total possible points
        int earnedScore; //Points earned by user
        int correctCount; //How many questions correct
        int currentStreak; //Current streak of correct answers
        int bestStreak; //Best streak in current session

    public:
        //Constructor
        QuizGame();
        //Destructor - must clean up all questions
        ~QuizGame();
        //Add a question to the quiz
        void add_question(Question* q);
        //Load default questions
        void load_default_questions();
        //Run the quiz game
        void run();
        //Display the final results
        void display_results();
        //Load questions from file
        bool load_from_file(std::string filename);
        //Display achievments/badges based on performance
        void display_achievements();

};

#endif
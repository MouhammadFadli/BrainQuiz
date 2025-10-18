#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include <cstdlib>
#include <ctime>
using namespace std;

const string UserFile = "QuizResult.txt";

//====================== ENUMS ======================//
enum enQuestionLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

//====================== STRUCTS ====================//
struct stQuestion {
	int number1 = 0;
	int number2 = 0;
	int StudentAnswer = 0;
	int CorrectAnswer = 0;
	bool AnswerResutl = false;
	enQuestionLevel QuestionLevel;
	enOperationType OperationType;
};

struct stQuizz {
	vector<stQuestion> vQuestionList;
	int NumberOfQuestions = 0;
	short NumberOfRightAnswer = 0;
	short NumberOfWrongAnswer = 0;
	bool FinishResult = false;
	string PlayerName = "";
	enQuestionLevel QuestionLevel;
	enOperationType OperationType;
};

//====================== FUNCTIONS ==================//
int random(int From, int To) {
	int RandNum = rand() % (To - From + 1) + From;
	return RandNum;
}

int ReadManyQuestion() {
	int ManyQuestion;
	do {
		cout << "How many Question do you wnat to answer ?" << endl;
		cin >> ManyQuestion;
		if (ManyQuestion < 1)
			cout << "Error Enter, You Enter : " << ManyQuestion << endl;
	} while (ManyQuestion < 1);
	return ManyQuestion;
}

enQuestionLevel ReadQuestionLevel() {
	int level;
	do {
		cout << "Enter Question Level [1] Easy, [2] Med, [3] Hard, [4] Mix" << endl;
		cin >> level;
		if (level < 1 || level > 4)
			cout << "Enter Error, You Enter : " << level;
	} while (level < 1 || level > 4);
	return enQuestionLevel(level);
}

enOperationType ReadOperationType() {
	int OpType;
	do {
		cout << "Enter Question Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ?" << endl;
		cin >> OpType;
		if (OpType < 1 || OpType > 5)
			cout << "Enter Error, You Enter : " << OpType << endl;
	} while (OpType < 1 || OpType > 5);
	return enOperationType(OpType);
}

string ReadName() {
	string name;
	cout << "Enter Your Name : ";
	getline(cin, name);
	return name;
}

int Calculater(enOperationType OperationType, int number1, int number2) {
	switch (OperationType) {
	case enOperationType::Add:
		return number1 + number2;
	case enOperationType::Sub:
		return number1 - number2;
	case enOperationType::Mult:
		return number1 * number2;
	case enOperationType::Div:

		return number1 / number2;
	}
}

stQuestion KnowstQuestion(enQuestionLevel QuestionLevel, enOperationType OperationType) {
	stQuestion Question;
	if (QuestionLevel == enQuestionLevel::Mix)
		QuestionLevel = enQuestionLevel(random(1, 3));
	if (OperationType == enOperationType::MixOp)
		OperationType = enOperationType(random(1, 4));

	switch (QuestionLevel) {
	case enQuestionLevel::EasyLevel:
		Question.number1 = random(1, 10);
		Question.number2 = random(1, 10);
		break;
	case enQuestionLevel::MedLevel:
		Question.number1 = random(10, 50);
		Question.number2 = random(10, 50);
		break;
	case enQuestionLevel::HardLevel:
		Question.number1 = random(50, 100);
		Question.number2 = random(50, 100);
		break;
	}

	Question.OperationType = OperationType;
	Question.QuestionLevel = QuestionLevel;
	Question.CorrectAnswer = Calculater(OperationType, Question.number1, Question.number2);

	return Question;
}

void KnowQuizz(stQuizz& Quizz) {
	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++) {
		Quizz.vQuestionList.push_back(KnowstQuestion(Quizz.QuestionLevel, Quizz.OperationType));
	}
}

string OperationTypeToText(enOperationType OperationType) {
	switch (OperationType) {
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mult:
		return "x";
	case enOperationType::Div:
		return "/";
	default:
		return "Mix";
	}
}

void PrintQuestion(stQuizz& Quizz, short QuestionNumber) {
	cout << "\n";
	cout << "\n====================================\n";
	cout << "          QUESTION [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n";
	cout << "====================================\n";
	cout << "              " << Quizz.vQuestionList[QuestionNumber].number1 << endl;;
	cout << "               " << OperationTypeToText(Quizz.vQuestionList[QuestionNumber].OperationType) << endl;;
	cout << "              " << Quizz.vQuestionList[QuestionNumber].number2 << endl;
	cout << "------------------" << endl;
}

int ReadAnswerStudent() {
	int answer;
	cout << "Enter answer : ";
	cin >> answer;
	return answer;
}

void ScreenColor(bool Result) {
	if (Result)
		system("color 2F");
	else {
		system("color 4F");
		cout << "\a";
	}


}

void CheckStudentAnswerIfCorrect(stQuizz& Quizz, short QuestionNumber) {
	if (Quizz.vQuestionList[QuestionNumber].StudentAnswer == Quizz.vQuestionList[QuestionNumber].CorrectAnswer) {
		Quizz.vQuestionList[QuestionNumber].AnswerResutl = true;
		Quizz.NumberOfRightAnswer++;
		cout << " Right Answer\n";
	}
	else {
		Quizz.vQuestionList[QuestionNumber].AnswerResutl = false;
		Quizz.NumberOfWrongAnswer++;
		cout << " Wrong Answer\n";
		cout << " Right Answer is : " << Quizz.vQuestionList[QuestionNumber].CorrectAnswer << "\n";
	}
	cout << endl;
	ScreenColor(Quizz.vQuestionList[QuestionNumber].AnswerResutl);
}

void AskAndCorrectQuestionAnswer(stQuizz& Quizz) {
	for (int QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++) {
		PrintQuestion(Quizz, QuestionNumber);
		Quizz.vQuestionList[QuestionNumber].StudentAnswer = ReadAnswerStudent();
		CheckStudentAnswerIfCorrect(Quizz, QuestionNumber);

	}
	if (Quizz.NumberOfRightAnswer > Quizz.NumberOfWrongAnswer)
		Quizz.FinishResult = true;
	else
		Quizz.FinishResult = false;
}

string QuizIsPassToText(bool IsPass) {
	if (IsPass)
		return "Pass";
	else
		return "Fail";
}

string QuizLevelToText(enQuestionLevel QuestionLevel) {
	string arr[4] = { "EasyLevel","MedLevel","HardLevel","MixLevel" };
	return arr[QuestionLevel - 1];
}

string QuizOperationToText(enOperationType OperationType) {
	string arr[5] = { "Add","Sub","Mult","Div","Mix" };
	return arr[OperationType - 1];
}

void PrintQuizzResult(stQuizz Quizz) {
	cout << "\n";
	cout << "            *** Finish ***\n";
	cout << "--------------------------------------\n\n";
	cout << " Final Result is : " << QuizIsPassToText(Quizz.FinishResult);
	cout << "\n\n--------------------------------------\n\n";

	cout << " Player Name            : " << Quizz.PlayerName << endl;
	cout << " Number of Questions    : " << Quizz.NumberOfQuestions << endl;
	cout << " Question Level         : " << QuizLevelToText(Quizz.QuestionLevel) << endl;
	cout << " Operation Type         : " << QuizOperationToText(Quizz.OperationType) << endl;
	cout << " Number of Right Answer : " << Quizz.NumberOfRightAnswer << endl;
	cout << " Number of Wrong Answer : " << Quizz.NumberOfWrongAnswer << endl;
	cout << "-----------------------------------------\n";
	cout << "Results saved to QuizResults.txt\n";
}

void SaveResultsToFile(stQuizz& Quizz, string FileName) {
	\
		ofstream outFile(FileName, ios::app); // append mode
	if (outFile.is_open()) {
		time_t now = time(0);
		tm ltm;
		localtime_s(&ltm, &now);

		outFile << "Data & Time : " << ltm.tm_year + 1900 << "-" << ltm.tm_mon + 1 << "-" << ltm.tm_mday << "\n";
		outFile << "Quiz Result            : " << QuizIsPassToText(Quizz.FinishResult) << "\n";
		outFile << "Player Name            : " << Quizz.PlayerName << "\n";
		outFile << "Number of Questions    : " << Quizz.NumberOfQuestions << "\n";
		outFile << "Number of Right Answers: " << Quizz.NumberOfRightAnswer << "\n";
		outFile << "Number of Wrong Answers: " << Quizz.NumberOfWrongAnswer << "\n";
		outFile << "Details:\n";
		for (int i = 0; i < Quizz.NumberOfQuestions; i++) {
			outFile << i + 1 << ") "
				<< Quizz.vQuestionList[i].number1 << " "
				<< OperationTypeToText(Quizz.vQuestionList[i].OperationType) << " "
				<< Quizz.vQuestionList[i].number2
				<< " | Your Answer: " << Quizz.vQuestionList[i].StudentAnswer
				<< " | Correct Answer: " << Quizz.vQuestionList[i].CorrectAnswer
				<< " | Result: " << (Quizz.vQuestionList[i].AnswerResutl ? "Right" : "Wrong") << "\n";
		}
		outFile << "---------------------------------\n";
		outFile.close();

	}
	else {
		cout << "Error: Cannot open file to save results.\n";
	}
}

void PlayQuizz() {
	stQuizz Quizz;
	Quizz.PlayerName = ReadName();
	Quizz.NumberOfQuestions = ReadManyQuestion();
	Quizz.QuestionLevel = ReadQuestionLevel();
	Quizz.OperationType = ReadOperationType();
	KnowQuizz(Quizz);
	AskAndCorrectQuestionAnswer(Quizz);
	PrintQuizzResult(Quizz);
	SaveResultsToFile(Quizz, UserFile);
}

void ResetScreen() {
	system("cls");
	system("color 0F");
}

string CheckChar(string word) {
	string Nword = "";
	for (int i = 0; i < size(word); i++) {
		if (isupper(word[i]))
			Nword += tolower(word[i]);
		else
			Nword += word[i];
	}
	return Nword;
}

void FinishQuizz() {
	string AgainQuizz = "";
	do {
		ResetScreen();
		PlayQuizz();
		cout << " Do you want to take the Quizz again [Yes] or [No] ? ";
		cin >> AgainQuizz;
		while (AgainQuizz != "yes" && AgainQuizz != "no")
		{
			cout << " Enter Error, You Enter : " << AgainQuizz << endl;;
			cout << " Do you want to take the Quizz again [Yes] or [No] ? ";
			cin >> AgainQuizz;
		}
	} while (CheckChar(AgainQuizz) != "no");
}

int main() {
	srand((unsigned)time(NULL));
	FinishQuizz();
	return 0;
}


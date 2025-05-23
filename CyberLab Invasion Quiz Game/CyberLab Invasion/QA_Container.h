// Ntulikazi and Anele
#pragma once
#include <queue>
using namespace std;

template<class Q, class A, int L>
class QA_Container
{
private:
	queue<Q> questions;
	queue<A> answers;

public:
	void addQA(const Q& q, const A& a);
	Q getQuestion();
	bool checkAnswer(const A& userAnswer);
	bool isEmpty() const;
};

template<class Q, class A, int L>
void QA_Container<Q, A, L>::addQA(const Q& q, const A& a) {
	questions.push(q);
	answers.push(a);
}

template<class Q, class A, int L>
Q QA_Container<Q, A, L>::getQuestion() {
	Q q = questions.front();  // use of iterators
	questions.pop();
	return q;
}

template<class Q, class A, int L>
bool QA_Container<Q, A, L>::checkAnswer(const A& userAnswer) {
	A a = answers.front();
	answers.pop();
	return userAnswer == a;
}

template<class Q, class A, int L>
bool QA_Container<Q, A, L>::isEmpty() const {
	return questions.empty();
}


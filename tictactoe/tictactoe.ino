/*
Copyright 2017 Jacques de Hooge, GEATEC engineering, www.geatec.com

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

// ====== Includes

#include <cantino.h>

using namespace cantino;

// ====== Consts

const int
	nrOfRows = 3,
    nrOfCols = 3;

// ====== Classes

class Observer {
	friend class Subject;
public:
	Observer ();
	virtual void update () = 0;
protected:
	Observer *pNextObserver;
};

class Subject {
public:
	Subject ();
	virtual void attach (Observer *pObserver);
	void detach (Observer *pObserver);
	void notifyObservers ();
protected:
	Observer *pFirstObserver;
};


class TicTacToeState {
public:
	TicTacToeState ();
	bool evenTurn;
	char fields [nrOfRows][nrOfCols];
};

class TicTacToeSubject;

class TicTacToeObserver: public Observer {
	friend class TicTacToeSubject;
public:
	virtual void update ();
	void play ();
	virtual void show () = 0;
	void show (char oddChar, char evenChar);
protected:
	TicTacToeState copiedState;
	TicTacToeSubject *pTicTacToeSubject;
};

class AlphaObserver: public TicTacToeObserver {
public:
	virtual void show ();
};

class BinObserver: public TicTacToeObserver {
public:
	virtual void show ();
};

class TicTacToeSubject: public Subject {
public:
	virtual void attach (TicTacToeObserver *pTicTacToeObserver);
	const TicTacToeState &getState ();
	void setState (const TicTacToeState &state);
protected:
	// ... Methods to check validity of move, determine winner, maintain score

	TicTacToeState state;
};

// ====== Global functions

// --- Main program function

int main () {
	TicTacToeSubject ticTacToeSubject;

	AlphaObserver alphaObserver;
	BinObserver binObserver;

	TicTacToeObserver
		*pTicTacToeObserver1 = 0,
		*pTicTacToeObserver2 = 0;

	// Type of observer determined at runtime, may be altered during play

	pTicTacToeObserver1 = &alphaObserver;
	pTicTacToeObserver2 = &binObserver;

	ticTacToeSubject.attach (pTicTacToeObserver1);
	ticTacToeSubject.attach (pTicTacToeObserver2);

	for (;;) {
		pTicTacToeObserver1->play ();
		pTicTacToeObserver2->play ();
	}

	ticTacToeSubject.detach (pTicTacToeObserver1);	// Unreachable
	ticTacToeSubject.detach (pTicTacToeObserver2);	// Unreachable

	return 0;
}

// ====== Member functions

// Member functions of class TObserver

Observer::Observer () {
	pNextObserver = 0;
}

// Member functions of class TSubject

Subject::Subject () {
	pFirstObserver = 0;
}

void Subject::attach (Observer *pObserver) {
	Observer **ppCurrentObserver = &pFirstObserver;
	while (*ppCurrentObserver != 0) {
		ppCurrentObserver = &((*ppCurrentObserver)->pNextObserver);
	}
	*ppCurrentObserver = pObserver;
	pObserver->update ();
}

void Subject::detach (Observer *pObserver) {
	// Not implemented
}

void Subject::notifyObservers () {
	Observer *pCurrentObserver = pFirstObserver;
	while (pCurrentObserver != 0) {
		pCurrentObserver->update ();
		pCurrentObserver = pCurrentObserver->pNextObserver;
	}
}

// Member functions of class TTicTacToeState

TicTacToeState::TicTacToeState () {
	{for (int rowNr = 0; rowNr < nrOfRows; rowNr++) {
		{for (int colNr = 0; colNr < nrOfCols; colNr++) {
			fields [rowNr][colNr] = ' ';
		}}
	}}
	evenTurn = false;
}

// Member functions of class TTicTacToeObserver

void TicTacToeObserver::update () {
	copiedState = pTicTacToeSubject->getState ();
	show ();
}

void TicTacToeObserver::play () {
	cout <<
		(copiedState.evenTurn ? "Even" : "Odd") <<
		" player, your move please... " << endl <<
		" <row (1..3, 0 = stop)> [enter] <col (1..3, 0 = stop)> [enter]: ";

	int
		row,
		col;

    char blanks [8];

	cin >> row;
	cin >> col;

	if ((row == 0) || (col == 0)) {
		exit (0);  // No cleanup done
	}

	int
		rowNr = row - 1,
		colNr = col - 1;

	copiedState.fields [rowNr][colNr] =
		copiedState.evenTurn ? 'E' : 'O';

	copiedState.evenTurn = !copiedState.evenTurn;

	pTicTacToeSubject->setState (copiedState);  // !
}

void TicTacToeObserver::show (char oddChar, char evenChar) {
	{for (int rowNr = 0; rowNr < nrOfRows; rowNr++) {
		{for (int colNr = 0; colNr < nrOfCols; colNr++) {
			switch (copiedState.fields [rowNr][colNr]) {
				case 'E':
					cout << oddChar;
					break;
				case 'O':
					cout << evenChar;
					break;
				default:
					cout << '.';
					break;  // redundant
			}
		}}
		cout << endl;
	}}
	cout << endl;
}

// Member functions of class TAlphaObserver

void AlphaObserver::show () {
	TicTacToeObserver::show ('O', 'X');
}

// Member functions of class TBinObserver

void BinObserver::show () {
	TicTacToeObserver::show ('0', '1');
}

// Member functions of class TTicTacToeSubject

void TicTacToeSubject::attach (TicTacToeObserver *pTicTacToeObserver) {
	pTicTacToeObserver->pTicTacToeSubject = this;
	Subject::attach (pTicTacToeObserver);
}

const TicTacToeState &TicTacToeSubject::getState () {
	return state;
}

void TicTacToeSubject::setState (const TicTacToeState &state) {
	TicTacToeSubject::state = state;
	notifyObservers ();
}

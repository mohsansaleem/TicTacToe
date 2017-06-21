#pragma once
#include "tictac.h"



class SaveLoad
{
	TicTac temp;
	int id;
	string password;
	friend ifstream & operator>>( ifstream &, SaveLoad & );
	friend ofstream & operator<<( ofstream &, SaveLoad & );
public:
	SaveLoad(void);
	bool save( TicTac & );
	bool load( TicTac & temp );
	~SaveLoad(void);
};


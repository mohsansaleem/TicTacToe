#include<string>
#include<iostream>
#include<fstream>
using namespace std;
class SaveLoad;
int strtoi( string );
bool exit_to_system();


#pragma once
class TicTac
{
private:
	int **a;
	int size ;
	char player2;
	bool saved;
	bool exited;
	void show();
	bool player( int );
	int check();
	bool check_player( int );
	int count();
	void new_arr_n_size();
	void set_arr_n_size( int );
	void player2_type();
	bool computer();
	bool comp_place( int );
	bool comp_place_win( int );
	void place_in_row( int );
	void place_in_col( int );
	void place_in_main_diagonal();
	void place_in_hyp();
	bool place_rand();
	friend class SaveLoad;
	friend ifstream & operator>>( ifstream &, TicTac & );
	friend ofstream & operator<<( ofstream &, TicTac & );
public:
	TicTac& operator=( TicTac& );
	bool get_saved();
	void set_saved( bool );
	static bool exitgame();
	void play( );
	TicTac( int );
	TicTac();
	TicTac( TicTac& );
	void run();
	~TicTac();
};


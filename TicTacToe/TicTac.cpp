#include "TicTac.h"

TicTac::TicTac( int size  )
{
	saved = false;
	exited = false;
	(this->size) = size;
	player2 = 'H';
	a = new int* [size];

	for( int i = 0; i < size ; i++ )
		a[i] = new int[size];


	for( int row = 0; row < size; row++ )
		for( int col = 0; col < size; col++ )
			this -> a[row][col] = 0;
}
TicTac::TicTac ()
{
	a = NULL; 
	size = 0;
	player2 = 'H';
	saved = false;
	exited = false;
}
TicTac::TicTac( TicTac& temp )
{
	(this->size) = temp.size;
	player2 = temp.player2 ;
	a = new int* [temp.size];

	for( int i = 0; i < size ; i++ )
		a[i] = new int[size];	
	
	for( int r = 0; r < size; r++ )
		for( int c = 0; c < size; c++  )
			(this->a[r][c]) = temp.a[r][c];
	saved = false;
	exited = false;
}
TicTac& TicTac::operator=( TicTac& temp )
{
	set_arr_n_size( temp.size );
	
	for( int r = 0; r < temp.size; r++ )
		for( int c = 0; c < temp.size; c++  )
			(this->a[r][c]) = temp.a[r][c];
	this->player2 = temp.player2;
	saved = false;
	exited = false;
	return (*this);
}
void TicTac::set_arr_n_size ( int s )
{
	size = s;
	if( a != NULL )
	delete []*a;
	
	a = new int* [size];

	for( int i = 0; i < size ; i++ )
		a[i] = new int[size];


	for( int row = 0; row < size; row++ )
		for( int col = 0; col < size; col++ )
			this -> a[row][col] = 0;

}
TicTac::~TicTac()
{
	if( size != 0 )
		delete []*a;
}

void TicTac::show()
{
	system("cls");
	cout << "Press 'S' to Save Game.\t\t Press 'M' to close current game.\n\t\t Press Q to Quit to system\n\n\n";
	for( int row = 0 ; row < size ; row++ )
	{
		for( int col = 0 ; col < size ; col++ )
			cout << this -> a[row][col] << '\t';
		
		cout << endl;

		if( row != (size - 1) )
		{
		
			for( int i = 0; i < (size - 1); i++ )
				cout << "____\t";
			cout << "____" << endl;
		}
					
	}
}

bool TicTac::player( const int player_no )
{

	int row_no = 0;	
	string stri;

	while( row_no < 1 || row_no > (size) )
	{
point:
		system("cls");
		this->show();
		cout << endl << endl << "Player " << player_no << endl;
		cout << endl << "Enter Row no: ";
		cin >> stri;
		if( stri == "q" || stri == "Q" )
		{
			exit_to_system();
			continue;
		}
		if( stri == "m" || stri == "M" )
		{
			if( exitgame() )
			{
				this->exited = true;
				return false;
			}
			continue;
		}
		if( stri == "s" || stri == "S" )
		{
			saved = true;
			return false;
		}
		row_no = strtoi( stri);
		if( row_no < 1 || row_no > (size) )
		{
			cout << "Wrong R0w!\n";
			system("pause");
		}
	}

	
	int col_no = 0;
	
	while( col_no < 1 || col_no > (size) )
	{
		system("cls");
		this->show();
		cout << endl << endl << "Player " << player_no << endl;
		cout << endl << "Enter Row no: " << row_no;
		cout << endl << "Enter Col no: ";
		cin >> stri;
		if( stri == "q" || stri == "Q" )
		{
			exit_to_system();
			continue;
		}
		if( stri == "m" || stri == "M" )
		{
			if( exitgame() )
			{
				this->exited = true;
				return false;
			}
			continue;
		}
		if( stri == "s" || stri == "S" )
		{
			saved = true;
			return false;
		}
		col_no = strtoi(stri);
		if( col_no < 1 || col_no > (size) )
		{
			cout << "Wrong column!\n";
			system("pause");
		}
	}



	if( a[row_no-1][col_no-1] != 1 && a[row_no-1][col_no-1] != 2 )
		a[row_no-1][col_no-1] = player_no ;	
	else
	{
		cout << "Already Filled. Select the other one!" << endl;
		system("pause");
		goto point;
	}
	
	system("cls");
	this->show();

	return (this->check_player (player_no));
}

bool TicTac::comp_place( int p )
{
	int plr[] = {0,0,0,0};
	int cmp[] = {0,0,0,0};
	
	for( int i = 0 ; i < size ; i++ )
	{
		plr[0] = 0;
		plr[1] = 0;
		cmp[0] = 0;
		cmp[1] = 0;


		for( int j = 0 ; j < size ; j++ )
		{
			if( a[i][j] == 1 )
				plr[0]++;
			
			
			if( a[j][i] == 1 )
				plr[1]++;			
		
			if( i == j && a[i][j] == 1 )
					plr[2]++;

			if( i + j == (size - 1) && a[i][j] == 1 )
				plr[3]++;

			if( a[i][j] == 2 )
				cmp[0]++;
			
			
			if( a[j][i] == 2 )
				cmp[1]++;			
		
			if( i == j && a[i][j] == 2 )
					cmp[2]++;

			if( (i + j) == (size - 1) && a[i][j] == 2 )
				cmp[3]++;
		}

		if( plr[0] == p && cmp[0] == 0 )
		{
			this->place_in_row(i);
			return true;
		}

		if( plr[1] == p && cmp[1] == 0 )
		{
			this->place_in_col(i);
			return true;
		}

	}

	if( plr[2] == p && cmp[2] == 0 )
	{
		this->place_in_main_diagonal();
		return true;
	}

	if( plr[3] == p && cmp[3] == 0 )
	{
		this->place_in_hyp ();
		return true;
	}


	return false;
}


bool TicTac::comp_place_win( int p )
{
	int plr[] = {0,0,0,0};
	int cmp[] = {0,0,0,0};
	
	for( int i = 0 ; i < size ; i++ )
	{
		plr[0] = 0;
		plr[1] = 0;
		cmp[0] = 0;
		cmp[1] = 0;


		for( int j = 0 ; j < size ; j++ )
		{
			if( a[i][j] == 1 )
				plr[0]++;
			
			
			if( a[j][i] == 1 )
				plr[1]++;			
		
			if( i == j && a[i][j] == 1 )
					plr[2]++;

			if( i + j == (size - 1) && a[i][j] == 1 )
				plr[3]++;

			if( a[i][j] == 2 )
				cmp[0]++;
			
			
			if( a[j][i] == 2 )
				cmp[1]++;			
		
			if( i == j && a[i][j] == 2 )
					cmp[2]++;

			if( (i + j) == (size - 1) && a[i][j] == 2 )
				cmp[3]++;
		}

		if( plr[0] == 0 && cmp[0] == p )
		{
			this->place_in_row(i);
			return true;
		}

		if( plr[1] == 0 && cmp[1] == p )
		{
			this->place_in_col(i);
			return true;
		}

	}

	if( plr[2] == 0 && cmp[2] == p )
	{
		this->place_in_main_diagonal();
		return true;
	}

	if( plr[3] == 0 && cmp[3] == p )
	{
		this->place_in_hyp ();
		return true;
	}


	return false;
}


void TicTac::place_in_row( int rowp )
{
	for( int colp = 0; colp < size; colp++ )
	{
		if( a[rowp][colp] == 0 )
		{
			a[rowp][colp] = 2;
			return;
		}
	}
}


void TicTac::place_in_col( int colp )
{
	for( int rowp = 0; rowp < size; rowp++ )
	{
		if( a[rowp][colp] == 0 )
		{
			a[rowp][colp] = 2;
			return;
		}
	}
}

void TicTac::place_in_main_diagonal()
{
	for( int row = 0; row < size; row++ )
		for( int col = 0; col < size; col++ )
			if( row == col && a[row][col] == 0 )
			{
				a[row][col] = 2;
				return;
			}
}

void TicTac::place_in_hyp()
{
	for( int row = 0; row < size; row++ )
		for( int col = 0; col < size; col++ )
			if(  (row+col) == (size - 1) && a[row][col] == 0 )
			{
				a[row][col] = 2;
				return;
			}
}

bool TicTac::place_rand()
{
	int r , c;
	r = ( rand() % size );
	c = ( rand() % size );
	if( a[r][c] == 0 )
		a[r][c] = 2;
	else
		return false;

	return true;
}

bool TicTac::computer()
{
	for( int plcs = size - 1; plcs > 0; plcs--  )
	{
		if( comp_place (plcs) )
		{
			system("cls");
			this->show();
			return check_player (2);
		}
		else if( comp_place_win (plcs) )
		{
			system("cls");
			this->show();
			return check_player (2);
		} 
	}


	while( !place_rand() );

	system("cls");
	this->show();
	return check_player(2);
}

bool TicTac::check_player( const int player_no )
{
	int plr[] = {0,0,0,0};
	
	for( int i = 0 ; i < size ; i++ )
	{
		plr[0] = 0;
		plr[1] = 0;

		for( int j = 0 ; j < size ; j++ )
		{
			if( a[i][j] == player_no )
				plr[0]++;
			
			if( a[j][i] == player_no )
				plr[1]++;			
		
			if( i == j && a[i][j] == player_no )
					plr[2]++;

			if( i + j == (size - 1) && a[i][j] == player_no )
				plr[3]++;
		}

		if( plr[0] == size || plr[1] == size || plr[2] == size || plr[3] == size )
			return 1;		
	}


	return 0;
}

int TicTac::check()
{
	if( check_player( 1 ) )
		return 1;
	
	if( check_player(2) )
		return 2;

	return 0;
}

void TicTac::new_arr_n_size()
{
	while( 1 )
	{
		cout << "\n\t\tEnTeR tHe SiZe oF Game Square( 3x3 to 9x9 ): ";
		string ss;
		cin >> ss;
		if( strtoi(ss) < 3 || strtoi(ss) > 9  )
		{
			cout << "\n\n\t\tWrong Input!\n\t\t";
			system("pause");
			continue;
		}
		else
		{
			size = strtoi( ss );

			if( a != NULL )
				delete []*a;

			a = new int* [size];

			for( int i = 0; i < size ; i++ )
				a[i] = new int[size];


			for( int row = 0; row < size; row++ )
				for( int col = 0; col < size; col++ )
					this -> a[row][col] = 0;
		}
		break;
	}
}

void TicTac::player2_type ()
{
	cout << "\n\t\t 1) Humane.\n\t\t 2) Computer";
	cout << "\n\t\tSelect 2nd Player Type: ";
	string ss;
	cin >> ss;
	int len = ss.length ();
	if( len > 1 || (ss[0] - 48) < 1 || (ss[0] - 48) > 2   )
	{
		cout << "\n\n\t\tWrong Input!\n\t\t";
		system("pause");
		player2_type();
	}
	else
	{
		if( ss[0] == 49 )
			this->player2 = 'H';
		else
			this->player2 = 'C';
	}

}

void TicTac::play( )
{
	saved = false;
	/*
	while( ( plr < size ) && !player(1) && !player(2) )
	{
		plr++;
	}*/	
	
	int i;
	for( i = count() ; i < size*size; i++ )
	{
		
		if( player2 == 'C' )
		{
			 if( i % 2 == 0 && computer() )
			 {
				 cout << "\nComputer Win!\n";
				 system("pause");
				 break;
			 }
			 else if( i % 2 != 0 && player(1))
			 {
				 cout << "\nPlayer Win!\n";
				 system("pause");
				 break;
			 }
		}
		else
		{
			if( i % 2 == 0 && player(1))
			{
				cout << "\nPlayer1 Win!\n";
				system("pause");
				break;
			} 
			else if( i % 2 != 0 && player(2))
			{
				cout << "\nPlayer2 Win!\n";
				system("pause");
				break;
			}
		}
		if( saved == true )
				return;
		if( exited == true )
			return;
		
	}

	
	if( i = size*size && !check())
	{
		cout << "Game Over!\n";
		system("pause");

	}
	//cout << endl;
	//system("pause");
	//int main();
	//main();

}

bool TicTac::exitgame()
{
	while( 1 )
	{
			string option;
			cout << "\n\t\t Do YoU WaNt To Return to main menu(Y/N): ";
			cin >> option;
			if( option.length() > 1 || ( option[0] != 'y' && option[0] != 'Y' && option[0] != 'N' && option[0] != 'n') )
			{
				cout << "\n\t\t WrOng Selection! \n\n\t\t ";
				continue;
			}
			else if( option[0] == 'y' || option[0] == 'Y' )
				return true;
			else
				break;
	}
	return false;
}

int TicTac::count()
{
	int countp = 0;

	for( int row = 0; row < size; row++ )
	{	
		for( int col = 0; col < size; col++ )
		{
			if( a[row][col] == 1 || a[row][col] == 2 )
			{
				countp++;
			}
		}
	}
	return countp;
}


void TicTac::run()
{
	saved = false;
	this->player2_type();
	this->new_arr_n_size ();
	play();
}

int strtoi( string temp )
{
	int intr = 0;
	for( int i = 0; i < temp.length(); i++ )
	{
		intr *= 10;
		intr += ( temp[i] - 48 );
	}

	return intr;
}


ifstream & operator>>( ifstream & inf, TicTac & temp )
{
	inf >> temp.player2;
	inf >> temp.size;
	temp.set_arr_n_size( temp.size );
	for( int i = 0; i < temp.size; i++ )
		for( int r = 0; r < temp.size; r++ )
			inf >> temp.a [i][r];
	return inf;
}

ofstream & operator<<( ofstream & outf, TicTac & temp )
{
	temp.show ();
	outf << temp.player2<<endl;
	outf << temp.size<<endl;
	
	for( int i = 0; i < temp.size; i++ )
	{
		for( int r = 0; r < temp.size; r++ )
			outf << temp.a [i][r] << '\t';
		outf << endl;
	}
	outf << endl;
	return outf;
}

void TicTac::set_saved( bool t ){ saved = t; }

bool TicTac::get_saved(){ return saved; }

bool exit_to_system()
{
       while( 1 )
	   {
			string option;
			cout << "\n\t\t Do YoU WaNt To Exit(Y/N): ";
			cin >> option;
			if( option.length() > 1 || ( option[0] != 'y' && option[0] != 'Y' && option[0] != 'N' && option[0] != 'n') )
			{
				cout << "\n\t\t WrOng Selection! \n\n\t\t ";
				continue;
			}
			else if( option[0] == 'y' || option[0] == 'Y' )
				exit(0);
			else
				break;
		}
	return false;
}
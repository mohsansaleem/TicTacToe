#include "SaveLoad.h"


SaveLoad::SaveLoad(void)
{
	id = 0;
	password = "";
}


SaveLoad::~SaveLoad(void)
{

}

bool SaveLoad::save( TicTac & tempt )
{
	ifstream inf("Game.txt",ios::in );
	if( inf )
	{
		while( !inf.eof() )
		{
			inf >> (*this);
		}
		inf.close();
	}

	
	
	id++;
	cout << "Enter Passward For this Game: ";
	cin >> password;
	this->temp = tempt;

	ofstream outf("Game.txt", ios::app | ios::out);
	outf << (*this);
	outf.close();
	cout << "Your Save id is "<< id << "\nSaved!\n";
	return true;
}


bool SaveLoad::load( TicTac & temp )
{
agninp:
	string tmpid, tmppsd;
	system("cls");
	cout << "Press 'M' to main menu.\t\t Press Q to Quit to system";
	cout << "\n\n\t\t Enter Game id: ";
	cin >> tmpid;

	if( tmpid == "q" || tmpid == "Q" )
	{
			exit_to_system();
			goto agninp;
	}
				
	if( tmpid == "m" || tmpid == "M" )
	{	
		if( TicTac::exitgame() )
			return false;

		goto agninp;
	}

	ifstream inf("Game.txt",ios::in );
	
	if( inf )
	{
		while( !inf.eof() )
		{
			inf >> (*this);
				
			if( this->id == strtoi( tmpid ) )
			{
			agnpsd:
				cout << "\n\t\t Enter Password: ";
				cin >> tmppsd;


				if( tmppsd == "q" || tmppsd == "Q" )
				{
					exit_to_system();
					continue;
				}
				
				if( tmppsd == "m" || tmppsd == "M" )
				{	
					if( TicTac::exitgame() )
						return false;
					continue;
				}


				if( tmppsd == ( this->password ) )
				{
					temp = this->temp;
					inf.close ();
					return true;
				}
				else
				{
					cout << "\n\t\t Wrong Password!\n\t\t";
					system("pause");
					goto  agnpsd;
				}
			}
		}
	
		inf.close();
		
		if( this-> id != strtoi(tmpid) )
		{
			cerr << "\n\t\t Dosn't Exist!\n\t\t";
			system("pause");
			return false;
		}
	}
	else
	{
		cout << "\n\t\t No Recod found!\n\t\t";
		system("pause");
	}

	return false;
}


ifstream & operator>>( ifstream &infs, SaveLoad &tmp )
{
	infs >> tmp.id;
	infs >> tmp.password;
	infs >> tmp.temp;
	return infs;
}

ofstream & operator<<( ofstream &outfs, SaveLoad &tmp )
{
	outfs << tmp.id << endl;
	outfs << tmp.password << endl;
	outfs << tmp.temp;
	return outfs;
}



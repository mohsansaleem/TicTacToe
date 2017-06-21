#include"SaveLoad.h"

int main()
{


	while(1)
		{
		string option;
		do
		{
	
			system("cls");
			cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
			cout << "+>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> TiC_TaC <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<+" << endl;
			cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
			cout << "\n\n\n\n\n\t\t 1) NeW GaMe \n\t\t 2) Load Game \n\t\t 3) ExIt tHe GaMe.";
			cout << "\n\n\t\t SeLeCt OnE: ";
	
	
			cin >> option;
	
			if(  strtoi( option ) < 1 || strtoi( option ) > 3  )
			{
				cout << "Wrong Selection!\n";
				system("pause");
			}

		}while( strtoi( option ) < 1 || strtoi( option ) > 3 );
	
		TicTac game;
		SaveLoad loadgme;
	
		switch( strtoi(option) )
		{
		case 1:
			game.run();
			break;
		case 2:
			if( loadgme.load(game) )
				game.play();
			break;
		case 3:
			if( !exit_to_system() )
				continue;
			break;
		default:
			cout << "\n\t\t WrOnG SeLeCtIoN!\n\n\t\t ";
			system("pause");
		}

		aab:

		if( game.get_saved() == true )
		{
			SaveLoad sl;
			sl.save( game );
			system("pause");
		}
	}
	
	return 0;
}

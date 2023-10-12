

#include <iostream>
#include <iomanip>	
#include <conio.h>	
#include <time.h>	
#include "y:\b11\console(v1.8).h" 
#include <windows.h>

using namespace std; 

void main()
{
	char réponse1, réponse2;
	int   jourInput, moisInput, anneeInput, jourSemaine, nbTotalJoursEcoules, l, c, jj,
		linecalendrier = 2, charjourcalen = 2; //max de 6 sinon ça pète; 
	int joursMois[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	const int espaCalendrier = 8, tab = 8; 
	const char separtioncalen = '_';
	string semaine2lettres;
	string jour[7] = { "Dimanche","Lundi","Mardi","Mercredi","Jeudi","Vendredi","Samedi" };
	string erreur[7] = {
		" ",
		"Vous devez entrer des nombres seulement",
		"Le jour doit \210tre entre 1 et 31 exclusivement",
		"Le mois est erron\202 (doit \210tre entre 1 et 1o2 inclusivement)",
		"L'ann\202e est erron\202e (de 1901 \205 2099)",
		"Le mois de f\202vrier ne peut compter plus de 28 jours",
		"Ce mois ne compte que 30 jours" };
	string const mois[12] = { "Janvier","F\202vrier", "Mars", "Avril","Mai","Juin","juillet",
		"Ao\226t","Septembre","Octobre","Novembre","D\202cembre" };
	string const textaffichage[4] = {
		"Entrez une date (JJ/MM/AAAA) : ",
		"Voulez-vous voir le calendrier complet du mois (O/N) ? ",
		"Voulez-vous traiter une autre date (O/N) ? ",
		"A U  R E V O I R !" };
	do
	{
		do
		{
			erreur[0] = " ";
			jourInput = moisInput = anneeInput = nbTotalJoursEcoules = 0;
			gotoxy(tab, 1);
			cout << textaffichage[0];
			c = wherex(); l = wherey();
			cin >> jourInput;
			cin.get();
			cin >> moisInput;
			cin.get();
			cin >> anneeInput;
			if (cin.fail())
			{
				cin.clear(); 
				cin.ignore(cin.rdbuf()->in_avail());
				erreur[0] = erreur[1];
			}
			else if (jourInput < 0 || jourInput > 31)
				erreur[0] = erreur[2];
			else if (moisInput < 0 || moisInput > 12)
				erreur[0] = erreur[3];
			else if (anneeInput < 1901 || anneeInput > 2099)
				erreur[0] = erreur[4];
			else if (jourInput == 29 && moisInput == 2)
			{
				if (anneeInput % 4 != 0)
					erreur[0] = erreur[5];
			}
			else if (jourInput == 31 && (moisInput == 4 || moisInput == 6 || moisInput == 9 || moisInput == 11))
				erreur[0] = erreur[6];

			clrscr();
			if (erreur[0] != " ")
			{
				gotoxy(tab, 29);
				cout << erreur[0];
			}

		} while (erreur[0] != " ");

		clrscr();

		joursMois[1] = 28;
		if (anneeInput % 4 == 0)
			joursMois[1]++;

		jourSemaine = nbTotalJoursEcoules = 0;
		for (int i = 1; i < moisInput; i++)
		{
			nbTotalJoursEcoules += joursMois[i - 1];
		}
		nbTotalJoursEcoules += jourInput;

		jourSemaine = (nbTotalJoursEcoules + (anneeInput - 1900) + (anneeInput - 1901) / 4) % 7;

		gotoxy(tab, 3);
		cout << "Le " << jourInput << "/" << moisInput << "/" << anneeInput << " est un : " << jour[jourSemaine];
		gotoxy(tab, 6);

		while (_kbhit()) _getch();

		cout << textaffichage[1];

		c = wherex(); l = wherey();
		do
		{
			réponse1 = toupper(_getche());
			gotoxy(c, l);
		} while (réponse1 != 'O' && réponse1 != 'N');

		if (réponse1 == 'O')
		{
			clrscr();

			nbTotalJoursEcoules -= jourInput;
			nbTotalJoursEcoules++;
			jourSemaine = (nbTotalJoursEcoules + (anneeInput - 1900) + (anneeInput - 1901) / 4) % 7;

			gotoxy((120 - (mois[moisInput - 1].size() + 5)) / 2, 2);
			cout << mois[moisInput - 1] << " " << anneeInput;

			gotoxy((120 - (charjourcalen * 7 + espaCalendrier * 6)) / 2, 5);
			c = wherex(); l = wherey();
			for (int i = 0; i < 7; i++)
			{
				semaine2lettres = "";
				for (int a = 0; a < charjourcalen; a++)
					semaine2lettres = semaine2lettres + jour[i][0 + a];
				cout << semaine2lettres << setw(espaCalendrier) << " ";
			}
			gotoxy(c, ++l);
			cout << setfill(separtioncalen) << setw(charjourcalen * 7 + espaCalendrier * 6) << "" << setfill(' ');
			gotoxy(c, l += 3);
			for (int i = 0; i < jourSemaine; i++)
				cout << setw(espaCalendrier + charjourcalen) << "";
			jj = 1;
			for (int i = 0; i < joursMois[moisInput - 1]; i++, jj++)
			{
				switch (jj + jourSemaine - 1)
				{
				case 7:
				case 14:
				case 21:
				case 28: gotoxy(c, l += linecalendrier);  break;
				}
				cout << left << setw(espaCalendrier + charjourcalen) << jj;
			}
		}

		while (_kbhit()) _getch();

		gotoxy(tab, 29);
		cout << textaffichage[2];

		c = wherex(); l = wherey();
		do
		{
			réponse2 = toupper(_getche());
			gotoxy(c, l);
		} while (réponse2 != 'O' && réponse2 != 'N');

		clrscr();

	}while (réponse2 != 'N');

	gotoxy((120 - textaffichage[3].size()) / 2, 15);
	cout << textaffichage[3];
	Sleep(1000);
}


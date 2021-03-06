// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "System.h"
#include <time.h>

int main()
{
	initHeapMonitor();

	cout << "\nZadajte volbu:\n\n 1. Vytvorenie noveho systemu\n 2. Nacitanie systemu zo suboru\n 3. Koniec\n\n";
	int volba;
	cin >> volba;

	srand(time(0));
	ifstream * infile = new ifstream();
	System * system = nullptr;

	switch (volba)
	{
	case 1:
		system = new System();
		break;
	case 2:
		system = new System(infile);
		break;
	default:
		delete infile;
		delete system;
		return 0;
	}

	while (true)
	{
		cout << "\n\nZadajte volbu:\n\n 1. Pridanie noveho biofarmara\n";
		cout << " 2. Vypisanie zoznamu biofarmarov\n";
		cout << " 3. Pridanie noveho vozidla\n";
		cout << " 4. Vypisanie zoznamu vozidiel\n";
		cout << " 5. Registracia noveho zakaznika\n";
		cout << " 6. Zaevidovanie novej objednavky\n";
		cout << " 7. -\n";
		cout << " 8. Vypisanie objednavok, ktore maju byt zrealizovane nasledujuci den\n";
		cout << " 9. -\n";
		cout << " 10. -\n";
		cout << " 11. Vypisanie zoznamu zakaznikov\n";
		cout << " 12. Vypisanie vsetkych objednavok, ktore sa podarilo zrealizovat\n";
		cout << " 13. Vypisanie vsetkych objednavok, ktore sa nepodarilo zrealizovat\n";
		cout << " 14. Vypisanie biofarmara, od ktoreho firma nakupila najviac polotovarov za poslednych 30 dni\n";
		cout << " 15. Vypisanie celkoveho zisku firmy\n\n";

		cout << " 16. Ulozenie aktualneho stavu do suboru\n";
		cout << " 17. Spustenie predpripravenej sekvencie prikazov\n";
		cout << " 18. Vypisanie aktualneho dna\n";
		cout << " 19. Koniec\n\n";
		
		cout << " 0. Prechod na dalsi den\n\n";
		cin >> volba;

		string nazov = "";
		int cislo = 0;
		int cislo2 = 0;
		int cislo3 = 0;
		int cislo4 = 0;
		Zakaznik * zakaznik = nullptr;
		switch (volba)
		{
		case 1:
			cout << "\n\nZadajte nazov biofarmara:\n";
			cin >> nazov;

			if (system->dajBioFarmarov()->vytvorBioFarmara(nazov))
			{
				while (true)
				{
					cout << "\nZadajte postupne polotovary, ktore bude dodavat \n(zemiaky = 0, olej = 1, ochucovadla = 2): ";
					cin >> cislo;
					if (cislo > 2 || cislo < 0)
					{
						break;
					}
					system->dajBioFarmarov()->pridajProduktBioFarmarovi(nazov, Polotovar::toTyp(cislo));
				}
			}
			else { cout << "\nFarmar s danym nazvom uz existuje!\n"; }
			break;

		case 2:
			cout << "Ktory polotovar \n(zemiaky = 0, olej = 1, ochucovadla = 2): ";
			cin >> cislo;
			system->dajBioFarmarov()->vypisBioFarmarovPodlaPolotovaru(Polotovar::toTyp(cislo));
			break;

		case 3:
			cout << "\n\nZadajte SPZ noveho vozidla:\n";
			cin >> nazov;
			cout << "Ktory tovar \n(hranolky = 0, lupienky = 1): ";
			cin >> cislo;
			if (cislo > 1 || cislo < 0)
			{
				cout << "Vozidlo nebolo pridane (Zadany zly typ tovaru).";
				break;
			}

			if (!system->dajVozidla()->vytvorNoveVozidlo(nazov, Tovar::toTyp(cislo), *system->aktualnyDatum()))
			{
				cout << "\nVozidlo s nadou SPZ uz existuje!\n";
			}
			break;

		case 4:
			system->dajVozidla()->vypisVozidiel();
			break;

		case 5:
			cout << "\n\nZadajte nazov noveho zakaznika:\n";
			cin >> nazov;
			cout << "Ktory region \n( 1-8 ): ";
			cin >> cislo;
			if (cislo > 8 || cislo < 1)
			{
				cout << "Zakaznik nebol pridany (Zadany zly region).";
				break;
			}

			if (!system->dajZakaznikov()->vytvorZakaznika(nazov, cislo))
			{
				cout << "\nVozidlo s danou SPZ uz existuje!\n";
			}
			break;

		case 6:
			cout << "\n\nZadajte nazov zakaznika:\n";
			cin >> nazov;
			zakaznik = system->dajZakaznikov()->dajZakaznika(nazov);
			if (zakaznik != nullptr)
			{
				cout << "Ktory tovar \n(hranolky = 0, lupienky = 1): ";
				cin >> cislo;
				if (cislo > 1 || cislo < 0)
				{
					cout << "Objednavka nebola pridana (Zadany zly typ tovaru).\n";
					break;
				}
				cout << "\nMnozstvo: ";
				cin >> cislo2;
				cout << "\nJednotkova predajna cena: ";
				cin >> cislo3;
				cout << "\nDatum dorucenia: ";
				cin >> cislo4;

				if (!system->dajObjednavky()->vytvorNovuObjednavku(zakaznik, Tovar::toTyp(cislo), cislo2, cislo3, cislo4, system->dajVozidla()->dajKapacituVozidiel(Tovar::toTyp(cislo)), *system->aktualnyDatum()))
				{
					cout << "\nPridanie objednavky sa nepodarilo. Nespravne udaje!\n";
				}
			}
			else { cout << "Zakaznik so zadanym nazvom neexistuje!\n"; }
			break;

		case 7:
		case 9:
		case 10:
			cout << "\nFunkciu nie je mozne volat manualne!\n";
			break;

		case 8:
			system->dajObjednavky()->vypisObjednavok(*system->aktualnyDatum() + 1);
			break;

		case 11:
			cout << "Zadajte region, z ktoreho chcete vypisat zakaznikov:\n";
			cin >> cislo;
			if (cislo < 1 || cislo > 8)
			{
				cout << "\nNeplatny region!\n";
				break;
			}
			cout << "Zadajte datum od: ";
			cin >> cislo2;
			cout << "\nZadajte datum do: ";
			cin >> cislo3;

			system->vypisZakaznikov(cislo, cislo2, cislo3);
			break;

		case 12:
			cout << "Zadajte datum od: ";
			cin >> cislo;
			cout << "\nZadajte datum do: ";
			cin >> cislo2;

			system->dajObjednavky()->vypisZrealizovanychObjednavok(cislo, cislo2);
			break;

		case 13:
			cout << "Zadajte datum od: ";
			cin >> cislo;
			cout << "\nZadajte datum do: ";
			cin >> cislo2;

			system->dajObjednavky()->vypisNezrealizovanychObjednavok(cislo, cislo2);
			break;

		case 14:
			cout << "Ktory polotovar \n(zemiaky = 0, olej = 1, ochucovadla = 2): ";
			cin >> cislo;

			system->vypisNajuzitocnejsiehoFarmara(Polotovar::toTyp(cislo), *system->aktualnyDatum() - 30, *system->aktualnyDatum());
			break;

		case 15:
			cout << "Zadajte datum od: ";
			cin >> cislo;
			cout << "\nZadajte datum do: ";
			cin >> cislo2;

			system->vypisZiskFirmy(cislo, cislo2);
			break;

		case 16:
			system->zapisSa();
			break;

		case 17:
			system->testuj();
			break;

		case 18:
			cout << "\n*** Aktualny den: " << *system->aktualnyDatum() << ". ***\n\n";
			break;

		case 0:
			system->dalsiDen();
			break;

		default:
			delete infile;
			delete system;
			return 0;
		}
	}
	

	//system->testuj();
	//system->dalsiDen();
	//for (int i = 0; i < 20; ++i)
	//{
	//	system->dalsiDen();
	//}
	//system->vypisZiskFirmy(28, 41);
	//system->zapisSa();


	delete infile;
	delete system;

	return 0;
}


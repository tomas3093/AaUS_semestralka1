#include "stdafx.h"
#include "EvidenciaObjednavokTovaru.h"
#include "EvidenciaVozidiel.h"
#include "System.h"
#include <string>;
#include <sstream>
#include "ObjednavkaTovaru.h"

EvidenciaObjednavokTovaru::EvidenciaObjednavokTovaru()
	:objednavkyPodlaDatumuZaevidovania_(new structures::LinkedList<ObjednavkaTovaru *>()),
	zrealizovaneObjednavky_(new structures::LinkedList<ObjednavkaTovaru *>())
{
}


EvidenciaObjednavokTovaru::~EvidenciaObjednavokTovaru()
{
	for (ObjednavkaTovaru* const item : *objednavkyPodlaDatumuZaevidovania_)
	{
		delete item;
	}
	delete objednavkyPodlaDatumuZaevidovania_;
	delete zrealizovaneObjednavky_;
}

bool EvidenciaObjednavokTovaru::pridajObjednavku(ObjednavkaTovaru* novaObjednavka, double celkovaKapacitaVozidiel)
{
	double obsadenaKapacitaNaDanyDen = 0;
	for (ObjednavkaTovaru* const item : *objednavkyPodlaDatumuZaevidovania_)
	{
		if (item->dajDatumDorucenia() == novaObjednavka->dajDatumDorucenia() && item->dajTypTovaru() == novaObjednavka->dajTypTovaru())
		{
			obsadenaKapacitaNaDanyDen += item->dajMnozstvo();
		}
	}

	// Zistenie celkovej volnej kapacity vozidiel prevazajucich dany polotovar
	double volnaKapacitaVozidiel = celkovaKapacitaVozidiel - obsadenaKapacitaNaDanyDen;

	if (volnaKapacitaVozidiel < novaObjednavka->dajMnozstvo())
	{
		// Zamietnutie objednavky z dovodu nedostatku volnej kapacity
		novaObjednavka->zmenStav(StavObjednavky::ZAMIETNUTA);
	}

	// Vlozenie objednavky do evidencie na spravne miesto
	int index = 0;
	for (ObjednavkaTovaru* const item : *objednavkyPodlaDatumuZaevidovania_)
	{
		if (novaObjednavka->dajDatumZaevidovania() <= item->dajDatumZaevidovania())
		{
			objednavkyPodlaDatumuZaevidovania_->insert(novaObjednavka, index);
			return true;
		}
		index++;
	}

	// Vlozenie na koniec.
	objednavkyPodlaDatumuZaevidovania_->add(novaObjednavka);
	return true;
}

bool EvidenciaObjednavokTovaru::vytvorNovuObjednavku(Zakaznik* zakaznik, Tovar::Typ typTovaru, double mnozstvo,
	double jednotkovaPredajnaCena, Datum datumDorucenia, double celkovaKapacitaVozidiel, Datum aktualnyDatum)
{
	// Datum dorucenia mensi ako 7 dni od aktualneho datumu
	if (datumDorucenia < aktualnyDatum + POCET_DNI_DODANIE_TOVARU)
	{
		// ObjednavkaTovaru sa do systemu nevlozi
		stringstream message;
		message << "Datum dorucenia musi byt minimalne " << POCET_DNI_DODANIE_TOVARU << " dni od aktualneho datumu!";
		showErrorMessage(message.str());
		return false;
	}

	// Vytvori a pokusi sa vlozit objednavku do evidencie
	ObjednavkaTovaru * novaObjednavka = new ObjednavkaTovaru(zakaznik, typTovaru, mnozstvo, jednotkovaPredajnaCena,
		aktualnyDatum, datumDorucenia,StavObjednavky::SPRACOVAVANA);

	if (!pridajObjednavku(novaObjednavka, celkovaKapacitaVozidiel))
	{
		delete novaObjednavka;
		return false;
	}
	return true;
}

double EvidenciaObjednavokTovaru::dajPoziadavkyNaTovar(Tovar::Typ typTovaru, Datum aktualnyDatum)
{
	double mnozstvoTovaru = 0;
	for (ObjednavkaTovaru* const item : *objednavkyPodlaDatumuZaevidovania_)
	{
		Datum datumDorucenia = item->dajDatumDorucenia();
		if (datumDorucenia > aktualnyDatum && datumDorucenia < aktualnyDatum + POCET_DNI_DODANIE_TOVARU)
		{
			if (item->dajStav() == StavObjednavky::SPRACOVAVANA && item->dajTypTovaru() == typTovaru)
			{
				mnozstvoTovaru += item->dajMnozstvo();
			}
		}
	}
	return mnozstvoTovaru;
}

double EvidenciaObjednavokTovaru::zrealizujObjednavkyDna(Datum datum)
{
	double celkovaCenaObjednavok = 0;

	for (ObjednavkaTovaru* const item : *objednavkyPodlaDatumuZaevidovania_)
	{
		if (item->dajDatumDorucenia() == datum && item->dajStav() == StavObjednavky::SPRACOVAVANA)
		{
			item->zmenStav(StavObjednavky::ZREALIZOVANA);
			celkovaCenaObjednavok += item->dajMnozstvo() * item->dajJednotkovuPredajnuCenu();

			// Vlozenie zrealizovanej objednavky na spravne miesto zoznamu zrealizovanych objednavok
			int index = 0;
			bool bolaVlozena = false;
			for (ObjednavkaTovaru* const zrealizovana : *zrealizovaneObjednavky_)
			{
				if (item->dajDatumDorucenia() <= zrealizovana->dajDatumDorucenia())
				{
					zrealizovaneObjednavky_->insert(item, index);
					bolaVlozena = true;
					break;
				}
				index++;
			}
			if (!bolaVlozena)
			{
				zrealizovaneObjednavky_->add(item);
			}
		}
	}

	return celkovaCenaObjednavok;
}

void EvidenciaObjednavokTovaru::vypisZrealizovanychObjednavok(Datum datumOd, Datum datumDo)
{
	cout << "\nZREALIZOVANE OBJEDNAVKY TOVARU S DATUMOM DORUCENIA MEDZI " << datumOd << ". a " << datumDo << ". :\n\n";
	for (ObjednavkaTovaru* const item : *zrealizovaneObjednavky_)
	{
		if (item->dajDatumDorucenia() >= datumOd && item->dajDatumDorucenia() <= datumDo)
		{
			cout << "Datum dorucenia: " << item->dajDatumDorucenia() << "." << endl;
			cout << "Zakaznik: " << item->dajZakaznika()->dajNazov() << endl;
			cout << "Tovar: " << Tovar::toString(item->dajTypTovaru()) << endl;
			cout << "Mnozstvo: " << item->dajMnozstvo() << endl;
			cout << "Trzby: " << (item->dajMnozstvo() * item->dajJednotkovuPredajnuCenu()) << "\n\n";
		}
	}
}

void EvidenciaObjednavokTovaru::vypisNezrealizovanychObjednavok(Datum datumOd, Datum datumDo)
{
	cout << "\nNEZREALIZOVANE OBJEDNAVKY TOVARU S DATUMOM DORUCENIA MEDZI " << datumOd << ". a " << datumDo << ". :\n\n";
	for (ObjednavkaTovaru* const item : *objednavkyPodlaDatumuZaevidovania_)
	{
		if ((item->dajStav() == StavObjednavky::ZAMIETNUTA || item->dajStav() == StavObjednavky::ZRUSENA) && item->dajDatumDorucenia() >= datumOd && item->dajDatumDorucenia() <= datumDo)
		{
			cout << "Datum zaevidovania: " << item->dajDatumZaevidovania() << "." << endl;
			cout << "Zakaznik: " << item->dajZakaznika()->dajNazov() << endl;
			cout << "Tovar: " << Tovar::toString(item->dajTypTovaru()) << endl;
			cout << "Mnozstvo: " << item->dajMnozstvo() << endl;
			cout << "Trzby: " << (item->dajMnozstvo() * item->dajJednotkovuPredajnuCenu()) << "\n\n";
		}
	}
}

void EvidenciaObjednavokTovaru::vypisObjednavok(Datum datum)
{
	cout << "\nOBJEDNAVKY TOVARU, KTORE BUDU ZREALIZOVANE " << datum << ". :\n\n";
	for (ObjednavkaTovaru* const item : *objednavkyPodlaDatumuZaevidovania_)
	{
		if (item->dajDatumDorucenia() == datum && (item->dajStav() == StavObjednavky::SPRACOVAVANA || item->dajStav() == StavObjednavky::ZRUSENA))
		{
			double mnozstvo = item->dajMnozstvo();
			double jednotkovaCena = item->dajJednotkovuPredajnuCenu();

			cout << "Zakaznik: " << item->dajZakaznika()->dajNazov() << endl;
			cout << "Region zakaznika: " << item->dajZakaznika()->dajRegion() << endl;
			cout << "Datum zaevidovania: " << item->dajDatumZaevidovania() << "." << endl;
			cout << "Tovar: " << Tovar::toString(item->dajTypTovaru()) << endl;
			cout << "Mnozstvo: " << mnozstvo << endl;
			cout << "Jednotkova cena: " << jednotkovaCena << endl;
			cout << "Trzby: " << (mnozstvo * jednotkovaCena) << endl;
			cout << "Stav: " << dajNazovStavObjednavky(item->dajStav()) << "\n\n";
		}
	}
}

structures::LinkedList<ObjednavkaTovaru*>* EvidenciaObjednavokTovaru::dajObjednavkyPodlaTrzieb(Datum datumDorucenia)
{
	structures::LinkedList<ObjednavkaTovaru*> * objednavkyNaDanyDen = new structures::LinkedList<ObjednavkaTovaru*>();
	
	// Vytvori zoznam usporiadany podla trzieb, od najnizsich po najvacsie
	for (ObjednavkaTovaru* const aktualnaObjednavka : *objednavkyPodlaDatumuZaevidovania_)
	{
		if (aktualnaObjednavka->dajDatumDorucenia() == datumDorucenia && aktualnaObjednavka->dajStav() == StavObjednavky::SPRACOVAVANA)
		{
			double trzbyAktualnejObjednavky = aktualnaObjednavka->dajJednotkovuPredajnuCenu() * aktualnaObjednavka->dajMnozstvo();
			
			// Vlozi aktualnuObjednavku na spravne miesto
			int index = 0;
			for (ObjednavkaTovaru* const item : *objednavkyNaDanyDen)
			{
				double trzbyItem = item->dajJednotkovuPredajnuCenu() * item->dajMnozstvo();
				if (trzbyItem < trzbyAktualnejObjednavky)
				{
					break;
				}
				index++;
			}
			// Vlozenie do prazdneho zoznamu.
			objednavkyNaDanyDen->insert(aktualnaObjednavka, index);
		}
	}

	return objednavkyNaDanyDen;
}

structures::LinkedList<ObjednavkaTovaru*>* EvidenciaObjednavokTovaru::dajObjednavkyPodlaRegionov(Datum datumDorucenia)
{
	structures::LinkedList<ObjednavkaTovaru*> * objednavkyNaDanyDen = new structures::LinkedList<ObjednavkaTovaru*>();

	// Vytvori zoznam usporiadany podla trzieb, od najnizsich po najvacsie
	for (ObjednavkaTovaru* const aktualnaObjednavka : *objednavkyPodlaDatumuZaevidovania_)
	{
		if (aktualnaObjednavka->dajDatumDorucenia() == datumDorucenia && aktualnaObjednavka->dajStav() == StavObjednavky::SPRACOVAVANA)
		{
			size_t regionAktualnejObjednavky = aktualnaObjednavka->dajZakaznika()->dajRegion();

			// Vlozi aktualnuObjednavku na spravne miesto
			int index = 0;
			bool bolVlozeny = false;
			for (ObjednavkaTovaru* const item : *objednavkyNaDanyDen)
			{
				size_t regionItem = item->dajZakaznika()->dajRegion();
				if (regionItem >= regionAktualnejObjednavky)
				{
					objednavkyNaDanyDen->insert(aktualnaObjednavka, index);
					bolVlozeny = true;
					break;
				}
				index++;
			}
			if (!bolVlozeny)
			{
				objednavkyNaDanyDen->add(aktualnaObjednavka);
			}
		}
	}

	return objednavkyNaDanyDen;
}

void EvidenciaObjednavokTovaru::zapisSa(ofstream* outFile)
{
	*outFile << objednavkyPodlaDatumuZaevidovania_->size() << endl;
	for (ObjednavkaTovaru* const item : *objednavkyPodlaDatumuZaevidovania_)
	{
		item->zapisSa(outFile);
	}
}

void EvidenciaObjednavokTovaru::nacitajSa(ifstream* inFile, EvidenciaZakaznikov * zakaznici)
{
	size_t pocet;
	*inFile >> pocet;
	for (int i = 0; i < pocet; ++i)
	{
		ObjednavkaTovaru * novy = new ObjednavkaTovaru();
		novy->nacitajSa(inFile, zakaznici);
		objednavkyPodlaDatumuZaevidovania_->add(novy);
	}

	// Naplnenie zoznamu zrealizovanych objednavok
	for (ObjednavkaTovaru* const item : *objednavkyPodlaDatumuZaevidovania_)
	{
		if (item->dajStav() == StavObjednavky::ZREALIZOVANA)
		{
			// Vlozenie zrealizovanej objednavky na spravne miesto zoznamu zrealizovanych objednavok
			for (int i = 0; i < zrealizovaneObjednavky_->size(); ++i)
			{
				if (item->dajDatumDorucenia() <= (*zrealizovaneObjednavky_)[i]->dajDatumDorucenia())
				{
					zrealizovaneObjednavky_->insert(item, i);
					break;
				}
			}
			// Vlozenie na koniec zoznamu
			zrealizovaneObjednavky_->insert(item, zrealizovaneObjednavky_->size());
		}
	}
}

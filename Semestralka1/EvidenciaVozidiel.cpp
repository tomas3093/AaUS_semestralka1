#include "stdafx.h"
#include "EvidenciaVozidiel.h"
#include "NaplnaneVozidlo.h"

EvidenciaVozidiel::EvidenciaVozidiel()
	:vozidlaPodlaDatumu_(new structures::LinkedList<Vozidlo *>)
{
}

EvidenciaVozidiel::~EvidenciaVozidiel()
{
	for (Vozidlo* const item : *vozidlaPodlaDatumu_)
	{
		delete item;
	}
	delete vozidlaPodlaDatumu_;
}

bool EvidenciaVozidiel::vytvorNoveVozidlo(string spz, Tovar::Typ typTovaru, size_t datumZaradenia)
{
	Vozidlo * noveVozidlo = new Vozidlo(spz, typTovaru, datumZaradenia);
	if (EvidenciaVozidiel::pridajVozidlo(noveVozidlo))
	{
		return true;
	}
	delete noveVozidlo;
	return false;
}

double EvidenciaVozidiel::naplnVozidla(structures::LinkedList<ObjednavkaTovaru*>* objednavkyPodlaRegionov)
{
	double celkoveNakladyNaRozvozObjednavok = 0;

	structures::LinkedList<ObjednavkaTovaru *> zostavajuceObjednavky = *objednavkyPodlaRegionov;

	// Prechadza vsetky typy tovaru
	for (int i = 0; i < Tovar::pocetTypov; ++i)
	{
		Tovar::Typ typTovaru = static_cast<Tovar::Typ>(i);
		
		// Vytvorenie zoznamu naplnanych vozidiel
		structures::LinkedList<Vozidlo *> * dostupneVozidla = dajZoznamVozidielTypu(typTovaru);
		structures::LinkedList<NaplnaneVozidlo *> * naplnaneVozidla = new structures::LinkedList<NaplnaneVozidlo *>();
		for (Vozidlo* const item : *dostupneVozidla)
		{
			NaplnaneVozidlo * noveNaplnaneVozidlo = new NaplnaneVozidlo(item);
			naplnaneVozidla->add(noveNaplnaneVozidlo);
		}


		// Prechadza dostupne vozidla pokial nerozdeli vsetky objednavky
		while (zostavajuceObjednavky.size() > 0)
		{
			for (NaplnaneVozidlo* const naplnaneVozidlo : *naplnaneVozidla)
			{
				// Ak uz su vsetky objednavky vo vozidlach, skonci naplnanie
				if (zostavajuceObjednavky.size() == 0)
				{
					break;
				}

				// Prechadza objednavky jedneho regionu a naklada ich do vozidiel kym nenarazi na objednavku z ineho regionu
				size_t aktualnyRegion = (*zostavajuceObjednavky[0]).dajZakaznika()->dajRegion();
				structures::LinkedList<ObjednavkaTovaru *> * naOdobratie = new structures::LinkedList<ObjednavkaTovaru*>();
				for (ObjednavkaTovaru* const objednavka : zostavajuceObjednavky)
				{
					// Ak sa zmeni region objednavok
					if (objednavka->dajZakaznika()->dajRegion() != aktualnyRegion)
					{
						break;
					}

					// Prida objednavku do vozidla
					if (naplnaneVozidlo->pridajObjednavku(objednavka))
					{
						naOdobratie->add(objednavka);
					}
				}

				// Dealokovanie docasneho zoznamu
				for (ObjednavkaTovaru* const item : *naOdobratie)
				{
					zostavajuceObjednavky.tryRemove(item);
				}
				delete naOdobratie;
			}
		}

		// Vypocet prevadzkovych nakladov vozidiel a dealokovanie pamate
		for (NaplnaneVozidlo* const item : *naplnaneVozidla)
		{
			int prevadzkoveNakladyJazdy = item->dajPrevadzkoveNakladyJazdy();
			celkoveNakladyNaRozvozObjednavok += prevadzkoveNakladyJazdy;
			item->dajVozidlo()->zvysPrevadzkoveNaklady(prevadzkoveNakladyJazdy);
			delete item;
		}
		delete naplnaneVozidla;
		delete dostupneVozidla;
	}
	delete objednavkyPodlaRegionov;

	return celkoveNakladyNaRozvozObjednavok;
}

bool EvidenciaVozidiel::pridajVozidlo(Vozidlo* noveVozidlo)
{
	// Pridanie do prazdneho zoznamu
	if (vozidlaPodlaDatumu_->size() == 0)
	{
		vozidlaPodlaDatumu_->add(noveVozidlo);
		return true;
	}

	Datum noveVozidloDatum = noveVozidlo->dajDatumZaradenia();
	string noveSpz = noveVozidlo->dajSpz();

	// Vlozenie vozidla na spravne miesto
	int index = 0;
	for (Vozidlo* const item : *vozidlaPodlaDatumu_)
	{
		if (noveSpz == item->dajSpz())
		{
			// Vozidlo s danou SPZ uz existuje
			showErrorMessage("Vozidlo s SPZ " + noveSpz + " uz existuje!");
			return false;
		}
		if (noveVozidloDatum < item->dajDatumZaradenia())
		{
			int novyIndex = vozidlaPodlaDatumu_->getIndexOf(item);
			vozidlaPodlaDatumu_->insert(noveVozidlo, index);
			return true;
		}
		index++;
	}

	// Vlozenie na koniec.
	vozidlaPodlaDatumu_->add(noveVozidlo);
	return true;
}

structures::LinkedList<Vozidlo*>* EvidenciaVozidiel::dajZoznamVozidielTypu(Tovar::Typ typTovaru)
{
	structures::LinkedList<Vozidlo *> * vozidlaDanehoTypu = new structures::LinkedList<Vozidlo*>();
	for (Vozidlo* const item : *vozidlaPodlaDatumu_)
	{
		if (item->dajTyp() == typTovaru)
		{
			vozidlaDanehoTypu->add(item);
		}
	}
	return vozidlaDanehoTypu;
}

void EvidenciaVozidiel::vypisVozidiel()
{
	cout << "\nVOZIDLA:\n\n";
	for (Vozidlo* const item : *vozidlaPodlaDatumu_)
	{
		cout << "Vozidlo: " << item->dajSpz() << endl;
		cout << "\tTovar (Typ): " << Tovar::toString(item->dajTyp()) << endl;
		cout << "\tDatum zaradenia do evidencie: " << item->dajDatumZaradenia() << ". den" << endl;
		cout << "\tCelkove prevadzkove naklady: " << item->dajPrevadzkoveNaklady() << " Eur\n\n" << endl;
	}
}

size_t EvidenciaVozidiel::dajKapacituVozidiel(Tovar::Typ typTovaru)
{
	size_t kapacita = 0;
	for (Vozidlo* const item : *vozidlaPodlaDatumu_)
	{
		if (item->dajTyp() == typTovaru)
		{
			kapacita += item->dajNosnostVozidla();
		}
	}
	return kapacita;
}

void EvidenciaVozidiel::zapisSa(ofstream* outFile)
{
	*outFile << vozidlaPodlaDatumu_->size() << endl;
	for (Vozidlo* const item : *vozidlaPodlaDatumu_)
	{
		item->zapisSa(outFile);
	}
}

void EvidenciaVozidiel::nacitajSa(ifstream* inFile)
{
	size_t pocet;
	*inFile >> pocet;
	for (int i = 0; i < pocet; ++i)
	{
		Vozidlo * novy = new Vozidlo();
		novy->nacitajSa(inFile);
		vozidlaPodlaDatumu_->add(novy);
	}
}

#include "stdafx.h"
#include "EvidenciaZakaznikov.h"
#include "Vozidlo.h"
#include "structures/list/linked_list.h"

EvidenciaZakaznikov::EvidenciaZakaznikov()
	:zakazniciPodlaAbecedy_(new structures::LinkedList<Zakaznik *>)
{
}

EvidenciaZakaznikov::~EvidenciaZakaznikov()
{
	for (Zakaznik* const item : *zakazniciPodlaAbecedy_)
	{
		delete item;
	}
	delete zakazniciPodlaAbecedy_;
}

Zakaznik* EvidenciaZakaznikov::dajZakaznika(string nazovZakaznika)
{
	for (Zakaznik* const item : *zakazniciPodlaAbecedy_)
	{
		if (item->dajNazov() == nazovZakaznika)
		{
			return item;
		}
	}
	return nullptr;
}

structures::List<Zakaznik*>* EvidenciaZakaznikov::dajZakaznikov(size_t region)
{
	structures::List<Zakaznik *> * zakazniciZRegionu = new structures::LinkedList<Zakaznik*>();
	for (Zakaznik* const item : *zakazniciPodlaAbecedy_)
	{
		if (item->dajRegion() == region)
		{
			zakazniciZRegionu->add(item);
		}
	}
	return zakazniciZRegionu;
}

bool EvidenciaZakaznikov::vytvorZakaznika(string nazovNovehoZakaznika, size_t region)
{
	Zakaznik * novyZakaznik = new Zakaznik(nazovNovehoZakaznika, region);
	if (EvidenciaZakaznikov::pridajZakaznika(novyZakaznik))
	{
		return true;
	}
	delete novyZakaznik;
	return false;
}

void EvidenciaZakaznikov::zapisSa(ofstream* outFile)
{
	*outFile << zakazniciPodlaAbecedy_->size() << endl;
	for (Zakaznik* const item : *zakazniciPodlaAbecedy_)
	{
		item->zapisSa(outFile);
	}
}

void EvidenciaZakaznikov::nacitajSa(ifstream* inFile)
{
	size_t pocet;
	*inFile >> pocet;
	for (int i = 0; i < pocet; ++i)
	{
		Zakaznik * novy = new Zakaznik();
		novy->nacitajSa(inFile);
		zakazniciPodlaAbecedy_->add(novy);
	}
}

bool EvidenciaZakaznikov::pridajZakaznika(Zakaznik* novyZakaznik)
{
	// Pridanie do prazdneho zoznamu
	if (zakazniciPodlaAbecedy_->size() == 0)
	{
		zakazniciPodlaAbecedy_->add(novyZakaznik);
		return true;
	}

	string novyZakaznikNazov = novyZakaznik->dajNazov();

	// Vlozenie zakaznika na spravne miesto
	int index = 0;
	for (Zakaznik* const item : *zakazniciPodlaAbecedy_)
	{
		if (novyZakaznikNazov == item->dajNazov())
		{
			// Zakaznik uz existuje
			showErrorMessage("Zakaznik s nazvom " + novyZakaznikNazov + " uz existuje!");
			return false;
		}
		if (novyZakaznikNazov < item->dajNazov())
		{
			zakazniciPodlaAbecedy_->insert(novyZakaznik, index);
			return true;
		}
		index++;
	}

	// Vlozenie na koniec.
	zakazniciPodlaAbecedy_->add(novyZakaznik);
	return true;
}

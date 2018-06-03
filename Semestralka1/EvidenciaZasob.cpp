#include "stdafx.h"
#include "EvidenciaZasob.h"
#include "MnozstvoPolotovaru.h"
#include "structures/list/linked_list.h"


EvidenciaZasob::EvidenciaZasob()
	:skladoveZasoby_(new structures::LinkedList<MnozstvoPolotovaru *>()),
	objednaneZasoby_(new structures::LinkedList<MnozstvoPolotovaru *>()),
	zoznamObjednavokPolotovarov_(new structures::LinkedList<ObjednavkaPolotovaru *>())
{
}


EvidenciaZasob::~EvidenciaZasob()
{
	for (MnozstvoPolotovaru* const item : *skladoveZasoby_)
	{
		delete item;
	}
	delete skladoveZasoby_;

	for (MnozstvoPolotovaru* const item : *objednaneZasoby_)
	{
		delete item;
	}
	delete objednaneZasoby_;

	for (ObjednavkaPolotovaru* const item : *zoznamObjednavokPolotovarov_)
	{
		delete item;
	}
	delete zoznamObjednavokPolotovarov_;
}

void EvidenciaZasob::pridajZasobu(Polotovar::Typ typPolotovaru, double mnozstvo)
{
	if (mnozstvo < 0)
	{
		showErrorMessage("Mnozstvo musi byt nezaporne!");
		return;
	}

	for (MnozstvoPolotovaru* const item : *skladoveZasoby_)
	{
		// Ak uz taka zasoba existuje, iba zmeni mnozstvo
		if (item->dajTypPolotovaru() == typPolotovaru)
		{
			item->zmenMnozstvo(mnozstvo);
			return;
		}
	}

	// Vytvori novu, pretoze este taka zasoba neexistuje
	MnozstvoPolotovaru * novaZasoba = new MnozstvoPolotovaru(typPolotovaru, mnozstvo);
	skladoveZasoby_->add(novaZasoba);
}

bool EvidenciaZasob::odoberZasobu(Polotovar::Typ typPolotovaru, double mnozstvo)
{
	double mnozstvoZasobyNaSklade = dajMnozstvoNaSklade(typPolotovaru);
	if (mnozstvoZasobyNaSklade >= mnozstvo)
	{
		for (MnozstvoPolotovaru* const item : *skladoveZasoby_)
		{
			if (item->dajTypPolotovaru() == typPolotovaru)
			{
				item->zmenMnozstvo(-mnozstvo);
				break;
			}
		}
		return true;
	}

	// Zasoba nie je dostatocna
	return false;
}

double EvidenciaZasob::dajMnozstvoNaSklade(Polotovar::Typ typPolotovaru)
{
	for (MnozstvoPolotovaru* const item : *skladoveZasoby_)
	{
		if (item->dajTypPolotovaru() == typPolotovaru)
		{
			return item->dajMnozstvo();
		}
	}
	return 0;
}

void EvidenciaZasob::pridajObjednavkuPolotovaru(ObjednavkaPolotovaru* novaObjednavka)
{
	// Vlozenie objednavky do evidencie na spravne miesto
	int index = 0;
	for (ObjednavkaPolotovaru* const item : *zoznamObjednavokPolotovarov_)
	{
		if (novaObjednavka->dajDatumObjednania() <= item->dajDatumObjednania())
		{
			zoznamObjednavokPolotovarov_->insert(novaObjednavka, index);

			// Pridanie objednanych zasob do zoznamu objednanych zasob
			pridajObjednanuZasobu(novaObjednavka->dajTypPolotovaru(), novaObjednavka->dajMnozstvo());
			return;
		}
		index++;
	}
	// Vlozenie do prazdneho zoznamu.
	zoznamObjednavokPolotovarov_->add(novaObjednavka);

	// Pridanie objednanych zasob do zoznamu objednanych zasob
	pridajObjednanuZasobu(novaObjednavka->dajTypPolotovaru(), novaObjednavka->dajMnozstvo());
}

void EvidenciaZasob::pridajObjednanuZasobu(Polotovar::Typ typPolotovaru, double mnozstvo)
{
	if (mnozstvo < 0)
	{
		showErrorMessage("Mnozstvo musi byt nezaporne!");
		return;
	}

	for (MnozstvoPolotovaru* const item : *objednaneZasoby_)
	{
		// Ak uz taka zasoba existuje, iba zmeni mnozstvo
		if (item->dajTypPolotovaru() == typPolotovaru)
		{
			item->zmenMnozstvo(mnozstvo);
			return;
		}
	}

	// Vytvori novu, pretoze este taka zasoba neexistuje
	MnozstvoPolotovaru * novaZasoba = new MnozstvoPolotovaru(typPolotovaru, mnozstvo);
	objednaneZasoby_->add(novaZasoba);
}

void EvidenciaZasob::aktualizuj()
{
	for (MnozstvoPolotovaru* const item : *objednaneZasoby_)
	{
		if (item->dajMnozstvo() > 0)
		{
			pridajZasobu(item->dajTypPolotovaru(), item->dajMnozstvo());
			item->zmenMnozstvo(-item->dajMnozstvo());	// Vynuluje mnozstvo objednanej zasoby
		}
	}
}

void EvidenciaZasob::zapisSa(ofstream* outFile)
{
	*outFile << skladoveZasoby_->size() << endl;
	for (MnozstvoPolotovaru* const item : *skladoveZasoby_)
	{
		item->zapisSa(outFile);
	}

	*outFile << objednaneZasoby_->size() << endl;
	for (MnozstvoPolotovaru* const item : *objednaneZasoby_)
	{
		item->zapisSa(outFile);
	}

	*outFile << zoznamObjednavokPolotovarov_->size() << endl;
	for (ObjednavkaPolotovaru* const item : *zoznamObjednavokPolotovarov_)
	{
		item->zapisSa(outFile);
	}
}

void EvidenciaZasob::nacitajSa(ifstream* inFile, EvidenciaBioFarmarov * biofarmari)
{
	size_t pocet;
	*inFile >> pocet;
	for (int i = 0; i < pocet; ++i)
	{
		MnozstvoPolotovaru * novy = new MnozstvoPolotovaru();
		novy->nacitajSa(inFile);
		skladoveZasoby_->add(novy);
	}

	*inFile >> pocet;
	for (int i = 0; i < pocet; ++i)
	{
		MnozstvoPolotovaru * novy = new MnozstvoPolotovaru();
		novy->nacitajSa(inFile);
		objednaneZasoby_->add(novy);
	}

	*inFile >> pocet;
	for (int i = 0; i < pocet; ++i)
	{
		ObjednavkaPolotovaru * novy = new ObjednavkaPolotovaru();
		novy->nacitajSa(inFile, biofarmari);
		zoznamObjednavokPolotovarov_->add(novy);
	}

}

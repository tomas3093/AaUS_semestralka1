#include "stdafx.h"

#include "types.h"
#include "EvidenciaBioFarmarov.h"
#include "structures/list/linked_list.h"


EvidenciaBioFarmarov::EvidenciaBioFarmarov()
	:farmariPodlaAbecedy_(new structures::LinkedList<BioFarmar *>()), 
	farmariPodlaPriemCien_(new structures::LinkedList<PriemernaCenaPolotovaru *>())
{
}

EvidenciaBioFarmarov::~EvidenciaBioFarmarov()
{
	for (BioFarmar* const item : *farmariPodlaAbecedy_)
	{
		delete item;
	}
	delete farmariPodlaAbecedy_;

	for (PriemernaCenaPolotovaru* const item : *farmariPodlaPriemCien_)
	{
		delete item;
	}
	delete farmariPodlaPriemCien_;
}

bool EvidenciaBioFarmarov::vytvorBioFarmara(string nazovNovehoBioFarmara)
{
	BioFarmar * novyFarmar = new BioFarmar(nazovNovehoBioFarmara);
	if (EvidenciaBioFarmarov::pridajBioFarmara(novyFarmar))
	{
		return true;
	}
	delete novyFarmar;
	return false;
}

bool EvidenciaBioFarmarov::pridajProduktBioFarmarovi(string nazovBioFarmara, Polotovar::Typ typPolotovaru)
{
	BioFarmar * farmar = dajFarmara(nazovBioFarmara);
	if (farmar != nullptr)
	{
		farmar->pridajNovyPolotovar(typPolotovaru);
		PriemernaCenaPolotovaru * priemernaCena = new PriemernaCenaPolotovaru(farmar, typPolotovaru, 0);

		// Pridanie na zaciatok, kedze priemerna cena je zatial nulova
		farmariPodlaPriemCien_->insert(priemernaCena, 0);
		return true;
	}

	return false;
}

BioFarmar* EvidenciaBioFarmarov::dajFarmara(string nazovFarmara)
{
	for (BioFarmar* const item : *farmariPodlaAbecedy_)
	{
		if (item->dajNazov() == nazovFarmara)
		{
			return item;
		}
	}
	return nullptr;
}

void EvidenciaBioFarmarov::zoradPodlaPriemCien(BioFarmar* bioFarmar, Polotovar::Typ typPolotovaru)
{
	PriemernaCenaPolotovaru * naZmazanie;
	for (PriemernaCenaPolotovaru* const item : *farmariPodlaPriemCien_)
	{
		// Stary zaznam
		if (item->dajBioFarmara() == bioFarmar && item->dajTypPolotovaru() == typPolotovaru)
		{
			naZmazanie = item;
			break;
		}
	}
	// Vymaze stary zaznam
	farmariPodlaPriemCien_->tryRemove(naZmazanie);
	delete naZmazanie;

	PriemernaCenaPolotovaru * novyZaznam = new PriemernaCenaPolotovaru(bioFarmar, typPolotovaru, bioFarmar->dajPriemernuCenuPolotovaru(typPolotovaru));
	// Vlozi novy zaznam na spravne miesto
	int index = 0;
	for (PriemernaCenaPolotovaru* const item : *farmariPodlaPriemCien_)
	{
		if (item->dajTypPolotovaru() == typPolotovaru && novyZaznam->dajPriemernuCenu() <= item->dajPriemernuCenu())
		{
			farmariPodlaPriemCien_->insert(novyZaznam, index);
			return;
		}
		index++;
	}
	// Vlozenie na zaciatok, ak je zoznam prazdny
	farmariPodlaPriemCien_->add(novyZaznam);
}

void EvidenciaBioFarmarov::vypisBioFarmarovPodlaPolotovaru(Polotovar::Typ typPolotovaru)
{
	cout << "\nBIOFARMARI DODAVAJUCI " << Polotovar::toString(typPolotovaru) << ":\n\n";
	structures::List<BioFarmar *> * zoznam = farmariPodlaAbecedy_;
	if (zoznam->size() > 0)
	{
		for (BioFarmar* const farmar : *zoznam)
		{
			if (farmar->dodavaPolotovar(typPolotovaru))
			{
				cout << "BioFarmar: " << farmar->dajNazov() << endl;
				cout << "Polotovary:\n";

				structures::Array<Polotovar::Typ> * typyPolotovarov = farmar->dajPolotovary();
				for (int i = 0; i < typyPolotovarov->size(); i++)
				{
					cout << "\tPolotovar: " << Polotovar::toString((*typyPolotovarov)[i]) << "\n\tPriemerna cena: " << farmar->dajPriemernuCenuPolotovaru(typPolotovaru) << " Eur\n\n";
				}
				delete typyPolotovarov;
			}
			cout << "\n";
		}
	}
	else
	{
		cout << "Zoznam je prazdny!";
	}
}

void EvidenciaBioFarmarov::aktualizuj()
{
	for (BioFarmar* const item : *farmariPodlaAbecedy_)
	{
		item->aktualizuj();
	}
}

void EvidenciaBioFarmarov::zapisSa(ofstream * outFile)
{
	*outFile << farmariPodlaAbecedy_->size() << endl;
	for (BioFarmar* const item : *farmariPodlaAbecedy_)
	{
		item->zapisSa(outFile);
	}
}

void EvidenciaBioFarmarov::nacitajSa(ifstream * inFile)
{
	size_t pocet;
	*inFile >> pocet;
	for (int i = 0; i < pocet; ++i)
	{
		BioFarmar * novy = new BioFarmar();
		novy->nacitajSa(inFile);
		farmariPodlaAbecedy_->add(novy);
	}

	// Vytvorenie usporiadaneho zoznamu priemernych cien
	for (BioFarmar* const farmar : *farmariPodlaAbecedy_)
	{
		structures::Array<Polotovar::Typ> * polotovaryFarmara = farmar->dajPolotovary();
		for (int i = 0; i < polotovaryFarmara->size(); ++i)
		{
			Polotovar::Typ typPolotovaru = (*polotovaryFarmara)[i];
			double priemernaCena = farmar->dajPriemernuCenuPolotovaru(typPolotovaru);
			PriemernaCenaPolotovaru * priemCenaPolotovaru = new PriemernaCenaPolotovaru(farmar, typPolotovaru, priemernaCena);

			if (farmariPodlaPriemCien_->size() == 0)
			{
				farmariPodlaPriemCien_->add(priemCenaPolotovaru);
				continue;
			}

			int index = 0;
			int indexPoslednehoDanehoTypu = -1;
			bool bolVlozeny = false;
			for (PriemernaCenaPolotovaru* const item : *farmariPodlaPriemCien_)
			{
				if (item->dajTypPolotovaru() == typPolotovaru)
				{
					if (priemernaCena <= item->dajPriemernuCenu())
					{
						farmariPodlaPriemCien_->insert(priemCenaPolotovaru, index);
						bolVlozeny = true;
						break;
					}
					indexPoslednehoDanehoTypu = index;
				}
				index++;
			}
			if (!bolVlozeny)
			{
				if (indexPoslednehoDanehoTypu + 1 < farmariPodlaPriemCien_->size())
				{
					farmariPodlaPriemCien_->insert(priemCenaPolotovaru, indexPoslednehoDanehoTypu + 1);
				}
				else
				{
					farmariPodlaPriemCien_->add(priemCenaPolotovaru);
				}
			}
		}
		delete polotovaryFarmara;
	}
}

bool EvidenciaBioFarmarov::pridajBioFarmara(BioFarmar* novyFarmar)
{
	// Pridanie do prazdneho zoznamu
	if (farmariPodlaAbecedy_->size() == 0)
	{
		farmariPodlaAbecedy_->add(novyFarmar);
		return true;
	}

	string novyFarmarNazov = novyFarmar->dajNazov();

	// Vlozenie farmara na spravne miesto
	int index = 0;
	for (BioFarmar* const item : *farmariPodlaAbecedy_)
	{
		if (novyFarmarNazov == item->dajNazov())
		{
			// Farmar uz existuje
			showErrorMessage("Farmar s nazvom " + novyFarmarNazov + " uz existuje!");
			return false;
		}
		if (novyFarmarNazov < item->dajNazov())
		{
			farmariPodlaAbecedy_->insert(novyFarmar, index);
			return true;
		}
		index++;
	}

	// Vlozenie na koniec.
	farmariPodlaAbecedy_->add(novyFarmar);
	return true;
}

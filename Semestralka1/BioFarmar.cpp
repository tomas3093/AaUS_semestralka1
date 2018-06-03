#include "stdafx.h"
#include "BioFarmar.h"
#include "structures/list/linked_list.h"


BioFarmar::BioFarmar()
	:nazov_(""), dodavanePolotovary_(new structures::LinkedList<UdajePolotovar*>())
{
}

BioFarmar::BioFarmar(string nazov)
	:nazov_(nazov), dodavanePolotovary_(new structures::LinkedList<UdajePolotovar*>())
{
}

BioFarmar::~BioFarmar()
{
	if (dodavanePolotovary_->size() > 0)
	{
		for (size_t i = 0; i < dodavanePolotovary_->size(); ++i)
		{
			delete (*dodavanePolotovary_)[i];
		}
	}

	delete dodavanePolotovary_;
}

bool BioFarmar::dodavaPolotovar(Polotovar::Typ typPolotovaru)
{
	for (UdajePolotovar* const item : *dodavanePolotovary_)
	{
		if (item->dajTypPolotovaru() == typPolotovaru)
		{
			return true;
		}
	}
	return false;
}

double BioFarmar::dajCenuPolotovaru(Polotovar::Typ typPolotovaru)
{
	for (UdajePolotovar* const item : *dodavanePolotovary_)
	{
		if (item->dajTypPolotovaru() == typPolotovaru)
		{
			return item->getCena();
		}
	}
	return -1;
}

double BioFarmar::dajMnozstvoPolotovaru(Polotovar::Typ typPolotovaru)
{
	for (UdajePolotovar* const item : *dodavanePolotovary_)
	{
		if (item->dajTypPolotovaru() == typPolotovaru)
		{
			return item->getMnozstvo();
		}
	}
	return -1;
}

double BioFarmar::dajPriemernuCenuPolotovaru(Polotovar::Typ typPolotovaru)
{
	for (UdajePolotovar* const item : *dodavanePolotovary_)
	{
		if (item->dajTypPolotovaru() == typPolotovaru)
		{
			return item->getPriemernaCena();
		}
	}
	return -1;
}

double BioFarmar::predajPolotovar(Polotovar::Typ typPolotovaru, double dopytovaneMnozstvo)
{
	UdajePolotovar * udaje_polotovar = dajUdajePolotovar(typPolotovaru);
	if (udaje_polotovar != nullptr)
	{
		return udaje_polotovar->znizMnozstvo(dopytovaneMnozstvo);
	}
	return 0;
}

bool BioFarmar::pridajNovyPolotovar(Polotovar::Typ typPolotovaru)
{
	if (!dodavaPolotovar(typPolotovaru))
	{
		UdajePolotovar * udaje = new UdajePolotovar(typPolotovaru);
		dodavanePolotovary_->add(udaje);
		return true;
	}
	return false;
}

void BioFarmar::aktualizuj()
{
	for (UdajePolotovar* const item : *dodavanePolotovary_)
	{
		item->aktualizuj();
	}
}

structures::Array<Polotovar::Typ>* BioFarmar::dajPolotovary()
{
	structures::Array<Polotovar::Typ> * typPolotovarov = new structures::Array<Polotovar::Typ>(dodavanePolotovary_->size());
	int index = 0;
	for (UdajePolotovar* const item : *dodavanePolotovary_)
	{
		(*typPolotovarov)[index] = item->dajTypPolotovaru();
		index++;
	}
	return typPolotovarov;
}

void BioFarmar::zapisSa(ofstream * outFile)
{
	*outFile << nazov_ << endl;

	// Dodavane polotovary
	*outFile << dodavanePolotovary_->size() << endl;
	for (UdajePolotovar* const item : *dodavanePolotovary_)
	{
		item->zapisSa(outFile);
	}
}

void BioFarmar::nacitajSa(ifstream * inFile)
{
	*inFile >> nazov_;

	size_t pocet = 0;
	*inFile >> pocet;
	for (int i = 0; i < pocet; ++i)
	{
		UdajePolotovar * novy = new UdajePolotovar();
		novy->nacitajSa(inFile);
		dodavanePolotovary_->add(novy);
	}
}

UdajePolotovar* BioFarmar::dajUdajePolotovar(Polotovar::Typ typPolotovaru)
{
	for (UdajePolotovar * item : *dodavanePolotovary_)
	{
		if (item->dajTypPolotovaru() == typPolotovaru)
		{
			return item;
		}
	}
	return nullptr;
}

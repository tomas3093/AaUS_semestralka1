#pragma once
#include "Vozidlo.h"

/// <summary> Trieda reprezentujuca vozidlo na rozvoz tovaru v priebehu procesu naplnania. </summary>
class NaplnaneVozidlo
{
public:
	/// <summary> Konstruktor. </summary>
	NaplnaneVozidlo(Vozidlo * vozidlo);

	/// <summary> Destruktor. </summary>
	~NaplnaneVozidlo();

	Vozidlo * dajVozidlo() { return vozidlo_; }
	double dajVolnuKapacitu() { return volnaKapacita_; }

	/// <summary> Prida do vozidla objednavku. Aktualizuje volnu kapacitu a pocet regionov nakladaneho vozidla. 
	///Ak sa pridanie podarilo vrati true, inak false. </summary>
	bool pridajObjednavku(ObjednavkaTovaru * novaObjednavka);

	/// <summary> Vrati prevadkove naklady potrebne na rozvoz nalozenych objednavok. </summary>
	double dajPrevadzkoveNakladyJazdy();

private:
	/// <summary> Vozidlo, ktore sa naplna. </summary>
	Vozidlo * vozidlo_;

	/// <summary> Zoznam objednavok, ktore uz su nalozene vo vozidle. </summary>
	structures::List<ObjednavkaTovaru *> * objednavky_;
	
	/// <summary> Zostavajuca volna kapacita vozidla. </summary>
	double volnaKapacita_;

	/// <summary> Regiony, do ktorych bude vozidlo rozvazat objednavky. </summary>
	structures::List<int> * regiony_;
};


inline NaplnaneVozidlo::NaplnaneVozidlo(Vozidlo * vozidlo)
	:vozidlo_(vozidlo), objednavky_(new structures::LinkedList<ObjednavkaTovaru *>()), 
	volnaKapacita_(vozidlo->dajNosnostVozidla()), regiony_(new structures::LinkedList<int>())
	
{
}


inline NaplnaneVozidlo::~NaplnaneVozidlo()
{
	delete objednavky_;
	delete regiony_;
}

inline bool NaplnaneVozidlo::pridajObjednavku(ObjednavkaTovaru* novaObjednavka)
{
	if (volnaKapacita_ < novaObjednavka->dajMnozstvo())
	{
		return false;
	}

	objednavky_->add(novaObjednavka);
	volnaKapacita_ -= novaObjednavka->dajMnozstvo();

	// Zisti ci je nova objednavka z noveho regionu
	int region = novaObjednavka->dajZakaznika()->dajRegion();
	bool jeNovyRegion = true;
	for (const int item : *regiony_)
	{
		if (item == region)
		{
			jeNovyRegion = false;
			break;
		}
	}

	if (jeNovyRegion)
	{
		regiony_->add(region);
	}
	return true;
}

inline double NaplnaneVozidlo::dajPrevadzkoveNakladyJazdy()
{
	return regiony_->size() * vozidlo_->dajJednotkoveNaklady();
}

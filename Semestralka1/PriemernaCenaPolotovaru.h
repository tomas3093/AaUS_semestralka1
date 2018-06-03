#pragma once

#include "types.h"
#include "BioFarmar.h"

/// <summary> Trieda reprezentuje priemernu nakupnu cenu polotovaru dodavanu konkretnym biofarmarom. </summary>
class PriemernaCenaPolotovaru
{
public:
	PriemernaCenaPolotovaru(BioFarmar * farmar, Polotovar::Typ typPolotovaru, double priemernaCena);
	~PriemernaCenaPolotovaru();

	BioFarmar * dajBioFarmara() { return bioFarmar_; }
	Polotovar::Typ dajTypPolotovaru() { return typPolotovaru_; }
	double dajPriemernuCenu() { return priemernaCena_; }

private:
	BioFarmar * bioFarmar_;
	Polotovar::Typ typPolotovaru_;
	double priemernaCena_;
};


inline PriemernaCenaPolotovaru::PriemernaCenaPolotovaru(BioFarmar * farmar, Polotovar::Typ typPolotovaru, double priemernaCena)
	:bioFarmar_(farmar), typPolotovaru_(typPolotovaru), priemernaCena_(priemernaCena)
{
}


inline PriemernaCenaPolotovaru::~PriemernaCenaPolotovaru()
{
}

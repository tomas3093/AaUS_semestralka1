#pragma once
#include "types.h"
#include "structures/queue/implicit_queue.h"

/// <summary> Udaje o konkretnom polotovare, ktory dodava farmar </summary>
class UdajePolotovar
{
public:
	/// <summary> Konstruktor. </summary>
	UdajePolotovar();

	/// <summary> Konstruktor. Vytvori udaje o zadanom polotovare pre konkretneho farmara. Cena, mnozstvo a priemerna cena sa nastavia na nulu. </summary>
	UdajePolotovar(Polotovar::Typ typPolotovaru);

	/// <summary> Destruktor </summary>
	~UdajePolotovar();

	/// <summary> Ak je dopytovane mnozstvo vacsie ako mnozstvo ake je farmar schopny dodat, vrati toto mnozstvo. 
	///Inak vrati dopytovane mnozstvo. Vypocita novu priemernu nakupnu cenu a nastavi priznak aktualizovania. </summary>
	double znizMnozstvo(double nakupneMnozstvo);

	/// <summary> Nahodne rozhodne a nastavi cenu a mnozstvo dodavaneho polotovaru. 
	///Ak sa v dany den neaktualizovala priemerna cena, dosadi do historie cien na dany den hodnotu -1. </summary>
	void aktualizuj();

	Polotovar::Typ dajTypPolotovaru() { return typPolotovaru_; }
	double getCena() { return cena_; }
	double getMnozstvo() { return mnozstvo_; }
	double getPriemernaCena() { return priemernaCena_; }

	/// <summary> Zapise objekt do suboru. </summary>
	void zapisSa(ofstream * outFile);

	/// <summary> Nacita objekt zo suboru. </summary>
	void nacitajSa(ifstream * inFile);

private:
	/// <summary> Typ polotovaru, ku ktoremu sa vztahuju udaje. </summary>
	Polotovar::Typ typPolotovaru_;
	
	/// <summary> Predajna cena polotovaru. </summary>
	double cena_;

	/// <summary> Mnozstvo polotovaru, ktore je farmar schopny dodat. </summary>
	double mnozstvo_;

	/// <summary> Priemerna cena, za ktoru sa polotovar u farmara nakupoval v urcenom casovom obdobi. </summary>
	double priemernaCena_;

	/// <summary> Sucet nakupnych cien, ktore su vo fronte. </summary>
	double sucetPredchadzajucichCien_;

	/// <summary> Priznak, ktory urcuje ci bola v dany den aktualizovana priemerna nakupna cena. </summary>
	bool aktualizovanaPriemCena_;

	/// <summary> Predchadzajuce nakupne ceny za urcene casove obdobie, na zaklade 
	///ktorych sa bude vypocitavat priemerna nakupna cena. </summary>
	structures::Queue<double> * nakupneCeny_;

	/// <summary> Vygeneruje a nastavi nahodnu cenu polotovaru, za ktoru je farmar ochotny predavat. </summary>
	void setNahodnaCena();

	/// <summary> Vygeneruje a nastavi nahodne mnozstvo polotovaru, ktore je schopny farmar dodat. </summary>
	void setNahodneMnozstvo();
};


inline UdajePolotovar::UdajePolotovar()
	:typPolotovaru_(Polotovar::Typ::ZEMIAKY), cena_(0), mnozstvo_(0), priemernaCena_(0),
	sucetPredchadzajucichCien_(0), aktualizovanaPriemCena_(false), 
	nakupneCeny_(new structures::ImplicitQueue<double>(PRIEMERNA_CENA_OBDOBIE_DNI))
{
}

inline UdajePolotovar::UdajePolotovar(Polotovar::Typ typPolotovaru)
	:typPolotovaru_(typPolotovaru), cena_(0), mnozstvo_(0), priemernaCena_(0), 
	sucetPredchadzajucichCien_(0), aktualizovanaPriemCena_(false),
	nakupneCeny_(new structures::ImplicitQueue<double>(PRIEMERNA_CENA_OBDOBIE_DNI))
{
	setNahodnaCena();
	setNahodneMnozstvo();
}

inline UdajePolotovar::~UdajePolotovar()
{
	delete nakupneCeny_;
}

inline void UdajePolotovar::setNahodnaCena()
{
	switch (typPolotovaru_)
	{
	case Polotovar::Typ::ZEMIAKY:
		cena_ = fRand(POLOTOVARY_CENA_MIN, POLOTOVARY_CENA_MAX_ZEMIAKY);
		break;

	case Polotovar::Typ::OCHUCOVADLA:
		cena_ = fRand(POLOTOVARY_CENA_MIN, POLOTOVARY_CENA_MAX_OCHUCOVADLA);
		break;

	case Polotovar::Typ::OLEJ:
		cena_ = fRand(POLOTOVARY_CENA_MIN, POLOTOVARY_CENA_MAX_OLEJ);
		break;

	default:
		cena_ = 0;
	}
}

inline void UdajePolotovar::setNahodneMnozstvo()
{
	switch (typPolotovaru_)
	{
	case Polotovar::Typ::ZEMIAKY:
		mnozstvo_ = fRand(POLOTOVARY_MNOZSTVO_MIN, POLOTOVARY_MNOZSTVO_MAX_ZEMIAKY);
		break;

	case Polotovar::Typ::OCHUCOVADLA:
		mnozstvo_ = fRand(POLOTOVARY_MNOZSTVO_MIN, POLOTOVARY_MNOZSTVO_MAX_OCHUCOVADLA);
		break;

	case Polotovar::Typ::OLEJ:
		mnozstvo_ = fRand(POLOTOVARY_MNOZSTVO_MIN, POLOTOVARY_MNOZSTVO_MAX_OLEJ);
		break;

	default:
		mnozstvo_ = 0;
	}
}

inline double UdajePolotovar::znizMnozstvo(double nakupneMnozstvo)
{
	if (mnozstvo_ > 0 && nakupneMnozstvo > 0)
	{
		// Ak je plny front
		if (nakupneCeny_->size() == PRIEMERNA_CENA_OBDOBIE_DNI)
		{
			sucetPredchadzajucichCien_ -= nakupneCeny_->pop();
		}

		// Vypocet priemernej nakupnej ceny
		nakupneCeny_->push(cena_);
		sucetPredchadzajucichCien_ += cena_;
		priemernaCena_ = sucetPredchadzajucichCien_ / nakupneCeny_->size();
		aktualizovanaPriemCena_ = true;

		if (nakupneMnozstvo > mnozstvo_)
		{
			return mnozstvo_;
		}
		return nakupneMnozstvo;
	}
	return 0;
}

inline void UdajePolotovar::aktualizuj()
{
	// Rozhodnutie ci farmar zmeni cenu
	if (fRand01() > 0.6)
	{
		setNahodnaCena();
	}
	setNahodneMnozstvo();

	// Aktualizuje front predchadzajucich cien
	if (aktualizovanaPriemCena_)
	{
		aktualizovanaPriemCena_ = false;
	}
	else
	{
		// Ak je front plny
		if (nakupneCeny_->size() == PRIEMERNA_CENA_OBDOBIE_DNI)
		{
			double vybrataCena = nakupneCeny_->pop();
			if (vybrataCena > 0)
			{
				sucetPredchadzajucichCien_ -= vybrataCena;
			}
		}
		nakupneCeny_->push(-1);
		aktualizovanaPriemCena_ = true;
	}
}

inline void UdajePolotovar::zapisSa(ofstream * outFile)
{
	*outFile << Polotovar::toNumber(typPolotovaru_) << endl;
	*outFile << cena_ << endl;
	*outFile << mnozstvo_ << endl;
	*outFile << priemernaCena_ << endl;
	*outFile << sucetPredchadzajucichCien_ << endl;
	*outFile << aktualizovanaPriemCena_ << endl;
	
	// Front nakupnych cien
	int pocet = nakupneCeny_->size();
	*outFile << pocet << endl;
	for (int i = 0; i < pocet; ++i)
	{
		*outFile << nakupneCeny_->pop() << endl;
	}

}

inline void UdajePolotovar::nacitajSa(ifstream * inFile)
{
	size_t typ;
	*inFile >> typ;
	typPolotovaru_ = Polotovar::toTyp(typ);

	*inFile >> cena_;
	*inFile >> mnozstvo_;
	*inFile >> priemernaCena_;
	*inFile >> sucetPredchadzajucichCien_;
	*inFile >> aktualizovanaPriemCena_;

	// Front priemernych cien
	int pocet = 0;
	*inFile >> pocet;
	for (int i = 0; i < pocet; ++i)
	{
		double cena;
		*inFile >> cena;
		nakupneCeny_->push(cena);
	}
}


#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "structures/list/array_list.h"

using namespace std;

/// *** KONSTANTY ***
// Subory pre ukladanie/loadovanie dat
const string FILE_NAME_SYSTEM = "data/system.txt";
const string FILE_NAME_BIOFARMARI = "data/farmari.txt";
const string FILE_NAME_VOZIDLA = "data/vozidla.txt";
const string FILE_NAME_ZAKAZNICI = "data/zakaznici.txt";
const string FILE_NAME_OBJEDNAVKY_TOVARU = "data/objednavky_tovar.txt";
const string FILE_NAME_ZASOBY = "data/zasoby.txt";

// Mnozstva a ceny polotovarov
const int POLOTOVARY_MNOZSTVO_MIN = 0;
const int POLOTOVARY_MNOZSTVO_MAX_ZEMIAKY = 5000;
const int POLOTOVARY_MNOZSTVO_MAX_OLEJ = 1000;
const int POLOTOVARY_MNOZSTVO_MAX_OCHUCOVADLA = 50;			// v kg
const int POLOTOVARY_CENA_MIN = 1;
const int POLOTOVARY_CENA_MAX_ZEMIAKY = 3;
const int POLOTOVARY_CENA_MAX_OLEJ = 4;
const int POLOTOVARY_CENA_MAX_OCHUCOVADLA = 2;

// Receptury (vsetko v zakladnych jednotkach kg, l, ...)
const double TOVAR_ZEM_HRANOLKY_POLOTOVAR_ZEMIAKY = 1.5;	// Na vyrobu 1 jednotky zemiakovych hranoliek, potrebujem 1.5 jednotky zemiakov
const double TOVAR_ZEM_HRANOLKY_POLOTOVAR_OLEJ = 0.2;
const double TOVAR_ZEM_LUPIENKY_POLOTOVAR_ZEMIAKY = 2;
const double TOVAR_ZEM_LUPIENKY_POLOTOVAR_OLEJ = 0.4;
const double TOVAR_ZEM_LUPIENKY_POLOTOVAR_OCHUCOVADLA = 0.02;	// v kg

// Pocty poloziek
const size_t POLOTOVARY_TYP_POCET = 3;
const size_t TOVARY_TYP_POCET = 2;

// Pocet dni pre vypocet priemernej ceny
const int PRIEMERNA_CENA_OBDOBIE_DNI = 30;

// Minimalny pocet dni na dodanie tovaru zakaznikom
const int POCET_DNI_DODANIE_TOVARU = 7;

// Cisla regionu
const int REGION_CISLO_MIN = 1;
const int REGION_CISLO_MAX = 8;

// Typy polotovarov
class Polotovar 
{
public:
	// Indexuje sa od nuly!
	enum class Typ {
		ZEMIAKY = 0,
		OLEJ = 1,
		OCHUCOVADLA = 2
	};

	// Ak sa prida novy polotovar, musi sa zvysit!
	static const size_t pocetTypov = size_t(POLOTOVARY_TYP_POCET);

	// Vrati ciselnu reprezentaciu zadaneho typu polotovaru
	static size_t toNumber(Polotovar::Typ typPolotovaru)
	{
		switch (typPolotovaru)
		{
		case Typ::ZEMIAKY:
			return 0;
		case Typ::OLEJ:
			return 1;
		case Typ::OCHUCOVADLA:
			return 2;
		default:
			return SIZE_MAX;
		}
	}

	// Vrati typ polotovaru na zaklade indexu
	static Polotovar::Typ toTyp(size_t typ)
	{
		switch (typ)
		{
		case 0:
			return Typ::ZEMIAKY;
		case 1:
			return Typ::OLEJ;
		case 2:
			return Typ::OCHUCOVADLA;
		default:
			return Typ::OCHUCOVADLA;
		}
	}

	// Vrati nazov ako retazec
	static string toString(Polotovar::Typ typPolotovaru)
	{
		string nazov = "N/A";
		switch (typPolotovaru)
		{
		case Polotovar::Typ::ZEMIAKY:
			nazov = "Zemiaky";
			break;
		case Polotovar::Typ::OLEJ:
			nazov = "Olej";
			break;
		case Polotovar::Typ::OCHUCOVADLA:
			nazov = "Ochucovadla";
			break;
		}
		return nazov;
	}
};

// Typy vyrabaneho tovaru
class Tovar
{
public: 
	// Indexuje sa od nuly!
	enum class Typ {
		ZEM_HRANOLKY = 0,
		ZEM_LUPIENKY = 1
	};

	// Ak sa prida novy tovar, musi sa zvysit!
	static const size_t pocetTypov = size_t(TOVARY_TYP_POCET);

	// Vrati typ tovaru na zaklade indexu
	static Tovar::Typ toTyp(size_t typ)
	{
		switch (typ)
		{
		case 0:
			return Typ::ZEM_HRANOLKY;
		case 1:
			return Typ::ZEM_LUPIENKY;
		default:
			return Typ::ZEM_HRANOLKY;
		}
	}

	// Vrati ciselnu reprezentaciu zadaneho typu tovaru
	static size_t toNumber(Tovar::Typ typTovaru)
	{
		switch (typTovaru)
		{
		case Typ::ZEM_HRANOLKY:
			return 0;
		case Typ::ZEM_LUPIENKY:
			return 1;
		default:
			return SIZE_MAX;
		}
	}

	// Vrati nazov ako retazec
	static string toString(Tovar::Typ typTovaru)
	{
		string nazov = "N/A";
		switch (typTovaru)
		{
		case Tovar::Typ::ZEM_HRANOLKY:
			nazov = "Zemiakove hranolky";
			break;
		case Tovar::Typ::ZEM_LUPIENKY:
			nazov = "Zemiakove lupienky";
			break;
		}
		return nazov;
	}
};

// Stav objednavky
enum class StavObjednavky
{
	ZREALIZOVANA = 1,	// Odovzdana zakaznikovi
	ZAMIETNUTA = 2,		// Prekrocena celkova kapacita vozidiel v zadany den dodania
	ZRUSENA = 3,		// Zrusena v dosledku nedostatku polotovarov
	SPRACOVAVANA = 4	// Vsetko ostatne
};

// Vrati ciselnu reprezentaciu zadaneho typu tovaru
static size_t stavObjednavkytoNumber(StavObjednavky stavObjednavky)
{
	switch (stavObjednavky)
	{
	case StavObjednavky::ZREALIZOVANA:
		return 1;
	case StavObjednavky::ZAMIETNUTA:
		return 2;
	case StavObjednavky::ZRUSENA:
		return 3;
	case StavObjednavky::SPRACOVAVANA:
		return 4;
	default:
		return SIZE_MAX;
	}
}

// Vrati typ tovaru na zaklade indexu
inline StavObjednavky stavObjednavkytoStav(size_t stavObjednavky)
{
	switch (stavObjednavky)
	{
	case 1:
		return StavObjednavky::ZREALIZOVANA;
	case 2:
		return StavObjednavky::ZAMIETNUTA;
	case 3:
		return StavObjednavky::ZRUSENA;
	case 4:
		return StavObjednavky::SPRACOVAVANA;
	default:
		return StavObjednavky::ZRUSENA;
	}
}

/// <summary> Vrati nazov zadaneho typu stavu objednavky. </summary>
inline string dajNazovStavObjednavky(StavObjednavky stavObjednavky)
{
	string nazov = "N/A";
	switch (stavObjednavky)
	{
	case StavObjednavky::SPRACOVAVANA:
		nazov = "Spracovavana";
		break;
	case StavObjednavky::ZREALIZOVANA:
		nazov = "Vybavena";
		break;
	case StavObjednavky::ZAMIETNUTA:
		nazov = "Zamietnuta";
		break;
	case StavObjednavky::ZRUSENA:
		nazov = "Zrusena";
		break;
	}
	return nazov;
}

/// <summary> Vrati mnozstvo zadaneho polotovaru, ktore je potrebne na vyrobenie 
///jednej jednotky zadaneho typu Tovaru. </summary>
inline double dajMnozstvoPolotovaruRecept(Polotovar::Typ typPolotovaru, Tovar::Typ typTovaru)
{
	switch (typTovaru)
	{
	case Tovar::Typ::ZEM_HRANOLKY:
		switch (typPolotovaru)
		{
		case Polotovar::Typ::ZEMIAKY: return TOVAR_ZEM_HRANOLKY_POLOTOVAR_ZEMIAKY;
		case Polotovar::Typ::OLEJ: return TOVAR_ZEM_HRANOLKY_POLOTOVAR_OLEJ;
			default: return 0;
		}

	case Tovar::Typ::ZEM_LUPIENKY:
		switch (typPolotovaru)
		{
		case Polotovar::Typ::ZEMIAKY: return TOVAR_ZEM_LUPIENKY_POLOTOVAR_ZEMIAKY;
		case Polotovar::Typ::OLEJ: return TOVAR_ZEM_LUPIENKY_POLOTOVAR_OLEJ;
		case Polotovar::Typ::OCHUCOVADLA: return TOVAR_ZEM_LUPIENKY_POLOTOVAR_OCHUCOVADLA;
		default: return 0;
		}

	default: return 0;
	}
}

/// <summary> Generator nahodneho cisla z intervalu (fMin, fMax). </summary> 
inline double fRand(double fMin, double fMax)
{
	double f = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
	return fMin + f * (fMax - fMin);
}

/// <summary> Generator nahodnych cisiel z intervalu (0,1). </summary>
inline double fRand01() { return static_cast<double>(rand()) / RAND_MAX; }

/// <summary> Vypise chybove hlasenie na konzolu. </summary>
inline void showErrorMessage(string message) { cout << "\n\n *** Chyba: " + message + " ***\n\n"; }
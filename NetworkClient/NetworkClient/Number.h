#pragma once
#include <string>
#include <iostream>
#include <cstdlib>
#include "Convertable.h"
#include "PluginSettings.h"

class PLUGIN_API Bool : Convertable
{
public:
	Bool(bool bl) : m_bool(bl) { }

	virtual std::string ToString() override;
	virtual void SetValue(std::string toConv) override;

	bool m_bool;
};

struct PLUGIN_API Int : Convertable
{
public:
	Int(int it) : m_int(it) { }

	virtual std::string ToString() override;
	virtual void SetValue(std::string toConv) override;

	int m_int;
};

struct PLUGIN_API Long : Convertable
{
public:
	Long(long lng) : m_long(lng) { }

	virtual std::string ToString() override;
	virtual void SetValue(std::string toConv) override;

	long m_long;
};

struct PLUGIN_API Short : Convertable
{
public:
	Short(short srt) : m_short(srt) { }

	virtual std::string ToString() override;
	virtual void SetValue(std::string toConv) override;

	short m_short;
};

struct PLUGIN_API Float : Convertable
{
public:
	Float(float flt) : m_float(flt) { }

	virtual std::string ToString() override;
	virtual void SetValue(std::string toConv) override;

	float m_float;
};

struct PLUGIN_API Double : Convertable
{
public:
	Double(double dbl) : m_double(dbl) { }

	virtual std::string ToString() override;
	virtual void SetValue(std::string toConv) override;

	double m_double;
};